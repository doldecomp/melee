#include "ef/efasync.h"
#include "ft/ft_81B.h"
#include "ft/ft_877.h"
#include "ft/inlines.h"
#include "ftNess/ftNess.h"

// 0x8011659C
// https://decomp.me/scratch/xVTx7
void ftNess_AttackLw4_Action(
    HSD_GObj* gobj) // Ness's Down Smash Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x2218_flag.bits.b0 = 0;
    fp->mv.ns.attacklw4.isChargeDisable = false;
    ftNess_YoyoSetVarAll(gobj);
    Fighter_ChangeMotionState(gobj, MS_NESS_ATTACKLW4, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x80116638
// https://decomp.me/scratch/NO0Pa
void ftNess_AttackLw4_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Animation callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ns.attacklw4.yoyoCurrentFrame++;
    if (ftNess_YoyoThink_IsRemove(gobj) == false) {
        ftNess_YoyoCheckTimedRehit(gobj);
        if (((s32) fp->mv.ns.attacklw4.yoyoCurrentFrame == 13) &&
            ((s32) fp->mv.ns.attacklw4.isChargeDisable == false) &&
            (ftNess_YoyoCheckNoObstruct(gobj) != false))
        {
            ftNess_AttackLw4_Charge_Action(gobj);
        }
        if (!ftAnim_IsFramesRemaining(gobj)) {
            func_8008A2BC(gobj);
        }
    }
}

// 0x801166D4
// https://decomp.me/scratch/Kq53f
void ftNess_AttackLw4_IASA(HSD_GObj* gobj) // Ness's Down Smash IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == false) {
        fp->mv.ns.attacklw4.isChargeDisable = true;
    }
    if (fp->x2218_flag.bits.b0 != 0) {
        func_8008A4D4(gobj);
    }
}

// 0x80116718
// https://decomp.me/scratch/rrVAL
void ftNess_AttackLw4_Phys(
    HSD_GObj* gobj) // Ness's Down Smash Physics callback
{
    ft_80084F3C(gobj);
    ftNess_YoyoSetHitPos(gobj);
}

// 0x8011674C
// https://decomp.me/scratch/IcIJj
void ftNess_AttackLw4_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNess_YoyoItemDespawn(gobj);
    }
}

// 0x80116798
// https://decomp.me/scratch/H7nP6
void ftNess_AttackLw4_Charge_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Charge Animation callback
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = GET_FIGHTER(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    ness_attr = fp->x2D4_specialAttributes;
    fp->mv.ns.attacklw4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    ftNess_YoyoSetUnkRate(gobj);
    ftNess_YoyoCheckTimedRehit(gobj);
    if ((f32) fp->mv.ns.attacklw4.yoyoCurrentFrame >=
        ness_attr->xAC_YOYO_CHARGE_DURATION)
    {
        ftNess_AttackLw4_Release_Action(gobj);
    }
}

// 0x80116828
// https://decomp.me/scratch/803jK
void ftNess_AttackLw4_Charge_IASA(
    HSD_GObj* gobj) // Ness's Down Smash Charge IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == false) {
        ftNess_AttackLw4_Release_Action(gobj);
    }
}

// 0x80116858
// https://decomp.me/scratch/aMuVK
void ftNess_AttackLw4_Charge_Phys(
    HSD_GObj* gobj) // Ness's Down Smash Charge Physics callback
{
    ft_80084F3C(gobj);
}

// 0x80116878
// https://decomp.me/scratch/XNQHN
void ftNess_AttackLw4_Charge_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Charge Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNess_YoyoItemDespawn(gobj);
    }
}

// 0x801168C4
// https://decomp.me/scratch/KJ6kU
void ftNess_AttackLw4_Charge_Action(
    HSD_GObj* gobj) // Ness's Down Smash Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, MS_NESS_ATTACKLW4_CHARGE,
                              FtStateChange_SkipUpdateItemVis, NULL, 12.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    ftNess_YoyoApplySmash(gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x80116958
// https://decomp.me/scratch/zksU7
void ftNess_AttackLw4_Release_Anim(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Animation callback
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    fp->mv.ns.attacklw4.yoyoCurrentFrame = (s32) (yoyoSmashFrameCurr + 1);
    if (ftNess_YoyoThink_IsRemove(gobj) == false) {
        ftNess_YoyoCheckTimedRehit(gobj);
        if (!ftAnim_IsFramesRemaining(gobj)) {
            func_8008A2BC(gobj);
        }
    }
}

// 0x801169BC
// https://decomp.me/scratch/dC4m7
void ftNess_AttackLw4_Release_IASA(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge IASA callback
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2218_flag.bits.b0 != 0) {
        func_8008A4D4(gobj);
    }
}

// 0x801169EC
// https://decomp.me/scratch/AkDxO
void ftNess_AttackLw4_Release_Phys(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Physics callback
{
    f32 yoyoSmashUnk;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ft_80084F3C(gobj);
    yoyoSmashFrameCurr = fp->mv.ns.attacklw4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 0x13) {
        yoyoSmashUnk =
            0.20000000298023224f * ((f32) yoyoSmashFrameCurr - 14.0f);
        if (yoyoSmashUnk >= 1.0f) {
            yoyoSmashUnk = 1.0f;
        }

        else if (yoyoSmashUnk <= 0.0f)
        {
            yoyoSmashUnk = 0.0f;
        }
        ftNess_YoyoSetHitPosUnk(gobj, yoyoSmashUnk);
        return;
    }
    ftNess_YoyoSetHitPos(gobj);
}

// 0x801169EC
// https://decomp.me/scratch/mD95b
void ftNess_AttackLw4_Release_Coll(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);

    ft_80084104(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        ftNess_YoyoItemDespawn(gobj);
    }
}

// 0x80116AE8
// https://decomp.me/scratch/qsqMH
void ftNess_AttackLw4_Release_Action(
    HSD_GObj* gobj) // Ness's Down Smash Post-Charge Motion State handler
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, MS_NESS_ATTACKLW4_RELEASE,
                              FtStateChange_SkipUpdateItemVis, NULL, 13.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftNess_YoyoSetChargeDamage(gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}
