#ifndef SUBSHELL_CRN_H
#define SUBSHELL_CRN_H

#include "crn.h"

class Subshell_CRN
{

public:

    /**
     * @brief runShell
     */
    void runShell();

    /**
     * @brief executeCommand
     * @param command
     */
    void executeCommand(QStringList command);

private:

    /**
     * @brief Shared Libary CRN
     */
    CRN crn;

};

#endif // SUBSHELL_CRN_H

