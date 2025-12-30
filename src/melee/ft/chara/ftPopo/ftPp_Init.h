#ifndef GALE01_11ED38
#define GALE01_11ED38

#include <platform.h>

#include "ft/types.h"

#include "ftPopo/forward.h"
#include <baselib/forward.h>

/* 11ED38 */ void ftPp_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 11EE18 */ void ftPp_Init_OnItemInvisible(HSD_GObj* gobj);
/* 11EE60 */ void ftPp_Init_OnItemVisible(HSD_GObj* gobj);
/* 11EEA8 */ void ftPp_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 11EEFC */ void ftPp_Init_OnLoad(HSD_GObj* gobj);
/* 11EF3C */ void ftPp_Init_OnLoadForNana(Fighter* fp);
/* 11EFE8 */ void ftPp_Init_OnDeath(HSD_GObj* gobj);
/* 11F060 */ void ftPp_Init_8011F060(HSD_GObj* gobj);
/* 11F0A4 */ void ftPp_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 11F0E4 */ void ftPp_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 11F128 */ void ftPp_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 11F16C */ void ftPp_Init_8011F16C(HSD_GObj* gobj, Item_GObj* item_gobj);
/* 3CD2D0 */ extern MotionState ftPp_Init_MotionStateTable[ftPp_MS_SelfCount];
/* 3CD610 */ extern char ftPp_Init_DatFilename[];
/* 3CD61C */ extern char ftPp_Init_DataName[];
/* 3CD738 */ extern char ftPp_Init_AnimDatFilename[];
/* 3CD7B4 */ extern Fighter_DemoStrings ftPp_Init_DemoMotionFilenames;
/* 3CD7C4 */ extern Fighter_CostumeStrings ftPp_Init_CostumeStrings[];

/* 4D9860 */ extern f32 ftPp_Init_804D9860;
/* 4D9880 */ extern f32 ftPp_Init_804D9880;

#endif
