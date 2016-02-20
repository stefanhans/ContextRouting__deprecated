// only for dev
#include <QCoreApplication>

// .h + .cpp
#include <QStringList>

// .cpp
#include <QDebug>
#include <QTextStream>
#include <QTcpSocket>
#include <QHostAddress>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064

// .h
int tcp_ping(QStringList command);


// .cpp
/**
 * @brief tcp_ping
 * @param command "ping udp rzv|max|rand|default"
 * @return
 */

int udp_ping(QStringList command) {
    qDebug() << "udp_ping(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 3 || command.at(0)!="ping" || command.at(1)!="udp" ) {

        errorStream << "Error: tcp_ping(" << command.join(" ") << ") is no valid call (ping udp <ip_address> <port> rzv|max|random|default)" << endl;
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
    QTcpSocket *tcpSocket;
    tcpSocket = new QTcpSocket();
    QTextStream outStream(stdout);

    QString out;

    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress::Broadcast, 22365);

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


// only for dev
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // call
    QStringList command;

    //    for(int i=1; i<argc; i++) {
    //        command.append(QString("%1").arg(argv[i]));
    //    }

    command.append("ping");
    command.append("udp");
    command.append("rzv");

    qDebug() << "Return: " << udp_ping(command) << endl;

    return a.exec();
}


