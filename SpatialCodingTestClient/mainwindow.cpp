#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Palettes
    noColor = Qt::white;

    // QColor(red, green, blue, transparency)
    offerContentColor = QColor(0, 255, 255, 120);
    offerMaskColor = QColor(0, 255, 255, 50);
    offerMatchColor = QColor(0, 255, 255, 255);

    requestContentColor = QColor(255, 255, 0, 120);
    requestMaskColor = QColor(255, 255, 0, 50);
    requestMatchColor = QColor(255, 255, 0, 255);

    doubleMatchColor = QColor(0, 255, 0, 200);


    offerContentPalette.setColor(QPalette::Window, offerContentColor);
    offerMaskPalette.setColor(QPalette::Window, offerMaskColor);


    requestContentPalette.setColor(QPalette::Window, requestContentColor);
    requestMaskPalette.setColor(QPalette::Window, requestMaskColor);



    // Offer Content
    offerContentByteGroupBox = new QGroupBox(tr("Content Byte"));
    offerContentByteGroupBox->setAutoFillBackground(true);
    offerContentByteGroupBox->setPalette(offerContentPalette);

    offerContentByteHBoxLayout = new QHBoxLayout;

    offerContentByte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerContentByte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerContentByte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerContentByte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerContentByte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerContentByte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerContentByte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerContentByte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerContentByteBtn = new QPushButton(tr("Show"), this);

    offerContentByteHBoxLayout->addWidget(offerContentByte_7_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_6_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_5_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_4_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_3_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_2_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_1_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByte_0_CheckBox);
    offerContentByteHBoxLayout->addWidget(offerContentByteBtn);

    offerContentByteGroupBox->setLayout(offerContentByteHBoxLayout);

    connect(offerContentByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferContentByte()));

    // Offer Mask
    offerMaskByteGroupBox = new QGroupBox(tr("Mask Byte"));
    offerMaskByteGroupBox->setAutoFillBackground(true);
    offerMaskByteGroupBox->setPalette(offerMaskPalette);

    offerMaskByteHBoxLayout = new QHBoxLayout;
    offerMaskByte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    offerMaskByte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    offerMaskByte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    offerMaskByte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    offerMaskByte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    offerMaskByte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    offerMaskByte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    offerMaskByte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    offerMaskByteBtn = new QPushButton(tr("Show"), this);

    offerMaskByteHBoxLayout->addWidget(offerMaskByte_7_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_6_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_5_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_4_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_3_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_2_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_1_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByte_0_CheckBox);
    offerMaskByteHBoxLayout->addWidget(offerMaskByteBtn);

    offerMaskByteGroupBox->setLayout(offerMaskByteHBoxLayout);

    connect(offerMaskByteBtn, SIGNAL(clicked(bool)), this, SLOT(showOfferMaskByte()));


    // Offer Layout
    offerLayout = new QGridLayout;
    offerLayout->addWidget(offerContentByteGroupBox, 0, 0);
    offerLayout->addWidget(offerMaskByteGroupBox, 0, 1);

    // Request Content
    requestContentByteGroupBox = new QGroupBox(tr("Content Byte"));
    requestContentByteGroupBox->setAutoFillBackground(true);
    requestContentByteGroupBox->setPalette(requestContentPalette);

    requestContentByteHBoxLayout = new QHBoxLayout;
    requestContentByte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestContentByte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestContentByte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestContentByte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestContentByte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestContentByte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestContentByte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestContentByte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestContentByteBtn = new QPushButton(tr("Show"), this);

    requestContentByteHBoxLayout->addWidget(requestContentByte_7_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_6_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_5_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_4_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_3_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_2_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_1_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByte_0_CheckBox);
    requestContentByteHBoxLayout->addWidget(requestContentByteBtn);

    requestContentByteGroupBox->setLayout(requestContentByteHBoxLayout);

    connect(requestContentByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestContentByte()));


    // Request Mask
    requestMaskByteGroupBox = new QGroupBox(tr("Mask Byte"));
    requestMaskByteGroupBox->setAutoFillBackground(true);
    requestMaskByteGroupBox->setPalette(requestMaskPalette);

    requestMaskByteHBoxLayout = new QHBoxLayout;
    requestMaskByte_7_CheckBox = new QCheckBox(tr("Byte 7"));
    requestMaskByte_6_CheckBox = new QCheckBox(tr("Byte 6"));
    requestMaskByte_5_CheckBox = new QCheckBox(tr("Byte 5"));
    requestMaskByte_4_CheckBox = new QCheckBox(tr("Byte 4"));
    requestMaskByte_3_CheckBox = new QCheckBox(tr("Byte 3"));
    requestMaskByte_2_CheckBox = new QCheckBox(tr("Byte 2"));
    requestMaskByte_1_CheckBox = new QCheckBox(tr("Byte 1"));
    requestMaskByte_0_CheckBox = new QCheckBox(tr("Byte 0"));
    requestMaskByteBtn = new QPushButton(tr("Show"), this);

    requestMaskByteHBoxLayout->addWidget(requestMaskByte_7_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_6_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_5_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_4_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_3_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_2_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_1_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByte_0_CheckBox);
    requestMaskByteHBoxLayout->addWidget(requestMaskByteBtn);

    requestMaskByteGroupBox->setLayout(requestMaskByteHBoxLayout);

    connect(requestMaskByteBtn, SIGNAL(clicked(bool)), this, SLOT(showRequestMaskByte()));


    // Request Layout
    requestLayout = new QGridLayout;
    requestLayout->addWidget(requestContentByteGroupBox, 0, 0);
    requestLayout->addWidget(requestMaskByteGroupBox, 0, 1);


    // Spatial Layout
    spatialLayout = new QVBoxLayout;

    refreshSpatialBtn = new QPushButton(tr("Refresh"), this);
    spatialLayout->addWidget(refreshSpatialBtn, 0);

    connect(refreshSpatialBtn, SIGNAL(clicked(bool)), this, SLOT(refreshSpatial()));

    tableSideCount = 16;
    tableWidget = new QTableWidget(tableSideCount, tableSideCount, this);

    int cellSide = 40;
    tableWidget->setFixedHeight(17*cellSide);
    tableWidget->setFixedWidth(17*cellSide);

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        tableWidget->setColumnWidth(i, cellSide);
        tableWidget->setRowHeight(i, cellSide);

        for(int j=0; j<tableSideCount; j++) {

            tableWidget->setCellWidget(i, j, new QTextEdit);

            ((QTextEdit*) tableWidget->cellWidget(i, j))->setText(QString("%1").arg(n));
            ((QTextEdit*) tableWidget->cellWidget(i, j))->setEnabled(false);
            ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(QPalette(Qt::white));

            n++;
        }
    }

    spatialLayout->addWidget(tableWidget, 0, Qt::AlignHCenter);




    // Interaction Layout
    interactionLayout = new QGridLayout;


    // Main Layout
    mainLayout = new QVBoxLayout;

    // Offer
    offerGBox = new QGroupBox(tr("Offer"));
    offerGBox->setLayout(offerLayout);
    mainLayout->addWidget(offerGBox);

    // Request
    requestGBox = new QGroupBox(tr("Request"));
    requestGBox->setLayout(requestLayout);
    mainLayout->addWidget(requestGBox);

    // Spatial
    spatialGBox = new QGroupBox(tr("Spatial"));
    spatialGBox->setLayout(spatialLayout);
    mainLayout->addWidget(spatialGBox);

    mainLayout->addStretch();

    // Interaction
    interactionGBox = new QGroupBox(tr("Interaction"));
    interactionGBox->setLayout(interactionLayout);
    mainLayout->addWidget(interactionGBox);

    // GUI - Widget
    guiWidget = new QWidget;
    guiWidget->setLayout(mainLayout);

    // GUI - ScrollArea
    guiScrollArea = new QScrollArea;
    guiScrollArea->setWidget(guiWidget);
    guiScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    guiScrollArea->setWidgetResizable(true);

    setCentralWidget(guiScrollArea);
    showMaximized();
}

