#include "corepacket.h"

/**
 * ContextService
 */

ContextService *UdpContextService = NULL;
ContextService *TcpContextService = NULL;

/**
 * ContextBrick
 */

ContextBrick::ContextBrick() :
		context(0), mask(0) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;
}

ContextBrick::ContextBrick(byte_t context, byte_t mask) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	this->context = context;
	this->mask    = mask;
}

bool ContextBrick::hasMatch(ContextBrick *otherBrick) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	byte_t notEqual = this->context ^ otherBrick->context;
	if (notEqual == 0) {
		return true;
	}

	byte_t offer_relevant = ~notEqual | this->mask;
	byte_t not_offer_relevant = ~offer_relevant;
	if (not_offer_relevant != 0) {
		return false;
	}

	byte_t request_relevant = ~notEqual | otherBrick->mask;
	byte_t not_request_relevant = ~request_relevant;
	if (not_request_relevant != 0) {
		return false;
	}

	return true;
}

/**
 * IpAddress
 */

IpAddress::IpAddress(unsigned char* addressId, struct sockaddr_in sockAddress) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	memcpy(this->addressId, addressId, 16);
	this->sockAddress 	= sockAddress;
}

/**
 * ContextPacket
 */

ContextPacket::ContextPacket() :

		service(SERVICE_DEFAULT),
		version(VERSION),
		channel(CHANNEL_DEFAULT),
		additionalHeaderSize(0),
		sockAddress(),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(0),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(0) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor()" << std::endl;

	memset(&uuid, 0, sizeof(uuid));

	memset (&sockAddress, 0, sizeof(sockAddress));
	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = INADDR_LOOPBACK;

//	timestamp = time(NULL);

	memset(&additionalData, 0, HEADER_ADDITIONAL_SIZE);

	firstBrick = new ContextBrick();

	memset(&data, 0, 140);
	memset(&additionalData, 0, DATA_ADDITIONAL_SIZE);
}


ContextPacket::ContextPacket(IpAddress *ipAddress) :

		service(SERVICE_DEFAULT),
		version(VERSION),
		channel(CHANNEL_META),
		additionalHeaderSize(5),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(4),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(8) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor(IpAddress: "
			<< inet_ntoa(ipAddress->getSockAddress().sin_addr) << ":" << ntohs(ipAddress->getSockAddress().sin_port) << ")" << std::endl;

	setUuid(ipAddress->getAddressId());

//	memset(&timestamp, 0, 8);
//	timestamp = time(NULL);

	this->sockAddress = ipAddress->getSockAddress();

	// additionalHeaderData
	memset(&additionalHeaderData, 0, additionalHeaderSize);
	for (int i =0; i<additionalHeaderSize; i++) {
		additionalHeaderData[i] = '#';
	}

	// firstBrick
	firstBrick = new ContextBrick(1, 2);


	// additionalBricks
	memset(&additionalBricks, 0, additionalBricksSize);
	for (int i =0; i<additionalBricksSize; i++) {
		additionalBricks[i] = (*new ContextBrick('#', '+'));
	}

	// data
	memset(&data, '*', 140);

	// additionalData
	memset(&additionalData, 0, DATA_ADDITIONAL_SIZE);
	for (int i =0; i<additionalDataSize; i++) {
		additionalData[i] = 'x';
	}
}

/**
 * Get needed size in bytes
 */
int ContextPacket::getSize() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	// Fix bytes for service (1), version (1), channel (1), optionalHeaderSize (1), uuid (16), ipAddress (4) and portNumber (2)
	int bytes = 26;

	bytes += additionalHeaderSize;

	// Fix bytes for type (1), firstBrick (2) and optionalBrickListSize (1)
	bytes += 4;

	bytes += additionalBricksSize*2;

	// Fix bytes for type (1), data (140) and optionalDataSize (1)
	bytes += 142;

	bytes += additionalDataSize;

	return bytes;
}

/**
 * Serialize outgoing data
 */
int ContextPacket::serialize(char *buffer) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned int b = 0;

	// HEADER
	buffer[b++] = service;
	buffer[b++] = version;
	buffer[b++] = channel;
	buffer[b++] = additionalHeaderSize;

	memcpy(&buffer[b], uuid, sizeof(uuid));
	b += sizeof(uuid);

	memcpy(&buffer[b], &sockAddress.sin_addr.s_addr, sizeof(sockAddress.sin_addr.s_addr));
	b += sizeof(sockAddress.sin_addr.s_addr);

	memcpy(&buffer[b], &sockAddress.sin_port, sizeof(sockAddress.sin_port));
	b += sizeof(sockAddress.sin_port);

	memcpy(&buffer[b], &additionalHeaderData, additionalHeaderSize);
	b += additionalHeaderSize;


	// BRICKS
	buffer[b++] = contextType;
	buffer[b++] = firstBrick->context;
	buffer[b++] = firstBrick->mask;
	buffer[b++] = additionalBricksSize;

	for(int i = 0; i<additionalBricksSize; i++) {
		buffer[b++] = additionalBricks[i].context;
		buffer[b++] = additionalBricks[i].mask;
	}

	// DATA
	buffer[b++] = dataType;

	memcpy(&buffer[b], &data, DATA_SIZE);
	b += DATA_SIZE;

	buffer[b++] = additionalDataSize;

	memcpy(&buffer[b], &additionalData, additionalDataSize);
	b += additionalDataSize;

	return b;
}

/**
 * Deserialize incoming data
 */
