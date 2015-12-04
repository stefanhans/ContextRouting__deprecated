#ifndef ABSTRACTCODINGREADER_H
#define ABSTRACTCODINGREADER_H

#include "abstractcodingwidget.h"

#include <QXmlStreamReader>

class AbstractCodingWidget;

class AbstractCodingReader : public QObject
{
    Q_OBJECT
public:
    AbstractCodingReader();

    QXmlStreamReader xml;

    bool read(QIODevice *device, AbstractCodingWidget *widget);

    QString errorString() const;
};
#endif // ABSTRACTCODINGREADER_H

