#ifndef CODINGWIDGET_H
#define CODINGWIDGET_H

#include "abstractwidget.h"
#include "abstractwriter.h"
#include "codingreader.h"

#include <uuid/uuid.h>

#include <QComboBox>
#include <QPushButton>

class CodingWidget : public AbstractWidget
{
    Q_OBJECT

public:
    CodingWidget(QWidget *parent = 0);

    bool loadFile(QString fileName);

    void loadGuiInteraction();

    // Coding - Id
    QString getCodingId() const {
        return codingIdLnEd->text();
    }
    void setCodingId(QString codingId) {
        codingIdLnEd->setText(codingId);
    }

    // Coding - Name
    QString getCodingName() const {
        return codingNameLnEd->text();
    }
    void setCodingName(QString codingName) {
        codingNameLnEd->setText(codingName);
    }

    // Coding - Language
    QString getCodingLanguage() const {
        return codingLanguageLnEd->text();
    }
    void setCodingLanguage(QString codingLanguage) {
        codingLanguageLnEd->setText(codingLanguage);
    }

    // Coding - ElementCount
    int getCodingElementCount() const {
        return codingElementCount;
    }
    void setCodingElementCount(int count) {
        codingElementCount = count;
    }

    // Coding - ElementSize
    int getCodingElementSize() const {
        return codingElementSize;
    }
    void setCodingElementSize(int size) {
        codingElementSize = size;
    }


    // Offer
    QString getOfferName() {
        return nameLnEd->text();
    }

    // Request
    QString getRequestName() {
        return nameLnEd->text();
    }

    // Context Header
    quint8 getCurrentServiceNumber() {
        return quint8(actionCBx->currentData().toInt());
    }
    QString getCurrentServiceName() {
       return actionCBx->currentText();
    }

    // Context Data
    QString getDataType() {
        return dataTypeCBx->currentText();
    }

    QString getDataText() {
        QString truncData = dataTxtEd->toPlainText();
        truncData.truncate(140);
        return truncData;
    }

    // ContextDatagramm
    QList<QList<QVariant> > getContextDatagramList() {
        return contextDatagramList;
    }

    // ContextBrickList
    QList<QPair<quint8, quint8> > getContextBrickList() {
        return contextBrickList;
    }

public slots:
    void saveContext();

    void receiveSelectedDictData(QList<QVariant> data);


signals:
    void requestContextData();
    void answerContextData(QList<QVariant>);

private:

    // Coding Header (constructor with addNextLayout(layout))
    QVBoxLayout *codLayout;
    QGroupBox *codGBox;

    QGridLayout *codingLayout;
    QLabel *codingIdLbl;
    QLineEdit *codingIdLnEd;
    QLabel *codingNameLbl;
    QLineEdit *codingNameLnEd;
    QLabel *codingLanguageLbl;
    QLineEdit *codingLanguageLnEd;

    // Interaction (loadGuiInteraction())
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

    QGridLayout *actionLayout;
    QLabel *nameLbl;
    QLineEdit *nameLnEd;
    QLabel *actionLbl;
    QComboBox *actionCBx;
    QLabel *dataTypeLbl;
    QComboBox *dataTypeCBx;
    QLabel *dataLbl;
    QTextEdit *dataTxtEd;
    QPushButton *saveBtn;

    // Internal (hidden)
    uuid_t sourceUuid;    


    AbstractWriter *writer;

    CodingReader *reader;
    int codingElementCount;
    int codingElementSize;

    QPair<quint8, quint8> contextBrick;
    QList<QPair<quint8, quint8> > contextBrickList;

    QList<QList<QVariant> > contextDatagramList;
};
#endif // CODINGWIDGET_H

