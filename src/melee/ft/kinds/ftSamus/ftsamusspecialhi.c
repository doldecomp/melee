/**
 * @file ftsamusspecialhi.c
 * @brief Up-B: Screw Attack implementation for Samus
 * @details Implements Samus's Up-B special move (Screw Attack), including
 * multi-hit rising mechanics, B-reverse / turnaround on startup, aerial drift
 * acceleration, ledge grab, and helpless (FallSpecial) landing lag transition.
 * Module prefix: ftSs
 */

#include "ftsamusspecialhi.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/types.h>

/**
 * @brief Up-B (Screw Attack): Grounded action state entry callback.
 * @details Changes state to ftSs_MS_SpecialHi (353), resets turnaround flag,
 * and spawns the Screw Attack lightning/energy aura effect (ID 1154).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    Fighter_ChangeMotionState(gobj, 353, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftSamus_updateDamageDeathCBs(gobj);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftCommon_8007D7FC(fp);
    Fighter_ClearCmdVars(fp);
    fp->mv.ss.specialhi.x0 = 0; // Clear turnaround flag
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1154, gobj, fp->parts[FtPart_YRotN].joint);
    fp->u.ss.x2244 = 1;
}

/**
 * @brief Up-B (Screw Attack): Aerial action state entry callback.
 * @details Changes state to ftSs_MS_SpecialAirHi (354), sets initial vertical
 * velocity, clamps horizontal velocity, and spawns the Screw Attack aura
 * effect (ID 1154).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, 354, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftSamus_updateDamageDeathCBs(gobj);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftCommon_8007D60C(fp);
    Fighter_ClearCmdVars(fp);
    fp->mv.ss.specialhi.x0 = 0; // Clear turnaround flag
    fp->self_vel.y =
        samus_attr->x44; // Initial aerial vertical launch velocity
    ftCommon_ClampSelfVelX(fp, samus_attr->x40); // Clamp horizontal speed
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1154, gobj, fp->parts[FtPart_YRotN].joint);
    fp->u.ss.x2244 = 1;
}

/**
 * @brief Cleans up Screw Attack visual effects and resets the active effect
 * flag.
 * @param gobj Samus fighter game object pointer
 */
static void ftSamus_DestroyAllUnsetx2444(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->u.ss.x2244 = 0;
}

/**
 * @brief Up-B (Screw Attack): Grounded animation callback.
 * @details When animation concludes, cleans up aura effect and transitions to
 * FallSpecial (freefall).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    samus_attr = samus_attr2 = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(gobj);
        ftCommon_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        // Transition to helpless / FallSpecial state with freefall drift clamp
        // and landing lag
        ftCo_80096900(gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

/**
 * @brief Up-B (Screw Attack): Aerial animation callback.
 * @details When animation concludes, cleans up aura effect and transitions to
 * FallSpecial (freefall).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    samus_attr = samus_attr2 = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(gobj);
        ftCommon_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        // Transition to helpless / FallSpecial state with freefall drift clamp
        // and landing lag
        ftCo_80096900(gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

/**
 * @brief Up-B (Screw Attack): Grounded IASA callback.
 * @details Handles B-reverse / turnaround on startup if stick X opposes facing
 * direction and exceeds the turnaround stick threshold (samus_attr->x4C).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialHi_IASA(HSD_GObj* gobj)
{
    float mag;
    float lstick_x;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    if ((!fp->cmd_vars[1]) && (!fp->mv.ss.specialhi.x0)) {
        if ((lstick_x = fp->input.lstick[0].x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        // Check if stick displacement exceeds turnaround sensitivity threshold
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->cmd_vars[1] = 1;
                fp->mv.ss.specialhi.x0 = 1;
                ftCommon_UpdateFacing(fp);
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

/**
 * @brief Up-B (Screw Attack): Aerial IASA callback.
 * @details Handles aerial B-reverse / turnaround on startup if stick X opposes
 * facing direction and exceeds the turnaround stick threshold
 * (samus_attr->x4C).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    float mag;
    float lstick_x;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if ((!fp->cmd_vars[1]) && (!fp->mv.ss.specialhi.x0)) {
        if ((lstick_x = fp->input.lstick[0].x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        // Check if stick displacement exceeds turnaround sensitivity threshold
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->cmd_vars[1] = 1;
                fp->mv.ss.specialhi.x0 = 1;
                ftCommon_UpdateFacing(fp);
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

/**
 * @brief Up-B (Screw Attack): Grounded physics callback.
 * @details When animation sets cmd_vars[0], launches Samus airborne with
 * forward velocity (samus_attr->x38), then applies aerial drift acceleration
 * (x3C) and clamp (x40).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);

    // Check if takeoff frame reached
    if (fp->cmd_vars[0]) {
        ftCommon_8007D60C(fp);
        fp->cmd_vars[0] = 0;
        fp->self_vel.x = samus_attr->x38 *
                         fp->facing_dir; // Grounded launch velocity forward
    }
    if (fp->ground_or_air == 1) {
        ft_800851C0(gobj);
        // Apply aerial drift acceleration (x3C) up to maximum speed (x40)
        ftCommon_CalcSelfAccel_DriftSimple(fp, 0.0f, samus_attr->x3C,
                                           samus_attr->x40);
        ftCommon_CalcSelfAccel_Drift(fp);
        return;
    }
    ft_80084F3C(gobj);
}

/**
 * @brief Up-B (Screw Attack): Aerial physics callback.
 * @details Applies upward acceleration/gravity and aerial drift acceleration
 * (x3C) up to max speed (x40).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    ft_80084DB0(gobj);
    ftCommon_CalcSelfAccel_DriftSimple(fp, 0.0f, samus_attr->x3C,
                                       samus_attr->x40);
}

/**
 * @brief Up-B (Screw Attack): Grounded collision callback.
 * @details In air: checks ceiling collision on ascent, ground landing into
 * FallSpecial landing lag (samus_attr->x50) on descent, or ledge grab.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->ground_or_air == GA_Air) {
        int direction;

        // Ascending: test environment collision
        if (fp->self_vel.y >= 0.0f) {
            ft_80081D0C(gobj);
            return;
        }
        // Descending: check landing and ledge grab
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCo_LandingFallSpecial_Enter(gobj, false, samus_attr->x50);
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCliffCommon_80081370(gobj);
        }
    } else {
        ft_80084104(gobj);
    }
}

/**
 * @brief Up-B (Screw Attack): Aerial collision callback.
 * @details In air: checks ceiling collision on ascent, ground landing into
 * FallSpecial landing lag (samus_attr->x50) on descent, or ledge grab.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    if (fp->ground_or_air == GA_Air) {
        int direction;

        // Ascending: test environment collision
        if (fp->self_vel.y >= 0.0f) {
            ft_80081D0C(gobj);
            return;
        }
        // Descending: check landing and ledge grab
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (ft_CheckGroundAndLedge(gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCo_LandingFallSpecial_Enter(gobj, false, samus_attr->x50);
            return;
        }
        if (ftCliffCommon_80081298(gobj)) {
            ftSamus_DestroyAllUnsetx2444(gobj);
            ftCliffCommon_80081370(gobj);
        }
    } else {
        ft_80084104(gobj);
    }
}
