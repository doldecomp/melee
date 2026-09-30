/**
 * @file itmaplib.h
 * @brief Item Map Collision Library
 * @details Primary interface between Items and the Map/ECB (Environment Collision Box) systems.
 * Includes logic for querying ground lines, calculating ECB coordinates, resolving ledge limits, 
 * slope physics, and terrain collision detection for items.
 * Module prefix: it (Item)
 */
#ifndef GALE01_ITMAPLIB
#define GALE01_ITMAPLIB

#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/lb/types.h>

/** @brief Resolves map collisions between two item GObjs */
/* 2759DC */ void it_802759DC(Item_GObj* item_gobj1, Item_GObj* item_gobj2);

/** @brief Initializes item map collision context against an owner GObj */
/* 275BC8 */ void it_80275BC8(Item_GObj* item_gobj, HSD_GObj* owner_gobj);

/** @brief Sets the ECB (Environment Collision Box) boundaries for an item */
/* 275D5C */ void it_80275D5C(Item_GObj* item_gobj, itECB* ecb);

/** @brief Updates ECB layout for an item based on facing direction and scale */
/* 275DFC */ void it_80275DFC(Item_GObj* item_gobj);

/** @brief Configures ECB boundary size logic upon item spawn */
/* 275E98 */ void it_80275E98(Item_GObj* item_gobj, SpawnItem* spawnItem);

/** @brief Calculates map collision coordinate queries for an airborne item */
/* 276100 */ void it_80276100(Item_GObj* item_gobj, Vec3* pos);

/** @brief Calculates map collision coordinate queries for a grounded item */
/* 276174 */ void it_80276174(Item_GObj* item_gobj, Vec3* pos);

/** @brief Processes item ECB boundary updates */
/* 276214 */ void it_80276214(Item_GObj* item_gobj);

/** @brief Processes item ECB collision query resolution */
/* 276278 */ void it_80276278(Item_GObj* item_gobj);

/** @brief Assigns grounded map collision state flag */
/* 2762B0 */ void it_802762B0(Item* item_data);

/** @brief Assigns airborne map collision state flag */
/* 2762BC */ void it_802762BC(Item* item_data);

/** @brief Detects ledge proximity by checking left and right edge collision flags */
/* 2762D8 */ bool it_802762D8(Item_GObj* item_gobj);

/** @brief Checks if item is in contact with walls and returns side index */
/* 276308 */ s32 it_80276308(Item_GObj* item_gobj);

/** @brief Checks wall contacts and retrieves the normal vector of the wall */
/* 276348 */ s32 it_80276348(Item_GObj* item_gobj, Vec3* wall_normal);

/** @brief Queries ground line contact and updates floor index */
/* 2763B8 */ bool it_802763B8(Item_GObj* item_gobj);

/** @brief Queries ceiling contact and updates ceiling index */
/* 2763E0 */ s32 it_802763E0(Item_GObj* item_gobj);

/** @brief Returns the normal vector for whatever surface the item is colliding with */
/* 276408 */ void it_80276408(Item_GObj* item_gobj, CollData* coll, Vec3* normal);

/** @brief Calculates item slope rotation based on the ground normal vector */
/* 27649C */ f32 it_8027649C(Item_GObj* item_gobj);

/** @brief Applies rotation transform to item model based on slope angle */
/* 2765BC */ void it_802765BC(Item_GObj* item_gobj, enum_t axis);

/** @brief Calculates rotation components across axes for slope integration */
/* 276934 */ void it_80276934(Item_GObj* item_gobj, enum_t axis);

/** @brief Corrects rotation for grounded items on specific terrain */
/* 276CB8 */ void it_80276CB8(Item_GObj* item_gobj);

/** @brief Updates logical normal vectors from collision data */
/* 276CEC */ void it_80276CEC(Item_GObj* item_gobj);

/** @brief Corrects penetration resolving logic based on collision limits */
/* 276D9C */ bool it_80276D9C(Item_GObj* item_gobj, enum_t axis);

/** @brief Central handler for physics collision iteration */
/* 276FC4 */ void it_80276FC4(Item_GObj* item_gobj, s32 axis);

/** @brief Applies terrain slope physics calculations to item velocity */
/* 277040 */ bool it_80277040(Item_GObj* item_gobj);

/** @brief Integrates physics velocity vector against item position */
/* 27737C */ void it_8027737C(Item_GObj* item_gobj, Vec3* pos);

/** @brief Re-evaluates item environmental collision state */
/* 277544 */ bool it_80277544(Item_GObj* item_gobj);

/** @brief Modifies slope orientation component vectors */
/* 2775F0 */ void it_802775F0(Item_GObj* item_gobj, Vec3* pos);

/** @brief Unresolved internal ground check routine */
/* 27770C */ bool it_8027770C(Item_GObj* item_gobj);

/** @brief Prepares ECB size components before collision query */
/* 27781C */ bool it_8027781C(Item_GObj* item_gobj);

/** @brief Internal handler for collision penetration offsets */
/* 277C40 */ void it_80277C40(Item_GObj* item_gobj, s32 axis);

#endif
