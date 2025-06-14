#include "gobjobject.h"

#include "debug.h"
#include "gobj.h"

HSD_GObj* HSD_GObjObject_80390A3C(u16 id, u8 arg1)
{
    HSD_GObj* cur;
    for (cur = ((HSD_GObj**) HSD_GObj_Entities)[arg1]; cur != NULL;
         cur = cur->next)
    {
        if (cur->classifier == id) {
            break;
        }
    }
    return cur;
}

void HSD_GObjObject_80390A70(HSD_GObj* gobj, u8 kind, void* obj)
{
    HSD_ASSERT(42, gobj->obj_kind == HSD_GOBJ_OBJ_NONE);
    gobj->obj_kind = kind;
    gobj->hsd_obj = obj;
}

UNK_T HSD_GObjObject_80390ADC(HSD_GObj* gobj)
{
    void* obj;
    if (gobj->obj_kind != HSD_GOBJ_OBJ_NONE) {
        gobj->obj_kind = HSD_GOBJ_OBJ_NONE;
        obj = gobj->hsd_obj;
        gobj->hsd_obj = NULL;
    } else {
        obj = NULL;
    }
    return obj;
}

void HSD_GObjObject_80390B0C(HSD_GObj* gobj)
{
    if (gobj->obj_kind != HSD_GOBJ_OBJ_NONE) {
        HSD_GObj_804D7810[gobj->obj_kind](gobj->hsd_obj);
        gobj->obj_kind = HSD_GOBJ_OBJ_NONE;
        gobj->hsd_obj = NULL;
    }
}
