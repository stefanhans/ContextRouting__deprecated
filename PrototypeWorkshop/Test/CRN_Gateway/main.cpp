#include <csignal>

#include "network.h"

#include <uuid/uuid.h>

/*
 * Functions etc. to stop main loop of running contextNetwork daemon
 */

ContextNetwork *contextNetwork;

void stop(ContextNetwork *contextNetwork) {
	contextNetwork->stop();
}


void exitMainLoop(int signum) {
	std::cout << "Interrupt signal " << signum << " received" << std::endl;

	stop(contextNetwork);
}

/*
 * Main method to register signal handling and start contextNetwork daemon
 */
int main(void) {
	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	signal(SIGHUP, exitMainLoop);
	signal(SIGINT, exitMainLoop);
	signal(SIGTERM, exitMainLoop);

	contextNetwork = new ContextNetwork();
	contextNetwork->run();

	return EXIT_SUCCESS;

}
