#include "it_26B1.h"

#include <placeholder.h>

#include "ft/ftlib.h"
#include "ft/types.h"
#include "gm/gm_unsplit.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/it_27CF.h"
#include "it/items/itbat.h"
#include "it/items/itbombhei.h"
#include "it/items/itbox.h"
#include "it/items/itfflower.h"
#include "it/items/itflipper.h"
#include "it/items/itkusudama.h"
#include "it/items/itmarumine.h"
#include "it/items/itmsbomb.h"
#include "it/items/itrabbitc.h"
#include "it/items/itsscope.h"
#include "it/items/itsword.h"
#include "it/types.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MetroTRK/intrinsics.h>

static inline float _sqrtfItem(float x)
{
    f64 _half = 0.5;

    if (x > 0) {
        vf32 y;
        // returns an approximation to
        f64 guess = __frsqrte(x);
        // now have 12 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        // now have 24 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        // now have 32 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = x * guess;
        return y;
    }
    return x;
}

/// Apply Item Damage
f32 it_8026B1D4(HSD_GObj* gobj, HitCapsule* itemHitboxUnk)
{
    f32 ret = itemHitboxUnk->damage;
    const Item* ip = gobj->user_data;
    if (ip->xDC8_word.flags.x14 != 0) {
        f32 itemSpeed = _sqrtfItem(ip->x40_vel.x * ip->x40_vel.x +
                                   ip->x40_vel.y * ip->x40_vel.y +
                                   ip->x40_vel.z * ip->x40_vel.z);

        ret += itemSpeed * it_804D6D28->x80_float[5];
        ret += it_804D6D28->x80_float[6];
        if (ret <= 1.0) {
            return ret = 1;
        }
    }
    return ret;
}

void it_8026B294(HSD_GObj* gobj,
                 Vec3* pos) // Copy Item position vector
{
    Item* temp_item;

    temp_item = gobj->user_data;
    *pos = temp_item->pos;
}

/// Check if item is heavy
bool it_8026B2B4(HSD_GObj* gobj)
{
    Item* temp_item = gobj->user_data;

    if (temp_item->xCC_item_attr->x0_is_heavy) {
        return true;
    }

    return false;
}

/// Check if item is heavy again?
bool it_8026B2D8(HSD_GObj* gobj)
{
    Item* temp_item = gobj->user_data;
    if (temp_item->xCC_item_attr->x0_is_heavy == 1) {
        return true;
    }
    return false;
}

/// Get Item ID
s32 itGetKind(HSD_GObj* gobj)
{
    Item* temp_item = gobj->user_data;
    return temp_item->kind;
}

/// Return flag from Item Attributes
enum_t it_8026B30C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    return ip->xCC_item_attr->x0_78;
}

/// Return item hold kind
enum_t it_8026B320(HSD_GObj* gobj)
{
    Item* temp_item = gobj->user_data;
    return temp_item->xCC_item_attr->x0_hold_kind;
}

f32 it_8026B334(HSD_GObj* gobj) // Return item damage multiplier
{
    Item* temp_item = gobj->user_data;
    return temp_item->xCC_item_attr->x1C_damage_mul;
}

void it_8026B344(HSD_GObj* gobj,
                 Vec3* pos) // Unknown item position math, related to velocity?
{
    Item* ip;

    ip = gobj->user_data;
    pos->x = (f32) ((ip->facing_dir * ip->xBCC_unk.x) + ip->pos.x);
    pos->y = (f32) (ip->pos.y + ip->xBCC_unk.y);
    pos->z = (f32) ip->pos.z;
}

f32 it_8026B378(HSD_GObj* gobj) // Return item's X-Axis grab range?
{
    Item* temp_item = gobj->user_data;
    return temp_item->xBD4_grabRange.x;
}

f32 it_8026B384(HSD_GObj* gobj) // Return item's Y-Axis grab range?
{
    Item* temp_item = gobj->user_data;
    return temp_item->xBD4_grabRange.y;
}

void it_8026B390(HSD_GObj* gobj) // Toggle item flag 0x15 in 0xDC8 word ON
{
    Item* temp_item;

    temp_item = gobj->user_data;
    temp_item->xDC8_word.flags.x15 = 1;
}

void it_8026B3A8(HSD_GObj* gobj) // Toggle item flag 0x15 in 0xDC8 word OFF
{
    Item* temp_item;

    temp_item = gobj->user_data;
    temp_item->xDC8_word.flags.x15 = 0;
}

