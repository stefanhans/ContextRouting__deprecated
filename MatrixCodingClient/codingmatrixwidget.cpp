#include "codingmatrixwidget.h"

#include <QDebug>
#include <QTextEdit>
#include <QTableWidget>
#include <QSpacerItem>
#include <QFileDialog>

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
    nextEncodingStepBtn = new QPushButton(tr("Next Encoding Step"));
    resetEncodingBtn = new QPushButton(tr("Reset Encoding"));

    // Report
    encodingReportTxEd = new QTextEdit;
    encodingReportTxEd->setFixedHeight(200);

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

    if (file.open(QFile::ReadOnly)) {

        int row = 0;
        QString line = file.readLine(200);
        QStringList list;

        while (file.canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){

                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setText(QString("%1").arg(list.at(col)));
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setFont(QFont("Times", 8, QFont::Bold));
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setAutoFillBackground(true);
                    ((QTextEdit*) codingMatrixTable->cellWidget(row, col))->setPalette(QPalette(Qt::white));

                    byteMatrix->matrix[row][col] = list.at(col).toInt();
                }
                ++row;
                ++byteMatrix->sideLength;

                line = file.readLine(200);
            }
        }
    }

    file.close();
    setTitle(fileName.section('/', -1));

    locationCxBkLnEd->setReadOnly(false);
    locationCxBkLnEd->setText(QString("%1  %2").arg(contextBrick->content, 8, 2, QLatin1Char('0')).arg(contextBrick->content));
    locationCxBkLnEd->setReadOnly(true);


    maskCxBkLnEd->setReadOnly(false);
    maskCxBkLnEd->setText(QString("%1  %2").arg(contextBrick->mask, 8, 2, QLatin1Char('0')).arg(contextBrick->mask));
    maskCxBkLnEd->setReadOnly(true);

    ((QTextEdit*) codingMatrixTable->cellWidget(0, 0))->setPalette(QPalette(Qt::gray));

    byteMatrix->printMatrix();
}

