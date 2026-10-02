/**
 * @file ftseakspecials.c
 * @brief Sheik's Side-B move: Chain.
 * @details Implements Sheik's grounded and aerial Side-B move (Chain whip),
 * including chain entity spawning, whip physics simulation, analog stick
 * aiming and whipping, dynamic hitbox activation based on segment
 * displacement, whip crack sound effects, and retraction mechanics. Module
 * prefix: ftSk (Fighter: Sheik)
 */

#include "ftseakspecials.h"

#include <melee/ft/forward.h>
#include <melee/lb/forward.h>

#include <math.h>
#include <placeholder.h>

#include "ftseak.h"
#include "types.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/kinds/ftNess/ftnessattackhi4.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itseakchain.h>
#include <melee/it/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbcollision.h>
#include <sysdolphin/baselib/jobj.h>

/// @todo Fix common data struct
#define COMMON_DATA_F32 ((float*) p_ftCommonData)

/**
 * @brief Updates chain whip target angle and extension magnitude from control
 * stick.
 * @details Computes stick angle via atan2, wraps between [0, 360), smoothes
 * angle transition using common data filter, and calculates clamped magnitude
 * into fp->mv.sk.specials.x14.
 * @param fp Fighter pointer
 */
void ftSk_SpecialS_80110490(Fighter* fp)
{
    float stick_rad, stick_deg, angle_diff, smoothed_angle, stick_mag;

    stick_rad = atan2f(fp->input.lstick[0].y,
                       (fp->input.lstick[0].x * fp->facing_dir));

    if (stick_rad < 0) {
        stick_rad += (float) M_TAU;
    }

    stick_deg = MTXRadToDeg(stick_rad);

    if (stick_deg < 0) {
        stick_deg = 0;
    }

    if (stick_deg > 359) {
        stick_deg = 359;
    }

    angle_diff = stick_deg - fp->mv.sk.specials.x18;

    if (angle_diff > 180) {
        angle_diff -= 360;
    } else if (angle_diff < -180) {
        angle_diff += 360;
    }

    smoothed_angle =
        angle_diff * COMMON_DATA_F32[275] + fp->mv.sk.specials.x18;

    if (smoothed_angle > 360) {
        smoothed_angle -= 360;
    } else if (smoothed_angle < 0) {
        smoothed_angle += 360;
    }

    fp->mv.sk.specials.x18 = smoothed_angle;

    stick_mag = sqrtf(fp->input.lstick[0].x * fp->input.lstick[0].x +
                      fp->input.lstick[0].y * fp->input.lstick[0].y);

    if (stick_mag > 1) {
        stick_mag = 1;
    }

    fp->mv.sk.specials.x14 +=
        COMMON_DATA_F32[275] * (stick_mag - fp->mv.sk.specials.x14);
}

/**
 * @brief Blends upper body and arm joint animation towards chain direction.
 * @param gobj Fighter game object
 * @param anim_id Animation identifier (305 for grounded, 308 for aerial)
 * @param blend_weight Blend weight factor
 */
void ftSk_SpecialS_80110610(HSD_GObj* gobj, s32 anim_id, float blend_weight)
{
    Fighter* fp = GET_FIGHTER(gobj);
    UNK_T* items = fp->ft_data->x48_items;

    u8 _[4];

    HSD_Joint** item;

    if (anim_id == 305) {
        item = items[4];
    } else {
        item = items[5];
    }

    ftSk_SpecialS_80110490(fp);

    {
        float f = 0.0556F * fp->mv.sk.specials.x18 + 4;

        if (fp->mv.sk.specials.x14) {
            HSD_JObj* bone = fp->x8AC_animSkeleton;
            ftAnim_8006F4C8(fp, true, ftData_80085E50(fp, anim_id));
            ftAnim_80070710(bone, f);
            ftAnim_8006FB88(fp, FtPart_TransN, fp->x108_costume_joint->child);
            HSD_JObjAnimAll(bone);

            if (fp->mv.sk.specials.x14 < 1) {
                ftAnim_80070108(fp, FtPart_TransN, 1 - fp->mv.sk.specials.x14,
                                fp->mv.sk.specials.x14, item[2]);
            }

            if (blend_weight < 1) {
                ftAnim_8006FE9C(fp, FtPart_TransN, blend_weight,
                                1 - blend_weight);
                return;
            }

            ftAnim_8006FF74(fp, FtPart_TransN);
            return;
        }
    }

    if (blend_weight < 1) {
        ftAnim_80070010(fp, FtPart_TransN, blend_weight, 1 - blend_weight,
                        item[2]);
        return;
    }

    ftAnim_8006FA58(fp, FtPart_TransN, item[2]);
}

