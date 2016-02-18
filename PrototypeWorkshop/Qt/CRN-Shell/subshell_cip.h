#ifndef SUBSHELL_CIP_H
#define SUBSHELL_CIP_H

#include "cip.h"

class Subshell_CIP
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
    CIP cip;

};

#endif // SUBSHELL_CIP_H

