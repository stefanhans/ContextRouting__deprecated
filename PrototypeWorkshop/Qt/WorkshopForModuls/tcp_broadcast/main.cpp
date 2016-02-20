// only for dev
#include <QCoreApplication>

// .h + .cpp
#include <QStringList>

// .cpp
#include <QDebug>
#include <QTextStream>
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


