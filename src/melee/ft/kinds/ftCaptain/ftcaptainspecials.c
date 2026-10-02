/**
 * @file ftcaptainspecials.c
 * @brief Side Special - Raptor Boost (Captain Falcon) / Gerudo Dragon
 * (Ganondorf)
 * @details Implements grounded and aerial states for Raptor Boost / Gerudo
 * Dragon, including target detection (fighters and items), startup dash,
 * uppercut hit, aerial meteor spike hit, custom gravity/terminal velocity, and
 * landing lag handling. Module prefix: ftCa
 */

#include "ftcaptainspecials.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/it/forward.h>

#include "ftcaptain.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/types.h>
#include <melee/it/it_26B1.h>
#include <sysdolphin/baselib/gobj.h>

/**
 * @brief Destroys all active visual effects and clears Raptor Boost state
 * flags.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    efLib_DestroyAll(gobj);
    fp->u.ca.during_specials = false;
    fp->u.ca.during_specials_start = false;
}

/**
 * @brief Sets damage and death callbacks to clear Raptor Boost effects.
 * @param gobj Pointer to Fighter GObj
 */
static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftCa_Init_800E28C8;
    fp->death2_cb = ftCa_Init_800E28C8;
}

/**
 * @brief Zeroes command script variables and marks the fighter as grounded.
 * @param gobj Pointer to Fighter GObj
 */
static void resetCmdVarsGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32* cmd_vars = (&fp->cmd_vars[0]);
    cmd_vars[0] = cmd_vars[1] = cmd_vars[2] = cmd_vars[3] = 0;
    ftCommon_8007D7FC(fp);
}

/**
 * @brief Zeroes 3D self-velocity vector.
 * @param fp Pointer to Fighter data
 */
static inline void resetVel(Fighter* fp)
{
    Vec3* vel = &fp->self_vel;
    vel->x = vel->y = vel->z = 0;
}

/**
 * @brief Grounded Side-B Startup (Raptor Boost / Gerudo Dragon) entry.
 * @details Initializes command variables, transitions to
 * ftCa_MS_SpecialSStart, spawns startup flame effect (effect 1169 on HeadN for
 * Falcon, 1293 on L2ndNb for Ganon), and attaches hurtbox detection callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    resetCmdVarsGround(gobj);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialSStart, Ft_MF_None, 0, 1, 0,
                              NULL);
    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);
    switch (ftLib_GetKind(gobj)) {
    case Ft_Kind_Captain: {
        efSync_Spawn(1169, gobj, fp->parts[FtPart_HeadN].joint);
        fp->u.ca.during_specials_start = true;
        break;
    }
    case Ft_Kind_Ganon:
        efSync_Spawn(1293, gobj, fp->parts[FtPart_L2ndNb].joint);
        fp->u.ca.during_specials_start = true;
        break;
    default:
        break;
    }
    fp->u.ca.during_specials = false;
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->hurtbox_detect_cb = ftCa_SpecialS_OnDetect;

    resetVel(fp);

    fp->gr_vel = 0;
}

/**
 * @brief Internal helper to set up aerial Raptor Boost startup state.
 * @param gobj Pointer to Fighter GObj
 */
static inline void setupAirStart(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    {
        u32* cmd_vars = &fp->cmd_vars[0];
        cmd_vars[0] = cmd_vars[1] = cmd_vars[2] = cmd_vars[3] = 0;
    }
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirSStart, Ft_MF_None, 0, 1,
                              0, NULL);
    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);
    switch (ftLib_GetKind(gobj)) {
    case Ft_Kind_Captain: {
        efSync_Spawn(1169, gobj, fp->parts[FtPart_HeadN].joint);
        fp->u.ca.during_specials_start = true;
        break;
    }
    case Ft_Kind_Ganon: {
        efSync_Spawn(1293, gobj, fp->parts[FtPart_L2ndNb].joint);
        fp->u.ca.during_specials_start = true;
        break;
    }
    default:
        break;
    }
    fp->u.ca.during_specials = false;
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->hurtbox_detect_cb = ftCa_SpecialS_OnDetect;
    {
        Vec3* vel = &fp->self_vel;
        vel->x = vel->y = vel->z = 0;
    }
}

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost / Aerial Gerudo Dragon)
 * entry.
 * @details Enters ftCa_MS_SpecialAirSStart, zeroes gravity accumulator, and
 * sets aerial state.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    setupAirStart(gobj);
    fp->mv.ca.specials.grav = 0;
    ftCommon_8007D60C(fp);
}

/// Transition flags for changing from startup to hit state
static u32 const transition_flags =
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd | Ft_MF_SkipColAnim |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/**
 * @brief Transitions grounded Raptor Boost from startup dash to uppercut on
 * contact.
 * @param gobj Pointer to Fighter GObj
 */
