#ifndef GALE01_26B1D4
#define GALE01_26B1D4
#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/types.h>

/// Apply Item Damage
/* 26B1D4 */ float it_8026B1D4(Item_GObj* gobj, HitCapsule* itemHitboxUnk);
/// Copy Item position vector
/* 26B294 */ void it_8026B294(Item_GObj* gobj, Vec3* pos);
/// Check if item is heavy
/* 26B2B4 */ bool itIsHeavy(Item_GObj* gobj);
/// Check if item is heavy again?
/* 26B2D8 */ bool it_8026B2D8(Item_GObj* gobj);
/// Get Item ID
/* 26B300 */ ItemKind itGetKind(Item_GObj* gobj);
/// Return flag from Item Attributes
/* 26B30C */ enum_t it_8026B30C(Item_GObj* gobj);
/// Return item hold kind
/* 26B320 */ Item_HoldKinds itGetHoldKind(Item_GObj* gobj);
/// Return item damage multiplier
/* 26B334 */ float itGetDamageMultiplier(Item_GObj* gobj);
/// Unknown item position math, related to velocity?
/* 26B344 */ void it_8026B344(Item_GObj* gobj, Vec3* pos);
/// Return item's X-Axis grab range?
/* 26B378 */ float itGetGrabRangeX(Item_GObj* gobj);
/// Return item's Y-Axis grab range?
/* 26B384 */ float itGetGrabRangeY(Item_GObj* gobj);
/// Toggle item flag 0x15 in 0xDC8 word ON
/* 26B390 */ void it_8026B390(Item_GObj* gobj);
/// Toggle item flag 0x15 in 0xDC8 word OFF
/* 26B3A8 */ void it_8026B3A8(Item_GObj* gobj);
/// Count item entities of identical kind?
/* 26B3C0 */ int it_8026B3C0(ItemKind kind);
/// Store Item article pointer to table
/* 26B3F8 */ void it_8026B3F8(Article* article, s32 kind);
/// Store Stage Item article pointer to table
/* 26B40C */ void it_8026B40C(Article* article, s32 kind);
/// Item Damage Math
/* 26B424 */ float it_8026B424(int damage);
/// Get heal value of healing items
/* 26B47C */ s32 it_8026B47C(Item_GObj* gobj);
/// Check if item is a healing item
/* 26B4F0 */ bool it_8026B4F0(Item_GObj* gobj);
/// Get unknown float from 0x0 of item's special attributes
/* 26B54C */ float it_8026B54C(Item_GObj* gobj);
/// Identical to #it_8026B54C but likely using a different itAttributes struct
/* 26B560 */ float it_8026B560(Item_GObj* gobj);
/// Get unknown float from 0x4 of item's special attributes
/* 26B574 */ float it_8026B574(Item_GObj* gobj);
/// Get unknown integer from itCommonData
/* 26B588 */ s32 it_8026B588(void);
/// Check if item can fire projectiles
/* 26B594 */ bool it_8026B594(Item_GObj* gobj);
/// Unknown item camera check?
/* 26B5E4 */ HSD_GObj* it_8026B5E4(Vec3* vector, Vec3* vector2,
                                   Item_GObj* gobj);
/// Unknown item camera check 2?
/* 26B634 */ Fighter_GObj* it_8026B634(Vec3*, Vec3*, Item_GObj*, float);
/// Get facing direction of fp (?) with argument 0
/* 26B684 */ float it_8026B684(Vec3* pos);
/// Get facing direction of fp (?) with variable argument
/* 26B6A8 */ float it_8026B6A8(Vec3* pos, HSD_GObj* arg);
/// Check if item is a stage item?
/* 26B6C8 */ bool it_8026B6C8(Item_GObj* gobj);
/// Set item's hitlag frames
/* 26B718 */ void it_8026B718(Item_GObj* gobj, float hitlagFrames);
/// Toggle bit 3 of 0xDC8 word ON
/* 26B724 */ void it_8026B724(Item_GObj* gobj);
/// Toggle bits in 0xDC8 word
/* 26B73C */ void it_8026B73C(Item_GObj* gobj);
/// Bitwise operations in 0xDC8 word
/* 26B774 */ bool it_8026B774(Item_GObj* gobj, u8 arg1);
/// Get Item State ID
/* 26B7A4 */ s32 itGetMotionId(Item_GObj* gobj);
/// Get Item Team ID
/* 26B7B0 */ u8 itGetTeamId(Item_GObj* gobj);
/// Get flag 0x14 of 0xDC8 word
/* 26B7BC */ s32 it_8026B7BC(Item_GObj* gobj);
/// Get 0x1C of Item - something to do with stale moves?
/* 26B7CC */ s32 it_8026B7CC(Item_GObj* gobj);
/// Get unknown var from global data
/* 26B7D8 */ s32 it_8026B7D8(void);
/// Get unknown var from global data
/* 26B7E0 */ s32 it_8026B7E0(void);
/// Get bit 1 of 0xDC8 word
/* 26B7E8 */ s32 it_8026B7E8(Item_GObj* gobj);
/// Remove item from player on death?
/* 26B7F8 */ void it_8026B7F8(Item_GObj* gobj);
/// Remove all GObj interaction references from item
/* 26B894 */ bool it_8026B894(Item_GObj* gobj, HSD_GObj* referenced_gobj);
/// Return result of unk item check
/* 26B924 */ s32 it_8026B924(Item_GObj* gobj);
/// Return float result of item kind and state checks
/* 26B960 */ float it_8026B960(Item_GObj* gobj);
/// Transfer item on character swap - used for Zelda <-> Sheik
/* 26B9A8 */ void it_8026B9A8(Item_GObj* gobj, HSD_GObj* arg1,
                              Fighter_Part arg2);
