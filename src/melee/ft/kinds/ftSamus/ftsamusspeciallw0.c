/**
 * @file ftsamusspeciallw0.c
 * @brief Down-B: Morph Ball and Bomb Jump implementation for Samus
 * @details Implements Samus's Down-B Morph Ball ground roll, aerial drift,
 * bomb explosion collision reaction (Bomb Jump physics and trajectory
 * calculation), interruptibility (IASA), and Charge Shot state inspection
 * queries. Module prefix: ftSs
 */

#include "ftsamusspeciallw0.h"

#include <melee/ft/forward.h>

#include "ftsamus.h"
#include "ftsamusspeciallw1.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack1.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/kinds/ftCommon/ftCo_Escape.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/kinds/ftCommon/ftCo_SquatWait.h>
#include <melee/ft/types.h>
#include <melee/lb/lbcollision.h>

/**
 * @brief Down-B (Bomb): Handles bomb explosion hit on Samus and initiates Bomb
 * Jump.
 * @details Calculates the launch angle from the bomb's position and triggers
 * the bomb jump state.
 * @param gobj Samus fighter game object pointer
 * @param bomb_pos_x World X position of exploding bomb
 * @param bomb_radius Explosion radius / divisor
 */
void ftSs_Init_80128944(HSD_GObj* gobj, float bomb_pos_x, float bomb_radius)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = fp->dat_attrs;
    float angle = ftSs_Init_80128AC8(gobj, bomb_pos_x, bomb_radius);

    u8 _[8];

    // Check invulnerability / intangibility
    if (!ftColl_8007B868(gobj)) {
        switch (fp->x2070.x0.x2071_b0_3) {
        case 0:
        case 2:
        case 3:
        case 4:
            if ((fp->x2070.x0.x2073 == 0x14) || ((fp->x2070.x0.x2071_b5) == 0))
            {
                if (fp->x5F4_arr[0].idx == 2) {
                    ftSs_Init_80128B1C(gobj, angle, da->x0, 1.0f);
                } else {
                    ftSs_Init_80128B1C(gobj, angle, 0.0f, 1.0f);
                }
            }
        }
    }
}

/**
 * @brief Checks collision between an attack/bomb capsule and Samus's hurt
 * capsules.
 * @param gobj Samus fighter game object pointer
 * @param attack_capsule Attack capsule data pointer
 * @param hit_radius Hitbox radius offset
 * @return True if collision detected, false otherwise
 */
bool ftSs_Init_80128A1C(HSD_GObj* gobj, UNK_T attack_capsule, float hit_radius)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->hurt_capsules_len; i++) {
        if (lbColl_80008248(attack_capsule, &fp->hurt_capsules[i].capsule,
                            ftCommon_8007F804(fp), hit_radius, fp->x34_scale.y,
                            fp->cur_pos.z))
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Down-B (Bomb): Calculates bomb jump trajectory angle based on
 * horizontal offset from bomb.
 * @details Angle formula: (-da->x4 * dx / radius) + (pi / 2).
 * Launch angle centers around 90 degrees (pi/2 radians, straight up) and tilts
 * left/right based on offset.
 * @param gobj Samus fighter game object pointer
 * @param bomb_pos_x World X position of exploding bomb
 * @param bomb_radius Explosion radius / divisor
 * @return Launch angle in radians
 */
float ftSs_Init_80128AC8(HSD_GObj* gobj, float bomb_pos_x, float bomb_radius)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = getFtSpecialAttrs(fp);
    float displacement_ratio = (fp->cur_pos.x - bomb_pos_x) / bomb_radius;
    if (displacement_ratio >= 1.0f) {
        displacement_ratio = 1.0f;
    }
    if (displacement_ratio <= -1.0f) {
        displacement_ratio = -1.0f;
    }
    // Launch angle: 90 degrees (pi/2 ~ 1.570796f) adjusted by normalized
    // horizontal displacement
    return (-da->x4 * displacement_ratio) + 1.5707963705062866f;
}

