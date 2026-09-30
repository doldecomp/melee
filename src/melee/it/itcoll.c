/**
 * @file itcoll.c
 * @brief Item collision detection and response implementation.
 * @details Implements collision detection for items in Super Smash Bros. Melee:
 * - Item-to-item collisions: hitbox clanking (recoil, spark effect), damage exchanges
 * - Item-to-fighter collisions: fighter attacks hitting items, catch/grab hitboxes
 * - Environmental Collision Box (ECB) mutual pushing and horizontal nudge physics
 * - Damage accumulation, knockback formula, and elemental hit effect dispatch
 * - Dynamic collision bones and hurtbox initialization
 * Module prefix: it (Item)
 */

#include "itcoll.h"

#include <Runtime/platform.h>

#include <melee/ef/forward.h>

#include <placeholder.h>

#include "inlines.h"
#include "it_26B1.h"
#include "it_2725.h"
#include "it_279C.h"
#include "it_3F14.h"
#include "item.h"
#include "types.h"
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_DownAttack.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcollision.h>
#include <melee/lb/lbvector.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

/* 271830 */ static void it_80271830(Item* item, f32 arg_angle);
/* 271B60 */ static void it_80271B60(Item_GObj* item_gobj);
/* 271D2C */ static void it_80271D2C(Item_GObj* arg_item_gobj);
/* 271F78 */ static void it_80271F78(Item_GObj* arg_item_gobj);

/**
 * @brief Checks if a target position falls within the combined bounding box of two ECBs.
 * @param pos_x Center X coordinate
 * @param pos_y Center Y coordinate
 * @param ecb_a Pointer to first Environmental Collision Box
 * @param ecb_b Pointer to second Environmental Collision Box
 * @param target Pointer to target 3D point
 * @return true if target is enclosed within the combined ECB dimensions
 */
static bool itColl_chkECBOverlap(f32 pos_x, f32 pos_y, itECB* ecb_a,
                                 itECB* ecb_b, Vec3* target)
{
    f32 top;
    f32 left;
    f32 right;
    f32 bottom;
    top = pos_y + (ecb_a->top + ecb_b->top);
    bottom = pos_y + (ecb_a->bottom + ecb_b->bottom);
    right = pos_x + (ecb_a->right + ecb_b->right);
    left = pos_x + (ecb_a->left + ecb_b->left);
    if (top >= target->y && bottom <= target->y && right <= target->x &&
        left >= target->x)
    {
        return true;
    } else {
        return false;
    }
}

/// Unit quaternion defining rotation axis along Z {0, 0, 1, 0}
const Quaternion it_803B8560 = { 0.0f, 0.0f, 1.0f, 0.0f };

/// Descriptor for item dynamic collision sphere
typedef struct ItCollDynamicsDesc {
    s32 bone_id;    ///< Target bone index
    Vec3 offset;    ///< Offset vector from bone origin
    f32 size;       ///< Collision sphere radius
} ItCollDynamicsDesc;

/// Header for list of item dynamic collision spheres
typedef struct ItCollDynamics {
    u8 _pad[8];
    s32 count;                  ///< Number of dynamic collision descriptors
    ItCollDynamicsDesc* descs;  ///< Array of dynamic collision descriptors
} ItCollDynamics;

/**
 * @brief Resets the global item damage log counter to zero.
 */
void it_8026F9A0(void)
{
    it_804D6D18 = 0;
}

/**
 * @brief Records a hit interaction into the global item damage log array.
 * @param hit_type Damage source type (1 = fighter attack, 2 = item collision)
 * @param fighter Pointer to striking entity (Fighter or Item)
 * @param hit Pointer to offensive HitCapsule that connected
 * @param arg_item Pointer to victim Item instance
 * @param hurt Pointer to defensive HurtCapsule that was struck
 */
void it_8026F9AC(s32 hit_type, void* fighter, HitCapsule* hit, Item* arg_item,
                 HurtCapsule* hurt)
{
    const int log_size = ARRAY_SIZE(it_804A0E70);
    if (it_804D6D18 < log_size) {
        it_804A0E70[it_804D6D18].x0 = hit_type;
        it_804A0E70[it_804D6D18].x4 = fighter;
        it_804A0E70[it_804D6D18].x8 = hit;
        it_804A0E70[it_804D6D18].xC = hurt;
        it_804D6D18++;
        return;
    }
    OSReport("damage log over %d!!\n", log_size);
    HSD_ASSERT(105, 0);
}

/// Particle effect IDs spawned on hit, indexed by HitElement (-1 = no effect)
static s32 hit_effect_ids[17] = {
    /* [HitElement_Normal]   */ Ef_Id_Unk1000,
    /* [HitElement_Fire]     */ Ef_Id_Unk1002,
    /* [HitElement_Electric] */ Ef_Id_Unk1001,
    /* [HitElement_Slash]    */ Ef_Id_Unk1004,
    /* [HitElement_Coin]     */ Ef_Id_Unk1145,
    /* [HitElement_Ice]      */ Ef_Id_Unk1005,
    /* [HitElement_Nap]      */ -1,
    /* [HitElement_Sleep]    */ -1,
    /* [HitElement_Catch]    */ -1,
    /* [HitElement_Ground]   */ Ef_Id_Unk1000,
    /* [HitElement_Cape]     */ Ef_Id_Unk1000,
    /* [HitElement_Inert]    */ -1,
    /* [HitElement_Disable]  */ -1,
    /* [HitElement_Dark]     */ Ef_Id_Unk1046,
    /* [HitElement_Scball]   */ -1,
    /* [HitElement_Lipstick] */ -1,
    /* [HitElement_Leadead]  */ 0,
};

/**
 * @brief Resets hit tracking on matching item hitboxes when clanking or hitting.
 * @param arg_item0 Pointer to Item instance
 * @param arg_hit Pointer to reference HitCapsule
 * @param arg2 Interaction type
 * @param arg_item3 Target victim item
 * @param arg_chk Flag indicating whether to clear hitbox hit tracking
 */
void it_8026FA2C(Item* arg_item0, HitCapsule* arg_hit, s32 arg2,
                 Item* arg_item3, bool arg_chk)
{
    HitCapsule* hit;
    int i;

    for (i = 0; i < ARRAY_SIZE(arg_item0->x5D4_hitboxes); i++) {
        hit = &arg_item0->x5D4_hitboxes[i].hit;
        if (hit->state != HitCapsule_Disabled && hit->x4 == arg_hit->x4 &&
            lbColl_80008688(hit, arg2, arg_item3) && arg_chk)
        {
            it_804D6D1C[i] = 0;
        }
    }
}

/**
 * @brief Resets hit tracking across all items sharing an ignoreItemID group.
 * @param arg_item0 Pointer to Item instance
 * @param arg_hit Pointer to reference HitCapsule
 * @param arg2 Interaction type
 * @param arg3 Target victim pointer
 * @param chk Flag indicating whether to clear hitbox hit tracking
 */
void it_8026FAC4(Item* arg_item0, HitCapsule* arg_hit, s32 arg2, void* arg3,
                 bool chk)
{
    HSD_GObj* item_gobj;
    Item* item;
    PAD_STACK(4);

    if (arg_item0->xAC4_ignoreItemID != 0) {
        item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item0->xAC4_ignoreItemID) {
                it_8026FA2C(item, arg_hit, arg2, arg3, chk);
            }
            item_gobj = item_gobj->next;
        }
    } else {
        it_8026FA2C(arg_item0, arg_hit, arg2, arg3, chk);
    }
}

