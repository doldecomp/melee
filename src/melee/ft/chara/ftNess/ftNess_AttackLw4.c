#include <melee/ft/chara/ftNess/ftNess.h>

// 0x8011659C //
// https://decomp.me/scratch/xVTx7 //
void ftNess_AttackLw4_Action(HSD_GObj* fighter_gobj)  // Ness's Down Smash Action State handler //
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->x2218_flag.bits.b0 = 0;
    fp->nessVars[0].AttackLw4.isChargeDisable = FALSE;
    ftNess_YoyoSetVarAll(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKLW4, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x80116638 //
// https://decomp.me/scratch/NO0Pa //
void ftNess_AttackLw4_Anim(HSD_GObj* fighter_gobj) // Ness's Down Smash Animation callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->nessVars[0].AttackLw4.yoyoCurrentFrame++;
    if (ftNess_YoyoThink_IsRemove(fighter_gobj) == FALSE) 
    {
        ftNess_YoyoCheckTimedRehit(fighter_gobj);
        if (((s32)fp->nessVars[0].AttackLw4.yoyoCurrentFrame == 13) && ((s32)fp->nessVars[0].AttackLw4.isChargeDisable == FALSE) && (ftNess_YoyoCheckNoObstruct(fighter_gobj) != FALSE)) 
        {
            ftNess_AttackLw4_Charge_Action(fighter_gobj);
        }
        if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

extern void func_8008A4D4(HSD_GObj*);

// 0x801166D4 //
// https://decomp.me/scratch/Kq53f //
void ftNess_AttackLw4_IASA(HSD_GObj* fighter_gobj)   // Ness's Down Smash IASA callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == FALSE)
    {
        fp->nessVars[0].AttackLw4.isChargeDisable = TRUE;
    }
    if (fp->x2218_flag.bits.b0 != 0)
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x80116718 //
// https://decomp.me/scratch/rrVAL //
void ftNess_AttackLw4_Phys(HSD_GObj* fighter_gobj)   // Ness's Down Smash Physics callback //
{
    func_80084F3C(fighter_gobj);
    ftNess_YoyoSetHitPos(fighter_gobj);
}

// 0x8011674C //
// https://decomp.me/scratch/IcIJj //
void ftNess_AttackLw4_Coll(HSD_GObj* fighter_gobj)   // Ness's Down Smash Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    func_80084104(fighter_gobj);
    if ((s32)fp->xE0_ground_or_air == GA_Air) 
    {
        ftNess_YoyoItemDespawn(fighter_gobj);
    }
}

// 0x80116798 //
// https://decomp.me/scratch/H7nP6 //
void ftNess_AttackLw4_Charge_Anim(HSD_GObj* fighter_gobj)   // Ness's Down Smash Charge Animation callback //
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;
    ftNessAttributes* ness_attr;

    fp = getFighter(fighter_gobj);
    yoyoSmashFrameCurr = fp->nessVars[0].AttackLw4.yoyoCurrentFrame;
    ness_attr = fp->x2D4_specialAttributes;
    fp->nessVars[0].AttackLw4.yoyoCurrentFrame = (s32)(yoyoSmashFrameCurr + 1);
    ftNess_YoyoSetUnkRate(fighter_gobj);
    ftNess_YoyoCheckTimedRehit(fighter_gobj);
    if ((f32)fp->nessVars[0].AttackLw4.yoyoCurrentFrame >= ness_attr->xAC_YOYO_CHARGE_DURATION)
    {
        ftNess_AttackLw4_Release_Action(fighter_gobj);
    }
}

// 0x80116828 //
// https://decomp.me/scratch/803jK //
void ftNess_AttackLw4_Charge_IASA(HSD_GObj* fighter_gobj)   // Ness's Down Smash Charge IASA callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_A) == FALSE)
    {
        ftNess_AttackLw4_Release_Action(fighter_gobj);
    }
}

