#include <melee/ft/chara/ftFox/ftfox.h>

// 0x800E83E0
// https://decomp.me/scratch/wfS8S // Create Reflector Loop GFX
void ftFox_SpecialLw_CreateLoopGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x488, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E845C
// https://decomp.me/scratch/NNvPa // Create Reflector Start GFX
void ftFox_SpecialLw_CreateStartGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x489, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x800E84D8
// https://decomp.me/scratch/fVnTp // Create Reflector Deflect GFX
void ftFox_SpecialLw_CreateReflectGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x48A, fighter_gobj, fp->x5E8_fighterBones[4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

inline void ftFox_SpecialLw_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = foxAttrs = getFtSpecialAttrs(fp);
    fp->foxVars[0].SpecialLw.releaseLag = (s32)foxAttrs->x98_FOX_REFLECTOR_RELEASE_LAG;
    fp->foxVars[0].SpecialLw.isRelease = 0;
    fp->x2204_ftcmd_var1 = 4;
    fp->foxVars[0].SpecialLw.gravityDelay = (s32)foxAttrs->xA4_FOX_REFLECTOR_GRAVITY_DELAY;
    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateStartGFX;
}

// 0x800E8560 
// https://decomp.me/scratch/fJ4P2 // Fox & Falco's grounded Reflector Start Action State handler
void ftFox_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    ftFoxAttributes* foxAttrs;
    Fighter* fp;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftFox_SpecialLw_SetVars(fighter_gobj);
}

// 0x800E85EC
// https://decomp.me/scratch/dDVIh // Fox & Falco's aerial Reflector Start Action State handler
void ftFox_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x /= foxAttrs->xA8_FOX_REFLECTOR_MOMENTUM_PRESERVE_X;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);

    ftFox_SpecialLw_SetVars(fighter_gobj);
}

// 0x800E8694
// https://decomp.me/scratch/isKUf // Fox & Falco's grounded Reflector Start Animation callback
void ftFox_SpecialLwStart_Anim(HSD_GObj* fighter_gobj) 
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            ftFox_SpecialLwLoop_Action(fighter_gobj);
        }
        else ftFox_SpecialAirLwLoop_Action(fighter_gobj);
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}


// 0x800E8720
// https://decomp.me/scratch/cvwhn // Fox & Falco's aerial Reflector Start Animation callback
void ftFox_SpecialAirLwStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 var;

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            ftFox_SpecialLwLoop_Action(fighter_gobj);
        }
        else ftFox_SpecialAirLwLoop_Action(fighter_gobj);
        func_8007DB24(fighter_gobj);

        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}

// 0x800E87AC
// https://decomp.me/scratch/CYqHS // Fox & Falco's grounded Reflector Start IASA callback
void ftFox_SpecialLwStart_IASA(HSD_GObj* fighter_gobj)
{
    if (ftFox_SpecialLwStart_CheckPass(fighter_gobj)) return;
}

// 0x800E87D0 - Fox & Falco's aerial Reflector Start IASA callback
void ftFox_SpecialAirLwStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

extern BOOL func_80099F1C(HSD_GObj*);

// 0x800E87D4
// https://decomp.me/scratch/HFn3E // Check for drop-through platform while in SpecialLwStart
BOOL ftFox_SpecialLwStart_CheckPass(HSD_GObj* fighter_gobj)
{
    if (func_80099F1C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialLwStart_Pass(fighter_gobj);
        return TRUE;
    }
    return FALSE;
}

extern void func_8009A184(HSD_GObj*, s32, u32, f32);

