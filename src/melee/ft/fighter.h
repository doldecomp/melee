#ifndef _fighter_h_
#define _fighter_h_
#include <global.h>
#include "sysdolphin/baselib/gobj.h"
#include <dolphin/types.h>
struct Fighter {
    u8 padding0[0x2D4];
    void* data;
    u8 padding2D8[0x169C];
    s32 unk1974;
    u8 padding1[0x8B8];
    u32 unk222C;
    u8 padding2[0x10];
    u32 unk2240;
    u32 unk2244;
    u32 unk2248;
    u32 unk224C;
};
#endif