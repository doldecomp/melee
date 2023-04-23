#include "forward.h"
#include "lb/forward.h"

#include "ftLg_SpecialS.h"

#include "ftLg_Init.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

#include <baselib/gobjproc.h>

/// Luigi's Green Missile GFX callback
void ftLg_SpecialS_SetGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_flag.bits.b0) {
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

/// Luigi's Green Missile Setup (RNG + calculations)
void ftLg_SpecialS_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrs(fp);

    fp->x2200_ftcmd_var0 = 0;

    if (fp->x673 < sa->x4_LUIGI_GREENMISSILE_SMASH) {
        fp->mv.lg.SpecialS.chargeFrames =
            sa->x8_LUIGI_GREENMISSILE_CHARGE_RATE;
        fp->x2070.x2072_b4 = true;
    } else {
        fp->mv.lg.SpecialS.chargeFrames = 0;
    }

    if (HSD_Randi(sa->x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE) == 0) {
        fp->mv.lg.SpecialS.isMisfire = true;
    } else {
        fp->mv.lg.SpecialS.isMisfire = false;
    }
}

/// Luigi's grounded Green Missile Motion State handler
void ftLg_SpecialS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLg_SpecialAirS_Enter.
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftLg_SpecialS_SetVars;
    fp->gr_vel /= sa->x18_LUIGI_GREENMISSILE_TRACTION;

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSStart, 0, NULL, 0, 1, 0);

    ftAnim_8006EBA4(gobj);
}

/// Luigi's aerial Green Missile Motion State handler
void ftLg_SpecialAirS_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftLg_SpecialS_SetVars;
    fp->x80_self_vel.x /= sa->x18_LUIGI_GREENMISSILE_TRACTION;
    fp->x80_self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSStart, 0, NULL, 0, 1,
                              0);

    ftAnim_8006EBA4(gobj);
}

/// Luigi's Green Missile OnGiveDamage callback
void ftLg_SpecialS_OnGiveDamage(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->x80_self_vel.x = 0;

    if (fp->x80_self_vel.y >= 0) {
        fp->x80_self_vel.y = 0;
    }

    ftLg_SpecialAirSEnd_Enter(gobj);
}

/// Luigi's grounded Green Missile Start Animation callback
void ftLg_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLg_SpecialSHold_Enter(gobj);
    }
}

/// Luigi's aerial Green Missile Start Animation callback
void ftLg_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLg_SpecialAirSHold_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Start IASA callback
void ftLg_SpecialSStart_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Start IASA callback
void ftLg_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

/// Luigi's grounded Green Missile Start Physics callback
void ftLg_SpecialSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007C930(fp, sa->x1C_LUIGI_GREENMISSILE_UNK2);
    ftCommon_8007CB74(gobj);
}

/// Luigi's aerial Green Missile Start Physics callback
void ftLg_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D494(fp, sa->x20_LUIGI_GREENMISSILE_FALLING_SPEED,
                          attr->x170_TerminalVelocity);
    }

    ftCommon_8007CE94(fp, sa->x1C_LUIGI_GREENMISSILE_UNK2);
}

/// Luigi's grounded Green Missile Start Collision callback
void ftLg_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftLg_SpecialSStart_GroundToAir(gobj);
    }
}

/// Luigi's aerial Green Missile Start Collision callback
void ftLg_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftLg_SpecialAirSStart_AirToGround(gobj);
    }
}

static u32 const transition_flags0 =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_PreserveSfx | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Start ground -> air Motion State handler
void ftLg_SpecialSStart_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSStart,
                              transition_flags0, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Start air -> ground Motion State handler
void ftLg_SpecialAirSStart_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSStart, transition_flags0,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Charge Animation callback
void ftLg_SpecialSHold_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLg_SpecialAirSHold_Anim.
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLg_SpecialS_SetGFX;
    }

    fp->mv.lg.SpecialS.chargeFrames++;

    if (fp->mv.lg.SpecialS.chargeFrames >
        sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLg_SpecialSLaunch_Enter(gobj);
    }
}

