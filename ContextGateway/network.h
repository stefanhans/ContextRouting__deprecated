#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

#include <pthread.h>

#include "corepacket.h"

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
		UDP_address_size(0),
		UDP_bytes_received(0),
//		localAddress(),
		bytes(0),
		p_thread() {

	}

	/*
	 * Start the main loop
	 */
	int run();

	/*
	 * Stop the main loop
	 */
	void stop();

private:

	/*
	 * This flag controls termination of the main loop
	 */
	volatile sig_atomic_t keep_going;

	/*
	 * Sockets for listening
	 */
	int UDP_sock, TCP_sock;


	int acceptSocket;
	socklen_t acceptLength;

	int read_fd, write_fd;

	struct sockaddr_in TCP_addr;
	struct sockaddr_un UDP_addr;

	/*
	 * Descriptor sets for select()
	 */
	fd_set active_fd_set, read_fd_set, write_fd_set;

	socklen_t UDP_address_size;
	int UDP_bytes_received;

//	struct in_addr localAddress;

	int bytes;

	pthread_t p_thread;

	char buffer[MAXMSG];
	char message[MAXMSG];

	std::pair<IpAddress*, char*> sizeAndContextStruct;
	IpAddress* senderAddressArray[FD_SETSIZE];

	int make_TCP_socket(uint16_t port);
	int make_UDP_socket(uint16_t port);

};

#endif /* SRC_NETWORK_H_ */
