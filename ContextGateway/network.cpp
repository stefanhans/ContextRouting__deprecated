#include "network.h"

using namespace std;


int ContextNetwork::run() {

	localAddress.s_addr = inet_addr("127.0.0.1");

	listenAddress.sin_addr = localAddress;
	listenAddress.sin_family = AF_INET;
	listenAddress.sin_port = htons(PORT_TCP_CONTEXT);

	printf("Server TCP: \tgoing to listen on %s:%u\n",
			inet_ntoa(listenAddress.sin_addr), htons(listenAddress.sin_port));

	/* Make the socket, then loop endlessly. */
	UDP_sock = make_UDP_socket(PORT_UDP_CONTEXT);
	TCP_sock = make_TCP_socket(PORT_TCP_CONTEXT);

	if (listen(TCP_sock, 3) == -1) {
		perror("listen(TCP_sock) failed");
		return 4;
	}

	cout << endl;
	cout << "Server TCP run():" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	/* Initialize the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(UDP_sock, &active_fd_set);
	FD_SET(TCP_sock, &active_fd_set);

	FD_ZERO(&read_fd_set);
	FD_ZERO(&write_fd_set);

	printf("FD_SETSIZE: %u\n", FD_SETSIZE);

	while (keep_going) {
		printf("keep_going: %u\n", keep_going);

		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;

		if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
			perror("select failed");
			exit(EXIT_FAILURE);
		}

		/* Service all the sockets with input pending. */
		for (read_fd = 0; read_fd < FD_SETSIZE; ++read_fd) {

			if (FD_ISSET(read_fd, &read_fd_set)) {

				// UDP Socket
				if (read_fd == UDP_sock) {
					printf("Server UDP: UDP_sock %u\n", read_fd);

					/* Wait for a datagram. */
					size = sizeof(UDP_addr);
					nbytes = recvfrom(UDP_sock, message, MAXMSG, 0,
							(struct sockaddr*) &UDP_addr, &size);

					if (nbytes < 0) {
						perror("recfrom (UDP_sock)");
						exit(EXIT_FAILURE);
					}

					/* Give a diagnostic message. */
					printf("Server UDP: got message: %s\n", message);

					ContextPacket *receivedContextPacket = new ContextPacket();
					receivedContextPacket->deserialize(buffer);

					receivedContextPacket->processUDP();

					receivedContextPacket->answerUDP();

					delete receivedContextPacket;

					printf("Server UDP: channel %u\n", receivedContextPacket->getChannel());


//					ContextService *testService = serviceFactory->GetService(receivedContextPacket->getChannel());
//					testService->processUDP(receivedContextPacket);
//
//					if (channel == CHANNEL_REQUEST) {
//						printf("Server channel: CHANNEL_REQUEST\n");
//
//						ContextPacket *receivedContextPacket = new ContextPacket();
//						receivedContextPacket->deserialize(buffer);
//
//						if (storage->contextPackets[receivedContextPacket->getContextType()].size() == 0) {
//							printf("contextPackets[contextType] is empty()\n");
//							continue;
//						}
//
//						for (std::vector<ContextPacket*>::iterator iter = storage->contextPackets[receivedContextPacket->getContextType()].begin();
//								iter != storage->contextPackets[receivedContextPacket->getContextType()].end(); ++iter) {
//
//							printf("for\n");
//
//							if ((*iter)->isMatchingContext(receivedContextPacket)) {
//
//								printf("if\n");
//								printf("(*iter)->getSize(): %u\n", (*iter)->getSize());
//
//								char sendBuffer[(*iter)->getSize()];
//
//								(*iter)->serialize(sendBuffer);
//
//								nbytes = sendto(UDP_sock, sendBuffer, (*iter)->getSize(), 0, (struct sockaddr *) &UDP_addr, size);
//								if (nbytes < 0) {
//									perror("sendto (UDP_sock)");
//									exit(EXIT_FAILURE);
//								}
//							}
//						}
//					}
					continue;
				}

				if (read_fd == TCP_sock) {
					printf("Server TCP: TCP_sock %u\n", read_fd);

					/* Connection request on original socket. */
					int acceptSocket;
					acceptLength = sizeof(TCP_addr);
					acceptSocket = accept(TCP_sock, (struct sockaddr*) &TCP_addr, &acceptLength);

					if (acceptSocket < 0) {
						perror("accept");
						exit(EXIT_FAILURE);
					}
					printf("Server TCP: connect from host %s, port %u\n", inet_ntoa(TCP_addr.sin_addr), ntohs(TCP_addr.sin_port));
					printf("Server TCP: acceptSocket %u\n", acceptSocket);

					FD_SET(acceptSocket, &active_fd_set);
				} else {
					printf("Server TCP: read_from_TCP_client(%u)\n", read_fd);

					bytes = recv(read_fd, buffer, sizeof(buffer) - 1, 0);
					printf("bytes: %u\n", bytes);

					if (bytes < 0) {
						perror("read");
						exit(EXIT_FAILURE);
					} else if (bytes == 0)
						/* End-of-file. */
						return -1;
					else {
						/* Data read. */
						printf("Server TCP: got message: ‘%s’\n", buffer);

						byte_t channel;
						channel = buffer[2];
						printf("Server TCP: channel %u\n", channel);

						uuid_t acceptUuid;
						memcpy(acceptUuid, buffer, 16);

						sizeAndContextStruct.first = new IpAddress(acceptUuid, TCP_addr);
						sizeAndContextStruct.second = buffer;

						printf("close(acceptSocket)\n");
						close(acceptSocket);
						printf("close(acceptSocket)\n");
//
//							storage->ipAddresses.push_back(new IpAddress(acceptUuid, TCP_addr));
//
////							printf("client from %s:%u arrived\n", inet_ntoa(TCP_addr.sin_addr), ntohs(TCP_addr.sin_port));

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
						if (fd_count == -1) {
							perror("select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL) failed");
							exit(EXIT_FAILURE);
						} else {
							printf("select(FD_SETSIZE, NULL, &write_fd_set, NULL, NULL): %i\n", fd_count);
						}

						/* Service all the sockets with output pending. */
						for (write_fd = 0; write_fd < FD_SETSIZE; ++write_fd) {
							printf("write_fd: %i\n", write_fd);

							if (FD_ISSET(write_fd, &write_fd_set)) {
								printf("FD_ISSET: %i\n", write_fd);

								ContextPacket *receipt = new ContextPacket(senderAddressArray[write_fd]);

								receipt->answerTCP();

								char answerBuffer[receipt->getSize()];
								receipt->serialize(answerBuffer);

								bytes = write(write_fd, answerBuffer, receipt->getSize());

								printf("receipt->getSize(): %u\n", receipt->getSize());

								if (bytes < 0) {
									perror("ERROR writing to socket");
								} else {
									printf("Answer sent: \"I got your message\"\n");
									break;
								}
							}
						}

						printf("close(read_fd)\n");
						close(read_fd);
						printf("close(read_fd)\n");
						FD_CLR(write_fd, &active_fd_set);

						/* ######################### */

					}
				}
			}
		}
	}
	close(TCP_sock);

//	delete storage;

	return EXIT_SUCCESS;
}

int ContextNetwork::make_TCP_socket(uint16_t port) {

	int sock;
	struct sockaddr_in name;

	/* Create the socket. */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Give the socket a name. */
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
		perror("make_TCP_socket bind");
		exit(EXIT_FAILURE);
	}
	return sock;
}

int ContextNetwork::make_UDP_socket(uint16_t port) {

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
	name.sin_port = htons(PORT_UDP_CONTEXT);
	name.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
		perror("make_UDP_socket bind");
		exit(EXIT_FAILURE);
	}
	return sock;
}

void* receiveTcpThread(void* data) {

	pair<IpAddress*, char*> incoming = *((pair<IpAddress*, char*>*) data);

	ContextPacket *receivedContextPacket = new ContextPacket();

	receivedContextPacket->deserialize(incoming.second);
	receivedContextPacket->setIpAddress(incoming.first->getSockAddress().sin_addr.s_addr);
	receivedContextPacket->setPortNumber(incoming.first->getSockAddress().sin_port);

	receivedContextPacket->processTCP();

	/* terminate the thread */
	pthread_exit(NULL);
}
