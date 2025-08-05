#ifndef MELEE_LB_TYPES_H
#define MELEE_LB_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "lb/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <dolphin/card.h>
#include <dolphin/mtx.h>

struct DynamicsData {
    /* +0 */ HSD_JObj* jobj;
    /* +4 */ u8 _4[0x90 - 0x4];
    /* +90 */ struct DynamicsData* next;
};

struct DynamicsDesc {
    /* +0 */ struct DynamicsData* data;
    /* +4 */ unsigned int count;
    /* +8 */ Vec3 pos;
};

struct BoneDynamicsDesc {
    enum_t bone_id;
    DynamicsDesc dyn_desc;
};

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
    /* +43 */ union {
        /* +43 */ u8 x43;
        struct {
            /* +43:0 */ u8 x43_b0 : 1;
            /* +43:1 */ u8 x43_b1 : 1;
            /* +43:2 */ u8 x43_b2 : 1;
            /* +43:3 */ u8 x43_b3 : 1;
            /* +43:4 */ u8 x43_b4 : 1;
            /* +43:5 */ u8 x43_b5 : 1;
            /* +43:6 */ u8 x43_b6 : 1;
            /* +43:7 */ u8 x43_b7 : 1;
        };
    };
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
    int bone_idx;      // 0x40
    HurtHeight height; // 0x44. 0 = low, 1 = mid, 2 = high
    u32 is_grabbable;  // 0x48 (might be flags)
};

STATIC_ASSERT(sizeof(HurtCapsule) == 0x4C);

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
    union {
        struct {
            u8 b0 : 1;
            u8 b1234 : 4;
            u8 b5 : 1;
            u8 b6 : 1;
            u8 b7 : 1;
        };
        u8 raw;
    };
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
    /* fp+750 */ s32 x60;
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
            /* fp+80C */ float x11C_f32;
            /* fp+810 */ float x120_f32;
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

#endif
