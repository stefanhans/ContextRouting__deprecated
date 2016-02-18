#ifndef SUBSHELL_CI_H
#define SUBSHELL_CI_H

#include "ci.h"

#include <QStringList>

class Subshell_CI
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
    CI ci;

};

#endif // SUBSHELL_CI_H

