#ifndef _grtgamewatch_h_
#define _grtgamewatch_h_

#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

void grTGameWatch_80224110(bool);
void grTGameWatch_80224114(void);
void grTGameWatch_80224184(void);
void grTGameWatch_80224188(void);
bool grTGameWatch_802241AC(void);
HSD_GObj* grTGameWatch_802241B4(int);
void grTGameWatch_8022429C(HSD_GObj*);
bool grTGameWatch_802242C8(HSD_GObj*);
void grTGameWatch_802242D0(HSD_GObj*);
void grTGameWatch_802242D4(HSD_GObj*);
void grTGameWatch_802242D8(HSD_GObj*);
bool grTGameWatch_80224328(HSD_GObj*);
void grTGameWatch_80224330(HSD_GObj*);
void grTGameWatch_80224364(HSD_GObj*);
void grTGameWatch_80224368(HSD_GObj*);
bool grTGameWatch_802243B8(HSD_GObj*);
void grTGameWatch_802243C0(HSD_GObj*);
void grTGameWatch_802243E0(HSD_GObj*);
DynamicsDesc* grTGameWatch_802243E4(int);
bool grTGameWatch_802243EC(Vec3*, int, HSD_JObj*);

#endif
