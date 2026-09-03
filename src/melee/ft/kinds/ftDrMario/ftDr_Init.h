#ifndef GALE01_14949C
#define GALE01_14949C

#include "ft/types.h"

#include <baselib/forward.h>

/* 14949C */ void ftDr_Init_OnDeath(HSD_GObj* gobj);
/* 1494E4 */ void ftDr_Init_OnLoad(HSD_GObj* gobj);
/* 149540 */ void ftDr_Init_80149540(HSD_GObj* gobj);
/* 149560 */ void ftDr_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 149640 */ void ftDr_Init_OnItemInvisible(HSD_GObj* gobj);
/* 149688 */ void ftDr_Init_OnItemVisible(HSD_GObj* gobj);
/* 1496D0 */ void ftDr_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 149724 */ void ftDr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 149744 */ void ftDr_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 149788 */ void ftDr_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 1497CC */ void ftDr_Init_801497CC(HSD_GObj* gobj);
/* 149844 */ bool ftDr_Init_80149844(HSD_GObj* gobj);
/* 1498A0 */ void ftDr_Init_801498A0(HSD_GObj* gobj);
/* 1498EC */ u32 ftDr_Init_801498EC(HSD_GObj* gobj);
/* 149910 */ void ftDr_Init_80149910(HSD_GObj* gobj);
/* 3D1498 */ extern MotionState ftDr_Init_MotionStateTable[ftMr_MS_SelfCount];
/* 3D15D8 */ extern Fighter_CostumeStrings ftDr_Init_CostumeStrings[];
/* 3D15E4 */ extern char ftDr_Init_DatFilename[];
/* 3D1770 */ extern char ftDr_Init_AnimDatFilename[];
/* 3D17FC */ extern Fighter_DemoStrings ftDr_Init_DemoMotionFilenames;
/* 3D180C */ extern char ftDr_Init_DataName[];

#endif
