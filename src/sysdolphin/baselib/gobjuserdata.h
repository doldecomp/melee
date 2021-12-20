#ifndef _gobjuserdata_h_
#define _gobjuserdata_h_

#include <global.h>

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

#define HSD_GOBJ_USER_DATA_NONE (u8)-1

void GObj_InitUserData(HSD_GObj *gobj, u8 kind, void (*remove_func)(), void *data);
void GObj_RemoveUserData(HSD_GObj *gobj);

#endif
