#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    // Initialize headerDataElements
    for(int i=0; i<256; i++) {
        headerDataElements.append(new Data(0, i));
    }

    // Initialize brickElements
    for(int i=0; i<256; i++) {
        brickElements.append(new CiBrick(0, 0, i));
    }

    // Initialize appDataElements
    for(int i=0; i<256; i++) {
        appDataElements.append(new Data(0, i));
    }

    //
    mainLayout = new QVBoxLayout;

    // Files - Fix Layout
    filesLayout = new QGridLayout;

    // Factory - Fix Layout
    factoryLayout = new QGridLayout;

    // Interaction
    interactionLayout = new QVBoxLayout;




    // Factory
    factoryGBox = new QGroupBox("CIP Factory");
    factoryGBox->setLayout(factoryLayout);
    mainLayout->addWidget(factoryGBox);


    // Factory - Service
    factoryServiceLbl = new QLabel(tr("Service"));
    factoryServiceCmbBx = new QComboBox();
    factoryServiceCmbBx->addItem("Heartbeat", 1);
    factoryServiceCmbBx->addItem("Offer", 2);
    factoryServiceCmbBx->addItem("Request", 3);
    factoryServiceCmbBx->addItem("TcpReply", 4);
    factoryServiceCmbBx->addItem("UdpReply", 5);
    factoryServiceLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    factoryServiceLbl->setBuddy(factoryServiceCmbBx);

    createBtn = new QPushButton(tr("New"), this);


    // Files
    filesGBox = new QGroupBox("CIP Files");
    filesGBox->setLayout(filesLayout);
    mainLayout->addWidget(filesGBox);

    openBtn = new QPushButton(tr("Open"), this);
    saveBtn = new QPushButton(tr("Save"), this);




    factoryLayout->setColumnMinimumWidth(0, 50);

    factoryLayout->addWidget(factoryServiceLbl, 0, 0);
    factoryLayout->addWidget(factoryServiceCmbBx, 0, 1);
    factoryLayout->addWidget(createBtn, 0, 2);


    filesLayout->addWidget(openBtn, 0, 0);
    filesLayout->addWidget(saveBtn, 0, 1);






    // Header - Fix Layout
    headerLayout = new QGridLayout;
    headerGBox = new QGroupBox("Header Data");
    headerGBox->setLayout(headerLayout);
    mainLayout->addWidget(headerGBox);

    headerLayout->setColumnStretch(9, 1);

    // SERVICE
    serviceLbl = new QLabel(tr("Service: "));
    serviceLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    serviceSeparatorLbl = new QLabel(QString('-', 60));
    serviceSeparatorLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    serviceToNumLbl = new QLabel();
    serviceToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    serviceToStringLbl = new QLabel();
    serviceToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(serviceLbl, 0, 0);
    headerLayout->addWidget(serviceToNumLbl, 0, 7);
    headerLayout->addWidget(serviceToStringLbl, 0, 8);

    serviceSeparatorLbl = new QLabel(QString(340, '-'));
    serviceSeparatorLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(serviceSeparatorLbl, 1, 0, 1, 9);


    // REQUEST
    requestLbl = new QLabel(tr("Request (1): "));
    requestLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    requestSpBox = new QSpinBox(headerGBox);
    requestSpBox->setFixedSize(180, 30);
    requestSpBox->setRange(0, 255);

    saveRequestFromNumberBtn = new QPushButton(tr("setRequest()"), this);

    requestCmbBx = new QComboBox(headerGBox);
    requestCmbBx->setFixedSize(180*2, 30);
    requestCmbBx->addItem("RequestRZV (0)", 0);
    requestCmbBx->addItem("RequestHeartbeat (1)", 1);
    requestCmbBx->addItem("RequestOffer (2)", 2);
    requestCmbBx->addItem("RequestRequest (2)", 2);
    requestCmbBx->addItem("RequestReply (3)", 3);
    requestCmbBx->addItem("undefined (4-255)", 4);

    saveRequestFromEnumBtn = new QPushButton(tr("setRequest()"), this);

    requestToNumLbl = new QLabel();
    requestToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    requestToStringLbl = new QLabel();
    requestToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(requestLbl, 3, 0);
    headerLayout->addWidget(requestSpBox, 3, 1);
    headerLayout->addWidget(saveRequestFromNumberBtn, 3, 2);
    headerLayout->addWidget(requestCmbBx, 3, 3, 1, 2);
    headerLayout->addWidget(saveRequestFromEnumBtn, 3, 5, 1, 2);
    headerLayout->addWidget(requestToNumLbl, 3, 7);
    headerLayout->addWidget(requestToStringLbl, 3, 8);



    // PROFILE
    profileLbl = new QLabel(tr("Profile (1): "));
    profileLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    profileSpBox = new QSpinBox(headerGBox);
    profileSpBox->setFixedSize(180, 30);
    profileSpBox->setRange(0, 255);

    saveProfileFromNumberBtn = new QPushButton(tr("setProfile()"), this);

    profileCmbBx = new QComboBox(headerGBox);
    profileCmbBx->setFixedSize(180*2, 30);
    profileCmbBx->addItem("ProfileRZV (0)", 0);
    profileCmbBx->addItem("undefined (1-255)", 1);

    saveProfileFromEnumBtn = new QPushButton(tr("setProfile()"), this);

    profileToNumLbl = new QLabel();
    profileToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    profileToStringLbl = new QLabel();
    profileToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(profileLbl, 4, 0);
    headerLayout->addWidget(profileSpBox, 4, 1);
    headerLayout->addWidget(saveProfileFromNumberBtn, 4, 2);
    headerLayout->addWidget(profileCmbBx, 4, 3, 1, 2);
    headerLayout->addWidget(saveProfileFromEnumBtn, 4, 5, 1, 2);
    headerLayout->addWidget(profileToNumLbl, 4, 7);
    headerLayout->addWidget(profileToStringLbl, 4, 8);



    // VERSION
    versionLbl = new QLabel(tr("Version (1): "));
    versionLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    versionSpBox = new QSpinBox(headerGBox);
    versionSpBox->setFixedSize(180, 30);
    versionSpBox->setRange(0, 255);

    saveVersionFromNumberBtn = new QPushButton(tr("setVersion()"), this);

    versionMajorSpBox = new QSpinBox(headerGBox);
    versionMajorSpBox->setFixedSize(180, 30);
    versionMajorSpBox->setRange(0, 15);

    saveVersionFromMajorBtn = new QPushButton(tr("setMajorVersion()"), this);

    versionMinorSpBox = new QSpinBox(headerGBox);
    versionMinorSpBox->setFixedSize(180, 30);
    versionMinorSpBox->setRange(0, 15);

    saveVersionFromMinorBtn = new QPushButton(tr("setMinorVersion()"), this);

    versionToNumLbl = new QLabel();
    versionToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    versionToStringLbl = new QLabel();
    versionToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(versionLbl, 5, 0);
    headerLayout->addWidget(versionSpBox, 5, 1);
    headerLayout->addWidget(saveVersionFromNumberBtn, 5, 2);

    headerLayout->addWidget(versionMajorSpBox, 5, 3);
    headerLayout->addWidget(saveVersionFromMajorBtn, 5, 4);
    headerLayout->addWidget(versionMinorSpBox, 5, 5);
    headerLayout->addWidget(saveVersionFromMinorBtn, 5, 6);
    headerLayout->addWidget(versionToNumLbl, 5, 7);
    headerLayout->addWidget(versionToStringLbl, 5, 8);


    // CHANNEL
    channelLbl = new QLabel(tr("Channel (1): "));
    channelLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    channelSpBox = new QSpinBox(headerGBox);
    channelSpBox->setFixedSize(180, 30);
    channelSpBox->setRange(0, 255);

    saveChannelFromNumberBtn = new QPushButton(tr("setChannel()"), this);

    channelCmbBx = new QComboBox(headerGBox);
    channelCmbBx->setFixedSize(180*2, 30);
    channelCmbBx->addItem("ChannelRZV (0)", 0);
    channelCmbBx->addItem("ChannelSimpleMatching (1)", 1);
    channelCmbBx->addItem("undefined (2-255)", 2);

    saveChannelFromEnumBtn = new QPushButton(tr("setChannel()"), this);

    channelToNumLbl = new QLabel();
    channelToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    channelToStringLbl = new QLabel();
    channelToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(channelLbl, 6, 0);
    headerLayout->addWidget(channelSpBox, 6, 1);
    headerLayout->addWidget(saveChannelFromNumberBtn, 6, 2);
    headerLayout->addWidget(channelCmbBx, 6, 3, 1, 2);
    headerLayout->addWidget(saveChannelFromEnumBtn, 6, 5, 1, 2);
    headerLayout->addWidget(channelToNumLbl, 6, 7);
    headerLayout->addWidget(channelToStringLbl, 6, 8);



    // UUID
    uuidLbl = new QLabel(tr("UUID (16): "));
    uuidLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    uuidCommentLbl = new QLabel(tr("Read Only"));
    uuidCommentLbl->setAlignment(Qt::AlignCenter);
    uuidToStringLbl = new QLabel();
    uuidToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(uuidLbl, 7, 0);
    headerLayout->addWidget(uuidCommentLbl, 7, 1, 1, 7);
    headerLayout->addWidget(uuidToStringLbl, 7, 8);


    // IP ADDRESS
    ipAddressLbl = new QLabel(tr("IP Address (4): "));
    ipAddressLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ipAddressASpBox = new QSpinBox(headerGBox);
    ipAddressASpBox->setFixedSize(180, 30);
    ipAddressASpBox->setRange(0, 255);
    ipAddressBSpBox = new QSpinBox(headerGBox);
    ipAddressBSpBox->setFixedSize(180, 30);
    ipAddressBSpBox->setRange(0, 255);
    ipAddressCSpBox = new QSpinBox(headerGBox);
    ipAddressCSpBox->setFixedSize(180, 30);
    ipAddressCSpBox->setRange(0, 255);
    ipAddressDSpBox = new QSpinBox(headerGBox);
    ipAddressDSpBox->setFixedSize(180, 30);
    ipAddressDSpBox->setRange(0, 255);
    saveIpAddressBtn = new QPushButton(tr("setIpAddress()"), this);
    ipAddressToStringLbl = new QLabel();
    ipAddressToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    headerLayout->addWidget(ipAddressLbl, 8, 0);
    headerLayout->addWidget(ipAddressASpBox, 8, 1);
    headerLayout->addWidget(ipAddressBSpBox, 8, 2);
    headerLayout->addWidget(ipAddressCSpBox, 8, 3);
    headerLayout->addWidget(ipAddressDSpBox, 8, 4);
    headerLayout->addWidget(saveIpAddressBtn, 8, 5, 1, 2);
    headerLayout->addWidget(ipAddressToStringLbl, 8, 8);


    // IP PORT
    ipPortLbl = new QLabel(tr("IP Port (2): "));
    ipPortLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ipPortSpBox = new QSpinBox(headerGBox);
    ipPortSpBox->setFixedSize(180, 30);
    ipPortSpBox->setRange(0, 65535);
    saveIpPortFromNumberBtn = new QPushButton(tr("setIpPort()"), this);

    ipPortCmbBx = new QComboBox(headerGBox);
    ipPortCmbBx->setFixedSize(180*2, 30);
    ipPortCmbBx->addItem("TCP (22365)", 22365);
    ipPortCmbBx->addItem("UDP (22366)", 22366);
    ipPortCmbBx->addItem("undefined", 2);
    saveIpPortFromEnumBtn = new QPushButton(tr("setIpPort()"), this);
    ipPortToNumLbl = new QLabel();
    ipPortToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ipPortToStringLbl = new QLabel();
    ipPortToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    headerLayout->addWidget(ipPortLbl, 9, 0);
    headerLayout->addWidget(ipPortSpBox, 9, 1);
    headerLayout->addWidget(saveIpPortFromNumberBtn, 9, 2);
    headerLayout->addWidget(ipPortCmbBx, 9, 3, 1, 2);
    headerLayout->addWidget(saveIpPortFromEnumBtn, 9, 5, 1, 2);
    headerLayout->addWidget(ipPortToNumLbl, 9, 7);
    headerLayout->addWidget(ipPortToStringLbl, 9, 8);


    // TIME
    timeLbl = new QLabel(tr("Time (8): "));
    timeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setCurrentTimeBtn = new QPushButton(tr("setCurrentTime()"), this);
    timeToNumLbl = new QLabel();
    timeToNumLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    timeToStringLbl = new QLabel();
    timeToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    headerLayout->addWidget(timeLbl, 10, 0);
    headerLayout->addWidget(setCurrentTimeBtn, 10, 1);
    headerLayout->addWidget(timeToNumLbl, 10, 4, 1, 2);
    headerLayout->addWidget(timeToStringLbl, 10, 8);


    // HEADER TYPE
    headerTypeLbl = new QLabel(tr("HeaderType (1): "));
    headerTypeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerTypeSpBox = new QSpinBox(headerGBox);
    headerTypeSpBox->setFixedSize(180, 30);
    headerTypeSpBox->setRange(0, 255);

    saveHeaderTypeFromNumberBtn = new QPushButton(tr("setHeaderType()"), this);

    headerTypeCmbBx = new QComboBox(headerGBox);
    headerTypeCmbBx->setFixedSize(180*2, 30);
    headerTypeCmbBx->addItem("HeaderTypeRZV (0)", 0);
    headerTypeCmbBx->addItem("HeaderTypeError (1)", 1);
    headerTypeCmbBx->addItem("undefined (2-255)", 2);

    saveHeaderTypeFromEnumBtn = new QPushButton(tr("setHeaderType()"), this);

    headerTypeToNumLbl = new QLabel();
    headerTypeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerTypeToStringLbl = new QLabel();
    headerTypeToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(headerTypeLbl, 11, 0);
    headerLayout->addWidget(headerTypeSpBox, 11, 1);
    headerLayout->addWidget(saveHeaderTypeFromNumberBtn, 11, 2);
    headerLayout->addWidget(headerTypeCmbBx, 11, 3, 1, 2);
    headerLayout->addWidget(saveHeaderTypeFromEnumBtn, 11, 5, 1, 2);
    headerLayout->addWidget(headerTypeToNumLbl, 11, 7);
    headerLayout->addWidget(headerTypeToStringLbl, 11, 8);


    // HEADER SIZE
    headerSizeLbl = new QLabel(tr("HeaderSize (1): "));
    headerSizeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerSizeSpBox = new QSpinBox(headerGBox);
    headerSizeSpBox->setFixedSize(180, 30);
    headerSizeSpBox->setRange(0, 255);

    saveHeaderSizeFromNumberBtn = new QPushButton(tr("setHeaderSizeFromNumber()"), this);

    headerSizeToNumLbl = new QLabel();
    headerSizeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(headerSizeLbl, 12, 0);
    headerLayout->addWidget(headerSizeSpBox, 12, 1);
    headerLayout->addWidget(saveHeaderSizeFromNumberBtn, 12, 2);
    headerLayout->addWidget(headerSizeToNumLbl, 12, 7);


    // HEADER DATA

    // HEADER DATA TYPE RZV
    headerDataTypeRZVLayout = new QGridLayout;
    headerDataTypeRZVGBox = new QGroupBox("Header Data Interpretation: No CIP loaded yet");
    headerDataTypeRZVGBox->setLayout(headerDataTypeRZVLayout);
    headerDataTypeRZVGBox->hide();

    for(int i=0; i<256; i++) {
        headerDataTypeRZVLayout->addWidget(headerDataElements.at(i), qFloor(i/3), i%3);
        headerDataTypeRZVLayout->itemAt(i)->widget()->hide();
    }


    // HEADER DATA TYPE ERROR
    headerDataTypeErrorLayout = new QGridLayout;
    headerDataTypeErrorGBox = new QGroupBox("Header Data Interpretation of HeaderTypeError");
    headerDataTypeErrorGBox->setLayout(headerDataTypeErrorLayout);
    headerDataTypeErrorGBox->hide();

    // ErrorCategory
    headerDataError0Lbl = new QLabel(tr("HeaderData[0]: "));
    headerDataError0Lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataError0SpBox = new QSpinBox(headerDataTypeErrorGBox);
    headerDataError0SpBox->setFixedSize(180, 30);
    headerDataError0SpBox->setRange(0, 255);

    saveheaderDataError0Btn = new QPushButton(tr("setHeaderData[0]"), this);

    headerDataErrorCategoryLbl = new QLabel(tr("ErrorCategory: "));
    headerDataErrorCategoryLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataErrorCategoryCmbBx = new QComboBox(headerDataTypeErrorGBox);
    headerDataErrorCategoryCmbBx->setFixedSize(240, 30);
    headerDataErrorCategoryCmbBx->addItem("ErrorCategoryNone (0)", 0);
    headerDataErrorCategoryCmbBx->addItem("CipFormatError (1)", 1);
    headerDataErrorCategoryCmbBx->addItem("undefined (2-255)", 2);

    saveheaderDataErrorCategoryFromEnumBtn = new QPushButton(tr("setErrorCategory()"), this);

    headerDataError0ToNumLbl = new QLabel();
    headerDataError0ToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerDataErrorCategoryToEnumLbl = new QLabel();
    headerDataErrorCategoryToEnumLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerDataTypeErrorLayout->addWidget(headerDataError0Lbl, 0, 0);
    headerDataTypeErrorLayout->addWidget(headerDataError0SpBox, 0, 1);
    headerDataTypeErrorLayout->addWidget(saveheaderDataError0Btn, 0, 2);
    headerDataTypeErrorLayout->addWidget(headerDataErrorCategoryLbl, 0, 3);
    headerDataTypeErrorLayout->addWidget(headerDataErrorCategoryCmbBx, 0, 4);
    headerDataTypeErrorLayout->addWidget(saveheaderDataErrorCategoryFromEnumBtn, 0, 5);
    headerDataTypeErrorLayout->addWidget(headerDataError0ToNumLbl, 0, 6);
    headerDataTypeErrorLayout->addWidget(headerDataErrorCategoryToEnumLbl, 0, 7);

    // ErrorPriority
    headerDataError1Lbl = new QLabel(tr("HeaderData[1]: "));
    headerDataError1Lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataError1SpBox = new QSpinBox(headerDataTypeErrorGBox);
    headerDataError1SpBox->setFixedSize(180, 30);
    headerDataError1SpBox->setRange(0, 255);

    saveheaderDataError1Btn = new QPushButton(tr("setHeaderData[1]"), this);

    headerDataErrorPriorityLbl = new QLabel(tr("ErrorPriority: "));
    headerDataErrorPriorityLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataErrorPriorityCmbBx = new QComboBox(headerDataTypeErrorGBox);
    headerDataErrorPriorityCmbBx->setFixedSize(240, 30);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityNone (0)", 0);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityDebug (1)", 1);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityInfo (2)", 2);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityNotice (3)", 3);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityCritical (4)", 4);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityAlert (5)", 5);
    headerDataErrorPriorityCmbBx->addItem("ErrorPriorityEmergency (6)", 6);
    headerDataErrorPriorityCmbBx->addItem("undefined (7-255)", 7);

    saveheaderDataErrorPriorityFromEnumBtn = new QPushButton(tr("setErrorPriority()"), this);

    headerDataError1ToNumLbl = new QLabel("1");
    headerDataError1ToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerDataErrorPriorityToEnumLbl = new QLabel("error");
    headerDataErrorPriorityToEnumLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerDataTypeErrorLayout->addWidget(headerDataError1Lbl, 1, 0);
    headerDataTypeErrorLayout->addWidget(headerDataError1SpBox, 1, 1);
    headerDataTypeErrorLayout->addWidget(saveheaderDataError1Btn, 1, 2);
    headerDataTypeErrorLayout->addWidget(headerDataErrorPriorityLbl, 1, 3);
    headerDataTypeErrorLayout->addWidget(headerDataErrorPriorityCmbBx, 1, 4);
    headerDataTypeErrorLayout->addWidget(saveheaderDataErrorPriorityFromEnumBtn, 1, 5);
    headerDataTypeErrorLayout->addWidget(headerDataError1ToNumLbl, 1, 6);
    headerDataTypeErrorLayout->addWidget(headerDataErrorPriorityToEnumLbl, 1, 7);

    // Error
    headerDataError2Lbl = new QLabel(tr("HeaderData[2]: "));
    headerDataError2Lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataError2SpBox = new QSpinBox(headerDataTypeErrorGBox);
    headerDataError2SpBox->setFixedSize(180, 30);
    headerDataError2SpBox->setRange(0, 255);

    saveheaderDataError2Btn = new QPushButton(tr("setHeaderData[2]"), this);

    headerDataErrorLbl = new QLabel(tr("Error: "));
    headerDataErrorLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerDataErrorCmbBx = new QComboBox(headerDataTypeErrorGBox);
    headerDataErrorCmbBx->setFixedSize(240, 30);
    headerDataErrorCmbBx->addItem("CipFormatErrorNone (0)", 0);
    headerDataErrorCmbBx->addItem("CipFormatErrorOutOfRange (1)", 1);
    headerDataErrorCmbBx->addItem("CipFormatErrorInconsistent (2)", 2);
    headerDataErrorCmbBx->addItem("CipFormatErrorWrongProtocol (3)", 3);
    headerDataErrorCmbBx->addItem("undefined (4-255)", 4);

    saveheaderDataErrorFromEnumBtn = new QPushButton(tr("setError()"), this);

    headerDataError2ToNumLbl = new QLabel("1");
    headerDataError2ToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerDataErrorToEnumLbl = new QLabel("error");
    headerDataErrorToEnumLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerDataTypeErrorLayout->addWidget(headerDataError2Lbl, 2, 0);
    headerDataTypeErrorLayout->addWidget(headerDataError2SpBox, 2, 1);
    headerDataTypeErrorLayout->addWidget(saveheaderDataError2Btn, 2, 2);
    headerDataTypeErrorLayout->addWidget(headerDataErrorLbl, 2, 3);
    headerDataTypeErrorLayout->addWidget(headerDataErrorCmbBx, 2, 4);
    headerDataTypeErrorLayout->addWidget(saveheaderDataErrorFromEnumBtn, 2, 5);
    headerDataTypeErrorLayout->addWidget(headerDataError2ToNumLbl, 2, 6);
    headerDataTypeErrorLayout->addWidget(headerDataErrorToEnumLbl, 2, 7);

    // HEADER DATA TYPE UNDEFINED
    headerDataTypeUndefinedLayout = new QGridLayout;
    headerDataTypeUndefinedGBox = new QGroupBox("Header Data Interpretation: No CIP loaded yet");

    headerDataTypeUndefinedGBox->setLayout(headerDataTypeUndefinedLayout);
    headerDataTypeUndefinedGBox->show();

    setDataTypeToUndefined();

    headerDataToStringLbl = new QLabel();
    headerDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(headerDataTypeRZVGBox, 13, 0, 1, 7);
    headerLayout->addWidget(headerDataTypeErrorGBox, 13, 0, 1, 7);
    headerLayout->addWidget(headerDataTypeUndefinedGBox, 13, 0, 1, 7);

    headerLayout->addWidget(headerDataToStringLbl, 13, 8);


    headerDataLbl = new QLabel(tr("HeaderData (size): "));
    headerDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerDataLbl->hide();

    saveHeaderDataBtn = new QPushButton(tr("setHeaderData()"), this);
    saveHeaderDataBtn->hide();

    headerLayout->addWidget(headerDataLbl, 14, 0);
    headerLayout->addWidget(saveHeaderDataBtn, 14, 1);





