#include <csignal>

#include "network.h"

/*
 * Functions etc. to stop main loop of running contextNetwork daemon
 */

ContextNetwork *contextNetwork;

void stop(ContextNetwork *contextNetwork) {
	contextNetwork->stop();
}


void exitMainLoop(int signum) {

	stop(contextNetwork);

	std::cout << "Interrupt signal " << signum << " received" << std::endl;
}

/*
 * Main method to register signal handling and start contextNetwork daemon
 */
int main(void) {

	signal(SIGHUP, exitMainLoop);
	signal(SIGINT, exitMainLoop);
	signal(SIGTERM, exitMainLoop);

	contextNetwork = new ContextNetwork();
	contextNetwork->run();

	return EXIT_SUCCESS;

}
