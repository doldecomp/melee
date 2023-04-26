#ifndef GALE01_148C64
#define GALE01_148C64

#include "ftLink/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 148C64 */ void ftCl_Init_OnDeath(HSD_GObj* gobj);
/* 148CE4 */ void ftCl_Init_OnLoad(HSD_GObj* gobj);
/* 148DC0 */ void ftCl_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 148E34 */ void ftCl_Init_OnItemInvisible(HSD_GObj* gobj);
/* 148E7C */ void ftCl_Init_OnItemVisible(HSD_GObj* gobj);
/* 148EC4 */ void ftCl_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 148F38 */ void ftCl_Init_OnItemPickupExt(HSD_GObj* gobj, bool arg1);
/* 149018 */ void ftCl_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1);
/* 14906C */ void ftCl_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 14908C */ void ftCl_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 1490D0 */ void ftCl_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 149114 */ void ftCl_Init_80149114(HSD_GObj* gobj);
/* 14919C */ void ftCl_Init_8014919C(HSD_GObj* gobj);
/* 14920C */ bool ftCl_Init_8014920C(HSD_GObj* gobj);
/* 149268 */ void ftCl_Init_80149268(HSD_GObj* gobj);
/* 1492C4 */ void ftCl_Init_801492C4(HSD_GObj* gobj);
/* 1492F4 */ u32 ftCl_Init_801492F4(HSD_GObj* gobj);
/* 149318 */ void ftCl_Init_80149318(HSD_GObj* gobj);
/* 3D0FA0 */ extern MotionState ftCl_Init_MotionStateTable[ftLk_MS_SelfCount];
/* 3D1240 */ extern char ftCl_Init_DatFilename[];
/* 3D124C */ extern char ftCl_Init_DataName[];
/* 3D13CC */ extern char ftCl_Init_AnimDatFilename[];
/* 3D1448 */ extern Fighter_DemoStrings ftCl_Init_DemoMotionFilenames;
/* 3D1458 */ extern Fighter_CostumeStrings ftCl_Init_CostumeStrings[];

#endif
