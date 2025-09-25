#ifndef MELEE_FT_CHARA_FTMARS_TYPES_H
#define MELEE_FT_CHARA_FTMARS_TYPES_H

#include <platform.h>

#include "ft/forward.h"

#include "lb/types.h"

#include <common_structs.h>

struct ftMars_FighterVars {
    /* 0x222C */ u32 x222C;
    u8 _[FIGHTERVARS_SIZE - 4];
};

struct SwordAttrs {
    u8 pad_x0[0x14];
    int x14;
    float x18;
    float x1C;
};

typedef struct _MarsAttributes {
    int x0;
    int x4;
    int x8;
    float specialn_friction;
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
    float x54;
    float x58;
    float x5C;
    float x60;
    AbsorbDesc x64;
    struct SwordAttrs x78;
} MarsAttributes;

union ftMars_MotionVars {
    struct ftMars_Unk0MotionVars {
        bool x0;
    } unk0;

    struct ftMars_SpecialNVars {
        int cur_frame;
    } specialn;

    struct ftMars_SpecialSVars {
        int x0;
    } specials;

    struct ftMars_SpecialLwVars {
        int x0;
    } speciallw;
};

#endif
