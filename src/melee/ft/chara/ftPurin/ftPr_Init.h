#ifndef GALE01_13C2F8
#define GALE01_13C2F8

#include <platform.h>

#include "ftPurin/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ft/types.h"

/* 13C2F8 */ void ftPr_Init_8013C2F8(void);
/* 13C318 */ void ftPr_Init_OnDeath(HSD_GObj* gobj);
/* 13C340 */ void ftPr_Init_OnUserDataRemove(HSD_GObj* gobj);
/* 13C360 */ void ftPr_Init_8013C360(HSD_GObj* gobj);
/* 13C494 */ void ftPr_Init_8013C494(HSD_GObj* gobj);
/* 13C4F0 */ void ftPr_Init_UnkMtxFunc0(HSD_GObj* gobj, int arg1, Mtx vmtx);
/* 13C614 */ void ftPr_Init_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2);
/* 13C664 */ HSD_JObj* ftPr_Init_UnkMotionStates6(HSD_GObj* gobj);
/* 13C67C */ void ftPr_Init_OnLoad(HSD_GObj* gobj);
/* 13C6EC */ void ftPr_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 13C798 */ void ftPr_Init_OnItemInvisible(HSD_GObj* gobj);
/* 13C7E8 */ void ftPr_Init_OnItemVisible(HSD_GObj* gobj);
/* 13C838 */ void ftPr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
/* 13C88C */ void ftPr_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 13C8C4 */ void ftPr_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 13C908 */ void ftPr_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 13C94C */ void ftPr_Init_8013C94C(HSD_GObj* gobj);
/* 3CFEF0 */ extern MotionState ftPr_Init_MotionStateTable[ftPr_MS_SelfCount];
/* 3D02F0 */ extern char ftPr_Init_DatFilename[];
/* 3D02FC */ extern char ftPr_Init_DataName[];
/* 3D047C */ extern char ftPr_Init_AnimDatFilename[];
/* 3D04F8 */ extern Fighter_DemoStrings ftPr_Init_DemoMotionFilenames;
/* 3D0508 */ extern Fighter_CostumeStrings ftPr_Init_CostumeStrings[];

#endif
