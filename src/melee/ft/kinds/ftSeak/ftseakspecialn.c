/**
 * @file ftseakspecialn.c
 * @brief Sheik's Neutral-B move: Needle Storm.
 * @details Implements Sheik's grounded and aerial Neutral-B projectile move
 * (Needle Storm), including charging loop (storing up to 6 needles), shield
 * and air-dodge cancellation, and rapid needle projectile firing with vertical
 * trajectory dispersion. Module prefix: ftSk (Fighter: Sheik)
 */

#include "ftseakspecialn.h"

#include <melee/ft/forward.h>

#include "forward.h"
#include "ftseak.h"
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcolanim.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/it/kinds/itseakneedleheld.h>
#include <melee/it/kinds/itseakneedlethrown.h>
#include <sysdolphin/baselib/random.h>

/* 1120D4 */ static void ftSk_SpecialN_801120D4(Fighter_GObj* gobj);
/* 112D44 */ static void shootNeedles(Fighter_GObj* gobj);

/// Vertical position scale offsets for needle projectile scatter (9 possible
/// offsets)
static float needleYPosScale[] = {
    -1, -0.75f, -0.5f, -0.25f, 0, +0.25f, +0.5f, +0.75f, +1,
};

/**
 * @brief Cleans up and destroys or drops held needles when damaged or killed.
 * @details Fires off any charged needles with no velocity and clears the held
 * needle item.
 * @param gobj Fighter game object
 */
void ftSk_SpecialN_80111FBC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    if (fp->u.sk.x4 != NULL) {
        fp->u.sk.x4 = NULL;
        // Drop all currently charged needles
        while (fp->u.sk.x0 != 0) {
            Vec3 pos = fp->cur_pos;
            PAD_STACK(4 * 1);
            {
                float y_scale;
                if (fp->ground_or_air == GA_Ground) {
                    y_scale = da->x4;
                } else {
                    y_scale = da->xC;
                }
                pos.y += fp->x34_scale.y * y_scale;
            }
            pos.z = 0;
            {
                Item_GObj* item_gobj = it_802AFD8C(
                    gobj, &pos, It_Kind_Seak_NeedleThrow, fp->facing_dir);
                if (item_gobj != NULL) {
                    it_802AFEA8(item_gobj, gobj, 1);
                }
            }
            --fp->u.sk.x0;
        }
        if (fp->death2_cb == ftSk_Init_80110198 ||
            fp->take_dmg_cb == ftSk_Init_80110198)
        {
            ftSk_SpecialN_801120D4(gobj);
        }
    }
    fp->u.sk.x0 = 0; // Reset needle count to 0
}

/**
 * @brief Clears damage and death callbacks set during needle charging.
 * @param gobj Fighter game object
 */
void ftSk_SpecialN_801120D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
}

/**
 * @brief Helper entering grounded or aerial Needle Storm startup.
 * @param gobj Fighter game object
 * @param msid Motion state identifier (ftSk_MS_SpecialNStart or
 * ftSk_MS_SpecialAirNStart)
 */
static inline void doEnter(Fighter_GObj* gobj, ftSeak_MotionState msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    fp->x2210.x0.throw_flags_b0 = false;
    Fighter_ClearCmdVars(fp);
    fp->mv.sk.specialn.x0 = 0;
    // If no needles stored yet, start charging at 1
    if (fp->u.sk.x0 == 0) {
        fp->u.sk.x0 = 1;
    }
    fp->mv.sk.specialn.x4 = 0;
    fp->mv.sk.specialn.x8 = 0;
    Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Enters grounded Neutral-B (Needle Storm) startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftSk_MS_SpecialNStart);
}

