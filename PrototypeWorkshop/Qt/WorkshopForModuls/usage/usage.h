#ifndef USAGE_H
#define USAGE_H

#include "usage_global.h"

#include <QStringList>
// other includes

USAGESHARED_EXPORT int man(QString commands);

USAGESHARED_EXPORT int usage(QStringList commands);
USAGESHARED_EXPORT int description(QStringList commands);
USAGESHARED_EXPORT int help(QStringList commands);

#endif // USAGE_H
