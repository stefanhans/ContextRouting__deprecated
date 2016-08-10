#include "MainWindow.h"
#include "ui_MainWindow.h"

//CONSTURCTOR
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}
//my stuff now starting
