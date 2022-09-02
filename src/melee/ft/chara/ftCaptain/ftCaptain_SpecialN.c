#include <melee/ft/chara/ftCaptain/ftCaptain.h>

void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* fighter_gobj) // Create Aesthetic Wind Effect for Warlock Punch
{
    s32 currentAnimFrame;
    Fighter* fp = fighter_gobj->user_data;
    s32 ftKind;

    currentAnimFrame = (s32)fp->x894_currentAnimFrame;

    ftKind = func_800872A4(fighter_gobj);
    switch (ftKind)
    {
    case FTKIND_CAPTAIN:
        break;
    case FTKIND_GANON:
        if (currentAnimFrame & 1)
        {
            if ((currentAnimFrame >= 16) && (currentAnimFrame <= 50))
            {
                func_800119DC(&fp->xB0_pos, 2, 2.0f, 2.0f, 0.0f);
            }
            else if ((currentAnimFrame >= 51) && (currentAnimFrame <= 68))
            {

                func_800119DC(&fp->xB0_pos, 2, 4.0f, 4.0f, 0.0f);
            }
        }
        break;
    }
}

f32 ftCaptain_SpecialN_GetAngleVel(Fighter* fp) // Calculate angle from control stick input - inline
{
    ftCaptainAttributes* tempAttrs = fp->x2D4_specialAttributes;

    f32 stickRangeMinPos;
    f32 stickRangeMinNeg;
    f32 stick_y;
    f32 floatVar = 0.01745329238474369f;

    stick_y = stickGetDir(fp->input.x624_lstick_y, 0.0f);

    stickRangeMinPos = tempAttrs->x4_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_POS;
    if (stick_y > stickRangeMinPos)
    {
        stick_y = stickRangeMinPos;
    }

    stickRangeMinNeg = tempAttrs->x0_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_NEG;
    stick_y -= stickRangeMinNeg;

    if (stick_y < 0.0f)
    {
        stick_y = 0.0f;
    }
    if (fp->input.x624_lstick_y < 0.0f)
    {
        stick_y = -stick_y;
    }
    return floatVar * ((stick_y * tempAttrs->x8_CAPTAIN_FALCONPUNCH_ANGLE_DIFF) / (stickRangeMinPos - stickRangeMinNeg));
}

// 0x800E2B80
// https://decomp.me/scratch/4yplr // Captain Falcon & Ganondorf's grounded Falcon/Warlock Punch Action State handler
void ftCaptain_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALN, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8006EBA4(fighter_gobj);
}

// 0x800E2C00
// https://decomp.me/scratch/CcfiS // Captain Falcon & Ganondorf's aerial Falcon/Warlock Punch Action State handler
void ftCaptain_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALAIRN, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8006EBA4(fighter_gobj);
}

// 0x800E2C80
// https://decomp.me/scratch/3nbJC // Captain Falcon & Ganondorf's grounded Falcon/Warlock Punch Animation callback
void ftCaptain_SpecialN_Anim(HSD_GObj* fighter_gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x800E2D5C
// https://decomp.me/scratch/TPyx9 // Captain Falcon & Ganondorf's aerial Falcon/Warlock Punch Animation callback
void ftCaptain_SpecialAirN_Anim(HSD_GObj* fighter_gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x800E2E38 - Captain Falcon & Ganondorf's grounded Falcon/Warlock Punch IASA callback
void ftCaptain_SpecialN_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E2E3C
// https://decomp.me/scratch/4rsQA // Captain Falcon & Ganondorf's aerial Falcon/Warlock Punch IASA callback
void ftCaptain_SpecialAirN_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftCaptainAttributes* captainAttrs = captainAttrs = getFtSpecialAttrs(fp);
    f32 vel;

    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        fp->x2200_ftcmd_var0 = 0U;
        vel = ftCaptain_SpecialN_GetAngleVel(fp);
        fp->x80_self_vel.y = (f32)(captainAttrs->xC_CAPTAIN_FALCONPUNCH_MOMENTUM_X * sinf(vel));
        fp->x80_self_vel.x = (f32)(captainAttrs->xC_CAPTAIN_FALCONPUNCH_MOMENTUM_X * (fp->x2C_facing_direction * cosf(vel)));
    }
}

