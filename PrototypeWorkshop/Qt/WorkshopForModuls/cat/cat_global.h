#ifndef CAT_GLOBAL_H
#define CAT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CAT_LIBRARY)
#  define CATSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CATSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CAT_GLOBAL_H
