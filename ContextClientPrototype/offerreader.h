#ifndef OFFERREADER_H
#define OFFERREADER_H

#include "abstractreader.h"
#include "abstractwidget.h"
#include "abstractcodingelement.h"

#include "offerwidget.h"
#include "abstractcodingelement.h"
#include "dictionarycodingelement.h"
#include "dictionarytree.h"

#include <QtWidgets>
#include <QDebug>

#include <QXmlStreamReader>

class OfferReader : public AbstractReader
{
    Q_OBJECT
public:
    OfferReader();

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
#endif // OFFERREADER_H

