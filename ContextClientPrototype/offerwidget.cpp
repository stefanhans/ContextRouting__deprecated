#include "offerwidget.h"
#include "abstractwidget.h"

#include "mainwindow.h"
#include "offerreader.h"
#include "offerwriter.h"
#include "abstractcodingelement.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUuid>

#include <string.h>

OfferWidget::OfferWidget(QWidget *parent)
    : AbstractWidget(parent)
{
    // Offer - Offer
    offerNameLbl = new QLabel(tr("Name"));
    offerNameLnEd = new QLineEdit;
    offerNameLbl->setBuddy(offerNameLnEd);

    offerCreateDateLbl = new QLabel(tr("Created"));
    offerCreateDateLnEd = new QLineEdit;
    offerCreateDateLbl->setBuddy(offerCreateDateLnEd);

    offerLanguageLbl = new QLabel(tr("Language"));
    offerLanguageLnEd = new QLineEdit;
    offerLanguageLbl->setBuddy(offerLanguageLnEd);

    offerLayout = new QGridLayout;
    offerLayout->addWidget(offerNameLbl, 0, 0);
    offerLayout->addWidget(offerNameLnEd, 0, 1);
    offerLayout->addWidget(offerCreateDateLbl, 0, 2);
    offerLayout->addWidget(offerCreateDateLnEd, 0, 3);
    offerLayout->addWidget(offerLanguageLbl, 0, 4);
    offerLayout->addWidget(offerLanguageLnEd, 0, 5);

    //  service="1" serviceName="Offer" version="0" channel="0" optionalSize="0" uuid="287477b1e629498bb224746524d841" ip_address="Not yet"

    // Offer - Header
    headerServiceNameLbl = new QLabel(tr("Service"));
    headerServiceNameLnEd = new QLineEdit;
    headerServiceNameLbl->setBuddy(headerServiceNameLnEd);

    headerServiceLbl = new QLabel(tr("Service Id"));
    headerServiceLnEd = new QLineEdit;
    headerServiceLbl->setBuddy(headerServiceLnEd);

    headerVersionLbl = new QLabel(tr("Version"));
    headerVersionLnEd = new QLineEdit;
    headerVersionLbl->setBuddy(headerVersionLnEd);

    headerChannelLbl = new QLabel(tr("Channel"));
    headerChannelLnEd = new QLineEdit;
    headerChannelLbl->setBuddy(headerChannelLnEd);

    headerOptionalSizeLbl = new QLabel(tr("Optional Size"));
    headerOptionalSizeLnEd = new QLineEdit;
    headerOptionalSizeLbl->setBuddy(headerOptionalSizeLnEd);

    headerUuidLbl = new QLabel(tr("UUID"));
    headerUuidLnEd = new QLineEdit;
    headerUuidLbl->setBuddy(headerUuidLnEd);

    headerIpAddressLbl = new QLabel(tr("IP Address"));
    headerIpAddressLnEd = new QLineEdit;
    headerIpAddressLbl->setBuddy(headerIpAddressLnEd);

    headerLayout = new QGridLayout;
    headerLayout->addWidget(headerServiceNameLbl, 0, 0);
    headerLayout->addWidget(headerServiceNameLnEd, 0, 1);
    headerLayout->addWidget(headerServiceLbl, 0, 2);
    headerLayout->addWidget(headerServiceLnEd, 0, 3);
    headerLayout->addWidget(headerVersionLbl, 0, 4);
    headerLayout->addWidget(headerVersionLnEd, 0, 5);

    headerLayout->addWidget(headerChannelLbl, 1, 0);
    headerLayout->addWidget(headerChannelLnEd,1, 1);
    headerLayout->addWidget(headerOptionalSizeLbl, 1, 2);
    headerLayout->addWidget(headerOptionalSizeLnEd, 1, 3);
    headerLayout->addWidget(headerUuidLbl, 1, 4);
    headerLayout->addWidget(headerUuidLnEd, 1, 5);

    headerLayout->addWidget(headerIpAddressLbl, 2, 0);
    headerLayout->addWidget(headerIpAddressLnEd, 2, 1);


    // Datagram
    datagramListSizeLbl = new QLabel(tr("List Size"));
    datagramListSizeLnEd = new QLineEdit;
    datagramListSizeLbl->setBuddy(datagramListSizeLnEd);

    datagramTypeLbl = new QLabel(tr("Type"));
    datagramTypeLnEd = new QLineEdit;
    datagramTypeLbl->setBuddy(datagramTypeLnEd);

    datagramLayout = new QGridLayout;
    datagramLayout->addWidget(datagramListSizeLbl, 0, 0);
    datagramLayout->addWidget(datagramListSizeLnEd, 0, 1);
    datagramLayout->addWidget(datagramTypeLbl, 0, 2);
    datagramLayout->addWidget(datagramTypeLnEd, 0, 3);

    // Offer
    mainLayout = new QVBoxLayout;
    offerGBox = new QGroupBox("Offer");
    offerGBox->setLayout(offerLayout);
    mainLayout->addWidget(offerGBox);

    headerGBox = new QGroupBox("Header");
    headerGBox->setLayout(headerLayout);
    mainLayout->addWidget(headerGBox);

    datagramGBox = new QGroupBox("Datagram");
    datagramGBox->setLayout(datagramLayout);
    mainLayout->addWidget(datagramGBox);

//    dataGBox = new QGroupBox("Data");
//    dataGBox->setLayout(dataLayout);
//    mainLayout->addWidget(dataGBox);

    addNextLayout(mainLayout);
}

