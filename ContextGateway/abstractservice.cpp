/*
 * abstractservice.cpp
 *
 *  Created on: Sep 2, 2015
 *      Author: stefan
 */

#include "abstractservice.h"
#include "offerservice.h"

ContextService* ContextService::create(byte_t service) {
	if(service==1) return new OfferService();

	return NULL;
}

