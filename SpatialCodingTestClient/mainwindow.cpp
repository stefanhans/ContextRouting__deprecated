#include "mainwindow.h"

#include <QDebug>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Palettes
    noColor = Qt::white;
    redColor = Qt::red;

    // QColor(red, green, blue, transparency)
    offerContentColor = QColor(0, 255, 255, 120);
    offerMaskColor = QColor(0, 255, 255, 50);
    offerMatchColor = QColor(0, 255, 255, 255);

    requestContentColor = QColor(255, 255, 0, 120);
    requestMaskColor = QColor(255, 255, 0, 50);
    requestMatchColor = QColor(255, 255, 0, 255);

    indirectMatchColor = QColor(0, 255, 0, 80);
    directMatchColor = QColor(0, 255, 0, 255);


    offerContentPalette.setColor(QPalette::Window, offerContentColor);
    offerMaskPalette.setColor(QPalette::Window, offerMaskColor);


    requestContentPalette.setColor(QPalette::Window, requestContentColor);
    requestMaskPalette.setColor(QPalette::Window, requestMaskColor);

    // Offer Content 1
    offerContent_1_ByteGroupBox = new QGroupBox(tr("Content 1 Byte"));
    offerContent_1_ByteGroupBox->setAutoFillBackground(true);
    offerContent_1_ByteGroupBox->setPalette(offerContentPalette);

    offerContent_1_ByteHBoxLayout = new QHBoxLayout;

    offerContent_1_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerContent_1_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerContent_1_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerContent_1_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerContent_1_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerContent_1_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerContent_1_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerContent_1_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerContent_1_ByteBtn = new QPushButton(tr("Show"), this);

    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_7_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_6_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_5_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_4_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_3_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_2_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_1_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_Byte_0_CheckBox);
    offerContent_1_ByteHBoxLayout->addWidget(offerContent_1_ByteBtn);

    offerContent_1_ByteGroupBox->setLayout(offerContent_1_ByteHBoxLayout);

    connect(offerContent_1_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferContent_1_Byte()));

    // Offer Mask 1
    offerMask_1_ByteGroupBox = new QGroupBox(tr("Mask 1 Byte"));
    offerMask_1_ByteGroupBox->setAutoFillBackground(true);
    offerMask_1_ByteGroupBox->setPalette(offerMaskPalette);

    offerMask_1_ByteHBoxLayout = new QHBoxLayout;
    offerMask_1_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerMask_1_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerMask_1_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerMask_1_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerMask_1_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerMask_1_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerMask_1_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerMask_1_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerMask_1_ByteBtn = new QPushButton(tr("Show"), this);

    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_7_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_6_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_5_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_4_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_3_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_2_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_1_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_Byte_0_CheckBox);
    offerMask_1_ByteHBoxLayout->addWidget(offerMask_1_ByteBtn);

    offerMask_1_ByteGroupBox->setLayout(offerMask_1_ByteHBoxLayout);

    connect(offerMask_1_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferMask_1_Byte()));

    // Offer Content 2
    offerContent_2_ByteGroupBox = new QGroupBox(tr("Content 2 Byte"));
    offerContent_2_ByteGroupBox->setAutoFillBackground(true);
    offerContent_2_ByteGroupBox->setPalette(offerContentPalette);

    offerContent_2_ByteHBoxLayout = new QHBoxLayout;

    offerContent_2_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerContent_2_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerContent_2_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerContent_2_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerContent_2_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerContent_2_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerContent_2_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerContent_2_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerContent_2_ByteBtn = new QPushButton(tr("Show"), this);

    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_7_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_6_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_5_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_4_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_3_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_2_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_1_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_Byte_0_CheckBox);
    offerContent_2_ByteHBoxLayout->addWidget(offerContent_2_ByteBtn);
    offerContent_2_ByteGroupBox->setLayout(offerContent_2_ByteHBoxLayout);

    connect(offerContent_2_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferContent_2_Byte()));

    // Offer Mask 2
    offerMask_2_ByteGroupBox = new QGroupBox(tr("Mask 2 Byte"));
    offerMask_2_ByteGroupBox->setAutoFillBackground(true);
    offerMask_2_ByteGroupBox->setPalette(offerMaskPalette);

    offerMask_2_ByteHBoxLayout = new QHBoxLayout;
    offerMask_2_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerMask_2_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerMask_2_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerMask_2_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerMask_2_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerMask_2_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerMask_2_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerMask_2_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerMask_2_ByteBtn = new QPushButton(tr("Show"), this);

    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_7_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_6_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_5_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_4_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_3_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_2_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_1_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_Byte_0_CheckBox);
    offerMask_2_ByteHBoxLayout->addWidget(offerMask_2_ByteBtn);

    offerMask_2_ByteGroupBox->setLayout(offerMask_2_ByteHBoxLayout);

    connect(offerMask_2_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferMask_2_Byte()));

    // Request Content 1
    requestContent_1_ByteGroupBox = new QGroupBox(tr("Content 1 Byte"));
    requestContent_1_ByteGroupBox->setAutoFillBackground(true);
    requestContent_1_ByteGroupBox->setPalette(requestContentPalette);

    requestContent_1_ByteHBoxLayout = new QHBoxLayout;
    requestContent_1_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestContent_1_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestContent_1_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestContent_1_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestContent_1_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestContent_1_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestContent_1_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestContent_1_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestContent_1_ByteBtn = new QPushButton(tr("Show"), this);

    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_7_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_6_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_5_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_4_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_3_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_2_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_1_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_Byte_0_CheckBox);
    requestContent_1_ByteHBoxLayout->addWidget(requestContent_1_ByteBtn);

    requestContent_1_ByteGroupBox->setLayout(requestContent_1_ByteHBoxLayout);

    connect(requestContent_1_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestContent_1_Byte()));


    // Request Mask 1
    requestMask_1_ByteGroupBox = new QGroupBox(tr("Mask 1 Byte"));
    requestMask_1_ByteGroupBox->setAutoFillBackground(true);
    requestMask_1_ByteGroupBox->setPalette(requestMaskPalette);

    requestMask_1_ByteHBoxLayout = new QHBoxLayout;
    requestMask_1_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestMask_1_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestMask_1_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestMask_1_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestMask_1_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestMask_1_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestMask_1_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestMask_1_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestMask_1_ByteBtn = new QPushButton(tr("Show"), this);

    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_7_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_6_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_5_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_4_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_3_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_2_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_1_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_Byte_0_CheckBox);
    requestMask_1_ByteHBoxLayout->addWidget(requestMask_1_ByteBtn);

    requestMask_1_ByteGroupBox->setLayout(requestMask_1_ByteHBoxLayout);

    connect(requestMask_1_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestMask_1_Byte()));


    // Request Content 2
    requestContent_2_ByteGroupBox = new QGroupBox(tr("Content 2 Byte"));
    requestContent_2_ByteGroupBox->setAutoFillBackground(true);
    requestContent_2_ByteGroupBox->setPalette(requestContentPalette);

    requestContent_2_ByteHBoxLayout = new QHBoxLayout;
    requestContent_2_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestContent_2_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestContent_2_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestContent_2_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestContent_2_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestContent_2_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestContent_2_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestContent_2_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestContent_2_ByteBtn = new QPushButton(tr("Show"), this);

    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_7_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_6_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_5_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_4_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_3_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_2_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_1_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_Byte_0_CheckBox);
    requestContent_2_ByteHBoxLayout->addWidget(requestContent_2_ByteBtn);

    requestContent_2_ByteGroupBox->setLayout(requestContent_2_ByteHBoxLayout);

    connect(requestContent_2_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestContent_2_Byte()));


    // Request Mask 2
    requestMask_2_ByteGroupBox = new QGroupBox(tr("Mask 2 Byte"));
    requestMask_2_ByteGroupBox->setAutoFillBackground(true);
    requestMask_2_ByteGroupBox->setPalette(requestMaskPalette);

    requestMask_2_ByteHBoxLayout = new QHBoxLayout;
    requestMask_2_Byte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestMask_2_Byte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestMask_2_Byte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestMask_2_Byte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestMask_2_Byte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestMask_2_Byte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestMask_2_Byte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestMask_2_Byte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestMask_2_ByteBtn = new QPushButton(tr("Show"), this);

    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_7_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_6_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_5_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_4_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_3_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_2_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_1_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_Byte_0_CheckBox);
    requestMask_2_ByteHBoxLayout->addWidget(requestMask_2_ByteBtn);

    requestMask_2_ByteGroupBox->setLayout(requestMask_2_ByteHBoxLayout);

    connect(requestMask_2_ByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestMask_2_Byte()));



    // Offer Layout
    offerLayout = new QGridLayout;
    offerLayout->addWidget(offerContent_1_ByteGroupBox, 0, 0);
    offerLayout->addWidget(offerMask_1_ByteGroupBox, 1, 0);
    offerLayout->addWidget(offerContent_2_ByteGroupBox, 0, 1);
    offerLayout->addWidget(offerMask_2_ByteGroupBox, 1, 1);

    // Request Layout
    requestLayout = new QGridLayout;
    requestLayout->addWidget(requestContent_1_ByteGroupBox, 0, 0);
    requestLayout->addWidget(requestMask_1_ByteGroupBox, 1, 0);
    requestLayout->addWidget(requestContent_2_ByteGroupBox, 0, 1);
    requestLayout->addWidget(requestMask_2_ByteGroupBox, 1, 1);

    // Spatial Layout
    spatialLayout = new QGridLayout;


    // Spatial 1
    refreshSpatial_1_Btn = new QPushButton(tr("Refresh 1"), this);
    spatialLayout->addWidget(refreshSpatial_1_Btn, 0, 0);

    connect(refreshSpatial_1_Btn, SIGNAL(clicked(bool)), this, SLOT(refreshSpatial_1()));

    clearSpatial_1_Btn = new QPushButton(tr("Clear 1"), this);
    spatialLayout->addWidget(clearSpatial_1_Btn, 1, 0);

    connect(clearSpatial_1_Btn, SIGNAL(clicked(bool)), this, SLOT(clearSpatial_1()));


    refreshSpatial_2_Btn = new QPushButton(tr("Refresh 2"), this);
    spatialLayout->addWidget(refreshSpatial_2_Btn, 0, 1);

    connect(refreshSpatial_2_Btn, SIGNAL(clicked(bool)), this, SLOT(refreshSpatial_2()));

    // Spatial 2
    clearSpatial_2_Btn = new QPushButton(tr("Clear 2"), this);
    spatialLayout->addWidget(clearSpatial_2_Btn, 1, 1);

    connect(clearSpatial_2_Btn, SIGNAL(clicked(bool)), this, SLOT(clearSpatial_2()));



    // Spatial All
    refreshSpatialAll_Btn = new QPushButton(tr("Refresh All"), this);
    spatialLayout->addWidget(refreshSpatialAll_Btn, 0, 2);

    connect(refreshSpatialAll_Btn, SIGNAL(clicked(bool)), this, SLOT(refreshSpatialAll()));

    clearSpatialAll_Btn = new QPushButton(tr("Clear All"), this);
    spatialLayout->addWidget(clearSpatialAll_Btn, 1, 2);

    connect(clearSpatialAll_Btn, SIGNAL(clicked(bool)), this, SLOT(clearSpatialAll()));


    spatialTableLayout =  new QHBoxLayout;

    tableSideCount = 16;
    tableWidget_1 = new QTableWidget(tableSideCount, tableSideCount, this);

    int cellSide = 30;
    tableWidget_1->setFixedHeight(17*cellSide);
    tableWidget_1->setFixedWidth(17*cellSide);

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        tableWidget_1->setColumnWidth(i, cellSide);
        tableWidget_1->setRowHeight(i, cellSide);

        for(int j=0; j<tableSideCount; j++) {

            tableWidget_1->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialTableLayout->addWidget(tableWidget_1, 0, Qt::AlignHCenter);


    tableWidget_2 = new QTableWidget(tableSideCount, tableSideCount, this);

//    int cellSide = 40;
    tableWidget_2->setFixedHeight(17*cellSide);
    tableWidget_2->setFixedWidth(17*cellSide);

    n=0;
    for(int i=0; i<tableSideCount; i++) {
        tableWidget_2->setColumnWidth(i, cellSide);
        tableWidget_2->setRowHeight(i, cellSide);

        for(int j=0; j<tableSideCount; j++) {

            tableWidget_2->setCellWidget(j, i, new QTextEdit);

            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setEnabled(false);
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialTableLayout->addWidget(tableWidget_2, 0, Qt::AlignHCenter);


    tableWidgetAll = new QTableWidget(tableSideCount, tableSideCount, this);
    tableWidgetAll->setFixedHeight(17*cellSide);
    tableWidgetAll->setFixedWidth(17*cellSide);

    n=0;
    for(int i=0; i<tableSideCount; i++) {
        tableWidgetAll->setColumnWidth(i, cellSide);
        tableWidgetAll->setRowHeight(i, cellSide);

        for(int j=0; j<tableSideCount; j++) {

            tableWidgetAll->setCellWidget(j, i, new QTextEdit);

//            ((QTextEdit*) tableWidgetAll->cellWidget(j, i))->setText(QString("%1").arg(n));
//            ((QTextEdit*) tableWidgetAll->cellWidget(j, i))->setFont(QFont("Times", 8, QFont::Bold));
//            ((QTextEdit*) tableWidgetAll->cellWidget(j, i))->setEnabled(false);
            ((QTextEdit*) tableWidgetAll->cellWidget(j, i))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialTableLayout->addWidget(tableWidgetAll, 0, Qt::AlignHCenter);



    spatialLayout->addLayout(spatialTableLayout, 2, 0, 2, 0);



    // Interaction Layout
    interactionLayout = new QGridLayout;


    // Main Layout
    mainLayout = new QVBoxLayout;

    // Offer
    offerGBox = new QGroupBox(tr("Offer"));
    offerGBox->setLayout(offerLayout);
    mainLayout->addWidget(offerGBox);

    // Request
    requestGBox = new QGroupBox(tr("Request"));
    requestGBox->setLayout(requestLayout);
    mainLayout->addWidget(requestGBox);

    // Spatial
    spatialGBox = new QGroupBox(tr("Spatial"));
    spatialGBox->setLayout(spatialLayout);
    mainLayout->addWidget(spatialGBox);

    mainLayout->addStretch();

    // Interaction
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

/*
 *
 *  _1_
 *
 */

int MainWindow::offerContent_1_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerContent;

    offerContent = (int) offerContent_1_Byte_0_CheckBox->isChecked();
    offerContent += (int) offerContent_1_Byte_1_CheckBox->isChecked() * 2;
    offerContent += (int) offerContent_1_Byte_2_CheckBox->isChecked()   * 4;
    offerContent += (int) offerContent_1_Byte_3_CheckBox->isChecked()   * 8;
    offerContent += (int) offerContent_1_Byte_4_CheckBox->isChecked()  * 16;
    offerContent += (int) offerContent_1_Byte_5_CheckBox->isChecked()  * 32;
    offerContent += (int) offerContent_1_Byte_6_CheckBox->isChecked()  * 64;
    offerContent += (int) offerContent_1_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerContent: " << offerContent;
    qDebug().noquote() << "offerContent: " << QString("%1").arg(offerContent, 8, 2, QLatin1Char('0'));

    return offerContent;
}

int MainWindow::offerMask_1_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerMask;

    offerMask = (int) offerMask_1_Byte_0_CheckBox->isChecked();
    offerMask += (int) offerMask_1_Byte_1_CheckBox->isChecked() * 2;
    offerMask += (int) offerMask_1_Byte_2_CheckBox->isChecked()   * 4;
    offerMask += (int) offerMask_1_Byte_3_CheckBox->isChecked()   * 8;
    offerMask += (int) offerMask_1_Byte_4_CheckBox->isChecked()  * 16;
    offerMask += (int) offerMask_1_Byte_5_CheckBox->isChecked()  * 32;
    offerMask += (int) offerMask_1_Byte_6_CheckBox->isChecked()  * 64;
    offerMask += (int) offerMask_1_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerMask: " << offerMask;
    qDebug().noquote() << "offerMask: " << QString("%1").arg(offerMask, 8, 2, QLatin1Char('0'));

    return offerMask;
}

int MainWindow::requestContent_1_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestContent;

    requestContent = (int) requestContent_1_Byte_0_CheckBox->isChecked();
    requestContent += (int) requestContent_1_Byte_1_CheckBox->isChecked() * 2;
    requestContent += (int) requestContent_1_Byte_2_CheckBox->isChecked()   * 4;
    requestContent += (int) requestContent_1_Byte_3_CheckBox->isChecked()   * 8;
    requestContent += (int) requestContent_1_Byte_4_CheckBox->isChecked()  * 16;
    requestContent += (int) requestContent_1_Byte_5_CheckBox->isChecked()  * 32;
    requestContent += (int) requestContent_1_Byte_6_CheckBox->isChecked()  * 64;
    requestContent += (int) requestContent_1_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestContent: " << requestContent;
    qDebug().noquote() << "requestContent: " << QString("%1").arg(requestContent, 8, 2, QLatin1Char('0'));

    return requestContent;
}

int MainWindow::requestMask_1_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestMask;

    requestMask = (int) requestMask_1_Byte_0_CheckBox->isChecked();
    requestMask += (int) requestMask_1_Byte_1_CheckBox->isChecked() * 2;
    requestMask += (int) requestMask_1_Byte_2_CheckBox->isChecked()   * 4;
    requestMask += (int) requestMask_1_Byte_3_CheckBox->isChecked()   * 8;
    requestMask += (int) requestMask_1_Byte_4_CheckBox->isChecked()  * 16;
    requestMask += (int) requestMask_1_Byte_5_CheckBox->isChecked()  * 32;
    requestMask += (int) requestMask_1_Byte_6_CheckBox->isChecked()  * 64;
    requestMask += (int) requestMask_1_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestMask: " << requestMask;
    qDebug().noquote() << "requestMask: " << QString("%1").arg(requestMask, 8, 2, QLatin1Char('0'));

    return requestMask;
}

void MainWindow::clearSpatial_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
        }
    }
}

