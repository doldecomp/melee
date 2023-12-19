#ifndef MELEE_IT_ITEM2_H
#define MELEE_IT_ITEM2_H

#include "it/types.h"

#include <baselib/gobj.h>

/// Transfer item on character swap - used for Zelda <-> Sheik
void it_8026B9A8(Item_GObj* gobj, HSD_GObj* arg1, u8 arg2);

/// Return flag from Item Attributes
enum_t it_8026B30C(Item_GObj* gobj);

/// Return item hold kind
enum_t it_8026B320(Item_GObj* gobj);

/// Apply Item Damage
f32 it_8026B1D4(Item_GObj* gobj, HitCapsule* itemHitboxUnk);

/// Copy Item position vector
void it_8026B294(Item_GObj* gobj, Vec3* pos);

/// Check if item is heavy
enum_t it_8026B2B4(Item_GObj* gobj);

/// Check if item is heavy again?
bool it_8026B2D8(Item_GObj* gobj);

/// Get Item ID
s32 itGetKind(Item_GObj* gobj);

/// Return item damage multiplier
f32 it_8026B334(Item_GObj* gobj);

/// Unknown item position math, related to velocity?
void it_8026B344(Item_GObj* gobj, Vec3* pos);

/// Return item's X-Axis grab range?
f32 it_8026B378(Item_GObj* gobj);

/// Return item's Y-Axis grab range?
f32 it_8026B384(Item_GObj* gobj);

/// Toggle item flag 0x15 in 0xDC8 word ON
void it_8026B390(Item_GObj* gobj);

/// Toggle item flag 0x15 in 0xDC8 word OFF
void it_8026B3A8(Item_GObj* gobj);

/// Count item entities of identical kind?
int it_8026B3C0(ItemKind kind);

/// Store Item article pointer to table
void it_8026B3F8(Article* article, s32 kind);

/// Store Stage Item article pointer to table
void it_8026B40C(Article* article, s32 kind);

/// Item Damage Math
f32 it_8026B424(s32 damage);

/// Get heal value of healing items
s32 it_8026B47C(Item_GObj* gobj);

/// Check if item is a healing item
bool it_8026B4F0(Item_GObj* gobj);

/// Get unknown float from 0x0 of item's special attributes
f32 it_8026B54C(Item_GObj* gobj);

/// Identical to #it_8026B54C but likely using a different itAttributes struct
f32 it_8026B560(Item_GObj* gobj);

/// Get unknown float from 0x4 of item's special attributes
f32 it_8026B574(Item_GObj* gobj);

/// Get unknown integer from itCommonData
s32 it_8026B588(void);

/// Check if item can fire projectiles
bool it_8026B594(Item_GObj* gobj);

/// Unknown item camera check?
HSD_GObj* it_8026B5E4(Vec3* vector, Vec3* vector2, Item_GObj* gobj);

/// Unknown item camera check 2?
HSD_GObj* it_8026B634(Vec3* vector, Vec3* vector2, Item_GObj* gobj);

/// Get facing direction of fp (?) with argument 0
f32 it_8026B684(Vec3* pos);

/// Get facing direction of fp (?) with variable argument
f32 it_8026B6A8(Vec3* pos, HSD_GObj* arg);

/// Check if item is a stage item?
bool it_8026B6C8(Item_GObj* gobj);

/// Set item's hitlag frames
void it_8026B718(Item_GObj* gobj, f32 hitlagFrames);

/// Toggle bit 3 of 0xDC8 word ON
void it_8026B724(Item_GObj* gobj);

/// Toggle bits in 0xDC8 word
void it_8026B73C(Item_GObj* gobj);

/// Bitwise operations in 0xDC8 word
bool it_8026B774(Item_GObj* gobj, u8 arg1);

/// Get Item State ID
s32 it_8026B7A4(Item_GObj* gobj);

/// Get Item Team ID
u8 it_8026B7B0(Item_GObj* gobj);

/// Get flag 0x14 of 0xDC8 word
s32 it_8026B7BC(Item_GObj* gobj);

/// Get 0x1C of Item - something to do with stale moves?
s32 it_8026B7CC(Item_GObj* gobj);

