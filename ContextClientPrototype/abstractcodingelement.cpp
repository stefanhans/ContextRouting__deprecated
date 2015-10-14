#include "abstractcodingelement.h"

#include <QTreeView>
#include <QDebug>

AbstractCodingElement::AbstractCodingElement(QWidget *parent)
    : QWidget(parent)
{
    // Element
    numberElement = 0;

    elementNameLbl = new QLabel(tr("Name"));
    elementNameLnEd = new QLineEdit;
    elementNameLbl->setBuddy(elementNameLnEd);

    elementTypeLbl = new QLabel(tr("Type"));
    elementTypeLnEd = new QLineEdit;
    elementTypeLbl->setBuddy(elementTypeLnEd);

    elementSizeLbl = new QLabel(tr("Bytes"));
    elementSizeLnEd = new QLineEdit;
    elementSizeLbl->setBuddy(elementSizeLnEd);

    elementLayout = new QGridLayout;
    elementLayout->addWidget(elementNameLbl, 0, 0);
    elementLayout->addWidget(elementNameLnEd, 0, 1);
    elementLayout->addWidget(elementTypeLbl, 0, 2);
    elementLayout->addWidget(elementTypeLnEd, 0, 3);
    elementLayout->addWidget(elementSizeLbl, 0, 4);
    elementLayout->addWidget(elementSizeLnEd, 0, 5);

    elementGBox = new QGroupBox(tr("Element"));
    elementGBox->setLayout(elementLayout);

    // Source
    sourceTypeLbl = new QLabel(tr("Type"));
    sourceTypeLnEd = new QLineEdit;
    sourceTypeLbl->setBuddy(sourceTypeLnEd);

    sourceFormatLbl = new QLabel(tr("Format"));
    sourceFormatLnEd = new QLineEdit;
    sourceFormatLbl->setBuddy(sourceFormatLnEd);

    sourceLocationLbl = new QLabel(tr("Location"));
    sourceLocationLnEd = new QLineEdit;
    sourceLocationLbl->setBuddy(sourceLocationLnEd);

    sourceLbl = new QLabel(tr("Source"));
    sourceLnEd = new QLineEdit;
    sourceLbl->setBuddy(sourceLnEd);

    sourceLayout = new QGridLayout;
    sourceLayout->addWidget(sourceTypeLbl, 0, 0);
    sourceLayout->addWidget(sourceTypeLnEd, 0, 1);
    sourceLayout->addWidget(sourceFormatLbl, 0, 2);
    sourceLayout->addWidget(sourceFormatLnEd, 0, 3);
    sourceLayout->addWidget(sourceLocationLbl, 0, 4);
    sourceLayout->addWidget(sourceLocationLnEd, 0, 5);
    sourceLayout->addWidget(sourceLbl, 1, 0);
    sourceLayout->addWidget(sourceLnEd, 1, 1, 1, 5);

    sourceGBox = new QGroupBox(tr("Source"));
    sourceGBox->setLayout(sourceLayout);

    // Header
    headerLayout = new QVBoxLayout;
    headerLayout->addWidget(elementGBox);
    headerLayout->addWidget(sourceGBox);

    mainLayout = new QVBoxLayout;
    mainGBox = new QGroupBox(tr("Coding Element"));
    mainGBox->setLayout(headerLayout);
    mainLayout->addWidget(mainGBox);
}


void AbstractCodingElement::addNextLayout(QLayout *nextLayout) {
    qDebug() << "AbstractCodingElement::addNextLayout(nextLayout)";

    mainLayout->addLayout(nextLayout);
}

QLayout* AbstractCodingElement::getLayout() {
    return mainLayout;
}

void AbstractCodingElement::setElementTitle(int number) {
    mainGBox->setTitle(QString("%1 %2").arg(mainGBox->title()).arg(number));
}

void AbstractCodingElement::addWidget(QWidget *widget) {
    headerLayout->addWidget(widget);
}


