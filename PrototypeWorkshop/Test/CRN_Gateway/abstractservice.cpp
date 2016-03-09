/*
 *
 * Extension i.e. a new service needs the following:
 *
 * - create header and source file like the existing extensions e.g. OfferService
 *
 * - edit this file i.e. add #include directive and new line with service constructor call
 *
 * - edit this file i.e. add static storage, if needed



                           UDP Services

   +-----------------------+---------------------+---------------------+
   | Service Enum          | Channel Enum        | Service             |
   | (request)             | (channel)           |                     |
   +-----------------------+---------------------+---------------------+
   | SERVICE_RZV (0)       | CHANNEL_RZV (0)     | RZVService          |
   |                       |                     |                     |
   | "not yet defined"     | CHANNEL_RZV (0)     | DefaultService      |
   | (1-255)               |                     |                     |
   |                       |                     |                     |
   | SERVICE_RZV (0)       | CHANNEL_CI_MATCHING | RZVService          |
   |                       | (1)                 |                     |
   |                       |                     |                     |
   | SERVICE_HEARTBEAT (1) | CHANNEL_CI_MATCHING | HeartbeatService    |
   |                       | (1)                 |                     |
   |                       |                     |                     |
   | SERVICE_OFFER_REQUEST | CHANNEL_CI_MATCHING | OfferRequestService |
   | (2)                   | (1)                 |                     |
   |                       |                     |                     |
   | SERVICE_REPLY (3)     | CHANNEL_CI_MATCHING | ReplyService        |
   |                       | (1)                 |                     |
   |                       |                     |                     |
   | "not yet defined"     | CHANNEL_CI_MATCHING | DefaultService      |
   | (4-255)               | (1)                 |                     |
   +-----------------------+---------------------+---------------------+


                           TCP Services

   +-----------------------+---------------------+---------------------+
   | Service Enum          | Channel Enum        | Service             |
   | (request)             | (channel)           |                     |
   +-----------------------+---------------------+---------------------+
   | SERVICE_RZV (0)       | CHANNEL_RZV (0)     | RZVService          |
   |                       |                     |                     |
   | "not yet defined"     | CHANNEL_RZV (0)     | DefaultService      |
   | (1-255)               |                     |                     |
   |                       |                     |                     |
   | SERVICE_RZV (0)       | CHANNEL_CI_MATCHING | RZVService          |
   |                       | (1)                 |                     |
   |                       |                     |                     |
   | SERVICE_OFFER_REQUEST | CHANNEL_CI_MATCHING | OfferRequestService |
   | (2)                   | (1)                 |                     |
   |                       |                     |                     |
   | SERVICE_REPLY (3)     | CHANNEL_CI_MATCHING | ReplyService        |
   |                       | (1)                 |                     |
   |                       |                     |                     |
   | "not yet defined"     | CHANNEL_CI_MATCHING | DefaultService      |
   | (4-255)               | (1)                 |                     |
   +-----------------------+---------------------+---------------------+

 */

#include "abstractservice.h"

#include "rzvservice.h"
#include "heartbeatservice.h"
#include "offerrequestservice.h"
#include "defaultservice.h"

#include <string>

/**
 * Static storage for ContextPackets indexed by first "contentBrick->content"
 */
static std::vector<ContextPacket*> contextPackets[UCHAR_MAX];

/*
 * Static storage for IP addresses of packet sender combined with UUID
 */
static std::vector<IpAddress*> ipAddresses;

/*
 * <new> static storage
 */
// Add line with <new> static storage here


/* mutex for static collections */
static pthread_mutex_t a_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Factory like static creator
 */
