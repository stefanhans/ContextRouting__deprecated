/*
 * abstractservice.h
 *
 *  Created on: Sep 2, 2015
 *      Author: stefan
 */

#ifndef SRC_ABSTRACTSERVICE_H_
#define SRC_ABSTRACTSERVICE_H_

#include "corepacket.h"

class ContextPacket;


/**
 * @brief ContextService
 *
 */
class ContextService {

public:
	ContextService();

	virtual ~ContextService(){}

	/*
	 * UDP method
	 */
	virtual int processUDP(void* packet, int socket, void *buffer, size_t size, struct sockaddr *addr) = 0;

	/*
	 * TCP method
	 */
	virtual int processTCP(void* receivedPacket) = 0;


	static ContextService* create(byte_t channel, byte_t request);

	std::vector<ContextPacket*>* getContextPackets(byte_t index);

	pthread_mutex_t getContextPacketsMutex();

	/*
	 * UDP method
	 */
	int validateUDP(void* packet, int socket, void *buffer, size_t size, struct sockaddr *addr);


protected:

	/*
	 * Do two ContextBricks match?
	 */
	bool matchContextBricks(void* contextBrick_1, void* contextBrick_2);

	/**
	 * Do two ContextPackets match?
	 */
	bool matchContextPackets(void* contextPacket_1, void* contextPacket_2);

	/*
	 * Do two ContextBricks have equal content?
	 */
	bool equalContextBricksContent(void* contextBrick_1, void* contextBrick_2);

	/**
	 * Do two ContextPackets have equal CIC-Bricks' content?
	 */
	bool equalContextPacketContents(void* contextPacket_1, void* contextPacket_2);

	void printPackets();

private:

	/*
	 * Prepare UDP error reply
	 */
	char errorHeader[3];
	ContextPacket *errorContextPacket;
};

#endif /* SRC_ABSTRACTSERVICE_H_ */
