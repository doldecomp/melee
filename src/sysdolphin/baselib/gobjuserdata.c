#include <sysdolphin/baselib/gobjuserdata.h>

void GObj_InitUserData(HSD_GObj* gobj, u8 kind, void (*remove_func)(),
                       void* data)
{
    assert_line(40, gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE);
    gobj->user_data_kind = kind;
    gobj->user_data = data;
    gobj->user_data_remove_func = remove_func;
}

void GObj_RemoveUserData(HSD_GObj* gobj)
{
    if (gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE)
        return;

    assert_line(99, gobj->user_data_remove_func);
    gobj->user_data_remove_func(gobj->user_data);
    gobj->user_data_kind = HSD_GOBJ_USER_DATA_NONE;
    gobj->user_data = NULL;
}
