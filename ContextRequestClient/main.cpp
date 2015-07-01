/*
 * main.cpp
 *
 *  Created on: May 21, 2015
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

	ContextStruct *request = new ContextStruct();
	initializeRequest(request);
	net->sendRequest(request);

	return 0;
}
