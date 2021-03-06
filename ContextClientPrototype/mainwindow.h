#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include "offerwidget.h"
#include "requestwidget.h"
#include "codingwidget.h"
#include "dictionarywidget.h"

#include <QMainWindow>
#include <QSplitter>
#include <QTreeView>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QLayout>
#include <QMdiArea>

#define FILTER "*.cod" << "*.dict" << "*.xml" << "*.cof" << "*.crq" << ".can" << "*.ctxt"
#define SPLITTER_SIZES << 250 << 750

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile(const QModelIndex &index);

private:
    QSplitter *mainSplitter;

    QTreeView *filesystemTree;
    QFileSystemModel model;

    QWidget *filesystemWidget;
    QScrollArea *filesystemScrollArea;
    QVBoxLayout *filesystemLayout;

    QMdiArea *mdiArea;
};

#endif // MAINWINDOW_H
