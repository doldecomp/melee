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

#endif