/// Luigi's aerial Green Missile Charge Animation callback
void ftLg_SpecialAirSHold_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLg_SpecialS_SetGFX;
    }

    fp->mv.lg.SpecialS.chargeFrames++;

    if (fp->mv.lg.SpecialS.chargeFrames >
        sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES)
    {
        ftLg_SpecialAirSLaunch_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Charge IASA callback
void ftLg_SpecialSHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        ftLg_SpecialSLaunch_Enter(gobj);
    }
}

/// Luigi's aerial Green Missile Charge IASA callback
void ftLg_SpecialAirSHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B)) {
        ftLg_SpecialAirSLaunch_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Charge Physics callback
void ftLg_SpecialSHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Luigi's aerial Green Missile Charge Physics callback
void ftLg_SpecialAirSHold_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// Luigi's grounded Green Missile Charge Collision callback
void ftLg_SpecialSHold_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftLg_SpecialSHold_GroundToAir(gobj);
    }
}

/// Luigi's aerial Green Missile Charge Collision callback
void ftLg_SpecialAirSHold_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftLg_SpecialAirSHold_AirToGround(gobj);
    }
}

static u32 const transition_flags1 =
    transition_flags0 | FtStateChange_PreserveGfx;

/// Luigi's Green Missile Charge ground -> air Acion State handler
void ftLg_SpecialSHold_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSHold, transition_flags1,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Charge air -> ground Motion State handler
void ftLg_SpecialAirSHold_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSHold, transition_flags1,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Charge Motion State handler
void ftLg_SpecialSHold_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    /// @todo Shared @c inline with #ftLg_SpecialAirSHold_Enter.

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSHold,
                              FtStateChange_PreserveSfx, NULL, 0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLg_SpecialS_SetGFX;
    }
}

/// Luigi's aerial Green Missile Charge Motion State handler
void ftLg_SpecialAirSHold_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSHold,
                              FtStateChange_PreserveSfx, NULL, 0, 1, 0);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftLg_SpecialS_SetGFX;
    }
}

/// Luigi's grounded Green Missile Launch Animation callback
void ftLg_SpecialSLaunch_Anim(HSD_GObj* gobj)
{
    /// @todo Shared @c inline with #ftLg_SpecialAirSLaunch_Anim.
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->mv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D5D4(fp);
        ftLg_SpecialSFly_Enter(gobj);
    }
}

/// Luigi's aerial Green Missile Launch Animation callback
void ftLg_SpecialAirSLaunch_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->mv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftLg_SpecialSFly_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Launch IASA callback
void ftLg_SpecialSLaunch_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Launch IASA callback
void ftLg_SpecialAirSLaunch_IASA(HSD_GObj* gobj) {}

/// Luigi's grounded Green Missile Launch Physics callback
void ftLg_SpecialSLaunch_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Luigi's aerial Green Missile Launch Physics callback
void ftLg_SpecialAirSLaunch_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// Luigi's grounded Green Missile Launch Collision callback
void ftLg_SpecialSLaunch_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftLg_SpecialSLaunch_GroundToAir(gobj);
    }
}

/// Luigi's aerial Green Missile Launch Collision callback
void ftLg_SpecialAirSLaunch_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftLg_SpecialAirSLaunch_AirToGround(gobj);
    }
}

/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags2 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Launch ground -> air Acion State handler
void ftLg_SpecialSLaunch_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSLaunch,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Launch air -> ground Motion State handler
void ftLg_SpecialAirSLaunch_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSLaunch, transition_flags2,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

static inline void ftLuigi_SpecialS_RemoveGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007DB24(gobj);
}

static inline void ftLuigi_SpecialS_Setup(HSD_GObj* gobj)
{
    /// @todo Use #GET_FIGHTER.
    Fighter* fp = getFighter(gobj);

    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x50A, gobj, fp->parts[FtPart_HipN].x0_jobj);
        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

