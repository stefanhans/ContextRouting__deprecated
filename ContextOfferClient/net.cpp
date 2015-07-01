/*
 * net.cpp
 *
 *  Created on: May 19, 2015
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

	offerSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (offerSocket == -1)
	{
		perror ("offerSocket failed");
		return 2;
	}

	printf ("Offer:\t\tConnect to %s:%u\n", inet_ntoa(offer.sin_addr), htons(offer.sin_port));

	if (connect(offerSocket, (struct sockaddr *) &offer, sizeof(offer)) == -1)
	{
		perror("connect() failed");
		return 3;
	}

	storage = new ContextStorage();

	return 0;
}


int Net::sendOffer(ContextStruct *contextStruct) {

	char buffer[contextStruct->getSizeOf()];

	storage->serializeStruct(contextStruct, buffer);

	if (send(offerSocket, buffer, contextStruct->getSizeOf(), 0) == -1) {
		perror("send(offer) failed");
		return 4;
	}
	printf ("Offer:\tSent to %s:%u\n", inet_ntoa(offer.sin_addr), htons(offer.sin_port));

	return 0;
}
