#ifndef MELEE_GR_TYPES_H
#define MELEE_GR_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include <melee/cm/forward.h>
#include <melee/gr/forward.h>
#include <melee/it/forward.h>
#include <melee/lb/forward.h>
#include <melee/sc/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct StageBlastZone {
    f32 left;   // 0x74
    f32 right;  // 0x78
    f32 top;    // 0x7C
    f32 bottom; // 0x80
} StageBlastZone;

/// @remarks This struct is based in part on the datasheet however the info
///          there is likely incorrect as this doesn't quite match @c
///          grGroundParam.
typedef struct StageCameraInfo {
    StageBlastZone cam_bounds; // 0x00
    f32 cam_x_offset;          // 0x10
    f32 cam_y_offset;          // 0x14
    f32 cam_vertical_tilt;     // 0x18
    f32 cam_pan_degrees;       // 0x1C
    f32 x20;                   // 0x20
    f32 x24;                   // 0x24
    f32 cam_track_ratio;       // 0x28
    f32 cam_fixed_zoom;        // 0x2C
    f32 cam_track_smooth;      // 0x30
    f32 cam_zoom_rate;         // 0x34
    f32 cam_max_depth;         // 0x38
    f32 x3C;                   // 0x3C
    f32 pausecam_zpos_min;     // 0x40
    f32 pausecam_zpos_init;    // 0x44
    f32 pausecam_zpos_max;     // 0x48
    f32 cam_angle_up;          // 0x4C
    f32 cam_angle_down;        // 0x50
    f32 cam_angle_left;        // 0x54
    f32 cam_angle_right;       // 0x58
    Vec3 fixed_cam_pos;        // 0x5C - 0x64
    f32 fixed_cam_fov;         // 0x68
    f32 fixed_cam_vert_angle;  // 0x6C
    f32 fixed_cam_horz_angle;  // 0x70
} StageCameraInfo;

struct StageInfo {
    StageCameraInfo cam_info;  // 0x00 - 0x70
    StageBlastZone blast_zone; // 0x74 - 0x80

    u32 flags; // 0x84

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
    bool (*x90)(Vec3*, int);
    bool (*x94)(Vec3*, int);
    s32 x98;
    u32 x9C;
    u8 xA0[4];
    u8 xA4_pad[0x12C - 0xA4];
    HSD_GObj* x12C;
    Vec3 x130, x13C, x148, x154, x160, x16C;
    DynamicsDesc* (*x178)(int);
    bool (*x17C)(Vec3*, int, HSD_JObj*);
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
    int x6E4[2];
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
    HSD_GObj* x72C;
    Vec3 x730;
    f32 x73C;
    s32 x740;
    u8 x744_pad[0x748 - 0x744];
};

typedef struct StageCallbacks {
    /*  +0 */ void (*callback0)(HSD_GObj*); ///< initialization callback
    /*  +4 */ bool (*callback1)(HSD_GObj*);
    /*  +8 */ void (*callback2)(HSD_GObj*);
    /*  +C */ void (*callback3)(HSD_GObj*);
    /* +10 */ union {
        /* +10 */ u32 flags;
        struct {
            /* +10:0 */ u8 flags_b0 : 1;
            /* +10:1 */ u8 flags_b1 : 1;
            /* +10:2 */ u8 flags_b2 : 1;
            /* +10:3 */ u8 flags_b3 : 1;
            /* +10:4 */ u8 flags_b4 : 1;
            /* +10:5 */ u8 flags_b5 : 1;
            /* +10:6 */ u8 flags_b6 : 1;
            /* +10:7 */ u8 flags_b7 : 1;
        };
    };
} StageCallbacks;

typedef struct StageData {
    u32 flags1;
    StageCallbacks* callbacks;
    char* data1;
    void (*callback0)(void);
    void (*callback1)(int);
    void (*callback2)(void); ///< on load callback
    void (*callback3)(void); ///< on GO! callback
    bool (*callback4)(void);
    DynamicsDesc* (*callback5)(enum_t);
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
};

struct GroundVars_izumi {
    HSD_TObj* xC4;
    HSD_GObj* xC8;
    HSD_GObj* xCC;
    HSD_JObj* xD0;
    HSD_JObj* xD4;
    int xD8;
    float xDC;
};

struct GroundVars_izumi2 {
    HSD_JObj* xC4;
    HSD_JObj* xC8;
    int xCC;
    int xD0;
    int xD4;
    int xD8;
    float xDC;
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
};

