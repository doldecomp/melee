#include <common_structs.h>
#include <melee/it/item.h>

#define FLOAT32_MAX 3.4028234663852886e+38f

static inline float _sqrtfItem(float x)
{
    f64 _half = 0.5;
    volatile f32 y;
    if (x > 0.0f) {
        f64 guess = __frsqrte((double) x);               // returns an approximation to
        guess = 0.5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        y = (f32) (x * guess);
        return y;
    }
    return x;
}

// 0x8026B1D4 //
// https://decomp.me/scratch/hrApQ //
f32 func_8026B1D4(HSD_GObj* item_gobj, itHit* itemHitboxUnk) // Apply Item Damage -  may not be itHit* ??? //
{
    f32 ret = itemHitboxUnk->xC_damage_staled;
    const Item* item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x14 != 0) {
        f32 itemSpeed = _sqrtfItem(item_data->x40_vel.x * item_data->x40_vel.x + item_data->x40_vel.y * item_data->x40_vel.y + item_data->x40_vel.z * item_data->x40_vel.z);

        ret += itemSpeed * lbl_804D6D28->x80_float[5];
        ret += lbl_804D6D28->x80_float[6];
        if (ret <= 1.0) {
            return ret = 1.0f;
        }
    }
    return ret;
}

// 0x8026B294 //
// https://decomp.me/scratch/WpnYu //
void func_8026B294(HSD_GObj* item_gobj, Vec3* pos) // Copy Item position vector //
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    *pos = temp_item->x4C_pos;
}

// 0x8026B2B4 //
// https://decomp.me/scratch/jaDrt //
BOOL func_8026B2B4(HSD_GObj* item_gobj) // Check if item is heavy //
{
    Item* temp_item = item_gobj->user_data;
    if (temp_item->xCC_item_attr->x0_is_heavy != 0) {
        return TRUE;
    }
    return FALSE;
}

// 0x8026B2D8 //
// https://decomp.me/scratch/cGHw4 //
BOOL func_8026B2D8(HSD_GObj* item_gobj) // Check if item is heavy again? //
{
    Item* temp_item = item_gobj->user_data;
    if (temp_item->xCC_item_attr->x0_is_heavy == 1) {
        return TRUE;
    }
    return FALSE;
}

// 0x8026B300 //
// https://decomp.me/scratch/zKcOx //
s32 itGetKind(HSD_GObj* item_gobj) // Get Item ID //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->x10_item_kind;
}

// 0x8026B30C //
// https://decomp.me/scratch/fmiAJ //
s32 func_8026B30C(HSD_GObj* item_gobj) // Return flag from Item Attributes //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->xCC_item_attr->x0_78;
}

// 0x8026B320 //
// https://decomp.me/scratch/w8ipn //
s32 func_8026B320(HSD_GObj* item_gobj) // Return item hold kind //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->xCC_item_attr->x0_hold_kind;
}

// 0x8026B334 //
// https://decomp.me/scratch/Ih7vI //
f32 func_8026B334(HSD_GObj* item_gobj) // Return item damage multiplier //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->xCC_item_attr->x1C_damage_mul;
}

// 0x8026B344 //
// https://decomp.me/scratch/Un4Dt //
void func_8026B344(HSD_GObj* item_gobj, Vec3* pos) // Unknown item position math, related to velocity? //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    pos->x = (f32) ((item_data->x2C_facing_direction * item_data->xBCC_unk.x) + item_data->x4C_pos.x);
    pos->y = (f32) (item_data->x4C_pos.y + item_data->xBCC_unk.y);
    pos->z = (f32) item_data->x4C_pos.z;
}

// 0x8026B378 //
// https://decomp.me/scratch/eZs7K //
f32 func_8026B378(HSD_GObj* item_gobj) // Return item's X-Axis grab range? //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->xBD4_grabRange.x;
}

// 0x8026B384 //
// https://decomp.me/scratch/uUSRO //
f32 func_8026B384(HSD_GObj* item_gobj) // Return item's Y-Axis grab range? //
{
    Item* temp_item = item_gobj->user_data;
    return temp_item->xBD4_grabRange.y;
}

// 0x8026B390 //
// https://decomp.me/scratch/n9c0y //
void func_8026B390(HSD_GObj* item_gobj) // Toggle item flag 0x15 in 0xDC8 word ON //
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    temp_item->xDC8_word.flags.x15 = 1;
}

// 0x8026B3A8 //
// https://decomp.me/scratch/DpuNn //
void func_8026B3A8(HSD_GObj* item_gobj) // Toggle item flag 0x15 in 0xDC8 word OFF //
{
    Item* temp_item;

    temp_item = item_gobj->user_data;
    temp_item->xDC8_word.flags.x15 = 0;
}

// 0x8026B3C0 //
// https://decomp.me/scratch/umbPP //
u32 func_8026B3C0(s32 itemID) // Count identical item GObj entities? //
{
    Item* temp_item;
    HSD_GObj* unkItemGObj;
    s32 i;

    i = 0;
    unkItemGObj = lbl_804D782C->x24_items;
    while (unkItemGObj != NULL) {
        temp_item = unkItemGObj->user_data;
        if ((s32) temp_item->x10_item_kind == itemID) {
            i += 1;
        }
        unkItemGObj = unkItemGObj->next;
    }
    return i;
}

extern struct r13_ItemTable* lbl_804D6D38;

// 0x8026B3F8 //
// https://decomp.me/scratch/lHHnR //
void func_8026B3F8(Article* article, s32 itemID) // Store Item article pointer to table //
{
    lbl_804D6D38->x0_article[itemID - It_Kind_Leadead] = article; // This feels very wrong //
}

extern UnkItemArticles3 lbl_804A0F60[];

