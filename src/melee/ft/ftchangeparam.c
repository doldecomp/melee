/**
 * @file ftchangeparam.c
 * @brief Fighter dynamic attribute modification and scaling implementation.
 * @details Implements the calculation and pipeline for recalculating fighter
 * physical attributes (movement speeds, jump velocities, fall gravity, weight,
 * landing lag, and item pickup ranges) when modified by status effects, items,
 * or game modes.
 *
 * Core Systems:
 * - Non-Linear Scale Interpolation: #ftCo_CalcYScaledKnockback computes attribute
 *   scaling curves for growing (Super Mushroom, Giant Melee) and shrinking
 *   (Poison Mushroom, Tiny Melee) fighters using coefficients from `PlCo.dat` (Fighter_804D6524).
 * - Master Recomputation Pipeline: #ftCo_800D105C restores base attributes from DAT,
 *   compounds model scale, Bunny Hood mobility boosts, Metal Box weight and fall penalties,
 *   and special mode physics, then dispatches to character-specific recalculation callbacks.
 * - Multi-Jump Adaptation: #ftCo_800D0CBC scales the mid-air jump velocity tables for
 *   characters with multiple aerial jumps (Kirby and Jigglypuff).
 *
 * Module prefix: ft / ftCo (Fighter Common)
 */

#include "ftchangeparam.h"

#include <placeholder.h>

#include "fighter.h"
#include "inlines.h"
#include <sysdolphin/baselib/debug.h>

/**
 * @brief Interpolates and scales an attribute value based on vertical model scale.
 * @details Evaluates a non-linear scaling curve based on character scale factor:
 * - Sensitivity zero (`factor == 0.0`): Returns `base_val` unmodified.
 * - Negative sensitivity (`factor < 0.0`): Applies reciprocal scaling via recursive call.
 * - Giant scaling (`scale >= 1.0` or `factor <= 1.0`):
 *   `result = (scale - 1.0) * base_val * factor + base_val`
 *   (linear expansion relative to normal scale 1.0).
 * - Tiny scaling (`scale < 1.0` and `factor > 1.0`):
 *   `result = base_val * scale / factor`
 *   (prevents excessive attribute attenuation when shrinking).
 *
 * @param base_val Base attribute value to scale
 * @param scale Fighter vertical model scale factor (fp->x34_scale.y)
 * @param factor Sensitivity coefficient from Fighter_804D6524
 * @return Scaled attribute value
 */
float ftCo_CalcYScaledKnockback(float base_val, float scale, float factor)
{
    HSD_ASSERT(0x1E, scale != 0.0F);
    if (factor == 0.0F) {
        return base_val;
    }
    if (factor < 0.0F) {
        return base_val / ftCo_CalcYScaledKnockback(1.0F, scale, -factor);
    }
    if (scale >= 1.0F || factor <= 1.0F) {
        return (scale - 1.0F) * base_val * factor + base_val;
    }
    return base_val * scale / factor;
}

/**
 * @brief Scales all common fighter physics and combat attributes by model scale.
 * @details Evaluates every attribute in ftCo_DatAttrs through #ftCo_CalcYScaledKnockback
 * using per-attribute coefficients loaded from PlCo.dat (Fighter_804D6524):
 * - Ground locomotion: Slow, mid, fast walk thresholds, and dash max velocity.
 * - Aerial mobility: Jump startup squat frames, full hop / short hop velocities,
 *   air drift acceleration / max speed, gravity, terminal velocity, and fast fall speed.
 * - Combat attributes: Character weight (affecting knockback received), shield break launch velocity.
 * - Recovery: Ledge jump horizontal and vertical launch velocities.
 * - Item interaction: Light and heavy item throw velocity multipliers, item grab reach boxes.
 * - Action lag: Empty landing lag and aerial landing lag (NAir, FAir, BAir, UAir, DAir) —
 *   giant fighters suffer longer recovery lag, while tiny fighters recover quicker.
 * - Interface & Camera: Overhead player name tag height and camera viewport subject offsets.
 *
 * @param attr Pointer to the fighter common attributes struct (fp->co_attrs)
 * @param scale Active vertical model scale factor (fp->x34_scale.y)
 */
