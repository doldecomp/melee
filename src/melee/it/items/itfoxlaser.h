#ifndef GALE01_29C4D4
#define GALE01_29C4D4

#include <platform.h>
#include "it/forward.h"
#include <baselib/forward.h>

#include "it/types.h"

#include <dolphin/mtx/types.h>
#include <baselib/jobj.h>

extern ItemStateTable it_803F67D0[];

bool it_8029C4D4(Item_GObj*);
void it_8029C504(HSD_GObj* parent, Vec3* pos, enum_t msid, int kind, f32 angle,
                 f32 arg9);
void it_8029C6A4(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind);
void it_8029C6CC(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind);
bool it_8029C6F4(Item_GObj*);
void it_8029C9CC(Item_GObj*);
bool it_8029C9EC(Item_GObj*);
bool it_8029CA78(Item_GObj*);
bool it_8029CA80(Item_GObj*);
bool it_8029CC4C(Item_GObj*);
bool it_8029CC54(Item_GObj*);
bool it_8029CCF0(Item_GObj*);
void it_8029CCF8(Item_GObj*, HSD_GObj* ref);

#endif
