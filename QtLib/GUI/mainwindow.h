#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cip_global.h"
#include "cip.h"

#include <QMainWindow>

#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QScrollArea>
#include <QNetworkSession>
#include <QUuid>

#include <QtNetwork>

#include "uuid/uuid.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

    void createCIP();

private:

    CIP *currentCIP;

    QWidget *guiWidget;
    QScrollArea *guiScrollArea;


    QVBoxLayout *mainLayout;

    // Factory
    QGroupBox *factoryGBox;
    QGridLayout *factoryLayout;

    QLabel *factoryServiceLbl;
    QComboBox *factoryServiceCmbBx;
    QPushButton *createBtn;



    // Files
    QGroupBox *filesGBox;
    QGridLayout *filesLayout;

    QPushButton *openBtn;
    QPushButton *saveBtn;


    // Header
    QGroupBox *headerGBox;
    QGridLayout *headerLayout;

    QLabel *requestLbl;
    QTextEdit *requestTxtEdt;

    // Context
    QGroupBox *contextGBox;
    QGridLayout *contextLayout;

    // Data
    QGridLayout *dataLayout;
    QGroupBox *dataGBox;

    // Raw CIP
    QGridLayout *rawCIPLayout;
    QGroupBox *rawCIPGBox;
    QTextEdit *rawCIPTxtEdt;


    // GuiInteraction
    QVBoxLayout *interactionLayout;
    QGroupBox *interactionGBox;

};

#endif // MAINWINDOW_H
