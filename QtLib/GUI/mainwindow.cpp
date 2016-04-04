#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

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
    headerTypeCmbBx->addItem("HeaderTypeOk (0)", 0);
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
    headerSizeCommentLbl = new QLabel(tr("Read Only"));
    headerSizeCommentLbl->setAlignment(Qt::AlignCenter);
    headerSizeToNumLbl = new QLabel();
    headerSizeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(headerSizeLbl, 12, 0);
    headerLayout->addWidget(headerSizeCommentLbl, 12, 1, 1, 7);
    headerLayout->addWidget(headerSizeToNumLbl, 12, 7);


    // HEADER DATA

    // HEADER DATA TYPE OK
    headerDataTypeOkLayout = new QGridLayout;
    headerDataTypeOkGBox = new QGroupBox("Header Data Interpretation of Header Type Ok (default interpretation as characters)");
    headerDataTypeOkGBox->setLayout(headerDataTypeOkLayout);
    headerDataTypeOkTxtEdt = new QTextEdit(headerDataTypeOkGBox);
    headerDataTypeOkTxtEdt->setReadOnly(false);
    headerDataTypeOkGBox->hide();

    headerDataTypeOkLayout->addWidget(headerDataTypeOkTxtEdt, 0, 0);

    // HEADER DATA TYPE ERROR
    headerDataTypeErrorLayout = new QGridLayout;
    headerDataTypeErrorGBox = new QGroupBox("Header Data Interpretation of Header Type Error");
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
    headerDataTypeUndefinedGBox = new QGroupBox("Undefined Header Data Interpretation (default interpretation as characters)");
    headerDataTypeUndefinedTxtEdt = new QTextEdit("No CIP loaded yet", headerGBox);
    headerDataTypeUndefinedTxtEdt->setReadOnly(false);
    headerDataTypeUndefinedGBox->setLayout(headerDataTypeUndefinedLayout);
    headerDataTypeUndefinedGBox->show();

    headerDataTypeUndefinedLayout->addWidget(headerDataTypeUndefinedTxtEdt, 0, 0);

    setDataTypeToUndefined();

    headerDataToStringLbl = new QLabel();
    headerDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(headerDataTypeOkGBox, 13, 0, 1, 7);
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
    rootCicTypeUndefinedGBox = new QGroupBox("CICBricks Interpretation of rootCIC Type Undefined");
    rootCicTypeUndefinedGBox->setLayout(rootCicTypeUndefinedLayout);


//    rootCicTypeUndefined__0ContentLbl = new QLabel(tr("[0] C: "));
//    rootCicTypeUndefined__0ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
////    rootCicTypeUndefined__0ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__0ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__0ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__0ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__0ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__0ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__0MaskLbl = new QLabel(tr("[0] M: "));
//    rootCicTypeUndefined__0MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
////    rootCicTypeUndefined__0MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__0MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__0MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__0MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__0MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__0MaskSpBox->setRange(0, 255);

//    rootCicTypeUndefined__1ContentLbl = new QLabel(tr("[1] C: "));
//    rootCicTypeUndefined__1ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
////    rootCicTypeUndefined__1ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__1ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__1ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__1ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__1ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__1ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__1MaskLbl = new QLabel(tr("[1] M: "));
//    rootCicTypeUndefined__1MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
////    rootCicTypeUndefined__1MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__1MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__1MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__1MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__1MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__1MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);



//    rootCicTypeUndefined__2ContentLbl = new QLabel(tr("[2] C: "));
//    rootCicTypeUndefined__2ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__2ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__2ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__2ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__2ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__2ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__2ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__2MaskLbl = new QLabel(tr("[2] M: "));
//    rootCicTypeUndefined__2MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__2MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__2MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__2MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__2MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__2MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__2MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    rootCicTypeUndefined__3ContentLbl = new QLabel(tr("[3] C: "));
//    rootCicTypeUndefined__3ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__3ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__3ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__3ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__3ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__3ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__3ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__3MaskLbl = new QLabel(tr("[3] M: "));
//    rootCicTypeUndefined__3MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__3MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__3MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__3MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__3MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__3MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__3MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);



//    rootCicTypeUndefined__4ContentLbl = new QLabel(tr("[4] C: "));
//    rootCicTypeUndefined__4ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__4ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__4ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__4ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__4ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__4ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__4ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__4MaskLbl = new QLabel(tr("[4] M: "));
//    rootCicTypeUndefined__4MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__4MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__4MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__4MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__4MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__4MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__4MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    rootCicTypeUndefined__5ContentLbl = new QLabel(tr("[5] C: "));
//    rootCicTypeUndefined__5ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__5ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__5ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__5ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__5ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__5ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__5ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__5MaskLbl = new QLabel(tr("[5] M: "));
//    rootCicTypeUndefined__5MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__5MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__5MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__5MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__5MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__5MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__5MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);



