#include "abstractwidget.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QPushButton>
#include <QScrollArea>
#include <QXmlSchema>
#include <QAbstractMessageHandler>
#include <QXmlSchemaValidator>

class MessageHandler : public QAbstractMessageHandler
{
public:
    MessageHandler()
        : QAbstractMessageHandler(0)
    {
    }

    QString statusMessage() const
    {
        return m_description;
    }

    int line() const
    {
        return m_sourceLocation.line();
    }

    int column() const
    {
        return m_sourceLocation.column();
    }

protected:
    virtual void handleMessage(QtMsgType type, const QString &description,
                               const QUrl &identifier, const QSourceLocation &sourceLocation)
    {
        Q_UNUSED(type);
        Q_UNUSED(identifier);

        m_messageType = type;
        m_description = description;
        m_sourceLocation = sourceLocation;
    }

private:
    QtMsgType m_messageType;
    QString m_description;
    QSourceLocation m_sourceLocation;
};

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


    // GUI - NamespaceURI
    guiNamespaceUriLnEd = new QLineEdit;
    guiNamespaceUriLayout = new QHBoxLayout;
    guiNamespaceUriLayout->addWidget(guiNamespaceUriLnEd);

    guiNamespaceUriGBox = new QGroupBox(tr("Namespace URI"));
    guiNamespaceUriGBox->setLayout(guiNamespaceUriLayout);

    // GUI - Layout
    guiLayout = new QVBoxLayout;
    guiLayout->addLayout(guiHeaderLayout);
    guiLayout->addWidget(guiNamespaceUriGBox);


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
    xmlFileTxtEd = new QTextEdit();

    xmlFileLayout = new QHBoxLayout;
    xmlFileLayout->addWidget(xmlFileTxtEd);

    xmlFileGBox = new QGroupBox(tr("XML File"));
    xmlFileGBox->setLayout(xmlFileLayout);

    // XML - XML Validator
    xmlValidatorLbl = new QLabel(tr("XML File"));
    xmlValidatorLnEd = new QLineEdit;
    xmlValidateBtn = new QPushButton(tr("Validate"));
    xmlValidatorResultLnEd = new QLineEdit;
    xmlValidatorResultLnEd->setEnabled(true);
    xmlSaveBtn = new QPushButton(tr("Save"));

    xmlValidatorLayout = new QGridLayout;
    xmlValidatorLayout->addWidget(xmlValidatorLbl, 0, 0);
    xmlValidatorLayout->addWidget(xmlValidatorLnEd, 0, 1);
    xmlValidatorLayout->addWidget(xmlValidateBtn, 0, 2);
    xmlValidatorLayout->addWidget(xmlValidatorResultLnEd, 0, 3);
    xmlValidatorLayout->addWidget(xmlSaveBtn, 0, 4);

    xmlValidatorGBox = new QGroupBox("XML Validator");
    xmlValidatorGBox->setLayout(xmlValidatorLayout);


    // XML - XSD file
    xsdFileTxtEd = new QTextEdit;
    xsdFileTxtEd->setReadOnly( ! XSD_ENABLED);

    xsdFileLayout = new QHBoxLayout;
    xsdFileLayout->addWidget(xsdFileTxtEd);

    xsdFileGBox = new QGroupBox(tr("XSD File"));
    xsdFileGBox->setLayout(xsdFileLayout);


    // XML - XSD Validator
    xsdValidatorLbl = new QLabel(tr("XSD File"));
    xsdValidatorLnEd = new QLineEdit;
    xsdValidateBtn = new QPushButton(tr("Validate"));
    xsdValidatorResultLnEd = new QLineEdit;
    xsdValidatorResultLnEd->setEnabled(false);
    xsdSaveBtn = new QPushButton(tr("Save"));

    xsdValidatorLayout = new QGridLayout;
    xsdValidatorLayout->addWidget(xsdValidatorLbl, 0, 0);
    xsdValidatorLayout->addWidget(xsdValidatorLnEd, 0, 1);
    xsdValidatorLayout->addWidget(xsdValidateBtn, 0, 2);
    xsdValidatorLayout->addWidget(xsdValidatorResultLnEd, 0, 3);
    xsdValidatorLayout->addWidget(xsdSaveBtn, 0, 4);

    xsdValidatorGBox = new QGroupBox("XSD Validator");
    xsdValidatorGBox->setEnabled(XSD_ENABLED);
    xsdValidatorGBox->setLayout(xsdValidatorLayout);

    // XML - Layout
    xmlLayout = new QVBoxLayout;
    xmlLayout->addWidget(xmlFileGBox);
    xmlLayout->addWidget(xmlValidatorGBox);
    xmlLayout->addWidget(xsdFileGBox);
    xmlLayout->addWidget(xsdValidatorGBox);


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

    connect(xmlValidateBtn, SIGNAL(clicked(bool)), this, SLOT(validateXml(bool)));
    connect(xmlSaveBtn, SIGNAL(clicked(bool)), this, SLOT(saveXmlFile(bool)));

    connect(xsdValidateBtn, SIGNAL(clicked(bool)), this, SLOT(validateXsd(bool)));
    connect(xsdSaveBtn, SIGNAL(clicked(bool)), this, SLOT(saveXsdFile(bool)));
}