/**
 * @brief Plays whip snapping and cracking sound effects based on control stick
 * flicks.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110788(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->u.sk.lstick_delta.x = fp->input.lstick[0].x - fp->input.lstick[1].x;
    fp->u.sk.lstick_delta.y = fp->input.lstick[0].y - fp->input.lstick[1].y;

    // Check forward flick / whip snap
    {
        s32 snap_timer_fwd = fp->mv.sk.specials.x8;

        if (snap_timer_fwd > 0) {
            fp->mv.sk.specials.x8 = snap_timer_fwd - 1;
        } else {
            const enum_t flags = (1 << 3) | (1 << 6) | (1 << 8) | (1 << 9) |
                                 (1 << 10) | (1 << 11) | (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->u.sk.lstick_delta.x > +0.3F) ||
                (fp->facing_dir == -1 && fp->u.sk.lstick_delta.x < -0.3F))
            {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.x8 = 6;
            } else if (fp->u.sk.lstick_delta.y > 0.5F) {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.x8 = 12;
            }
        }
    }

    // Check backward flick / whip snap
    {
        s32 snap_timer_back = fp->mv.sk.specials.xC;
        if (snap_timer_back > 0) {
            fp->mv.sk.specials.xC = snap_timer_back - 1;
        } else {
            const enum_t flags = (1 << 0) | (1 << 1) | (1 << 3) | (1 << 6) |
                                 (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11) |
                                 (1 << 12) | (1 << 18);

            if ((fp->facing_dir == +1 && fp->u.sk.lstick_delta.x < -0.3F &&
                 fp->input.lstick[0].x < 0) ||
                (fp->facing_dir == -1 && fp->u.sk.lstick_delta.x > +0.3F &&
                 fp->input.lstick[0].x > 0))
            {
                ft_PlaySFX(fp, flags, 127, 64);
                fp->mv.sk.specials.xC = 6;
            }
        }
    }

    // Dampen control stick delta based on chain attributes
    {
        HSD_GObj* item_gobj = fp->u.sk.x8;

        if (item_gobj == NULL) {
            return;
        }

        {
            float left_stick_x = fp->input.lstick[0].x;
            Item* item_data = item_gobj->user_data;
            Article* article = item_data->xC4_article_data;
            itChainSegment* chainSegment = article->x4_specialAttributes;

            if (left_stick_x < 0) {
                left_stick_x = -left_stick_x;
            }

            if (left_stick_x < chainSegment->x48) {
                float left_stick_y = fp->input.lstick[0].y;

                if (fp->input.lstick[0].y < 0) {
                    left_stick_y = -left_stick_y;
                }

                if (left_stick_y < chainSegment->x48) {
                    float mul = 0.5F;
                    fp->u.sk.lstick_delta.x *= mul;
                    fp->u.sk.lstick_delta.y *= mul;
                }
            }
        }
    }
}

/**
 * @brief Empty accessory callback stub for Side-B.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_8011097C(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Updates position for a specific chain segment hitbox.
 * @param gobj Fighter game object
 * @param new_pos New 3D position vector
 * @param hitbox_id Hitbox slot index (0-3)
 */
void ftSk_SpecialS_UpdateHitboxes(HSD_GObj* gobj, Vec3* new_pos, s32 hitbox_id)
{
    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (!fp->cmd_vars[0]) {
            return;
        }

        fp->u.sk.xC[hitbox_id] = *new_pos;

        if (new_pos->x != 0 || new_pos->y != 0) {
            ftColl_8007B8A8(&fp->x914[hitbox_id], new_pos);

            fp->x914[hitbox_id].x4C = *new_pos;

            if (fp->x914[hitbox_id].x58.x == 0 &&
                fp->x914[hitbox_id].x58.y == 0 &&
                fp->x914[hitbox_id].x58.z == 0)
            {
                fp->x914[hitbox_id].x58 = *new_pos;
            }
        }
    }
}

