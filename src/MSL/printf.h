#ifndef GALE01_323CF0
#define GALE01_323CF0

#include <placeholder.h>
#include <stdarg.h>

/* 323CF0 */ UNK_RET __stdio_atexit(UNK_PARAMS);
/* 323CF4 */ int sprintf(char* s, const char* format, ...);
/* 323DC8 */ int vsprintf(char* s, const char* format, va_list arg);
/* 323E38 */ int vprintf(const char* format, va_list arg);
/* 323EB4 */ int printf(const char*, ...);
/* 323F80 */ UNK_RET __StringWrite(UNK_PARAMS);
/* 323FEC */ UNK_RET __FileWrite(UNK_PARAMS);
/* 324044 */ UNK_RET __pformatter(UNK_PARAMS);
/* 324674 */ UNK_RET float2str(UNK_PARAMS);
/* 324CAC */ UNK_RET round_decimal(UNK_PARAMS);
/* 324DE0 */ UNK_RET longlong2str(UNK_PARAMS);
/* 3250C0 */ UNK_RET long2str(UNK_PARAMS);
/* 3252E4 */ UNK_RET parse_format(UNK_PARAMS);

#endif
