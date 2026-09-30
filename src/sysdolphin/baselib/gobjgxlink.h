/**
 * @file gobjgxlink.h
 * @brief Game Object GX Link rendering queue management.
 * @details Manages doubly linked lists of GObjs assigned to GX render passes (gx_link buckets).
 *          GObjs within each gx_link queue are sorted by render_priority, determining draw
 *          order for fighters, items, stage geometry, background elements, and HUD/UI.
 * Module prefix: HSD_GObjGXLink / GObj_GX (SysDolphin Base Library entity system)
 */

#ifndef _gobjgxlink_h_
#define _gobjgxlink_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/gobj.h>

/**
 * @brief Reorders a GObj in a GX link queue immediately after another GObj.
 * @param gobj Target Game Object to reposition.
 * @param hiprio_gobj Predecessor Game Object to insert after, or NULL to place at head.
 */
void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj);

/**
 * @brief Assigns a GObj to a standard GX render link queue and inserts from tail.
 * @param gobj Target Game Object.
 * @param render_cb Callback function invoked during rendering.
 * @param gx_link GX render link bucket index (0..gx_link_max).
 * @param priority Render priority within the bucket (lower draws earlier).
 */
void GObj_SetupGXLink(HSD_GObj* gobj, GObj_RenderFunc render_cb, u8 gx_link,
                      u32 priority);

/**
 * @brief Assigns a GObj to the camera/max GX link group and inserts from tail.
 * @param gobj Camera or high-level render Game Object.
 * @param render_cb Callback function invoked during camera pass.
 * @param priority Render priority within the max GX bucket.
 */
void GObj_SetupGXLinkMax(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                         u32 priority);

/**
 * @brief Assigns a GObj to the camera/max GX link group and inserts from head.
 * @param gobj Camera or high-level render Game Object.
 * @param render_cb Callback function invoked during camera pass.
 * @param priority Render priority within the max GX bucket.
 */
void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                               u32 priority);

/**
 * @brief Unlinks a GObj from its current GX render link queue and resets GX state.
 * @param gobj Target Game Object to unlink.
 */
void HSD_GObjGXLink_8039084C(HSD_GObj* gobj);

/**
 * @brief Modifies a GObj's GX render link group and priority, re-inserting from head.
 * @param gobj Target Game Object.
 * @param gx_link New GX link bucket index.
 * @param priority New render priority.
 */
void HSD_GObjGXLink_80390908(HSD_GObj* gobj, u8 gx_link, u8 priority);

/**
 * @brief Adopts the GX link and priority of another GObj and inserts immediately before it.
 * @param gobj Target Game Object to reposition.
 * @param other Reference Game Object whose queue and priority are inherited.
 */
void HSD_GObjGXLink_803909D8(HSD_GObj* gobj, HSD_GObj* other);

#endif
