/**
 * @file ftfoxspecialhi.c
 * @brief Up-B (Fire Fox / Falco Firebird)
 * @details Implements Fox and Falco's Up-B recovery move. Handles the grounded
 * and aerial charging/aiming phase, launch trajectory physics, model rotation,
 * collision detection against terrain (including wall/ceiling bonk bounces),
 * and transitions into landing lag or special fall (freefall).
 * Module prefix: ftFx
 */

#include "ftfoxspecialhi.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include <math.h>

#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Pass.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/lb/lbvector.h>

/// Motion flags for Fire Fox collision state changes
#define FTFOX_SPECIALHI_COLL_FLAG                                             \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd | Ft_MF_SkipColAnim | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

/// Half Pi constant for default upward launch angle (90 degrees in radians)
#define HALF_PI32 (1.5707963705062866f)

/// Two Pi constant for full rotation
#define DOUBLE_PI32 (6.2831854820251465f)

/**
 * @brief Up-B (Fire Fox) - Spawns launch flame trail particle effects
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_CreateLaunchGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        efSync_Spawn(1164, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint);

        fp->x2219_b0 = true;
    }

    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = NULL;
}

/**
 * @brief Up-B (Fire Fox) - Spawns charging flame aura particle effects
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_CreateChargeGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        efSync_Spawn(1163, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint);

        fp->x2219_b0 = true;
    }

    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = NULL;
}

/**
 * @brief Action State initialization for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp;
    ftFox_DatAttrs* da;

    fp = GET_FIGHTER(gobj);
    da = getFtSpecialAttrs(fp);

    // Initialize gravity delay and initial velocity dampening
    fp->mv.fx.SpecialHi.gravityDelay = da->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->gr_vel /= da->x58_FOX_FIREFOX_VEL_X;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHold, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

/**
 * @brief Action State initialization for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHiStart_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.gravityDelay = da->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->self_vel.x /= da->x58_FOX_FIREFOX_VEL_X;
    fp->self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHoldAir, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

/**
 * @brief Up-B (Fire Fox) - Rotates the fighter's model to align with launch
 * angle
 * @param gobj The fighter's game object
 */
