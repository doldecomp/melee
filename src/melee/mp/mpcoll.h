#ifndef MELEE_MP_MPCOLL_H
#define MELEE_MP_MPCOLL_H

#include <ctypes.h>
#include <dolphin/mtx/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

typedef struct _ftECB {
    Vec2 top;
    Vec2 bottom;
    Vec2 right;
    Vec2 left;
} ftECB;
typedef struct SurfaceData {
    s32 index;
    u32 unk;
    Vec3 normal;
} SurfaceData;

typedef struct _ECBFlagStruct {
    union {
        struct {
            u8 b0 : 1;
            u8 b1234 : 4;
            u8 b5 : 1;
            u8 b6 : 1;
            u8 b7 : 1;
        } bits;
        u8 raw;
    };
} ECBFlagStruct;

typedef struct _CollData {
    HSD_GObj* x0_gobj;
    Vec3 x4_vec;
    Vec3 x10_vec;
    Vec3 x1C_vec;
    Vec3 x28_vec;
    ECBFlagStruct x34_flags;
    ECBFlagStruct x35_flags;
    s16 x36;
    s32 x38;
    s32 x3C;
    s32 x40;
    u32 x44;
    u32 x48;
    u32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    s32 x60;
    ftECB x64_ecb;
    ftECB x84_ecb;
    ftECB xA4_ecbCurrCorrect;
    ftECB xC4_ecb;
    ftECB xE4_ecb;
    s32 x104; // TODO this is the start of a substruct with size 0x2C
    union {
        struct {
            HSD_JObj* x108_joint;
            HSD_JObj* x10C_joint[6];
        };
        struct {
            f32 x108_f32;
            f32 x10C_f32;
            f32 x110_f32;
            f32 x114_f32;
            f32 x118_f32;
            f32 x11C_f32;
            f32 x120_f32;
        };
    };
    f32 x124;
    f32 x128;
    f32 x12C;
    u32 x130_flags;
    s32 x134_envFlags;
    s32 filler138;
    s32 filler13C;
    Vec3 x140;
    SurfaceData x14C_ground;
    SurfaceData x160_rightwall;
    SurfaceData x174_leftwall;
    SurfaceData x188_ceiling;
    /* 0x19C */ s32 x19C;
} CollData;

void func_80042374(CollData*, f32, f32, f32);
void func_80042078(CollData* cd, HSD_GObj* gobj,
                   HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*,
                   HSD_JObj*, HSD_JObj*, HSD_JObj*, f32);
void func_80041EE4(CollData*);
unk_t func_800471F8();
unk_t func_800473CC();
unk_t func_800477E0();
unk_t func_80048464();
unk_t func_80048160();
unk_t func_80048274();
unk_t func_80048578();
unk_t func_80048768();
unk_t func_80048388();
void func_800436D8(CollData*, s32);
unk_t func_800475F4();
void func_8004730C(CollData*, f32 (*x)[6]);
unk_t func_80047A08();
unk_t func_8004B108();
unk_t func_8004B21C();
unk_t func_8004B2DC();
unk_t func_8004B3F0();
unk_t func_80047E14();
unk_t func_80047AC8();
unk_t func_80047F40();
unk_t func_80047BF4();
unk_t func_8004806C();
unk_t func_80047D20();
unk_t func_80048654();
unk_t func_800474E0();
unk_t func_800476B4();
unk_t func_800478F4();
unk_t func_8004B5C4();
unk_t func_8004CC00();
unk_t func_8004CA6C();
unk_t func_8004CBC0();
unk_t func_8004CBE8();
void func_80043680(CollData*, Vec3*);
unk_t func_800443C4();
unk_t func_80044164();
void func_80043670(CollData*);
void func_8004CBF4(CollData*);

#endif
