#ifndef MELEE_IT_ITSEAKVANISH_H
#define MELEE_IT_ITSEAKVANISH_H

#include <melee/it/forward.h>
#include <dolphin/mtx/forward.h>
#include <sysdolphin/baselib/forward.h>

extern ItemStateTable it_803F70B8[];

Item_GObj* it_802B1C60(HSD_GObj* parent, Vec3* pos, f32 dir);
bool it_802B1D38(Item_GObj*);
void it_802B1D40(Item_GObj*, HSD_GObj*);
bool it_802B1DAC(Item_GObj*);
void it_802B1DCC(Item_GObj*, HSD_GObj*);

#endif
