#ifndef REQUESTWRITER_H
#define REQUESTWRITER_H

#include "abstractwriter.h"

#include "abstractwidget.h"
#include "codingwidget.h"

#include <QXmlStreamWriter>

class AbstractWidget;

class RequestWriter : public AbstractWriter
{
    Q_OBJECT
public:
    RequestWriter();

//    AbstractCodingElement *codingElement;

    bool write(QIODevice *device, AbstractWidget *widget);

private:
    QList<QVariant> contextDatagram;
};
#endif // REQUESTWRITER_H

