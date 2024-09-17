#ifndef GALE01_284D54
#define GALE01_284D54

#include <platform.h>

#include "it/forward.h"
#include "it/items/forward.h"
#include <baselib/forward.h>

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 284D54 */ Item_GObj* itSword_Spawn(Vec3* pos);
/* 284E10 */ void it_80284E10(HSD_GObj*, int);
/* 284FC4 */ void it_80284FC4(Item_GObj* gobj, int, float);
/* 285024 */ void it_80285024(Item_GObj* gobj, int);
/* 2852B8 */ void it_802852B8(Item_GObj* gobj, float*, float*);
/* 285300 */ itSword_UnkBytes* it_80285300(Item_GObj* gobj);
/* 285314 */ void it_80285314(Item_GObj* gobj);
/* 285338 */ void it_80285338(Item_GObj* gobj);
/* 285804 */ void it_80285804(Item_GObj* gobj);
/* 285B00 */ void it_80285B00(Item_GObj* gobj);
/* 285C78 */ void it_80285C78(Item_GObj* gobj);
/* 285DF0 */ void it_80285DF0(Item_GObj* gobj);
/* 285FAC */ bool it_80285FAC(Item_GObj* gobj);
/* 285FE0 */ bool it_80285FE0(Item_GObj* gobj);
/* 286000 */ bool it_80286000(Item_GObj* gobj);
/* 286024 */ bool it_80286024(Item_GObj* gobj);
/* 286048 */ bool itSword_BounceOffShield(Item_GObj* gobj);
/* 286068 */ void it_80286068(Item_GObj* gobj, HSD_GObj* ref_gobj);
/* 3F5800 */ extern ItemStateTable it_803F5800[];

#endif
