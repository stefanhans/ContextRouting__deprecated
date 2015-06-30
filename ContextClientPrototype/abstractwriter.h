#ifndef ABSTRACTWRITER_H
#define ABSTRACTWRITER_H

#include "abstractwidget.h"

#include <QXmlStreamWriter>

class AbstractWidget;

class AbstractWriter : public QObject
{
    Q_OBJECT
public:
    AbstractWriter();

    QXmlStreamWriter xml;

    bool write(QIODevice *device, AbstractWidget *widget);
};
#endif // ABSTRACTWRITER_H

