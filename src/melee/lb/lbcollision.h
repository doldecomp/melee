#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include "ft/forward.h"
#include "lb/forward.h"

#include "dolphin/mtx/types.h"

#include <placeholder.h>
#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

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
    UNK_T x4;
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
    int x70;
    /// @at{74} @sz{60}
    HitVictim victims_1[12];
    /// @at{D4} @sz{60}
    HitVictim victims_2[12];

    HSD_GObj* owner;
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

void lbColl_JObjSetupMatrix(HSD_JObj*);
bool lbColl_80008248(HitCapsule*, HurtCapsule*, Mtx, f32, f32, f32);
void lbColl_80008440(HitCapsule*);
void lbColl_80008434(HitCapsule*);
bool lbColl_8000ACFC(UNK_T, HitCapsule*);
bool lbColl_80008688(HitCapsule*, enum_t, Fighter*);
void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst);
UNK_RET lbColl_80008820(UNK_PARAMS);
int lbColl_80005BB0(HitCapsule*, int);
bool lbColl_80007ECC(HitCapsule*, HurtCapsule*, Mtx, f32 hit_scl_y,
                     f32 hurt_scl_y, f32 hurt_pos_z);
bool lbColl_8000805C(HitCapsule*, HurtCapsule*, UNK_T, s32, f32, f32, f32);
bool lbColl_80007BCC(HitCapsule*, HitResult* shield_hit, unk_t, s32, f32, f32,
                     f32);
bool lbColl_80007AFC(HitCapsule*, HitCapsule*, f32, f32);
void lbColl_80007DD8(HitCapsule*, HitResult*, Mtx, unk_t, unk_t, f32);
void lbColl_80008D30(HitCapsule*, int);
void lbColl_80008428(HitCapsule*);
bool lbColl_80005C44(Vec3*, Vec3*, Vec3*, Vec3*, f32, f32);
f32 lbColl_80005EBC(Vec3*, Vec3*, Vec3*, f32*);
f32 lbColl_80005FC0(Vec3*, Vec3*, Vec3*, f32*);
bool lbColl_80006094(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32);
bool lbColl_800067F8(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32, f32);
bool lbColl_80006E58(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Mtx, Vec3*, f32,
                     f32 scl, f32);

/// @param[out] angle
void lbColl_800077A0(Vec3*, Mtx, Vec3*, Vec3*, Vec3*, Vec3*, f32* angle, f32,
                     f32);

UNK_RET lbColl_80007B78(Mtx, Mtx, f32, f32);
void lbColl_800083C4(HurtCapsule*);
UNK_RET lbColl_800089B8(UNK_PARAMS);
UNK_RET lbColl_80008A5C(UNK_PARAMS);
UNK_RET lbColl_80008DA4(UNK_PARAMS);
UNK_RET lbColl_80008FC8(UNK_PARAMS);
void lbColl_800096B4(MtxPtr, UNK_T, UNK_T, UNK_T, UNK_T, f32);
UNK_RET lbColl_80009DD4(UNK_PARAMS);
UNK_RET lbColl_80009F54(UNK_PARAMS);
UNK_RET lbColl_8000A044(UNK_PARAMS);
UNK_RET lbColl_8000A10C(UNK_PARAMS);
UNK_RET lbColl_8000A1A8(UNK_PARAMS);
void lbColl_8000A244(HurtCapsule*, u32, Mtx, f32);
UNK_RET lbColl_8000A460(UNK_PARAMS);
UNK_RET lbColl_8000A584(UNK_PARAMS);
UNK_RET lbColl_8000A78C(UNK_PARAMS);
bool lbColl_8000A95C(HitResult*, unk_t, Mtx*, f32 pos_z);
UNK_RET lbColl_8000AB2C(UNK_PARAMS);

static inline bool approximatelyZero(f32 x)
{
    bool result;

    if ((x < 0.00001f) && (x > -0.00001f)) {
        result = true;
    } else {
        result = false;
    }

    return result;
}

static inline bool testPlusX(Vec3* a, Vec3* b, Vec3* c, f32 offset)
{
    f32 x = a->x + offset;
    if (x < b->x && x < c->x) {
        return false;
    }

    return true;
}

static inline bool testPlus(float a, float b, float c, float offset)
{
    float x = a + offset;
    if (x < b && x < c) {
        return false;
    }

    return true;
}

static inline bool testMinusX(Vec3* a, Vec3* b, Vec3* c, f32 offset)
{
    f32 x = a->x - offset;
    if (x > b->x && x > c->x) {
        return false;
    }

    return true;
}

#endif
