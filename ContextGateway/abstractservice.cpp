/*
 *
 * Extension i.e. a new service needs the following:
 *
 * - create header and source file like the existing extensions e.g. OfferService
 *
 * - edit this file i.e. add #include directive and new line with service constructor call
 *
 */

#include "abstractservice.h"

#include "offerservice.h"
#include "requestservice.h"

ContextService* ContextService::create(byte_t service) {

	/*
	 * Offer service constructor call
	 */
	if(service == SERVICE_OFFER) return new OfferService();

	/*
	 * Request service constructor call
	 */
	if(service == SERVICE_REQUEST) return new RequestService();

	/*
	 * <new> service constructor call
	 */
	// Add line with <new> service constructor call here

	return NULL;
}

