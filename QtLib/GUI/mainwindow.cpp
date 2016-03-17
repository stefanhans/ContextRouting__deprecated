#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //
    mainLayout = new QVBoxLayout;

    // Files - Fix Layout
    filesLayout = new QGridLayout;

    // Factory - Fix Layout
    factoryLayout = new QGridLayout;

    // Header - Fix Layout
    headerLayout = new QGridLayout;

    // Fix Context Layout
    contextLayout = new QGridLayout;

    // Data Fix Layout
    dataLayout = new QGridLayout;

    // Interaction
    interactionLayout = new QVBoxLayout;




    // Factory
    factoryGBox = new QGroupBox("CIP Factory");
    factoryGBox->setLayout(factoryLayout);
    mainLayout->addWidget(factoryGBox);


    // Factory - Service
    factoryServiceLbl = new QLabel(tr("Service"));
    factoryServiceCBx = new QComboBox();
    factoryServiceCBx->addItem("PORT_TCP_CONTEXT", 1);
    factoryServiceCBx->addItem("PORT_UDP_CONTEXT", 2);
    factoryServiceLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    factoryServiceLbl->setBuddy(factoryServiceCBx);

    newBtn = new QPushButton(tr("New"), this);


    // Files
    filesGBox = new QGroupBox("CIP Files");
    filesGBox->setLayout(filesLayout);
    mainLayout->addWidget(filesGBox);

    openBtn = new QPushButton(tr("Open"), this);;
    saveBtn = new QPushButton(tr("Save"), this);;




    factoryLayout->setColumnMinimumWidth(0, 50);

    factoryLayout->addWidget(factoryServiceLbl, 0, 0);
    factoryLayout->addWidget(factoryServiceCBx, 0, 1);
    factoryLayout->addWidget(newBtn, 0, 2);


    filesLayout->addWidget(openBtn, 0, 0);
    filesLayout->addWidget(saveBtn, 0, 1);





    headerGBox = new QGroupBox("Header Data");
    headerGBox->setLayout(headerLayout);
    mainLayout->addWidget(headerGBox);

    contextGBox = new QGroupBox("Contextinformation");
    contextGBox->setLayout(contextLayout);
    mainLayout->addWidget(contextGBox);

    dataGBox = new QGroupBox("Application Data");
    dataGBox->setLayout(dataLayout);
    mainLayout->addWidget(dataGBox);

    mainLayout->addStretch();

    interactionGBox = new QGroupBox(tr("Interaction"));
    interactionGBox->setLayout(interactionLayout);
    mainLayout->addWidget(interactionGBox);


    // GUI - Widget
    guiWidget = new QWidget;
    guiWidget->setLayout(mainLayout);

    // GUI - ScrollArea
    guiScrollArea = new QScrollArea;
    guiScrollArea->setWidget(guiWidget);
    guiScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setWidgetResizable(true);

    setCentralWidget(guiScrollArea);
    showMaximized();

}

MainWindow::~MainWindow()
{

}
