/*
 * main.cpp
 *
 *  Created on: May 28, 2015
 *      Author: stefan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <limits.h>
#include <vector>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include "storage.h"

#define TCP_PORT 22365
#define UDP_PORT 22366
#define MAXMSG 1024

using namespace std;

static ContextStorage *storage = new ContextStorage();


int make_TCP_socket (uint16_t port);
int make_UDP_socket (uint16_t port);

/* This flag controls termination of the main loop. */
volatile sig_atomic_t keep_going = 1;

void* receiveOfferThread(void* data);

int main(void) {

	int UDP_sock, TCP_sock;
	struct sockaddr_in TCP_addr;
	struct sockaddr_un UDP_addr;

	fd_set active_fd_set, read_fd_set;
	int acceptSocket = -1;

	socklen_t size;
	int nbytes;
	char message[MAXMSG];

	struct sockaddr_in listenAddress;
	struct in_addr localAddress;
	socklen_t acceptLength = 0;

	localAddress.s_addr = inet_addr("127.0.0.1");

	listenAddress.sin_addr   = localAddress;
	listenAddress.sin_family = AF_INET;
	listenAddress.sin_port   = htons(TCP_PORT);

	/* Make the socket, then loop endlessly. */
	UDP_sock = make_UDP_socket(UDP_PORT);
	TCP_sock = make_TCP_socket(TCP_PORT);

	printf ("Server TCP: \tgoing to listen on %s:%u\n", inet_ntoa(listenAddress.sin_addr), htons(listenAddress.sin_port));

	if (listen(TCP_sock, 3) == -1) {
		perror("listen(TCP_sock) failed");
		return 4;
	}

	cout << endl;
	cout << "Server TCP run():" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	int read_fd;

	char buffer[MAXMSG];
	int bytes;

	pthread_t  p_thread;

	pair <int,char*> sizeAndContextStruct;

	/* Initialize the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(UDP_sock, &active_fd_set);
	FD_SET(TCP_sock, &active_fd_set);

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
				if (read_fd == UDP_sock) {
					printf("Server UDP: UDP_sock %u\n", read_fd);

					/* Wait for a datagram. */
					size = sizeof(UDP_addr);
					nbytes = recvfrom(UDP_sock, message, MAXMSG, 0, (struct sockaddr*) &UDP_addr, &size);

					if (nbytes < 0) {
						perror("recfrom (UDP_sock)");
						exit(EXIT_FAILURE);
					}

					/* Give a diagnostic message. */
					printf("Server UDP: got message: %s\n", message);

					byte channel;
					channel = message[16];
					printf("Server channel: %u\n", channel);

					if (channel == CMD_REQUEST) {
						printf("Server channel: CMD_REQUEST\n");

						ContextStruct *receivedContextStruct = new ContextStruct();

						storage->deserializeStruct(buffer, bytes, receivedContextStruct);

						if(storage->contextIds[receivedContextStruct->contextArray->contextId->context].size() == 0) {
							printf("contextIds is empty()\n");
							continue;
						}

						for (std::vector<ContextStruct*>::iterator iter = storage->contextIds[receivedContextStruct->contextArray->contextId->context].begin();
								iter != storage->contextIds[receivedContextStruct->contextArray->contextId->context].end(); ++iter) {

							printf("for\n");

							if(storage->array_match((*iter)->contextArray, receivedContextStruct->contextArray)) {

								printf("if\n");
								printf("(*iter)->getSizeOf(): %u\n", (*iter)->getSizeOf());

								char sendBuffer[(*iter)->getSizeOf()];

								storage->serializeStruct((*iter), sendBuffer);
								nbytes = sendto(UDP_sock, sendBuffer, (*iter)->getSizeOf(), 0, (struct sockaddr *) &UDP_addr, size);
								if (nbytes < 0) {
									perror("sendto (UDP_sock)");
									exit(EXIT_FAILURE);
								}
							}
						}
					}
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
				}
				else {
					printf("Server TCP: read_from_TCP_client(%u)\n", read_fd);

					bytes = read(read_fd, buffer, MAXMSG);
					printf("bytes: %u\n", bytes);

					if (bytes < 0) {
						perror("read");
						exit(EXIT_FAILURE);
					} else if (bytes == 0)
						/* End-of-file. */
						return -1;
					else {
						/* Data read. */
						printf("Server: got message: ‘%s’\n", buffer);

						byte channel;
						channel = buffer[16];
						printf("Server channel: %u\n", channel);

						if (channel == CMD_OFFER) {

							sizeAndContextStruct.first = bytes;
							sizeAndContextStruct.second = buffer;

							close(acceptSocket);

							uuid_t acceptUuid;
							memcpy(acceptUuid, buffer, 16);

							storage->offerAddresses.push_back(new OfferAdress(acceptUuid, TCP_addr));

							printOfferAdresses(storage);

							printf("client from %s:%u arrived\n", inet_ntoa(TCP_addr.sin_addr), ntohs(TCP_addr.sin_port));

							/* create a new thread that will execute 'receiveOfferThread()' */
							if (pthread_create(&p_thread, NULL, receiveOfferThread, (void*) &sizeAndContextStruct) != 0) {
								perror("pthread_create(receiveOfferThread) failed");
								return 4;
							}
						}

						close(read_fd);
						FD_CLR(read_fd, &active_fd_set);
					}
				}
			}
		}
	}
	printf("close(TCP_sock)\n");
	close(TCP_sock);
};

int make_TCP_socket (uint16_t port) {

	int sock;
	struct sockaddr_in name;

	/* Create the socket. */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	/* Give the socket a name. */
	name.sin_family = AF_INET;
	name.sin_port = htons (port);
	name.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	return sock;
}

int make_UDP_socket (uint16_t port) {

	struct sockaddr_in name;
	int sock;

	/* Create the socket. */
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	/* Bind a name to the socket. */
	name.sin_family = AF_INET;
	name.sin_port   = htons(UDP_PORT);
	name.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind (sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	return sock;
}

/* function to be executed by the new thread */
void* receiveOfferThread(void* data) {

	cout << endl;
	cout << "Server receiveOfferThread():"	<< endl;
	cout << "----------------------------------------------------------------------" << endl;

	pair <int,char*> incoming = *((pair<int, char*>*)data);

	ContextStruct *receivedContextStruct = new ContextStruct();

	storage->deserializeStruct(incoming.second, incoming.first, receivedContextStruct);
	storage->storeContextStruct(receivedContextStruct);

    /* terminate the thread */
    pthread_exit(NULL);
}
