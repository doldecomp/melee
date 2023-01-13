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

static inline void ItUnkHoldKind(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);

    switch (it->hold_kind) {
    case 4:
    case 5:
    case 6:
    case 7: {
        int temp_r3 = func_8017E068();
        if (temp_r3 >= 0)
            it->xC3C = lbl_804D6D28->x80_float[temp_r3];
    }
    }
}

static inline void HSD_JObjSetScaleItem(Item* it, HSD_JObj* jobj, Vec3* scl)
{
    scl->x = scl->y = scl->z = it->x38_scale;
    HSD_JObjSetScale(jobj, scl);
}

#endif
/// @}
