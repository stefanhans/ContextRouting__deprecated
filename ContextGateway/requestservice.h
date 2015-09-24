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
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//		printf("RequestService::processUDP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		return 0;
	}

	int processTCP(void* receivedPacket) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//		printf("RequestService::processTCP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());

		storePacket();

		return 0;
	}

	int answerUDP(void* packet) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int answerTCP(void* packet) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//		printf("RequestService::answerTCP: channel %i\n", ((ContextPacket*) packet)->getChannel());

		return 0;
	}

private:

	int storePacket();

};

#endif /* SRC_REQUESTSERVICE_H_ */
