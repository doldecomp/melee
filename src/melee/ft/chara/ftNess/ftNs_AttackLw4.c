#include "ftNs_AttackLw4.h"

#include "ftNs_AttackHi4.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Wait.h"
#include "ftNess/types.h"

#include <common_structs.h>

// 0x8011659C
// https://decomp.me/scratch/xVTx7
void ftNs_AttackLw4_Enter(
    HSD_GObj* gobj) // Ness's Down Smash Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->allow_interrupt = 0;
    fp->mv.ns.attacklw4.isChargeDisable = false;
    ftNs_AttackHi4_YoyoSetVarAll(gobj);
    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackLw4, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x2222_b2 = 1;
    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
}

// 0x80116638
// https://decomp.me/scratch/NO0Pa
void ftNs_AttackLw4_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Animation callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ns.attacklw4.yoyoCurrentFrame++;
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        ftNs_AttackHi4_YoyoCheckTimedRehit(gobj);
        if (((s32) fp->mv.ns.attacklw4.yoyoCurrentFrame == 13) &&
            ((s32) fp->mv.ns.attacklw4.isChargeDisable == false) &&
            (ftNs_AttackHi4_YoyoCheckNoObstruct(gobj) != false))
        {
            ftNs_AttackLw4Charge_Enter(gobj);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ft_8008A2BC(gobj);
        }
    }
}

// 0x801166D4
// https://decomp.me/scratch/Kq53f
void ftNs_AttackLw4_IASA(HSD_GObj* gobj) // Ness's Down Smash IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & HSD_PAD_A) == false) {
        fp->mv.ns.attacklw4.isChargeDisable = true;
    }
    if (fp->allow_interrupt != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x80116718
// https://decomp.me/scratch/rrVAL
void ftNs_AttackLw4_Phys(HSD_GObj* gobj) // Ness's Down Smash Physics callback
{
    ft_80084F3C(gobj);
    ftNs_AttackHi4_YoyoSetHitPos(gobj);
}

// 0x8011674C
// https://decomp.me/scratch/IcIJj
void ftNs_AttackLw4_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNs_AttackHi4_YoyoItemDespawn(gobj);
    }
}

// 0x80116798
// https://decomp.me/scratch/H7nP6
void ftNs_AttackLw4Charge_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Charge Animation callback
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = GET_FIGHTER(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    ness_attr = fp->dat_attrs;
    fp->mv.ns.attacklw4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    ftNs_AttackHi4_YoyoSetUnkRate(gobj);
    ftNs_AttackHi4_YoyoCheckTimedRehit(gobj);
    if ((float) fp->mv.ns.attacklw4.yoyoCurrentFrame >=
        ness_attr->xAC_YOYO_CHARGE_DURATION)
    {
        ftNs_AttackLw4Release_Enter(gobj);
    }
}

// 0x80116828
// https://decomp.me/scratch/803jK
void ftNs_AttackLw4Charge_IASA(
    HSD_GObj* gobj) // Ness's Down Smash Charge IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & HSD_PAD_A) == false) {
        ftNs_AttackLw4Release_Enter(gobj);
    }
}

// 0x80116858
// https://decomp.me/scratch/aMuVK
void ftNs_AttackLw4Charge_Phys(
    HSD_GObj* gobj) // Ness's Down Smash Charge Physics callback
{
    ft_80084F3C(gobj);
}

// 0x80116878
// https://decomp.me/scratch/XNQHN
void ftNs_AttackLw4Charge_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Charge Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNs_AttackHi4_YoyoItemDespawn(gobj);
    }
}

// 0x801168C4
// https://decomp.me/scratch/KJ6kU
void ftNs_AttackLw4Charge_Enter(
    HSD_GObj* gobj) // Ness's Down Smash Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackLw4Charge, Ft_MF_SkipItemVis,
                              12.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    ftNs_AttackHi4_YoyoApplySmash(gobj);
    fp->x2222_b2 = 1;
    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
}

// 0x80116958
// https://decomp.me/scratch/zksU7
void ftNs_AttackLw4Release_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Animation callback
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    fp->mv.ns.attacklw4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNs_AttackHi4_YoyoThink_IsRemove(gobj) == false) {
        ftNs_AttackHi4_YoyoCheckTimedRehit(gobj);
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ft_8008A2BC(gobj);
        }
    }
}

// 0x801169BC
// https://decomp.me/scratch/dC4m7
void ftNs_AttackLw4Release_IASA(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x801169EC
// https://decomp.me/scratch/AkDxO
void ftNs_AttackLw4Release_Phys(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Physics callback
{
    float yoyoSmashUnk;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ft_80084F3C(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 0x13) {
        yoyoSmashUnk =
            0.20000000298023224f * ((float) yoyoSmashFrameCurr - 14.0f);
        if (yoyoSmashUnk >= 1.0f) {
            yoyoSmashUnk = 1.0f;
        }

        else if (yoyoSmashUnk <= 0.0f)
        {
            yoyoSmashUnk = 0.0f;
        }
        ftNs_AttackHi4_YoyoSetHitPosUnk(gobj, yoyoSmashUnk);
        return;
    }
    ftNs_AttackHi4_YoyoSetHitPos(gobj);
}

// 0x801169EC
// https://decomp.me/scratch/mD95b
void ftNs_AttackLw4Release_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNs_AttackHi4_YoyoItemDespawn(gobj);
    }
}

// 0x80116AE8
// https://decomp.me/scratch/qsqMH
void ftNs_AttackLw4Release_Enter(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftNs_MS_AttackLw4Release,
                              Ft_MF_SkipItemVis, 13.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftNs_AttackHi4_YoyoSetChargeDamage(gobj);
    fp->x2222_b2 = 1;
    fp->deal_dmg_cb = ftNs_AttackHi4_YoyoStartTimedRehit;
    fp->accessory4_cb = ftNs_AttackHi4_YoyoUpdateHitPos;
}
