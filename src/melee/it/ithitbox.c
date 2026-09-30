/**
 * @file ithitbox.c
 * @brief Item hitbox management
 * @details Handles the activation, scaling, and damage adjustment of offensive item hitboxes.
 * Module prefix: it
 */
#include "ithitbox.h"

#include "inlines.h"
#include "it_2725.h"
#include "itcoll.h"

/**
 * @brief Resets item damage dealt and hitbox scaling modifiers.
 */
void it_802753DC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xC34_damageDealt = 0;
    item->xC40 = 1.0f;
    item->xC44 = 1.0f;
    item->xC3C = 1.0f;
    item->xC48 = 0;
    item->xC4C = 0;
    item->xC50 = 0;
    item->xDCE_flag.x0.b6 = 0;
}

/**
 * @brief Enables a specific collision/hitbox flag (xDCD_flag b7).
 */
void it_80275414(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.x0.b7 = 1;
}

/**
 * @brief Disables a specific collision/hitbox flag (xDCD_flag b7).
 */
void it_8027542C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.x0.b7 = 0;
}

/**
 * @brief Enables multiple collision flags in xDCD_flag.
 */
void it_80275444(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.x0.b5 = 1;
    item->xDCD_flag.x0.b7 = 1;
    item->xDCD_flag.x0.b6 = 1;
}

/**
 * @brief Disables multiple collision flags in xDCD_flag.
 */
void it_80275474(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.x0.b5 = 0;
    item->xDCD_flag.x0.b7 = 0;
    item->xDCD_flag.x0.b6 = 0;
}

/**
 * @brief Enables a specific collision/hitbox flag (xDCE_flag b2).
 */
void it_802754A4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.x0.b2 = 1;
}

/**
 * @brief Disables a specific collision/hitbox flag (xDCE_flag b2).
 */
void it_802754BC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.x0.b2 = 0;
}

/**
 * @brief Enables multiple collision flags in xDCE_flag.
 */
void it_802754D4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.x0.b0 = 1;
    item->xDCE_flag.x0.b2 = 1;
    item->xDCE_flag.x0.b1 = 1;
}

/**
 * @brief Disables multiple collision flags in xDCE_flag.
 */
void it_80275504(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.x0.b0 = 0;
    item->xDCE_flag.x0.b2 = 0;
    item->xDCE_flag.x0.b1 = 0;
}

/**
 * @brief Sets the scale for all active hitboxes of an item.
 */
void it_80275534(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 i;

    item = item_gobj->user_data;
    for (i = 0U; i < 4U; i++) {
        hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale = scale;
        }
    }
}

/**
 * @brief Multiplies the scale of a specific item hitbox.
 */
void it_80275594(Item_GObj* item_gobj, s32 idx, f32 mult)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->scale *= mult;
    }
}

/**
 * @brief Multiplies the scale for all active hitboxes of an item.
 */
void it_802755C0(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 i;

    item = item_gobj->user_data;
    for (i = 0U; i < 4U; i++) {
        hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale *= scale;
        }
    }
}

/**
 * @brief Multiplies the damage of all active hitboxes of an item.
 */
void it_80275640(Item_GObj* item_gobj, f32 damage_mul)
{
    Item* item = GET_ITEM(item_gobj);
    u32 i;

    for (i = 0; i < 4; i++) {
        HitCapsule* hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            it_80272460(hitcapsule, hitcapsule->damage * damage_mul, item_gobj);
        }
    }
}

/**
 * @brief Sets an item collision/hitlag state variable to 2.
 */
void it_802756D0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 2;
}

/**
 * @brief Clears an item collision/hitlag state variable and updates collision logic.
 */
void it_802756E0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 0;
    it_802714C0(item_gobj);
}

/**
 * @brief Disables a flag (x40_b0) on a specific item hitbox.
 */
void it_8027570C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 0;
}

/**
 * @brief Enables a flag (x40_b0) on a specific item hitbox.
 */
void it_8027572C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 1;
}

/**
 * @brief Updates position and collision boundaries for the item hitboxes.
 */
void it_8027574C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    it_80274D04(item_gobj, &item->xB54);
    it_80274D6C(item_gobj);
}

/**
 * @brief Sets all active hitboxes to a specific state (e.g. interpolated).
 */
void it_80275788(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    HitCapsuleState state;
    u32 i;

    item = item_gobj->user_data;
    state = HitCapsule_Unk4;
    for (i = 0U; i < 4U; i++) {
        hitcapsule = (0, &item->x5D4_hitboxes[i].hit);
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->state = state;
            item->xDAA.xDAA_flag.x0.b2 = 1;
        }
    }
}

/**
 * @brief Sets the primary and secondary coordinate vectors for a specific hitbox.
 */
void it_80275820(Item_GObj* item_gobj, Vec3* pos1, Vec3* pos2, s32 idx)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->x58 = *pos2;
        hitcapsule->x4C = *pos1;
    }
}

/**
 * @brief Checks if the item has any active hitboxes.
 */
bool it_80275870(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 i;

    item = item_gobj->user_data;
    for (i = 0U; i < 4U; i++) {
        hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the maximum damage value across all active hitboxes on the item.
 */
f32 it_802758D4(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 i;
    f32 damage;
    bool disable_chk;

    item = item_gobj->user_data;
    damage = 0.0f;
    for (i = 0U; i < 4U; i++) {
        hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            disable_chk = true;
            break;
        } else {
            disable_chk = false;
        }
    }

    if (disable_chk) {
        for (i = 0U; i < 4U; i++) {
            hitcapsule = &item->x5D4_hitboxes[i].hit;
            if (hitcapsule->state != HitCapsule_Disabled) {
                if (damage <= hitcapsule->damage) {
                    damage = hitcapsule->damage;
                }
            }
        }
    }
    return damage;
}
