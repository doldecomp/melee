#ifndef GALE01_1147C0
#define GALE01_1147C0

#include "ft/types.h"

#include "ftNess/forward.h"
#include <baselib/forward.h>

/* 1147C0 */ void ftNs_Init_OnDeath(HSD_GObj* gobj);
/* 11480C */ void ftNs_Init_OnLoad(HSD_GObj* gobj);
/* 1148F8 */ void ftNs_Init_OnDamage(HSD_GObj* gobj);
/* 11493C */ void ftNs_Init_OnAbsorb(HSD_GObj* gobj);
/* 11495C */ float ftNs_Init_GetAbsorbHeal(Fighter* fp);
/* 114968 */ void ftNs_Init_OnItemPickup(HSD_GObj* gobj, bool catchItemFlag);
/* 114A48 */ void ftNs_Init_OnItemInvisible(HSD_GObj* gobj);
/* 114A90 */ void ftNs_Init_OnItemVisible(HSD_GObj* gobj);
/* 114AD8 */ void ftNs_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag);
/* 114B2C */ void ftNs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 114B6C */ void ftNs_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 114BB0 */ void ftNs_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CC650 */ extern MotionState ftNs_Init_MotionStateTable[ftNs_MS_SelfCount];
/* 3CCAD0 */ extern char ftNs_Init_DatFilename[];
/* 3CCADC */ extern char ftNs_Init_DataName[];
/* 3CCBF8 */ extern char ftNs_Init_AnimDatFilename[];
/* 3CCC74 */ extern Fighter_DemoStrings ftNs_Init_DemoMotionFilenames;
/* 3CCC84 */ extern Fighter_CostumeStrings ftNs_Init_CostumeStrings[];

#endif
