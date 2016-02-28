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
		context(0), mask(0) {}

ContextBrick::ContextBrick(byte_t context, byte_t mask) {
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

		request(0),
		profile(0),
		version(VERSION),
		channel(CHANNEL_RZV),
		sockAddress(),
		headerType(0),
		headerSize(0),
		ciType(CI_TYPE_RZV),
		ciSize(0),
		appDataType(APP_TYPE_RZV),
		appDataSize(0) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor()" << std::endl;

	memset(&uuid, 0, sizeof(uuid));

	memset (&sockAddress, 0, sizeof(sockAddress));
	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = INADDR_ANY;

	setTime();

	rootCIC = new ContextBrick();

	memset(&headerData, 0, HEADER_ADDITIONAL_SIZE);
	memset(&appData, 0, DATA_ADDITIONAL_SIZE);

	if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ContextPacket::ContextPacket()" << std::endl;
	if (PRINT_PACKET_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------ " << std::endl;
	if (PRINT_PACKET_DEBUG) this->printPacket();
}


ContextPacket::ContextPacket(IpAddress *ipAddress) :

		request(0),
		profile(0),
		version(VERSION),
		channel(CHANNEL_RZV),
		headerType(0),
		headerSize(0),
		ciType(CI_TYPE_RZV),
		ciSize(4),
		appDataType(APP_TYPE_RZV),
		appDataSize(8) {

	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]  Constructor(IpAddress: "
			<< inet_ntoa(ipAddress->getSockAddress().sin_addr) << ":" << ntohs(ipAddress->getSockAddress().sin_port) << ")" << std::endl;

	// UUID
	setUuid();

	// IP address and port
	sockAddress = ipAddress->getSockAddress();

	// Current timestamp
	setTime();

	// headerData
	memset(&headerData, 0, headerSize);
	for (int i =0; i<headerSize; i++) {
		headerData[i] = '\0';
	}

	// root-CIC
	rootCIC = new ContextBrick(0, 0);


	// additional CIC-Bricks
	memset(&ciCICBricks, 0, ciSize);
	for (int i =0; i<ciSize; i++) {
		ciCICBricks[i] = (*new ContextBrick('#', '+'));
	}

	// Application data
	memset(&appData, 0, DATA_ADDITIONAL_SIZE);
	for (int i =0; i<appDataSize; i++) {
		appData[i] = 'x';
	}
}

/**
 * Get needed size in bytes
 */
size_t ContextPacket::getSize() {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	// Fix bytes for request(1),  profile(1),  version(1),  channel(1), uuid(16), ipAddress(4), portNumber(2), time(8), type(1), size(1)
	int bytes = 36;

	// 0 - 255
	bytes += headerSize;

	// Fix bytes for CI type (1), root-CIC (2) and CI size (1)
	bytes += 4;

	// 0 - 510
	bytes += ciSize*2;

	// Fix bytes for application data type (1), application data size (1)
	bytes += 2;

	// 0 - 255
	bytes += appDataSize;

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


	buffer[b++] = request;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] request: " << request << std::endl;

	buffer[b++] = profile;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] profile: " << profile << std::endl;

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

	buffer[b++] = headerType;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerType: " << (int) headerType << std::endl;


	buffer[b++] = headerSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerSize: " << (int) headerSize << std::endl;

	memcpy(&buffer[b], &headerData, headerSize);
	b += headerSize;
	for(size_t j = 0; j < headerSize; j++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerData[" << j << "]: " << (int) headerData[j] << std::endl;
	}

	/*
	 * BRICKS
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] BRICKS: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;


	buffer[b++] = ciType;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciType: " << (int) ciType << std::endl;

	buffer[b++] = rootCIC->context;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] rootCIC->context: " << (int) rootCIC->context << std::endl;

	buffer[b++] = rootCIC->mask;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] rootCIC->mask: " << (int) rootCIC->mask << std::endl;

	buffer[b++] = ciSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciSize: " << (int) ciSize << std::endl;

	for(int i = 0; i<ciSize; i++) {
		buffer[b++] = ciCICBricks[i].context;
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciCICBricks[" << i << "].context: " << (int) ciCICBricks[i].context << std::endl;
		buffer[b++] = ciCICBricks[i].mask;
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciCICBricks[" << i << "].mask: " << (int) ciCICBricks[i].mask << std::endl;
	}

	/*
	 * DATA
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DATA: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;


	buffer[b++] = appDataSize;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalDataSize: " << (int) appDataSize << std::endl;

	buffer[b++] = appDataType;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] dataType: " << (int) appDataType << std::endl;

	memcpy(&buffer[b], &appData, appDataSize);
	b += appDataSize;

	for(int i = 0; i < appDataSize; i++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] additionalData[" << i << "]: " << (int) appData[i] << std::endl;
	}

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


	request = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] request: " << (int) request << std::endl;

	profile = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] profile: " << (int) profile << std::endl;


	version = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] version: " << (int) version << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] major version: " << (int) getMajorVersion(version) << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] minor version: " << (int) getMinorVersion(version) << std::endl;

	channel = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] channel: " << (int) channel << std::endl;

	memcpy(uuid, &buffer[b], sizeof(uuid));
	b += sizeof(uuid);
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] uuid: " << getUuidString(uuid) << std::endl;

	memcpy(&sockAddress.sin_addr.s_addr, &buffer[b], sizeof(sockAddress.sin_addr.s_addr));
	b += sizeof(sockAddress.sin_addr.s_addr);

	memcpy(&sockAddress.sin_port, &buffer[b], sizeof(sockAddress.sin_port));
	b += sizeof(sockAddress.sin_port);

	setTime();
	b += 8;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] time: " << (long int) time << std::endl;

	headerType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerType: " << (int) headerType << std::endl;

	headerSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerSize: " << (int) headerSize << std::endl;

	memcpy(&headerData, &buffer[b], headerSize);
	b += headerSize;
	for(int j = 0; j < headerSize; j++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] headerData[" << j << "]: " << (int) headerData[j] << std::endl;
	}


	/*
	 * BRICKS
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] BRICKS: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;


	ciType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciType: " << (int) ciType << std::endl;

	rootCIC->context = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] rootCIC->context: " << (int) rootCIC->context << std::endl;

	rootCIC->mask = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] rootCIC->mask: " << (int) rootCIC->mask << std::endl;

	ciSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciSize: " << (int) ciSize << std::endl;

	for(int i = 0; i < ciSize; i++) {
		ciCICBricks[i].context = buffer[b++];
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciCICBricks[" << i << "].context: " << (int) ciCICBricks[i].context << std::endl;
		ciCICBricks[i].mask = buffer[b++];
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ciCICBricks[" << i << "].mask: " << (int) ciCICBricks[i].mask << std::endl;
	}


	/*
	 * DATA
	 */
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] DATA: "  << std::endl;
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] ------------"  << std::endl;


	appDataType = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] appDataType: " << (int) appDataType << std::endl;

	appDataSize = buffer[b++];
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] appDataSize: " << (int) appDataSize << std::endl;

	memcpy(&appData, &buffer[b], appDataSize);
	b += appDataSize;
	for(int i = 0; i < appDataSize; i++) {
		if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] appData[" << i << "]: " << (int) appData[i] << std::endl;
	}

	return 0;
}

