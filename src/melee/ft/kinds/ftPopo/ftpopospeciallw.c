/**
 * @file ftpopospeciallw.c
 * @brief Down-B: Blizzard (Ice breath projectile stream)
 * @details Implements grounded and aerial Blizzard logic for Ice Climbers
 * (Popo/Nana). Popo/Nana channels an icy breath stream that can freeze
 * opponents and tilts with floor slopes. Module prefix: ftPp
 */

#include "ftpopospeciallw.h"

#include <melee/ft/forward.h>

#include "ftpopo.h"
#include "ftpopospecialhi.h"
#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/it/kinds/itclimbersblizzard.h>
#include <melee/lb/lb_00B0.h>

/**
 * @brief Clean up Blizzard particle effects and model tilt rotation
 * @details Destroys all active particle effects, clears the active Blizzard
 * flag (x2230_b0), clears death/damage callbacks, and resets joint 0
 * X-rotation to flat.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80122898(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(16);
    if (fp->u.pp.x2230_b0) {
        efLib_DestroyAll(gobj);
        fp = gobj->user_data;
        fp->u.pp.x2230_b0 = false;
        fp->death2_cb = NULL;
        fp->take_dmg_cb = NULL;
        ftPartSetRotX(gobj->user_data, 0, 0.0f);
    }
}

/**
 * @brief Enter grounded Down-B (Blizzard)
 * @details Initializes throw flags, cmd_vars, and motion variables for
 * Blizzard, then enters motion state ftPp_MS_SpecialLw and binds the accessory
 * callback.
 * @param gobj Fighter game object
 */
void ftPp_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->x2210.throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[3] = 0;
    fp->mv.pp.speciallw.x0 = 0;
    fp->mv.pp.speciallw.x4_b0 = false;
    Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialLw, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

/**
 * @brief Enter aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->x2210.throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[3] = 0;
    fp->mv.pp.speciallw.x0 = 0;
    fp->mv.pp.speciallw.x4_b0 = false;
    Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirLw, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

/**
 * @brief Animation callback for grounded Down-B (Blizzard)
 * @details On animation completion, removes Blizzard effects, resets rotation,
 * and returns to Wait (idle).
 * @param gobj Fighter game object
 */
void ftPp_SpecialLw_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        if (fp->u.pp.x2230_b0) {
            efLib_DestroyAll(gobj);
            fp = gobj->user_data;
            fp->u.pp.x2230_b0 = false;
            fp->death2_cb = NULL;
            fp->take_dmg_cb = NULL;
            ftPartSetRotX(gobj->user_data, 0, 0.0f);
        }
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation callback for aerial Down-B (Blizzard)
 * @details On animation completion, removes Blizzard effects, resets rotation,
 * and enters Fall state.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        if (fp->u.pp.x2230_b0) {
            efLib_DestroyAll(gobj);
            fp = gobj->user_data;
            fp->u.pp.x2230_b0 = false;
            fp->death2_cb = NULL;
            fp->take_dmg_cb = NULL;
            ftPartSetRotX(gobj->user_data, 0, 0.0f);
        }
        ftCo_Fall_Enter(gobj);
    }
}

/**
 * @brief IASA callback for grounded Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void ftPp_SpecialLw_IASA(Fighter_GObj* gobj) {}

/**
 * @brief IASA callback for aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirLw_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for grounded Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void ftPp_SpecialLw_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Set death and damage cleanup callbacks for Blizzard
 * @param gobj Fighter game object
 */
static inline void ftPp_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->death2_cb = ftPp_Init_8011F060;
    fp->take_dmg_cb = ftPp_Init_8011F060;
}

/**
 * @brief Calculate and set body tilt rotation to match ground slope
 * @details If cmd_vars[3] is set, tilts Popo along the floor normal:
 * angle = facing_dir * atan2(normal.x, normal.y). Otherwise resets to 0.
 * @param gobj Fighter game object
 */
static inline void ftPp_SpecialLw_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3]) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

/**
 * @brief Aerial-to-ground landing transition during Down-B (Blizzard)
 * @param gobj Fighter game object
 */
