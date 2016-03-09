#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#define DEBUG 0
#define THREAD_DEBUG 0
#define PRINT_PACKET_DEBUG 0
#define PRINT_PACKETS_DEBUG 0

#define LINE_SEPARATOR "----------------------------------------------------------------------"

#define MAXMSG 1064

#define LISTEN_BACKLOG 128

/**
 * type definitions
 */
typedef unsigned char byte_t;
typedef unsigned short int port_t;

/**
 * Client Service Methods
 */
inline bool hasClientService(byte_t sg_byte) {
	return sg_byte % 2;
}
inline byte_t setClientService(byte_t sg_byte, bool checked) {


	return sg_byte;
}

/*
 * Gateway Service Methods
 */
inline bool hasGatewayService(byte_t sg_byte) {
	return sg_byte>>1 % 2;
}
inline byte_t setGatewayService(byte_t sg_byte, bool checked) {

	return sg_byte;
}

/*
 * <new service group's service> Service Methods
 */
// Add declaration lines with <new> service group's service methods here


/**
 * Extract major version from byte_t version
 */
inline int getMajorVersion(byte_t version) {

	return version >> 4;
}
/**
 * Extract minor version from byte_t version
 */
inline int getMinorVersion(byte_t version) {

	return version % 16;
}


inline void printUuid(uuid_t uuid, std::string header="") {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "] " << std::ends;

	std::cout << header << std::flush;

	size_t i;
	for (i = 0; i < 16; i++) {
		printf("%02x", *(uuid + i));
		std::flush(std::cout);
	}

	std::cout << std::endl;
}

inline std::string getUuidString(uuid_t uuid) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	std::string out;

	char buffer [16];

	size_t i;
	for (i = 0; i < 16; i++) {
		sprintf(buffer, "%02x", *(uuid + i));
		std::string tmp(buffer);
		out += tmp;
	}

	return out;
}

inline void printBits(size_t const size, void const * const ptr) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			printf("%u", byte);
			std::flush(std::cout);
		}
	}
	std::cout << std::endl;
}

inline std::string getBitsString(size_t const size, void const * const ptr) {
//	if (DEBUG) std::cout << __FILE__ << "(" << __LINE__ << ")"  << "[" << __FUNCTION__<< "]" << std::endl;

	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	std::string out_str;
	char str_buffer[1];

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = b[i] & (1 << j);
			byte >>= j;
			sprintf(str_buffer, "%u", byte);
			out_str.append(str_buffer);
		}
	}
	return out_str;
}


#endif /* SRC_GLOBALS_H_ */
