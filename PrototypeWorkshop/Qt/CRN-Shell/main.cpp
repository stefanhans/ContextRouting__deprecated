#include <QTextStream>
#include <QDebug>

#include "ci.h"
#include "cip.h"
//#include "crn.h"

#include "subshell_crn.h"
#include "subshell_ci.h"
#include "subshell_cip.h"


// INITIALIZE GLOBALS

/**
 * @brief The subshell_e enum
 */
enum subshell_e { SUBSHELL_CRN=0, SUBSHELL_CI=1, SUBSHELL_CIP=2, SUBSHELL_CIR=3 };
subshell_e subshell = SUBSHELL_CRN;

/**
 * @brief prompts
 */
QStringList prompts = (QStringList() << "<CRN> " << "<CI> " << "<CIP> " << "<CIR> ");

/**
 * @brief prompt
 */
QString prompt = prompts.at(subshell);

/**
 * @brief The mode_e enum
 */
enum mode_e { MODE_CMD=0, MODE_SHELL=1 };
mode_e mode;

QString my_global_string;


QTextStream outStream(stdout);
QTextStream stream(stdin);

QString line, outCmd;
QStringList command;



/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    qDebug() << "argc: " << argc << endl;

    my_global_string = QString ("ciao");


    // INITIALIZE SUBSHELLS
    Subshell_CRN crn;


    // START SHELL

    if(argc == 1) {
        ::mode = MODE_SHELL;

        crn.runShell();
    }


    // EXECUTE COMMAND

    if(argc > 1) {
        ::mode = MODE_CMD;

        QStringList command;

        for(int i=1; i<argc; i++) {
            command.append(QString("%1").arg(argv[i]));
        }

        crn.executeCommand(command);
    }

    qDebug() << "normal exit at program end" << endl;

}

