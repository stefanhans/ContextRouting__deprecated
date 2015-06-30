#include "codingwidget.h"

#include "mainwindow.h"
#include "codingreader.h"
#include "offerwriter.h"
#include "requestwriter.h"
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

CodingWidget::CodingWidget(QWidget *parent)
    : AbstractWidget(parent)
{
    qDebug() << "CodingWidget::CodingWidget(QWidget *parent)";

    // GUI - Coding - Coding
    codingIdLbl = new QLabel(tr("Identifier"));
    codingIdLnEd = new QLineEdit;
    codingIdLbl->setBuddy(codingIdLnEd);

    codingNameLbl = new QLabel(tr("Name"));
    codingNameLnEd = new QLineEdit;
    codingNameLbl->setBuddy(codingNameLnEd);

    codingLanguageLbl = new QLabel(tr("Language"));
    codingLanguageLnEd = new QLineEdit;
    codingLanguageLbl->setBuddy(codingLanguageLnEd);

    codingLayout = new QGridLayout;
    codingLayout->addWidget(codingIdLbl, 0, 0);
    codingLayout->addWidget(codingIdLnEd, 0, 1);
    codingLayout->addWidget(codingNameLbl, 0, 2);
    codingLayout->addWidget(codingNameLnEd, 0, 3);
    codingLayout->addWidget(codingLanguageLbl, 0, 4);
    codingLayout->addWidget(codingLanguageLnEd, 0, 5);

    // GUI - Coding
    codLayout = new QVBoxLayout;
    codGBox = new QGroupBox("Coding Header");

    codGBox->setLayout(codingLayout);
    codLayout->addWidget(codGBox);

    addNextLayout(codLayout);
}

bool CodingWidget::loadFile(QString fileName) {
    qDebug() << "CodingWidget::loadFile(QString fileName)";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    file.setObjectName(fileName);

    codingElementCount = 0;
    codingElementSize = 0;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    reader = new CodingReader();
    reader->read(&file, this);
    file.reset();

    QTextStream in(&file);
    setXml(in.readAll());

    QApplication::restoreOverrideCursor();

    return true;
}

void CodingWidget::loadGuiInteraction() {
    qDebug() << "CodingWidget::loadGuiInteraction()";

    // Interaction - Choose
    nameLbl = new QLabel(tr("Name"));
    nameLnEd = new QLineEdit;
    nameLnEd->setMaxLength(30);
    nameLnEd->setMinimumWidth(260);
    nameLnEd->setMaximumWidth(260);
    nameLbl->setBuddy(nameLnEd);

    actionLbl = new QLabel(tr("Action"));
    actionCBx = new QComboBox(this);
    actionCBx->addItem("Offer", 1);
    actionCBx->addItem("Request", 2);
    actionCBx->setMinimumWidth(260);
    actionLbl->setBuddy(actionCBx);

    dataTypeLbl = new QLabel(tr("Datatype"));
    dataTypeCBx = new QComboBox(this);
    dataTypeCBx->addItem("Text", 1);
    dataTypeCBx->addItem("URL", 2);
    dataTypeCBx->setMinimumWidth(260);
    dataTypeLbl->setBuddy(dataTypeCBx);

    dataLbl = new QLabel(dataTypeCBx->currentText());
    dataTxtEd = new QTextEdit(this);

    // Interaction - Button
    saveBtn = new QPushButton(tr("Save"), this);
    sendBtn = new QPushButton(tr("Send"), this);

    actionLayout = new QGridLayout;
    actionLayout->addWidget(nameLbl, 0, 0);
    actionLayout->addWidget(nameLnEd, 0, 1);
    actionLayout->addWidget(actionLbl, 1, 0);
    actionLayout->addWidget(actionCBx, 1, 1);
    actionLayout->addWidget(dataTypeLbl, 2, 0);
    actionLayout->addWidget(dataTypeCBx, 2, 1);
    actionLayout->addWidget(dataLbl, 0, 2);
    actionLayout->addWidget(dataTxtEd, 1, 2, 2, 1);

    actionLayout->addWidget(saveBtn, 3, 0, 1, 3);
    actionLayout->addWidget(sendBtn, 4, 0, 1, 3);


    // Interaction
    interactionGBox = new QGroupBox(tr("Interaction"));
    interactionGBox->setLayout(actionLayout);

    interactionLayout = new QVBoxLayout;
    interactionLayout->addWidget(interactionGBox);

    addNextLayout(interactionLayout);

    connect(dataTypeCBx, SIGNAL(currentTextChanged(QString)), dataLbl, SLOT(setText(QString)));
    connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(saveContext()));
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendContext()));
    connect(this, SIGNAL(requestContextData()), reader, SIGNAL(requestContextData()));

    connect(reader, SIGNAL(answerContextData(QList<QVariant>)), this, SLOT(receiveSelectedDictData(QList<QVariant>)));
}


