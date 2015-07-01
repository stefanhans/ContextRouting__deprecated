/*
 * storage.h
 *
 *  Created on: May 28, 2015
 *      Author: stefan
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uuid/uuid.h>
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

#define CONTEXT_DATA_SIZE 145

using namespace std;

/**
 * type definitions
 */
typedef unsigned char byte;

/**
 * enumeration definitions
 */
enum Command { CMD_DEFAULT=0, CMD_OFFER=1, CMD_REQUEST=8, CMD_TEST=UCHAR_MAX-1 };
enum Datatype { DT_DEFAULT=0, DT_TEXT=1, DT_URL=8, DT_TEST=UCHAR_MAX-1 };
enum ContextId { CID_DEFAULT=0, CID_TEST=UCHAR_MAX-1 };

/**
 * class definitions
 */
class ContextBrick {

public:

	ContextBrick();
	virtual ~ContextBrick() {}

	ContextBrick(byte context, byte mask);

	byte context;
	byte mask;
};

class OfferAdress {

public:

	uuid_t addressId;
	struct sockaddr_in offerAddress;

public:

	OfferAdress(uuid_t addressId, struct sockaddr_in offerAddress);
	virtual ~OfferAdress() {}
};

class ContextData {

public:
	byte command[2];
	byte datatype;
	char data[140];

	ContextBrick *contextMetatId;

	ContextData();
	virtual ~ContextData() {}

	int getSizeOf();
};

class ContextArray {

public:
	ContextBrick *contextId;
	vector<ContextBrick*> contextVector;

	ContextArray();
	virtual ~ContextArray() {}

	int getSizeOf();
};

class ContextStruct {

public:
	byte channel;
	uuid_t sourceUuid;
	ContextData *contextData;
	ContextArray *contextArray;
	struct sockaddr_in *sourceAddress;

	ContextStruct();
	virtual ~ContextStruct() {}

	int getSizeOf();
};

class ContextStorage {

public:
	ContextStorage() {}
	virtual ~ContextStorage() {}

	vector<OfferAdress*> offerAddresses;

	/* global mutex for our program. assignment initializes it */
	pthread_mutex_t a_mutex = PTHREAD_MUTEX_INITIALIZER;

	vector<ContextStruct*> contextIds[UCHAR_MAX];

	// Check storage for matching offer
	int requestContextStruct(ContextStruct *contextStruct);
	int storeContextStruct(ContextStruct *contextStruct);

	int deserializeStruct(char *buffer, int bytes, ContextStruct *contextStruct);
	int serializeStruct(ContextStruct *contextStruct, char *buffer);

	int insertContextStruct(ContextStruct *contextStruct);

	void* receiveOfferThread(void* data);
	bool array_match(ContextArray *offer, ContextArray *request);

private:

	bool atomic_match(ContextBrick *offer, ContextBrick *request);

	int handleOffer(ContextStruct *contextStruct);
	int handleRequest(ContextStruct *contextStruct);

};

/**
 * mock and print function definitions
 */
void initializeOffer(ContextStruct *context);
void initializeRequest(ContextStruct *context);

void printBits(size_t const size, void const * const ptr);

void printContextData(ContextStruct *context);
void printContextArray(ContextStruct *context);
void printContextStruct(ContextStruct *context);
void printContextStorage(ContextStorage *storage);
void printOfferAdresses(ContextStorage *storage);

#endif /* STORAGE_H_ */
