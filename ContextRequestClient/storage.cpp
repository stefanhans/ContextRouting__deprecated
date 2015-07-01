/*
 * storage.cpp
 *
 *  Created on: May 21, 2015
 *      Author: stefan
 */

#include "storage.h"


/**
 * ContextBrick
 */

ContextBrick::ContextBrick() {
	this->context = 0;
	this->mask    = 0;
}

ContextBrick::ContextBrick(byte context, byte mask) {

	this->context = context;
	this->mask    = mask;
}

/**
 * ContextData
 */

ContextData::ContextData() {

	this->command[0] = 0;
	this->command[1] = 0;

	this->datatype = 0;
	this->data[0] = '\0';

	this->contextMetatId = new ContextBrick();
}

int ContextData::getSizeOf() {

	return CONTEXT_DATA_SIZE;
}

/**
 * ContextArray
 */

ContextArray::ContextArray() {

	this->contextId = new ContextBrick();

}

int ContextArray::getSizeOf() {

	return 2 + (this->contextVector.size() * 2);
}

/**
 * ContextStruct
 */

ContextStruct::ContextStruct() {

	this->sourceAddress = NULL;

	uuid_t uuid;
	uuid_generate(uuid);

	this->channel = 0;

	uuid_copy(this->sourceUuid, uuid);

	this->contextData = new ContextData();
	this->contextArray = new ContextArray();
}

int ContextStruct::getSizeOf() {

	int size = 0;
	printf("%u\t: start\n", size);

	//channel
	size += 1;

	size += sizeof(uuid_t);
	printf("%u\t: uuid_t\t: %lu\n", size, sizeof(uuid_t));


	size += this->contextData->getSizeOf();
	printf("%u\t: contextData\t: %u\n", size, this->contextData->getSizeOf());


	size += this->contextArray->getSizeOf();
	printf("%u\t: contextArray\t: %u\n", size, this->contextArray->getSizeOf());

	return size;
}

int ContextStorage::requestContextStruct(ContextStruct *contextStruct) {

	if(contextStruct->contextData->command[0] == CMD_OFFER) {
		return this->handleOffer(contextStruct);
	}

	if(contextStruct->contextData->command[0] == CMD_REQUEST) {
		return this->handleRequest(contextStruct);
	}
	return -1;
}

int ContextStorage::storeContextStruct(ContextStruct *contextStruct) {

	if(contextStruct->contextData->command[0] == CMD_OFFER) {


	    int rc;	/* contain mutex lock/unlock results */

	    /* lock the mutex, to assure exclusive access to 'a' and 'b'. */
	    rc = pthread_mutex_lock(&a_mutex);

	    /* an error has occurred */
	    if (rc) {
	        perror("pthread_mutex_lock");
	        pthread_exit(NULL);
	    }



		this->contextIds[contextStruct->contextArray->contextId->context].push_back(contextStruct);



	    /* unlock mutex */
	    rc = pthread_mutex_unlock(&a_mutex);

	    if (rc) {
	        perror("pthread_mutex_unlock");
	        pthread_exit(NULL);
	    }


	}

	return 0;
}

int ContextStorage::handleOffer(ContextStruct *contextStruct) {

	this->contextIds[contextStruct->contextArray->contextId->context].push_back(contextStruct);

	return 0;
}

int ContextStorage::handleRequest(ContextStruct *contextStruct) {

	int match_cnt = 0;
	if(this->contextIds[contextStruct->contextArray->contextId->context].size() == 0) {
		return 0;
	}

	for (std::vector<ContextStruct*>::iterator iter = this->contextIds[contextStruct->contextArray->contextId->context].begin();
			iter != this->contextIds[contextStruct->contextArray->contextId->context].end(); ++iter) {


		if(array_match((*iter)->contextArray, contextStruct->contextArray)) {

			cout << "array_match: true" << endl;

			printContextStruct((*iter));

			match_cnt++;
		} else {
			cout << "array_match: false" << endl;
		}
	}

	return match_cnt;
}

bool ContextStorage::atomic_match(ContextBrick *offer, ContextBrick *request) {

	byte notEqual = offer->context ^ request->context;
	if (notEqual == 0) {
		return true;
	}

	byte offer_relevant = ~notEqual | offer->mask;
	byte not_offer_relevant = ~offer_relevant;
	if (not_offer_relevant != 0) {
		return false;
	}

	byte request_relevant = ~notEqual | request->mask;
	byte not_request_relevant = ~request_relevant;
	if (not_request_relevant != 0) {
		return false;
	}

	return true;
}

