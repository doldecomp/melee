#ifndef MELEE_FT_CHARA_FTSEAK_FTSEAK_SPECIALS_H
#define MELEE_FT_CHARA_FTSEAK_FTSEAK_SPECIALS_H

#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

void ftSk_SpecialS_80110490(Fighter* fp);
void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 arg1, f32 arg8);
void ftSk_SpecialS_80110788(HSD_GObj* gobj);
void ftSk_SpecialS_8011097C(HSD_GObj* gobj);
void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj, Vec3* new_position,
                                  s32 hitbox_id);
void ftSk_SpecialS_ZeroHitboxPositions(HSD_GObj* gobj);
void ftSk_SpecialS_80110AEC(HSD_GObj* gobj);
void ftSk_SpecialS_80110BCC(HSD_GObj* gobj);
void ftSk_SpecialS_80110E4C(HSD_GObj* gobj);
void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj);
void ftSk_SpecialS_80110EE8(HSD_GObj* gobj);
void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj);
f32 ftSk_SpecialS_80110F58(HSD_GObj* gobj);
f32 ftSk_SpecialS_80110F64(HSD_GObj* gobj);
void ftSk_SpecialS_80110F70(HSD_GObj* gobj);
void ftSk_SpecialS_Enter(HSD_GObj* gobj);
void ftSk_SpecialAirS_Enter(HSD_GObj* gobj);
bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj);
void ftSk_SpecialSStart_Anim(HSD_GObj* gobj);
void ftSk_SpecialAirSStart_Anim(HSD_GObj* gobj);
void ftSk_SpecialSStart_IASA(HSD_GObj* gobj);
void ftSk_SpecialAirSStart_IASA(HSD_GObj* gobj);
void ftSk_SpecialSStart_Phys(HSD_GObj* gobj);
void ftSk_SpecialAirSStart_Phys(HSD_GObj* gobj);
void ftSk_SpecialSStart_Coll(HSD_GObj* gobj);
void ftSk_SpecialAirSStart_Coll(HSD_GObj* gobj);
void ftSk_SpecialS_80111440(HSD_GObj* gobj);
void ftSk_SpecialS_801114E4(HSD_GObj* gobj);
void ftSk_SpecialSLoop_Anim(HSD_GObj* gobj);
void ftSk_SpecialAirSLoop_Anim(HSD_GObj* gobj);
void ftSk_SpecialSLoop_IASA(HSD_GObj* gobj);
void ftSk_SpecialAirSLoop_IASA(HSD_GObj* gobj);
void ftSk_SpecialSLoop_Phys(HSD_GObj* gobj);
void ftSk_SpecialAirSLoop_Phys(HSD_GObj* gobj);
void ftSk_SpecialSLoop_Coll(HSD_GObj* gobj);
void ftSk_SpecialAirSLoop_Coll(HSD_GObj* gobj);
void ftSk_SpecialS_80111830(HSD_GObj* gobj);
void ftSk_SpecialS_80111988(HSD_GObj* gobj);
void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj);
void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj);
void ftSk_SpecialSEnd_IASA(HSD_GObj* gobj);
void ftSk_SpecialAirSEnd_IASA(HSD_GObj* gobj);
void ftSk_SpecialSEnd_Phys(HSD_GObj* gobj);
void ftSk_SpecialAirSEnd_Phys(HSD_GObj* gobj);
void ftSk_SpecialSEnd_Coll(HSD_GObj* gobj);
void ftSk_SpecialAirSEnd_Coll(HSD_GObj* gobj);
void ftSk_SpecialS_80111CB0(HSD_GObj* gobj);
void ftSk_SpecialS_80111D54(HSD_GObj* gobj);
void ftSk_SpecialS_80111DF8(HSD_GObj* gobj);
void ftSk_SpecialS_80111EB4(HSD_GObj* gobj);
bool ftSk_SpecialS_80111F70(HSD_GObj* gobj);
int ftSk_SpecialS_80111FA0(HSD_GObj* gobj);

#endif
