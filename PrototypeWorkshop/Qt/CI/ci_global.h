#ifndef CI_GLOBAL_H
#define CI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CI_LIBRARY)
#  define CISHARED_EXPORT Q_DECL_EXPORT
#else
#  define CISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CI_GLOBAL_H
