#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftPopo_MotionStateTable[];
extern char lbl_803CD610[];
extern char lbl_803CD61C[];
extern Fighter_CostumeStrings lbl_803CD7C4[];
extern char lbl_803CD738[];
extern Fighter_DemoStrings lbl_803CD7B4;

void ftIceClimber_OnItemInvisible(HSD_GObj* gobj);
void ftIceClimber_OnItemVisible(HSD_GObj* gobj);
void ftIceClimber_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftIceClimber_OnLoad(HSD_GObj* gobj);
void ftIceClimber_OnDeath(HSD_GObj* gobj);
void ftIceClimber_8011F060(HSD_GObj* gobj);
void ftIceClimber_LoadSpecialAttrs(HSD_GObj* gobj);
void ftIceClimber_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftIceClimber_OnKnockbackEnter(HSD_GObj* gobj);
void ftIceClimber_OnKnockbackExit(HSD_GObj* gobj);

/* static */ void ftIceClimber_8011F190(HSD_GObj* gobj);
/* static */ void ftIceClimber_80122898(HSD_GObj* gobj);
/* static */ void ftIceClimber_80121164(HSD_GObj* gobj);
/* static */ void ftIceClimber_8011F68C(HSD_GObj* gobj);
void ftIceClimber_8011F16C(HSD_GObj* gobj, uint arg1);
void ftIceClimber_8011F500(HSD_GObj*);
void ftIceClimber_SpecialN_StartMotion(HSD_GObj* gobj);
void ftIceClimber_SpecialAirN_StartMotion(HSD_GObj* gobj);
void ftIceClimber_8011F318(HSD_GObj* gobj);
void ftIceClimber_8011F354(HSD_GObj* gobj);
void ftIceClimber_8011F390(HSD_GObj*);
void ftIceClimber_8011F394(HSD_GObj*);
void ftIceClimber_8011F398(HSD_GObj*);
void ftIceClimber_8011F3B8(HSD_GObj*);
void ftIceClimber_8011F3D8(HSD_GObj*);
void ftIceClimber_8011F454(HSD_GObj*);
bool ftIceClimber_8011F6FC(HSD_GObj*);

#endif