// 0x8026B40C //
// https://decomp.me/scratch/QbeU5 //
void func_8026B40C(Article* article, s32 itemID) // Store Stage Item article pointer to table //
{
    *lbl_804A0F60[itemID - It_Kind_Old_Kuri].unkptr = article;
}

// 0x8026B424 //
// https://decomp.me/scratch/yNyAM //
f32 func_8026B424(s32 damage) // Item Damage Math //
{
    ItemCommonData* itCommonData = lbl_804D6D28;

    return (f32) (s32) (((f32) damage * itCommonData->xB8) + itCommonData->xBC);
}

// 0x8026B47C //
// https://decomp.me/scratch/nSjIi //
s32 func_8026B47C(HSD_GObj* item_gobj) // Get heal value of healing items //
{
    s32 itemID;
    Item* temp_item;

    temp_item = item_gobj->user_data;
    itemID = temp_item->x10_item_kind;
    switch (itemID) {
    case It_Kind_Heart:
        return temp_item->xDD4_itemVar.HeartContainer.xDD4_heal;
    case It_Kind_Tomato:
        return temp_item->xDD4_itemVar.MaximTomato.xDD4_heal;
    case It_Kind_Foods:
        return temp_item->xDD4_itemVar.Food.xDD8_heal;
    case Pokemon_Lucky_Egg:
        return temp_item->xDD4_itemVar.Egg.xE34_heal;
    case It_Kind_WhispyHealApple:
        return temp_item->xDD4_itemVar.WhispyApple.xDD4_heal;
    default:
        return 0;
    }
}

// 0x8026B4F0 //
// https://decomp.me/scratch/uNMc0 //
BOOL func_8026B4F0(HSD_GObj* item_gobj) // Check if item is a healing item //
{
    s32 itemID;
    Item* temp_item;

    temp_item = item_gobj->user_data;
    itemID = temp_item->x10_item_kind;
    switch (itemID) {
    case It_Kind_Heart:           // Heart Container //
    case It_Kind_Tomato:          // Maxim Tomato //
    case It_Kind_Foods:           // Food //
    case It_Kind_Coin:            // Coin ??? //
    case Pokemon_Lucky_Egg:       // Chansey's Healing Egg //
    case It_Kind_WhispyHealApple: // Healing Whispy Apple //
        return TRUE;
    default:
        return FALSE;
    }
}

// 0x8026B54C //
// https://decomp.me/scratch/hy3ec //
f32 func_8026B54C(HSD_GObj* item_gobj) // Get unknown float from 0x0 of item's special attributes //
{
    Item* temp_item = item_gobj->user_data;
    itUnkAttributes* unk_attr = temp_item->xC4_article_data->x4_specialAttributes;

    return unk_attr->x0_float;
}

// 0x8026B560 //
// https://decomp.me/scratch/eodp1 //
f32 func_8026B560(HSD_GObj* item_gobj) // Identical to 0x8026B54C but likely using a different itAttributes struct //
{
    Item* temp_item = item_gobj->user_data;
    itUnkAttributes* unk_attr = temp_item->xC4_article_data->x4_specialAttributes;
    return unk_attr->x0_float;
}

// 0x8026B574 //
// https://decomp.me/scratch/tX8VT //
f32 func_8026B574(HSD_GObj* item_gobj) // Get unknown float from 0x4 of item's special attributes //
{
    Item* temp_item = item_gobj->user_data;
    itUnkAttributes* unk_attr = temp_item->xC4_article_data->x4_specialAttributes;
    return unk_attr->x4_float;
}

// 0x8026B588 //
// https://decomp.me/scratch/yaW6O //
s32 func_8026B588(void) // Get unknown integer from itCommonData //
{
    return lbl_804D6D28->xDC;
}

// 0x8026B594 //
// https://decomp.me/scratch/rBoew //
BOOL func_8026B594(HSD_GObj* item_gobj) // Check if item can fire projectiles //
{
    s32 itemID;
    Item* item_data;

    item_data = item_gobj->user_data;
    itemID = item_data->x10_item_kind;
    switch (itemID) {
    case It_Kind_L_Gun:
    case It_Kind_S_Scope:
    case It_Kind_StarRod:
    case It_Kind_LipStick:
    case It_Kind_F_Flower:
        if ((s32) item_data->xD4C <= 0) {
            return TRUE;
        }

    default:
    case It_Kind_Harisen: // Why though //
        return FALSE;
    }
}

// 0x8026B5E4 //
// https://decomp.me/scratch/VShKp //
HSD_GObj* func_8026B5E4(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj) // Unknown item camera check? //
{
    HSD_GObj* unk_gobj;

    unk_gobj = func_8008627C(vector, item_gobj);
    if (unk_gobj != NULL) {
        func_800866DC(unk_gobj, vector2);
    }
    return unk_gobj;
}

extern HSD_GObj* func_80086368(Vec3*, HSD_GObj*);

// 0x8026B634 //
// https://decomp.me/scratch/4IGbM //
HSD_GObj* func_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj) // Unknown item camera check 2? //
{
    HSD_GObj* unk_gobj;

    unk_gobj = func_80086368(vector, item_gobj);
    if (unk_gobj != NULL) {
        func_800866DC(unk_gobj, vector2);
    }
    return unk_gobj;
}

extern f32 func_800864A8(Vec3*, s32);

// 0x8026B684 //
// https://decomp.me/scratch/2wWfM //
f32 func_8026B684(Vec3* pos) // Get facing direction of fp (?) with argument 0 //
{
    return func_800864A8(pos, 0);
}

extern f32 func_800864A8(Vec3*, s32);

