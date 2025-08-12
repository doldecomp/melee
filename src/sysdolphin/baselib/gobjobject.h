#ifndef SYSDOLPHIN_BASELIB_GOBJOBJECT_H
#define SYSDOLPHIN_BASELIB_GOBJOBJECT_H

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h" // IWYU pragma: export

UNK_T HSD_GObjObject_80390ADC(HSD_GObj* gobj);
void HSD_GObjObject_80390A70(HSD_GObj* gobj, u8 kind, void* obj);
void HSD_GObjObject_80390B0C(HSD_GObj* gobj);
HSD_GObj* HSD_GObjObject_80390A3C(u16 id, u8 arg1);

#endif
