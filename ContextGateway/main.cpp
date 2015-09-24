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

	stop(contextNetwork);

	std::cout << "Interrupt signal " << signum << " received" << std::endl;
}

//inline void printUuid(uuid_t uuid) {
//
//	std::cout << "uuid:\t" << std::flush;
//
//	size_t i;
//	for (i = 0; i < sizeof(uuid)*2; i++) {
//		printf("%02x", *(uuid + i));
//		std::flush(std::cout);
//	}
//
//	std::cout << std::endl;
//}
//
//inline std::string getUuidString(uuid_t uuid) {
//
//	std::string out;
//
//	char buffer [sizeof(uuid)*2];
//
//	size_t i;
//	for (i = 0; i < sizeof(uuid)*2; i++) {
//		sprintf(buffer, "%02x", *(uuid + i));
//		std::string tmp(buffer);
//		out += tmp;
//	}
//
//	return out;
//}

/*
 * Main method to register signal handling and start contextNetwork daemon
 */
int main(void) {
	std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;


//	uuid_t uuid;
//	uuid_generate(uuid);
//
//	printf("++++++++++uuid:\t");
//	size_t i;
//	for (i = 0; i < sizeof(uuid); i++) {
//		printf("%02x", uuid[i]);
//	}
//	printf("++++++++++");
//	putchar('\n');
//
//	std::string uuid_str;
//
//	printUuid(uuid);
//
//	uuid_str = getUuidString(uuid);
//
//	std::cout << uuid_str << std::endl;

	signal(SIGHUP, exitMainLoop);
	signal(SIGINT, exitMainLoop);
	signal(SIGTERM, exitMainLoop);

	contextNetwork = new ContextNetwork();
	contextNetwork->run();

	return EXIT_SUCCESS;

}
