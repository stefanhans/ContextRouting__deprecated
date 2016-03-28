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

    // SERVICE
    serviceLbl = new QLabel(tr("Service: "));
    serviceLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    serviceToNumLbl = new QLabel();
    serviceToNumLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    serviceToStringLbl = new QLabel();
    serviceToStringLbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    headerLayout->addWidget(serviceLbl, 0, 0);
    headerLayout->addWidget(serviceToNumLbl, 0, 5);
    headerLayout->addWidget(serviceToStringLbl, 0, 6);

    // REQUEST
    requestLbl = new QLabel(tr("Request: "));
    requestLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    requestSpBox = new QSpinBox(headerGBox);
    requestSpBox->setFixedSize(180, 30);
    requestSpBox->setRange(0, 255);

    saveRequestFromNumberBtn = new QPushButton(tr("setRequest()"), this);

    requestCmbBx = new QComboBox(headerGBox);
    requestCmbBx->setFixedSize(180, 30);
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

    headerLayout->addWidget(requestLbl, 1, 0);
    headerLayout->addWidget(requestSpBox, 1, 1);
    headerLayout->addWidget(saveRequestFromNumberBtn, 1, 2);
    headerLayout->addWidget(requestCmbBx, 1, 3);
    headerLayout->addWidget(saveRequestFromEnumBtn, 1, 4);
    headerLayout->addWidget(requestToNumLbl, 1, 5);
    headerLayout->addWidget(requestToStringLbl, 1, 6);

    headerLayout->setColumnStretch(7, 5);


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


    connect(createBtn, &QAbstractButton::clicked, this, &MainWindow::createCIP);

    connect(openBtn, &QAbstractButton::clicked, this, &MainWindow::openCIP);
    connect(saveBtn, &QAbstractButton::clicked, this, &MainWindow::saveCIP);


    connect(saveRequestFromNumberBtn, &QAbstractButton::clicked, this, &MainWindow::setRequestFromNumber);
    connect(saveRequestFromEnumBtn, &QAbstractButton::clicked, this, &MainWindow::setRequestFromEnum);


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
