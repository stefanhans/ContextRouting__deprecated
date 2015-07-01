
#include "codingreader.h"
#include "codingwidget.h"
#include "abstractcodingelement.h"
#include "dictionarytree.h"

#include <QtWidgets>

CodingReader::CodingReader()
{

}

bool CodingReader::read(QIODevice *device, AbstractWidget *widget) {
    qDebug() << "CodingReader::read(QIODevice *device, AbstractWidget *widget)";

    xml.setDevice(device);


    CodingWidget *codingWidget = ((CodingWidget*) widget);

    int elementCount = 0;
    int elementSize = 0;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartDocument()) {
            codingWidget->setXmlFile(xml.device()->objectName());
            codingWidget->setVersion(xml.documentVersion().toString());
            codingWidget->setEncoding(xml.documentEncoding().toString());
            continue;
        }

        if (xml.isDTD()) {
            codingWidget->setName(xml.dtdName().toString());
            codingWidget->setType(xml.dtdPublicId().toString().isEmpty() ? "SYSTEM" : "PUBLIC");
            codingWidget->setDtdFile(xml.dtdSystemId().toString());
            continue;
        }

        if (xml.isStartElement()) {
//            qDebug() << "xml.name(): " << xml.name();

            if(xml.name() == "Coding") {

                for(int i=0; i<xml.attributes().size();i++) {
//                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    if(xml.attributes().at(i).name() == "id") {
                        codingWidget->setCodingId(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "name") {
                        codingWidget->setCodingName(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "language") {
                        codingWidget->setCodingLanguage(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }

            }

            if(xml.name() == "CodingElement") {

                // GUI - Coding - CodingElement
                codingElement = new AbstractCodingElement();
                codingElement->setElementTitle(++elementCount);
                codingElement->setNumberElement(elementCount);

                for(int i=0; i<xml.attributes().size();i++) {
//                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    // Element
                    if(xml.attributes().at(i).name() == "name") {
                        codingElement->setElementName(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "type") {
                        codingElement->setElementType(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "brickCount") {
                        codingElement->setElementSize(xml.attributes().at(i).value().toString());
                        elementSize += xml.attributes().at(i).value().toInt();
                        continue;
                    }

                    // Source
                    if(xml.attributes().at(i).name() == "sourceType") {
                        codingElement->setSourceType(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "sourceFormat") {
                        codingElement->setSourceFormat(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "sourceLocation") {
                        codingElement->setSourceLocation(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "source") {
                        codingElement->setSource(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }

                if(codingElement->getElementType() == "Dictionary") {
//                    qDebug() << "codingElement->getElementType(): Dictionary";
//                    qDebug() << "codingElement->getSource(): " << codingElement->getSource();

                    QFile file(codingElement->getSource());
                    if(!file.open(QFile::ReadOnly | QFile::Text)) {
                        QMessageBox msgBox;
                        msgBox.setText(file.errorString());
                        msgBox.setInformativeText(codingElement->getSource());
                        msgBox.exec();
                    }

//                    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//                        QMessageBox::warning(this, tr("codingElement"),
//                                             tr("Cannot read file %1:\n%2.")
//                                             .arg(codingElement->getSource())
//                                             .arg(file.errorString()));
//                        return false;
//                    }

                    DictionaryTree *dictTree = new DictionaryTree();
                    dictTree->setNumberInQueue(codingElement->getNumberElement());

                    dictTree->setBrickCount(QString("%1").arg(codingElement->getNumberElement()));
                    dictTree->setName(codingElement->getElementName());
                    dictTree->setSourceType(codingElement->getSourceType());
                    dictTree->setSourceLocation(codingElement->getSourceLocation());
                    dictTree->setSourceFormat(codingElement->getSourceFormat());

                    dictTree->loadDictionaryXml(&file);
                    dictTree->setMinimumHeight(40+dictTree->getMinimumSize());

                    codingElement->addWidget(dictTree->prepareDisplay());

                    connect(this, SIGNAL(requestContextData()), dictTree, SIGNAL(requestContextData()));
                    connect(dictTree, SIGNAL(answerContextData(QList<QVariant>)), this, SIGNAL(answerContextData(QList<QVariant>)));
                }

                widget->addNextLayout(codingElement->getLayout());
                continue;
            }
            continue;
        }
    }

    codingWidget->setCodingElementCount(elementCount);
    codingWidget->setCodingElementSize(elementSize);

    return !xml.error();
}
