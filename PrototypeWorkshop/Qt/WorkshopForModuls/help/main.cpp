#include "usage.h"

#include <QDebug>
#include <QTextStream>

int main(int argc, char *argv[])
{

    QTextStream errorStream(stderr);

    if(argc == 1 ) {
        errorStream << "Error: " << argv[0] << " has not enough parameters (help cmd ...)" << endl;
        return 1;
    }

    QStringList commands;

    for(int i=1; i<argc; i++) {
        commands.append(QString("%1").arg(argv[i]));
    }


    man("help " + commands.join(" "));

    return 0;
}
