#ifndef MELEE_LB_TYPES_H
#define MELEE_LB_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "lb/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <dolphin/card.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct HitResult {
    HSD_JObj* bone;

    /// Follows attach bone position if toggled OFF
    u8 skip_update_pos : 1;

    Vec3 pos;
    Vec3 offset;
    float size;
};

struct HitVictim {
    UNK_T victim;
    u32 x4;
};

struct HitCapsule {
    /*  +0 */ HitCapsuleState state;
    /*  +4 */ u32 x4;
    /*  +8 */ u32 unk_count;
    /*  +C */ float damage;
    /* +10 */ Vec3 b_offset;
    /* +1C */ float scale;
    /* +20 */ int kb_angle;
    /* +24 */ u32 x24;
    /* +28 */ u32 x28;
    /* +2C */ u32 x2C;
    /* +30 */ u32 element;
    /* +34 */ int x34;
    /* +38 */ int sfx_severity;
    /* +3C */ enum_t sfx_kind;
    /* +40 */ u16 x40_b0 : 1;
    /* +40 */ u16 x40_b1 : 1;
    /* +40 */ u16 x40_b2 : 1;
    /* +40 */ u16 x40_b3 : 1;
    /* +40 */ u16 x40_b4 : 8;
    /* +41:4 */ u16 x41_b4 : 1;
    /* +41:5 */ u16 x41_b5 : 1;
    /* +41:6 */ u16 x41_b6 : 1;
    /* +41:7 */ u16 x41_b7 : 1;
    /* +42:0 */ u8 x42_b0 : 1;
    /* +42:1 */ u8 x42_b1 : 1;
    /* +42:2 */ u8 x42_b2 : 1;
    /* +42:3 */ u8 x42_b3 : 1;
    /* +42:4 */ u8 x42_b4 : 1;
    /* +42:5 */ u8 x42_b5 : 1;
    /* +42:6 */ u8 x42_b6 : 1;
    /* +42:7 */ u8 x42_b7 : 1;
    /* +43:0 */ u8 x43_b0 : 1;
    /* +43:1 */ u8 x43_b1 : 1;
    /* +43:2 */ u8 x43_b2 : 1;
    /* +43:3 */ u8 x43_b3 : 1;
    /* +43:4 */ u8 x43_b4 : 1;
    /* +43:5 */ u8 x43_b5 : 1;
    /* +43:6 */ u8 x43_b6 : 1;
    /* +43:7 */ u8 x43_b7 : 1;
    /* +44 */ u8 x44; // victims_1 count
    /* +45 */ u8 x45; // victims_2 count
    /* +46 */ u8 x46[0x48 - 0x46];
    /* +48 */ HSD_JObj* jobj;
    /* +4C */ Vec3 x4C;
    /* +58 */ Vec3 x58;
    /* +64 */ Vec3 hurt_coll_pos;
    /* +70 */ float coll_distance;
    /* +74 */ HitVictim victims_1[12];
    /* +D4 */ HitVictim victims_2[12];
    /* +134 */ union {
        HSD_GObj* owner;
        u8 hit_grabbed_victim_only : 1;
    };
};
STATIC_ASSERT(sizeof(HitCapsule) == 0x138);

struct HurtCapsule {
    HurtCapsuleState state;
    Vec3 a_offset;
    Vec3 b_offset;
    float scale;
    HSD_JObj* bone; // 0x20
    u8 skip_update_pos : 1;
    u8 x24_b1 : 1; // 0x24 0x40
    u8 x24_b2 : 1; // 0x24 0x20
    u8 x24_b3 : 1; // 0x24 0x10
    u8 x24_b4 : 1; // 0x24 0x08
    u8 x24_b5 : 1; // 0x24 0x04
    u8 x24_b6 : 1; // 0x24 0x02
    u8 x24_b7 : 1; // 0x24 0x01
    Vec3 a_pos;
    Vec3 b_pos;
    int bone_idx; // 0x40
};

