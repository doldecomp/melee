#ifndef GALE01_2BD32C
#define GALE01_2BD32C

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2BD32C */ s32 it_802BD32C(Item_GObj*);
/* 2BD45C */ void it_802BD45C(Item_GObj* gobj);
/* 2BD47C */ void it_2725_Logic56_Destroyed(Item_GObj*);
/* 2BD4AC */ Item_GObj* it_802BD4AC(Item_GObj*, Vec3*, Fighter_Part, ItemKind,
                                    f32);
/* 2BD628 */ void it_2725_Logic56_PickedUp(Item_GObj*);
/* 2BD6D4 */ bool itPeachturnip_UnkMotion4_Anim(Item_GObj*);
/* 2BD6DC */ void itPeachturnip_UnkMotion4_Phys(Item_GObj*);
/* 2BD6E0 */ bool itPeachturnip_UnkMotion1_Anim(Item_GObj*);
/* 2BD718 */ void itPeachturnip_UnkMotion1_Phys(Item_GObj*);
/* 2BD748 */ void it_2725_Logic56_Thrown(Item_GObj*);
/* 2BD7E0 */ bool itPeachturnip_UnkMotion3_Anim(Item_GObj*);
/* 2BD818 */ void itPeachturnip_UnkMotion3_Phys(Item_GObj*);
/* 2BD864 */ bool itPeachturnip_UnkMotion3_Coll(Item_GObj*);
/* 2BD8CC */ void it_2725_Logic56_Dropped(Item_GObj*);
/* 2BD938 */ bool it_2725_Logic56_DmgDealt(Item_GObj*);
/* 2BD978 */ bool it_2725_Logic56_Clanked(Item_GObj*);
/* 2BD99C */ bool it_2725_Logic56_Reflected(Item_GObj*);
/* 2BD9C0 */ bool it_2725_Logic56_HitShield(Item_GObj*);
/* 2BD9E4 */ bool it_2725_Logic56_ShieldBounced(Item_GObj*);
/* 2BDA08 */ void it_2725_Logic56_EvtUnk(Item_GObj*, HSD_GObj*);
/* 3F74A8 */ extern ItemStateTable it_803F74A8[];

#endif
