#ifndef GALE01_2F0AE0
#define GALE01_2F0AE0

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2F0AE0 */ void it_802F0AE0(Item_GObj* gobj, Vec3* prev_pos, Vec3* pos,
                              ItemKind kind, s32 msid, f32 facing_dir,
                              f32 vel_x, f32 vel_y);
/* 2F0BC8 */ void it_2725_Logic85_EvtUnk(Item_GObj*, Item_GObj*);
/* 2F0BE8 */ void it_802F0BE8(Item_GObj*);
/* 2F0E70 */ bool itMasterhandbullet_UnkMotion1_Anim(Item_GObj*);
/* 2F0ED4 */ void itMasterhandbullet_UnkMotion1_Phys(Item_GObj*);
/* 2F0ED8 */ bool itMasterhandbullet_UnkMotion1_Coll(Item_GObj*);
/* 2F0F08 */ void it_802F0F08(Item_GObj*);
/* 2F0F0C */ bool it_2725_Logic83_DmgDealt(Item_GObj*);
/* 2F0F14 */ bool it_2725_Logic83_Reflected(Item_GObj*);
/* 2F0F34 */ bool it_2725_Logic83_Clanked(Item_GObj*);
/* 2F0F3C */ bool it_2725_Logic83_Absorbed(Item_GObj*);
/* 2F0F44 */ bool it_2725_Logic83_ShieldBounced(Item_GObj*);
/* 2F0F64 */ bool it_2725_Logic83_HitShield(Item_GObj*);
/* 3F9388 */ extern ItemStateTable it_803F9388[];

#endif
