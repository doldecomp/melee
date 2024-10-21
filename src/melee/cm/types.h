#ifndef MELEE_CM_TYPES_H
#define MELEE_CM_TYPES_H

#include <placeholder.h>

#include "cm/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

struct CameraBox {
    CameraBox* next;
    CameraBox* prev;
    bool x8;
    /* +C:0 */ u8 xC_b0 : 1;
    u8 xD_fill[0x10 - 0xD];
    Vec3 x10; // might be Vec2?
    Vec3 x1C;
    float x28;
    Vec2 x2C;
    Vec3 x34;
    Vec2 x40;
    Vec3 x48;
    Vec3 x54;
    Vec3 x60;
};

struct CameraMovement {
    /*  +0 */ Vec3 interest;
    /*  +C */ Vec3 target_interest;
    /* +18 */ Vec3 position;
    /* +24 */ Vec3 target_position;
    /* +30 */ float fov;
    /* +34 */ float target_fov;
};

struct CameraBounds {
    float x_min;
    float y_min;
    float x_max;
    float y_max;
    int subjects;
    float z_pos;
};

typedef struct Camera {
    /* 0x000 */ HSD_GObj* gobj;
    /* 0x004 */ u32 mode;
    /* 0x008 */ u8 background_r;
    /* 0x009 */ u8 background_g;
    /* 0x00A */ u8 background_b;
    /* 0x00B */ s8 pad_B;
    /* 0x00C */ f32 nearz;
    /* 0x010 */ f32 farz;
    /* 0x014 */ CameraMovement movement;
    /* 0x04C */ CameraMovement movement_lerp;
    /* 0x084 */ Vec2 translation;
    /* 0x08C */ char pad_8C[0x18]; /* maybe part of translation[4]? */
    /* 0x0A4 */ f32 unk_A4;
    /* 0x0A8 */ f32 unk_A8;
    /* 0x0AC */ f32 unk_AC;         /* inferred */
    /* 0x0B0 */ char pad_B0[0x20C]; /* maybe part of unk_AC[0x84]? */
    /* 0x2BC */ f32 unk_2bc;
    /* 0x2C0 */ f32 unk_2c0;
    /* 0x2C4 */ char pad_2C4[0x7D]; /* maybe part of unk_2c0[0x20]? */
    /* 0x341:0 */ u8 unk_341_b0 : 1;
    /* 0x341:1 */ u8 unk_341_b1 : 1;
    /* 0x341:2 */ u8 unk_341_b2 : 1;
    /* 0x341:3 */ u8 unk_341_b3 : 1;
    /* 0x341:4 */ u8 unk_341_b4 : 1;
    /* 0x341:5 */ u8 unk_341_b5 : 1;
    /* 0x341:6 */ u8 unk_341_b6 : 1;
    /* 0x341:7 */ u8 unk_341_b7 : 1;
    /* 0x342 */ char pad_342[0x56]; /* maybe part of unk_341[0x57]? */
    /* 0x398:0 */ u8 unk_398_b0 : 1;
    /* 0x398:1 */ u8 unk_398_b1 : 1;
    /* 0x398:2 */ u8 unk_398_b2 : 1;
    /* 0x398:3 */ u8 unk_398_b3 : 1;
    /* 0x398:4 */ u8 unk_398_b4 : 1;
    /* 0x398:5 */ u8 unk_398_b5 : 1;
    /* 0x398:6 */ u8 unk_398_b6_b7 : 2;
    /* 0x399:0 */ u8 unk_399_b0_b1 : 2;
    /* 0x399:2 */ u8 unk_399_b2 : 1;
    /* 0x399:3 */ u8 unk_399_b3 : 1;
    /* 0x399:4 */ u8 unk_399_b4 : 1;
    /* 0x399:5 */ u8 unk_399_b5 : 1;
    /* 0x399:6 */ u8 unk_399_b6 : 1;
    /* 0x399:7 */ u8 unk_399_b7 : 1;
    /* 0x39A:0 */ u8 unk_39A_b0 : 1;
    /* 0x39A:1 */ u8 unk_39A_b1 : 1;
    /* 0x39A:2 */ u8 unk_39A_b2 : 1;
    /* 0x39A:3 */ u8 unk_39A_b3 : 1;
    /* 0x39A:4 */ u8 unk_39A_b4 : 1;
    /* 0x39A:5 */ u8 unk_39A_b5 : 1;
    /* 0x39A:6 */ u8 unk_39A_b6 : 1;
    /* 0x39A:7 */ u8 unk_39A_b7 : 1;
    /* 0x39B */ char pad_39B[5]; /* maybe part of unk_39A[6]? */
    /* 0x3A0 */ u32 last_mode;
} Camera; /* size = 0x3A4 */

/// @todo Size should be 0x39C like #cm_80452C68
STATIC_ASSERT(sizeof(struct Camera) == 0x3A4);

struct CameraUnkGlobals {
    /*  +0 */ float _0[11];
    /* +2C */ float x2C;
    /* +30 */ float x30;
    /* +34 */ float x34;
    /* +38 */ float x38;
    /* +3C */ float x3C;
    /* +40 */ float x40;
    /* +44 */ float _44[43];
};

#endif
