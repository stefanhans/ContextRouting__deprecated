#ifndef CRN_H
#define CRN_H

#include "crn_global.h"
#include <QTcpSocket>
#include <QNetworkSession>

#include <QtNetwork>
#include <QObject>


class CRNSHARED_EXPORT CRN : public QObject
{
    Q_OBJECT

public:
    CRN() { tcpSocket = new QTcpSocket(); }

    void show();
    void showLocal();

    void getCIP(QByteArray* byteArray, QString type="rzv", QByteArray* randValues=NULL);

    QString ping();

    QString pingTcp(QString type="rzv", QByteArray* randValues=NULL);

    QString pingMax();

public slots:
    void tcpError( QAbstractSocket::SocketError error );

private:
    QTcpSocket *tcpSocket;
};

#endif // CRN_H
