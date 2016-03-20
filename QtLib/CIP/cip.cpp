#include "cip.h"

void CIP::initialize() {

    qDebug() << "initialize() service: " << service;

    switch (service) {

    case Heartbeat:
        setChannel(CI_Matching);
        setRequest(RequestHeartbeat);
        setIpPort(UDP);
        setHeaderType(HeaderTypeOk);
        break;

    case Offer:
        setChannel(CI_Matching);
        setRequest(RequestOffer);
        setIpPort(TCP);
        setHeaderType(HeaderTypeOk);
        break;

    case Request:
        setChannel(CI_Matching);
        setRequest(RequestRequest);
        setIpPort(UDP);
        setHeaderType(HeaderTypeOk);
        break;

    case TcpReply:
        setChannel(CI_Matching);
        setRequest(RequestReply);
        setIpPort(TCP);
        setHeaderType(HeaderTypeError);
        break;

    case UdpReply:
        setChannel(CI_Matching);
        setRequest(RequestReply);
        setIpPort(UDP);
        setHeaderType(HeaderTypeError);
        break;

    default:
        qDebug() << "Error: Initialize with undefined service " << service;
        break;
    }

    qDebug() << "initialize() headerType: " << headerType;
    qDebug() << getHeaderType();

    QString testMessage = "Hello World";
    QVector<quint8> testVector;

    switch(headerType) {

    case HeaderTypeOk:

        setHeadSize(testMessage.size());

        for (int i=0; i<testMessage.size();i++) {
            testVector.append(testMessage.at(i).toLatin1());
        }
        setHeadData(testVector);
        break;

    case HeaderTypeError:

        setHeadSize(3);

        testVector.append(1);
        testVector.append(1);
        testVector.append(1);
        setHeadData(testVector);
        break;

    default:
        qDebug() << "Error: Initialize with undefined headerType " << headerType;
        break;
    }

    qDebug() << "ciType" << ciType;
    qDebug() << "rootCIC content" << rootCIC.getContent();
    qDebug() << "rootCIC mask" << rootCIC.getMask();








    QString ciMessage = "Chill with friends";
    QVector<CICBrick> ciVector;


    setCiSize(ciMessage.size());

    for (int i=0; i<ciMessage.size();i++) {
        ciVector.append(CICBrick(ciMessage.at(i).toLatin1(), 0));
    }
    setCICBricks(ciVector);


    // TEST APPLICATION DATA
    setAppType(AppTypeText);
    QString appMessage = "Have a look and drop in";
    QVector<quint8> apppVector;

    setAppSize(appMessage.size());

    for (int i=0; i<appMessage.size();i++) {
        apppVector.append(appMessage.at(i).toLatin1());
    }
    setAppData(apppVector);

}


/*
 *
 * SERVICE ENUM
 *
 */

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
        setRequest(0);
        break;
    }
}


/*
 *
 * HEADER TYPE ENUM
 *
 */

QString CIP::getHeaderType() const {

    switch (headerType) {

    case HeaderTypeOk:
        return QString("HeaderType::HeaderTypeOk");
    case HeaderTypeError:
        return QString("HeaderType::HeaderTypeError");
    default:
        return QString("Error: Undefined enum HeaderType: %1").arg(headerType);
    }
}

void CIP::setHeaderType(const HeaderType &value)
{
    headerType = value;
}