// 0x800E881C
// https://decomp.me/scratch/2ggae // Fox & Falco's Reflector Start Platform Drop Action State handler
void ftFox_SpecialLwStart_Pass(HSD_GObj* fighter_gobj)
{
    func_8009A184(fighter_gobj, AS_FOX_SPECIALAIRLW_START, FTFOX_SPECIALLW_COLL_FLAG, getFighter(fighter_gobj)->x894_currentAnimFrame);
    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

// 0x800E8864 - Fox & Falco's Reflector Start Physics callback
void ftFox_SpecialLwStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x800E8884
// https://decomp.me/scratch/7gO11 // Fox & Falco's aerial Reflector Start Physics callback
void ftFox_SpecialAirLwStart_Phys(HSD_GObj* fighter_gobj)
{
    attr* ftAttrs;
    ftFoxAttributes* foxAttrs;
    Fighter* fp = fighter_gobj->user_data;
    s32 var;
    s32 var2;

    ftAttrs = &fp->x110_attr;
    foxAttrs = fp->x2D4_specialAttributes;

    if (fp->foxVars[0].SpecialLw.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialLw.gravityDelay--;
    }
    else func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL, ftAttrs->x170_TerminalVelocity);
    func_8007CF58(fp);
}

// 0x800E88E4
// https://decomp.me/scratch/l0NxX // Fox & Falco's grounded Reflector Start Collision callback
void ftFox_SpecialLwStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialLwStart_GroundToAir(fighter_gobj);
    }
}

// 0x800E8920
// https://decomp.me/scratch/9lyva // Fox & Falco's aerial Reflector Start Collision callback
void ftFox_SpecialAirLwStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialAirLwStart_AirToGround(fighter_gobj);
    }
}

// 0x800E895C
// https://decomp.me/scratch/y54IK // Fox & Falco's ground -> air Reflector Start Action State handler
void ftFox_SpecialLwStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_START, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x800E89BC
// https://decomp.me/scratch/u6HZN // Fox & Falco's air -> ground Reflector Start Action State handler
void ftFox_SpecialAirLwStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_START, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

// 0x800E8A24
// https://decomp.me/scratch/BtThS // Fox & Falco's grounded Reflector Loop Animation callback
void ftFox_SpecialLwLoop_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    if (((s32)fp->foxVars[0].SpecialLw.releaseLag <= 0) && ((s32)fp->foxVars[0].SpecialLw.isRelease != FALSE))
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
            return;
        }
        ftFox_SpecialAirLwEnd_Action(fighter_gobj);
    }
}

// 0x800E8A9C
// https://decomp.me/scratch/PeBvo // Fox & Falco's aerial Reflector Loop Animation callback
void ftFox_SpecialAirLwLoop_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    if (((s32)fp->foxVars[0].SpecialLw.releaseLag <= 0) && ((s32)fp->foxVars[0].SpecialLw.isRelease != FALSE))
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
            return;
        }
        ftFox_SpecialAirLwEnd_Action(fighter_gobj);
    }
}

extern BOOL func_800CAED0(HSD_GObj*);

// 0x800E8B14
// https://decomp.me/scratch/sr7tP // Fox & Falco's grounded Reflector Loop IASA callback
void ftFox_SpecialLwLoop_IASA(HSD_GObj* fighter_gobj)
{
    if ((ftFox_SpecialLwTurn_Check(fighter_gobj) == FALSE) && (func_800CAED0(fighter_gobj) == FALSE))
    {
        if (ftFox_SpecialLwLoop_CheckPass(fighter_gobj)) return;
    }
}

extern BOOL func_800CB870(HSD_GObj*);

// 0x800E8B64
// https://decomp.me/scratch/SVWjl // Fox & Falco's aerial Reflector Loop IASA callback
void ftFox_SpecialAirLwLoop_IASA(HSD_GObj* fighter_gobj)
{
    if (ftFox_SpecialLwTurn_Check(fighter_gobj) == FALSE)
    {
        if (func_800CB870(fighter_gobj)) return;
    }
}

// 0x800E8BA4
// https://decomp.me/scratch/sIE29 // Check for drop-through platform while in SpecialLwLoop
BOOL ftFox_SpecialLwLoop_CheckPass(HSD_GObj* fighter_gobj)
{
    if (func_80099F1C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialLwLoop_Pass(fighter_gobj);
        return TRUE;
    }
    return FALSE;
}

