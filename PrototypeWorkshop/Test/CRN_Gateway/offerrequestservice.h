/*
 * offerrequestservice.h
 *
 *  Created on: Feb 26, 2016
 *      Author: stefan
 */

#ifndef OFFERREQUESTSERVICE_H_
#define OFFERREQUESTSERVICE_H_


#include "abstractservice.h"

/**
 * @brief OfferRequestService
 *
 */
class OfferRequestService : public ContextService {

public:

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr);

	int processTCP(void* receivedPacket);
};




#endif /* OFFERREQUESTSERVICE_H_ */
