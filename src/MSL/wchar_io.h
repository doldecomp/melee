#ifndef _WCHAR_IO_H_
#define _WCHAR_IO_H_

#include <platform.h>

#include <ansi_files.h>
#include <common_structs.h>
#include <stdio.h>

int fwide(FILE* stream, int mode);

#endif