// 0x800E8BEC
// https://decomp.me/scratch/MPQ9F // Fox & Falco's Reflector Loop Platform Drop Action State handler
void ftFox_SpecialLwLoop_Pass(HSD_GObj* fighter_gobj)
{
    func_8009A184(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP, FTFOX_SPECIALLW_COLL_FLAG, getFighter(fighter_gobj)->x894_currentAnimFrame);
    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

extern void func_8007AEF8(HSD_GObj*);

// 0x800E8C34
// https://decomp.me/scratch/8fHun // Fox & Falco's grounded Reflector Loop Physics callback
void ftFox_SpecialLwLoop_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

inline void ftFox_SpecialLw_InlinePhys(HSD_GObj* fighter_gobj)
{
    attr* ftAttrs;
    ftFoxAttributes* foxAttrs;
    Fighter* fp = getFighter(fighter_gobj);

    ftAttrs = getFtAttrs(fp);
    foxAttrs = getFtSpecialAttrs(fp);

    if (fp->foxVars[0].SpecialLw.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialLw.gravityDelay--;
    }
    else func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL, ftAttrs->x170_TerminalVelocity);
    func_8007CF58(fp);
}

// 0x800E8C68
// https://decomp.me/scratch/J4FH6 // Fox & Falco's aerial Reflector Loop Physics callback
void ftFox_SpecialAirLwLoop_Phys(HSD_GObj* fighter_gobj)
{
    ftFox_SpecialLw_InlinePhys(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 0x800E8CDC
// https://decomp.me/scratch/sJ2uE // Fox & Falco's grounded Reflector Loop Collision callback
void ftFox_SpecialLwLoop_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialLwLoop_GroundToAir(fighter_gobj);
    }
}

// 0x800E8D18
// https://decomp.me/scratch/LagPr // Fox & Falco's aerial Reflector Loop Collision callback
void ftFox_SpecialAirLwLoop_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialAirLwLoop_AirToGround(fighter_gobj);
    }
}

// 0x800E8D54
// https://decomp.me/scratch/58iq0 // Fox & Falco's ground -> air Reflector Loop Action State handler
void ftFox_SpecialLwLoop_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

// 0x800E8DBC
// https://decomp.me/scratch/AHYGP // Fox & Falco's air -> ground Reflector Loop Action State Handler
void ftFox_SpecialAirLwLoop_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

extern void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*, void(*cb_OnReflect)(HSD_GObj*));

// 0x800E8E2C
// https://decomp.me/scratch/MYfXM // Create Reflector's reflect bubble
void ftFox_SpecialLw_CreateReflectHit(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    ftColl_CreateReflectHit(fighter_gobj, &foxAttrs->xB0_FOX_REFLECTOR_REFLECTION, ftFox_SpecialLwHit_Action);
}

// 0x800E8E60
// https://decomp.me/scratch/mCpWx // Fox & Falco's grounded Reflector Loop Action State handler
void ftFox_SpecialLwLoop_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

// 0x800E8EC0
// https://decomp.me/scratch/d6eYH // Fox & Falco's aerial Reflector Loop Action State handler
void ftFox_SpecialAirLwLoop_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);

    ftFox_SpecialLw_CreateReflectHit(fighter_gobj);
}

extern f32 func_80075F48(Fighter*, s32);

#pragma dont_inline on

