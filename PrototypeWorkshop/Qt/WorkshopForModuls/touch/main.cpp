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

int touch(QStringList command) {
    qDebug() << "touch(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

//    QRegExp("(mail|letter|correspondence)");

    if(command.size() != 3
            || command.at(0)!="touch"
            || ! command.at(1).contains(QRegExp("(mail|letter|correspondence)")) ) {

        errorStream << "Error: touch(" << command.join(" ") << ") is no valid call (touch () <name>" << endl;
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

    command.append("touch");
    command.append("maiL");
    command.append("rzv");

    qDebug() << "Return: " << touch(command) << endl;

    return a.exec();
}