void CodingWidget::sendContext() {
    qDebug() << "CodingWidget::sendContext()";

    // Check name is not empty
    if(nameLnEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("Send"), tr("Name is empty!"));
        return;
    }

    emit requestContextData();

    // UUID - Generate
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_copy(this->sourceUuid, uuid);

    // UUID - QString
    QString uuidString;
    size_t s;
    for (s = 0; s < sizeof(sourceUuid) - 1; s++) {
        uuidString += QString("%1").arg(sourceUuid[s], 0, 16);
    }

    // QUuid - Create
//    QUuid myuuid = QUuid::createUuid();


    // Internal
    qDebug() << "nameLnEd->text(): " << nameLnEd->text();
    qDebug() << "actionCBx->currentData().toInt(): " << actionCBx->currentData().toInt();
    qDebug() << "dataTypeCBx->currentData().toInt(): " << dataTypeCBx->currentData().toInt();
    qDebug() << "dataTxtEd->toPlainText(): " << dataTxtEd->toPlainText();

    // Context Header
    qDebug() << "Context Header: service (1): " << actionCBx->currentData().toInt();
    qDebug() << "Context Header: version (1): " << 0;
    qDebug() << "Context Header: channel (1): " << 0;
    qDebug() << "Context Header: opt. size (1): " << 0;
    qDebug() << "Context Header: UUID (16): " << uuidString;
    qDebug() << "Context Header: IP address (4): " << "";


//    qDebug() << "Context Header: UUID (16): " << myuuid.toString();

//    qDebug() << "Context Header: UUID (16): " << res.c_str();
//    qDebug() << "Context Header: UUID (16): " << myuuid.toByteArray();
//    qDebug() << "Context Header: UUID (16): " << myuuid.toByteArray().data();
//    qDebug() << "Context Header: UUID (16): " << (unsigned char*)(myuuid.toByteArray().data());
//    qDebug() << "Context Header: UUID (16): " << sizeof(sourceUuid);
//    qDebug() << "Context Header: UUID (16): " << sizeof(myuuid);

    // Context Bricks
    qDebug() << "Context Datagram: list size (1): " << getCodingElementSize()*2;
    qDebug() << "Context Datagram: type (1): " << codingIdLnEd->text().toInt();

    for(int i = 0; i<contextBrickList.size(); i++) {

        qDebug() << "Context Datagram " << i << ": content (1): " << contextBrickList[i].first;
        qDebug() << "Context Datagram " << i << ": mask (1): " << contextBrickList[i].second;
    }

    // Context Data
    QString truncData = dataTxtEd->toPlainText();
    truncData.truncate(140);
    qDebug() << "Context Data: type (1): " << dataTypeCBx->currentData().toInt();
    qDebug() << "Context Data: data (140): " << truncData;
    qDebug() << "Context Data: opt. size (1): " << 0;
}

void CodingWidget::receiveSelectedDictData(QList<QVariant> data) {
    qDebug() << "CodingWidget::receiveSelectedDictData(QList<QVariant> data)";


    for(int j=0; j<data.size(); j++) {
        qDebug() << "CodingWidget::receiveSelectedDictData(QList<QVariant> data): data.at(" << j << ").toString(): " << data.at(j).toString();
    }

    contextDatagramList.push_back(data);

//    for(int i=0; i<data.size(); i++) {
//        qDebug() << "data.at(" << i << ").toString(): " << data.at(i).toString();
//    }

//    for(int i=2; i<data.size(); i+=2) {
//        qDebug() << "data.at(" << i << ").toString(): " << data.at(i).toString();
//        qDebug() << "data.at(" << i+1 << ").toString(): " << data.at(i+1).toString();

//        quint8 content(data.at(i).toInt());
//        quint8 mask(data.at(i+1).toInt());
//        QPair<quint8, quint8> brick(content, mask);

//        contextBrickList.push_back(brick);
//    }
}

void CodingWidget::saveContext() {
    qDebug() << "CodingWidget::saveContext()";

    // Check name is not empty
    if(nameLnEd->text().isEmpty()) {
        QMessageBox::warning(this, tr("Save Context"), tr("Name is empty!"));
        return;
    }

    // Load data in contextDatagramList via slot "answerContextData(QList<QVariant>)"
    contextDatagramList.clear();
    emit requestContextData();

    if(actionCBx->currentText() == "Offer") {

        QString fileName = QString("%1/Offers/%2.%3").arg(PROTO_DIR).arg(nameLnEd->text()).arg("cof");
        fileName.replace(QString(" "), QString(""));

        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Save Context"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
            return;
        }

        writer = new OfferWriter();
        ((OfferWriter*) writer)->write(&file, this);

        return;
    }

    if(actionCBx->currentText() == "Request") {

        QString fileName = QString("%1/Requests/%2.%3").arg(PROTO_DIR).arg(nameLnEd->text()).arg("crq");
        fileName.replace(QString(" "), QString(""));

        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Save Context"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
            return;
        }

        writer = new RequestWriter();
        ((RequestWriter*) writer)->write(&file, this);

        return;
    }
}
