#ifndef USAGE_GLOBAL_H
#define USAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(USAGE_LIBRARY)
#  define USAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define USAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // USAGE_GLOBAL_H
