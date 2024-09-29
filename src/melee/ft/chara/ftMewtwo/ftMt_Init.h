#ifndef GALE01_144DFC
#define GALE01_144DFC

#include <platform.h>

#include "ftMewtwo/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 144DFC */ void ftMt_Init_OnDeath2(HSD_GObj* gobj);
/* 144E48 */ void ftMt_Init_OnLoad(HSD_GObj* gobj);
/* 144EE0 */ void ftMt_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 144EE4 */ void ftMt_Init_OnDeath(HSD_GObj* gobj);
/* 144F18 */ void ftMt_Init_OnTakeDamage(HSD_GObj* gobj);
/* 144F4C */ void ftMt_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 144F50 */ void ftMt_Init_OnItemInvisible(HSD_GObj* gobj);
/* 144F54 */ void ftMt_Init_OnItemVisible(HSD_GObj* gobj);
/* 144F58 */ void ftMt_Init_UnkMotionStates4(HSD_GObj* gobj);
/* 144FB4 */ void ftMt_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 145018 */ void ftMt_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 14505C */ void ftMt_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3D0B00 */ extern MotionState ftMt_Init_MotionStateTable[ftMt_MS_SelfCount];
/* 3D0D80 */ extern char ftMt_Init_DatFilename[];
/* 3D0D8C */ extern char ftMt_Init_DataName[];
/* 3D0EC4 */ extern char ftMt_Init_AnimDatFilename[];
/* 3D0F4C */ extern Fighter_DemoStrings ftMt_Init_DemoMotionFilenames;
/* 3D0F5C */ extern Fighter_CostumeStrings ftMt_Init_CostumeStrings[];

#endif
