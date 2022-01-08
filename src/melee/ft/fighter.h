#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

typedef struct _Fighter {
    u32 data[0x222C / 4];
    u32 x222C;
    u32 x2230;
    u32 x2234;
    u32 x2238;
    u32 x223C;
    u32 x2240;
} Fighter;

#endif
