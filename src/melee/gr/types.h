#ifndef MELEE_GR_TYPES_H
#define MELEE_GR_TYPES_H

#include <platform.h>
#include "gr/forward.h" // IWYU pragma: export
#include "it/forward.h"
#include "lb/forward.h"
#include "sc/forward.h"
#include <dolphin/gx/forward.h>
#include <baselib/forward.h>

#include <placeholder.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>

/// @remarks This struct is based in part on the datasheet however the info
///          there is likely incorrect as this doesn't quite match @c
///          grGroundParam.
typedef struct StageCameraInfo {
    f32 cam_bounds_left;      // 0x0
    f32 cam_bounds_right;     // 0x4
    f32 cam_bounds_top;       // 0x8
    f32 cam_bounds_bottom;    // 0xC
    f32 cam_x_offset;         // 0x10
    f32 cam_y_offset;         // 0x14
    f32 cam_vertical_tilt;    // 0x18
    f32 cam_pan_degrees;      // 0x1C
    f32 x20;                  // 0x20
    f32 x24;                  // 0x24
    f32 cam_track_ratio;      // 0x28
    f32 cam_fixed_zoom;       // 0x2C
    f32 cam_track_smooth;     // 0x30
    f32 cam_zoom_rate;        // 0x34
    f32 cam_max_depth;        // 0x38
    f32 x3C;                  // 0x3C
    f32 pausecam_zpos_min;    // 0x40
    f32 pausecam_zpos_init;   // 0x44
    f32 pausecam_zpos_max;    // 0x48
    f32 cam_angle_up;         // 0x4C
    f32 cam_angle_down;       // 0x50
    f32 cam_angle_left;       // 0x54
    f32 cam_angle_right;      // 0x58
    Vec3 fixed_cam_pos;       // 0x5C - 0x64
    f32 fixed_cam_fov;        // 0x68
    f32 fixed_cam_vert_angle; // 0x6C
    f32 fixed_cam_horz_angle; // 0x70
} StageCameraInfo;

typedef struct StageBlastZone {
    f32 left;   // 0x74
    f32 right;  // 0x78
    f32 top;    // 0x7C
    f32 bottom; // 0x80
} StageBlastZone;

typedef struct StageInfo {
    StageCameraInfo cam_info;  // 0x00 - 0x70
    StageBlastZone blast_zone; // 0x74 - 0x80

    u32 x84; // 0x84

    InternalStageId internal_stage_id; // 0x88

    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } unk8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    u8 xA0[4];
    u8 xA4_pad[0x12C - 0xA4];
    // TODO: determine actual type of x12C
    // Maybe a GObj with hsd_obj = TObj?
    struct {
        u8 x0_pad[0x28];
        struct {
            u8 x0_pad[0x18];
            GXColor color;
        }* ptr;
    }* x12C;
    Vec3 x130, x13C, x148, x154, x160, x16C;
    lb_UnkAnimStruct* (*x178)(int);
    void* x17C;
    HSD_GObj* x180[4];
    u8 x190_pad[0x280 - 0x190];
    HSD_JObj* x280[261];
    void* x694[4];
    void* x6A4;
    /* +6A8 */ struct {
        s32 unk0;
        Article* unk4;
    }** itemdata;
    /* +6AC */ void* coll_data;
    /* +6B0 */ UnkStage6B0* param;
    /* +6B4 */ UNK_T** ald_yaku_all;
    /* +6B8 */ void* map_ptcl;
    /* +6BC */ void* map_texg;
    /* +6C0 */ void* yakumono_param;
    /* +6C4 */ void* map_plit;
    /* +6C8 */ void* x6C8;
    /* +6CC */ DynamicModelDesc* quake_model_set;
    s16 x6D0;
    s16 x6D2;
    s16 x6D4;
    s16 x6D6;
    s32 x6D8;
    s16 x6DC;
    s16 x6DE;
    f32 x6E0;
    s32 x6E4[2];
    u8 x6EC_pad[0x708 - 0x6EC];
    s16 x708;
    f32 x70C;
    f32 x710;
    s32 x714;
    f32 x718;
    f32 x71C;
    s32 x720;
    f32 x724;
    f32 x728;
    s32 x72C;
    Vec3 x730;
    f32 x73C;
    s32 x740;
    u8 x744_pad[0x748 - 0x744];
} StageInfo;

typedef struct StageCallbacks {
    /*  +0 */ void (*callback0)(HSD_GObj*);
    /*  +4 */ bool (*callback1)(HSD_GObj*);
    /*  +8 */ void (*callback2)(HSD_GObj*);
    /*  +C */ void (*callback3)(HSD_GObj*);
    /* +10 */ u32 flags;
} StageCallbacks;

