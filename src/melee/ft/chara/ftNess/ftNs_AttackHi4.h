#ifndef GALE01_114EB8
#define GALE01_114EB8

#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 114EB8 */ void ftNs_AttackHi4_YoyoUpdateHitPos(HSD_GObj* gobj);
/* 114F0C */ void ftNs_AttackHi4_YoyoCheckTimedRehit(HSD_GObj* gobj);
/* 114FF8 */ s32 ftNs_AttackHi4_YoyoCheckEnvColl(HSD_GObj* gobj, Vec3* ECBUnk,
                                                 Vec3* ECBUnk2,
                                                 float float_unk);
/* 115114 */ void ftNs_AttackHi4_YoyoSetUnkPos(HSD_GObj* gobj, Vec3* arg1);
/* 1151EC */ void ftNs_AttackHi4_YoyoSetHitPos(HSD_GObj* gobj);
/* 1152D0 */ void ftNs_AttackHi4_YoyoSetHitPosUnk(HSD_GObj* gobj, float arg8);
/* 115404 */ bool ftNs_AttackHi4_YoyoCheckNoObstruct(HSD_GObj* gobj);
/* 115534 */ void ftNs_AttackHi4_YoyoSetVarAll(HSD_GObj* gobj);
/* 11556C */ void ftNs_AttackHi4_YoyoApplySmash(HSD_GObj* gobj);
/* 115680 */ void ftNs_AttackHi4_YoyoSetChargeDamage(HSD_GObj* gobj);
/* 115784 */ bool ftNs_AttackHi4_YoyoThink_IsRemove(HSD_GObj* gobj);
/* 11599C */ void ftNs_AttackHi4_YoyoSetUnkRate(HSD_GObj* gobj);
/* 115A08 */ void ftNs_AttackHi4_YoyoCreateItem(HSD_GObj* gobj);
/* 115AC4 */ void ftNs_AttackHi4_YoyoItemSetFlag(HSD_GObj* gobj);
/* 115AF8 */ void ftNs_AttackHi4_YoyoItemDespawn(HSD_GObj* gobj);
/* 115B50 */ void ftNs_AttackHi4_YoyoItemSetUnk2(HSD_GObj* gobj);
/* 115B80 */ void ftNs_AttackHi4_YoyoItemSetUnk(HSD_GObj* gobj);
/* 115BB0 */ void ftNs_AttackHi4_Enter(HSD_GObj* gobj);
/* 115C74 */ void ftNs_AttackHi4_YoyoStartTimedRehit(HSD_GObj* gobj);
/* 115C9C */ void ftNs_AttackHi4_Anim(HSD_GObj* gobj);
/* 115E74 */ void ftNs_AttackHi4_IASA(HSD_GObj* gobj);
/* 115EB8 */ void ftNs_AttackHi4_Phys(HSD_GObj* gobj);
/* 115F14 */ void ftNs_AttackHi4_Coll(HSD_GObj* gobj);
/* 115F88 */ void ftNs_AttackHi4Charge_Anim(HSD_GObj* gobj);
/* 1160B4 */ void ftNs_AttackHi4Charge_IASA(HSD_GObj* gobj);
/* 1160E4 */ void ftNs_AttackHi4Charge_Phys(HSD_GObj* gobj);
/* 116104 */ void ftNs_AttackHi4Charge_Coll(HSD_GObj* gobj);
/* 116178 */ void ftNs_AttackHi4Charge_Enter(HSD_GObj* gobj);
/* 11620C */ void ftNs_AttackHi4Release_Anim(HSD_GObj* gobj);
/* 1162B0 */ void ftNs_AttackHi4Release_IASA(HSD_GObj* gobj);
/* 1162E0 */ void ftNs_AttackHi4Release_Phys(HSD_GObj* gobj);
/* 116420 */ void ftNs_AttackHi4Release_Coll(HSD_GObj* gobj);
/* 116494 */ void ftNs_AttackHi4Release_Enter(HSD_GObj* gobj);

#endif
