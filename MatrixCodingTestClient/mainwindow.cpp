#include "mainwindow.h"

#include <iostream>

#define DEBUG 1

#include <QDebug>
#include <QtMath>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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

    // SpatialTests
    spatialTestGBox = new QGroupBox(tr("Test Run Matrix"));
//    spatialTestGBox->setAutoFillBackground(true);
//    spatialTestGBox->setPalette(QPalette(Qt::blue));

    spatialTestTableLayout =  new QHBoxLayout;


    spatialTestConfigGBox = new QGroupBox(tr("Test Matrix Configuration"));

    sideLengthConfigLabel = new QLabel(tr("Side Length: "));
    sideLengthConfigSpinBox = new QSpinBox();
    sideLengthConfigSpinBox->setMinimum(2);
    sideLengthConfigSpinBox->setMaximum(32);
    sideLengthConfigSpinBox->setValue(4);
    sideLengthConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sideLengthConfigLabel->setBuddy(sideLengthConfigSpinBox);



    // Matrix
    matrixSideCount = sideLengthConfigSpinBox->text().toInt();
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;
    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;

    run_id = 1;

    byteMatrix_1 = new ByteMatrix();
    byteMatrix_2 = new ByteMatrix();
    byteMatrix_3 = new ByteMatrix();
    byteMatrix_4 = new ByteMatrix();

    byteMatrix_1->sideLength = sideLengthConfigSpinBox->value();
    byteMatrix_2->sideLength = sideLengthConfigSpinBox->value();
    byteMatrix_3->sideLength = sideLengthConfigSpinBox->value();
    byteMatrix_4->sideLength = sideLengthConfigSpinBox->value();

    connect(sideLengthConfigSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSideLength(int)));

    repaintConfigLabel = new QLabel(tr("Repaint: "));
    repaintConfigCheckBox = new QCheckBox();
    repaintConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    repaintConfigLabel->setBuddy(repaintConfigCheckBox);

    connect(repaintConfigCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setRepainted(int)));

    repaint = repaintConfigCheckBox->isChecked();

    permutationFiguresConfigLabel = new QLabel(tr("Possible Permutation Figures: "));
    permutationFiguresConfigComboBox = new QComboBox();
    permutationFiguresConfigComboBox->addItem(tr("All possible figures"));
    permutationFiguresConfigComboBox->addItem(tr("Only squares"));
    permutationFiguresConfigComboBox->addItem(tr("Only distinct squares (recursive)"));
    permutationFiguresConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    permutationFiguresConfigLabel->setBuddy(permutationFiguresConfigComboBox);

    connect(permutationFiguresConfigComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resetSpatialFullTest(int)));

    testResultLabel = new QLabel(tr("Test Result: "));
    testResultTextEdit = new QPlainTextEdit();
    testResultTextEdit->setAutoFillBackground(true);
    testResultTextEdit->setReadOnly(true);
    testResultTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    testResultTextEdit->setLineWidth(160);
    testResultLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    testResultLabel->setBuddy(testResultTextEdit);


    spatialTestConfigLayout = new QGridLayout;
    spatialTestConfigLayout->addWidget(sideLengthConfigLabel,            0, 0);
    spatialTestConfigLayout->addWidget(sideLengthConfigSpinBox,          0, 1);
    spatialTestConfigLayout->addWidget(repaintConfigLabel,               1, 0);
    spatialTestConfigLayout->addWidget(repaintConfigCheckBox,            1, 1);
    spatialTestConfigLayout->addWidget(permutationFiguresConfigLabel,    2, 0);
    spatialTestConfigLayout->addWidget(permutationFiguresConfigComboBox, 2, 1);
    spatialTestConfigLayout->addWidget(testResultLabel,                   3, 0);
    spatialTestConfigLayout->addWidget(testResultTextEdit,                3, 1);

    spatialTestConfigGBox->setLayout(spatialTestConfigLayout);




    // TestTable
    tableTestWidget = new QTableWidget(matrixSideCount, matrixSideCount, this);
    tableTestWidgetFixedSide = 500;
    tableTestWidgetFixedMargin = 28;

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    tableTestWidget->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableTestWidget->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        tableTestWidget->setColumnWidth(i, cellSide);
        tableTestWidget->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableTestWidget->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableTestWidget->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableTestWidget->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }
    drawTestMatrix();

    spatialTestTableLayout->addWidget(tableTestWidget, 0, Qt::AlignHCenter);




    spatialTestTableLayout->addWidget(spatialTestConfigGBox);

    spatialTestTableLayout->addStretch();


    // Spatial Full Test Buttons
    startSpatialFullTest_Btn = new QPushButton(tr("Start Full Test"), this);
    resetSpatialFullTest_Btn = new QPushButton(tr("Reset Full Test"), this);
    nextSpatialFullTest_Btn = new QPushButton(tr("Next Single Test"), this);

    connect(startSpatialFullTest_Btn, SIGNAL(clicked(bool)), this, SLOT(startSpatialFullTest()));
    connect(resetSpatialFullTest_Btn, SIGNAL(clicked(bool)), this, SLOT(resetSpatialFullTest()));
    connect(nextSpatialFullTest_Btn, SIGNAL(clicked(bool)), this, SLOT(nextSpatialSingleTest()));

    // Spatial Single Test Buttons
    startSpatialSingleTest_Btn = new QPushButton(tr("Start Single Test"), this);
    nextSpatialSingleTest_Btn = new QPushButton(tr("Next Single Test Step"), this);
    resetSpatialSingleTest_Btn = new QPushButton(tr("Reset Single Test"), this);


    connect(startSpatialSingleTest_Btn, SIGNAL(clicked(bool)), this, SLOT(startSpatialSingleTest()));
    connect(nextSpatialSingleTest_Btn, SIGNAL(clicked(bool)), this, SLOT(nextSpatialSingleTestStep()));
    connect(resetSpatialSingleTest_Btn, SIGNAL(clicked(bool)), this, SLOT(resetSpatialSingleTest()));

    // Spatial Test Buttons Layout
    spatiaTestGridLayout = new QGridLayout;
    spatiaTestGridLayout->addLayout(spatialTestTableLayout,     0, 0, 1, 5);
    spatiaTestGridLayout->addWidget(startSpatialFullTest_Btn,   1, 0);
    spatiaTestGridLayout->addWidget(resetSpatialFullTest_Btn,   1, 1);
    spatiaTestGridLayout->addWidget(nextSpatialFullTest_Btn,    1, 2);
    spatiaTestGridLayout->addWidget(startSpatialSingleTest_Btn, 2, 0);
    spatiaTestGridLayout->addWidget(nextSpatialSingleTest_Btn,  2, 1);
    spatiaTestGridLayout->addWidget(resetSpatialSingleTest_Btn, 2, 2);

    spatialTestGBox->setLayout(spatiaTestGridLayout);







    // Test Coding Matrices Header
    testCodingMatricesHeaderGroupBox = new QGroupBox(tr("..."));
