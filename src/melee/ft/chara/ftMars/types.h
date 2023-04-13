#ifndef MELEE_FT_CHARA_FTMARS_TYPES_H
#define MELEE_FT_CHARA_FTMARS_TYPES_H

#include <platform.h>

#include <placeholder.h>

typedef struct _MarsAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
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
    u8 data_filler_68[0x98 - 0x68];
} MarsAttributes;

union ftMars_StateVars {
    struct ftMars_Unk0StateVars {
        bool x0;
    } unk0;

    struct ftMars_SpecialNVars {
        int x0;
    } specialn;

    struct ftMars_SpecialSVars {
        int x0;
    } specials;

    struct ftMars_SpecialLwVars {
        int x0;
    } speciallw;
};

#endif
