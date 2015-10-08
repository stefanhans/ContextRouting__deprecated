#ifndef SRC_REQUESTSERVICE_H_
#define SRC_REQUESTSERVICE_H_

#include "abstractservice.h"

/**
 * @brief RequestService
 *
 */
class RequestService : public ContextService {

public:

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr);

	int processTCP(void* receivedPacket) {
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

		return 0;
	}
};

#endif /* SRC_REQUESTSERVICE_H_ */
