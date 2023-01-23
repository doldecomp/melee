#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <melee/ft/forward.h>
#include <melee/lb/forward.h>
#include <placeholder.h>
#include <sysdolphin/baselib/jobj.h>

struct HitVictim {
    /// @at{0} @sz{4}
    HSD_GObj* entity;

    /// @at{4} @sz{4}
    /// @brief The number of frames needed to pass before this entity can be hit
    ///        again; 0 = can't rehit
    s32 iframes;
};

struct Hitbox {
    Tangibility tangiblity;
    s32 x4;
    s32 x8;
    f32 xC;
    char unk_10[0x30 - 0x10];

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
    int x44;
    char unk_48[0x74 - 0x48];
    int x74;
    char unk_78[0x7C - 0x78];
    int x7C;
    char unk_80[0x84 - 0x80];
    int x84;
    char unk_88[0x8C - 0x88];
    int x8C;
    char unk_90[0x94 - 0x90];
    int x94;
    char unk_98[0x9C - 0x98];
    int x9C;
    char unk_A0[0xA4 - 0xA0];
    int xA4;
    char unk_A8[0xAC - 0xA8];
    int xAC;
    char unk_B0[0x134 - 0xB0];

    /// @at{134} @sz{4}
    /// @todo This union is unacceptable.
    union {
        HSD_GObj* owner;
        u8 hit_grabbed_victim_only : 1;
    };
};

struct Hurtbox {
    Tangibility tangiblity; // 0x0, whether or not this hurtbox can be hit
    Vec3 x4_hurt1_offset;   // 0x4
    Vec3 x10_hurt2_offset;  // 0x10
    f32 x1C_scale;          // 0x1c
    HSD_JObj* x20_jobj;     // 0x20
    unsigned char x24_1_is_updated : 1; // 0x24, 0x80, if enabled, wont
                                        // update position
    unsigned char x24_2 : 1;            // 0x24 0x40
    unsigned char x24_3 : 1;            // 0x24 0x20
    unsigned char x24_4 : 1;            // 0x24 0x10
    unsigned char x24_5 : 1;            // 0x24 0x08
    unsigned char x24_6 : 1;            // 0x24 0x04
    unsigned char x24_7 : 1;            // 0x24 0x02
    unsigned char x24_8 : 1;            // 0x24 0x01
    Vec3 x28_hurt1_pos;                 // 0x28
    Vec3 x34_hurt2_pos;                 // 0x34
    u32 x40_bone_index;                 // 0x40
    u32 x44_hurt_kind;                  // 0x44. 0 = low, 1 = mid, 2 = high
    u32 x48_is_grabbable;               // 0x48
};

void HSD_JObjUnkMtxPtr(HSD_JObj*);
void lbColl_80008440(Hitbox*);
void lbColl_80008434(Hitbox*);
void lbColl_80008688();
void lbColl_800084FC();
void lbColl_80008820();
bool lbColl_80008248(bool, Hurtbox*, void*, f32, f32, f32);
void lbColl_80008440(Hitbox*);
void lbColl_80008434(Hitbox*);
bool lbColl_8000ACFC(UNK_T, Hitbox*);
void lbColl_80008688();
void lbColl_800084FC();
void lbColl_80008820();
void func_80077464();
int lbColl_80005BB0(Hitbox*, int);
bool lbColl_80007ECC(Hitbox*, Hurtbox*, unk_t, f32 hit_scl_y, f32 hurt_scl_y,
                     f32 hurt_pos_z);
bool lbColl_8000805C(Hitbox*, Hurtbox*, unk_t, s32, f32, f32, f32);
bool lbColl_80007BCC(Hitbox*, unk_t shield_hit, unk_t, s32, f32, f32, f32);
bool lbColl_80007AFC(Hitbox*, Hitbox*, f32, f32);
void lbColl_80007DD8();
void lbColl_80008D30();
void lbColl_80008428();
void lbColl_80005C44();
void lbColl_80005EBC();
void lbColl_80005FC0();
void lbColl_80006094();
void lbColl_800067F8();
void lbColl_80006E58();
void lbColl_800077A0();
void lbColl_80007B78(Mtx, Mtx, f32, f32);
bool lbColl_80007BCC(Hitbox*, unk_t shield_hit, unk_t, s32, f32, f32, f32);
void lbColl_800083C4();
void lbColl_800089B8();
void lbColl_80008A5C();
void lbColl_80008DA4();
void lbColl_80008FC8();

#endif
