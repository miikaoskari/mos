#include "mos/log.h"
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

extern void putchar(char c);

static void print_string(const char *s)
{
    if (!s) s = "(null)";
    while (*s) {
        putchar(*s++);
    }
}

static void print_num(unsigned long long num, int base, int width, char pad, int uppercase)
{
    char buf[32];
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0;

    if (num == 0) {
        buf[i++] = '0';
    } else {
        while (num > 0) {
            buf[i++] = digits[num % base];
            num /= base;
        }
    }

    while (i < width) {
        buf[i++] = pad;
    }

    while (i > 0) {
        putchar(buf[--i]);
    }
}

static void print_signed(long long num, int width, char pad)
{
    if (num < 0) {
        putchar('-');
        num = -num;
        if (width > 0) width--;
    }
    print_num((unsigned long long)num, 10, width, pad, 0);
}

void kvprintf(const char *format, va_list args)
{
    while (*format) {
        if (*format != '%') {
            putchar(*format++);
            continue;
        }

        format++;

        char pad = ' ';
        int width = 0;

        if (*format == '0') {
            pad = '0';
            format++;
        }

        while (*format >= '0' && *format <= '9') {
            width = width * 10 + (*format - '0');
            format++;
        }

        int is_long = 0;
        int is_long_long = 0;

        if (*format == 'l') {
            is_long = 1;
            format++;
            if (*format == 'l') {
                is_long_long = 1;
                format++;
            }
        }

        switch (*format) {
            case 's': {
                const char *s = va_arg(args, const char *);
                print_string(s);
                break;
            }
            case 'd':
            case 'i': {
                long long val;
                if (is_long_long) {
                    val = va_arg(args, long long);
                } else if (is_long) {
                    val = va_arg(args, long);
                } else {
                    val = va_arg(args, int);
                }
                print_signed(val, width, pad);
                break;
            }
            case 'u': {
                unsigned long long val;
                if (is_long_long) {
                    val = va_arg(args, unsigned long long);
                } else if (is_long) {
                    val = va_arg(args, unsigned long);
                } else {
                    val = va_arg(args, unsigned int);
                }
                print_num(val, 10, width, pad, 0);
                break;
            }
            case 'x': {
                unsigned long long val;
                if (is_long_long) {
                    val = va_arg(args, unsigned long long);
                } else if (is_long) {
                    val = va_arg(args, unsigned long);
                } else {
                    val = va_arg(args, unsigned int);
                }
                print_num(val, 16, width, pad, 0);
                break;
            }
            case 'X': {
                unsigned long long val;
                if (is_long_long) {
                    val = va_arg(args, unsigned long long);
                } else if (is_long) {
                    val = va_arg(args, unsigned long);
                } else {
                    val = va_arg(args, unsigned int);
                }
                print_num(val, 16, width, pad, 1);
                break;
            }
            case 'p': {
                void *ptr = va_arg(args, void *);
                print_string("0x");
                print_num((unsigned long long)(uintptr_t)ptr, 16, 16, '0', 0);
                break;
            }
            case 'c': {
                char c = (char)va_arg(args, int);
                putchar(c);
                break;
            }
            case '%': {
                putchar('%');
                break;
            }
            default:
                putchar('%');
                putchar(*format);
                break;
        }
        format++;
    }
}

void kprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    kvprintf(format, args);
    va_end(args);
}

void log_msg(log_level_t level, const char *file, int line, const char *format, ...)
{
    const char *prefix;

    switch (level) {
        case LOG_ERROR: prefix = "\033[31m[err]\033[0m  "; break;
        case LOG_WARN:  prefix = "\033[33m[warn]\033[0m "; break;
        case LOG_INFO:  prefix = "\033[34m[inf]\033[0m  "; break;
        case LOG_DEBUG: prefix = "\033[35m[dbg]\033[0m  "; break;
        default:        prefix = "[inf]  "; break;
    }

    print_string(prefix);
    print_string(file);
    putchar(':');
    print_num((unsigned long long)line, 10, 0, ' ', false);
    putchar(' ');

    va_list args;
    va_start(args, format);
    kvprintf(format, args);
    va_end(args);
    print_string("\n");
}
