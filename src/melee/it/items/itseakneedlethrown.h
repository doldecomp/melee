#ifndef GALE01_2AFD8C
#define GALE01_2AFD8C

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2AFD8C */ Item_GObj* it_802AFD8C(Item_GObj*, Vec3*, u32, float);
/* 2AFEA8 */ Item_GObj* it_802AFEA8(Item_GObj* gobj, Fighter_GObj* owner_gobj,
                                    u32);
/* 2AFEF8 */ void it_2725_Logic109_Destroyed(Item_GObj*);
/* 2AFF08 */ UNK_RET it_802AFF08(UNK_PARAMS);
/* 2B00F4 */ UNK_RET it_802B00F4(UNK_PARAMS);
/* 2B0210 */ bool itSeakneedlethrown_UnkMotion0_Anim(Item_GObj* gobj);
/* 2B024C */ bool itSeakneedlethrown_UnkMotion1_Anim(Item_GObj* gobj);
/* 2B033C */ bool itSeakneedlethrown_UnkMotion2_Anim(Item_GObj* gobj);
/* 2B0444 */ bool itSeakneedlethrown_UnkMotion3_Anim(Item_GObj* gobj);
/* 2B0464 */ bool itSeakneedlethrown_UnkMotion4_Anim(Item_GObj* gobj);
/* 2B0544 */ void itSeakneedlethrown_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B0548 */ void itSeakneedlethrown_UnkMotion1_Phys(Item_GObj* gobj);
/* 2B057C */ void itSeakneedlethrown_UnkMotion2_Phys(Item_GObj* gobj);
/* 2B0580 */ void itSeakneedlethrown_UnkMotion3_Phys(Item_GObj*);
/* 2B0598 */ void itSeakneedlethrown_UnkMotion4_Phys(Item_GObj* gobj);
/* 2B05CC */ bool itSeakneedlethrown_UnkMotion0_Coll(Item_GObj* gobj);
/* 2B0900 */ bool itSeakneedlethrown_UnkMotion1_Coll(Item_GObj* gobj);
/* 2B0AB8 */ bool itSeakneedlethrown_UnkMotion2_Coll(Item_GObj* gobj);
/* 2B0C5C */ bool itSeakneedlethrown_UnkMotion3_Coll(Item_GObj* gobj);
/* 2B0C64 */ bool itSeakneedlethrown_UnkMotion4_Coll(Item_GObj* gobj);
/* 2B0D84 */ bool it_2725_Logic109_DmgDealt(Item_GObj*);
/* 2B0F34 */ bool it_2725_Logic109_Clanked(Item_GObj*);
/* 2B10E4 */ bool it_2725_Logic109_DmgReceived(Item_GObj*);
/* 2B1294 */ bool it_2725_Logic109_Reflected(Item_GObj*);
/* 2B14DC */ bool it_2725_Logic109_ShieldBounced(Item_GObj*);
/* 2B16E4 */ bool it_2725_Logic109_HitShield(Item_GObj*);
/* 2B1890 */ void it_2725_Logic109_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F6F50 */ extern ItemStateTable it_803F6F50[];

#endif
