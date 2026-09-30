/**
 * @file ithitbox.h
 * @brief Item hitbox management
 * @details Handles the activation, scaling, and damage adjustment of offensive item hitboxes.
 * Module prefix: it
 */
#ifndef GALE01_IT_HITBOX
#define GALE01_IT_HITBOX

#include <Runtime/platform.h>

#include <melee/it/forward.h>

#include <dolphin/mtx.h>
#include <melee/it/types.h>

/* 2753DC */ /**
 * @brief Resets item damage dealt and hitbox scaling modifiers.
 * @param item_gobj The item GObj
 */
void it_802753DC(Item_GObj*);
/* 275414 */ /**
 * @brief Enables a specific collision/hitbox flag (xDCD_flag b7).
 * @param item_gobj The item GObj
 */
void it_80275414(Item_GObj*);
/* 27542C */ /**
 * @brief Disables a specific collision/hitbox flag (xDCD_flag b7).
 * @param item_gobj The item GObj
 */
void it_8027542C(Item_GObj*);
/* 275444 */ /**
 * @brief Enables multiple collision flags in xDCD_flag.
 * @param item_gobj The item GObj
 */
void it_80275444(Item_GObj*);

/// Toggle several flags in 0xDCD off
/* 275474 */ /**
 * @brief Disables multiple collision flags in xDCD_flag.
 * @param item_gobj The item GObj
 */
void it_80275474(Item_GObj*);

/* 2754A4 */ /**
 * @brief Enables a specific collision/hitbox flag (xDCE_flag b2).
 * @param item_gobj The item GObj
 */
void it_802754A4(Item_GObj*);
/* 2754BC */ /**
 * @brief Disables a specific collision/hitbox flag (xDCE_flag b2).
 * @param item_gobj The item GObj
 */
void it_802754BC(Item_GObj*);
/* 2754D4 */ /**
 * @brief Enables multiple collision flags in xDCE_flag.
 * @param item_gobj The item GObj
 */
void it_802754D4(Item_GObj*);

/// Toggle several flags in 0xDCE off
/* 275504 */ /**
 * @brief Disables multiple collision flags in xDCE_flag.
 * @param item_gobj The item GObj
 */
void it_80275504(Item_GObj*);

/* 275534 */ /**
 * @brief Sets the scale for all active hitboxes of an item.
 * @param item_gobj The item GObj
 * @param scale The new scale value
 */
void it_80275534(Item_GObj*, f32 scale);
/* 275594 */ /**
 * @brief Multiplies the scale of a specific item hitbox.
 * @param item_gobj The item GObj
 * @param idx The hitbox index (0-3)
 * @param mult The scale multiplier
 */
void it_80275594(Item_GObj*, s32 idx, f32 mult);
/* 2755C0 */ /**
 * @brief Multiplies the scale for all active hitboxes of an item.
 * @param item_gobj The item GObj
 * @param scale The scale multiplier
 */
void it_802755C0(Item_GObj*, f32 scale);
/* 275640 */ /**
 * @brief Multiplies the damage of all active hitboxes of an item.
 * @param item_gobj The item GObj
 * @param damage_mul The damage multiplier
 */
void it_80275640(Item_GObj*, f32 damage_mul);
/* 2756D0 */ /**
 * @brief Sets an item collision/hitlag state variable to 2.
 * @param item_gobj The item GObj
 */
void it_802756D0(Item_GObj*);
/* 2756E0 */ /**
 * @brief Clears an item collision/hitlag state variable and updates collision logic.
 * @param item_gobj The item GObj
 */
void it_802756E0(Item_GObj*);
/* 27570C */ /**
 * @brief Disables a flag (x40_b0) on a specific item hitbox.
 * @param item_gobj The item GObj
 * @param idx The hitbox index
 */
void it_8027570C(Item_GObj*, s32 idx);
/* 27572C */ /**
 * @brief Enables a flag (x40_b0) on a specific item hitbox.
 * @param item_gobj The item GObj
 * @param idx The hitbox index
 */
void it_8027572C(Item_GObj*, s32 idx);
/* 27574C */ /**
 * @brief Updates position and collision boundaries for the item hitboxes.
 * @param item_gobj The item GObj
 */
void it_8027574C(Item_GObj*);
/* 275788 */ /**
 * @brief Sets all active hitboxes to a specific state (e.g. interpolated).
 * @param item_gobj The item GObj
 */
void it_80275788(Item_GObj*);
/* 275820 */ /**
 * @brief Sets the primary and secondary coordinate vectors for a specific hitbox.
 * @param item_gobj The item GObj
 * @param pos1 The primary position vector
 * @param pos2 The secondary position vector
 * @param idx The hitbox index
 */
void it_80275820(Item_GObj*, Vec3* pos1, Vec3* pos2, s32 idx);
/* 275870 */ /**
 * @brief Checks if the item has any active hitboxes.
 * @param item_gobj The item GObj
 * @return true if there is at least one active hitbox
 */
bool it_80275870(Item_GObj*);
/* 2758D4 */ /**
 * @brief Gets the maximum damage value across all active hitboxes on the item.
 * @param item_gobj The item GObj
 * @return The maximum damage
 */
float it_802758D4(Item_GObj*);

#endif
