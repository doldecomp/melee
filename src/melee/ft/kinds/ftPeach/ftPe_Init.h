#ifndef GALE01_11B51C
#define GALE01_11B51C

#include <platform.h>

#include "ft/types.h"

#include "ftPeach/forward.h"
#include <baselib/forward.h>

/* 11B51C */ void ftPe_Init_OnDeath(HSD_GObj* gobj);
/* 11B628 */ void ftPe_Init_OnLoad(HSD_GObj* gobj);
/* 11B704 */ void ftPe_Init_OnDeath2(HSD_GObj* gobj);
/* 11B740 */ void ftPe_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 11B820 */ void ftPe_Init_OnItemInvisible(HSD_GObj* gobj);
/* 11B868 */ void ftPe_Init_OnItemVisible(HSD_GObj* gobj);
/* 11B8B0 */ void ftPe_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 11B904 */ void ftPe_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 11B93C */ void ftPe_Init_8011B93C(HSD_GObj* gobj);
/* 11B998 */ void ftPe_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 11B9DC */ void ftPe_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3CCCB8 */ extern MotionState ftPe_Init_MotionStateTable[ftPe_MS_SelfCount];
/* 3CD078 */ extern char ftPe_Init_DatFilename[];
/* 3CD084 */ extern char ftPe_Init_DataName[];
/* 3CD204 */ extern char ftPe_Init_AnimDatFilename[];
/* 3CD280 */ extern Fighter_DemoStrings ftPe_Init_DemoMotionFilenames;
/* 3CD290 */ extern Fighter_CostumeStrings ftPe_Init_CostumeStrings[];

#endif
