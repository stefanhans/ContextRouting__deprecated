#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cip_global.h"
#include "cip.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QGroupBox>

#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>

#include <QUuid>

#include <QFileDialog>
#include <QFile>

#include <QtMath>



class Data : public QWidget {

public:
    quint8 data, index;
    QBoxLayout *vLayout;
    QLabel *dataLbl;
    QSpinBox *dataSpBx;

    Data(quint8 c, quint8 ind) {

        data = c;
        index = ind;

        vLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        dataLbl = new QLabel(QString("[%1] Data: %2").arg(index).arg(data));
        dataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        dataSpBx = new QSpinBox();
        dataSpBx->setFixedSize(60, 30);
        dataSpBx->setRange(0, 255);
        dataSpBx->setValue(data);

        vLayout->addWidget(dataLbl);
        vLayout->addWidget(dataSpBx);

        setLayout(vLayout);
    }

    void update(quint8 c, quint8 ind) {

        data = c;
        index = ind;

        dataLbl->setText(QString("[%1] Data: %2").arg(index).arg(data));
        dataSpBx->setValue(data);
    }

    quint8 update() {
        data = dataSpBx->value();

        return data;
    }

};

class CiBrick : public QWidget {

public:
    quint8 content, mask, index;
    QBoxLayout *vLayout;
    QLabel *contentLbl;
    QSpinBox *contentSpBx;
    QLabel *maskLbl;
    QSpinBox *maskSpBx;

    CiBrick(quint8 c, quint8 m, quint8 ind) {

        content = c;
        mask = m;
        index = ind;

        vLayout = new QBoxLayout(QBoxLayout::LeftToRight);
        contentLbl = new QLabel(QString("[%1] Content: %2").arg(index).arg(content));
        contentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        contentSpBx = new QSpinBox();
        contentSpBx->setFixedSize(60, 30);
        contentSpBx->setRange(0, 255);
        contentSpBx->setValue(content);

        maskLbl = new QLabel(QString("[%1] Mask: %2").arg(index).arg(mask));
        maskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        maskSpBx = new QSpinBox();
        maskSpBx->setFixedSize(60, 30);
        maskSpBx->setRange(0, 255);
        maskSpBx->setValue(mask);

        vLayout->addWidget(contentLbl);
        vLayout->addWidget(contentSpBx);
        vLayout->addWidget(maskLbl);
        vLayout->addWidget(maskSpBx);

        setLayout(vLayout);
    }

    void update(quint8 c, quint8 m, quint8 ind) {

        content = c;
        mask = m;
        index = ind;

        contentLbl->setText(QString("[%1] Content: %2").arg(index).arg(content));
        contentSpBx->setValue(content);

        maskLbl->setText(QString("[%1] Mask: %2").arg(index).arg(mask));
        maskSpBx->setValue(mask);
    }

