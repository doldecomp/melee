/**
 * @file ftseakspeciallw.c
 * @brief Sheik's Down-B move: Transform.
 * @details Implements Sheik's grounded and aerial Down-B transformation into
 * Zelda, including visual particle bursts, velocity damping, state
 * transitions, and completion callbacks that execute the character swap.
 * Module prefix: ftSk (Fighter: Sheik)
 */

#include "ftseakspeciallw.h"

#include <melee/ft/forward.h>

#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/kinds/ftZelda/ftzeldaspeciallw.h>
#include <melee/ft/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>

static MotionFlags const ftSk_MF_SpecialLw_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus |
    Ft_MF_SkipHit;

/**
 * @brief Accessory callback for initial transform stage.
 * @details Spawns transformation flash visual effect (GFX ID 0x4FC) on Sheik's
 * right arm.
 * @param gobj Fighter game object
 */
static void fn_80114034(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4FC, gobj, fp->parts[FtPart_R2ndNb].joint);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = 0;
}

/**
 * @brief Accessory callback for transform exit/completion stage.
 * @details Spawns transformation completion visual effect (GFX ID 0x4FD) on
 * Sheik's hip.
 * @param gobj Fighter game object
 */
static void fn_801140B0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(0x4FD, gobj, fp->parts[FtPart_HipN].joint);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = 0;
}

/**
 * @brief Accessory callback that executes character transformation into Zelda.
 * @details Initiates character swap by calling ftCommon_8007EFC8 with Zelda's
 * transform handler.
 * @param gobj Fighter game object
 */
static void fn_8011412C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->accessory4_cb = NULL;
    ftCommon_8007EFC8(gobj, &ftZd_SpecialLw_8013B4D8);
}

/**
 * @brief Helper spawning transformation particle burst around Sheik.
 * @param v 3D world position vector for the effect center
 */
static void ftSk_unk_inline(Vec3* v)
{
    lb_800119DC(v, 0x78, 0.4F, 0.003F, M_PI / 3);
}

/**
 * @brief Enters grounded Down-B (Transform) phase 1.
 * @details Changes motion state to 0x169 (ftSk_MS_SpecialLw), dampens current
 * horizontal and vertical velocities using special attributes, and spawns the
 * transform light effect.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Vec3 hip_pos;
    Fighter* fp;
    ftSeakAttributes* attributes;

    u8 _[16];

    Fighter_ChangeMotionState(gobj, 0x169, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;
    fp->cmd_vars[0] = 0;
    // Velocity dampening on transformation start
    fp->self_vel.x /= attributes->x60;
    fp->self_vel.y /= attributes->x64;
    fp->gr_vel /= attributes->x60;
    lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &hip_pos);
    ftSk_unk_inline(&hip_pos);
    fp->accessory4_cb = &fn_80114034;
}

/**
 * @brief Enters aerial Down-B (Transform) phase 1.
 * @details Changes motion state to 0x16B (ftSk_MS_SpecialAirLw), dampens
 * current velocities, and begins the aerial transformation sequence.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Vec3 hip_pos;
    Fighter* fp;
    ftSeakAttributes* attributes;

    u8 _[16];

    Fighter_ChangeMotionState(gobj, 0x16B, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;

    fp->cmd_vars[0] = 0;
    // Velocity dampening on transformation start
    fp->self_vel.x /= attributes->x60;
    fp->self_vel.y /= attributes->x64;
    fp->gr_vel /= attributes->x60;
    lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &hip_pos);
    ftSk_unk_inline(&hip_pos);
    fp->accessory4_cb = &fn_80114034;
}

/**
 * @brief Animation update for grounded Down-B (Transform) phase 1.
 * @details When animation frames complete, sets callback to trigger the
 * transformation into Zelda.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

/**
 * @brief Animation update for aerial Down-B (Transform) phase 1.
 * @details When animation frames complete, sets callback to trigger the
 * transformation into Zelda.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fp->accessory4_cb = &fn_8011412C;
    }
}

/**
 * @brief Interrupt check for grounded Down-B phase 1.
 * @details Uninterruptible during transformation.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Down-B phase 1.
 * @details Uninterruptible during transformation.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics update for grounded Down-B phase 1.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Down-B phase 1.
 * @details Applies special fall gravity and air deacceleration.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_Fall(fp, attributes->x68, attributes->x6C);
    ftCommon_CalcSelfAccel_DeaccelAir(fp);
}

/**
 * @brief Collision update for grounded Down-B phase 1.
 * @details Switches to aerial state if Sheik slips off an edge.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftSk_SpecialLw_8011444C(gobj);
    }
}

/**
 * @brief Collision update for aerial Down-B phase 1.
 * @details Switches to grounded state if Sheik touches the floor.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftSk_SpecialLw_801144B8(gobj);
    }
}

/**
 * @brief State transition: Grounded -> Aerial during Down-B phase 1.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_8011444C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_GroundToAirStateChange(gobj, fp, 0x16B, ftSk_MF_SpecialLw_Coll);
    fp->accessory4_cb = fn_80114034;
}

/**
 * @brief State transition: Aerial -> Grounded during Down-B phase 1.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_801144B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_AirToGroundStateChange(gobj, fp, 0x169, ftSk_MF_SpecialLw_Coll);
    fp->accessory4_cb = fn_80114034;
}

/**
 * @brief Animation update for grounded Down-B phase 2 (reappearing as Sheik).
 * @details Transitions to Wait (idle) when animation finishes.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw2_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj); // Enter Wait / Idle
    }
}

/**
 * @brief Animation update for aerial Down-B phase 2 (reappearing as Sheik).
 * @details Transitions to Fall when animation finishes.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw2_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj); // Enter Fall state
    }
}

/**
 * @brief Interrupt check for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw2_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw2_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics update for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw2_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Down-B phase 2.
 * @details Applies special fall gravity and air deacceleration.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    ftCommon_Fall(fp, attributes->x68, attributes->x6C);
    ftCommon_CalcSelfAccel_DeaccelAir(fp);
}

/**
 * @brief Collision update for grounded Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw2_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftSk_SpecialLw_80114680(gobj);
    }
}

/**
 * @brief Collision update for aerial Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirLw2_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftSk_SpecialLw_801146EC(gobj);
    }
}

/**
 * @brief State transition: Grounded -> Aerial during Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_80114680(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_GroundToAirStateChange(gobj, fp, 0x16C, ftSk_MF_SpecialLw_Coll);
    fp->accessory4_cb = fn_801140B0;
}

/**
 * @brief State transition: Aerial -> Grounded during Down-B phase 2.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_801146EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_AirToGroundStateChange(gobj, fp, 0x16A, ftSk_MF_SpecialLw_Coll);
    fp->accessory4_cb = fn_801140B0;
}

/**
 * @brief Enters transformation completion state when switching back from Zelda
 * to Sheik.
 * @details Switches Sheik into motion state 0x16A (grounded) or 0x16C (aerial)
 * starting at frame `attributes->x70`, with the completion effect callback.
 * @param gobj Fighter game object
 */
void ftSk_SpecialLw_80114758(Fighter_GObj* gobj)
{
    s32 msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    u8 _[4];

    if (fp->ground_or_air == GA_Ground) {
        msid = 0x16A; // ftSk_MS_SpecialLw2 (grounded completion)
    } else {
        msid = 0x16C; // ftSk_MS_SpecialAirLw2 (aerial completion)
    }
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, attributes->x70, 1.0F,
                              0.0F, NULL);
    fp->accessory4_cb = fn_801140B0;
}
