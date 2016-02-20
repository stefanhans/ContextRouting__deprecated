#ifndef CI_H
#define CI_H

#include "ci_global.h"

#include <QObject>


/**
 * type definitions
 */
typedef unsigned char byte_t;

/**
 * enumeration definitions
 */
enum direct_modus_e { DM_INTEGER=0, DM_HEX=1, DM_CHAR=2 };


class CISHARED_EXPORT CI : public QObject
{
    Q_OBJECT

public:
    CI();

    /**
     * setInMode for direct interpretation
     */
    void setInMode(direct_modus_e modus_e) {
        iMode = modus_e;
    }

    /**
     * getInMode of direct interpretation
     */
    byte_t getInMode() {
        return iMode;
    }

    /**
     * setOutMode for direct interpretation
     */
    void setOutMode(direct_modus_e modus_e) {
        oMode = modus_e;
    }

    /**
     * getOutMode of direct interpretation
     */
    byte_t getOutMode() {
        return oMode;
    }

private:
    byte_t oMode, iMode;
};

#endif // CI_H
