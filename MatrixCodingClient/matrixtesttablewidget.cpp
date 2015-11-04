#include "matrixtesttablewidget.h"

#define DEBUG 1

#include <QDebug>
#include <QTextEdit>

MatrixTestTableWidget::MatrixTestTableWidget(QWidget *parent)
    :QTableWidget(parent)
{


}

MatrixTestTableWidget::MatrixTestTableWidget(int rows, int columns, QWidget *parent)
    :QTableWidget(parent)
{
    setParent(parent);
    setRowCount(rows);
    setColumnCount(columns);

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
    setFixedHeight(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);
    setFixedWidth(tableTestWidgetFixedSide+tableTestWidgetFixedMargin);

    for(int i=0; i<matrixSideCount; i++) {
        setColumnWidth(i, cellSide);
        setRowHeight(i, cellSide);

        for(int j=0; j<matrixSideCount; j++) {

            setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) cellWidget(i, j))->setPalette(QPalette(Qt::white));

        }
    }
}

/*
 *
 * drawTestMatrix()
 *
 */
void MatrixTestTableWidget::drawTestMatrix() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

//    clearTestMatrix();

    for(int x=min_x; x<=max_x; x++) {
        for(int y=min_y; y<=max_y; y++) {
            ((QTextEdit*) cellWidget(y, x))->setPalette(QPalette(Qt::red));
        }
    }

//    if(repaint) {
//        ((QTableWidget*)tableTestWidget)->repaint();
//    }
}
