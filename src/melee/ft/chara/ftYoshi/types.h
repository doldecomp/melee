#ifndef MELEE_FT_CHARA_FTYOSHI_TYPES_H
#define MELEE_FT_CHARA_FTYOSHI_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include <melee/it/forward.h>

struct ftYoshi_FighterVars {
    /* 0x222C */ Vec3 x222C;
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
    float x28;
    float x2C;
    float x30;
    float x34;
    int x38;
    Vec2 x3C;
    float x44;
    int x48;
    int x4C;
    int x50;
    u8 pad_x54[0x5C - 0x54];
    float x5C;
    u8 pad_x60[0x6C - 0x60];
    float specials_start_gravity;
    float specials_start_terminal_vel;
    u8 pad_x74[0x7C - 0x74];
    float x7C;
    u8 pad_x80[0x8C - 0x80];
    float x8C;
    float x90;
    u8 pad_x94[0xcc - 0x94];
    float xCC;
    u8 pad_xD0[0xE0 - 0xD0];
    float xE0;
    u8 pad_xE4[0x114 - 0xE4];
    float x114;
    float x118;
    float x11C;
    float x120;
    u8 pad_x124[0x138 - 0x124];
} ftYoshiAttributes;
STATIC_ASSERT(sizeof(struct _ftYoshiAttributes) == 0x138);

struct ftYs_DatAttrs {
    /*   +0 */ char pad_0[0x10];
    /*  +10 */ Vec2 x10;
    /*  +18 */ float x18;
    /*  +1C */ UNK_T x1C;
    /*  +20 */ UNK_T x20;
    /*  +24 */ float x24;
    /*  +28 */ char pad_28[0xEC - 0x28];
    /*  +EC */ float xEC;
    /*  +F0 */ float xF0;
    /*  +F4 */ float xF4;
    /*  +F8 */ float specialhi_base_angle;
    /*  +FC */ float xFC;
    /* +100 */ float x100;
    /* +104 */ char x104[0x118 - 0x104];
    /* +118 */ Vec2 speciallw_star_offset;
};
STATIC_ASSERT(sizeof(struct ftYs_DatAttrs) == 0x120);

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
    struct ftYoshi_SpecialNVars {
        /* fp+2340:0 */ u8 x0_b0 : 1;
        /* fp+2340:1 */ u8 x0_b1 : 1;
        /* fp+2340:2 */ u8 x0_b2 : 1;
        /* fp+2340:3 */ u8 x0_b3 : 1;
    } specialn;
    struct ftYoshi_SpecialSVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ u8 x4[0xC - 0x4];
        /* fp+234C */ int xC;
        /* fp+2350 */ f32 x10;
        /* fp+2354 */ f32 x14;
        /* fp+2358 */ f32 x18;
        /* fp+235C */ f32 x1C;
        /* fp+2360 */ f32 x20;
        /* fp+2364 */ f32 x24;
        /* fp+2368 */ u8 x28[0x30 - 0x28];
        /* fp+2370 */ int x30;
    } specials;
    struct ftYoshi_SpecialHiVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
    } specialhi;
    struct ftYoshi_GuardVars {
        /* fp+2340 */ f32 x0;
        /* fp+2344 */ u8 _pad[8];
        /* fp+234C */ bool xC;
        /* fp+2350 */ f32 x10;
        /* fp+2354 */ f32 x14;
        /* fp+2358 */ f32 x18;
        /* fp+235C */ UNK_T x1C;
        /* fp+2360 */ int x20;
        /* fp+2364 */ int x24;
    } guard;
};

#endif
