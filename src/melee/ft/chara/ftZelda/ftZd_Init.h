#ifndef MELEE_FT_CHARA_FTZELDA_FTZELDA1_H
#define MELEE_FT_CHARA_FTZELDA_FTZELDA1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftZd_Init_MotionStateTable[];
extern char ftZd_Init_DatFilename[];
extern char ftZd_Init_DataName[];
extern Fighter_CostumeStrings ftZd_Init_CostumeStrings[];
extern char ftZd_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftZd_Init_DemoMotionFilenames;

void ftZd_Init_OnDeath(HSD_GObj* gobj);
void ftZd_Init_OnLoad(HSD_GObj* gobj);
void ftZd_Init_801393AC(HSD_GObj* gobj);
void ftZd_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftZd_Init_OnItemInvisible(HSD_GObj* gobj);
void ftZd_Init_OnItemVisible(HSD_GObj* gobj);
void ftZd_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftZd_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftZd_Init_801395C8(HSD_GObj* gobj);
void ftZd_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftZd_Init_OnKnockbackExit(HSD_GObj* gobj);

#endif
