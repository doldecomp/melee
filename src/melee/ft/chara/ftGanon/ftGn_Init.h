#ifndef GALE01_14EE40
#define GALE01_14EE40

#include <platform.h>

#include "ft/types.h"

#include "ftCaptain/forward.h"
#include <baselib/forward.h>

/* 14EBFC */ void ftGn_Init_OnDeath(HSD_GObj* gobj);
/* 14EC58 */ void ftGn_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 14ED38 */ void ftGn_Init_OnItemInvisible(HSD_GObj* gobj);
/* 14ED80 */ void ftGn_Init_OnItemVisible(HSD_GObj* gobj);
/* 14EDC8 */ void ftGn_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 14EE1C */ void ftGn_Init_OnLoad(HSD_GObj* gobj);
/* 14EE40 */ void ftGn_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 14EE60 */ void ftGn_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 14EEAC */ void ftGn_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3D29F8 */ extern MotionState ftGn_Init_MotionStateTable[ftCa_MS_SelfCount];
/* 3D2CD8 */ extern char ftGn_Init_DatFilename[];
/* 3D2CE4 */ extern char ftGn_Init_DataName[];
/* 3D2DB4 */ extern char ftGn_Init_AnimDatFilename[];
/* 3D2E30 */ extern Fighter_DemoStrings ftGn_Init_DemoMotionFilenames;
/* 3D2E40 */ extern Fighter_CostumeStrings ftGn_Init_CostumeStrings[];

#endif
