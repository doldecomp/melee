#ifndef GALE01_110094
#define GALE01_110094

#include <platform.h>

#include "ft/types.h"

#include "ftSeak/forward.h"
#include <baselib/forward.h>

/* 110094 */ void ftSk_Init_OnDeath(HSD_GObj* gobj);
/* 1100EC */ void ftSk_Init_OnLoad(HSD_GObj* gobj);
/* 110198 */ void ftSk_Init_80110198(HSD_GObj* gobj);
/* 1101CC */ void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj);
/* 110204 */ void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 1102E4 */ void ftSk_Init_OnItemInvisible(HSD_GObj* gobj);
/* 11032C */ void ftSk_Init_OnItemVisible(HSD_GObj* gobj);
/* 110374 */ void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 1103C8 */ void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 110408 */ void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 11044C */ void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CC060 */ extern MotionState ftSk_Init_MotionStateTable[ftSk_MS_SelfCount];
/* 3CC360 */ extern char ftSk_Init_DatFilename[];
/* 3CC36C */ extern char ftSk_Init_DataName[];
/* 3CC4CC */ extern char ftSk_Init_AnimDatFilename[];
/* 3CC548 */ extern Fighter_DemoStrings ftSk_Init_DemoMotionFilenames;
/* 3CC558 */ extern Fighter_CostumeStrings ftSk_Init_CostumeStrings[];

#endif