/**
 * @brief Zeroes out position and previous position vectors for all 4 chain
 * hitboxes.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_ZeroHitboxPositions(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    // Zero out the position and last position of 4 hitboxes
    for (i = 0; i < 4; i++) {
        fp->x914[i].x58.x = 0;
        fp->x914[i].x58.y = 0;
        fp->x914[i].x58.z = 0;
        fp->x914[i].x4C.x = 0;
        fp->x914[i].x4C.y = 0;
        fp->x914[i].x4C.z = 0;
    }
}

/**
 * @brief Resets collision status and refreshes all 4 chain hitboxes.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110AEC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < 4; i++) {
        lbColl_80008434(&fp->x914[i]);
    }

    {
        Fighter* fp_2 = GET_FIGHTER(gobj);

        /// @todo The inlines in this file are wrong; this block should be
        ///       #ftSk_SpecialS_ZeroHitboxPositions.
        for (i = 0; i < 4; i++) {
            fp_2->x914[i].x58.x = 0;
            fp_2->x914[i].x58.y = 0;
            fp_2->x914[i].x58.z = 0;
            fp_2->x914[i].x4C.x = 0;
            fp_2->x914[i].x4C.y = 0;
            fp_2->x914[i].x4C.z = 0;
        }

        fp->x2219_b3 = true;
    }
}

/**
 * @brief Helper updating collision status across all chain hitboxes.
 * @param gobj Fighter game object
 */
static inline void ftSeakSpecialS_LoopChainHitCollisions(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008440(&fp->x914[i]);
        lbColl_80008428(&fp->x914[i]);
    }

    ftSk_SpecialS_ZeroHitboxPositions(gobj);
}

/**
 * @brief Helper activating hitboxes on all chain links when whip speed exceeds
 * threshold.
 * @param gobj Fighter game object
 */
static inline void ftSeakSpecialS_LoopChainHitActivate(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < (ssize_t) ARRAY_SIZE(fp->x914); i++) {
        lbColl_80008434(&fp->x914[i]);
    }

    ftSk_SpecialS_ZeroHitboxPositions(gobj);
    fp->x2219_b3 = true;
}

/**
 * @brief Computes squared 2D displacement (dx^2 + dy^2).
 * @param a Delta X
 * @param b Delta Y
 * @return float Squared displacement distance
 */
static inline float sumOfSquares(float a, float b)
{
    float c;

    a = a * a;
    c = b * b;

    return a + c;
}