/// Luigi's grounded Green Missile Launch Motion State handler
void ftLg_SpecialSLaunch_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.lg.SpecialS.isMisfire) {
        ftLg_SpecialSMisfire_Enter(gobj);
        return;
    }

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSLaunch, 0, NULL, 0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(gobj);
    ftLuigi_SpecialS_Setup(gobj);
}

/// Luigi's aerial Green Missile Launch Motion State handler
void ftLg_SpecialAirSLaunch_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.lg.SpecialS.isMisfire) {
        ftLg_SpecialAirSMisfire_Enter(gobj);
        return;
    }

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSLaunch, 0, NULL, 0, 1,
                              0);

    ftLuigi_SpecialS_RemoveGFX(gobj);
    ftLuigi_SpecialS_Setup(gobj);
}

/// Luigi's grounded Green Missile Misfire Animation callback
void ftLg_SpecialSMisfire_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->mv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCommon_8007D5D4(fp);
        ftLg_SpecialSFly_Enter(gobj);
    }
}

/// Luigi's aerial Green Missile Misfire Animation callback
void ftLg_SpecialAirSMisfire_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    if (!fp->mv.lg.SpecialS.isMisfire &&
        fp->x914[0].state == HitCapsule_Enabled)
    {
        ftColl_8007ABD0(&fp->x914[0],
                        fp->mv.lg.SpecialS.chargeFrames *
                                sa->x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE +
                            sa->x10_LUIGI_GREENMISSILE_DAMAGE_TILT,
                        gobj);
    }

    if (fp->x2200_ftcmd_var0 != 0) {
        ftLg_SpecialSFly_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Misfire IASA callback
void ftLg_SpecialSMisfire_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Misfire IASA callback
void ftLg_SpecialAirSMisfire_IASA(HSD_GObj* gobj) {}

/// Luigi's grounded Green Missile Misfire Physics callback
void ftLg_SpecialSMisfire_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Luigi's aerial Green Missile Misfire Physics callback
void ftLg_SpecialAirSMisfire_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Luigi's grounded Green Missile Misfire Collision callback
void ftLg_SpecialSMisfire_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftLg_SpecialSMisfire_GroundToAir(gobj);
    }
}

/// Luigi's aerial Green Missile Misfire Collision callback
void ftLg_SpecialAirSMisfire_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftLg_SpecialAirSMisfire_AirToGround(gobj);
    }
}

/// Luigi's Green Missile Misfire ground -> air Motion State handler
void ftLg_SpecialSMisfire_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSMisfire,
                              transition_flags2, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's Green Missile Misfire air -> ground Motion State Handler
void ftLg_SpecialAirSMisfire_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSMisfire, transition_flags2,
                              NULL, fp->x894_currentAnimFrame, 1, 0);
}

/// Luigi's grounded Green Missile Misfire Motion State handler
void ftLg_SpecialSMisfire_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSMisfire, 0, NULL, 0, 1, 0);

    ftLuigi_SpecialS_RemoveGFX(gobj);
    ftLuigi_SpecialS_Setup(gobj);
}

/// Luigi's aerial Green Missile Misfire Motion State handler
void ftLg_SpecialAirSMisfire_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSMisfire, 0, NULL, 0, 1,
                              0);

    ftLuigi_SpecialS_RemoveGFX(gobj);
    ftLuigi_SpecialS_Setup(gobj);
}

/// Luigi's grounded Green Missile Fly Animation callback
void ftLg_SpecialSFly_Anim(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Fly Animation callback
void ftLg_SpecialAirSFly_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLg_SpecialAirSEnd_Enter(gobj);
    }
}

/// Luigi's grounded Green Missile Fly IASA callback
void ftLg_SpecialSFly_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Fly IASA callback
void ftLg_SpecialAirSFly_IASA(HSD_GObj* gobj) {}

