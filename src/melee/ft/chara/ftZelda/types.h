#ifndef MELEE_FT_CHARA_FTZELDA_TYPES_H
#define MELEE_FT_CHARA_FTZELDA_TYPES_H

#include <platform.h>

#include "lb/types.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

struct ftZelda_FighterVars {
    /* 0x222C */ HSD_GObj* x222C;
};

typedef struct ftZelda_DatAttrs {
    float x0;
    s32 x4; // Type confirmed
    float x8;
    float xC;
    s32 x10;   // Type confirmed
    s32 x14;   // Type confirmed
    s32 x18;   // Type confirmed
    s32 x1C;   // Type confirmed
    float x20; // Type confirmed
    float x24; // Type confirmed
    s32 x28;
    float x2C; // Type confirmed
    s32 x30;
    float x34; // Type confirmed
    float x38; // Type confirmed
    float x3C; // Type confirmed
    float x40; // Type confirmed
    float x44; // Type confirmed
    s32 x48;   // Type confirmed
    float x4C; // Type confirmed
    float x50; // Type confirmed
    float x54;
    float x58;
    float x5C;
    s32 x60;   // Type confirmed
    float x64; // Type confirmed
    float x68; // Type confirmed
    float x6C; // Type confirmed
    float x70; // Type confirmed
    float x74; // Type confirmed
    float x78; // Type confirmed
    float x7C; // Type confirmed
    float x80; // Type confirmed
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