int it_8026B3C0(ItemKind kind) // Count identical item GObj entities?
{
    Item* temp_item;
    HSD_GObj* unkItemGObj;

    int i = 0;
    unkItemGObj = HSD_GObj_Entities->items;

    while (unkItemGObj != NULL) {
        temp_item = unkItemGObj->user_data;

        if (temp_item->kind == kind) {
            ++i;
        }

        unkItemGObj = unkItemGObj->next;
    }
    return i;
}

void it_8026B3F8(Article* article,
                 s32 kind) // Store Item article pointer to table
{
    it_804D6D38[kind - It_Kind_Kuriboh] = article;
}

void it_8026B40C(Article* article,
                 s32 kind) // Store Stage Item article pointer to table
{
    it_804A0F60[kind - It_Kind_Old_Kuri] = article;
}

f32 it_8026B424(s32 damage) // Item Damage Math
{
    ItemCommonData* itCommonData = it_804D6D28;

    return (f32) (s32) (((f32) damage * itCommonData->xB8) +
                        itCommonData->xBC);
}

s32 it_8026B47C(HSD_GObj* gobj) // Get heal value of healing items
{
    s32 kind;
    Item* temp_item;

    temp_item = gobj->user_data;
    kind = temp_item->kind;
    switch (kind) {
    case It_Kind_Heart:
        return temp_item->xDD4_itemVar.heart.xDD4_heal;
    case It_Kind_Tomato:
        return temp_item->xDD4_itemVar.tomato.heal_amount;
    case It_Kind_Foods:
        return temp_item->xDD4_itemVar.foods.heal_amount;
    case Pokemon_Lucky_Egg:
        return temp_item->xDD4_itemVar.egg.heal_amount;
    case It_Kind_WhispyHealApple:
        return temp_item->xDD4_itemVar.whispyapple.xDD4_heal;
    default:
        return 0;
    }
}

bool it_8026B4F0(HSD_GObj* gobj) // Check if item is a healing item
{
    Item* temp_item = gobj->user_data;
    ItemKind kind = temp_item->kind;

    switch (kind) {
    case It_Kind_Heart:
    case It_Kind_Tomato:
    case It_Kind_Foods:
    case It_Kind_Coin:
    case Pokemon_Lucky_Egg:
    case It_Kind_WhispyHealApple:
        return true;
    default:
        return false;
    }
}

f32 it_8026B54C(HSD_GObj* gobj) // Get unknown float from 0x0 of item's
                                // special attributes
{
    Item* temp_item = gobj->user_data;
    itUnkAttributes* unk_attr =
        temp_item->xC4_article_data->x4_specialAttributes;

    return unk_attr->x0_float;
}

f32 it_8026B560(HSD_GObj* gobj) // Identical to 0x8026B54C but likely
                                // using a different itAttributes struct
{
    Item* temp_item = gobj->user_data;
    itUnkAttributes* unk_attr =
        temp_item->xC4_article_data->x4_specialAttributes;
    return unk_attr->x0_float;
}

f32 it_8026B574(HSD_GObj* gobj) // Get unknown float from 0x4 of item's
                                // special attributes
{
    Item* temp_item = gobj->user_data;
    itUnkAttributes* unk_attr =
        temp_item->xC4_article_data->x4_specialAttributes;
    return unk_attr->x4_float;
}

s32 it_8026B588(void) // Get unknown integer from itCommonData
{
    return it_804D6D28->xDC;
}

/// Check if item can fire projectiles and if ammo is remaining
bool it_8026B594(HSD_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemKind kind = ip->kind;

    switch (kind) {
    case It_Kind_L_Gun:
    case It_Kind_S_Scope:
    case It_Kind_StarRod:
    case It_Kind_LipStick:
    case It_Kind_F_Flower:
        if (ip->xD4C <= 0) {
            return true;
        }

    default:
    case It_Kind_Harisen: // Why though
        return false;
    }
}

HSD_GObj* it_8026B5E4(Vec3* vector, Vec3* vector2,
                      HSD_GObj* gobj) // Unknown item camera check?
{
    HSD_GObj* unk_gobj;

    unk_gobj = ftLib_8008627C(vector, gobj);
    if (unk_gobj != NULL) {
        ftLib_800866DC(unk_gobj, vector2);
    }
    return unk_gobj;
}

#if false

/**
 * @todo Missing third argument passed to #ftLib_80086368.
 * @brief Unknown item camera check 2?
 */