struct FighterHurtCapsule {
    HurtCapsule capsule;
    HurtHeight height; // 0x44. 0 = low, 1 = mid, 2 = high
    bool is_grabbable; // 0x48
};

STATIC_ASSERT(sizeof(FighterHurtCapsule) == 0x4C);

struct ReflectDesc {
    u32 x0_bone_id;
    s32 x4_max_damage;
    Vec3 x8_offset;
    float x14_size;
    float x18_damage_mul;
    float x1C_speed_mul;

    /// @remarks Setting this to 1 causes the reflector to skip ownership
    /// change
    u8 x20_behavior;
};

struct AbsorbDesc {
    /*  +0 */ int x0_bone_id;
    /*  +4 */ Vec3 x4_offset;
    /* +10 */ float x10_size;
};

struct ShieldDesc {
    int bone;
    Vec3 pos;
    float radius;
    float dmg_mul;
    float vel_mul;
    u8 flags : 8;
};

struct lbRefract_CallbackData {
    s32 unk0;        // x00
    s32 unk1;        // x04
    s32 unk2;        // x08
    s32 unk3;        // x08
    s32 unk4;        // x10
    s32 unk5;        // x14
    void* callback0; // x1C
    void* callback1; // x20
};

typedef struct _ECBFlagStruct {
    u8 b0 : 1;
    u8 b1234 : 4;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} ECBFlagStruct;

typedef struct SurfaceData {
    int index;
    u32 unk;
    Vec3 normal;
} SurfaceData;

typedef struct _itECB {
    f32 top;
    f32 bottom;
    f32 right;
    f32 left;
} itECB;

typedef struct _ftECB {
    Vec2 top;
    Vec2 bottom;
    Vec2 right;
    Vec2 left;
} ftECB;

struct CollData {
    /* fp+6F0 */ HSD_GObj* x0_gobj;
    /* fp+6F4 */ Vec3 cur_topn;
    /* fp+700 */ Vec3 cur_topn_correct;
    /* fp+70C */ Vec3 prev_topn;
    /* fp+718 */ Vec3 x28_vec;
    /* fp+724 */ ECBFlagStruct x34_flags;
    /* fp+725 */ ECBFlagStruct x35_flags;
    /* fp+726 */ s16 x36;
    /* fp+728 */ s32 x38;
    /* fp+72C */ s32 x3C;
    /* fp+730 */ int ledge_id_unk0;
    /* fp+734 */ int ledge_id_unk1;
    /* fp+738 */ u32 x48;
    /* fp+73C */ u32 x4C;
    /* fp+740 */ float x50;
    /* fp+744 */ float x54;
    /* fp+748 */ float x58;
    /* fp+74C */ float x5C;
    /* fp+750 */ float x60;
    /* fp+754 */ ftECB x64_ecb;
    /* fp+774 */ ftECB x84_ecb;
    /* fp+794 */ ftECB xA4_ecbCurrCorrect;
    /* fp+7B4 */ ftECB xC4_ecb;
    /* fp+7D4 */ ftECB xE4_ecb;
    /// @todo this is the start of a substruct with size 0x2C
    /* fp+7F4 */ s32 x104;
    /* fp+7F8 */ union {
        /* fp+7F8 */ struct {
            /* fp+7F8 */ HSD_JObj* x108_joint;
            /* fp+7FC */ HSD_JObj* x10C_joint[6];
        };
        /* fp+7F8 */ struct {
            /* fp+7F8 */ float x108_f32;
            /* fp+7FC */ float x10C_f32;
            /* fp+800 */ float x110_f32;
            /* fp+804 */ float x114_f32;
            /* fp+808 */ float x118_f32;
        };
    };
    /* fp+814 */ float x124;
    /* fp+818 */ float x128;
    /* fp+81C */ float x12C;
    /* fp+820 */ u32 x130_flags;
    /* fp+824 */ s32 env_flags;
    /* fp+828 */ s32 prev_env_flags;
    /* fp+82C */ s32 x13C;
    /* fp+830 */ Vec3 x140;
    /* fp+83C */ SurfaceData floor;
    /* fp+850 */ SurfaceData right_wall;
    /* fp+864 */ SurfaceData left_wall;
    /* fp+878 */ SurfaceData ceiling;
};

