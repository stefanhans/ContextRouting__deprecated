#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

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

#include <pthread.h>

#include "corepacket.h"
#include "corestorage.h"
#include "abstractservice.h"

#define TCP_PORT 22365
#define UDP_PORT 22366
#define MAXMSG 1024

/**
 * type definitions
 */
typedef unsigned char byte_t;

/**
 * thread functions
 */
void* receiveTcpThread(void* data);

/**
 * ContextNetwork
 */
class ContextNetwork {

public:

	ContextNetwork() :
		keep_going(1),
		UDP_sock(0),
		TCP_sock(0),
		acceptSocket(-1),
		acceptLength(0),
		read_fd(0),
		write_fd(0),
		TCP_addr(),
		UDP_addr(),
		active_fd_set(),
		read_fd_set(),
		write_fd_set(),
		size(0),
		nbytes(0),
		listenAddress(),
		localAddress(),
		bytes(0),
		p_thread(),
		packetStorage() {

	}

	int run();

private:

	/* This flag controls termination of the main loop. */
	volatile sig_atomic_t keep_going;

	int UDP_sock, TCP_sock;
	int acceptSocket;

	socklen_t acceptLength;

	int read_fd, write_fd;

	struct sockaddr_in TCP_addr;
	struct sockaddr_un UDP_addr;

	fd_set active_fd_set, read_fd_set, write_fd_set;

	socklen_t size;
	int nbytes;

	struct sockaddr_in listenAddress;
	struct in_addr localAddress;

	int bytes;

	pthread_t p_thread;

	PacketStorage *packetStorage;

	char buffer[MAXMSG];
	char message[MAXMSG];

	pair<IpAddress*, char*> sizeAndContextStruct;
	IpAddress* senderAddressArray[FD_SETSIZE];

	int make_TCP_socket(uint16_t port);
	int make_UDP_socket(uint16_t port);

};

#endif /* SRC_NETWORK_H_ */
