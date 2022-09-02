#include <melee/ft/chara/ftLuigi/ftluigi.h>

// 0x80142A24
// https://decomp.me/scratch/TEGVv // Luigi's Green Missile GFX callback
void ftLuigi_SpecialS_SetGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->x2219_flag.bits.b0 == 0)
    {
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80142A5C
// https://decomp.me/scratch/EHQ0r // Luigi's Green Missile Setup (RNG + calculations)
void ftLuigi_SpecialS_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);

    fp->x2200_ftcmd_var0 = 0;
    if ((f32)fp->x673 < luigiAttrs->x4_LUIGI_GREENMISSILE_SMASH)
    {
        fp->luigiVars[0].SpecialS.chargeFrames = (s32)luigiAttrs->x8_LUIGI_GREENMISSILE_CHARGE_RATE;
        fp->x2072_b4 = 1;
    }
    else fp->luigiVars[0].SpecialS.chargeFrames = 0;

    if (HSD_Randi((s32)luigiAttrs->x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE) == 0)
    {
        fp->luigiVars[0].SpecialS.isMisfire = TRUE;
        return;
    }
    fp->luigiVars[0].SpecialS.isMisfire = FALSE;
}

// 0x80142B14
// https://decomp.me/scratch/6eTeE // Luigi's grounded Green Missile Action State handler
void ftLuigi_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    void (*callback)(HSD_GObj*);
    s32 ASID;

    fp->cb.x21EC_callback = ftLuigi_SpecialS_SetVars;
    fp->xEC_ground_vel /= luigiAttrs->x18_LUIGI_GREENMISSILE_TRACTION;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

// 0x80142B88
// https://decomp.me/scratch/Wb3jT // Luigi's aerial Green Missile Action State handler 
void ftLuigi_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    void (*callback)(HSD_GObj*);
    s32 ASID;

    fp->cb.x21EC_callback = ftLuigi_SpecialS_SetVars;
    fp->x80_self_vel.x /= luigiAttrs->x18_LUIGI_GREENMISSILE_TRACTION;
    fp->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

// 0x80142C00
// https://decomp.me/scratch/tyVNQ // Luigi's Green Missile OnGiveDamage callback
void ftLuigi_SpecialS_OnGiveDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->x80_self_vel.x = 0.0f;
    if (fp->x80_self_vel.y >= 0.0f)
    {
        fp->x80_self_vel.y = 0.0f;
    }
    ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
}

// 0x80142C40
// https://decomp.me/scratch/Jk0de // Luigi's grounded Green Missile Start Animation callback
void ftLuigi_SpecialSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialSHold_Action(fighter_gobj);
    }
}

// 0x80142C7C - Luigi's aerial Green Missile Start Animation callback
void ftLuigi_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialAirSHold_Action(fighter_gobj);
    }
}

// 0x80142CB8 - Luigi's grounded Green Missile Start IASA callback
void ftLuigi_SpecialSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80142CBC - Luigi's aerial Green Missile Start IASA callback
void ftLuigi_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80142CC0
// https://decomp.me/scratch/AbUbj // Luigi's grounded Green Missile Start Physics callback
void ftLuigi_SpecialSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007C930(fp, ((ftLuigiAttributes*)getFtSpecialAttrs(fp))->x1C_LUIGI_GREENMISSILE_UNK2);
    func_8007CB74(fighter_gobj);
}

// 0x80142D00
// https://decomp.me/scratch/O4crQ // Luigi's aerial Green Missile Start Physics callback
void ftLuigi_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    attr* ftAttr = &fp->x110_attr;
    s32 var;
    s32 var2;

    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        func_8007D494(fp, luigiAttrs->x20_LUIGI_GREENMISSILE_FALLING_SPEED, ftAttr->x170_TerminalVelocity);
    }
    func_8007CE94(fp, luigiAttrs->x1C_LUIGI_GREENMISSILE_UNK2);
}

// 0x80142D60 - Luigi's grounded Green Missile Start Collision callback
void ftLuigi_SpecialSStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialSStart_GroundToAir(fighter_gobj);
    }
}

// 0x80142D80 - Luigi's aerial Green Missile Start Collision callback
void ftLuigi_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftLuigi_SpecialAirSStart_AirToGround(fighter_gobj);
    }
}

