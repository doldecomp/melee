/**
 * @file ftcaptainspecialhi.c
 * @brief Up Special - Falcon Dive (Captain Falcon) / Dark Dive (Ganondorf)
 * @details Implements grounded and aerial states for Captain Falcon's Up
 * Special command grab, including leap velocity, turnaround steering, grab
 * contact detection, target attachment, explosion throw release, ledge grab
 * mechanics, and post-throw physics recoil. Module prefix: ftCa
 */

#include "ftcaptainspecialhi.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/kinds/ftCommon/ftCo_CaptureCaptain.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/kinds/ftCommon/ftCo_Throw.h>
#include <melee/ft/kinds/ftCommon/ftCo_Thrown.h>
#include <melee/ft/types.h>

/**
 * @brief Collision callback for Falcon Kick Wall Rebound (SpecialHiThrow1).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow1_Coll(HSD_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

/**
 * @brief Initialization helper invoked upon entering Falcon Dive (SpecialHi).
 * @details Consumes all remaining midair double-jumps, resets velocity and
 * flags, and initializes command variables.
 * @param gobj Pointer to Fighter GObj
 */
static void ftCa_SpecialLw_800E49FC(HSD_GObj* gobj)
{
    u8 _[16];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->mv.ca.specialhi.x0 = da->specialhi_air_var;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = da->specialhi_unk2;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.x2_b1 = false;
}

static void ftCa_SpecialLw_800E5128(HSD_GObj*);

/**
 * @brief Grounded Up-B (Falcon Dive) entry.
 * @details Enters ftCa_MS_SpecialHi, sets up catch callbacks for command grab,
 * and plays animation.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x21EC = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHi, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ftCo_8009CA0C);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Grounded Up-B (Falcon Dive) animation callback.
 * @details Upon animation end, transitions to freefall (FallSpecial) with
 * specialhi_freefall_air_spd_mul air speed and specialhi_landing_lag frames of
 * landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 1, false, da->specialhi_freefall_air_spd_mul,
                      da->specialhi_landing_lag);
    }
}

/**
 * @brief Grounded Up-B (Falcon Dive) IASA callback.
 * @details Checks analog stick X during startup window to reverse facing
 * direction and model Y rotation if stick magnitude exceeds
 * specialhi_input_var.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        fp->cmd_vars[0] = 0;
        fp->mv.ca.specialhi.x2_b1 = true;
        {
            float lstick_x = fp->input.lstick[0].x;
            if (lstick_x < 0) {
                lstick_x = -lstick_x;
            }
            if (lstick_x > da->specialhi_input_var) {
                ftCommon_UpdateFacing(fp);
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

/**
 * @brief Grounded Up-B (Falcon Dive) physics callback.
 * @details Calculates horizontal air drift and acceleration during the upward
 * leap using specialhi_horz_vel and specialhi_air_friction_mul.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    fp->self_vel.x = fp->mv.ca.specialhi.vel.x;
    fp->self_vel.y = fp->mv.ca.specialhi.vel.y;
    fp->self_vel.z = 0;
    if (!ftCommon_CalcSelfAccel_DeaccelQuick(fp, da->specialhi_horz_vel *
                                                     ca->air_drift_max))
    {
        ftCommon_CalcSelfAccel_DriftSimple_NoFriction(
            fp, p_ftCommonData->x258,
            ca->air_drift_stick_mul * da->specialhi_air_friction_mul,
            ca->air_drift_max * da->specialhi_horz_vel);
    }
    fp->mv.ca.specialhi.vel.x = fp->x74_self_accel.x + fp->self_vel.x;
    fp->mv.ca.specialhi.vel.y = fp->x74_self_accel.y + fp->self_vel.y;
    ft_80085134(gobj);
    fp->x74_self_accel.x = fp->x74_self_accel.y = 0;
    fp->self_vel.x = fp->self_vel.x + fp->mv.ca.specialhi.vel.x;
    fp->self_vel.y = fp->self_vel.y + fp->mv.ca.specialhi.vel.y;
}

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) entry.
 * @details Enters ftCa_MS_SpecialAirHi, initializes jump consumption and grab
 * callbacks.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x21EC = ftCa_SpecialLw_800E49FC;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirHi, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2D0(fp, 2, ftCa_SpecialLw_800E5128, NULL, ftCo_8009CA0C);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Handles aerial collision, ground landing, and ledge grab for Falcon
 * Dive.
 * @details If landing on ground after turnaround window has passed (x2_b1),
 * enters LandingFallSpecial with specialhi_landing_lag frames of lag. If near
 * a ledge, triggers cliff catch (ledge grab).
 * @param gobj Pointer to Fighter GObj
 */
static void doAirColl(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        if (fp->mv.ca.specialhi.x2_b1) {
            ftCo_LandingFallSpecial_Enter(gobj, false,
                                          da->specialhi_landing_lag);
        } else {
            ft_80083B68(gobj);
        }
    } else if (fp->mv.ca.specialhi.x2_b1 && ftCliffCommon_80081298(gobj)) {
        ftCliffCommon_80081370(gobj);
    }
}

