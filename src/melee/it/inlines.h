#ifndef MELEE_IT_INLINES_H
#define MELEE_IT_INLINES_H

#include "it/types.h"

#include <baselib/gobj.h>

#define GET_ITEM(gobj) ((Item*) HSD_GObjGetUserData(gobj))

static inline Item* GetItemData(HSD_GObj* gobj)
{
    Item* item_data = gobj->user_data;
    return item_data;
}

static inline void itResetVelocity(Item* ip)
{
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0F;
}

/// @todo Rename; probably gets a specific joint for items
static inline HSD_JObj* itGetJObjGrandchild(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (!jobj) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    if (!child) {
        child = NULL;
    } else {
        child = child->child;
    }
    return child;
}

#endif
