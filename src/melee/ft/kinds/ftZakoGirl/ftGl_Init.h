#ifndef GALE01_14F418
#define GALE01_14F418

#include <platform.h>

#include "ft/types.h"

#include <baselib/forward.h>

/* 14F418 */ void ftGl_Init_OnDeath(HSD_GObj* gobj);
/* 14F440 */ void ftGl_Init_OnLoad(HSD_GObj* gobj);
/* 14F460 */ void ftGl_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 14F540 */ void ftGl_Init_OnItemInvisible(HSD_GObj* gobj);
/* 14F588 */ void ftGl_Init_OnItemVisible(HSD_GObj* gobj);
/* 14F5D0 */ void ftGl_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 14F624 */ void ftGl_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 3D3568 */ extern char ftGl_Init_DatFilename[];
/* 3D3574 */ extern char ftGl_Init_DataName[];
/* 3D35A0 */ extern char ftGl_Init_AnimDatFilename[];
/* 3D35D8 */ extern Fighter_CostumeStrings ftGl_Init_CostumeStrings[];

#endif