void MainWindow::clearOfferContent_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == offerContentColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearOfferMask_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == offerMaskColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestContent_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == requestContentColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestMask_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == requestMaskColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}




void MainWindow::showOfferContent_1_Byte() {
    qDebug() << Q_FUNC_INFO;

    int offerContent = offerContent_1_ToByte();

    clearOfferContent_1();

    if (((QTextEdit*) tableWidget_1->cellWidget(qFloor(offerContent/16), offerContent%16))->palette().color(QPalette::Window) != indirectMatchColor) {
        ((QTextEdit*) tableWidget_1->cellWidget(qFloor(offerContent/16), offerContent%16))->setPalette(offerContentColor);
    }
}

void MainWindow::showOfferMask_1_Byte() {
    qDebug() << Q_FUNC_INFO;

    int offerContent = offerContent_1_ToByte();
    int offerMask = offerMask_1_ToByte();
    bool isMatch;

    clearOfferMask_1();

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            // offerContent is equal n
            if ((offerContent ^ n) == 0) {
                isMatch = true;
            }
            else {

                // offerContent neither equal n nor set true by the mask
                if (~(~(offerContent ^ n) | offerMask) != 0) {
                    isMatch = false;
                }
                else {
                    isMatch = true;
                }
            }


            // Repaint cell color according to former color
            if (isMatch) {
                if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == requestMaskColor
                        || ((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == requestContentColor) {
                    ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(indirectMatchColor);
                }
                else {
                    ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(offerMaskColor);
                }
            }
            n++;
        }
    }
    showOfferContent_1_Byte();
}