// 0x8026B6A8 //
// https://decomp.me/scratch/LJ42K //
f32 func_8026B6A8(Vec3* pos, s32 arg) // Get facing direction of fp (?) with variable argument //
{
    func_800864A8(pos, arg);
}

// 0x8026B6C8 //
// https://decomp.me/scratch/Xblue //
BOOL func_8026B6C8(HSD_GObj* item_gobj) // Check if item is a stage item? //
{
    s32 itemID;
    s32 itemID_2;
    s32 itemID_3;
    Item* item_data;

    item_data = item_gobj->user_data;
    itemID = item_data->x10_item_kind;
    if (((itemID >= It_Kind_Kuriboh) && (itemID < It_Kind_Octarock_Stone)) || ((itemID_2 = item_data->x10_item_kind, ((itemID_2 < It_Kind_Old_Kuri) == FALSE)) && (itemID_2 < It_Kind_Arwing_Laser))) {
        itemID_3 = item_data->x10_item_kind;
        if ((itemID_3 != It_Kind_Kyasarin_Egg) && (itemID_3 != It_Kind_WhispyApple)) {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x8026B718 //
// https://decomp.me/scratch/ttNdH //
void func_8026B718(HSD_GObj* item_gobj, f32 hitlagFrames) // Set item's hitlag frames //
{
    Item* item_data = item_gobj->user_data;
    item_data->itdmg.xCBC_hitlagFrames = hitlagFrames;
}

// 0x8026B724 //
// https://decomp.me/scratch/B6jVF //
void func_8026B724(HSD_GObj* item_gobj) // Toggle bit 3 of 0xDC8 word ON //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    item_data->xDC8_word.flags.x3 = 1;
}

// 0x8026B73C //
// https://decomp.me/scratch/Khcrj //
void func_8026B73C(HSD_GObj* item_gobj) // Toggle bits in 0xDC8 word //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->xDC8_word.flags.x7 != 0) {
        item_data->xDC8_word.flags.x5 = 1;
    }
    if (item_data->xDC8_word.flags.x3 != 0) {
        item_data->xDC8_word.flags.x3 = 0;
    }
}

// 0x8026B774 //
// https://decomp.me/scratch/MGx2T //
BOOL func_8026B774(HSD_GObj* item_gobj, u8 arg1) // Bitwise operations in 0xDC8 word //
{
    Item* item_data = item_gobj->user_data;

    if (((item_data->xDC8_word.word >> 0xDU) & 0xF & (1 << arg1)) != 0) {
        return TRUE;
    }
    return FALSE;
}

// 0x8026B7A4 //
// https://decomp.me/scratch/ZuyGU //
s32 func_8026B7A4(HSD_GObj* item_gobj) // Get Item State ID //
{
    Item* item_data = item_gobj->user_data;
    return item_data->x24_item_state_index;
}

// 0x8026B7B0 //
// https://decomp.me/scratch/FCpEJ //
u8 func_8026B7B0(HSD_GObj* item_gobj) // Get Item Team ID //
{
    Item* item_data = item_gobj->user_data;
    return item_data->x20_team_id;
}

// 0x8026B7BC //
// https://decomp.me/scratch/rzabo //
s32 func_8026B7BC(HSD_GObj* item_gobj) // Get flag 0x14 of 0xDC8 word //
{
    Item* item_data = item_gobj->user_data;
    return item_data->xDC8_word.flags.x14;
}

// 0x8026B7CC //
// https://decomp.me/scratch/3YFpn //
s32 func_8026B7CC(HSD_GObj* item_gobj) // Get 0x1C of Item - something to do with stale moves? //
{
    Item* item_data = item_gobj->user_data;
    return item_data->x1C;
}

// 0x8026B7D8 //
// https://decomp.me/scratch/bIbLR //
s32 func_8026B7D8(void) // Get unknown var from global data //
{
    return lbl_804D6D0C;
}

extern s32 lbl_804D6D08;

s32 func_8026B7E0(void) // Get unknown var from global data //
{
    return lbl_804D6D08;
}

// 0x8026B7E8 //
// https://decomp.me/scratch/hlkfj //
s32 func_8026B7E8(HSD_GObj* item_gobj) // Get bit 1 of 0xDC8 word //
{
    Item* item_data = item_gobj->user_data;
    return item_data->xDC8_word.flags.x1;
}

inline void RunCallbackUnk(void (*cb_Process)(HSD_GObj*, HSD_GObj*), HSD_GObj* unk, HSD_GObj* unk2)
{
    if (cb_Process != NULL) {
        cb_Process(unk, unk2);
    }
}

// 0x8026B7F8 //
// https://decomp.me/scratch/j2niI //
void func_8026B7F8(HSD_GObj* fighter_gobj) // Remove item from player on death? //
{
    void (*cb_OnFreeBlock)(HSD_GObj*, HSD_GObj*); // 0x38 of item logic table runs when the player block is reset; this usually clears the item's owner GObj pointer //
    HSD_GObj* enumGObj;
    HSD_GObj* itemOwner;
    Item* item_data;
    s32 i;

    enumGObj = lbl_804D782C->x24_items;
    while (enumGObj != NULL) {
        item_data = enumGObj->user_data;
        itemOwner = item_data->x518_ownerGObj;
        RunCallbackUnk(item_data->xB8_itemLogicTable->x38_callback_OnUnknown, enumGObj, fighter_gobj);
        if ((item_data->xDC8_word.flags.x13 != 0) && (itemOwner == fighter_gobj)) {
            func_8026A8EC(enumGObj);
        }
        enumGObj = enumGObj->next;
    }
}

