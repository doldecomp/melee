/**
 * @file ftpopospecials.c
 * @brief Side-B: Squall Hammer (Tornado spinning hammer attack)
 * @details Implements grounded and aerial Squall Hammer move logic for Ice
 * Climbers (Popo/Nana). Popo and Nana spin rapidly with hammers outstretched,
 * moving forward with player-steered horizontal drift. Rapidly pressing the B
 * button allows the Ice Climbers to gain vertical height. Module prefix: ftPp
 */

#include "ftpopospecials.h"

#include <math.h>

#include "ftpopo.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/kinds/ftNana/ftnana.h>
#include <melee/pl/player.h>

/**
 * @brief Unlink partner's cross-reference pointer and clear mutual flags
 * @param fp Fighter instance pointer
 */
static inline void setRefGObjFlagAndClear(Fighter* fp)
{
    Fighter_GObj* partner_gobj = fp->x1A5C;
    Fighter* partner_fp;

    if (partner_gobj != NULL) {
        partner_fp = partner_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(partner_gobj);
        partner_fp->x1A5C = NULL;
    }
    fp->x1A5C = NULL;
}

/**
 * @brief Reset rotation and unlink partner when Squall Hammer ends or is
 * interrupted
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_8011F68C(Fighter_GObj* gobj)
{
    Fighter* fp;
    u8 _[16];

    fp = gobj->user_data;
    ftPartSetRotX(fp, 0, 0);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    setRefGObjFlagAndClear(fp);
}

/**
 * @brief Check partner's command var 1 state
 * @param gobj Fighter game object
 * @return True if partner is valid and finished
 */
bool ftPp_SpecialS_8011F6FC(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp != NULL) {
            return fp->cmd_vars[1];
        }
    }

    return true;
}

/**
 * @brief Update hammer head joint visibility and slope tilt rotation
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_8011F720(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* root_jobj;
    HSD_JObj* child_jobj;
    f32 angle;
    HSD_GObj* hammer_gobj;

    fp = GET_FIGHTER(gobj);
    if (fp->mv.pp.specials.x8 != NULL) {
        if (fp->x2219_b0 && fp->mv.pp.specials.x8 != NULL) {
            hammer_gobj = fp->mv.pp.specials.x8->x4;
            if (hammer_gobj != NULL) {
                child_jobj =
                    HSD_JObjGetNext(HSD_JObjGetChild(GET_JOBJ(hammer_gobj)));
                root_jobj = hammer_gobj->hsd_obj;
                if (fp->motion_id == ftPp_MS_SpecialS1 ||
                    fp->motion_id == ftPp_MS_SpecialS2)
                {
                    HSD_JObjClearFlagsAll(child_jobj, JOBJ_HIDDEN);
                } else {
                    HSD_JObjSetFlagsAll(child_jobj, JOBJ_HIDDEN);
                }
                if (fp->cmd_vars[3] != 0 && fp->mv.pp.specials.xC != 0) {
                    // Match floor slope normal angle
                    angle = -atan2f(fp->coll_data.floor.normal.x,
                                    fp->coll_data.floor.normal.y);
                    HSD_JObjSetRotationZ(root_jobj, angle);
                } else {
                    HSD_JObjSetRotationZ(root_jobj, 0.0F);
                }
                Fighter_SetEffectHitlagCallbacks(fp);
                return;
            }
        }
        fp->mv.pp.specials.x8 = 0;
        fp->x2219_b0 = false;
        fp->pre_hitlag_cb = NULL;
        fp->post_hitlag_cb = NULL;
    }
}

/**
 * @brief Test if current state is solo vs paired Squall Hammer
 * @param gobj Fighter game object
 * @return False if paired (ftPp_MS_SpecialS2 / ftPp_MS_SpecialAirS2), true
 * otherwise
 */
bool ftPp_SpecialS_8011F964(Fighter_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->motion_id) {
    case ftPp_MS_SpecialS2:
    case ftPp_MS_SpecialAirS2:
        return false;
    }
    return true;
}

/**
 * @brief Setup damage and death cleanup callbacks for Squall Hammer
 * @param gobj Fighter game object
 */
