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

#include "corepacket.h"

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

	int run();

private:

	/* This flag controls termination of the main loop. */
	volatile sig_atomic_t keep_going;

	int make_TCP_socket(uint16_t port);
	int make_UDP_socket(uint16_t port);

};
#endif /* SRC_NETWORK_H_ */
