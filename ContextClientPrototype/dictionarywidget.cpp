#include "dictionarywidget.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>

DictionaryWidget::DictionaryWidget(QWidget *parent)
    : AbstractWidget(parent)
{
    qDebug() << "DictionaryWidget::DictionaryWidget(QWidget *parent)";

    // TreeView Layout
    dictTreeLayout = new QVBoxLayout;
    dictTree = new DictionaryTree();

    dictTreeLayout->addWidget(dictTree);

    // Dictionary GroupBox
    dictTreeGBox = new QGroupBox("Dictionary");
    dictTreeGBox->setLayout(dictTreeLayout);


    // New layout
    newLayout = new QVBoxLayout;
    newLayout->addWidget(dictTreeGBox);

    addNextLayout(newLayout);
}

bool DictionaryWidget::loadFile(QString fileName) {
    qDebug() << "DictionaryWidget::loadFile(QString fileName)";

    QFile xmlFile(fileName);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(xmlFile.errorString()));
        return false;
    }
    xmlFile.setObjectName(fileName);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    reader = new DictionaryReader();
    reader->read(&xmlFile, this);
    xmlFile.reset();

    dictTree->loadDictionaryXml(&xmlFile);
    xmlFile.reset();

    // XML
    QTextStream inXml(&xmlFile);
    setXml(inXml.readAll());

    // XSD
    QFile xsdFile(getXsdFilename());
    qDebug() << "getXsdFilename()): " << getXsdFilename();
    if (!xsdFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(getXsdFilename())
                             .arg(xsdFile.errorString()));
        return false;
    }
    QTextStream inXsd(&xsdFile);
    setXsd(inXsd.readAll());

    QApplication::restoreOverrideCursor();

    return true;
}
