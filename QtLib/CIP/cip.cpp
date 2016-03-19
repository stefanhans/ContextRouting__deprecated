#include "cip.h"

void CIP::initialize() {

    qDebug() << "initialize() service: " << service;

    switch (service) {

    case Heartbeat:
        setChannel(CI_Matching);
        qDebug() << "case Heartbeat:";
        setRequest(RequestHeartbeat);
        qDebug() << "request: " << request;
        setIpPort(UDP);
        break;

    case Offer:
        setChannel(CI_Matching);
        setRequest(RequestOffer);
        setIpPort(TCP);
        break;

    case Request:
        setChannel(CI_Matching);
        setRequest(RequestRequest);
        setIpPort(UDP);
        break;

    case TcpReply:
        setChannel(CI_Matching);
        setRequest(RequestReply);
        setIpPort(TCP);
        break;

    case UdpReply:
        setChannel(CI_Matching);
        setRequest(RequestReply);
        setIpPort(UDP);
        break;

    default:
        qDebug() << "Error: Initialize with undefined service " << service;
        break;
    }

}

QString CIP::getService() const
{

    switch (service) {

    case Heartbeat:
        return QString("Service::Heartbeat");
        break;

    case Offer:
        return QString("Service::Offer");
        break;

    case Request:
        return QString("Service::Request");
        break;

    case TcpReply:
        return QString("Service::TcpReply");
        break;

    case UdpReply:
        return QString("Service::UdpReply");
        break;

    default:
        return QString("Error: Undefined enum Service: %1").arg(service);
        break;
    }
}

void CIP::setService(const Service &value)
{
    service = value;

    qDebug() << "service: " << service;

    switch (service) {

    case Heartbeat:
        qDebug() << "case Heartbeat:";
        setRequest(RequestHeartbeat);
        qDebug() << "request: " << request;
        setIpPort(UDP);
        break;

    case Offer:
        setRequest(RequestOffer);
        setIpPort(TCP);
        break;

    case Request:
        setRequest(RequestRequest);
        setIpPort(UDP);
        break;

    case TcpReply:
        setRequest(RequestReply);
        setIpPort(TCP);
        break;

    case UdpReply:
        setRequest(RequestReply);
        setIpPort(UDP);
        break;

    default:
        setRequest(8);
        break;
    }

}


/*
 *
 * REQUEST
 *
 */
quint8 CIP::getRequest() const
{
    return request;
}

void CIP::setRequest(const quint8 &value)
{
    request = value;
}
QString CIP::requestToString(quint8 byte) const {

    qDebug() << "requestToString: " << byte;

    switch (byte) {
    case 0:
        return "Request RZV by convention";
        break;
    case 1:
        return "RequestHeartbeat";
        break;
    case 2:
        return "RequestOffer (TCP) || RequestRequest (UDP)";
        break;
    case 3:
        return "RequestReply";
        break;
    default:
        return "undefined";
        break;
    }
}

/*
 *
 * PROFILE
 *
 */
quint8 CIP::getProfile() const
{
    return profile;
}

void CIP::setProfile(const quint8 &value)
{
    profile = value;
}
QString CIP::profileToString(quint8 byte) const {

    return QString("undefined").arg(byte);
}


/*
 *
 * VERSION
 *
 */
quint8 CIP::getVersion() const
{
    return version;
}

void CIP::setVersion(const quint8 &value)
{
    version = value;
}
QString CIP::versionToString(quint8 byte) const {

    return QString("%1.%2").arg(byte>>4).rightJustified(2).arg(byte%16, 2, 10, QLatin1Char('0')).rightJustified(2);
}



/*
 *
 * CHANNEL
 *
 */
quint8 CIP::getChannel() const
{
    return channel;
}

void CIP::setChannel(const quint8 &value)
{
    channel = value;
}


QString CIP::channelToString(quint8 byte) const {

    qDebug() << "channelToString: " << byte;

    switch (byte) {
    case 0:
        return "Channel RZV by convention";
        break;
    case 1:
        return "CI_Matching";
        break;
    default:
        return "undefined";
        break;
    }
}

/*
 *
 * UUID
 *
 */
