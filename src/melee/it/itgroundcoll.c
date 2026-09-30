/**
 * @file itgroundcoll.c
 * @brief Item environmental collision and bounce logic
 * @details Handles item ECB (Environment Collision Box) interaction with stages, ground line detection, and bounce physics.
 * Module prefix: it
 */
#include "itgroundcoll.h"

#include "inlines.h"
#include "it_2725.h"
#include "it_3F14.h"
#include "item.h"
#include "itmaplib.h"
#include <melee/mp/mpcoll.h>
#include <melee/mp/mplib.h>
#include <sysdolphin/baselib/random.h>

/**
 * @brief Updates ECB and checks for ground collision. If found, updates position and floor line index.
 * @param gobj Item GObj
 * @return true if collided with ground
 */
bool it_8026D564(Item_GObj* gobj)
{
    bool is_colliding;
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    PAD_STACK(4);

    it_80276214(gobj);
    is_colliding = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    return is_colliding;
}

/**
 * @brief Updates ECB and checks for ground collision without updating item position.
 * @param gobj Item GObj
 * @return true if collided with ground
 */
bool it_8026D5CC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;

    it_80276214(gobj);
    return mpColl_8004B108(coll);
}

/**
 * @brief Checks if the item's current floor line index is valid.
 * @param gobj Item GObj
 * @return true if floor line is valid
 */
bool it_8026D604(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    return mpLib_80054ED8(ip->xC30);
}

/**
 * @brief Checks ground collision. If the item loses ground contact, calls the fall callback (air state transition).
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
void it_8026D62C(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* ip;
    bool is_colliding;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    is_colliding = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (is_colliding != false) {
        ip->xC30 = (u32) coll->floor.index;
    }
    if (is_colliding == false) {
        it_802762BC(ip);
        callback(gobj);
        return;
    }
    if ((it_80277544(gobj) != 0) && !ip->xDCD_flag.x0.b3) {
        Item_8026ADC0(gobj);
    }
}

/**
 * @brief Similar to it_8026D62C but doesn't drop the item explicitly or reset ECB upon losing ground.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
void it_8026D6F4(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* ip;
    bool is_colliding;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    is_colliding = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (is_colliding != false) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    if (is_colliding == false) {
        callback(gobj);
    }
}

/**
 * @brief Ground collision check. If lost, executes callback and clears related item ECB flags.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 */
void it_8026D78C(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* ip;
    bool is_colliding;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    is_colliding = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (is_colliding != false) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    if (is_colliding == false) {
        callback(gobj);
        it_802762BC(ip);
    }
}

/**
 * @brief Checks ground collision and clears ECB flags if ground contact is lost, but without a callback.
 * @param gobj Item GObj
 */
void it_8026D82C(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool is_colliding;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    is_colliding = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    if (!is_colliding) {
        it_802762BC(ip);
    }
}

/**
 * @brief Checks ground collision using an alternative mpColl function.
 * @param gobj Item GObj
 * @param callback Callback executed if item falls off the edge
 * @return true if collided with ground
 */
bool it_8026D8A4(Item_GObj* gobj, HSD_GObjEvent callback)
{
    bool is_colliding;
    PAD_STACK(8 * 4);

    it_80276214(gobj);

    {
        CollData* coll;
        Item* ip = GET_ITEM(gobj);
        coll = &ip->x378_itemColl;

        it_80276214(gobj);

        is_colliding = mpColl_8004B2DC(coll);
        ip->pos = coll->cur_pos;

        if (is_colliding != false) {
            // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
        }
    }
    if (it_802762D8(gobj) != false) {
        callback(gobj);
    }
    return is_colliding;
}

/**
 * @brief Validates the floor line index. If invalid, sets to -1 and triggers the callback.
 * @param gobj Item GObj
 * @param callback Callback to execute if floor is invalid
 */