//    rootCicTypeUndefined__6ContentLbl = new QLabel(tr("[6] C: "));
//    rootCicTypeUndefined__6ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__6ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__6ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__6ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__6ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__6ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__6ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__6MaskLbl = new QLabel(tr("[6] M: "));
//    rootCicTypeUndefined__6MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__6MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__6MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__6MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__6MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__6MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__6MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

//    rootCicTypeUndefined__7ContentLbl = new QLabel(tr("[7] C: "));
//    rootCicTypeUndefined__7ContentLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__7ContentLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__7ContentSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__7ContentSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__7ContentSpBox->setRange(0, 255);
//    rootCicTypeUndefined__7ContentCommentLbl = new QLabel();
//    rootCicTypeUndefined__7ContentCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
//    rootCicTypeUndefined__7MaskLbl = new QLabel(tr("[7] M: "));
//    rootCicTypeUndefined__7MaskLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    rootCicTypeUndefined__7MaskLbl->setFixedSize(100, 30);
//    rootCicTypeUndefined__7MaskSpBox = new QSpinBox(ciGBox);
//    rootCicTypeUndefined__7MaskSpBox->setFixedSize(60, 30);
//    rootCicTypeUndefined__7MaskSpBox->setRange(0, 255);
//    rootCicTypeUndefined__7MaskCommentLbl = new QLabel();
//    rootCicTypeUndefined__7MaskCommentLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);




    rootCicTypeUndefinedGBox->hide();

//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0ContentLbl, 0, 0);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0ContentCommentLbl, 0, 1);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0ContentSpBox, 0, 2);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0MaskLbl, 0, 3);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0MaskCommentLbl, 0, 4);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__0MaskSpBox, 0, 5);

//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1ContentLbl, 0, 6);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1ContentCommentLbl, 0, 7);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1ContentSpBox, 0, 8);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1MaskLbl, 0, 9);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1MaskCommentLbl, 0, 10);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__1MaskSpBox, 0, 11);


//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2ContentLbl, 0, 12);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2ContentCommentLbl, 0, 13);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2ContentSpBox, 0, 14);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2MaskLbl, 0, 15);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2MaskCommentLbl, 0, 16);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__2MaskSpBox, 0, 17);

//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3ContentLbl, 0, 18);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3ContentCommentLbl, 0, 19);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3ContentSpBox, 0, 20);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3MaskLbl, 0, 21);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3MaskCommentLbl, 0, 22);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__3MaskSpBox, 0, 23);


//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4ContentLbl, 0, 24);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4ContentCommentLbl, 0, 25);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4ContentSpBox, 0, 26);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4MaskLbl, 0, 27);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4MaskCommentLbl, 0, 28);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__4MaskSpBox, 0, 29);

//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5ContentLbl, 0, 30);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5ContentCommentLbl, 0, 31);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5ContentSpBox, 0, 32);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5MaskLbl, 0, 33);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5MaskCommentLbl, 0, 34);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__5MaskSpBox, 0, 35);


//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6ContentLbl, 0, 36);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6ContentCommentLbl, 0, 37);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6ContentSpBox, 0, 38);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6MaskLbl, 0, 39);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6MaskCommentLbl, 0, 40);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__6MaskSpBox, 0, 41);

//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7ContentLbl, 0, 42);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7ContentCommentLbl, 0, 43);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7ContentSpBox, 0, 44);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7MaskLbl, 0, 45);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7MaskCommentLbl, 0, 46);
//    rootCicTypeUndefinedLayout->addWidget(rootCicTypeUndefined__7MaskSpBox, 0, 47);

    ciDataToStringLbl = new QLabel();
    ciDataToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ciLayout->addWidget(rootCicTypeLatinTextGBox, 3, 0, 1, 9);
    ciLayout->addWidget(rootCicTypeUndefinedGBox, 3, 0, 1, 9);

    ciLayout->addWidget(ciDataToStringLbl, 3, 8);


    ciDataLbl = new QLabel(tr("CIC-Bricks (size): "));
    ciDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ciDataLbl->hide();

    saveCiDataBtn = new QPushButton(tr("setCICBricks()"), this);
    saveCiDataBtn->hide();

    ciLayout->addWidget(ciDataLbl, 4, 0);
    ciLayout->addWidget(saveCiDataBtn, 4, 1);





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


    // CONNECTS
    connect(createBtn, &QAbstractButton::clicked, this, &MainWindow::createCIP);

    connect(openBtn, &QAbstractButton::clicked, this, &MainWindow::openCIP);
    connect(saveBtn, &QAbstractButton::clicked, this, &MainWindow::saveCIP);


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

    connect(saveHeaderTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromNumber);
    connect(saveHeaderTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromEnum);


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


    // APPDATA CONNECTS
    connect(saveAppDataTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataTypeFromNumber);
    connect(saveAppDataTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataTypeFromEnum);

    connect(saveAppDataSizeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setAppDataSizeFromNumber);

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



