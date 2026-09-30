/**
 * @file gobjplink.h
 * @brief Game Object Priority Link management
 * @details Manages the priority-linked list of GObjs which dictates the main execution order of objects in the game loop.
 */
#ifndef SYSDOLPHIN_BASELIB_GOBJPLINK_H
#define SYSDOLPHIN_BASELIB_GOBJPLINK_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/gobj.h>

/**
 * @brief Frees a Game Object and cleans up its linked resources.
 * @param gobj The Game Object to free
 */
void HSD_GObjFree(HSD_GObj*);
/**
 * @brief Changes the priority of a Game Object within the Priority Link lists.
 * @param insert_type Insertion type (0: end of prio, 1: start of prio, 2: after pos, 3: before pos)
 * @param gobj The Game Object
 * @param p_link The priority link group
 * @param priority The specific priority inside the group
 * @param position Position GObj for relative insertion
 */
void HSD_GObjPLink_ChangeGObjPri_Unk(u32 insert_type, HSD_GObj* gobj, u8 p_link,
                                     u8 priority, HSD_GObj* position);

/**
 * @brief Reorders a Game Object immediately before another Game Object in the list.
 * @param gobj The Game Object to move
 * @param hiprio_gobj The higher priority Game Object to place it before
 */
void GObj_PReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj);

/**
 * @brief Creates a Game Object with specific priority link configuration.
 * @param insert_type Insertion type (0: end, 1: start, 2: after pos, 3: before pos)
 * @param classifier The GObj classification ID
 * @param p_link The priority link group
 * @param priority The specific priority inside the group
 * @param position Position GObj for relative insertion
 * @return Pointer to the allocated GObj
 */
HSD_GObj* CreateGObj(s32 where, u16 classifier, u8 p_link, u8 priority,
                     HSD_GObj* position);

#endif
