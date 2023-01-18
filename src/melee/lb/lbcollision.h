#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <melee/ft/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/jobj.h>

typedef struct Hitbox {
    Tangibility tangiblity;
    s32 x4;
    s32 x8;
    f32 xC;
    u8 x10[0x30 - 0x10];

    /// @at{30} @sz{4}
    HitElement element;

    u8 x34[0x40 - 0x34];
    u8 x40_b0 : 1;
    u8 x40_b1 : 1;
    u8 x40_b2 : 1;
    u8 x40_b3 : 1;
    u8 x40_b4 : 1;
    u8 x40_b5 : 1;
    u8 x40_b6 : 1;
    u8 x40_b7 : 1;
    u8 x41[0x134 - 0x41];
    s32 x134;
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

void* HSD_JObjUnkMtxPtr(HSD_JObj*);
s32 func_80008248(s32, struct Hurtbox*, void*, f32, f32, f32);
void func_80008440(Hitbox*);
void func_80008434(Hitbox*);
bool func_8000ACFC(Fighter*, Hitbox*);
void func_80008688(void);
void func_800084FC(void);
void func_80008820(void);
void func_80077464(void);
void func_80005BB0(void);
void func_80007ECC(void);

#endif
