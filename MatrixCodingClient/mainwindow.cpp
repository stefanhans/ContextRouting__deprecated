#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /*
     *
     * CREATE DEFAULT VALUES FOR STRUCTURE ELEMENTS
     *
     */

    matrixSideCount = 4;
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;
    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;

    run_id = 1;

    /*
     *
     * "tableTestWidget"
     *
     */

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



    /*
     *
     * "spatialTestConfigGBox"
     *
     */


    // "Side Length"
    sideLengthConfigLabel = new QLabel(tr("Side Length: "));
    sideLengthConfigSpinBox = new QSpinBox();
    sideLengthConfigSpinBox->setMinimum(2);
    sideLengthConfigSpinBox->setMaximum(16);
    sideLengthConfigSpinBox->setValue(4);
    sideLengthConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sideLengthConfigLabel->setBuddy(sideLengthConfigSpinBox);

    matrixSideCount = sideLengthConfigSpinBox->text().toInt();

    connect(sideLengthConfigSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSideLength(int)));

    // "Repaint"
    repaintConfigLabel = new QLabel(tr("Repaint: "));
    repaintConfigCheckBox = new QCheckBox();
    repaintConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    repaintConfigLabel->setBuddy(repaintConfigCheckBox);

    repaint = repaintConfigCheckBox->isChecked();

    connect(repaintConfigCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setRepainted(int)));

    // "Possible Permutation Figures"
    permutationFiguresConfigLabel = new QLabel(tr("Possible Permutation Figures: "));
    permutationFiguresConfigComboBox = new QComboBox();
    permutationFiguresConfigComboBox->addItem(tr("All possible figures"));
    permutationFiguresConfigComboBox->addItem(tr("Only squares"));
    permutationFiguresConfigComboBox->addItem(tr("Only distinct squares (recursive)"));
    permutationFiguresConfigLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    permutationFiguresConfigLabel->setBuddy(permutationFiguresConfigComboBox);

    connect(permutationFiguresConfigComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(resetSpatialFullTest(int)));

    // "Test Result"
    testResultLabel = new QLabel(tr("Test Result: "));
    testResultTextEdit = new QPlainTextEdit();
    testResultTextEdit->setAutoFillBackground(true);
    testResultTextEdit->setReadOnly(true);
    testResultTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    testResultTextEdit->setLineWidth(160);
    testResultLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    testResultLabel->setBuddy(testResultTextEdit);

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


    /*
     *
     * CREATE MAIN LAYOUT AND STRUCTURE ELEMENTS
     *
     */

    // "Test Matrix Configuration"
    spatialTestConfigGBox = new QGroupBox(tr("Test Matrix Configuration"));
    spatialTestConfigLayout = new QGridLayout;
    spatialTestConfigGBox->setLayout(spatialTestConfigLayout);

    spatialTestConfigLayout->addWidget(sideLengthConfigLabel,            0, 0);
    spatialTestConfigLayout->addWidget(sideLengthConfigSpinBox,          0, 1);
    spatialTestConfigLayout->addWidget(repaintConfigLabel,               1, 0);
    spatialTestConfigLayout->addWidget(repaintConfigCheckBox,            1, 1);
    spatialTestConfigLayout->addWidget(permutationFiguresConfigLabel,    2, 0);
    spatialTestConfigLayout->addWidget(permutationFiguresConfigComboBox, 2, 1);
    spatialTestConfigLayout->addWidget(testResultLabel,                   3, 0);
    spatialTestConfigLayout->addWidget(testResultTextEdit,                3, 1);

    // "Test Execution"
    testButtonGBox = new QGroupBox(tr("TestExecution"));
    testButtonLayout = new QGridLayout;
    testButtonGBox->setLayout(testButtonLayout);

    testButtonLayout->addWidget(startSpatialFullTest_Btn,   0, 0);
    testButtonLayout->addWidget(resetSpatialFullTest_Btn,   0, 1);
    testButtonLayout->addWidget(nextSpatialFullTest_Btn,    0, 2);
    testButtonLayout->addWidget(startSpatialSingleTest_Btn, 1, 0);
    testButtonLayout->addWidget(nextSpatialSingleTest_Btn,  1, 1);
    testButtonLayout->addWidget(resetSpatialSingleTest_Btn, 1, 2);


    spatialTestTableLayout =  new QHBoxLayout;
    spatialTestTableLayout->addWidget(tableTestWidget, 0, Qt::AlignHCenter);
    spatialTestTableLayout->addWidget(spatialTestConfigGBox);
    spatialTestTableLayout->addStretch();



    // "Test Run Matrix"
    spatialTestGBox = new QGroupBox(tr("Test Run Matrix"));
    spatiaTestGridLayout = new QGridLayout;
    spatialTestGBox->setLayout(spatiaTestGridLayout);

    spatiaTestGridLayout->addLayout(spatialTestTableLayout,   0, 0);
    spatiaTestGridLayout->addWidget(testButtonGBox,           1, 0);

    /*
     *
     *  DYNAMIC CODING MATRIX WIDGET SECTION
     *
     */
    dynamicCodingMatricesGBox = new QGroupBox(tr("Coding Matrices"));
    dynamicCodingMatricesLayout = new QGridLayout;
    dynamicCodingMatricesGBox->setLayout(dynamicCodingMatricesLayout);

    // Control Header - Coding Matrix Tables Count
    codingMatrixControlHeaderLabel = new QLabel(tr("Coding Matrix Tables Count: "));
    codingMatrixControlHeaderSpinBox = new QSpinBox();
    codingMatrixControlHeaderSpinBox->setMinimum(1);
    codingMatrixControlHeaderSpinBox->setMaximum(255);
    codingMatrixControlHeaderSpinBox->setValue(6);
    codingMatrixControlHeaderLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    codingMatrixControlHeaderLabel->setBuddy(codingMatrixControlHeaderSpinBox);

