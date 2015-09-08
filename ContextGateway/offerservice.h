/*
 * offerservice.h
 *
 *  Created on: Sep 2, 2015
 *      Author: stefan
 */

#ifndef SRC_OFFERSERVICE_H_
#define SRC_OFFERSERVICE_H_

#include "abstractservice.h"

using namespace std;

/**
 * @brief OfferService
 *
 */
class OfferService : public ContextService {

public:

	int processUDP(void* receivedPacket) {
		printf("OfferService::processUDP\n");

		printf("OfferService::processUDP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		return 0;
	}

	int processTCP(void* receivedPacket) {
		printf("OfferService::processTCP\n");

		printf("OfferService::processTCP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		printf("OfferService::processTCP: number of packets %i\n", getNumberOfPackets());
		storePacket(receivedPacket);
		printf("OfferService::processTCP: number of packets %i\n", getNumberOfPackets());

		return 0;
	}

	int answerUDP(void* packet) {
		printf("OfferService::answerUDP\n");

		return 0;
	}

	int answerTCP(void* packet) {
		printf("OfferService::answerTCP\n");

		printf("OfferService::answerTCP: channel %i\n", ((ContextPacket*) packet)->getChannel());

		return 0;
	}

};

#endif /* SRC_OFFERSERVICE_H_ */
