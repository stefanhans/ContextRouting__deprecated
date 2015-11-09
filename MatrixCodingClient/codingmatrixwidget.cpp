#include "codingmatrixwidget.h"

#include <QDebug>
#include <QTextEdit>
#include <QTableWidget>
#include <QSpacerItem>
#include <QFileDialog>
#include <QtMath>

CodingMatrixWidget::CodingMatrixWidget(QWidget *parent)
    : QGroupBox(parent)
{
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    byteMatrix = new ByteMatrix;

    contextBrick = new ContextBrick;

    codingMatrixLayout = new QVBoxLayout;
    setLayout(codingMatrixLayout);


    // Header Layout
    headerLayout = new QGridLayout;

    locationCxBkLbl = new QLabel(tr("Location: "));
    locationCxBkLnEd = new QLineEdit;    
    locationCxBkLnEd->setReadOnly(true);
    locationCxBkLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    locationCxBkLbl->setBuddy(locationCxBkLnEd);

    maskCxBkLbl = new QLabel(tr("Mask: "));
    maskCxBkLnEd = new QLineEdit;
    maskCxBkLnEd->setReadOnly(true);
    maskCxBkLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    maskCxBkLbl->setBuddy(maskCxBkLnEd);

    repaintProgressLbl = new QLabel(tr("Repaint: "));
    repaintProgressCkBx = new QCheckBox;
    repaintProgressLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    repaintProgressLbl->setBuddy(repaintProgressCkBx);

    loadCodingMatrixBtn = new QPushButton(tr("Load Coding Matrix"));
    connect(loadCodingMatrixBtn, SIGNAL(clicked(bool)), this, SLOT(loadCodingMatrix()));

    headerLayout->addWidget(locationCxBkLbl,      0, 0);
    headerLayout->addWidget(locationCxBkLnEd,     0, 1);
    headerLayout->addWidget(repaintProgressLbl,   0, 2);
    headerLayout->addWidget(repaintProgressCkBx,  0, 3);
    headerLayout->addWidget(maskCxBkLbl,          1, 0);
    headerLayout->addWidget(maskCxBkLnEd,         1, 1);
    headerLayout->addWidget(loadCodingMatrixBtn,  1, 2, 1, 2);

    headerLayout->addItem(new QSpacerItem(45, 10), 0, 4);

    codingMatrixLayout->addLayout(headerLayout);

    // Table
    codingMatrixTable = new QTableWidget;

    codingMatrixTable->setRowCount(4);
    codingMatrixTable->setColumnCount(4);

    tableTestWidgetFixedSide = 500;
    tableTestWidgetFixedMargin = 28;


    matrixSideCount = 4;
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;
    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;

    run_id = 1;

    cellSide = tableTestWidgetFixedSide/matrixSideCount;
    codingMatrixTable->setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    codingMatrixTable->setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        codingMatrixTable->setColumnWidth(i, cellSide);
        codingMatrixTable->setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            codingMatrixTable->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) codingMatrixTable->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) codingMatrixTable->cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }
    codingMatrixLayout->addWidget(codingMatrixTable);

    // Button Layout
    buttonLayout = new QGridLayout;

    startEncodingBtn = new QPushButton(tr("Start Encoding"));
    connect(startEncodingBtn, SIGNAL(clicked(bool)), this, SLOT(startEncoding()));

    nextEncodingStepBtn = new QPushButton(tr("Next Encoding Step"));
    connect(nextEncodingStepBtn, SIGNAL(clicked(bool)), this, SLOT(nextEncodingStep()));

    resetEncodingBtn = new QPushButton(tr("Reset Encoding"));
    connect(resetEncodingBtn, SIGNAL(clicked(bool)), this, SLOT(resetEncoding()));

    // Report
    encodingReportTxEd = new QPlainTextEdit;
    encodingReportTxEd->setFixedHeight(200);
    encodingReportTxEd->setReadOnly(true);

    buttonLayout->addWidget(startEncodingBtn,    0, 0);
    buttonLayout->addWidget(nextEncodingStepBtn, 0, 1);
    buttonLayout->addWidget(resetEncodingBtn,    0, 2);
    buttonLayout->addWidget(encodingReportTxEd,  1, 0, 1, 3);

    buttonLayout->addItem(new QSpacerItem(40, 10), 0, 3);

    codingMatrixLayout->addLayout(buttonLayout);






}

