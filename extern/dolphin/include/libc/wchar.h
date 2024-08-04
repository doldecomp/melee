#ifndef _WCHAR_H_
#define _WCHAR_H_

#include <stdio.h>

typedef unsigned short wchar_t;

int fwide(FILE *stream, int mode);

#endif
