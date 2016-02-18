#ifndef PING_H
#define PING_H

#include "crn.h"

#include <QDebug>

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)


/**
 * @brief Shared Libary CRN
 */
CRN crn;


static void ping(QStringList command) {
    qDebug() << "static void ping(" << command.join(" ") << ")" << endl;

    int argc = command.size();

    QTextStream outStream(stdout);

    if(command.at(0)=="ping") {

        if(argc > 1) {

            if(command.at(1)=="tcp") {

                if(argc > 2) {

                    if(command.at(2)=="rand") {

                        QByteArray randValues;
                        qsrand(QTime::currentTime().msec());
                        for(int i=0; i <= 1064; i++) {
                            randValues.append(floor(qrand()/CRN_RANDOM_DIVISOR));
                        }

                        outStream << crn.pingTcp(command.at(2), &randValues) << endl;
                        return;

                    } // rand

                    outStream << crn.pingTcp(command.at(2)) << endl;
                    return;

                } // argc = 2

                outStream << crn.pingTcp() << endl;
                return;

            } // tcp

            outStream << "Usage: ping [tcp [rzv|rand|max]]" << endl;

        } // argc = 1

        outStream << crn.ping() << endl;
        return;
    }
    return;
}

#endif // PING_H