//    // APP DATA TYPE UNDEFINED
//    appDataTypeUndefinedLayout = new QGridLayout;
//    appDataTypeUndefinedGBox = new QGroupBox("Application Data Interpretation of appData Type Undefined");
//    appDataTypeUndefinedGBox->setLayout(appDataTypeUndefinedLayout);

//    for(int i=0; i<256; i++) {
//        appDataTypeUndefinedLayout->addWidget(appDataElements.at(i), qFloor(i/3), i%3);
//    }
//    appDataTypeUndefinedGBox->hide();

//    appDataToStringLbl = new QLabel();
//    appDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    appDataLayout->addWidget(appDataTypeTextGBox, 3, 0, 1, 7);
//    appDataLayout->addWidget(appDataTypeUndefinedGBox, 3, 0, 1, 7);

//    appDataLayout->addWidget(appDataToStringLbl, 3, 8);

//    appDataLbl = new QLabel(tr("Application Data (size): "));
//    appDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    appDataLbl->hide();

//    saveAppDataBtn = new QPushButton(tr("setAppData()"), this);
//    saveAppDataBtn->hide();

//    appDataLayout->addWidget(appDataLbl, 4, 0);
//    appDataLayout->addWidget(saveAppDataBtn, 4, 1);




    // CI
    ciLayout = new QGridLayout;
    ciGBox = new QGroupBox("Contextinformation");
    ciGBox->setLayout(ciLayout);
    mainLayout->addWidget(ciGBox);

    ciLayout->setColumnStretch(9, 1);


    // CI TYPE
    ciTypeLbl = new QLabel(tr("CiType (1): "));
    ciTypeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    ciTypeSpBox = new QSpinBox(ciGBox);
    ciTypeSpBox->setFixedSize(180, 30);
    ciTypeSpBox->setRange(0, 255);

    saveCiTypeFromNumberBtn = new QPushButton(tr("setCiTypeFromNumber()"), this);

    ciTypeCmbBx = new QComboBox(ciGBox);
    ciTypeCmbBx->setFixedSize(180*2, 30);
    ciTypeCmbBx->addItem("CiTypeRZV (0)", 0);
    ciTypeCmbBx->addItem("CiTypeSimpleMatch (1)", 1);
    ciTypeCmbBx->addItem("undefined (2-255)", 2);

    saveCiTypeFromEnumBtn = new QPushButton(tr("setCiTypeFromEnum()"), this);
    saveCiTypeFromEnumBtn->setFixedSize(180*2, 30);

    ciTypeToNumLbl = new QLabel();
    ciTypeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ciTypeToStringLbl = new QLabel();
    ciTypeToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    ciLayout->addWidget(ciTypeLbl, 1, 0);
    ciLayout->addWidget(ciTypeSpBox, 1, 1);
    ciLayout->addWidget(saveCiTypeFromNumberBtn, 1, 2);
    ciLayout->addWidget(ciTypeCmbBx, 1, 3, 1, 2);
    ciLayout->addWidget(saveCiTypeFromEnumBtn, 1, 5, 1, 2);
    ciLayout->addWidget(ciTypeToNumLbl, 1, 7);
    ciLayout->addWidget(ciTypeToStringLbl, 1, 8);


    // CI SIZE
    ciSizeLbl = new QLabel(tr("CiSize (1): "));
    ciSizeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    ciSizeSpBox = new QSpinBox(ciGBox);
    ciSizeSpBox->setFixedSize(180, 30);
    ciSizeSpBox->setRange(0, 255);

    saveCiSizeFromNumberBtn = new QPushButton(tr("setCiSizeFromNumber()"), this);

    ciSizeToNumLbl = new QLabel();
    ciSizeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    ciLayout->addWidget(ciSizeLbl, 2, 0);
    ciLayout->addWidget(ciSizeSpBox, 2, 1);
    ciLayout->addWidget(saveCiSizeFromNumberBtn, 2, 2);
    ciLayout->addWidget(ciSizeToNumLbl, 2, 7);


    // CICBRICK TYPE LATIN TEXT
    rootCicTypeLatinTextLayout = new QGridLayout;
    rootCicTypeLatinTextGBox = new QGroupBox("CICBricks Interpretation of rootCIC Type LatinText");
    rootCicTypeLatinTextGBox->setLayout(rootCicTypeLatinTextLayout);
    rootCicTypeLatinTextTxtEdt = new QTextEdit(rootCicTypeLatinTextGBox);
    rootCicTypeLatinTextTxtEdt->setReadOnly(false);
    rootCicTypeLatinTextGBox->hide();

    rootCicTypeLatinTextLayout->addWidget(rootCicTypeLatinTextTxtEdt, 0, 0);



    // CICBRICK TYPE UNDEFINED
    rootCicTypeUndefinedLayout = new QGridLayout;
    rootCicTypeUndefinedGBox = new QGroupBox("CICBricks Interpretation: No CIP loaded yet");
    rootCicTypeUndefinedGBox->setLayout(rootCicTypeUndefinedLayout);
    rootCicTypeUndefinedGBox->show();

    for(int i=0; i<256; i++) {
        rootCicTypeUndefinedLayout->addWidget(brickElements.at(i), qFloor(i/3), i%3);
        rootCicTypeUndefinedLayout->itemAt(i)->widget()->hide();
    }

    ciDataToStringLbl = new QLabel();
    ciDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ciLayout->addWidget(rootCicTypeLatinTextGBox, 3, 0, 1, 7);
    ciLayout->addWidget(rootCicTypeUndefinedGBox, 3, 0, 1, 7);

    ciLayout->addWidget(ciDataToStringLbl, 3, 8);

    ciDataLbl = new QLabel(tr("CIC-Bricks (size): "));
    ciDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ciDataLbl->hide();

    saveCiBricksBtn = new QPushButton(tr("setCICBricks()"), this);
    saveCiBricksBtn->hide();

    ciLayout->addWidget(ciDataLbl, 4, 0);
    ciLayout->addWidget(saveCiBricksBtn, 4, 1);





    // APPDATA
    appDataLayout = new QGridLayout;
    appDataGBox = new QGroupBox("Application Data");
    appDataGBox->setLayout(appDataLayout);
    mainLayout->addWidget(appDataGBox);

    appDataLayout->setColumnStretch(9, 1);


    // APPDATA TYPE
    appDataTypeLbl = new QLabel(tr("AppDataType (1): "));
    appDataTypeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    appDataTypeSpBox = new QSpinBox(appDataGBox);
    appDataTypeSpBox->setFixedSize(180, 30);
    appDataTypeSpBox->setRange(0, 255);

    saveAppDataTypeFromNumberBtn = new QPushButton(tr("setAppDataTypeFromNumber()"), this);

    appDataTypeCmbBx = new QComboBox(appDataGBox);
    appDataTypeCmbBx->setFixedSize(180*2, 30);
    appDataTypeCmbBx->addItem("AppDataTypeRZV (0)", 0);
    appDataTypeCmbBx->addItem("AppDataTypeText (1)", 1);
    appDataTypeCmbBx->addItem("AppDataTypeUrl (2)", 2);
    appDataTypeCmbBx->addItem("undefined (3-255)", 3);

    saveAppDataTypeFromEnumBtn = new QPushButton(tr("setAppDataTypeFromEnum()"), this);
    saveAppDataTypeFromEnumBtn->setFixedSize(180*2, 30);

    appDataTypeToNumLbl = new QLabel();
    appDataTypeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    appDataTypeToStringLbl = new QLabel();
    appDataTypeToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    appDataLayout->addWidget(appDataTypeLbl, 1, 0);
    appDataLayout->addWidget(appDataTypeSpBox, 1, 1);
    appDataLayout->addWidget(saveAppDataTypeFromNumberBtn, 1, 2);
    appDataLayout->addWidget(appDataTypeCmbBx, 1, 3, 1, 2);
    appDataLayout->addWidget(saveAppDataTypeFromEnumBtn, 1, 5, 1, 2);
    appDataLayout->addWidget(appDataTypeToNumLbl, 1, 7);
    appDataLayout->addWidget(appDataTypeToStringLbl, 1, 8);


    // APPDATA SIZE
    appDataSizeLbl = new QLabel(tr("AppDataSize (1): "));
    appDataSizeLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    appDataSizeSpBox = new QSpinBox(appDataGBox);
    appDataSizeSpBox->setFixedSize(180, 30);
    appDataSizeSpBox->setRange(0, 255);

    saveAppDataSizeFromNumberBtn = new QPushButton(tr("setAppDataSizeFromNumber()"), this);

    appDataSizeToNumLbl = new QLabel();
    appDataSizeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    appDataLayout->addWidget(appDataSizeLbl, 2, 0);
    appDataLayout->addWidget(appDataSizeSpBox, 2, 1);
    appDataLayout->addWidget(saveAppDataSizeFromNumberBtn, 2, 2);
    appDataLayout->addWidget(appDataSizeToNumLbl, 2, 7);


    // APP DATA TYPE UNDEFINED
    appDataTypeUndefinedLayout = new QGridLayout;
    appDataTypeUndefinedGBox = new QGroupBox("Application Data Interpretation: No CIP loaded yet");
    appDataTypeUndefinedGBox->setLayout(appDataTypeUndefinedLayout);
    appDataTypeUndefinedGBox->show();

    for(int i=0; i<256; i++) {
        appDataTypeUndefinedLayout->addWidget(appDataElements.at(i), qFloor(i/3), i%3);
        appDataTypeUndefinedLayout->itemAt(i)->widget()->hide();
    }


    // APP DATA TYPE TEXT
    appDataTypeTextLayout = new QGridLayout;
    appDataTypeTextGBox = new QGroupBox("Application Data Interpretation of appData Type Text");
    appDataTypeTextGBox->setLayout(appDataTypeTextLayout);
    appDataTypeTextTxtEdt = new QTextEdit(appDataTypeTextGBox);
    appDataTypeTextTxtEdt->setReadOnly(false);
    appDataTypeTextGBox->hide();

    appDataTypeTextLayout->addWidget(appDataTypeTextTxtEdt, 0, 0);


    // APP DATA TYPE TEXT

    appDataToStringLbl = new QLabel();
    appDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    appDataLayout->addWidget(appDataTypeTextGBox, 3, 0, 1, 7);
    appDataLayout->addWidget(appDataTypeUndefinedGBox, 3, 0, 1, 7);

    appDataLayout->addWidget(appDataToStringLbl, 3, 8);

    appDataLbl = new QLabel(tr("Application Data (size): "));
    appDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    appDataLbl->hide();

    saveAppDataBtn = new QPushButton(tr("setAppData()"), this);
    saveAppDataBtn->hide();

    appDataLayout->addWidget(appDataLbl, 4, 0);
    appDataLayout->addWidget(saveAppDataBtn, 4, 1);




    // Raw CIP Layout
    rawCIPLayout = new QGridLayout;
    rawCIPGBox = new QGroupBox("Raw CIP Data");
    rawCIPGBox->setLayout(rawCIPLayout);
    mainLayout->addWidget(rawCIPGBox);

    rawCIPTxtEdt = new QTextEdit(rawCIPGBox);
    rawCIPTxtEdt->setStyleSheet ("font: 9pt; Monospace;");
    rawCIPTxtEdt->setReadOnly(true);    
    rawCIPTxtEdt->setFixedHeight(1000);
    rawCIPTxtEdt->setPlainText("No CIP loaded yet");

    rawCIPLayout->addWidget(rawCIPTxtEdt, 0, 0);


