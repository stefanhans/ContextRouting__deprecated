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
#include "protocol.h"

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
		TCP_bytes_received(0),
		TCP_bytes_to_send(0),
		p_thread(),
		errorContextPacket(){

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
	 * This flag controls termination of the main loop, i.e. 0 stops the main loop
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
	struct sockaddr_in UDP_addr;

	/*
	 * Descriptor sets for select()
	 */
	fd_set active_fd_set, read_fd_set, write_fd_set;

	socklen_t UDP_address_size;
	int UDP_bytes_received;

	size_t TCP_bytes_received;
	int TCP_bytes_to_send;

	pthread_t p_thread;

	char UDP_buffer[MAXMSG];
	char TCP_buffer[MAXMSG];

	std::pair<IpAddress*, char*> sizeAndContextStruct;
	IpAddress* senderAddressArray[FD_SETSIZE];

	int make_TCP_socket(uint16_t port);
	int make_UDP_socket(uint16_t port);


	int createTcpReply(ContextPacket* receivedContextPacket, char* reply_buffer, size_t& size);


	/*
	 * Prepare TCP error reply
	 */
	char errorHeader[3];
	ContextPacket *errorContextPacket;
};

#endif /* SRC_NETWORK_H_ */
