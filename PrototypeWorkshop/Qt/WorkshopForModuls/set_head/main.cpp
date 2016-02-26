// .h
#include <QStringList>
// other includes

// .h
int set_head(QStringList command);

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

// .cpp
/**
 * @brief set_head
 * @param command "set_head <file> binary|integer|hex|cip request|profile|version|channel|uuid|ip|port|time|type|size|data <value>"
 * @return
 */

int set_head(QStringList command) {
    qDebug() << "set_head(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 5) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage set_head");
        return 1;
    }


    if(command.at(0)!="set_head") {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid command!" << endl;
        man("usage set_head");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(binary|integer|hex|cip)$"))) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid CIP omode!" << endl;
        man("usage set_head");
        return 1;
    }

    if(! command.at(3).contains(QRegExp("^(request|profile|version|channel|uuid|ip|port|time|type|size|data)$"))) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header key!" << endl;
        man("usage set_head");
        return 1;
    }

    /**
     * Debug
     */
    for(int i=0;i<command.size();i++) {
        qDebug() << "command.at(" << i << ")" << command.at(i) << endl;
    }

    /**
     * Check value for integer and single value
     */
    if(command.at(2)=="integer" && command.at(3).contains(QRegExp("^(request|profile|version|channel|type|size)$"))
            && // not uint8 (0-255)
            ((! command.at(4).contains(QRegExp("^\\d\\d?\\d?$")))
            || command.at(4).toInt() < 0
            || command.at(4).toInt() > 255)) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header value!" << endl;
        man("usage set_head");
        return 1;
    }

    /**
     * Check value for binary and single value
     */
    if(command.at(2)=="binary" && command.at(3).contains(QRegExp("^(request|profile|version|channel|type|size)$"))
            && // not uint8 (00000000-11111111)
            ((! command.at(4).contains(QRegExp("^(0|1){8}$"))))) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header value!" << endl;
        man("usage set_head");
        return 1;
    }

    /**
     * Check value for hex and single value
     */
    if(command.at(2)=="hex" && command.at(3).contains(QRegExp("^(request|profile|version|channel|type|size)$"))
            && // not uint8 (00-ff)
            ((! command.at(4).contains(QRegExp("^(\\d|a|b|c|d|e|f){2}$"))))) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header value!" << endl;
        man("usage set_head");
        return 1;
    }


    /**
     * Check value for binary and uuid
     */
    if(command.at(2)=="binary" && command.at(3)=="uuid") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for integer and uuid
     */
    if(command.at(2)=="integer" && command.at(3)=="uuid") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for hex and uuid
     */
    if(command.at(2)=="hex" && command.at(3)=="uuid"
            && // not (0-16^32)
            ((! command.at(4).contains(QRegExp("^(\\d|a|b|c|d|e|f){32}$"))))) {

        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header value!" << endl;
        man("usage set_head");
        return 1;
    }

    /**
     * Check value for cip and uuid
     */
    if(command.at(2)=="cip" && command.at(3)=="uuid") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }


    /**
     * Check value for binary and ip
     */
    if(command.at(2)=="binary" && command.at(3)=="ip") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for integer and ip
     */
    if(command.at(2)=="integer" && command.at(3)=="ip") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for hex and ip
     */
    if(command.at(2)=="hex" && command.at(3)=="ip") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for cip and ip
     */
    if(command.at(2)=="cip" && command.at(3)=="ip") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }




    /**
     * Check value for binary and port
     */
    if(command.at(2)=="binary" && command.at(3)=="port") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for integer and port
     */
    if(command.at(2)=="integer" && command.at(3)=="port") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for hex and port
     */
    if(command.at(2)=="hex" && command.at(3)=="port") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for cip and port
     */
    if(command.at(2)=="cip" && command.at(3)=="port") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }




    /**
     * Check value for binary and time
     */
    if(command.at(2)=="binary" && command.at(3)=="time") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for integer and time
     */
    if(command.at(2)=="integer" && command.at(3)=="time") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for hex and time
     */
    if(command.at(2)=="hex" && command.at(3)=="time") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for cip and time
     */
    if(command.at(2)=="cip" && command.at(3)=="time" && command.at(4)!="now") {
        errorStream << "Error: set_head(" << command.join(" ") << "): No valid header value!" << endl;
        man("usage set_head time");
        return 1;
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

        errorStream << "Error: set_head(" << command.join(" ") << ") can not read " << filePath << endl;
        return 1;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;



    /**
     * Define map with start position
     */

    QMap<QString, int> keys;
    int pos;

    keys["request"] = 0;
    keys["profile"] = 1;
    keys["version"] = 2;
    keys["channel"] = 3;
    keys["uuid"] = 4;
    keys["ip"] = 20;
    keys["port"] = 24;
    keys["time"] = 26;
    keys["type"] = 34;
    keys["size"] = 35;



    QByteArray value;
    bool ok;


    /**
     * One byte keys (without size)
     */

    if(command.at(3).contains(QRegExp("^(request|profile|version|channel|type)$"))) {


        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;

            if(command.at(2)=="binary") {
                value.append(command.at(4).toUInt(&ok, 2));

                if(!ok) {
                    errorStream << "Cannot convert "<< command.at(4) << " to base 2!" << endl;
                    return 1;
                }
            }

            if(command.at(2)=="integer") {
                value.append(command.at(4).toUInt(&ok, 10));

                if(!ok) {
                    errorStream << "Cannot convert "<< command.at(4) << " to base 10!" << endl;
                    return 1;
                }
            }

            if(command.at(2)=="hex") {
                value.append(command.at(4).toUInt(&ok, 16));

                if(!ok) {
                    errorStream << "Cannot convert "<< command.at(4) << " to base 16!" << endl;
                    return 1;
                }
            }

            if(command.at(2)=="cip") {
                errorStream << "Not yet specified!" << endl;
                return 1;
            }

            pos = keys[command.at(3)];

            qDebug() << "byteArray.replace(" << pos << ", 1, " << value << ")" << endl;
            byteArray.replace(pos, 1, value);
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }

    }

    /**
     * uuid (16)
     */
    if(command.at(3)=="uuid") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;


            value.append(command.at(4).toLatin1());
            value.insert(20, '-');
            value.insert(16, '-');
            value.insert(12, '-');
            value.insert(8, '-');

            qDebug() << "value: " << value << endl;

            QUuid uuid(value);

            pos = keys[command.at(3)];

            qDebug() << "byteArray.replace(" << pos << ", 16, " << uuid << ")" << endl;
            byteArray.replace(pos, 16, uuid.toRfc4122());

        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }
    }

    /**
     * ip (4)
     */
    if(command.at(3)=="ip") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * port (2)
     */
    if(command.at(3)=="port") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * time (8)
     */
    if(command.at(3)=="time") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }

        uint unixTime = QDateTime::currentDateTime().toTime_t();
        qDebug().noquote().nospace() << "NOW: " << QDateTime::fromTime_t(unixTime).toString() << endl;

        pos = keys[command.at(3)];

        for(int j = 0; j < 8; j++) {

            byteArray[pos++] = unixTime%256;
            qDebug().noquote().nospace() << "time[" << j << "]: " << QString("%1").arg(unixTime%256, 8, 2, QLatin1Char('0'));

            unixTime = unixTime >> 8;
        }
    }

    /**
     * size (1)
     */
    if(command.at(3)=="size") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * data (size)
     */
    if(command.at(3)=="data") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }


    /**
     * Write file
     */

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        errorStream << "Error: set_head(" << command.join(" ") << ") can not write to file " << filePath << endl;
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

    qDebug() << "Return: " << set_head(command) << endl;
}


