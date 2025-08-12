#ifndef GALE01_14F9CC
#define GALE01_14F9CC

#include "ft/types.h"

#include "ftSandbag/forward.h"
#include <baselib/forward.h>

/* 14F9CC */ void ftSb_Init_OnDeath(HSD_GObj* gobj);
/* 14F9D0 */ void ftSb_Init_OnLoad(HSD_GObj* gobj);
/* 14FA30 */ void ftSb_Init_8014FA30(Fighter* fp);
/* 14FB78 */ void ftSb_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 14FB9C */ void ftSb_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 14FBA0 */ void ftSb_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 14FBA4 */ void ftSb_Init_8014FBA4(HSD_GObj* gobj);
/* 14FC20 */ void ftSb_WaitReverse_Anim(HSD_GObj* gobj);
/* 14FC24 */ void ftSb_WaitReverse_IASA(HSD_GObj* gobj);
/* 14FC28 */ void ftSb_WaitReverse_Phys(HSD_GObj* gobj);
/* 14FC48 */ void ftSb_WaitReverse_Coll(HSD_GObj* gobj);
/* 3D3998 */ extern MotionState ftSb_Init_MotionStateTable[ftSb_MS_SelfCount];
/* 3D39B8 */ extern char ftSb_Init_DatFilename[];
/* 3D39C4 */ extern char ftSb_Init_DataName[];
/* 3D3A18 */ extern char ftSb_Init_AnimDatFilename[];
/* 3D3A24 */ extern Fighter_CostumeStrings ftSb_Init_CostumeStrings[];

#endif
