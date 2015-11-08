#ifndef CODINGMATRIXWIDGET_H
#define CODINGMATRIXWIDGET_H

#include "globals.h"
#include "bytematrix.h"
#include "contextbrick.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QFile>
#include <QVector>
#include <QPair>

class CodingMatrixWidget : public QGroupBox
{
    Q_OBJECT

public:
    CodingMatrixWidget(QWidget *parent = 0);


    int tableTestWidgetFixedSide;
    int tableTestWidgetFixedMargin;
    int cellSide;

    int matrixSideCount;

    int matrix_min_x, matrix_min_y, matrix_max_x, matrix_max_y;
    int min_x, min_y, max_x, max_y;

    int tmp_matrix_min_x, tmp_matrix_min_y, tmp_matrix_max_x, tmp_matrix_max_y;

    bool stop, repaint;
    int run_id;

    // Main Layout
    QVBoxLayout *codingMatrixLayout;


    // Header Layout
    QGridLayout *headerLayout;

    QLabel *locationCxBkLbl;
    QLineEdit *locationCxBkLnEd;

    QLabel *maskCxBkLbl;
    QLineEdit *maskCxBkLnEd;

    QLabel *repaintProgressLbl;
    QCheckBox *repaintProgressCkBx;

    QPushButton *loadCodingMatrixBtn;


    // Table
    QTableWidget *codingMatrixTable;


    // Button Layout
    QGridLayout *buttonLayout;

    QPushButton *startEncodingBtn;
    QPushButton *nextEncodingStepBtn;
    QPushButton *resetEncodingBtn;

    // Report
    QPlainTextEdit *encodingReportTxEd;


    void clearTestMatrix();
    void drawTestMatrix();

    ByteMatrix *byteMatrix;

    ContextBrick *contextBrick;


public slots:

    void loadCodingMatrix();
    void startEncoding();
    void nextEncodingStep();
    void resetEncoding();

private:

    void displayContextBrick();

    void paintContextBrick(QColor contentColor = Qt::gray, QColor maskColor = Qt::lightGray);
};

#endif // CODINGMATRIXWIDGET_H

