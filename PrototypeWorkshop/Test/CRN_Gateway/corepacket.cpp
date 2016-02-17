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

		sg_request(0),
		sg_profile(0),
		service(SERVICE_RZV),
		version(VERSION),
		channel(CHANNEL_DEFAULT),
		sockAddress(),
		additionalHeaderType(0),
		additionalHeaderSize(0),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(0),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(0) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor()" << std::endl;

	memset(&uuid, 0, sizeof(uuid));

	memset (&sockAddress, 0, sizeof(sockAddress));
	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = INADDR_LOOPBACK;

	timestamp = time(NULL);

	memset(&additionalData, 0, HEADER_ADDITIONAL_SIZE);

	firstBrick = new ContextBrick();

	memset(&additionalData, 0, DATA_ADDITIONAL_SIZE);
}


ContextPacket::ContextPacket(IpAddress *ipAddress) :

		sg_request(0),
		sg_profile(0),
		service(SERVICE_RZV),
		version(VERSION),
		channel(CHANNEL_META),
		additionalHeaderType(0),
		additionalHeaderSize(0),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(4),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(8) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor(IpAddress: "
			<< inet_ntoa(ipAddress->getSockAddress().sin_addr) << ":" << ntohs(ipAddress->getSockAddress().sin_port) << ")" << std::endl;

	setUuid(ipAddress->getAddressId());

//	memset(&timestamp, 0, 8);
//	timestamp = time(NULL);

	this->setTime();

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

	// Fix bytes for request(1),  profile(1),  version(1),  channel(1), uuid(16), ipAddress(4), portNumber(2), time(8), type(1), size(1)
	int bytes = 36;

	// 0 - 255
	bytes += additionalHeaderSize;

	// Fix bytes for type (1), firstBrick (2) and optionalBrickListSize (1)
	bytes += 4;

	// 0 - 510
	bytes += additionalBricksSize*2;

	// Fix bytes for type (1), optionalDataSize (1)
	bytes += 2;

	// 0 - 255
	bytes += additionalDataSize;

	// 42 - 1062
	return bytes;
}

/**
 * Serialize outgoing data
 */
