#include "offerreader.h"

#include "offerwidget.h"
#include "abstractcodingelement.h"
#include "dictionarycodingelement.h"
#include "dictionarytree.h"

#include <QtWidgets>

OfferReader::OfferReader()
{

}

bool OfferReader::read(QIODevice *device, AbstractWidget *widget) {
    qDebug() << "OfferReader::read(QIODevice *device, AbstractWidget *widget)";

    xml.setDevice(device);

    OfferWidget* offerWidget = ((OfferWidget*) widget);

    DictionaryTree *dictTree;

    int elementCount = 0;
    int elementSize = 0;

    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartDocument()) {
            widget->setXmlFile(xml.device()->objectName());
            widget->setVersion(xml.documentVersion().toString());
            widget->setEncoding(xml.documentEncoding().toString());
            continue;
        }

        if (xml.isDTD()) {
            widget->setName(xml.dtdName().toString());
            widget->setType(xml.dtdPublicId().toString().isEmpty() ? "SYSTEM" : "PUBLIC");
            widget->setDtdFile(xml.dtdSystemId().toString());
            continue;
        }

        // <ContextOffer name="a" createDate="2015-06-25T10:46:21Z">

        if (xml.isStartElement()) {
            qDebug() << "xml.name(): " << xml.name();

            lastName = xml.name().toString();

            if(xml.name() == "ContextOffer") {

                for(int i=0; i<xml.attributes().size();i++) {
                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    if(xml.attributes().at(i).name() == "name") {
                        offerWidget->setOfferName(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "createDate") {
                        offerWidget->setOfferCreateDate(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "language") {
                        offerWidget->setOfferLanguage(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }
            }

//            <ContextHeader service="1" serviceName="Offer" version="0" channel="0" optionalSize="0" uuid="36efc7b51a894c8e8723a48af83264" ip_address="Not yet"/>


            if(xml.name() == "ContextHeader") {

                for(int i=0; i<xml.attributes().size();i++) {
                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    if(xml.attributes().at(i).name() == "serviceName") {
                        offerWidget->setHeaderServiceName(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "service") {
                        offerWidget->setHeaderService(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "version") {
                        offerWidget->setHeaderVersion(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "channel") {
                        offerWidget->setHeaderChannel(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "optionalSize") {
                        offerWidget->setHeaderOptionalSize(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "uuid") {
                        offerWidget->setHeaderUuid(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "ip_address") {
                        offerWidget->setHeaderIpAddress(xml.attributes().at(i).value().toString());
                        continue;
                    }

                }
            }

//                <ContextDatagram listSize="4" type="2">

            if(xml.name() == "ContextDatagram") {

                for(int i=0; i<xml.attributes().size();i++) {
                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    if(xml.attributes().at(i).name() == "listSize") {
                        offerWidget->setDatagramListSize(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "type") {
                        offerWidget->setDatagramType(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }
            }

            if(xml.name() == "CodingElement") {

                // GUI - Coding - CodingElement
                codingElement = new DictionaryCodingElement();

                DictionaryCodingElement *dictCodingElement = (DictionaryCodingElement*) codingElement;

                codingElement->setElementTitle(++elementCount);
                codingElement->setNumberElement(elementCount);

                for(int i=0; i<xml.attributes().size();i++) {
                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();


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


                    // Selection
                    if(xml.attributes().at(i).name() == "selection") {
                        dictCodingElement->setSelection(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "content") {
                        dictCodingElement->setContent(xml.attributes().at(i).value().toString());
                        continue;
                    }

                    if(xml.attributes().at(i).name() == "mask") {
                        dictCodingElement->setMask(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }

                if(codingElement->getElementType() == "ContextDictionary") {

                    QFile file(codingElement->getSource());
                    if(!file.open(QFile::ReadOnly | QFile::Text)) {
                        QMessageBox msgBox;
                        msgBox.setText(file.errorString());
                        msgBox.setInformativeText(codingElement->getSource());
                        msgBox.exec();
                    }

                    dictTree = new DictionaryTree();
                    dictTree->setNumberInQueue(codingElement->getNumberElement());
                    dictTree->loadDictionaryXml(&file);
                    dictTree->setMinimumHeight(40+dictTree->getMinimumSize());


                    QList<QStandardItem *>  found = dictTree->model.findItems(((DictionaryCodingElement*) codingElement)->getSelection(), Qt::MatchRecursive);
                    qDebug() << "dictTree->model.findItems: found: " << found.count();
                    if(!found.isEmpty()) {
                        dictTree->setCurrentIndex(dictTree->model.indexFromItem(found.at(0)));
                    }

                    dictLayout = new QVBoxLayout;
                    dictLayout->addWidget(dictTree);

                    dictGBox = new QGroupBox(tr("Dictionary"));
                    dictGBox->setLayout(dictLayout);


                    codingElement->addWidget(dictGBox);


                    connect(this, SIGNAL(requestContextData()), dictTree, SIGNAL(requestContextData()));
                    connect(dictTree, SIGNAL(answerContextData(QList<QVariant>)), this, SIGNAL(answerContextData(QList<QVariant>)));
                }
                offerWidget->addNextLayout(codingElement->getLayout());
            }


            //    <ContextData type="Text"><![CDATA[aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa]]></ContextData>

            if(xml.name() == "ContextData") {

                for(int i=0; i<xml.attributes().size();i++) {
                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

                    if(xml.attributes().at(i).name() == "type") {
                        offerWidget->setDataType(xml.attributes().at(i).value().toString());
                        continue;
                    }
                }
            }
        }


        if(xml.isCDATA()) {
            qDebug() << "isCDATA: xml.text().toString(): " << xml.text().toString();

            if(lastName == "Name") {
                qDebug() << "isCDATA from Name: " << xml.text().toString();

                int numRows = dictTree->model.children().count();
                qDebug() << "isCDATA: dictTree->model.children().count(): " << dictTree->model.children().count();
                for (int row = 0; row < numRows; ++row) {
                        QModelIndex index = dictTree->model.index(row, 0);
                        qDebug() << "isCDATA: " << index.data();
                }



//                QList<QStandardItem *>  found = dictTree->model.findItems(xml.text().toString());

            }

            if(lastName == "ContextData") {
                qDebug() << "isCDATA from ContextData: " << xml.text().toString();

                offerWidget->setDataText(xml.text().toString());
            }


            //                <ContextDatagram listSize="4" type="2">

//            if(xml.name() == "ContextBrick") {

//                for(int i=0; i<xml.attributes().size();i++) {
//                    qDebug() << "Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();

//                    if(xml.attributes().at(i).name() == "content") {

//                        QList<QStandardItem *>  found = dictTree->model.findItems(xml.attributes().at(i).value().toString(), Qt::MatchExactly, 1);
//                        qDebug() << "isCDATA: found: " << found.count();
//                        if(!found.isEmpty()) {
//                            dictTree->setCurrentIndex(dictTree->model.indexFromItem(found.at(0)));
//                        }

//                        continue;
//                    }

//                    if(xml.attributes().at(i).name() == "mask") {
//                        offerWidget->setDatagramType(xml.attributes().at(i).value().toString());
//                        continue;
//                    }
//                }
//            }
        }
    }

//    ((ContextCodingWidget*)widget)->setCodingElementCount(elementCount);
//    ((ContextCodingWidget*)widget)->setCodingElementSize(elementSize);

    return !xml.error();
}


//        <CodingElement type="ContextDictionary" category="SpassUndQuatsch">
//            <Name><![CDATA[Anständig]]></Name>
//            <ContextBrick content="5" mask="0"/>
//        </CodingElement>
//    </ContextDatagram>
//    <ContextData type="Text"><![CDATA[aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa]]></ContextData>
//</ContextOffer>

