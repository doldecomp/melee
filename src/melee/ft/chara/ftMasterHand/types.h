#ifndef MELEE_FT_CHARA_FTMASTERHAND_TYPES_H
#define MELEE_FT_CHARA_FTMASTERHAND_TYPES_H

#include <platform.h>

#include "ftMasterHand/forward.h" // IWYU pragma: export
#include "it/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct ftMasterhand_FighterVars {
    /* 0x222C */ HSD_GObj* x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ float x2238;
    /* 0x223C */ float x223C;
    /* 0x2240 */ Vec3 x2240_pos;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ s32 x2250;
    /* 0x2254 */ s32 x2254;
    /* 0x2258 */ s32 x2258;
};

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
    float x28;
    float x2C;
    Vec2 x30_pos2;
    float x38;
    float x3C;
    Vec3 x40_pos;
    float x4C;
    Vec2 x50;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    float x78;
    s32 x7C;
    float x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    float x98;
    float x9C;
    s32 xA0;
    float xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    float xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    float xD4;
    float xD8;
    float xDC;
    float xE0;
    float xE4;
    float xE8;
    s32 xEC;
    s32 xF0;
    float xF4;
    float xF8;
    float xFC;
    float x100;
    float x104;
    float x108;
    float x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    float x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
    s32 x144;
    s32 x148;
    float x14C;
    float x150;
    float x154;
    float x158;
    float x15C;
    s32 x160;
    s32 x164;
    s32 x168;
    s32 x16C;
    s32 x170;
    s32 x174;
    float x178;
};

union ftMasterHand_MotionVars {
    struct ftMasterHand_Unk0Vars {
        float x0;
        HSD_GObjEvent x4;
        int x8;
        Vec3 xC;
        float x18;
        float x1C;
        int x20;
        float x24;
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
        float x50;
        int x54;
        Vec3 x58;
        Vec3 x64;
        int x70;
        int x74;
        int x78;
    } unk0;

    struct ftMasterHand_Unk4Vars {
        ftMasterHand_UnkEnum0 x0;
        int x4;
        int x8;
    } unk4;

    struct ftMasterHand_Unk13Vars {
        float x0;
        float x4;
    } unk13;

    struct ftMasterHand_FingerBeamVars {
        /*  +0 fp+2340 */ char pad_0[0x34];
        /* +34 fp+2374 */ Item_GObj* x34;
        /* +38 fp+2378 */ Item_GObj* x38;
        /* +3C fp+237C */ Item_GObj* x3C;
        /* +40 fp+2380 */ Item_GObj* x40;
    } fingerbeam;

    struct ftMasterHand_Damage_0 {
        /*  +0 fp+2340 */ char pad_0[0x28];
        /* +28 fp+2368 */ int x28;
        /* +2C fp+236C */ int x2C;
        /* +30 fp+2370 */ int x30;
        /* +34 fp+2374 */ Item_GObj* x34;
        /* +38 fp+2378 */ Item_GObj* x38;
        /* +3C fp+237C */ Item_GObj* x3C;
        /* +40 fp+2380 */ Item_GObj* x40;
    } dmg0;
};

#endif
