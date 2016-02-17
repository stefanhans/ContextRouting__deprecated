/*
 * corepacket.h
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */

#ifndef SRC_COREPACKET_H_
#define SRC_COREPACKET_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "protocol.h"
#include "globals.h"
#include "abstractservice.h"

/**
 * ContextBrick
 */
class ContextBrick {

public:

	ContextBrick();
	~ContextBrick() {}

	ContextBrick(byte_t context, byte_t mask);

	bool hasMatch(ContextBrick *otherBrick);

	byte_t context;
	byte_t mask;
};



/**
 * @brief IpAddress
 *
 */
class IpAddress {

public:

	IpAddress(uuid_t addressId, struct sockaddr_in sockAddress);
	~IpAddress() {
//		delete [] addressId;
	}

	/**
	 * Getter/Setter for addressId
	 */
	uuid_t* getAddressId() {
		return &addressId;
	}
	void setAddressId(uuid_t* addressId) {
		memcpy(this->addressId, addressId, 16);
	}

	/**
	 * Getter/Setter for sockAddress
	 */
	sockaddr_in getSockAddress() {
		return sockAddress;
	}
	void setSockAddress(sockaddr_in sockAddress) {
		this->sockAddress = sockAddress;
	}


private:
	uuid_t addressId;
	struct sockaddr_in sockAddress;
};

/**
 * @brief ContextPacket
 *
 */
class ContextPacket {

public:

	ContextPacket();
	~ContextPacket() {
		delete firstBrick;
		deleteService();
	}

	ContextPacket(IpAddress *ipAddress);

	/**
	 * ############################################################################################
	 *
	 * HEADER
	 *
	 * ############################################################################################
	 */

	/**
	 * Getter/Setter for service
	 */
	byte_t getService() {
		return service;
	}
	void setService(byte_t service) {
		this->service = service;
	}

	/**
	 * Getter/Setter for version
	 */
	byte_t getVersion() {
		return version;
	}
	void setVersion(byte_t version) {
		this->version = version;
	}

	/**
	 * Getter/Setter for channel
	 */
	byte_t getChannel() {
		return channel;
	}
	void setChannel(byte_t channel) {
		this->channel = channel;
	}

	/**
	 * Getter/Setter for optionalHeaderSize
	 */
	byte_t getOptionalHeaderSize() {
		return additionalHeaderSize;
	}
	void setOptionalHeaderSize(byte_t optionalHeaderSize) {
		this->additionalHeaderSize = optionalHeaderSize;
	}

	/**
	 * Getter/Setter for uuid
	 */
	uuid_t* getUuid() {
		return &uuid;
	}
	void setUuid(uuid_t* uuid) {
		memcpy(this->uuid, uuid, 16);
	}

	struct sockaddr_in getIp() {
		return sockAddress;
	}

	/**
	 * Getter/Setter for 32-bit binary network byte ordered IPv4 address
	 */
	in_addr_t getIpAddress() {
		return sockAddress.sin_addr.s_addr;
	}
	void setIpAddress(in_addr_t in_addr) {
		this->sockAddress.sin_addr.s_addr = in_addr;
	}

	/**
	 * Getter/Setter for 16-bit binary network byte ordered port number
	 */
	port_t getPortNumber() {
		return sockAddress.sin_port;
	}
	void setPortNumber(port_t portNumber) {
		this->sockAddress.sin_port = portNumber;
	}

	/**
	 * Getter/Setter for a simple time stamp
	 */
	const time_t* getTime() {
		return &timestamp;
	}
	void setTime(time_t timestamp) {
		this->timestamp = timestamp;
	}
	void setTime() {
		this->timestamp = time(NULL);
	}

	/**
	 * Getter/Setter for additionalHeaderData array
	 */
	byte_t* getAdditionalHeaderData() {
		return additionalHeaderData;
	}
	int setAdditionalHeaderData(char* additionalHeaderData) {
		if(HEADER_ADDITIONAL_SIZE < strlen(additionalHeaderData)) {
			perror("setAdditionalHeaderData(char*) failed: size of additional header data is to big");
			return -1;
		}
		memcpy(this->additionalHeaderData, additionalHeaderData, strlen(additionalHeaderData));
		return 0;
	}

	/**
	 * Append additional data
	 */
//	int appendAdditonalHeaderData(byte_t headerData) {
//		if(HEADER_ADDITIONAL_SIZE <= strlen(additionalHeaderData))  {
//			perror("appendAdditonalHeaderData(byte_t) failed: additionalHeaderData is full");
//			return -1;
//		}
//		this->additionalHeaderData[strlen(this->additionalHeaderData)] = headerData;
//		return 0;
//	}
//	int appendAdditonalHeaderData(char* additionalHeaderData) {
//		if(HEADER_ADDITIONAL_SIZE < (strlen(this->additionalHeaderData) + strlen(additionalHeaderData)))  {
//			perror("appendAdditonalHeaderData(char*) failed: additionalHeaderData is to full");
//			return -1;
//		}
//		memcpy(&(this->additionalHeaderData)[strlen(this->additionalHeaderData)], additionalHeaderData, strlen(additionalHeaderData));
//		return 0;
//	}
//
//	/**
//	 * Get size of addiitionalHeaderData
//	 */
//	int getAdditonalHeaderDataSize() {
//		return strlen(this->additionalHeaderData);
//	}