// 0x8026B894 //
// https://decomp.me/scratch/4J9JB //
BOOL func_8026B894(HSD_GObj* item_gobj, HSD_GObj* referenced_gobj) // Remove all GObj interaction references from item //
{
    BOOL ret;
    Item* temp_item;

    temp_item = item_gobj->user_data;
    ret = 0;

    if (temp_item->x518_ownerGObj == referenced_gobj) {
        temp_item->x518_ownerGObj = NULL;
        ret = 1;
    }
    if (temp_item->itdmg.xC64_reflectGObj == referenced_gobj) {
        temp_item->itdmg.xC64_reflectGObj = NULL;
    }
    if (temp_item->itdmg.xC90_absorbGObj == referenced_gobj) {
        temp_item->itdmg.xC90_absorbGObj = NULL;
    }
    if (temp_item->itdmg.xCEC_fighterGObj == referenced_gobj) {
        temp_item->itdmg.xCEC_fighterGObj = NULL;
        temp_item->itdmg.xCB0_source_ply = 6;
    }
    if (temp_item->xCF4_fighterGObjUnk == referenced_gobj) {
        temp_item->xCF4_fighterGObjUnk = NULL;
    }
    if (temp_item->xCF8_detectGObj == referenced_gobj) {
        temp_item->xCF8_detectGObj = NULL;
        return ret;
    }
    return ret;
}

#ifdef NON_MATCHING

#pragma peephole off

// 0x8026B924 //
// https://decomp.me/scratch/2H33A //
s32 func_8026B924(HSD_GObj* item_gobj) // Return result of unk item check - requires -g compiler flag / Frank modifications to match //
{
    s32 itemID;
    s32 ret;
    Item* item_data;

    item_data = item_gobj->user_data;
    itemID = item_data->x10_item_kind;
    ret = -1;
    switch (itemID) {
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
        ret = item_data->xD4C;
    }
    return ret;
}

#else

#pragma peephole on

asm s32 func_8026B924(register HSD_GObj* item_gobj) // Inlined ASM due to compiler version generating mismatch //
{
    lwz r4, 0x2C(item_gobj); // Get Item Data //
    li r3, -1;               // Default return value //
    lwz r0, 0x10(r4);        // Get Item ID //
    cmpwi r0, 0x17;          // Item ID Switch //
    bge - lbl_compare;
    cmpwi r0, 0x10;
    beq - lbl_getVar;
    bltlr - ;
    cmpwi r0, 0x15;
    bge - lbl_getVar;
    blr;
lbl_compare:
    cmpwi r0, 0x19;
    bnelr - ;
lbl_getVar:
    lwz r3, 0xD4C(r4);
}

#endif

#pragma peephole on

#ifdef NON_MATCHING

#pragma peephole off

// 0x8026B960 //
// https://decomp.me/scratch/6Dc0G //
f32 func_8026B960(HSD_GObj* item_gobj) // Return float result of item kind and state checks - requires -g compiler flag / Frank modifications to match //
{
    s32 itemID;
    f32 unk_timer = -1.0f;
    Item* item_data;

    item_data = item_gobj->user_data;
    itemID = item_data->x10_item_kind;
    switch (itemID) {
    case It_Kind_BombHei:
        if ((s32) item_data->x24_item_state_index != 0xB) {
            unk_timer = item_data->xDD4_itemVar.BobOmb.xDEC;
        }
        break;
    case It_Kind_Link_Bomb:
        if ((s32) item_data->x24_item_state_index != 5) {
            unk_timer = item_data->xD44_lifeTimer;
        }
    }
    return unk_timer;
}

#else

#pragma peephole on

// 0x8026B960 //
// https://decomp.me/scratch/6Dc0G //
f32 func_8026B960(register HSD_GObj* item_gobj)
{
    register s32 itemID;
    register Item* item_data;
    register f32 unk_timer = -1.0f;

    item_data = item_gobj->user_data;
    itemID = item_data->x10_item_kind;
    {
        __asm(
            cmpwi itemID, It_Kind_Link_Bomb;
            beq - lbl_block;
            bgelr - ;
            cmpwi itemID, It_Kind_BombHei;
            bnelr - ;
            lwz itemID, 0x24(item_data);
            cmpwi itemID, 0xB;
            beqlr - ;);
        return unk_timer = item_data->xDD4_itemVar.BobOmb.xDEC;
    lbl_block:
        if (item_data->x24_item_state_index != 0x5) {
            return unk_timer = item_data->xD44_lifeTimer;
        }
    }
    return unk_timer;
}

#endif

#pragma peephole on

extern void func_8000B804(HSD_JObj*, HSD_Joint*);
extern void func_8000BA0C(HSD_JObj*, f32);
extern void HSD_JObjRemoveAnimAll(HSD_JObj*);

inline void What(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc, Item* item_data, HSD_JObj* item_jobj2) // Literally what //
{
    struct ItemStateDesc* temp_stateDesc;
    HSD_Joint* temp_joint;
    HSD_JObj* item_jobj; // r30 //
    item_jobj = NULL;
    item_data->xD54_throwNum -= 1;
    item_data->xDC8_word.flags.x14 = 0;
    if ((s32) item_data->x28_item_anim_index != -1) {
        item_data->xD0_itemStateDesc = itemStateDesc;
        if (item_data->xD0_itemStateDesc != NULL) {
            HSD_JObjRemoveAnimAll(item_jobj2);
            temp_joint = item_data->xC8_joint;
            if (temp_joint != NULL) {
                if (item_jobj2 == NULL) {
                    item_jobj = NULL;
                } else
                    item_jobj = item_jobj2->child;
                func_8000B804(item_jobj, temp_joint->child);
            }
            temp_stateDesc = item_data->xD0_itemStateDesc;
            HSD_JObjAddAnimAll(item_jobj2, temp_stateDesc->x0_anim_joint, temp_stateDesc->x4_matanim_joint, temp_stateDesc->x8_parameters);
            func_8000BA0C(item_jobj2, item_data->x5D0_animFrameSpeed);
            HSD_JObjReqAnimAll(item_jobj2, 0.0f);
            func_80268E40(item_data, itemStateDesc);
        }
        HSD_JObjAnimAll(item_jobj2);
        func_80279BE0(item_gobj);
        func_802799E4(item_gobj);
        return;
    }
    HSD_JObjRemoveAnimAll(item_jobj2);
    item_data->x52C_item_script = NULL;
}