// 0x800E8F20
// https://decomp.me/scratch/oQ3MP // Fox & Falco's Reflector Turn function
void ftFox_SpecialLw_Turn(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    s32 var[2];

    fp->foxVars[0].SpecialLw.turnFrames--;
    if (((u32)fp->x2200_ftcmd_var0 == 0U) && ((s32)fp->foxVars[0].SpecialLw.turnFrames <= foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES))
    {
        fp->x2200_ftcmd_var0 = 1;
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    func_80075AF0(fp, 0, -((0.01745329238474369f * (180.0f / foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES)) - func_80075F48(fp, 0)));
}

#pragma dont_inline off

// 0x800E8F20
// https://decomp.me/scratch/oQ3MP // Fox & Falco's Reflector Turn function
inline void ftFox_SpecialLw_Turn_Inline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    fp->foxVars[0].SpecialLw.turnFrames--;
    if (((u32)fp->x2200_ftcmd_var0 == 0U) && ((s32)fp->foxVars[0].SpecialLw.turnFrames <= foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES))
    {
        fp->x2200_ftcmd_var0 = 1;
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    func_80075AF0(fp, 0, -((0.01745329238474369f * (180.0f / foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES)) - func_80075F48(fp, 0)));
}

// 0x800E8FDC
// https://decomp.me/scratch/UEMry // Fox & Falco's grounded Reflector Turn Animation callback
void ftFox_SpecialLwTurn_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 var[4];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    ftFox_SpecialLw_Turn_Inline(fighter_gobj);
    if ((s32)fp->foxVars[0].SpecialLw.turnFrames <= 0)
    {
        ftFox_SpecialLwHit_Check(fighter_gobj);
    }
}

// 0x800E90EC
// https://decomp.me/scratch/ad8wR // Fox & Falco's aerial Reflector Turn Animation callback
void ftFox_SpecialAirLwTurn_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 var[5];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    ftFox_SpecialLw_Turn_Inline(fighter_gobj);
    if ((s32)fp->foxVars[0].SpecialLw.turnFrames <= 0)
    {
        ftFox_SpecialLwHit_Check(fighter_gobj);
    }
}

// 0x800E91FC - Fox & Falco's grounded Reflector Turn IASA callback
void ftFox_SpecialLwTurn_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9200 - Fox & Falco's aerial Reflector Turn IASA callback
void ftFox_SpecialAirLwTurn_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9204
// https://decomp.me/scratch/sQ6Zw // Fox & Falco's grounded Reflector Turn Physics callback
void ftFox_SpecialLwTurn_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 0x800E9238
// https://decomp.me/scratch/3Q4Oj // Fox & Falco's aerial Reflector Turn Physics callback
void ftFox_SpecialAirLwTurn_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars[0].SpecialLw.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialLw.gravityDelay--;
    }
    else
    {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL, ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 0x800E92AC
// https://decomp.me/scratch/hKwfA // Fox & Falco's grounded Reflector Turn Collision callback
void ftFox_SpecialLwTurn_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialLwTurn_GroundToAir(fighter_gobj);
    }
}

// 0x800E92E8
// https://decomp.me/scratch/L0Bhg // Fox & Falco's aerial Reflector Turn Collision callback
void ftFox_SpecialAirLwTurn_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialAirLwTurn_GroundToAir(fighter_gobj);
    }
}

inline void ftFox_SpecialLw_SetReflectVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
}

// 0x800E9324
// https://decomp.me/scratch/L2Rcy // Fox & Falco's ground -> air Reflector Turn Action State handler
void ftFox_SpecialLwTurn_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_TURN, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftFox_SpecialLw_SetReflectVars(fighter_gobj);
}

// 0x800E93A4
// https://decomp.me/scratch/BwZlC // Fox & Falco's air -> ground Reflector Turn Action State handler
void ftFox_SpecialAirLwTurn_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_TURN, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    ftFox_SpecialLw_SetReflectVars(fighter_gobj);
}

inline void ftFox_SpecialLwTurn_SetVarAll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
    fp->foxVars[0].SpecialLw.turnFrames = foxAttrs->x9C_FOX_REFLECTOR_TURN_FRAMES;
    fp->x2200_ftcmd_var0 = 0;
    ftFox_SpecialLw_Turn(fighter_gobj);
}

extern BOOL func_800C97A8(HSD_GObj*);

// 0x800E942C
// https://decomp.me/scratch/Hr5UW // Fox & Falco's Reflector Turn Action State handler
BOOL ftFox_SpecialLwTurn_Check(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (func_800C97A8(fighter_gobj) != FALSE)
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_TURN, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialLwTurn_SetVarAll(fighter_gobj);
        }
        else
        {
            Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_TURN, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
            ftFox_SpecialLwTurn_SetVarAll(fighter_gobj);
        }
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;

        return TRUE;
    }
    return FALSE;
}

