#ifndef GALE01_29C4D4
#define GALE01_29C4D4

#include <platform.h>

#include "it/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 29C4D4 */ bool it_8029C4D4(Item_GObj*, CollData*);
/* 29C504 */ void it_8029C504(HSD_GObj* parent, Vec3* pos, enum_t msid,
                              int kind, f32 angle, f32 speed);
/* 29C6A4 */ void it_8029C6A4(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec,
                              int kind);
/* 29C6CC */ void it_8029C6CC(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec,
                              int kind);
/* 29C6F4 */ bool it_8029C6F4(Item_GObj*);
/* 29C9CC */ void it_8029C9CC(Item_GObj*);
/* 29C9EC */ bool it_8029C9EC(Item_GObj*);
/* 29CA78 */ bool it_8029CA78(Item_GObj*);
/* 29CA80 */ bool it_8029CA80(Item_GObj*);
/* 29CC4C */ bool it_8029CC4C(Item_GObj*);
/* 29CC54 */ bool it_8029CC54(Item_GObj*);
/* 29CCF0 */ bool it_8029CCF0(Item_GObj*);
/* 29CCF8 */ void it_8029CCF8(Item_GObj*, HSD_GObj*);
/* 3F67D0 */ extern ItemStateTable it_803F67D0[];

#endif
