#include "cip.h"

void CIP::initialize() {

    qDebug() << "initialize() service: " << service;

    switch (service) {

    case Heartbeat:
        setChannel(ChannelSimpleMatching);
        setRequest(RequestHeartbeat);
        setIpPort(UDP);
        setHeaderType(HeaderTypeOk);
        break;

    case Offer:
        setChannel(ChannelSimpleMatching);
        setRequest(RequestOffer);
        setIpPort(TCP);
        setHeaderType(HeaderTypeOk);
        break;

    case Request:
        setChannel(ChannelSimpleMatching);
        setRequest(RequestRequest);
        setIpPort(UDP);
        setHeaderType(HeaderTypeOk);
        break;

    case TcpReply:
        setChannel(ChannelSimpleMatching);
        setRequest(RequestReply);
        setIpPort(TCP);
        setHeaderType(HeaderTypeError);
        break;

    case UdpReply:
        setChannel(ChannelSimpleMatching);
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

        setHeaderSize(testMessage.size());

        for (int i=0; i<testMessage.size();i++) {
            testVector.append(testMessage.at(i).toLatin1());
        }
        setHeaderData(testVector);
        break;

    case HeaderTypeError:

        setHeaderSize(3);

        testVector.append(1);
        testVector.append(1);
        testVector.append(1);
        setHeaderData(testVector);
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
    setAppDataType(AppDataTypeText);
    QString appMessage = "Have a look and drop in";
    QVector<quint8> apppVector;

    setAppDataSize(appMessage.size());

    for (int i=0; i<appMessage.size();i++) {
        apppVector.append(appMessage.at(i).toLatin1());
    }
    setAppData(apppVector);

}

QByteArray CIP::getByteArray() const
{
    return byteArray;
}

void CIP::setByteArray(const QByteArray &value)
{
    byteArray = value;
}


/*
 *
 * SERVICE ENUM
 *
 */

quint8 CIP::getService() const
{
    return (quint8) service;
}

QString CIP::serviceToString() const
{
    
    switch (service) {

    case RZV:
        return QString("Service::RZV");
    case Heartbeat:
        return QString("Service::Heartbeat");
    case Offer:
        return QString("Service::Offer");
    case Request:
        return QString("Service::Request");
    case TcpReply:
        return QString("Service::TcpReply");
    case UdpReply:
        return QString("Service::UdpReply");
    default:
        return QString("Service::Undefined");
    }
}

void CIP::setService(const Service &value)
{
    service = value;

    switch (service) {

    case RZV:
        setRequest(RequestRZV);
        break;

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

    case Undefined:
        break;
    }
}

void CIP::updateService() {
    qDebug() << "CIP::updateService()";

    switch (request) {

    case RequestRZV:
        qDebug() << "RequestRZV";
        setService(RZV);

        return;
    }

    if(ipPort == UDP) {
        qDebug() << "UDP";

        switch (request) {

        case RequestHeartbeat:
            qDebug() << "RequestHeartbeat";
            setService(Heartbeat);

            return;
        case RequestRequest:
            qDebug() << "RequestRequest";
            setService(Request);

            return;
        case RequestReply:
            qDebug() << "RequestReply";
            setService(UdpReply);

            return;
        }
    }

    if(ipPort == TCP) {
        qDebug() << "TCP";

        switch (request) {

        case RequestOffer:
            qDebug() << "RequestOffer";
            setService(Offer);

            return;
        case RequestReply:
            qDebug() << "RequestReply";
            setService(TcpReply);

            return;
        }
    }
    setService(Undefined);
    qDebug() << "setService(Undefined)";
}


/*
 *
 * HEADER TYPE ENUM
 *
 */

//QString CIP::getHeaderType() const {

//    switch (headerType) {

//    case HeaderTypeOk:
//        return QString("HeaderType::HeaderTypeOk");
//    case HeaderTypeError:
//        return QString("HeaderType::HeaderTypeError");
//    default:
//        return QString("Error: Undefined enum HeaderType: %1").arg(headerType);
//    }
//}

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

void CIP::setRequest(const quint8 &value) {
    qDebug() << QString("CIP::setRequest(%1)").arg(value);

    request = value;

    switch (request) {
    case RequestHeartbeat:
        setIpPort(UDP);
    }
}

QString CIP::requestToString(quint8 byte) const {

    switch (byte) {
    case RequestRZV:
        return "Request::RZV (by convention)";
    case RequestHeartbeat:
        return "Request::RequestHeartbeat";
    case 2:
        return "Request::RequestOffer (TCP) || Request::RequestRequest (UDP)";
    case RequestReply:
        return "Request::RequestReply";
    default:
        return "undefined";
    }
}

QString CIP::requestToString() const {

    switch (request) {
    case RequestRZV:
        return "Request::RZV (by convention)";
    case RequestHeartbeat:
        return "Request::RequestHeartbeat";
    case 2:
        if(ipPort == TCP) {
            return "Request::RequestOffer (TCP)";
        }
        if(ipPort == UDP) {
            return "Request::RequestRequest (UDP)";
        }
        return "undefined";
    case RequestReply:
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

    switch (byte) {
    case ProfileRZV:
        return "Profile::RZV (by convention)";
    default:
        return "Profile::ChannelUndefined";
    }
}
QString CIP::profileToString() const {

    switch (profile) {
    case ProfileRZV:
        return "Profile::RZV (by convention)";
    default:
        return "Profile::ChannelUndefined";
    }
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

void CIP::setMajorVersion(const quint8 &value) {
    version = (value<<4) + versionToMinorNumber();
}

void CIP::setMinorVersion(const quint8 &value) {

    version = (versionToMajorNumber()<<4) + value;
}

quint8 CIP::versionToMajorNumber() const {
    return version>>4;
}

quint8 CIP::versionToMajorNumber(quint8 byte) const {
    return byte>>4;
}

quint8 CIP::versionToMinorNumber() const {
    return version%16;
}

quint8 CIP::versionToMinorNumber(quint8 byte) const {
    return byte%16;
}

QString CIP::versionToString() const {

    return QString("%1.%2").arg(version>>4).rightJustified(2).arg(version%16, 2, 10, QLatin1Char('0')).rightJustified(2);
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
    case ChannelRZV:
        return "Channel::RZV (by convention)";
    case ChannelSimpleMatching:
        return "Channel::ChannelSimpleMatching";
    default:
        return "Channel::ChannelUndefined";
    }
}

QString CIP::channelToString() const {

    switch (channel) {
    case ChannelRZV:
        return "Channel::RZV (by convention)";
    case ChannelSimpleMatching:
        return "Channel::ChannelSimpleMatching";
    default:
        return "Channel::ChannelUndefined";
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

QByteArray CIP::uuidToByteArray()
{
    return uuid.toByteArray();
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

QString CIP::uuidToString() const {
    return uuid.toString();
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

QString CIP::ipAddressToString() const {

    return ipAddress.toString();
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

quint16 CIP::ipPortToNumber() const {
    return ipPort;
}

QString CIP::ipPortToString(QByteArray *bytes) const {

    switch ((bytes->at(0)<<8) + bytes->at(1)) {
    case TCP:
        return "Ports::TCP";
    case UDP:
        return "Ports::UDP";
    default:
        return "undefined";
    }
}

QString CIP::ipPortToString() const {

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

QString CIP::timeToString() const {
    return time.toString();
}


/*
 *
 * CIP HEAD TYPE
 *
 */

quint8 CIP::getHeaderType() const
{
    return headerType;
}

void CIP::setHeaderType(const quint8 &value)
{
    headerType = value;
}

QString CIP::headerTypeToString(quint8 byte) const {

    switch (byte) {
    case HeaderTypeOk:
        return "HeaderType::HeaderTypeOk";
    case HeaderTypeError:
        return "HeaderType::HeaderTypeError";
    case HeaderTypeUndefined:
        return "HeaderType::HeaderTypeUndefined";
    default:
        return "undefined";
    }
}

QString CIP::headerTypeToString() const {

    switch (getHeaderType()) {
    case HeaderTypeOk:
        return "HeaderType::HeaderTypeOk";
    case HeaderTypeError:
        return "HeaderType::HeaderTypeError";
    case HeaderTypeUndefined:
        return "HeaderType::HeaderTypeUndefined";
    default:
        return "undefined";
    }
}



/*
 *
 * CIP HEAD SIZE
 *
 */

quint8 CIP::getHeaderSize() const
{
    return headerSize;
}

void CIP::setHeaderSize(const quint8 &value)
{
    headerSize = value;
}


/*
 *
 * CIP HEAD DATA
 *
 */

QVector<quint8> CIP::getHeaderData() const
{
    return headerData;
}


quint8 CIP::getHeaderData(quint8 index) const {
    return (quint8) headerData.at(index);
}

void CIP::setHeaderData(const QVector<quint8> &value)
{
    headerData = value;
}


void CIP::setHeaderData(const quint8 &value, quint8 index)
{
    headerData.replace(index, value);
}

void CIP::truncateHeaderData(quint8 size) {
    headerData.resize(size);
}

QString CIP::interpreteHeaderData(QByteArray *bytes, quint8 size, quint8 type, quint8 channel) const {

    QString out;

    // HeaderTypeOk: default interpretation as characters (end of function)

    switch (channel) {
    case 1:
        switch (type) {
        case 1:

            for ( int i=0; i<size; i++) {
                out += (bytes->at(i));
            }

            qDebug() << out;
            return out;

        default:
            return "undefined type";
        }
    default:
        return interpreteHeaderData(bytes, size);
    }
}

QString CIP::interpreteHeaderData() const {

    QString category, priority, error;

    // HeaderTypeOk: default interpretation as characters

    if(headerType==HeaderTypeError) {

        switch (headerData.at(1)) {
        case ErrorPriorityNone:
            priority = "ErrorPriorityNone";
            break;
        case ErrorPriorityDebug:
            priority = "ErrorPriorityDebug";
            break;
        case ErrorPriorityInfo:
            priority = "ErrorPriorityInfo";
            break;
        case ErrorPriorityNotice:
            priority = "ErrorPriorityNotice";
            break;
        case ErrorPriorityCritical:
            priority = "ErrorPriorityCritical";
            break;
        case ErrorPriorityAlert:
            priority = "ErrorPriorityAlert";
            break;
        case ErrorPriorityEmergency:
            priority = "ErrorPriorityEmergency";
            break;
        default:
            priority = "undefined";
        }

        switch (headerData.at(0)) {
        case CipFormatError:

            category = "CipFormatError";

            switch (headerData.at(2)) {
            case CipFormatErrorOutOfRange:
                error = "CipFormatErrorOutOfRange";
                break;
            case CipFormatErrorInconsistent:
                error = "CipFormatErrorInconsistent";
                break;
            case CipFormatErrorWrongProtocol:
                error = "CipFormatErrorWrongProtocol";
                break;
            default:
                error = "undefined";
            }

            break;
        default:
            category = "undefined";
            error = "undefined";
        }
        return QString("%1 %2 %3").arg(category).arg(priority).arg(error);
    }

    QByteArray headDataArray;
    for (int i = 0; i < headerData.size(); ++i) {
        headDataArray.append(headerData.at(i));
    }
    return interpreteHeaderData(&headDataArray, headerData.size());
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

QString CIP::ciTypeToString() const {

    switch (ciType) {
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

quint8 CIP::getAppDataType() const
{
    return appDataType;
}

void CIP::setAppDataType(const quint8 &value)
{
    appDataType = value;
}

QString CIP::appDataTypeToString(quint8 byte) const {

    switch (byte) {
    case AppDataTypeRZV:
        return "AppDataType::AppDataTypeRZV";
    case AppDataTypeText:
        return "AppDataType::AppDataTypeText";
    case AppDataTypeUrl:
        return "AppDataType::AppDataTypeUrl";
    default:
        return "undefined";
    }
}

QString CIP::appDataTypeToString() const {

    switch (appDataType) {
    case AppDataTypeRZV:
        return "AppDataType::AppDataTypeRZV";
    case AppDataTypeText:
        return "AppDataType::AppDataTypeText";
    case AppDataTypeUrl:
        return "AppDataType::AppDataTypeUrl";
    default:
        return "undefined";
    }
}


/*
 *
 * CIP APPLICATION SIZE
 *
 */

quint8 CIP::getAppDataSize() const
{
    return appDataSize;
}

void CIP::setAppDataSize(const quint8 &value)
{
    appDataSize = value;
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

    switch (getAppDataType()) {
    case AppDataTypeText:
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

    switch (getAppDataType()) {
    case AppDataTypeText:
        for(int i=0; i<getAppDataSize(); i++) {
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

    byteArray.clear();

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
    byteArray.append(getHeaderType());

    // HEADER DATA
    quint8 headerSize = getHeaderSize();
    byteArray.append(headerSize);

    // HEADER SIZE
    for (int i=0; i<headerSize; i++) {
        byteArray.append(headerData.at(i));
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
    byteArray.append(getAppDataType());

    // APPLICATION SIZE
    quint8 appDataSize = getAppDataSize();
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

    quint8 byte;
    int b = 0;
    quint8 size;
    QByteArray tmpArray;
    QString cipString;

    // Header: request (1)
    byte = byteArray.at(b++);
    setRequest(byte);

    // Header: profile (1)
    byte = byteArray.at(b++);
    setProfile(byte);

    // Header: verion (1)
    byte = byteArray.at(b++);
    setVersion(byte);

    // Header: channel (1)
    byte = byteArray.at(b++);
    setChannel(byte);

    // Header: UUID (16)
    tmpArray = byteArray.mid(b, 16);
    b += 16;
    setUuid(QUuid::fromRfc4122(tmpArray));

    // Header: IP address (4)
    tmpArray.clear();
    tmpArray = byteArray.mid(b, 4);
    b += 4;
    in_addr ip;
    memcpy(&ip, tmpArray, 4);

    setIpAddress(QHostAddress(inet_ntoa(ip)));

    // Header: IP port (2)
    tmpArray.clear();
    tmpArray = byteArray.mid(b, 2);
    b += 2;
    ipPort = (tmpArray.at(0)<<8) + tmpArray.at(1);
//    memcpy(&ipPort, tmpArray, 2);


    // Header: time (8)
    tmpArray.clear();
    tmpArray = byteArray.mid(b, 8);
    b += 8;
    time_t unixTime;
    memcpy(&unixTime, tmpArray, 8);

    time.setTime_t((uint) unixTime);

    // Header: type (1)
    byte = byteArray.at(b++);
    setHeaderType(byte);

    // Header: size (1)
    byte = byteArray.at(b++);
    setHeaderSize(byte);
    size = byte;


    // Header Data (size)
    tmpArray.clear();
    tmpArray = byteArray.mid(b, 3);
    b += size;
}


/*
 *
 * VALIDATE CIP
 *
 */

bool CIP::validateByteArray() {

    qDebug() << "byteArray.size(): " << byteArray.size();

    if(byteArray.size() < 42 || byteArray.size() > 1062) {
        return false;
    }




    int size;
    int additionalBytes;
    bool ok;

    // Header: size
    size = 35;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "Header: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return false;
    }
    qDebug() << "Header: size: " << additionalBytes << endl;
    size += additionalBytes;

    // CI: size
    size += 4;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "CI: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return false;
    }
    qDebug() << "CI: size: " << additionalBytes << endl;
    size += additionalBytes*2;

    // Application: size
    size += 2;
    additionalBytes = QString("%1").arg((quint8) byteArray.at(size)).toInt(&ok);
    if(!ok) {
        qDebug() << "Application: size: Cannot convert "<< (quint8) byteArray.at(size) << " to integer!" << endl;
        return false;
    }
    qDebug() << "Application: size: " << additionalBytes << endl;
    size += additionalBytes;


    qDebug() << "byteArray.size(): " << byteArray.size() << endl;
    qDebug() << "size: " << size+1 << endl;
    if (byteArray.size() != size+1) {

        qDebug() << "INVALID: CIP size is not consistent!" << endl;
        return false;
    }


    return true;
}


/*
 *
 * BYTES TO STRING
 *
 */

QString CIP::bytesToString() {
    qDebug() << "CIP::bytesToString()" << endl;

    QString out;

    quint8 byte;
    int b = 0;
    int size;


    /*
     *
     * START
     *
     */

    out = QString(300, '-')+"\n";


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
    qDebug() << "REQUEST";


    /*
     *
     * PROFILE
     *
     */
    qDebug() << "PROFILE";

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
    qDebug() << "VERSION";

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
    out += QString(" (Major: %1").arg(versionToMajorNumber(byte));
    out += QString(" Minor: %1)").arg(versionToMinorNumber(byte));
    out += "\n";


    /*
     *
     * CHANNEL
     *
     */
    qDebug() << "CHANNEL";

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
    out +=  QString("%1 ").arg(ipPortToString(&portBytes));
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
    out +=  QString("%1").arg(headerTypeToString(byte));
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
            out +=  QString("%1").arg(interpreteHeaderData(&headDataArray, size));
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
    out +=  QString("%1").arg(appDataTypeToString(byte));
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



    /*
     *
     * END
     *
     */

    out += QString(300, '-')+"\n";

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
