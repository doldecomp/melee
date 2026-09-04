#ifndef GALE01_132A0C
#define GALE01_132A0C

#include <platform.h>

#include "ft/types.h"

#include "ftKoopa/forward.h"

/* 132A0C */ void ftKp_Init_OnDeath(Fighter_GObj* gobj);
/* 132A64 */ void ftKp_Init_UnkMotionStates3(Fighter_GObj* gobj);
/* 132A84 */ void ftKp_Init_OnLoadForGKoopa(Fighter* fp);
/* 132ABC */ void ftKp_Init_OnLoad(Fighter_GObj* gobj);
/* 132B38 */ void ftKp_Init_80132B38(void);
/* 132B3C */ void ftKp_Init_OnItemPickup(Fighter_GObj* gobj, bool flag);
/* 132C1C */ void ftKp_Init_OnItemInvisible(Fighter_GObj* gobj);
/* 132C64 */ void ftKp_Init_OnItemVisible(Fighter_GObj* gobj);
/* 132CAC */ void ftKp_Init_OnItemDrop(Fighter_GObj* gobj, bool bool1);
/* 132D00 */ void ftKp_Init_LoadSpecialAttrs(Fighter_GObj* gobj);
/* 132D38 */ void ftKp_Init_OnKnockbackEnter(Fighter_GObj* gobj);
/* 132D7C */ void ftKp_Init_OnKnockbackExit(Fighter_GObj* gobj);
/* 3CEDC0 */ extern MotionState ftKp_Init_MotionStateTable[ftKp_MS_SelfCount];
/* 3CF0A0 */ extern char ftKp_Init_DatFilename[];
/* 3CF0AC */ extern char ftKp_Init_DataName[];
/* 3CF1E0 */ extern char ftKp_Init_AnimDatFilename[];
/* 3CF25C */ extern Fighter_DemoStrings ftKp_Init_DemoMotionFilenames;
/* 3CF26C */ extern Fighter_CostumeStrings ftKp_Init_CostumeStrings[];
/* 45A090 */ extern UnkCostumeStruct ftKp_CostumeList[4];

#endif
