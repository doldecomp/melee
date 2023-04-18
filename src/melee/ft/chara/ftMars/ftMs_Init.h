#ifndef _ftmars_h_
#define _ftmars_h_

#include <platform.h>

#include "ft/fighter.h"

#include <baselib/gobj.h>

/* 136258 */ void ftMs_Init_OnDeath(HSD_GObj* gobj);
/* 1362b0 */ void ftMs_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
/* 136390 */ void ftMs_Init_OnItemInvisible(HSD_GObj* gobj);
/* 1363d8 */ void ftMs_Init_OnItemVisible(HSD_GObj* gobj);
/* 136420 */ void ftMs_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
/* 136474 */ void ftMs_Init_OnLoadForRoy(Fighter* fp);
/* 1364ac */ void ftMs_Init_OnLoad(HSD_GObj* gobj);
/* 1364e8 */ void ftMs_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 136520 */ void ftMs_Init_OnKnockbackEnter(HSD_GObj* gobj);
/* 136564 */ void ftMs_Init_OnKnockbackExit(HSD_GObj* gobj);
/* 1365a8 */ void ftMs_SpecialN_801365A8(HSD_GObj* gobj);
/* 13666c */ void ftMs_SpecialN_8013666C(HSD_GObj* gobj);
/* 136730 */ void ftMs_SpecialN_80136730(HSD_GObj* gobj);
/* 3cf420 */ extern MotionState ftMs_Init_MotionStateTable[];
/* 3cf820 */ extern char ftMs_Init_DatFilename[];
/* 3cf82c */ extern char ftMs_Init_DataName[];
/* 3cf98c */ extern char ftMs_Init_AnimDatFilename[];
/* 3cfa08 */ extern Fighter_DemoStrings ftMs_Init_DemoMotionFilenames;
/* 3cfa18 */ extern Fighter_CostumeStrings ftMs_Init_CostumeStrings[];

#endif
