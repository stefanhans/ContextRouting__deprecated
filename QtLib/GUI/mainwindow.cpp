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

    // Fix Context Layout
    contextLayout = new QGridLayout;

    // Data Fix Layout
    dataLayout = new QGridLayout;


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
    uuidToStringLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(uuidLbl, 7, 0);
    headerLayout->addWidget(uuidCommentLbl, 7, 1, 1, 8);
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
    ipPortCmbBx->addItem("TCP (0)", 0);
    ipPortCmbBx->addItem("UDP (1)", 1);
    ipPortCmbBx->addItem("undefined", 2);
    saveIpPortFromEnumBtn = new QPushButton(tr("setIpPort()"), this);
    ipPortToStringLbl = new QLabel();
    ipPortToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    headerLayout->addWidget(ipPortLbl, 9, 0);
    headerLayout->addWidget(ipPortSpBox, 9, 1);
    headerLayout->addWidget(saveIpPortFromNumberBtn, 9, 2);
    headerLayout->addWidget(ipPortCmbBx, 9, 3, 1, 2);
    headerLayout->addWidget(saveIpPortFromEnumBtn, 9, 5, 1, 2);
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

    headerSizeSpBox = new QSpinBox(headerGBox);
    headerSizeSpBox->setFixedSize(180, 30);
    headerSizeSpBox->setRange(0, 255);

    saveHeaderSizeBtn = new QPushButton(tr("setHeaderSize()"), this);

    headerUpdateLbl = new QLabel(tr("HeaderData (0-255): "));
    headerUpdateLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    updateHeaderSizeBtn = new QPushButton(tr("updateHeaderSize()"), this);

    headerSizeToNumLbl = new QLabel();
    headerSizeToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(headerSizeLbl, 12, 0);
    headerLayout->addWidget(headerSizeSpBox, 12, 1);
    headerLayout->addWidget(saveHeaderSizeBtn, 12, 2);
    headerLayout->addWidget(headerUpdateLbl, 12, 3, 1, 2);
    headerLayout->addWidget(updateHeaderSizeBtn, 12, 5, 1, 2);
    headerLayout->addWidget(headerSizeToNumLbl, 12, 7);


    // HEADER DATA
    headerDataLbl = new QLabel(tr("HeaderData (1): "));
    headerDataLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    saveHeaderDataBtn = new QPushButton(tr("setHeaderData()"), this);

    headerDataTxtEdt = new QTextEdit(headerGBox);
    headerDataTxtEdt->setReadOnly(false);

    headerDataToStringLbl = new QLabel();
    headerDataToStringLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    headerLayout->addWidget(headerDataLbl, 13, 0);
    headerLayout->addWidget(saveHeaderDataBtn, 13, 1);

    headerLayout->addWidget(headerDataTxtEdt, 14, 0, 1, 7);

    headerLayout->addWidget(headerDataToStringLbl, 15, 0, 1, 7);



    contextGBox = new QGroupBox("Contextinformation");
    contextGBox->setLayout(contextLayout);
    mainLayout->addWidget(contextGBox);

    dataGBox = new QGroupBox("Application Data");
    dataGBox->setLayout(dataLayout);
    mainLayout->addWidget(dataGBox);



    // Raw CIP Layout
    rawCIPLayout = new QGridLayout;
    rawCIPGBox = new QGroupBox("Raw CIP Data");
    rawCIPGBox->setLayout(rawCIPLayout);
    mainLayout->addWidget(rawCIPGBox);

    rawCIPTxtEdt = new QTextEdit(rawCIPGBox);
    rawCIPTxtEdt->setStyleSheet ("font: 9pt; Monospace;");
    rawCIPTxtEdt->setReadOnly(true);
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

    connect(setCurrentTimeBtn, &QAbstractButton::clicked, this, &MainWindow::setCurrentTime);

    connect(saveHeaderTypeFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromNumber);
    connect(saveHeaderTypeFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderTypeFromEnum);

    connect(saveHeaderSizeBtn, &QAbstractButton::clicked, this, &MainWindow::setHeaderSize);
    connect(updateHeaderSizeBtn, &QAbstractButton::clicked, this, &MainWindow::updateHeaderSize);


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

    ipPortSpBox->setValue(currentCIP->getIpPort());
    ipPortCmbBx->setCurrentIndex(getIndexForIpPortCmbBx());

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
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderTypeFromEnum() to %1\n%2")
                               .arg(headerTypeCmbBx->currentText())
                               .arg(currentCIP->bytesToString()));
}

// HEADER SIZE FUNCTIONS
void MainWindow::refreshHeaderSizeDisplay() {
    qDebug() << "refreshHeaderSizeDisplay()";

    headerSizeSpBox->setValue(currentCIP->getHeaderSize());
    headerSizeToNumLbl->setText(QString("%1").arg(currentCIP->getHeaderSize()));
}

void MainWindow::setHeaderSize() {
    qDebug() << "setHeaderSize()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }

    currentCIP->setHeaderSize(headerSizeSpBox->value());
    currentCIP->pack();

    refreshHeaderSizeDisplay();
    rawCIPTxtEdt->setPlainText(QString("CIP loaded after changed by setHeaderSize() to %1\n%2")
                               .arg(headerSizeSpBox->value())
                               .arg(currentCIP->bytesToString()));

}

void MainWindow::updateHeaderSize() {
    qDebug() << "updateHeaderSize()";

    if(currentCIP == NULL) {
        qDebug() << "currentCIP == NULL -> return";
        return;
    }
}
