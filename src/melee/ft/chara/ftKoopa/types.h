#ifndef MELEE_FT_CHARA_FTKOOPA_TYPES_H
#define MELEE_FT_CHARA_FTKOOPA_TYPES_H

#include <platform.h>

#include <placeholder.h>

struct ftKoopa_FighterVars {
    /* 0x222C */ f32 x222C;
    /* 0x2230 */ f32 x2230;
};

union ftKoopa_MotionVars {
    /// @todo Proper state name.
    struct ftKoopa_State1Vars {
        UNK_T x0;
        bool x4;
        UNK_T x8;
        bool xC;
    } unk1;
};

typedef struct _ftKoopaAttributes {
    f32 x0;
    u32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u32 x20;
    f32 x24;
    f32 x28;
    u32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    u32 unk50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    f32 x74;
    f32 x78;
    f32 x7C;
    f32 x80;
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    f32 x94;
    f32 x98;
    f32 x9C;
} ftKoopaAttributes;

typedef struct _ftKoopaVars {
    f32 x0;
    f32 x4;
} ftKoopaVars;

#endif
