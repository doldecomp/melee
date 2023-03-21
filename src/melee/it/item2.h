#ifndef MELEE_IT_ITEM2_H
#define MELEE_IT_ITEM2_H

#include "it/types.h"

#include <baselib/gobj.h>

/// Transfer item on character swap - used for Zelda <-> Sheik
void func_8026B9A8(HSD_GObj* item_gobj, HSD_GObj* arg1, u8 arg2);

s32 func_8026B30C(HSD_GObj*);

/// Return item hold kind
s32 func_8026B320(HSD_GObj*);

bool func_8026B594(HSD_GObj*);

/// Apply Item Damage
f32 func_8026B1D4(HSD_GObj* item_gobj, itHit* itemHitboxUnk);

/// Copy Item position vector
void func_8026B294(HSD_GObj* item_gobj, Vec3* pos);

/// Check if item is heavy
bool func_8026B2B4(HSD_GObj* item_gobj);

/// Check if item is heavy again?
bool func_8026B2D8(HSD_GObj* item_gobj);

/// Get Item ID
s32 itGetKind(HSD_GObj* item_gobj);

/// Return flag from Item Attributes
s32 func_8026B30C(HSD_GObj* item_gobj);

/// Return item damage multiplier
f32 func_8026B334(HSD_GObj* item_gobj);

/// Unknown item position math, related to velocity?
void func_8026B344(HSD_GObj* item_gobj, Vec3* pos);

/// Return item's X-Axis grab range?
f32 func_8026B378(HSD_GObj* item_gobj);

/// Return item's Y-Axis grab range?
f32 func_8026B384(HSD_GObj* item_gobj);

/// Toggle item flag 0x15 in 0xDC8 word ON
void func_8026B390(HSD_GObj* item_gobj);

/// Toggle item flag 0x15 in 0xDC8 word OFF
void func_8026B3A8(HSD_GObj* item_gobj);

/// Count item entities of identical kind?
int func_8026B3C0(ItemKind kind);

/// Store Item article pointer to table
void func_8026B3F8(Article* article, s32 kind);

/// Store Stage Item article pointer to table
void func_8026B40C(Article* article, s32 kind);

/// Item Damage Math
f32 func_8026B424(s32 damage);

/// Get heal value of healing items
s32 func_8026B47C(HSD_GObj* item_gobj);

/// Check if item is a healing item
bool func_8026B4F0(HSD_GObj* item_gobj);

/// Get unknown float from 0x0 of item's special attributes
f32 func_8026B54C(HSD_GObj* item_gobj);

/// Identical to #func_8026B54C but likely using a different itAttributes
/// struct
f32 func_8026B560(HSD_GObj* item_gobj);

/// Get unknown float from 0x4 of item's special attributes
f32 func_8026B574(HSD_GObj* item_gobj);

/// Get unknown integer from itCommonData
s32 func_8026B588(void);

/// Check if item can fire projectiles
bool func_8026B594(HSD_GObj* item_gobj);

/// Unknown item camera check?
HSD_GObj* func_8026B5E4(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj);

/// Unknown item camera check 2?
HSD_GObj* func_8026B634(Vec3* vector, Vec3* vector2, HSD_GObj* item_gobj);

/// Get facing direction of fp (?) with argument 0
f32 func_8026B684(Vec3* pos);

/// Get facing direction of fp (?) with variable argument
f32 func_8026B6A8(Vec3* pos, HSD_GObj* arg);

/// Check if item is a stage item?
bool func_8026B6C8(HSD_GObj* item_gobj);

/// Set item's hitlag frames
void func_8026B718(HSD_GObj* item_gobj, f32 hitlagFrames);

/// Toggle bit 3 of 0xDC8 word ON
void func_8026B724(HSD_GObj* item_gobj);

/// Toggle bits in 0xDC8 word
void func_8026B73C(HSD_GObj* item_gobj);

/// Bitwise operations in 0xDC8 word
bool func_8026B774(HSD_GObj* item_gobj, u8 arg1);

/// Get Item State ID
s32 func_8026B7A4(HSD_GObj* item_gobj);

/// Get Item Team ID
u8 func_8026B7B0(HSD_GObj* item_gobj);

/// Get flag 0x14 of 0xDC8 word
s32 func_8026B7BC(HSD_GObj* item_gobj);

/// Get 0x1C of Item - something to do with stale moves?
s32 func_8026B7CC(HSD_GObj* item_gobj);

