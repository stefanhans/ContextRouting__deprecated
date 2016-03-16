#ifndef CIP_GLOBAL_H
#define CIP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CIP_LIBRARY)
#  define CIPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CIPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CIP_GLOBAL_H
