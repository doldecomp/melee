#ifndef MELEE_FT_CHARA_FTMASTERHAND_TYPES_H
#define MELEE_FT_CHARA_FTMASTERHAND_TYPES_H

#include <platform.h>
#include "ftMasterHand/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct ftMasterHand_SpecialAttrs {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    f32 x28;
    f32 x2C;
    Vec2 x30_pos2;
    f32 x38;
    f32 x3C;
    Vec3 x40_pos;
    f32 x4C;
    Vec2 x50;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    f32 x78;
    s32 x7C;
    f32 x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    f32 x98;
    f32 x9C;
    s32 xA0;
    f32 xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    f32 xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    s32 xEC;
    s32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    f32 x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
    s32 x144;
    s32 x148;
    f32 x14C;
    f32 x150;
    f32 x154;
    f32 x158;
    f32 x15C;
    s32 x160;
    s32 x164;
    s32 x168;
    s32 x16C;
    s32 x170;
    s32 x174;
    f32 x178;
};

union ftMasterHand_StateVars {
    struct ftMasterHand_Unk0Vars {
        f32 x0;
        HSD_GObjEvent x4;
        int x8;
        Vec3 xC;
        f32 x18;
        f32 x1C;
        int x20;
        f32 x24;
        int x28;
        int x2C;
        int x30;
        int x34;
        int x38;
        int x3C;
        int x40;
        int x44;
        int x48;
        int x4C;
        f32 x50;
        int x54;
        Vec3 x58;
        Vec3 x64;
        int x70;
        int x74;
        int x78;
    } unk0;

    struct ftMasterHand_Unk4Vars {
        int x0;
        int x4;
        int x8;
    } unk4;

    struct ftMasterHand_Unk13Vars {
        f32 x0;
        f32 x4;
    } unk13;
};

#endif