void MainWindow::showRequestContent_1_Byte() {
    qDebug() << Q_FUNC_INFO;

    int requestContent = requestContent_1_ToByte();

    clearRequestContent_1();

    if (((QTextEdit*) tableWidget_1->cellWidget(qFloor(requestContent/16), requestContent%16))->palette().color(QPalette::Window) != indirectMatchColor) {
        ((QTextEdit*) tableWidget_1->cellWidget(qFloor(requestContent/16), requestContent%16))->setPalette(requestContentColor);
    }
}

void MainWindow::showRequestMask_1_Byte() {
    qDebug() << Q_FUNC_INFO;

    int requestContent = requestContent_1_ToByte();
    int requestMask = requestMask_1_ToByte();
    bool isMatch;

    clearRequestMask_1();

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            // requestContent is equal n
            if ((requestContent ^ n) == 0) {
                isMatch = true;
            }
            else {

                // requestContent neither equal n nor set true by the mask
                if (~(~(requestContent ^ n) | requestMask) != 0) {
                    isMatch = false;
                }
                else {
                    isMatch = true;
                }
            }

            // Repaint cell color according to former color
            if (isMatch) {
                if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == offerMaskColor) {
                    ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(indirectMatchColor);
                }
                else {
                    ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(requestMaskColor);
                }
            }
            n++;
        }
    }
    showRequestContent_1_Byte();
}