void ftCo_800CF6E8(ftCo_DatAttrs* attr, f32 scale)
{
    f32* attr_ptr;

    if (scale != 1.0f) {
        /* Ground movement speeds */
        attr->slow_walk_max = ftCo_CalcYScaledKnockback(
            attr->slow_walk_max, scale, Fighter_804D6524->x10);
        attr->mid_walk_point = ftCo_CalcYScaledKnockback(
            attr->mid_walk_point, scale, Fighter_804D6524->x14);
        attr->fast_walk_min = ftCo_CalcYScaledKnockback(
            attr->fast_walk_min, scale, Fighter_804D6524->x18);
        attr->dash_max_velocity = ftCo_CalcYScaledKnockback(
            attr->dash_max_velocity, scale, Fighter_804D6524->x1C);
        attr->run_animation_scaling = ftCo_CalcYScaledKnockback(
            attr->run_animation_scaling, scale, Fighter_804D6524->x20);

        /* Jump startup and velocities */
        attr->jump_startup_time = ftCo_CalcYScaledKnockback(
            attr->jump_startup_time, scale, Fighter_804D6524->x24);
        attr->jump_v_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->jump_v_initial_velocity, scale, Fighter_804D6524->x28);
        attr->hop_v_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->hop_v_initial_velocity, scale, Fighter_804D6524->x2C);

        /* Aerial gravity and drift mobility */
        attr->gravity = ftCo_CalcYScaledKnockback(attr->gravity, scale,
                                                  Fighter_804D6524->x30);
        attr->terminal_velocity = ftCo_CalcYScaledKnockback(
            attr->terminal_velocity, scale, Fighter_804D6524->x34);
        attr->air_drift_stick_mul = ftCo_CalcYScaledKnockback(
            attr->air_drift_stick_mul, scale, Fighter_804D6524->x38);
        attr->aerial_drift_base = ftCo_CalcYScaledKnockback(
            attr->aerial_drift_base, scale, Fighter_804D6524->x3C);
        attr->air_drift_max = ftCo_CalcYScaledKnockback(
            attr->air_drift_max, scale, Fighter_804D6524->x40);
        attr->fast_fall_velocity = ftCo_CalcYScaledKnockback(
            attr->fast_fall_velocity, scale, Fighter_804D6524->x44);

        /* Weight and shield break launch */
        attr->weight = ftCo_CalcYScaledKnockback(attr->weight, scale,
                                                 Fighter_804D6524->x48);
        attr->shield_break_initial_velocity = ftCo_CalcYScaledKnockback(
            attr->shield_break_initial_velocity, scale, Fighter_804D6524->x4C);

        /* Ledge jump recovery */
        attr->ledge_jump_horizontal_velocity =
            ftCo_CalcYScaledKnockback(attr->ledge_jump_horizontal_velocity,
                                      scale, Fighter_804D6524->x50);
        attr->ledge_jump_vertical_velocity = ftCo_CalcYScaledKnockback(
            attr->ledge_jump_vertical_velocity, scale, Fighter_804D6524->x54);

        /* Item throws */
        attr->item_throw_velocity_multiplier =
            ftCo_CalcYScaledKnockback(attr->item_throw_velocity_multiplier,
                                      scale, Fighter_804D6524->x58);
        attr->heavy_throw_velocity_multiplier =
            ftCo_CalcYScaledKnockback(attr->heavy_throw_velocity_multiplier,
                                      scale, Fighter_804D6524->x5C);

        /* Collision bubble and item pickup grab reach */
        attr_ptr = &attr->xBC.size;
        *attr_ptr = ftCo_CalcYScaledKnockback(*attr_ptr, scale, Fighter_804D6524->x60);
        attr_ptr = &attr->xDC;
        *attr_ptr = ftCo_CalcYScaledKnockback(*attr_ptr, scale, Fighter_804D6524->x64);
        attr_ptr[1] =
            ftCo_CalcYScaledKnockback(attr_ptr[1], scale, Fighter_804D6524->x68);

        /* Landing lag: normal empty landing lag and 5 aerial attack landing lags */
        attr->normal_landing_lag = ftCo_CalcYScaledKnockback(
            attr->normal_landing_lag, scale, Fighter_804D6524->x6C);
        attr->landingairn_lag = ftCo_CalcYScaledKnockback(
            attr->landingairn_lag, scale, Fighter_804D6524->x70);
        attr->landingairf_lag = ftCo_CalcYScaledKnockback(
            attr->landingairf_lag, scale, Fighter_804D6524->x74);
        attr->landingairb_lag = ftCo_CalcYScaledKnockback(
            attr->landingairb_lag, scale, Fighter_804D6524->x78);
        attr->landingairhi_lag = ftCo_CalcYScaledKnockback(
            attr->landingairhi_lag, scale, Fighter_804D6524->x7C);
        attr->landingairlw_lag = ftCo_CalcYScaledKnockback(
            attr->landingairlw_lag, scale, Fighter_804D6524->x80);

        /* HUD and special effect velocities */
        attr->name_tag_height = ftCo_CalcYScaledKnockback(
            attr->name_tag_height, scale, Fighter_804D6524->x84);
        attr->screw_attack_launch_velocity = ftCo_CalcYScaledKnockback(
            attr->screw_attack_launch_velocity, scale, Fighter_804D6524->x88);
        attr->damageicejump_vel_y = ftCo_CalcYScaledKnockback(
            attr->damageicejump_vel_y, scale, Fighter_804D6524->x8C);
        attr->damageicejump_vel_x_mult = ftCo_CalcYScaledKnockback(
            attr->damageicejump_vel_x_mult, scale, Fighter_804D6524->x90);

        /* Viewport camera subject offsets */
        attr->x170.x = ftCo_CalcYScaledKnockback(attr->x170.x, scale,
                                                 Fighter_804D6524->x94);
        attr->x170.y = ftCo_CalcYScaledKnockback(attr->x170.y, scale,
                                                 Fighter_804D6524->x94);
        attr->x170.z = ftCo_CalcYScaledKnockback(attr->x170.z, scale,
                                                 Fighter_804D6524->x94);
        attr->x17C = ftCo_CalcYScaledKnockback(attr->x17C, scale,
                                               Fighter_804D6524->x98);
    }
}