HSD_GObj* it_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* gobj)
{
    HSD_GObj* unk_gobj = ftLib_80086368(vector, gobj);

    if (unk_gobj != NULL)
        ftLib_800866DC(unk_gobj, vector2);

    return unk_gobj;
}

#elif defined(MWERKS_GEKKO)

#pragma push
asm HSD_GObj* it_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* gobj){
    // clang-format off
    nofralloc
/* 8026B634 00000000  7C 08 02 A6 */  mflr r0
/* 8026B638 00000004  90 01 00 04 */  stw r0, 0x4(r1)
/* 8026B63C 00000008  94 21 FF E0 */  stwu r1, -0x20(r1)
/* 8026B640 0000000C  93 E1 00 1C */  stw r31, 0x1c(r1)
/* 8026B644 00000010  93 C1 00 18 */  stw r30, 0x18(r1)
/* 8026B648 00000014  3B C4 00 00 */  addi r30, r4, 0x0
/* 8026B64C 00000018  38 85 00 00 */  addi r4, r5, 0x0
/* 8026B650 0000001C  4B E1 AD 19 */  bl ftLib_80086368
/* 8026B654 00000020  7C 7F 1B 79 */  mr. r31, r3
/* 8026B658 00000024  41 82 00 10 */  beq lbl_8026B668
/* 8026B65C 00000028  38 7F 00 00 */  addi r3, r31, 0x0
/* 8026B660 0000002C  38 9E 00 00 */  addi r4, r30, 0x0
/* 8026B664 00000030  4B E1 B0 79 */  bl ftLib_800866DC
lbl_8026B668:
/* 8026B668 00000034  7F E3 FB 78 */  mr r3, r31
/* 8026B66C 00000038  80 01 00 24 */  lwz r0, 0x24(r1)
/* 8026B670 0000003C  83 E1 00 1C */  lwz r31, 0x1c(r1)
/* 8026B674 00000040  83 C1 00 18 */  lwz r30, 0x18(r1)
/* 8026B678 00000044  38 21 00 20 */  addi r1, r1, 0x20
/* 8026B67C 00000048  7C 08 03 A6 */  mtlr r0
/* 8026B680 0000004C  4E 80 00 20 */  blr
} // clang-format on
#pragma pop

#else

HSD_GObj* it_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

#endif

/**
 * @brief Get facing direction of fighter (?) with #NULL
 */
f32 it_8026B684(Vec3* pos)
{
    return ftLib_800864A8(pos, NULL);
}

/**
 * @brief Get facing direction of fighter (?) with variable argument
 */
f32 it_8026B6A8(Vec3* pos, HSD_GObj* arg1)
{
    return ftLib_800864A8(pos, arg1);
}

bool it_8026B6C8(HSD_GObj* gobj) // Check if item is a stage item?
{
    s32 kind;
    s32 itemID_2;
    s32 itemID_3;
    Item* ip;

    ip = gobj->user_data;
    kind = ip->kind;
    if (((kind >= It_Kind_Kuriboh) && (kind < It_Kind_Octarock_Stone)) ||
        ((itemID_2 = ip->kind, ((itemID_2 < It_Kind_Old_Kuri) == false)) &&
         (itemID_2 < It_Kind_Arwing_Laser)))
    {
        itemID_3 = ip->kind;
        if ((itemID_3 != It_Kind_Kyasarin_Egg) &&
            (itemID_3 != It_Kind_WhispyApple))
        {
            return true;
        }
    }
    return false;
}

void it_8026B718(HSD_GObj* gobj,
                 f32 hitlagFrames) // Set item's hitlag frames
{
    Item* ip = gobj->user_data;
    ip->xCBC_hitlagFrames = hitlagFrames;
}

void it_8026B724(HSD_GObj* gobj) // Toggle bit 3 of 0xDC8 word ON
{
    Item* ip = gobj->user_data;
    ip->xDC8_word.flags.x3 = true;
}

void it_8026B73C(HSD_GObj* gobj) // Toggle bits in 0xDC8 word
{
    Item* ip;

    ip = gobj->user_data;
    if (ip->xDC8_word.flags.x7 != 0) {
        ip->xDC8_word.flags.x5 = 1;
    }
    if (ip->xDC8_word.flags.x3 != 0) {
        ip->xDC8_word.flags.x3 = 0;
    }
}

bool it_8026B774(HSD_GObj* gobj,
                 u8 arg1) // Bitwise operations in 0xDC8 word
{
    Item* ip = gobj->user_data;

    if (ip->xDC8_word.flags.xF & (1 << arg1)) {
        return true;
    }
    return false;
}

