/// @file
/// @attention Symbols in this file are placed correctly.
#ifndef MELEE_IT_ITEM_H
#define MELEE_IT_ITEM_H

#include <dolphin/mtx/mtxtypes.h>
#include <melee/it/inlines.h>
#include <melee/it/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>

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
void func_80268E5C(HSD_GObj* item_gobj, s32 itemStateID, s32 itemStateFlags);

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
void func_8026AC74(HSD_GObj* item_gobj, s32 drop_gfx, s32 drop_sfx, f32 arg8);

/// Throw Item
void func_8026AD20(HSD_GObj* item_gobj, s32 drop_gfx, s32 drop_sfx, f32 arg8);

/// Make Item Airborne
void func_8026ADC0(HSD_GObj* item_gobj);

/// Increment something
u32 func_8026AE60(void);

void func_8026AE84(Item* item_data, enum_t sfx_id, u8 pan, u8 volume);
void func_8026AF0C(Item* item_data, enum_t sfx_id, u8 pan, u8 volume);

/// Play Item SFX 3
void func_8026AFA0(Item* item_data, enum_t sfx_id, u8 pan, u8 volume);

/// Stop Item SFX
void func_8026B034(Item* item_data);

/// Stop Item SFX 2
void func_8026B074(Item* item_data);

/// Check if item is grabbable
bool func_8026B1A4(HSD_GObj* item_gobj);

#endif
