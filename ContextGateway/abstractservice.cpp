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
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

    int rc;	/* contain mutex lock/unlock results */

    /* lock the mutex, to assure exclusive access to 'a' and 'b'. */
    rc = pthread_mutex_lock(&a_mutex);

    /* an error has occurred */
    if (rc) {
        perror("pthread_mutex_lock");
        pthread_exit(NULL);
    }

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] :"
			" push_back at index " << (uint) ((ContextPacket*) packet)->getFirstBrick()->context << std::endl;

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

void ContextService::findMatchingContextPackets(void* contextPacket) {
	if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(contextPackets[((ContextPacket*) contextPacket)->getFirstBrick()->context].size() == 0) {
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;
		return;
	}

	for (std::vector<ContextPacket*>::iterator iter = contextPackets[((ContextPacket*) contextPacket)->getFirstBrick()->context].begin();
									iter != contextPackets[((ContextPacket*) contextPacket)->getFirstBrick()->context].end(); ++iter) {
		if(matchContextPackets((*iter), (ContextPacket*) contextPacket)) {
			(*iter)->printPacket("FOUND: ");


			char sendBuffer[(*iter)->getSize()];

			(*iter)->serialize(sendBuffer);




//			struct sockaddr_in name;
//			int sock;
//
//			/* Create the socket. */
//			sock = socket(AF_INET, SOCK_DGRAM, 0);
//
//			if (sock < 0) {
//				perror("socket");
//				exit(EXIT_FAILURE);
//			}
//
//			/* Bind a name to the socket. */
//			name.sin_family = AF_INET;
//			name.sin_port = htons(PORT_UDP_META);
//			name.sin_addr.s_addr = inet_addr("127.0.0.1");
//
//			if (bind(sock, (struct sockaddr *) &name, sizeof(name)) < 0) {
//				std::cerr << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << " ";
//				perror("ERROR");
//				exit(EXIT_FAILURE);
//			}
//
//
////			(struct sockaddr *) &UDP_addr
//			int nbytes = send(UDP_sock, sendBuffer, (*iter)->getSize(), 0);
//			if (nbytes < 0) {
//				perror("sendto (UDP_sock)");
//				exit(EXIT_FAILURE);
//			}
		}
	}
}

int ContextService::getNumberOfPackets() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	return sizeof(contextPackets) / sizeof(contextPackets[0]);
};


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
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	printPacketStorage();
}




ContextService* ContextService::create(byte_t service) {
	if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) service << std::endl;

	/*
	 * Offer service constructor call
	 */
	if(service == SERVICE_OFFER) {
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) service << std::endl;
		return new OfferService();
	}

	/*
	 * Request service constructor call
	 */
	if(service == SERVICE_REQUEST) {
		if (! DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << (uint) service << std::endl;
		return new RequestService();
	}

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	return 0;
}

ContextService::ContextService() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//	vector<ContextPacket*> contextPackets[UCHAR_MAX];
}