/**
 * @brief Inlined helper to record fighter hit interaction across item hitboxes.
 * @param arg_item Pointer to Item instance
 * @param arg_hit Pointer to reference HitCapsule
 * @param arg2 Interaction type
 * @param arg3 Pointer to striking Fighter
 */
static void it_8026FC00_inline(Item* arg_item, HitCapsule* arg_hit, int arg2,
                               Fighter* arg3)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(arg_item->x5D4_hitboxes); i++) {
        HitCapsule* hit = &arg_item->x5D4_hitboxes[i].hit;
        if (hit->state != HitCapsule_Disabled && hit->x4 == arg_hit->x4) {
            lbColl_80008820(hit, arg2, arg3);
        }
    }
}

/**
 * @brief Records a fighter hit interaction across all hitboxes of an item group.
 * @param arg_item Pointer to Item instance
 * @param arg_hit Pointer to reference HitCapsule
 * @param arg2 Interaction type
 * @param arg3 Pointer to striking Fighter
 */
void it_8026FC00(Item* arg_item, HitCapsule* arg_hit, s32 arg2, Fighter* arg3)
{
    PAD_STACK(8);

    if (arg_item->xAC4_ignoreItemID != 0) {
        HSD_GObj* item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
        if (item_gobj->next) {
        }
        while (item_gobj != NULL) {
            Item* item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                it_8026FC00_inline(item, arg_hit, arg2, arg3);
            }
            item_gobj = item_gobj->next;
        }
    } else {
        it_8026FC00_inline(arg_item, arg_hit, arg2, arg3);
    }
}

/**
 * @brief Updates item hitbox collision interpolation or copies state from matching active hitboxes.
 * @param arg_item Pointer to Item instance
 * @param arg_hit Pointer to HitCapsule to update
 */
void it_8026FCF8(Item* arg_item, HitCapsule* arg_hit)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    bool chk;
    Item* item;
    PAD_STACK(8);

    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                u32 i;

                chk = false;
                for (i = 0; i < ARRAY_SIZE(item->x5D4_hitboxes); i++) {
                    hit = &item->x5D4_hitboxes[i].hit;
                    if ((hit != arg_hit) &&
                        (hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4))
                    {
                        lbColl_CopyHitCapsule(hit, arg_hit);
                        chk = true;
                        break;
                    }
                    chk = false;
                }

                if (chk) {
                    return;
                }
            }
            item_gobj = item_gobj->next;
        }
    }
    lbColl_80008440(arg_hit);
}

#ifdef MUST_MATCH
static void order_sdata2_0(void)
{
    (void) 0.0f;
    (void) S32_TO_F32;
}
#endif

/**
 * @brief Resolves item-to-item hitbox clanking when two active hitboxes collide.
 * @details Compares damage values against clank threshold (it_804D6D28->xB4),
 * spawns clank spark effect (0x41C), and calculates recoil damage direction.
 * @param arg_item0 Pointer to first Item
 * @param hit1 Pointer to first Item's HitCapsule
 * @param arg_item2 Pointer to second Item
 * @param hit3 Pointer to second Item's HitCapsule
 */