bool ContextStorage::array_match(ContextArray *offer, ContextArray *request) {

	if (!atomic_match(offer->contextId, request->contextId)) {
		return false;
	}
	if (offer->contextVector.size() != request->contextVector.size()) {
		return false;
	}

	unsigned int i;
	for (i = 0; i < offer->contextVector.size(); i++) {
		if ( ! atomic_match(offer->contextVector[i], request->contextVector[i])) {
			return false;
		}
	}

	return true;
}

int ContextStorage::serializeStruct(ContextStruct *contextStruct, char *buffer) {

	unsigned int b;

	// uuid
	for (b=0; b<16; b++) {
		buffer[b] = contextStruct->sourceUuid[b];
	}

	buffer[b] = contextStruct->channel;
	b++;

	buffer[b] = contextStruct->contextData->command[0];
	b++;
	buffer[b] = contextStruct->contextData->command[1];
	b++;
	buffer[b] = contextStruct->contextData->datatype;
	b++;

	// data
	int d;
	for (d=0; d<140; d++, b++) {
		buffer[b] = contextStruct->contextData->data[d];
	}

	buffer[b] = contextStruct->contextData->contextMetatId->context;
	b++;
	buffer[b] = contextStruct->contextData->contextMetatId->mask;
	b++;

	buffer[b] = contextStruct->contextArray->contextId->context;
	b++;
	buffer[b] = contextStruct->contextArray->contextId->mask;
	b++;

	// contextVector
	for (std::vector<ContextBrick*>::iterator iter = contextStruct->contextArray->contextVector.begin();
			iter != contextStruct->contextArray->contextVector.end(); ++iter) {

		buffer[b] = (*iter)->context;
		b++;
		buffer[b] = (*iter)->mask;
		b++;
	}
	return 0;
}

int ContextStorage::deserializeStruct(char *buffer, int bytes, ContextStruct *contextStruct) {

	memcpy(contextStruct->sourceUuid, buffer, 16);

	contextStruct->channel = buffer[16];

	contextStruct->contextData->command[0] = buffer[17];
	contextStruct->contextData->command[1] = buffer[18];

	contextStruct->contextData->datatype = buffer[19];

	int i, j;
	for (i=0, j=20; j<160; i++, j++) {
		contextStruct->contextData->data[i] = buffer[j];
	}

	contextStruct->contextData->contextMetatId->context = buffer[160];
	contextStruct->contextData->contextMetatId->mask    = buffer[161];

	contextStruct->contextArray->contextId->context = buffer[162];
	contextStruct->contextArray->contextId->mask    = buffer[163];

	contextStruct->contextArray->contextVector.clear();
	int k;
	for (k=164;k<bytes; k+=2) {
		contextStruct->contextArray->contextVector.push_back(new ContextBrick(buffer[k], buffer[k+1]));
	}
	return 0;
}


void initializeOffer(ContextStruct *context) {

	ContextData *offer_data = new ContextData();
	ContextArray *offer_arr = new ContextArray();

	offer_data->command[0] = CMD_OFFER;
	offer_data->command[1] = CMD_DEFAULT;

	offer_data->datatype = DT_TEXT;
	strcpy(offer_data->data, "this is a test message!");

	offer_data->contextMetatId = new ContextBrick();

	offer_arr->contextId = new ContextBrick(CID_TEST, CID_DEFAULT);

	offer_arr->contextVector.push_back(new ContextBrick(0b000001, 0b001111));
	offer_arr->contextVector.push_back(new ContextBrick(0b000011, 0b000111));
	offer_arr->contextVector.push_back(new ContextBrick(0b000111, 0b000011));
	offer_arr->contextVector.push_back(new ContextBrick(0b001111, 0b000001));
	offer_arr->contextVector.push_back(new ContextBrick(0b011111, 0b000000));

	context->channel = CMD_OFFER;
	context->contextData  = offer_data;
	context->contextArray = offer_arr;
}

void initializeRequest(ContextStruct *context) {

	ContextData *offer_data = new ContextData();
	ContextArray *offer_arr = new ContextArray();

	offer_data->command[0] = CMD_REQUEST;
	offer_data->command[1] = CMD_DEFAULT;

	offer_data->datatype = DT_DEFAULT;
	strcpy(offer_data->data, "this is a test message!");

	offer_data->contextMetatId = new ContextBrick();

	offer_arr->contextId = new ContextBrick(CID_TEST, CID_DEFAULT);

	offer_arr->contextVector.push_back(new ContextBrick(0b000001, 0b001111));
	offer_arr->contextVector.push_back(new ContextBrick(0b000011, 0b000111));
	offer_arr->contextVector.push_back(new ContextBrick(0b000111, 0b000011));
	offer_arr->contextVector.push_back(new ContextBrick(0b001111, 0b000001));
	offer_arr->contextVector.push_back(new ContextBrick(0b011111, 0b000000));

	context->channel = CMD_REQUEST;
	context->contextData  = offer_data;
	context->contextArray = offer_arr;
}

