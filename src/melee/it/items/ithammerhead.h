#ifndef GALE01_299C48
#define GALE01_299C48

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 299C48 */ void it_80299C48(HSD_GObj*, Vec3*, Vec3*, f32);
/* 299D4C */ void it_3F14_Logic40_Spawned(Item_GObj*);
/* 299D7C */ UNK_RET it_80299D7C(UNK_PARAMS);
/* 299DD0 */ void it_3F14_Logic40_PickedUp(Item_GObj*);
/* 299E1C */ bool itHammerhead_UnkMotion1_Anim(Item_GObj* gobj);
/* 299E24 */ void itHammerhead_UnkMotion1_Phys(Item_GObj* gobj);
/* 299E28 */ void it_3F14_Logic40_Dropped(Item_GObj* gobj);
/* 299E48 */ void it_3F14_Logic40_Thrown(Item_GObj*);
/* 299E9C */ bool itHammerhead_UnkMotion2_Anim(Item_GObj* gobj);
/* 299F1C */ void itHammerhead_UnkMotion2_Phys(Item_GObj* gobj);
/* 299F68 */ bool itHammerhead_UnkMotion2_Coll(Item_GObj* gobj);
/* 299F94 */ void it_80299F94(void);
/* 299FB4 */ UNK_RET it_80299FB4(UNK_PARAMS);
/* 29A000 */ bool itHammerhead_UnkMotion3_Anim(Item_GObj* gobj);
/* 29A080 */ void itHammerhead_UnkMotion3_Phys(Item_GObj* gobj);
/* 29A084 */ bool itHammerhead_UnkMotion3_Coll(Item_GObj* gobj);
/* 29A0B0 */ bool it_3F14_Logic40_DmgDealt(Item_GObj*);
/* 29A0B8 */ bool it_3F14_Logic40_Clanked(Item_GObj*);
/* 29A0C0 */ bool it_3F14_Logic40_HitShield(Item_GObj*);
/* 29A0C8 */ bool it_3F14_Logic40_Reflected(Item_GObj*);
/* 29A0EC */ bool it_3F14_Logic40_DmgReceived(Item_GObj*);
/* 29A0F4 */ void it_3F14_Logic40_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F6640 */ extern ItemStateTable it_803F6640[];

#endif
