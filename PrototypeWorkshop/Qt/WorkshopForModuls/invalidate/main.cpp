// .h
#include <QStringList>
// other includes

// .h
int invalidate(QStringList command);

// .cpp
#include <QDebug>
#include <QTextStream>
#include <QFile>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064
#define CIP_ROOT "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/cips"

#include "usage.h"

// .cpp
/**
 * @brief invalidate
 * @param command "invalidate <file> append|chop <bytes>"
 * @return
 */

int invalidate(QStringList command) {
    qDebug() << "invalidate(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 4) {

        errorStream << "Error: invalidate(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage invalidate");
        return 1;
    }


    if(command.at(0)!="invalidate") {

        errorStream << "Error: invalidate(" << command.join(" ") << "): No valid command!" << endl;
        man("usage invalidate");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(append|chop)$"))) {

        errorStream << "Error: invalidate(" << command.join(" ") << "): No valid action!" << endl;
        man("usage invalidate");
        return 1;
    }

    if(! command.at(3).contains(QRegExp("^\\d+$")) || command.at(3) == "0") {

        errorStream << "Error: invalidate(" << command.join(" ") << "): No valid number of bytes!" << endl;
        man("usage invalidate");
        return 1;
    }

    /**
     * Debug
     */
    for(int i=0;i<command.size();i++) {
        qDebug() << "command.at(" << i << ")" << command.at(i) << endl;
    }


    /**
     * Read file
     */

    QString filePath;

    filePath = CIP_ROOT;
    filePath += "/" + command.at(1);

    qDebug() << "filePath: " << filePath << endl;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {

        errorStream << "Error: invalidate(" << command.join(" ") << ") can not read " << filePath << endl;
        return 1;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;

    bool ok;
    int bytes = command.at(3).toInt(&ok);

    if(!ok) {
        errorStream << "Cannot convert "<< command.at(3) << " to integer!" << endl;
        return 1;
    }


    /**
     * Add bytes
     */

    if (command.at(2) == "append") {
        qDebug() << "append: " << bytes << " bytes" << endl;

        QByteArray filling;
        byteArray.append(filling.fill('\0', (uint) bytes));
    }


    /**
     * Chop bytes
     */

    if (command.at(2) == "chop") {
        if (bytes > byteArray.size()) {
            errorStream << "Cannot chop "<< command.at(3) << " from " << byteArray.size() << " bytes!" << endl;
            return 1;
        }
        byteArray.chop(bytes);
    }


    /**
     * Write file
     */

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        errorStream << "Error: invalidate(" << command.join(" ") << ") can not write to file " << filePath << endl;
        return 1;
    }
    file.write(byteArray);

    file.close();

    qDebug() << "filePath: " << filePath << endl;
    qDebug() << "byteArray.size(): " << byteArray.size() << endl;


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

    qDebug() << "Return: " << invalidate(command) << endl;
}