/**
 * @brief Monitors chain segment movement and enables hitboxes when whip speed
 * exceeds threshold.
 * @details Computes displacement for each chain segment; if any segment
 * exceeds chain->x4C^2, hitboxes are activated for specialAttributes->x18
 * frames.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110BCC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* item_gobj = fp->u.sk.x8;
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    if (item_gobj == NULL) {
        return;
    }

    {
        Item* item_data = item_gobj->user_data;
        itChainSegment* chain =
            item_data->xC4_article_data->x4_specialAttributes;

        {
            float sums_of_squares[4];
            int i;
            for (i = 0; i < (ssize_t) ARRAY_SIZE(sums_of_squares); i++) {
                float x = fp->u.sk.xC[i].x - fp->u.sk.x3C[i].x;
                float y = fp->u.sk.xC[i].y - fp->u.sk.x3C[i].y;

                sums_of_squares[i] = sumOfSquares(x, y);

                fp->u.sk.x3C[i].x = fp->u.sk.xC[i].x;
                fp->u.sk.x3C[i].y = fp->u.sk.xC[i].y;
            }

            if (fp->mv.sk.specials.x1C > 0) {
                fp->mv.sk.specials.x1C--;

                if (fp->mv.sk.specials.x1C == 0) {
                    ftSeakSpecialS_LoopChainHitCollisions(gobj);
                }
            }

            // Check if any chain link moved faster than speed threshold
            {
                float chain_val = chain->x4C;
                float chain_val_sq = chain_val * chain_val;

                if (sums_of_squares[0] > chain_val_sq ||
                    sums_of_squares[1] > chain_val_sq ||
                    sums_of_squares[2] > chain_val_sq ||
                    sums_of_squares[3] > chain_val_sq)
                {
                    if (fp->mv.sk.specials.x1C <= 0) {
                        fp->mv.sk.specials.x1C = specialAttributes->x18;
                        ftSeakSpecialS_LoopChainHitActivate(gobj);
                    }
                } else {
                    s32 pause_timer = fp->mv.sk.specials.x20;
                    if (pause_timer > 0) {
                        fp->mv.sk.specials.x20--;
                    } else {
                        fp->mv.sk.specials.x1C = 0;
                        ftSeakSpecialS_LoopChainHitCollisions(gobj);
                    }
                }
            }
        }
    }
}

/**
 * @brief Unlinks chain item and clears fighter callbacks upon state interrupt.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110E4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftSk_SpecialS_ChainSomething(gobj);

    fp->u.sk.x8 = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/**
 * @brief Despawns active chain item entity and clears references.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_CheckAndDestroyChain(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (fp->u.sk.x8 == NULL) {
        return;
    }

    it_802BB20C(fp->u.sk.x8); // Despawn chain entity

    fp = gobj->user_data;

    ftSk_SpecialS_ChainSomething(gobj);

    fp->u.sk.x8 = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/**
 * @brief Pre-hitlag callback: pauses chain entity during hitlag.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110EE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.sk.x8) {
        it_802BAEEC(fp->u.sk.x8);
    }
}

/**
 * @brief Post-hitlag callback: resumes chain entity after hitlag.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_ChainSomething(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.sk.x8) {
        it_802BAF0C(fp->u.sk.x8);
        fp->mv.sk.specials.x20 = 2;
    }
}

/**
 * @brief Returns current horizontal control stick input.
 * @param gobj Fighter game object
 * @return float Stick X value
 */
float ftSk_SpecialS_80110F58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick[0].x;
}

/**
 * @brief Returns current vertical control stick input.
 * @param gobj Fighter game object
 * @return float Stick Y value
 */
float ftSk_SpecialS_80110F64(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick[0].y;
}

/**
 * @brief Initializes Side-B motion variables and zeroes chain hitbox tracking.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80110F70(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->cmd_vars[0] = 0;

    fp->mv.sk.specials.x0 = 0;
    fp->mv.sk.specials.x4 = 0;
    fp->mv.sk.specials.x8 = 0;
    fp->mv.sk.specials.xC = 0;

    {
        float zero = 0.0;

        fp->mv.sk.specials.x10 = zero;
        fp->mv.sk.specials.x18 = 4.0;
        fp->mv.sk.specials.x14 = zero;

        fp->mv.sk.specials.x1C = 0;
        fp->mv.sk.specials.x20 = 0;
        fp->u.sk.x8 = 0;

        {
            int i;
            for (i = 0; i < 4; i++) {
                fp->u.sk.xC[i].z = zero;
                fp->u.sk.xC[i].y = zero;
                fp->u.sk.xC[i].x = zero;

                fp->u.sk.x3C[i].z = zero;
                fp->u.sk.x3C[i].y = zero;
                fp->u.sk.x3C[i].x = zero;
            }
        }

        fp->u.sk.lstick_delta.z = zero;
        fp->u.sk.lstick_delta.y = zero;
        fp->u.sk.lstick_delta.x = zero;
    }

    fp->x2222_b2 = true;
    fp->accessory4_cb = &ftSk_SpecialS_8011097C;
}

/**
 * @brief Enters grounded Side-B (Chain) startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 349, Ft_MF_None, 0.0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialS_80110F70(gobj);
}

/**
 * @brief Enters aerial Side-B (Chain) startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = 0;

    Fighter_ChangeMotionState(gobj, 352, Ft_MF_None, 0.0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialS_80110F70(gobj);
}

/**
 * @brief Helper spawning the chain item entity and setting up hitlag
 * callbacks.
 * @param gobj Fighter game object
 */
static inline void ftSk_SpecialS_SpawnChain(HSD_GObj* gobj)
{
    Fighter* fp = getFighterPlus(gobj);
    Vec3 pos;

    lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &pos);
    fp->u.sk.x8 = itSeakChain_Spawn(gobj, &pos, fp->facing_dir);
    fp->x1984_heldItemSpec = fp->u.sk.x8;

    if (fp->u.sk.x8 != NULL) {
        fp->death2_cb = &ftSk_Init_80110198;
        fp->take_dmg_cb = &ftSk_Init_80110198;
    }

    fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
    fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
}