static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftPp_Init_8011F060;
    fp->death2_cb = ftPp_Init_8011F060;
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Setup hammer subpart and hitlag callbacks
 * @param gobj Fighter game object
 */
static inline void inlineA1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pp.specials.x8 = 0;
    fp->x2219_b0 = true;
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Setup state and parameters for grounded Squall Hammer
 * @details Checks partner availability; enters solo (SpecialS1) or paired
 * (SpecialS2) state.
 * @param gobj Fighter game object
 */
static inline void inlineA2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_ClearCmdVars(fp);
    fp->mv.pp.specials.x0 = 0;
    fp->mv.pp.specials.x4 = 10;
    fp->mv.pp.specials.xC = 0;
    fp->mv.pp.specials.x8 = 0;
    fp->mv.pp.specials.x10 = 0;
    fp->mv.pp.specials.x14 = da->x68;
    fp->mv.pp.specials.x18 = 0;
    fp->mv.pp.specials.x1C = 0;
    if (ftNn_Init_80123954(Player_GetEntityAtIndex(fp->player_idx, 1),
                           fp->ground_or_air) == GA_Air)
    {
        // Solo Squall Hammer (grounded)
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialS1, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->x1A5C = NULL;
    } else {
        // Paired Squall Hammer with partner Nana (grounded)
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialS2, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->x1A5C = Player_GetEntityAtIndex(fp->player_idx, 1);
    }
    fp->self_vel.y = 0;
    {
        float x_vel = da->x28 * fp->facing_dir;
        fp->self_vel.x = x_vel;
        fp->gr_vel = x_vel;
    }
}

/**
 * @brief Enter grounded Side-B: Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_Enter(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    inlineA2(gobj);
    inlineA0(gobj);
    ftAnim_8006EBA4(gobj);
    inlineA1(gobj);
    inlineA0(gobj);
}

/**
 * @brief Setup state and parameters for aerial Squall Hammer
 * @param gobj Fighter game object
 */
static inline void inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_ClearCmdVars(fp);
    fp->mv.pp.specials.x0 = 0;
    fp->mv.pp.specials.x4 = 10;
    fp->mv.pp.specials.xC = 0;
    fp->mv.pp.specials.x8 = 0;
    fp->mv.pp.specials.x10 = 0;
    fp->mv.pp.specials.x14 = da->x68;
    fp->mv.pp.specials.x18 = 0;
    fp->mv.pp.specials.x1C = 0;
    if (ftNn_Init_80123954(Player_GetEntityAtIndex(fp->player_idx, 1),
                           fp->ground_or_air) == GA_Air)
    {
        // Solo Squall Hammer (aerial)
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS1, Ft_MF_None, 0, 1,
                                  0, NULL);
        fp->x1A5C = NULL;
        fp->self_vel.y = da->x20;
    } else {
        // Paired Squall Hammer with partner Nana (aerial)
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS2, Ft_MF_None, 0, 1,
                                  0, NULL);
        fp->x1A5C = Player_GetEntityAtIndex(fp->player_idx, 1);
        fp->self_vel.y = da->x24;
    }
    fp->self_vel.x = da->x2C * fp->facing_dir;
}

/**
 * @brief Enter aerial Side-B: Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    inlineB0(gobj);
    inlineA0(gobj);
    ftAnim_8006EBA4(gobj);
    inlineA1(gobj);
    inlineA0(gobj);
}

/**
 * @brief Reset callbacks and return to Wait on animation completion
 * @param gobj Fighter game object
 */
static inline void resetAnim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
    fp->pre_hitlag_cb = NULL;
    fp->post_hitlag_cb = NULL;
    fp->x1A5C = NULL;
    ft_8008A2BC(gobj);
}

/**
 * @brief Animation callback for grounded solo Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialS1_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(4 * 2);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        resetAnim(gobj);
    }
}

/**
 * @brief Helper to clear partner flags and unlink partner reference
 * @param gobj Fighter game object
 */
static inline void inlineC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    fp->x1A5C = NULL;
}

/**
 * @brief Reset rotation, notify partner, and transition to Wait
 * @param gobj Fighter game object
 */
