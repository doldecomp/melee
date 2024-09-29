#ifndef GALE01_0E2888
#define GALE01_0E2888

#include <platform.h>

#include "ftCaptain/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

/* 0E2888 */ void ftCa_Init_OnDeath(HSD_GObj* gobj);
/* 0E28C8 */ void ftCa_Init_800E28C8(HSD_GObj* gobj);
/* 0E28E8 */ void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 0E29C8 */ void ftCa_Init_OnItemInvisible(HSD_GObj* gobj);
/* 0E2A10 */ void ftCa_Init_OnItemVisible(HSD_GObj* gobj);
/* 0E2A58 */ void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 0E2AAC */ void ftCa_Init_OnLoadForGanon(Fighter*);
/* 0E2AEC */ void ftCa_Init_OnLoad(HSD_GObj* gobj);
/* 0E2B40 */ void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 3C72B8 */ extern MotionState ftCa_Init_MotionStateTable[ftCa_MS_SelfCount];
/* 3C7598 */ extern char ftCa_Init_DatFilename[];
/* 3C75A4 */ extern char ftCa_Init_DataName[];
/* 3C76A0 */ extern char ftCa_Init_AnimDatFilename[];
/* 3C772C */ extern Fighter_DemoStrings ftCa_Init_DemoMotionFilenames;
/* 3C773C */ extern Fighter_CostumeStrings ftCa_Init_CostumeStrings[];

#endif
