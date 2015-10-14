#include "dictionarycodingelement.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>


DictionaryCodingElement::DictionaryCodingElement(QWidget *parent)
    : AbstractCodingElement(parent)
{
    qDebug() << "DictionaryCodingElement::DictionaryCodingElement(QWidget *parent)";

    selectedTextLbl = new QLabel(tr("Name"));
    selectedTextLnEd = new QLineEdit;
    selectedTextLbl->setBuddy(selectedTextLnEd);

    selectedContentLbl = new QLabel(tr("Content"));
    selectedContentLnEd = new QLineEdit;
    selectedContentLbl->setBuddy(selectedContentLnEd);

    selectedMaskLbl = new QLabel(tr("Mask"));
    selectedMaskLnEd = new QLineEdit;
    selectedMaskLbl->setBuddy(selectedMaskLnEd);

    selectedLayout = new QGridLayout;
    selectedLayout->addWidget(selectedTextLbl, 0, 0);
    selectedLayout->addWidget(selectedTextLnEd, 0, 1);
    selectedLayout->addWidget(selectedContentLbl, 0, 2);
    selectedLayout->addWidget(selectedContentLnEd, 0, 3);
    selectedLayout->addWidget(selectedMaskLbl, 0, 4);
    selectedLayout->addWidget(selectedMaskLnEd, 0, 5);

    selectedGBox = new QGroupBox(tr("Selection"));
    selectedGBox->setLayout(selectedLayout);

    addWidget(selectedGBox);
}
