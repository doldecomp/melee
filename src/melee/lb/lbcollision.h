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
    u8 x10[0x1C - 0x10];
    f32 x1C;
    u8 x20[0x30 - 0x20];

    /// @at{30} @sz{4}
    HitElement element;

    u8 x34[0x38 - 0x34];

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
    u8 x41[0x42 - 0x41];
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
    u8 x46[0x4C - 0x46];
    int x4C;

    u8 x50[0x58 - 0x50];
    int x58;
    int x5C;
    int x60;
    int x64;
    u8 x68[0x74 - 0x68];
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
bool lbColl_80008248(bool, Hurtbox*, void*, f32, f32, f32);
void lbColl_80008440(Hitbox*);
void lbColl_80008434(Hitbox*);
bool lbColl_8000ACFC(UNK_T, Hitbox*);
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
void lbColl_80007DD8(void);
void lbColl_80008D30(void);
void lbColl_80005C44(void);
void lbColl_80005EBC(void);
void lbColl_80005FC0(void);
void lbColl_80006094(void);
void lbColl_800067F8(void);
void lbColl_80006E58(void);
void lbColl_800077A0(void);
void lbColl_80007B78(void);
UNK_RET lbColl_80008428(UNK_PARAMS);
UNK_RET lbColl_800089B8(UNK_PARAMS);

#endif