ContextService* ContextService::create(byte_t channel, byte_t request) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] channel " << (uint) channel << ", request " << (uint) request << std::endl;



	/*
	 * RZV (Reserved Zero Value) service constructor call
	 */
	if(request == SERVICE_RZV || channel == CHANNEL_RZV) {
//		if (DEBUG)
			std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new RZVService()" << std::endl;
		return new RZVService();
	}

	/*
	 * Heartbeat service constructor call
	 */
	if(channel == CHANNEL_CI_MATCHING && request == SERVICE_HEARTBEAT) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new HeartbeatService()" << std::endl;
		return new HeartbeatService();
	}

	/*
	 * OfferRequest service (offer (TCP) resp. request (UDP)) constructor call
	 */
	if(channel == CHANNEL_CI_MATCHING && request == SERVICE_OFFER_REQUEST) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new OfferRequestService()" << std::endl;
		return new OfferRequestService();
	}

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	/*
	 * Default service constructor call
	 */
//	if (DEBUG)
		std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] No known request with id " << (int) request << " - use default service instead" << std::endl;
	return new DefaultService();
}


ContextService::ContextService() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] Constructor()" << std::endl;

	errorContextPacket = new ContextPacket();
}

std::vector<ContextPacket*>* ContextService::getContextPackets(byte_t index) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return &contextPackets[index];
}

pthread_mutex_t ContextService::getContextPacketsMutex() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return a_mutex;
}


int ContextService::validateUDP(void* receivedPacket, int socket, void *buffer, size_t size, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(size < 42 || size > 1062) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] size: " << size <<  std::endl;

		/**
		 * Create header data for error
		 */
		errorHeader[0] = (byte_t) CIP_FORMAT_ERROR;
		errorHeader[1] = (byte_t) ERROR_PRIORITY_NOTICE;
		errorHeader[2] = (byte_t) CIP_FORMAT_ERROR_OUT_OF_RANGE;

		/*
		 * Create CIP for UDP reply with error
		 */
		errorContextPacket->setHeaderType(HEADER_TYPE_ERROR);
		errorContextPacket->setHeaderSize(3);
		errorContextPacket->setHeaderData(errorHeader);

		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] CIP_FORMAT_ERROR_OUT_OF_RANGE" << std::endl;
		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
		if (PRINT_PACKET_DEBUG) errorContextPacket->printPacket();

		char sendBuffer[errorContextPacket->getSize()];
		errorContextPacket->serialize(sendBuffer);

		int nbytes;
		nbytes = sendto(socket, sendBuffer,
				errorContextPacket->getSize(), 0,
				( struct sockaddr *) addr,
				sizeof(struct sockaddr));


		if (nbytes < 0) {
			perror("sendto(UDP_sock) failed");
		}
		else {
			if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] sendto(UDP_sock): " << nbytes << std::endl;

		}

		std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX : " << "UDP reply error: CIP_FORMAT_ERROR_OUT_OF_RANGE" << std::endl;

		return 1;
	}



	if( ((ContextPacket*) receivedPacket)->getSize() != size) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] ((ContextPacket*) receivedPacket)->getSize() " << ((ContextPacket*) receivedPacket)->getSize() << " != size " << size <<  std::endl;

		/**
		 * Create header data for error
		 */
		errorHeader[0] = (byte_t) CIP_FORMAT_ERROR;
		errorHeader[1] = (byte_t) ERROR_PRIORITY_NOTICE;
		errorHeader[2] = (byte_t) CIP_FORMAT_ERROR_INCONSISTENT;

		/*
		 * Create CIP for UDP reply with error
		 */
		errorContextPacket->setHeaderType(HEADER_TYPE_ERROR);
		errorContextPacket->setHeaderSize(3);
		errorContextPacket->setHeaderData(errorHeader);


		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] CIP_FORMAT_ERROR_INCONSISTENT" << std::endl;
		if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
		if (PRINT_PACKET_DEBUG) errorContextPacket->printPacket();

		char sendBuffer[errorContextPacket->getSize()];
		errorContextPacket->serialize(sendBuffer);

		int nbytes;
		nbytes = sendto(socket, sendBuffer,
				errorContextPacket->getSize(), 0,
				( struct sockaddr *) addr,
				sizeof(struct sockaddr));


		if (nbytes < 0) {
			perror("sendto(UDP_sock) failed");
		}
		else {
			if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")" << "["	<< __FUNCTION__ << "] sendto(UDP_sock): " << nbytes << std::endl;

		}

		std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX : " << "UDP reply error: CIP_FORMAT_ERROR_INCONSISTENT" << std::endl;

		return 1;
	}

	return 0;
}





