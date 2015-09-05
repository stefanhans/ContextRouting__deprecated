/*
 * corestorage.cpp
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */

#include "corestorage.h"

//bool PacketStorage::atomic_match(ContextPacket *offer, ContextPacket *request) {
//
//	return true;
//}

#include <stddef.h>  // defines NULL

// Global static pointer used to ensure a single instance of the class.
Logger* Logger::m_pInstance = NULL;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/

Logger* Logger::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Logger;

   return m_pInstance;
}

bool Logger::openLogFile(std::string _logFile)
{
   printf("HELLO: \n");
}

