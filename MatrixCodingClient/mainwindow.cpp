#include "mainwindow.h"
#include "bitmatrixmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    bitMatrixModel = new BitMatrixModel(this);
    bitMatrixTableView = new QTableView;
    bitMatrixTableView->setModel(bitMatrixModel);
}

MainWindow::~MainWindow()
{

}
