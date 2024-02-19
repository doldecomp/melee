#ifndef GALE01_2ADC04
#define GALE01_2ADC04

#include <platform.h>

#include "it/types.h"

void it_802ADC04(Item_GObj* gobj);
void it_802ADC34(Item_GObj* gobj);
Item_GObj* it_802ADC54(HSD_GObj* parent, Vec3* pos, u8 sfx, u32 vars, f32 dir);
void it_802ADD88(Item_GObj* gobj);
void it_802ADDB0(Item_GObj* gobj, HSD_GObj* ref_gobj);
extern ItemStateTable it_803F6C98[];

#endif
