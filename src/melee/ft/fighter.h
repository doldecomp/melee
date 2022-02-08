#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

typedef struct _Fighter {
    u32 data_filler_1[0x618 / 4];
    s8 x618_flag;
    s8 x619_flag;
    u32 data_filler_2[0x1C10 / 4];
    u32 x222C;
    u32 x2230;
    u32 x2234;
    u32 x2238;
    u32 x223C;
    u32 x2240;
    u32 x2244;
    u32 x2248;
} Fighter;

#endif
