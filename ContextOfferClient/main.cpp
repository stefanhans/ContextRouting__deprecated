/*
 * main.cpp
 *
 *  Created on: May 19, 2015
 *      Author: stefan
 */

#include "net.h"
#include "storage.h"

int main() {

	cout << endl;
	cout << "Create new Net:"	<< endl;
	cout << "----------------------------------------------------------------------" << endl;
	Net *net = new Net();
	net->initialize();

	cout << endl;
	cout << "Prompt"	<< endl;
	cout << "----------------------------------------------------------------------" << endl;

	ContextStruct *offer = new ContextStruct();
	initializeOffer(offer);
	net->sendOffer(offer);

	return 0;
}
