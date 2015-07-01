#include "requestwriter.h"

#include "codingwidget.h"

#include <QDebug>
#include <QDateTime>

RequestWriter::RequestWriter()
{

}

bool RequestWriter::write(QIODevice *device, AbstractWidget *widget) {
    qDebug() << "RequestWriter::write(QIODevice *device, AbstractWidget *widget)";

    // Initialize
    xml.setDevice(device);

    AbstractWriter::write(device, widget);

    CodingWidget* codingWidget = ((CodingWidget*)widget);

    xml.writeDTD("<!DOCTYPE ContextRequest SYSTEM \"ContextRequest.dtd\">");


    // Context Request
    xml.writeStartElement("ContextRequest");
    xml.writeAttribute("name", codingWidget->getRequestName());
    xml.writeAttribute("createDate", QDateTime::currentDateTime().toUTC().toString(Qt::ISODate));
    xml.writeAttribute("language", codingWidget->getCodingLanguage());


    // ContextHeader
    xml.writeEmptyElement("ContextHeader");
    xml.writeAttribute("serviceName", codingWidget->getCurrentServiceName());
    xml.writeAttribute("service", QString("%1").arg(codingWidget->getCurrentServiceNumber()));
    xml.writeAttribute("version", "0");
    xml.writeAttribute("channel", "0");
    xml.writeAttribute("optionalSize", "0");
    xml.writeAttribute("ip_address", "Not yet");


    // Context Datagram
    xml.writeStartElement("ContextDatagram");
    xml.writeAttribute("listSize", QString("%1").arg(codingWidget->getCodingElementSize()*2));
    xml.writeAttribute("type", codingWidget->getCodingId());

//    qDebug() << "RequestWriter::write: getContextDatagramList().size(): " << codingWidget->getContextDatagramList().size();
    for(int i=0; i<codingWidget->getContextDatagramList().size(); i++) {
        contextDatagram = codingWidget->getContextDatagramList().at(i);

        xml.writeStartElement("CodingElement");
        xml.writeAttribute("type", contextDatagram.at(1).toString());
        xml.writeAttribute("category", contextDatagram.at(2).toString());
        xml.writeAttribute("selection", contextDatagram.at(9).toString().toUtf8());
        xml.writeAttribute("content", contextDatagram.at(10).toString());
        xml.writeAttribute("mask", contextDatagram.at(11).toString());
        xml.writeAttribute("brickCount", contextDatagram.at(3).toString());
        xml.writeAttribute("name", contextDatagram.at(4).toString());
        xml.writeAttribute("sourceType", contextDatagram.at(5).toString());
        xml.writeAttribute("sourceLocation", contextDatagram.at(6).toString());
        xml.writeAttribute("sourceFormat", contextDatagram.at(7).toString());
        xml.writeAttribute("source", contextDatagram.at(8).toString());

        xml.writeStartElement("Name");
        xml.writeCDATA(contextDatagram.at(9).toString());
        xml.writeEndElement();

        for(int j=10; j<contextDatagram.size(); j+=2) {
            xml.writeStartElement("ContextBrick");
            xml.writeAttribute("content", contextDatagram.at(j).toString());
            xml.writeAttribute("mask", contextDatagram.at(j+1).toString());
            xml.writeEndElement();
        }

        xml.writeEndElement();
    }
    xml.writeEndElement();

    // Close all open tags
    xml.writeEndDocument();

    return true;
}
