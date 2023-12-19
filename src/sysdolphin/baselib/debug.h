#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <platform.h>

ATTRIBUTE_NORETURN void __assert(char*, u32, char*);

void HSD_Debug_803881E4(void);
ATTRIBUTE_NORETURN void HSD_Panic(char*, u32, char*);

/// @todo Take @c file as another arg, ignore it if @c !MUST_MATCH.
/// @todo Add another variant that takes a string for @c cond.
#ifdef MUST_MATCH
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))
#else
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, __LINE__, #cond))
#endif

#define HSD_ASSERT2(file, line, msg, cond)                                    \
    ((cond) ? ((void) 0) : __assert((file), (line), (#msg)))

int HSD_Debug_8038815C(s32 arg0, s32 arg1, s32* arg2, s32 arg3);

#endif
