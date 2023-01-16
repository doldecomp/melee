#include <sysdolphin/baselib/gobjuserdata.h>

void GObj_InitUserData(HSD_GObj* gobj, u8 kind,
                       void (*remove_func)(any_t user_data), void* data)
{
    HSD_ASSERT(40, gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE);
    gobj->user_data_kind = kind;
    gobj->user_data = data;
    gobj->user_data_remove_func = remove_func;
}

void GObj_RemoveUserData(HSD_GObj* gobj)
{
    if (gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE)
        return;

    HSD_ASSERT(99, gobj->user_data_remove_func);
    gobj->user_data_remove_func(gobj->user_data);
    gobj->user_data_kind = HSD_GOBJ_USER_DATA_NONE;
    gobj->user_data = NULL;
}
