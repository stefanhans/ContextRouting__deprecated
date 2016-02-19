#ifndef CRN_H
#define CRN_H

#include "crn_global.h"

#include <QObject>

class CRNSHARED_EXPORT CRN
{

public:

    int ping(QStringList command);
};

#endif // CRN_H