/*
 *
 * CIP REQUEST
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

    switch (byte) {
    case 0:
        return "Request RZV by convention";
    case 1:
        return "Request::RequestHeartbeat";
    case 2:
        return "Request::RequestOffer (TCP) || Request::RequestRequest (UDP)";
    case 3:
        return "Request::RequestReply";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP PROFILE
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
 * CIP VERSION
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
 * CIP CHANNEL
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

    switch (byte) {
    case 0:
        return "Channel RZV by convention";
    case CI_Matching:
        return "Channel::CI_Matching";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP UUID
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
 * CIP IP ADDRESS
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
 * CIP IP PORT
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

quint16 CIP::ipPortToNumber(QByteArray *bytes) const {
    return (bytes->at(0)<<8) + bytes->at(1);
}

QString CIP::interpreteIpPort(QByteArray *bytes) const {

    switch ((bytes->at(0)<<8) + bytes->at(1)) {
    case TCP:
        return "Ports::TCP";
    case UDP:
        return "Ports::UDP";
    default:
        return "undefined";
    }
}

QString CIP::interpreteIpPort() const {

    switch (ipPort) {
    case TCP:
        return "Ports::TCP";
    case UDP:
        return "Ports::UDP";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP TIME
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

    QDateTime *dateTime = new QDateTime;
    time_t unixTime;
    memcpy(&unixTime, (*bytes), 8);
    dateTime->setTime_t(unixTime);

    return dateTime->toString();
}


/*
 *
 * CIP HEAD TYPE
 *
 */

quint8 CIP::getHeadType() const
{
    return headType;
}

void CIP::setHeadType(const quint8 &value)
{
    headType = value;
}