//    testCodingMatricesHeaderGroupBox->setAutoFillBackground(true);
//    testCodingMatricesHeaderGroupBox->setPalette(QPalette(Qt::lightGray));

    testCodingMatricesHeaderLayout = new QHBoxLayout;
    testCodingMatricesHeaderGroupBox->setLayout(testCodingMatricesHeaderLayout);

    // Test Coding Matrices Tables
    testCodingMatricesTablesGroupBox = new QGroupBox(tr("Tables"));
//    testCodingMatricesTablesGroupBox->setAutoFillBackground(true);
//    testCodingMatricesTablesGroupBox->setPalette(QPalette(Qt::lightGray));

    testCodingMatricesTablesLayout = new QGridLayout;
    testCodingMatricesTablesGroupBox->setLayout(testCodingMatricesTablesLayout);


    // Test Coding Matrices
    testCodingMatricesGroupBox = new QGroupBox(tr("Test Coding Matrices"));

    testCodingMatricesLayout = new QVBoxLayout;
    testCodingMatricesGroupBox->setLayout(testCodingMatricesLayout);

    testCodingMatricesLayout->addWidget(testCodingMatricesHeaderGroupBox);
    testCodingMatricesLayout->addWidget(testCodingMatricesTablesGroupBox);


    // Table_1
    testCodingMatricesTableGroupBox_1 = new QGroupBox(tr("no coding matrix loaded"));
    testCodingMatricesTableWidget_1 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    testCodingMatricesTableWidget_1->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    testCodingMatricesTableWidget_1->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        testCodingMatricesTableWidget_1->setColumnWidth(i, cellSide);
        testCodingMatricesTableWidget_1->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            testCodingMatricesTableWidget_1->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) testCodingMatricesTableWidget_1->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) testCodingMatricesTableWidget_1->cellWidget(i, j))->setPalette(QPalette(Qt::white));


        }
    }

    testCodingMatricesFile_Btn_1 = new QPushButton(tr("Load Matrix"));
    testCodingMatricesFile_Btn_1->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    connect(testCodingMatricesFile_Btn_1, SIGNAL(clicked(bool)), this, SLOT(testCodingMatricesFileLoad_1()));

    testCodingMatricesTableLayout_1 = new QVBoxLayout;
    testCodingMatricesTableGroupBox_1->setLayout(testCodingMatricesTableLayout_1);

    testCodingMatricesTableLayout_1->addWidget(testCodingMatricesTableWidget_1);
    testCodingMatricesTableLayout_1->addWidget(testCodingMatricesFile_Btn_1);


    // Table_2
    testCodingMatricesTableGroupBox_2 = new QGroupBox(tr("no coding matrix loaded"));
    testCodingMatricesTableWidget_2 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    testCodingMatricesTableWidget_2->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    testCodingMatricesTableWidget_2->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        testCodingMatricesTableWidget_2->setColumnWidth(i, cellSide);
        testCodingMatricesTableWidget_2->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            testCodingMatricesTableWidget_2->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) testCodingMatricesTableWidget_2->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) testCodingMatricesTableWidget_2->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }

    testCodingMatricesFile_Btn_2 = new QPushButton(tr("Load Matrix"));
    testCodingMatricesFile_Btn_2->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    connect(testCodingMatricesFile_Btn_2, SIGNAL(clicked(bool)), this, SLOT(testCodingMatricesFileLoad_2()));

    testCodingMatricesTableLayout_2 = new QVBoxLayout;
    testCodingMatricesTableGroupBox_2->setLayout(testCodingMatricesTableLayout_2);

    testCodingMatricesTableLayout_2->addWidget(testCodingMatricesTableWidget_2);
    testCodingMatricesTableLayout_2->addWidget(testCodingMatricesFile_Btn_2);


    // Table_3
    testCodingMatricesTableGroupBox_3 = new QGroupBox(tr("no coding matrix loaded"));
    testCodingMatricesTableWidget_3 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    testCodingMatricesTableWidget_3->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    testCodingMatricesTableWidget_3->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        testCodingMatricesTableWidget_3->setColumnWidth(i, cellSide);
        testCodingMatricesTableWidget_3->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            testCodingMatricesTableWidget_3->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) testCodingMatricesTableWidget_3->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) testCodingMatricesTableWidget_3->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }

    testCodingMatricesFile_Btn_3 = new QPushButton(tr("Load Matrix"));
    testCodingMatricesFile_Btn_3->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    connect(testCodingMatricesFile_Btn_3, SIGNAL(clicked(bool)), this, SLOT(testCodingMatricesFileLoad_3()));

    testCodingMatricesTableLayout_3 = new QVBoxLayout;
    testCodingMatricesTableGroupBox_3->setLayout(testCodingMatricesTableLayout_3);

    testCodingMatricesTableLayout_3->addWidget(testCodingMatricesTableWidget_3);
    testCodingMatricesTableLayout_3->addWidget(testCodingMatricesFile_Btn_3);


    // Table_4
    testCodingMatricesTableGroupBox_4 = new QGroupBox(tr("no coding matrix loaded"));
    testCodingMatricesTableWidget_4 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    testCodingMatricesTableWidget_4->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    testCodingMatricesTableWidget_4->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        testCodingMatricesTableWidget_4->setColumnWidth(i, cellSide);
        testCodingMatricesTableWidget_4->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            testCodingMatricesTableWidget_4->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) testCodingMatricesTableWidget_4->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) testCodingMatricesTableWidget_4->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }

    testCodingMatricesFile_Btn_4 = new QPushButton(tr("Load Matrix"));
    testCodingMatricesFile_Btn_4->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    connect(testCodingMatricesFile_Btn_4, SIGNAL(clicked(bool)), this, SLOT(testCodingMatricesFileLoad_4()));

    testCodingMatricesTableLayout_4 = new QVBoxLayout;
    testCodingMatricesTableGroupBox_4->setLayout(testCodingMatricesTableLayout_4);

    testCodingMatricesTableLayout_4->addWidget(testCodingMatricesTableWidget_4);
    testCodingMatricesTableLayout_4->addWidget(testCodingMatricesFile_Btn_4);


    testCodingMatricesTablesLayout->addWidget(testCodingMatricesTableGroupBox_1, 0, 0);
    testCodingMatricesTablesLayout->addWidget(testCodingMatricesTableGroupBox_2, 0, 1);
    testCodingMatricesTablesLayout->addWidget(testCodingMatricesTableGroupBox_3, 1, 0);
    testCodingMatricesTablesLayout->addWidget(testCodingMatricesTableGroupBox_4, 1, 1);








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

    tableWidget_1 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    tableWidget_1->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidget_1->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    int n=0;
    for(int i=0; i<matrixSideCount; i++) {
        tableWidget_1->setColumnWidth(i, cellSide);
        tableWidget_1->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidget_1->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialTableLayout->addWidget(tableWidget_1, 0, Qt::AlignHCenter);


    tableWidget_2 = new QTableWidget(matrixSideCount, matrixSideCount, this);

    tableWidget_2->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidget_2->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    n=0;
    for(int i=0; i<matrixSideCount; i++) {
        tableWidget_2->setColumnWidth(i, cellSide);
        tableWidget_2->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidget_2->setCellWidget(j, i, new QTextEdit);

            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setEnabled(false);
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialTableLayout->addWidget(tableWidget_2, 0, Qt::AlignHCenter);


    tableWidgetAll = new QTableWidget(matrixSideCount, matrixSideCount, this);
    tableWidgetAll->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidgetAll->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    n=0;
    for(int i=0; i<matrixSideCount; i++) {
        tableWidgetAll->setColumnWidth(i, cellSide);
        tableWidgetAll->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidgetAll->setCellWidget(j, i, new QTextEdit);

            ((QTextEdit*) tableWidgetAll->cellWidget(j, i))->setEnabled(false);
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

    // Test
    mainLayout->addWidget(spatialTestGBox);
    mainLayout->addWidget(testCodingMatricesGroupBox);

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

void MainWindow::testCodingMatricesFileLoad_1() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Matrices"), "/home/stefan/Development/ContextRouting/Matrices", tr("%1x%1 Matrix Files (*.%1x%1_matrix)").arg(matrixSideCount));
    QFile file(fileName);

    if (file.open(QFile::ReadOnly)) {

        int row = 0;
        QString line = file.readLine(200);
        QStringList list;

        while (file.canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    testCodingMatricesTableWidget_1->setCellWidget(row, col, new QTextEdit);
                    ((QTextEdit*) testCodingMatricesTableWidget_1->cellWidget(row, col))->setText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) testCodingMatricesTableWidget_1->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                }
                ++row;

                line = file.readLine(200);
            }
        }
    }
    file.close();    
    testCodingMatricesTableGroupBox_1->setTitle(fileName.section('/', -1));

    // Load data into model
    byteMatrix_1->loadDataFile(&file);

}
void MainWindow::testCodingMatricesFileLoad_2() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Matrices"), "/home/stefan/Development/ContextRouting/Matrices", tr("%1x%1 Matrix Files (*.%1x%1_matrix)").arg(matrixSideCount));
    QFile file(fileName);

    if (file.open(QFile::ReadOnly)) {

        int row = 0;
        QString line = file.readLine(200);
        QStringList list;

        while (file.canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    testCodingMatricesTableWidget_2->setCellWidget(row, col, new QTextEdit);
                    ((QTextEdit*) testCodingMatricesTableWidget_2->cellWidget(row, col))->setText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) testCodingMatricesTableWidget_2->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                }
                ++row;

                line = file.readLine(200);
            }
        }
    }
    file.close();
    testCodingMatricesTableGroupBox_2->setTitle(fileName.section('/', -1));

    // Load data into model
    byteMatrix_2->loadDataFile(&file);
}
void MainWindow::testCodingMatricesFileLoad_3() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Matrices"), "/home/stefan/Development/ContextRouting/Matrices", tr("%1x%1 Matrix Files (*.%1x%1_matrix)").arg(matrixSideCount));
    QFile file(fileName);

    if (file.open(QFile::ReadOnly)) {

        int row = 0;
        QString line = file.readLine(200);
        QStringList list;

        while (file.canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    testCodingMatricesTableWidget_3->setCellWidget(row, col, new QTextEdit);
                    ((QTextEdit*) testCodingMatricesTableWidget_3->cellWidget(row, col))->setText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) testCodingMatricesTableWidget_3->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                }
                ++row;

                line = file.readLine(200);
            }
        }
    }
    file.close();
    testCodingMatricesTableGroupBox_3->setTitle(fileName.section('/', -1));

    // Load data into model
    byteMatrix_3->loadDataFile(&file);
}
void MainWindow::testCodingMatricesFileLoad_4() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Matrices"), "/home/stefan/Development/ContextRouting/Matrices", tr("%1x%1 Matrix Files (*.%1x%1_matrix)").arg(matrixSideCount));
    QFile file(fileName);

    if (file.open(QFile::ReadOnly)) {

        int row = 0;
        QString line = file.readLine(200);
        QStringList list;

        while (file.canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    testCodingMatricesTableWidget_4->setCellWidget(row, col, new QTextEdit);
                    ((QTextEdit*) testCodingMatricesTableWidget_4->cellWidget(row, col))->setText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) testCodingMatricesTableWidget_4->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                }
                ++row;

                line = file.readLine(200);
            }
        }
    }
    file.close();
    testCodingMatricesTableGroupBox_4->setTitle(fileName.section('/', -1));

    // Load data into model
    byteMatrix_4->loadDataFile(&file);
}