inline void ftFox_SpecialLwHit_CreateReflectInline(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    ftColl_CreateReflectHit(fighter_gobj, &foxAttrs->xB0_FOX_REFLECTOR_REFLECTION, ftFox_SpecialLwHit_Action);
}

// 0x800E9564
// https://decomp.me/scratch/R1XfY // Fox & Falco's Reflector Hit Action State handler
BOOL ftFox_SpecialLwHit_Check(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (((s32)fp->foxVars[0].SpecialLw.releaseLag <= 0) && ((s32)fp->foxVars[0].SpecialLw.isRelease != FALSE))
    {
        if ((s32)fp->xE0_ground_or_air == GA_Ground)
        {
            ftFox_SpecialLwEnd_Action(fighter_gobj);
        }
        else
        {
            ftFox_SpecialAirLwEnd_Action(fighter_gobj);
        }
        return FALSE;
    }
    if ((s32)fp->xE0_ground_or_air == GA_Ground)
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_LOOP, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
        ftFox_SpecialLwHit_CreateReflectInline(fighter_gobj);
    }
    else
    {
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_LOOP, FIGHTER_GFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
        ftFox_SpecialLwHit_CreateReflectInline(fighter_gobj);
    }
    return TRUE;
}

// 0x800E965C
// https://decomp.me/scratch/S2PRK // Fox & Falco's grounded Reflector Hit Animation callback
void ftFox_SpecialLwHit_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 var;

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        if (ftFox_SpecialLwHit_Check(fighter_gobj) != FALSE)
        {
            func_8007DB24(fighter_gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
        }
    }
}

#pragma dont_inline on

// 0x800E97B4
// https://decomp.me/scratch/A9W0B // Fox & Falco's aerial Reflector Hit Animation callback
void ftFox_SpecialAirLwHit_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    s32 var[2];

    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        fp->foxVars[0].SpecialLw.isRelease = TRUE;
    }
    if (fp->foxVars[0].SpecialLw.releaseLag > 0)
    {
        fp->foxVars[0].SpecialLw.releaseLag--;
    }
    if ((ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) && (ftFox_SpecialLwHit_Check(fighter_gobj) != FALSE))
    {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateLoopGFX;
    }
}

#pragma dont_inline off

// 0x800E9844 - Fox & Falco's grounded Reflector Hit IASA callback
void ftFox_SpecialLwHit_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9848 - Fox & Falco's aerial Reflector Hit IASA callback
void ftFox_SpecialAirLwHit_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E984C
// https://decomp.me/scratch/P8Wyt // Fox & Falco's grounded Reflector Hit Physics callback
void ftFox_SpecialLwHit_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
    func_8007AEF8(fighter_gobj);
}

// 0x800E9880
// https://decomp.me/scratch/RUoIF // Fox & Falco's aerial Reflector Hit Physics callback
void ftFox_SpecialAirLwHit_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars[0].SpecialLw.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialLw.gravityDelay--;
    }
    else
    {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL, ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
    func_8007AEF8(fighter_gobj);
}

// 0x800E98F4
// https://decomp.me/scratch/tH9vD // Fox & Falco's grounded Reflector Hit Collision callback
void ftFox_SpecialLwHit_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialLwHit_GroundToAir(fighter_gobj);
    }
}

// 0x800E9930
// https://decomp.me/scratch/fkoyN // Fox & Falco's aerial Reflector Hit Collision callback
void ftFox_SpecialAirLwHit_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialAirLwHit_AirToGround(fighter_gobj);
    }
}

// 0x800E996C
// https://decomp.me/scratch/wnviJ // Fox & Falco's ground -> air Reflector Hit Action State handler
void ftFox_SpecialLwHit_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_HIT, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);
}

// 0x800E99D4
// https://decomp.me/scratch/zXqEI // Fox & Falco's air -> ground Reflector Hit Action State handler
void ftFox_SpecialAirLwHit_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_HIT, FTFOX_SPECIALLW_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);
}

