#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bitmatrixmodel.h"

#include <QMainWindow>
#include <QTableView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();



    BitMatrixModel *bitMatrixModel;
    QTableView *bitMatrixTableView;

};

#endif // MAINWINDOW_H
