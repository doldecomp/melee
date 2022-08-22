#pragma once

#include <melee/ft/ftcommon.h>
#include <melee/lb/lbvector.h>

typedef struct _ftIceClimberAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0xC4 - 0x30];
    f32 xC4;
    f32 xC8;
    u8 data_filler_2[0x90];
} ftIceClimberAttributes;
