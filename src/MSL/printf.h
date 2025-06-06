#ifndef GALE01_323CF0
#define GALE01_323CF0

#include <placeholder.h>

#include <stdarg.h>

/* 323CF4 */ int sprintf(char* s, const char* format, ...);
/* 323DC8 */ int vsnprintf(char* s, size_t n, const char* format, va_list);
/* 323DC8 */ int vsprintf(char* s, const char* format, va_list arg);
/* 323E38 */ int vprintf(const char* format, va_list arg);
/* 323EB4 */ int printf(const char*, ...);

#endif
