#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include "globals.h"
#include "abstractreader.h"

#include <QWidget>
#include <QTabWidget>
#include <QLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class AbstractWidget : public QTabWidget
{
    Q_OBJECT

public:
    AbstractWidget(QWidget *parent = 0);
    ~AbstractWidget(){}

    virtual bool loadFile(QString fileName);

    virtual void loadGuiInteraction();

    virtual void addNextLayout(QLayout *nextLayout);


    // XML - File
    QString getXmlFile() const {
        return xmlFileLnEd->text();
    }
    void setXmlFile(QString xmlFile) {
        xmlFileLnEd->setText(xmlFile);
        xmlValidatorLnEd->setText(xmlFile);
    }

    // XML - Version
    QString getVersion() const {
        return versionLnEd->text();
    }
    void setVersion(QString version) {
        versionLnEd->setText(version);
    }

    // XML - Encoding
    QString getEncoding() const {
        return encodingLnEd->text();
    }
    void setEncoding(QString encoding) {
        encodingLnEd->setText(encoding);
    }

    // Doctype - Name
    QString getName() const {
        return nameLnEd->text();
    }
    void setName(QString name) {
        nameLnEd->setText(name);
    }

    // Doctype - Type
    QString getType() const {
        return typeLnEd->text();
    }
    void setType(QString type) {
        typeLnEd->setText(type);
    }

    // Doctype - Name
    QString getDtdFile() const {
        return dtdFileLnEd->text();
    }
    void setDtdFile(QString dtdFile) {
        dtdFileLnEd->setText(dtdFile);
    }

    // Namespace URI
    QString getNamespaceUri() const {
        return guiNamespaceUriLnEd->text();
    }
    void setNamespaceUri(QString namespaceUri);

    // XML
    QString getXml() const {
        return xmlFileTxtEd->toPlainText();
    }
    void setXml(QString xml) {
        xmlFileTxtEd->setPlainText(xml);
    }

    // XSD
    QString getXsdFilename() const {
        return xsdValidatorLnEd->text();
    }
    void setXsdFilename(QString filename) {
        xsdValidatorLnEd->setText(filename);
    }
    QString getXsd() const {
        return xsdFileTxtEd->toPlainText();
    }
    void setXsd(QString xsd) {
        xsdFileTxtEd->setPlainText(xsd);
    }

public slots:
    void saveXmlFile(bool b);
    void validateXml(bool b);

    void saveXsdFile(bool b);
    void validateXsd(bool b);

private:

    QScrollArea *guiScrollArea;
    QScrollArea *xmlScrollArea;

    // GUI
    QWidget *guiWidget;
    QVBoxLayout *guiLayout;

    QHBoxLayout *guiHeaderLayout;
    QGroupBox *guiHeaderXmlGBox;
    QGroupBox *guiHeaderDoctypeGBox;

    QGridLayout *guiHeaderXmlLayout;
    QLabel *xmlFileLbl;
    QLineEdit *xmlFileLnEd;
    QLabel *versionLbl;
    QLineEdit *versionLnEd;
    QLabel *encodingLbl;
    QLineEdit *encodingLnEd;

    QGridLayout *guiHeaderDoctypeLayout;
    QLabel *nameLbl;
    QLineEdit *nameLnEd;
    QLabel *typeLbl;
    QLineEdit *typeLnEd;
    QLabel *fileLbl;
    QLineEdit *dtdFileLnEd;


    QHBoxLayout *guiNamespaceUriLayout;
    QGroupBox *guiNamespaceUriGBox;
    QLineEdit *guiNamespaceUriLnEd;

    // XML
    QWidget *xmlWidget;
    QVBoxLayout *xmlLayout;

    QHBoxLayout *xmlFileLayout;
    QGroupBox *xmlFileGBox;
    QTextEdit *xmlFileTxtEd;

    QGridLayout *xmlValidatorLayout;
    QGroupBox *xmlValidatorGBox;
    QLabel *xmlValidatorLbl;
    QLineEdit *xmlValidatorLnEd;
    QPushButton *xmlValidateBtn;
    QLineEdit *xmlValidatorResultLnEd;
    QPushButton *xmlSaveBtn;

    // XSD
    QHBoxLayout *xsdFileLayout;
    QGroupBox *xsdFileGBox;
    QTextEdit *xsdFileTxtEd;

    QGridLayout *xsdValidatorLayout;
    QGroupBox *xsdValidatorGBox;
    QLabel *xsdValidatorLbl;
    QLineEdit *xsdValidatorLnEd;
    QPushButton *xsdValidateBtn;
    QLineEdit *xsdValidatorResultLnEd;
    QPushButton *xsdSaveBtn;

};
#endif // ABSTRACTWIDGET_H

