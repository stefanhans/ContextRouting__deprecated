#include "abstractwriter.h"

#include <QtWidgets>

AbstractWriter::AbstractWriter()
{
}

bool AbstractWriter::write(QIODevice *device, AbstractWidget *widget) {
    qDebug() << "AbstractWriter::write(QIODevice *device, AbstractWidget *widget)";

    xml.setDevice(device);

    xml.setAutoFormatting(true);
    xml.setAutoFormattingIndent(4);

    xml.writeStartDocument("1.0");

    return true;
}

