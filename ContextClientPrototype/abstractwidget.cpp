#include "abstractwidget.h"

#include "abstractreader.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QPushButton>
#include <QScrollArea>

AbstractWidget::AbstractWidget(QWidget *parent)
    : QTabWidget(parent)
{
    qDebug() << "AbstractWidget::AbstractWidget(QWidget *parent)";

    // GUI - Header - XML
    xmlFileLbl = new QLabel(tr("File"));
    xmlFileLnEd = new QLineEdit;
    xmlFileLbl->setBuddy(xmlFileLnEd);

    versionLbl = new QLabel(tr("Version"));
    versionLnEd = new QLineEdit;
    versionLbl->setBuddy(versionLnEd);

    encodingLbl = new QLabel(tr("Encoding"));
    encodingLnEd = new QLineEdit;
    encodingLbl->setBuddy(encodingLnEd);

    guiHeaderXmlLayout = new QGridLayout;
    guiHeaderXmlLayout->addWidget(xmlFileLbl, 0, 0);
    guiHeaderXmlLayout->addWidget(xmlFileLnEd, 0, 1);
    guiHeaderXmlLayout->addWidget(versionLbl, 1, 0);
    guiHeaderXmlLayout->addWidget(versionLnEd, 1, 1);
    guiHeaderXmlLayout->addWidget(encodingLbl, 2, 0);
    guiHeaderXmlLayout->addWidget(encodingLnEd, 2, 1);

    guiHeaderXmlGBox = new QGroupBox("XML");
    guiHeaderXmlGBox->setLayout(guiHeaderXmlLayout);


    // GUI - Header - Doctype
    nameLbl = new QLabel(tr("Name"));
    nameLnEd = new QLineEdit;
    nameLbl->setBuddy(nameLnEd);

    typeLbl = new QLabel(tr("Type"));
    typeLnEd = new QLineEdit;
    typeLbl->setBuddy(typeLnEd);

    fileLbl = new QLabel(tr("File"));
    dtdFileLnEd = new QLineEdit;
    fileLbl->setBuddy(dtdFileLnEd);

    guiHeaderDoctypeLayout = new QGridLayout;
    guiHeaderDoctypeLayout->addWidget(nameLbl, 0, 0);
    guiHeaderDoctypeLayout->addWidget(nameLnEd, 0, 1);
    guiHeaderDoctypeLayout->addWidget(typeLbl, 1, 0);
    guiHeaderDoctypeLayout->addWidget(typeLnEd, 1, 1);
    guiHeaderDoctypeLayout->addWidget(fileLbl, 2, 0);
    guiHeaderDoctypeLayout->addWidget(dtdFileLnEd, 2, 1);

    guiHeaderDoctypeGBox = new QGroupBox("Doctype");
    guiHeaderDoctypeGBox->setLayout(guiHeaderDoctypeLayout);


    // GUI - Header
    guiHeaderLayout = new QHBoxLayout;
    guiHeaderLayout->addWidget(guiHeaderXmlGBox);
    guiHeaderLayout->addWidget(guiHeaderDoctypeGBox);


    // GUI - Layout
    guiLayout = new QVBoxLayout;
    guiLayout->addLayout(guiHeaderLayout);


    // GUI - Widget
    guiWidget = new QWidget;
    guiWidget->setLayout(guiLayout);


    // GUI - ScrollArea
    guiScrollArea = new QScrollArea;
    guiScrollArea->setWidget(guiWidget);
    guiScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setWidgetResizable(true);

    addTab(guiScrollArea, tr("GUI"));


    // XML - Text
    xmlEdit = new QTextEdit();


    // XML - Layout
    xmlLayout = new QVBoxLayout;
    xmlLayout->addWidget(xmlEdit);


    // XML - Widget
    xmlWidget = new QWidget;
    xmlWidget->setLayout(xmlLayout);

    // XML - ScrollArea
    xmlScrollArea = new QScrollArea;
    xmlScrollArea->setWidget(xmlWidget);
    xmlScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    xmlScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    xmlScrollArea->setWidgetResizable(true);

    // XML - Tab
    addTab(xmlScrollArea, tr("XML"));

//    showMinimized();
//    showMaximized();
}

bool AbstractWidget::loadFile(QString fileName) {
    qDebug() << "AbstractWidget::loadFile(QString fileName)";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    file.setObjectName(fileName);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    AbstractReader *reader = new AbstractReader();
    reader->read(&file, this);
    file.reset();

    QTextStream in(&file);
    setXml(in.readAll());

    QApplication::restoreOverrideCursor();

    return true;
}

void AbstractWidget::loadGuiInteraction() {
    qDebug() << "AbstractWidget::loadGuiInteraction()";

//    QHBoxLayout *buttonLayout = new QHBoxLayout;

//    QPushButton *reloadBtn = new QPushButton(tr("Reload"), this);
//    buttonLayout->addWidget(reloadBtn);

//    guiLayout->addLayout(buttonLayout);

}


void AbstractWidget::addNextLayout(QLayout *nextLayout) {
    qDebug() << "AbstractWidget::addNextLayout(nextLayout)";

    guiLayout->addLayout(nextLayout);
}
