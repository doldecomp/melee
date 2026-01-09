#ifndef GALE01_291BE0
#define GALE01_291BE0

#include <platform.h>

#include "it/forward.h"

#include "it/itCommonItems.h"
#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 291BE0 */ HSD_GObj* it_80291BE0(Vec3*);
/* 291C98 */ void it_3F14_Logic21_Spawned(Item_GObj*);
/* 291CCC */ itSScopeAttributes* it_80291CCC(Item_GObj* gobj, Vec3* pos);
/* 291CF4 */ s32 it_80291CF4(Item_GObj*, s32);
/* 291D38 */ UNK_RET it_80291D38(UNK_PARAMS);
/* 291DAC */ int it_80291DAC(Item_GObj*, int);
/* 291F14 */ UNK_RET it_80291F14(UNK_PARAMS);
/* 291FA8 */ UNK_RET it_80291FA8(UNK_PARAMS);
/* 292030 */ void it_80292030(Item_GObj* gobj);
/* 292080 */ bool itSscope_UnkMotion0_Anim(Item_GObj* gobj);
/* 292088 */ void itSscope_UnkMotion0_Phys(Item_GObj* gobj);
/* 29208C */ bool itSscope_UnkMotion0_Coll(Item_GObj* gobj);
/* 2920B8 */ void it_802920B8(Item_GObj* gobj);
/* 2920E0 */ bool itSscope_UnkMotion3_Anim(Item_GObj* gobj);
/* 2920E8 */ void itSscope_UnkMotion1_Phys(Item_GObj* gobj);
/* 292118 */ bool itSscope_UnkMotion3_Coll(Item_GObj* gobj);
/* 29215C */ void it_3F14_Logic21_PickedUp(Item_GObj*);
/* 292184 */ bool itSscope_UnkMotion2_Anim(Item_GObj* gobj);
/* 29218C */ void itSscope_UnkMotion2_Phys(Item_GObj* gobj);
/* 292190 */ void it_3F14_Logic21_Dropped(Item_GObj*);
/* 2921B8 */ void it_3F14_Logic21_Thrown(Item_GObj*);
/* 2921E0 */ void itSscope_UnkMotion3_Phys(Item_GObj* gobj);
/* 29222C */ bool it_3F14_Logic21_DmgDealt(Item_GObj*);
/* 292250 */ bool it_3F14_Logic21_Clanked(Item_GObj*);
/* 292274 */ bool it_3F14_Logic21_HitShield(Item_GObj*);
/* 292298 */ bool it_3F14_Logic21_Reflected(Item_GObj*);
/* 2922B8 */ bool it_3F14_Logic21_ShieldBounced(Item_GObj*);
/* 2922D8 */ void it_3F14_Logic21_EnteredAir(Item_GObj*);
/* 292300 */ bool itSscope_UnkMotion4_Anim(Item_GObj* gobj);
/* 292308 */ void itSscope_UnkMotion4_Phys(Item_GObj* gobj);
/* 29230C */ bool itSscope_UnkMotion4_Coll(Item_GObj* gobj);
/* 292340 */ void it_3F14_Logic21_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F5F40 */ extern ItemStateTable it_803F5F40[];

#endif
