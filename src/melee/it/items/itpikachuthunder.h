#ifndef GALE01_2B1DEC
#define GALE01_2B1DEC

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2B1DEC */ int it_802B1DEC(Item_GObj*);
/* 2B1DF8 */ Item_GObj* it_802B1DF8(Item_GObj*, Vec3*, Vec3*, s32, s32, s32);
/* 2B1FC8 */ s32 it_802B1FC8(Item_GObj*);
/* 2B1FE8 */ void it_802B1FE8(Item_GObj*, Vec3*);
/* 2B202C */ void it_2725_Logic39_Destroyed(Item_GObj*);
/* 2B2080 */ UNK_RET it_802B2080(UNK_PARAMS);
/* 2B20DC */ bool itPikachuthunder_UnkMotion0_Anim(Item_GObj* gobj);
/* 2B211C */ UNK_RET it_802B211C(UNK_PARAMS);
/* 2B21A8 */ bool itPikachuthunder_UnkMotion1_Anim(Item_GObj* gobj);
/* 2B21E0 */ bool itPikachuthunder_UnkMotion1_Coll(Item_GObj* gobj);
/* 2B22B8 */ s32 it_802B22B8(Item_GObj* gobj);
/* 2B2340 */ bool itPikachuthunder_UnkMotion2_Anim(Item_GObj* gobj);
/* 2B2508 */ bool it_2725_Logic39_DmgDealt(Item_GObj*);
/* 2B2510 */ bool it_2725_Logic39_HitShield(Item_GObj*);
/* 2B2518 */ bool it_2725_Logic39_Clanked(Item_GObj*);
/* 2B2520 */ bool it_2725_Logic39_Absorbed(Item_GObj*);
/* 2B2528 */ void it_2725_Logic39_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F70C8 */ extern ItemStateTable it_803F70C8[];
#endif
