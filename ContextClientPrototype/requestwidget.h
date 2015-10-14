#ifndef REQUESTWIDGET_H
#define REQUESTWIDGET_H

#include "abstractwidget.h"
#include "abstractwriter.h"
#include "requestreader.h"
#include "requestwriter.h"

#include <uuid/uuid.h>

#include <QPushButton>

class RequestReader;

class RequestWidget : public AbstractWidget
{
    Q_OBJECT

public:
    RequestWidget(QWidget *parent = 0);

    bool loadFile(QString fileName);

    void loadGuiInteraction();

    // Request
    QString getRequestName() const {
        return requestNameLnEd->text();
    }
    void setRequestName(QString name) {
        requestNameLnEd->setText(name);
    }

    QString getRequestCreateDate() const {
        return requestCreateDateLnEd->text();
    }
    void setRequestCreateDate(QString createDate) {
        requestCreateDateLnEd->setText(createDate);
    }

    QString getRequestLanguage() const {
        return requestLanguageLnEd->text();
    }
    void setRequestLanguage(QString language) {
        requestLanguageLnEd->setText(language);
    }


    // Header
    QString getHeaderServiceName() const {
        return headerServiceNameLnEd->text();
    }
    void setHeaderServiceName(QString serviceName) {
        headerServiceNameLnEd->setText(serviceName);
    }

    QString getHeaderService() const {
        return headerServiceLnEd->text();
    }
    void setHeaderService(QString service) {
        headerServiceLnEd->setText(service);
    }

    QString getHeaderVersion() const {
        return headerVersionLnEd->text();
    }
    void setHeaderVersion(QString version) {
        headerVersionLnEd->setText(version);
    }

    QString getHeaderChannel() const {
        return headerChannelLnEd->text();
    }
    void setHeaderChannel(QString channel) {
        headerChannelLnEd->setText(channel);
    }

    QString getHeaderOptionalSize() const {
        return headerOptionalSizeLnEd->text();
    }
    void setHeaderOptionalSize(QString optionalSize) {
        headerOptionalSizeLnEd->setText(optionalSize);
    }

    QString getHeaderIpAddress() const {
        return headerIpAddressLnEd->text();
    }
    void setHeaderIpAddress(QString ipAddress) {
        headerIpAddressLnEd->setText(ipAddress);
    }


    // Datagram
    QString getDatagramListSize() const {
        return datagramListSizeLnEd->text();
    }
    void setDatagramListSize(QString listSize) {
        datagramListSizeLnEd->setText(listSize);
    }

    QString getDatagramType() const {
        return datagramTypeLnEd->text();
    }
    void setDatagramType(QString type) {
        datagramTypeLnEd->setText(type);
    }

public slots:
    void sendContext();

private:

    AbstractWriter *writer;

    RequestReader *reader;

    QVBoxLayout *mainLayout;


    // Request
    QGroupBox *requestGBox;
    QGridLayout *requestLayout;

    QLabel *requestNameLbl;
    QLineEdit *requestNameLnEd;

    QLabel *requestCreateDateLbl;
    QLineEdit *requestCreateDateLnEd;

    QLabel *requestLanguageLbl;
    QLineEdit *requestLanguageLnEd;


    // Header
    QGroupBox *headerGBox;
    QGridLayout *headerLayout;

    QLabel *headerServiceNameLbl;
    QLineEdit *headerServiceNameLnEd;

    QLabel *headerServiceLbl;
    QLineEdit *headerServiceLnEd;

    QLabel *headerVersionLbl;
    QLineEdit *headerVersionLnEd;

    QLabel *headerChannelLbl;
    QLineEdit *headerChannelLnEd;

    QLabel *headerOptionalSizeLbl;
    QLineEdit *headerOptionalSizeLnEd;

    QLabel *headerUuidLbl;
    QLineEdit *headerUuidLnEd;

    QLabel *headerIpAddressLbl;
    QLineEdit *headerIpAddressLnEd;


    // Datagram
    QGroupBox *datagramGBox;
    QGridLayout *datagramLayout;

    QLabel *datagramListSizeLbl;
    QLineEdit *datagramListSizeLnEd;

    QLabel *datagramTypeLbl;
    QLineEdit *datagramTypeLnEd;
};
#endif // REQUESTWIDGET_H