	/**
	 * Clear addiitionalHeaderData
	 */
	void clearAdditonalHeaderDataSize() {
		memset(&additionalHeaderData, 0, HEADER_ADDITIONAL_SIZE);
	}

	/**
	 * ############################################################################################
	 *
	 * BRICKS
	 *
	 * ############################################################################################
	 */

	/**
	 * Getter/Setter for type
	 */
	byte_t getContextType() {
		return contextType;
	}
	void setContextType(byte_t contextType) {
		this->contextType = contextType;
	}

	/**
	 * Getter/Setter for firstBrick
	 */
	ContextBrick* getFirstBrick() {
		return firstBrick;
	}
	void setFirstBrick(ContextBrick *contextBrick) {
		this->firstBrick = contextBrick;
	}

	/**
	 * Getter/Setter for optionalBrickListSize
	 */
	byte_t getOptionalBrickListSize() {
		return additionalBricksSize;
	}
	void setOptionalBrickListSize(byte_t optionalBrickListSize) {
		this->additionalBricksSize = optionalBrickListSize;
	}

	/**
	 * ############################################################################################
	 *
	 * DATA
	 *
	 * ############################################################################################
	 */

	/**
	 * Getter/Setter for dataType
	 */
	byte_t getType() {
		return dataType;
	}
	void setDataType(byte_t dataType) {
		this->dataType = dataType;
	}

	/**
	 * Getter/Setter for optionalDataSize
	 */
	byte_t getOptionalDataSize() {
		return additionalDataSize;
	}
	void setOptionalDataSize(byte_t optionalDataSize) {
		this->additionalDataSize = optionalDataSize;
	}

	/**
	 * Getter/Setter for additionalData
	 */
	byte_t* getAdditionalData() {
		return additionalData;
	}
	int setAdditionalData(char* additionalData) {
		if(DATA_ADDITIONAL_SIZE < strlen(additionalData)) {
			perror("setAdditionalData(char*) failed: size of additionalData is to big");
			return -1;
		}
		memcpy(this->additionalData, additionalData, strlen(additionalData));
		return 0;
	}

	/**
	 * ############################################################################################
	 *
	 * OTHER
	 *
	 * ############################################################################################
	 */

	/**
	 * Get needed size in bytes
	 */
	int getSize();

	/**
	 * Serialize outgoing data
	 */
	int serialize(char *buffer);

	/**
	 * Deserialize incoming data
	 */
	int deserialize(char *buffer);

	/**
	 * ############################################################################################
	 *
	 * SERVICE
	 *
	 * ############################################################################################
	 */

	/**
	 * Process received UDP packet by service object according to packet's service
	 */
	int processUDP(int socket, struct sockaddr *addr);

	/**
	 * Process received TCP packet by service object according to packet's service
	 */
	int processTCP();

	int deleteService();

	/**
	 * Print data for debugging
	 */
	void printPacket(std::string line_start="");

	/**
	 * Array of 255 context bricks
	 */
	ContextBrick additionalBricks[BRICKS_ADDITIONAL_SIZE];

private:

	/**
	 * Service Group Request
	 */
	byte_t sg_request;

	/**
	 * Service Group Profile
	 */
	byte_t sg_profile;

	/**
	 * What has to be done respectively to be transfered?
	 */
	byte_t service;

	/**
	 * For future use
	 */
	byte_t version;

	/**
	 * What kind of content to be handled?
	 */
	byte_t channel;

	/**
	 * UUID to distinctly identify each context packet
	 */
	uuid_t uuid;

	/**
	 * Struct of socket's address
	 */
	struct sockaddr_in sockAddress;

	/**
	 * Time stamp
	 */
	time_t timestamp;

	/**
	 * Type of additional header data
	 */
	byte_t additionalHeaderType;

	/**
	 * Number of additional header data in bytes
	 */
	byte_t additionalHeaderSize;

	/**
	 * Array of 255 bytes for additional data
	 */
	byte_t additionalHeaderData[HEADER_ADDITIONAL_SIZE];

	/**
	 * What type of context is described
	 */
	byte_t contextType;

	/**
	 * Mandatory first context brick
	 */
	ContextBrick *firstBrick;

	/**
	 * Number of additional bricks in bytes
	 */
	byte_t additionalBricksSize;

	/**
	 * Array of 255 context bricks
	 */
//	ContextBrick additionalBricks[BRICKS_ADDITIONAL_SIZE]; shift to public

	/**
	 * What type of data is described
	 */
	byte_t dataType;

	/**
	 * Number of additional data in bytes
	 */
	byte_t additionalDataSize;

	/**
	 * Array of 255 bytes for additional data
	 */
	byte_t additionalData[DATA_ADDITIONAL_SIZE];
};

#endif /* SRC_COREPACKET_H_ */