void MainWindow::refreshSpatial_1() {
    qDebug() << Q_FUNC_INFO;

    clearSpatial_1();

    showRequestMask_1_Byte();
    showOfferMask_1_Byte();

    int offerContent = offerContent_1_ToByte();
    if(offerContent == requestContent_1_ToByte()) {
         ((QTextEdit*) tableWidget_1->cellWidget(qFloor(offerContent/16), offerContent%16))->setPalette(directMatchColor);
    }
    copyColor(tableWidget_2);
}


/*
 *
 *  _2_
 *
 */

int MainWindow::offerContent_2_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerContent;

    offerContent = (int) offerContent_2_Byte_0_CheckBox->isChecked();
    offerContent += (int) offerContent_2_Byte_1_CheckBox->isChecked() * 2;
    offerContent += (int) offerContent_2_Byte_2_CheckBox->isChecked()   * 4;
    offerContent += (int) offerContent_2_Byte_3_CheckBox->isChecked()   * 8;
    offerContent += (int) offerContent_2_Byte_4_CheckBox->isChecked()  * 16;
    offerContent += (int) offerContent_2_Byte_5_CheckBox->isChecked()  * 32;
    offerContent += (int) offerContent_2_Byte_6_CheckBox->isChecked()  * 64;
    offerContent += (int) offerContent_2_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerContent: " << offerContent;
    qDebug().noquote() << "offerContent: " << QString("%1").arg(offerContent, 8, 2, QLatin1Char('0'));

    return offerContent;
}