int ContextPacket::serialize(char *buffer) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned int b = 0;


	/*
	 * HEADER
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] HEADER: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	buffer[b++] = sg_request;
	buffer[b++] = sg_profile;

	if(hasClientService(sg_request)) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_request:  ClientService" << std::endl;
	}
	else {

		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_request:  No ClientService" << std::endl;
	}

	if(hasClientService(sg_profile)) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_profile:  ClientService" << std::endl;
	}
	else {

		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_profile:  No ClientService" << std::endl;
	}

	if(hasGatewayService(sg_request)) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_request:  GatewayService" << std::endl;
	}
	else {

		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_request:  No GatewayService" << std::endl;
	}

	if(hasGatewayService(sg_profile)) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_profile:  GatewayService" << std::endl;
	}
	else {

		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_profile:  No GatewayService" << std::endl;
	}

	buffer[b++] = version;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] version: " << (int) version << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] major version: " << (int) getMajorVersion(version) << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] minor version: " << (int) getMinorVersion(version) << std::endl;

	buffer[b++] = channel;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] channel: " << (int) channel << std::endl;

	memcpy(&buffer[b], uuid, sizeof(uuid));
	b += sizeof(uuid);
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] uuid: " << getUuidString(uuid) << std::endl;

	memcpy(&buffer[b], &sockAddress.sin_addr.s_addr, sizeof(sockAddress.sin_addr.s_addr));
	b += sizeof(sockAddress.sin_addr.s_addr);
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sockAddress.sin_addr: " << inet_ntoa(sockAddress.sin_addr) << std::endl;

	memcpy(&buffer[b], &sockAddress.sin_port, sizeof(sockAddress.sin_port));
	b += sizeof(sockAddress.sin_port);
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sockAddress.sin_port: " <<  ntohs(sockAddress.sin_port) << std::endl;

	memcpy(&buffer[b], &timestamp, 8);
	b += 8;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] timestamp: " << (long int) timestamp << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] timestamp: " << asctime (localtime (&timestamp)) << std::ends;

	buffer[b++] = additionalHeaderType;

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderType: " << (int) additionalHeaderType << std::endl;


	buffer[b++] = additionalHeaderSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderSize: " << (int) additionalHeaderSize << std::endl;

	memcpy(&buffer[b], &additionalHeaderData, additionalHeaderSize);
	b += additionalHeaderSize;

	for(size_t j = 0; j < additionalHeaderSize; j++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderData[" << j << "]: " << (int) additionalHeaderData[j] << std::endl;
	}

	/*
	 * BRICKS
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] BRICKS: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	buffer[b++] = contextType;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] contextType: " << (int) contextType << std::endl;

	buffer[b++] = firstBrick->context;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] firstBrick->context: " << (int) firstBrick->context << std::endl;

	buffer[b++] = firstBrick->mask;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] firstBrick->mask: " << (int) firstBrick->mask << std::endl;

	buffer[b++] = additionalBricksSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricksSize: " << (int) additionalBricksSize << std::endl;
//!!!
//	for(int i = 0; i<additionalBricksSize; i++) {
//		buffer[b++] = additionalBricks[i].context;
//		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricks[" << i << "].context: " << (int) additionalBricks[i].context << std::endl;
//		buffer[b++] = additionalBricks[i].mask;
//		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricks[" << i << "].mask: " << (int) additionalBricks[i].mask << std::endl;
//	}
//!!!

	/*
	 * DATA
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DATA: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	buffer[b++] = additionalDataSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalDataSize: " << (int) additionalDataSize << std::endl;

	buffer[b++] = dataType;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] dataType: " << (int) dataType << std::endl;
//!!!
//	memcpy(&buffer[b], &data, DATA_SIZE);
//	b += DATA_SIZE-1;
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] data: " << data << std::endl;
//
//	memcpy(&buffer[b], &additionalData, additionalDataSize);
//	b += additionalDataSize;
//
//	for(int i = 0; i < additionalDataSize; i++) {
//		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalData[" << i << "]: " << (int) additionalData[i] << std::endl;
//	}
//!!!
	return b;
}

/**
 * Deserialize incoming data
 */
int ContextPacket::deserialize(char *buffer) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned int b = 0;

	/*
	 * HEADER
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] HEADER: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	sg_request = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_request: " << (int) sg_request << std::endl;

	sg_profile = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] sg_profile: " << (int) sg_profile << std::endl;


	version = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] version: " << (int) version << std::endl;
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] major version: " << (int) getMajorVersion(version) << std::endl;
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] minor version: " << (int) getMinorVersion(version) << std::endl;

	channel = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] channel: " << (int) channel << std::endl;

	memcpy(uuid, &buffer[b], sizeof(uuid));
	b += sizeof(uuid);
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] uuid: " << getUuidString(uuid) << std::endl;

//	memcpy(&sockAddress.sin_addr.s_addr, &buffer[b], sizeof(sockAddress.sin_addr.s_addr));
	b += sizeof(sockAddress.sin_addr.s_addr);

//	memcpy(&sockAddress.sin_port, &buffer[b], sizeof(sockAddress.sin_port));
	b += sizeof(sockAddress.sin_port);

//	memcpy(&timestamp, &buffer[b], 8);
	setTime();
	b += 8;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] timestamp: " << (long int) timestamp << std::endl;

	additionalHeaderType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderType: " << (int) additionalHeaderType << std::endl;

	additionalHeaderSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderSize: " << (int) additionalHeaderSize << std::endl;

	memcpy(&additionalHeaderData, &buffer[b], additionalHeaderSize);
	b += additionalHeaderSize;

	for(int j = 0; j < additionalHeaderSize; j++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalHeaderData[" << j << "]: " << (int) additionalHeaderData[j] << std::endl;
	}


	/*
	 * BRICKS
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] BRICKS: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	contextType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] contextType: " << (int) contextType << std::endl;

	firstBrick->context = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] firstBrick->context: " << (int) firstBrick->context << std::endl;

	firstBrick->mask = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] firstBrick->mask: " << (int) firstBrick->mask << std::endl;

	additionalBricksSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricksSize: " << (int) additionalBricksSize << std::endl;

	for(int i = 0; i < additionalBricksSize; i++) {
		additionalBricks[i].context = buffer[b++];
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricks[" << i << "].context: " << (int) additionalBricks[i].context << std::endl;

		additionalBricks[i].mask = buffer[b++];
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalBricks[" << i << "].mask: " << (int) additionalBricks[i].mask << std::endl;
	}

	/*
	 * DATA
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DATA: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;

	dataType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] dataType: " << (int) dataType << std::endl;

	additionalDataSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalDataSize: " << (int) additionalDataSize << std::endl;

	memcpy(&additionalData, &buffer[b], additionalDataSize);
	b += additionalDataSize;

	for(int i = 0; i < additionalDataSize; i++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalData[" << i << "]: " << (int) additionalData[i] << std::endl;
	}

	return 0;
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

	return 0;
}

int ContextPacket::deleteService() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

//	delete UdpContextService;
//	delete TcpContextService;
	return 0;
}


/**
 * Print data for debugging
 */
