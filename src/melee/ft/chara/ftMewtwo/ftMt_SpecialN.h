/// @file
/// Neutral Special - Shadow Ball (SpecialN/SpecialAirN)
#ifndef GALE01_146CCC
#define GALE01_146CCC

#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 146CCC */ s32 ftMt_SpecialN_GetChargeLevel(HSD_GObj* gobj, s32* chargeLevel,
                                              s32* chargeCycles);
/* 146D24 */ bool ftMt_SpecialN_CheckShadowBallRemove(HSD_GObj* gobj);
/* 146D74 */ bool ftMt_SpecialN_CheckShadowBallCancel(HSD_GObj* gobj);
/* 146DC8 */ void ftMt_SpecialN_SetNULL(HSD_GObj* gobj);
/* 146E30 */ void ftMt_SpecialN_OnTakeDamage(HSD_GObj* gobj);
/* 146ED0 */ void ftMt_SpecialN_OnDeath(HSD_GObj* gobj);
/* 146FA8 */ void ftMt_SpecialN_ReleaseShadowBall(HSD_GObj* gobj);
/* 1471C8 */ void ftMt_SpecialN_PlayChargeSFX(HSD_GObj* gobj);
/* 147320 */ void ftMt_SpecialN_Enter(HSD_GObj* gobj);
/* 1473F4 */ void ftMt_SpecialAirN_Enter(HSD_GObj* gobj);
/* 1474C0 */ void ftMt_SpecialNStart_Anim(HSD_GObj* gobj);
/* 14764C */ void ftMt_SpecialNLoop_Anim(HSD_GObj* gobj);
/* 147850 */ void ftMt_SpecialNLoopFull_Anim(HSD_GObj* gobj);
/* 147880 */ void ftMt_SpecialNCancel_Anim(HSD_GObj* gobj);
/* 147910 */ void ftMt_SpecialNEnd_Anim(HSD_GObj* gobj);
/* 147954 */ void ftMt_SpecialAirNStart_Anim(HSD_GObj* gobj);
/* 147AEC */ void ftMt_SpecialAirNLoop_Anim(HSD_GObj* gobj);
/* 147CF0 */ void ftMt_SpecialAirNLoopFull_Anim(HSD_GObj* gobj);
/* 147D20 */ void ftMt_SpecialAirNCancel_Anim(HSD_GObj* gobj);
/* 147DB0 */ void ftMt_SpecialAirNEnd_Anim(HSD_GObj* gobj);
/* 147E30 */ void ftMt_SpecialNStart_IASA(HSD_GObj* gobj);
/* 147E34 */ void ftMt_SpecialNLoop_IASA(HSD_GObj* gobj);
/* 14800C */ void ftMt_SpecialNLoopFull_IASA(HSD_GObj* gobj);
/* 1481CC */ void ftMt_SpecialNCancel_IASA(HSD_GObj* gobj);
/* 1481D0 */ void ftMt_SpecialNEnd_IASA(HSD_GObj* gobj);
/* 1481D4 */ void ftMt_SpecialAirNStart_IASA(HSD_GObj* gobj);
/* 1481D8 */ void ftMt_SpecialAirNLoop_IASA(HSD_GObj* gobj);
/* 148354 */ void ftMt_SpecialAirNLoopFull_IASA(HSD_GObj* gobj);
/* 1484B8 */ void ftMt_SpecialAirNCancel_IASA(HSD_GObj* gobj);
/* 1484BC */ void ftMt_SpecialAirNEnd_IASA(HSD_GObj* gobj);
/* 1484C0 */ void ftMt_SpecialNStart_Phys(HSD_GObj* gobj);
/* 1484E0 */ void ftMt_SpecialNLoop_Phys(HSD_GObj* gobj);
/* 148500 */ void ftMt_SpecialNLoopFull_Phys(HSD_GObj* gobj);
/* 148520 */ void ftMt_SpecialNCancel_Phys(HSD_GObj* gobj);
/* 148540 */ void ftMt_SpecialNEnd_Phys(HSD_GObj* gobj);
/* 148560 */ void ftMt_SpecialAirNStart_Phys(HSD_GObj* gobj);
/* 148580 */ void ftMt_SpecialAirNLoop_Phys(HSD_GObj* gobj);
/* 1485A0 */ void ftMt_SpecialAirNLoopFull_Phys(HSD_GObj* gobj);
/* 1485C0 */ void ftMt_SpecialAirNCancel_Phys(HSD_GObj* gobj);
/* 1485E0 */ void ftMt_SpecialAirNEnd_Phys(HSD_GObj* gobj);
/* 148600 */ void ftMt_SpecialNStart_Coll(HSD_GObj* gobj);
/* 14868C */ void ftMt_SpecialNLoop_Coll(HSD_GObj* gobj);
/* 148718 */ void ftMt_SpecialNLoopFull_Coll(HSD_GObj* gobj);
/* 1487A4 */ void ftMt_SpecialNCancel_Coll(HSD_GObj* gobj);
/* 148830 */ void ftMt_SpecialNEnd_Coll(HSD_GObj* gobj);
/* 1488BC */ void ftMt_SpecialAirNStart_Coll(HSD_GObj* gobj);
/* 148948 */ void ftMt_SpecialAirNLoop_Coll(HSD_GObj* gobj);
/* 1489D4 */ void ftMt_SpecialAirNLoopFull_Coll(HSD_GObj* gobj);
/* 148A60 */ void ftMt_SpecialAirNCancel_Coll(HSD_GObj* gobj);
/* 148AEC */ void ftMt_SpecialAirNEnd_Coll(HSD_GObj* gobj);
/* 148B78 */ void ftMt_SpecialN_Shoot(HSD_GObj* gobj);

#endif
