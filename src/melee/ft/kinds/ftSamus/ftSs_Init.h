#ifndef GALE01_12832C
#define GALE01_12832C

#include <platform.h>

#include "ft/types.h"

#include "ftSamus/forward.h"
#include <baselib/forward.h>

/* 12832C */ void ftSs_Init_OnDeath(HSD_GObj* gobj);
/* 12837C */ void ftSs_Init_OnLoad(HSD_GObj* gobj);
/* 128428 */ void ftSs_Init_80128428(HSD_GObj* gobj);
/* 128464 */ void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 128544 */ void ftSs_Init_OnItemInvisible(HSD_GObj* gobj);
/* 12858C */ void ftSs_Init_OnItemVisible(HSD_GObj* gobj);
/* 1285D4 */ void ftSs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
/* 128628 */ void ftSs_Init_UnkMotionStates4(HSD_GObj* gobj);
/* 128684 */ void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 128770 */ void ftSs_Init_80128770(HSD_AObj* gobj, float rate);
/* 1287C4 */ void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj,
                                                   s32 motion_state,
                                                   float anim_speed);
/* 128944 */ void ftSs_Init_80128944(HSD_GObj* gobj, float farg1, float farg2);
/* 128A1C */ bool ftSs_Init_80128A1C(HSD_GObj* gobj, UNK_T arg1, float farg1);
/* 128AC8 */ float ftSs_Init_80128AC8(HSD_GObj* gobj, float farg1,
                                      float farg2);
/* 128B1C */ void ftSs_Init_80128B1C(HSD_GObj* gobj, float, float, float);
/* 3CE2D0 */ extern MotionState ftSs_Init_MotionStateTable[ftSs_MS_SelfCount];
/* 3CE510 */ extern char ftSs_Init_DatFilename[];
/* 3CE51C */ extern char ftSs_Init_DataName[];
/* 3CE5EC */ extern char ftSs_Init_AnimDatFilename[];
/* 3CE668 */ extern Fighter_DemoStrings ftSs_Init_DemoMotionFilenames;
/* 3CE678 */ extern Fighter_CostumeStrings ftSs_Init_CostumeStrings[];

#endif
