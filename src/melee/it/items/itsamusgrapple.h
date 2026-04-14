#ifndef GALE01_2B7150
#define GALE01_2B7150

#include "ft/forward.h"
#include "it/forward.h"

#include "it/itCharItems.h"
#include "it/items/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 2A77DC */ void it_802A77DC(Item_GObj* gobj);
/* 2B7150 */ void itSamusGrapple_Logic53_Spawned(Item_GObj*);
/* 2B7160 */ void it_802B7160(Fighter_GObj*, void*);
/* 2B743C */ void it_802B743C(HSD_GObj*, Item*, s32);
/* 2B75FC */ HSD_JObj* it_802B75FC(Item*, HSD_JObj*, s32, f32);
/* 2B7B84 */ void it_802B7B84(Item_GObj* gobj);
/* 2B7C18 */ Item_GObj* it_802B7C18(Fighter_GObj*, Vec3*, float facing_dir);
/* 2B7E34 */ void fn_802B7E34(Item_GObj*);
/* 2B8048 */ void itSamusgrapple_UnkMotion0_Phys(Item_GObj* gobj);
/* 2B805C */ void fn_802B805C(Item_GObj*);
/* 2B8370 */ void itSamusgrapple_UnkMotion1_Phys(Item_GObj* gobj);
/* 2B8384 */ void fn_802B8384(Item_GObj*);
/* 2B8510 */ void itSamusgrapple_UnkMotion2_Phys(Item_GObj* gobj);
/* 2B8524 */ void fn_802B8524(Item_GObj*);
/* 2B8670 */ void itSamusgrapple_UnkMotion3_Phys(Item_GObj* gobj);
/* 2B8684 */ void fn_802B8684(Item_GObj*);
/* 2B8800 */ void itSamusgrapple_UnkMotion4_Phys(Item_GObj* gobj);
/* 2B8814 */ void fn_802B8814(Item_GObj*);
/* 2B8948 */ void itSamusgrapple_UnkMotion5_Phys(Item_GObj* gobj);
/* 2B895C */ void fn_802B895C(Item_GObj*);
/* 2B8B40 */ void itSamusgrapple_UnkMotion6_Phys(Item_GObj* gobj);
/* 2B8B54 */ void fn_802B8B54(Item_GObj*);
/* 2B8D24 */ void itSamusgrapple_UnkMotion7_Phys(Item_GObj* gobj);
/* 2B8D38 */ void fn_802B8D38(Item_GObj*);
/* 2B8FF8 */ void itSamusgrapple_UnkMotion8_Phys(Item_GObj* gobj);
/* 2B900C */ void it_802B900C(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              f32);
/* 2B91C4 */ void it_802B91C4(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              f32);
/* 2B9328 */ s32 it_802B9328(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                             Fighter*);
/* 2B99A0 */ s32 it_802B99A0(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                             Fighter*);
/* 2B9CE8 */ void it_802B9CE8(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              Fighter*);
/* 2B9FD4 */ bool it_802B9FD4(ItemLink*, Vec3*, itSamusGrappleAttributes*);
/* 2BA194 */ bool it_802BA194(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              f32);
/* 2BA2D8 */ bool it_802BA2D8(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              f32);
/* 2BA3BC */ bool it_802BA3BC(ItemLink*, ItemLink*, Vec3*,
                              itSamusGrappleAttributes*, f32);
/* 2BA5DC */ void it_802BA5DC(ItemLink*, ItemLink*, Vec3*,
                              itSamusGrappleAttributes*);
/* 2BA760 */ bool it_802BA760(ItemLink*, Vec3*, itSamusGrappleAttributes*,
                              Fighter*);
/* 2BA97C */ void itSamusGrapple_Logic53_PickedUp(Item_GObj*);
/* 2BA9B8 */ void it_802BA9B8(Item_GObj* gobj);
/* 2BAA08 */ void it_802BAA08(Item_GObj* gobj);
/* 2BAA58 */ void it_802BAA58(Item_GObj* gobj);
/* 2BAA94 */ void it_802BAA94(Item_GObj* gobj);
/* 2BAAE4 */ void it_802BAAE4(Item_GObj* gobj, Vec3* vel);
/* 2BAB40 */ void it_802BAB40(Item_GObj*);
/* 2BAB7C */ void it_802BAB7C(Item_GObj*);
/* 2BABB8 */ void it_802BABB8(Item_GObj* gobj);
/* 2BAC3C */ void it_802BAC3C(Fighter_GObj* gobj);
/* 2BAC80 */ void it_802BAC80(Fighter_GObj* gobj);
/* 2BACC4 */ void it_802BACC4(Fighter_GObj* gobj);
/* 2BAEA0 */ void itSamusGrapple_Logic53_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F73A8 */ extern ItemStateTable it_803F73A8[];

#endif
