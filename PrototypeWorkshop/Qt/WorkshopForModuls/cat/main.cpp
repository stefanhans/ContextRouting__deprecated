// .h
#include <QStringList>
// other includes

// .h
int my_function(QStringList command);

// .cpp
#include <QDebug>
#include <QTextStream>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064


// .cpp
/**
 * @brief tcp_ping
 * @param command "ping udp rzv|max|rand|default"
 * @return
 */

int my_function(QStringList command) {
    qDebug() << "my_function(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 4 || command.at(0)!="function" || command.at(1)!="my" ) {

        errorStream << "Error: my_function(" << command.join(" ") << ") is no valid call (function my <arg_2> <arg_4>)" << endl;
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

    // call
    QStringList command;

    //    for(int i=1; i<argc; i++) {
    //        command.append(QString("%1").arg(argv[i]));
    //    }

    command.append("function");
    command.append("my");
    command.append("arg_2");
    command.append("arg_3");

    qDebug() << "Return: " << my_function(command) << endl;
}