/// Multiply item's scale
/* 26BAE8 */ void it_8026BAE8(Item_GObj* gobj, float scale_mul);
/// Clear JObj flags on item model
/* 26BB20 */ void it_8026BB20(Item_GObj* gobj);
/// Set JObj flags on item model
/* 26BB44 */ void it_8026BB44(Item_GObj* gobj);
/// Adjust item's position to fp bone
/* 26BB68 */ void it_8026BB68(Item_GObj* gobj, Vec3* pos);
/// Adjust item's position based on ECB?
/* 26BB88 */ void it_8026BB88(Item_GObj* gobj, Vec3* pos);
/// Adjust item's ECB position?
/* 26BBCC */ void it_8026BBCC(Item_GObj* gobj, Vec3* pos);
/// Check if item owner is a fp + decrement hitlag
/* 26BC14 */ void it_8026BC14(Item_GObj* gobj);
/// Return bit 0 of 0xDD0
/* 26BC68 */ bool it_8026BC68(Item_GObj* gobj);
/// Get item owner
/* 26BC78 */ HSD_GObj* itGetOwner(Item_GObj* gobj);
/// Get item attack kind
/* 26BC84 */ s32 itGetAttackId(Item_GObj* gobj);
/// Unknown item ECB / position update
/* 26BC90 */ void it_8026BC90(Item_GObj* gobj, Vec3* pos);
/// Toggle bit 2 of 0xDCD OFF
/* 26BCF4 */ void it_8026BCF4(Item_GObj* gobj);
/// Toggle bit 2 of 0xDCD ON
/* 26BD0C */ void it_8026BD0C(Item_GObj* gobj);
/// Toggle bit 3 of 0xDD0 ON
/* 26BD24 */ void it_8026BD24(Item_GObj* gobj);
/// Toggle bit 3 of 0xDCC ON
/* 26BD3C */ void it_8026BD3C(Item_GObj* gobj);
/// Toggle bit 3 of 0xDCC OFF
/* 26BD54 */ void it_8026BD54(Item_GObj* gobj);
/// Toggle bit 3 of 0xDCD ON
/* 26BD6C */ void it_8026BD6C(Item_GObj* gobj);
/// Toggle bit 4 of 0xDCD ON
/* 26BD84 */ void it_8026BD84(Item_GObj* gobj);
/// Toggle 0x1A of 0xDC8 word ON
/* 26BD9C */ void it_8026BD9C(Item_GObj* gobj);
/// Toggle 0x1A of 0xDC8 word OFF
/* 26BDB4 */ void it_8026BDB4(Item_GObj* gobj);
/// Toggle several item flags
/* 26BDCC */ void it_8026BDCC(Item_GObj* gobj);
/// Toggle several item flags, inverted
/* 26BE28 */ void it_8026BE28(Item_GObj* gobj);
/// Bob-Omb Rain Switch
/* 26BE84 */ HSD_GObj* it_8026BE84(BobOmbRain* bobOmbRain);
/// Get item's CollData pointer
/* 26C100 */ CollData* it_8026C100(Item_GObj* gobj);
/// Check if Hammer item's head should break off
/* 26C16C */ void it_8026C16C(Item_GObj* gobj, bool isHeadless);
/// Check if item has a hitbox
/* 26C1B4 */ bool it_8026C1B4(Item_GObj* gobj);
/// Get unknown var from r13 pointer
/* 26C1D4 */ u32 it_8026C1D4(void);
/// Check if item has grabbed a GObj?
/* 26C1E8 */ bool it_8026C1E8(Item_GObj* gobj);
/// Get item owner's port number
/* 26C220 */ void it_8026C220(Item_GObj* gobj, HSD_GObj* arg1);
/// Find the closest item to the given position?
/* 26C258 */ HSD_GObj* it_8026C258(Vec3* vector, float facingDir);
/// Unknown item position / ECB update
/* 26C334 */ void it_8026C334(Item_GObj* gobj, Vec3* pos);
/// Run bomb item explosion callbacks
/* 26C368 */ void it_8026C368(Item_GObj* gobj);
/// Toggle bit 3 of 0xDC8 ON for all active item GObjs?
/* 26C3FC */ void it_8026C3FC(void);
/// Toggle bits in 0xDC8 for all active item GObjs?
/* 26C42C */ void it_8026C42C(void);

#endif
