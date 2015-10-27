#ifndef CONTEXTBRICK_H
#define CONTEXTBRICK_H

#define DEBUG 1

#include <QtGlobal>
#include <QDebug>
#include <QtMath>

//typedef unsigned char byte_t;

class ContextBrick
{
public:
    ContextBrick();

    ContextBrick(int content, int mask);

    int content;
    int mask;

    inline bool isMatch(int in_content) {

        int notEqual = in_content ^ content;
        if (notEqual == 0) {
            return true;
        }
        return ( ! (in_content ^ content) ) || mask;
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


    inline bool setNextMaskInstance() {

        int tmp_content;

        if(mask == 0) {
            content++;

            return true;
        }

        tmp_content = content + mask - (content % mask) + 1;

        if(tmp_content < 256) {

            content = tmp_content;

            return true;
        }
        return false;
    }



    inline bool setNextMaskInstance(int sideLength) {

        int tmp_content;

        if(mask == 0 && content < pow(2, sideLength) - 1) {
            content++;
            return true;
        }

        if(mask == 0) {
            return false;
        }

        tmp_content = content + mask - (content % mask) + 1;

        if(tmp_content < pow(2, sideLength) - 1) {
            content = tmp_content;
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