// 0x8026B9A8 //
// https://decomp.me/scratch/yyy9T // Transfer item on character transformation (Zelda <-> Sheik)
void func_8026B9A8(HSD_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Vec3 sp1C;
    Item* item_data; // r29 //
    struct ItemStateDesc* itemStateDesc;
    HSD_JObj* item_jobj2;                 // r27 //
    struct ItemStateDesc* temp_stateDesc; // r6 //
    ItemStateArray* temp_stateArray;      // r5 //

    item_data = item_gobj->user_data;
    temp_stateArray = item_data->xC4_article_data->xC_itemStates;
    item_jobj2 = item_gobj->hsd_obj;
    itemStateDesc = &temp_stateArray->x0_itemStateDesc[item_data->x28_item_anim_index];
    sp1C.z = 0.0f;
    sp1C.y = 0.0f;
    sp1C.x = 0.0f;
    func_8027429C(item_gobj, &sp1C);
    func_802742F4(item_gobj, arg1, arg2);
    {
        struct ItemStateDesc* temp_stateDesc;
        HSD_JObj* item_jobj; // r30 //

        item_jobj = NULL;
        item_data->xD54_throwNum -= 1;
        item_data->xDC8_word.flags.x14 = 0;
        if ((s32) item_data->x28_item_anim_index != -1) {
            item_data->xD0_itemStateDesc = itemStateDesc;
            if (item_data->xD0_itemStateDesc != NULL) {
                HSD_JObjRemoveAnimAll(item_jobj2);
                if (item_data->xC8_joint != NULL) {
                    item_jobj = (item_jobj2 == NULL) ? NULL : item_jobj2->child;

                    func_8000B804(item_jobj, item_data->xC8_joint->child);
                }
                temp_stateDesc = item_data->xD0_itemStateDesc;
                HSD_JObjAddAnimAll(item_jobj2, temp_stateDesc->x0_anim_joint, temp_stateDesc->x4_matanim_joint, temp_stateDesc->x8_parameters);
                func_8000BA0C(item_jobj2, item_data->x5D0_animFrameSpeed);
                HSD_JObjReqAnimAll(item_jobj2, 0.0f);
                func_80268E40(item_data, itemStateDesc);
            }
            HSD_JObjAnimAll(item_jobj2);
            func_80279BE0(item_gobj);
            func_802799E4(item_gobj);
            return;
        }
        HSD_JObjRemoveAnimAll(item_jobj2);
        item_data->x52C_item_script = NULL;
    }
}

// 0x8026BAE8 //
// https://decomp.me/scratch/iVkPs //
void func_8026BAE8(HSD_GObj* item_gobj, f32 scale_mul) // Multiply item's scale //
{
    f32 scale;
    Item* item_data;
    HSD_JObj* item_jobj;

    item_data = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    scale = scale_mul * item_data->xCC_item_attr->x60_scale;
    item_data->x38_scale = scale;
    func_80272F7C(item_jobj, scale);
}

// 0x8026BB20 //
// https://decomp.me/scratch/wvM6g //
void func_8026BB20(HSD_GObj* item_gobj) // Clear JObj flags on item model //
{
    func_80272A18(item_gobj->hsd_obj);
}

// 0x8026BB44 //
// https://decomp.me/scratch/mH7hj //
void func_8026BB44(HSD_GObj* item_gobj) // Set JObj flags on item model //
{
    func_80272A3C(item_gobj->hsd_obj);
}

extern void func_80086990(HSD_GObj*, Vec3*);

// 0x8026BB68 //
// https://decomp.me/scratch/U1sE9 //
void func_8026BB68(HSD_GObj* fighter_gobj, Vec3* pos) // Adjust item's position to fp bone //
{
    func_80086990(fighter_gobj, pos);
}

// 0x8026BB88 //
// https://decomp.me/scratch/8uWqT //
void func_8026BB88(HSD_GObj* item_gobj, Vec3* pos) // Adjust item's position based on ECB? //
{
    Item* item_data = item_gobj->user_data;
    f32 temp_float;
    f32 temp_float2 = 0.0f;

    temp_float = 0.5f * (item_data->x378_itemColl.xA4_ecbCurrCorrect.top.y + item_data->x378_itemColl.xA4_ecbCurrCorrect.bottom.y);
    pos->x = item_data->x4C_pos.x + temp_float2;
    pos->y = item_data->x4C_pos.y + temp_float;
    pos->z = item_data->x4C_pos.z + temp_float2;
}

// 0x8026BBCC //
// https://decomp.me/scratch/WAcXj //
void func_8026BBCC(HSD_GObj* item_gobj, Vec3* pos) // Adjust item's ECB position? //
{
    f32 temp_float = 0.0f;
    f32 temp_float2;
    Item* item_data = item_gobj->user_data;
    CollData* collData = &item_data->x378_itemColl;

    temp_float2 = (0.5f * (collData->xE4_ecb.top.y + collData->xE4_ecb.bottom.y));
    pos->x = collData->x1C_vec.x + temp_float;
    pos->y = collData->x1C_vec.y + temp_float2;
    pos->z = collData->x1C_vec.z + temp_float;
}

