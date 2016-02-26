/*
 * defaultservice.h
 *
 *  Created on: Feb 17, 2016
 *      Author: stefan
 */

#ifndef DEFAULTSERVICE_H_
#define DEFAULTSERVICE_H_

#include "abstractservice.h"

/**
 * @brief DefaultService
 *
 */
class DefaultService : public ContextService {

public:

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr);

	int processTCP(void* receivedPacket);
};

#endif /* DEFAULTSERVICE_H_ */
