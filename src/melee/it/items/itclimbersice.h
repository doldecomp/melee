#ifndef GALE01_2C1590
#define GALE01_2C1590

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C1590 */ Item_GObj* it_802C1590(Item_GObj*, Vec3*, enum_t,
                                    float facing_dir);
/* 2C16F8 */ void it_802C16F8(Item_GObj*);
/* 2C17DC */ void it_802C17DC(Item_GObj*);
/* 2C17FC */ void it_2725_Logic90_Destroyed(Item_GObj*);
/* 2C1854 */ UNK_RET it_802C1854(UNK_PARAMS);
/* 2C1950 */ void it_802C1950(Item_GObj*);
/* 2C198C */ bool itClimbersice_UnkMotion0_Anim(Item_GObj* gobj);
/* 2C1A14 */ void itClimbersice_UnkMotion0_Phys(Item_GObj* gobj);
/* 2C1A18 */ bool itClimbersice_UnkMotion0_Coll(Item_GObj* gobj);
/* 2C1A58 */ void it_802C1A58(Item_GObj* gobj);
/* 2C1A80 */ bool itClimbersice_UnkMotion1_Anim(Item_GObj* gobj);
/* 2C1A88 */ void itClimbersice_UnkMotion1_Phys(Item_GObj* gobj);
/* 2C1AB8 */ bool itClimbersice_UnkMotion1_Coll(Item_GObj* gobj);
/* 2C1AE4 */ UNK_RET it_802C1AE4(UNK_PARAMS);
/* 2C1B80 */ bool itClimbersice_UnkMotion2_Anim(Item_GObj* gobj);
/* 2C1BB4 */ void itClimbersice_UnkMotion2_Phys(Item_GObj* gobj);
/* 2C1C7C */ bool itClimbersice_UnkMotion2_Coll(Item_GObj* gobj);
/* 2C1D44 */ UNK_RET fn_802C1D44(UNK_PARAMS);
/* 2C1D80 */ bool itClimbersice_UnkMotion3_Anim(Item_GObj* gobj);
/* 2C1DB4 */ void itClimbersice_UnkMotion3_Phys(Item_GObj* gobj);
/* 2C1E94 */ bool itClimbersice_UnkMotion3_Coll(Item_GObj* gobj);
/* 2C1FC8 */ bool it_2725_Logic90_DmgDealt(Item_GObj*);
/* 2C1FD0 */ bool it_2725_Logic90_Reflected(Item_GObj*);
/* 2C1FF0 */ bool it_2725_Logic90_Clanked(Item_GObj*);
/* 2C1FF8 */ bool it_2725_Logic90_HitShield(Item_GObj*);
/* 2C20E4 */ bool it_2725_Logic90_Absorbed(Item_GObj*);
/* 2C20EC */ bool it_2725_Logic90_ShieldBounced(Item_GObj*);
/* 2C210C */ void it_2725_Logic90_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7668 */ extern ItemStateTable it_803F7668[];

#endif