void it_8026FE68(Item* arg_item0, HitCapsule* hit1, Item* arg_item2,
                 HitCapsule* hit3)
{
    Vec3 spark_pos;
    f32 dmg_b;
    s32 clank_type;
    f32 dmg_a;
    f32 vel_x;
    f32 vel_x_mag;
    f32 pos_x;
    f32 dir;
    s32 dmg_int;
    PAD_STACK(28);

    /* Midpoint between colliding capsules for spawning spark effect */
    spark_pos.x = 0.5f * (hit1->hurt_coll_pos.x + hit3->hurt_coll_pos.x);
    spark_pos.y = 0.5f * (hit1->hurt_coll_pos.y + hit3->hurt_coll_pos.y);
    spark_pos.z = 0.5f * (hit1->hurt_coll_pos.z + hit3->hurt_coll_pos.z);

    /* Check if hit3 damage overcomes hit1 (within clank threshold) */
    dmg_b = hit3->damage;
    if (((s32) dmg_b - it_804D6D28->xB4) < (s32) hit1->damage) {
        dmg_int = dmg_b;
        if (hit3->x41_b5) {
            clank_type = 4;
        } else {
            clank_type = 3;
        }
        it_8026FAC4(arg_item2, hit3, clank_type, arg_item0, true);
        if (dmg_int > arg_item2->xC48) {
            arg_item2->xC48 = dmg_int;
            arg_item2->xCF4_fighterGObjUnk = NULL;
            arg_item2->xC38 = arg_item0->kind;
            arg_item2->xCD4 = arg_item0->pos;
            vel_x_mag = arg_item2->x40_vel.x;
            vel_x = vel_x_mag;
            if (vel_x < 0.0f) {
                vel_x_mag = -vel_x;
            } else {
                vel_x_mag = vel_x;
            }
            if (vel_x_mag < it_804D6D28->xD4) {
                pos_x = arg_item2->pos.x;
                if (pos_x > arg_item0->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (vel_x < 0.0f) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item2->xCB8_outDamageDirection = dir;
        }
        efSync_Spawn(0x41C, arg_item2->entity, &spark_pos);
    }

    /* Check if hit1 damage overcomes hit3 (within clank threshold) */
    dmg_a = hit1->damage;
    if (((s32) dmg_a - it_804D6D28->xB4) < (s32) hit3->damage) {
        dmg_int = dmg_a;
        if (hit1->x41_b5) {
            clank_type = 4;
        } else {
            clank_type = 3;
        }
        it_8026FAC4(arg_item0, hit1, clank_type, arg_item2, false);
        if (dmg_int > arg_item0->xC48) {
            arg_item0->xC48 = dmg_int;
            arg_item0->xCF4_fighterGObjUnk = NULL;
            arg_item0->xC38 = arg_item2->kind;
            arg_item0->xCD4 = arg_item2->pos;
            vel_x_mag = arg_item0->x40_vel.x;
            vel_x = vel_x_mag;
            if (vel_x < 0.0f) {
                vel_x_mag = -vel_x;
            } else {
                vel_x_mag = vel_x;
            }
            if (vel_x_mag < it_804D6D28->xD4) {
                pos_x = arg_item0->pos.x;
                if (pos_x > arg_item2->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (vel_x < 0.0f) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item0->xCB8_outDamageDirection = dir;
        }
        efSync_Spawn(0x41C, arg_item0->entity, &spark_pos);
    }
}

static void it_8026FAC4_noinline(Item* ip, HitCapsule* hit, s32 arg2,
                                 void* arg3, bool chk)
{
    it_8026FAC4(ip, hit, arg2, arg3, chk);
}

/**
 * @brief Detects item grab / catch hitboxes connecting with fighters.
 * @details Checks catch-element hitboxes against grabbable fighter hurtboxes
 * and records the grab victim if valid.
 * @param gobj Pointer to Item GObj
 */
void it_802701BC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Fighter_GObj* fighter_gobj;
    PAD_STACK(4);

    ip->grab_victim = 0;
    ip->xD10 = 3.4028235e38f;
    fighter_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    while (fighter_gobj != NULL) {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        if ((!ftLib_IsSamePlayer(fighter_gobj, ip->owner) ||
             ip->xDCD_flag.x0.b5) &&
            (!gm_8016B168() || gm_8016B0D4() || ip->xDCD_flag.x0.b6 ||
             (ip->x20_team_id != fp->team)) &&
            !fp->x2219_b1 && !fp->x222A_b0 && (fp->x1988 == 0) &&
            (fp->x198C == 0) && !fp->x221D_b6 && !(fp->x1A6A & ip->xD08))
        {
            u32 it_hit_index = 0U;
            while (it_hit_index < 4U) {
                HitCapsule* arg_hit = &ip->x5D4_hitboxes[it_hit_index].hit;
                HitCapsule* hit = arg_hit;
                if ((hit->state != HitCapsule_Disabled) &&
                    (hit->element == HitElement_Catch) &&
                    ((hit->x40_b2 && (fp->ground_or_air == GA_Air)) ||
                     (hit->x40_b3 && (fp->ground_or_air == GA_Ground))) &&
                    !lbColl_8000ACFC(fp, hit))
                {
                    u32 ft_hit_index = 0U;
                    while (ft_hit_index < fp->hurt_capsules_len) {
                        if (fp->hurt_capsules[ft_hit_index].is_grabbable &&
                            lbColl_80007ECC(
                                hit,
                                &fp->hurt_capsules[ft_hit_index].capsule,
                                ftCommon_8007F804(fp), ip->scl,
                                fp->x34_scale.y, fp->cur_pos.z))
                        {
                            f32 dist_x;
                            it_8026FAC4_noinline(ip, hit, 0, fp, 0);
                            dist_x = ABS(fp->cur_pos.x - ip->pos.x);
                            if (dist_x < ip->xD10) {
                                ip->grab_victim = ip->atk_victim = fp->gobj;
                                ip->xDD0_flag.x0.b1 = 1;
                                ip->xD10 = dist_x;
                            }
                            return;
                        }
                        ft_hit_index++;
                    }
                }
                it_hit_index++;
            }
        }
        fighter_gobj = fighter_gobj->next;
    }
}

static void it_8026F9AC_noinline(s32 arg0, void* fighter, HitCapsule* hit,
                                 Item* arg_item, HurtCapsule* hurt)
{
    it_8026F9AC(arg0, fighter, hit, arg_item, hurt);
}

/**
 * @brief Checks fighter attack hitboxes colliding with an item's defensive hurtboxes.
 * @details Handles team checks, friendly fire, damage accumulation, damage logging,
 * and hit sound effects.
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_802703E8(Item_GObj* arg_item_gobj)
{
    Item* arg_item;
    HSD_GObj* fighter_gobj;
    Fighter* fighter;
    u32 hit_index;
    HitCapsule* hit;
    ItemKind kind;
    s32 dmg;
    u32 hurt_index;
    u32 ft_team;
    PAD_STACK(16);

    arg_item = arg_item_gobj->user_data;
    if (arg_item->xAC8_hurtboxNum == 0) {
        return;
    }
    for (fighter_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
         fighter_gobj != NULL; fighter_gobj = fighter_gobj->next)
    {
        if (((arg_item->owner == fighter_gobj) && !arg_item->xDCE_flag.x0.b0))
        {
            continue;
        }
        fighter = fighter_gobj->user_data;
        if (!((fighter->x1064_thrownHitbox.x134.owner == NULL) ||
              (fighter->x1064_thrownHitbox.x134.owner != arg_item->owner) ||
              arg_item->xDCE_flag.x0.b0))
        {
            continue;
        }
        if (fighter->x1064_thrownHitbox.x134.owner != NULL) {
            ft_team =
                ftLib_GetTeam(fighter->x1064_thrownHitbox.x134.owner) & 0xFF;
        } else {
            ft_team = fighter->team;
        }
        if (gm_8016B168() && !gm_8016B0D4() && !arg_item->xDCE_flag.x0.b1 &&
            (ft_team == arg_item->x20_team_id))
        {
            continue;
        }
        for (hit_index = 0; hit_index < 4; hit_index++) {
            hit = &fighter->x914[hit_index];
            if ((hit->state == HitCapsule_Disabled) ||
                (hit->element == HitElement_Catch) || (hit->x42_b7 != 1) ||
                ((!hit->x40_b2 || (arg_item->ground_or_air != GA_Air)) &&
                 (!hit->x40_b3 || (arg_item->ground_or_air != GA_Ground))) ||
                lbColl_8000ACFC(arg_item, hit) || (arg_item->xD0C == 2))
            {
                continue;
            }
            for (hurt_index = 0; hurt_index < arg_item->xAC8_hurtboxNum;
                 hurt_index++)
            {
                if (!lbColl_8000805C(
                        hit, &arg_item->xACC_itemHurtbox[hurt_index], NULL, 0,
                        fighter->x34_scale.y, arg_item->scl, 0.0f))
                {
                    continue;
                }
                if (hit->element != HitElement_Inert) {
                    ftColl_80076808(fighter, hit, 0, arg_item, 0);
                    dmg = hit->damage;
                    fighter->dmg.x1914 = dmg;
                    arg_item->xCA0 += dmg;
                    if (dmg > arg_item->xCA4) {
                        arg_item->xCA4 = dmg;
                    }
                    it_8026F9AC_noinline(
                        1, fighter, hit, arg_item,
                        &arg_item->xACC_itemHurtbox[hurt_index]);
                    it_8027B378(fighter->gobj, arg_item->entity, dmg);
                    kind = arg_item->kind;
                    if ((kind == It_PKind_Random) &&
                        (arg_item->xDD4_itemVar.pokemon.x0 == 7) &&
                        ((hit->sfx_kind == 1U) || (hit->sfx_kind == 2U)))
                    {
                        lbAudioAx_800237A8(0x61A87, 0x7FU, 0x40U);
                    } else if ((kind != It_PKind_Random) ||
                                (arg_item->xDD4_itemVar.pokemon.x0 != 8) ||
                                ((hit->sfx_kind != 1U) &&
                                 (hit->sfx_kind != 2U)))
                    {
                        lbColl_80005BB0(hit, -1);
                    }
                } else {
                    fighter->unk_gobj = arg_item_gobj;
                }
                break;
            }
        }
    }
}

/**
 * @brief Subroutine applying damage to an item when struck by another item's hitbox.
 * @param item Attacking Item
 * @param arg_item Victim Item
 * @param hit Connecting offensive HitCapsule
 * @param arg_hurt Struck defensive HurtCapsule
 */
static inline void it_802706D0_sub3(Item* item, Item* arg_item,
                                    HitCapsule* hit, HurtCapsule* arg_hurt)
{
    f32 dir;
    s32 dmg;
    ItemKind kind;
    it_8026FAC4_noinline(item, hit, (hit->x41_b4) ? 8 : 0, arg_item, 0);
    if (ABS(item->x40_vel.x) < it_804D6D28->xD4) {
        if (item->pos.x > arg_item->pos.x) {
            dir = -1.0f;
        } else {
            dir = 1.0f;
        }
    } else if (item->x40_vel.x < 0.0f) {
        dir = -1.0f;
    } else {
        dir = 1.0f;
    }
    item->xCB8_outDamageDirection = dir;
    dmg = hit->damage;
    item->xC34_damageDealt = dmg;
    item->xCF4_fighterGObjUnk = NULL;
    item->xC38 = arg_item->kind;
    item->xCD4 = arg_item->pos;
    arg_item->xCA0 = arg_item->xCA0 + dmg;
    if (dmg > arg_item->xCA4) {
        arg_item->xCA4 = dmg;
    }
    it_8026F9AC_noinline(2, item, hit, arg_item, arg_hurt);
    it_8027B408(item->entity, arg_item->entity, dmg);
    kind = arg_item->kind;
    if ((kind == It_PKind_Random) &&
        (arg_item->xDD4_itemVar.pokemon.x0 == 7) &&
        ((hit->sfx_kind == 1U) || (hit->sfx_kind == 2U)))
    {
        lbAudioAx_800237A8(0x61A87, 0x7FU, 0x40U);
    } else if ((kind != It_PKind_Random) ||
               (arg_item->xDD4_itemVar.pokemon.x0 != 8) ||
               ((hit->sfx_kind != 1U) && (hit->sfx_kind != 2U)))
    {
        lbColl_80005BB0(hit, -1);
    }
}

/**
 * @brief Master item-to-item collision detection routine.
 * @details Tests all active item pairs for hitbox vs hitbox clanking, hitbox vs hurtbox
 * damage, and inert collision touches.
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_802706D0(Item_GObj* arg_item_gobj)
{
    u32 hit_index;
    u32 hurt_index;
    Item* arg_item;
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    bool chk;
    s32 count;
    Item* item;
    PAD_STACK(12);

    chk = false;
    arg_item = GET_ITEM(arg_item_gobj);
    for (item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM]; item_gobj != NULL;
         item_gobj = item_gobj->next)
    {
        item = item_gobj->user_data;
        if (arg_item_gobj == item_gobj) {
            chk = true;
            continue;
        } else if (((arg_item->owner == NULL) && (item->owner == NULL) &&
                    !item->xDCD_flag.x0.b7 && !arg_item->xDCE_flag.x0.b2) ||
                   (ftLib_IsFighter(item->owner) &&
                    ftLib_IsFighter(arg_item->owner) &&
                    ftLib_IsSamePlayer(arg_item->owner, item->owner) &&
                    !item->xDCD_flag.x0.b7 && !arg_item->xDCE_flag.x0.b2) ||
                   (gm_8016B168() && !gm_8016B0D4() &&
                    !item->xDCD_flag.x0.b6 && !arg_item->xDCE_flag.x0.b1 &&
                    (item->x20_team_id == arg_item->x20_team_id)))
        {
            continue;
        }
        if (chk && !arg_item->xDD0_flag.x0.b1) {
            count = 0;
            for (hit_index = 0; hit_index < 4; hit_index++) {
                HitCapsule* arg_hit = &arg_item->x5D4_hitboxes[hit_index].hit;
                HitCapsule* tmp_hit = arg_hit;
                if ((arg_hit->state != HitCapsule_Disabled) &&
                    (arg_hit->element != HitElement_Catch) &&
                    ((arg_hit->x40_b2 && (item->ground_or_air == GA_Air)) ||
                     (arg_hit->x40_b3 &&
                      (item->ground_or_air == GA_Ground))) &&
                    !lbColl_8000ACFC(item, tmp_hit))
                {
                    it_804D6D1C[hit_index] = 1;
                    count++;
                } else {
                    it_804D6D1C[hit_index] = 0;
                }
            }
        }
        for (hit_index = 0; hit_index < 4; hit_index++) {
            hit = &item->x5D4_hitboxes[hit_index].hit;
            if ((hit->state == HitCapsule_Disabled) || (hit->x42_b7 != 1) ||
                ((!hit->x40_b2 || (arg_item->ground_or_air != GA_Air)) &&
                 (!hit->x40_b3 || (arg_item->ground_or_air != GA_Ground))) ||
                lbColl_8000ACFC(arg_item, hit))
            {
                continue;
            }
            if (chk && !arg_item->xDD0_flag.x0.b1 && (count != 0)) {
                u32 i;
                bool hitbox_clanked = false;
                for (i = 0; i < 4U; i++) {
                    if (it_804D6D1C[i] != 0) {
                        HitCapsule* arg_hit = &arg_item->x5D4_hitboxes[i].hit;
                        HitCapsule* tmp_hit = arg_hit;
                        if ((hit->element == HitElement_Inert) ||
                            (arg_hit->element == HitElement_Inert))
                        {
                            if ((hit->element != arg_hit->element) &&
                                lbColl_80007AFC(hit, tmp_hit, item->scl,
                                                arg_item->scl))
                            {
                                if (hit->element == HitElement_Inert) {
                                    item->xDCE_flag.x0.b6 = 1;
                                    item->toucher = arg_item_gobj;
                                } else {
                                    arg_item->xDCE_flag.x0.b6 = 1;
                                    arg_item->toucher = item->entity;
                                }
                                hitbox_clanked = true;
                                break;
                            }
                        } else if ((hit->x40_b0 == 1) &&
                                   (arg_hit->x40_b0 == 1) &&
                                   lbColl_80007AFC(hit, tmp_hit, item->scl,
                                                   arg_item->scl))
                        {
                            it_8026FE68(item, hit, arg_item, tmp_hit);
                            hitbox_clanked = true;
                            break;
                        }
                    }
                }
                if (hitbox_clanked) {
                    continue;
                }
            }
            if (arg_item->xAC8_hurtboxNum == 0) {
                continue;
            }
            if (hit->element == HitElement_Inert) {
                u32 i;
                for (i = 0; i < arg_item->xAC8_hurtboxNum; i++) {
                    if (lbColl_80008248(hit, &arg_item->xACC_itemHurtbox[i],
                                        NULL, item->scl, arg_item->scl, 0.0f))
                    {
                        item->xDCE_flag.x0.b6 = 1;
                        item->toucher = arg_item_gobj;
                    }
                }
            } else if (arg_item->xD0C != 2) {
                for (hurt_index = 0; hurt_index < arg_item->xAC8_hurtboxNum;
                     hurt_index++)
                {
                    if (lbColl_8000805C(
                            hit, &arg_item->xACC_itemHurtbox[hurt_index], NULL,
                            0, item->scl, arg_item->scl, 0.0f))
                    {
                        it_802706D0_sub3(
                            item, arg_item, hit,
                            &arg_item->xACC_itemHurtbox[hurt_index]);
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief Computes knockback for an item from a hit capsule based on item attributes.
 * @details Knockback formula:
 * KB = 0.01 * bks * (p11 * (dmg_mul * (p8 * dmg_accum + p9 * (dmg * dmg_accum))) + p12) + kbg
 * Clamped to max knockback threshold (it_804D6D28->x80_float[7]).
 * @param ip Pointer to Item instance
 * @param hit Pointer to connecting HitCapsule
 * @return Computed knockback value, clamped to maximum
 */
f32 it_80270CD8(Item* ip, HitCapsule* hit)
{
    ItemAttr* attr = ip->xCC_item_attr;
    f32 f0;
    f32 knockback;

    if (hit->x28 != 0) {
        knockback = (0.01f * hit->x24 *
              ((it_804D6D28->x80_float[11] *
                (attr->x1C_damage_mul *
                 ((it_804D6D28->x80_float[10] * it_804D6D28->x80_float[8]) +
                  (it_804D6D28->x80_float[9] *
                   (it_804D6D28->x80_float[10] * hit->x28))))) +
               it_804D6D28->x80_float[12])) +
             hit->x2C;
    } else {
        knockback = ((0.01f * hit->x24) *
              ((it_804D6D28->x80_float[11] *
                (attr->x1C_damage_mul *
                 ((it_804D6D28->x80_float[8] * (ip->xC9C + (f32) ip->xCA0)) +
                  (it_804D6D28->x80_float[9] *
                   (hit->damage * (ip->xC9C + (f32) ip->xCA0)))))) +
               it_804D6D28->x80_float[12])) +
             hit->x2C;
    }
    if (knockback >= it_804D6D28->x80_float[7]) {
        knockback = it_804D6D28->x80_float[7];
    }
    return knockback;
}

struct it_80270E30_hurt_pos {
    Vec3 v;
};

struct it_80270E30_damage_log {
    DamageLogEntry* v;
};

struct it_80270E30_hurt_pos_p {
    Vec3* v;
};

/**
 * @brief Processes damage log entries, applies maximum knockback, and spawns elemental hit effects.
 * @details Evaluates all logged hits, determines the highest knockback attack, spawns
 * element-specific particles (Fire, Electric, Slash, Coin, Ice, Dark, etc.), and updates
 * attacker identity and knockback angle on the item.
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_80270E30(Item_GObj* arg_item_gobj)
{
    Item* arg_item;
    u32 index;
    UNUSED f32 unused_float1;
    struct it_80270E30_hurt_pos hurt_pos;
    struct it_80270E30_damage_log damage_log;
    HSD_GObj* item_owner_gobj;
    f32 knockback_cap;
    f32 dir;
    f32 knockback;
    f32 max_knockback;
    UNUSED f32 unused_float2;
    UNUSED f32 unused_float3;
    UNUSED f32 unused_float4;
    f32 dmg_f32;
    UNUSED s32 unused_int0;
    s32 element;
    Item* item;
    DamageLogEntry* dominant_hit;
    struct it_80270E30_hurt_pos_p hurt_pos_p;
    u32 max_kb_idx;
    HitCapsule* hit2;
    ItemAttr* attr;
    Vec3* hurt_coll_pos;
    Fighter* fighter;
    HitCapsule* hit;
    Item* arg_item2;

    if (it_804D6D18 != 0U) {
        arg_item = arg_item_gobj->user_data;
        max_knockback = -1.0f;
        {
            hurt_pos_p.v = &hurt_pos.v;
            damage_log.v = it_804A0E70;
            index = 0;
            while (index < it_804D6D18) {
                hit = damage_log.v->x8;
                attr = arg_item->xCC_item_attr;
                (void) attr;
                if (hit->x28 != 0) {
                    knockback =
                        (0.01f * hit->x24 *
                         ((it_804D6D28->x80_float[11] *
                           (attr->x1C_damage_mul *
                            ((it_804D6D28->x80_float[10] *
                              it_804D6D28->x80_float[8]) +
                             (it_804D6D28->x80_float[9] *
                              (it_804D6D28->x80_float[10] * hit->x28))))) +
                          it_804D6D28->x80_float[12])) +
                        hit->x2C;
                } else {
                    knockback =
                        ((0.01f * hit->x24) *
                         ((it_804D6D28->x80_float[11] *
                           (attr->x1C_damage_mul *
                            ((it_804D6D28->x80_float[8] *
                              (arg_item->xC9C + (f32) arg_item->xCA0)) +
                             (it_804D6D28->x80_float[9] *
                              (hit->damage *
                               (arg_item->xC9C + (f32) arg_item->xCA0)))))) +
                          it_804D6D28->x80_float[12])) +
                        hit->x2C;
                }
                knockback_cap = it_804D6D28->x80_float[7];
                if (knockback >= knockback_cap) {
                    knockback = knockback_cap;
                }
                if (!arg_item->xDCF_flag.x0.b1) {
                    if ((arg_item->hold_kind == ITEM_HOLD_4) ||
                        (arg_item->hold_kind == ITEM_HOLD_6))
                    {
                        dmg_f32 = hit->damage;
                        hit2 = damage_log.v->x8;
                        arg_item2 = arg_item_gobj->user_data;
                        hurt_coll_pos = &hit2->hurt_coll_pos;
                        element = hit_effect_ids[hit2->element];
                        switch (element) {
                        case Ef_Id_Unk1000:
                            efSync_Spawn(Ef_Id_Unk1000, arg_item_gobj,
                                         hurt_coll_pos, &dmg_f32);
                            break;
                        case Ef_Id_Unk1001:
                        case Ef_Id_Unk1002:
                        case Ef_Id_Unk1004:
                        case Ef_Id_Unk1046:
                        case Ef_Id_Unk1145:
                            efSync_Spawn(hit_effect_ids[hit2->element],
                                         arg_item_gobj, hurt_coll_pos,
                                         arg_item2);
                            break;
                        case Ef_Id_Unk1005:
                            efSync_Spawn(hit_effect_ids[hit2->element],
                                         arg_item_gobj, hurt_coll_pos,
                                         &arg_item2->facing_dir);
                            break;
                        }
                    } else {
                        hurt_pos.v = hit->hurt_coll_pos;
                        efSync_Spawn(Ef_Id_Unk1000, arg_item_gobj,
                                     hurt_pos_p.v, &damage_log.v->x8->damage);
                    }
                }
                if (knockback > max_knockback) {
                    max_knockback = knockback;
                    max_kb_idx = index;
                }
                damage_log.v++;
                index++;
            }
        }
        dominant_hit = &it_804A0E70[max_kb_idx];
        switch (dominant_hit->x0) {
        case 1:
            fighter = dominant_hit->x4;
            arg_item->xCB0_source_ply = (s32) fighter->player_idx;
            arg_item->xCEC_fighterGObj = fighter->gobj;
            arg_item->xCF0_itemGObj = NULL;
            if (arg_item->pos.x > fighter->cur_pos.x) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item->xCCC_incDamageDirection = dir;
            it_8027B4A4(fighter->gobj, arg_item_gobj);
            break;
        case 2:
            item = dominant_hit->x4;
            item_owner_gobj = item->owner;
            if ((item_owner_gobj != NULL) && ftLib_IsFighter(item_owner_gobj))
            {
                arg_item->xCB0_source_ply =
                    (s32) ((Fighter*) item_owner_gobj->user_data)->player_idx;
                arg_item->xCEC_fighterGObj = NULL;
                arg_item->xCF0_itemGObj = item_owner_gobj;
            } else {
                arg_item->xCB0_source_ply = 6;
                arg_item->xCEC_fighterGObj = NULL;
                arg_item->xCF0_itemGObj = NULL;
            }
            arg_item->xCB4 = item->kind;
            arg_item->xCE0 = item->pos;
            if (ABS(item->x40_vel.x) < it_804D6D28->x78_float) {
                if (arg_item->pos.x > item->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (item->x40_vel.x < 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            arg_item->xCCC_incDamageDirection = dir;
            it_8027B508(item->entity, arg_item_gobj);
            break;
        }
        arg_item->xCAC_angle = dominant_hit->x8->kb_angle;
        arg_item->xCC8_knockback = max_knockback;
        arg_item->xCC4 = dominant_hit->x8->element;
        arg_item->xDCF_flag.x0.b6 = dominant_hit->x8->x43_b0;
    }
}

/**
 * @brief Updates position and advances interpolation state for a single item hitbox.
 * @param arg_item_gobj Pointer to Item GObj
 * @param index Index of the hitbox (0-3)
 */
void it_8027129C(Item_GObj* arg_item_gobj, s32 index)
{
    HitCapsuleState state;
    HitCapsule* hit;
    Item* item;

    item = GET_ITEM(arg_item_gobj);
    hit = &item->x5D4_hitboxes[index].hit;
    state = hit->state;

    switch (state) {
    case HitCapsule_Enabled:
        lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
        hit->x58 = hit->x4C;
        hit->state = HitCapsule_Unk2;
        item->xDAA.xDAA_flag.x0.b2 = 1;
        return;
    case HitCapsule_Unk2:
        hit->state = HitCapsule_Unk3;
        /* fallthrough */
    case HitCapsule_Unk3:
        hit->x58 = hit->x4C;
        lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
        /* fallthrough */
    case HitCapsule_Unk4:
    case HitCapsule_Disabled:
        return;
    }
}

/**
 * @brief Updates world positions and advances interpolation states for all hitboxes on an item.
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_8027137C(Item_GObj* arg_item_gobj)
{
    u32 index;
    HitCapsule* hit;
    Item* arg_item;

    index = 0U;
    while (index < 4U) {
        arg_item = arg_item_gobj->user_data;
        hit = &arg_item->x5D4_hitboxes[index].hit;
        switch (hit->state) {
        case HitCapsule_Unk4:
        case HitCapsule_Disabled:
            break;
        case HitCapsule_Enabled:
            lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
            hit->x58 = hit->x4C;
            hit->state = HitCapsule_Unk2;
            arg_item->xDAA.xDAA_flag.x0.b2 = 1;
            break;
        case HitCapsule_Unk2:
            hit->state = HitCapsule_Unk3;
            /* fallthrough */
        case HitCapsule_Unk3:
            hit->x58 = hit->x4C;
            lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
            break;
        }
        index++;
    }
}

