#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

typedef enum log_level {
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
} log_level_t;

#define info(...) log_msg(LOG_INFO, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define warn(...) log_msg(LOG_WARN, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define error(...) log_msg(LOG_ERROR, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define dbg(...) log_msg(LOG_DEBUG, __FILE_NAME__, __LINE__, __VA_ARGS__)

void kprintf(const char *format, ...);
void kvprintf(const char *format, va_list args);

void log_msg(log_level_t level, const char *file, int line, const char *format, ...);

#endif // LOG_H
