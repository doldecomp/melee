#ifndef _ftmasterhand_h_
#define _ftmasterhand_h_

#include <dolphin/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _MasterHandAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    f32 x28;
    f32 x2C;
    Vec2 x30_pos2;
    f32 x38;
    f32 x3C;
    Vec3 x40_pos;
    f32 x4C;
    Vec2 x50;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    f32 x78;
    s32 x7C;
    f32 x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    f32 x98;
    f32 x9C;
    s32 xA0;
    f32 xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    f32 xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    s32 xEC;
    s32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    f32 x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
    s32 x144;
    s32 x148;
    f32 x14C;
    f32 x150;
    f32 x154;
    f32 x158;
    f32 x15C;
    s32 x160;
    s32 x164;
    s32 x168;
    s32 x16C;
    s32 x170;
    s32 x174;
    f32 x178;
} MasterHandAttributes;

// ftMasterHand_1
void ftMasterhand_OnDeath(HSD_GObj* gobj);
void ftMasterhand_OnLoad(HSD_GObj* gobj);

// ftMasterHand_2
void ftMasterHand_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftMasterHand_8014FE10(HSD_GObj* fighter_gobj);
void ftMasterHand_8014FE58(HSD_GObj* fighter_gobj);
void ftMasterHand_80150890(HSD_GObj* fighter_gobj);

// ftMasterHand_3
void lbl_80150F00(HSD_GObj* fighter_gobj);
void lbl_80150F68(HSD_GObj* fighter_gobj);
void ftMasterHand_80150FC8(HSD_GObj* fighter_gobj);
void ftMasterHand_80151018(HSD_GObj* fighter_gobj);

// ftMasterHand_4
void ftMasterHand_80151168(HSD_GObj* gobj);
void ftMasterHand_801511B0(HSD_GObj* gobj);
void ftMasterHand_801511F4(HSD_GObj* gobj);
void ftMasterHand_801511F8(HSD_GObj* gobj);

// ftMasterHand_14
void lbl_80152E28(HSD_GObj* gobj);

// ftMasterHand_15
void lbl_801535B0(HSD_GObj* gobj);
void func_8015364C(struct _HSD_GObj *, struct _HSD_JObj *, f32, f32);

// ftMasterHand_21
void lbl_801541C4(HSD_GObj* gobj);

// ftMasterHand_22
void lbl_80154A2C(HSD_GObj* gobj);

// ftMasterHand_31
void lbl_80155A58(HSD_GObj* gobj_1, HSD_GObj* gobj_2);

void lbl_801526D8(HSD_GObj*); // 12 Ground Slap
void lbl_80152BCC(HSD_GObj*); // 14 Lasers
void lbl_80153B90(HSD_GObj*); // 19 Ram
void lbl_80153D2C(HSD_GObj*); // 20 Crush
void ftMasterHand_80155194(HSD_GObj*); // 27 Crazy Hand Combo Attack 1
void ftMasterHand_801552F8(HSD_GObj*); // 28 Crazy Hand Combo Attack 2
void lbl_80155484(HSD_GObj*); // 29 Crazy Hand Combo Attack 3

#endif
