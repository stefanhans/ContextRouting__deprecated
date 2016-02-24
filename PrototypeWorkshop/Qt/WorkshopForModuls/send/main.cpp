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
 * @param commands "send tcp|udp <ip> <port> <file>"
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

    if(command.size() != 5) {

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

    QString filePath;

    filePath = CIP_ROOT;
    filePath += "/" + command.at(4);

    qDebug() << "filePath: " << filePath << endl;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {

        errorStream << "Error: send(" << command.join(" ") << ") can not read " << filePath << endl;
        return 1;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;




    /**
     * Send via tcp
     */

    if(command.at(1) == "tcp") {
        qDebug() << "send via tcp" << endl;

        QTcpSocket *tcpSocket;
        tcpSocket= new QTcpSocket();

        tcpSocket->abort();

    }



    /**
     * Send via udp
     */

    if(command.at(1) == "udp") {
        qDebug() << "send via udp" << endl;

        QUdpSocket *udpSocket;
        udpSocket= new QUdpSocket();



        udpSocket->abort();











        udpSocket->abort();
        udpSocket->connectToHost("127.0.0.1", 22366);

        qDebug() << "waitForConnected!";
        if (udpSocket->waitForConnected(5000)) {
            qDebug() << "Connected!";
        }
        else {
            errorStream << "Error: udp_ping(" << command.join(" ") << "): No connection available!" << endl;
            return 1;
        }

        qDebug() << QString("BytesWritten: %1").arg(udpSocket->write(byteArray, byteArray.length()));
        udpSocket->flush();

        int numRead = 0, numReadTotal = 0;
        char buffer[MAXMSG];

        forever {
            numRead  = udpSocket->read(buffer, MAXMSG);
            qDebug() << "read buffer: " << numRead;

            numReadTotal += numRead;
            if (numRead <= 0 && !udpSocket->waitForReadyRead(30))
                break;
        }
        qDebug() << numReadTotal << " bytes red";

        if(numReadTotal==-1) {
            errorStream << "Error: udp_ping(" << command.join(" ") << "): " << udpSocket->errorString() << endl;
            return 1;
        }
        else {
            for(int i=0; i < numReadTotal; i++) {
                qDebug() << QString("receipt[%1]: %2\n").arg(i).arg(buffer[i], 8, 2, QLatin1Char('0')) << endl;;
            }
            QByteArray receipt(buffer);


            qDebug() << "receipt.size(): " << receipt.size();

            for(int i = 0; i < receipt.size();++i) {
               qDebug() << QString("receipt[%1]: %2\n").arg(i).arg(receipt.at(i), 8, 2, QLatin1Char('0')) << endl;;
            }
            qDebug() << "buffer: " << buffer;
        }

        udpSocket->disconnectFromHost();
        udpSocket->close();

        outStream << out << endl;

    }

    /**
     * <functionality>
     */

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


