/**
 * @file
 * @brief Fighting Wireframe items (@c It_Kind_Boy and @c It_Kind_Girl).
 */

#ifndef GALE01_ITZAKO
#define GALE01_ITZAKO

#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/// Spawns and initializes a Zako item.
/* 27B5B0 */ Item_GObj* it_8027B5B0(ItemKind kind, Vec3* pos, HSD_JObj* jobj,
                                    Vec3* vel, bool use_init);

/// Resets Zako item state variables.
/* 27B730 */ void it_8027B730(Item_GObj* item_gobj);

/// Calculates Zako item knockback velocity based on hit angle.
/* 27B798 */ bool it_8027B798(Item_GObj* item_gobj, Vec3* target);

/// Initializes physics parameters for a spawned Zako item.
/* 27B964 */ void it_8027B964(Item_GObj* item_gobj, bool chk);

/// Calculates randomized camera-relative position offsets.
/* 27BA54 */ int it_8027BA54(HSD_GObj* gobj, Vec3* target);

/// Applies Euler angle rotations to a vector.
/* 27BB1C */ void it_8027BB1C(Vec3* pos, Vec3* target);

/// Rotates Zako items based on terrain collision normals.
/* 27BBF4 */ void it_8027BBF4(Item_GObj* item_gobj, bool arg_chk,
                              f64 facing_dir, f32 frames);

/// Internal wrapper for normal-based rotation (variant 1).
/* 27C0A8 */ void it_8027C0A8(Item_GObj* item_gobj, f32 facing_dir,
                              f32 frames);

/// Internal wrapper for normal-based rotation (variant 2).
/* 27C0CC */ void it_8027C0CC(Item_GObj* item_gobj, f32 facing_dir,
                              f32 frames);

/// Computes Zako item rotation from arbitrary reference angles.
/* 27C0F0 */ void it_8027C0F0(Item_GObj* item_gobj, Vec3* target,
                              f64 facing_dir, f32 frames);

/// Corrects X/Y/Z rotations for a Zako item.
/* 27C56C */ void it_8027C56C(Item_GObj* item_gobj, f32 y_rot);

/// Unused Zako verification routine.
/* 27C794 */ bool it_8027C794(Item_GObj* item_gobj);

/// Evaluates lifetime logic for Zako parts.
/* 27C79C */ bool it_8027C79C(Item_GObj* item_gobj);

/// Processes Zako item state with a provided callback function.
/* 27C824 */ bool it_8027C824(Item_GObj* item_gobj,
                              s32 (*callback_func)(Item_GObj*));

/// Handles Zako item destruction callback.
/* 27C8B0 */ void it_2725_Logic9_Destroyed(Item_GObj* item_gobj);

/// Calculates proportional vector orientations.
/* 27C8D0 */ void it_8027C8D0(Vec3* pos, Vec3* target, f32 facing_dir);

/// Triggers randomized audio events for Zako pieces.
/* 27C9D8 */ void it_8027C9D8(Item* item_data);

/// Evaluates fighter animation states against Zako interactions.
/* 27CA7C */ bool it_8027CA7C(HSD_GObj* gobj);

/// Halts Zako item velocity and clears ownership.
/* 27CAD8 */ void it_8027CAD8(Item_GObj* item_gobj);

/// Inherits facing direction from the holding fighter.
/* 27CB3C */ void it_8027CB3C(Item_GObj* item_gobj);

/// Readjusts facing direction when caught or grabbed.
/* 27CBA4 */ void it_8027CBA4(Item_GObj* item_gobj);

/// Returns lifetime boundaries for standard items.
/* 27CBFC */ f32 it_8027CBFC(Item_GObj* item_gobj);

/// Evaluates rare item drops (e.g. trophies) upon Zako defeat.
/* 27CC88 */ Item_GObj* it_8027CC88(Item_GObj* item_gobj_arg);

/// Grants points to the player upon Zako item absorption/destruction.
/* 27CE18 */ void it_8027CE18(Item_GObj* item_gobj);

/// Triggers the destruction event in the generator.
/* 27CE44 */ void it_8027CE44(Item_GObj* item_gobj);

/// Game&Watch specific initialization hook for Zako interactions.
/* 27CE64 */ void it_8027CE64(Item_GObj* item_gobj, HSD_GObj* fighter_gobj,
                              void* attr_address);

#endif
