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
//class OfferService: public ContextService {
//
//public:
//
//	int processUDP(ContextPacket *receivedPacket);
//	int processTCP(ContextPacket *receivedPacket);
//
//	int answerUDP(ContextPacket *receivedPacket);
//	int answerTCP(ContextPacket *receivedPacket);
//
//};


class OfferService: public ContextService {

public:

	int processUDP(ContextPacket *receivedPacket);
	int processTCP(ContextPacket *receivedPacket);

	int answerUDP(ContextPacket *receivedPacket);
	int answerTCP(ContextPacket *receivedPacket);

};

#endif /* SRC_OFFERSERVICE_H_ */