int MainWindow::offerMask_2_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerMask;

    offerMask = (int) offerMask_2_Byte_0_CheckBox->isChecked();
    offerMask += (int) offerMask_2_Byte_1_CheckBox->isChecked() * 2;
    offerMask += (int) offerMask_2_Byte_2_CheckBox->isChecked()   * 4;
    offerMask += (int) offerMask_2_Byte_3_CheckBox->isChecked()   * 8;
    offerMask += (int) offerMask_2_Byte_4_CheckBox->isChecked()  * 16;
    offerMask += (int) offerMask_2_Byte_5_CheckBox->isChecked()  * 32;
    offerMask += (int) offerMask_2_Byte_6_CheckBox->isChecked()  * 64;
    offerMask += (int) offerMask_2_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerMask: " << offerMask;
    qDebug().noquote() << "offerMask: " << QString("%1").arg(offerMask, 8, 2, QLatin1Char('0'));

    return offerMask;
}

int MainWindow::requestContent_2_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestContent;

    requestContent = (int) requestContent_2_Byte_0_CheckBox->isChecked();
    requestContent += (int) requestContent_2_Byte_1_CheckBox->isChecked() * 2;
    requestContent += (int) requestContent_2_Byte_2_CheckBox->isChecked()   * 4;
    requestContent += (int) requestContent_2_Byte_3_CheckBox->isChecked()   * 8;
    requestContent += (int) requestContent_2_Byte_4_CheckBox->isChecked()  * 16;
    requestContent += (int) requestContent_2_Byte_5_CheckBox->isChecked()  * 32;
    requestContent += (int) requestContent_2_Byte_6_CheckBox->isChecked()  * 64;
    requestContent += (int) requestContent_2_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestContent: " << requestContent;
    qDebug().noquote() << "requestContent: " << QString("%1").arg(requestContent, 8, 2, QLatin1Char('0'));

    return requestContent;
}

