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

class CiBrick : public QWidget {

public:
    quint8 content, mask, index;
    QBoxLayout *vLayout;
    QLabel *contentLbl;
    QSpinBox *contentSpBx;
    QLabel *maskLbl;
    QSpinBox *maskSpBx;

    void initialize(quint8 c, quint8 m, quint8 ind) {

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
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<CiBrick*> brickElements;

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

    // HEADER DATA SLOTS    
    void setHeaderTypeFromNumber();
    void setHeaderTypeFromEnum();

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

    // CI SIZE SLOTS
    void setCiSizeFromNumber();


    // APPDATA TYPE SLOTS
    void setAppDataTypeFromNumber();
    void setAppDataTypeFromEnum();

    // APPDATA SIZE SLOTS
    void setAppDataSizeFromNumber();



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
    QLabel *headerSizeCommentLbl;
    QLabel *headerSizeToNumLbl;

    void refreshHeaderSizeDisplay();


    // HEADER DATA
    QLabel *headerDataLbl;
    QPushButton *saveHeaderDataBtn;

    // HEADER DATA TYPE OK
    QGroupBox *headerDataTypeOkGBox;
    QGridLayout *headerDataTypeOkLayout;
    QTextEdit *headerDataTypeOkTxtEdt;

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
    QTextEdit *headerDataTypeUndefinedTxtEdt;

    QLabel *headerDataToStringLbl;

    void clearDataTypes();
    void setDataTypeToOk();
    void setDataTypeToError();
    void setDataTypeToUndefined();

    void refreshHeaderDataDisplay();


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


    // CI SIZE
    QLabel *ciSizeLbl;
    QSpinBox *ciSizeSpBox;
    QPushButton *saveCiSizeFromNumberBtn;
    QLabel *ciSizeCommentLbl;
    QLabel *ciSizeToNumLbl;

    void refreshCiSizeDisplay();


    // CICBRICKS DATA
    QLabel *ciDataLbl;
    QPushButton *saveCiDataBtn;

    // CICBRICK TYPE LATIN TEXT
    QGroupBox *rootCicTypeLatinTextGBox;
    QGridLayout *rootCicTypeLatinTextLayout;
    QTextEdit *rootCicTypeLatinTextTxtEdt;

    // CICBRICK TYPE UNDEFINED
    QGroupBox *rootCicTypeUndefinedGBox;
    QGridLayout *rootCicTypeUndefinedLayout;

//    QLabel *rootCicTypeUndefined__0ContentLbl;
//    QSpinBox *rootCicTypeUndefined__0ContentSpBox;
//    QLabel *rootCicTypeUndefined__0ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__0MaskLbl;
//    QSpinBox *rootCicTypeUndefined__0MaskSpBox;
//    QLabel *rootCicTypeUndefined__0MaskCommentLbl;

//    QLabel *rootCicTypeUndefined__1ContentLbl;
//    QSpinBox *rootCicTypeUndefined__1ContentSpBox;
//    QLabel *rootCicTypeUndefined__1ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__1MaskLbl;
//    QSpinBox *rootCicTypeUndefined__1MaskSpBox;
//    QLabel *rootCicTypeUndefined__1MaskCommentLbl;


//    QLabel *rootCicTypeUndefined__2ContentLbl;
//    QSpinBox *rootCicTypeUndefined__2ContentSpBox;
//    QLabel *rootCicTypeUndefined__2ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__2MaskLbl;
//    QSpinBox *rootCicTypeUndefined__2MaskSpBox;
//    QLabel *rootCicTypeUndefined__2MaskCommentLbl;

//    QLabel *rootCicTypeUndefined__3ContentLbl;
//    QSpinBox *rootCicTypeUndefined__3ContentSpBox;
//    QLabel *rootCicTypeUndefined__3ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__3MaskLbl;
//    QSpinBox *rootCicTypeUndefined__3MaskSpBox;
//    QLabel *rootCicTypeUndefined__3MaskCommentLbl;


//    QLabel *rootCicTypeUndefined__4ContentLbl;
//    QSpinBox *rootCicTypeUndefined__4ContentSpBox;
//    QLabel *rootCicTypeUndefined__4ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__4MaskLbl;
//    QSpinBox *rootCicTypeUndefined__4MaskSpBox;
//    QLabel *rootCicTypeUndefined__4MaskCommentLbl;

//    QLabel *rootCicTypeUndefined__5ContentLbl;
//    QSpinBox *rootCicTypeUndefined__5ContentSpBox;
//    QLabel *rootCicTypeUndefined__5ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__5MaskLbl;
//    QSpinBox *rootCicTypeUndefined__5MaskSpBox;
//    QLabel *rootCicTypeUndefined__5MaskCommentLbl;


//    QLabel *rootCicTypeUndefined__6ContentLbl;
//    QSpinBox *rootCicTypeUndefined__6ContentSpBox;
//    QLabel *rootCicTypeUndefined__6ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__6MaskLbl;
//    QSpinBox *rootCicTypeUndefined__6MaskSpBox;
//    QLabel *rootCicTypeUndefined__6MaskCommentLbl;

//    QLabel *rootCicTypeUndefined__7ContentLbl;
//    QSpinBox *rootCicTypeUndefined__7ContentSpBox;
//    QLabel *rootCicTypeUndefined__7ContentCommentLbl;
//    QLabel *rootCicTypeUndefined__7MaskLbl;
//    QSpinBox *rootCicTypeUndefined__7MaskSpBox;
//    QLabel *rootCicTypeUndefined__7MaskCommentLbl;

    QLabel *ciDataToStringLbl;

    void clearRootCicTypes();
    void setRootCicTypeToLatinText();
    void setRootCicTypeToUndefined();

    void refreshCiDataDisplay();


//    // CICBricks TYPE RZV
//    QGroupBox *cICBricksTypeGBox;
//    QGridLayout *headerDataTypeOkLayout;
//    QTextEdit *headerDataTypeOkTxtEdt;








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

    void refreshAppDataSizeDisplay();


    // RAW CIP DATA
    QGridLayout *rawCIPLayout;
    QGroupBox *rawCIPGBox;

    QTextEdit *rawCIPTxtEdt;


    // INTERACTION
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

};

#endif // MAINWINDOW_H
