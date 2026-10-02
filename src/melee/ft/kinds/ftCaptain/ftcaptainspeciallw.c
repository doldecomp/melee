/**
 * @file ftcaptainspeciallw.c
 * @brief Down Special - Falcon Kick (Captain Falcon) / Wizard's Foot
 * (Ganondorf)
 * @details Implements grounded and aerial states for Falcon Kick / Wizard's
 * Foot, including on-hit slowdown drag, foot flame particles, ground slide
 * recovery, aerial landing lag, ledge slip-off, and wall bonk rebound
 * mechanics. Module prefix: ftCa
 */

#include "ftcaptainspeciallw.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include <placeholder.h>

#include "forward.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/efasync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/types.h>

/// /* literal */ float const ftCa_SpecialHi_804D9220 = 0.0F;
/// /* literal */ float const ftCa_SpecialHi_804D9224 = 0.01745329238474369f;
/// /* literal */ float const ftCa_SpecialHi_804D9228 = 1;
/// /* literal */ float const ftCa_SpecialHi_804D922C = -1;

/**
 * @brief Helper to test and clear the throw_flags_b1 hit trigger flag.
 * @param fp Pointer to Fighter data
 * @return True if flag was set, false otherwise
 */
static inline bool ftCa_Special_Inline_Check_Flag(Fighter* fp)
{
    if (fp->x2210.x0.throw_flags_b1) {
        fp->x2210.x0.throw_flags_b1 = 0;
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Zeroes command script variables cmd_vars[0..2].
 * @param gobj Pointer to Fighter GObj
 */
static inline void ftCa_Special_Inline_SetFlags(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
}

/**
 * @brief Spawns foot flame particle effect during Falcon Kick.
 * @details Spawns on right foot (FtPart_RFootJA) at 0 deg for grounded kick
 * (0x165), or left foot (FtPart_LFootJA) angled at
 * speciallw_flame_particle_angle for aerial kick (0x167). Effect ID: 0x490
 * (Falcon flame) or 0x50C (Ganon dark energy).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHi_800E3EAC(HSD_GObj* gobj)
{
    f32 particle_angle;
    enum Fighter_Part foot_bone;

    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(12);
    if (ftCa_Special_Inline_Check_Flag(fp) != 0) {
        if (!fp->x2219_b0) {
            if (fp->motion_id == 0x165) {
                particle_angle = 0.0F;
                foot_bone = ftParts_GetBoneIndex(fp, FtPart_RFootJA);
            } else if (fp->motion_id == 0x167) {
                particle_angle =
                    0.017453292f * da->speciallw_flame_particle_angle;
                foot_bone = ftParts_GetBoneIndex(fp, FtPart_LFootJA);
            }
            switch (ftLib_GetKind(gobj)) {
            case Ft_Kind_Captain:
                efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3U, 0x490U,
                              fp->parts[foot_bone].joint, &particle_angle);
                break;
            case Ft_Kind_Ganon:
                efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 3U, 0x50CU,
                              fp->parts[foot_bone].joint, &particle_angle);
                break;
            default:
                break;
            }
            fp->x2219_b0 = 1;
            return;
        }
        ftCommon_8007DB24((Fighter_GObj*) gobj);
    }
}

/**
 * @brief Damage dealt callback for Falcon Kick: applies on-hit slowdown drag.
 * @details Increments hit count and multiplies friction by
 * speciallw_on_hit_spd_modifier to decelerate Falcon Kick upon connecting with
 * targets.
 * @param gobj Pointer to Fighter GObj
 */
static void ftCa_SpecialHi_800E400C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = getFtSpecialAttrsD(fp);
    if (fp->mv.ca.speciallw.x0 <= da->speciallw_unk2) {
        ++fp->mv.ca.speciallw.x0;
        fp->mv.ca.speciallw.friction *= da->speciallw_on_hit_spd_modifier;
    }
}

/**
 * @brief Grounded Down-B (Falcon Kick) state entry.
 * @details Initializes command variables, sets friction to 1.0, registers deal
 * damage callback, and enters ftCa_MS_SpecialLw.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLw_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    fp->mv.ca.speciallw.x0 = 0.0F;
    fp->mv.ca.speciallw.friction = 1.0F;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLw, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->deal_dmg_cb = ftCa_SpecialHi_800E400C;
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) state entry.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLw, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Helper to transition from grounded Falcon Kick into recovery states.
 * @param gobj Pointer to Fighter GObj
 * @param is_air 0 for grounded recovery (SpecialLwEnd), 1 for air recovery
 * (SpecialLwEndAir)
 */
static inline void ftCa_SpecialLw_Anim_inline(HSD_GObj* gobj, s32 is_air)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    if (is_air == 0) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEnd, Ft_MF_None, 0,
                                  da->speciallw_ground_lag_mul, 0, NULL);
    } else {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialLwEndAir, Ft_MF_None, 0,
                                  1, 0, NULL);
    }
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Grounded Down-B (Falcon Kick) animation callback.
 * @details On kick completion, transitions to ground recovery or air recovery.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Ground) {
            ftCa_SpecialLw_Anim_inline(gobj, 0);
        } else {
            ftCa_SpecialLw_Anim_inline(gobj, 1);
        }
    }
}

