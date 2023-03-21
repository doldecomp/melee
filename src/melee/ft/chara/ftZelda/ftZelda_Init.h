#ifndef MELEE_FT_CHARA_FTZELDA_FTZELDA1_H
#define MELEE_FT_CHARA_FTZELDA_FTZELDA1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftZelda_MotionStateTable[];
extern char lbl_803CFC98[];
extern char lbl_803CFCA4[];
extern Fighter_CostumeStrings lbl_803CFEB0[];
extern char lbl_803CFE24[];
extern Fighter_DemoStrings lbl_803CFEA0;

void ftZelda_OnDeath(HSD_GObj* gobj);
void ftZelda_OnLoad(HSD_GObj* gobj);
void ftZelda_801393AC(HSD_GObj* gobj);
void ftZelda_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftZelda_OnItemInvisible(HSD_GObj* gobj);
void ftZelda_OnItemVisible(HSD_GObj* gobj);
void ftZelda_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj);
void ftZelda_801395C8(HSD_GObj* gobj);
void ftZelda_OnKnockbackEnter(HSD_GObj* gobj);
void ftZelda_OnKnockbackExit(HSD_GObj* gobj);

#endif
