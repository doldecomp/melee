#ifndef GALE01_29B6F8
#define GALE01_29B6F8

#include <platform.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "it/items/types.h"

#include <dolphin/mtx.h>

void it_8029B6F8(Item_GObj*, Vec3*, ItemKind, f32);
void it_8029B7C0(Item_GObj*);
bool itMariofireball_UnkMotion0_Anim(Item_GObj*);
void itMariofireball_UnkMotion0_Phys(Item_GObj*);
bool itMariofireball_UnkMotion0_Coll(Item_GObj*);
bool it_2725_Logic87_DmgDealt(Item_GObj*);
bool it_2725_Logic87_Reflected(Item_GObj*);
bool it_2725_Logic87_Clanked(Item_GObj*);
bool it_2725_Logic87_HitShield(Item_GObj*);
bool it_2725_Logic87_Absorbed(Item_GObj*);
bool it_2725_Logic87_ShieldBounced(Item_GObj*);
void it_2725_Logic87_EvtUnk(Item_GObj*, Item_GObj*);
extern ItemStateTable it_803F6788[];

#endif
