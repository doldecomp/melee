#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H

#include <Runtime/platform.h>

void ftIceClimber_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftIceClimber_OnItemVisible(HSD_GObj* fighter_gobj);
void ftIceClimber_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftIceClimber_OnLoad(HSD_GObj* fighter_gobj);
void ftIceClimber_OnDeath(HSD_GObj* fighter_gobj);
void ftIceClimber_8011F060(HSD_GObj* fighter_gobj);
void ftIceClimber_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftIceClimber_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftIceClimber_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftIceClimber_OnKnockbackExit(HSD_GObj* fighter_gobj);

#endif