extern BOOL func_80086960(HSD_GObj*);
extern void func_80086A4C(HSD_GObj*, f32);

// 0x8026BC14 //
// https://decomp.me/scratch/j3vB2 //
void func_8026BC14(HSD_GObj* item_gobj) // Check if item owner is a fp + decrement hitlag //
{
    Item* item_data;

    item_data = item_gobj->user_data;
    if ((item_data->x518_ownerGObj != NULL) && (func_80086960(item_data->x518_ownerGObj) != FALSE)) {
        func_80086A4C(item_data->x518_ownerGObj, item_data->itdmg.xCBC_hitlagFrames - 1.0f);
    }
}

// 0x8026BC68 //
// https://decomp.me/scratch/HeaU5 //
s32 func_8026BC68(HSD_GObj* item_gobj) // Return bit 0 of 0xDD0 //
{
    Item* item_data = item_gobj->user_data;
    return item_data->xDD0_flag.bits.b0;
}

// 0x8026BC78 //
// https://decomp.me/scratch/v1BMF //
HSD_GObj* func_8026BC78(HSD_GObj* item_gobj) // Get item owner //
{
    Item* item_data = item_gobj->user_data;
    return item_data->x518_ownerGObj;
}

// 0x8026BC84 //
// https://decomp.me/scratch/s3W5l // Get item attack kind //
BOOL func_8026BC84(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data->xD88_attackID;
}

extern void func_80086644(HSD_GObj*, Vec3*);

// 0x8026BC90 //
// https://decomp.me/scratch/NBrjV //
void func_8026BC90(HSD_GObj* item_gobj, Vec3* pos) // Unknown item ECB / position update //
{
    pos->z = 0.0f;
    pos->y = 0.0f;
    pos->x = 0.0f;
    if ((item_gobj != NULL) && (func_80086960(item_gobj) != FALSE)) {
        func_80086644(item_gobj, pos);
    }
}

// 0x8026BCF4 //
// https://decomp.me/scratch/tPuXc //
void func_8026BCF4(HSD_GObj* item_gobj) // Toggle bit 2 of 0xDCD OFF //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCD_flag.bits.b2 = 0;
}

// 0x8026BD0C //
// https://decomp.me/scratch/tPuXc // This function is identical to 0x8026BCF4 except for the toggle being 1 instead //
void func_8026BD0C(HSD_GObj* item_gobj) // Toggle bit 2 of 0xDCD ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCD_flag.bits.b2 = 1;
}

// 0x8026BD24 //
// https://decomp.me/scratch/nzGPz //
void func_8026BD24(HSD_GObj* item_gobj) // Toggle bit 3 of 0xDD0 ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDD0_flag.bits.b3 = 1;
}

// 0x8026BD3C //
// https://decomp.me/scratch/RJzus //
void func_8026BD3C(HSD_GObj* item_gobj) // Toggle bit 3 of 0xDCC ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCC_flag.b3 = 1;
}

// 0x8026BD54 // Identical to previous function except for the toggle bit //
void func_8026BD54(HSD_GObj* item_gobj) // Toggle bit 3 of 0xDCC OFF //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCC_flag.b3 = 0;
}

// 0x8026BD6C //
// https://decomp.me/scratch/S0jWr //
void func_8026BD6C(HSD_GObj* item_gobj) // Toggle bit 3 of 0xDCD ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCD_flag.bits.b3 = 1;
}

// 0x8026BD84 //
// https://decomp.me/scratch/QEhSj //
void func_8026BD84(HSD_GObj* item_gobj) // Toggle bit 4 of 0xDCD ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDCD_flag.bits.b4 = 1;
}

// 0x8026BD9C //
// https://decomp.me/scratch/0Uw50 //
void func_8026BD9C(HSD_GObj* item_gobj) // Toggle 0x1A of 0xDC8 word ON //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDC8_word.flags.x1A = 1;
}

// 0x8026BDB4 // Identical to previous function except for the toggle bit //
void func_8026BDB4(HSD_GObj* item_gobj) // Toggle 0x1A of 0xDC8 word OFF //
{
    Item* item_data = item_gobj->user_data;
    item_data->xDC8_word.flags.x1A = 0;
}

// 0x8026BDCC //
// https://decomp.me/scratch/ww5Fc //
void func_8026BDCC(HSD_GObj* item_gobj) // Toggle several item flags //
{
    Item* item_data;
    Item* temp_item;
    Item* temp_item_2;
    Item* temp_item_3;
    Item* temp_item_4;

    temp_item = item_gobj->user_data;
    temp_item->xDD0_flag.bits.b3 = 0;
    temp_item_2 = item_gobj->user_data;
    temp_item_2->xDCC_flag.b3 = 1;
    temp_item_3 = item_gobj->user_data;
    temp_item_3->xDCD_flag.bits.b3 = 0;
    temp_item_4 = item_gobj->user_data;
    temp_item_4->xDCD_flag.bits.b4 = 0;
    item_data = item_gobj->user_data;
    item_data->xDC8_word.flags.x1A = 1;
}

// 0x8026BE28 //
// https://decomp.me/scratch/mRjRG //
void func_8026BE28(HSD_GObj* item_gobj) // Toggle several item flags, inverted //
{
    Item* item_data;
    Item* temp_item;
    Item* temp_item_2;
    Item* temp_item_3;
    Item* temp_item_4;

    temp_item = item_gobj->user_data;
    temp_item->xDD0_flag.bits.b3 = !0;
    temp_item_2 = item_gobj->user_data;
    temp_item_2->xDCC_flag.b3 = !1;
    temp_item_3 = item_gobj->user_data;
    temp_item_3->xDCD_flag.bits.b3 = !0;
    temp_item_4 = item_gobj->user_data;
    temp_item_4->xDCD_flag.bits.b4 = !0;
    item_data = item_gobj->user_data;
    item_data->xDC8_word.flags.x1A = !1;
}