/// Get unknown var from global data
s32 it_8026B7D8(void);

/// Get unknown var from global data
s32 it_8026B7E0(void);

/// Get bit 1 of 0xDC8 word
s32 it_8026B7E8(Item_GObj* gobj);

/// Remove item from player on death?
void it_8026B7F8(Item_GObj* gobj);

/// Remove all GObj interaction references from item
bool it_8026B894(Item_GObj* gobj, HSD_GObj* referenced_gobj);

/// Return result of unk item check
s32 it_8026B924(Item_GObj* gobj);

/// Return float result of item kind and state checks
f32 it_8026B960(Item_GObj* gobj);

/// Multiply item's scale
void it_8026BAE8(Item_GObj* gobj, f32 scale_mul);

/// Clear JObj flags on item model
void it_8026BB20(Item_GObj* gobj);

/// Set JObj flags on item model
void it_8026BB44(Item_GObj* gobj);

/// Adjust item's position to fp bone
void it_8026BB68(Item_GObj* gobj, Vec3* pos);

/// Adjust item's position based on ECB?
void it_8026BB88(Item_GObj* gobj, Vec3* pos);

/// Adjust item's ECB position?
void it_8026BBCC(Item_GObj* gobj, Vec3* pos);

/// Check if item owner is a fp + decrement hitlag
void it_8026BC14(Item_GObj* gobj);

/// Return bit 0 of 0xDD0
bool it_8026BC68(Item_GObj* gobj);

/// Get item owner
HSD_GObj* it_8026BC78(Item_GObj* gobj);

/// Get item attack kind
bool it_8026BC84(Item_GObj* gobj);

/// Unknown item ECB / position update
void it_8026BC90(Item_GObj* gobj, Vec3* pos);

/// Toggle bit 2 of 0xDCD OFF
void it_8026BCF4(Item_GObj* gobj);

/// Toggle bit 2 of 0xDCD ON
void it_8026BD0C(Item_GObj* gobj);

/// Toggle bit 3 of 0xDD0 ON
void it_8026BD24(Item_GObj* gobj);

/// Toggle bit 3 of 0xDCC ON
void it_8026BD3C(Item_GObj* gobj);

/// Toggle bit 3 of 0xDCC OFF
void it_8026BD54(Item_GObj* gobj);

/// Toggle bit 3 of 0xDCD ON
void it_8026BD6C(Item_GObj* gobj);

/// Toggle bit 4 of 0xDCD ON
void it_8026BD84(Item_GObj* gobj);

/// Toggle 0x1A of 0xDC8 word ON
void it_8026BD9C(Item_GObj* gobj);

/// Toggle 0x1A of 0xDC8 word OFF
void it_8026BDB4(Item_GObj* gobj);

/// Toggle several item flags
void it_8026BDCC(Item_GObj* gobj);

/// Toggle several item flags, inverted
void it_8026BE28(Item_GObj* gobj);

/// Bob-Omb Rain Switch
HSD_GObj* it_8026BE84(BobOmbRain* bobOmbRain);

/// Get item's CollData pointer
CollData* it_8026C100(Item_GObj* gobj);

/// Check if Hammer item's head should break off
void it_8026C16C(Item_GObj* gobj, bool isHeadless);

/// Check if item has a hitbox
void it_8026C1B4(Item_GObj* gobj);

/// Get unknown var from r13 pointer
u32 it_8026C1D4(void);

/// Check if item has grabbed a GObj?
bool it_8026C1E8(Item_GObj* gobj);

/// Get item owner's port number
void it_8026C220(Item_GObj* gobj, HSD_GObj* arg1);

/// Find the closest item to the given position?
HSD_GObj* it_8026C258(Vec3* vector, f32 facingDir);

/// Unknown item position / ECB update
void it_8026C334(Item_GObj* gobj, Vec3* pos);

/// Run bomb item explosion callbacks
void it_8026C368(Item_GObj* gobj);

/// Toggle bit 3 of 0xDC8 ON for all active item GObjs?
void it_8026C3FC(void);

/// Toggle bits in 0xDC8 for all active item GObjs?
void it_8026C42C(void);

#endif