//    mainLayout->addStretch();

    interactionGBox = new QGroupBox(tr("Interaction"));
    interactionGBox->setLayout(interactionLayout);
    mainLayout->addWidget(interactionGBox);


    // GUI - Widget
    guiWidget = new QWidget;
    guiWidget->setLayout(mainLayout);

    // GUI - ScrollArea
    guiScrollArea = new QScrollArea;
    guiScrollArea->setWidget(guiWidget);
    guiScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setWidgetResizable(true);

    setCentralWidget(guiScrollArea);
    showMaximized();


    // CIP CONNECTS
    connect(createBtn, &QAbstractButton::clicked, this, &MainWindow::createCIP);

    connect(openBtn, &QAbstractButton::clicked, this, &MainWindow::openCIP);
    connect(saveBtn, &QAbstractButton::clicked, this, &MainWindow::saveCIP);


    // FIX HEADER CONNECTS
    connect(saveRequestFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setRequestFromNumber);
    connect(saveRequestFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setRequestFromEnum);

    connect(saveProfileFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setProfileFromNumber);
    connect(saveProfileFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setProfileFromEnum);

    connect(saveVersionFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setVersionFromNumber);
    connect(saveVersionFromMajorBtn, &QAbstractButton::clicked, this, &MainWindow::setVersionFromMajor);
    connect(saveVersionFromMinorBtn, &QAbstractButton::clicked, this, &MainWindow::setVersionFromMinor);

    connect(saveChannelFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setChannelFromNumber);
    connect(saveChannelFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setChannelFromEnum);

    connect(saveIpAddressBtn, &QAbstractButton::clicked, this, &MainWindow::setIpAddress);

    connect(saveIpPortFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setIpPortFromNumber);
    connect(saveIpPortFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setIpPortFromEnum);

    connect(setCurrentTimeBtn, &QAbstractButton::clicked, this, &MainWindow::setCurrentTime);


    // DYNAMIC HEADER CONNECTS
    connect(saveHeaderTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromNumber);
    connect(saveHeaderTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromEnum);

    connect(saveHeaderSizeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderSizeFromNumber);

    connect(saveheaderDataError0Btn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataError0);
    connect(saveheaderDataErrorCategoryFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataErrorCategory);

    connect(saveheaderDataError1Btn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataError1);
    connect(saveheaderDataErrorPriorityFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataErrorPriority);

    connect(saveheaderDataError2Btn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataError2);
    connect(saveheaderDataErrorFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderDataError);

    connect(saveHeaderDataBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderData);


    // CI CONNECTS
    connect(saveCiTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setCiTypeFromNumber);
    connect(saveCiTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setCiTypeFromEnum);

    connect(saveCiSizeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setCiSizeFromNumber);

    connect(saveCiBricksBtn, &QAbstractButton::clicked, this, &MainWindow::setCiBricks);


    // APPDATA CONNECTS
    connect(saveAppDataTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataTypeFromNumber);
    connect(saveAppDataTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataTypeFromEnum);

    connect(saveAppDataSizeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataSizeFromNumber);

    connect(saveAppDataBtn, &QAbstractButton::clicked, this, &MainWindow::setAppData);

}

