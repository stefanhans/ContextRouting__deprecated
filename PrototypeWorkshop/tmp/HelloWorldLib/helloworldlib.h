#ifndef HELLOWORLDLIB_H
#define HELLOWORLDLIB_H

#include "helloworldlib_global.h"

#include <QString>

class HELLOWORLDLIBSHARED_EXPORT HelloWorldLib
{

public:
    HelloWorldLib();

    QString sayHello() {
        return QString("Hello World");
    }
};

#endif // HELLOWORLDLIB_H
