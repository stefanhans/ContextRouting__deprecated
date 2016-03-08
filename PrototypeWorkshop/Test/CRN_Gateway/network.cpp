#include "network.h"

#include <unistd.h>

int ContextNetwork::run() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	/*
	 * Create one socket each for TCP and for UDP
	 */
	UDP_sock = make_UDP_socket(PORT_UDP_DEFAULT);
	TCP_sock = make_TCP_socket(PORT_TCP_DEFAULT);

	/*
	 * Listen on TCP socket
	 */
	if (listen(TCP_sock, LISTEN_BACKLOG) == -1) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	/*
	 * Initialize the set of active sockets.
	 */
	FD_ZERO(&active_fd_set);
	FD_SET(UDP_sock, &active_fd_set);
	FD_SET(TCP_sock, &active_fd_set);

	FD_ZERO(&read_fd_set);
	FD_ZERO(&write_fd_set);

	std::cout << std::endl;
	std::cout << "Gateway's Main Loop Start:" << std::endl;
	std::cout << LINE_SEPARATOR << std::endl;

	/*
	 * Main loop
	 */
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
							" received via UDP" << std::endl;

					ContextPacket *receivedContextPacket = new ContextPacket();
					receivedContextPacket->deserialize(UDP_buffer);

					receivedContextPacket->setIpAddress(inet_addr(inet_ntoa(UDP_addr.sin_addr)));
					receivedContextPacket->setPortNumber(UDP_addr.sin_port);

					receivedContextPacket->processUDP(UDP_sock, (struct sockaddr *) &UDP_addr, UDP_bytes_received);


//					delete receivedContextPacket;

					continue;

				} // Data from UDP socket found

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

				} // Data from TCP socket found

				/*
				 * Read data from accepted TCP socket in buffer
				 */
				else {
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Read data from accepted TCP socket (fd: " <<  read_fd << ") in buffer" << std::endl;

					TCP_bytes_received = recv(read_fd, TCP_buffer, sizeof(TCP_buffer) - 1, 0);
					if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << TCP_bytes_received << " bytes received" << std::endl;

					/*
					 * TCP receive failed
					 */
					if (TCP_bytes_received < 0) {
						perror("TCP_bytes_received < 0");

					}
					else if (TCP_bytes_received == 0) {
						if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << TCP_bytes_received << " bytes received" << std::endl;
						break;
					}

					/*
					 * TCP receive succeeded
					 */
					else {

						/*
						 * Check CIP_FORMAT_ERROR_OUT_OF_RANGE and reply on read_fd accordingly
						 */
						if(TCP_bytes_received < 42 || TCP_bytes_received > 1062) {
							std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] TCP_bytes_received: " << TCP_bytes_received <<  std::endl;

							errorContextPacket = new ContextPacket();

							/**
							 * Create header data for error
							 */
							errorHeader[0] = (byte_t) CIP_FORMAT_ERROR;
							errorHeader[1] = (byte_t) ERROR_PRIORITY_NOTICE;
							errorHeader[2] = (byte_t) CIP_FORMAT_ERROR_OUT_OF_RANGE;

							/*
							 * Create CIP for TCP reply with error
							 */
							errorContextPacket->setHeaderType(HEADER_TYPE_ERROR);
							errorContextPacket->setHeaderSize(3);
							errorContextPacket->setHeaderData(errorHeader);

							if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] CIP_FORMAT_ERROR_OUT_OF_RANGE" << std::endl;
							if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
							if (PRINT_PACKET_DEBUG) errorContextPacket->printPacket();

							char errorBuffer[errorContextPacket->getSize()];
							errorContextPacket->serialize(errorBuffer);

							TCP_bytes_to_send = write(read_fd, errorBuffer, errorContextPacket->getSize());

							if (TCP_bytes_to_send < 0) {
								perror("write(read_fd, errorBuffer, errorContextPacket->getSize()) failed");
							}
							else {
								if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] write(read_fd, errorBuffer, errorContextPacket->getSize()): " << TCP_bytes_to_send << std::endl;

							}

							std::cout << "XXXXXXXX : " << "Reply error: CIP_FORMAT_ERROR_OUT_OF_RANGE" << std::endl;

							if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(read_fd " << read_fd << ")" << std::endl;
							close(read_fd);

							FD_CLR(read_fd, &active_fd_set);

						} // Check CIP_FORMAT_ERROR_OUT_OF_RANGE and reply on read_fd accordingly

						/*
						 * No CIP_FORMAT_ERROR_OUT_OF_RANGE
						 */
						else {

							/*
							 * Process data from buffer
							 */
							uuid_t acceptUuid;
							memcpy(acceptUuid, (TCP_buffer+4), 16);

							std::cout << getUuidString(acceptUuid) << " : " <<
									TCP_bytes_received << " bytes" <<
									" from " << inet_ntoa(TCP_addr.sin_addr) << ":" << ntohs(TCP_addr.sin_port) <<
									" received via TCP" << std::endl;

							sizeAndContextStruct.first = new IpAddress(acceptUuid, TCP_addr);
							sizeAndContextStruct.second = TCP_buffer;

							if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(acceptSocket " << acceptSocket << ")" << std::endl;
							close(acceptSocket);

							/*
							 * Store IP Address
							 */
							senderAddressArray[read_fd] = new IpAddress(acceptUuid, TCP_addr);

							FD_CLR(read_fd, &active_fd_set);
							FD_SET(read_fd, &write_fd_set);

							int fd_count = select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL);

							if (fd_count == -1) {
								perror("select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL) failed");
							}

							/*
							 * Service all the sockets with output pending.
							 */
							for (write_fd = 0; write_fd < FD_SETSIZE; ++write_fd) {

								if (FD_ISSET(write_fd, &write_fd_set)) {

									ContextPacket *receipt = new ContextPacket(); //senderAddressArray[write_fd]
									receipt->deserialize(TCP_buffer);

									receipt->setIpAddress(inet_addr(inet_ntoa(senderAddressArray[write_fd]->getSockAddress().sin_addr)));
									receipt->setPortNumber(senderAddressArray[write_fd]->getSockAddress().sin_port);

									if (PRINT_PACKETS_DEBUG) receipt->printPacket();


									char replyBuffer[MAXMSG];
									size_t sizeInout = TCP_bytes_received;

									int tcpValidation = createTcpReply(receipt, replyBuffer, sizeInout);
									if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] tcpValidation: " << (int) tcpValidation << std::endl;


									int size = receipt->getSize();
									if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << "size: " << size << std::endl;


									char answerBuffer[size];
									receipt->serialize(answerBuffer);

									TCP_bytes_to_send = write(write_fd, replyBuffer, sizeInout);

									if (TCP_bytes_to_send < 0) {
										perror("ERROR writing to socket");
									}
									else {
										if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << "TCP_bytes_to_send: " << TCP_bytes_to_send << std::endl;
										break;
									}


									if(tcpValidation == 0) {
										if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "tcpValidation == 0" << std::endl;

										/*
										 * Create a new thread that will execute 'receiveTcpThread()'
										 */
										if (pthread_create(&p_thread, NULL, receiveTcpThread, (void*) &sizeAndContextStruct) != 0) {
											perror("pthread_create(receiveTcpThread) failed");

										}
									}

								} // FD_ISSET

							} // Service all the sockets with output pending

							if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(read_fd " << read_fd << ")" << std::endl;
							close(read_fd);

							FD_CLR(write_fd, &active_fd_set);

						} // No CIP_FORMAT_ERROR_OUT_OF_RANGE

					} // Read data from accepted TCP socket in buffer

				} // TCP receive succeeded

			} // IF: FD_ISSET(read_fd, &read_fd_set)

		} // FOR: Searching set of file descriptors for socket with data

	} // WHILE: Main loop

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : " << "close(TCP_sock " << TCP_sock << ")" << std::endl;
	close(TCP_sock);

	if(! keep_going) {
		std::cout << "Main loop cancelled normally." << std::endl;

		return EXIT_SUCCESS;
	}

