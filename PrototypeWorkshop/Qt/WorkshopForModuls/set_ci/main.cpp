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
 * @brief set_ci
 * @param commands "set_ci <file> binary|integer|hex|cip type|root-CIC|size|CIC-Bricks <value>"
 * @return
 */

int set_ci(QStringList command) {
    qDebug() << "set_ci(" << command.join(" ") << ")" << endl;


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

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage set_ci");
        return 1;
    }


    if(command.at(0)!="set_ci") {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid command!" << endl;
        man("usage set_ci");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(...|...)$"))) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid ...!" << endl;
        man("usage set_ci");
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

    qDebug() << "Return: " << set_ci(command) << endl;

    return 0;
}