QUuid CIP::getUuid() const
{
    return uuid;
}
void CIP::setUuid(const QUuid &value)
{
    uuid = value;
}
QString CIP::uuidToString(QByteArray *bytes) const {

    QString uuidStr;
    quint8 byte;
    for(QByteArray::iterator it = bytes->begin(); it != bytes->end(); it++){
        byte = (*it);
        uuidStr.append(QString("%1").arg(byte, 0, 16));
    };
    return uuidStr;
}

/*
 *
 * IP ADDRESS
 *
 */
QHostAddress CIP::getIpAddress() const
{
    return ipAddress;
}

void CIP::setIpAddress(const QHostAddress &value)
{
    ipAddress = value;
}
QString CIP::ipAddressToString(QByteArray *bytes) const {

    return QString("%1.%2.%3.%4").arg((quint8)bytes->at(0)).arg((quint8)bytes->at(1)).arg((quint8)bytes->at(2)).arg((quint8)bytes->at(3));
}


/*
 *
 * IP PORT
 *
 */
quint16 CIP::getIpPort() const
{
    return ipPort;
}
void CIP::setIpPort(const quint16 &value)
{
    ipPort = value;
}
QString CIP::ipPortToString(QByteArray *bytes) const {

    quint16 ipPortNumber = (bytes->at(0)<<8) + bytes->at(1);
    return QString("%1").arg(ipPortNumber);
}


/*
 *
 * TIME
 *
 */
QDateTime CIP::getTime() const
{
    return time;
}
void CIP::setTime(const QDateTime &value)
{
    time = value;
}
QString CIP::timeToString(QByteArray *bytes) const {


//    time_t unixTime;
//    memcpy(&unixTime, bytes, 8);

    bool ok;
    uint unixTime = bytes->toUInt(&ok);

    QDateTime *dateTime = new QDateTime;
    dateTime->setTime_t((uint) unixTime);



    //    // Header: time (8)
    //    QByteArray timeArray = byteArray.mid(b, 8);
    //    b += 8;
    //    time_t unixTime;
    //    memcpy(&unixTime, timeArray, 8);

    //    QDateTime *dateTime = new QDateTime;
    //    dateTime->setTime_t((uint) unixTime);

    qDebug().noquote().nospace() << " timeToString: dateTime: " << dateTime->toString();




    return dateTime->toString();
}

quint8 CIP::getHeadType() const
{
    return headType;
}

void CIP::setHeadType(const quint8 &value)
{
    headType = value;
}

quint8 CIP::getHeadSize() const
{
    return headSize;
}

void CIP::setHeadSize(const quint8 &value)
{
    headSize = value;
}

QVector<quint8> CIP::getHeadData() const
{
    return headData;
}

void CIP::setHeadData(const QVector<quint8> &value)
{
    headData = value;
}

quint8 CIP::getCiType() const
{
    return ciType;
}

void CIP::setCiType(const quint8 &value)
{
    ciType = value;
}

CICBrick CIP::getRootCIC() const
{
    return rootCIC;
}

void CIP::setRootCIC(const CICBrick &value)
{
    rootCIC = value;
}

quint8 CIP::getCiSize() const
{
    return ciSize;
}

void CIP::setCiSize(const quint8 &value)
{
    ciSize = value;
}

QVector<CICBrick> CIP::getCICBricks() const
{
    return CICBricks;
}

void CIP::setCICBricks(const QVector<CICBrick> &value)
{
    CICBricks = value;
}

quint8 CIP::getAppType() const
{
    return appType;
}

void CIP::setAppType(const quint8 &value)
{
    appType = value;
}

quint8 CIP::getAppSize() const
{
    return appSize;
}

void CIP::setAppSize(const quint8 &value)
{
    appSize = value;
}

QVector<quint8> CIP::getAppData() const
{
    return appData;
}

void CIP::setAppData(const QVector<quint8> &value)
{
    appData = value;
}


