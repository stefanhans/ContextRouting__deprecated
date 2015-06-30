#include "mainwindow.h"

#include "abstractwidget.h"
#include "codingwidget.h"
#include "offerwidget.h"
#include "requestwidget.h"
#include "dictionarywidget.h"

#include <QDebug>
#include <QMdiSubWindow>

class CodingWidget;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Filessystem
    filesystemTree = new QTreeView();

    model.setRootPath(PROTO_DIR);
    model.setReadOnly(true);

    QStringList filters;
    filters << FILTER;
    model.setNameFilters(filters);
    model.setNameFilterDisables(false);

    model.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

    filesystemTree->setModel(&model);
    filesystemTree->setRootIndex(model.index(PROTO_DIR));
    filesystemTree->setAnimated(false);

    filesystemTree->setIndentation(20);
    filesystemTree->setSortingEnabled(true);
    filesystemTree->setHeaderHidden(true);
    filesystemTree->hideColumn(1);
    filesystemTree->hideColumn(2);
    filesystemTree->hideColumn(3);
    filesystemTree->adjustSize(); // ? not working
    filesystemTree->expandAll(); // ? not working

    filesystemLayout = new QVBoxLayout;
    filesystemLayout->addWidget(filesystemTree);

    filesystemWidget = new QWidget;
    filesystemWidget->setLayout(filesystemLayout);

    filesystemScrollArea = new QScrollArea;
    filesystemScrollArea->setWidget(filesystemWidget);

    mdiArea = new QMdiArea;
    mdiArea->setViewMode(QMdiArea::TabbedView);

    mainSplitter = new QSplitter(Qt::Horizontal);

    QList<int> sizes;
    sizes SPLITTER_SIZES;
    mainSplitter->setSizes(sizes);

    mainSplitter->addWidget(filesystemWidget);
    mainSplitter->addWidget(mdiArea);

    setCentralWidget(mainSplitter);
    showMaximized();

    connect(filesystemTree,  SIGNAL(doubleClicked(const QModelIndex& )), this, SLOT(openFile(const QModelIndex&)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile(const QModelIndex& index) {

    qDebug() << "MainWindow::openFile(" << model.filePath(index) << ")";

    foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
        AbstractWidget *mdiChild = qobject_cast<AbstractWidget *>(window->widget());

        if (mdiChild->parentWidget()->windowTitle() == model.fileName(index)) {
            mdiChild->setFocus();
            return;
        }
    }

    QMdiSubWindow *mdiSubWindow = new QMdiSubWindow;
    mdiSubWindow->setWindowTitle(model.fileName(index));
    mdiSubWindow->setObjectName(model.filePath(index));
    mdiSubWindow->setAttribute(Qt::WA_DeleteOnClose);


    AbstractWidget *contextWidget;

    // DICT
    if(model.fileInfo(index).suffix() == "dict") {
        contextWidget = new DictionaryWidget();

    }

    // COD
    if(model.fileInfo(index).suffix() == "cod") {
       contextWidget = new CodingWidget;
    }

    // COF
    if(model.fileInfo(index).suffix() == "cof") {
       contextWidget = new OfferWidget;
    }

    // CRQ
    if(model.fileInfo(index).suffix() == "crq") {
       contextWidget = new RequestWidget;
    }

    if (contextWidget->loadFile(model.filePath(index))) {

        contextWidget->loadGuiInteraction();

        mdiSubWindow->setWidget(contextWidget);

        mdiArea->addSubWindow(mdiSubWindow);
        mdiSubWindow->showMinimized();
        mdiSubWindow->showMaximized();
    }
}
