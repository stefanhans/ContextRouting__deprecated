/*
 * corestorage.h
 *
 *  Created on: Aug 22, 2015
 *      Author: stefan
 */

#ifndef SRC_CORESTORAGE_H_
#define SRC_CORESTORAGE_H_

class CoreStorage {

public:

	static CoreStorage* getInstance();


private:

	CoreStorage(){};
	CoreStorage(CoreStorage const&){};
	CoreStorage& operator=(CoreStorage const&){};

	static CoreStorage* m_pInstance;
};

#endif /* SRC_CORESTORAGE_H_ */