bool ContextService::matchContextBricks(void* contextBrick_1, void* contextBrick_2) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	byte_t notEqual = ((ContextBrick*) contextBrick_1)->context ^ ((ContextBrick*) contextBrick_2)->context;
	if (notEqual == 0) {
		return true;
	}

	byte_t offer_relevant = ~notEqual | ((ContextBrick*) contextBrick_1)->mask;
	byte_t not_offer_relevant = ~offer_relevant;
	if (not_offer_relevant != 0) {
		return false;
	}

	byte_t request_relevant = ~notEqual | ((ContextBrick*) contextBrick_2)->mask;
	byte_t not_request_relevant = ~request_relevant;
	if (not_request_relevant != 0) {
		return false;
	}

	return true;
}

bool ContextService::matchContextPackets(void* contextPacket_1, void* contextPacket_2) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if (!matchContextBricks(((ContextPacket*) contextPacket_1)->getRootCIC(), ((ContextPacket*) contextPacket_2)->getRootCIC())) {
		return false;
	}
	if (((ContextPacket*) contextPacket_1)->getCiSize() != ((ContextPacket*) contextPacket_2)->getCiSize()) {
		return false;
	}

	unsigned int i;
	for (i = 0; i < ((ContextPacket*) contextPacket_1)->getCiSize(); i++) {
		if ( ! matchContextBricks(&(((ContextPacket*) contextPacket_1)->ciCICBricks[i]), &(((ContextPacket*) contextPacket_2)->ciCICBricks[i])) ) {
			return false;
		}
	}

	return true;
}


/**
 * Debugging method to print whole static packet storage
 */
void printPacketStorage() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	int vector_number;
	int non_empty_indices = 0;
	int sum_packets = 0;

	char str_buffer [50];
	std::string line_start;

	for (int index=0; index < UCHAR_MAX; index++) {

		if (contextPackets[index].size() == 0) {
			continue;
		}

		std::cout << std::endl;
		std::cout << "INDEX " << index << " (" << contextPackets[index].size() << " entries):" << std::endl;
		std::cout << LINE_SEPARATOR << std::endl;

		non_empty_indices++;

		vector_number = 0;
		for (std::vector<ContextPacket*>::iterator iter = contextPackets[index].begin();
				iter != contextPackets[index].end(); ++iter) {

			vector_number++;

			/*
			 * Packet print header
			 */
			std::cout << std::endl;
			std::cout << index << "_" << vector_number << ": " << getUuidString( * (*iter)->getUuid() ) << std::endl;
			std::cout << LINE_SEPARATOR << std::endl;

			/*
			 * Packet print details
			 */
			sprintf(str_buffer, "%i_%i:\t", index, vector_number);
			line_start = str_buffer;

			(*iter)->printPacket(line_start);

			std::cout << LINE_SEPARATOR << std::endl;


		}
		sum_packets += vector_number;
	}

	std::cout << std::endl;
	std::cout << "SUMMARY:" << std::endl;
	std::cout << LINE_SEPARATOR << std::endl;
	std::cout << "Number of non empty indices:" << non_empty_indices << std::endl;
	std::cout << "Number of packets:" << sum_packets << std::endl;
	std::cout << LINE_SEPARATOR << std::endl;
}


/*
 * Wrapper for printPacketStorage() to be called by derived services
 */
void ContextService::printPackets() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	printPacketStorage();
}
