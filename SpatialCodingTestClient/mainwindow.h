#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QScrollArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *guiWidget;
    QScrollArea *guiScrollArea;

    QVBoxLayout *mainLayout;

    // Colors & Palettes
    QColor noColor;

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


    // Offer
    QGroupBox *offerGBox;
    QGridLayout *offerLayout;

    QGroupBox *offerContentByteGroupBox;
    QHBoxLayout *offerContentByteHBoxLayout;
    QCheckBox *offerContentByte_7_CheckBox;
    QCheckBox *offerContentByte_6_CheckBox;
    QCheckBox *offerContentByte_5_CheckBox;
    QCheckBox *offerContentByte_4_CheckBox;
    QCheckBox *offerContentByte_3_CheckBox;
    QCheckBox *offerContentByte_2_CheckBox;
    QCheckBox *offerContentByte_1_CheckBox;
    QCheckBox *offerContentByte_0_CheckBox;
    QPushButton *offerContentByteBtn;

    QGroupBox *offerMaskByteGroupBox;
    QHBoxLayout *offerMaskByteHBoxLayout;
    QCheckBox *offerMaskByte_7_CheckBox;
    QCheckBox *offerMaskByte_6_CheckBox;
    QCheckBox *offerMaskByte_5_CheckBox;
    QCheckBox *offerMaskByte_4_CheckBox;
    QCheckBox *offerMaskByte_3_CheckBox;
    QCheckBox *offerMaskByte_2_CheckBox;
    QCheckBox *offerMaskByte_1_CheckBox;
    QCheckBox *offerMaskByte_0_CheckBox;
    QPushButton *offerMaskByteBtn;

    // Request
    QGroupBox *requestGBox;
    QGridLayout *requestLayout;

    QGroupBox *requestContentByteGroupBox;
    QHBoxLayout *requestContentByteHBoxLayout;
    QCheckBox *requestContentByte_7_CheckBox;
    QCheckBox *requestContentByte_6_CheckBox;
    QCheckBox *requestContentByte_5_CheckBox;
    QCheckBox *requestContentByte_4_CheckBox;
    QCheckBox *requestContentByte_3_CheckBox;
    QCheckBox *requestContentByte_2_CheckBox;
    QCheckBox *requestContentByte_1_CheckBox;
    QCheckBox *requestContentByte_0_CheckBox;
    QPushButton *requestContentByteBtn;

    QGroupBox *requestMaskByteGroupBox;
    QHBoxLayout *requestMaskByteHBoxLayout;
    QCheckBox *requestMaskByte_7_CheckBox;
    QCheckBox *requestMaskByte_6_CheckBox;
    QCheckBox *requestMaskByte_5_CheckBox;
    QCheckBox *requestMaskByte_4_CheckBox;
    QCheckBox *requestMaskByte_3_CheckBox;
    QCheckBox *requestMaskByte_2_CheckBox;
    QCheckBox *requestMaskByte_1_CheckBox;
    QCheckBox *requestMaskByte_0_CheckBox;
    QPushButton *requestMaskByteBtn;


    // Spatial
    QGroupBox *spatialGBox;
    QVBoxLayout *spatialLayout;

    QPushButton *refreshSpatialBtn;

    QTableWidget *tableWidget;

    int tableSideCount;

    // Interaction
    QGroupBox *interactionGBox;
    QGridLayout *interactionLayout;

public slots:

    void showOfferContentByte();
    void showOfferMaskByte();
    void showRequestContentByte();
    void showRequestMaskByte();
    void refreshSpatial();

private:

    int offerContentToByte();
    int offerMaskToByte();
    int requestContentToByte();
    int requestMaskToByte();
};

#endif // MAINWINDOW_H
