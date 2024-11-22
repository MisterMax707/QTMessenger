#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTMESSENGERLIBRARY1_LIB)
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_EXPORT
# else
#  define QTMESSENGERLIBRARY1_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTMESSENGERLIBRARY1_EXPORT
#endif