    void update() {
        content = contentSpBx->value();
        mask = maskSpBx->value();
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QVector<Data*> headerDataElements;
    QVector<CiBrick*> brickElements;    
    QVector<Data*> appDataElements;

public slots:

    // CIP FACTORY SLOTS
    void createCIP();


    // CIP FILES SLOTS
    void openCIP();
    void saveCIP();


    // HEADER REQUEST SLOTS
    void setRequestFromNumber();
    void setRequestFromEnum();

    // HEADER PROFILE SLOTS
    void setProfileFromNumber();
    void setProfileFromEnum();

    // HEADER VERSION SLOTS
    void setVersionFromNumber();
    void setVersionFromMajor();
    void setVersionFromMinor();

    // HEADER CHANNEL SLOTS
    void setChannelFromNumber();
    void setChannelFromEnum();

    // HEADER IP SLOTS
    void setIpAddress();
    void setIpPortFromNumber();
    void setIpPortFromEnum();

    // HEADER TIME SLOTS
    void setCurrentTime();

    // HEADER TYPE SLOTS
    void setHeaderTypeFromNumber();
    void setHeaderTypeFromEnum();

    // HEADER SIZE SLOTS
    void setHeaderSizeFromNumber();

    // HEADER DATA SLOTS
    void setHeaderData();

    void setHeaderDataError0();
    void setHeaderDataError1();
    void setHeaderDataError2();

    void setHeaderDataErrorCategory();
    void setHeaderDataErrorPriority();
    void setHeaderDataError();


    // CI TYPE SLOTS
    void setCiTypeFromNumber();
    void setCiTypeFromEnum();

    // CI ROOT CIC SLOTS
    void setCiRootCicContentFromNumber();
    void setCiRootCicContentFromEnum();

    // CI SIZE SLOTS
    void setCiSizeFromNumber();

    // CI BRICKS SLOTS
    void setCiBricks();


    // APPDATA TYPE SLOTS
    void setAppDataTypeFromNumber();
    void setAppDataTypeFromEnum();

    // APPDATA SIZE SLOTS
    void setAppDataSizeFromNumber();

    // APPDATA SLOTS
    void setAppData();



private:

    CIP *currentCIP = NULL;

    QVector<CiBrick> ciBricks;

    QWidget *guiWidget;
    QScrollArea *guiScrollArea;
    QVBoxLayout *mainLayout;


    // CIP FACTORY
    QGroupBox *factoryGBox;
    QGridLayout *factoryLayout;

    QLabel *factoryServiceLbl;
    QComboBox *factoryServiceCmbBx;
    QPushButton *createBtn;



    // CIP FILRS
    QGroupBox *filesGBox;
    QGridLayout *filesLayout;

    QPushButton *openBtn;
    QPushButton *saveBtn;


    // HEADER
    QGroupBox *headerGBox;
    QGridLayout *headerLayout;


    // HEADER SERVICE
    QLabel *serviceLbl;
    QLabel *serviceToNumLbl;
    QLabel *serviceToStringLbl;
    QLabel *serviceSeparatorLbl;

    void refreshServiceDisplay();


    // HEADER REQUEST
    QLabel *requestLbl;
    QSpinBox *requestSpBox;
    QPushButton *saveRequestFromNumberBtn;
    QComboBox *requestCmbBx;
    QPushButton *saveRequestFromEnumBtn;
    QLabel *requestToNumLbl;
    QLabel *requestToStringLbl;

    int getIndexForRequestCmbBx();
    void refreshRequestDisplay();


    // HEADER PROFILE
    QLabel *profileLbl;
    QSpinBox *profileSpBox;
    QPushButton *saveProfileFromNumberBtn;
    QComboBox *profileCmbBx;
    QPushButton *saveProfileFromEnumBtn;
    QLabel *profileToNumLbl;
    QLabel *profileToStringLbl;

    int getIndexForProfileCmbBx();
    void refreshProfileDisplay();


    // HEADER VERSION
    QLabel *versionLbl;
    QSpinBox *versionSpBox;
    QPushButton *saveVersionFromNumberBtn;
    QSpinBox *versionMajorSpBox;
    QPushButton *saveVersionFromMajorBtn;
    QSpinBox *versionMinorSpBox;
    QPushButton *saveVersionFromMinorBtn;
    QLabel *versionToNumLbl;
    QLabel *versionToStringLbl;

    void refreshVersionDisplay();


    // HEADER CHANNEL
    QLabel *channelLbl;
    QSpinBox *channelSpBox;
    QPushButton *saveChannelFromNumberBtn;
    QComboBox *channelCmbBx;
    QPushButton *saveChannelFromEnumBtn;
    QLabel *channelToNumLbl;
    QLabel *channelToStringLbl;

    int getIndexForChannelCmbBx();
    void refreshChannelDisplay();


    // HEADER UUID
    QLabel *uuidLbl;
    QLabel *uuidCommentLbl;
    QLabel *uuidToStringLbl;

    void refreshUuidDisplay();


    // HEADER IP ADDRESS
    QLabel *ipAddressLbl;
    QSpinBox *ipAddressASpBox;
    QSpinBox *ipAddressBSpBox;
    QSpinBox *ipAddressCSpBox;
    QSpinBox *ipAddressDSpBox;
    QPushButton *saveIpAddressBtn;
    QLabel *ipAddressToStringLbl;

    void refreshIpAddressDisplay();


    // HEADER IP PORT
    QLabel *ipPortLbl;
    QSpinBox *ipPortSpBox;
    QPushButton *saveIpPortFromNumberBtn;
    QComboBox *ipPortCmbBx;
    QPushButton *saveIpPortFromEnumBtn;
    QLabel *ipPortToNumLbl;
    QLabel *ipPortToStringLbl;

    int getIndexForIpPortCmbBx();
    void refreshIpPortDisplay();


    // HEADER TIME
    QLabel *timeLbl;
    QPushButton *setCurrentTimeBtn;
    QLabel *timeToNumLbl;
    QLabel *timeToStringLbl;

    void refreshTimeDisplay();


    // HEADER TYPE
    QLabel *headerTypeLbl;
    QSpinBox *headerTypeSpBox;
    QPushButton *saveHeaderTypeFromNumberBtn;
    QComboBox *headerTypeCmbBx;
    QPushButton *saveHeaderTypeFromEnumBtn;
    QLabel *headerTypeToNumLbl;
    QLabel *headerTypeToStringLbl;

    int getIndexForHeaderTypeCmbBx();
    void refreshHeaderTypeDisplay();


    // HEADER SIZE
    QLabel *headerSizeLbl;
    QSpinBox *headerSizeSpBox;
    QPushButton *saveHeaderSizeFromNumberBtn;
    QLabel *headerSizeToNumLbl;

    quint8 headerOldSize;

    void refreshHeaderSizeDisplay();
    void refreshHeaderSizeDisplay(quint8 size);


    // HEADER DATA
    QLabel *headerDataLbl;
    QPushButton *saveHeaderDataBtn;

    // HEADER DATA TYPE RZV
    QGroupBox *headerDataTypeRZVGBox;
    QGridLayout *headerDataTypeRZVLayout;

    // HEADER DATA TYPE ERROR
    QGroupBox *headerDataTypeErrorGBox;
    QGridLayout *headerDataTypeErrorLayout;

    QLabel *headerDataError0Lbl;
    QSpinBox *headerDataError0SpBox;
    QPushButton *saveheaderDataError0Btn;

    QLabel *headerDataErrorCategoryLbl;
    QComboBox *headerDataErrorCategoryCmbBx;
    QPushButton *saveheaderDataErrorCategoryFromEnumBtn;

    QLabel *headerDataError0ToNumLbl;
    QLabel *headerDataErrorCategoryToEnumLbl;

    int getIndexForHeaderDataErrorCategoryCmbBx();

    QLabel *headerDataError1Lbl;
    QSpinBox *headerDataError1SpBox;
    QPushButton *saveheaderDataError1Btn;

    QLabel *headerDataErrorPriorityLbl;
    QComboBox *headerDataErrorPriorityCmbBx;
    QPushButton *saveheaderDataErrorPriorityFromEnumBtn;

    QLabel *headerDataError1ToNumLbl;
    QLabel *headerDataErrorPriorityToEnumLbl;

    int getIndexForHeaderDataErrorPriorityCmbBx();

    QLabel *headerDataError2Lbl;
    QSpinBox *headerDataError2SpBox;
    QPushButton *saveheaderDataError2Btn;

    QLabel *headerDataErrorLbl;
    QComboBox *headerDataErrorCmbBx;
    QPushButton *saveheaderDataErrorFromEnumBtn;

    QLabel *headerDataError2ToNumLbl;
    QLabel *headerDataErrorToEnumLbl;

    int getIndexForHeaderDataErrorCmbBx();

    // HEADER DATA TYPE UNDEFINED
    QGroupBox *headerDataTypeUndefinedGBox;
    QGridLayout *headerDataTypeUndefinedLayout;

    QLabel *headerDataToStringLbl;

    void clearHeaderDataTypes();
    void setHeaderDataTypeToRZV();
    void setHeaderDataTypeToRZV(quint8 size, quint16 oldSize);
    void setHeaderDataTypeToError();
    void setHeaderDataTypeToUndefined();

    void refreshHeaderDataDisplay();
    void refreshHeaderDataDisplay(quint8 size, quint16 oldSize=256);


    // CI
    QGroupBox *ciGBox;
    QGridLayout *ciLayout;


    // CI TYPE
    QLabel *ciTypeLbl;
    QSpinBox *ciTypeSpBox;
    QPushButton *saveCiTypeFromNumberBtn;
    QComboBox *ciTypeCmbBx;
    QPushButton *saveCiTypeFromEnumBtn;
    QLabel *ciTypeToNumLbl;
    QLabel *ciTypeToStringLbl;

    int getIndexForCiTypeCmbBx();
    void refreshCiTypeDisplay();


    // CI ROOT CIC
    QLabel *ciRootCicContentLbl;
    QSpinBox *ciRootCicContentSpBox;
    QPushButton *saveCiRootCicContentFromNumberBtn;
    QComboBox *ciRootCicContentCmbBx;
    QPushButton *saveCiRootCicContentFromEnumBtn;
    QLabel *ciRootCicToNumLbl;
    QLabel *ciRootCicToStringLbl;

    int getIndexForCiRootCicCmbBx();
    void refreshCiRootCicDisplay();


    // CI SIZE
    QLabel *ciSizeLbl;
    QSpinBox *ciSizeSpBox;
    QPushButton *saveCiSizeFromNumberBtn;
    QLabel *ciSizeToNumLbl;

    quint8 ciOldSize;

    void refreshCiSizeDisplay();


    // CICBRICKS DATA
    QLabel *ciDataLbl;
    QPushButton *saveCiBricksBtn;

    // CICBRICK TYPE LATIN TEXT
    QGroupBox *rootCicTypeLatinTextGBox;
    QGridLayout *rootCicTypeLatinTextLayout;
    QTextEdit *rootCicTypeLatinTextTxtEdt;

    // CICBRICK TYPE UNDEFINED
    QGroupBox *rootCicTypeUndefinedGBox;
    QGridLayout *rootCicTypeUndefinedLayout;

    QLabel *ciDataToStringLbl;

    void clearRootCicTypes();
    void setRootCicTypeToLatinText();
    void setRootCicTypeToUndefined();

    void refreshCiDataDisplay();








    // APP DATA
    QGridLayout *appDataLayout;
    QGroupBox *appDataGBox;

    // APP DATA TYPE
    QLabel *appDataTypeLbl;
    QSpinBox *appDataTypeSpBox;
    QPushButton *saveAppDataTypeFromNumberBtn;
    QComboBox *appDataTypeCmbBx;
    QPushButton *saveAppDataTypeFromEnumBtn;
    QLabel *appDataTypeToNumLbl;
    QLabel *appDataTypeToStringLbl;

    int getIndexForAppDataTypeCmbBx();
    void refreshAppDataTypeDisplay();

    // APP DATA SIZE
    QLabel *appDataSizeLbl;
    QSpinBox *appDataSizeSpBox;
    QPushButton *saveAppDataSizeFromNumberBtn;
    QLabel *appDataSizeCommentLbl;
    QLabel *appDataSizeToNumLbl;

    quint8 appDataOldSize;

    void refreshAppDataSizeDisplay();
    void refreshAppDataSizeDisplay(quint8 size, quint16 oldSize=256);


    // APP DATA
    QLabel *appDataLbl;
    QPushButton *saveAppDataBtn;

    // APP DATA TYPE RZV
    QGroupBox *appDataTypeRZVGBox;
    QGridLayout *appDataTypeRZVLayout;

    // APP DATA TYPE TEXT
    QGroupBox *appDataTypeTextGBox;
    QGridLayout *appDataTypeTextLayout;
    QTextEdit *appDataTypeTextTxtEdt;

    // APP DATA TYPE UNDEFINED
    QGroupBox *appDataTypeUndefinedGBox;
    QGridLayout *appDataTypeUndefinedLayout;

    QLabel *appDataToStringLbl;

    void clearAppDataTypes();
    void setAppDataTypeToRZV();
    void setAppDataTypeToRZV(quint8 size, quint16 oldSize);
    void setAppDataTypeToText();
    void setAppDataTypeToUndefined();

    void refreshAppDataDisplay();
    void refreshAppDataDisplay(quint8 size, quint16 oldSize=256);


    // RAW CIP DATA
    QGridLayout *rawCIPLayout;
    QGroupBox *rawCIPGBox;

    QTextEdit *rawCIPTxtEdt;


    // INTERACTION
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

};

#endif // MAINWINDOW_H
