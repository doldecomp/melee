#ifndef SYSDOLPHIN_BASELIB_SISLIB_STATIC_H
#define SYSDOLPHIN_BASELIB_SISLIB_STATIC_H

#include <Runtime/platform.h>

/// Shared by the sislib translation units.
static inline u8* HSD_SisLib_BytePtr(void* ptr)
{
    return ptr;
}

#endif
