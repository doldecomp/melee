#ifndef GALE01_2ADC04
#define GALE01_2ADC04

#include <platform.h>

#include "ft/types.h"

#include "it/forward.h"

#include "it/items/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 2ADC04 */ void itKirbyHammer_Logic8_Destroyed(Item_GObj* gobj);
/* 2ADC34 */ void it_802ADC34(Item_GObj* gobj);
/* 2ADC54 */ Item_GObj* it_802ADC54(HSD_GObj* parent, Vec3* pos,
                                    Fighter_Part sfx, u32 vars, float dir);
/* 2ADD88 */ void itKirbyHammer_Logic8_PickedUp(Item_GObj* gobj);
/* 2ADDB0 */ void it_802ADDB0(Item_GObj* gobj, HSD_GObj* ref_gobj);
/* 3F6C98 */ extern ItemStateTable it_803F6C98[];

#endif
