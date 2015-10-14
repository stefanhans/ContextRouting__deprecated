#include "abstractreader.h"

#include <QtWidgets>

AbstractReader::AbstractReader()
{
}

bool AbstractReader::read(QIODevice *device, AbstractWidget *widget) {
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

//        if (xml.isDTD()) {
//            widget->setName(xml.dtdName().toString());
//            widget->setType(xml.dtdPublicId().toString().isEmpty() ? "SYSTEM" : "PUBLIC");
//            widget->setDtdFile(xml.dtdSystemId().toString());
//            continue;
//        }
    }

    return !xml.error();
}

QString AbstractReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}