struct GroundVars_flatzone {
    u8 xC4;
    u8 xC5;
    u8 xC6;
    u8 xC7;
    s16 xC8;
    s16 xCA;
    s16 xCC;
    s16 xCE;
    s32 xD0;
    s32 xD4;
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

struct GroundVars_flatzone2 {
    s32 xC4;
    f32 xC8;
    grDynamicAttr_UnkStruct* xCC;
    s32 xD0;
    s32 xD4;
};

struct grKongo_GroundVars {
    /* gp+C4 */ f32 xC4;
    /* gp+C8 */ f32 xC8;
    /* gp+CC */ f32 xCC;
    /* gp+D0 */ union {
        struct {
            void* keep;
        } taru;
    } u;
    /* gp+D4 */ f32 xD4;
    /* gp+D8 */ f32 xD8;
    /* gp+DC */ HSD_JObj* xDC;
    /* gp+E0 */ HSD_JObj* xE0;
    /* gp+E4 */ s16 xE4;
    /* gp+E6 */ s16 xE6;
    /* gp+E8 */ f32 xE8;
};

struct grKongo_GroundVars2 {
    HSD_Spline* xC4;
    f32 xC8;
    s16 xCC;
    s16 xCE;
    f32 xD0;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
};

/// @todo: Investigate if these extra structs could be
/// shared among stages/other things as more are decompiled.
struct grKongo_GroundVars3 {
    /* gp+C4 */ s16 xC4;
    /* gp+C6 */ s16 xC6;
    /* gp+C8 */ s16 xC8;
    /* gp+CA */ s16 xCA;
    HSD_JObj* xCC;
    HSD_JObj* xD0;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
};

struct grKraid_GroundVars {
    /*  + gp+C4 */ u8 x0;
    /*  + gp+C5 */ s8 x1;
    /*  + gp+C8 */ f32 x4;
    /*  + gp+CC */ f32 x8;
    /*  + gp+D0 */ f32 xC;
};

struct grCorneria_GroundVars {
    u32 xC4_b0 : 1;
    u32 xC4_b1 : 1;
    u32 xC8;
    u32 xCC;
    f32 xD0;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    f32 xEC;
    f32 xF0;
    f32 xF4;
    f32 xF8;
    u32 xFC;
    u32 x100;
    u32 x104;
    u32 x108;
    u32 x10C;
    u32 x110;
    f32 x114;
    u8 x118;
    u8 x119;
    u8 x11A;
    u8 x11B;
    u32 x11C;
    Item_GObj* x120;
    Item_GObj* x124;
    HSD_GObj* x128;
    HSD_JObj* x12C;
};

struct grIceMt_GroundVars {
    /* +0 gp+C4 */ char pad_0[0x14];
    /* +0 gp+D8 */ s16 xD8;
};

struct grStadium_GroundVars {
/* +0 gp+C4:0 */   u8 xC4_b0 : 1;
/* +0 gp+C4:1 */   u8 xC4_b1 : 1;
/* +0 gp+C8:0 */   u32 xC8;
/* +4 gp+CC   */   HSD_MObj* xCC;
/* +4 gp+D0   */   UnkArchiveStruct* xD0;
/* +4 gp+D4   */   float xD4;
/* +4 gp+D8   */   int xD8;
/* +4 gp+DC   */   s16 xDC;
/* +4 gp+DE   */   s16 xDE;
/* +4 gp+E0   */   s16 xE0;
/* +4 gp+E2   */   s16 xE2;
/* +4 gp+E4   */   HSD_GObj* xE4;
/* +4 gp+E8   */   HSD_GObj* xE8;
};

// Specific to the Pokemon Stadium jumbotron
struct grStadium_Display {
/* C4:0 */  u8 xC4_b0 : 1;
/* C4:1 */  u8 xC4_b1 : 1;
/* C8   */  HSD_TObj* xC8;
/* CC   */  HSD_MObj* xCC;
/* D0   */  HSD_ImageDesc* xD0;
/* D4   */  HSD_GObj* xD4; ///< Text display
/* D8   */  HSD_GObj* xD8; ///< Stage camera feed
/* DC   */  HSD_GObj* xDC; ///< Zoomed camera feed
/* E0   */  int xE0;
/* E4   */  s16 xE4;
/* E6   */  s16 xE6;
/* E8   */  s16 xE8;
/* EA   */  s16 xEA;
/* EC   */  s16 xEC;
/* EE   */  s16 xEE; ///< The focused player, or 99 if none
/* F0   */  s16 xF0;
/* F2   */  s16 xF2;
/* F4   */  CameraBox* xF4;
/* F8:0 */  u8 xF8_0 : 1;
/* F8:1 */  u8 xF8_1 : 1;
/* F8:2 */  u8 xF8_2 : 1;
};

// Unknown, but used for IDS:
// 6
// 9
// and possibly more
struct grStadium_type9_GroundVars {
/* C4:0 */  u8 xC4_b0 : 1;
/* C4:1 */  u8 xC4_b1 : 1;
/* C8   */  UnkGeneratorStruct* xC8;
/* CC   */  HSD_GObj* xCC_gobj;
/* D0   */  HSD_GObj* xD0_gobj;
/* D4   */  HSD_JObj* xD4_jobj;
};

struct grZebes_GroundVars {
    /*  +0 gp+C4:0 */ u8 x0_b0 : 1;
    /*  +4 gp+C8 */ UNK_T x4;
    /*  +8 gp+CC */ UNK_T x8;
    /*  +C gp+D0 */ Vec3 xC;
};

struct grOnett_GroundVars {
    /*  +0 gp+C4:0 */ u8 x0_b0 : 1;
};

struct grBigBlue_GroundVars {
    /*  +0 gp+C4:0 */ u8 x0_b0 : 1;
};

struct grLast_GroundVars {
    /* +0 gp+C4:0 */ u8 x0_b0 : 1;
};

struct Randall {
/* +0 gp+C4 */ s16 timer;
/* +4 gp+C8 */ HSD_JObj* jobj;
};

struct ShyGuys {
/* +0 gp+C4 */ s8 count;
/* +1 gp+C5 */ s8 pattern;
/* +4 gp+C8 */ int timer;
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
    Vec3 self_vel;
    Vec3 cur_pos;
    int x58;
    int x5C;
    int x60;
    int x64;
    int x68;
    int x6C;
    int x70;
    char pad_40[0xC4 - 0x74];

