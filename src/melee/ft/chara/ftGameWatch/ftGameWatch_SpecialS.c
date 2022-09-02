#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

void ftGameWatch_ItemJudgementExitHitlag(HSD_GObj* fighter_gobj);
extern void func_8028FAF4(HSD_GObj*, Vec3*);
extern HSD_GObj* func_802C7774(f32, HSD_GObj*, Vec3*, s32, u32);
void ftGameWatch_ItemJudgementEnterHitlag(HSD_GObj* fighter_gobj);

// 0x8014C46C 
// https://decomp.me/scratch/ohXu0 // Create Judgement item
void ftGameWatch_ItemJudgementSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* judgementGObj;

    if (getFighter(fighter_gobj)->x2204_ftcmd_var1 != 0U)
    {
        fp->x2204_ftcmd_var1 = 0;
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x31)].x0_jobj, NULL, &sp20);
        fp->sa.gaw.x2264_judgementGObj = func_802C7774(fp->x2C_facing_direction, fighter_gobj, &sp20, func_8007500C(fp, 0x31), fp->sa.gaw.x222C_judgeVar1);
        if ((s32)fp->sa.gaw.x222C_judgeVar1 == 6)
        {
            sp14.z = 0.0f;
            sp14.x = 0.0f;
            sp14.y = 5.0f;
            func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x1F)].x0_jobj, &sp14, &sp20);
            func_8028FAF4(fighter_gobj, &sp20);
        }
        if (fp->sa.gaw.x2264_judgementGObj != NULL)
        {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemJudgementEnterHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemJudgementExitHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014C590
// https://decomp.me/scratch/KIUEJ // Set Judgement flags + clear pointers
void ftGameWatch_ItemJudgementSetFlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    ftGameWatch_ItemJudgementExitHitlag(fighter_gobj);
    fp->sa.gaw.x2264_judgementGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

extern void func_802C7A84(HSD_GObj*);

// 0x8014C5CC
// https://decomp.me/scratch/jU9ji // Remove Judgement item
void ftGameWatch_ItemJudgementRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    Fighter* fp2;
    HSD_GObj* judgementGObj;

    if (fp->sa.gaw.x2264_judgementGObj != NULL)
    {
        func_802C7A84(fp->sa.gaw.x2264_judgementGObj);
        ftGameWatch_ItemJudgementSetFlag(fighter_gobj);
    }
}

extern void func_802C7AD0(HSD_GObj*);
extern void func_802C7AF0(HSD_GObj*);

// 0x8014C62C
// https://decomp.me/scratch/vFist // Apply hitlag to Judgement item
void ftGameWatch_ItemJudgementEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.gaw.x2264_judgementGObj != NULL)
    {
        func_802C7AD0(fp->sa.gaw.x2264_judgementGObj);
    }
}

// 0x8014C65C - Remove hitlag for Judgement item
void ftGameWatch_ItemJudgementExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.gaw.x2264_judgementGObj != NULL)
    {
        func_802C7AF0(fp->sa.gaw.x2264_judgementGObj);
    }
}

// 0x8014C68C
// https://decomp.me/scratch/MTdOC // Check if Mr. Game & Watch is in any of his SpecialS Action States
BOOL ftGameWatch_ItemCheckJudgementRemove(HSD_GObj* fighter_gobj)
{
    s32 ASID;

    ASID = getFighter(fighter_gobj)->x10_action_state_index;
    if ((ASID >= AS_GAMEWATCH_SPECIALS1) && (ASID <= AS_GAMEWATCH_SPECIALAIRS9))
    {
        return FALSE;
    }
    return TRUE;
}

// 0x8014C6B4 - shououts to EstexNT
// https://decomp.me/scratch/Dn1jh // Roll Judgement RNG value
s32 ftGameWatch_SpecialS_GetRandomInt(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);
    ftGameWatchJudge sp3C;
    ftGameWatchJudge sp18;
    s32 randomInt;
    s32 judgeVar;
    s32 returnRNG;
    s32 i;

    judgeVar = 9;
    for (judgeVar -= 9, i = 0, randomInt = 0; judgeVar < 9; judgeVar++)
    {
        if ((judgeVar != fp->sa.gaw.x222C_judgeVar1) && (judgeVar != fp->sa.gaw.x2230_judgeVar2))
        {
            (&sp3C)->rollVar[i] = judgeVar;
            randomInt += gawAttrs->x34_GAMEWATCH_JUDGE_ROLL[judgeVar];
            (&sp18)->rollVar[i] = randomInt;
            i++;
        }
    }
    randomInt = HSD_Randi(randomInt);
    for (i = 0; i < 9; i++)
    {
        if (randomInt < (&sp18)->rollVar[i])
        {
            returnRNG = sp3C.rollVar[i];
            break;
        }
    }
    fp->sa.gaw.x2230_judgeVar2 = fp->sa.gaw.x222C_judgeVar1;
    fp->sa.gaw.x222C_judgeVar1 = returnRNG;
    return returnRNG;
}

inline void ftGameWatch_SpecialS_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemJudgementSetup;
}

