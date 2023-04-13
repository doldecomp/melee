#ifndef MELEE_FT_CHARA_FTSEAK_FTSEAK_SPECIALS_H
#define MELEE_FT_CHARA_FTSEAK_FTSEAK_SPECIALS_H

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <Runtime/platform.h>

void ftSeak_80110490(Fighter* fp);
void ftSeak_80110610(HSD_GObj* fighter_gobj, s32 arg1, f32 arg8);
void ftSeak_80110788(HSD_GObj* fighter_gobj);
void ftSeak_8011097C(HSD_GObj* fighter_gobj);
void ftSeak_UpdateHitboxes(HSD_GObj* fighter_gobj, Vec3* new_position,
                           s32 hitbox_id);
void ftSeak_ZeroHitboxPositions(HSD_GObj* fighter_gobj);
void ftSeak_80110AEC(HSD_GObj* fighter_gobj);
void ftSeak_80110BCC(HSD_GObj* fighter_gobj);
void ftSeak_80110E4C(HSD_GObj* fighter_gobj);
void ftSeak_CheckAndDestroyChain(HSD_GObj* fighter_gobj);
void ftSeak_80110EE8(HSD_GObj* fighter_gobj);
void ftSeak_ChainSomething(HSD_GObj* fighter_gobj);
f32 ftSeak_80110F58(HSD_GObj* fighter_gobj);
f32 ftSeak_80110F64(HSD_GObj* fighter_gobj);
void ftSeak_80110F70(HSD_GObj* fighter_gobj);
void ftSeak_SpecialS_StartMotion(HSD_GObj* fighter_gobj);
void ftSeak_SpecialAirS_StartMotion(HSD_GObj* fighter_gobj);
bool ftSeak_SpecialS_CheckInitChain(HSD_GObj* fighter_gobj);
void ftSeak_SpecialS_Anim(HSD_GObj* fighter_gobj);
void ftSeak_80111308(HSD_GObj* fighter_gobj);
void ftSeak_80111344(HSD_GObj* fighter_gobj);
void ftSeak_80111348(HSD_GObj* fighter_gobj);
void ftSeak_8011134C(HSD_GObj* fighter_gobj);
void ftSeak_8011136C(HSD_GObj* fighter_gobj);
void ftSeak_801113C8(HSD_GObj* fighter_gobj);
void ftSeak_80111404(HSD_GObj* fighter_gobj);
void ftSeak_80111440(HSD_GObj* fighter_gobj);
void ftSeak_801114E4(HSD_GObj* fighter_gobj);
void ftSeak_80111588(HSD_GObj* fighter_gobj);
void ftSeak_80111648(HSD_GObj* fighter_gobj);
void ftSeak_80111708(HSD_GObj* fighter_gobj);
void ftSeak_80111740(HSD_GObj* fighter_gobj);
void ftSeak_80111778(HSD_GObj* fighter_gobj);
void ftSeak_80111798(HSD_GObj* fighter_gobj);
void ftSeak_801117B8(HSD_GObj* fighter_gobj);
void ftSeak_801117F4(HSD_GObj* fighter_gobj);
void ftSeak_80111830(HSD_GObj* fighter_gobj);
void ftSeak_80111988(HSD_GObj* fighter_gobj);
void ftSeak_80111A48(HSD_GObj* fighter_gobj);
void ftSeak_80111B1C(HSD_GObj* fighter_gobj);
void ftSeak_80111BF0(HSD_GObj* fighter_gobj);
void ftSeak_80111BF4(HSD_GObj* fighter_gobj);
void ftSeak_80111BF8(HSD_GObj* fighter_gobj);
void ftSeak_80111C18(HSD_GObj* fighter_gobj);
void ftSeak_80111C38(HSD_GObj* fighter_gobj);
void ftSeak_80111C74(HSD_GObj* fighter_gobj);
void ftSeak_80111CB0(HSD_GObj* fighter_gobj);
void ftSeak_80111D54(HSD_GObj* fighter_gobj);
void ftSeak_80111DF8(HSD_GObj* fighter_gobj);
void ftSeak_80111EB4(HSD_GObj* fighter_gobj);
bool ftSeak_80111F70(HSD_GObj* fighter_gobj);
int ftSeak_80111FA0(HSD_GObj* fighter_gobj);

#endif
