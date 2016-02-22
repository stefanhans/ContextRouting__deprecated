// only for dev
#include <QCoreApplication>

// .h + .cpp
#include <QStringList>

// .cpp
#include <QDebug>
#include <QTextStream>
#include <QUdpSocket>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064

// .h
int udp_ping(QStringList command);


// .cpp
/**
 * @brief udp_ping
 * @param command "ping udp rzv|max|rand|default"
 * @return
 */

int udp_ping(QStringList command) {
    qDebug() << "udp_ping(" << command.join(" ") << ")" << endl;
    qDebug() << "udp_ping(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 3 || command.at(0)!="ping" || command.at(1)!="udp" ) {

        errorStream << "Error: udp_ping(" << command.join(" ") << ") is no valid call (ping udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }


    /**
     * <functionality>
     */


    QByteArray byteArray;

    /**
     * CIP for "rzv"
     */
    if(command.at(2)=="rzv") {
        qDebug() << "rzv" << endl;

        byteArray.append(QByteArray(42, '\0'));
     }


    /**
     * Sent via TCP
     */
    QUdpSocket *udpSocket;
    udpSocket = new QUdpSocket();
    QTextStream outStream(stdout);

    QString out;

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

    return 0;
}


// only for dev
int main(int argc, char *argv[])
{

    // call
    QStringList command;

//    for(int i=1; i<argc; i++) {
//        command.append(QString("%1").arg(argv[i]));
//    }

    command.append("ping");
    command.append("udp");
    command.append("rzv");

    qDebug() << "Return: " << udp_ping(command) << endl;
}