bool OfferWidget::loadFile(QString fileName) {
    qDebug() << "OfferWidget::loadFile(QString fileName)";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    file.setObjectName(fileName);

//    codingElementCount = 0;
//    codingElementSize = 0;

    reader = new OfferReader();
    reader->read(&file, this);
    file.reset();

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setXml(in.readAll());
    QApplication::restoreOverrideCursor();

    return true;
}

//void OfferWidget::loadGuiInteraction() {
//    qDebug() << "OfferWidget::loadGuiInteraction()";

//    // Interaction - Choose
//    nameLbl = new QLabel(tr("Name"));
//    nameLnEd = new QLineEdit;
//    nameLnEd->setMaxLength(30);
//    nameLnEd->setMinimumWidth(260);
//    nameLnEd->setMaximumWidth(260);
//    nameLbl->setBuddy(nameLnEd);

//    actionLbl = new QLabel(tr("Action"));
//    actionCBx = new QComboBox(this);
//    actionCBx->addItem("Offer", 1);
//    actionCBx->addItem("Request", 2);
//    actionCBx->setMinimumWidth(260);
//    actionLbl->setBuddy(actionCBx);

//    dataTypeLbl = new QLabel(tr("Datatype"));
//    dataTypeCBx = new QComboBox(this);
//    dataTypeCBx->addItem("Text", 1);
//    dataTypeCBx->addItem("URL", 2);
//    dataTypeCBx->setMinimumWidth(260);
//    dataTypeLbl->setBuddy(dataTypeCBx);

//    dataLbl = new QLabel(dataTypeCBx->currentText());
//    dataTxtEd = new QTextEdit(this);

//    // Interaction - Button
//    saveBtn = new QPushButton(tr("Save"), this);
//    sendBtn = new QPushButton(tr("Send"), this);

//    actionLayout = new QGridLayout;
//    actionLayout->addWidget(nameLbl, 0, 0);
//    actionLayout->addWidget(nameLnEd, 0, 1);
//    actionLayout->addWidget(actionLbl, 1, 0);
//    actionLayout->addWidget(actionCBx, 1, 1);
//    actionLayout->addWidget(dataTypeLbl, 2, 0);
//    actionLayout->addWidget(dataTypeCBx, 2, 1);
//    actionLayout->addWidget(dataLbl, 0, 2);
//    actionLayout->addWidget(dataTxtEd, 1, 2, 2, 1);