void fn_80122B54(Fighter_GObj* gobj)
{
    Fighter_GObj* fighter_gobj = gobj;
    Fighter* fp = gobj->user_data;
    Fighter* temp_fp;
    PAD_STACK(8);
    ftCommon_8007D7FC(fp);
    temp_fp = fp;
    Fighter_ChangeMotionState(fighter_gobj, ftPp_MS_SpecialLw, 0x0C4C5282,
                              temp_fp->cur_anim_frame, 1.0F, 0.0F, 0L);
    ftPp_set_cbs(fighter_gobj);
    ftPp_SpecialLw_Coll_inline(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

/**
 * @brief Grounded-to-air transition when slipping off a ledge during Blizzard
 * @param gobj Fighter game object
 */
static inline void ftPp_SpecialLw_Coll_Land(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftPp_MS_SpecialAirLw,
                                    ftPp_MF_SpecialLw_Coll);
    ftPp_set_cbs(gobj);
    fp->accessory4_cb = fn_80122D2C;
    ftCommon_ClampAirDrift(fp);
}

/**
 * @brief Collision callback for grounded Down-B (Blizzard)
 * @details If ground contact is lost, transitions to aerial Blizzard.
 * If grounded, updates slope tilt rotation.
 * @param gobj Fighter game object
 */
void ftPp_SpecialLw_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftPartSetRotX(fp, 0, 0.0f);
        ftPp_SpecialLw_Coll_Land(gobj);
    } else {
        ftPp_SpecialLw_Coll_inline(gobj);
    }
}

/**
 * @brief Collision callback for aerial Down-B (Blizzard)
 * @details Checks for ground contact and calls fn_80122B54 to land.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80122B54);
}

/**
 * @brief Animation accessory callback for Down-B: Blizzard
 * @details Handles Blizzard projectile spawning and particle sync:
 * - When active (x4_b0 is true): Decrements spawn timer. When it reaches 0,
 *   spawns a Blizzard particle/projectile (itClimbersBlizzard_Spawn) at Popo's
 *   mouth/hand bone offset (pos.x += da->xBC * facing_dir, pos.y += da->xC0),
 *   and resets the timer to da->xB8 frames.
 * - cmd_vars[0] == 1: Starts Blizzard emission, attaches particle effect 0x4EC
 * to joint FtPart_L4thNb, sets callbacks, and plays Popo/Nana sound effects.
 * - cmd_vars[0] == 2: Stops Blizzard emission (x4_b0 = false).
 * @param gobj Fighter game object
 */
void fn_80122D2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    PAD_STACK(8);
    if (fp->mv.pp.speciallw.x4_b0) {
        if (fp->mv.pp.speciallw.x0 == 0) {
            ftIceClimberAttributes* da = fp->dat_attrs;
            lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &pos);
            pos.x += da->xBC * fp->facing_dir;
            pos.y += da->xC0;
            itClimbersBlizzard_Spawn(gobj, &pos, fp->facing_dir);
            fp->mv.pp.speciallw.x0 = da->xB8;
        }
        fp->mv.pp.speciallw.x0--;
    }
    switch (fp->cmd_vars[0]) {
    case 1:
        // Begin frost emission, spawn sync particle effect 0x4EC
        efSync_Spawn(0x4EC, gobj, fp->parts[FtPart_L4thNb].joint);
        fp->mv.pp.speciallw.x4_b0 = true;
        fp->u.pp.x2230_b0 = true;
        ftPp_set_cbs(gobj);
        fp->cmd_vars[0] = 0;
        if (fp->kind == Ft_Kind_Popo) {
            ft_800881D8(fp, 0x1FC42, 0x7F, 0x40);
            ft_80088510(fp, 0x1FBEB, 0x7F, 0x40);
        } else {
            ft_800881D8(fp, 0x1FC0F, 0x7F, 0x40);
            ft_80088510(fp, 0x1FBEE, 0x7F, 0x40);
        }
        break;
    case 2:
        // End frost emission
        fp->mv.pp.speciallw.x4_b0 = false;
        fp->cmd_vars[0] = 0;
        break;
    }
}