QString CIP::headTypeToString(quint8 byte) const {

    switch (byte) {
    case HeaderTypeOk:
        return "HeaderType::HeaderTypeOk";
    case HeaderTypeError:
        return "HeaderType::HeaderTypeError";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP HEAD SIZE
 *
 */

quint8 CIP::getHeadSize() const
{
    return headSize;
}

void CIP::setHeadSize(const quint8 &value)
{
    headSize = value;
}


/*
 *
 * CIP HEAD DATA
 *
 */

QVector<quint8> CIP::getHeadData() const
{
    return headData;
}

void CIP::setHeadData(const QVector<quint8> &value)
{
    headData = value;
}

QString CIP::interpreteHeadData(QByteArray *bytes) const {

    QString out;
    out = '"';
    for ( int i=0; i<bytes->size(); i++) {
        out += (bytes->at(i));
    }
    out += '"';

    qDebug() << out;
    return out;
}

QString CIP::interpreteHeadData() const {

    QString out;

    if(headerType==HeaderTypeError) {

        switch (headData.at(1)) {
        case ErrorPriorityNone:
            out += "ErrorPriorityNone ";
            break;
        case ErrorPriorityDebug:
            out += "ErrorPriorityDebug ";
            break;
        case ErrorPriorityInfo:
            out += "ErrorPriorityInfo ";
            break;
        case ErrorPriorityCritical:
            out += "ErrorPriorityCritical ";
            break;
        case ErrorPriorityAlert:
            out += "ErrorPriorityAlert ";
            break;
        case ErrorPriorityEmergency:
            out += "ErrorPriorityEmergency ";
            break;
        default:
            out += "ErrorPriority undefined";
            return out;
        }

        switch (headData.at(0)) {
        case CipFormatError:

            out += "CipFormatError ";

            switch (headData.at(2)) {
            case CipFormatErrorOutOfRange:
                out += "CipFormatErrorOutOfRange ";
                break;
            case CipFormatErrorInconsistent:
                out += "CipFormatErrorInconsistent ";
                break;
            case CipFormatErrorWrongProtocol:
                out += "CipFormatErrorWrongProtocol ";
                break;
            default:
                out += "CipFormatError undefined";
                return out;
            }

            break;
        default:
            out += "ErrorCategory undefined";
            return out;
        }
        return out;
    }
    else {
        QByteArray headDataArray;
        for (int i = 0; i < headData.size(); ++i) {
            headDataArray.append(headData.at(i));
        }
        return interpreteHeadData(&headDataArray);
    }
}


/*
 *
 * CIP CI TYPE
 *
 */

quint8 CIP::getCiType() const
{
    return ciType;
}

void CIP::setCiType(const quint8 &value)
{
    ciType = value;
}

QString CIP::ciTypeToString(quint8 byte) const {

    switch (byte) {
    case CiTypeRZV:
        return "CiType::CiTypeRZV";
        break;
    case CiTypeSimpleMatch:
        return "CiType::CiTypeSimpleMatch";
        break;
    default:
        return "undefined";
    }
}


/*
 *
 * CIP ROOT CIC
 *
 */

CICBrick CIP::getRootCIC() const
{
    return rootCIC;
}

void CIP::setRootCIC(const CICBrick &value)
{
    rootCIC = value;
}

QString CIP::rootCicToString(quint8 byte) const {

    switch (byte) {
    case RootCIC_RZV:
        return "RootCIC_SimpleMatch::RootCIC_RZV";
    case RootCIC_LatinText:
        return "RootCIC_SimpleMatch::RootCIC_LatinText";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP CI SIZE
 *
 */

quint8 CIP::getCiSize() const
{
    return ciSize;
}

void CIP::setCiSize(const quint8 &value)
{
    ciSize = value;
}


/*
 *
 * CIP CIC BRICKS
 *
 */

QVector<CICBrick> CIP::getCICBricks() const
{
    return CICBricks;
}

void CIP::setCICBricks(const QVector<CICBrick> &value)
{
    CICBricks = value;
}

QString CIP::interpreteCICBricks(QByteArray *bytes) const {

    QString out;
    out += '"';

    switch (getRootCIC().getContent()) {
    case RootCIC_LatinText:
        for(int i=0; i<bytes->size();i++) {
            out += QChar(bytes->at(i)).toLatin1();
        }
        out += '"';
        return out;
    default:
        return "undefined";
    }
}

QString CIP::interpreteCICBricks() const {

    QString out;
    out += '"';

    switch (getRootCIC().getContent()) {
    case RootCIC_LatinText:
        for(int i=0; i<getCiSize(); i++) {
            out += QChar(CICBricks.at(i).getContent()).toLatin1();
        }
        out += '"';
        return out;
    default:
        return "undefined";
    }
}


/*
 *
 * CIP APPLICATION TYPE
 *
 */

quint8 CIP::getAppType() const
{
    return appType;
}

void CIP::setAppType(const quint8 &value)
{
    appType = value;
}

QString CIP::appTypeToString(quint8 byte) const {

    switch (byte) {
    case AppTypeRZV:
        return "AppType::AppTypeRZV";
    case AppTypeText:
        return "AppType::AppTypeText";
    case AppTypeUrl:
        return "AppType::AppTypeUrl";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP APPLICATION SIZE
 *
 */

quint8 CIP::getAppSize() const
{
    return appSize;
}

void CIP::setAppSize(const quint8 &value)
{
    appSize = value;
}


/*
 *
 * CIP APPLICATION DATA
 *
 */

QVector<quint8> CIP::getAppData() const
{
    return appData;
}

void CIP::setAppData(const QVector<quint8> &value)
{
    appData = value;
}

QString CIP::interpreteAppData(QByteArray *bytes) const {

    QString out;
    out += '"';

    switch (getAppType()) {
    case AppTypeText:
        for(int i=0; i<bytes->size();i++) {
            out += QChar(bytes->at(i)).toLatin1();
        }
        out += '"';
        return out;
    default:
        return "undefined";
    }
}

QString CIP::interpreteAppData() const {

    QString out;
    out += '"';

    switch (getAppType()) {
    case AppTypeText:
        for(int i=0; i<getAppSize(); i++) {
            out += QChar(appData.at(i)).toLatin1();
        }
        out += '"';
        return out;
    default:
        return "undefined";
    }
}


/*
 *
 * PACK
 *
 */

void CIP::pack() {

    // START HEADER
    byteArray.append(getRequest());
    byteArray.append(getProfile());
    byteArray.append(getVersion());
    byteArray.append(getChannel());

    // UUID
    QByteArray uuid_arr = uuid.toRfc4122();
    for(int j=0; j<16;j++) {
        byteArray.append(uuid_arr.at(j));
    }

    // IP ADDRESS
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

    // IP PORT
    quint8 portSub;

    portSub = ipPort>>8;
    byteArray.append(portSub);
    portSub = ipPort;
    byteArray.append(portSub);

    // TIME
    uint unixTime = time.toTime_t();
    QByteArray seconds;
    int pos = 0;

    for(int j = 0; j < 8; j++) {

        seconds[pos++] = unixTime%256;
        unixTime = unixTime >> 8;
    }
    byteArray.append(seconds);

    // HEADER TYPE
    byteArray.append(getHeadType());

    // HEADER DATA
    quint8 headerSize = getHeadSize();
    byteArray.append(headerSize);

    // HEADER SIZE
    for (int i=0; i<headerSize; i++) {
        byteArray.append(headData.at(i));
    }


    // CI TYPE
    byteArray.append(getCiType());

    // ROOT CIC
    byteArray.append(getRootCIC().getContent());
    byteArray.append(getRootCIC().getMask());

    // CIC BRICKS
    quint8 ciSize = getCiSize();
    byteArray.append(ciSize);

    for (int i=0; i<ciSize; i++) {
        byteArray.append(CICBricks.at(i).getContent());
        byteArray.append(CICBricks.at(i).getMask());
    }


    // APPLICATION TYPE
    byteArray.append(getAppType());

    // APPLICATION SIZE
    quint8 appDataSize = getAppSize();
    byteArray.append(appDataSize);

    // APPLICATION DATA
    for (int i=0; i<appDataSize; i++) {
        byteArray.append(appData.at(i));
    }
}


/*
 *
 * UNPACK
 *
 */

void CIP::unpack() {

}


/*
 *
 * BYTES TO STRING
 *
 */

QString CIP::bytesToString() {

    QString out;

    quint8 byte;
    int b = 0;
    int size;


    /*
     *
     * HEADLINE
     *
     */

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
        out += "Section: Header\tParameter: UUID[" + QString("%1").arg(i).rightJustified(2) + "]";
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
    out +=  "Section: Header\tParameter: UUID[15]";
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
        out += "Section: Header\tParameter: IP address[" + QString("%1").arg(i) + "]";
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
    out +=  "Section: Header\tParameter: IP address[3]";
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
    out +=  QString("%1 ").arg(interpreteIpPort(&portBytes));
    out +=  QString("(%1)").arg(ipPortToNumber(&portBytes));
    out +=  "\n";


    /*
     *
     * TIME
     *
     */

    QByteArray timeArray = byteArray.mid(b, 8);

    for(int i=0;i<8;i++) {

        byte = byteArray.at(b++);

        if (i<7) {
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out += "Section: Header\tParameter: time[" + QString("%1").arg(i) + "]";
            out +=  "\n";
        }
        else {
            out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  "Section: Header\tParameter: time[7]";
            out +=  "\t";
            out +=  QString("%1").arg(timeToString(&timeArray));
            out +=  "\n";
        }
    }


    /*
     *
     * HEAD TYPE
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
    out +=  "Section: Header\tParameter: type";
    out +=  "\t";
    out +=  QString("%1").arg(headTypeToString(byte));
    out +=  "\n";


    /*
     *
     * HEAD SIZE
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
    out +=  "Section: Header\tParameter: size";
    out +=  "\t";
    out +=  QString("%1").arg(byte);
    out +=  "\n";

    size = byte;


    /*
     *
     * HEAD DATA
     *
     */

    QByteArray headDataArray = byteArray.mid(b, size);

    for(int i=0;i<size;i++) {

        byte = byteArray.at(b++);

        if (i != (size-1)) {
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Header\tParameter: data[%1]").arg((i)).rightJustified(3);
            out +=  "\n";
        }
        else {
            out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Header\tParameter: data[%1]").arg((size-1)).rightJustified(3);
            out +=  "\t";
            out +=  QString("%1").arg(interpreteHeadData(&headDataArray));
            out +=  "\n";
        }
    }


    /*
     *
     * CI TYPE
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
    out +=  "Section: Contextinformation\tParameter: type";
    out +=  "\t";
    out +=  QString("%1").arg(ciTypeToString(byte));
    out +=  "\n";


    /*
     *
     * ROOT CIC
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
    out +=  "Section: Contextinformation\tParameter: rootCic[content]";
    out +=  "\t";
    out +=  QString("%1").arg(rootCicToString(byte));
    out +=  "\n";

    byte = byteArray.at(b++);
    out += "Line: " + QString("%1").arg(b-1).rightJustified(4);
    out += "\t";
    out += "Integer: " + QString("%1").arg(byte).rightJustified(3);
    out += "\t";
    out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
    out +=  "\t";
    out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
    out +=  "\t";
    out +=  "Section: Contextinformation\tParameter: rootCic[  mask   ]";
    out +=  "\n";


    /*
     *
     * CI SIZE
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
    out +=  "Section: Contextinformation\tParameter: size";
    out +=  "\t";
    out +=  QString("%1").arg(byte);
    out +=  "\n";

    size = byte;


    /*
     *
     * CIC BRICKS
     *
     */

    QByteArray ciDataArray = byteArray.mid(b, size*2);

    for(int i=0;i<size;i++) {

        byte = byteArray.at(b++);

        if (i != (size-1)) {
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Contextinformation\tParameter: cicBricks[%1][content]").arg((i)).rightJustified(3);
            out +=  "\n";

            byte = byteArray.at(b++);
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Contextinformation\tParameter: cicBricks[%1][  mask   ]").arg((i)).rightJustified(3);
            out +=  "\n";
        }
        else {
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Contextinformation\tParameter: cicBricks[%1][content]").arg((i)).rightJustified(3);
            out +=  "\n";

            byte = byteArray.at(b++);
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Contextinformation\tParameter: cicBricks[%1][  mask   ]").arg((i)).rightJustified(3);
            out +=  "\t";
            out +=  QString("%1").arg(interpreteCICBricks(&ciDataArray));
            out +=  "\n";
        }
    }



    /*
     *
     * APPLICATION DATA TYPE
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
    out +=  "Section: Application\tParameter: type";
    out +=  "\t";
    out +=  QString("%1").arg(appTypeToString(byte));
    out +=  "\n";


    /*
     *
     * APPLICATION DATA SIZE
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
    out +=  "Section: Application\tParameter: size";
    out +=  "\t";
    out +=  QString("%1").arg(byte);
    out +=  "\n";

    size = byte;


    /*
     *
     * APPLICATION DATA
     *
     */

    QByteArray appDataArray = byteArray.mid(b, size);

    for(int i=0;i<size;i++) {

        byte = byteArray.at(b++);

        if (i != (size-1)) {
            out +=  "Line: " + QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Application\tParameter: data[%1]").arg((i)).rightJustified(3);
            out +=  "\n";
        }
        else {
            out += "Line: " +  QString("%1").arg(b-1).rightJustified(4);
            out +=  "\t";
            out +=  "Integer: " + QString("%1").arg(byte).rightJustified(3);
            out +=  "\t";
            out += QString("Hexadecimal: %1").arg(byte, 4, 16, QLatin1Char('0'));
            out +=  "\t";
            out += QString("Binary: %1").arg(byte, 8, 2, QLatin1Char('0'));
            out +=  "\t";
            out +=  QString("Section: Application\tParameter: data[%1]").arg((size-1)).rightJustified(3);
            out +=  "\t";
            out +=  QString("%1").arg(interpreteAppData(&appDataArray));
            out +=  "\n";
        }
    }
    return out;
}


/*
 *
 * CIC BRICK
 *
 */

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
