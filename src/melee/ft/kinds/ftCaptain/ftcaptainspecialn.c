/**
 * @file ftcaptainspecialn.c
 * @brief Neutral Special - Falcon Punch (Captain Falcon) / Warlock Punch
 * (Ganondorf)
 * @details Implements grounded and aerial states for Captain Falcon's
 * signature Falcon Punch and Ganondorf's Warlock Punch, including wind
 * effects, control stick angle calculation, particle spawning, physics phases,
 * and ground/air state transitions. Module prefix: ftCa
 */

#include "ftcaptainspecialn.h"

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
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/lb/lb_00F9.h>

#ifdef MUST_MATCH
static void order_sdata2(void)
{
    (void) 2.0f;
    (void) 0.0f;
    (void) 4.0f;
}
#endif

/**
 * @brief Spawns aesthetic wind / dust swirl effects during Ganondorf's Warlock
 * Punch startup.
 * @details Spawns on alternating frames (cur_anim_frame & 1):
 * - Frames 16-50: small wind effect (radius 2)
 * - Frames 51-68: large wind effect (radius 4)
 * Captain Falcon does not produce wind effects.
 * @param gobj Pointer to Fighter GObj
 */
static inline void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int cur_anim_frame = fp->cur_anim_frame;
    FighterKind kind = ftLib_GetKind(gobj);

    switch (kind) {
    case Ft_Kind_Captain:
        return;
    case Ft_Kind_Ganon:
        if (cur_anim_frame & 1) {
            if (cur_anim_frame >= 16 && cur_anim_frame <= 50) {
                lb_800119DC(&fp->cur_pos, 2, 2, 2, 0);
            } else if (cur_anim_frame >= 51 && cur_anim_frame <= 68) {
                lb_800119DC(&fp->cur_pos, 2, 4, 4, 0);
            }
        }
        return;
    default:
        break;
    }
}

/**
 * @brief Calculates angle deflection for aerial Falcon Punch based on analog
 * stick Y input.
 * @param fp Pointer to Fighter data
 * @return Punch angle offset in radians
 */
static float ftCaptain_SpecialN_GetAngleVel(Fighter* fp)
{
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    {
        float stick_max;
        float stick_y = stickGetDir(fp->input.lstick[0].y, 0);
        float stick_min;
        stick_max = da->specialn_stick_range_y_pos;
        if (stick_y > stick_max) {
            stick_y = stick_max;
        }
        stick_min = da->specialn_stick_range_y_neg;
        stick_y -= stick_min;
        if (stick_y < 0) {
            stick_y = 0;
        }
        if (fp->input.lstick[0].y < 0) {
            stick_y = -stick_y;
        }
        {
            float rad_per_deg = MTXDegToRad(1);
            return rad_per_deg * (stick_y * da->specialn_angle_diff /
                                  (stick_max - stick_min));
        }
    }
}

/**
 * @brief Grounded Neutral-B (Falcon Punch / Warlock Punch) entry.
 * @details Resets script command variables and throw flags, enters state
 * ftCa_MS_SpecialN.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialN, Ft_MF_None, 0, 1, 0,
                              NULL);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch / Aerial Warlock Punch) entry.
 * @details Resets script command variables and throw flags, enters state
 * ftCa_MS_SpecialAirN.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->x2210.throw_flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirN, Ft_MF_None, 0, 1, 0,
                              NULL);
    Fighter_SetEffectHitlagCallbacks(fp);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Grounded Neutral-B (Falcon Punch) animation callback.
 * @details Checks wind effect; on animation end, transitions to Wait (idle).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) animation callback.
 * @details Checks wind effect; on animation end, transitions to Fall.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Grounded Neutral-B (Falcon Punch) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialN_IASA(HSD_GObj* gobj) {}

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) IASA callback.
 * @details When animation command variable cmd_vars[0] triggers momentum
 * release: computes angle from control stick Y and applies directional
 * velocity.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = (ftCaptain_DatAttrs*) getFtSpecialAttrs(fp);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        {
            float angle_rad = ftCaptain_SpecialN_GetAngleVel(fp);
            fp->self_vel.y = da->specialn_vel_x * sinf(angle_rad);
            fp->self_vel.x =
                da->specialn_vel_x * (fp->facing_dir * cosf(angle_rad));
        }
    }
}

/**
 * @brief Shared Falcon Punch physics routine for visual effects and hitlag
 * handling.
 * @details Spawns flame bird effect 1167 (Falcon) or dark energy effect 1291
 * (Ganon) on the punching fist joint (joint 57 for Falcon, 78 for Ganon) upon
 * throw_flags_b1 trigger.
 * @param gobj Pointer to Fighter GObj
 */
