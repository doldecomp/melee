#ifndef GALE01_2B5518
#define GALE01_2B5518

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2B5518 */ bool it_802B5518(Item_GObj*, CollData*);
/* 2B55C8 */ HSD_GObj* it_802B55C8(Item_GObj* owner, Vec3*, s32, s32,
                                   float facing_dir);
/* 2B56E4 */ void it_802B56E4(Item_GObj*, Vec3*, float, float, float);
/* 2B58D8 */ void it_2725_Logic108_Destroyed(Item_GObj*);
/* 2B5974 */ void it_802B5974(Item_GObj*);
/* 2B59C4 */ void it_2725_Logic108_PickedUp(Item_GObj*);
/* 2B5A98 */ bool itSamuschargeshot_UnkMotion0_Anim(Item_GObj* gobj);
/* 2B5CB0 */ void itSamuschargeshot_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B5CB4 */ bool itSamuschargeshot_UnkMotion0_Coll(Item_GObj* gobj);
/* 2B5CBC */ UNK_RET it_802B5CBC(UNK_PARAMS);
/* 2B5D54 */ bool itSamuschargeshot_UnkMotion8_Anim(Item_GObj* gobj);
/* 2B5E50 */ void itSamuschargeshot_UnkMotion8_Phys(Item_GObj* gobj);
/* 2B5EA0 */ bool itSamuschargeshot_UnkMotion8_Coll(Item_GObj* gobj);
/* 2B5EDC */ UNK_RET it_802B5EDC(UNK_PARAMS);
/* 2B5FD8 */ bool it_2725_Logic108_DmgDealt(Item_GObj*);
/* 2B5FE0 */ bool it_2725_Logic108_Clanked(Item_GObj*);
/* 2B5FE8 */ bool it_2725_Logic108_Absorbed(Item_GObj*);
/* 2B5FF0 */ bool it_2725_Logic108_Reflected(Item_GObj*);
/* 2B613C */ bool it_2725_Logic108_HitShield(Item_GObj*);
/* 2B6144 */ bool it_2725_Logic108_ShieldBounced(Item_GObj*);
/* 2B62B0 */ void it_2725_Logic108_EvtUnk(Item_GObj*, Item_GObj*);
/* 2B62D0 */ void it_802B62D0(Item_GObj*, Vec3* pos, bool, float facing_dir);
/* 3F7288 */ extern ItemStateTable it_803F7288[];

#endif
