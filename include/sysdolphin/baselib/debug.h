#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <dolphin/types.h>

void __assert(char*, u32, char*);
void HSD_Panic(char* file, u32 line, char* msg);

#endif