static void ftFox_SpecialHi_RotateModel(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN),
                  (2 * (float) M_PI) - fp->mv.fx.SpecialHi.rotateModel);
}

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirHi_Enter(gobj);
            return;
        }

        ftFx_SpecialAirHi_AirToGround(gobj);
    }
}

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHoldAir_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirHi_Enter(gobj);
            return;
        }
        ftFx_SpecialAirHi_AirToGround(gobj);
    }
}

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) charge (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) charge (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHoldAir_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) charge
 * @details Freezes vertical movement during gravity delay; falls and applies
 * air drag after.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHoldAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;

    u8 _[8];

    if (fp->mv.fx.SpecialHi.gravityDelay != 0) {
        fp->mv.fx.SpecialHi.gravityDelay -= 1;
    } else {
        ftCommon_Fall(fp, da->x60_FOX_FIREFOX_FALL_ACCEL,
                      ca->terminal_velocity);
    }

    ftCommon_CalcSelfAccel_Deaccel(
        fp, da->x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X);
}

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHold_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialHiHold_GroundToAir(gobj);
    }
}

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHoldAir_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftFx_SpecialHiHoldAir_AirToGround(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Ground to air transition during Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHold_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHoldAir,
                              FTFOX_SPECIALHI_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

/**
 * @brief Air to ground transition during Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiHoldAir_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_AirToGroundStateChange(gobj, fp, ftFx_MS_SpecialHiHold,
                                    FTFOX_SPECIALHI_COLL_FLAG);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;

    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) launch travel
 * @details Decrements travel frames (typically 42). Transitions to
 * landing/fall on finish.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Common inline with #ftFx_SpecialAirHi_Anim.
    fp->mv.fx.SpecialHi.travelFrames--;

    if (fp->mv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFx_SpecialHiFall_AirToGround(gobj);
    }
}

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.SpecialHi.travelFrames--;

    if (fp->mv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFx_SpecialHiFall_AirToGround(gobj);
    }
}

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) launch (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) launch (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) launch travel
 * @details Applies reverse ground acceleration after duration threshold.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Possibly common inline with #ftFx_SpecialAirHi_Phys.
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.unk++;

    if (fp->mv.fx.SpecialHi.unk >= da->x70_FOX_FIREFOX_DURATION_END) {
        ftCommon_CalcGroundAccel_Deaccel(fp,
                                         da->x78_FOX_FIREFOX_REVERSE_ACCEL);
    }

    ftCommon_SetSelfMovementFromGroundedMovement(gobj);
}

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) launch travel
 * @details Applies reverse acceleration along launch vector near the end of
 * the move.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.unk++;

    if (fp->mv.fx.SpecialHi.unk >= da->x70_FOX_FIREFOX_DURATION_END) {
        fp->self_vel.x =
            -((fp->facing_dir * (da->x78_FOX_FIREFOX_REVERSE_ACCEL *
                                 cosf(fp->mv.fx.SpecialHi.rotateModel))) -
              fp->self_vel.x);
        fp->self_vel.y = -((da->x78_FOX_FIREFOX_REVERSE_ACCEL *
                            sinf(fp->mv.fx.SpecialHi.rotateModel)) -
                           fp->self_vel.y);
    }
}

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->coll_data;

    fp->mv.fx.SpecialHi.unk2 += 1;

    if (ft_80082708(gobj) == false) {
        ftFx_SpecialHi_GroundToAir(gobj);
        return;
    }

    if (collData->env_flags & Collide_FloorMask) {
        fp->mv.fx.SpecialHi.rotateModel =
            atan2f(-collData->floor.normal.x * fp->facing_dir,
                   collData->floor.normal.y);
        ftFox_SpecialHi_RotateModel(gobj);
    }
}

/**
 * @brief Checks if Fire Fox launch bounce threshold has been met
 * @param gobj The fighter's game object
 * @return True if bounce should occur, false otherwise
 */
static inline bool ftFox_SpecialHi_IsBound(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (fp->mv.fx.SpecialHi.unk2 >= da->x6C_FOX_FIREFOX_BOUNCE_VAR) {
        return true;
    } else if (ftCo_8009A134(gobj)) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) launch travel
 * @details Evaluates collision with floors, ceilings, and walls. If angle of
 * incidence with surface normal exceeds threshold, enters wall bonk rebound
 * (SpecialHiBound).
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    float facingDir;

    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = da = getFtSpecialAttrs(fp);
    CollData* collData = collData = getFtColl(fp);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH)) {
        if (ftFox_SpecialHi_IsBound(gobj)) {
            // Check floor collision angle against bounce threshold
            if (!(collData->env_flags & Collide_FloorMask) ||
                (!(lbVector_AngleXY(&collData->floor.normal, &fp->self_vel) <
                   (0.01745329238474369f *
                    (90.0f + da->x94_FOX_FIREFOX_BOUND_ANGLE)))))
            {
                ftFx_SpecialHiBound_Enter(gobj);
                return;
            } else {
                goto facingDir;
            }
        }
    }

    if (ftCliffCommon_80081298(gobj) == false) {
        do {
            s32 envFlags = collData->env_flags;
            float impact_angle;
            if (envFlags & Collide_CeilingMask) {
                impact_angle =
                    lbVector_AngleXY(&collData->ceiling.normal, &fp->self_vel);
            } else if (envFlags & Collide_LeftWallMask) {
                impact_angle = lbVector_AngleXY(
                    &collData->left_facing_wall.normal, &fp->self_vel);
            } else if (envFlags & Collide_RightWallMask) {
                impact_angle = lbVector_AngleXY(
                    &collData->right_facing_wall.normal, &fp->self_vel);
            } else {
                if (((!fp->self_vel.x) && (!fp->self_vel.x)) &&
                    (!fp->self_vel.x))
                {
                }
                break;
            }

            if (impact_angle < (0.01745329238474369f *
                                (90.0f + da->x94_FOX_FIREFOX_BOUND_ANGLE)))
            {
                goto facingDir;
            } else {
                continue;
            }

        } while (false);

        return;

        {
        facingDir:
            if (fp->self_vel.x >= 0.0f) {
                facingDir = 1.0f;
            } else {
                facingDir = -1.0f;
            }

            fp->facing_dir = facingDir;
            fp->mv.fx.SpecialHi.rotateModel =
                atan2f(fp->self_vel.y, fp->self_vel.x * fp->facing_dir);
            ftFox_SpecialHi_RotateModel(gobj);
        }
    }
}

