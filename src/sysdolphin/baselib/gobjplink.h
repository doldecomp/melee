#ifndef SYSDOLPHIN_BASELIB_GOBJPLINK_H
#define SYSDOLPHIN_BASELIB_GOBJPLINK_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/gobj.h>

void HSD_GObjFree(HSD_GObj*);
void HSD_GObjPLink_ChangeGObjPri_Unk(u32 arg0, HSD_GObj* gobj, u8 p_link,
                                     u8 priority, HSD_GObj* position);

void GObj_PReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj);

HSD_GObj* CreateGObj(s32 where, u16 classifier, u8 p_link, u8 priority,
                     HSD_GObj* position);

#endif