struct HSD_AllocEntry {
    struct HSD_AllocEntry* next;
    u32* addr;
    size_t size;
};

struct PreloadCacheSceneEntry {
    u32 char_id;
    u8 color;
    u8 x5;
};

struct PreloadEntry {
    s8 state;
    s8 type;
    s8 heap;
    s8 load_state;
    u8 unknown004;
    u8 field5_0x5;
    s16 entry_num;
    s16 load_score;
    u8 field8_0xa;
    u8 field9_0xb;
    u32 size;
    HSD_AllocEntry* raw_data;
    HSD_AllocEntry* archive;
    s32 effect_index;
};

// TODO: this struct might need to be smaller,
// based on the number of iters in the struct-copy code
// emitted by e.g. lbDvd_80018CF4
struct PreloadCacheScene {
    u32 is_heap_persistent[2];
    struct GameCache {
        u8 major_id;
        u8 field2_0x9;
        u8 field3_0xa;
        u8 field4_0xb;
        u32 stage_id;
        PreloadCacheSceneEntry entries[8];
    } game_cache;
    s32 major_scene_changes;
};

struct PreloadCache {
    s32 persistent_heaps;
    PreloadCacheScene scene;
    PreloadCacheScene new_scene;
    PreloadEntry entries[80];
    s32 persistent_heap;
    int preloaded;
    UNK_T x974;
};

struct lb_800138D8_t {
    /*  +0 */ char pad_0[0x11];
    /* +11 */ s8 x11;
    /* +12 */ s8 x12;
    /* +13 */ char pad_13[0x18 - 0x13];
    /* +18 */ int x18;
};

struct lb_80432A68_38_t {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
};
STATIC_ASSERT(sizeof(struct lb_80432A68_38_t) == 0x8);

struct lb_80432A68_t {
    /* 0x000 */ UNK_T work_area;
    /* 0x004 */ UNK_T lib_area;
    /* 0x008 */ int chan;
    /* 0x00C */ UNK_T unk_C;
    /* 0x010 */ const char* unk_10;
    /* 0x014 */ const char* unk_14;
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ s32 unk_1C;
    /* 0x020 */ UNK_T unk_20;
    /* 0x024 */ int* unk_24;
    /* 0x028 */ int* unk_28;
    /* 0x02C */ char x2C[2];
    /* 0x02C */ char x2E;
    /* 0x02C */ char x2F[4];
    /* 0x034 */ s32 unk_34;
    /* 0x038 */ struct lb_80432A68_38_t unk_38[9];
    /* 0x080 */ s32 unk_80;
    /* 0x084 */ s32 memsize;
    /* 0x088 */ s32 sectorsize;
    /* 0x08C */ s32 unused_bytes;
    /* 0x090 */ s32 unused_files;
    /* 0x094 */ CARDFileInfo file_info;
    /* 0x0A8 */ s32 unk_A8;
    /* 0x098 */ u8 pad_AC[0xD0 - 0xAC]; /* maybe part of unk_80[0x123]? */
    /* 0x0A8 */ int xD0[9];
    /* 0x0A8 */ volatile int xF4[9];
    /* 0x098 */ u8
        pad_500[0x50C - 0xF4 - 9 * 4]; /* maybe part of unk_80[0x123]? */
    /* 0x50C */ void (*x50C)(int);
    /* 0x510 */ struct CardTask {
        int x0;
        int x4;
        UNK_T x8;
        char* xC;
        char x10[0x20];
        u8 x18;
        char x19[7];
        u8 unk20[0x1C];
    } task_array[11];
    /* 0x8AC */ int x8AC;
}; /* size = 0x8B0 */
STATIC_ASSERT(sizeof(struct lb_80432A68_t) == 0x8B0);

