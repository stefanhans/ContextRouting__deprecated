#ifndef CODINGMATRIXWIDGET_H
#define CODINGMATRIXWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableWidget>

class CodingMatrixWidget : public QGroupBox
{
    Q_OBJECT

public:
    CodingMatrixWidget(QWidget *parent = 0);


    QVBoxLayout *codingMatrixLayout;
    QTableWidget *codingMatrixTable;


    int tableTestWidgetFixedSide;
    int tableTestWidgetFixedMargin;
    int cellSide;

    int matrixSideCount;

    int matrix_min_x, matrix_min_y, matrix_max_x, matrix_max_y;
    int min_x, min_y, max_x, max_y;

    int tmp_matrix_min_x, tmp_matrix_min_y, tmp_matrix_max_x, tmp_matrix_max_y;

    bool stop, repaint;
    int run_id;

    void clearTestMatrix();
    void drawTestMatrix();
};

#endif // CODINGMATRIXWIDGET_H