// 0x80142DD8
// https://decomp.me/scratch/MX0y2 // Luigi's Green Missile Start ground -> air Action State handler
void ftLuigi_SpecialSStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_START, FTLUIGI_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x80142E38
// https://decomp.me/scratch/KJRhZ // Luigi's Green Missile Start air -> ground Action State handler
void ftLuigi_SpecialAirSStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_START, FTLUIGI_SPECIALS_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x80142E98
// https://decomp.me/scratch/JZWFY // Luigi's grounded Green Missile Charge Animation callback
void ftLuigi_SpecialSHold_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    void (*callback)(HSD_GObj*);
    s32 stateVar;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }
    fp->luigiVars[0].SpecialS.chargeFrames++;
    if ((f32)fp->luigiVars[0].SpecialS.chargeFrames > luigiAttrs->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLuigi_SpecialSLaunch_Action(fighter_gobj);
    }
}

// 0x80142F38
// https://decomp.me/scratch/taZqq // Luigi's aerial Green Missile Charge Animation callback
void ftLuigi_SpecialAirSHold_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    void (*callback)(HSD_GObj*);
    s32 stateVar;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }
    fp->luigiVars[0].SpecialS.chargeFrames++;
    if ((f32)fp->luigiVars[0].SpecialS.chargeFrames > luigiAttrs->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLuigi_SpecialAirSLaunch_Action(fighter_gobj);
    }
}

// 0x80142FD8
// https://decomp.me/scratch/spI7k // Luigi's grounded Green Missile Charge IASA callback
void ftLuigi_SpecialSHold_IASA(HSD_GObj* fighter_gobj)
{
    if ((getFighter(fighter_gobj)->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        ftLuigi_SpecialSLaunch_Action(fighter_gobj);
    }
}

// 0x80143008 - Luigi's aerial Green Missile Charge IASA callback
void ftLuigi_SpecialAirSHold_IASA(HSD_GObj* fighter_gobj)
{
    if ((getFighter(fighter_gobj)->input.x65C_heldInputs & HSD_BUTTON_B) == FALSE)
    {
        ftLuigi_SpecialAirSLaunch_Action(fighter_gobj);
    }
}

// 0x80143038 - Luigi's grounded Green Missile Charge Physics callback
void ftLuigi_SpecialSHold_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x80143058 - Luigi's aerial Green Missile Charge Physics callback
void ftLuigi_SpecialAirSHold_Phys(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

// 0x80143078 - Luigi's grounded Green Missile Charge Collision callback
void ftLuigi_SpecialSHold_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialSHold_GroundToAir(fighter_gobj);
    }
}

// 0x801430B4 - Luigi's aerial Green Missile Charge Collision callback
void ftLuigi_SpecialAirSHold_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftLuigi_SpecialAirSHold_AirToGround(fighter_gobj);
    }
}

// 0x801430F0
// https://decomp.me/scratch/IJjXT // Luigi's Green Missile Charge ground -> air Acion State handler
void ftLuigi_SpecialSHold_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_HOLD, (FIGHTER_GFX_PRESERVE | FTLUIGI_SPECIALS_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x80143150 - Luigi's Green Missile Charge air -> ground Action State handler
void ftLuigi_SpecialAirSHold_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_HOLD, (FIGHTER_GFX_PRESERVE | FTLUIGI_SPECIALS_COLL_FLAG), NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x801431B0
// https://decomp.me/scratch/0FOkW // Luigi's grounded Green Missile Charge Action State handler
void ftLuigi_SpecialSHold_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 ASID;
    void (*callback)(HSD_GObj*);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_HOLD, FIGHTER_SFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
    getFighter(fighter_gobj)->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
}

// 0x80143204
// https://decomp.me/scratch/0FOkW // Luigi's aerial Green Missile Charge Action State handler
void ftLuigi_SpecialAirSHold_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 ASID;
    void (*callback)(HSD_GObj*);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_HOLD, FIGHTER_SFX_PRESERVE, NULL, 0.0f, 1.0f, 0.0f);
    getFighter(fighter_gobj)->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
}