struct ColorOverlay_UnkInner {
    /*  +0 */ int x0;
    /*  +0 */ u8 x4[0x7B - 0x4];
    /* +7B */ u8 x7B;
};

union ColorOverlay_x8_t {
    GXColor light_color;
    struct {
        s32 unk : 6;
        s32 x : 13;
        s32 yz : 13;
    } light_rot1;
    struct {
        u32 x0_0 : 1;
        u32 x0_1 : 1;
        u32 x0_2 : 1;
        u32 x0_3 : 1;
        u32 x0_4 : 1;
        u32 x0_5 : 1;
        u32 light_enable : 1;
        u32 x0_7 : 1;
        s32 x : 12;
        s32 yz : 12;
    } light_rot2;
    struct {
        u32 unk : 6;
        u32 timer : 26;
    } unk;
};
STATIC_ASSERT(sizeof(union ColorOverlay_x8_t) == 0x4);

struct ColorOverlay {
    s32 x0_timer; // 0x0
    s32 x4_pri;   // 0x4  this colanims priority, lower = will persist
    union ColorOverlay_x8_t* x8_ptr1; // 0x8
    s32 xC_loop;                      // 0xc
    s32* x10_ptr2;                    // 0x10
    s32 x14;                          // 0x14
    s32* x18_alloc;                   // 0x18
    s32 x1c;                          // 0x1c
    s32 x20;                          // 0x20
    s32 x24;                          // 0x24
    union {
        enum_t i;
        struct ColorOverlay_UnkInner* ptr;
    } x28_colanim;            // 0x28, id for the color animation in effect
    GXColor x2C_hex;          // 0x2C
    f32 x30_color_red;        // 0x30
    f32 x34_color_green;      // 0x34
    f32 x38_color_blue;       // 0x38
    f32 x3C_color_alpha;      // 0x3C
    f32 x40_colorblend_red;   // 0x40
    f32 x44_colorblend_green; // 0x44
    f32 x48_colorblend_blue;  // 0x48
    f32 x4C_colorblend_alpha; // 0x4C
    GXColor x50_light_color;  // 0x50
    f32 x54_light_red;        // 0x54
    f32 x58_light_green;      // 0x58
    f32 x5C_light_blue;       // 0x5C
    f32 x60_light_alpha;      // 0x60
    f32 x64_lightblend_red;   // 0x64
    f32 x68_lightblend_green; // 0x68
    f32 x6C_lightblend_blue;  // 0x6c
    f32 x70_lightblend_alpha; // 0x70
    f32 x74_light_rot_x;      // 0x74
    f32 x78_light_rot_yz;     // 0x78
    u8 x7C_color_enable : 1;  // 0x7c, 0x80
    u8 x7C_flag2 : 1;         // 0x7c, 0x40
    u8 x7C_light_enable : 1;  // 0x7c, 0x20
    u8 x7C_flag4 : 1;         // 0x7c, 0x10
    u8 x7C_flag5 : 1;         // 0x7c, 0x08
    u8 x7C_flag6 : 1;         // 0x7c, 0x04
    u8 x7C_flag7 : 1;         // 0x7c, 0x02
    u8 x7C_flag8 : 1;         // 0x7c, 0x01
};
STATIC_ASSERT(sizeof(struct ColorOverlay) == 0x80);

struct lb_80011A50_t {
    /*  +0 */ u8 x0;
    /*  +1 */ u8 x1;
    /*  +2 */ s8 x2;
    /*  +3 */ s8 x3;
    /*  +4 */ Vec3 x4;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ f32 unk_scale;
    /* +24 */ f32 x24;
    /* +28 */ int unk_count0;
    /* +2C */ f32 unk_angle_float;
    /* +30 */ int unk_angle_int;
    /* +34 */ struct lb_80011A50_t* next;
};