void MainWindow::changeSideLength(int sideLength) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    matrixSideCount = sideLength;

    // Test Table
    tableTestWidget->clear();

    tableTestWidget->setColumnCount(matrixSideCount);
    tableTestWidget->setRowCount(matrixSideCount);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    tableTestWidget->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableTestWidget->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        tableTestWidget->setColumnWidth(i, cellSide);
        tableTestWidget->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableTestWidget->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableTestWidget->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableTestWidget->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }



    // tableWidget_1
    tableWidget_1->clear();

    tableWidget_1->setColumnCount(matrixSideCount);
    tableWidget_1->setRowCount(matrixSideCount);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    tableWidget_1->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidget_1->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    int n = 0;
    for(int i=0; i<matrixSideCount; i++) {
        tableWidget_1->setColumnWidth(i, cellSide);
        tableWidget_1->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidget_1->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(QPalette(Qt::white));

            n++;

        }
    }



    // tableWidget_2
    tableWidget_2->clear();

    tableWidget_2->setColumnCount(matrixSideCount);
    tableWidget_2->setRowCount(matrixSideCount);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    tableWidget_2->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidget_2->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    n = 0;
    for(int i=0; i<matrixSideCount; i++) {
        tableWidget_2->setColumnWidth(i, cellSide);
        tableWidget_2->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidget_2->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidget_2->cellWidget(i, j))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget_2->cellWidget(i, j))->setFont(QFont("Times", 8, QFont::Bold));
            ((QTextEdit*) tableWidget_2->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidget_2->cellWidget(i, j))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    // tableWidgetAll
    tableWidgetAll->clear();

    tableWidgetAll->setColumnCount(matrixSideCount);
    tableWidgetAll->setRowCount(matrixSideCount);

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    tableWidgetAll->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    tableWidgetAll->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        tableWidgetAll->setColumnWidth(i, cellSide);
        tableWidgetAll->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            tableWidgetAll->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidgetAll->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidgetAll->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }

    matrixSideCount = sideLengthConfigSpinBox->text().toInt();
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;

    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;
}

