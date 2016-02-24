/*
 * rzvservice.h
 *
 *  Created on: Feb 17, 2016
 *      Author: stefan
 */

#ifndef RZVSERVICE_H_
#define RZVSERVICE_H_

#include "abstractservice.h"

/**
 * @brief RZVService
 *
 */
class RZVService : public ContextService {

public:

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr);

	int processTCP(void* receivedPacket);
};

#endif /* RZVSERVICE_H_ */
