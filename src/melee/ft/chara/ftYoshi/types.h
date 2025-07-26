#ifndef MELEE_FT_CHARA_FTYOSHI_TYPES_H
#define MELEE_FT_CHARA_FTYOSHI_TYPES_H

#include <platform.h>
#include <placeholder.h>
#include <sysdolphin/baselib/forward.h>

struct ftYoshi_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ Item_GObj* x2238;
};

typedef struct _ftYoshiAttributes { // x2D4 (fp->dat_attrs)
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
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
    f32 x40;
    f32 x44;
    s32 x48;
    s32 x4C;
    u8 pad_x50[0x6C - 0x50];
    float x6C;
    float x70;
    u8 pad_x74[0x114 - 0x74];
    float x114;
    float x118;
    float x11C;
    float x120;
    u8 pad_x124[0x138 - 0x124];
} ftYoshiAttributes;
STATIC_ASSERT(sizeof(struct _ftYoshiAttributes) == 0x138);

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
        /* fp+2340:0 */ u8 x0_b0 : 1;
        /* fp+2340:1 */ u8 x0_b1 : 1;
        /* fp+2340:2 */ u8 x0_b2 : 1;
        /* fp+2340:3 */ u8 x0_b3 : 1;
    } specialn;
    struct ftYoshi_SpecialSVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ u8 x4[0x30 - 0x4];
        /* fp+2370 */ int x30;
    } specials;
    struct ftYoshi_SpecialHiVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
    } specialhi;
};

#endif
