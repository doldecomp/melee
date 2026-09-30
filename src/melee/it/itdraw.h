/**
 * @file itdraw.h
 * @brief Item drawing and rendering dispatch
 * @details Hooks into sysdolphin's GObj rendering pipeline to display items, their dynamic bones, and debug overlays.
 * Module prefix: it (Item)
 */
#ifndef GALE01_ITDRAW_H
#define GALE01_ITDRAW_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <melee/it/types.h>

/**
 * @brief Dispatches drawing for an item's JObj tree, applying camera shake if needed.
 */
/* 26EB18 */ void it_8026EB18(HSD_GObj* gobj, s32 rendermode, Vec3* shake_offset);
/**
 * @brief Disables rendering for specific dynamic bones within an item.
 */
/* 26EBC8 */ void it_8026EBC8(HSD_GObj* gobj, u16 count, u8* indices);
/**
 * @brief Enables rendering for specific dynamic bones within an item.
 */
/* 26EC54 */ void it_8026EC54(HSD_GObj* gobj, u16 count, u8* indices);
/**
 * @brief Draws debug hitboxes, hurtboxes, and environment collision for items.
 * @return 1 if any debug graphics were drawn, 0 otherwise.
 */
/* 26ECE0 */ u32 it_8026ECE0(Item_GObj* gobj, u32 rendermode);
/**
 * @brief Main render callback for items. Hooks into sysdolphin GObj display.
 */
/* 26EECC */ void it_8026EECC(HSD_GObj* gobj, intptr_t rendermode);

#endif
