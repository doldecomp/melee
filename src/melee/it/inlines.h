#ifndef MELEE_IT_INLINES_H
#define MELEE_IT_INLINES_H

#include <melee/it/types.h>
#include <Runtime/platform.h>

static inline Item* GetItemData(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data;
}

static inline Item* GetItemDirect(HSD_GObj* item_gobj)
{
    return item_gobj->user_data;
}

#endif
