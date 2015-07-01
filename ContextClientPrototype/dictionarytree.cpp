#include "dictionarytree.h"

#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QTreeWidget>

DictionaryTree::DictionaryTree(QWidget *parent)
    : QTreeView(parent)
{
//    qDebug() << "------------   DictionaryTree  ------------";

    xmlType = "ContextDictionary";

    setRowCount(0);

    level = 0;
    maxLevel = 0;

    connect(this, SIGNAL(requestContextData()), this, SLOT(answerContextData()));
}

int DictionaryTree::appendNode(QStandardItemModel *model, QString text, QVariant data, int level, QStandardItem *currentItem) {

    QList<QStandardItem*> itemColumns;
    QStandardItem *item = new QStandardItem(text);
    item->setEditable( false );

    QStandardItem *itemContent = new QStandardItem(data.toList().at(0).toString());
    QStandardItem *itemMask = new QStandardItem(data.toList().at(1).toString());

    itemColumns << item << itemContent << itemMask;



    if(level == 0) {
//        qDebug() << "------------ appendNode level 0 -----------" << text;

//        qDebug() << "data.toList().at(0).toString(): " << data.toList().at(0).toString();
//        qDebug() << "data.toList().at(1).toString(): " << data.toList().at(1).toString();

        model->appendRow(itemColumns);

        return model->rowCount();
    }

    if(level == 1) {

        if(currentItem == NULL) {
//            qDebug() << "------------ appendNode level 1 NULL -----------" << text;

//            qDebug() << "data.toList().at(0).toString(): " << data.toList().at(0).toString();
//            qDebug() << "data.toList().at(1).toString(): " << data.toList().at(1).toString();

            model->item(model->rowCount()-1)->appendRow(itemColumns);

            return model->item(model->rowCount()-1)->rowCount();
        }

//        qDebug() << "------------ appendNode level 1 NOT NULL -----------" << text;

//        qDebug() << "data.toList().at(0).toString(): " << data.toList().at(0).toString();
//        qDebug() << "data.toList().at(1).toString(): " << data.toList().at(1).toString();

        currentItem->appendRow(itemColumns);

        return currentItem->rowCount();
    }

    if(currentItem == NULL) {
//        qDebug() << "------------ appendNode level " << level << " NULL -----------" << text;

//        qDebug() << "data.toList().at(0).toString(): " << data.toList().at(0).toString();
//        qDebug() << "data.toList().at(1).toString(): " << data.toList().at(1).toString();

        return appendNode(model, text, data, --level, model->item(model->rowCount()-1)->child(model->item(model->rowCount()-1)->rowCount()-1));
    }

//    qDebug() << "------------ appendNode level " << level << " NOT NULL -----------" << text;

//    qDebug() << "data.toList().at(0).toString(): " << data.toList().at(0).toString();
//    qDebug() << "data.toList().at(1).toString(): " << data.toList().at(1).toString();

    return appendNode(model, text, data, --level, currentItem->child(currentItem->rowCount()-1));
}

