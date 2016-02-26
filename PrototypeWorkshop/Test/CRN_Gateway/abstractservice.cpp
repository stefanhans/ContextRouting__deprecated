/*
 *
 * Extension i.e. a new service needs the following:
 *
 * - create header and source file like the existing extensions e.g. OfferService
 *
 * - edit this file i.e. add #include directive and new line with service constructor call
 *
 * - edit this file i.e. add static storage, if needed
 *
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
ContextService* ContextService::create(byte_t service) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) service << std::endl;

	/*
	 * Reserved Zero Value (RZV) service constructor call (CIP request 0)
	 */
	if(service == SERVICE_RZV) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new RZVService()" << std::endl;
		return new RZVService();
	}

	/*
	 * Heartbeat service constructor call (CIP request 1)
	 */
	if(service == SERVICE_HEARTBEAT) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new HeartbeatService()" << std::endl;
		return new HeartbeatService();
	}

	/*
	 * Offer (TCP) resp. Request (UDP) service constructor call (CIP request 2)
	 */
	if(service == SERVICE_OFFER_REQUEST) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] new OfferRequestService()" << std::endl;
		return new OfferRequestService();
	}

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	/*
	 * Default service  (CIP request -255)
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] No known service with id " << (int) service << " - use default service instead" << std::endl;
	return new DefaultService();
}


ContextService::ContextService() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] Constructor()" << std::endl;

}

std::vector<ContextPacket*>* ContextService::getContextPackets(byte_t index) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return &contextPackets[index];
}

pthread_mutex_t ContextService::getContextPacketsMutex() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return a_mutex;
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