// 0x80143258
// https://decomp.me/scratch/8478K // Luigi's grounded Green Missile Launch Animation callback
void ftLuigi_SpecialSLaunch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    s32 var;

    fp = getFighter(fighter_gobj);
    luigiAttrs = getFtSpecialAttrs(fp);
    if (((s32)fp->luigiVars[0].SpecialS.isMisfire == FALSE) && ((s32)fp->x914[0].x0 == 1))
    {
        func_8007ABD0(&fp->x914[0], (u32)(((f32)fp->luigiVars[0].SpecialS.chargeFrames * luigiAttrs->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE) + luigiAttrs->x10_LUIGI_GREENMISSILE_DAMAGE_TILT), fighter_gobj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        func_8007D5D4(fp);
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

// 0x80143304
// https://decomp.me/scratch/hlU8P // Luigi's aerial Green Missile Launch Animation callback
void ftLuigi_SpecialAirSLaunch_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    s32 var;

    fp = getFighter(fighter_gobj);
    luigiAttrs = getFtSpecialAttrs(fp);
    if (((s32)fp->luigiVars[0].SpecialS.isMisfire == FALSE) && ((s32)fp->x914[0].x0 == 1))
    {
        func_8007ABD0(&fp->x914[0], (u32)(((f32)fp->luigiVars[0].SpecialS.chargeFrames * luigiAttrs->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE) + luigiAttrs->x10_LUIGI_GREENMISSILE_DAMAGE_TILT), fighter_gobj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

// 0x801433A8 - Luigi's grounded Green Missile Launch IASA callback
void ftLuigi_SpecialSLaunch_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x801433AC - Luigi's aerial Green Missile Launch IASA callback
void ftLuigi_SpecialAirSLaunch_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x801433B0 - Luigi's grounded Green Missile Launch Physics callback
void ftLuigi_SpecialSLaunch_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x801433D0 - Luigi's aerial Green Missile Launch Physics callback
void ftLuigi_SpecialAirSLaunch_Phys(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

// 0x801433F0 - Luigi's grounded Green Missile Launch Collision callback
void ftLuigi_SpecialSLaunch_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialSLaunch_GroundToAir(fighter_gobj);
    }
}

// 0x8014342C - Luigi's aerial Green Missile Launch Collision callback
void ftLuigi_SpecialAirSLaunch_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftLuigi_SpecialAirSLaunch_AirToGround(fighter_gobj);
    }
}

// 0x80143468
// https://decomp.me/scratch/IJjXT // Luigi's Green Missile Launch ground -> air Acion State handler
void ftLuigi_SpecialSLaunch_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_LAUNCH, FTLUIGI_SPECIALS_GROUND_AIR_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x801434C8 - Luigi's Green Missile Launch air -> ground Action State handler
void ftLuigi_SpecialAirSLaunch_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_LAUNCH, FTLUIGI_SPECIALS_GROUND_AIR_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

inline void ftLuigi_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    func_8007DB24(fighter_gobj);
}

