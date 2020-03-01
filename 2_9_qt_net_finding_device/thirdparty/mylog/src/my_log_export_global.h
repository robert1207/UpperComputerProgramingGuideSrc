#ifndef MY_LOG_EXPORT_GLOBAL_H
#define MY_LOG_EXPORT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MY_LOG_LIBRARY)
#  define MY_LOG_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define MY_LOG_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MY_LOG_EXPORT_GLOBAL_H
