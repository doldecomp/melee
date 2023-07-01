#ifndef MELEE_IT_ITPEACHPARASOL_H
#define MELEE_IT_ITPEACHPARASOL_H

#include <melee/it/forward.h>
#include <dolphin/mtx/forward.h>
#include <sysdolphin/baselib/forward.h>

extern ItemStateTable it_803F74F8[];

int it_802BDA40(Item_GObj*, int);
Item_GObj* it_802BDA64(HSD_GObj* parent, Vec3* pos, u8 arg2, f32 dir);
void it_802BDB4C(Item_GObj*);
void it_802BDB94(Item_GObj*);
void it_802BDBF8(Item_GObj*);
void it_802BDC18(Item_GObj*);
bool it_802BDC38(Item_GObj*);
void it_802BDC74(Item_GObj*);
bool it_802BDCC0(Item_GObj*);
void it_802BDD3C(Item_GObj*);
void it_802BDD40(Item_GObj*, f32 arg8);
void it_802BDDB4(Item_GObj*, f32 arg8);
void it_802BDDF8(Item_GObj*, HSD_GObj*);

#endif
