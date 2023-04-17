#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H

#include <platform.h>
#include "ftCaptain/forward.h"

#include "ft/fighter.h"

#include <baselib/gobj.h>

extern MotionState ftCa_Init_MotionStateTable[];
extern char ftCa_Init_DatFilename[];
extern char ftCa_Init_DataName[];
extern Fighter_CostumeStrings ftCa_Init_CostumeStrings[];
extern char ftCa_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftCa_Init_DemoMotionFilenames;

void ftCa_Init_800E28C8(HSD_GObj* gobj);
void ftCa_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCa_Init_OnDeath(HSD_GObj* gobj);
void ftCa_Init_OnItemDrop(HSD_GObj* gobj, bool);
void ftCa_Init_OnItemInvisible(HSD_GObj* gobj);
void ftCa_Init_OnItemPickup(HSD_GObj* gobj, bool);
void ftCa_Init_OnItemVisible(HSD_GObj* gobj);
void ftCa_Init_OnLoad(HSD_GObj* gobj);
void ftCa_Init_OnLoadForGanon(Fighter*);

#endif