s32 it_8026B7A4(HSD_GObj* gobj) // Get Item State ID
{
    Item* ip = gobj->user_data;
    return ip->msid;
}

u8 it_8026B7B0(HSD_GObj* gobj) // Get Item Team ID
{
    Item* ip = gobj->user_data;
    return ip->x20_team_id;
}

s32 it_8026B7BC(HSD_GObj* gobj) // Get flag 0x14 of 0xDC8 word
{
    Item* ip = gobj->user_data;
    return ip->xDC8_word.flags.x14;
}

s32 it_8026B7CC(HSD_GObj* gobj) // Get 0x1C of Item - something to do
                                // with stale moves?
{
    Item* ip = gobj->user_data;
    return ip->x1C;
}

s32 it_8026B7D8(void) // Get unknown var from global data
{
    return it_804D6D0C;
}

extern s32 it_804D6D08;

s32 it_8026B7E0(void) // Get unknown var from global data
{
    return it_804D6D08;
}

s32 it_8026B7E8(HSD_GObj* gobj) // Get bit 1 of 0xDC8 word
{
    Item* ip = gobj->user_data;
    return ip->xDC8_word.flags.x1;
}

inline void RunCallbackUnk(HSD_GObjInteraction proc, HSD_GObj* gobj0,
                           HSD_GObj* gobj1)
{
    if (proc != NULL) {
        proc(gobj0, gobj1);
    }
}

/// Remove item from player on death?
void it_8026B7F8(HSD_GObj* fighter_gobj)
{
    u8 _[8];

    HSD_GObj *cur, *owner;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        Item* ip = GET_ITEM(cur);
        owner = ip->owner;
        RunCallbackUnk(ip->xB8_itemLogicTable->evt_unk, cur, fighter_gobj);

        if (ip->xDC8_word.flags.x13 && owner == fighter_gobj) {
            Item_8026A8EC(cur);
        }
    }
}

/// Remove all GObj interaction references from item
/// @returns Whether or not @p ref_gobj was the #Item::owner.
bool it_8026B894(HSD_GObj* gobj, HSD_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool result = false;

    if (ip->owner == ref_gobj) {
        ip->owner = NULL;
        result = true;
    }

    if (ip->xC64_reflectGObj == ref_gobj) {
        ip->xC64_reflectGObj = NULL;
    }

    if (ip->xC90_absorbGObj == ref_gobj) {
        ip->xC90_absorbGObj = NULL;
    }

    if (ip->xCEC_fighterGObj == ref_gobj) {
        ip->xCEC_fighterGObj = NULL;
        ip->xCB0_source_ply = 6;
    }

    if (ip->xCF4_fighterGObjUnk == ref_gobj) {
        ip->xCF4_fighterGObjUnk = NULL;
    }

    if (ip->toucher == ref_gobj) {
        ip->toucher = NULL;
    }

    return result;
}

/// Return result of unk item check
s32 it_8026B924(HSD_GObj* gobj)
{
    s32 result;
    Item* ip = GET_ITEM(gobj);
    enum_t kind = ip->kind;
    result = -1;
    switch (kind) {
    case It_Kind_Freeze:
    case It_Kind_Foods:
    case It_Kind_MSBomb:
    case It_Kind_Flipper:
    case It_Kind_LipStick:
    case It_Kind_Harisen:
        break;
    case It_Kind_S_Scope:
    case It_Kind_StarRod:
    case It_Kind_L_Gun:
    case It_Kind_F_Flower:
        result = ip->xD4C;
    }
    return result;
}

/// Return float result of item kind and state checks
f32 it_8026B960(HSD_GObj* gobj)
{
    s32 kind;
    f32 unk_timer = -1.0f;
    Item* ip;

    ip = gobj->user_data;
    kind = ip->kind;
    switch (kind) {
    case It_Kind_BombHei:
        if ((s32) ip->msid != 0xB) {
            unk_timer = ip->xDD4_itemVar.bombhei.xDEC;
        }
        break;
    case It_Kind_Link_Bomb:
        if ((s32) ip->msid != 5) {
            unk_timer = ip->xD44_lifeTimer;
        }
    }
    return unk_timer;
}

extern void lb_8000B804(HSD_JObj*, HSD_Joint*);
extern void lb_8000BA0C(HSD_JObj*, f32);
extern void HSD_JObjRemoveAnimAll(HSD_JObj*);