/**
 * @brief Handles chain spawn timing during startup.
 * @details Spawns chain on frame da->x1C, applies launch impulse on da->x1C +
 * 1, and signals completion once frame count exceeds da->x20.
 * @param gobj Fighter game object
 * @return bool True if startup duration finished and ready for active whip
 * loop
 */
bool ftSk_SpecialS_CheckInitChain(HSD_GObj* gobj)
{
    Fighter* fp = getFighterPlus(gobj);
    ftSeakAttributes* da = fp->dat_attrs;

    fp->mv.sk.specials.x0 += 1;

    // Spawn chain on frame da->x1C
    if (fp->mv.sk.specials.x0 == da->x1C) {
        ftSk_SpecialS_SpawnChain(gobj);
        fp->mv.sk.specials.x1C = da->x18;

        if (fp->u.sk.x8 == NULL) {
            if (fp->ground_or_air == GA_Air) {
                ftCo_Fall_Enter(gobj);
            } else {
                ft_8008A2BC(gobj);
            }
        }
    }

    // Apply initial launch impulse on frame da->x1C + 1
    if (fp->mv.sk.specials.x0 == da->x1C + 1) {
        Vec3 vel = { 1.8f, 0.0f, 0.0f };
        HSD_GObj* item_gobj = fp->u.sk.x8;
        Item* ip = item_gobj->user_data;
        itChainSegment* segment = ip->xC4_article_data->x4_specialAttributes;

        vel.x = segment->x50;
        vel.x *= ip->facing_dir;
        it_802BCFC4(item_gobj, &vel);
    }

    if (fp->mv.sk.specials.x0 > da->x20) {
        return true;
    }

    return false;
}

