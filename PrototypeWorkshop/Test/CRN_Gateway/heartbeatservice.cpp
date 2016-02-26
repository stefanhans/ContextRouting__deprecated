#include "heartbeatservice.h"

int HeartbeatService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] RZV SERVICE" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;


	/*
	 * Create CIP for UDP reply
	 */
	ContextPacket *replyContextPacket = new ContextPacket();

	replyContextPacket->setIpAddress(inet_addr(inet_ntoa(((struct sockaddr_in *)addr)->sin_addr)));
	replyContextPacket->setPortNumber(((struct sockaddr_in *)addr)->sin_port);
	replyContextPacket->setTime();

	if (DEBUG) replyContextPacket->printPacket();

	char sendBuffer[replyContextPacket->getSize()];
	replyContextPacket->serialize(sendBuffer);

	int nbytes;
	nbytes = sendto(socket, sendBuffer,
			replyContextPacket->getSize(), 0,
			(struct sockaddr *) addr,
			sizeof(struct sockaddr));
	if (nbytes < 0) {
		perror("sendto(socket) failed");
	}
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] sendto(UDP_sock): " << nbytes << std::endl;

	std::cout << getUuidString(*((ContextPacket*) receivedPacket)->getUuid()) << " : " << "Service RZV provided: RZV CIP with client's ip:port and current timestamp." << std::endl;



//	if (PRINT_PACKETS_DEBUG) printPackets();

//	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	return 0;
}

int HeartbeatService::processTCP(void* receivedPacket) {
	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] HEARTBEAT SERVICE" << std::endl;
	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;

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

	store_vector->push_back((ContextPacket*) receivedPacket);

	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] :"
			" push_back at index " << (uint) ((ContextPacket*) receivedPacket)->getRootCIC()->context << std::endl;

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
