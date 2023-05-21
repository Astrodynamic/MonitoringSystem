#pragma once

#include <QtCore/qglobal.h>

#if defined(LIB_CPU_AGENT_LIBRARY)
#  define LIB_CPU_AGENT_EXPORT Q_DECL_EXPORT
#else
#  define LIB_CPU_AGENT_EXPORT Q_DECL_IMPORT
#endif
