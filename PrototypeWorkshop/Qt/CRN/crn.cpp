#include "crn.h"
#include "tcp_ping.h"

#include <QDebug>

int CRN::ping(QStringList command) {
    qDebug() << "CRN::ping(" << command.join(" ") << ")" << endl;

    return tcp_ping(command);
}