void AbstractWidget::setNamespaceUri(QString namespaceUri) {
    guiNamespaceUriLnEd->setText(namespaceUri);

    QUrl xmlns(namespaceUri);

    if(xmlns.isLocalFile()) {
        xsdValidatorLnEd->setText(xmlns.toLocalFile().replace(QString("//"), QString("/")));
    }
    else {
        xsdValidatorLnEd->setText(namespaceUri);
        xsdSaveBtn->setEnabled(true);
    }
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

    // GUI
    AbstractReader *reader = new AbstractReader();
    reader->read(&file, this);
    file.reset();

    // XML
    QTextStream in(&file);
    setXml(in.readAll());

    // XSD
    QFile xsdFile(getXsdFilename());
    qDebug() << "getXsdFilename()): " << getXsdFilename();
    if (!xsdFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(getXsdFilename())
                             .arg(xsdFile.errorString()));
        return false;
    }
    QTextStream inXsd(&xsdFile);
    setXsd(inXsd.readAll());

    setXsd("Test");

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

void AbstractWidget::saveXmlFile(bool b) {
    qDebug() << "AbstractWidget::saveXmlFile()";

    QFile file(xmlFileLnEd->text());
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write to file %1:\n%2.")
                             .arg(xmlFileLnEd->text())
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << xmlFileTxtEd->toPlainText().toUtf8();
}

void AbstractWidget::validateXml(bool b) {
    qDebug() << "AbstractWidget::validateXml(bool b)";

    const QByteArray xsdData = xsdFileTxtEd->toPlainText().toUtf8();
    const QByteArray xmlData = xmlFileTxtEd->toPlainText().toUtf8();

    MessageHandler messageHandler;

    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);

    schema.load(xsdData);


    bool errorOccurred = false;
    if (!schema.isValid()) {
        errorOccurred = true;
    } else {
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(xmlData))
            errorOccurred = true;
    }

    if (errorOccurred) {
        xmlValidatorResultLnEd->setText(messageHandler.statusMessage());
//        moveCursor(messageHandler.line(), messageHandler.column());
    } else {
        xmlValidatorResultLnEd->setText(tr("validation successful"));
    }

}

void AbstractWidget::saveXsdFile(bool b) {
    qDebug() << "AbstractWidget::saveXsdFile(" << dtdFileLnEd->text() << ")";

    QFile file(xsdValidatorLnEd->text());
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write to file %1:\n%2.")
                             .arg(xsdValidatorLnEd->text())
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << xsdFileTxtEd->toPlainText().toUtf8();

}

void AbstractWidget::validateXsd(bool b) {
    qDebug() << "AbstractWidget::validateXsd(bool b)";

    QUrl schemaUrl(xsdValidatorLnEd->text());

    QXmlSchema schema;
    schema.load(schemaUrl);
}