// 0x80116858 //
// https://decomp.me/scratch/aMuVK //   
void ftNess_AttackLw4_Charge_Phys(HSD_GObj* fighter_gobj)   // Ness's Down Smash Charge Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80116878 //
// https://decomp.me/scratch/XNQHN //
void ftNess_AttackLw4_Charge_Coll(HSD_GObj* fighter_gobj)   // Ness's Down Smash Charge Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    func_80084104(fighter_gobj);
    if ((s32)fp->xE0_ground_or_air == GA_Air) 
    {
        ftNess_YoyoItemDespawn(fighter_gobj);
    }
}

// 0x801168C4 //
// https://decomp.me/scratch/KJ6kU //
void ftNess_AttackLw4_Charge_Action(HSD_GObj* fighter_gobj)  // Ness's Down Smash Charge Action State handler //
{
    Fighter* fp = getFighter(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKLW4_CHARGE, FIGHTER_ITEMVIS_NOUPDATE, NULL, 12.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    ftNess_YoyoApplySmash(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}

// 0x80116958 //
// https://decomp.me/scratch/zksU7 //
void ftNess_AttackLw4_Release_Anim(HSD_GObj* fighter_gobj)   // Ness's Down Smash Post-Charge Animation callback //
{
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    yoyoSmashFrameCurr = fp->nessVars[0].AttackLw4.yoyoCurrentFrame;
    fp->nessVars[0].AttackLw4.yoyoCurrentFrame = (s32)(yoyoSmashFrameCurr + 1);
    if (ftNess_YoyoThink_IsRemove(fighter_gobj) == FALSE) 
    {
        ftNess_YoyoCheckTimedRehit(fighter_gobj);
        if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) 
        {
            func_8008A2BC(fighter_gobj);
        }
    }
}

// 0x801169BC //
// https://decomp.me/scratch/dC4m7 //
void ftNess_AttackLw4_Release_IASA(HSD_GObj* fighter_gobj)   // Ness's Down Smash Post-Charge IASA callback //
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x2218_flag.bits.b0 != 0) 
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x801169EC //
// https://decomp.me/scratch/AkDxO //
void ftNess_AttackLw4_Release_Phys(HSD_GObj* fighter_gobj)   // Ness's Down Smash Post-Charge Physics callback //
{
    f32 yoyoSmashUnk;
    s32 yoyoSmashFrameCurr;
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    func_80084F3C(fighter_gobj);
    yoyoSmashFrameCurr = fp->nessVars[0].AttackLw4.yoyoCurrentFrame;
    if (yoyoSmashFrameCurr < 0x13)
    {
        yoyoSmashUnk = 0.20000000298023224f * ((f32)yoyoSmashFrameCurr - 14.0f);
        if (yoyoSmashUnk >= 1.0f)
        {
            yoyoSmashUnk = 1.0f;
        }

        else if (yoyoSmashUnk <= 0.0f)
        {
            yoyoSmashUnk = 0.0f;
        }
        ftNess_YoyoSetHitPosUnk(fighter_gobj, yoyoSmashUnk);
        return;
    }
    ftNess_YoyoSetHitPos(fighter_gobj);
}

// 0x801169EC //
// https://decomp.me/scratch/mD95b //
void ftNess_AttackLw4_Release_Coll(HSD_GObj* fighter_gobj)   // Ness's Down Smash Post-Charge Collision callback //
{
    Fighter* fp = getFighter(fighter_gobj);

    func_80084104(fighter_gobj);
    if ((s32)fp->xE0_ground_or_air == GA_Air) 
    {
        ftNess_YoyoItemDespawn(fighter_gobj);
    }
}

// 0x80116AE8 //
// https://decomp.me/scratch/qsqMH //
void ftNess_AttackLw4_Release_Action(HSD_GObj* fighter_gobj) // Ness's Down Smash Post-Charge Action State handler //
{
    Fighter* fp = getFighter(fighter_gobj);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_ATTACKLW4_RELEASE, FIGHTER_ITEMVIS_NOUPDATE, NULL, 13.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftNess_YoyoSetChargeDamage(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    fp->cb.x21C0_callback_OnGiveDamage = ftNess_YoyoStartTimedRehit;
    fp->cb.x21BC_callback_Accessory4 = ftNess_YoyoUpdateHitPos;
}
