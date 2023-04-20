#ifndef MELEE_FT_CHARA_FTZELDA_TYPES_H
#define MELEE_FT_CHARA_FTZELDA_TYPES_H

#include <platform.h>

#include <common_structs.h>
#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct ftZelda_FighterVars {
    /* 0x222C */ HSD_GObj* x222C;
};

typedef struct ftZelda_DatAttrs {
    f32 x0;
    s32 x4; // Type confirmed
    f32 x8;
    f32 xC;
    s32 x10; // Type confirmed
    s32 x14; // Type confirmed
    s32 x18; // Type confirmed
    s32 x1C; // Type confirmed
    f32 x20; // Type confirmed
    f32 x24; // Type confirmed
    s32 x28;
    f32 x2C; // Type confirmed
    s32 x30;
    f32 x34; // Type confirmed
    f32 x38; // Type confirmed
    f32 x3C; // Type confirmed
    f32 x40; // Type confirmed
    f32 x44; // Type confirmed
    s32 x48; // Type confirmed
    f32 x4C; // Type confirmed
    f32 x50; // Type confirmed
    f32 x54;
    f32 x58;
    f32 x5C;
    s32 x60; // Type confirmed
    f32 x64; // Type confirmed
    f32 x68; // Type confirmed
    f32 x6C; // Type confirmed
    f32 x70; // Type confirmed
    f32 x74; // Type confirmed
    f32 x78; // Type confirmed
    f32 x7C; // Type confirmed
    f32 x80; // Type confirmed
    ReflectDesc x84;
} ftZelda_DatAttrs;

union ftZelda_MotionVars {
    struct ftZelda_SpecialHiVars {
        int x0;
        Vec2 x4;
        int xC;
        Vec2 x10;
        float x18;
    } specialhi;

    struct ftZelda_SpecialNVars {
        int x0;
    } specialn;

    struct ftZelda_SpecialSVars {
        int x0;
        int x4;
        int x8;
        int xC;
    } specials;
};

#endif
