/*
 * requestservice.h
 *
 *  Created on: Sep 4, 2015
 *      Author: stefan
 */

#ifndef SRC_REQUESTSERVICE_H_
#define SRC_REQUESTSERVICE_H_

#include "abstractservice.h"

using namespace std;

/**
 * @brief RequestService
 *
 */
class RequestService : public ContextService {

public:

	int processUDP(void* receivedPacket) {
		printf("RequestService::processUDP\n");

		printf("RequestService::processUDP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		return 0;
	}

	int processTCP(void* receivedPacket) {
		printf("RequestService::processTCP\n");

		printf("RequestService::processTCP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		storePacket();

		return 0;
	}

	int answerUDP(void* packet) {
		printf("RequestService::answerUDP\n");

		return 0;
	}

	int answerTCP(void* packet) {
		printf("RequestService::answerTCP\n");

		printf("RequestService::answerTCP: channel %i\n", ((ContextPacket*) packet)->getChannel());

		return 0;
	}

private:

	int storePacket();

};

#endif /* SRC_REQUESTSERVICE_H_ */
