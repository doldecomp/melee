#ifndef GALE01_110490
#define GALE01_110490

#include <platform.h>

#include "ft/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 110490 */ void ftSk_SpecialS_80110490(Fighter* fp);
/* 110610 */ void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 arg1, float arg8);
/* 110788 */ void ftSk_SpecialS_80110788(HSD_GObj* gobj);
/* 11097C */ void ftSk_SpecialS_8011097C(HSD_GObj* gobj);
/* 110980 */ void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj,
                                               Vec3* new_position,
                                               s32 hitbox_id);
/* 110A80 */ void ftSk_SpecialS_ZeroHitboxPositions(HSD_GObj* gobj);
/* 110AEC */ void ftSk_SpecialS_80110AEC(HSD_GObj* gobj);
/* 110BCC */ void ftSk_SpecialS_80110BCC(HSD_GObj* gobj);
/* 110E4C */ void ftSk_SpecialS_80110E4C(HSD_GObj* gobj);
/* 110E88 */ void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj);
/* 110EE8 */ void ftSk_SpecialS_80110EE8(HSD_GObj* gobj);
/* 110F18 */ void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj);
/* 110F58 */ float ftSk_SpecialS_80110F58(HSD_GObj* gobj);
/* 110F64 */ float ftSk_SpecialS_80110F64(HSD_GObj* gobj);
/* 110F70 */ void ftSk_SpecialS_80110F70(HSD_GObj* gobj);
/* 111038 */ void ftSk_SpecialS_Enter(HSD_GObj* gobj);
/* 11108C */ void ftSk_SpecialAirS_Enter(HSD_GObj* gobj);
/* 1110E8 */ bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj);
/* 1112CC */ void ftSk_SpecialSStart_Anim(HSD_GObj* gobj);
/* 111308 */ void ftSk_SpecialAirSStart_Anim(HSD_GObj* gobj);
/* 111344 */ void ftSk_SpecialSStart_IASA(HSD_GObj* gobj);
/* 111348 */ void ftSk_SpecialAirSStart_IASA(HSD_GObj* gobj);
/* 11134C */ void ftSk_SpecialSStart_Phys(HSD_GObj* gobj);
/* 11136C */ void ftSk_SpecialAirSStart_Phys(HSD_GObj* gobj);
/* 1113C8 */ void ftSk_SpecialSStart_Coll(HSD_GObj* gobj);
/* 111404 */ void ftSk_SpecialAirSStart_Coll(HSD_GObj* gobj);
/* 111440 */ void ftSk_SpecialS_80111440(HSD_GObj* gobj);
/* 1114E4 */ void ftSk_SpecialS_801114E4(HSD_GObj* gobj);
/* 111588 */ void ftSk_SpecialS_Anim(HSD_GObj* gobj);
/* 111648 */ void ftSk_SpecialAirS_Anim(HSD_GObj* gobj);
/* 111708 */ void ftSk_SpecialS_IASA(HSD_GObj* gobj);
/* 111740 */ void ftSk_SpecialAirS_IASA(HSD_GObj* gobj);
/* 111778 */ void ftSk_SpecialS_Phys(HSD_GObj* gobj);
/* 111798 */ void ftSk_SpecialAirS_Phys(HSD_GObj* gobj);
/* 1117B8 */ void ftSk_SpecialS_Coll(HSD_GObj* gobj);
/* 1117F4 */ void ftSk_SpecialAirS_Coll(HSD_GObj* gobj);
/* 111830 */ void ftSk_SpecialS_80111830(HSD_GObj* gobj);
/* 111988 */ void ftSk_SpecialS_80111988(HSD_GObj* gobj);
/* 111A48 */ void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj);
/* 111B1C */ void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj);
/* 111BF0 */ void ftSk_SpecialSEnd_IASA(HSD_GObj* gobj);
/* 111BF4 */ void ftSk_SpecialAirSEnd_IASA(HSD_GObj* gobj);
/* 111BF8 */ void ftSk_SpecialSEnd_Phys(HSD_GObj* gobj);
/* 111C18 */ void ftSk_SpecialAirSEnd_Phys(HSD_GObj* gobj);
/* 111C38 */ void ftSk_SpecialSEnd_Coll(HSD_GObj* gobj);
/* 111C74 */ void ftSk_SpecialAirSEnd_Coll(HSD_GObj* gobj);
/* 111CB0 */ void ftSk_SpecialS_80111CB0(HSD_GObj* gobj);
/* 111D54 */ void ftSk_SpecialS_80111D54(HSD_GObj* gobj);
/* 111DF8 */ void ftSk_SpecialS_80111DF8(HSD_GObj* gobj);
/* 111EB4 */ void ftSk_SpecialS_80111EB4(HSD_GObj* gobj);
/* 111F70 */ bool ftSk_SpecialS_80111F70(HSD_GObj* gobj);
/* 111FA0 */ int ftSk_SpecialS_80111FA0(HSD_GObj* gobj);

#endif
