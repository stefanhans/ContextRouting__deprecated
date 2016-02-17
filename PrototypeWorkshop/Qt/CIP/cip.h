#ifndef CIP_H
#define CIP_H

#include "cip_global.h"

#include <QByteArray>
#include <QString>
#include <QUuid>
#include <QDateTime>

#include <arpa/inet.h>


/**
 * type definitions
 */
typedef unsigned char byte_t;

class CIPSHARED_EXPORT CIP
{

public:
    CIP();

    QByteArray touch();
    QString cat(QByteArray byteArray);
};

#endif // CIP_H
