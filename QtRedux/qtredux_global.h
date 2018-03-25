#ifndef QTREDUX_GLOBAL_H
#define QTREDUX_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTREDUX_LIBRARY)
#  define QTREDUXSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTREDUXSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTREDUX_GLOBAL_H
