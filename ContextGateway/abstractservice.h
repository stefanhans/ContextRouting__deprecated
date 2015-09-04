/*
 * abstractservice.h
 *
 *  Created on: Sep 2, 2015
 *      Author: stefan
 */

#ifndef SRC_ABSTRACTSERVICE_H_
#define SRC_ABSTRACTSERVICE_H_

#include "corepacket.h"

#include "globals.h"

using namespace std;

/**
 * @brief ContextService
 *
 */
class ContextService {

public:
	virtual ~ContextService(){}

	virtual int processUDP(void* receivedPacket) = 0;
	virtual int processTCP(void* receivedPacket) = 0;

	virtual int answerUDP(void* receivedPacket) = 0;
	virtual int answerTCP(void* receivedPacket) = 0;

	static ContextService* create(byte_t service);

};

#endif /* SRC_ABSTRACTSERVICE_H_ */