/**
 * @brief Enters aerial Neutral-B (Needle Storm) startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    doEnter(gobj, ftSk_MS_SpecialAirNStart);
}

/**
 * @brief Animation update for grounded Neutral-B startup.
 * @details Spawns the held needle item entity and enters the charging loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // Spawn held needle model in Sheik's hand
        fp->u.sk.x4 = it_802B19AC(gobj, &fp->cur_pos, 23,
                                  It_Kind_Seak_NeedleHeld, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialNLoop, Ft_MF_None, 0, 1,
                                  0, NULL);
        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    }
}

/**
 * @brief Animation update for grounded Neutral-B charging loop.
 * @details Increments needle charge count up to a maximum of 6 needles.
 * Plays charging SFX and triggers full charge flash when max is reached.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.sk.specialn.x8) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64); // Needle charge sound effect
    }
    }
    ++fp->mv.sk.specialn.x8;
    // Each completed loop charges 1 additional needle
    if (fp->cur_anim_frame == 0) {
        ++fp->u.sk.x0;
        fp->mv.sk.specialn.x8 = 0;
        // Maximum needle capacity is 6
        if (fp->u.sk.x0 > 6) {
            fp->u.sk.x0 = 6;
            fp->mv.sk.specialn.x8 = 100;
            ftCo_800BFFD0(fp, 86, 0); // Full charge visual flash
        }
    }
}

/**
 * @brief Animation update for grounded Neutral-B shield cancel.
 * @details Clears held needle display and returns to Wait (idle) when
 * animation ends.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.sk.x4 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Enter Wait / Idle
    }
}

/**
 * @brief Animation update for grounded Neutral-B needle throwing.
 * @details Sets firing flag at specific cadence frames (2, 5, 8, 11, 14, 17)
 * to shoot needles.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 8);
    // Fire needle on specific frame cadence
    switch (fp->mv.sk.specialn.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.sk.specialn.x4 = true; // Signal needle shot
        fp->u.sk.x4 = NULL;
    }
    ++fp->mv.sk.specialn.x0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Enter Wait / Idle
    }
}

/**
 * @brief Animation update for aerial Neutral-B startup.
 * @details Spawns held needle item and enters aerial charging loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->u.sk.x4 = it_802B19AC(gobj, &fp->cur_pos, 23,
                                  It_Kind_Seak_NeedleHeld, fp->facing_dir);
        Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirNLoop, Ft_MF_None, 0,
                                  1, 0, NULL);
        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    }
}

/**
 * @brief Animation update for aerial Neutral-B charging loop.
 * @details Charges up to 6 needles in the air.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->mv.sk.specialn.x8) {
    case 0: {
        Fighter* fp = GET_FIGHTER(gobj);
        ft_PlaySFX(fp, 270134, 127, 64);
    }
    }
    ++fp->mv.sk.specialn.x8;
    if (fp->cur_anim_frame == 0) {
        ++fp->u.sk.x0;
        fp->mv.sk.specialn.x8 = 0;
        if (fp->u.sk.x0 > 6) {
            fp->u.sk.x0 = 6;
            fp->mv.sk.specialn.x8 = 100;
            ftCo_800BFFD0(fp, 86, 0); // Full charge visual flash
        }
    }
}

/**
 * @brief Animation update for aerial Neutral-B cancel (air dodge / cancel).
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNCancel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    fp->u.sk.x4 = 0;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

/**
 * @brief Animation update for aerial Neutral-B needle throwing.
 * @details Fires needles on frames 2, 5, 8, 11, 14, 17 and enters Fall on
 * completion.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;

    PAD_STACK(4 * 8);

    switch (fp->mv.sk.specialn.x0) {
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        fp->mv.sk.specialn.x4 = true;
        fp->u.sk.x4 = NULL;
    }

    ++fp->mv.sk.specialn.x0;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

/**
 * @brief Interrupt check for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNStart_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Common IASA check during needle charging.
 * @details If B button is released, begins throwing needles (end_msid);
 * if L or R trigger is pressed, cancels charging into shield/dodge
 * (cancel_msid).
 * @param gobj Fighter game object
 * @param end_msid Motion state to enter on B release (firing needles)
 * @param cancel_msid Motion state to enter on L/R press (canceling charge)
 */
static void doIasa(Fighter_GObj* gobj, ftSeak_MotionState end_msid,
                   ftSeak_MotionState cancel_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    // B button released -> throw needles
    if (!(fp->input.held_buttons[0] & HSD_PAD_B)) {
        fp->mv.sk.specialn.x0 = 0;
        Fighter_ChangeMotionState(gobj, end_msid, Ft_MF_None, 0, 1, 0, NULL);
        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
        fp->accessory4_cb = shootNeedles;
        // L or R pressed -> shield cancel
    } else if (fp->input.pressed_buttons & HSD_PAD_LR) {
        Fighter_ChangeMotionState(gobj, cancel_msid, Ft_MF_None, 0, 1, 0,
                                  NULL);
        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    }
}

