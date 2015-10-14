#include "requestwidget.h"

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

RequestWidget::RequestWidget(QWidget *parent)
    : AbstractWidget(parent)
{
    // Request - Request
    requestNameLbl = new QLabel(tr("Name"));
    requestNameLnEd = new QLineEdit;
    requestNameLbl->setBuddy(requestNameLnEd);

    requestCreateDateLbl = new QLabel(tr("Created"));
    requestCreateDateLnEd = new QLineEdit;
    requestCreateDateLbl->setBuddy(requestCreateDateLnEd);

    requestLanguageLbl = new QLabel(tr("Language"));
    requestLanguageLnEd = new QLineEdit;
    requestLanguageLbl->setBuddy(requestLanguageLnEd);

    requestLayout = new QGridLayout;
    requestLayout->addWidget(requestNameLbl, 0, 0);
    requestLayout->addWidget(requestNameLnEd, 0, 1);
    requestLayout->addWidget(requestCreateDateLbl, 0, 2);
    requestLayout->addWidget(requestCreateDateLnEd, 0, 3);
    requestLayout->addWidget(requestLanguageLbl, 0, 4);
    requestLayout->addWidget(requestLanguageLnEd, 0, 5);

    //  service="1" serviceName="Request" version="0" channel="0" optionalSize="0" uuid="287477b1e629498bb224746524d841" ip_address="Not yet"

    // Request - Header
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
    headerLayout->addWidget(headerIpAddressLbl, 1, 4);
    headerLayout->addWidget(headerIpAddressLnEd, 1, 5);


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

    // Request
    mainLayout = new QVBoxLayout;
    requestGBox = new QGroupBox("Request");
    requestGBox->setLayout(requestLayout);
    mainLayout->addWidget(requestGBox);

    headerGBox = new QGroupBox("Header");
    headerGBox->setLayout(headerLayout);
    mainLayout->addWidget(headerGBox);

    datagramGBox = new QGroupBox("Datagram");
    datagramGBox->setLayout(datagramLayout);
    mainLayout->addWidget(datagramGBox);

    addNextLayout(mainLayout);
}

bool RequestWidget::loadFile(QString fileName) {
    qDebug() << "RequestWidget::loadFile(QString fileName)";

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

    reader = new RequestReader();
    reader->read(&file, this);
    file.reset();

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setXml(in.readAll());
    QApplication::restoreOverrideCursor();

    return true;
}


void RequestWidget::loadGuiInteraction() {
    qDebug() << "RequestWidget::loadGuiInteraction()";

}


void RequestWidget::sendContext() {
    qDebug() << "RequestWidget::sendContext()";
}