typedef struct StageData {
    u32 flags1;
    StageCallbacks* callbacks;
    char* data1;
    void (*callback0)(void);
    void (*callback1)(int);
    void (*callback2)(void);
    void (*callback3)(void);
    bool (*callback4)(void);
    lb_UnkAnimStruct* (*callback5)(enum_t);
    bool (*callback6)(Vec3*, int, HSD_JObj*);
    u32 flags2;
    S16Vec3* x2C;
    size_t x30; // size of x2C array
} StageData;

typedef struct StructPairWithStageID {
    s32 stage_id;
    s32 list_idx;
} StructPairWithStageID;

struct GroundVars_unk {
    int xC4;
    int xC8;
    int xCC;
    int xD0;
    int xD4;
    int xD8;
    float xDC;
    u8 xE0_pad[0x218 - 0xE0];
};

struct GroundVars_izumi {
    HSD_TObj* xC4;
    HSD_GObj* xC8;
    HSD_GObj* xCC;
    HSD_JObj* xD0;
    HSD_JObj* xD4;
    int xD8;
    float xDC;
    u8 xE0_pad[0x218 - 0xE0];
};

struct GroundVars_izumi2 {
    HSD_JObj* xC4;
    HSD_JObj* xC8;
    int xCC;
    int xD0;
    int xD4;
    int xD8;
    float xDC;
    u8 xE0_pad[0x218 - 0xE0];
};

struct GroundVars_izumi3 {
    short xC4;
    short xC6;
    short xC8;
    short xCA;
    HSD_JObj* xCC;
    float xD0;
    float xD4;
    float xD8;
    float xDC;
    u8 xE0_pad[0x218 - 0xE0];
};

struct Ground {
    int x0;         // 0x0
    HSD_GObj* gobj; // 0x4
    HSD_GObjEvent x8_callback;
    HSD_GObjEvent xC_callback;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } x10_flags;
    struct {
        u8 b012 : 3;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } x11_flags;

    InternalStageId map_id; // 0x14
    HSD_GObj* x18;          // 0x18
    HSD_GObjEvent x1C_callback;
    int x20[8];
    u8 x40_pad[0xC4 - 0x40];
    union GroundVars { // how big should this be?
        u8 _[0x218 - 0xC4];
        struct GroundVars_unk unk;
        struct GroundVars_izumi izumi;
        struct GroundVars_izumi2 izumi2;
        struct GroundVars_izumi3 izumi3;
    } gv;
};

// Appears to be related to stage audio
struct UnkBgmStruct {
    s32 x0;
    s32 x4;
    s32 x8;
    u32 xC;
    u32 x10;
    s16 x14;
    s16 x16;
    s16 x18;
    u8 pad[0x64 - 0x1A];
};

// TODO: what is this struct?
struct UnkStage6B0 {
    f32 x0;
    s16 x4;
    u8 x6_pad[2];
    s16 x8;
    s16 xA;
    s32 xC;
    s32 x10;
    s32 x14;
    f32 x18;
    f32 x1C, x20, x24, x28;
    u8 x2C_pad[0x2E - 0x2C];
    s16 x2E;
    s32 x30;
    s32 x34;
    s32 x38;
    f32 x3C, x40, x44, x48;
    bool x4C_fixed_cam;
    f32 x50, x54, x58, x5C, x60, x64;
    s16 x68;
    u8 x6C_pad[0xB0 - 0x6A];
    UnkBgmStruct* xB0;
    s32 xB4; // number of entries in xB0
    s32 xB8;
    s32 xBC;
    s32 xC0;
    s32 xC4;
    s32 xC8;
    s32 xCC;
    s32 xD0;
    s32 xD4;
    s32 xD8;
};

struct UnkStageDatInternal {
    u8 x0_fill[0x4];
    u32 unk4; // flags
};

struct UnkStageDat {
    void* unk0;
    s32 unk4;

    struct {
        struct HSD_Joint* unk0;
        u8 x4_fill[0x20 - 0x4];
        S16Vec3* unk20;
        s32 unk24; // size of unk20 array
        u8 x28_fill[0x34 - 0x28];
    }* unk8;
    s32 unkC;

    s32* unk10;
    s32 unk14;

    u8 x18_fill[0x20 - 0x18];

    void* unk20;
    s32 unk24;

    UnkStageDatInternal** unk28;
    s32 unk2C; // size
};

struct UnkArchiveStruct {
    HSD_Archive* unk0;
    UnkStageDat* unk4;
    s32 unk8;
};

struct grDynamicAttr_UnkStruct {
    grDynamicAttr_UnkStruct* next;
    s32 unk4;
    Vec3 unk8;
    s32 unk14;
    f32 unk18;
    s32 unk1C;
    u8 x0_fill[0x24 - 0x20];
};

#endif