/**
 * @brief Sets Samus's self velocity components using bomb jump velocity and
 * launch angle.
 * @param gobj Samus fighter game object pointer
 * @param angle Launch angle in radians
 */
static inline void ftSamus_80128B1C_inner(HSD_GObj* gobj, float angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    // Apply bomb jump velocity magnitude (samus_attr->x8)
    fp->self_vel.x = samus_attr->x8 * cosf(angle);
    fp->self_vel.y = samus_attr->x8 * sinf(angle);
    // Clamp horizontal launch speed to air drift limit scaled by x10
    ftCommon_ClampSelfVelX(fp, ftAttr->air_drift_max * samus_attr->x10);
}

/**
 * @brief Down-B (Bomb): Enters aerial bomb jump action state (0x156).
 * @param gobj Samus fighter game object pointer
 * @param angle Launch angle in radians
 * @param start_frame Starting animation frame
 * @param frame_speed Animation playback speed multiplier
 */
void ftSs_Init_80128B1C(HSD_GObj* gobj, float angle, float start_frame,
                        float frame_speed)
{
    Fighter* fp;
    Fighter* fighter2;

    u8 _[8];

    fp = fighter2 = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftSamus_80128B1C_inner(gobj, angle);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->mv.ss.speciallw.x0 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fighter2);
    }
    // Change to ftSs_MS_SpecialAirLw (0x156 = 342: aerial morph ball / bomb
    // jump reaction)
    Fighter_ChangeMotionState(gobj, 0x156, Ft_MF_None, start_frame,
                              frame_speed, 0.0f, 0);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Down-B (Morph Ball / Bomb Jump): Grounded animation callback.
 * @details Toggles morph ball hurtbox state based on cmd_vars[0] and returns
 * to idle when done.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[0]) && (!fp->mv.ss.speciallw.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->mv.ss.speciallw.x0 = 1;
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.speciallw.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->mv.ss.speciallw.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Return to grounded wait
    }
}

