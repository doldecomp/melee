#ifndef GALE01_136258
#define GALE01_136258

#include <platform.h>

#include "ft/types.h"

#include "ftMars/forward.h"
#include <baselib/forward.h>

/* 136258 */ void ftMs_Init_OnDeath(HSD_GObj* gobj);
/* 1362B0 */ void ftMs_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 136390 */ void ftMs_Init_OnItemInvisible(HSD_GObj* gobj);
/* 1363D8 */ void ftMs_Init_OnItemVisible(HSD_GObj* gobj);
/* 136420 */ void ftMs_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 136474 */ void ftMs_Init_OnLoadForRoy(Fighter* fp);
/* 1364AC */ void ftMs_Init_OnLoad(HSD_GObj* gobj);
/* 1364E8 */ void ftMs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 136520 */ void ftMs_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 136564 */ void ftMs_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 1365A8 */ void ftMs_SpecialN_801365A8(HSD_GObj* gobj);
/* 13666C */ void ftMs_SpecialN_8013666C(HSD_GObj* gobj);
/* 136730 */ void ftMs_SpecialN_80136730(HSD_GObj* gobj);
/* 3CF420 */ extern MotionState ftMs_Init_MotionStateTable[ftMs_MS_SelfCount];
/* 3CF820 */ extern char ftMs_Init_DatFilename[];
/* 3CF82C */ extern char ftMs_Init_DataName[];
/* 3CF98C */ extern char ftMs_Init_AnimDatFilename[];
/* 3CFA08 */ extern Fighter_DemoStrings ftMs_Init_DemoMotionFilenames;
/* 3CFA18 */ extern Fighter_CostumeStrings ftMs_Init_CostumeStrings[];

#endif
