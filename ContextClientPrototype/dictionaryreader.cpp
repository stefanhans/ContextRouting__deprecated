#include "dictionaryreader.h"

DictionaryReader::DictionaryReader()
{
}

bool DictionaryReader::read(QIODevice *device, AbstractWidget *widget)
{
    AbstractReader::read(device, widget);

    return true;
}

QString DictionaryReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

