#ifndef SRC_OFFERSERVICE_H_
#define SRC_OFFERSERVICE_H_

#include "abstractservice.h"

/**
 * @brief OfferService
 *
 */
class OfferService : public ContextService {

public:

	int processUDP(void* receivedPacket) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}


	int processUDP(void* packet, int socket, void *buffer, size_t size, struct sockaddr *addr) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int processTCP(void* receivedPacket) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) ((ContextPacket*) receivedPacket)->getService()<< std::endl;

		storePacket(receivedPacket);

//		if (DEBUG) printPackets();

		if (DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

		return 0;
	}
};

#endif /* SRC_OFFERSERVICE_H_ */
