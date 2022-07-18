#pragma once

#include "melee/ft/ftcommon.h"
#include "melee/lb/lbvector.h"

typedef struct _ftDonkeyAttributes {
    s8* x0_arr;
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
    s32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
} ftDonkeyAttributes;

void ftDonkey_8010D774(HSD_GObj* fighterObj);

void ftDonkey_8010DB3C(HSD_GObj* fighterObj);
void ftDonkey_8010DE88(HSD_GObj* fighterObj);
void ftDonkey_8010DFF8(HSD_GObj* fighterObj);

void ftDonkey_8010E0CC(HSD_GObj* fighterObj);
void ftDonkey_8010E148(HSD_GObj* fighterObj);
void ftDonkey_8010E464(HSD_GObj* fighterObj);
void ftDonkey_8010E4EC(HSD_GObj* fighterObj);

void ftDonkey_DestroyAllEffects(HSD_GObj* fighterObj);