int ContextPacket::deserialize(char *buffer) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned int b = 0;

	// HEADER
	service = buffer[b++];
	version = buffer[b++];
	channel = buffer[b++];
	additionalHeaderSize = buffer[b++];

	memcpy(uuid, &buffer[b], sizeof(uuid));
	b += sizeof(uuid);

	memcpy(&sockAddress.sin_addr.s_addr, &buffer[b], sizeof(sockAddress.sin_addr.s_addr));
	b += sizeof(sockAddress.sin_addr.s_addr);

	memcpy(&sockAddress.sin_port, &buffer[b], sizeof(sockAddress.sin_port));
	b += sizeof(sockAddress.sin_port);

	memcpy(&additionalHeaderData, &buffer[b], additionalHeaderSize);
	b += additionalHeaderSize;


	// BRICKS
	contextType = buffer[b++];
	firstBrick->context = buffer[b++];
	firstBrick->mask = buffer[b++];
	additionalBricksSize = buffer[b++];

	for(int i = 0; i<additionalBricksSize;i++) {
		additionalBricks[i].context = buffer[b++];
		additionalBricks[i].mask = buffer[b++];
	}

	// DATA
	dataType = buffer[b++];

	memcpy(&data, &buffer[b], DATA_SIZE);
	b += DATA_SIZE;

	additionalDataSize = buffer[b++];

	memcpy(&additionalData, &buffer[b], additionalDataSize);
	b += additionalDataSize;

	return b;
}

int ContextPacket::processUDP() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(UdpContextService == NULL) {
		UdpContextService = ContextService::create(service);
	}

	return UdpContextService->processUDP(this);
}

int ContextPacket::processUDP(int sock, struct sockaddr *addr) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(UdpContextService == NULL) {
		UdpContextService = ContextService::create(service);
	}

	char sendBuffer[getSize()];
	serialize(sendBuffer);

	return UdpContextService->processUDP(this, sock, sendBuffer, getSize(), addr);
}


int ContextPacket::processTCP() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(TcpContextService == NULL) {
		TcpContextService = ContextService::create(service);
	}

	return TcpContextService->processTCP(this);
}

int ContextPacket::deleteService() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//	delete UdpContextService;
//	delete TcpContextService;
	return 0;
}


bool ContextPacket::isMatchingContext(ContextPacket *request) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]"<< std::endl;

	if (this->getContextType() != request->getContextType()) {
		return false;
	}

	if ( ! this->getFirstBrick()->hasMatch(request->getFirstBrick())) {
		return false;
	}

	if (this->getOptionalBrickListSize() != request->getOptionalBrickListSize()) {
		return false;
	}

	unsigned int i;
	for (i = 0; i < this->getOptionalBrickListSize(); i++) {
		if ( ! this->additionalBricks[i].hasMatch(&request->additionalBricks[i])) {
			return false;
		}
	}

	return true;
}


/**
 * Print data for debugging
 */
void ContextPacket::printPacket(std::string line_start) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	/*
	 * Print header part
	 */
	std::cout << line_start << "Header Service:\t" << (uint) service << std::endl;
	std::cout << line_start << "Header Version:\t" << (uint) version << std::endl;
	std::cout << line_start << "Header Channel:\t" << (uint) channel << std::endl;
	std::cout << line_start << "Header OptionalHeaderSize:\t" << (uint) additionalHeaderSize << std::endl;
	std::cout << line_start << "Header UUID:\t" << getUuidString(uuid) << std::endl;
	std::cout << line_start << "Header SocketAddress:\t" << inet_ntoa(sockAddress.sin_addr) << std::endl;
	std::cout << line_start << "Header SocketPort:\t" << ntohs(sockAddress.sin_port) << std::endl;
	std::cout << line_start << "Header OptionalHeaderData:\t" << additionalHeaderData << std::endl;


//	struct tm * localtime (const time t * time )
// char * asctime (const struct tm * brokentime )
//	printf("timestamp: %s\n", asctime(localtime(getTime())));

	/*
	 * Print context part
	 */
	std::cout << line_start << "Context Type:\t" << (uint) contextType << std::endl;
	std::cout << line_start << "Context FirstBrick->context:\t" << (uint) firstBrick->context << "\t"<< getBitsString(sizeof(byte_t), &(firstBrick->context)) << std::endl;
	std::cout << line_start << "Context FirstBrick->mask:\t" << (uint) firstBrick->mask << "\t"<< getBitsString(sizeof(byte_t), &(firstBrick->mask)) << std::endl;
	std::cout << line_start << "Context AdditionalBricksSize:\t" << (uint) additionalBricksSize << std::endl;

	for (int i = 0; i < additionalBricksSize; i++) {

		std::cout << line_start << "Context AdditionalBrick[" << i << "]:\tcontext\t" << (uint) additionalBricks[i].context << "\t"<< getBitsString(sizeof(byte_t), &(additionalBricks[i].context)) << std::endl;
		std::cout << line_start << "Context AdditionalBrick[" << i << "]:\tmask\t" << (uint) additionalBricks[i].mask << "\t"<< getBitsString(sizeof(byte_t), &(additionalBricks[i].mask)) << std::endl;

	}

	/*
	 * Print data part
	 */
	std::cout << line_start << "Data Type:\t" << (uint) dataType << std::endl;
	std::cout << line_start << "Data Text:\t\"" << data << "\"" << std::endl;
	std::cout << line_start << "Data OptionalDataSize:\t" << (uint) additionalDataSize << std::endl;
	std::cout << line_start << "Data OptionalData:\t\"" << additionalData << "\"" << std::endl;

}


