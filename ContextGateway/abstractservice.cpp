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
	return sizeof(contextPackets) / sizeof(contextPackets[0]);
};



ContextService* ContextService::create(byte_t service) {

	/*
	 * Offer service constructor call
	 */
	if(service == SERVICE_OFFER) return new OfferService();

	/*
	 * Request service constructor call
	 */
	if(service == SERVICE_REQUEST) return new RequestService();

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	return NULL;
}

ContextService::ContextService() {

//	vector<ContextPacket*> contextPackets[UCHAR_MAX];
}
