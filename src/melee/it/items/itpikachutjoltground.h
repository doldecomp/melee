#ifndef GALE01_2B3368
#define GALE01_2B3368

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2B3368 */ void* it_802B3368(Item_GObj* gobj);
/* 2B338C */ void it_802B338C(Item_GObj*, Vec3*, float facing_dir, u32);
/* 2B34E4 */ void it_2725_Logic106_Destroyed(Item_GObj*);
/* 2B3544 */ void it_802B3544(Item_GObj* gobj);
/* 2B3554 */ UNK_RET it_802B3554(UNK_PARAMS);
/* 2B3680 */ bool itPikachutjoltground_UnkMotion0_Anim(Item_GObj* gobj);
/* 2B36BC */ bool itPikachutjoltground_UnkMotion1_Anim(Item_GObj* gobj);
/* 2B3790 */ void itPikachutjoltground_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B3808 */ bool itPikachutjoltground_UnkMotion0_Coll(Item_GObj* gobj);
/* 2B397C */ bool itPikachutjoltground_UnkMotion1_Coll(Item_GObj* gobj);
/* 2B3A94 */ bool it_2725_Logic106_DmgDealt(Item_GObj*);
/* 2B3AF8 */ bool it_2725_Logic106_Reflected(Item_GObj*);
/* 2B3C44 */ bool it_2725_Logic106_Clanked(Item_GObj*);
/* 2B3CA8 */ bool it_2725_Logic106_Absorbed(Item_GObj*);
/* 2B3D0C */ bool it_2725_Logic106_HitShield(Item_GObj*);
/* 2B3D70 */ bool it_2725_Logic106_ShieldBounced(Item_GObj*);
/* 2B3EDC */ void it_2725_Logic106_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7190 */ extern ItemStateTable it_803F7190[];

#endif