// 0x800E9A44
// https://decomp.me/scratch/XIxX1 // Toggle bit flag and set OnReflect callback for Reflector
void ftFox_SpecialLwHit_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->x2218_flag.bits.b3 = 1;
    fp->cb.x21C8_callback_OnReflectHit = ftFox_SpecialLwHit_Action;
}

// 0x800E9A68
// https://decomp.me/scratch/SyGv6 // Fox & Falco's Reflect Hit Action State handler
void ftFox_SpecialLwHit_Action(HSD_GObj* fighter_gobj)
{
    Vec3 sp14;
    Fighter* fp = fp = getFighter(fighter_gobj);
    s32 ASID;

    fp->x2C_facing_direction = fp->ReflectAttr.x1A2C_reflectHitDirection;

    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, NULL, &sp14);
    func_800119DC(&sp14, 0x78, 3.0f, 0.10000000149011612f, 1.0471975803375244f);

    if ((s32)fp->xE0_ground_or_air == GA_Ground)
    {
        ASID = 0x16A;
    }
    else ASID = 0x16F;

    Fighter_ActionStateChange_800693AC(fighter_gobj, ASID, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftFox_SpecialLwHit_SetCall(fighter_gobj);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialLw_CreateReflectGFX;
}

// 0x800E9B40
// https://decomp.me/scratch/cfyZU // Fox & Falco's grounded Reflector End Animation callback
void ftFox_SpecialLwEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x800E9B84
// https://decomp.me/scratch/2gua7 // Fox & Falco's aerial Reflector End Animation callback
void ftFox_SpecialAirLwEnd_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8007DB24(fighter_gobj);
        func_8007D92C(fighter_gobj);
    }
}

// 0x800E9BC8 - Fox & Falco's grounded Reflector End IASA callback
void ftFox_SpecialLwEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9BCC - Fox & Falco's aerial Reflector End IASA callback
void ftFox_SpecialAirLwEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x800E9BD0 - Fox & Falco's grounded Reflector End Physics callback
void ftFox_SpecialLwEnd_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x800E9BF0
// https://decomp.me/scratch/ivwWP // Fox & Falco's aerial Reflector End Physics callback
void ftFox_SpecialAirLwEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = getFighter(fighter_gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);
    attr* ftAttrs = getFtAttrs(fp);
    s32 var;

    if (fp->foxVars[0].SpecialLw.gravityDelay != 0)
    {
        fp->foxVars[0].SpecialLw.gravityDelay--;
    }
    else
    {
        func_8007D494(fp, foxAttrs->xAC_FOX_REFLECTOR_FALL_ACCEL, ftAttrs->x170_TerminalVelocity);
    }
    func_8007CF58(fp);
}

// 0x800E9C50
// https://decomp.me/scratch/chekC // Fox & Falco's grounded Reflector End Collision callback
void ftFox_SpecialLwEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftFox_SpecialLwEnd_GroundToAir(fighter_gobj);
    }
}

// 0x800E9C8C
// https://decomp.me/scratch/t5ghA // Fox & Falco's aerial Reflector End Collision callback
void ftFox_SpecialAirLwEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftFox_SpecialAirLwEnd_AirToGround(fighter_gobj);
    }
}

// 0x800E9CC8
// https://decomp.me/scratch/xAGsZ // Fox & Falco's ground -> air Reflector End Action State handler
void ftFox_SpecialLwEnd_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_END, (FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x800E9D24
// https://decomp.me/scratch/pG1xg // Fox & Falco's air -> ground Reflector End Action State handler
void ftFox_SpecialAirLwEnd_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_END, (FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

// 0x800E9D88
// https://decomp.me/scratch/oUZ7Q // Fox & Falco's grounded Reflector End Action State handler
void ftFox_SpecialLwEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALLW_END, 0, NULL, 0.0f, 1.0f, 0.0f);
}

// 0x800E9DC0 - Fox & Falco's aerial Reflector End Action State handler
void ftFox_SpecialAirLwEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_FOX_SPECIALAIRLW_END, 0, NULL, 0.0f, 1.0f, 0.0f);
}
