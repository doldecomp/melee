#ifndef _stage_h_
#define _stage_h_

#include <global.h>

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef Vec Vec3;

enum InternalStageID {
    CASTLE = 0x02, // Princess Peach's Castle
    RCRUISE = 0x03, // Rainbow Cruise
    KONGO = 0x04, // Kongo Jungle
    GARDEN = 0x05, // Jungle Japes
    GREATBAY = 0x06, // Great Bay
    SHRINE = 0x07, // Hyrule Temple
    ZEBES = 0x08, // Brinstar
    KRAID = 0x09, // Brinstar Depths
    STORY = 0x0A, // Yoshi's Story
    YORSTER = 0x0B, // Yoshi's Island
    IZUMI = 0x0C, // Fountain of Dreams
    GREENS = 0x0D, // Green Greens
    CORNERIA = 0x0E, // Corneria
    VENOM = 0x0F, // Venom
    PSTADIUM = 0x10, // Pokemon Stadium
    PURA = 0x11, // Poke Floats
    MUTECITY = 0x12, // Mute City
    BIGBLUE = 0x13, // Big Blue
    ONETT = 0x14, // Onett
    FOURSIDE = 0x15, // Fourside
    ICEMTN = 0x16, // Icicle Mountain
    INISHIE1 = 0x18, // Mushroom Kingdom
    INISHIE2 = 0x19, // Mushroom Kingdom II
    FLATZONE = 0x1B, // Flat Zone
    OLDPUPUPU = 0x1C, // Dream Land
    OLDYOSHI = 0x1D, // Yoshi's Island (64)
    OLDKONGO = 0x1E, // Kongo Jungle (64)
};

// This struct is based in part on the datasheet
// however the info there is likely incorrect as this doesn't quite match grGroundParam
typedef struct _StageCameraInfo {
    f32 cam_bounds_left; // 0x0
    f32 cam_bounds_right; // 0x4
    f32 cam_bounds_top; // 0x8
    f32 cam_bounds_bottom; // 0xC
    f32 cam_x_offset; // 0x10
    f32 cam_y_offset; // 0x14
    f32 cam_vertical_tilt; // 0x18
    f32 cam_pan_degrees; // 0x1C
    f32 x20; // 0x20
    f32 x24; // 0x24
    f32 cam_track_ratio; // 0x28
    f32 cam_fixed_zoom; // 0x2C
    f32 cam_track_smooth; // 0x30
    f32 cam_zoom_rate; // 0x34
    f32 cam_max_depth; // 0x38
    f32 x3C; // 0x3C
    f32 pausecam_zpos_min; // 0x40
    f32 pausecam_zpos_init; // 0x44
    f32 pausecam_zpos_max; // 0x48
    f32 cam_angle_up; // 0x4C
    f32 cam_angle_down; // 0x50
    f32 cam_angle_left; // 0x54
    f32 cam_angle_right; // 0x58
    Vec fixed_cam_pos; // 0x5C - 0x64
    f32 fixed_cam_fov; // 0x68
    f32 fixed_cam_vert_angle; // 0x6C
    f32 fixed_cam_horz_angle; // 0x70
} StageCameraInfo;

typedef struct _StageBlastZone {
    f32 left; // 0x74
    f32 right; // 0x78
    f32 top; // 0x7C
    f32 bottom; // 0x80
} StageBlastZone;

typedef struct _StageAnim {
    struct _HSD_Joint* joint;
    struct _HSD_AnimJoint** anims;
} StageAnim;

