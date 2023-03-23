#ifndef MELEE_FT_CHARA_FTSEAK_TYPES_H
#define MELEE_FT_CHARA_FTSEAK_TYPES_H

#include <platform.h>

/// @sz{74}
typedef struct _ftSeakAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x4C;
    u8 data_filler_1[0x24];
} ftSeakAttributes;

typedef struct itChainSegment {
    f32 x00;
    f32 x04;
    f32 x08;
    f32 x0C;
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
} itChainSegment;

union ftSeak_StateVars {
    struct ftSeak_SpecialNVars {
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
        s32 x28;
        s32 x2C;
    } specialn;

    struct ftSeak_SpecialSVars {
        s32 x0;
        s32 x4;
        s32 x8;
        s32 xC;
        f32 x10;
        f32 x14;
        f32 x18;
        s32 x1C;
        s32 x20;
        s32 x24;
        s32 x28;
        s32 x2C;
    } specials;

    struct ftSeakSpecialHi {
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
        s32 x28;
        s32 x2C;
    } specialhi;
};

#endif