int MainWindow::requestMask_2_ToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestMask;

    requestMask = (int) requestMask_2_Byte_0_CheckBox->isChecked();
    requestMask += (int) requestMask_2_Byte_1_CheckBox->isChecked() * 2;
    requestMask += (int) requestMask_2_Byte_2_CheckBox->isChecked()   * 4;
    requestMask += (int) requestMask_2_Byte_3_CheckBox->isChecked()   * 8;
    requestMask += (int) requestMask_2_Byte_4_CheckBox->isChecked()  * 16;
    requestMask += (int) requestMask_2_Byte_5_CheckBox->isChecked()  * 32;
    requestMask += (int) requestMask_2_Byte_6_CheckBox->isChecked()  * 64;
    requestMask += (int) requestMask_2_Byte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestMask: " << requestMask;
    qDebug().noquote() << "requestMask: " << QString("%1").arg(requestMask, 8, 2, QLatin1Char('0'));

    return requestMask;
}



void MainWindow::clearSpatial_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
        }
    }
}

void MainWindow::clearOfferContent_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == offerContentColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearOfferMask_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == offerMaskColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestContent_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == requestContentColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestMask_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == requestMaskColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}




void MainWindow::showOfferContent_2_Byte() {
    qDebug() << Q_FUNC_INFO;

    int offerContent = offerContent_2_ToByte();

    clearOfferContent_2();

    if (((QTextEdit*) tableWidget_2->cellWidget(offerContent%16, qFloor(offerContent/16)))->palette().color(QPalette::Window) != indirectMatchColor) {
        ((QTextEdit*) tableWidget_2->cellWidget(offerContent%16, qFloor(offerContent/16)))->setPalette(offerContentColor);
    }
}