/**
 * @brief Clears hit status and disables all hitboxes on an item.
 * @param item_gobj Pointer to Item GObj
 */
void it_8027146C(Item_GObj* item_gobj)
{
    int i;
    Item* item = GET_ITEM(item_gobj);
    for (i = 0; i < ARRAY_SIZE(item->x5D4_hitboxes); i++) {
        lbColl_80008A5C(&item->x5D4_hitboxes[i].hit);
    }
}

/**
 * @brief Resets the skip position update flag on all hurtboxes of an item.
 * @param item_gobj Pointer to Item GObj
 */
void it_802714C0(Item_GObj* item_gobj)
{
    u32 index;
    Item* item;
    HurtCapsule* hurt;

    item = item_gobj->user_data;
    index = 0U;
    while (index < item->xAC8_hurtboxNum) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->skip_update_pos = 0;
        index++;
    }
    item->xDAA.xDAA_flag.x0.b1 = 1;
}

/**
 * @brief Sets the hurtbox state (enabled, disabled, invulnerable) across all item hurtboxes.
 * @param item_gobj Pointer to Item GObj
 * @param state HurtCapsuleState to apply
 */
void it_80271508(Item_GObj* item_gobj, HurtCapsuleState state)
{
    u32 index;
    Item* item;
    HurtCapsule* hurt;

    item = item_gobj->user_data;
    index = 0U;
    while (index < item->xAC8_hurtboxNum) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->state = state;
        index++;
    }
}

