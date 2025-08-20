#ifndef GALE01_148C64
#define GALE01_148C64

#include <platform.h>

#include "ft/types.h"

#include "ftLink/forward.h"

/* 148C64 */ void ftCl_Init_OnDeath(Fighter_GObj* gobj);
/* 148CE4 */ void ftCl_Init_OnLoad(Fighter_GObj* gobj);
/* 148DC0 */ void ftCl_Init_OnItemPickup(Fighter_GObj* gobj, bool flag);
/* 148E34 */ void ftCl_Init_OnItemInvisible(Fighter_GObj* gobj);
/* 148E7C */ void ftCl_Init_OnItemVisible(Fighter_GObj* gobj);
/* 148EC4 */ void ftCl_Init_OnItemDrop(Fighter_GObj* gobj, bool flag);
/* 148F38 */ void ftCl_Init_OnItemPickupExt(Fighter_GObj* gobj, bool flag);
/* 149018 */ void ftCl_Init_OnItemDropExt(Fighter_GObj* gobj, bool flag);
/* 14906C */ void ftCl_Init_LoadSpecialAttrs(Fighter_GObj* gobj);
/* 14908C */ void ftCl_Init_OnKnockbackEnter(Fighter_GObj* gobj);
/* 1490D0 */ void ftCl_Init_OnKnockbackExit(Fighter_GObj* gobj);
/* 149114 */ void ftCl_Init_80149114(Fighter_GObj* gobj);
/* 14919C */ void ftCl_Init_8014919C(Fighter_GObj* gobj);
/* 14920C */ bool ftCl_Init_8014920C(Fighter_GObj* gobj);
/* 149268 */ void ftCl_Init_80149268(Fighter_GObj* gobj);
/* 1492C4 */ void ftCl_Init_801492C4(Fighter_GObj* gobj);
/* 1492F4 */ bool ftCl_Init_801492F4(Fighter_GObj* gobj);
/* 149318 */ void ftCl_Init_80149318(Fighter_GObj* gobj);
/* 3D0FA0 */ extern MotionState ftCl_Init_MotionStateTable[ftLk_MS_SelfCount];
/* 3D1240 */ extern char ftCl_Init_DatFilename[];
/* 3D124C */ extern char ftCl_Init_DataName[];
/* 3D13CC */ extern char ftCl_Init_AnimDatFilename[];
/* 3D1448 */ extern Fighter_DemoStrings ftCl_Init_DemoMotionFilenames;
/* 3D1458 */ extern Fighter_CostumeStrings ftCl_Init_CostumeStrings[];

#endif