MainWindow::~MainWindow()
{

}


int MainWindow::offerContentToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerContent;

    offerContent = (int) offerContentByte_0_CheckBox->isChecked();
    offerContent += (int) offerContentByte_1_CheckBox->isChecked() * 2;
    offerContent += (int) offerContentByte_2_CheckBox->isChecked()   * 4;
    offerContent += (int) offerContentByte_3_CheckBox->isChecked()   * 8;
    offerContent += (int) offerContentByte_4_CheckBox->isChecked()  * 16;
    offerContent += (int) offerContentByte_5_CheckBox->isChecked()  * 32;
    offerContent += (int) offerContentByte_6_CheckBox->isChecked()  * 64;
    offerContent += (int) offerContentByte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerContent: " << offerContent;
    qDebug().noquote() << "offerContent: " << QString("%1").arg(offerContent, 8, 2, QLatin1Char('0'));

    return offerContent;
}

int MainWindow::offerMaskToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 offerMask;

    offerMask = (int) offerMaskByte_0_CheckBox->isChecked();
    offerMask += (int) offerMaskByte_1_CheckBox->isChecked() * 2;
    offerMask += (int) offerMaskByte_2_CheckBox->isChecked()   * 4;
    offerMask += (int) offerMaskByte_3_CheckBox->isChecked()   * 8;
    offerMask += (int) offerMaskByte_4_CheckBox->isChecked()  * 16;
    offerMask += (int) offerMaskByte_5_CheckBox->isChecked()  * 32;
    offerMask += (int) offerMaskByte_6_CheckBox->isChecked()  * 64;
    offerMask += (int) offerMaskByte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "offerMask: " << offerMask;
    qDebug().noquote() << "offerMask: " << QString("%1").arg(offerMask, 8, 2, QLatin1Char('0'));

    return offerMask;
}