// 0x800E2F2C
// https://decomp.me/scratch/YdpbL // Captain Falcon & Ganondorf's grounded Falcon/Warlock Punch Physics callback
void ftCaptain_SpecialN_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 ftKind;
    s32 flag;
    s32 var;

    fp = getFighter(fighter_gobj);
    if (fp->x2210_ThrowFlags.b1 != 0)
    {
        fp->x2210_ThrowFlags.b1 = 0;
        flag = TRUE;
    }
    else
    {
        flag = FALSE;
    }
    if (flag != FALSE)
    {
        if (fp->x2219_flag.bits.b0 == 0)
        {
            ftKind = func_800872A4(fighter_gobj);
            switch (ftKind)
            {
            case 2:
                ef_Spawn(0x48F, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, fp->x5E8_fighterBones[0x39].x0_jobj);
                break;
            case 25:
                ef_Spawn(0x50B, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, fp->x5E8_fighterBones[0x4E].x0_jobj);
                break;
            }
            fp->x2219_flag.bits.b0 = 1;
        }
        else
        {
            func_8007DB24(fighter_gobj);
        }
    }
    func_80084FA8(fighter_gobj);
}

extern void func_80084DB0(HSD_GObj*);

// 0x800E3018
// https://decomp.me/scratch/CiZfS // Captain Falcon & Ganondorf's aerial Falcon/Warlock Punch Physics callback
void ftCaptain_SpecialAirN_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftCaptainAttributes* captainAttrs = captainAttrs = getFtSpecialAttrs(fp);
    s32 ftKind;
    s32 flag;
    s32 var;

    if (fp->x2210_ThrowFlags.b1 != 0)
    {
        fp->x2210_ThrowFlags.b1 = 0;
        flag = TRUE;
    }
    else
    {
        flag = FALSE;
    }
    if (flag != FALSE)
    {
        if (fp->x2219_flag.bits.b0 == 0)
        {
            ftKind = func_800872A4(fighter_gobj);
            switch (ftKind)
            {
            case 2:
                ef_Spawn(0x48F, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, fp->x5E8_fighterBones[0x39].x0_jobj);
                break;
            case 25:
                ef_Spawn(0x50B, fighter_gobj, fp->x5E8_fighterBones[0].x0_jobj, fp->x5E8_fighterBones[0x4E].x0_jobj);
                break;
            }
            fp->x2219_flag.bits.b0 = 1;
        }
        else
        {
            func_8007DB24(fighter_gobj);
        }
    }
    switch (fp->x2204_ftcmd_var1)
    {
    case 0:
        func_80084EEC(fighter_gobj);
        break;

    case 1:
        fp->x80_self_vel.y *= captainAttrs->x10_CAPTAIN_FALCONPUNCH_MOMENTUM_MUL;
        fp->x80_self_vel.x *= captainAttrs->x10_CAPTAIN_FALCONPUNCH_MOMENTUM_MUL;
        break;

    case 2:
        func_80084DB0(fighter_gobj);
    }
}

extern void func_8007D468(Fighter*);

// 0x800E3168
// https://decomp.me/scratch/34fFe // Captain Falcon & Ganondorf's grounded Falcon/Warlock Punch Collision callback
void ftCaptain_SpecialN_Coll(HSD_GObj* fighter_gobj)
{
    if (func_800827A0(fighter_gobj) == FALSE)
    {
        Fighter* fp = fighter_gobj->user_data;
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALAIRN, FTCAPTAIN_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        func_8007D468(fp);
    }
}

// 0x800E31F4
// https://decomp.me/scratch/LiPmy // Captain Falcon & Ganondorf's aerial Falcon/Warlock Punch Collision callback
void ftCaptain_SpecialAirN_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        Fighter* fp = fighter_gobj->user_data;
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALN, FTCAPTAIN_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