/**
 * @brief Down-B (Morph Ball / Bomb Jump): Aerial animation callback.
 * @details Toggles morph ball hurtbox state based on cmd_vars[0] and
 * transitions to Fall when done.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->cmd_vars[0]) && (!fp->mv.ss.speciallw.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->mv.ss.speciallw.x0 = 1;
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.speciallw.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->mv.ss.speciallw.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj); // Transition to normal aerial fall
    }
}

/**
 * @brief Down-B (Morph Ball): Grounded IASA callback.
 * @details Checks stick down input to unmorph into crouch/squat wait,
 * or allows interruptibility into various grounded attacks and specials.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_IASA(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* da = fp->dat_attrs;

    // Check stick Y threshold (da->x14) to unmorph into squat wait
    if (fp->cmd_vars[1] && fp->input.lstick[0].y < da->x14) {
        fp->cmd_vars[1] = 0;
        ftCo_800D638C(gobj);
        return;
    }

    // Action interrupts
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80099794(gobj));
}

/**
 * @brief Down-B (Morph Ball): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    ftCo_Fall_IASA_Inner(gobj);
}

/**
 * @brief Down-B (Morph Ball): Grounded physics callback.
 * @details Applies horizontal roll acceleration when morph ball is active
 * (cmd_vars[0]).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[4];

    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;

    if (fp->cmd_vars[0]) {
        float samus_attr_xC = samus_attr->xC;
        // Roll movement: scale walk acceleration and max velocity by attribute
        // xC
        ftCommon_CalcGroundAccel_AccelToLStickX(
            fp, 0.0f, ftAttr->walk_accel_mul * samus_attr_xC,
            ftAttr->walk_max_vel * samus_attr_xC);
        ftCommon_SetSelfMovementFromGroundedMovement(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

/**
 * @brief Down-B (Morph Ball): Aerial physics callback.
 * @details Applies basic gravity and horizontal drift scaled by attribute x10.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    struct ftCo_DatAttrs* ftAttr = &fp->co_attrs;

    u8 _[8];

    ftCommon_FallBasic(fp);
    // Apply aerial drift scaled by samus_attr->x10
    ftCommon_CalcSelfAccel_DriftSimple(
        fp, 0.0f,
        ftAttr->ground_to_air_jump_momentum_multiplier * samus_attr->x10,
        ftAttr->jump_h_max_velocity * samus_attr->x10);
}

/**
 * @brief Down-B (Morph Ball): Grounded collision callback.
 * @details Checks environment collision; transitions to aerial morph ball if
 * walking off ledge.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (!ft_80082888(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_80129048(gobj);
        }
    } else if (!ft_800827A0(gobj)) {
        ftSs_SpecialLw_80129048(gobj);
    }
}

/**
 * @brief Down-B (Morph Ball): Aerial collision callback.
 * @details Checks ground collision; transitions to grounded morph ball upon
 * landing.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (ft_800824A0(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_801290A4(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        ftSs_SpecialLw_801290A4(gobj);
    }
}

/**
 * @brief Down-B (Morph Ball): Ground-to-air transition.
 * @details Switches motion state to ftSs_MS_SpecialAirLw (0x156 = 342).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_80129048(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x156, JOBJ_HIDDEN, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0f, 0);
}

/**
 * @brief Down-B (Morph Ball): Air-to-ground transition.
 * @details Switches motion state to ftSs_MS_SpecialLw (0x155 = 341).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialLw_801290A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x155, JOBJ_HIDDEN, fp->cur_anim_frame,
                              fp->frame_speed_mul, 0.0f, 0);
}

/**
 * @brief Queries current and maximum Charge Shot charge levels.
 * @param gobj Samus fighter game object pointer
 * @param[out] out_charge Current charge level pointer
 * @param[out] out_max Maximum charge level pointer
 * @return 0 on success, -1 if no Charge Shot is active
 */
int ftSs_SpecialLw_80129100(HSD_GObj* gobj, int* out_charge, int* out_max)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSs_DatAttrs* samus_attr = fp->dat_attrs;

        u8 _[4];

        if (!fp->u.ss.x222C) {
            return -1;
        }

        *out_charge = fp->u.ss.x2230;
        *out_max = samus_attr->x18;
        return 0;
    }

    return -1;
}

/**
 * @brief Checks if Samus is currently in Neutral-B charge states with state
 * flag set.
 * @param gobj Samus fighter game object pointer
 * @return Status flag (0 or 1)
 */
s32 ftSs_SpecialLw_80129158(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 motion_state_index = fp->motion_id;
        switch (motion_state_index) {
        case 0x157: // ftSs_MS_SpecialNStart
        case 0x158: // ftSs_MS_SpecialNHold
        case 0x159: // ftSs_MS_SpecialNCancel
        case 0x15A: // ftSs_MS_SpecialN
        case 0x15B: // ftSs_MS_SpecialAirNStart
        case 0x15C: // ftSs_MS_SpecialAirN
            if (fp->x2070.x0.x2071_b6) {
                return 1;
            }
            return 0;
        }

        return 1;
    }
    return 1;
}

/**
 * @brief Checks if Samus is currently in Neutral-B (Charge Shot) motion
 * states.
 * @param gobj Samus fighter game object pointer
 * @return 0 if in Charge Shot states, 1 otherwise
 */
s32 ftSs_SpecialN_801291A8(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 motion_state_index = fp->motion_id;

        switch (motion_state_index) {
        case 0x157: // ftSs_MS_SpecialNStart
        case 0x158: // ftSs_MS_SpecialNHold
        case 0x15A: // ftSs_MS_SpecialN
        case 0x15B: // ftSs_MS_SpecialAirNStart
        case 0x15C: // ftSs_MS_SpecialAirN
            return 0;
        }

        return 1;
    }
    return 1;
}
