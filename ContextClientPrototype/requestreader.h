#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include "abstractreader.h"
#include "abstractwidget.h"
#include "abstractcodingelement.h"

#include "requestwidget.h"
#include "abstractcodingelement.h"
#include "dictionarycodingelement.h"
#include "dictionarytree.h"

#include <QXmlStreamReader>

class RequestReader;

class RequestReader : public AbstractReader
{
    Q_OBJECT
public:
    RequestReader();

    AbstractCodingElement *codingElement;

    bool read(QIODevice *device, AbstractWidget *widget);

    QString errorString() const;

signals:
    void requestContextData();
    void answerContextData(QList<QVariant> data);

private:
    QString lastName;

    QLayout *newLayout;
    QGridLayout *dataLayout;

    QVBoxLayout *dictLayout;
    QGroupBox *dictGBox;
};
#endif // REQUESTREADER_H

