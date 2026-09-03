#ifndef GALE01_14A250
#define GALE01_14A250

#include "ft/types.h"

#include "ftGameWatch/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

/* 14A250 */ void ftGw_Init_OnDeath(HSD_GObj* gobj);
/* 14A37C */ void ftGw_Init_OnLoad(HSD_GObj* gobj);
/* 14A4CC */ void ftGw_Init_OnDamage(HSD_GObj* gobj);
/* 14A538 */ void ftGw_Init_8014A538(HSD_GObj* gobj);
/* 14A5B8 */ void ftGw_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 14A698 */ void ftGw_Init_OnItemInvisible(HSD_GObj* gobj);
/* 14A6E0 */ void ftGw_Init_OnItemVisible(HSD_GObj* gobj);
/* 14A728 */ void ftGw_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag);
/* 14A77C */ void ftGw_Init_UnkMotionStates4(HSD_GObj* gobj);
/* 14A7B4 */ void ftGameWatch_CopySpecialAttrs(HSD_GObj* gobj);
/* 14A7F4 */ void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod);
/* 14A814 */ void ftGw_Init_8014A814(HSD_GObj* gobj, ItemModStruct* item_mod);
/* 14A828 */ void ftGw_Init_OnAbsorb(HSD_GObj* gobj);
/* 3D23E8 */ extern MotionState ftGw_Init_MotionStateTable[ftGw_MS_SelfCount];
/* 3D28E8 */ extern char ftGw_Init_DatFilename[];
/* 3D28F4 */ extern char ftGw_Init_DataName[];
/* 3D292C */ extern char ftGw_Init_AnimDatFilename[];
/* 3D29B8 */ extern Fighter_DemoStrings ftGw_Init_DemoMotionFilenames;
/* 3D29C8 */ extern Fighter_CostumeStrings ftGw_Init_CostumeStrings[];

#endif