void it_8026D938(Item_GObj* gobj, HSD_GObjEvent callback)
{
    Item* ip = GET_ITEM(gobj);
    if (mpLib_80054ED8(ip->xC30) == false) {
        ip->xC30 = -1;
        callback(gobj);
    }
}

/**
 * @brief Evaluates full ECB environmental collision (ground, walls, ceilings) and updates position.
 * @param gobj Item GObj
 * @return true if collision detected
 */
bool it_8026D9A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll_data = &item->x378_itemColl;
    it_80276214(gobj);
    {
        u8 _[4];
        bool temp = mpColl_800477E0(coll_data);
        item->pos = coll_data->cur_pos;
        if (temp) {
            item->xC30 = coll_data->floor.index;
        }
        return temp;
    }
}

/**
 * @brief Checks for collision against floor lines.
 * @param gobj Item GObj
 * @return true if collision detected
 */
bool it_8026DA08(Item_GObj* gobj)
{
    Item* ip;
    CollData* coll;
    bool is_colliding;
    PAD_STACK(3 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;

    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    return is_colliding;
}

/**
 * @brief Checks for collision against floor lines without updating item position.
 * @param gobj Item GObj
 * @return true if collision detected
 */
bool it_8026DA70(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll = &item->x378_itemColl;

    it_80276214(gobj);
    return mpColl_800471F8(coll);
}

/**
 * @brief Checks for floor, wall, and ceiling collisions.
 * @param gobj Item GObj
 * @return Bitmask of collisions (0x1 = Floor, 0x4 = Wall, 0x8 = Ceiling)
 */
s32 it_8026DAA8(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    s32 is_colliding;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding != 0) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    is_colliding |= it_80276308(gobj);
    is_colliding |= it_802763E0(gobj);
    return is_colliding;
}

/**
 * @brief Checks for floor and wall collisions.
 * @param gobj Item GObj
 * @return Bitmask of collisions (0x1 = Floor, 0x4 = Wall)
 */
bool it_8026DB40(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool is_colliding;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding != false) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    return is_colliding |= it_80276308(gobj);
}

/**
 * @brief Top-level check for item bounce/landing logic.
 * @param gobj Item GObj
 * @return true if item successfully landed
 */
bool it_8026DBC8(Item_GObj* gobj)
{
    if (it_8026DDFC(gobj) && it_8026DC24(gobj)) {
        it_802725D4(gobj);
        return it_8026DD5C(gobj);
    }
    return false;
}

/**
 * @brief Handles bounce physics and impact threshold. Dampens velocity and transitions to landing if velocity is too low.
 * @param gobj Item GObj
 * @return true if the item should land rather than bounce
 */
bool it_8026DC24(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    if (ip->xD50_landNum <= 1) {
        // Play impact/bounce sound effect based on item properties
        it_80274658(gobj, it_804D6D28->x74_float);
        it_80275DFC(gobj);
    }
    if (ABS(ip->x40_vel.x) <= 0.00001f) {
        ip->x40_vel.x = 0.0f;
    }
    if (ABS(ip->x40_vel.y) <= 0.00001f) {
        ip->x40_vel.y = 0.0f;
    }
    // Bounce logic: Check if horizontal velocity is below the bounce threshold
    if (ABS(ip->x40_vel.x) <= attr->x5c) {
        if ((ABS(ip->x40_vel.y) <= attr->x5c)) {
            goto block_18a8;
        }
    }
    if (ip->xDCD_flag.x0.b4 || !attr->x58) {
    block_18a8:
        // Velocity too low to bounce; reset velocity to land
        itResetVelocity(ip);
        return true;
    }
    return false;
}

/**
 * @brief Finalizes landing logic, resets land count, and enters the item's ground action state.
 * @param gobj Item GObj
 * @return true on successful landing transition
 */
bool it_8026DD5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum = 0;
    it_802762B0(ip);
    if (!it_80277040(gobj) || ip->xDCD_flag.x0.b3) {
        it_80274740(gobj);
        it_80276CEC(gobj);
    } else {
        if (ip->xB8_itemLogicTable->entered_air != NULL) {
            Item_8026ADC0(gobj);
            return false;
        }
        it_802734B4(gobj);
    }
    return true;
}

