/*
 * net.h
 *
 *  Created on: May 19, 2015
 *      Author: stefan
 */

#ifndef NET_H_
#define NET_H_

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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "storage.h"

class Net {

public:

	int offerSocket, requestSocket, listenSocket;

	struct sockaddr_in offer, request;
	struct in_addr localAddress;
	unsigned short sendOfferPort, sendRequestPort;

	ContextStorage *storage;

//	struct sockaddr_in acceptOffer, acceptRequest;
//	int acceptOfferSocket, acceptRequestSocket;
//	int offerRunning, requestRunning;
//	socklen_t acceptOfferLength, acceptRequestLength;

	Net();
	virtual ~Net() {}

	int initialize();

	int sendOffer(ContextStruct *contextStruct);
	int listenAnswer(OfferAdress *contextStruct);
};

#endif /* NET_H_ */
