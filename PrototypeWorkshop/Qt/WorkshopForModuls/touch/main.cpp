// .h + .cpp
#include <QStringList>

// .cpp
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QUuid>
#include <QTime>
#include <QtMath>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064
#define CIP_ROOT "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/cips"

#include "usage.h"

// .h
int touch(QStringList command);


// .cpp
/**
 * @brief touch
 * @param command "touch <file> rzv|max|rand|default"
 * @return
 */

int touch(QStringList command) {
    qDebug() << "touch(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 3) {

        errorStream << "Error: touch(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage touch");
        return 1;
    }


    if(command.at(0)!="touch") {

        errorStream << "Error: touch(" << command.join(" ") << "): No valid command!" << endl;
        man("usage touch");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(rzv|max|random|default)$"))) {

        errorStream << "Error: touch(" << command.join(" ") << "): No valid CIP specification!" << endl;
        man("usage touch");
        return 1;
    }

    /**
     * Read arguments
     */
    for(int i=0;i<command.size();i++) {
        qDebug() << "command.at(" << i << ")" << command.at(i) << endl;
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
     * CIP for "default"
     */
    if(command.at(2)=="default") {
        qDebug() << "default" << endl;

        // Header: request (1), profile (1), version (1), channel (1)
        byteArray.append(QByteArray(4, '\0'));

        // Header: UUID (16)
        QUuid uuid;
        uuid = QUuid::createUuid();
        QByteArray uuid_arr = uuid.toRfc4122();

        for(int j=0; j<16;j++) {

            byteArray.append(uuid_arr.at(j));
        }

        // Header: Empty IP address (4), port number (2), time (8), type (1), size (1)
        byteArray.append(QByteArray(16, '\0'));

        // Contextinformation: type (1), root-CIC (2), size (1)
        byteArray.append(QByteArray(4, '\0'));

        // Application: type (1), size (1)
        byteArray.append(QByteArray(2, '\0'));
     }

    /**
     * CIP for "max"
     */
    if(command.at(2)=="max") {
        qDebug() << "max" << endl;

        // Header: fix
        byteArray.append(QByteArray(34, '\0'));

        // Header: size (1)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255, '\0'));

        // Contextinformation: fix
        byteArray.append(QByteArray(2, '\0'));

        // Contextinformation: size (255)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255*2, '\0'));

        // Application Data: fix
        byteArray.append(QByteArray(0, '\0'));

        // Application Data: size (255)
        byteArray.append(QByteArray(QByteArray::fromHex("0xff")));
        byteArray.append(QByteArray(255, '\0'));


     }

    /**
     * CIP for "random"
     */
    if(command.at(2)=="random") {
        qDebug() << "random" << endl;

        QByteArray randValues;
        qsrand(QTime::currentTime().msec());
        for(int i=0; i <= 1064; i++) {
            randValues.append(qFloor(qrand()/CRN_RANDOM_DIVISOR));
        }


        int i = 0;
        quint8 rand;

        // Header: request (1)
        byteArray.append(randValues.at(i++));


        // Header: profile (1)
        byteArray.append(randValues.at(i++));


        // Header: version (1)
        byteArray.append(randValues.at(i++));


        // Header: channel (1)
        byteArray.append(randValues.at(i++));

        // Header: UUID (16)
        QUuid uuid;
        uuid = QUuid::createUuid();
        QByteArray uuid_arr = uuid.toRfc4122();

        for(int j=0; j<16;j++) {

            byteArray.append(uuid_arr.at(j));
        }

        // Header: Empty IP address (4) and port number (2)
        byteArray.append(QByteArray(6, '\0'));

        // Header: time (8)
        byteArray.append(QByteArray(8, '\0'));

        // Header: type (1)
        byteArray.append(randValues.at(i++));

        // Header: size (1) and data
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand, rand));

        // Contextinformation: type (1)
        byteArray.append(randValues.at(i++));

        // Contextinformation: root-CIC (2)
        byteArray.append(randValues.at(i++));
        byteArray.append(randValues.at(i++));

        // Contextinformation: size (1)
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand*2, rand));

        // Application: type (1)
        byteArray.append(randValues.at(i++));

        // Application: size (1)
        rand = randValues.at(i++);
        byteArray.append(rand);
        byteArray.append(QByteArray(rand, rand));

    } // rand



    /**
     * Write file
     */

    QString filePath;

    filePath = CIP_ROOT;
    filePath += "/" + command.at(1);

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        errorStream << "Error: touch(" << command.join(" ") << ") can not write to file " << filePath << endl;
        return 1;
    }
    file.write(byteArray);

    file.close();

    qDebug() << "filePath: " << filePath << endl;


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

//    command.append("touch");
//    command.append("myfile");
//    command.append("rzv");

    qDebug() << "Return: " << touch(command) << endl;

    return 0;
}


