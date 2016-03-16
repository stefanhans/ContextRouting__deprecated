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
 * @brief offer
 * @param commands "offer <file> random"
 * @return
 */

int offer(QStringList command) {
    qDebug() << "offer(" << command.join(" ") << ")" << endl;


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

    if(command.size() != 3) {

        errorStream << "Error: offer(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage offer");
        return 1;
    }


    if(command.at(0)!="offer") {

        errorStream << "Error: offer(" << command.join(" ") << "): No valid command!" << endl;
        man("usage offer");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(random)$"))) {

        errorStream << "Error: offer(" << command.join(" ") << "): No valid mode!" << endl;
        man("usage offer");
        return 1;
    }


    QByteArray byteArray;

    /**
     * Offer CIP for "random"
     */
    if(command.at(2)=="random") {
        qDebug() << "random" << endl;


        /*
         * Create random CIP
         */



        QByteArray randValues;
        qsrand(QTime::currentTime().msec());

        for(int i=0; i <= 1064; i++) {
            randValues.append((quint8) qFloor(qrand()/CRN_RANDOM_DIVISOR));
        }


        quint8 i = 0;
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
        qDebug() << "xxxxxxxxxxxxxxx: " << i;
        rand = randValues.at(i++);
        qDebug() << "xxxxxxxxxxxxxxx: " << i;
        qDebug() << "xxxxxxxxxxxxxxx: " << rand;
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



        /**
         * Define map with start position
         */

        QMap<QString, quint8> keys;
        quint8 pos;

        keys["request"] = 0;
        keys["profile"] = 1;
        keys["version"] = 2;
        keys["channel"] = 3;
        keys["uuid"] = 4;
        keys["ip"] = 20;
        keys["port"] = 24;
        keys["time"] = 26;
        keys["head_type"] = 34;
        keys["head_size"] = 35;

        i = byteArray.at(35) + 35;
        qDebug() << "XXXXXXXXXXXX: " << i;

        keys["ci_type"] = ++i;
        keys["content"] = ++i;
        keys["mask"] = ++i;
        keys["ci_size"] = ++i;
        keys["contents"] = ++i;



        QByteArray value;


        /*
         * Transform to Offer
         */

        // Header request -> 2
        pos = keys["request"];
        value.clear();
        value.append((quint8) 2);

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);


        // Header channel -> 1
        pos = keys["channel"];
        value.clear();
        value.append((quint8) 1);

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);


        // Header version -> 1
        pos = keys["version"];
        value.clear();
        value.append((quint8) 1);

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);


        // CI type -> 1
        pos = keys["ci_type"];
        value.clear();
        value.append((quint8) 1);

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);


        // CI root-CIC->content -> 1
        pos = keys["content"];
        value.clear();
        value.append((quint8) 1);

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);


        // CI root-CIC->mask -> 0
        pos = keys["mask"];
        value.clear();
        value.append('\0');

        qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
        byteArray.replace(pos, 1, value);



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

    //    command.append("function");
    //    command.append("my");
    //    command.append("arg_2");
    //    command.append("arg_3");

    qDebug() << "Return: " << offer(command) << endl;

    return 0;
}

