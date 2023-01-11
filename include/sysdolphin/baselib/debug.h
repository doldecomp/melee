#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <Runtime/platform.h>

void __assert(char*, u32, char*);
void func_803881E4(void);
void HSD_Panic(char*, u32, char*);

/// @todo This is @c HSD_ASSERT and belongs in @c baselib/debug.h.
/// @todo Take @c file as another arg, ignore it if @c !MUST_MATCH.
/// @todo Add another variant that takes a string for @c cond.
#ifdef MUST_MATCH
#define HSD_ASSERT(line, cond)                                                 \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))
#else
#define HSD_ASSERT(line, cond)                                                 \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#endif

#endif