static inline void inlineC1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, 0, 0);
    Fighter_UnkSetFlag_8006CFBC(gobj);

    if (fp->x1A5C != NULL) {
        inlineC0(fp->x1A5C);
    }
    fp->x1A5C = NULL;
    resetAnim(gobj);
}

/**
 * @brief Animation callback for grounded paired Squall Hammer
 * @details Ends when animation finishes or partner Nana's move completes
 * early.
 * @param gobj Fighter game object
 */
void ftPp_SpecialS2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* nn_gobj = Player_GetEntityAtIndex(fp->player_idx, 1);
    PAD_STACK(4 * 2);
    if (!ftAnim_IsFramesRemaining(gobj) || ftNn_Init_80123B10(nn_gobj)) {
        inlineC1(gobj);
    }
}

/**
 * @brief Clear callbacks and partner reference on aerial move end
 * @param gobj Fighter game object
 */
static inline void inline0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = NULL;
    fp->death2_cb = NULL;
    fp->pre_hitlag_cb = NULL;
    fp->post_hitlag_cb = NULL;
    fp->x1A5C = NULL;
}

/**
 * @brief Animation callback for aerial solo Squall Hammer
 * @details Transitions to Fall or Special Fall based on attribute da->x70.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        inline0(gobj);
        if (da->x70 == 0.0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCommon_8007D60C(fp);
            ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->x70);
        }
    }
}

/**
 * @brief Reset tilt rotation and clear partner flags on aerial end
 * @param gobj Fighter game object
 */
static inline void inline1(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPartSetRotX(fp, 0, 0.0F);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    setRefGObjFlagAndClear(fp);
}

/**
 * @brief Animation callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* nana_gobj = Player_GetEntityAtIndex(fp->player_idx, 1);
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj) || ftNn_Init_80123B10(nana_gobj)) {
        inline1(gobj);
        inline0(gobj);
        if (da->x70 == 0.0) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCommon_8007D60C(fp);
            ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->x70);
        }
    }
}

/**
 * @brief IASA steering input callback for grounded solo Squall Hammer
 * @details Reads analog stick X: if outside deadzone da->x40, applies steering
 * factor da->x30.
 * @param gobj Fighter game object
 */
void ftPp_SpecialS1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (ABS(fp->input.lstick[0].x) >= da->x40) {
        fp->mv.pp.specials.x1C = fp->input.lstick[0].x * da->x30;
    } else {
        fp->mv.pp.specials.x1C = 0.0F;
    }
}

/**
 * @brief IASA steering input callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialS2_IASA(Fighter_GObj* gobj)
{
    ftPp_SpecialS1_IASA(gobj);
}

/**
 * @brief IASA steering input callback for aerial solo Squall Hammer
 * @details Reads analog stick X: if outside deadzone da->x40, applies aerial
 * steering factor da->x34.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (ABS(fp->input.lstick[0].x) >= da->x40) {
        fp->mv.pp.specials.x1C = fp->input.lstick[0].x * da->x34;
    } else {
        fp->mv.pp.specials.x1C = 0.0F;
    }
}

/**
 * @brief IASA steering input callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS2_IASA(Fighter_GObj* gobj)
{
    ftPp_SpecialAirS1_IASA(gobj);
}

/**
 * @brief Physics callback for grounded solo Squall Hammer
 * @details Computes horizontal steering acceleration, slope push, friction,
 * and processes B-button mashing to take off into the air!
 * @param gobj Fighter game object
 */
