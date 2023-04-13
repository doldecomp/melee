#include <melee/lb/forward.h>

#include "melee/ft/inlines.h"

#include <sysdolphin/baselib/gobjproc.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftLuigi/ftluigi.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>

/// Luigi's Green Missile GFX callback
void ftLuigi_SpecialS_SetGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (!fp->x2219_flag.bits.b0) {
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

/// Luigi's Green Missile Setup (RNG + calculations)
void ftLuigi_SpecialS_SetVars(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrs(fp);

    fp->x2200_ftcmd_var0 = 0;

    if (fp->x673 < sa->x4_LUIGI_GREENMISSILE_SMASH) {
        fp->sv.lg.SpecialS.chargeFrames =
            sa->x8_LUIGI_GREENMISSILE_CHARGE_RATE;
        fp->x2070.x2072_b4 = true;
    } else {
        fp->sv.lg.SpecialS.chargeFrames = 0;
    }

    if (HSD_Randi(sa->x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE) == 0) {
        fp->sv.lg.SpecialS.isMisfire = true;
    } else {
        fp->sv.lg.SpecialS.isMisfire = false;
    }
}

/// Luigi's grounded Green Missile Action State handler
void ftLuigi_SpecialS_StartMotion(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLuigi_SpecialAirS_StartMotion.
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftLuigi_SpecialS_SetVars;
    fp->xEC_ground_vel /= sa->x18_LUIGI_GREENMISSILE_TRACTION;

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_START, 0, NULL,
                              0, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
}

/// Luigi's aerial Green Missile Action State handler
void ftLuigi_SpecialAirS_StartMotion(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftLuigi_SpecialS_SetVars;
    fp->x80_self_vel.x /= sa->x18_LUIGI_GREENMISSILE_TRACTION;
    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_START, 0,
                              NULL, 0, 1, 0);

    ftAnim_8006EBA4(fighter_gobj);
}

/// Luigi's Green Missile OnGiveDamage callback
void ftLuigi_SpecialS_OnGiveDamage(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    fp->x80_self_vel.x = 0;

    if (fp->x80_self_vel.y >= 0) {
        fp->x80_self_vel.y = 0;
    }

    ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
}

/// Luigi's grounded Green Missile Start Animation callback
void ftLuigi_SpecialSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftLuigi_SpecialSHold_Action(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Start Animation callback
void ftLuigi_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftLuigi_SpecialAirSHold_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Start IASA callback
void ftLuigi_SpecialSStart_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Start IASA callback
void ftLuigi_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's grounded Green Missile Start Physics callback
void ftLuigi_SpecialSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007C930(fp, sa->x1C_LUIGI_GREENMISSILE_UNK2);
    ftCommon_8007CB74(fighter_gobj);
}

/// Luigi's aerial Green Missile Start Physics callback
void ftLuigi_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D494(fp, sa->x20_LUIGI_GREENMISSILE_FALLING_SPEED,
                          attr->x170_TerminalVelocity);
    }

    ftCommon_8007CE94(fp, sa->x1C_LUIGI_GREENMISSILE_UNK2);
}

/// Luigi's grounded Green Missile Start Collision callback
void ftLuigi_SpecialSStart_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftLuigi_SpecialSStart_GroundToAir(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Start Collision callback
void ftLuigi_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftLuigi_SpecialAirSStart_AirToGround(fighter_gobj);
    }
}

static Fighter_ActionStateChangeFlags const transition_flags0 =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_PreserveSfx | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Start ground -> air Action State handler
void ftLuigi_SpecialSStart_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_START,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Start air -> ground Action State handler
void ftLuigi_SpecialAirSStart_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_START,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Charge Animation callback
void ftLuigi_SpecialSHold_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLuigi_SpecialAirSHold_Anim.
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftCommon_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }

    fp->sv.lg.SpecialS.chargeFrames++;

    if (fp->sv.lg.SpecialS.chargeFrames >
        sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLuigi_SpecialSLaunch_Action(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Charge Animation callback
void ftLuigi_SpecialAirSHold_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftCommon_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }

    fp->sv.lg.SpecialS.chargeFrames++;

    if (fp->sv.lg.SpecialS.chargeFrames >
        sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLuigi_SpecialAirSLaunch_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Charge IASA callback
void ftLuigi_SpecialSHold_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        ftLuigi_SpecialSLaunch_Action(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Charge IASA callback
void ftLuigi_SpecialAirSHold_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        ftLuigi_SpecialAirSLaunch_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Charge Physics callback
void ftLuigi_SpecialSHold_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Luigi's aerial Green Missile Charge Physics callback
void ftLuigi_SpecialAirSHold_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

/// Luigi's grounded Green Missile Charge Collision callback
void ftLuigi_SpecialSHold_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftLuigi_SpecialSHold_GroundToAir(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Charge Collision callback
void ftLuigi_SpecialAirSHold_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftLuigi_SpecialAirSHold_AirToGround(fighter_gobj);
    }
}

static Fighter_ActionStateChangeFlags const transition_flags1 =
    transition_flags0 | FtStateChange_PreserveGfx;

/// Luigi's Green Missile Charge ground -> air Acion State handler
void ftLuigi_SpecialSHold_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_HOLD,
                              transition_flags1, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Charge air -> ground Action State handler
void ftLuigi_SpecialAirSHold_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_HOLD,
                              transition_flags1, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Charge Action State handler
void ftLuigi_SpecialSHold_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLuigi_SpecialAirSHold_Action.

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_HOLD,
                              FtStateChange_PreserveSfx, NULL, 0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }
}

