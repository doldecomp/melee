/// @addtogroup melee_it_item item
/// @{
#ifndef MELEE_IT_INLINES_H
#define MELEE_IT_INLINES_H

#include <melee/it/code_80266F3C.h>
#include <melee/it/item.h>
#include <melee/it/types.h>
#include <Runtime/platform.h>

static inline Item* GetItemData(HSD_GObj* item_gobj)
{
    Item* item_data = item_gobj->user_data;
    return item_data;
}

static inline void HSD_JObjSetFacingDirItem(HSD_JObj* jobj, Item* it)
{
    if (it->xDC8_word.flags.x19 == true)
        HSD_JObjSetRotationY(jobj, M_PI / 2 * it->facing_dir);
}

#endif
/// @}
