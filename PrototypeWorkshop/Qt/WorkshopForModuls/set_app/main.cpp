#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QUuid>
#include <QTime>
#include <QtMath>

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064
#define CIP_ROOT "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/cips"

#include "usage.h"

/**
 * @brief set_app
 * @param commands "set_app <file> binary|integer|hex|cip type|root-CIC|size|CIC-Bricks <value>"
 * @return
 */

int set_app(QStringList command) {
    qDebug() << "set_app(" << command.join(" ") << ")" << endl;


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

        errorStream << "Error: set_app(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage set_app");
        return 1;
    }


    if(command.at(0)!="set_app") {

        errorStream << "Error: set_app(" << command.join(" ") << "): No valid command!" << endl;
        man("usage set_app");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(...|...)$"))) {

        errorStream << "Error: set_app(" << command.join(" ") << "): No valid ...!" << endl;
        man("usage set_app");
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

    for(int i=1; i<argc; i++) {
        command.append(QString("%1").arg(argv[i]));
    }

    //    command.append("function");
    //    command.append("my");
    //    command.append("arg_2");
    //    command.append("arg_3");

    qDebug() << "Return: " << set_app(command) << endl;

    return 0;
}