void CIP::pack() {

    byteArray.append(getRequest());
    byteArray.append(getProfile());
    byteArray.append(getVersion());
    byteArray.append(getChannel());

    QByteArray uuid_arr = uuid.toRfc4122();
    for(int j=0; j<16;j++) {

        byteArray.append(uuid_arr.at(j));
    }

    quint32 ip = ipAddress.toIPv4Address();
    quint8 ipSub;

    ipSub = ip>>24;
    byteArray.append(ipSub);

    ipSub = ip>>16;
    byteArray.append(ipSub);

    ipSub = ip>>8;
    byteArray.append(ipSub);

    ipSub = ip;
    byteArray.append(ipSub);

    qDebug() << "ipPort: " << ipPort;
    quint8 portSub;

    portSub = ipPort>>8;
    qDebug() << "portSub: " << portSub;
    byteArray.append(portSub);

    portSub = ipPort;
    qDebug() << "portSub: " << portSub;
    byteArray.append(portSub);

    QByteArray seconds;
    seconds.setNum(time.toTime_t());
    byteArray.append(seconds);

    qDebug().noquote().nospace() << "pack(): dateTime: " << time.toString();



    // Header: time (8)
    QByteArray timeArray = seconds;

    time_t unixTime;
    memcpy(&unixTime, seconds, 8);

    QDateTime *dateTime = new QDateTime;
    dateTime->setTime_t((uint) unixTime);

    qDebug().noquote().nospace() << "pack(): dateTime: " << dateTime->toString();



//    byteArray.append(get());
//    byteArray.append(get());
//    byteArray.append(get());
//    byteArray.append(get());
//    byteArray.append(get());
//    byteArray.append(get());
//    byteArray.append(get());



    /*
     *
        uuid(QUuid::createUuid()),
        ipAddress("127.0.0.1"),
        ipPort(TCP),
        time(QDateTime::currentDateTime()),
        headType(0),
        headSize(0),
        headData(),
        ciType(0),
        rootCIC(),
        ciSize(0),
        CICBricks(),
        appType(0),
        appSize(0),
        appData()
        */
}

void CIP::unpack() {

}


