#ifndef MELEE_CM_TYPES_H
#define MELEE_CM_TYPES_H

#include <placeholder.h>

#include "cm/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <dolphin/mtx.h>

struct CameraBox {
    CameraBox* next;
    CameraBox* prev;
    bool x8;
    /* +C:0 */ u8 xC_b0 : 1;
    /* +C:1 */ u8 xC_b1 : 1;
    /* +C:2 */ u8 xC_b2 : 1;
    s16 xE;
    Vec3 x10; // might be Vec2?
    Vec3 pos;
    float dir;
    Vec2 x2C;
    Vec3 size;
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

struct CameraQuake {
    /* 0x0 */ Vec3 x0;
    /* 0xC */ int type;
};

// global vars for camera mode 7 and 8
// mode 7 will attach and follow a player, and 8 is free cam
struct CameraDebugMode {
    int last_mode;
    int ply_slot;
    Vec3 mode7_int_offset;
    Vec3 mode7_eye_offset;
    Vec3 mode7_eye_pos;
    Vec3 mode7_int_pos;
    float mode7_fov;
    Vec3 mode8_int_pos;
    Vec3 mode8_eye_pos;
    float mode8_fov;
    u8 x4c[0x8]; // padding? not sure if this is correct
};

typedef struct Camera {
    /* 0x000 */ HSD_GObj* gobj;
    /* 0x004 */ int mode;
    /* 0x008 */ u8 background_r;
    /* 0x009 */ u8 background_g;
    /* 0x00A */ u8 background_b;
    /* 0x00B */ s8 pad_B;
    /* 0x00C */ f32 nearz;
    /* 0x010 */ f32 farz;
    /* 0x014 */ CameraMovement movement;
    /* 0x04C */ CameraMovement movement_lerp;
    /* 0x084 */ Vec2 translation;
    /* 0x08C */ s32 unk_8C[5]; /* maybe part of translation[4]? */
    /* 0x0A0 */ HSD_GObj* unk_A0;
    /* 0x0A4 */ f32 unk_A4;
    /* 0x0A8 */ f32 unk_A8;
    /* 0x0AC */ f32 unk_AC; /* inferred */
    /* 0x0B0 */ struct CameraQuake unk_B0[2][8];
    /* 0x1B0 */ struct CameraQuake unk_1B0[2][8];
    /* 0x2B0 */ float unk_2B0;
    /* 0x2B4 */ float unk_2B4;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2ba;
    /* 0x2BC */ f32 unk_2bc;
    /* 0x2C0 */ f32 unk_2c0;
    /* 0x2C4 */ s8 unk_2C4; /* unk player slot */
    /* 0x2C5 */ s8 unk_2C5;
    /* 0x2C6 */ char pad_2C6[0x2C8 - 0x2C6];
    /* 0x2C8 */ float pitch_offset;
    /* 0x2CC */ float yaw_offset;
    /* 0x2D0 */ char pad_2D0[0x2F8 - 0x2D0];
    /* 0x2F8 */ f32 unk_2F8;
    /* 0x2FC */ f32 unk_2FC;
    /* 0x300 */ char pad_300[0x320 - 0x300];
    /* 0x320 */ Vec3 unk_320;
    /* 0x32C */ f32 unk_32C;
    /* 0x330 */ f32 unk_330;
    /* 0x334 */ Vec3 unk_334;
    /* 0x340 */ u8 unk_341;
    /* 0x341:0 */ u8 unk_341_b0 : 1;
    /* 0x341:1 */ u8 unk_341_b1_b2 : 2;
    /* 0x341:3 */ u8 unk_341_b3_b4 : 2;
    /* 0x341:5 */ u8 unk_341_b5_b6 : 2;
    /* 0x341:7 */ u8 unk_341_b7 : 1;
    /* 0x342 */ char pad_342[0x350 - 0x342]; /* maybe part of unk_341[0x57]? */
    /* 0x350 */ Vec3 unk_350;
    /* 0x35C */ union {
        Vec3          vec;
        s32 (*cb)(f32*);
    } unk_35C;
    /* 0x368 */ Vec3 unk_368;
    /* 0x374 */ f32 unk_374;
    /* 0x378 */ f32 unk_378;
    /* 0x378 */ char pad_37C[0x398 - 0x37C];
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
    /* 0x39B */ char pad_39B; /* maybe part of unk_39A[6]? */
    /* 0x39C */ struct CameraDebugMode debug_mode;
} Camera; /* size = 0x3A4 */

/// @todo Size should be 0x39C like #cm_80452C68
// STATIC_ASSERT(sizeof(struct Camera) == 0x3A4);

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
struct CameraModeCallbacks {
    void (*(callback[9]))(void*);
};

struct CameraFixednessMult {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
};

#endif
