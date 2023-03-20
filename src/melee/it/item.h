/// @file
/// @attention Symbols in this file are placed correctly.
/// @defgroup melee_it_item item
/// @{
#ifndef MELEE_IT_ITEM_H
#define MELEE_IT_ITEM_H

#include <dolphin/mtx/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/it/types.h>
#include <Runtime/platform.h>

extern HSD_ObjAllocData itemAllocData;
extern HSD_ObjAllocData unkAllocData1;
extern HSD_ObjAllocData lbl_804A0C38;
extern HSD_ObjAllocUnk lbl_804A0C64;
extern HSD_ObjAllocUnk2 lbl_804A0CCC;
extern S32Vec3 lbl_804A0E24;

/// Checks if items are enabled
bool func_80266F3C(void);

/// Check to load ItCo.dat/usd
void func_80266F70(void);

/// ItCo prefunction with 0
void func_80266FA8(void);

/// Init item struct?
void func_80266FCC(void);

/// Remove Camera Box
void func_80267454(HSD_GObj* item_gobj);

/// Setup Item JObj
void func_802680CC(HSD_GObj* item_gobj);

/// Set item model scale
void func_8026849C(HSD_GObj* item_gobj);

/// Item spawn prefunction - spawn airborne
void func_80268B18(SpawnItem* spawnItem);

/// Item spawn prefunction - spawn grounded
void func_80268B5C(SpawnItem* spawnItem);

/// Item spawn prefunction - spawn grounded and toggle unknown true
void func_80268B9C(SpawnItem* spawnItem);

/// Unk Item AObj-related function
void func_80268D34(HSD_GObj* item_gobj, struct ItemStateDesc* itemStateDesc);

/// Advance item animation?
void func_80268DD4(HSD_GObj* item_gobj, f32 arg8);

/// Copy item script
void func_80268E40(Item* item_data, struct ItemStateDesc* itemStateDesc);

/// Item State Change
void func_80268E5C(HSD_GObj* item_gobj, enum_t asid,
                   Item_StateChangeFlags flags);

/// Advance item animation + script?
void func_802694CC(HSD_GObj* item_gobj);

/// Item Think - Physics
void func_802697D4(HSD_GObj* item_gobj);

/// Item Think - Collision
void func_80269978(HSD_GObj* item_gobj);

/// Set damage taken
void func_80269CA0(Item* item_data, s32 damage);

/// Remove Item from Player
void func_8026A848(HSD_GObj* item_gobj, HSD_GObj* fighter_gobj);

/// Destroy Item
void func_8026A8EC(HSD_GObj* item_gobj);

/// Make Item Held
void func_8026AB54(HSD_GObj* item_gobj, HSD_GObj* pickupGFX, u8 pickupSFX);

/// Drop Item
void func_8026ABD8(HSD_GObj* item_gobj, Vec3* pos, f32 arg2);

/// This is actually another Item Drop function
void func_8026AC74(HSD_GObj* this, enum_t drop_gfx, enum_t drop_sfx, f32 arg3);

/// Throw Item
void func_8026AD20(HSD_GObj* this, s32 drop_gfx, s32 drop_sfx, f32 arg8);

/// Make Item Airborne
void func_8026ADC0(HSD_GObj* item_gobj);

/// Increment something
uint func_8026AE60(void);

/// Play Item SFX
void func_8026AE84(Item* item_data, enum_t sfx, int pan, int volume);

/// Play Item SFX 2
void func_8026AF0C(Item* item_data, enum_t sfx, int pan, int volume);

/// Play Item SFX 3
void func_8026AFA0(Item* item_data, enum_t sfx, int pan, int volume);

/// Stop Item SFX
void func_8026B034(Item* item_data);

/// Stop Item SFX 2
void func_8026B074(Item* item_data);

/// Check if item is grabbable
bool Item_IsGrabbable(HSD_GObj* item_gobj);

/// Initialize item coordinates?
void func_80267130(HSD_GObj* item_gobj, SpawnItem* spawnItem);

/// Set Item Hold kind
void func_802674AC(SpawnItem* spawnItem);

void func_802675A8(HSD_GObj* item_gobj);

void func_802676F4(HSD_GObj* item_gobj);

bool func_8026784C(enum_t dropItem, int _);

/// Store Item Pointers
void func_80267978(HSD_GObj* item_gobj);

