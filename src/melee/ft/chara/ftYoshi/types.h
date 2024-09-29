#ifndef MELEE_FT_CHARA_FTYOSHI_TYPES_H
#define MELEE_FT_CHARA_FTYOSHI_TYPES_H

#include <platform.h>
#include <placeholder.h>

struct ftYoshi_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
};

typedef struct _ftYoshiAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    s32 x28;
    s32 x2C;
    u8 data_filler1[0xEF];
    float x120;
    u8 data_filler2[0x14];
} ftYoshiAttributes;

struct S_UNK_YOSHI2 {
    s32 x0;
    s32 x4;
    s32 x8_end_index;
    u8* xC_start_index;
};

struct S_UNK_YOSHI1 {
    s32 x0;
    struct S_UNK_YOSHI2* unk_struct;
};

union ftYoshi_MotionVars {
    /// @todo Proper state name.
    struct ftYoshi_State2Vars {
        float x0;
        UNK_T x4;
        UNK_T x8;
        bool xC;
        UNK_T x10;
        float x14;
        float x18;
    } unk2;
    struct ftYoshi_SpecialNVars {
        /* fp+2340 */ int x0_b0 : 1;
    } specialn;
};

#endif
