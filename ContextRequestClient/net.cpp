/*
 * net.cpp
 *
 *  Created on: May 21, 2015
 *      Author: stefan
 */

#include "net.h"

using namespace std;



Net::Net() {

	cout << endl;
	cout << "Server Net():"	<< endl;
	cout << "----------------------------------------------------------------------" << endl;

	localAddress.s_addr = inet_addr("127.0.0.1");

	sendOfferPort    = static_cast<unsigned short>(22365);
	sendRequestPort  = static_cast<unsigned short>(22366);

	offer.sin_addr   = localAddress;
	offer.sin_family = AF_INET;
	offer.sin_port   = htons(sendOfferPort);

	request.sin_addr   = localAddress;
	request.sin_family = AF_INET;
	request.sin_port   = htons(sendRequestPort);

	offerSocket = -1;
	requestSocket = -1;

	storage = new ContextStorage();
}

int Net::initialize() {

	cout << endl;
	cout << "Server initialize():"	<< endl;
	cout << "----------------------------------------------------------------------" << endl;

	requestSocket = socket(PF_INET, SOCK_DGRAM, 0);

	if (requestSocket == -1)
	{
		perror ("requestSocket failed");
		return 2;
	}

	storage = new ContextStorage();

	return 0;
}


int Net::sendRequest(ContextStruct *contextStruct) {


	char buffer[contextStruct->getSizeOf()];
	int bytes;
	socklen_t size;

	storage->serializeStruct(contextStruct, buffer);

	size = sizeof(request);

	/* Bounce the message back to the sender. */
	bytes = sendto(requestSocket, buffer, contextStruct->getSizeOf(), 0, (struct sockaddr*) &request, size);
	if (bytes < 0) {
		perror("sendto(requestSocket) failed");
		exit(EXIT_FAILURE);
	}

	printf ("Request:\tSent to %s:%u\n", inet_ntoa(request.sin_addr), htons(request.sin_port));

	while(1) {
		memset(&buffer, 0, sizeof(buffer));

		bytes = recvfrom (requestSocket, buffer, 1024, 0, NULL, 0);
		if (bytes < 0) {
			perror ("recfrom(requestSocket) failed");
			exit (EXIT_FAILURE);
		}

		ContextStruct *receivedContextStruct = new ContextStruct();

		storage->deserializeStruct(buffer, bytes, receivedContextStruct);

		printContextStruct(receivedContextStruct);
	}

	return 0;
}