void ItUnkHoldKind(HSD_GObj* item_gobj);
void HSD_JObjSetScaleItem(Item* it, HSD_JObj* jobj, Vec3* scl);

/// Initialize item variables
void func_80267AA8(HSD_GObj* item_gobj, SpawnItem* spawnItem);

/// Set up item render objects?
void func_8026814C(HSD_GObj* item_gobj);

/// Initialize item bones
bool func_802682F0(HSD_GObj* item_gobj);

/// Set up item dynamic bones
void func_80268560(HSD_GObj* item_gobj);

void lbl_802693E4(HSD_GObj* item_gobj);

/// Item Think - Animation
void lbl_80269528(HSD_GObj* item_gobj);

/// Item Think - Accessory + Camera Box
void lbl_80269A9C(HSD_GObj* item_gobj);

/// Item Think - Yellow Bar Collision (cb_JumpedOn)
void lbl_80269B60(HSD_GObj* item_gobj);

/// Item Think - Grab
void lbl_80269BE4(HSD_GObj* item_gobj);

/// Item Think - Hit Collision Logic
void lbl_80269C5C(HSD_GObj* item_gobj);

/// Item Think - Hit Collision
void lbl_8026A294(HSD_GObj* item_gobj);

/// Item Think - Process Dynamic Bones
void lbl_8026A788(HSD_GObj* item_gobj);

/// Item Think - Spawn
void func_8026A810(HSD_GObj* item_gobj);

/// Clear Item Struct ?
void lbl_8026AE10(void* user_data);

/// Create Item
HSD_GObj* func_8026862C(SpawnItem* spawnItem);

/// Adds #HSD_AObj instances to item model
void func_80268BE0(HSD_JObj* item_jobj, HSD_AnimJoint* anim_joint,
                   HSD_MatAnimJoint* matanim_joint,
                   HSD_ShapeAnimJoint* shapeanim_joint, Item* item_data);

/// Item Think - Exit Hitlag Check
void func_8026A0A0(HSD_GObj* item_gobj);

/// Item Think - Exit Hitlag Check 2
void func_8026A0FC(HSD_GObj* item_gobj);

/// Item Think - Exit Hitlag
void func_8026A1E8(HSD_GObj* item_gobj);

void lbl_802693E4(HSD_GObj* item_gobj);

/// Item Think - Check for Blast Zones
bool func_802696CC(HSD_GObj* item_gobj);

/// Set damage struct
void func_80269CC4(HSD_GObj* item_gobj);

/// Item Think - Shield Collision
bool func_80269DC8(HSD_GObj* item_gobj);

/// Item Think - On Reflect
bool func_80269F14(HSD_GObj* item_gobj);

/// Item Think - Enter Hitlag
void func_8026A158(HSD_GObj* item_gobj);

void func_8026A158_helper(HSD_GObj* atkCollGObj);

void func_8026A1E8_inline(HSD_GObj* atkCollGObj);

bool processCallback(HSD_GObjPredicate cb, HSD_GObj* item_gobj,
                     Item* item_data);

bool OnTakeDamageThink(HSD_GObj* item_gobj, Item* item_data);
bool OnClankThink(HSD_GObj* item_gobj, Item* item_data);
bool OnGiveDamageThink(HSD_GObj* item_gobj, Item* item_data);
void EnterHitlagThink(HSD_GObj* item_gobj, Item* item_data);
void checkHitLag(f32 min_value, Item* item_data);
void DestroyItemInline(HSD_GObj* item_gobj, Item* item_data);
void ItemSwitch(HSD_GObj* item_gobj);
void RunCallback(HSD_GObj* this, HSD_GObjEvent arg1);
void func_8026A8EC_inline1(HSD_GObj* this);
void func_8026A8EC_inline2(HSD_GObj* item_gobj);
void func_8026A8EC_inline3(HSD_GObj* item_gobj);
void foobar(HSD_GObj* gobj);
void foobar2(HSD_GObj* gobj);
void foobar3(HSD_GObj* gobj);

/// Stop All Item SFX
void func_8026B0B4(HSD_GObj* item_gobj);

void Item_OnUserDataRemove(any_t user_data);
void HSD_JObjSetFacingDirItem(HSD_JObj* jobj, Item* it);

#define GET_ITEM(gobj) ((Item*) HSD_GObjGetUserData(gobj))

/// @deprecated Use #GET_ITEM instead.
static inline Item* GetItemData(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data;
}

#endif

/// @}