struct lb_80014638_arg0_t {
    /*  +0 */ Vec3 x0;
    /*  +C */ Vec3 xC;
};
STATIC_ASSERT(sizeof(struct lb_80014638_arg0_t) == 0x18);

struct lb_80014638_arg1_t {
    /*  +0 */ float unk_x;
    /*  +4 */ float unk_y;
    /*  +8 */ Vec3 x8;
};
STATIC_ASSERT(sizeof(struct lb_80014638_arg1_t) == 0x14);

struct Fighter_804D653C_t {
    void* unk;
    u8 unk4;
    u8 unk5;
};
STATIC_ASSERT(sizeof(struct Fighter_804D653C_t) == 8);

struct lb_00F9_UnkDesc1Inner {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;  /* inferred */
    /* 0x08 */ s32 unk_8;  /* inferred */
    /* 0x0C */ s32 unk_C;  /* inferred */
    /* 0x10 */ s32 unk_10; /* inferred */
    /* 0x14 */ s32 unk_14; /* inferred */
    /* 0x18 */ f32 unk_18; /* inferred */
    /* 0x1C */ s32 unk_1C; /* inferred */
    /* 0x20 */ s32 unk_20; /* inferred */
    /* 0x24 */ f32 unk_24; /* inferred */
    /* 0x28 */ s32 unk_28; /* inferred */
    /* 0x2C */ s32 unk_2C; /* inferred */
    /* 0x30 */ s32 unk_30; /* inferred */
    /* 0x34 */ f32 unk_34; /* inferred */
    /* 0x38 */ f32 unk_38; /* inferred */
};
STATIC_ASSERT(sizeof(struct lb_00F9_UnkDesc1Inner) == 0x3C);

struct lb_00F9_UnkDesc1 {
    struct lb_00F9_UnkDesc1Inner array[2];
};

struct lb_00F9_UnkDesc0 {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ f32 unk_38;
    char pad_3C[0x78 - 0x3C];
    int unk_78;
    int unk_7C;
    int unk_80;
    f32 unk_84;
    f32 unk_88;
    f32 unk_8C;
};

struct ftDynamics_UnkDesc {
    HSD_JObj* jobj;
};

union PolymorphicDesc {
    u8 _[0x90];
    struct lb_00F9_UnkDesc0 lb_unk0;
    struct lb_00F9_UnkDesc1 lb_unk1;
    struct ftDynamics_UnkDesc ft_unk;
    struct AbsorbDesc absorb;
    struct HurtCapsule hurt;
};
STATIC_ASSERT(sizeof(union PolymorphicDesc) == 0x90);

struct DynamicsData {
    union PolymorphicDesc desc;
    /* 0x90 */ struct DynamicsData* next;
}; /* size = 0x94 */
STATIC_ASSERT(sizeof(struct DynamicsData) == 0x94);

struct DynamicsDesc {
    /* +0 */ struct DynamicsData* data;
    /* +4 */ unsigned int count;
    /* +8 */ Vec3 pos;
};

struct BoneDynamicsDesc {
    enum_t bone_id;
    DynamicsDesc dyn_desc;
};

struct lb_8000FD18_t {
    char pad_0[0x94];
};

struct lb_804D63A0_t {
    /* +0 */ char pad_0[0xBE00];
};
STATIC_ASSERT(sizeof(struct lb_804D63A0_t) == 0xBE00);

struct lb_804D63A8_t {
    /* +0 */ char pad_0[0x1C0];
};
STATIC_ASSERT(sizeof(struct lb_804D63A8_t) == 0x1C0);

struct lbColl_8000A10C_arg0_t {
    float x0;
    float x4;
    Vec3 x8;
    Vec3 x14;
};

