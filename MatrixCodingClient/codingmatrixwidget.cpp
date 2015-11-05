#include "codingmatrixwidget.h"

#define DEBUG 1

#include <QDebug>
#include <QTextEdit>
#include <QTableWidget>

CodingMatrixWidget::CodingMatrixWidget(QWidget *parent)
    : QGroupBox(parent)
{
    codingMatrixLayout = new QVBoxLayout;
    setLayout(codingMatrixLayout);

    codingMatrixTable = new QTableWidget;

    codingMatrixTable->setRowCount(4);
    codingMatrixTable->setColumnCount(4);

    matrixSideCount = 4;
    matrix_min_x = 0;
    matrix_min_y = 0;
    matrix_max_x = matrixSideCount-1;
    matrix_max_y = matrixSideCount-1;

    min_x = min_y = max_x =  max_y = 0;
    tmp_matrix_min_x = tmp_matrix_min_y = tmp_matrix_max_x = tmp_matrix_max_y = -1;

    run_id = 1;


    tableTestWidgetFixedSide = 500;
    tableTestWidgetFixedMargin = 28;

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

}