void MainWindow::setRepainted(int checked) {
    qDebug() << Q_FUNC_INFO;

    repaint = checked;
}


void MainWindow::clearTestMatrix() {
    qDebug() << Q_FUNC_INFO;

    for(int x=matrix_min_x; x<=matrix_max_x; x++) {
        for(int y=matrix_min_y; y<=matrix_max_y; y++) {
            ((QTextEdit*) tableTestWidget->cellWidget(x, y))->setPalette(QPalette(noColor));
        }
    }
}

void MainWindow::drawTestMatrix() {
    qDebug() << Q_FUNC_INFO;

    clearTestMatrix();

    for(int x=min_x; x<=max_x; x++) {
        for(int y=min_y; y<=max_y; y++) {
            ((QTextEdit*) tableTestWidget->cellWidget(y, x))->setPalette(QPalette(redColor));
        }
    }

    if(repaint) {
        tableTestWidget->repaint();
    }
}

void MainWindow::startSpatialFullTest() {
    qDebug() << Q_FUNC_INFO;

    resetSpatialFullTest();

    testResultTextEdit->setPlainText(QString(tr("Side Length\t: %1").arg(sideLengthConfigSpinBox->value())));
    testResultTextEdit->appendPlainText(QString(tr("Repaint\t\t: %1").arg(repaintConfigCheckBox->isChecked()?"Yes":"No")));
    testResultTextEdit->appendPlainText(QString(tr("Permutation Figure\t: %1").arg(permutationFiguresConfigComboBox->currentText())));

    while(true) {

        nextSpatialSingleTest();

        if(stop) {
            qDebug().noquote() << "STOPPED at run_id " << run_id;
            return;
        }
    }
}



