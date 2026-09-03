#ifndef GALE01_14F1F0
#define GALE01_14F1F0

#include <platform.h>

#include "ft/types.h"

#include <baselib/forward.h>

/* 14F1F0 */ void ftBo_Init_OnDeath(HSD_GObj* gobj);
/* 14F218 */ void ftBo_Init_OnItemPickup(HSD_GObj* gobj, bool flag);
/* 14F2F8 */ void ftBo_Init_OnItemInvisible(HSD_GObj* gobj);
/* 14F340 */ void ftBo_Init_OnItemVisible(HSD_GObj* gobj);
/* 14F388 */ void ftBo_Init_OnItemDrop(HSD_GObj* gobj, bool flag);
/* 14F3DC */ void ftBo_Init_OnLoad(HSD_GObj* gobj);
/* 14F3FC */ void ftBo_Init_LoadSpecialAttrs(HSD_GObj* gobj);
/* 3D34E8 */ extern char ftBo_Init_DatFilename[];
/* 3D34F4 */ extern char ftBo_Init_DataName[];
/* 3D3520 */ extern char ftBo_Init_AnimDatFilename[];
/* 3D3558 */ extern Fighter_CostumeStrings ftBo_Init_CostumeStrings[];

#endif