/**
 * @brief Ground to air transition during Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHi_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirHi,
                              (Ft_MF_SkipHit | FTFOX_SPECIALHI_COLL_FLAG),
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);

    fp->x2223_b4 = true;
    fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
}

/**
 * @brief Air to ground transition during Up-B (Fire Fox) launch travel
 * @details Reads control stick input to determine launch direction: enters
 * grounded launch if angled along floor, or enters aerial launch if angled
 * away.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_AirToGround(HSD_GObj* gobj)
{
    Vec3 stick_vec;
    ftFox_DatAttrs* da;
    Fighter* fp;
    CollData* collData;
    ftFox_DatAttrs* tempAttrs;
    float temp_stick;
    float stick_x;
    float stick_y;

    fp = GET_FIGHTER(gobj);
    stick_y = fp->input.lstick[0].y;

    collData = getFtColl(fp);
    da = fp->dat_attrs;

    if (stick_y < 0.0f) {
        stick_y = -stick_y;
    }
    temp_stick = fp->input.lstick[0].x;
    stick_x = stickGetDir(fp->input.lstick[0].x, 0.0f);

    if (!((stick_x + stick_y) < da->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN))
    {
        stick_vec.x = temp_stick;
        stick_vec.y = fp->input.lstick[0].y;
        stick_vec.z = 0.0f;

        if (!(lbVector_AngleXY(&collData->floor.normal, &stick_vec) <
              HALF_PI32) &&
            (ftCo_8009A134(gobj) == false))
        {
            ftCommon_UpdateFacing(fp);

            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHi, Ft_MF_None,
                                      0.0f, 1.0f, 0.0f, NULL);

            tempAttrs = fp->dat_attrs;
            fp->x2223_b4 = 1;

            fp->mv.fx.SpecialHi.travelFrames =
                tempAttrs->x68_FOX_FIREFOX_DURATION;

            fp->mv.fx.SpecialHi.unk = 0.0f;
            fp->mv.fx.SpecialHi.unk2 = 0.0f;

            fp->gr_vel = da->x74_FOX_FIREFOX_SPEED * fp->facing_dir;

            fp->mv.fx.SpecialHi.rotateModel =
                atan2f(-collData->floor.normal.x * fp->facing_dir,
                       collData->floor.normal.y);

            ftFox_SpecialHi_RotateModel(gobj);
            fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
            fp->x21F8 = ftCommon_8007F76C;
            return;
        }
    }
    ftCommon_8007D60C(fp);
    ftFx_SpecialAirHi_Enter(gobj);
}

/**
 * @brief Action State initialization for aerial Up-B (Fire Fox) launch travel
 * @details Reads control stick X/Y to calculate launch angle (atan2). Sets
 * launch velocity, applies model rotation, and consumes all mid-air jumps
 * (`max_jumps`).
 * @param gobj The fighter's game object
 */