/// Luigi's aerial Green Missile Charge Action State handler
void ftLuigi_SpecialAirSHold_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_HOLD,
                              FtStateChange_PreserveSfx, NULL, 0, 1, 0);
    {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLuigi_SpecialS_SetGFX;
    }
}

/// Luigi's grounded Green Missile Launch Animation callback
void ftLuigi_SpecialSLaunch_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Shared @c inline with #ftLuigi_SpecialAirSLaunch_Anim.
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->sv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->sv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D5D4(fp);
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Launch Animation callback
void ftLuigi_SpecialAirSLaunch_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->sv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->sv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Launch IASA callback
void ftLuigi_SpecialSLaunch_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Launch IASA callback
void ftLuigi_SpecialAirSLaunch_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's grounded Green Missile Launch Physics callback
void ftLuigi_SpecialSLaunch_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Luigi's aerial Green Missile Launch Physics callback
void ftLuigi_SpecialAirSLaunch_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

/// Luigi's grounded Green Missile Launch Collision callback
void ftLuigi_SpecialSLaunch_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftLuigi_SpecialSLaunch_GroundToAir(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Launch Collision callback
void ftLuigi_SpecialAirSLaunch_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftLuigi_SpecialAirSLaunch_AirToGround(fighter_gobj);
    }
}

/// @todo Combine common flags with #transition_flags0.
static Fighter_ActionStateChangeFlags const transition_flags2 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Launch ground -> air Acion State handler
void ftLuigi_SpecialSLaunch_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_LAUNCH,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Launch air -> ground Action State handler
void ftLuigi_SpecialAirSLaunch_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_LAUNCH,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

static inline void ftLuigi_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007DB24(fighter_gobj);
}

static inline void ftLuigi_SpecialS_Setup(HSD_GObj* fighter_gobj)
{
    /// @todo Use #GET_FIGHTER.
    Fighter* fp = getFighter(fighter_gobj);

    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x50A, fighter_gobj, fp->x5E8_fighterBones[HipN].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Luigi's grounded Green Missile Launch Action State handler
void ftLuigi_SpecialSLaunch_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sv.lg.SpecialS.isMisfire) {
        ftLuigi_SpecialSMisfire_Action(fighter_gobj);
        return;
    }

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_LAUNCH, 0, NULL,
                              0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

/// Luigi's aerial Green Missile Launch Action State handler
void ftLuigi_SpecialAirSLaunch_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sv.lg.SpecialS.isMisfire) {
        ftLuigi_SpecialAirSMisfire_Action(fighter_gobj);
        return;
    }

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_LAUNCH, 0,
                              NULL, 0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