QString CIP::toString(QString mode) {

    QString out;

    quint8 byte;
    int b = 0;
    int size;
    QString cipString;

    out  = getService()+"\n";
    out += QString(300, '-')+"\n";

    /*
     *
     * REQUEST
     *
     */
    byte = byteArray.at(b++);
    out += "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out += "\t";
    out += "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out += "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out += "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out += "\t";
    out += "Section: Header\tParameter: request";
    out += "\t";
    out += QString("%1").arg(requestToString(byte));
    out += "\n";


    /*
     *
     * PROFILE
     *
     */
    byte = byteArray.at(b++);
    out += "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out += "\t";
    out += "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out += "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out += "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out += "\t";
    out += "Section: Header\tParameter: profile";
    out += "\t";
    out += QString("%1").arg(profileToString(byte));
    out += "\n";


    /*
     *
     * VERSION
     *
     */
    byte = byteArray.at(b++);
    out += "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out += "\t";
    out += "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out += "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out += "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out += "\t";
    out += "Section: Header\tParameter: version";
    out += "\t";
    out += QString("%1").arg(versionToString(byte));
    out += "\n";




    /*
     *
     * CHANNEL
     *
     */
    byte = byteArray.at(b++);
    out += "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out += "\t";
    out += "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out += "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Header\tParameter: channel";
    out +=  "\t";
    out +=  QString("%1").arg(channelToString(byte));
    out +=  "\n";



    /*
     *
     * UUID
     *
     */

    QByteArray uuidBytes = byteArray.mid(b, 16);
    qDebug() << uuid.toString();

    for(int i=0;i<15;i++) {

        byte = byteArray.at(b++);
        out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
        out +=  "\t";
        out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
        out +=  "\t";
        out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
        out +=  "\t";
        out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
        out +=  "\t";
        out += "Section: Header\tParameter: UUID[" + QString("%1").arg(i).rightJustified(3) + "]";
        out +=  "\n";
    }
    byte = byteArray.at(b++);
    out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
    out +=  "\t";
    out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out +=  "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Header\tParameter: UUID[ 15]";
    out +=  "\t";
    out +=  QString("%1").arg(uuidToString(&uuidBytes));
    out +=  "\n";



    /*
     *
     * IP ADDRESS
     *
     */

    QByteArray ipBytes = byteArray.mid(b, 4);

    for(int i=0;i<3;i++) {

        byte = byteArray.at(b++);
        out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
        out +=  "\t";
        out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
        out +=  "\t";
        out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
        out +=  "\t";
        out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
        out +=  "\t";
        out += "Section: Header\tParameter: IP address[" + QString("%1").arg(i).rightJustified(3) + "]";
        out +=  "\n";
    }
    byte = byteArray.at(b++);
    out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
    out +=  "\t";
    out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out +=  "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Header\tParameter: IP address[  3]";
    out +=  "\t";
    out +=  QString("%1").arg(ipAddressToString(&ipBytes));
    out +=  "\n";






    /*
     *
     * IP PORT
     *
     */

    QByteArray portBytes = byteArray.mid(b, 2);

    byte = byteArray.at(b++);
    out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out +=  "\t";
    out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out +=  "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out += "Section: Header\tParameter: IP port[0]";
    out +=  "\n";

    byte = byteArray.at(b++);

    out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
    out +=  "\t";
    out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out +=  "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Header\tParameter: IP port[1]";
    out +=  "\t";
    out +=  QString("%1").arg(ipPortToString(&portBytes));
    out +=  "\n";


    /*
     *
     * TIME
     *
     */

    QByteArray timeArray = byteArray.mid(b, 8);

    for(int i=0;i<7;i++) {

        byte = byteArray.at(b++);
        out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
        out +=  "\t";
        out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
        out +=  "\t";
        out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
        out +=  "\t";
        out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
        out +=  "\t";
        out += "Section: Header\tParameter: time[" + QString("%1").arg(i).rightJustified(3) + "]";
        out +=  "\n";
    }
    byte = byteArray.at(b++);
    out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
    out +=  "\t";
    out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out +=  "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Header\tParameter: IP address[  3]";
    out +=  "\t";
    out +=  QString("%1").arg(timeToString(&timeArray));
    out +=  "\n";



//    // Header: port number (2)
//    QByteArray ipPort = byteArray.mid(b, 2);
//    b += 2;
//    quint16 portNum;
//    memcpy(&portNum, ipPort, 2);
//    qDebug().noquote().nospace() << QString("%1").arg(b-2).rightJustified(4) << " Header: port number: " << ntohs(portNum);


//    // Header: time (8)
//    QByteArray timeArray = byteArray.mid(b, 8);
//    b += 8;
//    time_t unixTime;
//    memcpy(&unixTime, timeArray, 8);

//    QDateTime *dateTime = new QDateTime;
//    dateTime->setTime_t((uint) unixTime);

////        qDebug() << "Header: unixTime: " << unixTime;
//    qDebug().noquote().nospace() << QString("%1").arg(b-8).rightJustified(4) << " Header: dateTime: " << dateTime->toString();

//    // Header: type (1)
//    byte = byteArray.at(b++);

//    switch (byte) {
//    case 0:
//        cipString = "HEADER_TYPE_OK (HEADER_TYPE_RZV)";
//        break;
//    case 1:
//        cipString = "HEADER_TYPE_ERROR";
//        break;
//    default:
//        cipString = "undefined";
//        break;
//    }
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) <<  " Header: type: " << byte << " : " <<  cipString;

//    // Header: size (1) and data
//    byte = byteArray.at(b++);
//    qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: size: " << byte;

//    if(cipString == "HEADER_TYPE_ERROR" && byte == 3) {

//        QString errorCategory = "";

//        // ERROR_CATEGORY
//        byte = byteArray.at(b++);

//        switch (byte) {
//        case 0:
//            cipString = "ERROR_CATEGORY_NONE (unexpected)";
//            break;
//        case 1:
//            cipString = "CIP_FORMAT_ERROR";
//            errorCategory = "CIP_FORMAT_ERROR";
//            break;
//        default:
//            cipString = "undefined";
//            break;
//        }
//        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: ERROR_CATEGORY: " << byte << " : " <<  cipString;

//        // ERROR_PRIORITY
//        byte = byteArray.at(b++);

//        switch (byte) {
//        case 0:
//            cipString = "ERROR_PRIORITY_NONE (unexpected)";
//            break;
//        case 1:
//            cipString = "ERROR_PRIORITY_DEBUG";
//            break;
//        case 2:
//            cipString = "ERROR_PRIORITY_INFO";
//            break;
//        case 3:
//            cipString = "ERROR_PRIORITY_NOTICE";
//            break;
//        case 4:
//            cipString = "ERROR_PRIORITY_CRITICAL";
//            break;
//        case 5:
//            cipString = "ERROR_PRIORITY_ALERT";
//            break;
//        case 6:
//            cipString = "ERROR_PRIORITY_EMERGENCY";
//            break;
//        default:
//            cipString = "undefined";
//            break;
//        }
//        qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: ERROR_PRIORITY: " << byte << " : " <<  cipString;