void ftFx_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    ftFox_DatAttrs* da;
    ftCo_DatAttrs* ca;
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* tempAttrs;
    float stick_x;
    float stick_y;
    float temp_stick;

    ca = &fp->co_attrs;
    da = fp->dat_attrs;

    stick_y = stickGetDir(fp->input.lstick[0].y, 0.0f);

    temp_stick = fp->input.lstick[0].x;

    stick_x = stickGetDir(temp_stick, 0.0f);

    // Calculate launch angle from control stick if outside deadzone
    if ((stick_x + stick_y) >= da->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN) {
        if (temp_stick < 0.0f) {
            temp_stick = -temp_stick;
        }
        if (temp_stick > da->x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN) {
            ftCommon_UpdateFacing(fp);
        }
        fp->mv.fx.SpecialHi.rotateModel = atan2f(
            fp->input.lstick[0].y, fp->input.lstick[0].x * fp->facing_dir);
    } else {
        // Default to straight up (90 degrees)
        fp->mv.fx.SpecialHi.rotateModel = HALF_PI32;
    }

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirHi, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);

    tempAttrs = fp->dat_attrs;
    fp->x2223_b4 = 1;

    fp->mv.fx.SpecialHi.travelFrames = tempAttrs->x68_FOX_FIREFOX_DURATION;
    fp->mv.fx.SpecialHi.unk = 0;
    fp->mv.fx.SpecialHi.unk2 = 0;

    // Apply launch velocity vector
    fp->self_vel.x = fp->facing_dir * (da->x74_FOX_FIREFOX_SPEED *
                                       cosf(fp->mv.fx.SpecialHi.rotateModel));
    fp->self_vel.y =
        da->x74_FOX_FIREFOX_SPEED * sinf(fp->mv.fx.SpecialHi.rotateModel);
    ftFox_SpecialHi_RotateModel(gobj);
    fp->x21F8 = ftCommon_8007F76C;
    fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
    fp->x1968_jumpsUsed = ca->max_jumps;
}

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiLanding_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) freefall
 * @details Transitions into FallSpecial with freefall mobility and landing lag
 * (26 frames).
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) landing (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiLanding_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) freefall (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiLanding_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    ftCommon_CalcGroundAccel_Deaccel(fp,
                                     da->x7C_FOX_FIREFOX_GROUND_MOMENTUM_END);
    ftCommon_SetSelfMovementFromGroundedMovement(gobj);
}

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiLanding_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (ft_80082708(gobj) == false) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH)) {
        ftFx_SpecialHiFall_Enter(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Transitions from aerial Up-B fall to grounded landing at frame 13.0
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_Enter(HSD_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiLanding,
                              (Ft_MF_SkipColAnim | Ft_MF_UpdateCmd), 13.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Handles landing from Up-B (Fire Fox) onto ground
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiFall_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB24(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiLanding, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x21F8 = ftCommon_8007F76C;
}

/**
 * @brief Handles sliding off ledge during Up-B (Fire Fox) landing lag
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiLanding_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB24(gobj);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiFall, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x21F8 = ftCommon_8007F76C;
}

/**
 * @brief Animation callback for Up-B (Fire Fox) wall/floor rebound (bonk)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiBound_Anim(HSD_GObj* gobj)
{
    ftCo_DatAttrs* ca;
    Fighter* fp;
    ftFox_DatAttrs* da;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;
    da = fp->dat_attrs;

    if (fp->cmd_vars[0] != 0 && fp->ground_or_air == GA_Air) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
        fp->x1968_jumpsUsed = (u8) ca->max_jumps;
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftCo_80096900(gobj, 1, 0, true,
                          da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                          da->x90_FOX_FIREFOX_LANDING_LAG);
            fp->x1968_jumpsUsed = (u8) ca->max_jumps;
            return;
        }
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief IASA callback for Up-B (Fire Fox) rebound (no interrupts)
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiBound_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for Up-B (Fire Fox) rebound
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiBound_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool ground_or_air = ftGetGroundAir(fp);

    if (ground_or_air == GA_Air) {
        ft_800851C0(gobj);
        ftCommon_CalcSelfAccel_DeaccelQuickAir(fp);
        return;
    }
    ft_80084F3C(gobj);
}

/**
 * @brief Collision callback for Up-B (Fire Fox) rebound
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiBound_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Air) {
        if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
            ftCommon_8007D7FC(fp);
            return;
        }

        if (ftCliffCommon_80081298(gobj)) {
            return;
        }
    } else {
        ft_80084104(gobj);
    }
}

/**
 * @brief Helper to initialize impact angle and spawn wall bonk GFX
 * @param gobj The fighter's game object
 */
static inline void ftFox_SpecialHiBound_SetVars(HSD_GObj* gobj)
{
    vf32 ground_angle;
    Fighter* fp = fp = gobj->user_data;
    CollData* collData = collData = getFtColl(fp);

    if (fp->coll_data.env_flags & Collide_FloorMask) {
        ground_angle =
            -atan2f(collData->floor.normal.x, collData->floor.normal.y);
    } else {
        ground_angle = 0.0f;
    }
    efSync_Spawn(1030, gobj, &fp->cur_pos, &ground_angle);
    fp->x2219_b0 = true;
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Action State initialization for Up-B (Fire Fox) wall/floor rebound
 * @details Dampens horizontal velocity by `x84_FOX_FIREFOX_BOUND_VEL_X` and
 * spawns bonk GFX.
 * @param gobj The fighter's game object
 */
void ftFx_SpecialHiBound_Enter(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftFox_DatAttrs* da = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiBound, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->x21F8 = ftCommon_8007F76C;
    fp->self_vel.x *= da->x84_FOX_FIREFOX_BOUND_VEL_X;
    fp->cmd_vars[0] = 0;
    ftFox_SpecialHiBound_SetVars(gobj);
}
