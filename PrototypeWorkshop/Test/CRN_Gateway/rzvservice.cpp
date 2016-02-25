#include "rzvservice.h"

int RZVService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) ((ContextPacket*) receivedPacket)->getService()<< std::endl;
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] RZV SERVICE" << std::endl;
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;



//	if (PRINT_PACKETS_DEBUG) printPackets();

//	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	return 0;
}

int RZVService::processTCP(void* receivedPacket) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) ((ContextPacket*) receivedPacket)->getService()<< std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] RZV SERVICE" << std::endl;
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
	store_vector = getContextPackets(((ContextPacket*) receivedPacket)->getFirstBrick()->context);

	store_vector->push_back((ContextPacket*) receivedPacket);

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] :"
			" push_back at index " << (uint) ((ContextPacket*) receivedPacket)->getFirstBrick()->context << std::endl;

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
