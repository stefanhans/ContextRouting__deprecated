#ifndef OFFERWIDGET_H
#define OFFERWIDGET_H

#include "abstractwidget.h"
#include "abstractwriter.h"
#include "offerreader.h"
#include "offerwriter.h"

#include <uuid/uuid.h>

#include <QPushButton>

class OfferWidget : public AbstractWidget
{
    Q_OBJECT

public:
    OfferWidget(QWidget *parent = 0);

    bool loadFile(QString fileName);

    void loadGuiInteraction();

    // Offer
    QString getOfferName() const {
        return offerNameLnEd->text();
    }
    void setOfferName(QString name) {
        offerNameLnEd->setText(name);
    }

    QString getOfferCreateDate() const {
        return offerCreateDateLnEd->text();
    }
    void setOfferCreateDate(QString createDate) {
        offerCreateDateLnEd->setText(createDate);
    }

    QString getOfferLanguage() const {
        return offerLanguageLnEd->text();
    }
    void setOfferLanguage(QString language) {
        offerLanguageLnEd->setText(language);
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

    QString getHeaderUuid() const {
        return headerUuidLnEd->text();
    }
    void setHeaderUuid(QString uuid) {
        headerUuidLnEd->setText(uuid);
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

    OfferReader *reader;

    QVBoxLayout *mainLayout;


    // Offer
    QGroupBox *offerGBox;
    QGridLayout *offerLayout;

    QLabel *offerNameLbl;
    QLineEdit *offerNameLnEd;

    QLabel *offerCreateDateLbl;
    QLineEdit *offerCreateDateLnEd;

    QLabel *offerLanguageLbl;
    QLineEdit *offerLanguageLnEd;


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
#endif // OFFERWIDGET_H

