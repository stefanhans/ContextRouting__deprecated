#include "usage.h"

#include <QDebug>
#include <QTextStream>
#include <QFile>

#define HELP_DIR "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/texts"


QTextStream errorStream(stderr);
QTextStream outStream(stdout);

/**
 * @brief man
 * @param commands
 * @return
 */
int man(QString commands) {
    //qDebug() << "man(" << commands << ")" << endl;

    QStringList arguments = commands.split(QRegExp("\\s+"));



    if(arguments.at(0) == "" ) {
        errorStream << "Error: man(\"\") has no parameter (man cmd ...)" << endl;
        return 1;
    }

    if(arguments.at(0) == "usage" ) {
        usage(arguments);
        return 0;
    }

    if(arguments.at(0) == "desc" ) {
        desc(arguments);
        return 0;
    }

    if(arguments.at(0) == "help" ) {
        help(arguments);
        return 0;
    }

    errorStream << "Error: man(" << arguments.join(" ") << ") is no valid call (man cmd ...)" << endl;
        return 1;
}


/**
 * @brief usage
 * @param commands "usage cmd ..."
 * @return
 */

int usage(QStringList commands) {
    //qDebug() << "usage(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    if(commands.size() < 2 ) {

        errorStream << "Error: usage(" << commands.join(" ") << ") has not enough parameters (usage cmd ...)" << endl;
        return 1;
    }

    if(commands.at(0)!="usage") {

        errorStream << "Error: usage(" << commands.join(" ") << ") is no valid call (usage cmd ...)" << endl;
        return 1;
    }

    QString filePath;

    /**
     * Read usage file
     */

    filePath = HELP_DIR;
    commands.pop_front();
    filePath += "/" + commands.join("/") + "/usage";

    //qDebug() << filePath << endl;



    QFile descFile(filePath);
    if (!descFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        errorStream << "Error: usage(" << commands.join(" ") << ") can not read usage file " << filePath << endl;
        return 1;
    }

    while (!descFile.atEnd()) {
        QByteArray line = descFile.readLine();
        outStream << line << endl;
    }


    return 0;
}




/**
 * @brief desc
 * @param commands "desc cmd ..."
 * @return
 */

int desc(QStringList commands) {
    //qDebug() << "desc(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    if(commands.size() < 2 ) {

        errorStream << "Error: desc(" << commands.join(" ") << ") has not enough parameters (desc cmd ...)" << endl;
        return 1;
    }

    if(commands.at(0)!="desc") {

        errorStream << "Error: desc(" << commands.join(" ") << ") is no valid call (desc cmd ...)" << endl;
        return 1;
    }

    QString filePath;

    /**
     * Read desc file
     */

    filePath = HELP_DIR;
    commands.pop_front();
    filePath += "/" + commands.join("/") + "/desc";

    //qDebug() << filePath << endl;



    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        errorStream << "Error: desc(" << commands.join(" ") << ") can not read desc file " << filePath << endl;
        return 1;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        outStream << line << endl;
    }

    return 0;
}

/**
 * @brief help
 * @param commands "help cmd ..."
 * @return
 */

int help(QStringList commands) {
    //qDebug() << "help(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    if(commands.size() < 2 ) {

        errorStream << "Error: help(" << commands.join(" ") << ") has not enough parameters (help cmd ...)" << endl;
        return 1;
    }

    if(commands.at(0)!="help") {

        errorStream << "Error: help(" << commands.join(" ") << ") is no valid call (help cmd ...)" << endl;
        return 1;
    }

    commands.pop_front();
    commands.insert(0, "usage");

    usage(commands);

    commands.pop_front();
    commands.insert(0, "desc");

    desc(commands);

    return 0;
}
