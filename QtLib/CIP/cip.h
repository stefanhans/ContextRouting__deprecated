#ifndef CIP_H
#define CIP_H

#include "cip_global.h"

#include <arpa/inet.h>

#include <QUuid>
#include <QHostAddress>
#include <QDateTime>
#include <QVector>

/*

   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   request (1) |  profile (1)  |  version (1)  |  channel (1)  | |
   |                                                               | |
   |                            UUID (16)                          | |
   |                                                               | |
   |                                                               | fix
   |                          IP address (4)                       | |
   |            IP port (2)        |                               | |
   |                            time (8)                           | |
   |                               |   type (1)   |    size (1)    |---
   | ............................................................  | |
   | .............. additional data up to 255 bytes .............  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+


   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |         root-CIC (2)          |   size (1)    | fix
   | ............................................................  | |
   | .............. additional data up to 510 bytes .............  | dyn
   | .............. i.e. up to 255 CIC-Bricks  ..................  | |
   | ............................................................  | |
   +---------------------------------------------------------------+


   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   type (1)    |   size (1)    | ............................  | fix
   | ............................................................  | |
   | .......... additional data up to 255 bytes (size) ..........  | dyn
   | ............................................................  | |
   +---------------------------------------------------------------+


   NAME         TYPE        SIZE    toString()    to<type>
   ----------------------------------------------------------
   request      enum        1       y              n
   profile      special     1       y              n
   version      special     1       y              toMajor(), toMinor()
   channel      enum        1       y              n
   UUID         special     16      y              toByteArray(), toRfc4122()

   channel      enum        1       y              n

*/

class CIPSHARED_EXPORT CICBrick {

public:

    CICBrick() :
    content(0),
    mask(0) {}

    CICBrick(quint8 content, quint8 mask) :
    content(content),
    mask(mask) {}

    quint8 getContent() const;
    void setContent(const quint8 &value);

    quint8 getMask() const;
    void setMask(const quint8 &value);

private:

    quint8 content;
    quint8 mask;
};

class CIPSHARED_EXPORT CIP
{
    Q_ENUMS(RequestService)

public:

    // HEADER ENUMS
    enum Service { RZV=0, Heartbeat=1, Offer=2, Request=3, TcpReply=4, UdpReply=5, Undefined };
    enum Request { RequestRZV=0, RequestHeartbeat=1, RequestOffer=2, RequestRequest=2, RequestReply=3, RequestUndefined };
    enum Profile { ProfileRZV=0, ProfileUndefined };
    enum Channel { ChannelRZV=0, ChannelSimpleMatching=1, ChannelUndefined };
    enum Ports { TCP=22365, UDP=22366 };

    // DYNAMIC HEADER ENUMS
    enum HeaderType { HeaderTypeOk=0, HeaderTypeError=1, HeaderTypeUndefined };
    enum ErrorCategory { ErrorCategoryNone=0, CipFormatError=1 };
    enum ErrorPriority { ErrorPriorityNone=0, ErrorPriorityDebug=1, ErrorPriorityInfo=2, ErrorPriorityNotice=3, ErrorPriorityCritical=4, ErrorPriorityAlert=5, ErrorPriorityEmergency=6 };
    enum CipFormatErrorEnum { CipFormatErrorNone=0, CipFormatErrorOutOfRange=1, CipFormatErrorInconsistent=2, CipFormatErrorWrongProtocol=3 };

    // CI ENUMS
    enum CiType { CiTypeRZV=0, CiTypeSimpleMatch=1 };
    enum RootCIC_SimpleMatch { RootCIC_RZV=0, RootCIC_LatinText=1 };

    // APP DATA ENUMS
    enum AppDataType { AppDataTypeRZV=0, AppDataTypeText=1, AppDataTypeUrl=2 };


    /*
     * CONSTRUCTORS
     */

    CIP() :
        byteArray(),
        service(RZV),
        request(RZV),
        profile(0),
        version(1),
        channel(0),
        uuid(QUuid::createUuid()),
        ipAddress("127.0.0.1"),
        ipPort(TCP),
        time(QDateTime::currentDateTime()),
        headerType(0),
        headerSize(0),
        headerData(),
        ciType(0),
        rootCIC(),
        ciSize(0),
        CICBricks(),
        appDataType(0),
        appDataSize(0),
        appData()
    {
        initialize();
    }

    CIP(Service service) :
        byteArray(),
        service(service),
        request(RZV),
        profile(0),
        version(1),
        channel(0),
        uuid(QUuid::createUuid()),
        ipAddress("127.0.0.1"),
        ipPort(TCP),
        time(QDateTime::currentDateTime()),
        headerType(0),
        headerSize(0),
        headerData(),
        ciType(1),
        rootCIC(1, 0),
        ciSize(0),
        CICBricks(),
        appDataType(1),
        appDataSize(0),
        appData()
    {
        initialize();
        pack();
    }


    /*
     * SERVICE
     */
    quint8 getService() const;
    void setService(const Service &value);
    QString serviceToString() const;

    void updateService();


    /*
     * REQUEST
     */
    quint8 getRequest() const;
    void setRequest(const quint8 &value);

    QString requestToString(quint8 byte) const;
    QString requestToString() const;


    /*
     * PROFILE
     */
    quint8 getProfile() const;
    void setProfile(const quint8 &value);

