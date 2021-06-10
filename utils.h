#ifndef _IRON_UTILS_H
#define _IRON_UTILS_H

#include "define_EVIL/define_EVIL.h"

#define IRON_VERSION_X 0
#define IRON_VERSION_Y 1
#define IRON_VERSION_Z 0
#define IRON_VERSION IRON_VERSION_X.IRON_VERSION_Y.IRON_VERSION_Z

#define IRON_DEBUG

#ifdef IRON_DEBUG
#define _IRON_DEBUG TRUE
#else
#define _IRON_DEBUG FALSE
#endif

#define IRON_INTERNAL_DEBUG

#ifdef IRON_INTERNAL_DEBUG
#define _IRON_INTERNAL_DEBUG TRUE
#else
#define _IRON_INTERNAL_DEBUG FALSE
#endif

// These are so granular so they can be turned on or off individually
#define iron_assert(expr) if (!(expr)) iron_log(__FILE__, __func__, __LINE__, IRON_LOG_ERROR, "Assertion '" #expr "' failed")
#define iron_internal_assert(expr) iron_assert(expr)
#define iron_error(msg, ...) iron_log(__FILE__, __func__, __LINE__, IRON_LOG_ERROR, msg, __VA__ARGS__)
#define iron_warning(msg, ...) iron_log(__FILE__, __func__, __LINE__, IRON_LOG_WARNING, msg, __VA__ARGS__)
#define iron_message(msg, ...) iron_log(__FILE__, __func__, __LINE__, IRON_LOG_MESSAGE, msg, __VA__ARGS__)
#define iron_debug(msg, ...) iron_message(msg, __VA__ARGS__)
#define iron_internal_debug(msg, ...) iron_message(msg, __VA__ARGS__)
enum iron_log_level {IRON_LOG_ERROR, IRON_LOG_WARNING, IRON_LOG_MESSAGE};
void iron_log(const char * file, const char * func_name, int line, enum iron_log_level log_level, const char * format, ...);

#endif // _IRON_UTILS_H
