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
void ftSk_SpecialS_StartMotion(HSD_GObj* gobj);
void ftSk_SpecialAirS_StartMotion(HSD_GObj* gobj);
bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj);
void ftSk_SpecialS_Anim(HSD_GObj* gobj);
void ftSk_SpecialS_80111308(HSD_GObj* gobj);
void ftSk_SpecialS_80111344(HSD_GObj* gobj);
void ftSk_SpecialS_80111348(HSD_GObj* gobj);
void ftSk_SpecialS_8011134C(HSD_GObj* gobj);
void ftSk_SpecialS_8011136C(HSD_GObj* gobj);
void ftSk_SpecialS_801113C8(HSD_GObj* gobj);
void ftSk_SpecialS_80111404(HSD_GObj* gobj);
void ftSk_SpecialS_80111440(HSD_GObj* gobj);
void ftSk_SpecialS_801114E4(HSD_GObj* gobj);
void ftSk_SpecialS_80111588(HSD_GObj* gobj);
void ftSk_SpecialS_80111648(HSD_GObj* gobj);
void ftSk_SpecialS_80111708(HSD_GObj* gobj);
void ftSk_SpecialS_80111740(HSD_GObj* gobj);
void ftSk_SpecialS_80111778(HSD_GObj* gobj);
void ftSk_SpecialS_80111798(HSD_GObj* gobj);
void ftSk_SpecialS_801117B8(HSD_GObj* gobj);
void ftSk_SpecialS_801117F4(HSD_GObj* gobj);
void ftSk_SpecialS_80111830(HSD_GObj* gobj);
void ftSk_SpecialS_80111988(HSD_GObj* gobj);
void ftSk_SpecialS_80111A48(HSD_GObj* gobj);
void ftSk_SpecialS_80111B1C(HSD_GObj* gobj);
void ftSk_SpecialS_80111BF0(HSD_GObj* gobj);
void ftSk_SpecialS_80111BF4(HSD_GObj* gobj);
void ftSk_SpecialS_80111BF8(HSD_GObj* gobj);
void ftSk_SpecialS_80111C18(HSD_GObj* gobj);
void ftSk_SpecialS_80111C38(HSD_GObj* gobj);
void ftSk_SpecialS_80111C74(HSD_GObj* gobj);
void ftSk_SpecialS_80111CB0(HSD_GObj* gobj);
void ftSk_SpecialS_80111D54(HSD_GObj* gobj);
void ftSk_SpecialS_80111DF8(HSD_GObj* gobj);
void ftSk_SpecialS_80111EB4(HSD_GObj* gobj);
bool ftSk_SpecialS_80111F70(HSD_GObj* gobj);
int ftSk_SpecialS_80111FA0(HSD_GObj* gobj);

#endif
