#include <QTextStream>
#include <QDebug>

#include "ci.h"
#include "cip.h"
#include "crn.h"

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)


/**
 * @brief Shared Libary CI
 */
CI ci;


/**
 * @brief Shared Libary CIP
 */
CIP cip;

/**
 * @brief Shared Libary CRN
 */
CRN crn;

/**
 * @brief interpretMode
 * @param modus
 * @return
 */
inline QString interpretMode(byte_t mode) {
    switch (mode) {
    case DM_INTEGER:
        return "INTEGER";
        break;
    case DM_HEX:
        return "HEX";
        break;
    case DM_CHAR:
        return "CHAR";
        break;
    default:
        return "Not defined";
    }
}

inline quint8 randByte() {
    return floor(qrand()/CRN_RANDOM_DIVISOR);
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QTextStream outStream(stdout);
    QTextStream stream(stdin);
    QString line;
    QStringList command;

    if(argc > 1) {
        for(int i=1; i<argc; i++) {
            command.append(QString("%1").arg(argv[i]));
        }

        if(command.at(0)=="ping") {
outStream << "ping" << endl;
            if(argc > 2) {
                outStream << "ping" << endl;

                if(command.at(1)=="tcp") {
                    outStream << command.at(1) << endl;
                    if(argc > 3) {
                        outStream << command.at(2) << endl;
                        if(argc > 3 && command.at(2)=="rand") {
                            QByteArray randValues;
                            quint8 rand;
                            qsrand(QTime::currentTime().msec());
                            for(int i=0; i <= 1064; i++) {
                                rand = floor(qrand()/CRN_RANDOM_DIVISOR);

//                                outStream << "rand: " << rand << endl;
                                randValues.append(rand);
//                                outStream << "randValues.size(): " << randValues.size() << endl;
//                                outStream << "randValues[" << rand << "]: " << randValues.at(rand) << endl;
                            }
                            outStream << "command.at(2): " << command.at(2) << endl;
                            outStream << "randValues.size(): " << randValues.size() << endl;
                            outStream << "randValues[" << rand << "]: " << randValues.at(10) << endl;
                            outStream << crn.pingTcp(command.at(2), &randValues) << endl;
                            exit(0);
                        }
                        else {
                            outStream << crn.pingTcp(command.at(2)) << endl;
                            exit(0);
                        }
                    }
                    else {
                        outStream << crn.pingTcp() << endl;
                        exit(0);
                    }
                }


//                if(command.at(2)=="udp") {
//                    if(argc > 3) {
//                        outStream << crn.pingUdp(command.at(1)) << endl;
//                        exit(0);
//                    }
//                    else {
//                        outStream << crn.pingUdp() << endl;
//                        exit(0);
//                    }


//                }
//                outStream << crn.pingTcp(command.at(2)) << endl;
//            }
//            else {
//                outStream << crn.pingTcp() << endl;
//            }
            }
        }
        exit(0);

    }

    QString prompt = "<CRN> ";

    /**
    * Main loop
    */
    outStream << prompt << flush;
    do {

        line = stream.readLine();
        command = line.split(QRegExp("\\s+"));

        /*
         * touch
         */
        if(command.at(0)=="touch") {
            outStream << cip.cat(cip.touch()) << endl;

            outStream << prompt << flush;
            continue;
        }


        /*
         * cat
         */
        if(command.at(0)=="cat") {
            outStream << cip.cat(QByteArray(42, '\0')) << endl;

            outStream << prompt << flush;
            continue;
        }



        /*
         * help
         * env
         * exit
         */
        if(command.at(0)=="help") {
            outStream << "env" << endl;
            outStream << "exit" << endl;
            outStream << "help" << endl;
            outStream << "imode" << endl;
            outStream << "omode" << endl;
            outStream << "set imode [integer|hex|char]" << endl;
            outStream << "set omode [integer|hex|char]" << endl;

            outStream << prompt << flush;
            continue;
        }

        if(command.at(0)=="env") {
            outStream << "line: \"" << line << "\"" << endl;
            outStream << "prompt: \"" << prompt << "\"" << endl;
            outStream << "imode: " << interpretMode(ci.getInMode())  << endl;
            outStream << "omode: " << interpretMode(ci.getOutMode())  << endl;

            outStream << prompt << flush;
            continue;
        }

        if(command.at(0)=="exit") {
            exit(0);
        }

        /*
         * imode
         * omode
         *
         */
        if(command.at(0)=="imode") {
                outStream << "CI direct mode in: " << interpretMode(ci.getInMode())  << endl;

                outStream << prompt << flush;
                continue;
        }
        if(command.at(0)=="omode") {
                outStream << "CI direct mode out: " << interpretMode(ci.getOutMode())  << endl;

                outStream << prompt << flush;
                continue;
        }

        /*
         * set imode [integer|hex|char]
         * set omode [integer|hex|char]
         *
         */
        if(command.at(0)=="set") {

            if(command.length()==1) {

                outStream << "Usage: set [imode|omode]" << endl;

                outStream << prompt << flush;
                continue;
            }

            if(command.at(1)=="imode") {

                if(command.length()==2) {

                    outStream << "Usage: set imode [integer|hex|char]" << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="integer") {
                    ci.setInMode(DM_INTEGER);
                    outStream << "CI direct modus in: " << interpretMode(ci.getInMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="hex") {
                    ci.setInMode(DM_HEX);
                    outStream << "CI direct modus in: " << interpretMode(ci.getInMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="char") {
                    ci.setInMode(DM_CHAR);
                    outStream << "CI direct modus in: " << interpretMode(ci.getInMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                outStream << "Usage: set imode [integer|hex|char]" << endl;

                outStream << prompt << flush;
                continue;
            }


            if(command.at(1)=="omode") {

                if(command.length()==2) {

                    outStream << "Usage: set omode [integer|hex|char]" << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="integer") {
                    ci.setOutMode(DM_INTEGER);
                    outStream << "CI direct modus out: " << interpretMode(ci.getOutMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="hex") {
                    ci.setOutMode(DM_HEX);
                    outStream << "CI direct modus out: " << interpretMode(ci.getOutMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                if(command.at(2)=="char") {
                    ci.setOutMode(DM_CHAR);
                    outStream << "CI direct modus out: " << interpretMode(ci.getOutMode())  << endl;

                    outStream << prompt << flush;
                    continue;
                }

                outStream << "Usage: set omode [integer|hex|char]" << endl;

                outStream << prompt << flush;
                continue;
            }

            outStream << "Usage: set [imode|omode]" << endl;

            outStream << prompt << flush;
            continue;
        }


        if(command.at(0)=="ping") {
            outStream << crn.ping() << endl;

            outStream << prompt << flush;
            continue;
        }

        // Unknown command
        if(command.length()>0 && line != "") {
            outStream << command.at(0) << " not found"  << endl;

            outStream << prompt << flush;
            continue;
        }

        // Prompt after return
        outStream << prompt << flush;

    } while (!line.isNull());

//    return a.exec();
}