static inline void What(HSD_GObj* gobj, struct ItemStateDesc* itemStateDesc,
                        Item* ip, HSD_JObj* item_jobj2)
{
    struct ItemStateDesc* temp_stateDesc;
    HSD_Joint* temp_joint;
    HSD_JObj* item_jobj; // r30
    item_jobj = NULL;
    ip->xD54_throwNum -= 1;
    ip->xDC8_word.flags.x14 = 0;
    if ((s32) ip->anim_id != -1) {
        ip->xD0_itemStateDesc = itemStateDesc;
        if (ip->xD0_itemStateDesc != NULL) {
            HSD_JObjRemoveAnimAll(item_jobj2);
            temp_joint = ip->xC8_joint;
            if (temp_joint != NULL) {
                if (item_jobj2 == NULL) {
                    item_jobj = NULL;
                } else {
                    item_jobj = item_jobj2->child;
                }
                lb_8000B804(item_jobj, temp_joint->child);
            }
            temp_stateDesc = ip->xD0_itemStateDesc;
            HSD_JObjAddAnimAll(item_jobj2, temp_stateDesc->x0_anim_joint,
                               temp_stateDesc->x4_matanim_joint,
                               temp_stateDesc->x8_parameters);
            lb_8000BA0C(item_jobj2, ip->x5D0_animFrameSpeed);
            HSD_JObjReqAnimAll(item_jobj2, 0.0f);
            Item_80268E40(ip, itemStateDesc);
        }
        HSD_JObjAnimAll(item_jobj2);
        it_80279BE0(gobj);
        it_802799E4(gobj);
        return;
    }
    HSD_JObjRemoveAnimAll(item_jobj2);
    ip->x524_cmd.u = NULL;
}

/// Transfer item on character transformation (Zelda <-> Sheik)
void it_8026B9A8(HSD_GObj* gobj, HSD_GObj* arg1, Fighter_Part arg2)
{
    Vec3 vec;
    Item* ip = GET_ITEM(gobj);
    ItemStateArray* states = ip->xC4_article_data->xC_itemStates;

    ItemStateDesc* state_desc;

    /// @todo Not enough stack for #GET_JOBJ.
    HSD_JObj* jobj0 = gobj->hsd_obj;

    state_desc = &states->x0_itemStateDesc[ip->anim_id];
    vec.z = 0.0f;
    vec.y = 0.0f;
    vec.x = 0.0f;
    it_8027429C(gobj, &vec);
    it_802742F4(gobj, arg1, arg2);

    {
        ItemStateDesc* temp_stateDesc;
        HSD_JObj* jobj1;

        jobj1 = NULL;
        ip->xD54_throwNum -= 1;
        ip->xDC8_word.flags.x14 = 0;

        if (ip->anim_id != -1) {
            ip->xD0_itemStateDesc = state_desc;
            if (ip->xD0_itemStateDesc != NULL) {
                HSD_JObjRemoveAnimAll(jobj0);
                if (ip->xC8_joint != NULL) {
                    jobj1 = (jobj0 == NULL) ? NULL : jobj0->child;

                    lb_8000B804(jobj1, ip->xC8_joint->child);
                }
                temp_stateDesc = ip->xD0_itemStateDesc;
                HSD_JObjAddAnimAll(jobj0, temp_stateDesc->x0_anim_joint,
                                   temp_stateDesc->x4_matanim_joint,
                                   temp_stateDesc->x8_parameters);
                lb_8000BA0C(jobj0, ip->x5D0_animFrameSpeed);
                HSD_JObjReqAnimAll(jobj0, 0.0f);
                Item_80268E40(ip, state_desc);
            }

            HSD_JObjAnimAll(jobj0);
            it_80279BE0(gobj);
            it_802799E4(gobj);
            return;
        }
    }

    HSD_JObjRemoveAnimAll(jobj0);
    ip->x524_cmd.u = NULL;
}

/// Multiply item's scale
void it_8026BAE8(HSD_GObj* gobj, f32 scl_mul)
{
    f32 scl;
    Item* ip;
    HSD_JObj* item_jobj;

    ip = gobj->user_data;
    item_jobj = gobj->hsd_obj;
    scl = scl_mul * ip->xCC_item_attr->x60_scale;
    ip->scl = scl;
    it_80272F7C(item_jobj, scl);
}

/// Clear JObj flags on item model
void it_8026BB20(HSD_GObj* gobj)
{
    it_80272A18(gobj->hsd_obj);
}

/// Set JObj flags on item model
void it_8026BB44(HSD_GObj* gobj)
{
    it_80272A3C(gobj->hsd_obj);
}

