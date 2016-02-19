#include "tcp_ping.h"

#include <QDebug>
#include <QTextStream>
#include <QTcpSocket>
#include <QUuid>
#include <QObject>
#include <QTime>
#include <QtMath>

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064

/**
 * @brief tcp_ping
 * @param command "ping tcp rzv|max|rand|default"
 * @return
 */

int tcp_ping(QStringList command) {
    qDebug() << "tcp_ping(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 3 || command.at(0)!="ping" || command.at(1)!="tcp" ) {

        errorStream << "Error: tcp_ping(" << command.join(" ") << ") is no valid call (ping tcp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }

    QByteArray byteArray;

    /**
     * CIP for "rzv"
     */
    if(command.at(2)=="rzv") {
        qDebug() << "rzv" << endl;

        byteArray.append(QByteArray(42, '\0'));
     }

    /**
     * CIP for "default"
     */
    if(command.at(2)=="default") {
        qDebug() << "default" << endl;

        // Header: request (1), profile (1), version (1), channel (1)
        byteArray.append(QByteArray(4, '\0'));

        // Header: UUID (16)
        QUuid uuid;
        uuid = QUuid::createUuid();
        QByteArray uuid_arr = uuid.toRfc4122();

        for(int j=0; j<16;j++) {

            byteArray.append(uuid_arr.at(j));
        }

        // Header: Empty IP address (4), port number (2), time (8), type (1), size (1)
        byteArray.append(QByteArray(16, '\0'));

        // Contextinformation: type (1), root-CIC (2), size (1)
        byteArray.append(QByteArray(4, '\0'));

        // Application: type (1), size (1)
        byteArray.append(QByteArray(2, '\0'));
     }

    /**
     * CIP for "max"
     */
    if(command.at(2)=="max") {
        qDebug() << "max" << endl;

        // Header: fix
        byteArray.append(QByteArray(34, '\0'));

        // Header: size (1)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255, '\0'));

        // Contextinformation: fix
        byteArray.append(QByteArray(2, '\0'));

        // Contextinformation: size (255)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255*2, '\0'));

        // Application Data: fix
        byteArray.append(QByteArray(0, '\0'));

        // Application Data: size (255)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255, '\0'));


     }

    /**
     * CIP for "random"
     */
    if(command.at(2)=="random") {
        qDebug() << "random" << endl;

        QByteArray randValues;
        qsrand(QTime::currentTime().msec());
        for(int i=0; i <= 1064; i++) {
            randValues.append(qFloor(qrand()/CRN_RANDOM_DIVISOR));
        }


        int i = 0;
        quint8 rand;

        // Header: request (1)
        byteArray.append(randValues.at(i++));


        // Header: profile (1)
        byteArray.append(randValues.at(i++));


        // Header: version (1)
        byteArray.append(randValues.at(i++));


        // Header: channel (1)
        byteArray.append(randValues.at(i++));

        // Header: UUID (16)
        QUuid uuid;
        uuid = QUuid::createUuid();
        QByteArray uuid_arr = uuid.toRfc4122();

        for(int j=0; j<16;j++) {

            byteArray.append(uuid_arr.at(j));
        }

        // Header: Empty IP address (4) and port number (2)
        byteArray.append(QByteArray(6, '\0'));

        // Header: time (8)
        byteArray.append(QByteArray(8, '\0'));

        // Header: type (1)
        byteArray.append(randValues.at(i++));

        // Header: size (1) and data
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand, rand));

        // Contextinformation: type (1)
        byteArray.append(randValues.at(i++));

        // Contextinformation: root-CIC (2)
        byteArray.append(randValues.at(i++));
        byteArray.append(randValues.at(i++));

        // Contextinformation: size (1)
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand*2, rand));

        // Application: type (1)
        byteArray.append(randValues.at(i++));

        // Application: size (1)
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand, rand));

    } // rand

    /**
     * Sent via TCP
     */
    QTcpSocket *tcpSocket;
    tcpSocket = new QTcpSocket();
    QTextStream outStream(stdout);

    QString out;

    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1", 22365);

    qDebug() << "waitForConnected!";
    if (tcpSocket->waitForConnected(5000)) {

        qDebug() << "Connected!";
    }
    else {
        errorStream << "Error: tcp_ping(" << command.join(" ") << ") No connection available!" << endl;
        return 1;
    }

    out = QString("BytesWritten: %1").arg(tcpSocket->write(byteArray, byteArray.length()));

    qDebug() << out;

    int numRead = 0, numReadTotal = 0;
    char buffer[MAXMSG];

    forever {
        numRead  = tcpSocket->read(buffer, MAXMSG);
        qDebug() << "read buffer";

        qDebug() << buffer;

        numReadTotal += numRead;
        if (numRead == 0 && !tcpSocket->waitForReadyRead())
            break;
    }
    qDebug() << numReadTotal << " bytes red";

    tcpSocket->flush();
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    outStream << out << endl;

    return 0;
}



//public slots:
//    void tcpError( QAbstractSocket::SocketError error );


