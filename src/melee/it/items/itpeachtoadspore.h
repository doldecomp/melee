#ifndef GALE01_2BE214
#define GALE01_2BE214

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2BE214 */ Item_GObj* it_802BE214(Item_GObj* gobj, Vec3* pos, ItemKind kind,
                                    f32 facing_dir);
/* 2BE2E8 */ UNK_RET it_802BE2E8(Item_GObj*, Item_GObj*);
/* 2BE408 */ bool itPeachtoadspore_UnkMotion0_Anim(Item_GObj*);
/* 2BE458 */ void itPeachtoadspore_UnkMotion0_Phys(Item_GObj*);
/* 2BE488 */ bool it_2725_Logic92_DmgDealt(Item_GObj*);
/* 2BE4AC */ bool it_2725_Logic68_Clanked(Item_GObj*);
/* 2BE4D0 */ bool it_2725_Logic68_HitShield(Item_GObj*);
/* 2BE4F4 */ bool it_2725_Logic68_Absorbed(Item_GObj*);
/* 2BE518 */ bool it_2725_Logic68_ShieldBounced(Item_GObj*);
/* 2BE538 */ bool it_2725_Logic68_Reflected(Item_GObj*);
/* 2BE578 */ void it_2725_Logic92_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7548 */ extern ItemStateTable it_803F7548[];

#endif