//    actionLayout->addWidget(saveBtn, 3, 0, 1, 3);
//    actionLayout->addWidget(sendBtn, 4, 0, 1, 3);


//    // Interaction
//    interactionGBox = new QGroupBox(tr("Interaction"));
//    interactionGBox->setLayout(actionLayout);

//    interactionLayout = new QVBoxLayout;
//    interactionLayout->addWidget(interactionGBox);

//    addNextLayout(interactionLayout);

//    connect(dataTypeCBx, SIGNAL(currentTextChanged(QString)), dataLbl, SLOT(setText(QString)));
//    connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(saveContext()));
//    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendContext()));
//    connect(this, SIGNAL(requestContextData()), reader, SIGNAL(requestContextData()));

//    connect(reader, SIGNAL(answerContextData(QList<QVariant>)), this, SLOT(receiveSelectedDictData(QList<QVariant>)));

////        QScrollArea *scroll=new QScrollArea;
//////        scroll->setParent(this->widget(0));
//////        scroll->setGeometry(guiWidget->parentWidget()->geometry());
////        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
////        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
////        scroll->setWidget(guiWidget);
////        scroll->show();

//}


//void OfferWidget::sendContext() {
//    qDebug() << "OfferWidget::sendContext()";

//    // Check name is not empty
//    if(nameLnEd->text().isEmpty()) {
//        QMessageBox::warning(this, tr("Send"), tr("Name is empty!"));
//        return;
//    }

//    emit requestContextData();

//    // UUID - Generate
//    uuid_t uuid;
//    uuid_generate(uuid);
//    uuid_copy(this->sourceUuid, uuid);

//    // UUID - QString
//    QString uuidString;
//    size_t s;
//    for (s = 0; s < sizeof(sourceUuid) - 1; s++) {
//        uuidString += QString("%1").arg(sourceUuid[s], 0, 16);
//    }

//    // QUuid - Create
////    QUuid myuuid = QUuid::createUuid();


//    // Internal
//    qDebug() << "nameLnEd->text(): " << nameLnEd->text();
//    qDebug() << "actionCBx->currentData().toInt(): " << actionCBx->currentData().toInt();
//    qDebug() << "dataTypeCBx->currentData().toInt(): " << dataTypeCBx->currentData().toInt();
//    qDebug() << "dataTxtEd->toPlainText(): " << dataTxtEd->toPlainText();

//    // Context Header
//    qDebug() << "Context Header: service (1): " << actionCBx->currentData().toInt();
//    qDebug() << "Context Header: version (1): " << 0;
//    qDebug() << "Context Header: channel (1): " << 0;
//    qDebug() << "Context Header: opt. size (1): " << 0;
//    qDebug() << "Context Header: UUID (16): " << uuidString;
//    qDebug() << "Context Header: IP address (4): " << "";


////    qDebug() << "Context Header: UUID (16): " << myuuid.toString();

////    qDebug() << "Context Header: UUID (16): " << res.c_str();
////    qDebug() << "Context Header: UUID (16): " << myuuid.toByteArray();
////    qDebug() << "Context Header: UUID (16): " << myuuid.toByteArray().data();
////    qDebug() << "Context Header: UUID (16): " << (unsigned char*)(myuuid.toByteArray().data());
////    qDebug() << "Context Header: UUID (16): " << sizeof(sourceUuid);
////    qDebug() << "Context Header: UUID (16): " << sizeof(myuuid);

//    // Context Bricks
//    qDebug() << "Context Datagram: list size (1): " << getCodingElementSize()*2;
//    qDebug() << "Context Datagram: type (1): " << codingIdLnEd->text().toInt();

//    for(int i = 0; i<contextBrickList.size(); i++) {