/**
 * @brief Recalculates multi-jump vertical velocities for multi-jump characters.
 * @details Compounds all active jump multipliers and applies them to the array
 * of mid-air jump initial vertical velocities for characters with multi-jumps
 * (Kirby and Jigglypuff, stored in fp->x2D0):
 * 1. Model scale multiplier: Evaluates jump initial vertical velocity coefficient (x28).
 * 2. Bunny Hood multiplier: Compounds vertical jump multiplier (x14) if equipped.
 * 3. Metal Box penalty: Compounds vertical jump multiplier (x4) if in metal state.
 * Multiplies each jump entry in `multi_jump->x14[i]` by the compounded scale factor.
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
void ftCo_800D0CBC(Fighter_GObj* gobj)
{
    struct Fighter_x2D0_t* multi_jump;
    Fighter* fp;
    f32 scale;
    f32 orig_scale;
    s32 jump_idx;
    s32 jump_count;
    PAD_STACK(8);

    fp = gobj->user_data;
    jump_count = (multi_jump = fp->x2D0)->x28;
    scale = 1.0f;

    /* Apply size scaling to jump vertical velocity */
    if (scale != fp->x34_scale.y) {
        orig_scale = fp->x34_scale.y;
        scale *=
            ftCo_CalcYScaledKnockback(1.0f, orig_scale, Fighter_804D6524->x28);
    }

    /* Apply Bunny Hood jump boost */
    if (fp->x197C != NULL) {
        scale *= Fighter_804D6520->x14;
    }

    /* Apply Metal Box jump penalty */
    if (fp->is_metal) {
        scale *= Fighter_804D651C->x4;
    }

    /* Update all consecutive mid-air jump velocities */
    for (jump_idx = 0; jump_idx < jump_count; jump_idx++) {
        multi_jump->x14[jump_idx] *= scale;
    }
}

