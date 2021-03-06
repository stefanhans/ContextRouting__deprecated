#include "defaultservice.h"

int DefaultService::processUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DEFAULT SERVICE" << std::endl;
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

	std::cout << getUuidString(*((ContextPacket*) receivedPacket)->getUuid()) << " : " << "UDP Default Service provides CIP with client's ip:port and current timestamp." << std::endl;

	if (PRINT_PACKET_DEBUG) ((ContextPacket*) receivedPacket)->printPacket();

	return 0;
}