void ContextPacket::printPacket(std::string line_start) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	/*
	 * Print header part
	 */
	std::cout << line_start << "Header Request:\t" << (uint) sg_request << std::endl;
	std::cout << line_start << "Header Profile:\t" << (uint) sg_profile << std::endl;
	std::cout << line_start << "Header Version:\t" << (uint) version << std::endl;
	std::cout << line_start << "Header Channel:\t" << (uint) channel << std::endl;
	std::cout << line_start << "Header UUID:\t" << getUuidString(uuid) << std::endl;
	std::cout << line_start << "Header IP address:\t" << inet_ntoa(sockAddress.sin_addr) << std::endl;
	std::cout << line_start << "Header IP Port:\t" << ntohs(sockAddress.sin_port) << std::endl;
	std::cout << line_start << "Header time:\t" << ctime(getTime()) << std::endl;
	std::cout << line_start << "Header type:\t" << (uint) additionalHeaderType << std::endl;
	std::cout << line_start << "Header size:\t" << (uint) additionalHeaderSize << std::endl;
	for(uint i=0; i<(uint) additionalHeaderSize;i++) {
		std::cout << line_start << "Header OptionalHeaderData[" << i << "]:\t" << (uint) additionalHeaderData[i] << std::endl;
	}


//	struct tm * localtime (const time t * time )
// char * asctime (const struct tm * brokentime )
//	printf("timestamp: %s\n", asctime(localtime(getTime())));

	/*
	 * Print context part
	 */
	std::cout << line_start << "Context Type:\t" << (uint) contextType << std::endl;
	std::cout << line_start << "Context root-CIC->context:\t" << (uint) firstBrick->context << "\t"<< getBitsString(sizeof(byte_t), &(firstBrick->context)) << std::endl;
	std::cout << line_start << "Context root-CIC->mask:\t" << (uint) firstBrick->mask << "\t"<< getBitsString(sizeof(byte_t), &(firstBrick->mask)) << std::endl;
	std::cout << line_start << "Context AdditionalBricksSize:\t" << (uint) additionalBricksSize << std::endl;
	for (int i = 0; i < additionalBricksSize; i++) {
		std::cout << line_start << "Context AdditionalBrick[" << i << "]:\tcontext\t" << (uint) additionalBricks[i].context << "\t"<< getBitsString(sizeof(byte_t), &(additionalBricks[i].context)) << std::endl;
		std::cout << line_start << "Context AdditionalBrick[" << i << "]:\tmask\t" << (uint) additionalBricks[i].mask << "\t"<< getBitsString(sizeof(byte_t), &(additionalBricks[i].mask)) << std::endl;
	}

	/*
	 * Print data part
	 */
	std::cout << line_start << "Application Type:\t" << (uint) dataType << std::endl;
	std::cout << line_start << "Application OptionalDataSize:\t" << (uint) additionalDataSize << std::endl;
	for(uint i=0; i<(uint) additionalDataSize;i++) {
		std::cout << line_start << "Application OptionalData[" << i << "]:\t" << (uint) additionalData[i] << std::endl;
	}

}


