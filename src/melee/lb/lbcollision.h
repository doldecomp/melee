#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <melee/ft/forward.h>
#include <melee/lb/forward.h>
#include <placeholder.h>
#include <sysdolphin/baselib/jobj.h>

struct HitResult {
    HSD_JObj* bone;

    /// Follows attach bone position if toggled OFF
    u8 skip_update_pos : 1;

    Vec3 pos;
    Vec3 offset;
    f32 size;
};

struct HitVictim {
    /// @at{0} @sz{4}
    HSD_GObj* victim;

    /// @at{4} @sz{4}
    /// @brief The number of frames needed to pass before this entity can be hit
    ///        again; 0 = can't rehit
    s32 iframes;
};

struct Hitbox {
    /// @at{0} @sz{4}
    Tangibility tangiblity;
    /// @at{4} @sz{C}
    /// The offset of point @e a of the capsule.
    Vec3 a_offset;

    /// @at{10} @sz{C}
    /// The offset of point @e b of the capsule.
    Vec3 b_offset;

    /// @at{1C} @sz{4}
    /// The scale of the capsule.
    f32 scl;

    HSD_JObj* bone;

    u8 x24[0x30 - 0x24];

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
    u8 x43_b0 : 1;
    u8 x43_b1 : 1;
    u8 x43_b2 : 1;
    u8 x43_b3 : 1;
    u8 x43_b4 : 1;
    u8 x43_b5 : 1;
    u8 x43_b6 : 1;
    u8 x43_b7 : 1;
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

    /// @at{134} @sz{4}
    /// @todo This union is unacceptable.
    union {
        HSD_GObj* owner;
        u8 hit_grabbed_victim_only : 1;
    };
};

struct Hurtbox {
    /// @at{0} @sz{4}
    Tangibility tangiblity;

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

void HSD_JObjUnkMtxPtr(HSD_JObj*);
bool lbColl_80008248(Hitbox*, Hurtbox*, Mtx, f32, f32, f32);
void lbColl_80008440(Hitbox*);
void lbColl_80008434(Hitbox*);
bool lbColl_8000ACFC(UNK_T, Hitbox*);
UNK_RET lbColl_80008688(UNK_PARAMS);
UNK_RET lbColl_800084FC(UNK_PARAMS);
UNK_RET lbColl_80008820(UNK_PARAMS);
void func_80077464();
int lbColl_80005BB0(Hitbox*, int);
bool lbColl_80007ECC(Hitbox*, Hurtbox*, unk_t, f32 hit_scl_y, f32 hurt_scl_y,
                     f32 hurt_pos_z);
bool lbColl_8000805C(Hitbox*, Hurtbox*, unk_t, s32, f32, f32, f32);
bool lbColl_80007BCC(Hitbox*, HitResult shield_hit, unk_t, s32, f32, f32, f32);
bool lbColl_80007AFC(Hitbox*, Hitbox*, f32, f32);
UNK_RET lbColl_80007DD8(UNK_PARAMS);
UNK_RET lbColl_80008D30(UNK_PARAMS);
void lbColl_80008428(Hitbox*);
bool lbColl_80005C44(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, f32 arg8,
                     f32 arg9);
f32 lbColl_80005EBC(Vec3*, Vec3*, Vec3*, f32*);
UNK_RET lbColl_80005FC0(Vec3*, Vec3*, Vec3*, f32*);
bool lbColl_80006094(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32);
bool lbColl_800067F8(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, Vec3* arg4,
                     Vec3* arg5, f32 arg6, f32 arg7, f32 arg8);
bool lbColl_80006E58(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Mtx, Vec3*, f32,
                     f32 scl, f32);
UNK_RET lbColl_800077A0(UNK_PARAMS);
UNK_RET lbColl_80007B78(Mtx, Mtx, f32, f32);
void lbColl_800083C4(Hurtbox*);
UNK_RET lbColl_800089B8(UNK_PARAMS);
UNK_RET lbColl_80008A5C(UNK_PARAMS);
UNK_RET lbColl_80008DA4(UNK_PARAMS);
UNK_RET lbColl_80008FC8(UNK_PARAMS);
UNK_RET lbColl_800096B4(UNK_PARAMS);
UNK_RET lbColl_80009DD4(UNK_PARAMS);
UNK_RET lbColl_80009F54(UNK_PARAMS);
UNK_RET lbColl_8000A044(UNK_PARAMS);
UNK_RET lbColl_8000A10C(UNK_PARAMS);
UNK_RET lbColl_8000A1A8(UNK_PARAMS);
void lbColl_8000A244(Hurtbox* arg0, u32 arg1, Mtx arg2, f32 arg3);
UNK_RET lbColl_8000A460(UNK_PARAMS);
UNK_RET lbColl_8000A584(UNK_PARAMS);
UNK_RET lbColl_8000A78C(UNK_PARAMS);
bool lbColl_8000A95C(HitResult*, unk_t, Mtx*, f32 pos_z);
UNK_RET lbColl_8000AB2C(UNK_PARAMS);

#endif
