#ifndef _ftkoopa_h_
#define _ftkoopa_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct _ftKoopaAttributes {
    f32 x0;
    u32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u32 x20;
    f32 x24;
    f32 x28;
    u32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    u32 unk50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    f32 x74;
    f32 x78;
    f32 x7C;
    f32 x80;
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    f32 x94;
    f32 x98;
    f32 x9C;
} ftKoopaAttributes;

typedef struct _ftKoopaVars {
    f32 x0;
    f32 x4;
} ftKoopaVars;

void ftKoopa_SpecialS_StartAction(HSD_GObj* gobj);
void func_8013302C(HSD_GObj* gobj);
void func_801330E4(HSD_GObj* gobj);
void func_80132A64(HSD_GObj* gobj);
void ftKoopa_OnLoadForGKoopa(Fighter* fp);
void ftKoopa_LoadSpecialAttrs(HSD_GObj* gobj);

f32 func_80132DC0(HSD_GObj* gobj);
f32 func_80132DD0(HSD_GObj* gobj);
f32 func_80132DE0(HSD_GObj* gobj);
f32 func_80132DF0(HSD_GObj* gobj);
f32 func_80132E00(HSD_GObj* gobj);
f32 func_80132E10(HSD_GObj* gobj);
f32 func_80132E20(HSD_GObj* gobj);
void ftKoopa_OnDeath(HSD_GObj* gobj);
void func_80132E30(HSD_GObj* gobj);
void ftKoopa_SpecialAirS_StartAction(HSD_GObj* gobj);
void func_8013319C(HSD_GObj* gobj);
void func_8013322C(HSD_GObj* gobj);
void func_801332C4(HSD_GObj* gobj);
void func_80133324(HSD_GObj* gobj);
void func_80133398(HSD_GObj* gobj);
void func_801333F8(HSD_GObj* gobj);
void func_80133484(HSD_GObj* gobj);
void func_801334E4(HSD_GObj* gobj);
void func_8013359C(HSD_GObj* gobj);
void func_80133654(HSD_GObj* gobj);
void func_80133690(HSD_GObj* gobj);
void func_801336CC(HSD_GObj* gobj);
void ftKoopa_OnLoad(HSD_GObj* gobj);
void func_80132B38(void);
void ftKoopa_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftKoopa_OnItemInvisible(HSD_GObj* gobj);
void ftKoopa_OnItemVisible(HSD_GObj* gobj);
void ftKoopa_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftKoopa_OnKnockbackEnter(HSD_GObj* gobj);
void ftKoopa_OnKnockbackExit(HSD_GObj* gobj);

#endif
