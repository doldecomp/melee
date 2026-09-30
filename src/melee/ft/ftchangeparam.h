#ifndef GALE01_0CF138
#define GALE01_0CF138

#include <melee/ft/forward.h>
#include <melee/ft/types.h>

/**
 * @file ftchangeparam.h
 * @brief Fighter dynamic attribute modification and scaling declarations.
 * @details Declares functions for recalculating and scaling live fighter attributes
 * (such as movement speeds, jump velocities, fall gravity, weight, landing lag, and pickup ranges)
 * in response to status effects, items, and game modes.
 *
 * Key Parameter Modifiers in Melee:
 * - Model Scale / Mushrooms: Super Mushroom (giant scale > 1.0) and Poison Mushroom
 *   (tiny scale < 1.0) scale all movement attributes non-linearly via #ftCo_CalcYScaledKnockback
 *   using scaling tables loaded from PlCo.dat (Fighter_804D6524).
 * - Bunny Hood: Multiplies run acceleration, max dash velocity, jump heights, air drift,
 *   and ledge/wall jump speeds (Fighter_804D6520).
 * - Metal Box: Dramatically increases weight (+super knockback resistance), accelerates
 *   gravity and fall speeds, and severely reduces jump heights (Fighter_804D651C).
 * - Physics Flags / Special Modes: Stamina or custom match physics modifying gravity and weight
 *   (Fighter_804D6518).
 * - Multi-Jump Scaling: Adjusts mid-air jump initial velocities for multi-jump characters
 *   (Kirby, Jigglypuff) via #ftCo_800D0CBC.
 * - Character-Specific Recalculation: Dispatches to per-character parameter recalculation
 *   callbacks in #ftKindCalcIndiviParamTable.
 *
 * Module prefix: ft / ftCo (Fighter Common)
 */

/**
 * @brief Interpolates and scales an attribute value based on vertical model scale.
 * @details Applies non-linear scaling curves based on model scale factor:
 * - If factor == 0.0: Returns base_val unscaled.
 * - If factor < 0.0: Inversely scales base_val by recursive evaluation with positive factor.
 * - If scale >= 1.0 (giant) or factor <= 1.0: Scales linearly: `base_val + (scale - 1.0) * base_val * factor`.
 * - Otherwise (scale < 1.0 and factor > 1.0): Scales by `base_val * scale / factor`.
 *
 * @param base_val Base attribute value to scale
 * @param scale Fighter vertical scale (fp->x34_scale.y)
 * @param factor Sensitivity / multiplier constant from Fighter_804D6524
 * @return Scaled attribute value
 */
/* 0CF138 */ float ftCo_CalcYScaledKnockback(float base_val, float scale,
                                             float factor);

/**
 * @brief Scales all common fighter physics and combat attributes by model scale.
 * @details Evaluates all attributes in ftCo_DatAttrs (walk/run speeds, jump heights,
 * gravity, terminal velocities, weight, landing lag, throw velocities, hurtbox size,
 * and camera offsets) through #ftCo_CalcYScaledKnockback using constants from Fighter_804D6524.
 *
 * @param attr Pointer to fighter common attributes struct (fp->co_attrs)
 * @param scale Active vertical model scale factor (fp->x34_scale.y)
 */
/* 0CF6E8 */ void ftCo_800CF6E8(ftCo_DatAttrs* attr, f32 scale);

/**
 * @brief Recalculates multi-jump vertical velocities for multi-jump characters.
 * @details Adjusts mid-air jump initial vertical velocities for Kirby and Jigglypuff
 * (stored in multi-jump struct fp->x2D0) by compounding model scale, Bunny Hood
 * jump multipliers, and Metal Box jump penalties.
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 0D0CBC */ void ftCo_800D0CBC(Fighter_GObj* gobj);

/**
 * @brief Computes size-scaled downward vertical velocity threshold.
 * @details Evaluates common constant p_ftCommonData->x310 with gravity scaling
 * to determine the minimum fall speed threshold for transition checks (e.g. FallSpecial).
 *
 * @param fp Pointer to the Fighter instance data
 * @return Scaled negative downward vertical velocity threshold
 */
/* 0D0EC8 */ float ftCo_800D0EC8(Fighter* fp);

/**
 * @brief Restores common attributes from pristine character archive data.
 * @details Copies default attributes from fp->ft_data->x0 (co_attrs),
 * fp->ft_data->x40 (item pickup bounding boxes), and fp->ft_data->x50 (offset vector).
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 0D0FA0 */ void ftCo_800D0FA0(Fighter_GObj* gobj);

/**
 * @brief Master attribute recomputation pipeline for a fighter.
 * @details Completely recalculates live fighter attributes:
 * 1. Resets attributes from pristine DAT data (#ftCo_800D0FA0).
 * 2. Applies size scaling if model scale != 1.0f (#ftCo_800CF6E8).
 * 3. Applies Bunny Hood mobility multipliers (Fighter_804D6520).
 * 4. Applies Metal Box weight, fall speed, and jump multipliers (Fighter_804D651C).
 * 5. Applies special match physics modifiers (Fighter_804D6518).
 * 6. Invokes character-specific parameter recalculation callback (#ftKindCalcIndiviParamTable).
 * 7. Scales multi-jump stats if present (#ftCo_800D0CBC).
 * 8. Scales Donkey Kong cargo carry parameters if active.
 *
 * @param gobj Pointer to the fighter's HSD_GObj
 */
/* 0D105C */ void ftCo_800D105C(Fighter_GObj* gobj);

#endif
