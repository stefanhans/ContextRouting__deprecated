#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bitmatrixmodel.h"
#include "matrixtesttablewidget.h"


#include <QMainWindow>

#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QScrollArea>

#include <QTableView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();



//    BitMatrixModel *bitMatrixModel;
//    QTableView *bitMatrixTableView;



    // Matrix
    int matrixSideCount;

    int matrix_min_x, matrix_min_y, matrix_max_x, matrix_max_y;
    int min_x, min_y, max_x, max_y;

    int tmp_matrix_min_x, tmp_matrix_min_y, tmp_matrix_max_x, tmp_matrix_max_y;

    bool stop, repaint;
    int run_id;


    QWidget *guiWidget;
    QScrollArea *guiScrollArea;

    QVBoxLayout *mainLayout;

    // SpatialTest
    QGroupBox *spatialTestGBox;
    QGridLayout *spatiaTestGridLayout;

    // SpatialTest Table
    QHBoxLayout *spatialTestTableLayout;
    QTableWidget *tableTestWidget;
    int tableTestWidgetFixedSide;
    int tableTestWidgetFixedMargin;
    int cellSide;

    // SpatialTest Config
    QGroupBox *spatialTestConfigGBox;
    QGridLayout *spatialTestConfigLayout;

    QLabel *sideLengthConfigLabel;
    QSpinBox *sideLengthConfigSpinBox;

    QLabel *repaintConfigLabel;
    QCheckBox *repaintConfigCheckBox;

    QLabel *permutationFiguresConfigLabel;
    QComboBox *permutationFiguresConfigComboBox;

    QLabel *testResultLabel;
    QPlainTextEdit *testResultTextEdit;

    QGroupBox *testButtonGBox;
    QGridLayout *testButtonLayout;

    // FullTest Buttons
    QPushButton *startSpatialFullTest_Btn;
    QPushButton *nextSpatialFullTest_Btn;
    QPushButton *resetSpatialFullTest_Btn;

    // SpatialSingleTest Buttons
    QPushButton *startSpatialSingleTest_Btn;
    QPushButton *nextSpatialSingleTest_Btn;
    QPushButton *resetSpatialSingleTest_Btn;

    // TEST matrixtesttablewidget
    QGroupBox *matrixTestTableGBox;
    QVBoxLayout *matrixTestTableLayout;
    MatrixTestTableWidget *matrixTestTableWidget;

public slots:

    void startSpatialFullTest();
    void resetSpatialFullTest();
    void resetSpatialFullTest(int);
    void nextSpatialSingleTest();

    void startSpatialSingleTest();
    void nextSpatialSingleTestStep();
    void resetSpatialSingleTest();

    void changeSideLength(int);
    void setRepainted(int);

private:

    void clearTestMatrix();
    void drawTestMatrix();

};

#endif // MAINWINDOW_H
