/*
 * corepacket.cpp
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */

#include "corepacket.h"
#include "abstractservice.h"

ContextService *contextService = NULL;

/**
 * ContextBrick
 */

ContextBrick::ContextBrick() :
		context(0), mask(0) {
}

ContextBrick::ContextBrick(byte_t context, byte_t mask) {

	this->context = context;
	this->mask    = mask;
}

bool ContextBrick::hasMatch(ContextBrick *otherBrick) {

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

IpAddress::IpAddress(unsigned char* addressId, struct sockaddr_in sockAddress) {

	memcpy(this->addressId, addressId, 16);
	this->sockAddress 	= sockAddress;
}

/**
 * ContextPacket
 */

ContextPacket::ContextPacket() :

		service(SERVICE_DEFAULT),
		version(0),
		channel(CHANNEL_DEFAULT),
		additionalHeaderSize(0),
		sockAddress(),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(0),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(0) {

	memset(&uuid, 0, sizeof(uuid));

	memset (&sockAddress, 0, sizeof(sockAddress));
	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = INADDR_LOOPBACK;

//	timestamp = time(NULL);

	memset(&additionalData, 0, HEADER_ADDITIONAL_SIZE);

	firstBrick = new ContextBrick();

	memset(&data, 0, 140);
	memset(&additionalData, 0, DATA_ADDITIONAL_SIZE);



	//	ContextService *contextService = NULL;
}


ContextPacket::ContextPacket(IpAddress *ipAddress) :

		service(SERVICE_RECEIPT),
		version(0),
		channel(CHANNEL_META),
		additionalHeaderSize(5),
		contextType(CONTEXT_TYPE_DEFAULT),
		additionalBricksSize(4),
		dataType(DATA_TYPE_DEFAULT),
		additionalDataSize(8) {

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

	unsigned int b = 0;

	printf("service:\t%u\n", service);
	printf("version:\t%u\n", version);
	printf("channel:\t%u\n", channel);
	printf("additionalHeaderSize:\t%u\n", additionalHeaderSize);

	printf("uuid:\t");
	size_t i;
	for (i = 0; i < sizeof(uuid); i++) {
		printf("%02x", uuid[i]);
	}
	putchar('\n');


	printf("sockAddress.sin_addr:\t%s\n", inet_ntoa(sockAddress.sin_addr));
	printf("sockAddress.sin_port:\t%u\n", ntohs(sockAddress.sin_port));

	printf("additionalHeaderData: ");
	for (int i = 0; i < additionalHeaderSize; i++) {
		printf("%c", additionalHeaderData[i]);
	}
	putchar('\n');



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
	printf("additionalBricks: ");
	for (int i = 0; i < additionalBricksSize; i++) {
		printf("additionalBricks[%u].context: %c\n", i, additionalBricks[i].context);
		printf("additionalBricks[%u].context: %i\n", i, additionalBricks[i].context);
		printf("additionalBricks[%u].mask: %c\n", i, additionalBricks[i].mask);
		printf("additionalBricks[%u].mask: %i\n", i, additionalBricks[i].mask);
	}
	putchar('\n');

	// DATA

	buffer[b++] = dataType;

	memcpy(&buffer[b], &data, DATA_SIZE);
	b += DATA_SIZE;

	buffer[b++] = additionalDataSize;

	memcpy(&buffer[b], &additionalData, additionalDataSize);
	b += additionalDataSize;

	printf("additionalDataSize: %i\n", additionalDataSize);
	for (int i = 0; i < additionalDataSize; i++) {
		printf("additionalData[%u]: %c\n", i, additionalData[i]);
	}
	putchar('\n');

	return b;
}

/**
 * Deserialize incoming data
 */
int ContextPacket::deserialize(char *buffer) {

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

	if(contextService == NULL) {
		contextService = ContextService::create(service);
	}

	return contextService->processUDP(this);
}


int ContextPacket::processTCP() {

	if(contextService == NULL) {
		contextService = ContextService::create(service);
	}

	return contextService->processTCP(this);
}


int ContextPacket::answerUDP() {

	if(contextService == NULL) {
		contextService = ContextService::create(service);
	}

	return contextService->answerUDP(this);
}

int ContextPacket::answerTCP() {

	if(contextService == NULL) {
		contextService = ContextService::create(service);
	}

	return contextService->answerTCP(this);
}


bool ContextPacket::isMatchingContext(ContextPacket *request) {

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
void ContextPacket::printPacket() {


	// HEADER

	printf("service:\t%u\n", service);
	printf("version:\t%u\n", version);
	printf("channel:\t%u\n", channel);
	printf("additionalHeaderSize:\t%u\n", additionalHeaderSize);

	printf("uuid:\t");
	size_t i;
	for (i = 0; i < sizeof(uuid); i++) {
		printf("%02x", uuid[i]);
	}
	putchar('\n');


	printf("sockAddress.sin_addr:\t%s\n", inet_ntoa(sockAddress.sin_addr));
	printf("sockAddress.sin_port:\t%u\n", ntohs(sockAddress.sin_port));


//	struct tm * localtime (const time t * time )
// char * asctime (const struct tm * brokentime )
//	printf("timestamp: %s\n", asctime(localtime(getTime())));

	printf("additionalHeaderData:\n0x: ");
	for (int i = 0; i < additionalHeaderSize; i++) {
		printf("%c", additionalHeaderData[i]);
	}
	putchar('\n');


	// BRICKS

	printf("contextType:\t%u\n", contextType);

	printf("firstBrick->context:\t%u\t", firstBrick->context);
	printBits(sizeof(byte_t), &(firstBrick->context));

	printf("firstBrick->mask:\t%u\t", firstBrick->mask);
	printBits(sizeof(byte_t), &(firstBrick->mask));

	printf("additionalBricksSize:\t%u\n", additionalBricksSize);

	printf("additionalBricks:\n");
	for (int i = 0; i < additionalBricksSize; i++) {

		printf("additionalBricks[%u]->context:\t%u\t", i, additionalBricks[i].context);
		printBits(sizeof(byte_t), &(additionalBricks[i].context));

		printf("additionalBricks[%u]->mask:\t%u\t", i, additionalBricks[i].mask);
		printBits(sizeof(byte_t), &(additionalBricks[i].mask));
	}
	putchar('\n');


	// DATA

	printf("dataType:\t%u\n", dataType);

	printf("strlen(data): %lu\n", strlen(data));
	printf("data:\n\"%s\"\n", data);

	printf("additionalDataSize:\t%u\n", additionalDataSize);
	printf("additionalData:\n\"%s\"\n", additionalData);

}

void printBits(size_t const size, void const * const ptr) {
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
		}
	}
	puts("");
}