    union {

    /// @todo This union is named 'u', from assert statements
    union GroundVars {
        char pad_0[0x204 - 0xC4];
        struct grBigBlue_GroundVars bigblue;
        struct grCorneria_GroundVars corneria;
        struct GroundVars_flatzone flatzone;
        struct GroundVars_flatzone2 flatzone2;
        struct grIceMt_GroundVars icemt;
        struct GroundVars_izumi izumi;
        struct GroundVars_izumi2 izumi2;
        struct GroundVars_izumi3 izumi3;
        struct grKongo_GroundVars kongo;
        struct grKongo_GroundVars2 kongo2;
        struct grKongo_GroundVars3 kongo3;
        struct grKraid_GroundVars kraid;
        struct grLast_GroundVars last;
        struct grOnett_GroundVars onett;
        struct GroundVars_unk unk;
        struct grZebes_GroundVars zebes;
    } gv;

    /**
     * Union of Ground object subtypes
     *
     * A Ground object can be one of multiple subtypes. The toplevel Ground
     * object for the stage itself is a generic type, but uses different
     * subtypes for various stage hazards, graphics effects, backgrounds, etc.
     * used by the stage.
     *
     * Each index in a stage's StageCallbacks array may use a different subtype
     * of Ground object - but each callback in a single StageCallbacks struct
     * should operate on the same subtype.
     *
     * This is known from assert statements to contain at least the following
     * members:
     * - map
     *   - A generic member used for multiple stages - used in in Onett,
     *     RCruise, Home Run Contest, and more. Grep for `gp->u.map`
     *     to see lots of assert statements using it.
     * - scroll
     *   - Used for Rainbow Cruise
     * - taru
     *   - "Barrel", used in Kongo Jungle
     * - car, carnull
     *   - Used in Big Blue
     *
     * @todo The previous #Ground.gv union members should be moved here.
     */
    union {
        struct grStadium_GroundVars stadium;
        struct grStadium_type9_GroundVars stadium9;
        struct grStadium_Display display; ///< Pokemon Stadium jumbotron
        struct Randall randall;
        struct ShyGuys shyguys;
    } u;

    };
};
STATIC_ASSERT(sizeof(struct Ground) == 0x204);

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

struct UnkStageDat_x8_t {
    /*  +0 */ struct HSD_Joint* unk0;
    /*  +4 */ u8 _4[0x10 - 0x4];
    /* +10 */ HSD_CameraDescPerspective* x10;
    /* +14 */ UNK_T x14;
    /* +18 */ UNK_T x18;
    /* +1C */ HSD_FogDesc* x1C;
    /* +20 */ S16Vec3* unk20;
    /* +24 */ s32 unk24; // size of unk20 array
    /* +28 */ UNK_T x28;
    /* +2C */ s16* x2C;
    /* +30 */ int x30;
};

struct UnkStageDat {
    void* unk0;
    s32 unk4;

    struct UnkStageDat_x8_t* unk8;
    s32 unkC;

    HSD_Spline** unk10;
    s32 unk14;

    u8 x18_fill[0x20 - 0x18];

    void* unk20;
    s32 unk24;

    UnkStageDatInternal** unk28;
    s32 unk2C; // size
};
STATIC_ASSERT(sizeof(struct UnkStageDat_x8_t) == 0x34);

struct UnkArchiveStruct {
    HSD_Archive* unk0;
    UnkStageDat* unk4;
    u32 unk8;
};

#endif