extern s32 func_8026D324(s32);

// 0x8026BE84 //
// https://decomp.me/scratch/NDeQY //
void* func_8026BE84(BobOmbRain* bobOmbRain) // Bob-Omb Rain Switch //
{
    s32 bobOmbID;
    s32 itemID;
    s32 itemID2;
    Item* item_data;
    Item* item_data_2;
    Item* item_data_3;
    Item* item_data_4;
    Item* item_data_5;
    HSD_GObj* bobOmbGObj;

    bobOmbGObj = NULL;
    if ((func_8016B238() != 0) && ((s32) bobOmbRain->x14 != 6)) {
        return NULL;
    }
    bobOmbID = bobOmbRain->x14;
    switch (bobOmbID) {
    case 1:
        if (func_8026D324(1) != 0) {
            bobOmbGObj = func_80286088(bobOmbRain->x0);
        }
        break;

    case 20:
        bobOmbGObj = func_80290938(bobOmbRain->x4);
        break;

    case 8:
        bobOmbGObj = func_80283AE4(bobOmbRain->x0, &bobOmbRain->x8_vec, bobOmbRain->x18);
        if (bobOmbGObj != NULL) {
            item_data = GetItemData(bobOmbGObj);
            itemID = item_data->x10_item_kind;
            switch (itemID) {
            case It_Kind_Heart:
                func_80283BD4(bobOmbGObj);
                break;
            case It_Kind_Tomato: // Not sure why it's looking for healing items here... //
                func_8028428C(bobOmbGObj);
                break;
            }
        }
        break;

    case 9:
        bobOmbGObj = func_802841B4(bobOmbRain->x0, &bobOmbRain->x8_vec, bobOmbRain->x18);
        if (bobOmbGObj != NULL) {
            item_data = GetItemData(bobOmbGObj);
            itemID2 = item_data->x10_item_kind;
            switch (itemID2) {
            case It_Kind_Heart:
                func_80283BD4(bobOmbGObj);
                break;

            case It_Kind_Tomato: // ...or here //
                func_8028428C(bobOmbGObj);
                break;
            }
        }
        break;

    case 4:
        if (func_8026D324(4) != 0) {
            bobOmbGObj = func_802896CC(&bobOmbRain->x8_vec);
            if (bobOmbGObj != NULL) {
                func_80274F10(bobOmbGObj);
            }
        }
        break;

    case 12:
        bobOmbGObj = func_80284D54(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            func_80274F10(bobOmbGObj);
        }
        break;

    case 21:
        bobOmbGObj = func_80291BE0(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            func_80274F10(bobOmbGObj);
        }
        break;

    case 25:
        bobOmbGObj = func_80292D48(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            func_80274F10(bobOmbGObj);
        }
        break;

    case 31:
        bobOmbGObj = func_80294DC0(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            func_80274F10(bobOmbGObj);
        }
        break;

    case 11:
        bobOmbGObj = func_80284854(&bobOmbRain->x8_vec);
        if (bobOmbGObj != NULL) {
            func_80274F10(bobOmbGObj);
        }
        break;

    case 6:
        func_8027D670(&bobOmbRain->x8_vec);

    default:
        bobOmbGObj = NULL;
        break;
    }
    if ((bobOmbGObj != NULL) && (bobOmbRain->x1C.bits.b0 != 0)) {
        item_data = bobOmbGObj->user_data;
        item_data->xDD0_flag.bits.b3 = !0;
        item_data_2 = bobOmbGObj->user_data;
        item_data_2->xDCC_flag.b3 = !1;
        item_data_3 = bobOmbGObj->user_data;
        item_data_3->xDCD_flag.bits.b3 = !0;
        item_data_4 = bobOmbGObj->user_data;
        item_data_4->xDCD_flag.bits.b4 = !0;
        item_data_5 = bobOmbGObj->user_data;
        item_data_5->xDC8_word.flags.x1A = !1;
    }
    return bobOmbGObj;
}

extern CollData* func_80086984(HSD_GObj*);

// 0x8026C100 //
// https://decomp.me/scratch/3hnjS //
CollData* func_8026C100(HSD_GObj* item_gobj) // Get item's CollData pointer //
{
    CollData* collDataPtr;
    Item* item_data;
    s32 filler;

    collDataPtr = NULL;
    switch (func_80272D40(item_gobj)) {
    case 0:
        collDataPtr = func_80086984(item_gobj);
        break;
    case 1:
        item_data = item_gobj->user_data;
        collDataPtr = &item_data->x378_itemColl;
        break;
    }
    return collDataPtr;
}

// 0x8026C16C //
// https://decomp.me/scratch/vvPkf //
void func_8026C16C(HSD_GObj* item_gobj, BOOL isHeadless) // Check if Hammer item's head should break off //
{
    Item* item_data = item_gobj->user_data;
    if ((s32) item_data->xD4C <= 0) {
        func_802725D4(item_gobj);
        return;
    }
    if (isHeadless != 0) {
        func_80272784(item_gobj);
        return;
    }
    func_802725D4(item_gobj);
}

// 0x8026C1B4 //
// https://decomp.me/scratch/nwDPV //
void func_8026C1B4(HSD_GObj* item_gobj) // Check if item has a hitbox //
{
    func_80275870(item_gobj);
}

extern CommonItemArticles* lbl_804D6D24;

