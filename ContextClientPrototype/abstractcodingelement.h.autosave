#ifndef ABSTRACTCODINGELEMENT_H
#define ABSTRACTCODINGELEMENT_H

#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

class AbstractCodingElement : public QWidget
{
    Q_OBJECT
public:
    AbstractCodingElement(QWidget *parent = 0);

    virtual void addNextLayout(QLayout *nextLayout);

    QLayout* getLayout();

    void setElementTitle(int number);

    void addWidget(QWidget *widget);



    // Tree - NumberElement
    int getNumberElement() const{
        return numberElement;
    }
    void setNumberElement(int number) {
        numberElement = number;
    }

    // Element - Name
    QString getElementName() const {
        return elementNameLnEd->text();
    }
    void setElementName(QString elementName) {
        elementNameLnEd->setText(elementName);
    }

    // Element - Type
    QString getElementType() const {
        return elementTypeLnEd->text();
    }
    void setElementType(QString elementType) {
        elementTypeLnEd->setText(elementType);
    }

    // Element - Size
    QString getElementSize() const {
        return elementSizeLnEd->text();
    }
    void setElementSize(QString elementSize) {
        elementSizeLnEd->setText(elementSize);
    }

    // Source - Type
    QString getSourceType() const {
        return sourceTypeLnEd->text();
    }
    void setSourceType(QString sourceType) {
        sourceTypeLnEd->setText(sourceType);
    }

    // Source - Format
    QString getSourceFormat() const {
        return sourceFormatLnEd->text();
    }
    void setSourceFormat(QString sourceFormat) {
        sourceFormatLnEd->setText(sourceFormat);
    }

    // Source - Location
    QString getSourceLocation() const {
        return sourceLocationLnEd->text();
    }
    void setSourceLocation(QString sourceLocation) {
        sourceLocationLnEd->setText(sourceLocation);
    }

    // Source - Source
    QString getSource() const {
        return sourceLnEd->text();
    }
    void setSource(QString source) {
        sourceLnEd->setText(source);
    }

private:
    int numberElement;
    QString elementId;

    QVBoxLayout *mainLayout;
    QGroupBox *mainGBox;

    QVBoxLayout *headerLayout;

    QGroupBox *elementGBox;
    QGridLayout *elementLayout;
    QLabel *elementNameLbl;
    QLineEdit *elementNameLnEd;
    QLabel *elementTypeLbl;
    QLineEdit *elementTypeLnEd;
    QLabel *elementSizeLbl;
    QLineEdit *elementSizeLnEd;

    QGroupBox *sourceGBox;
    QGridLayout *sourceLayout;
    QLabel *sourceTypeLbl;
    QLineEdit *sourceTypeLnEd;
    QLabel *sourceFormatLbl;
    QLineEdit *sourceFormatLnEd;
    QLabel *sourceLocationLbl;
    QLineEdit *sourceLocationLnEd;
    QLabel *sourceLbl;
    QLineEdit *sourceLnEd;
};
#endif // ABSTRACTCODINGELEMENT_H