void CodingMatrixWidget::loadCodingMatrix() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Matrices"), "/home/stefan/Development/ContextRouting/Matrices", tr("%1x%1 Matrix Files (*.%1x%1_matrix)").arg(matrixSideCount));
    QFile file(fileName);

    int highestNumber = 0;
    byteMatrix->sideLength = 0;

    contextBrick->reset();

    if (file.open(QFile::ReadOnly)) {

        QString line = file.readLine(200);
        QStringList list;

        int row = 0;
        while (file.canReadLine()) {

            if (!line.startsWith("#") && line.contains(",")) {

                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setPlainText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setAutoFillBackground(true);
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setPalette(QPalette(Qt::white));

                    byteMatrix->matrix[row][col] = list.at(col).toInt();

                    if( highestNumber < list.at(col).toInt() ) {
                        highestNumber = list.at(col).toInt();
                    }
                }
                ++row;
                ++byteMatrix->sideLength;

                line = file.readLine(200);
            }
        }
    }

    file.close();

    byteMatrix->dataUrl = fileName;
    byteMatrix->highestNumber = highestNumber;

    setTitle(fileName.section('/', -1));

    run_id=1;
    encodingReportTxEd->clear();

    displayContextBrick();
    paintContextBrick();


    if (DEBUG) byteMatrix->printMatrix();
}


void CodingMatrixWidget::startEncoding() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;


    encodingReportTxEd->setPlainText(byteMatrix->printMatrix());

    stop = 0;

    while(stop == 0) {
        nextEncodingStep();
    }



}

void CodingMatrixWidget::nextEncodingStep() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    qDebug() << contextBrick->content << " == " << pow(byteMatrix->sideLength, 2);
    qDebug() << contextBrick->content << " == " << pow(2, byteMatrix->sideLength);

    if ( (contextBrick->content == pow(byteMatrix->sideLength, 2))
         || ( (contextBrick->content == 0) && (contextBrick->mask+1 == pow(2, byteMatrix->sideLength)))
         || (contextBrick->content > byteMatrix->highestNumber || contextBrick->mask >= byteMatrix->highestNumber)
         ) {
        stop = 1;
        return;
    }

    encodingReportTxEd->appendPlainText(QString(tr("Encoding Step\t: %1").arg(QString("%1").arg(run_id++), 3, QLatin1Char(' '))));

    paintContextBrick(Qt::white, Qt::white);

    if( ! contextBrick->setNextMaskInstance(byteMatrix->sideLength, byteMatrix->highestNumber)) {
        contextBrick->content = 0;
        contextBrick->setNextMask();
    }


    displayContextBrick();
    paintContextBrick();
}

void CodingMatrixWidget::resetEncoding() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    paintContextBrick(Qt::white, Qt::white);
    contextBrick->reset();
    displayContextBrick();
    paintContextBrick();

    run_id=1;
    encodingReportTxEd->clear();
}

void CodingMatrixWidget::displayContextBrick() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    int highestNumberLength = 1;

    for(int i = 1; i < 8; i++) {
        if(pow(2, i) > byteMatrix->highestNumber) {
            highestNumberLength = i;
            break;
        }
    }

    locationCxBkLnEd->setText(QString("%1  %2").arg(contextBrick->content, highestNumberLength, 2, QLatin1Char('0')).arg(contextBrick->content));
    maskCxBkLnEd->setText(QString("%1  %2").arg(contextBrick->mask, highestNumberLength, 2, QLatin1Char('0')).arg(contextBrick->mask));
}

void CodingMatrixWidget::paintContextBrick(QColor contentColor, QColor maskColor) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    for(int row=0; row<byteMatrix->sideLength; row++) {
        for(int col=0; col<byteMatrix->sideLength; col++) {

            if(contextBrick->isMatch(((QTextEdit*) codingMatrixTable->cellWidget(row, col))->toPlainText().toInt())) {
                ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setPalette(QPalette(maskColor));
            }

            if(((QTextEdit*) codingMatrixTable->cellWidget(row, col))->toPlainText().toInt() == (int) contextBrick->content) {
                ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setPalette(QPalette(contentColor));
            }

        }
    }
}


