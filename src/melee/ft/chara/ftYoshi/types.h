#ifndef MELEE_FT_CHARA_FTYOSHI_TYPES_H
#define MELEE_FT_CHARA_FTYOSHI_TYPES_H

#include <platform.h>

#include <placeholder.h>

typedef struct _ftYoshiAttributes {
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
    s32 x28;
    s32 x2C;
    u8 data_filler1[0xEF];
    f32 x120;
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

union ftYoshi_StateVars {
    /// @todo Proper state name.
    struct ftYoshi_State2Vars {
        f32 x0;
        UNK_T x4;
        UNK_T x8;
        bool xC;
        UNK_T x10;
        f32 x14;
        f32 x18;
    } unk2;
};

#endif
