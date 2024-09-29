#ifndef GALE01_1422E8
#define GALE01_1422E8

#include <platform.h>

#include "ftLuigi/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 1422E8 */ void ftLg_Init_OnDeath(HSD_GObj* gobj);
/* 142324 */ void ftLg_Init_OnLoad(HSD_GObj* gobj);
/* 142388 */ void ftLg_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 142468 */ void ftLg_Init_OnItemInvisible(HSD_GObj* gobj);
/* 1424B0 */ void ftLg_Init_OnItemVisible(HSD_GObj* gobj);
/* 1424F8 */ void ftLg_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 14254C */ void ftLg_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 142584 */ void ftLg_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 1425C8 */ void ftLg_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 14260C */ void ftLg_Init_UnkDemoCallbacks0(int arg0, int* arg1, int* arg2);
/* 142640 */ char* ftLg_Init_GetMotionFileString(enum_t demoMotionArg);
/* 3D0628 */ extern MotionState ftLg_Init_MotionStateTable[ftLg_MS_SelfCount];
/* 3D0868 */ extern MotionState ftLg_Init_UnkMotionStates0[];
/* 3D08A8 */ extern char ftLg_Init_DatFilename[];
/* 3D08B4 */ extern char ftLg_Init_DataName[];
/* 3D09E8 */ extern char ftLg_Init_AnimDatFilename[];
/* 3D0A64 */ extern Fighter_DemoStrings ftLg_Init_DemoMotionFilenames;
/* 3D0AB4 */ extern Fighter_CostumeStrings ftLg_Init_CostumeStrings[];

#endif
