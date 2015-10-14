#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include "abstractwidget.h"
#include "globals.h"

#include <QXmlStreamReader>

class AbstractWidget;

class AbstractReader : public QObject
{
    Q_OBJECT
public:
    AbstractReader();

    QXmlStreamReader xml;

    bool read(QIODevice *device, AbstractWidget *widget);

    QString errorString() const;
};
#endif // ABSTRACTREADER_H