/**
 * @brief Interrupt check for grounded Neutral-B charging loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNLoop_IASA(Fighter_GObj* gobj)
{
    doIasa(gobj, ftSk_MS_SpecialNEnd, ftSk_MS_SpecialNCancel);
}

/**
 * @brief Interrupt check for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNCancel_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNEnd_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNStart_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Neutral-B charging loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    doIasa(gobj, ftSk_MS_SpecialAirNEnd, ftSk_MS_SpecialAirNCancel);
}

/**
 * @brief Interrupt check for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNCancel_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics update for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for grounded Neutral-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Physics update for aerial Neutral-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Physics update for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Physics update for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Collision update for grounded Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNStart_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_GroundToAirStateChange(gobj, fp, ftSk_MS_SpecialAirNStart,
                                        mf);

        {
            Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
        }
    }
}

/**
 * @brief Collision update for grounded Neutral-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNLoop_Coll(Fighter_GObj* gobj)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_GroundToAirStateChange(gobj, fp, ftSk_MS_SpecialAirNLoop, mf);

        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    }
}

/**
 * @brief Collision update for grounded Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    PAD_STACK(4 * 2);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter_SetDamageCallback(gobj, NULL);
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1, da->x10);
        }
    }
}

/**
 * @brief Collision update for grounded Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter_SetDamageCallback(gobj, NULL);
        fp->u.sk.x0 = 0;
        fp->mv.sk.specialn.x4 = false;
        if (da->x10 == 0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1, da->x10);
        }
    }
}

/**
 * @brief Common aerial-to-ground collision handler for needle charging.
 * @param gobj Fighter game object
 * @param msid Target grounded motion state
 */
static inline void doColl(Fighter_GObj* gobj, ftSeak_MotionState msid)
{
    /// @todo Named flags.
    static u32 const mf = (1 << 7) | (1 << 12) | (1 << 14) | (1 << 18) |
                          (1 << 19) | (1 << 22) | (1 << 26) | (1 << 27);
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_AirToGroundStateChange(gobj, fp, msid, mf);
        Fighter_SetDamageCallback(gobj, ftSk_Init_80110198);
    }
}

/**
 * @brief Collision update for aerial Neutral-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    doColl(gobj, ftSk_MS_SpecialNStart);
}

/**
 * @brief Collision update for aerial Neutral-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    doColl(gobj, ftSk_MS_SpecialNLoop);
}

/**
 * @brief Collision update for aerial Neutral-B cancel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNCancel_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_Landing_Enter_Basic(gobj);
        Fighter_SetDamageCallback(gobj, NULL);
    }
}

/**
 * @brief Collision update for aerial Neutral-B throw.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) != GA_Ground) {
        Fighter_SetDamageCallback(gobj, NULL);
        fp->u.sk.x0 = 0;
        fp->mv.sk.specialn.x4 = false;
        ftCo_Landing_Enter_Basic(gobj);
    }
}

/**
 * @brief Spawns and fires a single needle projectile item.
 * @details Spawns `It_Kind_Seak_NeedleThrow` entity, applies vertical random
 * scatter from `needleYPosScale`, decrements needle counter `fp->u.sk.x0`,
 * spawns needle flash effect 1283, and plays firing SFX 270140.
 * @param gobj Fighter game object
 */
void shootNeedles(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSeakAttributes* da = fp->dat_attrs;

    if (fp->mv.sk.specialn.x4) {
        fp->mv.sk.specialn.x4 = false;

        if (fp->u.sk.x0 > 0) {
            Vec3 pos = fp->cur_pos;
            float x_scale, y_scale;
            int scatter_idx;
            if (fp->ground_or_air == GA_Ground) {
                x_scale = da->x0 * fp->facing_dir;
                pos.x += fp->x34_scale.y * x_scale;
                scatter_idx = HSD_Randi(9);
                y_scale = da->x4 + needleYPosScale[scatter_idx];
                pos.y += fp->x34_scale.y * y_scale;
            } else {
                x_scale = da->x8 * fp->facing_dir;
                pos.x += fp->x34_scale.y * x_scale;
                scatter_idx = HSD_Randi(9);
                y_scale = (2.0f * needleYPosScale[scatter_idx]) + da->xC;
                pos.y += fp->x34_scale.y * y_scale;
            }
            pos.z = 0;

            // Spawn and launch needle projectile
            {
                Item_GObj* item_gobj = it_802AFD8C(
                    gobj, &pos, It_Kind_Seak_NeedleThrow, fp->facing_dir);
                if (item_gobj != NULL) {
                    it_802AFEA8(item_gobj, gobj, 0);
                }
            }

            --fp->u.sk.x0; // Decrement stored needles

            efSync_Spawn(1283, gobj, &pos);  // Needle fire muzzle flash
            ft_PlaySFX(fp, 270140, 127, 64); // Needle release sound effect
        }
    }
}