void MainWindow::resetSpatialFullTest(){
    qDebug() << Q_FUNC_INFO;

    min_x = min_y = max_x =  max_y = 0;
    run_id = 1;
    stop = false;

    testResultTextEdit->clear();
    tableTestWidget->repaint();

    drawTestMatrix();

    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;
}

void MainWindow::resetSpatialFullTest(int index) {
    qDebug() << Q_FUNC_INFO;

    qDebug() << index;


    resetSpatialFullTest();
}


void MainWindow::nextSpatialSingleTest() {
    qDebug() << Q_FUNC_INFO;

    if(permutationFiguresConfigComboBox->currentText() == "Only distinct squares (recursive)") {

        if(min_x == matrix_max_x && min_y == matrix_max_y) {
            run_id++;
            stop = true;
            return;
        }

        if(tmp_matrix_min_x == -1) {

            tmp_matrix_min_x = matrix_min_x;
            tmp_matrix_min_y = matrix_min_y;
            tmp_matrix_max_x = matrix_max_x;
            tmp_matrix_max_y = matrix_max_y;

            min_x = matrix_min_x;
            min_y = matrix_min_y;
            max_x = matrix_max_x;
            max_y = matrix_max_y;

            qDebug() << "min_x = matrix_min_x: " << min_x;
            qDebug() << "min_y = matrix_min_y: " << min_y;
            qDebug() << "max_x = matrix_max_x: " << max_x;
            qDebug() << "max_y = matrix_max_y: " << max_y;

            drawTestMatrix();

        }
        else {
            min_x = matrix_min_x;
            min_y = matrix_min_y;
            max_x = matrix_max_x;
            max_y = matrix_max_y;
        }

        qDebug() << "min_x = matrix_min_x: " << min_x;
        qDebug() << "min_y = matrix_min_y: " << min_y;
        qDebug() << "max_x = matrix_max_x: " << max_x;
        qDebug() << "max_y = matrix_max_y: " << max_y;

        drawTestMatrix();


        min_x = matrix_min_x;
        min_y = matrix_min_y;
        max_x /= 2;
        max_y /= 2;

        qDebug() << "min_x: " << min_x;
        qDebug() << "min_y: " << min_y;
        qDebug() << "max_x: " << max_x;
        qDebug() << "max_y: " << max_y;
        qDebug() << "max_x - min_x" << max_x - min_x;

        drawTestMatrix();

        min_x = max_x +1;
        max_x = matrix_max_x;

        drawTestMatrix();

        min_x = matrix_min_x;
        min_y = max_y + 1;
        max_x /= 2;
        max_y = matrix_max_y;


        min_x = max_x +1;
        max_x = matrix_max_x;

        drawTestMatrix();


        stop = true;

    //    while ( max_x - min_x >= 0 ) {
    //        drawTestMatrix();

    //        min_x = matrix_min_x;
    //        min_y = matrix_min_y;
    //        max_x /= 2;
    //        max_y /= 2;
    //    }


        testResultTextEdit->clear();
        testResultTextEdit->setPlainText(QString(tr("Side Length\t: %1").arg(sideLengthConfigSpinBox->value())));
        testResultTextEdit->appendPlainText(QString(tr("Repaint\t\t: %1").arg(repaintConfigCheckBox->isChecked()?"Yes":"No")));
        testResultTextEdit->appendPlainText(QString(tr("Permutation Figure\t: %1").arg(permutationFiguresConfigComboBox->currentText())));

        run_id++;
        testResultTextEdit->appendPlainText(QString(tr("Tested Permutations\t: %1").arg(run_id)));

        drawTestMatrix();

    }


    else if(permutationFiguresConfigComboBox->currentText() == "All possible figures") {

        if(min_x == matrix_max_x && min_y == matrix_max_y) {
            run_id++;
            stop = true;
            return;
        }

        if(max_x < matrix_max_x) {
            max_x++;
        }
        else if (max_y < matrix_max_y) {
            max_x = min_x;
            max_y++;
        }
        else if (min_x < matrix_max_x) {
            min_x++;
            max_x = min_x;
            max_y = min_y;
        }
        else if (min_y < matrix_max_y) {
            min_y++;
            min_x = matrix_min_x;
            max_x = min_x;
            max_y = min_y;
        }
        else {
            stop = true;
        }

        testResultTextEdit->clear();
        testResultTextEdit->setPlainText(QString(tr("Side Length\t: %1").arg(sideLengthConfigSpinBox->value())));
        testResultTextEdit->appendPlainText(QString(tr("Repaint\t\t: %1").arg(repaintConfigCheckBox->isChecked()?"Yes":"No")));
        testResultTextEdit->appendPlainText(QString(tr("Permutation Figure\t: %1").arg(permutationFiguresConfigComboBox->currentText())));

        run_id++;
        testResultTextEdit->appendPlainText(QString(tr("Tested Permutations\t: %1").arg(run_id)));

        drawTestMatrix();



    }

    else if(permutationFiguresConfigComboBox->currentText() == "Only squares") {

        if(min_x == matrix_max_x && min_y == matrix_max_y) {
            run_id++;
            stop = true;
            return;
        }

        if(max_x < matrix_max_x && max_y < matrix_max_y) {
            max_x++;
            max_y++;
        }
        else if (min_x < matrix_max_x) {
            min_x++;
            max_x = min_x;
            max_y = min_y;
        }
        else if (min_x < matrix_max_x) {
            min_x++;
            max_x = min_x;
            max_y = min_y;
        }
        else if (min_y < matrix_max_y) {
            min_y++;
            min_x = matrix_min_x;
            max_x = min_x;
            max_y = min_y;
        }
        else {
            stop = true;
        }

        testResultTextEdit->clear();
        testResultTextEdit->setPlainText(QString(tr("Side Length\t: %1").arg(sideLengthConfigSpinBox->value())));
        testResultTextEdit->appendPlainText(QString(tr("Repaint\t\t: %1").arg(repaintConfigCheckBox->isChecked()?"Yes":"No")));
        testResultTextEdit->appendPlainText(QString(tr("Permutation Figure\t: %1").arg(permutationFiguresConfigComboBox->currentText())));

        run_id++;
        testResultTextEdit->appendPlainText(QString(tr("Tested Permutations\t: %1").arg(run_id)));

        drawTestMatrix();

    }
    else {
        stop = true;
    }
}



