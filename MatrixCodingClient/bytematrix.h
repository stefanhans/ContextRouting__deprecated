#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include "globals.h"
#include "contextbrick.h"

#include <QFile>
#include <QtGlobal>
#include <QDebug>
#include <QtMath>


//typedef unsigned char byte_t;


class ByteMatrix
{
public:
    ByteMatrix():
        matrix(),
        sideLength(0),
        dataFile(){}

    int matrix[16][16];

    int sideLength;

    QFile *dataFile;

    inline bool isMatch(int x, int y, int content, int mask) {

        byte_t in_content = matrix[x][y];

        qDebug() << QString("isMatch matrix[%1][%2]: %3").arg(x).arg(y).arg(matrix[x][y]);

        if ((in_content ^ content) == 0) {
            return true;
        }

        if (~(~(in_content ^ content) | mask) != 0) {
            return false;
        }

        return true;

    }

    inline bool isMatch(int min_x, int min_y, int max_x, int max_y, int content, int mask) {

        qDebug() << QString("isMatch matrix[%1,%2][%3,%4]").arg(min_x).arg(min_y).arg(max_x).arg(max_y);

        for(int y = min_y; y <= max_y; y++) {
            qDebug() << QString("outer loop y: %1").arg(y);
            for(int x = min_x; x <= max_x; x++) {
                qDebug() << QString("inner loop x: %1").arg(x);
                if( ! isMatch(y, x, content, mask)) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool isSuperset(int min_x, int min_y, int max_x, int max_y, int content, int mask) {

        if( ! isMatch(min_x, min_y, max_x, max_y, content, mask)) {
            return false;
        }

        // Left Edge
        if(min_x > 0 && isMatch(min_x - 1, min_y, content, mask)) {
            return true;
        }

        // Right Edge
        if(max_x < sideLength && isMatch(max_x + 1, min_y, content, mask)) {
            return true;
        }

        // Top Edge
        if(min_y > 0 && isMatch(min_x, min_y - 1, content, mask)) {
            return true;
        }

        // Lower Edge
        if(max_y < sideLength && isMatch(min_x, max_y + 1, content, mask)) {
            return true;
        }

        return false;
    }

    inline void printMatrix() {

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

};

#endif // BYTEMATRIX_H

