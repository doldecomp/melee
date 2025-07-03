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
    s32 x0;
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
    // additions to match ftYs_SpecialN_8012CDB4
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
    f32 x40;
    f32 x44;
    // u8 data_filler1[0xEF];
    u8 data_filler1[0xD7]; // subtracting 18
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
        union x0 {
            /* fp+2340 */ s32 x0;
            struct ftYoshi_SpecialN_x0Bytes {
                /* fp+2340 */ int x0_b0 : 1;
                /* fp+2341 */ int x0_b1 : 1;
                /* fp+2342 */ int x0_b2 : 1;
                /* fp+2343 */ int x0_b3 : 1;
            }x0_bytes;
        };
        /* fp+2344 */ s32 x4;
    } specialn;
};

#endif