void MainWindow::startSpatialSingleTest() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

}

void MainWindow::nextSpatialSingleTestStep() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

//    int mask;

//    // ContentBrick's mask: Loop all permutations of one byte with 0-bits left and 1-bits (right both from none to all)
//    for(int bit=0; bit <=2; bit++) {
//        mask = (int) qPow(2, bit);
//        qDebug() << "mask: " << mask;

//        // ContentBrick's content: Loop all permutations
//        for(int content=0; content<4; content+=mask) {

////            ContextBrick *firstMatch = byteMatrix_1->getFirstMatch(1, 1, 1, 2);
//            qDebug() << QString("byteMatrix_1->isMatch(1, 1, %1, %2) => %3").arg(content).arg(mask).arg(byteMatrix_1->isMatch(1, 1, content, mask));

//        }
//    }

    ContextBrick *contextBrick = new ContextBrick(0, 0);

    for (int i=0; i < 16; i++) {
        if(contextBrick->isMatch(i)) {

            qDebug() << QString("contextBrick->isMatch(%1) => match").arg(i);
        }
        else {

            qDebug() << QString("contextBrick->isMatch(%1) => no match").arg(i);
        }

    }

//    qDebug() << "min_x: " << min_x;
//    qDebug() << "min_y: " << min_y;
//    qDebug() << "max_x: " << max_x;
//    qDebug() << "max_y: " << max_y;

