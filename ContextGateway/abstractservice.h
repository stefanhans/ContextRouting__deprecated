/*
 * abstractservice.h
 *
 *  Created on: Sep 2, 2015
 *      Author: stefan
 */

#ifndef SRC_ABSTRACTSERVICE_H_
#define SRC_ABSTRACTSERVICE_H_

#include "corepacket.h"

/**
 * @brief ContextService
 *
 */
class ContextService {

public:
	ContextService();

	virtual ~ContextService(){}

	/*
	 * UDP methods
	 */
	virtual int processUDP(void* receivedPacket) = 0;
	virtual int processUDP(void* packet, int socket, void *buffer, size_t size, struct sockaddr *addr) = 0;

	/*
	 * TCP methods
	 */
	virtual int processTCP(void* receivedPacket) = 0;


	static ContextService* create(byte_t service);

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
	 * Send all matching packets from storage to sender of request
	 */
	void sendMatchingContextPackets(void* requestPacket, int socket, struct sockaddr *addr);



	/**
	 * Store ContextPacket in "contextPackets[]"
	 */
	int storePacket(void* packet);

	int getNumberOfPackets();

	void printPackets();
};

#endif /* SRC_ABSTRACTSERVICE_H_ */