extern void ftLib_80086990(HSD_GObj*, Vec3*);

/// Adjust item's position to fp bone
void it_8026BB68(HSD_GObj* fighter_gobj, Vec3* pos)
{
    ftLib_80086990(fighter_gobj, pos);
}

/// Adjust item's position based on ECB?
void it_8026BB88(HSD_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    ftECB* ecb = &ip->x378_itemColl.ecb;

    /// @todo Why is this always zero? Stripped something?
    f32 offset_xz = 0.0f;

    f32 offset_y = 0.5f * (ecb->top.y + ecb->bottom.y);

    pos->x = ip->pos.x + offset_xz;
    pos->y = ip->pos.y + offset_y;
    pos->z = ip->pos.z + offset_xz;
}

/// Adjust item's ECB position?
void it_8026BBCC(HSD_GObj* gobj, Vec3* pos)
{
    Item* ip = gobj->user_data;
    CollData* coll_data = &ip->x378_itemColl;
    ftECB* ecb = &coll_data->xE4_ecb;

    /// @todo Why is this always zero? Stripped something?
    f32 offset_xz = 0.0f;

    f32 offset_y = 0.5f * (ecb->top.y + ecb->bottom.y);

    pos->x = coll_data->last_pos.x + offset_xz;
    pos->y = coll_data->last_pos.y + offset_y;
    pos->z = coll_data->last_pos.z + offset_xz;
}

extern bool ftLib_80086960(HSD_GObj*);
extern void ftLib_80086A4C(HSD_GObj*, f32);

/// Check if item owner is a fighter + decrement hitlag
void it_8026BC14(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->owner != NULL && ftLib_80086960(ip->owner)) {
        ftLib_80086A4C(ip->owner, ip->xCBC_hitlagFrames - 1);
    }
}

/// @returns #Item::xDD0_flag::bits::b0 of @p gobj.
bool it_8026BC68(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    return ip->xDD0_flag.b0;
}

/// @returns #Item::owner of @p gobj.
HSD_GObj* it_8026BC78(HSD_GObj* gobj) // Get item owner
{
    Item* ip = GET_ITEM(gobj);
    return ip->owner;
}

/// @returns #Item::xD88_attackID of @p gobj.
bool it_8026BC84(HSD_GObj* gobj)
{
    Item* ip = gobj->user_data;
    return ip->xD88_attackID;
}

extern void ftLib_80086644(HSD_GObj*, Vec3*);

/// Unknown item ECB / position update
void it_8026BC90(HSD_GObj* gobj, Vec3* pos)
{
    pos->z = 0;
    pos->y = 0;
    pos->x = 0;

    if (gobj != NULL && ftLib_80086960(gobj)) {
        ftLib_80086644(gobj, pos);
    }
}

/// Unsets #Item::xDCD_flag::bits::b2 of @p gobj.
void it_8026BCF4(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCD_flag.b2 = false;
}

/// Sets #Item::xDCD_flag::bits::b2 of @p gobj.
void it_8026BD0C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCD_flag.b2 = true;
}

/// Sets #Item::xDD0_flag::bits::b3 of @p gobj.
void it_8026BD24(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD0_flag.b3 = true;
}

/// Sets #Item::xDCC_flag::bits::b3 of @p gobj.
void it_8026BD3C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCC_flag.b3 = true;
}

/// Unsets #Item::xDCC_flag::bits::b3 of @p gobj.
void it_8026BD54(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCC_flag.b3 = 0;
}

/// Sets #Item::xDCD_flag::bits::b3 of @p gobj.
void it_8026BD6C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCD_flag.b3 = true;
}

/// Sets #Item::xDCD_flag::bits::b4 of @p gobj.
void it_8026BD84(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCD_flag.b4 = true;
}

/// Sets #Item::xDC8_word::flags::x1A of @p gobj.
void it_8026BD9C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDC8_word.flags.x1A = true;
}

// 0x8026BDB4 // Identical to previous function except for the toggle bit
void it_8026BDB4(HSD_GObj* gobj) // Toggle 0x1A of 0xDC8 word OFF
{
    Item* ip = GET_ITEM(gobj);
    ip->xDC8_word.flags.x1A = false;
}

/// Toggles several item flags.
void it_8026BDCC(HSD_GObj* gobj)
{
    /// @todo Each of these is an inlined function. Some are already defined.
    {
        Item* ip = GET_ITEM(gobj);
        ip->xDD0_flag.b3 = false;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCC_flag.b3 = true;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCD_flag.b3 = false;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCD_flag.b4 = false;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDC8_word.flags.x1A = true;
    }
}