//    qDebug() << "contextBrick->content: " << contextBrick->content;

//    qDebug() << "byteMatrix_1->sideLength: " << byteMatrix_1->sideLength;

//    do {
//        while(contextBrick->setNextMaskInstance(byteMatrix_1->sideLength)) {
//            for (int x = 0; x < byteMatrix_1->sideLength; x++) {
//                for (int y = 0; y < byteMatrix_1->sideLength; y++)

//                    if(byteMatrix_1->isMatch(min_x, min_y, max_x, max_y, contextBrick->content, contextBrick->mask)) {
//                        qDebug() << QString("martix[%1][%2]: %3 => match").arg(x).arg(y).arg(byteMatrix_1->matrix[x][y]);

//                    }
//                    else {
//                        qDebug() << QString("martix[%1][%2]: %3 => no match").arg(x).arg(y).arg(byteMatrix_1->matrix[x][y]);

//                    }
//            }

//            qDebug() << "contextBrick->content: " << contextBrick->content;
//            qDebug() << "contextBrick->mask: " << contextBrick->mask;
//        }
//    } while(contextBrick->setNextMask());



}

void MainWindow::resetSpatialSingleTest() {
    qDebug() << Q_FUNC_INFO;

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

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
        }
    }
}

void MainWindow::clearOfferContent_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == offerContentColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearOfferMask_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == offerMaskColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestContent_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == requestContentColor) {
                ((QTextEdit*) tableWidget_1->cellWidget(i, j))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestMask_1() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
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
    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {

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
    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {

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

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
        }
    }
}