//        if(errorCategory == "CIP_FORMAT_ERROR") {

//            // CIP_FORMAT_ERROR_ENUM
//            byte = byteArray.at(b++);

//            switch (byte) {
//            case 0:
//                cipString = "CIP_FORMAT_ERROR_NONE (unexpected)";
//                break;
//            case 1:
//                cipString = "CIP_FORMAT_ERROR_OUT_OF_RANGE";
//                break;
//            case 2:
//                cipString = "CIP_FORMAT_ERROR_INCONSISTENT";
//                break;
//            case 3:
//                cipString = "CIP_FORMAT_ERROR_WRONG_PROTOCOL";
//                break;
//            default:
//                cipString = "undefined";
//                break;
//            }
//            qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: CIP_FORMAT_ERROR: " << byte << " : " <<  cipString;

//        }
//        else {
//            qDebug().noquote().nospace() <<  QString("%1").arg(b-1).rightJustified(4) << " Header: CIP_FORMAT_ERROR: " << byte << " : unexpected";

//        }


//    }
//    else {
//        size = byte;
//        for(int i=0; i<size; i++) {
//            byte = byteArray.at(b++);
//            qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Header: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << byte;
//        }
//    }

//    // Contextinformation: type (1)
//    byte = byteArray.at(b++);

//    switch (byte) {
//    case 0:
//        cipString = "CI_TYPE_RZV";
//        break;
//    case 1:
//        cipString = "CI_TYPE_SIMPLE_MATCH";
//        break;
//    default:
//        cipString = "undefined";
//        break;
//    }
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: type: " << byte << " : " <<  cipString;

//    // Contextinformation: root-CIC (2)
//    byte = byteArray.at(b++);
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: root-CIC content: " << byte;
//    byte = byteArray.at(b++);
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: root-CIC mask: " << byte;

//    // Contextinformation: size (1)
//    byte = byteArray.at(b++);
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: size: " << byte;

//    size = byte;
//    for(int i=0; i<size; i++) {
//        byte = byteArray.at(b++);
//        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: CIC[" << QString("%1").arg(i).rightJustified(3) << "] content: " << QString("%1").arg(byte).rightJustified(3);
//        byte = byteArray.at(b++);
//        qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Contextinformation: CIC[" << QString("%1").arg(i).rightJustified(3) << "] mask:    " << QString("%1").arg(byte).rightJustified(3);
//    }

//    // Application: type (1)
//    byte = byteArray.at(b++);

//    switch (byte) {
//    case 0:
//        cipString = "APP_TYPE_RZV";
//        break;
//    case 1:
//        cipString = "APP_TYPE_TEXT";
//        break;
//    case 2:
//        cipString = "APP_TYPE_URL";
//        break;
//    default:
//        cipString = "undefined";
//        break;
//    }
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: type: " << byte << " : " <<  cipString;

//    // Application: size (1) and data
//    byte = byteArray.at(b++);
//    qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: size: " << byte;

//    if(cipString == "APP_TYPE_TEXT" || cipString == "APP_TYPE_URL") {
//        size = byte;
//        for(int i=0; i<size; i++) {
//            byte = byteArray.at(b++);
//            qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << QString("%1").arg(byte).rightJustified(3) << " : " <<  QChar(byte);
//        }
//    }
//    else {
//        size = byte;
//        for(int i=0; i<size; i++) {
//            byte = byteArray.at(b++);
//            qDebug().noquote().nospace() << QString("%1").arg(b-1).rightJustified(4) << " Application data: additional data[" << QString("%1").arg(i).rightJustified(3) << "]: " << QString("%1").arg(byte).rightJustified(3);
//        }
//    }
//}


//    out = "... from CIP::toString(QString mode)\n";
//    out += getService()+"\n";
//    out += getRequest()+"\n";
//    out += "\n";

    return out;
}






quint8 CICBrick::getContent() const
{
    return content;
}

void CICBrick::setContent(const quint8 &value)
{
    content = value;
}

quint8 CICBrick::getMask() const
{
    return mask;
}

void CICBrick::setMask(const quint8 &value)
{
    mask = value;
}