/**
 * @brief Animation update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (ftSk_SpecialS_CheckInitChain(gobj)) {
        ftSk_SpecialS_80111830(gobj);
    }
}

/**
 * @brief Animation update for aerial Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (ftSk_SpecialS_CheckInitChain(gobj)) {
        ftSk_SpecialS_80111988(gobj);
    }
}

/**
 * @brief Interrupt check for grounded Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSStart_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Interrupt check for aerial Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSStart_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Side-B startup.
 * @details Applies fall gravity and aerial friction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* fighter_attr = &fp->co_attrs;

    if (fp->cmd_vars[0] != 0) {
        ftCommon_Fall(fp, fighter_attr->gravity,
                      fighter_attr->terminal_velocity);
    }

    ftCommon_CalcSelfAccel_Deaccel(fp, fighter_attr->aerial_friction);
}

/**
 * @brief Collision update for grounded Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111440(gobj);
    }
}

/**
 * @brief Collision update for aerial Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_801114E4(gobj);
    }
}

static u32 const transition_flags =
    Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/**
 * @brief State transition: Grounded -> Aerial for Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111440(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    {
        Fighter_ChangeMotionState(gobj, 352, transition_flags,
                                  fp->cur_anim_frame, 1, 0, NULL);
    }

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->u.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief State transition: Aerial -> Grounded for Side-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_801114E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_AirToGroundStateChange(gobj, fp, 349, transition_flags);

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->u.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief Animation update for grounded active Side-B loop.
 * @details Checks chain segment velocity, polls if B button is released to
 * begin retraction, and updates arm/body blend animation.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    ftSk_SpecialS_80110BCC(gobj);

    fp->mv.sk.specials.x0 += 1;

    {
        bool result;
        // B button released and minimum duration elapsed -> enter retraction
        if (fp->mv.sk.specials.x0 > specialAttributes->x14 &&
            fp->mv.sk.specials.x4)
        {
            fp->mv.sk.specials.x4 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSk_SpecialS_80111DF8(gobj);
            return;
        }
    }

    ftSk_SpecialS_80110610(gobj, 305, 1);
}

/**
 * @brief Animation update for aerial active Side-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirS_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;

    ftSk_SpecialS_80110BCC(gobj);
    fp->mv.sk.specials.x0 += 1;

    {
        bool result;
        // B button released and minimum duration elapsed -> enter aerial
        // retraction
        if (fp->mv.sk.specials.x0 > specialAttributes->x14 &&
            fp->mv.sk.specials.x4)
        {
            fp->mv.sk.specials.x4 = false;
            result = true;
        } else {
            result = false;
        }

        if (result) {
            ftSk_SpecialS_80111EB4(gobj);
            return;
        }
    }

    ftSk_SpecialS_80110610(gobj, 308, 1);
}

/**
 * @brief Interrupt check for grounded active Side-B loop.
 * @details Detects B button release (signals chain retraction) and processes
 * stick flicks.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!(fp->input.held_buttons[0] & HSD_PAD_B)) {
        fp->mv.sk.specials.x4 = true;
    }

    ftSk_SpecialS_80110788(gobj);
}

/**
 * @brief Interrupt check for aerial active Side-B loop.
 * @details Detects B button release and processes stick flicks.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirS_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!(fp->input.held_buttons[0] & HSD_PAD_B)) {
        fp->mv.sk.specials.x4 = true;
    }

    ftSk_SpecialS_80110788(gobj);
}

/**
 * @brief Physics update for grounded active Side-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial active Side-B loop.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirS_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Collision update for grounded active Side-B loop.
 * @details If Sheik falls off the platform, immediately triggers chain
 * retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111DF8(gobj);
    }
}

/**
 * @brief Collision update for aerial active Side-B loop.
 * @details If Sheik lands on the floor, immediately triggers chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_80111EB4(gobj);
    }
}

/**
 * @brief Enters grounded active Side-B loop (state 350) and checks environment
 * collision.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111830(HSD_GObj* gobj)
{
    /// @todo Split into two functions, one with @var fp and one with @var fp2
    Vec3 vec0;
    Vec3 vec1;
    Fighter* fp2;

    Fighter* fp = gobj->user_data;

    Fighter_ChangeMotionState(gobj, 350, Ft_MF_SkipHit, 0.0, 1, 0, NULL);
    ftSk_SpecialS_80110610(gobj, 305, 0);

    fp2 = gobj->user_data;
    fp2->mv.sk.specials.x0 = 0;

    ftSk_SpecialS_80110AEC(gobj);

    if (fp2->u.sk.x8 != NULL) {
        fp2->death2_cb = &ftSk_Init_80110198;
        fp2->take_dmg_cb = &ftSk_Init_80110198;
    }

    fp2->x2222_b2 = true;
    fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
    fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
    fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;

    {
        float ecb_top;
        float ecb_bot;
        vec0.x = 0.0;
        ecb_top = fp->coll_data.ecb.top.y;
        ecb_bot = fp->coll_data.ecb.bottom.y;
        vec0.y = 0.5F * (ecb_top + ecb_bot);
        vec0.z = 0.0;
        vec0.x += fp->cur_pos.x;
        vec0.y += fp->cur_pos.y;
        vec0.z += fp->cur_pos.z;

        lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &vec1);

        {
            s32 flags =
                ftNs_AttackHi4_YoyoCheckEnvColl(gobj, &vec0, &vec1, 0.5F);

            if (flags != 0) {
                ftSk_SpecialS_80111DF8(gobj);
            }
        }
    }
}

/**
 * @brief Enters aerial active Side-B loop (state 353).
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111988(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 353, Ft_MF_SkipHit, 0.0, 1.0, 0.0, NULL);
    ftSk_SpecialS_80110610(gobj, 308, 0.0);

    {
        Fighter* fp = gobj->user_data;
        fp->mv.sk.specials.x0 = 0;

        ftSk_SpecialS_80110AEC(gobj);

        if (fp->u.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief Animation update for grounded Side-B chain retraction.
 * @details Retracts chain links at frame x24, despawns chain item at frame
 * x28, and enters Wait (idle) upon animation completion.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    u8 _[36];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* specialAttributes = fp->dat_attrs;
    fp->mv.sk.specials.x0 += 1;

    {
        s32 timer = fp->mv.sk.specials.x0;
        float retract_finish_frame = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (timer < retract_finish_frame) {
            item_gobj = fp->u.sk.x8;

            if (timer == specialAttributes->x24) {
                it_802BCF84(item_gobj); // Begin chain retraction
            }

            /// @todo Split inner function
            goto inner_ret;
        }

        if (timer == retract_finish_frame) {
            item_gobj = fp->u.sk.x8;
            it_802BB20C(item_gobj); // Despawn chain entity
        } else {
        inner_ret:
            ftSk_SpecialS_80110BCC(gobj);
        }
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Enter Wait / Idle
    }
}

/**
 * @brief Animation update for aerial Side-B chain retraction.
 * @details Retracts and despawns chain, then enters Fall upon animation
 * completion.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    u8 _[36];

    Fighter* fp = gobj->user_data;
    ftSeakAttributes* specialAttributes = fp->dat_attrs;
    fp->mv.sk.specials.x0 += 1;

    {
        s32 timer = fp->mv.sk.specials.x0;
        float retract_finish_frame = specialAttributes->x28;

        HSD_GObj* item_gobj;

        if (timer < retract_finish_frame) {
            item_gobj = fp->u.sk.x8;
            if (timer == specialAttributes->x24) {
                it_802BCF84(item_gobj); // Begin chain retraction
            }
            goto inner_ret;
        }
        if (timer == retract_finish_frame) {
            item_gobj = fp->u.sk.x8;
            it_802BB20C(item_gobj); // Despawn chain entity
        } else {
        inner_ret:
            ftSk_SpecialS_80110BCC(gobj);
        }

        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftCo_Fall_Enter(gobj); // Enter Fall state
        }
    }
}

/**
 * @brief Interrupt check for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Interrupt check for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSEnd_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics update for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/**
 * @brief Collision update for grounded Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftSk_SpecialS_80111CB0(gobj);
    }
}

/**
 * @brief Collision update for aerial Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftSk_SpecialS_80111D54(gobj);
    }
}

/**
 * @brief State transition: Grounded -> Aerial for Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111CB0(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, 354, transition_flags);

    {
        Fighter* fp2 = gobj->user_data;

        if (fp2->u.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief State transition: Aerial -> Grounded for Side-B chain retraction.
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111D54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, 351, transition_flags);

    {
        Fighter* fp2 = GET_FIGHTER(gobj);

        if (fp2->u.sk.x8 != NULL) {
            fp2->death2_cb = &ftSk_Init_80110198;
            fp2->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp2->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp2->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp2->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief Enters grounded Side-B chain retraction (state 351).
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111DF8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 351, Ft_MF_SkipHit, 0, 1, 0, NULL);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.sk.specials.x0 = 0;

        if (fp->mv.sk.specials.x1C != 0) {
            ftSk_SpecialS_80110AEC(gobj);
        }

        if (fp->u.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief Enters aerial Side-B chain retraction (state 354).
 * @param gobj Fighter game object
 */