/**
 * @brief Copies hurtbox offsets and scale from argument into the specified item hurtbox.
 * @param item_gobj Pointer to Item GObj
 * @param index Hurtbox index
 * @param arg_hurt Source HurtCapsule containing offsets and scale
 */
void it_80271534(Item_GObj* item_gobj, s32 index, HurtCapsule* arg_hurt)
{
    HurtCapsule* hurt;
    Item* item;

    item = item_gobj->user_data;
    if (item->xC4_article_data->x8_hurtbones != NULL) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->a_offset = arg_hurt->a_offset;
        hurt->b_offset = arg_hurt->b_offset;
        hurt->scale = arg_hurt->scale;
    }
}

/**
 * @brief Reads hurtbox offsets and scale from the specified item hurtbox into argument.
 * @param item_gobj Pointer to Item GObj
 * @param index Hurtbox index
 * @param arg_hurt Destination HurtCapsule to receive offsets and scale
 */
void it_80271590(Item_GObj* item_gobj, s32 index, HurtCapsule* arg_hurt)
{
    u8 _[8];
    Vec3 zero_vec;
    HurtCapsule* hurt;
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->xC4_article_data->x8_hurtbones != NULL) {
        hurt = &item->xACC_itemHurtbox[index];
        arg_hurt->a_offset = hurt->a_offset;
        arg_hurt->b_offset = hurt->b_offset;
        arg_hurt->scale = hurt->scale;
        return;
    }
    zero_vec.x = zero_vec.y = zero_vec.z = 0.0f;
    arg_hurt->a_offset = zero_vec;
    arg_hurt->b_offset = zero_vec;
    arg_hurt->scale = 0.0f;
}

