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
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		if (! DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

		findMatchingContextPackets((ContextPacket*) receivedPacket);

		return 0;
	}

	int answerUDP(void* packet) {
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int processTCP(void* receivedPacket) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int answerTCP(void* packet) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

private:

	int storePacket();

};

#endif /* SRC_REQUESTSERVICE_H_ */
