#ifndef GALE01_2C8038
#define GALE01_2C8038

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C8038 */ Item_GObj* it_802C8038(Item_GObj*, Vec3*, s32, s32, float, float);
/* 2C8158 */ void it_802C8158(Item_GObj* item_gobj);
/* 2C81C8 */ void it_802C81C8(Item_GObj* item_gobj);
/* 2C81E8 */ void it_802C81E8(Item_GObj* item_gobj);
/* 2C8208 */ void it_802C8208(HSD_GObj* hsd_gobj, enum_t msid);
/* 2C8240 */ bool itGamewatchrescue_UnkMotion1_Anim(Item_GObj* gobj);
/* 2C8350 */ void itGamewatchrescue_UnkMotion1_Phys(Item_GObj* gobj);
/* 2C8354 */ bool itGamewatchrescue_UnkMotion1_Coll(Item_GObj* gobj);
/* 2C835C */ void itGameWatchRescue_Logic81_EvtUnk(Item_GObj* item_gobj1,
                                                   Item_GObj* item_gobj2);
/* 3F79C0 */ extern ItemStateTable it_803F79C0[];

#endif
