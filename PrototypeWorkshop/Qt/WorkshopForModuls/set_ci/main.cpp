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
 * @param commands "set_ci <file> binary|integer|hex|cip type|content|mask|size|contents|bricks <value>"
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

    if(! command.at(2).contains(QRegExp("^(binary|integer|hex|cip)$"))) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid CIP mode!" << endl;
        man("usage set_ci");
        return 1;
    }

    if(! command.at(3).contains(QRegExp("^(type|content|mask|size|contents|bricks)$"))) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid CI key!" << endl;
        man("usage set_ci");
        return 1;
    }

    /**
     * Check value for integer and single value
     */
    if(command.at(2)=="integer" && command.at(3).contains(QRegExp("^(type|content|mask|size)$"))
            && // not uint8 (0-255)
            ((! command.at(4).contains(QRegExp("^\\d\\d?\\d?$")))
            || command.at(4).toInt() < 0
            || command.at(4).toInt() > 255)) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid CI value!" << endl;
        man("usage set_ci");
        return 1;
    }

    /**
     * Check value for binary and single value
     */
    if(command.at(2)=="binary" && command.at(3).contains(QRegExp("^(type|content|mask|size)$"))
            && // not uint8 (00000000-11111111)
            ((! command.at(4).contains(QRegExp("^(0|1){8}$"))))) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid CI value!" << endl;
        man("usage set_ci");
        return 1;
    }

    /**
     * Check value for hex and single value
     */
    if(command.at(2)=="hex" && command.at(3).contains(QRegExp("^(type|content|mask|size)$"))
            && // not uint8 (00-ff)
            ((! command.at(4).contains(QRegExp("^(\\d|a|b|c|d|e|f){2}$"))))) {

        errorStream << "Error: set_ci(" << command.join(" ") << "): No valid CI value!" << endl;
        man("usage set_ci");
        return 1;
    }

    /**
     * Check value for binary and contents
     */
    if(command.at(2)=="binary" && command.at(3)=="contents") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for integer and contents
     */
    if(command.at(2)=="integer" && command.at(3)=="contents") {
        errorStream << "Not yet implemented!" << endl;
        return 1;
    }

    /**
     * Check value for hex and contents
     */
    if(command.at(2)=="hex" && command.at(3)=="contents") {
        errorStream << "Not yet implemented!" << endl;
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

        errorStream << "Error: set_ci(" << command.join(" ") << ") can not read " << filePath << endl;
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

    int i = byteArray.at(35) + 35;

    keys["type"] = ++i;
    keys["content"] = ++i;
    keys["mask"] = ++i;
    keys["size"] = ++i;
    keys["contents"] = ++i;


    QByteArray value;
    bool ok;


    /**
     * One byte keys (without size)
     */

    if(command.at(3).contains(QRegExp("^(type|content|mask|size)$"))) {


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
     * contents
     */
    if(command.at(3)=="contents") {
        if (keys.contains(command.at(3))) {
            qDebug() << "keys.contains(" << command.at(3) << ")" << endl;
        }
        else {
            errorStream << "Cannot find key for "<< command.at(3) << "!" << endl;
            return 1;
        }

        // Remove old contents
        qDebug().noquote().nospace() << "Remove " << (int) byteArray.at(keys["size"]) << " byte(s) of old CIC-bricks" << endl;

        pos = keys["size"];
        int oldContentsSize = byteArray.at(keys["size"]);

        for (int i=0; i < oldContentsSize; i++) {
            byteArray.remove(pos, 2);
        }


        // Set size
        QString size = QString("%1").arg(command.at(4).size());

        value.append(size.toUInt(&ok, 10));

        if(!ok) {
            errorStream << "Cannot convert "<< command.at(4) << " to base 10!" << endl;
            return 1;
        }

        byteArray.replace(keys["size"], 1, value);
        qDebug().noquote().nospace() << "Set size to " << size << endl;


        // Set contents
        pos = keys[command.at(3)];

        const QChar *data = command.at(4).data();
        while (!data->isNull()) {
            qDebug() << data->toLatin1() << " (" << data->unicode() << ")";
            byteArray.insert(pos++, data->toLatin1());
            byteArray.insert(pos++, '\0');
            ++data;
        }

    }



    /**
     * Write file
     */

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

        errorStream << "Error: set_ci(" << command.join(" ") << ") can not write to file " << filePath << endl;
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

    qDebug() << "Return: " << set_ci(command) << endl;

    return 0;
}

