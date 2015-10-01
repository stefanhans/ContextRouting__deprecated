#ifndef SRC_REQUESTSERVICE_H_
#define SRC_REQUESTSERVICE_H_

#include "abstractservice.h"

/**
 * @brief RequestService
 *
 */
class RequestService : public ContextService {

public:

	int processUDP(void* receivedPacket) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		if (DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

		return 0;
	}

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		sendMatchingContextPackets((ContextPacket*) receivedPacket, socket, addr);

		return 0;
	}

	int processTCP(void* receivedPacket) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

private:

	int storePacket();

};

#endif /* SRC_REQUESTSERVICE_H_ */
