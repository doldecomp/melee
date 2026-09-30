/**
 * @file itcoll.h
 * @brief Item collision detection declarations.
 * @details Implements collision detection for items in Super Smash Bros. Melee, including:
 * - Item-to-item collisions (hitbox clanking, hurtbox damage, inert touches)
 * - Item-to-fighter collisions (fighter attacks hitting items, item grab/catch hitboxes)
 * - Environmental Collision Box (ECB) overlap and mutual pushing/nudging
 * - Damage logging, knockback calculation, and elemental hit effect dispatch
 * - Hitbox / hurtbox state updating, scaling, and staling
 * Module prefix: it (Item)
 */

#ifndef _itcoll_h_
#define _itcoll_h_

#include <Runtime/platform.h>

#include <melee/it/forward.h>

#include <melee/lb/types.h>

/**
 * @brief Resets the global item damage log counter to zero.
 */
/* 26F9A0 */ void it_8026F9A0(void);

/**
 * @brief Records a hit interaction into the global item damage log array.
 * @param hit_type Damage source type (1 = fighter attack, 2 = item collision)
 * @param attacker Pointer to attacking Fighter or Item instance
 * @param hit Pointer to offensive HitCapsule that connected
 * @param item Pointer to victim Item instance
 * @param hurt Pointer to defensive HurtCapsule that was struck
 */
/* 26F9AC */ void it_8026F9AC(s32 hit_type, void* attacker, HitCapsule* hit, Item* item, HurtCapsule* hurt);

/**
 * @brief Resets hit tracking on matching item hitboxes when clanking or hitting.
 * @param item Pointer to Item instance
 * @param hit Pointer to reference HitCapsule
 * @param hit_type Interaction type
 * @param victim Target item/victim
 * @param check Flag indicating whether to clear hitbox hit tracking
 */
/* 26FA2C */ void it_8026FA2C(Item* item, HitCapsule* hit, s32 hit_type, Item* victim, bool check);

/**
 * @brief Resets hit tracking across all items sharing an ignoreItemID group.
 * @param item Pointer to Item instance
 * @param hit Pointer to reference HitCapsule
 * @param hit_type Interaction type
 * @param victim Target victim pointer
 * @param check Flag indicating whether to clear hitbox hit tracking
 */
/* 26FAC4 */ void it_8026FAC4(Item* item, HitCapsule* hit, s32 hit_type, void* victim, bool check);

/**
 * @brief Records a fighter hit interaction across all hitboxes of an item group.
 * @param item Pointer to Item instance
 * @param hit Pointer to reference HitCapsule
 * @param hit_type Interaction type
 * @param fighter Pointer to striking Fighter
 */
/* 26FC00 */ void it_8026FC00(Item* item, HitCapsule* hit, s32 hit_type, Fighter* fighter);

/**
 * @brief Updates item hitbox collision interpolation or copies state from matching active hitboxes.
 * @param item Pointer to Item instance
 * @param hit Pointer to HitCapsule to update
 */
/* 26FCF8 */ void it_8026FCF8(Item* item, HitCapsule* hit);

/**
 * @brief Resolves item-to-item hitbox clanking when two active hitboxes collide.
 * @details Compares damage values against clank threshold (it_804D6D28->xB4),
 * spawns clank spark effect (0x41C), and calculates recoil damage direction.
 * @param item_a Pointer to first Item
 * @param hit_a Pointer to first Item's HitCapsule
 * @param item_b Pointer to second Item
 * @param hit_b Pointer to second Item's HitCapsule
 */
/* 26FE68 */ void it_8026FE68(Item* item_a, HitCapsule* hit_a, Item* item_b, HitCapsule* hit_b);

/**
 * @brief Detects item grab / catch hitboxes connecting with fighters.
 * @details Checks catch-element hitboxes against grabbable fighter hurtboxes
 * and records the grab victim if valid.
 * @param item_gobj Pointer to Item GObj
 */
/* 2701BC */ void it_802701BC(Item_GObj* item_gobj);

/**
 * @brief Checks fighter attack hitboxes colliding with an item's defensive hurtboxes.
 * @details Handles team checks, friendly fire, damage accumulation, damage logging,
 * and hit sound effects.
 * @param item_gobj Pointer to Item GObj
 */
/* 2703E8 */ void it_802703E8(Item_GObj* item_gobj);

/**
 * @brief Master item-to-item collision detection routine.
 * @details Tests all active item pairs for hitbox vs hitbox clanking, hitbox vs hurtbox
 * damage, and inert collision touches.
 * @param item_gobj Pointer to Item GObj
 */
/* 2706D0 */ void it_802706D0(Item_GObj* item_gobj);

/**
 * @brief Computes knockback for an item from a hit capsule based on item attributes.
 * @param item Pointer to Item instance
 * @param hit Pointer to connecting HitCapsule
 * @return Computed knockback value, clamped to maximum
 */
/* 270CD8 */ f32 it_80270CD8(Item* item, HitCapsule* hit);

