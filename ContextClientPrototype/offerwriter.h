#ifndef OFFERWRITER_H
#define OFFERWRITER_H

#include "abstractwriter.h"

#include "abstractwidget.h"
#include "abstractcodingelement.h"

#include <QXmlStreamWriter>

class AbstractWidget;

class OfferWriter : public AbstractWriter
{
    Q_OBJECT
public:
    OfferWriter();

//    AbstractCodingElement *codingElement;

    bool write(QIODevice *device, AbstractWidget *widget);

private:
    QList<QVariant> contextDatagram;
};
#endif // OFFERWRITER_H