/// Luigi's grounded Green Missile Misfire Animation callback
void ftLuigi_SpecialSMisfire_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->sv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->sv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D5D4(fp);
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Misfire Animation callback
void ftLuigi_SpecialAirSMisfire_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->sv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->sv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftLuigi_SpecialSFly_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Misfire IASA callback
void ftLuigi_SpecialSMisfire_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Misfire IASA callback
void ftLuigi_SpecialAirSMisfire_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's grounded Green Missile Misfire Physics callback
void ftLuigi_SpecialSMisfire_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Luigi's aerial Green Missile Misfire Physics callback
void ftLuigi_SpecialAirSMisfire_Phys(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

/// Luigi's grounded Green Missile Misfire Collision callback
void ftLuigi_SpecialSMisfire_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ftLuigi_SpecialSMisfire_GroundToAir(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile Misfire Collision callback
void ftLuigi_SpecialAirSMisfire_Coll(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ftLuigi_SpecialAirSMisfire_AirToGround(fighter_gobj);
    }
}

/// Luigi's Green Missile Misfire ground -> air Action State handler
void ftLuigi_SpecialSMisfire_GroundToAir(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_MISFIRE,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Misfire air -> ground Action State Handler
void ftLuigi_SpecialAirSMisfire_AirToGround(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_MISFIRE,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Misfire Action State handler
void ftLuigi_SpecialSMisfire_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_MISFIRE, 0, NULL,
                              0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

/// Luigi's aerial Green Missile Misfire Action State handler
void ftLuigi_SpecialAirSMisfire_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_MISFIRE, 0,
                              NULL, 0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(fighter_gobj);
    ftLuigi_SpecialS_Setup(fighter_gobj);
}

/// Luigi's grounded Green Missile Fly Animation callback
void ftLuigi_SpecialSFly_Anim(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Fly Animation callback
void ftLuigi_SpecialAirSFly_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile Fly IASA callback
void ftLuigi_SpecialSFly_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Fly IASA callback
void ftLuigi_SpecialAirSFly_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's grounded Green Missile Fly Physics callback
void ftLuigi_SpecialSFly_Phys(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Fly Physics callback
void ftLuigi_SpecialAirSFly_Phys(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D494(fp, sa->x40_LUIGI_GREENMISSILE_GRAVITY_MUL,
                          sa->x34_LUIGI_GREENMISSILE_GRAVITY_START);
    } else {
        ftCommon_8007D494(fp, sa->x30_LUIGI_GREENMISSILE_MUL_Y,
                          sa->x34_LUIGI_GREENMISSILE_GRAVITY_START);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007CE94(fp, sa->x3C_LUIGI_GREENMISSILE_X_DECEL);
    }
}

/// Luigi's grounded Green Missile Fly Collision callback
void ftLuigi_SpecialSFly_Coll(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile Fly Collision callback
void ftLuigi_SpecialAirSFly_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp0 = GET_FIGHTER(fighter_gobj);
    CollData* coll_data = &fp0->x6F0_collData;

    if (ft_80081D0C(fighter_gobj)) {
        Fighter* fp1 = fp0;
        ftCommon_8007D7FC(fp1);
        ftLuigi_SpecialSEnd_Action(fighter_gobj);
    }

    {
        u32 env_flags = coll_data->x134_envFlags;

        /// @todo Named flags
        if ((env_flags & MPCOLL_RIGHTWALL) || (env_flags & MPCOLL_LEFTWALL)) {
            ftLuigi_SpecialAirSEnd_Action(fighter_gobj);
        }
    }
}

/// @todo Combine common flags with #transition_flags0.
static Fighter_ActionStateChangeFlags const transition_flags3 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Fly Setup
void ftLuigi_SpecialSFly_Action(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp;
    ftLuigiAttributes* sa;

    fp = getFighter(fighter_gobj);
    sa = getFtSpecialAttrsD(fp);
    fp->x2200_ftcmd_var0 = 0;

    if (fp->sv.lg.SpecialS.isMisfire) {
        fp->x80_self_vel.x = sa->x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    } else {
        fp->x80_self_vel.x = sa->x28_LUIGI_GREENMISSILE_MUL_X *
                                 fp->sv.lg.SpecialS.chargeFrames +
                             sa->x24_LUIGI_GREENMISSILE_VEL_X;
    }

    fp->x80_self_vel.x *= fp->facing_dir;

    if (fp->sv.lg.SpecialS.isMisfire) {
        fp->x80_self_vel.y = sa->x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;
    } else {
        f32 vel_y = sa->x2C_LUIGI_GREENMISSILE_VEL_Y;

        fp->x80_self_vel.y =
            0.5f * vel_y +
            vel_y * (0.5f * fp->sv.lg.SpecialS.chargeFrames /
                     sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES);
    }

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_FLY,
                              transition_flags3, NULL,
                              fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21F8_callback = ftCommon_8007F76C;
    fp->cb.x21C0_callback_OnGiveDamage = ftLuigi_SpecialS_OnGiveDamage;
}

/// Luigi's grounded Green Missile End Animation callback
void ftLuigi_SpecialSEnd_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile End Animation callback
void ftLuigi_SpecialAirSEnd_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

/// Luigi's grounded Green Missile End IASA callback
void ftLuigi_SpecialSEnd_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's aerial Green Missile End IASA callback
void ftLuigi_SpecialAirSEnd_IASA(HSD_GObj* fighter_gobj) {}

/// Luigi's grounded Green Missile End Physics callback
void ftLuigi_SpecialSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007C930(fp, sa->x3C_LUIGI_GREENMISSILE_X_DECEL);
    ftCommon_8007CB74(fighter_gobj);
}

/// Luigi's aerial Green Missile End Physics callback
void ftLuigi_SpecialAirSEnd_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007D494(fp, sa->x40_LUIGI_GREENMISSILE_GRAVITY_MUL,
                      fp->x110_attr.x170_TerminalVelocity);
    ftCommon_8007CE94(fp, sa->x3C_LUIGI_GREENMISSILE_X_DECEL);
}

/// Luigi's grounded Green Missile End Collision callback
void ftLuigi_SpecialSEnd_Coll(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

/// Luigi's aerial Green Missile End Collision callback
void ftLuigi_SpecialAirSEnd_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (ft_80081D0C(fighter_gobj)) {
        ftCommon_8007D7FC(fp);
        ftLuigi_SpecialSEnd_Action(fighter_gobj);
    }
}

/// Luigi's Green Missile End air -> ground Action State handler
void ftLuigi_SpecialSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->xEC_ground_vel /= sa->x38_LUIGI_GREENMISSILE_FRICTION_END;
    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALS_END, 0, NULL, 0,
                              1, 0);
}

/// Luigi's Green Missile End ground -> air Action State handler
void ftLuigi_SpecialAirSEnd_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.x /= sa->x38_LUIGI_GREENMISSILE_FRICTION_END;

    Fighter_ChangeMotionState(fighter_gobj, AS_LUIGI_SPECIALAIRS_END, 0, NULL,
                              0, 1, 0);
}
