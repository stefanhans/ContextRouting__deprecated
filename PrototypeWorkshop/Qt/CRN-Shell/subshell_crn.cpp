#include "subshell_crn.h"
#include "subshell_ci.h"
#include "subshell_cip.h"

#include "crn.h"

#include <QDebug>

#define CRN_RANDOM_DIVISOR (RAND_MAX/255)

/**
 * global variables
 */
extern QString prompt;
extern QStringList prompts;

extern QString my_global_string;


extern QTextStream outStream;
extern QTextStream stream;

extern QString line, outCmd;
extern QStringList command;



Subshell_CI ci;
Subshell_CIP cip;


void Subshell_CRN::runShell() {
    qDebug() << "Subshell_CRN::runShell()" << endl;
    qDebug() << "my_global_string::runShell()" << my_global_string << endl;

    /**
    * Main loop
    */
    outStream << ::prompt << flush;
    do {

        line = stream.readLine();
        command = line.split(QRegExp("\\s+"));


        if(command.at(0)=="ci") {

            ::prompt = ::prompts.at(1);
            ci.runShell();

            ::prompt = ::prompts.at(0);
            outStream << ::prompt << flush;
            continue;
        }

        if(command.at(0)=="cip") {

            ::prompt = ::prompts.at(2);
            cip.runShell();

            ::prompt = ::prompts.at(0);
            outStream << ::prompt << flush;
            continue;
        }

        if(command.at(0)=="ping") {

            crn.ping(command);

            outStream << ::prompt << flush;
            continue;
        }

        if(command.at(0)=="exit" || command.at(0)=="quit") {
            return;
        }

        // Unknown command
        if(command.length()>0 && line != "") {
            outStream << command.at(0) << " not found"  << endl;

            outStream << ::prompt << flush;
            continue;
        }

        // Prompt after return
        outStream << ::prompt << flush;

    } while (!line.isNull());


    return;
}

void Subshell_CRN::executeCommand(QStringList command) {
    qDebug() << "Subshell_CRN::executeCommand(" << command.join(" ") << ")" << endl;

    QTextStream outStream(stdout);
    int argc = command.size();

    outStream << "argc: " << argc << endl;

    if(command.at(0)=="ci") {

        ci.executeCommand(command);
    }
    if(command.at(0)=="cip") {

        cip.executeCommand(command);
    }


    if(command.at(0)=="ping") {

        crn.ping(command);
    }



    return;
}
