#include "crn.h"
#include <arpa/inet.h>
#include <string.h>

#include <QDebug>
#include <QtNetwork>
#include <QTcpSocket>

#define MAXMSG 1064

//extern QString my_global_string;


void CRN::tcpError( QAbstractSocket::SocketError error ) {
    return;
}

void CRN::show() {

//    qDebug() << my_global_string << endl;
    return;

}

void CRN::showLocal() {

    qDebug() << "CRN::showLocal()" << endl;
    return;

}

void CRN::getCIP(QByteArray* byteArray, QString type, QByteArray* randValues) {

//    qDebug() << my_global_string << endl;



    // RZV
    if(type=="rzv") {
        byteArray->append(QByteArray(42, '\0'));
        return;
    }

    // MAX
    if(type=="max") {

        // Header: fix
        byteArray->append(QByteArray(34, '\0'));

        // Header: size (1)
        byteArray->append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray->append(QByteArray(255, '\0'));

        // Contextinformation: fix
        byteArray->append(QByteArray(2, '\0'));

        // Contextinformation: size (255)
        byteArray->append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray->append(QByteArray(255*2, '\0'));

        // Application Data: fix
        byteArray->append(QByteArray(0, '\0'));

        // Application Data: size (255)
        byteArray->append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray->append(QByteArray(255, '\0'));

        return;
    }

    // RAND
    if(type=="rand" && randValues != NULL && randValues->size() >= 1064) {

        int i = 0;
        quint8 rand;

        // Header: request (1)
        byteArray->append(randValues->at(i++));


        // Header: profile (1)
        byteArray->append(randValues->at(i++));


        // Header: version (1)
        byteArray->append(randValues->at(i++));


        // Header: channel (1)
        byteArray->append(randValues->at(i++));

        // Header: UUID (16)
        QUuid uuid;
        uuid = QUuid::createUuid();
        QByteArray uuid_arr = uuid.toRfc4122();

        for(int j=0; j<16;j++) {

            byteArray->append(uuid_arr.at(j));
        }

        // Header: Empty IP address (4) and port number (2)
        for(int j=0; j<6;j++) {
            byteArray->append(QByteArray::fromHex("0x0"));
        }

        // Header: time (4)
        quint64 unixTime = QDateTime::currentDateTime().toTime_t();
        for(int j=0; j<8; j++) {

            byteArray->append(unixTime%256);
            unixTime = unixTime >> 8;
        }

        // Header: type (1)
        byteArray->append(randValues->at(i++));

        // Header: size (1) and data
        rand = randValues->at(i++);
        byteArray->append(rand);
        byteArray->append(QByteArray(rand, rand));

        // Contextinformation: type (1)
        byteArray->append(randValues->at(i++));

        // Contextinformation: root-CIC (2)
        byteArray->append(randValues->at(i++));
        byteArray->append(randValues->at(i++));

        // Contextinformation: size (1)
        rand = randValues->at(i++);
        byteArray->append(rand);
        byteArray->append(QByteArray(rand*2, rand));

        // Application: type (1)
        byteArray->append(randValues->at(i++));

        // Application: size (1)
        rand = randValues->at(i++);
        byteArray->append(rand);
        byteArray->append(QByteArray(rand, rand));

        return;
    }

    // default
    byteArray->append(QByteArray(42, '\0'));

    return;
}



QString CRN::pingTcp(QString type, QByteArray* randValues) {

    tcpSocket = new QTcpSocket();

    QByteArray byteArray;
    getCIP(&byteArray, type, randValues);

    QString out;

    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1", 22365);

    qDebug() << "waitForConnected!";
    if (tcpSocket->waitForConnected(5000)) {

        qDebug() << "Connected!";
    }
    else {
        return "NOT Connected!";
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

    return out;
}


QString CRN::ping() {

    QByteArray byteArray(42, '\0');

    QString out;

    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1", 22365);

    qDebug() << "waitForConnected!";
    if (tcpSocket->waitForConnected(5000)) {

        qDebug() << "Connected!";
    }
    else {
        return "NOT Connected!";
    }

    out = QString("BytesWritten: %1").arg(tcpSocket->write(byteArray, byteArray.length()));

    qDebug() << out;

    int numRead = 0, numReadTotal = 0;
    char buffer[50];

    forever {
        numRead  = tcpSocket->read(buffer, 50);
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

    return out;
}


QString CRN::pingMax() {
    qDebug() <<  "pingMax()";

    QTcpSocket *tcpSocket;
    tcpSocket = new QTcpSocket();

    // Header: fix
    QByteArray byteArray(35, '\0');

    // Header: size (1)
    byteArray[byteArray.length()] = quint8(255);
    byteArray.append(QByteArray(255, '\0'));


    // Contextinformation: fix
    byteArray.append(QByteArray(3, '\0'));

    // Contextinformation: size (255)
    byteArray[byteArray.length()] = quint8(255);
    byteArray.append(QByteArray(255*2, '\0'));


    // Application Data: fix
    byteArray.append(QByteArray(1, '\0'));

    // Application Data: size (255)
    byteArray[byteArray.length()] = quint8(255);
    byteArray.append(QByteArray(255, '\0'));

    QString out;

    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1", 22365);

    qDebug() << "waitForConnected!";
    if (tcpSocket->waitForConnected(5000)) {

//        qDebug() << "Connected!";
    }
    else {
        return "NOT Connected!";
    }


    out = QString("BytesWritten: %1").arg(tcpSocket->write(byteArray, byteArray.length()));

    int numRead = 0, numReadTotal = 0;
    char buffer[50];

    forever {
        numRead  = tcpSocket->read(buffer, 50);
//        qDebug() << "read buffer";

//        qDebug() << buffer;

        numReadTotal += numRead;
        if (numRead == 0 && !tcpSocket->waitForReadyRead())
            break;
    }
    qDebug() << numReadTotal << " bytes red";

    tcpSocket->flush();
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    return out;
}

