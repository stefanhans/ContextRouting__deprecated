#include "mainwindow.h"
#include <QApplication>

#define BRICKS_ADDITIONAL_SIZE 255

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
