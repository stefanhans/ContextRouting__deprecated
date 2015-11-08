#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include "globals.h"

#include <QUrl>
#include <QtGlobal>
#include <QDebug>
#include <QtMath>


typedef unsigned char byte_t;


class ByteMatrix
{
public:
    ByteMatrix():
        matrix(),
        sideLength(0),
        dataUrl(),
        min_x(0),
        min_y(0),
        max_x(0),
        max_y(0),
        highestNumber(256) {}

    int matrix[16][16];

    int sideLength;

    QUrl dataUrl;

    int min_x, min_y, max_x, max_y, highestNumber;

    inline bool isMatch(int x, int y, byte_t content, byte_t mask) {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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

    inline bool isMatch(int min_x, int min_y, int max_x, int max_y, byte_t content, byte_t mask) {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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

    inline bool isSuperset(int min_x, int min_y, int max_x, int max_y, byte_t content, byte_t mask) {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

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

    inline QString printMatrix() {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

        QString matrixOut(QString("\nCurrent Loaded Matrix Data:\n%1\n").arg(LINE_SEPARATOR));

        matrixOut.append(QString("dataUrl: %1\n").arg(dataUrl.toString()));

        matrixOut.append(QString("matrix: \n"));
        for (int row = 0; row < sideLength; ++row){

            matrixOut.append("\t");

            for (int col = 0; col < sideLength; ++col){
                if(col < sideLength-1) {

                    matrixOut.append(QString("%1, ").arg(QString("%1").arg(matrix[row][col]), 3, QLatin1Char(' ')));
                }
                else {
                    matrixOut.append(QString("%1\n").arg(QString("%1").arg(matrix[row][col]), 3, QLatin1Char(' ')));
                }
            }
        }
        matrixOut.append("\n");

        matrixOut.append(QString("sideLength: %1\n").arg(sideLength));
        matrixOut.append(QString("min_x: %1\n").arg(min_x));
        matrixOut.append(QString("min_y: %1\n").arg(min_y));
        matrixOut.append(QString("max_x: %1\n").arg(max_x));
        matrixOut.append(QString("max_y: %1\n").arg(max_y));
        matrixOut.append(QString("%1\n").arg(LINE_SEPARATOR));

        qDebug().noquote() << matrixOut;

        return matrixOut;
    }

};

#endif // BYTEMATRIX_H