// 0x8014C7A0
// https://decomp.me/scratch/PnafK
void ftGameWatch_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 ASID;

    getFighter(fighter_gobj)->x80_self_vel.y = 0.0f;
    ftGameWatch_SpecialS_GetRandomInt(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, fp->sa.gaw.x222C_judgeVar1 + AS_GAMEWATCH_SPECIALS1, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialS_SetVars(fighter_gobj);
}

// 0x8014C828
// https://decomp.me/scratch/IzXqX
void ftGameWatch_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;
    s32 ASID;

    getFighter(fighter_gobj)->x80_self_vel.x /= gawAttrs->x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE;
    ftGameWatch_SpecialS_GetRandomInt(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, fp->sa.gaw.x222C_judgeVar1 + AS_GAMEWATCH_SPECIALAIRS1, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    ftGameWatch_SpecialS_SetVars(fighter_gobj);
}

// 0x8014C8BC
// https://decomp.me/scratch/xcOet // Mr. Game & Watch's Grounded Judgement Animation callback
void ftGameWatch_SpecialS_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

extern void func_800CC730(HSD_GObj* fighter_gobj);

// 0x8014C8F8 - Mr. Game & Watch's Aerial Judgement Animation callback
void ftGameWatch_SpecialAirS_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x8014C934 - Mr. Game & Watch's Grounded Judgement IASA callback
void ftGameWatch_SpecialS_IASA(HSD_GObj* fighter_gobj) 
{
    return;
}

// 0x8014C938 - Mr. Game & Watch's Aerial Judgement IASA callback
void ftGameWatch_SpecialAirS_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014C93C
// https://decomp.me/scratch/ulBEx // Mr. Game & Watch's Grounded Judgement Physics callback
void ftGameWatch_SpecialS_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((u32)fp->x2200_ftcmd_var0 == 1U)
    {
        fp->x2200_ftcmd_var0 = 2U;
    }
    func_80084F3C(fighter_gobj);
}

// 0x8014C974
// https://decomp.me/scratch/kDevS // Mr. Game & Watch's Aerial Judgement Physics callback
void ftGameWatch_SpecialAirS_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;
    f32 ftGameWatchPhys[4];

    if (ftcmd_var >= 1U)
    {
        if (ftcmd_var == 1)
        {
            fp->x2200_ftcmd_var0 = 2;
            if ((s32)fp->sa.gaw.x2234 == 0)
            {
                fp->sa.gaw.x2234 = 1;
                fp->x80_self_vel.y = gawAttrs->x28_GAMEWATCH_JUDGE_VEL_Y;
            }
            else fp->x80_self_vel.y = 0.0f;
        }
        func_8007D494(fp, gawAttrs->x2C_GAMEWATCH_JUDGE_FRICTION1, gawAttrs->x30_GAMEWATCH_JUDGE_FRICTION2);
    }
    else
    {
        func_8007D4B8(fp);
    }
    func_8007CE94(fp, gawAttrs->x24_GAMEWATCH_JUDGE_MOMENTUM_MUL);
}

void ftGameWatch_SpecialS_GroundToAir(HSD_GObj*);                         /* extern */
void ftGameWatch_SpecialAirS_AirToGround(HSD_GObj*);

// 0x8014CA10
// https://decomp.me/scratch/G9OvA // Mr. Game & Watch's Grounded Judgement Collision callback
void ftGameWatch_SpecialS_Coll(HSD_GObj* fighter_gobj)
{
    if (func_800827A0(fighter_gobj) == FALSE)
    {
        ftGameWatch_SpecialS_GroundToAir(fighter_gobj);
    }
}

// 0x8014CA4C - Mr. Game & Watch's Aerial Judgement Collision callback
void ftGameWatch_SpecialAirS_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftGameWatch_SpecialAirS_AirToGround(fighter_gobj);
    }
}

inline void ftGameWatch_SpecialS_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->sa.gaw.x2264_judgementGObj != NULL)
    {
        fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
    }
    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemJudgementEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemJudgementExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemJudgementSetup;
}

// 0x8014CA88
// https://decomp.me/scratch/FPdQK // Mr. Game & Watch's ground -> air Judgement Acion State handler
void ftGameWatch_SpecialS_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 ASID;

    func_8007D5D4(fp);
    !fighter_gobj;
    Fighter_ActionStateChange_800693AC(fighter_gobj, fp->sa.gaw.x222C_judgeVar1 + AS_GAMEWATCH_SPECIALAIRS1, FTGAMEWATCH_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    if ((u32)fp->x2200_ftcmd_var0 == 1)
    {
        fp->x2200_ftcmd_var0 = 2;
    }
    ftGameWatch_SpecialS_SetCall(fighter_gobj);
}

// 0x8014CB44 - Mr. Game & Watch's air -> ground Judgement Action State Handler
void ftGameWatch_SpecialAirS_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 ASID;

    fp->sa.gaw.x2234 = 0;
    func_8007D7FC(fp);
    !fighter_gobj;
    Fighter_ActionStateChange_800693AC(fighter_gobj, fp->sa.gaw.x222C_judgeVar1 + AS_GAMEWATCH_SPECIALS1, FTGAMEWATCH_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialS_SetCall(fighter_gobj);
}