void ftPp_SpecialS1_Phys(Fighter_GObj* gobj)
{
    ftIceClimberAttributes* attrs;
    Fighter* fighter;
    Fighter* fp;
    Fighter* fighter_fp;
    Fighter* fighter_fp2;
    f32 temp_f1;
    f32 target_vel;
    ftIceClimberAttributes* icattr;

    PAD_STACK(0x18);

    fp = GET_FIGHTER(gobj);
    icattr = fp->dat_attrs;
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        target_vel =
            fp->mv.pp.specials.x1C > 0.0F ? icattr->x38 : -icattr->x38;
        ftCommon_CalcGroundAccel_AccelToVel(fp, fp->mv.pp.specials.x1C,
                                            target_vel,
                                            fp->co_attrs.ground_friction);
        fighter_fp = GET_FIGHTER(gobj);
        {
            ftIceClimberAttributes* da = fighter_fp->dat_attrs;
            fighter_fp->xE4_ground_accel_1 +=
                da->x6C * fighter_fp->coll_data.floor.normal.x;
        }
        ftCommon_ClampGroundVel(fp, icattr->x38);
        ftCommon_SetSelfMovementFromGroundedMovement_NoFriction(gobj);
    } else {
        float friction = fp->co_attrs.ground_friction;
        ftCommon_CalcGroundAccel_Deaccel(fp, friction);
        ftCommon_ClampGroundVel(fp, icattr->x38);
        ftCommon_SetSelfMovementFromGroundedMovement_NoFriction(gobj);
    }
    fp->mv.pp.specials.x14 += 1;
    // B-button mash detection
    if (fp->cmd_vars[2] != 0 && (fp->input.pressed_buttons & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    // Launch into air when mashed sufficiently
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > icattr->x68) {
        fighter = GET_FIGHTER(gobj);
        attrs = fighter->dat_attrs;
        ftCommon_8007D5D4(fighter);
        fighter->x74_self_accel.x = fighter->xE4_ground_accel_1;
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS1, 0x0C4C528A,
                                  fighter->cur_anim_frame, 1.0F, 0.0F, NULL);
        fighter_fp2 = GET_FIGHTER(gobj);
        fighter_fp2->take_dmg_cb = ftPp_Init_8011F060;
        fighter_fp2->death2_cb = ftPp_Init_8011F060;
        Fighter_SetEffectHitlagCallbacks(fighter_fp2);
        ftCommon_ClampSelfVelX(fighter, attrs->x3C);
        fp->self_vel.y += icattr->x60;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
}

/**
 * @brief Physics callback for grounded paired Squall Hammer
 * @details Computes steering velocity, friction, and paired B-button mash
 * upward lift (da->x64).
 * @param gobj Fighter game object
 */
void ftPp_SpecialS2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftIceClimberAttributes* icattr;
    ftIceClimberAttributes* attrs;
    Fighter* fighter;
    Fighter* fighter_fp;
    Fighter* fighter_fp2;
    f32 temp_f1;
    f32 target_vel;

    PAD_STACK(0x18);

    fp = GET_FIGHTER(gobj);
    icattr = fp->dat_attrs;
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        target_vel =
            fp->mv.pp.specials.x1C > 0.0F ? icattr->x38 : -icattr->x38;
        ftCommon_CalcGroundAccel_AccelToVel(fp, fp->mv.pp.specials.x1C,
                                            target_vel,
                                            fp->co_attrs.ground_friction);
        fighter_fp = GET_FIGHTER(gobj);
        {
            ftIceClimberAttributes* da = fighter_fp->dat_attrs;
            fighter_fp->xE4_ground_accel_1 +=
                da->x6C * fighter_fp->coll_data.floor.normal.x;
        }
        ftCommon_ClampGroundVel(fp, icattr->x38);
        ftCommon_SetSelfMovementFromGroundedMovement_NoFriction(gobj);
    } else {
        float friction = fp->co_attrs.ground_friction;
        ftCommon_CalcGroundAccel_Deaccel(fp, friction);
        ftCommon_ClampGroundVel(fp, icattr->x38);
        ftCommon_SetSelfMovementFromGroundedMovement_NoFriction(gobj);
    }
    fp->mv.pp.specials.x14 += 1;
    // B-button mash detection
    if ((fp->cmd_vars[2] != 0) && (fp->input.pressed_buttons & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    // Launch into air when mashed
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > icattr->x68) {
        fighter = GET_FIGHTER(gobj);
        attrs = fighter->dat_attrs;
        ftCommon_8007D5D4(fighter);
        fighter->x74_self_accel.x = fighter->xE4_ground_accel_1;
        Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirS2, 0xC4C528A,
                                  fighter->cur_anim_frame, 1.0F, 0.0F, NULL);
        fighter_fp2 = GET_FIGHTER(gobj);
        fighter_fp2->take_dmg_cb = ftPp_Init_8011F060;
        fighter_fp2->death2_cb = ftPp_Init_8011F060;
        Fighter_SetEffectHitlagCallbacks(fighter_fp2);
        ftCommon_ClampSelfVelX(fighter, attrs->x3C);
        fp->self_vel.y += icattr->x64;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
}

