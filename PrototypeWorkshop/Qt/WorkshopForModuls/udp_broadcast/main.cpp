// .h
#include <QStringList>

#include <QUdpSocket>


// .h
int udp_broadcast(QStringList command);

QUdpSocket *udpSocket;


// .cpp
#include <QDebug>
#include <QStringList>
#include <QTextStream>

#include <QUdpSocket>
// other includes


// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064

#define LINE_SEP "------------------------------------------------------"


#include "usage.h"

// .cpp
/**
 * @brief tcp_ping
 * @param command "ping udp rzv|max|rand|default"
 * @return
 */

int udp_broadcast(QStringList command) {
    qDebug() << "udp_broadcast(" << command.join(" ") << ")" << endl;

    qDebug() << LINE_SEP << endl;
    man("usage help");
    qDebug() << LINE_SEP << endl;

    qDebug() << LINE_SEP << endl;
    man("desc help");
    qDebug() << LINE_SEP << endl;

    qDebug() << LINE_SEP << endl;
    man("help help");
    qDebug() << LINE_SEP << endl;


    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 5) {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid number of arguments" << endl;
        man("usage udp_broadcast");
        return 1;
    }


    if(command.at(0)!="broadcast") {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid prototcol (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }

    if(command.at(1)!="udp") {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid prototcol (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^\\d\\d?\\d?.\\d\\d?\\d?.\\d\\d?\\d?.\\d\\d?\\d?$"))) {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid IP address (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }

    if(! command.at(3).contains(QRegExp("^\\d\\d?\\d?\\d?\\d?\\d?$"))) {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid port number (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }

    if(! command.at(4).contains(QRegExp("(rzv|max|random|default)"))) {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") has no valid CIP specification (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
        return 1;
    }


    /**
     * <functionality>
     */


    QByteArray byteArray;

    /**
     * CIP for "rzv"
     */
    if(command.at(4)=="rzv") {
        qDebug() << "rzv" << endl;

        byteArray.append(QByteArray(42, '\0'));
     }

    /**
     * CIP for "test"
     */
    if(command.at(4)=="test") {
        qDebug() << "test" << endl;

        byteArray = "Broadcast message ";
     }


    udpSocket = new QUdpSocket();

//    udpSocket->writeDatagram(byteArray, byteArray.length(),
//                             QHostAddress::Broadcast, 22366);
//    "0.0.0.0"

    udpSocket->writeDatagram(byteArray, byteArray.length(),
                             QHostAddress(command.at(2)), QString(command.at(3)).toUInt());

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

    command.append("broadcast");
    command.append("udp");
    command.append("0.0.0.0");
    command.append("22365");
    command.append("rzv");

    qDebug() << "Return: " << udp_broadcast(command) << endl;

}


