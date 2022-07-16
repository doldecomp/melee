#pragma once

#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

typedef struct _ftDonkeyAttributes {
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
    u8 data_filler_10[0x68 - 0x30];
    f32 x68;
    f32 x6C;
    f32 x70;
} ftDonkeyAttributes;

void ftDonkey_8010DB3C(HSD_GObj* fighterObj);
void ftDonkey_8010DE88(HSD_GObj* fighterObj);
void ftDonkey_8010DFF8(HSD_GObj* fighterObj);