/**
 * @brief Physics callback for aerial solo Squall Hammer
 * @details Applies B-press rise boost (da->x60), custom gravity/fall, and
 * aerial drift.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.pp.specials.x14 += 1;
    // B-button mash height gain
    if (fp->cmd_vars[2] != 0 && (fp->input.pressed_buttons & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > da->x68) {
        fp->self_vel.y += da->x60;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
    // Custom gravity during initial window (da->x5C frames)
    if (fp->mv.pp.specials.x18 < da->x5C) {
        ftCommon_Fall(fp, da->x4C_gravity, da->x54_terminal_vel);
    } else {
        ftCommon_FallBasic(fp);
    }
    // Horizontal drift steering
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        f32 target_vel = fp->mv.pp.specials.x1C > 0.0F ? da->x3C : -da->x3C;
        ftCommon_CalcSelfAccel_AccelToVel(fp, fp->mv.pp.specials.x1C,
                                          target_vel, 0.0F);
    } else {
        ftCommon_CalcSelfAccel_DeaccelAir(fp);
    }
}

/**
 * @brief Physics callback for aerial paired Squall Hammer
 * @details Applies paired B-press rise boost (da->x64), paired gravity, and
 * drift.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);

    fp->mv.pp.specials.x14 += 1;
    // Paired B-button mash height gain
    if (fp->cmd_vars[2] != 0 && (fp->input.pressed_buttons & HSD_PAD_B)) {
        fp->mv.pp.specials.x10 += 1;
    }
    if (fp->mv.pp.specials.x10 != 0 && fp->mv.pp.specials.x14 > da->x68) {
        fp->self_vel.y += da->x64;
        fp->mv.pp.specials.x10 = 0;
        fp->mv.pp.specials.x14 = 0;
    }
    fp->mv.pp.specials.x18 += 1;
    // Custom paired gravity
    if (fp->mv.pp.specials.x18 < da->x5C) {
        ftCommon_Fall(fp, da->x50_gravity, da->x58_terminal_vel);
    } else {
        ftCommon_FallBasic(fp);
    }
    // Paired aerial drift steering
    if (fp->cmd_vars[0] == 0 && fp->mv.pp.specials.x1C != 0.0F) {
        f32 target_vel = fp->mv.pp.specials.x1C > 0.0F ? da->x3C : -da->x3C;
        ftCommon_CalcSelfAccel_AccelToVel(fp, fp->mv.pp.specials.x1C,
                                          target_vel, 0.0F);
    } else {
        ftCommon_CalcSelfAccel_DeaccelAir(fp);
    }
}

static ftCollisionBox ftNn_Init_803CD820 = {
    12, 0, -6, 6, 6, 6,
};

/**
 * @brief Update joint tilt rotation for ground slope alignment
 * @param gobj Fighter game object
 */
static inline void inline2(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3] != 0 && fp->mv.pp.specials.xC != 0) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

/**
 * @brief Transition from grounded to aerial Squall Hammer when slipping off
 * ledge
 * @param gobj Fighter game object
 * @param msid Target motion state ID
 */
static inline void inline3(Fighter_GObj* gobj, int msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* icattr = fp->dat_attrs;
    ftCommon_8007D5D4(fp);
    fp->x74_self_accel.x = fp->xE4_ground_accel_1;
    Fighter_ChangeMotionState(gobj, msid, 0xC4C528A, fp->cur_anim_frame, 1.0F,
                              0.0F, NULL);
    inlineA0(gobj);
    ftCommon_ClampSelfVelX(fp, icattr->x3C);
}

/**
 * @brief Collision callback for grounded solo Squall Hammer
 * @details Handles wall bouncing: reflects velocity by -da->x44 if above
 * threshold da->x48.
 * @param gobj Fighter game object
 */
