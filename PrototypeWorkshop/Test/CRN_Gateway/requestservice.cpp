#include "requestservice.h"

int RequestService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] REQUEST SERVICE" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;

	std::vector<ContextPacket*>* store_vector;
	store_vector = getContextPackets(((ContextPacket*) receivedPacket)->getFirstBrick()->context);

	if(store_vector->size() == 0) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] no context found" << std::endl;

		// Answer UDP

		return 0;
	}

	int bytes_send;

	for (std::vector<ContextPacket*>::iterator iter = store_vector->begin(); iter != store_vector->end(); ++iter) {

		if(matchContextPackets((*iter), (ContextPacket*) receivedPacket)) {

			//(*iter)->printPacket("FOUND: ");

			if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : FOUND " << getUuidString(*(*iter)->getUuid()) << std::endl;


			char sendBuffer[(*iter)->getSize()];

			(*iter)->serialize(sendBuffer);

			bytes_send = sendto(socket, sendBuffer, sizeof(sendBuffer), 0, addr, sizeof(struct sockaddr));
			if (bytes_send < 0) {
				perror("sendto (socket)");
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}
