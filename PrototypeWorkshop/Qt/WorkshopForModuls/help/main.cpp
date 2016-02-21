// .h
#include <QStringList>
// other includes

// .h
int usage(QStringList commands);
int desc(QStringList commands);
int help(QStringList commands);

// .cpp
#include <QDebug>
#include <QTextStream>
#include <QFile>

#define HELP_DIR "/home/stefan/Development/PrototypeWorkshop/QtWorkspace/WorkshopForModuls/texts"

// .cpp


/**
 * @brief usage
 * @param commands "usage cmd ..."
 * @return
 */

int usage(QStringList commands) {
    qDebug() << "usage(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(commands.size() < 2 ) {

        errorStream << "Error: usage(" << commands.join(" ") << ") has not enough parameters (usage cmd ...)" << endl;
        return 1;
    }

    if(commands.at(0)!="usage") {

        errorStream << "Error: usage(" << commands.join(" ") << ") is no valid call (usage cmd ...)" << endl;
        return 1;
    }

    QString filePath;
    QTextStream outStream(stdout);

    /**
     * Read usage file
     */

    filePath = HELP_DIR;
    commands.pop_front();
    filePath += "/" + commands.join("/") + "/usage";

    qDebug() << filePath << endl;



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
    qDebug() << "desc(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

    if(commands.size() < 2 ) {

        errorStream << "Error: desc(" << commands.join(" ") << ") has not enough parameters (desc cmd ...)" << endl;
        return 1;
    }

    if(commands.at(0)!="desc") {

        errorStream << "Error: desc(" << commands.join(" ") << ") is no valid call (desc cmd ...)" << endl;
        return 1;
    }

    QString filePath;
    QTextStream outStream(stdout);

    /**
     * Read desc file
     */

    filePath = HELP_DIR;
    commands.pop_front();
    filePath += "/" + commands.join("/") + "/desc";

    qDebug() << filePath << endl;



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
    qDebug() << "help(" << commands.join(" ") << ")" << endl;

    /**
     * Check input
     */
    QTextStream errorStream(stderr);

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

    QTextStream outStream(stdout);
    outStream << commands.join("/") << endl;

    return 0;
}




// only for dev
int main(int argc, char *argv[])
{

    qDebug() << "argc: " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        qDebug() << "argv[" << i << "]: " << argv[i] << endl;
    }


    QTextStream errorStream(stderr);

    if(argc <= 2 ) {
        errorStream << "Error: " << argv[0] << " has not enough parameters (help cmd ...)" << endl;
        return 1;
    }

    // call
    QStringList commands;

    for(int i=1; i<argc; i++) {
        commands.append(QString("%1").arg(argv[i]));
    }

    for(int i=0; i<commands.size(); i++) {
        qDebug() << "commands.at(" << i << "): " << commands.at(i) << endl;
    }


    if(commands.size() > 1 && commands.at(0) == "usage" ) {
        qDebug() << "main: usage: " << commands.join(" ") << ")" << endl;
        usage(commands);
        return 0;
    }

    if(commands.size() > 1 && commands.at(0) =="desc" ) {
        qDebug() << "main: desc: " << commands.join(" ") << ")" << endl;
        desc(commands);
        return 0;
    }

    if(commands.size() > 1 && commands.at(0) =="help" ) {
        qDebug() << "main: help: " << commands.join(" ") << ")" << endl;
        help(commands);
        return 0;
    }

    qDebug() << "main: default: " << commands.join(" ") << ")" << endl;
        help(commands);
        return 0;

//    commands.append("usage");
//    commands.append("help");
////    qDebug() << "Return: " << usage(commands) << endl;

//    commands.clear();
//    commands.append("desc");
//    commands.append("help");
////    qDebug() << "Return: " << desc(commands) << endl;

//    commands.clear();
//    commands.append("help");
//    commands.append("help");
//    qDebug() << "Return: " << help(commands) << endl;
}


