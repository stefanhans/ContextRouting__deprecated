#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

    // Colors & Palettes
    QColor noColor;
    QColor redColor;

    QColor offerContentColor;
    QPalette offerContentPalette;

    QColor offerMaskColor;
    QPalette offerMaskPalette;

    QColor requestContentColor;
    QPalette requestContentPalette;

    QColor requestMaskColor;
    QPalette requestMaskPalette;

    QColor offerMatchColor;
    QPalette offerMatchPalette;

    QColor requestMatchColor;
    QPalette requestMatchPalette;

    QColor doubleMatchColor;
    QPalette doubleMatchPalette;

    QColor directMatchColor;
    QColor indirectMatchColor;

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

    // FullTest Buttons
    QPushButton *startSpatialFullTest_Btn;
    QPushButton *nextSpatialFullTest_Btn;
    QPushButton *resetSpatialFullTest_Btn;


    // SpatialSingleTest Buttons
    QPushButton *startSpatialSingleTest_Btn;
    QPushButton *nextSpatialSingleTest_Btn;
    QPushButton *resetSpatialSingleTest_Btn;

    // Test Coding Matrices
    QGroupBox *testCodingMatricesGroupBox;
    QVBoxLayout *testCodingMatricesLayout;

    // Test Coding Matrices Header
    QGroupBox *testCodingMatricesHeaderGroupBox;
    QHBoxLayout *testCodingMatricesHeaderLayout;

    // Test Coding Matrices Tables
    QGroupBox *testCodingMatricesTablesGroupBox;
    QGridLayout *testCodingMatricesTablesLayout;

    // Table_1
    QGroupBox *testCodingMatricesTableGroupBox_1;
    QVBoxLayout *testCodingMatricesTableLayout_1;
    QTableWidget *testCodingMatricesTableWidget_1;
    QPushButton *testCodingMatricesFile_Btn_1;

    // Table_2
    QGroupBox *testCodingMatricesTableGroupBox_2;
    QVBoxLayout *testCodingMatricesTableLayout_2;
    QTableWidget *testCodingMatricesTableWidget_2;
    QPushButton *testCodingMatricesFile_Btn_2;

    // Table_3
    QGroupBox *testCodingMatricesTableGroupBox_3;
    QVBoxLayout *testCodingMatricesTableLayout_3;
    QTableWidget *testCodingMatricesTableWidget_3;
    QPushButton *testCodingMatricesFile_Btn_3;

    // Table_4
    QGroupBox *testCodingMatricesTableGroupBox_4;
    QVBoxLayout *testCodingMatricesTableLayout_4;
    QTableWidget *testCodingMatricesTableWidget_4;
    QPushButton *testCodingMatricesFile_Btn_4;

    // Offer
    QGroupBox *offerGBox;
    QGridLayout *offerLayout;

    // Request
    QGroupBox *requestGBox;
    QGridLayout *requestLayout;

    // offerContent_1
    QGroupBox *offerContent_1_ByteGroupBox;
    QHBoxLayout *offerContent_1_ByteHBoxLayout;
    QCheckBox *offerContent_1_Byte_7_CheckBox;
    QCheckBox *offerContent_1_Byte_6_CheckBox;
    QCheckBox *offerContent_1_Byte_5_CheckBox;
    QCheckBox *offerContent_1_Byte_4_CheckBox;
    QCheckBox *offerContent_1_Byte_3_CheckBox;
    QCheckBox *offerContent_1_Byte_2_CheckBox;
    QCheckBox *offerContent_1_Byte_1_CheckBox;
    QCheckBox *offerContent_1_Byte_0_CheckBox;
    QPushButton *offerContent_1_ByteBtn;

    // offerMask_1
    QGroupBox *offerMask_1_ByteGroupBox;
    QHBoxLayout *offerMask_1_ByteHBoxLayout;
    QCheckBox *offerMask_1_Byte_7_CheckBox;
    QCheckBox *offerMask_1_Byte_6_CheckBox;
    QCheckBox *offerMask_1_Byte_5_CheckBox;
    QCheckBox *offerMask_1_Byte_4_CheckBox;
    QCheckBox *offerMask_1_Byte_3_CheckBox;
    QCheckBox *offerMask_1_Byte_2_CheckBox;
    QCheckBox *offerMask_1_Byte_1_CheckBox;
    QCheckBox *offerMask_1_Byte_0_CheckBox;
    QPushButton *offerMask_1_ByteBtn;

    // requestContent_1
    QGroupBox *requestContent_1_ByteGroupBox;
    QHBoxLayout *requestContent_1_ByteHBoxLayout;
    QCheckBox *requestContent_1_Byte_7_CheckBox;
    QCheckBox *requestContent_1_Byte_6_CheckBox;
    QCheckBox *requestContent_1_Byte_5_CheckBox;
    QCheckBox *requestContent_1_Byte_4_CheckBox;
    QCheckBox *requestContent_1_Byte_3_CheckBox;
    QCheckBox *requestContent_1_Byte_2_CheckBox;
    QCheckBox *requestContent_1_Byte_1_CheckBox;
    QCheckBox *requestContent_1_Byte_0_CheckBox;
    QPushButton *requestContent_1_ByteBtn;

    // requestMask_1
    QGroupBox *requestMask_1_ByteGroupBox;
    QHBoxLayout *requestMask_1_ByteHBoxLayout;
    QCheckBox *requestMask_1_Byte_7_CheckBox;
    QCheckBox *requestMask_1_Byte_6_CheckBox;
    QCheckBox *requestMask_1_Byte_5_CheckBox;
    QCheckBox *requestMask_1_Byte_4_CheckBox;
    QCheckBox *requestMask_1_Byte_3_CheckBox;
    QCheckBox *requestMask_1_Byte_2_CheckBox;
    QCheckBox *requestMask_1_Byte_1_CheckBox;
    QCheckBox *requestMask_1_Byte_0_CheckBox;
    QPushButton *requestMask_1_ByteBtn;

    // offerContent_2
    QGroupBox *offerContent_2_ByteGroupBox;
    QHBoxLayout *offerContent_2_ByteHBoxLayout;
    QCheckBox *offerContent_2_Byte_7_CheckBox;
    QCheckBox *offerContent_2_Byte_6_CheckBox;
    QCheckBox *offerContent_2_Byte_5_CheckBox;
    QCheckBox *offerContent_2_Byte_4_CheckBox;
    QCheckBox *offerContent_2_Byte_3_CheckBox;
    QCheckBox *offerContent_2_Byte_2_CheckBox;
    QCheckBox *offerContent_2_Byte_1_CheckBox;
    QCheckBox *offerContent_2_Byte_0_CheckBox;
    QPushButton *offerContent_2_ByteBtn;

    // offerMask_2
    QGroupBox *offerMask_2_ByteGroupBox;
    QHBoxLayout *offerMask_2_ByteHBoxLayout;
    QCheckBox *offerMask_2_Byte_7_CheckBox;
    QCheckBox *offerMask_2_Byte_6_CheckBox;
    QCheckBox *offerMask_2_Byte_5_CheckBox;
    QCheckBox *offerMask_2_Byte_4_CheckBox;
    QCheckBox *offerMask_2_Byte_3_CheckBox;
    QCheckBox *offerMask_2_Byte_2_CheckBox;
    QCheckBox *offerMask_2_Byte_1_CheckBox;
    QCheckBox *offerMask_2_Byte_0_CheckBox;
    QPushButton *offerMask_2_ByteBtn;

    // requestContent_2
    QGroupBox *requestContent_2_ByteGroupBox;
    QHBoxLayout *requestContent_2_ByteHBoxLayout;
    QCheckBox *requestContent_2_Byte_7_CheckBox;
    QCheckBox *requestContent_2_Byte_6_CheckBox;
    QCheckBox *requestContent_2_Byte_5_CheckBox;
    QCheckBox *requestContent_2_Byte_4_CheckBox;
    QCheckBox *requestContent_2_Byte_3_CheckBox;
    QCheckBox *requestContent_2_Byte_2_CheckBox;
    QCheckBox *requestContent_2_Byte_1_CheckBox;
    QCheckBox *requestContent_2_Byte_0_CheckBox;
    QPushButton *requestContent_2_ByteBtn;

    // requestMask_2
    QGroupBox *requestMask_2_ByteGroupBox;
    QHBoxLayout *requestMask_2_ByteHBoxLayout;
    QCheckBox *requestMask_2_Byte_7_CheckBox;
    QCheckBox *requestMask_2_Byte_6_CheckBox;
    QCheckBox *requestMask_2_Byte_5_CheckBox;
    QCheckBox *requestMask_2_Byte_4_CheckBox;
    QCheckBox *requestMask_2_Byte_3_CheckBox;
    QCheckBox *requestMask_2_Byte_2_CheckBox;
    QCheckBox *requestMask_2_Byte_1_CheckBox;
    QCheckBox *requestMask_2_Byte_0_CheckBox;
    QPushButton *requestMask_2_ByteBtn;

    // Spatial
    QGroupBox *spatialGBox;
    QGridLayout *spatialLayout;

    QPushButton *clearSpatial_1_Btn;
    QPushButton *refreshSpatial_1_Btn;

    QPushButton *clearSpatial_2_Btn;
    QPushButton *refreshSpatial_2_Btn;

    QPushButton *clearSpatialAll_Btn;
    QPushButton *refreshSpatialAll_Btn;

    QHBoxLayout *spatialTableLayout;
    QTableWidget *tableWidget_1;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidgetAll;

    // Interaction
    QGroupBox *interactionGBox;
    QGridLayout *interactionLayout;

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

    void testCodingMatricesFileLoad_1();
    void testCodingMatricesFileLoad_2();
    void testCodingMatricesFileLoad_3();
    void testCodingMatricesFileLoad_4();

    void showOfferContent_1_Byte();
    void showOfferMask_1_Byte();
    void showRequestContent_1_Byte();
    void showRequestMask_1_Byte();

    void refreshSpatial_1();
    void clearSpatial_1();

    void showOfferContent_2_Byte();
    void showOfferMask_2_Byte();
    void showRequestContent_2_Byte();
    void showRequestMask_2_Byte();

    void refreshSpatial_2();
    void clearSpatial_2();

    void refreshSpatialAll();
    void clearSpatialAll();

private:

    void clearTestMatrix();
    void drawTestMatrix();

    int offerContent_1_ToByte();
    int offerMask_1_ToByte();
    int requestContent_1_ToByte();
    int requestMask_1_ToByte();

    void clearOfferContent_1();
    void clearOfferMask_1();
    void clearRequestContent_1();
    void clearRequestMask_1();

    int offerContent_2_ToByte();
    int offerMask_2_ToByte();
    int requestContent_2_ToByte();
    int requestMask_2_ToByte();

    void clearOfferContent_2();
    void clearOfferMask_2();
    void clearRequestContent_2();
    void clearRequestMask_2();
};

#endif // MAINWINDOW_H
