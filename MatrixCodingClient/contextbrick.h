#ifndef CONTEXTBRICK_H
#define CONTEXTBRICK_H

#include "globals.h"

#include <QtGlobal>
#include <QDebug>
#include <QtMath>

typedef unsigned char byte_t;

class ContextBrick
{
public:
    ContextBrick() :
        content(0), mask(0) {}

    ContextBrick(byte_t content, byte_t mask) :
        content(content), mask(mask) {}

    byte_t content;
    byte_t mask;

    inline bool isMatch(byte_t in_content) {

        if ((in_content ^ content) == 0) {
            return true;
        }

        if (~(~(in_content ^ content) | mask) != 0) {
            return false;
        }

        return true;
    }

    inline bool setNextMatchingContent() {

        if(isMatch(content+1)) {
            content += 1;
            return true;
        }
        return false;
    }


    inline bool setNextMask() {

        if(mask < 128) {
            mask = (mask * 2) + 1;
            return true;
        }
        return false;
    }

    inline bool setNextMask(int sideLength) {

        if(mask < (sideLength * sideLength) / 2) {
            mask = (mask * 2) + 1;
            return true;
        }
        return false;
    }


    inline bool setNextMaskInstance() {

        if(mask > 128) {
            return false;
        }

        if(content < 256 - (mask+ 1)) {

            content += mask + 1;

            return true;
        }
        return false;
    }



    inline bool setNextMaskInstance(int sideLength) {

        if(mask > (sideLength * sideLength) / 2) {
            return false;
        }

        if(content < (sideLength * sideLength) - (mask+ 1)) {

            content += mask + 1;

            return true;
        }
        return false;
    }

    inline bool hasMatch(ContextBrick *otherBrick) {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

        int notEqual = this->content ^ otherBrick->content;
        if (notEqual == 0) {
            return true;
        }

        int offer_relevant = ~notEqual | this->mask;
        int not_offer_relevant = ~offer_relevant;
        if (not_offer_relevant != 0) {
            return false;
        }

        int request_relevant = ~notEqual | otherBrick->mask;
        int not_request_relevant = ~request_relevant;
        if (not_request_relevant != 0) {
            return false;
        }

        return true;
    }

    void printContextBrick()  {
        if (DEBUG) qDebug().nospace()  << __FILE__ << "(" << __LINE__ << "): "  << Q_FUNC_INFO;

        qDebug().noquote() << QString("Content:\t%1 %2").arg(content).arg(content, 8, 2, QLatin1Char('0'));
        qDebug().noquote() << QString("Mask:\t%1 %2").arg(content).arg(mask, 8, 2, QLatin1Char('0'));
    }
};

#endif // CONTEXTBRICK_H