struct CommandInfo {
    f32 timer;       // 0x00
    f32 frame_count; // 0x04
    union {
        u32* ptr[1]; ///< @todo Hack to match #Command_04
        union CmdUnion {
            struct {
                u32 code : 6;
                u32 value : 26;
            } Command_00;
            struct {
                u32 code : 6;
                u32 value : 26;
            } Command_02;
            struct {
                u32 code : 6;
                u32 value : 26;
            } Command_03;
            struct {
                u32 x;
            } Command_04_2;
            struct {
                union CmdUnion* ptr;
            } Command_05;
            struct {
                union CmdUnion* ptr;
            } Command_07;
            struct {
                u32 id : 6;
                u32 param_1 : 8;
                u32 param_2 : 18;
            } Command_09;
            struct {
                u32 code : 6;  ///< Bits 0~5
                u32 unk1 : 8;  ///< Bits 6~13
                u32 unk2 : 18; ///< Bits 14~31
            } unk0;
            struct {
                u32 code : 6; ///< Bits 0~5
                u32 unk0 : 2; ///< Bits 6~7
                u32 unk1 : 4; ///< Bits 8~11
                u32 unk2 : 1; ///< Bit 12
            } unk1;
            struct {
                u32 code : 6;     ///< Bits 0~5
                u32 hit_idx : 26; ///< Bits 6~31
            } unk2;
            struct {
                s32 unk0 : 7;  ///< Bits 0~6
                s32 unk1 : 25; ///< Bits 7~31
            } unk3;
            struct {
                u16 unk0 : 6; ///< Bits 0~5
                u16 unk1 : 8; ///< Bits 6~13
            } unk4;
            struct {
                s32 unk0 : 14; ///< Bits 0~13
                s32 unk1 : 18; ///< Bits 14~31
            } unk5;
            struct {
                u8 unk0 : 6; ///< Bits 0~5
                u8 unk1 : 1; ///< Bit 6
            } unk6;
            struct {
                u32 unk0 : 6;  ///< Bits 0~5
                u32 unk1 : 26; ///< Bits 6~31
            } unk7;            ///< #ftAction_80071998
            struct {
                int unk0;
            } unk8;
            struct {
                s32 unk0 : 6;
                s32 unk1 : 7;
                s32 unk2 : 7;
                u32 unk3 : 12;
            } part_anim;
            struct {
                s32 unk0 : 6;
                u32 unk1 : 13;
                u32 unk2 : 13;
            } unk9;
            struct {
                s32 unk0 : 6;
                u32 unk1 : 1;
                u32 unk2 : 12;
                u32 unk3 : 13;
            } unk10;
            struct {
                s32 unk0 : 6;
                u32 unk1 : 26;
            } unk11;
            struct {
                u32 unk0 : 6;
                u32 unk1 : 2;
                u32 unk2 : 10;
                u32 unk3 : 14;
            } unk12;
            struct {
                u32 unk0 : 6;
                u32 unk1 : 8;
                u32 unk2 : 18;
            } unk13;
            struct {
                u32 unk0 : 6;
                u32 unk1 : 8;
            } unk14;
            struct {
                u32 unk0 : 6;
                u32 unk1 : 26;
            } unk15; ///< #ftAction_80072B14
            struct {
                u32 unk0 : 6;
                s32 unk3 : 1;
                s32 unk4 : 25;
            } unk16; ///< #ftAction_80072B3C
            struct {
                u32 unk0 : 6;
                s32 unk1 : 26;
            } unk17; ///< #ftAction_80072B94
            struct {
                u32 unk0 : 6;
                s32 damage_amount : 26;
            } unk18; ///< #ftAction_80072BF4
            struct {
                u32 unk0 : 6;
                u32 unk1 : 26;
            } unk19; ///< #ftAction_80072C6C
            struct {
                u32 unk0 : 6;
                u32 unk1 : 26;
            } unk20; ///< #ftAction_80072CB0
            struct {
                u32 unk0 : 6;
                u32 unk1 : 1;
                u32 unk2 : 8;
            } unk21; ///< #ftAction_800730B8
            struct {
                u32 code : 6;
                u32 idx : 3;
                u32 value : 23;
            } set_hitbox_damage; ///< #ftAction_8007162C
            struct {
                u32 code : 6;
                u32 idx : 3;
                u32 value : 23;
            } set_hitbox_scale; ///< #ftAction_8007169C
            struct {
                u32 code : 6;
                u32 idx : 24;
                u32 type : 1;
                u32 value : 1;
            } unk22; ///< #ftAction_80071708
            struct {
                u32 code : 6;
                u32 idx : 2;
                u32 value : 24;
            } set_cmd_var; ///< #ftAction_80071708
            struct {
                u32 code : 6;
                u32 bone_idx : 8;
                u32 state : 18;
            } set_hurt_state; ///< #ftAction_80071A9C
            struct {
                u32 code : 6;
                u32 disabled : 26;
            } unk23; ///< #ftAction_80071AE8
            struct {
                u32 code : 6;
                u32 unk0 : 26;
            } unk24; ///< #ftAction_80071B28
            struct {
                u32 code : 6;
                s32 unk0 : 7;
                s32 unk1 : 19;
            } unk25; ///< #ftAction_80071D40
            struct {
                u32 code : 6;
                u32 idx : 3;
                u32 unk0 : 23;
            } unk26_0; ///< #ftAction_80071E04 command 0
            struct {
                u32 unk0 : 9;
                u32 hit_x24 : 9;
                u32 hit_x28 : 9;
            } unk26_1; ///< #ftAction_80071E04 command 1
            struct {
                u32 hit_x2C : 9;
                u32 element : 4;
                u32 sfx_severity : 3;
                u32 sfx_kind : 4;
            } unk26_2; ///< #ftAction_80071E04 command 2
            struct {
                u32 code : 6;
                u32 value : 26;
            } unk27; ///< #ftAction_80071F34
            struct {
                u32 code : 6;
                u32 value : 26;
            } unk28; ///< #ftAction_80071F78
            struct {
                u32 code : 6;
                u32 value : 26;
            } unk29; ///< #ftAction_80071FA0
            struct {
                u32 code : 6;
                u32 b : 1;
                s32 i0 : 7;
                s32 i1 : 7;
                s32 f : 11;
            } unk30; ///< #ftAction_800726F4
            struct {
                u32 code : 6;
                u32 unk0 : 10;
                u32 unk1 : 16;
            } unk31; ///< #ftAction_80073008
            struct {
                u32 code : 6;
                u32 unk0 : 13;
                u32 unk1 : 13;
            } unk32; ///< #ftAction_80073008
            struct {
                u32 code : 6;
                u32 unk0 : 13;
                u32 unk1 : 13;
            } unk33; ///< #it_8027990C
            struct {
                u32 opcode : 6;
                u32 boneId : 8;
                u32 useCommonBoneIDs : 1;
                u32 destroyOnStateChange : 1;
                u32 useUnkBone : 1;
                u32 unk1 : 15;
            } test1;
            struct {
                u32 gfxID : 16;
                u32 unkFloat : 16;
            } test2;
            struct {
                s16 offsetZ : 16;
                s16 offsetY : 16;
            } test3;
            struct {
                s16 offsetX : 16;
                u16 rangeZ : 16;
            } test4;
            struct {
                u16 rangeY : 16;
                u16 rangeX : 16;
            } test5;
        }* u;
    };
    u32 loop_count; // 0x0C
    union CmdUnion*
        event_return[3]; // 0x10 - Array Size is purely made-up for now
    u32 loop_count_dup;  // 0x14
    u32 unk_x18;         // 0x18
};

struct LbShadow {
    u8 x0_b0 : 1;
    u8 x0_b1 : 1;
    u8 x0_b2 : 1;
    u8 x0_b3 : 1;
    u8 x0_b4 : 1;
    u8 x0_b5 : 1;
    u8 x0_b6 : 1;
    u8 x0_b7 : 1;
    HSD_Shadow* shadow;
};

#endif
