/*
 * main.cpp
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */


#include "network.h"

using namespace std;

int main(void) {

	ContextNetwork *contextNetwork;
	contextNetwork = new ContextNetwork();

	contextNetwork->run();

	return EXIT_SUCCESS;

}