//	delete storage;

	return EXIT_FAILURE;

} // ContextNetwork::run()

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

int ContextNetwork::createTcpReply(ContextPacket* receivedContextPacket, char* reply_buffer, size_t& size) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;



	/*
	 * Check CIP_FORMAT_ERROR_INCONSISTENT
	 */
	if(receivedContextPacket->getSize() != (size_t) size) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] receivedContextPacket->getSize() != (size_t*) size" << std::endl;

		errorContextPacket = new ContextPacket();

		errorContextPacket->setUuid(receivedContextPacket->getUuid());

		/**
		 * Create header data for error
		 */
		errorHeader[0] = (byte_t) CIP_FORMAT_ERROR;
		errorHeader[1] = (byte_t) ERROR_PRIORITY_NOTICE;
		errorHeader[2] = (byte_t) CIP_FORMAT_ERROR_INCONSISTENT;

		/*
		 * Create CIP for UDP reply with error
		 */
		errorContextPacket->setHeaderType(HEADER_TYPE_ERROR);
		errorContextPacket->setHeaderSize(3);
		errorContextPacket->setHeaderData(errorHeader);


		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] CIP_FORMAT_ERROR_INCONSISTENT" << std::endl;
		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
		if (PRINT_PACKET_DEBUG) errorContextPacket->printPacket();

		size = (size_t) errorContextPacket->getSize();
		errorContextPacket->serialize(reply_buffer);

		return 1;
	}


	/*
	 * Check CIP_FORMAT_ERROR_WRONG_PROTOCOL
	 */
	if(receivedContextPacket->getChannel() == CHANNEL_CI_MATCHING && receivedContextPacket->getRequest() == SERVICE_HEARTBEAT) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] CHANNEL_CI_MATCHING && SERVICE_HEARTBEAT" << std::endl;

		errorContextPacket = new ContextPacket();

		errorContextPacket->setUuid(receivedContextPacket->getUuid());
		errorContextPacket->setRequest(receivedContextPacket->getRequest());
		errorContextPacket->setChannel(receivedContextPacket->getChannel());

		/**
		 * Create header data for error
		 */
		errorHeader[0] = (byte_t) CIP_FORMAT_ERROR;
		errorHeader[1] = (byte_t) ERROR_PRIORITY_NOTICE;
		errorHeader[2] = (byte_t) CIP_FORMAT_ERROR_WRONG_PROTOCOL;

		/*
		 * Create CIP for UDP reply with error
		 */
		errorContextPacket->setHeaderType(HEADER_TYPE_ERROR);
		errorContextPacket->setHeaderSize(3);
		errorContextPacket->setHeaderData(errorHeader);


		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] CIP_FORMAT_ERROR_WRONG_PROTOCOL" << std::endl;
		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
		if (PRINT_PACKET_DEBUG) errorContextPacket->printPacket();

		size = (size_t) errorContextPacket->getSize();
		errorContextPacket->serialize(reply_buffer);

		return 1;
	}

	/*
	 * Default echo like reply
	 */
	receivedContextPacket->setRequest(SERVICE_REPLY);
	receivedContextPacket->setHeaderType(HEADER_TYPE_OK);

	size = (size_t) receivedContextPacket->getSize();
	receivedContextPacket->serialize(reply_buffer);

	return 0;
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
