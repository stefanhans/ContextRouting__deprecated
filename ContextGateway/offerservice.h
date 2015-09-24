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
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int answerUDP(void* packet) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}

	int processTCP(void* receivedPacket) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) ((ContextPacket*) receivedPacket)->getService()<< std::endl;

//		printf("OfferService::processTCP: channel %i\n", ((ContextPacket*) receivedPacket)->getChannel());
//
//		printf("OfferService::processTCP: number of packets %i\n", getNumberOfPackets());
		storePacket(receivedPacket);
		printPackets();
//		printf("OfferService::processTCP: number of packets %i\n", getNumberOfPackets());

		return 0;
	}

	int answerTCP(void* packet) {
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		struct  sockaddr_in ipAddr = ((ContextPacket*) packet)->getIp();

//		printf("OfferService::answerTCP: ipAddress %s\n", inet_ntoa(ipAddr.sin_addr));
//		printf("OfferService::answerTCP: port %i\n", ntohs(ipAddr.sin_port));

		return 0;
	}

};

#endif /* SRC_OFFERSERVICE_H_ */
