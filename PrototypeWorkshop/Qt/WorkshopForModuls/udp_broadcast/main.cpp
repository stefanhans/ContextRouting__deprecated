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
int tcp_ping(QStringList command);

QUdpSocket *udpSocket;


// .cpp
/**
 * @brief tcp_ping
 * @param command "ping udp rzv|max|rand|default"
 * @return
 */

int udp_broadcast(QStringList command) {
    qDebug() << "udp_broadcast(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 5 || command.at(0)!="broadcast" || command.at(1)!="udp" ) {

        errorStream << "Error: udp_broadcast(" << command.join(" ") << ") is no valid call (broadcast udp <ip_address> <port> rzv|max|random|default)" << endl;
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
    QCoreApplication a(argc, argv);

    // call
    QStringList command;

    for(int i=1; i<argc; i++) {
        command.append(QString("%1").arg(argv[i]));
    }

//    command.append("broadcast");
//    command.append("udp");
//    command.append("rzv");

    qDebug() << "Return: " << udp_broadcast(command) << endl;

}