int ContextPacket::processUDP(int sock, struct sockaddr *addr, int UDP_bytes_received) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(UdpContextService == NULL) {
		UdpContextService = ContextService::create(request, channel);
	}

	char sendBuffer[getSize()];
	serialize(sendBuffer);

	int validated = UdpContextService->validateUDP(this, sock, sendBuffer, UDP_bytes_received, addr);

	if(validated == 0) {
		return UdpContextService->processUDP(this, sock, sendBuffer, getSize(), addr);
	}
	return 1;
}


int ContextPacket::processTCP() {
	if (THREAD_DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	if(TcpContextService == NULL) {
		TcpContextService = ContextService::create(request, channel);
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
	std::cout << line_start << "Header Request:\t" << (uint) request << std::endl;
	std::cout << line_start << "Header Profile:\t" << (uint) profile << std::endl;
	std::cout << line_start << "Header Version:\t" << (uint) version << std::endl;
	std::cout << line_start << "Header Channel:\t" << (uint) channel << std::endl;
	std::cout << line_start << "Header UUID:\t" << getUuidString(uuid) << std::endl;
	std::cout << line_start << "Header IP address:\t" << inet_ntoa(sockAddress.sin_addr) << std::endl;
	std::cout << line_start << "Header IP Port:\t" << ntohs(sockAddress.sin_port) << std::endl;
	std::cout << line_start << "Header time:\t" << ctime(getTime()) << std::ends;
	std::cout << line_start << "Header type:\t" << (uint) headerType << std::endl;
	std::cout << line_start << "Header size:\t" << (uint) headerSize << std::endl;
	for(uint i=0; i<(uint) headerSize;i++) {
		std::cout << line_start << "Header Data[" << i << "]:\t" << (uint) headerData[i] << std::endl;
	}

	/*
	 * Print context part
	 */
	std::cout << line_start << "CI Type:\t" << (uint) ciType << std::endl;
	std::cout << line_start << "CI root-CIC->context:\t" << (uint) rootCIC->context << "\t"<< getBitsString(sizeof(byte_t), &(rootCIC->context)) << std::endl;
	std::cout << line_start << "CI root-CIC->mask:\t\t" << (uint) rootCIC->mask << "\t"<< getBitsString(sizeof(byte_t), &(rootCIC->mask)) << std::endl;
	std::cout << line_start << "CI Size:\t" << (uint) ciSize << std::endl;
	for (int i = 0; i < ciSize; i++) {
		std::cout << line_start << "CI CICBrick[" << i << "]:\tcontext\t" << (uint) ciCICBricks[i].context << "\t"<< getBitsString(sizeof(byte_t), &(ciCICBricks[i].context)) << std::endl;
		std::cout << line_start << "CI CICBrick[" << i << "]:\tmask\t" << (uint) ciCICBricks[i].mask << "\t"<< getBitsString(sizeof(byte_t), &(ciCICBricks[i].mask)) << std::endl;
	}

	/*
	 * Print data part
	 */
	std::cout << line_start << "Application Data Type:\t" << (uint) appDataType << std::endl;
	std::cout << line_start << "Application Data Size:\t" << (uint) appDataSize << std::endl;
	for(uint i=0; i<(uint) appDataSize;i++) {
		std::cout << line_start << "Application Data[" << i << "]:\t" << (uint) appData[i] << std::endl;
	}

}


