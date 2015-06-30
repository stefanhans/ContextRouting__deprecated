#ifndef DICTIONARYREADER_H
#define DICTIONARYREADER_H

#include "abstractreader.h"

#include <QXmlStreamReader>

class AbstractWidget;

class DictionaryReader : public AbstractReader
{
    Q_OBJECT
public:
    DictionaryReader();

    bool read(QIODevice *device, AbstractWidget *widget);

    QString errorString() const;

private:
    QXmlStreamReader xml;
};
#endif // DICTIONARYREADER_H

