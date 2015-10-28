#include "contextbrick.h"

#include <iostream>

#include <QDebug>

ContextBrick::ContextBrick() :
        content(0), mask(0) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;
}

ContextBrick::ContextBrick(byte_t context, byte_t mask) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    this->content = context;
    this->mask    = mask;

//    qDebug() << "initialized content: " << content;
//    qDebug() << "initialized mask: " << mask;
}