/**
 * @brief Grounded Down-B Ground Recovery (Falcon Kick End) animation callback.
 * @details On animation completion, transitions to Wait (idle).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

/**
 * @brief Grounded Down-B Edge Slip Air Recovery (Falcon Kick End Air)
 * animation callback.
 * @details On animation completion, transitions to Fall.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

/**
 * @brief Helper to zero command variables upon completing aerial Falcon Kick.
 * @param gobj Pointer to Fighter GObj
 */
static inline void ftCa_SpecialAirLw_Anim_inline(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
}

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) animation callback.
 * @details On kick completion in the air, transitions to aerial end state
 * (SpecialAirLwEndAir).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCa_SpecialAirLw_Anim_inline(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirLwEndAir, Ft_MF_None,
                                  0, 1, 0, NULL);
    }
}

/**
 * @brief Aerial Down-B Landing Recovery (Falcon Kick Landing End) animation
 * callback.
 * @details On completion, transitions to Wait.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Aerial Down-B Air Recovery (Falcon Kick Air End Air) animation
 * callback.
 * @details On completion, transitions to Fall.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEndAir_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Falcon Kick Wall Rebound (Wall Bonk) animation callback.
 * @details On rebound completion, transitions to Fall.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Applies friction factor to self-velocity.
 * @param fp Pointer to Fighter data
 */
static inline void ftCa_Special_Inline_Friction(Fighter* fp)
{
    float friction = fp->mv.ca.speciallw.friction;
    fp->self_vel.x *= friction;
    fp->self_vel.y *= friction;
}

