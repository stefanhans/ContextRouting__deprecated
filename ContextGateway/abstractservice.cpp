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

#include "offerservice.h"
#include "requestservice.h"

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

int ContextService::storePacket(void* packet) {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

    int rc;	/* contain mutex lock/unlock results */

    /* lock the mutex, to assure exclusive access to 'a' and 'b'. */
    rc = pthread_mutex_lock(&a_mutex);

    /* an error has occurred */
    if (rc) {
        perror("pthread_mutex_lock");
        pthread_exit(NULL);
    }

	contextPackets[((ContextPacket*) packet)->getFirstBrick()->context].push_back((ContextPacket*) packet);

    /* unlock mutex */
    rc = pthread_mutex_unlock(&a_mutex);

    if (rc) {
        perror("pthread_mutex_unlock");
        pthread_exit(NULL);
	}

	return 0;
};

bool ContextService::matchContextBricks(void* contextBrick_1, void* contextBrick_2) {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

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
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if (!matchContextBricks(((ContextPacket*) contextPacket_1)->getFirstBrick(), ((ContextPacket*) contextPacket_2)->getFirstBrick())) {
		return false;
	}
	if (((ContextPacket*) contextPacket_1)->getOptionalBrickListSize() != ((ContextPacket*) contextPacket_2)->getOptionalBrickListSize()) {
		return false;
	}

	unsigned int i;
	for (i = 0; i < ((ContextPacket*) contextPacket_1)->getOptionalBrickListSize(); i++) {
		if ( ! matchContextBricks(&(((ContextPacket*) contextPacket_1)->additionalBricks[i]), &(((ContextPacket*) contextPacket_2)->additionalBricks[i])) ) {
			return false;
		}
	}

	return true;
}

int ContextService::getNumberOfPackets() {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return sizeof(contextPackets) / sizeof(contextPackets[0]);
};


void printPacketStorage() {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;
//	std::cout << "printPacketStorage()" << std::endl;
//	std::cout << "getNumberOfPackets(): " << (sizeof(contextPackets) / sizeof(contextPackets[0])) << std::endl;

	for (int index=0; index < UCHAR_MAX; index++) {

		if (contextPackets[index].size() == 0) {
//			printf("contextPackets[%i] (%02x) is empty()\n", index, index);
			continue;
		}

//		printf("contextPackets[%i] (%02x) has %lu entries()\n", index, index, contextPackets[index].size());

		for (std::vector<ContextPacket*>::iterator iter = contextPackets[index].begin();
				iter != contextPackets[index].end(); ++iter) {


			printUuid( * (*iter)->getUuid() );

//			std::cout << getUuidString( * (*iter)->getUuid() ) << std::endl;

//			printBits(sizeof(byte_t), &((*iter)->getFirstBrick()->context));
//			printBits(sizeof(byte_t), &((*iter)->getFirstBrick()->mask));


		}

	}





	//						if (storage->contextPackets[receivedContextPacket->getContextType()].size() == 0) {
	//							printf("contextPackets[contextType] is empty()\n");
	//							continue;
	//						}
	//
	//						for (std::vector<ContextPacket*>::iterator iter = storage->contextPackets[receivedContextPacket->getContextType()].begin();
	//								iter != storage->contextPackets[receivedContextPacket->getContextType()].end(); ++iter) {
	//
	//							printf("for\n");
	//
	//							if ((*iter)->isMatchingContext(receivedContextPacket)) {
	//
	//								printf("if\n");
	//								printf("(*iter)->getSize(): %u\n", (*iter)->getSize());
	//
	//								char sendBuffer[(*iter)->getSize()];
	//
	//								(*iter)->serialize(sendBuffer);
	//
	//								nbytes = sendto(UDP_sock, sendBuffer, (*iter)->getSize(), 0, (struct sockaddr *) &UDP_addr, size);
	//								if (nbytes < 0) {
	//									perror("sendto (UDP_sock)");
	//									exit(EXIT_FAILURE);
	//								}
	//							}
	//						}
}

void ContextService::printPackets() {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	printPacketStorage();
}




ContextService* ContextService::create(byte_t service) {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) service << std::endl;

	/*
	 * Offer service constructor call
	 */
	if(service == SERVICE_OFFER) return new OfferService();
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	/*
	 * Request service constructor call
	 */
	if(service == SERVICE_REQUEST) return new RequestService();
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	return new OfferService();
}

ContextService::ContextService() {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//	vector<ContextPacket*> contextPackets[UCHAR_MAX];
}
