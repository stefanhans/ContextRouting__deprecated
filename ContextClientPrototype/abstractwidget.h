#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

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

    // XML
    QString getXml() const {
        return xmlEdit->toPlainText();
    }
    void setXml(QString xml) {
        xmlEdit->setPlainText(xml);
    }

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

    // XML
    QWidget *xmlWidget;
    QVBoxLayout *xmlLayout;
    QTextEdit *xmlEdit;

};
#endif // ABSTRACTWIDGET_H

