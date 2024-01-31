#ifndef _STDIO_H_
#define _STDIO_H_

#include <platform.h>

#include <stdarg.h>

typedef struct {
    uint open_mode : 2;
    uint io_mode : 3;
    uint buffer_mode : 2;
    uint file_kind : 3;
    uint file_orientation : 2;
    uint binary_io : 1;
} __file_modes;

int puts(const char* s);
int printf(const char*, ...);
int sprintf(char* s, const char* format, ...);
int vprintf(const char* format, va_list arg);
int vsprintf(char* s, const char* format, va_list arg);

#endif