int getIndexForHeaderTypeCmbBx();
void refreshHeaderTypeDisplay();





// HEADER TYPE FUNCTIONS
int MainWindow::getIndexForHeaderTypeCmbBx() {
    qDebug() << "MainWindow::getIndexForHeaderTypeCmbBx()";

    switch (currentCIP->getHeaderType()) {

    case CIP::HeaderTypeOk:
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
    qDebug() << "setHeaderTypeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderType(headerTypeSpBox->value());
    currentCIP->pack();

    refreshHeaderTypeDisplay();
    refreshHeaderDataDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderTypeFromNumber() to %1\n%2")
                               .arg(headerTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::setHeaderTypeFromEnum() {
    qDebug() << "setHeaderTypeFromEnum()";

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
    qDebug() << "refreshHeaderSizeDisplay()";

    headerSizeToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderSize()));
}


// HEADER DATA FUNCTIONS
void MainWindow::refreshHeaderDataDisplay() {
    qDebug() << "refreshHeaderDataDisplay()";

    headerDataToStringLbl->setText(QString("interpreteHeaderData():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteHeaderData()).arg('"'));

    switch (currentCIP->getHeaderType()) {
    case 0:
        setDataTypeToOk();
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

    if(headerDataTypeOkGBox->isVisible()) {

        inString = headerDataTypeOkTxtEdt->toPlainText();
    }

    if(headerDataTypeUndefinedGBox->isVisible()) {

        inString = headerDataTypeUndefinedTxtEdt->toPlainText();
    }

    currentCIP->setHeaderData(inString.toLatin1());
    currentCIP->setHeaderSize((quint8) inString.length());
    refreshHeaderSizeDisplay();
    refreshHeaderDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderData() to \"%1\"\n%2")
                               .arg(inString)
                               .arg(currentCIP->bytesToString()));
}

void MainWindow::clearDataTypes() {
    qDebug() << "MainWindow::clearDataTypes()";

    headerDataTypeOkGBox->hide();
    headerDataTypeErrorGBox->hide();
    headerDataTypeUndefinedGBox->hide();

    headerDataLbl->hide();
    saveHeaderDataBtn->hide();
}

void MainWindow::setDataTypeToOk() {
    qDebug() << "MainWindow::setDataTypeToOk()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearDataTypes();

    headerDataTypeOkTxtEdt->setText(currentCIP->interpreteHeaderData());
    headerDataTypeOkGBox->show();

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

    headerDataTypeUndefinedTxtEdt->setText(currentCIP->interpreteHeaderData());
    headerDataTypeUndefinedGBox->show();

    headerDataLbl->show();
    saveHeaderDataBtn->show();
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
    qDebug() << "refreshCiDataDisplay()";

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



void MainWindow::clearRootCicTypes() {
    qDebug() << "MainWindow::clearRootCicTypes()";

    rootCicTypeLatinTextGBox->hide();
    rootCicTypeUndefinedGBox->hide();

    ciDataToStringLbl->clear();

    ciDataLbl->hide();
    saveCiDataBtn->hide();
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
    saveCiDataBtn->show();

    ciDataToStringLbl->setText(QString("interpreteCICBricks():\n%1\n%2%3%4").arg(QString(38, '-')).arg('"').arg(currentCIP->interpreteCICBricks()).arg('"'));
}

void MainWindow::setRootCicTypeToUndefined() {
    qDebug() << "MainWindow::setRootCicTypeToUndefined()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    clearRootCicTypes();

//    rootCicTypeUndefined__0ContentSpBox->setValue(currentCIP->getCICBricks().at(0).getContent());
//    rootCicTypeUndefined__0MaskSpBox->setValue(currentCIP->getCICBricks().at(0).getMask());
//    rootCicTypeUndefined__0ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(0).getContent()));
//    rootCicTypeUndefined__0MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(0).getMask()));

//    rootCicTypeUndefined__1ContentSpBox->setValue(currentCIP->getCICBricks().at(1).getContent());
//    rootCicTypeUndefined__1MaskSpBox->setValue(currentCIP->getCICBricks().at(1).getMask());
//    rootCicTypeUndefined__1ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(1).getContent()));
//    rootCicTypeUndefined__1MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(1).getMask()));

//    rootCicTypeUndefined__2ContentSpBox->setValue(currentCIP->getCICBricks().at(2).getContent());
//    rootCicTypeUndefined__2MaskSpBox->setValue(currentCIP->getCICBricks().at(2).getMask());
//    rootCicTypeUndefined__2ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(2).getContent()));
//    rootCicTypeUndefined__2MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(2).getMask()));

//    rootCicTypeUndefined__3ContentSpBox->setValue(currentCIP->getCICBricks().at(3).getContent());
//    rootCicTypeUndefined__3MaskSpBox->setValue(currentCIP->getCICBricks().at(3).getMask());
//    rootCicTypeUndefined__3ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(3).getContent()));
//    rootCicTypeUndefined__3MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(3).getMask()));

//    rootCicTypeUndefined__4ContentSpBox->setValue(currentCIP->getCICBricks().at(4).getContent());
//    rootCicTypeUndefined__4MaskSpBox->setValue(currentCIP->getCICBricks().at(4).getMask());
//    rootCicTypeUndefined__4ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(4).getContent()));
//    rootCicTypeUndefined__4MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(4).getMask()));

//    rootCicTypeUndefined__5ContentSpBox->setValue(currentCIP->getCICBricks().at(5).getContent());
//    rootCicTypeUndefined__5MaskSpBox->setValue(currentCIP->getCICBricks().at(5).getMask());
//    rootCicTypeUndefined__5ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(5).getContent()));
//    rootCicTypeUndefined__5MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(5).getMask()));


//    rootCicTypeUndefined__6ContentSpBox->setValue(currentCIP->getCICBricks().at(6).getContent());
//    rootCicTypeUndefined__6MaskSpBox->setValue(currentCIP->getCICBricks().at(6).getMask());
//    rootCicTypeUndefined__6ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(6).getContent()));
//    rootCicTypeUndefined__6MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(6).getMask()));

//    rootCicTypeUndefined__7ContentSpBox->setValue(currentCIP->getCICBricks().at(7).getContent());
//    rootCicTypeUndefined__7MaskSpBox->setValue(currentCIP->getCICBricks().at(7).getMask());
//    rootCicTypeUndefined__7ContentCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(7).getContent()));
//    rootCicTypeUndefined__7MaskCommentLbl->setText(QString("%1").arg(currentCIP->getCICBricks().at(7).getMask()));


    for(int i=0; i<=currentCIP->getCiSize();i++) {

        CiBrick *ciBrick = new CiBrick();
        ciBrick->initialize(1, 2, i);

//        ciBrick->content = currentCIP->getCICBricks().at(i).getContent();
//        ciBrick->mask = currentCIP->getCICBricks().at(i).getMask();

//        ciBrick->update();

        rootCicTypeUndefinedLayout->addWidget(ciBrick, qFloor(i/3), i%3);

    }

    rootCicTypeUndefinedGBox->show();

}

//int MainWindow::getIndexForHeaderDataErrorCategoryCmbBx() {
//    qDebug() << "MainWindow::getIndexForHeaderDataErrorCategoryCmbBx()";

//    if(currentCIP == NULL) {
//        qDebug() << "currentCIP == NULL -> return";
//        return -1;
//    }

//    switch ((quint8) currentCIP->getHeaderData().at(0)) {

//    case CIP::ErrorCategoryNone:
//        return 0;

//    case CIP::CipFormatError:
//        return 1;

//    default:
//        return 2;
//    }

//}












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
//    refreshAppDataDataDisplay();

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
//    refreshAppDataDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppDataTypeFromEnum() to %1\n%2")
                               .arg(appDataTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// APPDATA SIZE FUNCTIONS
void MainWindow::refreshAppDataSizeDisplay() {
    qDebug() << "refreshAppDataSizeDisplay()";

    appDataSizeToNumLbl->setText(QString("%1").arg(currentCIP->getAppDataSize()));
}

void MainWindow::setAppDataSizeFromNumber() {
    qDebug() << "setAppDataSizeFromNumber()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setAppDataSize(appDataSizeSpBox->value());
    refreshAppDataSizeDisplay();
//    refreshAppDataDataDisplay();

    currentCIP->pack();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setAppDataSizeFromNumber() to %1\n%2")
                               .arg(appDataSizeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}


