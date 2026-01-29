#ifndef GALE01_2C61F4
#define GALE01_2C61F4

#include "it/forward.h"

#include "it/items/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 2C61F4 */ HSD_GObj* itGamewatchGreenhouse_Spawn(HSD_GObj*, Vec3*,
                                                   Fighter_Part, float);
/* 2C62F8 */ void itGamewatchGreenhouse_Destroyed(Item_GObj*);
/* 2C6328 */ void itGamewatchGreenhouse_802C6328(Item_GObj*);
/* 2C6374 */ void itGamewatchGreenhouse_802C6374(Item_GObj*);
/* 2C6394 */ void itGamewatchGreenhouse_802C6394(Item_GObj*);
/* 2C63B4 */ void itGamewatchGreenhouse_PickedUp(Item_GObj*);
/* 2C6430 */ void itGamewatchGreenhouse_802C6430(Item_GObj*);
/* 2C6458 */ void itGamewatchGreenhouse_802C6458(Item_GObj*);
/* 2C6480 */ void itGamewatchGreenhouse_802C6480(Item_GObj*);
/* 2C64A8 */ void itGamewatchGreenhouse_802C64A8(Item_GObj*);
/* 2C64D0 */ bool itGamewatchGreenhouse_Motion3_Anim(Item_GObj*);
/* 2C653C */ bool itGamewatchGreenhouse_Motion2_Anim(Item_GObj* item_gobj);
/* 2C65C4 */ void itGamewatchGreenhouse_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7898 */ extern ItemStateTable it_803F7898[];

#endif
