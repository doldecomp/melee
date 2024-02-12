#ifndef MELEE_LB_TYPES_H
#define MELEE_LB_TYPES_H

#include <platform.h>
#include "lb/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct lb_UnkAnimStruct {
    UNK_T x0_data;
    size_t x4_size;
};

struct HitResult {
    HSD_JObj* bone;

    /// Follows attach bone position if toggled OFF
    u8 skip_update_pos : 1;

    Vec3 pos;
    Vec3 offset;
    f32 size;
};

struct HitVictim {
    UNK_T victim;
    uint x4;
};

struct HitCapsule {
    /// @at{0} @sz{4}
    HitCapsuleState state;

    int x4;
    int x8;
    float damage;

    /// @at{10} @sz{C}
    /// The offset of point @e b of the capsule.
    Vec3 b_offset;

    /// @at{1C} @sz{4}
    /// The scale of the capsule.
    f32 scl;

    int kb_angle;

    int x24;
    int x28;
    int x2C;

    /// @at{30} @sz{4}
    HitElement element;

    char unk_34[0x38 - 0x34];

    /// @at{38} @sz{4}
    int sfx_severity;

    /// @at{3C} @sz{4}
    enum_t sfx_kind;

    u8 x40_b0 : 1;
    u8 x40_b1 : 1;
    u8 x40_b2 : 1;
    u8 x40_b3 : 1;
    u8 x40_b4 : 1;
    u8 x40_b5 : 1;
    u8 x40_b6 : 1;
    u8 x40_b7 : 1;
    char unk_41[0x42 - 0x41];
    u8 x42_b0 : 1;
    u8 x42_b1 : 1;
    u8 x42_b2 : 1;
    u8 x42_b3 : 1;
    u8 x42_b4 : 1;
    u8 x42_b5 : 1;
    u8 x42_b6 : 1;
    u8 x42_b7 : 1;
    union {
        u8 x43;
        struct {
            u8 x43_b0 : 1;
            u8 x43_b1 : 1;
            u8 x43_b2 : 1;
            u8 x43_b3 : 1;
            u8 x43_b4 : 1;
            u8 x43_b5 : 1;
            u8 x43_b6 : 1;
            u8 x43_b7 : 1;
        };
    };
    u8 x44;
    u8 x45;
    char unk_46[0x4C - 0x46];
    Vec3 x4C;
    Vec3 x58;
    Vec3 x64;
    f32 x70;
    /// @at{74} @sz{60}
    HitVictim victims_1[12];
    /// @at{D4} @sz{60}
    HitVictim victims_2[12];
    // @at{134}
    union {
        HSD_GObj* owner;
        u8 hit_grabbed_victim_only : 1;
    };
};

struct HurtCapsule {
    /// @at{0} @sz{4}
    Tangibility tangibility;

    /// @at{4} @sz{C}
    /// The offset of point @e a of the capsule.
    Vec3 a_offset;

    /// @at{10} @sz{C}
    /// The offset of point @e b of the capsule.
    Vec3 b_offset;

    /// @at{1C} @sz{4}
    /// The scale of the capsule.
    f32 scl;

    HSD_JObj* bone; // 0x20
    u8 skip_update_pos : 1;
    u8 x24_b1 : 1; // 0x24 0x40
    u8 x24_b2 : 1; // 0x24 0x20
    u8 x24_b3 : 1; // 0x24 0x10
    u8 x24_b4 : 1; // 0x24 0x08
    u8 x24_b5 : 1; // 0x24 0x04
    u8 x24_b6 : 1; // 0x24 0x02
    u8 x24_b7 : 1; // 0x24 0x01

    /// @at{28} @sz{C}
    /// The position of point @e a of the capsule.
    Vec3 a_pos;

    /// @at{28} @sz{C}
    /// The position of point @e b of the capsule.
    Vec3 b_pos;

    int bone_idx;      // 0x40
    enum_t kind;       // 0x44. 0 = low, 1 = mid, 2 = high
    bool is_grabbable; // 0x48
};

struct ReflectDesc {
    u32 x0_bone_id;
    s32 x4_max_damage;
    Vec3 x8_offset;
    f32 x14_size;
    f32 x18_damage_mul;
    f32 x1C_speed_mul;

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
    f32 radius;
    f32 dmg_mul;
    f32 vel_mul;
    u8 flags : 8;
};

#endif
