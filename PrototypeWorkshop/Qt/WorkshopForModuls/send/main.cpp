#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTcpSocket>
#include <QUdpSocket>

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064
#define CIP_ROOT "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/cips"

#include "usage.h"

/**
 * @brief send
 * @param commands "send tcp|udp <ip> <port> <sendfile> <receivefile>"
 * @return
 */

int send(QStringList command) {
    qDebug() << "send(" << command.join(" ") << ")" << endl;


    /**
     * Debug
     */
    for(int i=0;i<command.size();i++) {
        qDebug() << "command.at(" << i << ")" << command.at(i) << endl;
    }


    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 6) {

        errorStream << "Error: send(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage send");
        return 1;
    }


    if(command.at(0)!="send") {

        errorStream << "Error: send(" << command.join(" ") << "): No valid command!" << endl;
        man("usage send");
        return 1;
    }

    if(! command.at(1).contains(QRegExp("^(tcp|udp)$"))) {

        errorStream << "Error: send(" << command.join(" ") << "): No valid protocol!" << endl;
        man("usage send");
        return 1;
    }


    if(! command.at(2).contains(QRegExp("^\\d\\d?\\d?.\\d\\d?\\d?.\\d\\d?\\d?.\\d\\d?\\d?$"))) {

        errorStream << "Error: send(" << command.join(" ") << "): No valid IP address!" << endl;
        man("usage send");
        return 1;
    }


    if(! command.at(3).contains(QRegExp("^\\d\\d?\\d?\\d?\\d?$"))) {

        errorStream << "Error: send(" << command.join(" ") << "): No valid port number!" << endl;
        man("usage send");
        return 1;
    }



    /**
     * Read file
     */

    QString sendfilePath;

    sendfilePath = CIP_ROOT;
    sendfilePath += "/" + command.at(4);

    qDebug() << "sendfilePath: " << sendfilePath << endl;

    QFile file(sendfilePath);
    if (!file.open(QIODevice::ReadOnly)) {

        errorStream << "Error: send(" << command.join(" ") << ") can not read " << sendfilePath << endl;
        return 1;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;


    /**
     * Prepare send
     */
    QHostAddress ip(command.at(2));

    bool ok;
    quint16 port(command.at(3).toUInt(&ok));
    if(!ok) {
        errorStream << "Cannot convert "<< command.at(3) << " to base 2!" << endl;
        return 1;
    }


    /**
     * Prepare receipt
     */
    int numRead = 0, numReadTotal = 0;
    char buffer[MAXMSG];

    QByteArray receipt;


    /**
     * Send via tcp
     */

    if(command.at(1) == "tcp") {
        qDebug() << "send via tcp" << endl;

        QTcpSocket *tcpSocket;
        tcpSocket= new QTcpSocket();
        tcpSocket->abort();
        tcpSocket->connectToHost(ip, port);

        qDebug() << "waitForConnected!";
        if (tcpSocket->waitForConnected(5000)) {

            qDebug() << "Connected!";
        }
        else {
            errorStream << "Error: send(" << command.join(" ") << ") No connection available!" << endl;
            return 1;
        }

        qDebug() << QString("BytesWritten: %1").arg(tcpSocket->write(byteArray, byteArray.length()));

        forever {
            numRead  = tcpSocket->read(buffer, MAXMSG);
            qDebug() << "read buffer";

            qDebug() << buffer;
            qDebug() << " sizeof(buffer): " << sizeof(buffer);

            numReadTotal += numRead;
            if (numRead == 0 && !tcpSocket->waitForReadyRead())
                break;
        }
        qDebug() << numReadTotal << " bytes red";
        qDebug() << "sizeof(buffer): " << sizeof(buffer);


        quint8 byte;
        for(int b=0; b<byteArray.size(); b++) {
            byte = byteArray.at(b);
            qDebug().noquote().nospace() << QString("%1").arg(b).rightJustified(4) << ": " << QString("%1").arg(byte, 8, 2, QLatin1Char('0'));
        }

        tcpSocket->flush();
        tcpSocket->disconnectFromHost();
        tcpSocket->close();






    }



    /**
     * Send via udp
     */

    if(command.at(1) == "udp") {
        qDebug() << "send via udp" << endl;

        QUdpSocket *udpSocket;
        udpSocket= new QUdpSocket();
        udpSocket->abort();
        udpSocket->connectToHost(ip, port);

        qDebug() << "waitForConnected!";
        if (udpSocket->waitForConnected(5000)) {
            qDebug() << "Connected!";
        }
        else {
            errorStream << "Error: send(" << command.join(" ") << "): No connection available!" << endl;
            return 1;
        }

        qDebug() << QString("BytesWritten: %1").arg(udpSocket->write(byteArray, byteArray.length()));

        forever {
            numRead  = udpSocket->read(buffer, MAXMSG);
            qDebug() << "read buffer";

            qDebug() << buffer;
            qDebug() << " sizeof(buffer): " << sizeof(buffer);

            numReadTotal += numRead;
            if (numRead == 0 && !udpSocket->waitForReadyRead(30))
                break;
        }
        qDebug() << numReadTotal << " bytes red";
        qDebug() << "sizeof(buffer): " << sizeof(buffer);


        if(numReadTotal==-1) {
            errorStream << "Error: send(" << command.join(" ") << "): " << udpSocket->errorString() << endl;
            return 1;
        }

        udpSocket->disconnectFromHost();
        udpSocket->close();

    }

    /**
     * <functionality>
     */


    receipt.append(buffer, numReadTotal);

    quint8 byte;
    for(int b=0; b<receipt.size(); b++) {
        byte = receipt.at(b);
        qDebug().noquote().nospace() << QString("%1").arg(b).rightJustified(4) << ": " << QString("%1").arg(byte, 8, 2, QLatin1Char('0'));
    }




    /**
     * Write file
     */

    QString receivefilePath;

    receivefilePath = CIP_ROOT;
    receivefilePath += "/" + command.at(5);

    qDebug() << "receivefilePath: " << receivefilePath << endl;

    QFile receivefile(receivefilePath);

    if (!receivefile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        errorStream << "Error: CMD(" << command.join(" ") << ") can not write to file " << receivefilePath << endl;
        return 1;
    }
    receivefile.write(receipt);
    receivefile.close();

    qDebug() << "receivefilePath: " << receivefilePath << endl;
    qDebug() << "byteArray.size(): " << byteArray.size() << endl;

    return 0;
}


// only for dev
int main(int argc, char *argv[])
{

    // call
    QStringList command;

    for(int i=1; i<argc; i++) {
        command.append(QString("%1").arg(argv[i]));
    }

    //    command.append("function");
    //    command.append("my");
    //    command.append("arg_2");
    //    command.append("arg_3");

    qDebug() << "Return: " << send(command) << endl;

    return 0;
}