/**
 * @brief Initializes item hurtboxes and dynamic collision bones from Article data.
 * @param item_gobj Pointer to Item GObj
 */
void it_8027163C(Item_GObj* item_gobj)
{
    Item* item;
    Article* article;
    ItHurtBoneList* it_hurtbox;
    ItCollDynamics* it_dynams;
    u32 cnt;
    HurtCapsule* hurt;
    ItHurtBoneDesc* hurt_dyn_desc;
    s32 index;
    PAD_STACK(16);

    item = item_gobj->user_data;
    article = item->xC4_article_data;
    it_hurtbox = article->x8_hurtbones;
    it_dynams = (ItCollDynamics*) article->x14_dynamics;
    if (it_hurtbox != NULL) {
        if (it_hurtbox->count > 2) {
            HSD_ASSERTREPORT(0x3F4, 0, "item hit num over!\n");
        }
        cnt = 0U;
        item->xAC8_hurtboxNum = it_hurtbox->count;
        index = 0;
        while (cnt < it_hurtbox->count) {
            hurt = &item->xACC_itemHurtbox[index];
            hurt_dyn_desc = &it_hurtbox->descs[index];
            item->xACC_itemHurtbox[index].state = HurtCapsule_Enabled;
            if (hurt_dyn_desc->bone_id != 0) {
                if (item->xBBC_dynamicBoneTable == NULL) {
                    HSD_ASSERTREPORT(0x402, 0, "item can't init hit!\n");
                }
                hurt->bone =
                    item->xBBC_dynamicBoneTable->bones[hurt_dyn_desc->bone_id];
            } else {
                hurt->bone = item_gobj->hsd_obj;
            }
            index++;
            cnt++;
            hurt->a_offset = hurt_dyn_desc->a_offset;
            hurt->b_offset = hurt_dyn_desc->b_offset;
            hurt->scale = hurt_dyn_desc->scale;
        }
    } else {
        item->xAC8_hurtboxNum = 0;
    }
    if (it_dynams != NULL) {
        if (it_dynams->count > 2) {
            HSD_ASSERTREPORT(0x415, 0, "item dynamics hit num over!\n");
        }
        cnt = 0U;
        item->xB68 = it_dynams->count;
        index = 0;
        while (cnt < it_dynams->count) {
            struct xB6C_t* vars = &item->xB6C_vars[cnt];
            ItCollDynamicsDesc* bone_dyn_desc = &it_dynams->descs[index];
            vars->xB90 = bone_dyn_desc->bone_id;
            vars->xB7C =
                item->xBBC_dynamicBoneTable->bones[bone_dyn_desc->bone_id];
            vars->xB6C = bone_dyn_desc->offset;
            vars->xB78 = bone_dyn_desc->size;
            index++;
            cnt++;
        }
    }
}