int MainWindow::requestContentToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestContent;

    requestContent = (int) requestContentByte_0_CheckBox->isChecked();
    requestContent += (int) requestContentByte_1_CheckBox->isChecked() * 2;
    requestContent += (int) requestContentByte_2_CheckBox->isChecked()   * 4;
    requestContent += (int) requestContentByte_3_CheckBox->isChecked()   * 8;
    requestContent += (int) requestContentByte_4_CheckBox->isChecked()  * 16;
    requestContent += (int) requestContentByte_5_CheckBox->isChecked()  * 32;
    requestContent += (int) requestContentByte_6_CheckBox->isChecked()  * 64;
    requestContent += (int) requestContentByte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestContent: " << requestContent;
    qDebug().noquote() << "requestContent: " << QString("%1").arg(requestContent, 8, 2, QLatin1Char('0'));

    return requestContent;
}

int MainWindow::requestMaskToByte() {
    qDebug() << Q_FUNC_INFO;

    quint8 requestMask;

    requestMask = (int) requestMaskByte_0_CheckBox->isChecked();
    requestMask += (int) requestMaskByte_1_CheckBox->isChecked() * 2;
    requestMask += (int) requestMaskByte_2_CheckBox->isChecked()   * 4;
    requestMask += (int) requestMaskByte_3_CheckBox->isChecked()   * 8;
    requestMask += (int) requestMaskByte_4_CheckBox->isChecked()  * 16;
    requestMask += (int) requestMaskByte_5_CheckBox->isChecked()  * 32;
    requestMask += (int) requestMaskByte_6_CheckBox->isChecked()  * 64;
    requestMask += (int) requestMaskByte_7_CheckBox->isChecked() * 128;

    qDebug().noquote() << "requestMask: " << requestMask;
    qDebug().noquote() << "requestMask: " << QString("%1").arg(requestMask, 8, 2, QLatin1Char('0'));

    return requestMask;
}

