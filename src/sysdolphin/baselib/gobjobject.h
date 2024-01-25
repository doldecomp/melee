#ifndef SYSDOLPHIN_BASELIB_GOBJOBJECT_H
#define SYSDOLPHIN_BASELIB_GOBJOBJECT_H

#include <platform.h>
#include <baselib/forward.h>

#include <baselib/gobj.h>
#include <baselib/jobj.h>

unk_t HSD_GObjObjet_80390ADC(HSD_GObj* gobj);
void HSD_GObjObjet_80390A70(HSD_GObj* gobj, u8 kind, void* obj);
void HSD_GObjObjet_80390B0C(HSD_GObj* gobj);
HSD_GObj* HSD_GObjObjet_80390A3C(u16 id, u8 arg1);

#endif
