#ifndef GALE01_149E34
#define GALE01_149E34

#include <platform.h>

#include "ft/forward.h"

#include "ft/types.h"

#include "ftPikachu/forward.h"
#include <baselib/forward.h>

/* 149E34 */ void ftPc_Init_OnLoad(HSD_GObj* gobj);
/* 149EAC */ void ftPc_Init_OnDeath(HSD_GObj* gobj);
/* 149FE4 */ void ftPc_Init_OnItemPickup(HSD_GObj* gobj, bool);
/* 14A0C4 */ void ftPc_Init_OnItemInvisible(HSD_GObj* gobj);
/* 14A10C */ void ftPc_Init_OnItemVisible(HSD_GObj* gobj);
/* 14A154 */ void ftPc_Init_OnItemDrop(HSD_GObj* gobj, bool);
/* 14A1A8 */ void ftPc_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 14A1C8 */ void ftPc_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 14A20C */ void ftPc_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 3D1EA8 */ extern MotionState ftPc_Init_MotionStateTable[ftPk_MS_SelfCount];
/* 3D21E8 */ extern char ftPc_Init_DatFilename[];
/* 3D21F4 */ extern char ftPc_Init_DataName[];
/* 3D2328 */ extern char ftPc_Init_AnimDatFilename[];
/* 3D23A4 */ extern Fighter_DemoStrings ftPc_Init_DemoMotionFilenames;
/* 3D23B4 */ extern Fighter_CostumeStrings ftPc_Init_CostumeStrings[];

#endif