void ftSk_SpecialS_80111EB4(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 354, Ft_MF_SkipHit, 0, 1, 0, NULL);

    {
        Fighter* fp = gobj->user_data;
        fp->mv.sk.specials.x0 = 0;

        if (fp->mv.sk.specials.x1C != 0) {
            ftSk_SpecialS_80110AEC(gobj);
        }

        if (fp->u.sk.x8 != NULL) {
            fp->death2_cb = &ftSk_Init_80110198;
            fp->take_dmg_cb = &ftSk_Init_80110198;
        }

        fp->x2222_b2 = true;
        fp->accessory4_cb = &ftSk_SpecialS_8011097C;
        fp->pre_hitlag_cb = &ftSk_SpecialS_80110EE8;
        fp->post_hitlag_cb = &ftSk_SpecialS_ChainSomething;
    }
}

/**
 * @brief Checks if Sheik does not currently hold a needle item.
 * @param gobj Fighter game object
 * @return bool True if held needle item is NULL
 */
bool ftSk_SpecialS_80111F70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (gobj != NULL) {
        if (fp->u.sk.x4 != 0) {
            return false;
        }

        return true;
    }

    return true;
}

/**
 * @brief Returns the number of needles currently charged (0-6).
 * @param gobj Fighter game object
 * @return int Stored needle count
 */
int ftSk_SpecialS_80111FA0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (gobj != NULL) {
        return fp->u.sk.x0;
    }

    return 0;
}
