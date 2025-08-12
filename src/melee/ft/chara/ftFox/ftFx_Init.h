#ifndef GALE01_0E5534
#define GALE01_0E5534

#include <platform.h>

#include "ft/types.h"

#include "ftFox/forward.h"
#include <baselib/forward.h>

/* 0E5534 */ bool ftFx_Init_800E5534(HSD_GObj* gobj);
/* 0E5554 */ void ftFx_Init_OnDeath(HSD_GObj* gobj);
/* 0E5588 */ void ftFx_Init_800E5588(HSD_GObj* gobj);
/* 0E55A8 */ void ftFx_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 0E5688 */ void ftFx_Init_OnItemInvisible(HSD_GObj* gobj);
/* 0E56D0 */ void ftFx_Init_OnItemVisible(HSD_GObj* gobj);
/* 0E5718 */ void ftFx_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 0E576C */ void ftFx_Init_OnLoadForFalco(Fighter* fp);
/* 0E57AC */ void ftFx_Init_OnLoad(HSD_GObj* gobj);
/* 0E5858 */ void ftFx_Init_LoadSpecialAttrs(HSD_GObj*);
/* 0E5898 */ void ftFx_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 0E5904 */ void ftFx_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3C7788 */ extern MotionState ftFx_Init_MotionStateTable[ftFx_MS_SelfCount];
/* 3C7BE8 */ extern char ftFx_Init_DatFilename[];
/* 3C7BF4 */ extern char ftFx_Init_DataName[];
/* 3C7D10 */ extern char ftFx_Init_AnimDatFilename[];
/* 3C7D8C */ extern Fighter_DemoStrings ftFx_Init_DemoMotionFilenames;
/* 3C7D9C */ extern Fighter_CostumeStrings ftFx_Init_CostumeStrings[];

#endif
