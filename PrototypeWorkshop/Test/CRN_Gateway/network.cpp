#include "network.h"

#include <unistd.h>

int ContextNetwork::run() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//	localAddress.s_addr = inet_addr("127.0.0.1");

	/*
	 * Create one socket each for TCP and for UDP
	 */
	UDP_sock = make_UDP_socket(PORT_UDP_CONTEXT);
	TCP_sock = make_TCP_socket(PORT_TCP_CONTEXT);

	/*
	 * Listen on TCP socket
	 */
	if (listen(TCP_sock, LISTEN_BACKLOG) == -1) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	/* Initialize the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(UDP_sock, &active_fd_set);
	FD_SET(TCP_sock, &active_fd_set);

	FD_ZERO(&read_fd_set);
	FD_ZERO(&write_fd_set);

	std::cout << std::endl;
	std::cout << "Gateway's Main Loop Start:" << std::endl;
	std::cout << LINE_SEPARATOR << std::endl;

	while (keep_going) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] keep_going: " << keep_going << std::endl;

		/*
		 * Acknowledge active listener sockets
		 */
		read_fd_set = active_fd_set;

		/*
		 * Waiting for the next packet or continue processing received one
		 */
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "Waiting for the next packet or continue processing received one" << std::endl;

		if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0 && keep_going) {
			std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
		else {
			if (!keep_going) {
				continue;
			}
		}

		/*
		 * Searching set of file descriptors for socket with data
		 */
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "Searching set of file descriptors for socket with data" << std::endl;

		for (read_fd = 0; read_fd < FD_SETSIZE; ++read_fd) {

			if (FD_ISSET(read_fd, &read_fd_set)) {

				/*
				 * Data from UDP socket found
				 */
				if (read_fd == UDP_sock) {
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Data from UDP socket (fd: " <<  read_fd << ") found" << std::endl;

					/*
					 * Read data from UDP socket in buffer
					 */
					UDP_address_size = sizeof(UDP_addr);
					UDP_bytes_received = recvfrom(UDP_sock, UDP_buffer, sizeof(UDP_buffer), 0, (struct sockaddr*) &UDP_addr, &UDP_address_size);
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] UDP_bytes_received: " << UDP_bytes_received << std::endl;

					if (UDP_bytes_received < 0) {
						std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
						perror("ERROR");
						exit(EXIT_FAILURE);
					}

					/*
					 * Process data from buffer
					 */
					uuid_t UDP_uuid;
					memcpy(UDP_uuid, (UDP_buffer+4), 16);

					std::cout << getUuidString(UDP_uuid) << " : " <<
							UDP_bytes_received << " bytes" <<
							" from " << inet_ntoa(UDP_addr.sin_addr) << ":" << ntohs(UDP_addr.sin_port) <<
							" received" << std::endl;

					ContextPacket *receivedContextPacket = new ContextPacket();
					receivedContextPacket->deserialize(UDP_buffer);

					receivedContextPacket->setIpAddress(inet_addr(inet_ntoa(UDP_addr.sin_addr)));
					receivedContextPacket->setPortNumber(UDP_addr.sin_port);

					receivedContextPacket->processUDP(UDP_sock, (struct sockaddr *) &UDP_addr);


					ContextPacket *answerContextPacket = new ContextPacket();

					answerContextPacket->printPacket();


					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] answerContextPacket->getSize(): " << answerContextPacket->getSize() << std::endl;
					char sendBuffer[answerContextPacket->getSize()];



					int nbytes;
					nbytes = sendto(UDP_sock, sendBuffer,
							answerContextPacket->getSize(), 0,
							(struct sockaddr *) &UDP_addr,
							sizeof(struct sockaddr));
					if (nbytes < 0) {
						perror("sendto(UDP_sock)");
						exit(EXIT_FAILURE);
					}
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] sendto(UDP_sock): " << nbytes << std::endl;




					delete receivedContextPacket;

//					close(UDP_sock);

					continue;
				}

				/*
				 * Data from TCP socket found
				 */
				if (read_fd == TCP_sock) {
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Data from TCP socket (fd: " <<  read_fd << ") found" << std::endl;

					int acceptSocket;

					/*
					 * Accept TCP socket
					 */
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Accept TCP socket (fd: " <<  read_fd << ")" << std::endl;

					acceptLength = sizeof(TCP_addr);
					acceptSocket = accept(TCP_sock, (struct sockaddr*) &TCP_addr, &acceptLength);

					if (acceptSocket < 0) {
						std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
						perror("ERROR");
						exit(EXIT_FAILURE);
					}

					/*
					 * Put accepted TCP in active socket set
					 */
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Put accepted TCP in active socket set" << std::endl;

					FD_SET(acceptSocket, &active_fd_set);
				}

				/*
				 * Read data from accepted TCP socket in buffer
				 */
				else {
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Read data from accepted TCP socket (fd: " <<  read_fd << ") in buffer" << std::endl;

					TCP_bytes_received = recv(read_fd, TCP_buffer, sizeof(TCP_buffer) - 1, 0);
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << TCP_bytes_received << " bytes received" << std::endl;

					if (TCP_bytes_received < 0) {
						perror("read");
						exit(EXIT_FAILURE);
					} else if (TCP_bytes_received == 0)
						/* End-of-file. */
						return -1;
					else {

						/*
						 * Process data from buffer
						 */
						uuid_t acceptUuid;
						memcpy(acceptUuid, (TCP_buffer+4), 16);

						std::cout << getUuidString(acceptUuid) << " : " <<
								TCP_bytes_received << " bytes" <<
								" from " << inet_ntoa(TCP_addr.sin_addr) << ":" << ntohs(TCP_addr.sin_port) <<
								" received" << std::endl;

						sizeAndContextStruct.first = new IpAddress(acceptUuid, TCP_addr);
						sizeAndContextStruct.second = TCP_buffer;

						if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(acceptSocket " << acceptSocket << ")" << std::endl;
						close(acceptSocket);

						/*
						 * Store IP Address
						 */
						senderAddressArray[read_fd] = new IpAddress(acceptUuid, TCP_addr);

						/* create a new thread that will execute 'receiveTcpThread()' */
						if (pthread_create(&p_thread, NULL, receiveTcpThread, (void*) &sizeAndContextStruct) != 0) {
							perror("pthread_create(receiveTcpThread) failed");
							return 4;
						}
						FD_CLR(read_fd, &active_fd_set);

						/* ######################### */

						FD_SET(read_fd, &write_fd_set);

						int fd_count = select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL);
//!!!
//						if (fd_count == -1) {
//							perror("select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL) failed");
//							exit(EXIT_FAILURE);
//						}
//!!!

						/* Service all the sockets with output pending. */
						for (write_fd = 0; write_fd < FD_SETSIZE; ++write_fd) {

							if (FD_ISSET(write_fd, &write_fd_set)) {

								ContextPacket *receipt = new ContextPacket(senderAddressArray[write_fd]);
								receipt->deserialize(TCP_buffer);

//								receipt->answerTCP();

								char answerBuffer[receipt->getSize()];
								receipt->serialize(answerBuffer);

								TCP_bytes_to_send = write(write_fd, answerBuffer, receipt->getSize());

								if (TCP_bytes_to_send < 0) {
									perror("ERROR writing to socket");
								} else {
//									printf("Answer sent: \"I got your message\"\n");
									break;
								}
							}
						}

						if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(read_fd " << read_fd << ")" << std::endl;
						close(read_fd);

						FD_CLR(write_fd, &active_fd_set);

						/* ######################### */

					}
				}
			}
		}
	}
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(TCP_sock " << TCP_sock << ")" << std::endl;
	close(TCP_sock);

	if(! keep_going) {
		std::cout << "Main loop cancelled normally." << std::endl;
	}

//	delete storage;

	return EXIT_SUCCESS;
}

void ContextNetwork::stop() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	keep_going = 0;
}

int ContextNetwork::make_TCP_socket(uint16_t port) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	int sock;
	struct sockaddr_in name;

	/* Create the socket. */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	/* Give the socket a name. */
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	return sock;
}

int ContextNetwork::make_UDP_socket(uint16_t port) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	struct sockaddr_in name;
	int sock;

	/* Create the socket. */
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Bind a name to the socket. */
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.178.18");

	if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	return sock;
}

void* receiveTcpThread(void* data) {
	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	std::pair<IpAddress*, char*> incoming = *((std::pair<IpAddress*, char*>*) data);

	ContextPacket *receivedContextPacket = new ContextPacket();

	receivedContextPacket->deserialize(incoming.second);

	receivedContextPacket->setIpAddress(incoming.first->getSockAddress().sin_addr.s_addr);

	receivedContextPacket->setPortNumber(incoming.first->getSockAddress().sin_port);

	receivedContextPacket->processTCP();

	/* terminate the thread */
	pthread_exit(NULL);
}