MainWindow::~MainWindow()
{

}

void MainWindow::createCIP() {
    qDebug() << "createCIP()";

    int service = factoryServiceCmbBx->currentData().toInt();
    qDebug() << service;

    switch (service) {
    case CIP::Heartbeat:
        qDebug() << "new CIP(CIP::Heartbeat)";
        currentCIP = new CIP(CIP::Heartbeat);
        break;
    case CIP::Offer:
        currentCIP = new CIP(CIP::Offer);
        break;
    case CIP::Request:
        currentCIP = new CIP(CIP::Request);
        break;
    case CIP::TcpReply:
        currentCIP = new CIP(CIP::TcpReply);
        break;
    case CIP::UdpReply
    :
        currentCIP = new CIP(CIP::UdpReply);
        break;
    default:
        break;
    }

    // SERVICE
    serviceToNumLbl->setText(QString("%1").arg(currentCIP->getService()));
    serviceToStringLbl->setText(currentCIP->serviceToString());

    // REQUEST
    requestToNumLbl->setText(QString("%1").arg(currentCIP->getRequest()));
    requestToStringLbl->setText(currentCIP->requestToString());
    requestSpBox->setValue(currentCIP->getRequest());
    requestCmbBx->setCurrentIndex(getIndexForRequestCmbBx());

    // PROFILE
    profileToNumLbl->setText(QString("%1").arg(currentCIP->getProfile()));
    profileToStringLbl->setText(currentCIP->profileToString());
    profileSpBox->setValue(currentCIP->getProfile());
    profileCmbBx->setCurrentIndex(getIndexForProfileCmbBx());

    // VERSION
    versionToNumLbl->setText(QString("%1").arg(currentCIP->getVersion()));
    versionToStringLbl->setText(currentCIP->versionToString());
    versionSpBox->setValue(currentCIP->getVersion());
    versionMajorSpBox->setValue(currentCIP->versionToMajorNumber());
    versionMinorSpBox->setValue(currentCIP->versionToMinorNumber());

    // CHANNEL
    channelToNumLbl->setText(QString("%1").arg(currentCIP->getChannel()));
    channelToStringLbl->setText(currentCIP->channelToString());
    channelSpBox->setValue(currentCIP->getChannel());
    channelCmbBx->setCurrentIndex(getIndexForChannelCmbBx());

    // UUID
    refreshUuidDisplay();
    refreshIpAddressDisplay();
    refreshIpPortDisplay();
    refreshTimeDisplay();

    refreshHeaderTypeDisplay();
    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    // CI DISPLAY
    refreshCiTypeDisplay();
    refreshCiSizeDisplay();
    refreshCiDataDisplay();

    // APPDATE DISPLAY
    refreshAppDataTypeDisplay();
    refreshAppDataSizeDisplay();
    refreshAppDataDisplay();

    // RAW CIP
    rawCIPTxtEdt->setPlainText(QString("New CIP created with argument %1 (%2)\n%3")
                               .arg(currentCIP->serviceToString())
                               .arg(currentCIP->getService())
                               .arg(currentCIP->bytesToString()));
}