// 0x8026C1D4 //
// https://decomp.me/scratch/D9Iaa //
u32 func_8026C1D4(void) // Get unknown var from r13 pointer //
{
    return lbl_804D6D24->x40->x4->x0;
}

// 0x8026C1E8 //
// https://decomp.me/scratch/e6IVC //
BOOL func_8026C1E8(HSD_GObj* item_gobj) // Check if item has grabbed a GObj? //
{
    Item* item_data = item_gobj->user_data;

    if ((item_data->xD00_grabGObj != NULL) || (item_data->xDC8_word.flags.x13 != 0) && (item_data->x518_ownerGObj != NULL)) {
        return 0;
    }
    return 1;
}

// 0x8026C220 //
// https://decomp.me/scratch/chP97 //
void func_8026C220(HSD_GObj* item_gobj, HSD_GObj* fighter_gobj) // Get item owner's port number //
{
    Item* item_data = GetItemDirect(item_gobj);
    item_data->itdmg.xCB0_source_ply = (u8) func_80086BE0(fighter_gobj);
}

// Shoutouts to CelestialAmber for helping clean up this next one //

extern f32 lbl_804DC690;

// 0x8026C258 //
// https://decomp.me/scratch/D9ivt //
HSD_GObj* func_8026C258(Vec3* vector, f32 facingDir) // Find the closest item to the given position? Used by Samus's Homing Missile to lock onto certain items //
{
    f32 minMagnitude = FLOAT32_MAX;
    f32 magnitude;
    f32 xDist;
    f32 yDist;
    s32 holdKind;
    Item* item_data;
    HSD_GObj* item_gobj; // r5 //
    HSD_GObj* closest_item_gobj;

    closest_item_gobj = NULL;
    item_gobj = lbl_804D782C->x24_items;

    while (item_gobj != NULL) {
        item_data = item_gobj->user_data;
        holdKind = item_data->x14_hold_kind;                                                                                             // Might not actually be (exclusively) hold kind in the end??? //
        if (((int) holdKind == ITEM_UNK_MATO) || (int) (holdKind == 5) || (short) (holdKind == ITEM_UNK_ENEMY) || (int) (holdKind == 7)) // Decide lock-on type for Samus Missile?
        {
            if (item_data->xD00_grabGObj == NULL) {
                if (item_data->xDC8_word.flags.x13 == 0 || item_data->x518_ownerGObj == NULL) {
                    if ((facingDir != -1.0f) || !(item_data->x4C_pos.x > vector->x)) {
                        if ((facingDir != 1.0f) || !(item_data->x4C_pos.x < vector->x)) {
                            xDist = vector->x - item_data->x4C_pos.x;
                            yDist = vector->y - item_data->x4C_pos.y;
                            magnitude = (xDist * xDist) + (yDist * yDist);
                            if (magnitude < minMagnitude) {
                                minMagnitude = magnitude;
                                closest_item_gobj = item_gobj;
                            }
                        }
                    }
                }
            }
        }
        item_gobj = item_gobj->next;
    }
    return closest_item_gobj;
}

// 0x8026C334 //
// https://decomp.me/scratch/C3xjM //
void func_8026C334(HSD_GObj* item_gobj, Vec3* pos) // Unknown item position / ECB update //
{
    Item* item_data = item_gobj->user_data;
    f32 temp_ECBvar = item_data->x378_itemColl.xA4_ecbCurrCorrect.bottom.y;
    f32 temp_zero = 0.0f;

    pos->x = item_data->x4C_pos.x + temp_zero;
    pos->y = item_data->x4C_pos.y + temp_ECBvar;
    pos->z = item_data->x4C_pos.z + temp_zero;
}

// 0x8026C368 //
// https://decomp.me/scratch/f1P2c //
void func_8026C368(HSD_GObj* item_gobj) // Run bomb item explosion callbacks //
{
    s32 itemID;
    Item* item_data;

    item_data = item_gobj->user_data;
    if (item_data->x378_itemColl.x34_flags.bits.b7 != 0) {
        itemID = item_data->x10_item_kind;
        switch (itemID) {
        case It_Kind_BombHei: // Bob-Omb //
            func_8027D730(item_gobj);
            return;

        case It_Kind_MSBomb: // Motion-Sensor Bomb //
            func_8028FE90(item_gobj);
            return;

        case It_Kind_Link_Bomb:
        case It_Kind_CLink_Bomb:
            func_8029D968(item_gobj);
            return;

        case Pokemon_Marumine: // Electrode //
            func_802D09D0(item_gobj);
            return;

        default:
            item_data->xD60 = 0;
            func_8026A8EC(item_gobj);
        }
    }
}

// 0x8026C3FC //
// https://decomp.me/scratch/T0jPV //
void func_8026C3FC(void) // Toggle bit 3 of 0xDC8 ON for all active item GObjs? //
{
    HSD_GObj* item_gobj = lbl_804D782C->x24_items;
    Item* item_data;

    while (item_gobj != NULL) {
        item_data = item_gobj->user_data;
        item_data->xDC8_word.flags.x3 = 1;
        item_gobj = item_gobj->next;
    }
}

// 0x8026C42C //
// https://decomp.me/scratch/SOozs //
void func_8026C42C(void) // Toggle bits in 0xDC8 for all active item GObjs? //
{
    HSD_GObj* item_gobj;
    Item* item_data;

    item_gobj = lbl_804D782C->x24_items;
    while (item_gobj != NULL) {
        item_data = item_gobj->user_data;
        if (item_data->xDC8_word.flags.x7 != 0) {
            item_data->xDC8_word.flags.x5 = 1;
        }
        if (item_data->xDC8_word.flags.x3 != 0) {
            item_data->xDC8_word.flags.x3 = 0;
        }
        item_gobj = item_gobj->next;
    }
}
