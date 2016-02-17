#include "cip.h"


/*

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   request (1) |  profile (1)  |  version (1)  |  channel (1)  | |
   |                                                               | |
   |                            UUID (16)                          | |
   |                                                               | |
   |                                                               | fix
   |                          IP address (4)                       | |
   |            IP port (2)        |                               | |
   |                            time (8)                           | |
   |                               |   type (1)   |    size (1)    |---
   | ............................................................  | |
   | .............. additional data up to 255 bytes .............  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |         root-CIC (2)          |   size (1)    | fix
   | ............................................................  | |
   | .............. additional data up to 510 bytes .............  | dyn
   | .............. i.e. up to 255 CIC-Bricks  ..................  | |
   | ............................................................  | |
   +---------------------------------------------------------------+


   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |   size (1)    | ............................  | fix
   | ............................................................  | |
   | .......... additional data up to 255 bytes (size) ..........  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+

*/


CIP::CIP()
{
}

QByteArray CIP::touch() {

    QByteArray byteArray = QByteArray();
    int i = 0;

    // Header: request (1)
    byteArray[i++] = quint8(0);

    // Header: profile (1)
    byteArray[i++] = quint8(2);

    // Header: version (1)
    byteArray[i++] = quint8(4);

    // Header: channel (1)
    byteArray[i++] = quint8(8);

    // Header: UUID (16)
    QUuid uuid;
    uuid = QUuid::createUuid();
    QByteArray uuid_arr = uuid.toRfc4122();

    for(int j=0; j<16;j++) {
        byteArray[i++] = uuid_arr.at(j);
    }

    // Header: Empty IP address (4) and port number (2)
    for(int j=0; j<6;j++) {
        byteArray[i++] = quint8(0);
    }

    // Header: time (4)
    quint64 unixTime = QDateTime::currentDateTime().toTime_t();
    for(int j=0; j<8; j++) {

        byteArray[i++] = unixTime%256;
        unixTime = unixTime >> 8;
    }

    // Header: type (1)
    byteArray[i++] = quint8(16);

    // Header: size (1)
    byteArray[i++] = quint8(32);

    // Contextinformation: type (1)
    byteArray[i++] = quint8(64);

    // Contextinformation: root-CIC (2)
    byteArray[i++] = quint8(1);
    byteArray[i++] = quint8(3);

    // Contextinformation: size (1)
    byteArray[i++] = quint8(7);

    // Application: type (1)
    byteArray[i++] = quint8(16);

    // Application: size (1)
    byteArray[i++] = quint8(32);


    return byteArray;
}


QString CIP::cat(QByteArray byteArray) {

    QString out;
    QByteArray header;
    int i = 0;

    quint8 oneByte;

    // Header: request
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: request: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Header: profile
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: profile: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Header: version
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: version: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Header: channel
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: channel: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Header: UUID
    QByteArray uuid = byteArray.mid(i, 16);
    i += 16;

    QString uuidStr;
    quint8 byte;
    for(QByteArray::iterator it = uuid.begin(); it != uuid.end(); it++){
        byte = (*it);
        uuidStr.append(QString("%1").arg(byte, 0, 16));
    };
    out += QString("Header: UID (C): %1\n").arg(uuidStr);

    QUuid quuid = QUuid::fromRfc4122(uuid);
    out += QString("Header: UID (Qt): %1\n").arg(quuid.toString());


    // Header: IP Address (4)
    QByteArray ipAddress = byteArray.mid(i, 4);
    i += 4;
    in_addr ip;
    memcpy(&ip, ipAddress, 4);
    out += QString("Header: IP Address: %1\n").arg(inet_ntoa(ip));

    // Header: IP port (2)
    QByteArray ipPort = byteArray.mid(i, 2);
    i += 2;
    quint16 portNum;
    memcpy(&portNum, ipPort, 2);
    out += QString("Header: IP Port: %1\n").arg(ntohs(portNum));

    // Header: time (4)
    QByteArray time_arr = byteArray.mid(i, 8);
    i += 8;
    quint64 unixTime;
    memcpy(&unixTime, time_arr, 8);

    QDateTime time;
    time.setTime_t(unixTime);
    out += QString("Header: time: %1\n").arg(time.toString());

    // Header: type (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: type: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Header: size (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Header: size: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Contextinformation: type (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Contextinformation: type: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Contextinformation: root-CIC (2)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Contextinformation: root-CIC: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Contextinformation: root-CIC: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Contextinformation: size (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Contextinformation: size: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Application: type (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Application: type: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    // Application: size (1)
    header = byteArray.mid(i++, 1);
    memcpy(&oneByte, header, 1);
    out += QString("Application: size: %1\n").arg(oneByte, 8, 2, QLatin1Char('0'));

    return out;
}