/// Toggle several item flags. The inverse of #it_8026BDCC.
void it_8026BE28(HSD_GObj* gobj)
{
    /// @todo Each of these is an inlined function. Some are already defined.
    {
        Item* ip = GET_ITEM(gobj);
        ip->xDD0_flag.b3 = true;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCC_flag.b3 = false;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCD_flag.b3 = true;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDCD_flag.b4 = true;
    }

    {
        Item* ip = GET_ITEM(gobj);
        ip->xDC8_word.flags.x1A = false;
    }
}

HSD_GObj* it_8026BE84(BobOmbRain* bobOmbRain)
{
    enum_t bobomb_id;
    enum_t kind0;
    enum_t kind1;
    Item* ip;
    Item* item_data_2;
    Item* item_data_3;
    Item* item_data_4;
    Item* item_data_5;

    HSD_GObj* bobOmbGObj = NULL;

    if (gm_8016B238() && bobOmbRain->x14 != 6) {
        return NULL;
    }

    bobomb_id = bobOmbRain->x14;

    switch (bobomb_id) {
    case 1:
        if (it_8026D324(true)) {
            bobOmbGObj = it_80286088(bobOmbRain->x0);
        }

        break;

    case 20:
        bobOmbGObj = it_80290938(bobOmbRain->x4);
        break;

    case 8:
        bobOmbGObj =
            it_80283AE4(bobOmbRain->x0, &bobOmbRain->x8_vec, bobOmbRain->x18);
        if (bobOmbGObj != NULL) {
            u8 _[8];

            ip = GET_ITEM(bobOmbGObj);
            kind0 = ip->kind;
            switch (kind0) {
            case It_Kind_Heart:
                it_80283BD4(bobOmbGObj);
                break;
            case It_Kind_Tomato:
                it_8028428C(bobOmbGObj);
                break;
            }
        }
        break;

    case 9:
        bobOmbGObj =
            it_802841B4(bobOmbRain->x0, &bobOmbRain->x8_vec, bobOmbRain->x18);
        if (bobOmbGObj != NULL) {
            ip = GetItemData(bobOmbGObj);
            kind1 = ip->kind;

            switch (kind1) {
            case It_Kind_Heart:
                it_80283BD4(bobOmbGObj);
                break;

            case It_Kind_Tomato:
                it_8028428C(bobOmbGObj);
                break;
            }
        }
        break;

    case 4:
        if (it_8026D324(4)) {
            bobOmbGObj = it_802896CC(&bobOmbRain->x8_vec);
            if (bobOmbGObj != NULL) {
                it_80274F10(bobOmbGObj);
            }
        }
        break;

    case 12:
        bobOmbGObj = itSword_Spawn(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            it_80274F10(bobOmbGObj);
        }
        break;

    case 21:
        bobOmbGObj = it_80291BE0(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            it_80274F10(bobOmbGObj);
        }

        break;

    case 25:
        bobOmbGObj = it_80292D48(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            it_80274F10(bobOmbGObj);
        }
        break;

    case 31:
        bobOmbGObj = it_80294DC0(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            it_80274F10(bobOmbGObj);
        }
        break;

    case 11:
        bobOmbGObj = it_80284854(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            it_80274F10(bobOmbGObj);
        }
        break;

    case 6:
        it_8027D670(&bobOmbRain->x8_vec);

    default:
        bobOmbGObj = NULL;
        break;
    }

    if (bobOmbGObj != NULL && bobOmbRain->x1C.b0) {
        ip = bobOmbGObj->user_data;
        ip->xDD0_flag.b3 = true;

        item_data_2 = bobOmbGObj->user_data;
        item_data_2->xDCC_flag.b3 = false;

        item_data_3 = bobOmbGObj->user_data;
        item_data_3->xDCD_flag.b3 = true;

        item_data_4 = bobOmbGObj->user_data;
        item_data_4->xDCD_flag.b4 = true;

        item_data_5 = bobOmbGObj->user_data;
        item_data_5->xDC8_word.flags.x1A = false;
    }

    return bobOmbGObj;
}

extern CollData* ftLib_80086984(HSD_GObj*);

