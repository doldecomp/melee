#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H

#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

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

/* static */ void func_8011F190(HSD_GObj* fighter_gobj);
/* static */ void func_80122898(HSD_GObj* fighter_gobj);
/* static */ void func_80121164(HSD_GObj* fighter_gobj);
/* static */ void func_8011F68C(HSD_GObj* fighter_gobj);
void func_8011F16C(HSD_GObj* fighter_gobj, uint arg1);
void lbl_8011F500(HSD_GObj*);
void ftIceClimber_SpecialN_StartAction(HSD_GObj* fighter_gobj);
void ftIceClimber_SpecialAirN_StartAction(HSD_GObj* fighter_gobj);
void lbl_8011F318(HSD_GObj* gobj);
void lbl_8011F354(HSD_GObj* gobj);

#endif