void ftPp_SpecialS1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool is_grounded = ft_80082888(gobj, &ftNn_Init_803CD820);
    bool hit_wall = false;
    PAD_STACK(0x10);
    if (fp->gr_vel != 0.0F) {
        if (fp->gr_vel > 0.0F) {
            hit_wall = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            hit_wall = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    // Wall bounce reflection
    if (hit_wall) {
        if (ABS(fp->gr_vel) < da->x48) {
            fp->gr_vel = fp->gr_vel > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->gr_vel *= -da->x44;
        }
    }
    if (!is_grounded) {
        inline3(gobj, ftPp_MS_SpecialAirS1);
        fp->mv.pp.specials.xC = 0;
    } else {
        fp->mv.pp.specials.xC = 1;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

/**
 * @brief Collision callback for grounded paired Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialS2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool is_grounded = ft_80082888(gobj, &ftNn_Init_803CD820);
    bool hit_wall = false;
    PAD_STACK(0x10);
    if (fp->gr_vel != 0.0F) {
        if (fp->gr_vel > 0.0F) {
            hit_wall = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            hit_wall = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    // Paired wall bounce reflection
    if (hit_wall) {
        if (ABS(fp->gr_vel) < da->x48) {
            fp->gr_vel = fp->gr_vel > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->gr_vel *= -da->x44;
        }
    }
    if (!is_grounded) {
        inline3(gobj, ftPp_MS_SpecialAirS2);
        fp->mv.pp.specials.xC = 0;
    } else {
        fp->mv.pp.specials.xC = 1;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

/**
 * @brief Transition from aerial to grounded Squall Hammer upon landing
 * @param gobj Fighter game object
 * @param msid Target grounded motion state ID
 */
static inline void inline4(Fighter_GObj* gobj, int msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCommon_AirToGroundStateChange(gobj, fp, msid, ftPp_MF_SpecialS_Coll);
    inlineA0(gobj);
    fp->x74_self_accel.y = 0.0F;
    fp->self_vel.y = 0.0F;
    ftCommon_ClampGroundVel(fp, da->x38);
}

/**
 * @brief Collision callback for aerial solo Squall Hammer
 * @details Detects ceiling, wall bounce reflection, and landing.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool is_grounded;
    bool hit_wall;
    PAD_STACK(0x18);

    is_grounded = ft_800824A0(gobj, &ftNn_Init_803CD820);
    if ((fp->coll_data.env_flags & Collide_CeilingMask) == 1) {
        fp->self_vel.y = 0.0F;
    }
    hit_wall = false;
    if (fp->self_vel.x != 0.0F) {
        if (fp->self_vel.x > 0.0F) {
            hit_wall = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            hit_wall = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    // Aerial wall bounce reflection
    if (hit_wall) {
        if (ABS(fp->self_vel.x) < da->x48) {
            fp->self_vel.x = fp->self_vel.x > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->self_vel.x *= -da->x44;
        }
    }
    if (is_grounded) {
        inline4(gobj, ftPp_MS_SpecialS1);
        fp->mv.pp.specials.xC = 1;
    } else {
        fp->mv.pp.specials.xC = 0;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}

/**
 * @brief Collision callback for aerial paired Squall Hammer
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirS2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    bool is_grounded = ft_800824A0(gobj, &ftNn_Init_803CD820);
    bool hit_wall;
    PAD_STACK(0x18);
    if ((fp->coll_data.env_flags & Collide_CeilingMask) == 1) {
        fp->self_vel.y = 0.0F;
    }
    hit_wall = false;
    if (fp->self_vel.x != 0.0F) {
        if (fp->self_vel.x > 0.0F) {
            hit_wall = fp->coll_data.env_flags & Collide_LeftWallMask;
        } else {
            hit_wall = fp->coll_data.env_flags & Collide_RightWallMask;
        }
    }
    // Paired aerial wall bounce reflection
    if (hit_wall) {
        if (ABS(fp->self_vel.x) < da->x48) {
            fp->self_vel.x = fp->self_vel.x > 0.0F ? -da->x48 : da->x48;
        } else {
            fp->self_vel.x *= -da->x44;
        }
    }
    if (is_grounded) {
        inline4(gobj, ftPp_MS_SpecialS2);
        fp->mv.pp.specials.xC = 1;
    } else {
        fp->mv.pp.specials.xC = 0;
    }
    inline2(gobj);
    ftPp_SpecialS_8011F720(gobj);
    inlineA0(gobj);
}
