#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>


int puts(const char* s);
int printf(const char*, ...);
int sprintf(char* s, const char* format, ...);
int vprintf(const char* format, va_list arg);
int vsprintf(char* s, const char* format, va_list arg);

#endif