inline void ftLuigi_SpecialS_Setup(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x2219_flag.bits.b0 == 0)
    {
        ef_Spawn(0x50A, fighter_gobj, fp->x5E8_fighterBones[0x4].x0_jobj);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x80143528
// https://decomp.me/scratch/EzvGh // Luigi's grounded Green Missile Launch Action State handler
void ftLuigi_SpecialSLaunch_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    void (*EnterHitlag)(HSD_GObj*);
    void (*ExitHitlag)(HSD_GObj*);
    s32 stateVar;

    if ((s32)fp->luigiVars[0].SpecialS.isMisfire != FALSE)
    {
        ftLuigi_SpecialSMisfire_Action(fighter_gobj);
        return;
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_LAUNCH, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

// 0x80143600
// https://decomp.me/scratch/ehhGj // Luigi's aerial Green Missile Launch Action State handler
void ftLuigi_SpecialAirSLaunch_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    s32 stateVar;

    if ((s32)fp->luigiVars[0].SpecialS.isMisfire != FALSE)
    {
        ftLuigi_SpecialAirSMisfire_Action(fighter_gobj);
        return;
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_LAUNCH, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

// 0x801436D8
// https://decomp.me/scratch/04NUV // Luigi's grounded Green Missile Misfire Animation callback
void ftLuigi_SpecialSMisfire_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    s32 stateVar;

    if (((s32)fp->luigiVars[0].SpecialS.isMisfire == FALSE) && ((s32)fp->x914[0].x0 == 1))
    {
        func_8007ABD0(&fp->x914[0], (u32)(((f32)fp->luigiVars[0].SpecialS.chargeFrames * luigiAttrs->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE) + luigiAttrs->x10_LUIGI_GREENMISSILE_DAMAGE_TILT), fighter_gobj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        func_8007D5D4(fp);
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

// 0x80143784
// https://decomp.me/scratch/gBi6d // Luigi's aerial Green Missile Misfire Animation callback
void ftLuigi_SpecialAirSMisfire_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    s32 stateVar;

    if (((s32)fp->luigiVars[0].SpecialS.isMisfire == FALSE) && ((s32)fp->x914[0].x0 == 1))
    {
        func_8007ABD0(&fp->x914[0], (u32)(((f32)fp->luigiVars[0].SpecialS.chargeFrames * luigiAttrs->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE) + luigiAttrs->x10_LUIGI_GREENMISSILE_DAMAGE_TILT), fighter_gobj);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0U)
    {
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

// 0x80143828 - Luigi's grounded Green Missile Misfire IASA callback
void ftLuigi_SpecialSMisfire_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x8014382C - Luigi's aerial Green Missile Misfire IASA callback
void ftLuigi_SpecialAirSMisfire_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143830 - Luigi's grounded Green Missile Misfire Physics callback
void ftLuigi_SpecialSMisfire_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x80143850 - Luigi's aerial Green Missile Misfire Physics callback
void ftLuigi_SpecialAirSMisfire_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x80143870 - Luigi's grounded Green Missile Misfire Collision callback
void ftLuigi_SpecialSMisfire_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialSMisfire_GroundToAir(fighter_gobj);
    }
}

// 0x801438AC - Luigi's aerial Green Missile Misfire Collision callback
void ftLuigi_SpecialAirSMisfire_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        ftLuigi_SpecialAirSMisfire_AirToGround(fighter_gobj);
    }
}

// 0x801438E8
// https://decomp.me/scratch/Kx8l7 // Luigi's Green Missile Misfire ground -> air Action State handler
void ftLuigi_SpecialSMisfire_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_MISFIRE, FTLUIGI_SPECIALS_GROUND_AIR_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x80143948
// https://decomp.me/scratch/2R5bm // Luigi's Green Missile Misfire air -> ground Action State Handler
void ftLuigi_SpecialAirSMisfire_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_MISFIRE, FTLUIGI_SPECIALS_GROUND_AIR_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x801439A8
// https://decomp.me/scratch/EDozx // Luigi's grounded Green Missile Misfire Action State handler
void ftLuigi_SpecialSMisfire_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    u32 ftcmd;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_MISFIRE, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

// 0x80143A60 - Luigi's aerial Green Missile Misfire Action State handler
void ftLuigi_SpecialAirSMisfire_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    u32 ftcmd;

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_MISFIRE, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

// 0x80143B18 - Luigi's grounded Green Missile Fly Animation callback
void ftLuigi_SpecialSFly_Anim(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143B1C - Luigi's aerial Green Missile Fly Animation callback
void ftLuigi_SpecialAirSFly_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
    }
}

// 0x80143B58 - Luigi's grounded Green Missile Fly IASA callback
void ftLuigi_SpecialSFly_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143B5C - Luigi's aerial Green Missile Fly IASA callback
void ftLuigi_SpecialAirSFly_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143B60 - Luigi's grounded Green Missile Fly Physics callback
void ftLuigi_SpecialSFly_Phys(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143B64
// https://decomp.me/scratch/urKKQ // Luigi's aerial Green Missile Fly Physics callback
void ftLuigi_SpecialAirSFly_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);

    if ((u32)fp->x2200_ftcmd_var0 != 0)
    {
        func_8007D494(fp, luigiAttrs->x40_LUIGI_GREENMISSILE_GRAVITY_MUL, luigiAttrs->x34_LUIGI_GREENMISSILE_GRAVITY_START);
    }
    else
    {
        func_8007D494(fp, luigiAttrs->x30_LUIGI_GREENMISSILE_MUL_Y, luigiAttrs->x34_LUIGI_GREENMISSILE_GRAVITY_START);
    }
    if ((u32)fp->x2200_ftcmd_var0 != 0)
    {
        func_8007CE94(fp, luigiAttrs->x3C_LUIGI_GREENMISSILE_X_DECEL);
    }
}

// 0x80143BE0 - Luigi's grounded Green Missile Fly Collision callback
void ftLuigi_SpecialSFly_Coll(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143BE4 
// https://decomp.me/scratch/bjBo1 // Luigi's aerial Green Missile Fly Collision callback
void ftLuigi_SpecialAirSFly_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* temp_fp;
    CollData* collData;
    s32 envFlags;

    temp_fp = fighter_gobj->user_data;
    fp = temp_fp;
    collData = &temp_fp->x6F0_collData;

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fp);
        ftLuigi_SpecialSEnd_Action(fighter_gobj);
    }
    envFlags = collData->x134_envFlags;
    if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0))
    {
        ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
    }
}

