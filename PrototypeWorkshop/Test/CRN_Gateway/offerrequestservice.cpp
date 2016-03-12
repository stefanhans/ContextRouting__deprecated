#include "offerrequestservice.h"


int OfferRequestService::processTCP(void* receivedPacket) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] OFFER SERVICE" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;

	pthread_mutex_t storageMutex = getContextPacketsMutex();

	int rc;	/* contain mutex lock/unlock results */

	/* lock the mutex, to assure exclusive access to 'a' and 'b'. */
	rc = pthread_mutex_lock(&storageMutex);

	/* an error has occurred */
	if (rc) {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}

	std::vector<ContextPacket*>* store_vector;
	store_vector = getContextPackets(((ContextPacket*) receivedPacket)->getRootCIC()->context);

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] :"
			" push_back at index " << (uint) ((ContextPacket*) receivedPacket)->getRootCIC()->context << std::endl;

	int update = 0;
	if(store_vector->size() > 0) {


		for (std::vector<ContextPacket*>::iterator iter = store_vector->begin(); iter != store_vector->end(); ++iter) {

			if(equalContextPacketContents((*iter), (ContextPacket*) receivedPacket)) {

				if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : Erase CIP with equal CIC-Bricks' content from storage." << getUuidString(*(*iter)->getUuid()) << std::endl;

				store_vector->erase(iter);

				update = 1;

				break;
			}
		}
	}

	store_vector->push_back((ContextPacket*) receivedPacket);

	if(update) {
		std::cout << getUuidString(*((ContextPacket*) receivedPacket)->getUuid()) << " : " << "TCP Offer Service updates CIP : " << ctime(((ContextPacket*) receivedPacket)->getTime()) << std::ends;
	}
	else {
		std::cout << getUuidString(*((ContextPacket*) receivedPacket)->getUuid()) << " : " << "TCP Offer Service stores CIP : " << ctime(((ContextPacket*) receivedPacket)->getTime()) << std::ends;
	}

	/* unlock mutex */
	rc = pthread_mutex_unlock(&storageMutex);

	if (rc) {
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}

	if (PRINT_PACKETS_DEBUG) printPackets();

	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	return 0;
}


int OfferRequestService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] REQUEST SERVICE" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;

	std::vector<ContextPacket*>* store_vector;
	store_vector = getContextPackets(((ContextPacket*) receivedPacket)->getRootCIC()->context);

	if(store_vector->size() == 0) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] no context found" << std::endl;

		// Answer UDP

		return 0;
	}

	int bytes_send;

	for (std::vector<ContextPacket*>::iterator iter = store_vector->begin(); iter != store_vector->end(); ++iter) {

		if(matchContextPackets((*iter), (ContextPacket*) receivedPacket)) {

			if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] : FOUND " << getUuidString(*(*iter)->getUuid()) << std::endl;


			char sendBuffer[(*iter)->getSize()];

			(*iter)->serialize(sendBuffer);

			bytes_send = sendto(socket, sendBuffer, sizeof(sendBuffer), 0, addr, sizeof(struct sockaddr));
			if (bytes_send < 0) {
				perror("sendto (socket)");
				exit(EXIT_FAILURE);
			}


			std::cout << getUuidString(*(*iter)->getUuid()) << " : " << "UDP Request Service provides CIP with appropriate offer." << std::endl;

		}
	}

	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	return 0;
}


