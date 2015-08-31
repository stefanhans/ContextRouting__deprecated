/*
 * corestorage.cpp
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */

#include "corestorage.h"

#include <stddef.h>  // defines NULL

CoreStorage* CoreStorage::m_pInstance = NULL;

CoreStorage* CoreStorage::getInstance() {

	if (!m_pInstance) { // Only allow one instance of class to be generated.

		m_pInstance = new CoreStorage;
	}

   return m_pInstance;
}




