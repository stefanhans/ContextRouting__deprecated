#include "cip.h"


quint8 CIP::getRequest() const
{
    return request;
}

void CIP::setRequest(const quint8 &value)
{
    request = value;
}

quint8 CIP::getProfile() const
{
    return profile;
}

void CIP::setProfile(const quint8 &value)
{
    profile = value;
}

quint8 CIP::getVersion() const
{
    return version;
}

void CIP::setVersion(const quint8 &value)
{
    version = value;
}

quint8 CIP::getChannel() const
{
    return channel;
}

void CIP::setChannel(const quint8 &value)
{
    channel = value;
}

QUuid CIP::getUuid() const
{
    return uuid;
}

void CIP::setUuid(const QUuid &value)
{
    uuid = value;
}

QHostAddress CIP::getIpAddress() const
{
    return ipAddress;
}

void CIP::setIpAddress(const QHostAddress &value)
{
    ipAddress = value;
}

quint16 CIP::getIpPort() const
{
    return ipPort;
}

void CIP::setIpPort(const quint16 &value)
{
    ipPort = value;
}

QDateTime CIP::getTime() const
{
    return time;
}

void CIP::setTime(const QDateTime &value)
{
    time = value;
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