void DictionaryTree::loadDictionaryXml(QFile *file) {

    model.clear();

    source = file->fileName();

    QXmlStreamReader xml(file);


    while (!xml.atEnd()) {
        type = xml.readNext();

//        qDebug() << "\n\n";
//        qDebug() << "LAST_TYPE: " << lastType;
//        qDebug() << "LAST_NAME: " << lastName;

//        qDebug() << "TYPE: " << type;
//        qDebug() << "NAME: " << xml.name();
//        qDebug() << "-----------------------------------------------------------";

        // Dictionary
        if(xml.name() == "Dictionary") {

            if(xml.isStartElement()) {
//                qDebug() << "Start:\t" << xml.name().toString();
//                for(int i=0; i<xml.attributes().size();i++) {
//                    qDebug() << type << ": " << i+1 << " Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();
//                }

                if(xml.attributes().hasAttribute("name")) {
//                    qDebug() << "NAME: " << xml.attributes().value("name");

                    xmlName = xml.attributes().value("name").toString();

                    model.setHorizontalHeaderItem( 0, new QStandardItem(xmlName));

                    model.setHorizontalHeaderItem( 1, new QStandardItem("ContextBrick.content"));
                    model.setHorizontalHeaderItem( 2, new QStandardItem("ContextBrick.mask"));
                }
            }

            lastType = type;
            lastName = xml.name().toString();
            continue;
        }

        // type 4
        if(xml.name() == "DictionaryElement" && xml.isStartElement()) {

            setRowCount(getRowCount()+1);

//            qDebug() << "Start:\t" << xml.name().toString();
//            for(int i=0; i<xml.attributes().size();i++) {
//                qDebug() << type << ": " << i+1 << " Attribute:\t" << xml.attributes().at(i).name() << "=" << xml.attributes().at(i).value();
//            }

//            if(xml.attributes().hasAttribute("name") && xml.attributes().hasAttribute("number")) {
//                qDebug() << "NAME: " << xml.attributes().value("name");
//                qDebug() << "NUMBER: " << xml.attributes().value("number");
//            }

            QList<QVariant> brickVariant;

            QString name = xml.attributes().value("name").toString();

            brickVariant.insert(0, xml.attributes().value("content").toString());
            brickVariant.insert(1, xml.attributes().value("mask").toString());

            levelRowCount = appendNode(&model, xml.attributes().value("name").toString(), QVariant(brickVariant), level);

            if(levelRowCounts.size() <= level) {
                levelRowCounts.insert(level, levelRowCount);
            }
            else {
                if(levelRowCount > levelRowCounts[level]) {
                    levelRowCounts.replace(level, levelRowCount);
                }
            }

//            qDebug() << "level: " << level;
//            qDebug() << "levelRowCount: " << levelRowCount;
//            qDebug() << "levelRowCounts[level]: " << levelRowCounts[level];

            lastType = type;
            lastName = xml.name().toString();
            continue;
        }

        // type 6
        if(xml.isCharacters() && lastName == "DictionaryElement") {

            // 6 4
            if(lastType == QXmlStreamReader::StartElement) {

//                qDebug() << "level++";

                level++;

                if(level > maxLevel) {
                    maxLevel = level;
                }
            }

            lastType = type;
            continue;
        }

        // type 5
        if(xml.name() == "DictionaryElement" && xml.isEndElement()) {

//            qDebug() << "End:\t\n";

            if(lastType == QXmlStreamReader::Characters && lastName == "DictionaryElement" && level > 0) {
                level--;
            }

            lastType = type;
            continue;
        }

    }
    if (xml.hasError()) {
        qDebug() << xml.errorString();
    }

    setModel( &model );
//    hideColumn(1);
//    hideColumn(2);
    resizeColumnToContents(0);
    resizeColumnToContents(1);
    resizeColumnToContents(2);
    expandAll();

    minimumSize = rowHeight(model.index(0, 0))*rowCount;
}



QWidget* DictionaryTree::prepareDisplay(QString selectionText) {
    qDebug() << "QWidget* prepareDisplay(" << selectionText << ")";

    if(!selectionText.isEmpty()) {

        QList<QStandardItem *>  found = model.findItems(selectionText, Qt::MatchRecursive);
        if(!found.isEmpty()) {
            setCurrentIndex(model.indexFromItem(found.at(0)));
        }
    }

    QVBoxLayout *dictLayout = new QVBoxLayout;
    dictLayout->addWidget(this);

    QGroupBox *dictGBox = new QGroupBox(tr("Dictionary"));
    dictGBox->setLayout(dictLayout);

    return dictGBox;
}

QList<QVariant> DictionaryTree::getSelectedData() {
    qDebug() << "QList<QVariant> DictionaryTree::getSelectedData()";


    QList<QVariant> outList;

    outList.push_back(getNumberInQueue());
    outList.push_back(xmlType);
    outList.push_back(xmlName);
    outList.push_back(brickCount);
    outList.push_back(name);
    outList.push_back(sourceType);
    outList.push_back(sourceLocation);
    outList.push_back(sourceFormat);
    outList.push_back(source);

    if(selectedIndexes().count() == 0) {

        qDebug() << "selectedIndexes().count(): " << selectedIndexes().count();

        outList.push_back("NA");
        outList.push_back(0);
        outList.push_back(255);

        return outList;
    }

    outList.push_back(currentIndex().sibling(this->currentIndex().row(), 0).data(Qt::DisplayRole));
    outList.push_back(currentIndex().sibling(this->currentIndex().row(), 1).data(Qt::DisplayRole));
    outList.push_back(currentIndex().sibling(this->currentIndex().row(), 2).data(Qt::DisplayRole));

    return outList;
}

void DictionaryTree::answerContextData() {
    qDebug() << "DictionaryTree::answerContextData()";

    emit answerContextData(getSelectedData());
}