void MainWindow::showOfferMask_2_Byte() {
    qDebug() << Q_FUNC_INFO;

    int offerContent = offerContent_2_ToByte();
    int offerMask = offerMask_2_ToByte();
    bool isMatch;

    clearOfferMask_2();

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            // offerContent is equal n
            if ((offerContent ^ n) == 0) {
                isMatch = true;
            }
            else {

                // offerContent neither equal n nor set true by the mask
                if (~(~(offerContent ^ n) | offerMask) != 0) {
                    isMatch = false;
                }
                else {
                    isMatch = true;
                }
            }


            // Repaint cell color according to former color
            if (isMatch) {
                if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == requestMaskColor
                        || ((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == requestContentColor) {
                    ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(indirectMatchColor);
                }
                else {
                    ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(offerMaskColor);
                }
            }
            n++;
        }
    }
    showOfferContent_2_Byte();
}

void MainWindow::showRequestContent_2_Byte() {
    qDebug() << Q_FUNC_INFO;

    int requestContent = requestContent_2_ToByte();

    clearRequestContent_2();

    if (((QTextEdit*) tableWidget_2->cellWidget(requestContent%16, qFloor(requestContent/16)))->palette().color(QPalette::Window) != indirectMatchColor) {
        ((QTextEdit*) tableWidget_2->cellWidget(requestContent%16, qFloor(requestContent/16)))->setPalette(requestContentColor);
    }
}

