#ifndef MELEE_FT_CHARA_FTSEAK_FTSEAK_INIT_H
#define MELEE_FT_CHARA_FTSEAK_FTSEAK_INIT_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftSk_Init_MotionStateTable[];
extern char ftSk_Init_DatFilename[];
extern char ftSk_Init_DataName[];
extern char ftSk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftSk_Init_DemoMotionFilenames;
extern Fighter_CostumeStrings ftSk_Init_CostumeStrings[];

void ftSk_Init_OnDeath(HSD_GObj* gobj);
void ftSk_Init_OnLoad(HSD_GObj* gobj);
void ftSk_Init_80110198(HSD_GObj* gobj);
void ftSk_Init_UnkMotionStates4(HSD_GObj* gobj);
void ftSk_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftSk_Init_OnItemInvisible(HSD_GObj* gobj);
void ftSk_Init_OnItemVisible(HSD_GObj* gobj);
void ftSk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftSk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftSk_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftSk_Init_OnKnockbackExit(HSD_GObj* gobj);

#endif