/**
 * @brief Increments bounce count and handles random item breakage on first impact.
 * @param gobj Item GObj
 * @return false if the item broke, true otherwise
 */
bool it_8026DDFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum += 1;
    if (ip->xD50_landNum == 1) {
        if (ip->xD54_throwNum != 0) {
            u8* break_odds = &it_804D6D28->x48_byte;
            if ((ip->xD54_throwNum == ((*break_odds >> 4) & 0xF)) ||
                (HSD_Randi(*break_odds & 0xF) == 0))
            {
                ip->destroy_type = 1;
                Item_8026A8EC(gobj);
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Increments bounce count and handles random item breakage on first impact (variant).
 * @param gobj Item GObj
 * @return false if the item broke, true otherwise
 */
bool it_8026DE98(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum += 1;
    if (ip->xD50_landNum == 1) {
        if (ip->xD54_throwNum != 0) {
            u8* break_odds = &it_804D6D28->x48_byte;
            if ((ip->xD54_throwNum == ((*break_odds >> 4) & 0xF)) ||
                (HSD_Randi(*break_odds & 0xF) == 0))
            {
                ip->destroy_type = 1;
                Item_8026A8EC(gobj);
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Performs floor collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if floor collided
 */
bool it_8026DF34(Item_GObj* gobj)
{
    bool is_colliding;
    CollData* coll;
    Item* ip;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    if (is_colliding) {
        return true;
    }
    return false;
}

/**
 * @brief Performs floor, wall, and ceiling collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if any collision occurred
 */
bool it_8026DFB0(Item_GObj* gobj)
{
    bool is_colliding;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    is_colliding |= it_80276308(gobj);
    is_colliding |= it_802763E0(gobj);
    if (is_colliding & 0xF) {
        return true;
    }
    return false;
}

/**
 * @brief Performs floor and wall collision check and returns boolean result.
 * @param gobj Item GObj
 * @return true if floor or wall collided
 */
bool it_8026E058(Item_GObj* gobj)
{
    bool is_colliding;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    is_colliding |= it_80276308(gobj);
    if (is_colliding & 0xD) {
        return true;
    }
    return false;
}

/**
 * @brief Updates position based on full environmental ECB collision.
 * @param gobj Item GObj
 */
void it_8026E0F4(Item_GObj* gobj)
{
    bool is_colliding;
    CollData* coll;
    Item* ip;
    PAD_STACK(16);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800477E0(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
}

static inline bool it_8026E_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool is_colliding;
    CollData* coll;
    bool coll_mask;
    PAD_STACK(24);

    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (is_colliding) {
        // Store the valid floor line index from the ECB collision
        ip->xC30 = coll->floor.index;
    }
    coll_mask = is_colliding;
    coll_mask |= it_80276308(gobj);
    coll_mask |= it_802763E0(gobj);
    is_colliding = coll_mask;
    return is_colliding;
}

static bool it_8026E15C_inline1(Item_GObj* gobj)
{
    return it_8026DDFC(gobj);
}
static bool it_8026E15C_inline2(Item_GObj* gobj)
{
    return it_8026DD5C(gobj);
}

/**
 * @brief Evaluates air-to-ground environmental collision, processes bounce velocity, and conditionally transitions to landing state.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
void it_8026E15C(Item_GObj* gobj, HSD_GObjEvent callback)
{
    bool did_land;
    bool coll_mask = it_8026E_inline(gobj);
    u8 _[22];

    if (coll_mask & 0xF) {
        it_80276FC4(gobj, coll_mask);
        if (coll_mask & 1) {
            if (it_8026E15C_inline1(gobj) && it_8026DC24(gobj)) {
                it_802725D4(gobj);
                did_land = it_8026E15C_inline2(gobj);
            } else {
                did_land = false;
            }
            if (did_land != false) {
                callback(gobj);
            }
        }
    }
}

static inline bool land(Item_GObj* gobj)
{
    if (it_8026DE98(gobj) && it_8026DC24(gobj)) {
        return it_8026DD5C(gobj);
    }
    return false;
}

/**
 * @brief Evaluates air-to-ground environmental collision and processes bounce/landing logic (variant).
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
void it_8026E248(Item_GObj* gobj, HSD_GObjEvent callback)
{
    bool coll_mask = it_8026E_inline(gobj);
    PAD_STACK(18);

    if (coll_mask & 0xF) {
        it_80276FC4(gobj, coll_mask);
        if (coll_mask & 1) {
            if (land(gobj)) {
                callback(gobj);
            }
        }
    }
}

static bool it_8026E32C_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD50_landNum += 1;
    if (it_8026DC24(gobj)) {
        return it_8026DD5C(gobj);
    }
    return false;
}

/**
 * @brief Evaluates air-to-ground environmental collision, returning the collision bitmask.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 * @return Collision bitmask
 */
s32 it_8026E32C(Item_GObj* gobj, HSD_GObjEvent callback)
{
    bool coll_mask = it_8026E_inline(gobj);
    PAD_STACK(32);

    if (coll_mask & 0xF) {
        it_80276FC4(gobj, coll_mask);
        if (coll_mask & 1) {
            if (it_8026E32C_inline(gobj)) {
                callback(gobj);
            }
        }
    }
    return coll_mask;
}

/**
 * @brief Evaluates air-to-ground collision, forcing an immediate landing upon ground contact (no bounce check).
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
void it_8026E414(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    bool coll_mask;
    PAD_STACK(28);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    is_colliding = is_colliding | it_802763E0(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xE) {
        it_80276FC4(gobj, coll_mask);
    }
    if (coll_mask & 1) {
        it_80275DFC(gobj);
        it_802762B0(item);
        callback(gobj);
    }
}

/**
 * @brief Evaluates air-to-ground collision, forcing landing and resetting item model scale upon ground contact.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
void it_8026E4D0(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    HSD_JObj* item_jobj;
    Item* item;
    bool is_colliding;
    bool coll_mask;
    PAD_STACK(34);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    is_colliding = is_colliding | it_802763E0(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xE) {
        it_80276FC4(gobj, coll_mask);
    }
    if (coll_mask & 1) {
        item_jobj = gobj->hsd_obj;
        it_80275DFC(gobj);
        it_802762B0(item);
        callback(gobj);
        it_80272F7C(item_jobj, item->xCC_item_attr->x60_scale);
    }
}

/**
 * @brief Evaluates full environmental collision and conditionally transitions to landing without bounce check.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
void it_8026E5A0(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    bool coll_mask;
    PAD_STACK(28);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    is_colliding = is_colliding | it_802763E0(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xF) {
        if (coll_mask & 0xE) {
            it_80276FC4(gobj, coll_mask);
        }
        if (coll_mask & 1) {
            it_80275DFC(gobj);
            it_802762B0(item);
        }
        callback(gobj);
    }
}

/**
 * @brief Evaluates floor and wall collision and conditionally transitions to landing without bounce check.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
void it_8026E664(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    bool coll_mask;

    PAD_STACK(28);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xD) {
        if (coll_mask & 0xC) {
            it_80276FC4(gobj, coll_mask);
        }
        if (coll_mask & 1) {
            it_80275DFC(gobj);
            it_802762B0(item);
        }
        callback(gobj);
    }
}

/**
 * @brief Evaluates full environmental collision with alternate bounce physics callback upon hit.
 * @param gobj Item GObj
 * @param callback Callback executed upon collision
 */
void it_8026E71C(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    bool coll_mask;
    PAD_STACK(28);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    is_colliding = is_colliding | it_802763E0(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xF) {
        if (coll_mask & 0xC) {
            it_80276D9C(gobj, coll_mask);
        }
        if (coll_mask & 1) {
            it_80275DFC(gobj);
            it_802762B0(item);
        }
        callback(gobj);
    }
}

/**
 * @brief Evaluates full environmental collision with alternate bounce physics and standard landing check.
 * @param gobj Item GObj
 * @param callback Callback executed upon landing
 */
void it_8026E7E0(Item_GObj* gobj, HSD_GObjEvent callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    bool coll_mask;
    PAD_STACK(38);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    is_colliding = is_colliding | it_80276308(gobj);
    is_colliding = is_colliding | it_802763E0(gobj);
    coll_mask = is_colliding;
    if (coll_mask & 0xC) {
        it_80276D9C(gobj, coll_mask);
    }
    if (coll_mask & 1) {
        if (land(gobj)) {
            callback(gobj);
        }
    }
}

/**
 * @brief Ground to air collision logic with split callbacks for hitting an obstruction or falling off an edge.
 * @param gobj Item GObj
 * @param callback Executed on obstruction
 * @param fall_callback Executed if ground contact is lost
 */
void it_8026E8C4(Item_GObj* gobj, HSD_GObjEvent callback, HSD_GObjEvent fall_callback)
{
    CollData* coll;
    Item* item;
    bool is_colliding;
    PAD_STACK(14);

    item = gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(gobj);
    is_colliding = mpColl_8004B108(coll);
    item->pos = coll->cur_pos;
    if (is_colliding) {
        item->xC30 = coll->floor.index;
    }
    if (is_colliding == false) {
        it_802762BC(item);
        fall_callback(gobj);
        return;
    }
    it_80277040(gobj);
    if (it_80276308(gobj)) {
        item->xD5C = 0;
    }
    if (!(item->xDC8_word.flags.x1F & 1) || (item->xD5C == 0U)) {
        it_80276CEC(gobj);
        callback(gobj);
    }
}

/**
 * @brief Raycast environment collision check between start and hit positions.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @return true if raycast hit
 */
bool it_8026E9A4(HSD_GObj* gobj, Vec3* start_pos, Vec3* hit_pos, Vec3* normal)
{
    u8 _[4];
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, NULL, NULL, normal, -1, -1, start_pos->x, start_pos->y,
                        fall_start_pos->x, fall_start_pos->y) == true)
    {
        *hit_pos = p;
        return true;
    }
    return false;
}

/**
 * @brief Raycast environment collision check that also retrieves the hit line index and material flags.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @param line_idx Pointer to store hit line index
 * @param flags_out Pointer to store material flags
 * @return true if raycast hit
 */
bool it_8026EA20(HSD_GObj* gobj, Vec3* start_pos, Vec3* hit_pos, Vec3* normal, int* line_idx,
                 u32* flags_out)
{
    UNUSED int _;
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, line_idx, flags_out, normal, -1, -1, start_pos->x, start_pos->y,
                        fall_start_pos->x, fall_start_pos->y) == true)
    {
        *hit_pos = p;
        return true;
    }
    return false;
}

/**
 * @brief Raycast environment collision check filtered by specific material flags.
 * @param gobj Item GObj
 * @param start_pos Raycast start vector
 * @param hit_pos Raycast end vector (updated on hit)
 * @param normal Returned surface normal
 * @param line_idx Pointer to store hit line index
 * @param flags_out Pointer to store material flags
 * @param material_flags Material flags to filter against
 * @return true if raycast hit
 */
bool it_8026EA9C(HSD_GObj* gobj, Vec3* start_pos, Vec3* hit_pos, Vec3* normal, int* line_idx,
                 u32* flags_out, s32 material_flags)
{
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, line_idx, flags_out, normal, -1, material_flags, start_pos->x, start_pos->y,
                        fall_start_pos->x, fall_start_pos->y) == true)
    {
        *hit_pos = p;
        return true;
    }
    return false;
}
