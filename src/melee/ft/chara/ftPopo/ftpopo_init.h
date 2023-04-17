#ifndef MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H
#define MELEE_FT_CHARA_FTICECLIMBER_FTICECLIMBER1_H

#include <platform.h>
#include <baselib/forward.h>

#include "ft/types.h"

extern MotionState ftPp_Init_MotionStateTable[];
extern char ftPp_Init_DatFilename[];
extern char ftPp_Init_DataName[];
extern Fighter_CostumeStrings ftPp_Init_CostumeStrings[];
extern char ftPp_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftPp_Init_DemoMotionFilenames;

void ftPp_Init_OnItemInvisible(HSD_GObj* gobj);
void ftPp_Init_OnItemVisible(HSD_GObj* gobj);
void ftPp_Init_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftPp_Init_OnLoad(HSD_GObj* gobj);
void ftPp_Init_OnDeath(HSD_GObj* gobj);
void ftPp_Init_8011F060(HSD_GObj* gobj);
void ftPp_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftPp_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftPp_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftPp_Init_OnKnockbackExit(HSD_GObj* gobj);

/* static */ void ftPp_Init_8011F190(HSD_GObj* gobj);
/* static */ void ftPp_SpecialHi_80122898(HSD_GObj* gobj);
/* static */ void ftPp_SpecialS_80121164(HSD_GObj* gobj);
/* static */ void ftPp_SpecialN_8011F68C(HSD_GObj* gobj);
void ftPp_Init_8011F16C(HSD_GObj* gobj, uint arg1);
void ftPp_SpecialN_8011F500(HSD_GObj*);
void ftPp_SpecialN_Enter(HSD_GObj* gobj);
void ftPp_SpecialAirN_Enter(HSD_GObj* gobj);
void ftPp_SpecialN_Anim(HSD_GObj* gobj);
void ftPp_SpecialAirN_Anim(HSD_GObj* gobj);
void ftPp_SpecialN_IASA(HSD_GObj*);
void ftPp_SpecialAirN_IASA(HSD_GObj*);
void ftPp_SpecialN_Phys(HSD_GObj*);
void ftPp_SpecialAirN_Phys(HSD_GObj*);
void ftPp_SpecialN_Coll(HSD_GObj*);
void ftPp_SpecialAirN_Coll(HSD_GObj*);
bool ftPp_SpecialN_8011F6FC(HSD_GObj*);

#endif
