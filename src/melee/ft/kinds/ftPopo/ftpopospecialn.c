/**
 * @file ftpopospecialn.c
 * @brief Neutral-B: Ice Shot (Ice block projectile)
 * @details Implements grounded and aerial Ice Shot logic for Ice Climbers
 * (Popo/Nana). Popo summons a chunk of ice on the ground/in air, then smashes
 * it with his hammer to slide/send it forward as an active projectile. Module
 * prefix: ftPp
 */

#include "ftpopospecialn.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <melee/it/forward.h>

#include <placeholder.h>

#include "ftpopo.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itclimbersice.h>
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/gobj.h>

/* 11F500 */ static void ftPp_SpecialN_8011F500(Fighter_GObj* gobj);

/**
 * @brief Enter grounded Neutral-B (Ice Shot)
 * @details Initializes throw flags, clears cmd_vars, changes motion state to
 * 341 (ftPp_MS_SpecialN), and binds the hammer strike accessory callback.
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210.throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->u.nn.x222C = NULL;

    // Transition to grounded Ice Shot (motion state 341)
    Fighter_ChangeMotionState(gobj, 341, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

/**
 * @brief Enter aerial Neutral-B (Ice Shot)
 * @details If not previously used midair (x224C == false), gives a small
 * vertical hop (icattr->x4) and sets stall flag to prevent infinite aerial
 * stalling. Subsequent aerial uses set a negative Y offset.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirN_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* icattr = fp->dat_attrs;

    fp->x2210.throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->u.nn.x222C = NULL;

    // Aerial vertical impulse logic (stall prevention)
    if ((s32) fp->u.nn.x224C == false) {
        fp->self_vel.y = icattr->x4;
        fp->u.nn.x224C = true;
        fp->u.nn.x2250 = 0.0f;
    } else {
        fp->u.nn.x2250 = -10.0;
    }

    // Transition to aerial Ice Shot (motion state 342)
    Fighter_ChangeMotionState(gobj, 342, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &ftPp_SpecialN_8011F500;
}

/**
 * @brief Animation handler for grounded Neutral-B (Ice Shot)
 * @details Transitions to Wait state (idle) upon animation completion.
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation handler for aerial Neutral-B (Ice Shot)
 * @details Transitions to Fall state upon animation completion.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief IASA callback for grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_IASA(HSD_GObj* gobj) {}

/**
 * @brief IASA callback for aerial Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirN_IASA(HSD_GObj* gobj) {}

/**
 * @brief Physics callback for grounded Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial Neutral-B (Ice Shot)
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Collision callback for grounded Neutral-B (Ice Shot)
 * @details If Popo slips off edge into air, destroys unlaunched ice block and
 * enters Fall.
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp1 = GET_FIGHTER(gobj);
        if (fp1->u.nn.x222C != NULL) {
            Fighter* fp2;
            it_802C17DC(fp1->u.nn.x222C);
            fp2 = GET_FIGHTER(gobj);
            if (fp1->u.nn.x222C == fp2->u.nn.x222C) {
                fp2->u.nn.x222C = NULL;
                fp2->death2_cb = NULL;
                fp2->take_dmg_cb = NULL;
            }
        }
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief Collision callback for aerial Neutral-B (Ice Shot)
 * @details If landing on ground, destroys unlaunched ice block, resets air
 * stall flag, and enters LandingFallSpecial with character landing lag
 * (da->x8).
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter *fp, *fp1, *fp2;
    ftIceClimberAttributes* da;
    PAD_STACK(16);

    fp = gobj->user_data;
    da = fp->dat_attrs;
    if (ft_80081D0C(gobj) != GA_Ground) {
        fp1 = gobj->user_data;
        if (fp1->u.pp.x222C != NULL) {
            it_802C17DC(fp1->u.pp.x222C);
            fp2 = gobj->user_data;
            if (fp1->u.pp.x222C == fp2->u.pp.x222C) {
                fp2->u.pp.x222C = NULL;
                fp2->death2_cb = NULL;
                fp2->take_dmg_cb = NULL;
            }
        }
        fp->u.pp.x224C = 0;
        fp->u.pp.x2250 = 0.0f;
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x8);
    }
}

/**
 * @brief Helper to clear ice block pointer and callbacks on hammer hit
 * @param gobj Fighter game object
 * @param other_fp Fighter instance pointer
 */
static inline void inlineA0(Fighter_GObj* gobj, Fighter* other_fp)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (other_fp->u.pp.x222C == fp->u.pp.x222C) {
        fp->u.pp.x222C = NULL;
        fp->death2_cb = NULL;
        fp->take_dmg_cb = NULL;
    }
}

/**
 * @brief Animation accessory callback for Neutral-B: Ice Shot
 * @details Handles animation-driven events via cmd_vars[0]:
 * - cmd_vars[0] == 1: Spawns the ice block entity (It_Kind_IceClimber_Ice) in
 * front of Popo at position (da->xC * facing_dir, da->x10 + y_offset). Sets
 * death and damage cleanup callbacks.
 * - cmd_vars[0] == 2: Hammer strikes the ice block (it_802C16F8), launching it
 * as a projectile. Plays Popo/Nana voice clip and hammer strike SFX (130024).
 * Clears active reference.
 * @param gobj Fighter game object
 */
void ftPp_SpecialN_8011F500(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 cmd_var0 = fp->cmd_vars[0];

    if (cmd_var0 == 0) {
        return;
    }
    if (cmd_var0 == 1) {
        // Spawn ice block projectile in front of fighter
        ftIceClimberAttributes* da = fp->dat_attrs;
        Vec3 pos;
        PAD_STACK(4 * 2);
        lb_8000B1CC(fp->parts[0].joint, NULL, &pos);
        pos.x = da->xC * fp->facing_dir + pos.x;
        pos.y += da->x10 + fp->u.pp.x2250;
        fp->u.pp.x222C =
            it_802C1590(gobj, &pos, It_Kind_IceClimber_Ice, fp->facing_dir);
        ft_PlaySFX(fp, 130021, 127, 64);
        if (fp->u.pp.x222C != NULL) {
            fp->death2_cb = ftPp_Init_8011F060;
            fp->take_dmg_cb = ftPp_Init_8011F060;
        }
        fp->cmd_vars[0] = 0;
    } else if (cmd_var0 == 2) {
        // Strike ice block with hammer to propel it forward
        if (fp->u.pp.x222C != NULL) {
            it_802C16F8(fp->u.pp.x222C);
            fp->cmd_vars[0] = 0;
            if (fp->kind == Ft_Kind_Popo) {
                ft_800881D8(fp, 130141, 127, 64);
            } else {
                ft_800881D8(fp, 130090, 127, 64);
            }
            ft_PlaySFX(fp, 130024, 127, 64);
            inlineA0(gobj, fp);
        }
    }
}
