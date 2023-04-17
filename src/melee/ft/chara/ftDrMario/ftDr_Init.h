#ifndef _ftdrmario_h_
#define _ftdrmario_h_

#include <platform.h>

#include "ft/fighter.h"

#include <baselib/gobj.h>

typedef struct _ftDrMarioAttributes {
    u8 pad_x0[4];
    u32 x4;
    u8 pad_x8[4];
    u32 xC;
    u8 pad_x10[4];
    u32 x14;
} ftDrMarioAttributes;

extern MotionState ftDr_Init_MotionStateTable[];
extern char ftDr_Init_DatFilename[];
extern char ftDr_Init_DataName[];
extern Fighter_CostumeStrings ftDr_Init_CostumeStrings[];
extern char ftDr_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftDr_Init_DemoMotionFilenames;

bool ftDr_Init_80149844(HSD_GObj* gobj);
u32 ftDr_Init_801498EC(HSD_GObj* gobj);
void ftDr_Appeal_Anim(HSD_GObj* gobj);
void ftDr_Appeal_Coll(HSD_GObj* gobj);
void ftDr_Appeal_IASA(HSD_GObj* gobj);
void ftDr_Appeal_Phys(HSD_GObj* gobj);
void ftDr_Init_80149540(HSD_GObj* gobj);
void ftDr_Init_801497CC(HSD_GObj* gobj);
void ftDr_Init_801498A0(HSD_GObj* gobj);
void ftDr_Init_80149910(HSD_GObj* gobj);
void ftDr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftDr_Init_OnDeath(HSD_GObj* gobj);
void ftDr_Init_OnItemDrop(HSD_GObj* gobj, bool);
void ftDr_Init_OnItemInvisible(HSD_GObj* gobj);
void ftDr_Init_OnItemPickup(HSD_GObj* gobj, bool);
void ftDr_Init_OnItemVisible(HSD_GObj* gobj);
void ftDr_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftDr_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftDr_Init_OnLoad(HSD_GObj* gobj);

#endif
