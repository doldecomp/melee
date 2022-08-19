#include <sysdolphin/baselib/gobjuserdata.h>

extern char lbl_804085D0[];

void GObj_InitUserData(HSD_GObj *gobj, u8 kind, void (*remove_func)(), void *data)
{
    if (gobj->user_data_kind != HSD_GOBJ_USER_DATA_NONE) {
        __assert(__FILE__, 40, "gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE");
    }
    gobj->user_data_kind = kind;
    gobj->user_data = data;
    gobj->user_data_remove_func = remove_func;
}

void GObj_RemoveUserData(HSD_GObj *gobj)
{
    if (gobj->user_data_kind == HSD_GOBJ_USER_DATA_NONE)
        return;
    
    if (gobj->user_data_remove_func == NULL) {
        __assert(__FILE__, 99, "gobj->user_data_remove_func");
    }
    (*gobj->user_data_remove_func)(gobj->user_data);
    gobj->user_data_kind = HSD_GOBJ_USER_DATA_NONE;
    gobj->user_data = NULL;
}