//        qDebug() << "Context Datagram " << i << ": content (1): " << contextBrickList[i].first;
//        qDebug() << "Context Datagram " << i << ": mask (1): " << contextBrickList[i].second;
//    }

//    // Context Data
//    QString truncData = dataTxtEd->toPlainText();
//    truncData.truncate(140);
//    qDebug() << "Context Data: type (1): " << dataTypeCBx->currentData().toInt();
//    qDebug() << "Context Data: data (140): " << truncData;
//    qDebug() << "Context Data: opt. size (1): " << 0;
//}

//void OfferWidget::receiveSelectedDictData(QList<QVariant> data) {
//    qDebug() << "OfferWidget::receiveSelectedDictData(QList<QVariant> data)";


//    for(int j=0; j<data.size(); j++) {
//        qDebug() << "OfferWidget::receiveSelectedDictData(QList<QVariant> data): data.at(" << j << ").toString(): " << data.at(j).toString();
//    }

//    contextDatagramList.push_back(data);

////    for(int i=0; i<data.size(); i++) {
////        qDebug() << "data.at(" << i << ").toString(): " << data.at(i).toString();
////    }

////    for(int i=2; i<data.size(); i+=2) {
////        qDebug() << "data.at(" << i << ").toString(): " << data.at(i).toString();
////        qDebug() << "data.at(" << i+1 << ").toString(): " << data.at(i+1).toString();

////        quint8 content(data.at(i).toInt());
////        quint8 mask(data.at(i+1).toInt());
////        QPair<quint8, quint8> brick(content, mask);

////        contextBrickList.push_back(brick);
////    }
//}

//void OfferWidget::saveContext() {
//    qDebug() << "OfferWidget::saveContext()";

//    // Check name is not empty
//    if(nameLnEd->text().isEmpty()) {
//        QMessageBox::warning(this, tr("Save Context"), tr("Name is empty!"));
//        return;
//    }

//    // Load data in contextDatagramList via slot "answerContextData(QList<QVariant>)"
//    contextDatagramList.clear();
//    emit requestContextData();

//    if(actionCBx->currentText() == "Offer") {

//        QString fileName = QString("%1/Offers/%2.%3").arg(PROTO_DIR).arg(nameLnEd->text()).arg("cof");
//        fileName.replace(QString(" "), QString(""));

//        QFile file(fileName);
//        if (!file.open(QFile::WriteOnly | QFile::Text)) {
//            QMessageBox::warning(this, tr("Save Context"),
//                                 tr("Cannot write file %1:\n%2.")
//                                 .arg(fileName)
//                                 .arg(file.errorString()));
//            return;
//        }

//        writer = new OfferWriter();
//        ((OfferWriter*) writer)->write(&file, this);

//        return;
//    }
//}


//// Coding - Id
//QString OfferWidget::getCodingId() const {
//    return codingIdLnEd->text();
//}
//void OfferWidget::setCodingId(QString codingId) {
//    codingIdLnEd->setText(codingId);
//}

//// Coding - Name
//QString OfferWidget::getCodingName() const {
//    return codingNameLnEd->text();
//}
//void OfferWidget::setCodingName(QString codingName) {
//    codingNameLnEd->setText(codingName);
//}

//// Coding - Language
//QString OfferWidget::getCodingLanguage() const {
//    return codingLanguageLnEd->text();
//}
//void OfferWidget::setCodingLanguage(QString codingLanguage) {
//    codingLanguageLnEd->setText(codingLanguage);
//}

//// Coding - ElementCount
//int OfferWidget::getCodingElementCount() const {
//    return codingElementCount;
//}
//void OfferWidget::setCodingElementCount(int count) {
//    codingElementCount = count;
//}

//// Coding - ElementSize
//int OfferWidget::getCodingElementSize() const {
//    return codingElementSize;
//}

//void OfferWidget::setCodingElementSize(int size) {
//    codingElementSize = size;
//}
