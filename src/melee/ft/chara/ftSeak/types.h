#ifndef MELEE_FT_CHARA_FTSEAK_TYPES_H
#define MELEE_FT_CHARA_FTSEAK_TYPES_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct ftSeak_FighterVars { // x222C (fp->fv.sk._)
    /* 0x222C */ int x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ HSD_GObj* x2234;
    /* 0x2238 */ Vec3 x2238[4];
    /* 0x2268 */ Vec3 x2268[4];
    /* 0x2298 */ Vec3 lstick_delta;
};

/// @sz{74}
typedef struct _ftSeakAttributes { // x2D4 (fp->dat_attrs)
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
    float x00;
    float x04;
    float x08;
    float x0C;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
} itChainSegment;

union ftSeak_MotionVars { // x2340 (fp->mv.sk._._)
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
        float x10;
        float x14;
        float x18;
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
