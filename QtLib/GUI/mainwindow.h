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


    // Context
    QGroupBox *contextGBox;
    QGridLayout *contextLayout;

    // Data
    QGridLayout *dataLayout;
    QGroupBox *dataGBox;

    // Raw CIP
    QGridLayout *rawCIPLayout;
    QGroupBox *rawCIPGBox;
    QTextEdit *rawCIPTxtEdt;


    // GuiInteraction
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

};

#endif // MAINWINDOW_H