void MainWindow::clearOfferContent_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == offerContentColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearOfferMask_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == offerMaskColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestContent_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if (((QTextEdit*) tableWidget_2->cellWidget(j, i))->palette().color(QPalette::Window) == requestContentColor) {
                ((QTextEdit*) tableWidget_2->cellWidget(j, i))->setPalette(noColor);
            }
        }
    }
}

void MainWindow::clearRequestMask_2() {
    qDebug() << Q_FUNC_INFO;

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
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
    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {

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
    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {

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
}


/*
 *
 *  All
 */

void MainWindow::clearSpatialAll() {
    qDebug() << Q_FUNC_INFO;

    clearSpatial_1();
    clearSpatial_2();

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
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

    for(int i=0; i<matrixSideCount; i++) {
        for(int j=0; j<matrixSideCount; j++) {
            if(((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == ((QTextEdit*) tableWidget_2->cellWidget(i, j))->palette().color(QPalette::Window)
                    &&
                    (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == indirectMatchColor
                     ||
                     ((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == directMatchColor)) {
                ((QTextEdit*) tableWidgetAll->cellWidget(i, j))->setPalette(((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window));
            }
            else {
                if((((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == directMatchColor
                    &&
                    ((QTextEdit*) tableWidget_2->cellWidget(i, j))->palette().color(QPalette::Window) == indirectMatchColor)
                        ||
                        (((QTextEdit*) tableWidget_1->cellWidget(i, j))->palette().color(QPalette::Window) == indirectMatchColor
                         &&
                         ((QTextEdit*) tableWidget_2->cellWidget(i, j))->palette().color(QPalette::Window) == directMatchColor)) {
                    ((QTextEdit*) tableWidgetAll->cellWidget(i, j))->setPalette(indirectMatchColor);
                }
            }
        }
    }
}
