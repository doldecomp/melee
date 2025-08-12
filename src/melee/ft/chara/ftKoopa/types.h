#ifndef MELEE_FT_CHARA_FTKOOPA_TYPES_H
#define MELEE_FT_CHARA_FTKOOPA_TYPES_H

#include <placeholder.h>
#include <platform.h>

struct ftKoopa_FighterVars {
    /* 0x222C */ float x222C;
    /* 0x2230 */ float x2230;
};

union ftKoopa_MotionVars {
    /// @todo Proper state name.
    struct ftKoopa_State1Vars {
        UNK_T x0;
        bool x4;
        UNK_T x8;
        bool xC;
    } unk1;
    /// @todo Possibly #ftKoopa_State1Vars.
    struct ftKoopa_SpecialSVars {
        /* fp+2340 */ bool b_held;
        /* fp+2344 */ bool x4;
        /* fp+2348 */ int facing_dir;
        /* fp+2348 */ bool xC;
    } specials;
};

typedef struct _ftKoopaAttributes {
    float x0;
    u32 x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    u32 x20;
    float x24;
    float x28;
    u32 x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    u32 unk50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    float x98;
    float x9C;
} ftKoopaAttributes;

typedef struct _ftKoopaVars {
    float x0;
    float x4;
} ftKoopaVars;

#endif