/**
 * @brief Grounded Up-B (Falcon Dive) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_Coll(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        doAirColl(gobj);
    } else if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
    }
}

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) animation callback.
 * @details On animation completion, transitions to freefall (FallSpecial)
 * with specialhi_landing_lag frames of landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    u8 _[24];
    ftCaptain_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 1, false, da->specialhi_freefall_air_spd_mul,
                      da->specialhi_landing_lag);
    }
}

/**
 * @brief Helper for aerial Up-B turnaround control stick input check.
 * @param gobj Pointer to Fighter GObj
 */
static void doAirIASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    fp->mv.ca.specialhi.x2_b1 = true;
    {
        float lstick_x = fp->input.lstick[0].x;
        if (lstick_x < 0) {
            lstick_x = -lstick_x;
        }
        if (lstick_x > da->specialhi_input_var) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
        }
    }
}

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) IASA callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        doAirIASA(gobj);
    }
}

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    PAD_STACK(28);
    ftCa_SpecialHi_Phys(gobj);
}

/**
 * @brief Aerial Up-B (Aerial Falcon Dive) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    ftCa_SpecialHi_Coll(gobj);
}

static void ftCa_SpecialLw_800E550C(HSD_GObj*);

/**
 * @brief Up-B Command Grab Hit Callback (Falcon Dive Catch).
 * @details Invoked when Falcon Dive hitbox contacts an opponent. Transitions
 * to ftCa_MS_SpecialHiCatch, grants intangibility, and syncs victim position.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLw_800E5128(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->victim_gobj);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiCatch, Ft_MF_KeepGfx, 0,
                              1, 0, NULL);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    if (vic_fp->ground_or_air == GA_Air) {
        fp->x221B.x221B_b7 = false;
    } else {
        ftCo_800DB368(vic_fp, fp);
        fp->x221B.x221B_b7 = true;
        fp->accessory4_cb = ftCa_SpecialLw_800E550C;
    }
}

static void doCatchAnim(HSD_GObj* gobj);

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) animation callback.
 * @details When grab contact animation finishes, transitions to throw release.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiCatch_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doCatchAnim(gobj);
    }
}

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiCatch_IASA(HSD_GObj* gobj) {}

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) physics callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiCatch_Phys(HSD_GObj* gobj) {}

/**
 * @brief Up-B Grab Contact (Falcon Dive Catch) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiCatch_Coll(HSD_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x221B.x221B_b7) {
        ft_80083B68(gobj);
    }
}

/**
 * @brief Transitions from Falcon Dive grab contact into the explosion throw.
 * @details Enters ftCa_MS_SpecialHiThrow and triggers thrown damage/knockback
 * on victim.
 * @param gobj Pointer to Fighter GObj
 */
static void doCatchAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* vic_gobj = fp->victim_gobj;
    fp->cmd_vars[0] = 0;
    fp->mv.ca.specialhi.x2_b0 = false;
    fp->mv.ca.specialhi.vel.x = 0;
    fp->mv.ca.specialhi.vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow,
                              Ft_MF_Unk19 | Ft_MF_KeepGfx, 0, 1, 0, NULL);
    ftCommon_8007E2F4(fp, 0);
    ftCo_800DE2A8(gobj, vic_gobj);
    ftCo_800DE7C0(vic_gobj, 0, 0);
}

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) animation callback.
 * @details On animation completion, transitions to Fall.
 * When cmd_vars[0] != 0 (recoil frame trigger), enables post-explosion gravity
 * physics.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow0_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
    ftCommon_8007D60C(fp);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        fp->mv.ca.specialhi.x2_b0 = true;
    }
}

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow0_IASA(HSD_GObj* gobj) {}

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) physics callback.
 * @details After explosion release (x2_b0 == true), applies
 * specialhi_catch_grav downward gravity acceleration clamped to terminal
 * velocity.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca;
    PAD_STACK(32);
    if (fp->mv.ca.specialhi.x2_b0) {
        ftCa_SpecialHi_Phys(gobj);
        ca = &fp->co_attrs;
        {
            float vel_y = fp->self_vel.y - fp->mv.ca.specialhi.vel.y;
            ftCommon_Fall(fp, da->specialhi_catch_grav, ca->terminal_velocity);
            fp->mv.ca.specialhi.vel.y = fp->self_vel.y - vel_y;
        }
    } else {
        ft_80085134(gobj);
    }
}

/**
 * @brief Up-B Explosion Throw (Falcon Dive Release) collision callback.
 * @details If touching ground during throw recovery, enters LandingFallSpecial
 * with specialhi_landing_lag frames of landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj)) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->specialhi_landing_lag);
    }
}

/**
 * @brief Accessory callback synchronizing Captain Falcon's position to victim
 * during catch.
 * @param gobj Pointer to Fighter GObj
 */
static void ftCa_SpecialLw_800E550C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* vic_fp = GET_FIGHTER(fp->victim_gobj);
    fp->cur_pos = vic_fp->cur_pos;
}