/// Get unknown var from global data
s32 func_8026B7D8(void);

/// Get unknown var from global data
s32 func_8026B7E0(void);

/// Get bit 1 of 0xDC8 word
s32 func_8026B7E8(HSD_GObj* item_gobj);

/// Remove item from player on death?
void func_8026B7F8(HSD_GObj* gobj);

/// Remove all GObj interaction references from item
bool func_8026B894(HSD_GObj* item_gobj, HSD_GObj* referenced_gobj);

/// Return result of unk item check - requires -g compiler flag / Frank
/// modifications to match
s32 func_8026B924(HSD_GObj* item_gobj);

/// Return float result of item kind and state checks - requires -g compiler
/// flag / Frank modifications to match
f32 func_8026B960(HSD_GObj* item_gobj);

/// Multiply item's scale
void func_8026BAE8(HSD_GObj* item_gobj, f32 scale_mul);

/// Clear JObj flags on item model
void func_8026BB20(HSD_GObj* item_gobj);

/// Set JObj flags on item model
void func_8026BB44(HSD_GObj* item_gobj);

/// Adjust item's position to fp bone
void func_8026BB68(HSD_GObj* gobj, Vec3* pos);

/// Adjust item's position based on ECB?
void func_8026BB88(HSD_GObj* item_gobj, Vec3* pos);

/// Adjust item's ECB position?
void func_8026BBCC(HSD_GObj* item_gobj, Vec3* pos);

/// Check if item owner is a fp + decrement hitlag
void func_8026BC14(HSD_GObj* item_gobj);

/// Return bit 0 of 0xDD0
bool func_8026BC68(HSD_GObj* item_gobj);

/// Get item owner
HSD_GObj* func_8026BC78(HSD_GObj* item_gobj);

/// Get item attack kind
bool func_8026BC84(HSD_GObj* item_gobj);

/// Unknown item ECB / position update
void func_8026BC90(HSD_GObj* item_gobj, Vec3* pos);

/// Toggle bit 2 of 0xDCD OFF
void func_8026BCF4(HSD_GObj* item_gobj);

/// Toggle bit 2 of 0xDCD ON
void func_8026BD0C(HSD_GObj* item_gobj);

/// Toggle bit 3 of 0xDD0 ON
void func_8026BD24(HSD_GObj* item_gobj);

/// Toggle bit 3 of 0xDCC ON
void func_8026BD3C(HSD_GObj* item_gobj);

/// Toggle bit 3 of 0xDCC OFF
void func_8026BD54(HSD_GObj* item_gobj);

/// Toggle bit 3 of 0xDCD ON
void func_8026BD6C(HSD_GObj* item_gobj);

/// Toggle bit 4 of 0xDCD ON
void func_8026BD84(HSD_GObj* item_gobj);

/// Toggle 0x1A of 0xDC8 word ON
void func_8026BD9C(HSD_GObj* item_gobj);

/// Toggle 0x1A of 0xDC8 word OFF
void func_8026BDB4(HSD_GObj* item_gobj);

/// Toggle several item flags
void func_8026BDCC(HSD_GObj* item_gobj);

/// Toggle several item flags, inverted
void func_8026BE28(HSD_GObj* item_gobj);

/// Bob-Omb Rain Switch
HSD_GObj* func_8026BE84(BobOmbRain* bobOmbRain);

/// Get item's CollData pointer
CollData* func_8026C100(HSD_GObj* item_gobj);

/// Check if Hammer item's head should break off
void func_8026C16C(HSD_GObj* item_gobj, bool isHeadless);

/// Check if item has a hitbox
void func_8026C1B4(HSD_GObj* item_gobj);

/// Get unknown var from r13 pointer
u32 func_8026C1D4(void);

/// Check if item has grabbed a GObj?
bool func_8026C1E8(HSD_GObj* item_gobj);

/// Get item owner's port number
void func_8026C220(HSD_GObj* item_gobj, HSD_GObj* gobj);

/// Find the closest item to the given position?
HSD_GObj* func_8026C258(Vec3* vector, f32 facingDir);

/// Unknown item position / ECB update
void func_8026C334(HSD_GObj* item_gobj, Vec3* pos);

/// Run bomb item explosion callbacks
void func_8026C368(HSD_GObj* item_gobj);

/// Toggle bit 3 of 0xDC8 ON for all active item GObjs?
void func_8026C3FC(void);

/// Toggle bits in 0xDC8 for all active item GObjs?
void func_8026C42C(void);

#endif
