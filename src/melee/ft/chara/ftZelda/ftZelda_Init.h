#ifndef MELEE_FT_CHARA_FTZELDA_FTZELDA1_H
#define MELEE_FT_CHARA_FTZELDA_FTZELDA1_H

#include <platform.h>
#include <baselib/forward.h>

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