void MainWindow::refreshSpatial() {
    qDebug() << Q_FUNC_INFO;

    // offerContent
    int offerContent = offerContentToByte();

    // offerMask
    int offerMask = offerMaskToByte();

    // requestContent
    int requestContent = requestContentToByte();

    // requestMask
    int requestMask = requestMaskToByte();


    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            qDebug().noquote() << "n: " << n << "i: " << i << "j: " << j;

            // Reset cell color
            ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);

            // Offer Mask
            if (n == offerMask) {
                if(requestMask == 0) {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
                }
                else {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(offerMaskColor);
                }
            }

            // Request Mask
            if (n == requestMask) {
                if(requestMask == 0) {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
                }
                else {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(requestMaskColor);
                }
            }

            // Offer Content
            if (n == offerContent) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(offerContentColor);
                qDebug().noquote() << "n: " << n << "offerContent: " << offerContent;
            }

            // Request Content
            if (n == requestContent) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(requestContentColor);
                qDebug().noquote() << "n: " << n << "requestContent: " << requestContent;
            }
            n++;
        }
    }

//    ((QTextEdit*) tableWidget->cellWidget(0, 0))->setPalette(offerMaskColor);
//    ((QTextEdit*) tableWidget->cellWidget(1, 1))->setPalette(offerContentColor);
//    ((QTextEdit*) tableWidget->cellWidget(2, 2))->setPalette(offerMatchColor);
//    ((QTextEdit*) tableWidget->cellWidget(3, 3))->setPalette(requestMaskColor);
//    ((QTextEdit*) tableWidget->cellWidget(4, 4))->setPalette(requestContentColor);
//    ((QTextEdit*) tableWidget->cellWidget(5, 5))->setPalette(requestMatchColor);

//    ((QTextEdit*) tableWidget->cellWidget(6, 6))->setPalette(doubleMatchColor);

}


void MainWindow::showOfferContentByte() {
    qDebug() << Q_FUNC_INFO;

    // offerContent
    int offerContent = offerContentToByte();

    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            qDebug().noquote() << "n: " << n << "i: " << i << "j: " << j;

            // Reset cell color of offerContent
            if (((QTextEdit*) tableWidget->cellWidget(i, j))->palette().color(QPalette::Window) == offerContentColor) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
            }



            // offer Content
            if (n == offerContent) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(offerContentColor);
                qDebug().noquote() << "n: " << n << "offerContent: " << offerContent;
            }

            n++;
        }
    }


}

void MainWindow::showOfferMaskByte() {
        qDebug() << Q_FUNC_INFO;

        // offerMask
        int offerMask = offerMaskToByte();


        int n=0;
        for(int i=0; i<tableSideCount; i++) {
            for(int j=0; j<tableSideCount; j++) {

                qDebug().noquote() << "n: " << n << "i: " << i << "j: " << j;

                // Reset cell color of offerMask
                if (((QTextEdit*) tableWidget->cellWidget(i, j))->palette().color(QPalette::Window) == offerMaskColor) {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
                }

                // Offer Mask
                if (n == offerMask) {
                    if(offerMask == 0) {
                        ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
                    }
                    else {
                        ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(offerMaskColor);
                    }
                }

                n++;
            }
        }

}

void MainWindow::showRequestContentByte() {
    qDebug() << Q_FUNC_INFO;

    // requestContent
    int requestContent = requestContentToByte();


    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            qDebug().noquote() << "n: " << n << "i: " << i << "j: " << j;

            // Reset cell color of requestContent
            if (((QTextEdit*) tableWidget->cellWidget(i, j))->palette().color(QPalette::Window) == requestContentColor) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
            }

            // Request Content
            if (n == requestContent) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(requestContentColor);
                qDebug().noquote() << "n: " << n << "requestContent: " << requestContent;
            }

            n++;
        }
    }


}

void MainWindow::showRequestMaskByte() {
    qDebug() << Q_FUNC_INFO;

    // requestMask
    int requestMask = requestMaskToByte();


    int n=0;
    for(int i=0; i<tableSideCount; i++) {
        for(int j=0; j<tableSideCount; j++) {

            qDebug().noquote() << "n: " << n << "i: " << i << "j: " << j;

            // Reset cell color of requestMask
            if (((QTextEdit*) tableWidget->cellWidget(i, j))->palette().color(QPalette::Window) == requestMaskColor) {
                ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
            }

            // Request Mask
            if (n == requestMask) {
                if(requestMask == 0) {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(noColor);
                }
                else {
                    ((QTextEdit*) tableWidget->cellWidget(i, j))->setPalette(requestMaskColor);
                }
            }

            n++;
        }
    }


}
