#ifndef MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H
#define MELEE_FT_CHARA_FTDONKEY_FTDONKEY_CALLBACKS_H

#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftDk_Init_MotionStateTable[];
extern char ftDk_Init_DatFilename[];
extern char ftDk_Init_DataName[];
extern Fighter_CostumeStrings ftDk_Init_CostumeStrings[];
extern char ftDk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftDk_Init_DemoMotionFilenames;

void ftDk_Init_8010D774(HSD_GObj* gobj);
void ftDk_Init_8010DB3C(HSD_GObj* gobj);
void ftDk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftDk_Init_OnDeath(HSD_GObj* gobj);
void ftDk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftDk_Init_OnItemInvisible(HSD_GObj* gobj);
void ftDk_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftDk_Init_OnItemVisible(HSD_GObj* gobj);
void ftDk_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftDk_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftDk_Init_OnLoad(HSD_GObj* gobj);
void ftDk_Init_UnkMotionStates4(HSD_GObj* gobj);

#endif
