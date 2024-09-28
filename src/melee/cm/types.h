#ifndef MELEE_CM_TYPES_H
#define MELEE_CM_TYPES_H

#include "cm/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <placeholder.h>
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
    Vec3 interest;
    Vec3 target_interest;
    Vec3 position;
    Vec3 target_position;
    float fov;
    float target_fov;
};

struct CameraBounds {
    float x_min;
    float y_min;
    float x_max;
    float y_max;
    int subjects;
    float z_pos;
};

struct Camera {
    HSD_GObj* gobj;
    uint mode;
    unsigned char background_r;
    unsigned char background_g;
    unsigned char background_b;
    u8 unk_0xb;
    float nearz;
    float farz;
    CameraMovement movement;
    CameraMovement movement_lerp;
    Vec2 translation;
    u8 unk_cam[0x2B0 - 0x8C];
    u8 unk[0x2BC - 0x2B0];
    float unk_2bc;
    float unk_2c0;
    u8 unk2[0x39C - 0x2c0];
    uint last_mode;
};

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
