// .h
#include <QStringList>
// other includes

// .h
int validate(QStringList command);

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
 * @brief validate
 * @param command "validate <file>"
 * @return
 */

int validate(QStringList command) {
    qDebug() << "validate(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 2) {

        errorStream << "Error: validate(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage validate");
        return 1;
    }


    if(command.at(0)!="validate") {

        errorStream << "Error: validate(" << command.join(" ") << "): No valid command!" << endl;
        man("usage validate");
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

        errorStream << "Error: validate(" << command.join(" ") << ") can not read " << filePath << endl;
        return 1;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;

    if (byteArray.size() < 42 || byteArray.size() > 1062) {

        qDebug() << "INVALID: CIP size is out of range!" << endl;
        return 1;
    }

    int size;
    int additionalBytes;
    bool ok;

    // Header: size
    size = 35;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        errorStream << "Header: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return 1;
    }
    qDebug() << "Header: size: " << additionalBytes << endl;
    size += additionalBytes;

    // CI: size
    size += 4;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        errorStream << "CI: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return 1;
    }
    qDebug() << "CI: size: " << additionalBytes << endl;
    size += additionalBytes*2;

    // Application: size
    size += 2;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        errorStream << "Application: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return 1;
    }
    qDebug() << "Application: size: " << additionalBytes << endl;
    size += additionalBytes;


    qDebug() << "byteArray.size(): " << byteArray.size() << endl;
    qDebug() << "size: " << size+1 << endl;
    if (byteArray.size() != size+1) {

        qDebug() << "INVALID: CIP size is not consistent!" << endl;
        return 1;
    }

    qDebug() << "VALID: CIP is valid." << endl;

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

    qDebug() << "Return: " << validate(command) << endl;
}


