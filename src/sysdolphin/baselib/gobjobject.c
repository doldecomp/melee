#include <sysdolphin/baselib/gobj.h>

extern void (**lbl_804D7810)(void*);

HSD_GObj* func_80390A3C(u16 id, u8 arg1)
{
    HSD_GObj* cur;
    for (cur = ((HSD_GObj**)lbl_804D782C)[arg1]; cur != NULL; cur = cur->next) {
        if (cur->classifier == id) {
            break;
        }
    }
    return cur;
}

void func_80390A70(HSD_GObj* gobj, u8 kind, unk_t obj)
{
    assert_line(42, gobj->obj_kind == HSD_GOBJ_OBJ_NONE);
    gobj->obj_kind = kind;
    gobj->hsd_obj = obj;
}

unk_t func_80390ADC(HSD_GObj* gobj)
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

void func_80390B0C(HSD_GObj* gobj)
{
    if (gobj->obj_kind != HSD_GOBJ_OBJ_NONE) {
        lbl_804D7810[gobj->obj_kind](gobj->hsd_obj);
        gobj->obj_kind = HSD_GOBJ_OBJ_NONE;
        gobj->hsd_obj = NULL;
    }
}