void printContextData(ContextStruct *context) {

	printf("context->contextData->command[0]\t: %u\n", context->contextData->command[0]);
	printf("context->contextData->command[1]\t: %u\n", context->contextData->command[1]);

	printf("context->contextData->datatype\t\t: %u\n", context->contextData->datatype);
	printf("context->contextData->data    \t\t: '%s'\n", context->contextData->data);

	printf("context->contextData->contextMetatId->context\t: %u\t", context->contextData->contextMetatId->context);
	printBits(sizeof(byte), &(context->contextData->contextMetatId->context));
	printf("context->contextData->contextMetatId->mask   \t: \t");
	printBits(sizeof(byte), &(context->contextData->contextMetatId->mask));
}

void printContextArray(ContextStruct *context) {

	printf("context->contextArray->contextId->context\t: %u\t", context->contextArray->contextId->context);
	printBits(sizeof(byte), &(context->contextArray->contextId->context));
	printf("context->contextArray->contextId->mask   \t: \t");
	printBits(sizeof(byte), &(context->contextArray->contextId->mask));

	printf("context->contextArray->context_v.size()\t\t: %lu\n",
			context->contextArray->contextVector.size());

	size_t i = 0;

	for (std::vector<ContextBrick*>::iterator it = context->contextArray->contextVector.begin() ; it != context->contextArray->contextVector.end(); ++it) {
		printf("context->contextArray->context_v(%lu)->context\t: %u\t", i, (*it)->context);
		printBits(sizeof(byte),&(*it)->context);

		printf("context->contextArray->context_v(%lu)->mask\t: \t", i);
		printBits(sizeof(byte),&(*it)->mask);

		i++;
	}
}

void printContextStruct(ContextStruct *context) {

	printf("context->sourceUuid\t: ");
	size_t i;
	for (i = 0; i < sizeof(context->sourceUuid) - 1; i++) {
		printf("%02x", context->sourceUuid[i]);
	}
	putchar('\n');

	printContextData(context);
	printContextArray(context);
}

void printContextStorage(ContextStorage *storage) {

	int i, j, k;
	int empty, nonEmpty;

	empty = 0;
	nonEmpty = 0;

	for (i = 0; i < UCHAR_MAX; i++) {
		if (storage->contextIds[i].size() > 0) {

			k = 0;
			for (std::vector<ContextStruct*>::iterator iter = storage->contextIds[i].begin();
						iter != storage->contextIds[i].end(); ++iter) {


				printf("storage->contextIds[%u].at(%u)->sourceUuid\t\t\t\t: ", i, k);
				size_t l;
				for (l = 0; l < sizeof((*iter)->sourceUuid) - 1; l++) {
					printf("%02x", (*iter)->sourceUuid[l]);
				}
				putchar('\n');


				printf("storage->contextIds[%u].at(%u)->contextData->command[0]\t\t\t: %u\n", i, k, (*iter)->contextData->command[0]);
				printf("storage->contextIds[%u].at(%u)->contextData->command[1]\t\t\t: %u\n", i, k, (*iter)->contextData->command[1]);

				printf("storage->contextIds[%u].at(%u)->contextData->datatype\t\t\t: %u\n", i, k, (*iter)->contextData->datatype);
				printf("storage->contextIds[%u].at(%u)->contextData->data    \t\t\t: '%s'\n", i, k, (*iter)->contextData->data);

				printf("storage->contextIds[%u].at(%u)->contextData->contextMetatId->context\t: %u\t", i, k, (*iter)->contextData->contextMetatId->context);
				printBits(sizeof(byte), &((*iter)->contextData->contextMetatId->context));
				printf("storage->contextIds[%u].at(%u)->contextData->contextMetatId->mask   \t: \t", i, k);
				printBits(sizeof(byte), &((*iter)->contextData->contextMetatId->mask));


				j = 0;
				for (std::vector<ContextBrick*>::iterator it = (*iter)->contextArray->contextVector.begin();
						it != (*iter)->contextArray->contextVector.end(); ++it) {
					printf("storage->contextIds[%u].at(%u)->contextArray->contextVector[%u]->context\t: %u\t", i, k,  j, (*iter)->contextArray->contextVector[j]->context);
					printBits(sizeof(byte), &(*it)->context);

					printf("storage->contextIds[%u].at(%u)->contextArray->contextVector[%u]->mask\t: \t", i, k, j);
					printBits(sizeof(byte), &(*it)->mask);

					j++;
				}
				k++;
			}
			nonEmpty++;
		} else {
			empty++;
		}
	}
	printf("storage->contextIds summary: \t%u empty and %u non emtpy = %u\n", empty, nonEmpty, UCHAR_MAX);
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
