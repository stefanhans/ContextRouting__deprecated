#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include "contextbrick.h"

#include <QFile>
#include <QtGlobal>
#include <QDebug>
#include <QtMath>

//typedef unsigned char byte_t;


class ByteMatrix
{
public:
    ByteMatrix();

    int matrix[16][16];

    int sideLength;
//    int min_x, min_y, max_x, max_y;

    QFile *dataFile;

    inline bool isMatch(int x, int y, int content, int mask) {
qDebug() << "";
        byte_t in_content = matrix[x][y];

//        qDebug() << "in_content: " << in_content;

        if ((in_content ^ content) == 0) {
            qDebug() << "((in_content ^ content) == 0)";
            return true;
        }

        if (~(~(in_content ^ content) | mask) != 0) {
            qDebug() << "(~(~(in_content ^ content) | mask) != 0)";
            return false;
        }

        return true;

    }

    inline bool isMatch(int min_x, int min_y, int max_x, int max_y, int content, int mask) {

        for(int x = min_x; x <= max_x; x++) {
            for(int y = min_y; y <= max_y; y++) {
                if( ! isMatch(x, y, content, mask)) {
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

    void loadDataFile(QFile* dataFile);

    // Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
    ContextBrick* getFirstMatch(int min_x, int min_y, int max_x, int max_y);

    // Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
    ContextBrick* getSmallestSuperset(int min_x, int min_y, int max_x, int max_y);

    void printMatrix();

};

#endif // BYTEMATRIX_H