// 0x80143C60
// https://decomp.me/scratch/xomU0 // Luigi's Green Missile Fly Setup
void ftLuigi_SpecialSFly_Action(HSD_GObj* fighter_gobj)
{
    f32 temp_vel;
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;

    fp = getFighter(fighter_gobj);
    luigiAttrs = getFtSpecialAttrs(fp);
    fp->x2200_ftcmd_var0 = 0;
    if ((s32)fp->luigiVars[0].SpecialS.isMisfire != FALSE)
    {
        fp->x80_self_vel.x = (f32)luigiAttrs->x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    }
    else
    {
        fp->x80_self_vel.x = (f32)((luigiAttrs->x28_LUIGI_GREENMISSILE_MUL_X * (f32)fp->luigiVars[0].SpecialS.chargeFrames) + luigiAttrs->x24_LUIGI_GREENMISSILE_VEL_X);
    }
    fp->x80_self_vel.x *= fp->x2C_facing_direction;
    if ((s32)fp->luigiVars[0].SpecialS.isMisfire != FALSE)
    {
        fp->x80_self_vel.y = (f32)luigiAttrs->x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;
    }
    else
    {
        temp_vel = luigiAttrs->x2C_LUIGI_GREENMISSILE_VEL_Y;
        fp->x80_self_vel.y = (f32)((0.5f * temp_vel) + (temp_vel * ((0.5f * (f32)fp->luigiVars[0].SpecialS.chargeFrames) / luigiAttrs->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)));
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_FLY, FTLUIGI_SPECIALS_MISFIRE_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21F8_callback = func_8007F76C;
    fp->cb.x21C0_callback_OnGiveDamage = ftLuigi_SpecialS_OnGiveDamage;
}

// 0x80143D7C - Luigi's grounded Green Missile End Animation callback
void ftLuigi_SpecialSEnd_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80143DB8 - Luigi's aerial Green Missile End Animation callback
void ftLuigi_SpecialAirSEnd_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80143DF4 - Luigi's grounded Green Missile End IASA callback
void ftLuigi_SpecialSEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143DF8 - Luigi's aerial Green Missile End IASA callback
void ftLuigi_SpecialAirSEnd_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// 0x80143DFC
// https://decomp.me/scratch/GZ27s // Luigi's grounded Green Missile End Physics callback
void ftLuigi_SpecialSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 decel;

    func_8007C930(fp, ((ftLuigiAttributes*)fp->x2D4_specialAttributes)->x3C_LUIGI_GREENMISSILE_X_DECEL);
    func_8007CB74(fighter_gobj);
}

// 0x80143E3C
// https://decomp.me/scratch/9y6Ua // Luigi's aerial Green Missile End Physics callback
void ftLuigi_SpecialAirSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    f32 gravity;
    f32 decel;

    func_8007D494(fp, luigiAttrs->x40_LUIGI_GREENMISSILE_GRAVITY_MUL, fp->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fp, luigiAttrs->x3C_LUIGI_GREENMISSILE_X_DECEL);
}

// 0x80143E8C - Luigi's grounded Green Missile End Collision callback
void ftLuigi_SpecialSEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (func_80082708(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80143EC8 - Luigi's aerial Green Missile End Collision callback
void ftLuigi_SpecialAirSEnd_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        func_8007D7FC(fp);
        ftLuigi_SpecialSEnd_Action(fighter_gobj);
    }
}

// 0x80143F18
// https://decomp.me/scratch/zZpxK // Luigi's Green Missile End air -> ground Action State handler
void ftLuigi_SpecialSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->xEC_ground_vel /= luigiAttrs->x38_LUIGI_GREENMISSILE_FRICTION_END;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALS_END, 0, NULL, 0.0f, 1.0f, 0.0f);
}

// 0x80143F70
// https://decomp.me/scratch/pVzMc // Luigi's Green Missile End ground -> air Action State handler
void ftLuigi_SpecialAirSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.x /= luigiAttrs->x38_LUIGI_GREENMISSILE_FRICTION_END;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRS_END, 0, NULL, 0.0f, 1.0f, 0.0f);
}
