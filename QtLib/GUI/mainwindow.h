#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cip_global.h"
#include "cip.h"

#include <QMainWindow>

#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QScrollArea>
#include <QNetworkSession>
#include <QUuid>
#include <QFileDialog>
#include <QFile>

#include <QtNetwork>

#include "uuid/uuid.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

    void createCIP();

    void openCIP();
    void saveCIP();

    void setRequestFromNumber();
    void setRequestFromEnum();

    void setProfileFromNumber();
    void setProfileFromEnum();

    void setVersionFromNumber();
    void setVersionFromMajor();
    void setVersionFromMinor();

    void setChannelFromNumber();
    void setChannelFromEnum();

    void setIpAddress();

    void setIpPortFromNumber();
    void setIpPortFromEnum();

    void setCurrentTime();

    void setHeaderTypeFromNumber();
    void setHeaderTypeFromEnum();

    // HEADER DATA SLOTS
    void setHeaderDataError0();
    void setHeaderDataError1();
    void setHeaderDataError2();

    void setHeaderDataErrorCategory();
    void setHeaderDataErrorPriority();
    void setHeaderDataError();

    void setHeaderData();


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

    QWidget *guiWidget;
    QScrollArea *guiScrollArea;


    QVBoxLayout *mainLayout;

    // Factory
    QGroupBox *factoryGBox;
    QGridLayout *factoryLayout;

    QLabel *factoryServiceLbl;
    QComboBox *factoryServiceCmbBx;
    QPushButton *createBtn;



    // Files
    QGroupBox *filesGBox;
    QGridLayout *filesLayout;

    QPushButton *openBtn;
    QPushButton *saveBtn;


    // Header
    QGroupBox *headerGBox;
    QGridLayout *headerLayout;


    // SERVICE
    QLabel *serviceLbl;
    QLabel *serviceToNumLbl;
    QLabel *serviceToStringLbl;
    QLabel *serviceSeparatorLbl;

    void refreshServiceDisplay();


    // REQUEST
    QLabel *requestLbl;
    QSpinBox *requestSpBox;
    QPushButton *saveRequestFromNumberBtn;
    QComboBox *requestCmbBx;
    QPushButton *saveRequestFromEnumBtn;
    QLabel *requestToNumLbl;
    QLabel *requestToStringLbl;

    int getIndexForRequestCmbBx();
    void refreshRequestDisplay();


    // PROFILE
    QLabel *profileLbl;
    QSpinBox *profileSpBox;
    QPushButton *saveProfileFromNumberBtn;
    QComboBox *profileCmbBx;
    QPushButton *saveProfileFromEnumBtn;
    QLabel *profileToNumLbl;
    QLabel *profileToStringLbl;

    int getIndexForProfileCmbBx();
    void refreshProfileDisplay();

    // VERSION
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


    // CHANNEL
    QLabel *channelLbl;
    QSpinBox *channelSpBox;
    QPushButton *saveChannelFromNumberBtn;
    QComboBox *channelCmbBx;
    QPushButton *saveChannelFromEnumBtn;
    QLabel *channelToNumLbl;
    QLabel *channelToStringLbl;

    int getIndexForChannelCmbBx();
    void refreshChannelDisplay();


    // UUID
    QLabel *uuidLbl;
    QLabel *uuidCommentLbl;
    QLabel *uuidToStringLbl;

    void refreshUuidDisplay();


    // IP ADDRESS
    QLabel *ipAddressLbl;
    QSpinBox *ipAddressASpBox;
    QSpinBox *ipAddressBSpBox;
    QSpinBox *ipAddressCSpBox;
    QSpinBox *ipAddressDSpBox;
    QPushButton *saveIpAddressBtn;
    QLabel *ipAddressToStringLbl;

    void refreshIpAddressDisplay();


    // IP PORT
    QLabel *ipPortLbl;
    QSpinBox *ipPortSpBox;
    QPushButton *saveIpPortFromNumberBtn;
    QComboBox *ipPortCmbBx;
    QPushButton *saveIpPortFromEnumBtn;
    QLabel *ipPortToNumLbl;
    QLabel *ipPortToStringLbl;

    int getIndexForIpPortCmbBx();
    void refreshIpPortDisplay();

    // TIME
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


    // DATA
    QGridLayout *appDataLayout;
    QGroupBox *appDataGBox;

    // DATA TYPE
    QLabel *appDataTypeLbl;
    QSpinBox *appDataTypeSpBox;
    QPushButton *saveAppDataTypeFromNumberBtn;
    QComboBox *appDataTypeCmbBx;
    QPushButton *saveAppDataTypeFromEnumBtn;
    QLabel *appDataTypeToNumLbl;
    QLabel *appDataTypeToStringLbl;

    int getIndexForAppDataTypeCmbBx();
    void refreshAppDataTypeDisplay();

    // DATA SIZE
    QLabel *appDataSizeLbl;
    QSpinBox *appDataSizeSpBox;
    QPushButton *saveAppDataSizeFromNumberBtn;
    QLabel *appDataSizeCommentLbl;
    QLabel *appDataSizeToNumLbl;

    void refreshAppDataSizeDisplay();


    // Raw CIP
    QGridLayout *rawCIPLayout;
    QGroupBox *rawCIPGBox;
    QTextEdit *rawCIPTxtEdt;


    // GuiInteraction
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

};

#endif // MAINWINDOW_H
