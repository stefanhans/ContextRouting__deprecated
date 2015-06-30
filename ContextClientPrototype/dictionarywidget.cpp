#include "dictionarywidget.h"

#include "dictionaryreader.h"

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

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    file.setObjectName(fileName);

    reader = new DictionaryReader();
    reader->read(&file, this);
    file.reset();

    dictTree->loadDictionaryXml(&file);
    file.reset();

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setXml(in.readAll());
    QApplication::restoreOverrideCursor();

    return true;
}
