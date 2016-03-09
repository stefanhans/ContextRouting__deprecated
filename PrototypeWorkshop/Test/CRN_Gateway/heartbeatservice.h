#ifndef HEARTBEATSERVICE_H_
#define HEARTBEATSERVICE_H_

#include "abstractservice.h"

/**
 * @brief HeartbeatService
 *
 */
class HeartbeatService : public ContextService {

public:

	int processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr);

	int processTCP(void* receivedPacket) {
		return 0;
	}
};

#endif /* HEARTBEATSERVICE_H_ */
