#ifndef MELEE_LB_LBCOLLISION_H
#define MELEE_LB_LBCOLLISION_H

#include <sysdolphin/baselib/jobj.h>

/// @todo Does not belong here.
typedef struct _Hitbox {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    /// @remarks @c f32 needed for 'manual' mods to hitbox damage.
    u8 x10[0x134 - 0x10];
    s32 x134;
} Hitbox;

typedef struct ftHurt {
    u32 tangiblity;        // 0x0, whether or not this hurtbox can be hit
    Vec3 x4_hurt1_offset;  // 0x4
    Vec3 x10_hurt2_offset; // 0x10
    f32 x1C_scale;         // 0x1c
    HSD_JObj* x20_jobj;    // 0x20
    unsigned char
        x24_1_is_updated : 1; // 0x24, 0x80, if enabled, wont update position
    unsigned char x24_2 : 1;  // 0x24 0x40
    unsigned char x24_3 : 1;  // 0x24 0x20
    unsigned char x24_4 : 1;  // 0x24 0x10
    unsigned char x24_5 : 1;  // 0x24 0x08
    unsigned char x24_6 : 1;  // 0x24 0x04
    unsigned char x24_7 : 1;  // 0x24 0x02
    unsigned char x24_8 : 1;  // 0x24 0x01
    Vec3 x28_hurt1_pos;       // 0x28
    Vec3 x34_hurt2_pos;       // 0x34
    u32 x40_bone_index;       // 0x40
    u32 x44_hurt_kind;        // 0x44. 0 = low, 1 = mid, 2 = high
    u32 x48_is_grabbable;     // 0x48
} ftHurt;

void* HSD_JObjUnkMtxPtr(HSD_JObj*);
s32 func_80008248(s32, struct ftHurt*, void*, f32, f32, f32);
void func_80008440(struct _Hitbox*);
void func_80008434(struct _Hitbox*);
void func_8000ACFC(void);
void func_80008688(void);
void func_800084FC(void);
void func_80008820(void);
void func_80077464(void);
void func_80005BB0(void);
void func_80007ECC(void);

#endif
