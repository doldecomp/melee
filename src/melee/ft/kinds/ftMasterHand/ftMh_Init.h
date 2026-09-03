#ifndef GALE01_14FC68
#define GALE01_14FC68

#include "ft/types.h"

#include "ftMasterHand/forward.h"
#include <baselib/forward.h>

/* 14FC68 */ void ftMh_Init_OnDeath(HSD_GObj* gobj);
/* 14FC6C */ void ftMh_Init_OnLoad(HSD_GObj* gobj);
/* 14FDD0 */ void ftMh_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 3D3A30 */ extern MotionState ftMh_Init_MotionStateTable[ftMh_MS_SelfCount];
/* 3D4070 */ extern char ftMh_Init_DatFilename[];
/* 3D407C */ extern char ftMh_Init_DataName[];
/* 3D40B8 */ extern char ftMh_Init_AnimDatFilename[];
/* 3D40C4 */ extern Fighter_CostumeStrings ftMh_Init_CostumeStrings[];

#endif