static void onDetectGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = getFtSpecialAttrsD(fp);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialS, transition_flags, 0, 1,
                              0, NULL);
    setCallbacks(gobj);
    {
        Vec3* vel = &fp->self_vel;
        vel->y = vel->z = 0;
    }
    fp->gr_vel *= da->specials_gr_vel_x;
}

/**
 * @brief Transitions aerial Raptor Boost from startup dive to meteor spike on
 * contact.
 * @param gobj Pointer to Fighter GObj
 */
static void onDetectAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirS, transition_flags, 0,
                              1, 0, NULL);
    setCallbacks(gobj);
    fp->self_vel.z = 0;
}

/**
 * @brief Hurtbox detection callback for Raptor Boost / Gerudo Dragon.
 * @details When detection window is active (cmd_vars[0] != 0), checks target
 * entity:
 * - Opponent fighters: triggers hit
 * - Crates, barrels, capsules, eggs: triggers hit
 * - Pokemon, stage hazards, random items: triggers hit
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_OnDetect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        HSD_GObj* detected_gobj = fp->unk_gobj;
        if (fp->unk_gobj->classifier == HSD_GOBJ_CLASS_FIGHTER) {
            switch (fp->motion_id) {
            case ftCa_MS_SpecialSStart: {
                onDetectGround(gobj);
                break;
            }
            case ftCa_MS_SpecialAirSStart: {
                onDetectAir(gobj);
                break;
            }
            }
        } else if (fp->unk_gobj->classifier == HSD_GOBJ_CLASS_ITEM) {
            if (itGetKind(detected_gobj) < It_Kind_Container_End) {
                switch (fp->motion_id) {
                case ftCa_MS_SpecialSStart: {
                    onDetectGround(gobj);
                    break;
                }
                case ftCa_MS_SpecialAirSStart: {
                    onDetectAir(gobj);
                    break;
                }
                }
            } else if ((itGetKind(detected_gobj) >= It_Kind_Monster_Start &&
                        itGetKind(detected_gobj) < It_Kind_Monster_End) ||
                       (itGetKind(detected_gobj) >= It_Kind_Monster2_Start &&
                        itGetKind(detected_gobj) < It_Kind_Stage_End) ||
                       itGetKind(detected_gobj) == It_PKind_Random)
            {
                switch (fp->motion_id) {
                case ftCa_MS_SpecialSStart: {
                    onDetectGround(gobj);
                    break;
                }
                case ftCa_MS_SpecialAirSStart: {
                    onDetectAir(gobj);
                    break;
                }
                }
            }
        }
    }
}

/**
 * @brief Grounded Side-B Startup (Raptor Boost) animation callback.
 * @details On animation completion (whiff), transitions to Wait (idle).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) animation callback.
 * @details Spawns uppercut flame effect (1170 for Falcon, 1294 for Ganon) on
 * TransN. On completion, transitions to Wait.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->u.ca.during_specials) {
        switch (ftLib_GetKind(gobj)) {
        case Ft_Kind_Captain: {
            efSync_Spawn(1170, gobj, fp->parts[FtPart_TransN].joint,
                         &fp->facing_dir);
            fp->u.ca.during_specials = true;
            break;
        }
        case Ft_Kind_Ganon:
            efSync_Spawn(1294, gobj, fp->parts[FtPart_TransN].joint,
                         &fp->facing_dir);
            fp->u.ca.during_specials = true;
            break;
        default:
            break;
        }
        Fighter_SetEffectHitlagCallbacks(fp);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) animation callback.
 * @details On completion (whiff), enters freefall / landing lag with
 * specials_miss_landing_lag frames.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (da->specials_miss_landing_lag == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 1, 0, 1, da->specials_miss_landing_lag);
        }
    }
}

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) animation
 * callback.
 * @details Spawns meteor spike flame effect (1171 for Falcon, 1295 for Ganon)
 * on TransN. On completion, enters freefall with specials_hit_landing_lag
 * frames of landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    u8 _[8];
    if (!fp->u.ca.during_specials) {
        switch (ftLib_GetKind(gobj)) {
        case Ft_Kind_Captain: {
            efSync_Spawn(1171, gobj, fp->parts[FtPart_TransN].joint,
                         &fp->facing_dir);
            fp->u.ca.during_specials = true;
            break;
        }
        case Ft_Kind_Ganon: {
            efSync_Spawn(1295, gobj, fp->parts[FtPart_TransN].joint,
                         &fp->facing_dir);
            fp->u.ca.during_specials = true;
            break;
        }
        default:
            break;
        }
        Fighter_SetEffectHitlagCallbacks(fp);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (da->specials_hit_landing_lag == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 1, 0, 1, da->specials_hit_landing_lag);
        }
    }
}

/**
 * @brief Grounded Side-B Startup (Raptor Boost) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialSStart_IASA(HSD_GObj* gobj) {}

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_IASA(HSD_GObj* gobj) {}

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) IASA callback (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) IASA callback
 * (no-op).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirS_IASA(HSD_GObj* gobj) {}

/**
 * @brief Grounded Side-B Startup (Raptor Boost) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialSStart_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) physics callback.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) physics callback.
 * @details When active descent flag (cmd_vars[1] == 1) is set, accelerates
 * downward by specials_grav, clamped to -specials_terminal_vel.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    u8 _[8];
    ft_80085134(gobj);
    if (fp->cmd_vars[1] == 1) {
        fp->mv.ca.specials.grav -= da->specials_grav;
        if (fp->mv.ca.specials.grav < -da->specials_terminal_vel) {
            fp->mv.ca.specials.grav = -da->specials_terminal_vel;
        }
        fp->self_vel.y = fp->mv.ca.specials.grav;
    }
}

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) physics
 * callback.
 * @details Accelerates downward by specials_grav, clamped to
 * -specials_terminal_vel.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    u8 _[8];
    ft_80085134(gobj);
    fp->mv.ca.specials.grav -= da->specials_grav;
    if (fp->mv.ca.specials.grav < -da->specials_terminal_vel) {
        fp->mv.ca.specials.grav = -da->specials_terminal_vel;
    }
    fp->self_vel.y = fp->mv.ca.specials.grav;
}

/**
 * @brief Grounded Side-B Startup (Raptor Boost) collision callback.
 * @details Checks for cliff edges (transitions to fall if running off ledge)
 * and wall contact in facing direction (cancels dash into Wait on wall bonk).
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialSStart_Coll(HSD_GObj* gobj)
{
    u8 unused[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[2] == 0) {
        ft_80084104(gobj);
        return;
    }
    if (ft_80082708(gobj) == false) {
        efLib_DestroyAll(gobj);
        ftCommon_8007D60C(fp);
        if (da->specials_miss_landing_lag == 0) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCommon_ClampAirDrift(fp);
        ftCo_80096900(gobj, 1, 1, 0, 1, da->specials_miss_landing_lag);
        return;
    }
    if (fp->cmd_vars[0] == 1) {
        float _ = fp->facing_dir;
        if ((fp->facing_dir == +1 &&
             (fp->coll_data.env_flags & Collide_LeftWallMask)) ||
            (fp->facing_dir == -1 &&
             fp->coll_data.env_flags & Collide_RightWallMask))
        {
            efLib_DestroyAll(gobj);
            ft_8008A2BC(gobj);
        }
    }
}

/**
 * @brief Grounded Side-B Hit (Raptor Boost Uppercut) collision callback.
 * @details If fighter leaves ground during uppercut, transitions to fall or
 * landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        ftCaptain_DatAttrs* da = fp->dat_attrs;
        u8 _[8];
        if (!ft_80082708(gobj)) {
            efLib_DestroyAll(gobj);
            ftCommon_8007D60C(fp);
            if (da->specials_hit_landing_lag == 0) {
                ftCo_Fall_Enter(gobj);
                return;
            } else {
                ftCommon_ClampAirDrift(fp);
                ftCo_80096900(gobj, 1, 1, 0, 1, da->specials_hit_landing_lag);
            }
        }
    }
}

/**
 * @brief Aerial Side-B Startup (Aerial Raptor Boost) collision callback.
 * @details If fighter touches ground during startup dive, enters
 * LandingFallSpecial with specials_miss_landing_lag frames of landing lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj) == true) {
        efLib_DestroyAll(gobj);
        ftCo_LandingFallSpecial_Enter(gobj, false,
                                      da->specials_miss_landing_lag);
    }
}

/**
 * @brief Aerial Side-B Hit (Aerial Raptor Boost Meteor Spike) collision
 * callback.
 * @details If fighter touches ground during meteor spike, converts horizontal
 * air velocity to ground velocity and enters LandingFallSpecial with
 * specials_hit_landing_lag frames of lag.
 * @param gobj Pointer to Fighter GObj
 */
void ftCa_SpecialAirS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    u8 _[8];
    if (ft_80081D0C(gobj) == true) {
        fp->gr_vel = fp->self_vel.x;
        efLib_DestroyAll(gobj);
        ftCo_LandingFallSpecial_Enter(gobj, false,
                                      da->specials_hit_landing_lag);
    }
}
