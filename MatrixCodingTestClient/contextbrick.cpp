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
}

bool ContextBrick::hasMatch(ContextBrick *otherBrick) {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    byte_t notEqual = this->content ^ otherBrick->content;
    if (notEqual == 0) {
        return true;
    }

    byte_t offer_relevant = ~notEqual | this->mask;
    byte_t not_offer_relevant = ~offer_relevant;
    if (not_offer_relevant != 0) {
        return false;
    }

    byte_t request_relevant = ~notEqual | otherBrick->mask;
    byte_t not_request_relevant = ~request_relevant;
    if (not_request_relevant != 0) {
        return false;
    }

    return true;
}

void ContextBrick::printContextBrick() {
    if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

    qDebug().noquote() << QString("Content:\t%1 %2").arg(content).arg(content, 8, 2, QLatin1Char('0'));
    qDebug().noquote() << QString("Mask:\t%1 %2").arg(content).arg(mask, 8, 2, QLatin1Char('0'));

}

