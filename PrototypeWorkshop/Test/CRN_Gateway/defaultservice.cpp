#include "defaultservice.h"

int DefaultService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] RZV SERVICE" << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;


	/*
	 * Create CIP for UDP reply with error message
	 */
	ContextPacket *replyContextPacket = new ContextPacket();

	replyContextPacket->setIpAddress(inet_addr(inet_ntoa(((struct sockaddr_in *)addr)->sin_addr)));
	replyContextPacket->setPortNumber(((struct sockaddr_in *)addr)->sin_port);
	replyContextPacket->setTime();
//	replyContextPacket->set

	if (PRINT_PACKET_DEBUG) replyContextPacket->printPacket();

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

int DefaultService::processTCP(void* receivedPacket) {
	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DEFAULT SERVICE" << std::endl;
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


	;


//
//	/*
//	 * Create CIP for TCP reply
//	 */
//	ContextPacket *replyContextPacket = new ContextPacket();
//
//	replyContextPacket->setIpAddress(inet_addr(inet_ntoa(((struct sockaddr_in *)addr)->sin_addr)));
//	replyContextPacket->setPortNumber(((struct sockaddr_in *)addr)->sin_port);
//	replyContextPacket->setTime();

	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	char sendBuffer[((ContextPacket*) receivedPacket)->getSize()];
	((ContextPacket*) receivedPacket)->serialize(sendBuffer);






	int sock;
	struct sockaddr name;

	/* Create the socket. */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	int nbytes;
	nbytes = sendto(sock, sendBuffer,
			((ContextPacket*) receivedPacket)->getSize(), 0,
			&name,
			sizeof(struct sockaddr));
	if (nbytes < 0) {
		perror("sendto(socket) failed");
	}
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] sendto(UDP_sock): " << nbytes << std::endl;

	std::cout << getUuidString(*((ContextPacket*) receivedPacket)->getUuid()) << " : " << "Service RZV provided: RZV CIP with client's ip:port and current timestamp." << std::endl;








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
