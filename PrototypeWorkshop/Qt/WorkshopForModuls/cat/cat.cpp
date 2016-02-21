#include "cat.h"

#include <QDebug>
#include <QTextStream>
#include <QFile>

QTextStream errorStream(stderr);
QTextStream outStream(stdout);

/**
 * @brief my_function
 * @param commands
 * @return
 */

int my_function(QStringList commands) {
    qDebug() << "my_function(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(commands.size() != 4 || commands.at(0)!="function" || commands.at(1)!="my" ) {

        errorStream << "Error: my_function(" << commands.join(" ") << ") is no valid call (function my <arg_3> <arg_4>)" << endl;
        return 1;
    }


    /**
     * <functionality>
     */

    return 0;
}
