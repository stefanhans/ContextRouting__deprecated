#ifndef CRN_GLOBAL_H
#define CRN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRN_LIBRARY)
#  define CRNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CRNSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CRN_GLOBAL_H