CollData* it_8026C100(HSD_GObj* gobj) // Get item's CollData pointer
{
    CollData* collDataPtr = NULL;

    switch (it_80272D40(gobj)) {
    case 0:
        collDataPtr = ftLib_80086984(gobj);
        break;
    case 1: {
        Item* ip = GET_ITEM(gobj);
        collDataPtr = &ip->x378_itemColl;
        break;
    }
    }
    return collDataPtr;
}

/// Check if Hammer item's head should break off
void it_8026C16C(HSD_GObj* gobj, bool is_headless)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C <= 0) {
        it_802725D4(gobj);
    } else if (is_headless) {
        it_80272784(gobj);
    } else {
        it_802725D4(gobj);
    }
}

/// Check if item has a hitbox
bool it_8026C1B4(HSD_GObj* gobj)
{
    return it_80275870(gobj);
}

u32 it_8026C1D4(void)
{
    itLGun_ItemVars* lgun = it_804D6D24[It_Kind_L_Gun]->x4_specialAttributes;
    return lgun->timer;
}

/// Check if item has grabbed a GObj?
bool it_8026C1E8(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->grab_victim != NULL ||
        (ip->xDC8_word.flags.x13 && ip->owner != NULL))
    {
        return false;
    }

    return true;
}

/// Get item owner's port number
void it_8026C220(HSD_GObj* gobj, HSD_GObj* fighter_gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xCB0_source_ply = (u8) ftLib_80086BE0(fighter_gobj);
}

/// Find the closest item to the given position?
/// @remarks Used by Samus's Homing Missile to lock onto certain items.
/// @returns The nearest #HSD_GObj to @p pos that fits the criteria.
HSD_GObj* it_8026C258(Vec3* pos, f32 facing_dir)
{
    f32 min_sq_dist = F32_MAX;
    HSD_GObj *cur, *result = NULL;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        Item* ip = GET_ITEM(cur);

        // Might not actually be (exclusively) hold kind in the end???
        enum_t hold_kind = ip->hold_kind;

        // Decide lock-on type for Samus Missile?
        if ((hold_kind == ITEM_UNK_MATO || hold_kind == ITEM_UNK_LOCKON ||
             /// @todo Why is this cast to @c short necessary?
             (short) (hold_kind == ITEM_UNK_ENEMY) ||
             hold_kind == ITEM_UNK_7) &&
            ip->grab_victim == NULL &&
            (!ip->xDC8_word.flags.x13 || ip->owner == NULL) &&
            (facing_dir != -1 || !(ip->pos.x > pos->x)) &&
            (facing_dir != +1 || !(ip->pos.x < pos->x)))
        {
            f32 dist_x = pos->x - ip->pos.x;
            f32 dist_y = pos->y - ip->pos.y;
            f32 sq_dist = dist_x * dist_x + dist_y * dist_y;

            if (sq_dist < min_sq_dist) {
                min_sq_dist = sq_dist;
                result = cur;
            }
        }
    }

    return result;
}

/// Unknown item position / ECB update
void it_8026C334(HSD_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    f32 offset_xz = 0.0f;
    f32 offset_y = ip->x378_itemColl.ecb.bottom.y;

    pos->x = ip->pos.x + offset_xz;
    pos->y = ip->pos.y + offset_y;
    pos->z = ip->pos.z + offset_xz;
}

/// Run bomb item explosion callbacks
void it_8026C368(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->x378_itemColl.x34_flags.b7) {
        ItemKind kind = ip->kind;
        switch (kind) {
        case It_Kind_BombHei:
            it_8027D730(gobj);
            return;

        case It_Kind_MSBomb:
            it_8028FE90(gobj);
            return;

        case It_Kind_Link_Bomb:
        case It_Kind_CLink_Bomb:
            it_8029D968(gobj);
            return;

        case Pokemon_Marumine:
            it_802D09D0(gobj);
            return;

        default:
            ip->destroy_type = 0;
            Item_8026A8EC(gobj);
        }
    }
}

/// Toggle bit 3 of 0xDC8 ON for all active item GObjs?
void it_8026C3FC(void)
{
    HSD_GObj* cur;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        it_8026B724(cur);
    }
}

/// Toggle bits in 0xDC8 for all active item GObjs?
void it_8026C42C(void)
{
    HSD_GObj* cur;
    for (cur = HSD_GObj_Entities->items; cur != NULL; cur = cur->next) {
        Item* ip = GET_ITEM(cur);

        if (ip->xDC8_word.flags.x7) {
            ip->xDC8_word.flags.x5 = true;
        }

        if (ip->xDC8_word.flags.x3) {
            ip->xDC8_word.flags.x3 = false;
        }
    }
}