void MainWindow::showRequestMask_2_Byte() {
    qDebug() << Q_FUNC_INFO;

    int requestContent = requestContent_2_ToByte();
    int requestMask = requestMask_2_ToByte();
    bool isMatch;

    clearRequestMask_2();

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            // requestContent is equal n
            if ((requestContent ^ n) == 0) {
                isMatch = true;
            }
            else {

                // requestContent neither equal n nor set true by the mask
                if (~(~(requestContent ^ n) | requestMask) != 0) {
                    isMatch = false;
                }
                else {
                    isMatch = true;
                }
            }

            // Repaint cell color according to former color
            if (isMatch) {
                if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == offerMaskColor) {
                    ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(indirectMatchColor);
                }
                else {
                    ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(requestMaskColor);
                }
            }
            n++;
        }
    }
    showRequestContent_2_Byte();
}

void MainWindow::refreshSpatial_2() {
    qDebug() << Q_FUNC_INFO;

    clearSpatial_2();

    showRequestMask_2_Byte();
    showOfferMask_2_Byte();

    int offerContent = offerContent_2_ToByte();
    if(offerContent == requestContent_2_ToByte()) {
         ((QTextEdit*) tableWidget_2->cellWidget(offerContent%16, qFloor(offerContent/16)))->setPalette(directMatchColor);
    }
//    copyColor(tableWidget_2);
}


/*
 *
 *  All
 */

void MainWindow::clearSpatialAll() {
    qDebug() << Q_FUNC_INFO;

    clearSpatial_1();
    clearSpatial_2();

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            ((QTextEdit*) tableWidgetAll->cellWidget(i, j))->setPalette(noColor);
        }
    }
}

void MainWindow::refreshSpatialAll() {
    qDebug() << Q_FUNC_INFO;

    clearSpatial_1();
    clearSpatial_2();
    clearSpatialAll();

    refreshSpatial_1();
    refreshSpatial_2();


//    showRequestMask_1_Byte();
//    showOfferMask_1_Byte();

//    int offerContent = offerContent_1_ToByte();
//    if(offerContent == requestContent_1_ToByte()) {
//         ((QTextEdit*) tableWidget_1->cellWidget(qFloor(offerContent/16), offerContent%16))->setPalette(directMatchColor);
//    }
//    copyColor(tableWidget_2);
}



void MainWindow::copyColor(QTableWidget* targetTable) {
    qDebug() << Q_FUNC_INFO;


    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            ((QTextEdit*) targetTable->cellWidget(i, j))->setPalette(((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window));
        }
    }

    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {
            if(((QTextEdit*) tableWidget_2->cellWidget(i, j))->palette().color(QPalette::Window) == indirectMatchColor
                    && ((QTextEdit*) targetTable->cellWidget(i, j))->palette().color(QPalette::Window) == indirectMatchColor) {
                ((QTextEdit*) targetTable->cellWidget(i, j))->setPalette(directMatchColor);
            }
        }
    }
}