/**
 * @brief Grounded Down-B (Falcon Kick) physics callback.
 * @details Applies ground movement, friction drag, and spawns foot flame
 * effect.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        ft_80085088(gobj);
    } else {
        ftPartSetRotZ(fp, 0, 0);
        ft_80085134(gobj);
    }
    ftCa_Special_Inline_Friction(fp);
    ftCa_SpecialHi_800E3EAC(gobj);
}

/**
 * @brief Grounded Down-B Ground Recovery physics callback.
 * @details Applies ground deceleration using speciallw_ground_traction *
 * ground_friction.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = gobj->user_data;
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        if (fp->cmd_vars[2] != 0) {
            ftCommon_CalcGroundAccel_Deaccel(fp,
                                             da->speciallw_ground_traction *
                                                 fp->co_attrs.ground_friction);
            ftCommon_SetSelfMovementFromGroundedMovement(gobj);
        } else {
            ft_80084F3C(gobj);
        }
    } else {
        ftPartSetRotZ(fp, 0, 0.0F);
        ft_80084EEC(gobj);
    }
    ftCa_Special_Inline_Friction(fp);
}

/**
 * @brief Grounded Down-B Edge Slip Air Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEndAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007E5AC(fp);
        ft_80085088(gobj);
        return;
    }
    ftPartSetRotZ(fp, 0, 0);
    if (fp->cmd_vars[0] != 0) {
        ft_80084EEC(gobj);
    } else {
        ft_80085134(gobj);
    }
}

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) physics callback.
 * @details Applies aerial downward trajectory and spawns foot flame effect.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
    ftCa_SpecialHi_800E3EAC(gobj);
}

/**
 * @brief Aerial Down-B Landing Recovery physics callback.
 * @details Applies landing slide deceleration using
 * speciallw_air_landing_traction * ground_friction.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEnd_Phys(HSD_GObj* gobj)
{
    ftCo_DatAttrs* ca;
    ftCaptain_DatAttrs* da;

    Fighter* fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;
    if (fp->cmd_vars[2] != 0) {
        ca = getFtAttrs(fp);
        ftCommon_CalcGroundAccel_Deaccel(
            fp, da->speciallw_air_landing_traction * ca->ground_friction);
        ftCommon_SetSelfMovementFromGroundedMovement(gobj);
        return;
    } else {
        ft_80084F3C(gobj);
    }
}

/**
 * @brief Aerial Down-B Air Recovery physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEndAir_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Falcon Kick Wall Rebound physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialHiThrow1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

/**
 * @brief Grounded Down-B (Falcon Kick) collision callback.
 * @details Handles ground/air transition and wall collisions:
 * If kicking into a wall facing it (Collide_RightWallHug /
 * Collide_LeftWallHug), triggers Falcon Kick Wall Rebound bounce into
 * ftCa_MS_SpecialHiThrow1.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLw_Coll(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    if ((s32) fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == 0) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj) != 0) {
        ftCommon_8007D7FC(fp);
    }
    {
        if ((fp->cmd_vars[0] != 0) &&
            /// @todo Pull out these check functions
            ((((fp->facing_dir == -1) != 0) &&
              (fp->coll_data.env_flags & Collide_RightWallHug)) ||
             (fp->facing_dir == +1 &&
              (fp->coll_data.env_flags & Collide_LeftWallHug))))
        {
            fp = GET_FIGHTER(gobj);
            ftCa_Special_Inline_SetFlags(gobj);
            fp->x2210.throw_flags = 0;
            ftCommon_8007D5D4(fp);
            Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialHiThrow1,
                                      Ft_MF_None, 0, 1, 0, NULL);
        }
    }
}

/**
 * @brief Grounded Down-B Ground Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        if (fp->cmd_vars[1] != 0) {
            if (!ft_800827A0(gobj)) {
                ftCommon_8007D5D4(fp);
            }
        } else if (!ft_80082708(gobj)) {
            ftCommon_8007D5D4(fp);
        }
    } else if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
    }
}

/**
 * @brief Grounded Down-B Edge Slip Air Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialLwEndAir_Coll(Fighter_GObj* gobj)
{
    ftCa_SpecialLwEnd_Coll(gobj);
}

/**
 * @brief Resets command variables and throw flags.
 * @param gobj Pointer to Fighter GObj
 */
static void resetCmdAndThrow(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = 0;
    fp->x2210.throw_flags = 0;
}

/**
 * @brief Landing collision helper for aerial Falcon Kick.
 * @details If touching ground, enters landing recovery motion state msid
 * with speciallw_landing_lag_mul animation speed.
 * @param gobj Pointer to Fighter GObj
 * @param msid Target landing motion state ID
 */
static void doColl(Fighter_GObj* gobj, ftCaptain_MotionState msid)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        PAD_STACK(4 * 4);
        resetCmdAndThrow(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0,
                                  da->speciallw_landing_lag_mul, 0, NULL);
    }
}

/**
 * @brief Aerial Down-B (Aerial Falcon Kick) collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doColl(gobj, ftCa_MS_SpecialAirLwEnd);
}

/**
 * @brief Aerial Down-B Landing Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEnd_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
}

/**
 * @brief Aerial Down-B Air Recovery collision callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirLwEndAir_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 4);
    doColl(gobj, ftCa_MS_SpecialAirLwEnd);
}