static inline void doPhys(HSD_GObj* gobj)
{
    bool has_throw_flag;
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2210.x0.throw_flags_b1) {
        fp->x2210.x0.throw_flags_b1 = false;
        has_throw_flag = true;
    } else {
        has_throw_flag = false;
    }
    if (has_throw_flag) {
        if (!fp->x2219_b0) {
            FighterKind kind = ftLib_GetKind(gobj);
            switch (kind) {
            case Ft_Kind_Captain:
                efSync_Spawn(1167, gobj, fp->parts[FtPart_TopN].joint,
                             fp->parts[57].joint);
                break;
            case Ft_Kind_Ganon:
                efSync_Spawn(1291, gobj, fp->parts[FtPart_TopN].joint,
                             fp->parts[78].joint);
                break;
            default:
                break;
            }
            fp->x2219_b0 = true;
        } else {
            ftCommon_8007DB24(gobj);
        }
    }
}

/**
 * @brief Grounded Neutral-B (Falcon Punch) physics callback.
 * @details Runs visual effect checks and applies standard grounded friction.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialN_Phys(HSD_GObj* gobj)
{
    u8 _[8];
    doPhys(gobj);
    ft_80084FA8(gobj);
}

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) physics callback.
 * @details Applies visual effects and handles 3 distinct momentum phases via
 * cmd_vars[1]:
 * - 0: Standard aerial gravity physics
 * - 1: Aerial momentum drift decayed by specialn_vel_mul per frame
 * - 2: Horizontal air drag / deceleration
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirN_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = (ftCaptain_DatAttrs*) getFtSpecialAttrs(fp);
    doPhys(gobj);
    switch (fp->cmd_vars[1]) {
    case 0: {
        ft_80084EEC(gobj);
        return;
    }
    case 1: {
        fp->self_vel.y *= da->specialn_vel_mul;
        fp->self_vel.x *= da->specialn_vel_mul;
        return;
    }
    case 2: {
        ft_80084DB0(gobj);
        return;
    }
    default:
        return;
    }
}

/// Motion state transition flags preserving animation frame, GFX, and command
/// state
static u32 const transition_flags =
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipRumble | Ft_MF_UpdateCmd |
    Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/**
 * @brief Grounded Neutral-B (Falcon Punch) collision callback.
 * @details Checks if fighter walks off edge; transitions smoothly to aerial
 * Falcon Punch while clamping air drift to prevent abrupt momentum jumps.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_GroundToAirStateChange(gobj, fp, ftCa_MS_SpecialAirN,
                                        transition_flags);
        Fighter_SetEffectHitlagCallbacks(fp);
        ftCommon_ClampAirDrift(fp);
    }
}

/**
 * @brief Aerial Neutral-B (Aerial Falcon Punch) collision callback.
 * @details Checks for ground contact; transitions smoothly to grounded Falcon
 * Punch upon landing without resetting animation progress.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_AirToGroundStateChange(gobj, fp, ftCa_MS_SpecialN,
                                        transition_flags);
        Fighter_SetEffectHitlagCallbacks(fp);
    }
}