    QString profileToString(quint8 byte) const;
    QString profileToString() const;


    /*
     * VERSION
     */
    quint8 getVersion() const;
    void setVersion(const quint8 &value);

    void setMajorVersion(const quint8 &value);
    void setMinorVersion(const quint8 &value);

    QString versionToString(quint8 byte) const;
    QString versionToString() const;

    quint8 versionToMajorNumber(quint8 byte) const;
    quint8 versionToMajorNumber() const;

    quint8 versionToMinorNumber(quint8 byte) const;
    quint8 versionToMinorNumber() const;


    /*
     * CHANNEL
     */
    quint8 getChannel() const;
    void setChannel(const quint8 &value);

    QString channelToString(quint8 byte) const;
    QString channelToString() const;


    /*
     * UUID
     */
    QUuid getUuid() const;
    void setUuid(const QUuid &value);
    QByteArray uuidToByteArray();
    QString uuidToString(QByteArray *bytes) const;
    QString uuidToString() const;


    /*
     * IP ADDRESS
     */
    QHostAddress getIpAddress() const;
    void setIpAddress(const QHostAddress &value);
    QString ipAddressToString(QByteArray *bytes) const;
    QString ipAddressToString() const;


    /*
     * IP PORT
     */
    quint16 getIpPort() const;
    void setIpPort(const quint16 &value);
    quint16 ipPortToNumber(QByteArray *bytes) const;
    quint16 ipPortToNumber() const;
    QString ipPortToString(QByteArray *bytes) const;
    QString ipPortToString() const;


    /*
     * TIME
     */
    QDateTime getTime() const;
    void setTime(const QDateTime &value);
    QString timeToString(QByteArray *bytes) const;
    QString timeToString() const;


    /*
     * DYNAMIC HEADER TYPE
     */
    quint8 getHeaderType() const;
    void setHeaderType(const quint8 &value);
    QString headerTypeToString(quint8 byte) const;
    QString headerTypeToString() const;


    /*
     * DYNAMIC HEADER SIZE
     */
    quint8 getHeaderSize() const;
    void setHeaderSize(const quint8 &value);


    /*
     * DYNAMIC HEADER DATA
     */
    QVector<quint8> getHeaderData() const;
    quint8 getHeaderData(quint8 index) const;
    void setHeaderData(const QVector<quint8> &value);
    void setHeaderData(const QByteArray &value);
    void setHeaderData(const quint8 &value, quint8 index);
    void truncateHeaderData(quint8 size);
    QString interpreteHeaderData(QByteArray *bytes, quint8 size, quint8 type=1, quint8 channel=1) const;
    QString interpreteHeaderData() const;



    /*
     * CI TYPE
     */
    quint8 getCiType() const;
    void setCiType(const quint8 &value);
    QString ciTypeToString(quint8 byte) const;
    QString ciTypeToString() const;


    /*
     * CIP XXX
     */
    CICBrick getRootCIC() const;
    void setRootCIC(const CICBrick &value);
    QString rootCicToString(quint8 byte) const;


    /*
     * CIP XXX
     */
    quint8 getCiSize() const;
    void setCiSize(const quint8 &value);


    /*
     * CIP XXX
     */
    QVector<CICBrick> getCICBricks() const;
    void setCICBricks(const QVector<CICBrick> &value);
    void setCICBricks(const QByteArray &value);
    void setCICBrick(const CICBrick &value, quint8 index);
    void setCICBrickContent(const quint8 &value, quint8 index);
    void setCICBrickMask(const quint8 &value, quint8 index);
    QString interpreteCICBricks(QByteArray *bytes) const;
    QString interpreteCICBricks() const;


    /*
     * APP DATA TYPE
     */
    quint8 getAppDataType() const;
    void setAppDataType(const quint8 &value);
    QString appDataTypeToString(quint8 byte) const;
    QString appDataTypeToString() const;


    /*
     * APP DATA SIZE
     */
    quint8 getAppDataSize() const;
    void setAppDataSize(const quint8 &value);
    void setAppDataSize();


    /*
     * CIP XXX
     */
    QVector<quint8> getAppData() const;
    void setAppData(const QVector<quint8> &value);
    void setAppData(const QByteArray &value);
    void setAppData(const quint8 &value, quint8 index);
    QString interpreteAppData(QByteArray *bytes) const;
    QString interpreteAppData() const;


    /*
     * RAW CIP DATA
     */

    QByteArray getByteArray() const;
    void setByteArray(const QByteArray &value);

    void pack();
    void unpack();

    bool validateByteArray();

    QString bytesToString();

private:

    QByteArray byteArray;
    Service service;

    void initialize();


    /*
     * CIP HEADER
     */    
    quint8 request;
    quint8 profile;
    quint8 version;
    quint8 channel;
    QUuid uuid;
    QHostAddress ipAddress;
    quint16 ipPort;
    QDateTime time;
    quint8 headerType;
    quint8 headerSize;
    QVector<quint8> headerData;


    /*
     * CIP CI
     */    
    quint8 ciType;
    CICBrick rootCIC;
    quint8 ciSize;
    QVector<CICBrick> CICBricks;


    /*
     * CIP APP DATA
     */
    quint8 appDataType;
    quint8 appDataSize;
    QVector<quint8> appData;

};

#endif // CIP_H
