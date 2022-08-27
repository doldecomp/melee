#ifndef _ftkoopa_h_
#define _ftkoopa_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/gobj.h>

#include <melee/ft/fighter.h>

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

void ftKoopa_SpecialS_StartAction(HSD_GObj *gobj);
void func_8013302C(HSD_GObj *gobj);
void func_801330E4(HSD_GObj* gobj);

#endif
