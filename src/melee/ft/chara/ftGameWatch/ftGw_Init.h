#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_INIT_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FTGAMEWATCH_INIT_H

#include "ft/types.h"

extern MotionState ftGw_Init_MotionStateTable[];
extern char ftGw_Init_DatFilename[];
extern char ftGw_Init_DataName[];
extern Fighter_CostumeStrings ftGw_Init_CostumeStrings[];
extern char ftGw_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftGw_Init_DemoMotionFilenames;

// General callbacks
void ftGw_Init_OnDeath(HSD_GObj* gobj);
void ftGw_Init_OnLoad(HSD_GObj* gobj);
void ftGw_Init_OnDamage(HSD_GObj* gobj);
void ftGw_Init_8014A538(HSD_GObj* gobj);
void ftGw_Init_OnItemPickup(HSD_GObj* gobj, bool arg1);
void ftGw_Init_OnItemInvisible(HSD_GObj* gobj);
void ftGw_Init_OnItemVisible(HSD_GObj* gobj);
void ftGw_Init_OnItemDrop(HSD_GObj* gobj, bool dropItemFlag);
void ftGw_Init_UnkMotionStates4(HSD_GObj* gobj);
void ftGameWatch_CopySpecialAttrs(HSD_GObj* gobj);
void ftGw_Init_8014A7F4(HSD_GObj* gobj, ItemModStruct* item_mod);
void ftGw_Init_8014A814(HSD_GObj* gobj, ItemModStruct* item_mod);
void ftGw_Init_OnAbsorb(HSD_GObj* gobj);

#endif
