#include "abstractcodingreader.h"

#include <QtWidgets>

AbstractCodingReader::AbstractCodingReader()
{
}

bool AbstractCodingReader::read(QIODevice *device, AbstractCodingWidget *widget) {
    qDebug() << Q_FUNC_INFO;

    xml.setDevice(device);

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartDocument()) {
            widget->setXmlFile(xml.device()->objectName());
            widget->setVersion(xml.documentVersion().toString());
            widget->setEncoding(xml.documentEncoding().toString());
            break;
        }
    }

    return !xml.error();
}

QString AbstractCodingReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