/**
 * @brief Rotates an item's Environmental Collision Box (ECB) around the Z axis.
 * @param item Pointer to Item instance
 * @param angle Rotation angle in radians
 */
void it_80271830(Item* item, f32 angle)
{
    Vec3 top_vec;
    Vec3 bottom_vec;
    Vec3 right_vec;
    Vec3 left_vec;
    UNUSED unsigned char _pad[24];
    Vec3 unit_z = *(Vec3*) &it_803B8560;
    f32 left_pos;
    f32 top_pos;
    f32 right_pos;
    f32 bottom_pos;

    while (angle < 0.0f) {
        angle += M_TAU;
    }
    while (angle > (M_TAU)) {
        angle -= M_TAU;
    }
    top_vec.y = item->xBEC.top;
    top_vec.x = top_vec.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&top_vec, &unit_z, angle);
    bottom_vec.y = item->xBEC.bottom;
    bottom_vec.x = bottom_vec.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&bottom_vec, &unit_z, angle);
    right_vec.x = item->xBEC.right;
    right_vec.y = right_vec.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&right_vec, &unit_z, angle);
    left_vec.x = item->xBEC.left;
    left_vec.y = left_vec.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&left_vec, &unit_z, angle);
    left_pos = (top_vec.x > bottom_vec.x) ? top_vec.x : bottom_vec.x;
    left_pos = (left_pos > right_vec.x) ? left_pos : right_vec.x;
    left_pos = (left_pos > left_vec.x) ? left_pos : left_vec.x;
    item->xBEC.left = left_pos;
    top_pos = (top_vec.y > bottom_vec.y) ? top_vec.y : bottom_vec.y;
    top_pos = (top_pos > right_vec.y) ? top_pos : right_vec.y;
    top_pos = (top_pos > left_vec.y) ? top_pos : left_vec.y;
    item->xBEC.top = top_pos;
    right_pos = (top_vec.x < bottom_vec.x) ? top_vec.x : bottom_vec.x;
    right_pos = (right_pos < right_vec.x) ? right_pos : right_vec.x;
    right_pos = (right_pos < left_vec.x) ? right_pos : left_vec.x;
    item->xBEC.right = right_pos;
    bottom_pos = (top_vec.y < bottom_vec.y) ? top_vec.y : bottom_vec.y;
    bottom_pos = (bottom_pos < right_vec.y) ? bottom_pos : right_vec.y;
    bottom_pos = (bottom_pos < left_vec.y) ? bottom_pos : left_vec.y;
    item->xBEC.bottom = bottom_pos;
}

/**
 * @brief Computes rotated Environmental Collision Box (ECB) from joint rotation.
 * @param item_gobj Pointer to Item GObj
 */
void it_80271A58(Item_GObj* item_gobj)
{
    f32 rotate;
    Item* item;
    HSD_JObj* jobj;

    item = GET_ITEM(item_gobj);
    item->xBEC = item->xBDC;
    if ((item->facing_dir == 1.0f) && (item->xDC8_word.flags.x19 == 1)) {
        f32 temp = -item->xBEC.right;
        item->xBEC.right = -item->xBEC.left;
        item->xBEC.left = temp;
    }
    jobj = it_802746F8(item_gobj);
    if (item->xDC8_word.flags.x17 == 0) {
        rotate = HSD_JObjGetRotationZ(jobj);
    } else if (item->xDC8_word.flags.x17 == 1) {
        rotate = HSD_JObjGetRotationX(jobj);
    } else {
        rotate = HSD_JObjGetRotationY(jobj);
    }
    it_80271830(item, rotate);
}

/**
 * @brief Checks item ECB overlap against active fighters and applies nudge velocity.
 * @param item_gobj Pointer to Item GObj
 */