/**
 * @brief Computes size-scaled downward vertical velocity threshold.
 * @details Evaluates constant `p_ftCommonData->x310` with gravity scaling factor (x30)
 * to determine the minimum fall velocity threshold for transition checks
 * (used in FallSpecial / helpless fall state logic).
 *
 * @param fp Pointer to the Fighter instance data
 * @return Negative downward vertical velocity threshold
 */
float ftCo_800D0EC8(Fighter* fp)
{
    return -ftCo_CalcYScaledKnockback(p_ftCommonData->x310, fp->x34_scale.y,
                                      Fighter_804D6524->x30);
}

/**
 * @brief Restores common attributes from pristine character archive data.
 * @details Resets `co_attrs`, item pickup grab bounding boxes (`x294_itPickup`),
 * and model offset vector (`x2C4`) to default values loaded from the character's DAT file.
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
void ftCo_800D0FA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->co_attrs = *fp->ft_data->x0;
    {
        fp->x294_itPickup = *fp->ft_data->x40;
        fp->x2C4 = *fp->ft_data->x50;
    }
}

extern HSD_GObjEvent ftKindCalcIndiviParamTable[];

/**
 * @brief Master attribute recomputation pipeline for a fighter.
 * @details Completely recalculates a fighter's live attributes:
 * 1. Resets attributes to default baseline from DAT archives (#ftCo_800D0FA0).
 * 2. Applies size scaling if model scale != 1.0f:
 *    - Scales common attributes via #ftCo_800CF6E8.
 *    - Scales ground light, ground heavy, and air light item pickup reach boxes.
 *    - Scales bone offset vector fp->x2C4.
 * 3. Applies Bunny Hood modifiers (Fighter_804D6520):
 *    - Dash acceleration, max dash velocity, jump velocities, air drift, gravity,
 *      terminal/fast-fall speeds, and ledge/wall jump velocities.
 * 4. Applies Metal Box modifiers (Fighter_804D651C):
 *    - Jump vertical velocity penalties, increased gravity and terminal fall speeds,
 *      and massive weight multiplier (super knockback resistance).
 * 5. Applies custom/stamina match physics modifiers (Fighter_804D6518) if fp->x2229_b1 is set.
 * 6. Invokes character-specific parameter callback via #ftKindCalcIndiviParamTable.
 * 7. Recalculates multi-jump statistics via #ftCo_800D0CBC if present (Kirby/Jigglypuff).
 * 8. Scales Donkey Kong cargo carry parameters if fp->x2222_b0 is set.
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
void ftCo_800D105C(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftDonkeyAttributes* dk_attrs;
    f32 dk_scale_y;
    f32 scale_y;
    PAD_STACK(36); /// @todo fix stack

    fp = GET_FIGHTER(gobj);

    /* 1. Reset baseline attributes from pristine DAT tables */
    fp->co_attrs = *fp->ft_data->x0;
    fp->x294_itPickup = *fp->ft_data->x40;
    fp->x2C4 = *fp->ft_data->x50;

    /* 2. Apply model scale modifications (Super Mushroom / Poison Mushroom) */
    if (fp->x34_scale.y != 1.0f) {
        ftCo_800CF6E8(&fp->co_attrs, fp->x34_scale.y);
        scale_y = fp->x34_scale.y;

        /* Scale ground light item pickup reach box */
        fp->x294_itPickup.gr_light_offset.x *= scale_y;
        fp->x294_itPickup.gr_light_offset.y *= scale_y;
        fp->x294_itPickup.gr_light_offset.z *= scale_y;
        fp->x294_itPickup.gr_light_offset.w *= scale_y;

        /* Scale ground heavy item pickup reach box */
        fp->x294_itPickup.gr_heavy_offset.x *= scale_y;
        fp->x294_itPickup.gr_heavy_offset.y *= scale_y;
        fp->x294_itPickup.gr_heavy_offset.z *= scale_y;
        fp->x294_itPickup.gr_heavy_offset.w *= scale_y;

        /* Scale aerial light item pickup reach box */
        fp->x294_itPickup.air_light_offset.x *= scale_y;
        fp->x294_itPickup.air_light_offset.y *= scale_y;
        fp->x294_itPickup.air_light_offset.z *= scale_y;
        fp->x294_itPickup.air_light_offset.w *= scale_y;

        {
            f32 scale_offset_y = fp->x34_scale.y;
            fp->x2C4.x *= scale_offset_y;
            fp->x2C4.y *= scale_offset_y;
        }
    }

    /* 3. Apply Bunny Hood mobility modifiers */
    if (fp->x197C != NULL) {
        fp->co_attrs.dash_accel_mul *= Fighter_804D6520->x4;
        fp->co_attrs.dash_accel_base *= Fighter_804D6520->x8;
        fp->co_attrs.dash_max_velocity *= Fighter_804D6520->xC;
        fp->co_attrs.jump_h_initial_velocity *= Fighter_804D6520->x10;
        fp->co_attrs.jump_v_initial_velocity *= Fighter_804D6520->x14;
        fp->co_attrs.jump_h_max_velocity *= Fighter_804D6520->x1C;
        fp->co_attrs.hop_v_initial_velocity *= Fighter_804D6520->x18;
        fp->co_attrs.gravity *= Fighter_804D6520->x20;
        fp->co_attrs.terminal_velocity *= Fighter_804D6520->x24;
        fp->co_attrs.fast_fall_velocity *= Fighter_804D6520->x28;
        fp->co_attrs.ledge_jump_horizontal_velocity *= Fighter_804D6520->x2C;
        fp->co_attrs.ledge_jump_vertical_velocity *= Fighter_804D6520->x30;
        fp->co_attrs.wall_jump_horizontal_velocity *= Fighter_804D6520->x34;
        fp->co_attrs.wall_jump_vertical_velocity *= Fighter_804D6520->x38;
    }

    /* 4. Apply Metal Box weight and physics modifiers */
    if (fp->is_metal) {
        fp->co_attrs.jump_v_initial_velocity *= Fighter_804D651C->x4;
        fp->co_attrs.hop_v_initial_velocity *= Fighter_804D651C->x8;
        fp->co_attrs.gravity *= Fighter_804D651C->xC;
        fp->co_attrs.terminal_velocity *= Fighter_804D651C->x10;
        fp->co_attrs.fast_fall_velocity *= Fighter_804D651C->x14;
        fp->co_attrs.weight *= Fighter_804D651C->x18; // Massive knockback resistance
        fp->co_attrs.ledge_jump_vertical_velocity *= Fighter_804D651C->x1C;
        fp->co_attrs.wall_jump_vertical_velocity *= Fighter_804D651C->x20;
    }

    /* 5. Apply special match / stamina physics modifiers */
    if (fp->x2229_b1) {
        fp->co_attrs.gravity *= Fighter_804D6518->x0;
        fp->co_attrs.weight *= Fighter_804D6518->x4;
    }

    /* 6. Dispatch character-specific parameter recalculation */
    HSD_ASSERTREPORT(0x10d, ftKindCalcIndiviParamTable[fp->kind] != NULL,
                     "don\'t set ftKindCalcIndiviParamTable!!\n");
    ftKindCalcIndiviParamTable[fp->kind](gobj);

    /* 7. Recalculate multi-jump velocities (Kirby & Jigglypuff) */
    if (fp->x2D0 != NULL) {
        ftCo_800D0CBC(gobj);
    }

    /* 8. Scale Donkey Kong cargo carry parameters */
    if (fp->x2222_b0) {
        fp = gobj->user_data;
        dk_scale_y = fp->x34_scale.y;
        dk_attrs = fp->x2CC;
        if (dk_scale_y != 1.0f) {
            dk_attrs->x14 *= dk_scale_y;
            dk_attrs->x18 *= fp->x34_scale.y;
            dk_attrs->x1C *= fp->x34_scale.y;
        }
    }
}
