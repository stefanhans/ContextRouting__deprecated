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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