void it_80271B60(Item_GObj* item_gobj)
{
    f32 x_pos;
    itECB* ecb;
    UNUSED Item_FtTrack* unused_ft_track;
    f32 x_float;
    Vec3 item_pos;
    f32 y_pos;
    f32 x_float_mag;
    HSD_JObj* item_jobj;
    f32 dir;
    u32 cnt;
    Item* item;
    u8 _padA[8];

    item_jobj = GET_JOBJ(item_gobj);
    item = GET_ITEM(item_gobj);
    if (Item_804A0CCC.x154.x0.b0 != 1) {
        HSD_JObjGetTranslation(item_jobj, &item_pos);
        cnt = 0U;

        while (cnt < Item_804A0CCC.count) {
            ecb = &Item_804A0CCC.ecb_offset_arr[cnt];
            y_pos = Item_804A0CCC.ft_pos_arr[cnt].y;
            x_pos = Item_804A0CCC.ft_pos_arr[cnt].x;
            if (itColl_chkECBOverlap(x_pos, y_pos, &item->xBEC, ecb, &item_pos)) {
                if (ABS(item_pos.x - x_pos) < 0.001f) {
                    if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else {
                    if (item_pos.x - x_pos < 0.0f) {
                        dir = -1.0f;
                    } else {
                        dir = 1.0f;
                    }
                }
                item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                item->xDC0 |= 1;
            }
            cnt++;
        }
    }
}

/**
 * @brief Checks item ECB overlap against other grounded items and applies mutual nudge velocity.
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_80271D2C(Item_GObj* arg_item_gobj)
{
    u8 _pad[12];
    HSD_JObj* arg_item_jobj = GET_JOBJ(arg_item_gobj);
    Item* arg_item = GET_ITEM(arg_item_gobj);
    Vec3 item_a_pos;
    Vec3 item_b_pos;
    HSD_GObj* item_gobj;
    f32 dir;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    HSD_JObjGetTranslation(arg_item_jobj, &item_a_pos);
    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ(item_gobj);
        item = GET_ITEM(item_gobj);
        if ((arg_item_gobj != item_gobj) && !item->xDC8_word.flags.x13 &&
            (item->ground_or_air == GA_Ground) && !item->xDD1_flag.x0.b0 &&
            ((item->hold_kind != ITEM_HOLD_3) ||
             ((item->hold_kind == ITEM_HOLD_3) &&
              arg_item->xDC8_word.flags
                  .x1E)) // hold_kind 3 is open palm, facing down(?)
        )
        {
            HSD_JObjGetTranslation(item_jobj, &item_b_pos);
            if (itColl_chkECBOverlap(item_b_pos.x, item_b_pos.y, &arg_item->xBEC,
                                     &item->xBEC, &item_a_pos))
            {
                if (ABS(item_a_pos.x - item_b_pos.x) < 0.001f) {
                    if (!item->xDC8_word.flags.x1B) {
                        if (item->x70_nudge.x < 0.0f) {
                            dir = 1.0f;
                        } else {
                            dir = -1.0f;
                        }
                    } else if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else if (item_a_pos.x - item_b_pos.x < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                arg_item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                arg_item->xDC0 |= 2;
            }
        }
        item_gobj = item_gobj->next;
    }
}

/**
 * @brief Checks heavy item ECB overlap and applies horizontal nudge velocity to lighter items.
 * @param gobj Pointer to Item GObj
 */
void it_80271F78(Item_GObj* gobj)
{
    u8 _pad[12];
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* arg_item = GET_ITEM(gobj);
    Vec3 item_a_pos;
    Vec3 item_b_pos;
    HSD_GObj* item_gobj;
    f32 dir;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    HSD_JObjGetTranslation(jobj, &item_a_pos);
    item_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM];

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ(item_gobj);
        item = GET_ITEM(item_gobj);
        if ((gobj != item_gobj) && !item->xDC8_word.flags.x13 &&
            (item->ground_or_air == GA_Ground) && !item->xDD1_flag.x0.b0 &&
            (itIsHeavy(item_gobj) == 1))
        {
            HSD_JObjGetTranslation(item_jobj, &item_b_pos);
            if (itColl_chkECBOverlap(item_b_pos.x, item_b_pos.y, &arg_item->xBEC,
                                     &item->xBEC, &item_a_pos))
            {
                if (ABS(item_a_pos.x - item_b_pos.x) < 0.001f) {
                    if (!item->xDC8_word.flags.x1B) {
                        if (item->x70_nudge.x < 0.0f) {
                            dir = 1.0f;
                        } else {
                            dir = -1.0f;
                        }
                    } else if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else if (item_a_pos.x - item_b_pos.x < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                arg_item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                arg_item->xDC0 |= 2;
            }
        }
        item_gobj = item_gobj->next;
    }
}

/**
 * @brief Master ECB collision update for grounded items.
 * @details Evaluates ECB overlap against fighters, other grounded items, and heavy items,
 * applying mutual horizontal nudge velocities.
 * @param item_gobj Pointer to Item GObj
 */
void it_802721B8(Item_GObj* item_gobj)
{
    u8 temp_r3;
    Item* item;

    item = item_gobj->user_data;
    item->x70_nudge.z = 0.0f;
    item->x70_nudge.y = 0.0f;
    item->x70_nudge.x = 0.0f;
    item->xDC0 = 0;
    if (!item->xDC8_word.flags.x13) {
        if ((item->xDC8_word.flags.x1A == 1) &&
            (item->ground_or_air == GA_Ground))
        {
            if (item->xDC8_word.flags.x1C) {
                it_80271B60(item_gobj);
            }
            if (item->xDC8_word.flags.x1D) {
                it_80271D2C(item_gobj);
            }
        }
    }
    if (!item->xDC8_word.flags.x13 && (item->ground_or_air == GA_Ground) &&
        (itIsHeavy(item_gobj) == 1))
    {
        it_80271F78(item_gobj);
    }
}

/**
 * @brief Clears ECB nudge random flag (x1B) on an item.
 * @param item_gobj Pointer to Item GObj
 */
void it_80272280(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1B = 0;
}

/**
 * @brief Sets ECB nudge random flag (x1B) on an item.
 * @param item_gobj Pointer to Item GObj
 */
void it_80272298(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1B = 1;
}

/**
 * @brief Updates fighter ECB tracking cache if item is head of item list.
 * @param item_gobj Pointer to Item GObj
 */
void it_802722B0(Item_GObj* item_gobj)
{
    if (item_gobj == HSD_GObjPLinkHead[HSD_GOBJ_PLINK_ITEM]) {
        ftCo_80098634(&Item_804A0CCC);
        Item_804A0CCC.x154.x0.b0 = 0;
    }
}

/**
 * @brief Updates world space transform positions for dynamic collision bones.
 * @param item_gobj Pointer to Item GObj
 */
void it_80272304(Item_GObj* item_gobj)
{
    u32 i;
    Item* item = GET_ITEM(item_gobj);
    for (i = 0; i < item->xB68; i++) {
        struct xB6C_t* bone_var = &item->xB6C_vars[i];
        lb_8000B1CC(bone_var->xB7C, &bone_var->xB6C, &bone_var->xB84);
    }
}

/**
 * @brief Updates item owner and team ID from last attacking fighter or item.
 * @param arg_item_gobj Pointer to Item GObj
 * @return Pointer to resolved owner HSD_GObj
 */
HSD_GObj* it_8027236C(Item_GObj* arg_item_gobj)
{
    HSD_GObj* fighter_gobj;
    HSD_GObj* unk_owner_gobj;
    Item* arg_item;

    arg_item = arg_item_gobj->user_data;
    fighter_gobj = arg_item->xCEC_fighterGObj;
    if (fighter_gobj != NULL) {
        arg_item->owner = fighter_gobj;
        arg_item->x20_team_id = ftLib_GetTeam(arg_item->xCEC_fighterGObj);
    } else {
        unk_owner_gobj = arg_item->xCF0_itemGObj;
        if (unk_owner_gobj != NULL) {
            arg_item->owner = unk_owner_gobj;
            arg_item->x20_team_id = ftLib_GetTeam(arg_item->xCF0_itemGObj);
        } else {
            arg_item->owner = NULL;
            arg_item->x20_team_id = U8_MAX;
        }
    }
    it_8027B1F4(arg_item_gobj);
    return arg_item->owner;
}

/**
 * @brief Updates item owner and team ID from xCFC fighter pointer.
 * @param arg_item_gobj Pointer to Item GObj
 * @return Pointer to resolved owner HSD_GObj
 */
HSD_GObj* it_802723FC(Item_GObj* arg_item_gobj)
{
    Item* arg_item;

    arg_item = arg_item_gobj->user_data;
    if (ftLib_IsFighter(arg_item->xCFC)) {
        arg_item->owner = arg_item->xCFC;
        arg_item->x20_team_id = ftLib_GetTeam(arg_item->owner);
    } else {
        arg_item->owner = NULL;
        arg_item->x20_team_id = U8_MAX;
    }
    return arg_item->owner;
}

/**
 * @brief Calculates scaled and staled damage for an item hitbox based on owning fighter.
 * @details Accounts for giant/tiny scale factors and move staling.
 * @param hitbox Pointer to HitCapsule to update
 * @param damage Base damage value
 * @param arg_item_gobj Pointer to Item GObj
 */
void it_80272460(HitCapsule* hitbox, u32 damage, Item_GObj* arg_item_gobj)
{
    HSD_GObj* owner_gobj;
    u32 dmg;
    Item* arg_item;
    Fighter* owner;

    dmg = damage;
    arg_item = GET_ITEM(arg_item_gobj);
    owner_gobj = arg_item->owner;
    if (ftLib_IsFighter(owner_gobj)) {
        owner = GET_FIGHTER(owner_gobj);
        if (owner->x34_scale.y != 1.0f) {
            dmg = 0.999f + ftCo_CalcYScaledKnockback(dmg, owner->x34_scale.y,
                                                     Fighter_804D6524->x4);
        }
        hitbox->unk_count = dmg;
        hitbox->damage =
            ft_80089228(owner, arg_item->xD88_attackID,
                        arg_item->xD8C_attack_instance, hitbox->unk_count);
        return;
    }
    hitbox->unk_count = dmg;
    hitbox->damage = dmg;
}
