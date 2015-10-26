#ifndef BYTEMATRIX_H
#define BYTEMATRIX_H

#include "contextbrick.h"

#include <QFile>

class ByteMatrix
{
public:
    ByteMatrix();

    int matrix[16][16];

    int sideLength;
    int min_x, min_y, max_x, max_y;

    QFile *dataFile;

    void loadDataFile(QFile* dataFile);

    // Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
    ContextBrick* getFirstMatch(int min_x, int min_y, int max_x, int max_y);

    // Normalized ContextBrick, i.e. mask matters and content is the lowest possible within the mask area
    ContextBrick* getSmallestSuperset(int min_x, int min_y, int max_x, int max_y);

    void printMatrix();

};

#endif // BYTEMATRIX_H