void MainWindow::openCIP() {
    qDebug() << "openCIP()";


    QString infilePath = QFileDialog::getOpenFileName(this,
        tr("Open CIP"), "/home/stefan/Development/CRN_QtLib/CIPs", tr("CIP Files (*.cip);;All files (*)"));


    QFile infile(infilePath);
    if (!infile.open(QIODevice::ReadOnly)) {

        qDebug() << "Error: openCIP() can not read " << infilePath << endl;
        qDebug() << infile.errorString() << endl;

        return;
    }


    if(currentCIP == NULL) {
        currentCIP = new CIP();
    }

    qDebug() << "setByteArray()";
    currentCIP->setByteArray(infile.readAll());
    qDebug() << "infile.close()";

    if ( ! currentCIP->validateByteArray()) {
        qDebug() << "Not a valid CIP!";
        infile.close();
        return;
    }

    currentCIP->unpack();
    infile.close();

    currentCIP->updateService();

    refreshServiceDisplay();
    refreshRequestDisplay();
    refreshProfileDisplay();
    refreshVersionDisplay();
    refreshChannelDisplay();
    refreshUuidDisplay();
    refreshIpAddressDisplay();
    refreshIpPortDisplay();
    refreshTimeDisplay();
    refreshHeaderTypeDisplay();
    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    // CI DISPLAY
    refreshCiTypeDisplay();
    refreshCiSizeDisplay();
    refreshCiDataDisplay();

    // APPDATE DISPLAY
    refreshAppDataTypeDisplay();
    refreshAppDataSizeDisplay();
    refreshAppDataDisplay();


    qDebug() << "setPlainText()";
    rawCIPTxtEdt->setPlainText(QString("CIP loaded from file %1\n%2")
                               .arg(infilePath)
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::saveCIP() {
    qDebug() << "saveCIP()";

    QString outfilePath = QFileDialog::getSaveFileName(this,
        tr("Save CIP"), "/home/stefan/Development/CRN_QtLib/CIPs", tr("CIP Files (*.cip);;All files (*)"));


    qDebug() << "outfilePath: " << outfilePath;


    QFile outfile(outfilePath);
    if (!outfile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {

//        errorStream << "Error: CMD(" << command.join(" ") << ") can not write to file " << outfilePath << endl;
//        errorStream << outfile.errorString() << endl;

        return;
    }
    outfile.write(currentCIP->getByteArray());
    outfile.close();

}


void MainWindow::refreshServiceDisplay() {
    qDebug() << "MainWindow::getIndexForRequestCmbBx()";

        serviceToNumLbl->setText(QString("%1").arg(currentCIP->getService()));
        serviceToStringLbl->setText(currentCIP->serviceToString());

//        serviceToStringLbl->setText(currentCIP->ipPortToString());
}

int MainWindow::getIndexForRequestCmbBx() {
    qDebug() << "MainWindow::getIndexForRequestCmbBx()";

    switch (currentCIP->getRequest()) {

    case 0:
        return 0;

    case 1:
        return 1;
    case 2:
        if(currentCIP->getIpPort() == CIP::TCP) {
            return 2;
        }

        if(currentCIP->getIpPort() == CIP::UDP) {
            return 3;
        }

    case 3:
        return 4;

    default:
        return 5;
    }
}

void MainWindow::refreshRequestDisplay() {
    qDebug() << "refreshRequestDisplay()";

    requestSpBox->setValue(currentCIP->getRequest());
    requestCmbBx->setCurrentIndex(getIndexForRequestCmbBx());
    requestToNumLbl->setText(QString("%1").arg(currentCIP->getRequest()));
    requestToStringLbl->setText(currentCIP->requestToString());
}

void MainWindow::setRequestFromNumber() {
    qDebug() << "setRequestFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setRequest(requestSpBox->value());
    currentCIP->updateService();
    currentCIP->pack();

    refreshServiceDisplay();
    refreshRequestDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setRequestFromNumber() to %1\n%2")
                               .arg(requestCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setRequestFromEnum() {
    qDebug() << "setRequestFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setRequest(requestCmbBx->currentData().toInt());
    if(requestCmbBx->currentText() == "RequestOffer (2)") {
        currentCIP->setIpPort(CIP::TCP);
    }
    if(requestCmbBx->currentText() == "RequestRequest (2)") {
        currentCIP->setIpPort(CIP::UDP);
    }
    currentCIP->updateService();
    currentCIP->pack();

    refreshServiceDisplay();
    refreshRequestDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setRequestFromEnum() to %1\n%2")
                               .arg(requestCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// PROFILE FUNCTIONS
int MainWindow::getIndexForProfileCmbBx() {
    qDebug() << "MainWindow::getIndexForProfileCmbBx()";

    switch (currentCIP->getProfile()) {

    case CIP::ProfileRZV:
        return 0;

    case CIP::ProfileUndefined:
        return 1;

    default:
        return 1;
    }
}

void MainWindow::refreshProfileDisplay() {
    qDebug() << "refreshProfileDisplay()";

    profileSpBox->setValue(currentCIP->getProfile());
    profileCmbBx->setCurrentIndex(getIndexForProfileCmbBx());
    profileToNumLbl->setText(QString("%1").arg(currentCIP->getProfile()));
    profileToStringLbl->setText(currentCIP->profileToString());
}

void MainWindow::setProfileFromNumber() {
    qDebug() << "setProfileFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setProfile(profileSpBox->value());
    currentCIP->pack();

    refreshProfileDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setProfileFromNumber() to %1\n%2")
                               .arg(profileCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setProfileFromEnum() {
    qDebug() << "setProfileFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setProfile(profileCmbBx->currentData().toInt());
    currentCIP->pack();

    refreshProfileDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setProfileFromEnum() to %1\n%2")
                               .arg(profileCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}


// VERSION FUNCTIONS
void MainWindow::refreshVersionDisplay() {
    qDebug() << "refreshVersionDisplay()";

    versionSpBox->setValue(currentCIP->getVersion());
    versionMajorSpBox->setValue(currentCIP->versionToMajorNumber());
    versionMinorSpBox->setValue(currentCIP->versionToMinorNumber());
    versionToNumLbl->setText(QString("%1").arg(currentCIP->getVersion()));
    versionToStringLbl->setText(currentCIP->versionToString());
}

void MainWindow::setVersionFromNumber() {
    qDebug() << "setVersionFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setVersion(versionSpBox->value());
    currentCIP->pack();

    refreshVersionDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setVersionFromNumber() to %1\n%2")
                               .arg(versionSpBox->value())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setVersionFromMajor() {
    qDebug() << "setVersionFromMajor()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setMajorVersion(versionMajorSpBox->value());
    currentCIP->pack();

    refreshVersionDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setVersionFromMajor() to %1\n%2")
                               .arg(versionMajorSpBox->value())
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setVersionFromMinor() {
    qDebug() << "setVersionFromMinor()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setMinorVersion(versionMinorSpBox->value());
    currentCIP->pack();

    refreshVersionDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setVersionFromMinor() to %1\n%2")
                               .arg(versionMajorSpBox->value())
                               .arg(currentCIP->bytesToString()));
}


// CHANNEL FUNCTIONS
int MainWindow::getIndexForChannelCmbBx() {
    qDebug() << "MainWindow::getIndexForChannelCmbBx()";

    switch (currentCIP->getChannel()) {

    case CIP::ChannelRZV:
        return 0;

    case CIP::ChannelSimpleMatching:
        return 1;

    case CIP::ChannelUndefined:
        return 2;

    default:
        return 2;
    }
}

void MainWindow::refreshChannelDisplay() {
    qDebug() << "refreshChannelDisplay()";

    channelSpBox->setValue(currentCIP->getChannel());
    channelCmbBx->setCurrentIndex(getIndexForChannelCmbBx());
    channelToNumLbl->setText(QString("%1").arg(currentCIP->getChannel()));
    channelToStringLbl->setText(currentCIP->channelToString());
}

void MainWindow::setChannelFromNumber() {
    qDebug() << "setChannelFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setChannel(channelSpBox->value());
    currentCIP->pack();

    refreshChannelDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setChannelFromNumber() to %1\n%2")
                               .arg(channelCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setChannelFromEnum() {
    qDebug() << "setChannelFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setChannel(channelCmbBx->currentData().toInt());
    currentCIP->pack();

    refreshChannelDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setChannelFromEnum() to %1\n%2")
                               .arg(channelCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// UUID
void MainWindow::refreshUuidDisplay() {
    qDebug() << "refreshUuidDisplay()";

    uuidToStringLbl->setText(currentCIP->uuidToString());
}

// IP ADDRESS
void MainWindow::refreshIpAddressDisplay() {
    qDebug() << "refreshIpAddressDisplay()";

    ipAddressToStringLbl->setText(currentCIP->ipAddressToString());

    QStringList ipList = currentCIP->getIpAddress().toString().split('.');
    ipAddressASpBox->setValue(QString(ipList.at(0)).toInt());
    ipAddressBSpBox->setValue(QString(ipList.at(1)).toInt());
    ipAddressCSpBox->setValue(QString(ipList.at(2)).toInt());
    ipAddressDSpBox->setValue(QString(ipList.at(3)).toInt());
}

void MainWindow::setIpAddress() {
    qDebug() << "setIpAddress()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setIpAddress(QHostAddress(QString("%1.%2.%3.%4")
                                          .arg(ipAddressASpBox->value())
                                          .arg(ipAddressBSpBox->value())
                                          .arg(ipAddressCSpBox->value())
                                          .arg(ipAddressDSpBox->value())));
    currentCIP->pack();

    refreshIpAddressDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setIpAddress() to %1\n%2")
                               .arg(QString("%1.%2.%3.%4")
                                    .arg(ipAddressASpBox->value())
                                    .arg(ipAddressBSpBox->value())
                                    .arg(ipAddressCSpBox->value())
                                    .arg(ipAddressDSpBox->value()))
                               .arg(currentCIP->bytesToString()));
}


// IP PORT FUNCTIONS
int MainWindow::getIndexForIpPortCmbBx() {
    qDebug() << "MainWindow::getIndexForIpPortCmbBx()";

    switch (currentCIP->getIpPort()) {

    case CIP::TCP:
        return 0;
    case CIP::UDP:
        return 1;
    default:
        return 2;
    }
}

void MainWindow::refreshIpPortDisplay() {
    qDebug() << "refreshIpPortDisplay()";

    qDebug() << "currentCIP->getIpPort(): " << currentCIP->getIpPort();

    ipPortSpBox->setValue(currentCIP->getIpPort());
    ipPortCmbBx->setCurrentIndex(getIndexForIpPortCmbBx());

    ipPortToNumLbl->setText(QString("%1").arg(currentCIP->ipPortToNumber()));
    ipPortToStringLbl->setText(currentCIP->ipPortToString());
}

void MainWindow::setIpPortFromNumber() {
    qDebug() << "setIpPortFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setIpPort(ipPortSpBox->value());
    currentCIP->pack();

    refreshIpPortDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setIpPortFromNumber() to %1\n%2")
                               .arg(ipPortCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setIpPortFromEnum() {
    qDebug() << "setIpPortFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setIpPort(ipPortCmbBx->currentData().toInt());
    currentCIP->pack();

    refreshIpPortDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setIpPortFromEnum() to %1\n%2")
                               .arg(ipPortCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}


// TIME FUNCTIONS
void MainWindow::setCurrentTime() {
    qDebug() << "setCurrentTime()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setTime(QDateTime::currentDateTime());
    currentCIP->pack();

    refreshTimeDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCurrentTime() to %1\n%2")
                               .arg(currentCIP->getTime().toString())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::refreshTimeDisplay() {
    qDebug() << "refreshTimeDisplay()";

    timeToNumLbl->setText(QString("Unix Epoch: %1 seconds").arg(currentCIP->getTime().toMSecsSinceEpoch()));
    timeToStringLbl->setText(currentCIP->timeToString());
}



//int getIndexForHeaderTypeCmbBx();
//void refreshHeaderTypeDisplay();





// HEADER TYPE FUNCTIONS
int MainWindow::getIndexForHeaderTypeCmbBx() {
    qDebug() << "MainWindow::getIndexForHeaderTypeCmbBx()";

    switch (currentCIP->getHeaderType()) {

    case CIP::HeaderTypeRZV:
        return 0;

    case CIP::HeaderTypeError:
        return 1;

    case CIP::HeaderTypeUndefined:
        return 2;

    default:
        return 2;
    }
}

void MainWindow::refreshHeaderTypeDisplay() {
    qDebug() << "refreshHeaderTypeDisplay()";

    headerTypeSpBox->setValue(currentCIP->getHeaderType());
    headerTypeCmbBx->setCurrentIndex(getIndexForHeaderTypeCmbBx());
    headerTypeToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderType()));
    headerTypeToStringLbl->setText(currentCIP->headerTypeToString());

    qDebug() << "currentCIP->headerTypeToString()" << currentCIP->headerTypeToString();
}

void MainWindow::setHeaderTypeFromNumber() {
    qDebug() << "MainWindow::setHeaderTypeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderType(headerTypeSpBox->value());
    currentCIP->pack();

    refreshHeaderTypeDisplay();
    refreshHeaderDataDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderTypeFromNumber() to %1\n%2")
                               .arg(headerTypeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setHeaderTypeFromEnum() {
    qDebug() << "MainWindow::setHeaderTypeFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderType(headerTypeCmbBx->currentData().toInt());
    currentCIP->pack();

    refreshHeaderTypeDisplay();
    refreshHeaderDataDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderTypeFromEnum() to %1\n%2")
                               .arg(headerTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// HEADER SIZE FUNCTIONS
void MainWindow::refreshHeaderSizeDisplay() {
    qDebug() << "MainWindow::refreshHeaderSizeDisplay()";

    headerSizeSpBox->setValue(currentCIP->getHeaderSize());
    headerSizeToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderSize()));
}


void MainWindow::setHeaderSizeFromNumber() {
    qDebug() << "MainWindow::setHeaderSizeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    headerOldSize = currentCIP->getHeaderSize();
    currentCIP->setHeaderSize(headerSizeSpBox->value());

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderSizeFromNumber() to %1\n%2")
                               .arg(headerSizeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}


// HEADER DATA FUNCTIONS
void MainWindow::refreshHeaderDataDisplay() {
    qDebug() << "MainWindow::refreshHeaderDataDisplay()";

    headerDataToStringLbl->setText(QString("interpreteHeaderData():\n%1\n%2").arg(QString(38, '-')).arg(currentCIP->interpreteHeaderData()));

    if(headerOldSize == 0) {

        headerOldSize = currentCIP->getHeaderSize();
    }

    switch (currentCIP->getHeaderType()) {
    case 0:
        setDataTypeToRZV();
        return;
    case 1:
        setDataTypeToError();
        return;
    default:
        setDataTypeToUndefined();
    }
}

void MainWindow::setHeaderData() {
    qDebug() << "MainWindow::setHeaderData()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    if(headerDataTypeErrorGBox->isVisible()) {
        return;
    }

    QString inString;

    if(headerDataTypeRZVGBox->isVisible()) {


        headerOldSize = currentCIP->getHeaderSize();

        for(int i=0; i<currentCIP->getHeaderSize(); i++) {

            if(headerDataTypeRZVLayout->itemAt(i) != NULL) {
                ((Data*) headerDataTypeRZVLayout->itemAt(i)->widget())->update();

                currentCIP->setHeaderData(((Data*) headerDataElements.at(i))->data, i);
            }
        }

        refreshHeaderSizeDisplay();
        refreshHeaderDataDisplay();

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderData()\n%1")
                                   .arg(currentCIP->bytesToString()));

        return;
    }

    if(headerDataTypeUndefinedGBox->isVisible()) {


        headerOldSize = currentCIP->getHeaderSize();

        for(int i=0; i<currentCIP->getHeaderSize(); i++) {

            if(headerDataTypeUndefinedLayout->itemAt(i) != NULL) {
                ((Data*) headerDataTypeUndefinedLayout->itemAt(i)->widget())->update();

                currentCIP->setHeaderData(((Data*) headerDataElements.at(i))->data, i);
            }
        }

        refreshHeaderSizeDisplay();
        refreshHeaderDataDisplay();

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderData()\n%2")
                                   .arg(currentCIP->bytesToString()));

        return;
    }
}

void MainWindow::clearDataTypes() {
    qDebug() << "MainWindow::clearDataTypes()";

    headerDataTypeRZVGBox->hide();
    headerDataTypeErrorGBox->hide();

    for(int i=0; i<256; i++) {

        if(headerDataTypeUndefinedLayout->itemAt(i) != NULL) {
            headerDataTypeUndefinedLayout->itemAt(i)->widget()->hide();
        }
    }
    headerDataTypeUndefinedGBox->hide();

    headerDataLbl->hide();
    saveHeaderDataBtn->hide();
}

void MainWindow::setDataTypeToRZV() {
    qDebug() << "MainWindow::setDataTypeToRZV()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearDataTypes();

    for(int i=0; i<currentCIP->getHeaderSize(); i++) {

        qDebug() << "i: " << i;

        if(i<headerOldSize) {

            headerDataElements.at(i)->update(currentCIP->getHeaderData().at(i), i);
        }
        else {
            headerDataElements.at(i)->update(0, i);
        }

        if(headerDataTypeRZVLayout->itemAt(i) != NULL) {
            qDebug() << "i !=NULL: " << i;
            headerDataTypeRZVLayout->itemAt(i)->widget()->show();
        }
    }

    headerDataTypeRZVGBox->setTitle("Header Data Interpretation: HeaderTypeRZV");
    headerDataTypeRZVGBox->show();

    headerDataLbl->show();
    saveHeaderDataBtn->show();
}

int MainWindow::getIndexForHeaderDataErrorCategoryCmbBx() {
    qDebug() << "MainWindow::getIndexForHeaderDataErrorCategoryCmbBx()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return -1;
    }

    switch ((quint8) currentCIP->getHeaderData().at(0)) {

    case CIP::ErrorCategoryNone:
        return 0;

    case CIP::CipFormatError:
        return 1;

    default:
        return 2;
    }

}

int MainWindow::getIndexForHeaderDataErrorPriorityCmbBx() {
    qDebug() << "MainWindow::getIndexForHeaderDataErrorPriorityCmbBx()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return -1;
    }

    switch (currentCIP->getHeaderData(1)) {

    case CIP::ErrorPriorityNone:
        return 0;

    case CIP::ErrorPriorityDebug:
        return 1;

    case CIP::ErrorPriorityInfo:
        return 2;

    case CIP::ErrorPriorityNotice:
        return 3;

    case CIP::ErrorPriorityCritical:
        return 4;

    case CIP::ErrorPriorityAlert:
        return 5;

    case CIP::ErrorPriorityEmergency:
        return 6;

    default:
        return 7;
    }

}

int MainWindow::getIndexForHeaderDataErrorCmbBx() {
    qDebug() << "MainWindow::getIndexForHeaderDataErrorCmbBx()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return -1;
    }

    switch (currentCIP->getHeaderData(2)) {

    case CIP::CipFormatErrorNone:
        return 0;

    case CIP::CipFormatErrorOutOfRange:
        return 1;

    case CIP::CipFormatErrorInconsistent:
        return 2;

    case CIP::CipFormatErrorWrongProtocol:
        return 3;

    default:
        return 4;
    }
}

void MainWindow::setDataTypeToError() {
    qDebug() << "setDataTypeToError()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearDataTypes();

    headerDataTypeUndefinedGBox->setTitle("Header Data Interpretation: HeaderTypeError");

    headerDataError0SpBox->setValue(currentCIP->getHeaderData(0));
    headerDataError1SpBox->setValue(currentCIP->getHeaderData(1));
    headerDataError2SpBox->setValue(currentCIP->getHeaderData(2));
    headerDataErrorCategoryCmbBx->setCurrentIndex(getIndexForHeaderDataErrorCategoryCmbBx());
    headerDataErrorPriorityCmbBx->setCurrentIndex(getIndexForHeaderDataErrorPriorityCmbBx());
    headerDataErrorCmbBx->setCurrentIndex(getIndexForHeaderDataErrorCmbBx());

    headerDataError0ToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderData().at(0)));
    headerDataErrorCategoryToEnumLbl->setText(currentCIP->interpreteHeaderData().split(' ').at(0));
    headerDataError1ToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderData().at(1)));
    headerDataErrorPriorityToEnumLbl->setText(currentCIP->interpreteHeaderData().split(' ').at(1));
    headerDataError2ToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderData().at(2)));
    headerDataErrorToEnumLbl->setText(currentCIP->interpreteHeaderData().split(' ').at(2));

    headerDataTypeErrorGBox->show();
}

void MainWindow::setDataTypeToUndefined() {
    qDebug() << "MainWindow::setDataTypeToUndefined()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearDataTypes();

    for(int i=0; i<currentCIP->getHeaderSize(); i++) {

        if(i<headerOldSize) {

            headerDataElements.at(i)->update(currentCIP->getHeaderData().at(i), i);
        }
        else {
            headerDataElements.at(i)->update(0, i);
        }

        if(headerDataTypeUndefinedLayout->itemAt(i) != NULL) {
            headerDataTypeUndefinedLayout->itemAt(i)->widget()->show();
        }
    }

    headerDataTypeUndefinedGBox->setTitle("Header Data Interpretation: HeaderTypeUndefined");
    headerDataTypeUndefinedGBox->show();
}


void MainWindow::setHeaderDataError0() {
    qDebug() << "MainWindow::setHeaderDataError0()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataError0SpBox->value(), 0);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataError0FromNumber() to %1\n%2")
                               .arg(currentCIP->getHeaderData(0))
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setHeaderDataError1() {
    qDebug() << "MainWindow::setHeaderDataError1()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataError1SpBox->value(), 1);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataError1FromNumber() to %1\n%2")
                               .arg(currentCIP->getHeaderData(1))
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setHeaderDataError2() {
    qDebug() << "MainWindow::setHeaderDataError2()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataError2SpBox->value(), 2);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataError2FromNumber() to %1\n%2")
                               .arg(currentCIP->getHeaderData(2))
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setHeaderDataErrorCategory() {
    qDebug() << "MainWindow::setHeaderDataErrorCategory()";


    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataErrorCategoryCmbBx->currentIndex(), 0);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataErrorCategory() to %1\n%2")
                               .arg(currentCIP->getHeaderData(0))
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setHeaderDataErrorPriority() {
    qDebug() << "MainWindow::setHeaderDataErrorPriority()";


    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataErrorPriorityCmbBx->currentIndex(), 1);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataErrorPriority() to %1\n%2")
                               .arg(currentCIP->getHeaderData(1))
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::setHeaderDataError() {
    qDebug() << "MainWindow::setHeaderDataError()";


    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderData((quint8) headerDataErrorCmbBx->currentIndex(), 2);
    currentCIP->truncateHeaderData(3);
    currentCIP->setHeaderSize(3);

    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderDataError() to %1\n%2")
                               .arg(currentCIP->getHeaderData(2))
                               .arg(currentCIP->bytesToString()));
}



// CI TYPE FUNCTIONS
int MainWindow::getIndexForCiTypeCmbBx() {
    qDebug() << "MainWindow::getIndexForCiTypeCmbBx()";

    switch (currentCIP->getCiType()) {

    case CIP::CiTypeRZV:
        return 0;

    case CIP::CiTypeSimpleMatch:
        return 1;

    default:
        return 2;
    }
}

void MainWindow::refreshCiTypeDisplay() {
    qDebug() << "refreshCiTypeDisplay()";

    ciTypeSpBox->setValue(currentCIP->getCiType());
    ciTypeCmbBx->setCurrentIndex(getIndexForCiTypeCmbBx());
    ciTypeToNumLbl->setText(QString("%1").arg(currentCIP->getCiType()));
    ciTypeToStringLbl->setText(currentCIP->ciTypeToString());

    qDebug() << "currentCIP->ciTypeToString()" << currentCIP->ciTypeToString();
}

void MainWindow::setCiTypeFromNumber() {
    qDebug() << "setCiTypeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setCiType(ciTypeSpBox->value());
    refreshCiTypeDisplay();
    refreshCiDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCiTypeFromNumber() to %1\n%2")
                               .arg(ciTypeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setCiTypeFromEnum() {
    qDebug() << "setCiTypeFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setCiType(ciTypeCmbBx->currentData().toInt());
    refreshCiTypeDisplay();
    refreshCiDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCiTypeFromEnum() to %1\n%2")
                               .arg(ciTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// CI SIZE FUNCTIONS
void MainWindow::refreshCiSizeDisplay() {
    qDebug() << "refreshCiSizeDisplay()";

    ciSizeSpBox->setValue(currentCIP->getCiSize());
    ciSizeToNumLbl->setText(QString("%1").arg(currentCIP->getCiSize()));
}

void MainWindow::setCiSizeFromNumber() {
    qDebug() << "setCiSizeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    ciOldSize = currentCIP->getCiSize();
    currentCIP->setCiSize(ciSizeSpBox->value());

    refreshCiSizeDisplay();
    refreshCiDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCiSizeFromNumber() to %1\n%2")
                               .arg(ciSizeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}






// CI DATA FUNCTIONS
void MainWindow::refreshCiDataDisplay() {
    qDebug() << "MainWindow::refreshCiDataDisplay()";

    switch (currentCIP->getCiType()) {
    case 0:
        setRootCicTypeToUndefined();
        return;
    case 1:
        break;
    default:
        setRootCicTypeToUndefined();
        return;
    }

    switch (currentCIP->getRootCIC().getContent()) {
    case 0:
        setRootCicTypeToUndefined();
        return;
    case 1:
        setRootCicTypeToLatinText();
        return;
    default:
        setRootCicTypeToUndefined();
    }
}



void MainWindow::setCiBricks() {
    qDebug() << "MainWindow::setCiBricks()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    if(rootCicTypeLatinTextGBox->isVisible()) {

        QString inString;

        inString = rootCicTypeLatinTextTxtEdt->toPlainText();

        for(int i=0; i<inString.length(); i++) {
            currentCIP->setCICBrickContent(inString.toLatin1().at(i), i);
        }

        currentCIP->setCiSize((quint8) inString.length());

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCiBricks() to \"%1\"\n%2")
                                   .arg(inString)
                                   .arg(currentCIP->bytesToString()));
        refreshCiSizeDisplay();
        refreshCiDataDisplay();

        return;
    }

    if(rootCicTypeUndefinedGBox->isVisible()) {

        ciOldSize = currentCIP->getCiSize();

        for(int i=0; i<currentCIP->getCiSize(); i++) {

            if(rootCicTypeUndefinedLayout->itemAt(i) != NULL) {
                ((CiBrick*) rootCicTypeUndefinedLayout->itemAt(i)->widget())->update();

                currentCIP->setCICBrickContent(brickElements.at(i)->content, i);
                currentCIP->setCICBrickMask(brickElements.at(i)->mask, i);
            }
        }

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setCiBricks()\n%2")
                                   .arg(currentCIP->bytesToString()));
        refreshCiSizeDisplay();
        refreshCiDataDisplay();

        return;
    }

}



void MainWindow::clearRootCicTypes() {
    qDebug() << "MainWindow::clearRootCicTypes()";

    rootCicTypeLatinTextGBox->hide();

    for(int i=0; i<256; i++) {
        if(rootCicTypeUndefinedLayout->itemAt(i) != NULL) {
            rootCicTypeUndefinedLayout->itemAt(i)->widget()->hide();
        }
    }
    rootCicTypeUndefinedGBox->hide();

    ciDataToStringLbl->clear();

    ciDataLbl->hide();
    saveCiBricksBtn->hide();
}

void MainWindow::setRootCicTypeToLatinText() {
    qDebug() << "MainWindow::setRootCicTypeToLatinText()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearRootCicTypes();

    rootCicTypeLatinTextTxtEdt->setText(currentCIP->interpreteCICBricks());
    rootCicTypeLatinTextGBox->show();

    ciDataLbl->show();
    saveCiBricksBtn->show();

    ciDataToStringLbl->setText(QString("interpreteCICBricks():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteCICBricks()).arg('"'));
}

void MainWindow::setRootCicTypeToUndefined() {
    qDebug() << "MainWindow::setRootCicTypeToUndefined()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearRootCicTypes();

    for(int i=0; i<currentCIP->getCiSize(); i++) {

        if(i<ciOldSize) {

            brickElements.at(i)->update(currentCIP->getCICBricks().at(i).getContent(), currentCIP->getCICBricks().at(i).getMask(), i);
        }
        else {
            brickElements.at(i)->update(0, 0, i);
        }

        if(rootCicTypeUndefinedLayout->itemAt(i) != NULL) {
            rootCicTypeUndefinedLayout->itemAt(i)->widget()->show();
        }
    }

    rootCicTypeUndefinedGBox->show();

    ciDataLbl->show();
    saveCiBricksBtn->show();

    ciDataToStringLbl->setText(QString("interpreteCICBricks():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteCICBricks()).arg('"'));
}










// APPDATA TYPE FUNCTIONS
int MainWindow::getIndexForAppDataTypeCmbBx() {
    qDebug() << "MainWindow::getIndexForAppDataTypeCmbBx()";

    switch (currentCIP->getAppDataType()) {

    case CIP::AppDataTypeRZV:
        return 0;

    case CIP::AppDataTypeText:
        return 1;

    case CIP::AppDataTypeUrl:
        return 2;

    default:
        return 3;
    }
}

void MainWindow::refreshAppDataTypeDisplay() {
    qDebug() << "refreshAppDataTypeDisplay()";

    appDataTypeSpBox->setValue(currentCIP->getAppDataType());
    appDataTypeCmbBx->setCurrentIndex(getIndexForAppDataTypeCmbBx());
    appDataTypeToNumLbl->setText(QString("%1").arg(currentCIP->getAppDataType()));
    appDataTypeToStringLbl->setText(currentCIP->appDataTypeToString());

    qDebug() << "currentCIP->appDataTypeToString()" << currentCIP->appDataTypeToString();
}

void MainWindow::setAppDataTypeFromNumber() {
    qDebug() << "setAppDataTypeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setAppDataType(appDataTypeSpBox->value());
    refreshAppDataTypeDisplay();
    refreshAppDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppDataTypeFromNumber() to %1\n%2")
                               .arg(appDataTypeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setAppDataTypeFromEnum() {
    qDebug() << "setAppDataTypeFromEnum()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setAppDataType(appDataTypeCmbBx->currentData().toInt());
    refreshAppDataTypeDisplay();
    refreshAppDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppDataTypeFromEnum() to %1\n%2")
                               .arg(appDataTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// APPDATA SIZE FUNCTIONS
void MainWindow::refreshAppDataSizeDisplay() {
    qDebug() << "refreshAppDataSizeDisplay()";

    appDataSizeSpBox->setValue(currentCIP->getAppDataSize());
    appDataSizeToNumLbl->setText(QString("%1").arg(currentCIP->getAppDataSize()));
}

void MainWindow::setAppDataSizeFromNumber() {
    qDebug() << "setAppDataSizeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    appDataOldSize = currentCIP->getAppDataSize();

    currentCIP->setAppDataSize(appDataSizeSpBox->value());
    refreshAppDataSizeDisplay();
    refreshAppDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppDataSizeFromNumber() to %1\n%2")
                               .arg(appDataSizeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}



void MainWindow::clearAppDataTypes() {
    qDebug() << "MainWindow::clearAppDataTypes()";

    appDataTypeTextGBox->hide();

    for(int i=0; i<256; i++) {
        if(appDataTypeUndefinedLayout->itemAt(i) != NULL) {
            appDataTypeUndefinedLayout->itemAt(i)->widget()->hide();
        }
    }
    appDataTypeUndefinedGBox->hide();

    appDataToStringLbl->clear();

    appDataLbl->hide();
    saveAppDataBtn->hide();

}

void MainWindow::setAppDataTypeToText() {
    qDebug() << "MainWindow::setAppDataTypeToText()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearAppDataTypes();

    appDataTypeTextTxtEdt->setText(currentCIP->interpreteAppData());
    appDataTypeTextGBox->show();

    appDataLbl->show();
    saveAppDataBtn->show();

    appDataToStringLbl->setText(QString("interpreteAppData():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteAppData()).arg('"'));

}

void MainWindow::setAppDataTypeToUndefined() {
    qDebug() << "MainWindow::setAppDataTypeToUndefined()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearAppDataTypes();

    for(int i=0; i<currentCIP->getAppDataSize(); i++) {

        if(i<appDataOldSize) {

            appDataElements.at(i)->update(currentCIP->getAppData().at(i), i);
        }
        else {
            appDataElements.at(i)->update(0, i);
        }

        if(appDataTypeUndefinedLayout->itemAt(i) != NULL) {
            appDataTypeUndefinedLayout->itemAt(i)->widget()->show();
        }
    }

    appDataTypeUndefinedGBox->show();

    appDataLbl->show();
    saveAppDataBtn->show();

    appDataToStringLbl->setText(QString("interpreteAppData():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteAppData()).arg('"'));

}

void MainWindow::refreshAppDataDisplay() {
    qDebug() << "MainWindow::refreshAppDataDisplay()";

    switch (currentCIP->getAppDataType()) {
    case 0:
        setAppDataTypeToUndefined();
        return;
    case 1:
        setAppDataTypeToText();
        return;
    default:
        setAppDataTypeToUndefined();
        return;
    }
}


void MainWindow::setAppData() {
    qDebug() << "MainWindow::setAppData()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    if(appDataTypeTextGBox->isVisible()) {

        QString inString;

        inString = appDataTypeTextTxtEdt->toPlainText();

        for(int i=0; i<inString.length(); i++) {
            currentCIP->setAppData(inString.toLatin1().at(i), i);
        }

        currentCIP->setAppDataSize((quint8) inString.length());

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppData() to \"%1\"\n%2")
                                   .arg(inString)
                                   .arg(currentCIP->bytesToString()));
        refreshAppDataSizeDisplay();
        refreshAppDataDisplay();

        return;
    }

    if(appDataTypeUndefinedGBox->isVisible()) {

        appDataOldSize = currentCIP->getAppDataSize();

        for(int i=0; i<currentCIP->getAppDataSize(); i++) {

            if(appDataTypeUndefinedLayout->itemAt(i) != NULL) {
                ((Data*) appDataTypeUndefinedLayout->itemAt(i)->widget())->update();

                currentCIP->setCICBrickContent(appDataElements.at(i)->data, i);
            }
        }

        currentCIP->pack();
        rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppData()\n%2")
                                   .arg(currentCIP->bytesToString()));
        refreshAppDataSizeDisplay();
        refreshAppDataDisplay();

        return;
    }

}



