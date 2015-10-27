#include "bytematrix.h"


#include <iostream>

#define DEBUG 1

#include <QStringList>
#include <QDebug>


ByteMatrix::ByteMatrix():
    matrix(),
    sideLength(0),

//    min_x(0),
//    min_y(0),
//    max_x(0),
//    max_y(0),

    dataFile(){
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;
}


void ByteMatrix::loadDataFile(QFile* dataFile) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    if (dataFile->open(QFile::ReadOnly)) {

        int row = 0;
        QString line = dataFile->readLine(200);
        QStringList list;

        while (dataFile->canReadLine()) {
            if (!line.startsWith("#") && line.contains(",")) {
                qDebug().noquote() << line.trimmed();
                list= line.simplified().split(",");
                for (int col = 0; col < list.length(); ++col){
                    matrix[row][col] = list.at(col).toInt();
                }
                ++row;

                line = dataFile->readLine(200);
            }
        }
    }
    dataFile->close();

    printMatrix();

}


// Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
ContextBrick* ByteMatrix::getFirstMatch(int min_x, int min_y, int max_x, int max_y)  {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    ContextBrick* matchingContextBrick = new ContextBrick;

    matchingContextBrick->content = min_x;
    matchingContextBrick->mask = max_x;

    matchingContextBrick->printContextBrick();

    return matchingContextBrick;
}

// Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
ContextBrick* ByteMatrix::getSmallestSuperset(int min_x, int min_y, int max_x, int max_y) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    ContextBrick* supersetContextBrick = new ContextBrick;

    return supersetContextBrick;

}


void ByteMatrix::printMatrix() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    QString matrixOut;
    for (int row = 0; row < sideLength; ++row){
        for (int col = 0; col < sideLength; ++col){
            if(col < sideLength-1) {

                matrixOut.append(QString("%1, ").arg(matrix[row][col]));
            }
            else {
                matrixOut.append(QString("%1\n").arg(matrix[row][col]));
            }
        }

    }
    qDebug().noquote() << matrixOut;
}
