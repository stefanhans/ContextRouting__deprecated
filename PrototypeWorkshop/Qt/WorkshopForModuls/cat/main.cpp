// .h
#include <QStringList>
// other includes

// .h
int cat(QStringList command);

// .cpp

#include <arpa/inet.h>

#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QUuid>
#include <QDateTime>
// other includes

// .cpp
#define CRN_RANDOM_DIVISOR (RAND_MAX/255)
#define MAXMSG 1064
#define CIP_ROOT "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/cips"

#include "usage.h"

// .cpp
/**
 * @brief cat
 * @param command "cat <file> binary|integer|hex|cip"
 * @return
 */

int cat(QStringList command) {
    qDebug() << "cat(" << command.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(command.size() != 3) {

        errorStream << "Error: cat(" << command.join(" ") << "): No valid number of arguments!" << endl;
        man("usage cat");
        return 1;
    }

    if(command.at(0)!="cat") {

        errorStream << "Error: cat(" << command.join(" ") << "): No valid command!" << endl;
        man("usage cat");
        return 1;
    }

    if(! command.at(2).contains(QRegExp("^(binary|integer|hex|cip)$"))) {

        errorStream << "Error: cat(" << command.join(" ") << "): No valid CIP omode!" << endl;
        man("usage cat");
        return 1;
    }

    /**
     * Read file
     */

    QString filePath;
    QByteArray byteArray;

    filePath = CIP_ROOT;
    filePath += "/" + command.at(1);

    qDebug() << "filePath: " << filePath << endl;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {

        errorStream << "Error: cat(" << command.join(" ") << ") can not read " << filePath << endl;
        errorStream << file.errorString() << endl;

        return 1;
    }
    byteArray = file.readAll();
    file.close();

    qDebug() << "byteArray.size(): " << byteArray.size() << endl;




    /**
     * CIP as "binary"
     */
    if(command.at(2)=="binary") {
        qDebug() << "binary" << endl;

        quint8 byte;
        for(int b=0; b<byteArray.size(); b++) {
            byte = byteArray.at(b);
            qDebug().noquote().nospace() << QString("%1").arg(b).rightJustified(4) << ": " << QString("%1").arg(byte, 8, 2, QLatin1Char('0'));
        }
    }

    /**
     * CIP as "hex"
     */
    if(command.at(2)=="hex") {
        qDebug() << "hex" << endl;

        quint8 byte;
        for(int b=0; b<byteArray.size(); b++) {
            byte = byteArray.at(b);
            qDebug().noquote().nospace() << QString("%1").arg(b).rightJustified(4) << ": " << QString("%1").arg(byte, 4, 16, QLatin1Char('0'));
        }
    }


    /**
     * CIP as "integer"
     */
    if(command.at(2)=="integer") {
        qDebug() << "integer" << endl;

        quint8 byte;
        for(int b=0; b<byteArray.size(); b++) {
            byte = byteArray.at(b);
            qDebug().noquote().nospace() << QString("%1").arg(b).rightJustified(4) << ": " << QString("%1").arg(byte).rightJustified(3);
        }
    }


    /**
     * CIP as "cip"
     */
    if(command.at(2)=="cip") {
        qDebug() << "cip" << endl;

        quint8 byte;
        int b = 0;
        int size;
        QString cipString;

        // Header: request (1)
        byte = byteArray.at(b++);

        switch (byte) {
        case 0:
            cipString = "SERVICE_RZV";
            break;
        case 1:
            cipString = "SERVICE_HEARTBEAT";
            break;
        case 2:
            cipString = "SERVICE_OFFER_REQUEST";
            break;
        case 3:
            cipString = "SERVICE_REPLY";
            break;
        default:
            cipString = "undefined";
            break;
        }
        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: request: " << byte << " : " <<  cipString;


        // Header: profile (1)
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: profile: " << byte;


        // Header: version (1)
        byte = byteArray.at(b++);
        qDebug().noquote() <<  QString("%1").arg(b-1).rightJustified(4) << QString("Header: version: %1.%2").arg(byte>>4).rightJustified(2).arg(byte%16, 2, 10, QLatin1Char('0')).rightJustified(2);


        // Header: channel (1)
        byte = byteArray.at(b++);

        switch (byte) {
        case 0:
            cipString = "CHANNEL_RZV";
            break;
        case 1:
            cipString = "CHANNEL_CI_MATCHING";
            break;
        default:
            cipString = "undefined";
            break;
        }
        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: channel: " << byte << " : " <<  cipString;

        // Header: UUID (16)
        QByteArray uuid = byteArray.mid(b, 16);
        b += 16;

        // Show UUID
//        QString uuidStr;
//        for(QByteArray::iterator it = uuid.begin(); it != uuid.end(); it++){
//            byte = (*it);
//            uuidStr.append(QString("%1").arg(byte, 0, 16));
//        };
//        qDebug() << "UUID (C): " << uuidStr;

        QUuid quuid = QUuid::fromRfc4122(uuid);
        qDebug().noquote().nospace() <<  QString("%1").arg(b-16).rightJustified(4) << " Header: UUID: " << quuid.toString();

        // Header: IP address (4)
        QByteArray ipAddress = byteArray.mid(b, 4);
        b += 4;
        in_addr ip;
        memcpy(&ip, ipAddress, 4);
        qDebug().noquote().nospace() << QString("%1").arg(b-4).rightJustified(4) << " Header: IP address: "  << inet_ntoa(ip);

        // Header: port number (2)
        QByteArray ipPort = byteArray.mid(b, 2);
        b += 2;
        quint16 portNum;
        memcpy(&portNum, ipPort, 2);
        qDebug().noquote().nospace() << QString("%1").arg(b-2).rightJustified(4) << " Header: port number: " << ntohs(portNum);


        // Header: time (8)
        QByteArray timeArray = byteArray.mid(b, 8);
        b += 8;
        time_t unixTime;
        memcpy(&unixTime, timeArray, 8);

        QDateTime *dateTime = new QDateTime;
        dateTime->setTime_t((uint) unixTime);

//        qDebug() << "Header: unixTime: " << unixTime;
        qDebug().noquote().nospace() << QString("%1").arg(b-8).rightJustified(4) << " Header: dateTime: " << dateTime->toString();

        // Header: type (1)
        byte = byteArray.at(b++);

        switch (byte) {
        case 0:
            cipString = "HEADER_TYPE_OK (HEADER_TYPE_RZV)";
            break;
        case 1:
            cipString = "HEADER_TYPE_ERROR";
            break;
        default:
            cipString = "undefined";
            break;
        }
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) <<  " Header: type: " << byte << " : " <<  cipString;

        // Header: size (1) and data
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: size: " << byte;

        if(cipString == "HEADER_TYPE_ERROR" && byte == 3) {

            QString errorCategory = "";

            // ERROR_CATEGORY
            byte = byteArray.at(b++);

            switch (byte) {
            case 0:
                cipString = "ERROR_CATEGORY_NONE (unexpected)";
                break;
            case 1:
                cipString = "CIP_FORMAT_ERROR";
                errorCategory = "CIP_FORMAT_ERROR";
                break;
            default:
                cipString = "undefined";
                break;
            }
            qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: ERROR_CATEGORY: " << byte << " : " <<  cipString;

            // ERROR_PRIORITY
            byte = byteArray.at(b++);

            switch (byte) {
            case 0:
                cipString = "ERROR_PRIORITY_NONE (unexpected)";
                break;
            case 1:
                cipString = "ERROR_PRIORITY_DEBUG";
                break;
            case 2:
                cipString = "ERROR_PRIORITY_INFO";
                break;
            case 3:
                cipString = "ERROR_PRIORITY_NOTICE";
                break;
            case 4:
                cipString = "ERROR_PRIORITY_CRITICAL";
                break;
            case 5:
                cipString = "ERROR_PRIORITY_ALERT";
                break;
            case 6:
                cipString = "ERROR_PRIORITY_EMERGENCY";
                break;
            default:
                cipString = "undefined";
                break;
            }
            qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: ERROR_PRIORITY: " << byte << " : " <<  cipString;

            if(errorCategory == "CIP_FORMAT_ERROR") {

                // CIP_FORMAT_ERROR_ENUM
                byte = byteArray.at(b++);

                switch (byte) {
                case 0:
                    cipString = "CIP_FORMAT_ERROR_NONE (unexpected)";
                    break;
                case 1:
                    cipString = "CIP_FORMAT_ERROR_OUT_OF_RANGE";
                    break;
                case 2:
                    cipString = "CIP_FORMAT_ERROR_INCONSISTENT";
                    break;
                case 3:
                    cipString = "CIP_FORMAT_ERROR_WRONG_PROTOCOL";
                    break;
                default:
                    cipString = "undefined";
                    break;
                }
                qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: CIP_FORMAT_ERROR: " << byte << " : " <<  cipString;

            }
            else {
                qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: CIP_FORMAT_ERROR: " << byte << " : unexpected";

            }


        }
        else {
            size = byte;
            for(int i=0; i<size; i++) {
                byte = byteArray.at(b++);
                qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Header: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << byte;
            }
        }

        // Contextinformation: type (1)
        byte = byteArray.at(b++);

        switch (byte) {
        case 0:
            cipString = "CI_TYPE_RZV";
            break;
        case 1:
            cipString = "CI_TYPE_SIMPLE_MATCH";
            break;
        default:
            cipString = "undefined";
            break;
        }
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: type: " << byte << " : " <<  cipString;

        // Contextinformation: root-CIC (2)
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: root-CIC content: " << byte;
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: root-CIC mask: " << byte;

        // Contextinformation: size (1)
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: size: " << byte;

        size = byte;
        for(int i=0; i<size; i++) {
            byte = byteArray.at(b++);
            qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: CIC[" << QString("%1").arg(i).rightJustified(3) << "] content: " << QString("%1").arg(byte).rightJustified(3);
            byte = byteArray.at(b++);
            qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: CIC[" << QString("%1").arg(i).rightJustified(3) << "] mask:    " << QString("%1").arg(byte).rightJustified(3);
        }

        // Application: type (1)
        byte = byteArray.at(b++);

        switch (byte) {
        case 0:
            cipString = "APP_TYPE_RZV";
            break;
        case 1:
            cipString = "APP_TYPE_TEXT";
            break;
        case 2:
            cipString = "APP_TYPE_URL";
            break;
        default:
            cipString = "undefined";
            break;
        }
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: type: " << byte << " : " <<  cipString;

        // Application: size (1) and data
        byte = byteArray.at(b++);
        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: size: " << byte;

        if(cipString == "APP_TYPE_TEXT" || cipString == "APP_TYPE_URL") {
            size = byte;
            for(int i=0; i<size; i++) {
                byte = byteArray.at(b++);
                qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << QString("%1").arg(byte).rightJustified(3) << " : " <<  QChar(byte);
            }
        }
        else {
            size = byte;
            for(int i=0; i<size; i++) {
                byte = byteArray.at(b++);
                qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << QString("%1").arg(byte).rightJustified(3);
            }
        }
    }
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

//    command.append("cat");
//    command.append("test.bin");
//    command.append("binary");

    qDebug() << "Return: " << cat(command) << endl;
}