/**
 * @brief Processes damage log entries, applies maximum knockback, and spawns elemental hit effects.
 * @details Evaluates all logged hits, determines the highest knockback attack, spawns
 * element-specific particles (Fire, Electric, Slash, Coin, Ice, Dark, etc.), and updates
 * attacker identity and knockback angle on the item.
 * @param item_gobj Pointer to Item GObj
 */
/* 270E30 */ void it_80270E30(Item_GObj* item_gobj);

/**
 * @brief Updates position and advances interpolation state for a single item hitbox.
 * @param item_gobj Pointer to Item GObj
 * @param index Index of the hitbox (0-3)
 */
/* 27129C */ void it_8027129C(Item_GObj* item_gobj, s32 index);

/**
 * @brief Updates world positions and advances interpolation states for all hitboxes on an item.
 * @param item_gobj Pointer to Item GObj
 */
/* 27137C */ void it_8027137C(Item_GObj* item_gobj);

/**
 * @brief Clears hit status and disables all hitboxes on an item.
 * @param item_gobj Pointer to Item GObj
 */
/* 27146C */ void it_8027146C(Item_GObj* item_gobj);

/**
 * @brief Resets the skip position update flag on all hurtboxes of an item.
 * @param item_gobj Pointer to Item GObj
 */
/* 2714C0 */ void it_802714C0(Item_GObj* item_gobj);

/**
 * @brief Sets the hurtbox state (enabled, disabled, invulnerable) across all item hurtboxes.
 * @param item_gobj Pointer to Item GObj
 * @param state HurtCapsuleState to apply
 */
/* 271508 */ void it_80271508(Item_GObj* item_gobj, HurtCapsuleState state);

/**
 * @brief Copies hurtbox offsets and scale from argument into the specified item hurtbox.
 * @param item_gobj Pointer to Item GObj
 * @param index Hurtbox index
 * @param hurt Source HurtCapsule containing offsets and scale
 */
/* 271534 */ void it_80271534(Item_GObj* item_gobj, s32 index, HurtCapsule* hurt);

/**
 * @brief Reads hurtbox offsets and scale from the specified item hurtbox into argument.
 * @param item_gobj Pointer to Item GObj
 * @param index Hurtbox index
 * @param hurt Destination HurtCapsule to receive offsets and scale
 */
/* 271590 */ void it_80271590(Item_GObj* item_gobj, s32 index, HurtCapsule* hurt);

/**
 * @brief Initializes item hurtboxes and dynamic collision bones from Article data.
 * @param item_gobj Pointer to Item GObj
 */
/* 27163C */ void it_8027163C(Item_GObj* item_gobj);

/**
 * @brief Computes rotated Environmental Collision Box (ECB) from joint rotation.
 * @param item_gobj Pointer to Item GObj
 */
/* 271A58 */ void it_80271A58(Item_GObj* item_gobj);

/**
 * @brief Master ECB collision update for grounded items.
 * @details Evaluates ECB overlap against fighters, other grounded items, and heavy items,
 * applying mutual horizontal nudge velocities.
 * @param item_gobj Pointer to Item GObj
 */
/* 2721B8 */ void it_802721B8(Item_GObj* item_gobj);

/**
 * @brief Clears ECB nudge random flag (x1B) on an item.
 * @param item_gobj Pointer to Item GObj
 */
/* 272280 */ void it_80272280(Item_GObj* item_gobj);

/**
 * @brief Sets ECB nudge random flag (x1B) on an item.
 * @param item_gobj Pointer to Item GObj
 */
/* 272298 */ void it_80272298(Item_GObj* item_gobj);

/**
 * @brief Updates fighter ECB tracking cache if item is head of item list.
 * @param item_gobj Pointer to Item GObj
 */
/* 2722B0 */ void it_802722B0(Item_GObj* item_gobj);

/**
 * @brief Updates world space transform positions for dynamic collision bones.
 * @param item_gobj Pointer to Item GObj
 */
/* 272304 */ void it_80272304(Item_GObj* item_gobj);

/**
 * @brief Updates item owner and team ID from last attacking fighter or item.
 * @param item_gobj Pointer to Item GObj
 * @return Pointer to resolved owner HSD_GObj
 */
/* 27236C */ HSD_GObj* it_8027236C(Item_GObj* item_gobj);

/**
 * @brief Updates item owner and team ID from xCFC fighter pointer.
 * @param item_gobj Pointer to Item GObj
 * @return Pointer to resolved owner HSD_GObj
 */
/* 2723FC */ HSD_GObj* it_802723FC(Item_GObj* item_gobj);

/**
 * @brief Calculates scaled and staled damage for an item hitbox based on owning fighter.
 * @details Accounts for giant/tiny scale factors and move staling.
 * @param hitbox Pointer to HitCapsule to update
 * @param damage Base damage value
 * @param item_gobj Pointer to Item GObj
 */
/* 272460 */ void it_80272460(HitCapsule* hitbox, u32 damage, Item_GObj* item_gobj);

#endif
