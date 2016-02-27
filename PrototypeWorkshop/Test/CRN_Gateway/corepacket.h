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
		delete rootCIC;
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
	 * Getter/Setter for request
	 */
	byte_t getRequest() {
		return request;
	}
	void setRequest(byte_t request) {
		this->request = request;
	}

	/**
	 * Getter/Setter for profile
	 */
	byte_t getProfile() {
		return profile;
	}
	void setProfile(byte_t profile) {
		this->profile = profile;
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
	 * Getter/Setter for uuid
	 */
	uuid_t* getUuid() {
		return &uuid;
	}
	void setUuid(uuid_t* uuid) {
		memcpy(this->uuid, uuid, 16);
	}
	void setUuid() {
		memset(this->uuid, 0, 16);
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
	 * Getter/Setter for headerData array
	 */
	byte_t getHeaderType() {
		return headerType;
	}
	void setHeaderType(byte_t headerType) {
		this->headerType = headerType;
	}

	byte_t getHeaderSize() {
		return headerSize;
	}
	void setHeaderSize(byte_t headerSize) {
		this->headerSize = headerSize;
	}

	byte_t* getHeaderData() {
		return headerData;
	}
	int setHeaderData(char* headerData) {
		if(HEADER_ADDITIONAL_SIZE < strlen(headerData)) {
			perror("setHeaderData(char*) failed: size of additional header data is to big");
			return -1;
		}
		memcpy(this->headerData, headerData, strlen(headerData));
		return 0;
	}

	/**
	 * Clear addiitionalHeaderData
	 */
	void clearAdditonalHeaderDataSize() {
		memset(&headerData, 0, HEADER_ADDITIONAL_SIZE);
	}

	/**
	 * ############################################################################################
	 *
	 * BRICKS
	 *
	 * ############################################################################################
	 */

	/**
	 * Getter/Setter for Contextinformation type
	 */
	byte_t getCiType() {
		return ciType;
	}
	void setCiType(byte_t ciType) {
		this->ciType = ciType;
	}

	/**
	 * Getter/Setter for root-CIC
	 */
	ContextBrick* getRootCIC() {
		return rootCIC;
	}
	void setRootCIC(ContextBrick *contextBrick) {
		this->rootCIC = contextBrick;
	}

	/**
	 * Getter/Setter for Contextinformation size
	 */
	byte_t getCiSize() {
		return ciSize;
	}
	void setCiSize(byte_t ciSize) {
		this->ciSize = ciSize;
	}

	/**
	 * ############################################################################################
	 *
	 * DATA
	 *
	 * ############################################################################################
	 */

	/**
	 * Getter/Setter for application data type
	 */
	byte_t getAppDataType() {
		return appDataType;
	}
	void setAppDataType(byte_t dataType) {
		this->appDataType = dataType;
	}

	/**
	 * Getter/Setter for application data size
	 */
	byte_t getAppDataSize() {
		return appDataSize;
	}
	void setAppDataSize(byte_t optionalDataSize) {
		this->appDataSize = optionalDataSize;
	}

	/**
	 * Getter/Setter for application data
	 */
	byte_t* getAppData() {
		return appData;
	}
	int setAppData(char* appData) {
		if(DATA_ADDITIONAL_SIZE < strlen(appData)) {
			perror("setAppData(char*) failed: size of application data is to big");
			return -1;
		}
		memcpy(this->appData, appData, strlen(appData));
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
	size_t getSize();

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
	int processUDP(int socket, struct sockaddr *addr, int UDP_bytes_received);

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
	ContextBrick ciCICBricks[BRICKS_ADDITIONAL_SIZE];

private:

	/**
	 * Service Group Request
	 */
	byte_t request;

	/**
	 * Service Group Profile
	 */
	byte_t profile;

	/**
	 * Currently 1 (0.1)
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
	byte_t headerType;

	/**
	 * Number of additional header data in bytes
	 */
	byte_t headerSize;

	/**
	 * Array of 255 bytes for additional data
	 */
	byte_t headerData[HEADER_ADDITIONAL_SIZE];

	/**
	 * What type of context is described
	 */
	byte_t ciType;

	/**
	 * Mandatory first context brick
	 */
	ContextBrick *rootCIC;

	/**
	 * Number of additional bricks in bytes
	 */
	byte_t ciSize;

	/**
	 * Array of 255 context bricks
	 */
//	ContextBrick additionalBricks[BRICKS_ADDITIONAL_SIZE]; shift to public

	/**
	 * What type of data is described
	 */
	byte_t appDataType;

	/**
	 * Number of additional data in bytes
	 */
	byte_t appDataSize;

	/**
	 * Array of 255 bytes for additional data
	 */
	byte_t appData[DATA_ADDITIONAL_SIZE];
};

#endif /* SRC_COREPACKET_H_ */