//    connect(sideLengthConfigSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSideLength(int)));

    dynamicCodingMatricesLayout->addWidget(codingMatrixControlHeaderLabel, 0, 0);
    dynamicCodingMatricesLayout->addWidget(codingMatrixControlHeaderSpinBox, 0, 1);



    for(int i=0; i<6; i++) {

        dynamicCodingMatrixWidgets.push_back(new CodingMatrixWidget(this));
        dynamicCodingMatrixWidgets.at(i)->setTitle(tr("Coding Matrix %1").arg(i+1));
    }

    // Layout Integrations
    for(int i=0; i<6; i++) {
        dynamicCodingMatricesLayout->addWidget(dynamicCodingMatrixWidgets.at(i), qFloor(i/3)+1, i%3);
    }


    // GUI - Main Layout
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(spatialTestGBox);
    mainLayout->addWidget(dynamicCodingMatricesGBox);
    mainLayout->addStretch();

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
 * startSpatialFullTest()
 *
 */

void MainWindow::startSpatialFullTest() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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


/*
 *
 * resetSpatialFullTest()
 *
 */

void MainWindow::resetSpatialFullTest(){
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    min_x = min_y = max_x =  max_y = 0;
    run_id = 1;
    stop = false;

    testResultTextEdit->clear();
    tableTestWidget->repaint();

    drawTestMatrix();

    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;
}



/*
 *
 * resetSpatialFullTest(int)
 *
 */

void MainWindow::resetSpatialFullTest(int index) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    qDebug() << index;


    resetSpatialFullTest();
}



/*
 *
 * nextSpatialSingleTest()
 *
 */

void MainWindow::nextSpatialSingleTest() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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


/*
 *
 * startSpatialSingleTest()
 *
 */

void MainWindow::startSpatialSingleTest() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

}


/*
 *
 * nextSpatialSingleTestStep()
 *
 */

void MainWindow::nextSpatialSingleTestStep() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

}


/*
 *
 * resetSpatialSingleTest()
 *
 */

void MainWindow::resetSpatialSingleTest() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

}


/*
 *
 * changeSideLength(int)
 *
 */
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

    matrixSideCount = sideLengthConfigSpinBox->text().toInt();
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;

    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;
}

/*
 *
 * setRepainted(int)
 *
 */
void MainWindow::setRepainted(int checked) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    repaint = checked;
}



/*
 *
 * clearTestMatrix()
 *
 */
void MainWindow::clearTestMatrix() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    for(int x=matrix_min_x; x<=matrix_max_x; x++) {
        for(int y=matrix_min_y; y<=matrix_max_y; y++) {
            ((QTextEdit*) tableTestWidget->cellWidget(x, y))->setPalette(QPalette(Qt::white));
        }
    }
}

/*
 *
 * drawTestMatrix()
 *
 */
void MainWindow::drawTestMatrix() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    clearTestMatrix();

    for(int x=min_x; x<=max_x; x++) {
        for(int y=min_y; y<=max_y; y++) {
            ((QTextEdit*) tableTestWidget->cellWidget(y, x))->setPalette(QPalette(Qt::red));
        }
    }

    if(repaint) {
        tableTestWidget->repaint();
    }
}