/// Luigi's grounded Green Missile Fly Physics callback
void ftLg_SpecialSFly_Phys(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Fly Physics callback
void ftLg_SpecialAirSFly_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(gobj);
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
void ftLg_SpecialSFly_Coll(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile Fly Collision callback
void ftLg_SpecialAirSFly_Coll(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    CollData* coll_data = &fp0->x6F0_collData;

    if (ft_80081D0C(gobj)) {
        Fighter* fp1 = fp0;
        ftCommon_8007D7FC(fp1);
        ftLg_SpecialSEnd_Enter(gobj);
    }

    {
        u32 env_flags = coll_data->x134_envFlags;

        /// @todo Named flags
        if ((env_flags & MPCOLL_RIGHTWALL) || (env_flags & MPCOLL_LEFTWALL)) {
            ftLg_SpecialAirSEnd_Enter(gobj);
        }
    }
}

/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags3 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

/// Luigi's Green Missile Fly Setup
void ftLg_SpecialSFly_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp;
    ftLuigiAttributes* sa;

    fp = getFighter(gobj);
    sa = getFtSpecialAttrsD(fp);
    fp->x2200_ftcmd_var0 = 0;

    if (fp->mv.lg.SpecialS.isMisfire) {
        fp->x80_self_vel.x = sa->x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    } else {
        fp->x80_self_vel.x = sa->x28_LUIGI_GREENMISSILE_MUL_X *
                                 fp->mv.lg.SpecialS.chargeFrames +
                             sa->x24_LUIGI_GREENMISSILE_VEL_X;
    }

    fp->x80_self_vel.x *= fp->facing_dir;

    if (fp->mv.lg.SpecialS.isMisfire) {
        fp->x80_self_vel.y = sa->x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;
    } else {
        f32 vel_y = sa->x2C_LUIGI_GREENMISSILE_VEL_Y;

        fp->x80_self_vel.y =
            0.5f * vel_y +
            vel_y * (0.5f * fp->mv.lg.SpecialS.chargeFrames /
                     sa->xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES);
    }

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSFly, transition_flags3,
                              NULL, fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21F8_callback = ftCommon_8007F76C;
    fp->cb.x21C0_callback_OnGiveDamage = ftLg_SpecialS_OnGiveDamage;
}

/// Luigi's grounded Green Missile End Animation callback
void ftLg_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Luigi's aerial Green Missile End Animation callback
void ftLg_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

/// Luigi's grounded Green Missile End IASA callback
void ftLg_SpecialSEnd_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Green Missile End IASA callback
void ftLg_SpecialAirSEnd_IASA(HSD_GObj* gobj) {}

/// Luigi's grounded Green Missile End Physics callback
void ftLg_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007C930(fp, sa->x3C_LUIGI_GREENMISSILE_X_DECEL);
    ftCommon_8007CB74(gobj);
}

/// Luigi's aerial Green Missile End Physics callback
void ftLg_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007D494(fp, sa->x40_LUIGI_GREENMISSILE_GRAVITY_MUL,
                      fp->x110_attr.x170_TerminalVelocity);
    ftCommon_8007CE94(fp, sa->x3C_LUIGI_GREENMISSILE_X_DECEL);
}

/// Luigi's grounded Green Missile End Collision callback
void ftLg_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

/// Luigi's aerial Green Missile End Collision callback
void ftLg_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        ftLg_SpecialSEnd_Enter(gobj);
    }
}

/// Luigi's Green Missile End air -> ground Motion State handler
void ftLg_SpecialSEnd_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->gr_vel /= sa->x38_LUIGI_GREENMISSILE_FRICTION_END;
    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialSEnd, 0, NULL, 0, 1, 0);
}

/// Luigi's Green Missile End ground -> air Motion State handler
void ftLg_SpecialAirSEnd_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.x /= sa->x38_LUIGI_GREENMISSILE_FRICTION_END;

    Fighter_ChangeMotionState(gobj, ftLg_MS_SpecialAirSEnd, 0, NULL, 0, 1, 0);
}