typedef struct _StageInfo {
    StageCameraInfo cam_info; // 0x00 - 0x70
    StageBlastZone blast_zone; // 0x74 - 0x80

    u32 x84; // 0x84

    s32 internal_stage_id; // 0x88

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
    BOOL (*x178)(s32);
    void* x17C;
    struct _HSD_GObj* x180[4];
    u8 x190_pad[0x280 - 0x190];
    struct _HSD_JObj* x280[261];
    void* x694[4];
    void* x6A4;
    struct {
        s32 unk0;
        s32 unk4;
    }** x6A8;
    void* x6AC;
    struct _UnkStage6B0* x6B0;
    u32* x6B4;
    void* x6B8;
    void* x6BC;
    void* x6C0;
    void* x6C4;
    void* x6C8;
    StageAnim* x6CC;
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

typedef struct {
    void (*callback0)(struct _HSD_GObj*);
    s32 (*callback1)();
    void (*callback2)(struct _HSD_GObj*);
    void (*callback3)();
    u32 flags;
} StageCallbacks;

typedef struct _StageData {
    u32 flags1;
    StageCallbacks* callbacks;
    char* data1;
    void (*callback0)(void);
    void (*callback1)(s32);
    void (*callback2)(void);
    void (*callback3)(void);
    s32 (*callback4)();
    BOOL (*callback5)(s32);
    s32 (*callback6)(Vec*, s32, struct _HSD_JObj*);
    u32 flags2;
    S16Vec* x2C;
    s32 x30; // size of x2C array
} StageData;

typedef struct _StructPairWithStageID {
    s32 stage_id;
    s32 list_idx;
} StructPairWithStageID;

typedef struct _Map {
    int x0;                 // 0x0
    struct _HSD_GObj* gobj; // 0x4
    void (*x8_callback)(struct _HSD_GObj*); // 0x8
    void (*xC_callback)(struct _HSD_GObj*); // 0xC
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

    int map_id; // 0x14
    struct _HSD_GObj* x18; // 0x18
    void (*x1C_callback)(struct _HSD_GObj*);
    s32 x20[8];
    u8 x40_pad[0xC4 - 0x40];
    s32 xC4;
    s32 xC8;
    s32 xCC;
    s32 xD0;
    u8 xD4_pad[0x218 - 0xD4];
} Map;

f32 Stage_GetCamBoundsLeftOffset();
f32 Stage_GetCamBoundsRightOffset();
f32 Stage_GetCamBoundsTopOffset();
f32 Stage_GetCamBoundsBottomOffset();
f32 Stage_GetCamPanAngleRadians();
f32 Stage_GetCamMaxDepth();
f32 Stage_GetCamZoomRate();
f32 Stage_GetCamInfoX20();
f32 Stage_GetCamInfoX24();
f32 Stage_GetCamFixedZoom();
f32 Stage_GetCamTrackRatio();
f32 Stage_GetCamTrackSmooth();
f32 Stage_GetBlastZoneRightOffset();
f32 Stage_GetBlastZoneLeftOffset();
f32 Stage_GetBlastZoneTopOffset();
f32 Stage_GetBlastZoneBottomOffset();
f32 Stage_CalcUnkCamY();
f32 Stage_CalcUnkCamYBounds();
void Stage_UnkSetVec3TCam_Offset(Vec* vec3);
f32 Stage_GetPauseCamZPosMin();
f32 Stage_GetPauseCamZPosInit();
f32 Stage_GetPauseCamZPosMax();
f32 Stage_GetCamAngleRadiansUp();
f32 Stage_GetCamAngleRadiansDown();
f32 Stage_GetCamAngleRadiansLeft();
f32 Stage_GetCamAngleRadiansRight();
void Stage_80224CAC(Vec* arg0);
void Stage_SetVecToFixedCamPos(Vec* arg0);
f32 Stage_GetCamFixedFov();
BOOL Stage_80224DC8(s32 arg);
void Stage_80224E38(Vec* arg0, s32 arg1);
void Stage_80224E64(s32 arg0, Vec* arg_vec);
s32 Stage_80224FDC(Vec* arg0);
s32 Stage_80225074(s32 arg0);
s32 Stage_80225194();
s32 Stage_8022519C(s32 idx);
s32 Stage_802251B4(s32 idx, s32 arg1);
void Stage_802251E8(s32 idx, s32* unused);
void Stage_8022524C();
void Stage_80225298();
void Stage_802252E4(s32 idx, s32 unused);
void Stage_8022532C(s32 idx, s32 arg1);

#endif
