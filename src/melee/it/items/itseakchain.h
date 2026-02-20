#ifndef GALE01_2BAEEC
#define GALE01_2BAEEC

#include "it/forward.h"

#include "it/itCharItems.h"
#include "it/items/types.h"

/* 2BAEEC */ void it_802BAEEC(Item_GObj*);
/* 2BAEEC */ void it_802BAEEC(Item_GObj* gobj);
/* 2BAF0C */ void it_802BAF0C(Item_GObj*);
/* 2BAF0C */ void it_802BAF0C(Item_GObj* gobj);
/* 2BAF2C */ int it_802BAF2C(Item* ip, HSD_JObj* jobj);
/* 2BB20C */ void it_802BB20C(Item_GObj*);
/* 2BB290 */ Item_GObj* itSeakChain_Spawn(Fighter_GObj* owner_gobj, Vec3* arg1,
                                          float facing_dir);
/* 2BB428 */ void fn_802BB428(Item_GObj* gobj);
/* 2BB44C */ void fn_802BB44C(Item_GObj* gobj);
/* 2BB574 */ void fn_802BB574(Item_GObj* gobj);
/* 2BB694 */ void fn_802BB694(Item_GObj* gobj);
/* 2BB784 */ void fn_802BB784(Item_GObj* gobj);
/* 2BB880 */ bool itSeakchain_UnkMotion4_Anim(Item_GObj*);
/* 2BB938 */ int it_802BB938(ItemLink* link, int arg1, f32 arg2);
/* 2BBAEC */ s32 it_802BBAEC(ItemLink* link, s32 arg1, f32 arg2);
/* 2BBB0C */ int it_802BBB0C(ItemLink* link, Vec3* offset, Mtx mtx,
                             float scale);
/* 2BBC38 */ int it_802BBC38(ItemLink*, Vec3*, Mtx, float);
/* 2BBD64 */ enum_t it_802BBD64(ItemLink*, Vec3*, Mtx);
/* 2BBED0 */ enum_t it_802BBED0(ItemLink*, Vec3*, Mtx);
/* 2BC94C */ bool it_802BC94C(ItemLink*, Vec3*, Mtx, float);
/* 2BCA30 */ void it_802BCA30(Item* ip);
/* 2BCE94 */ void it_2725_Logic54_PickedUp(Item_GObj* gobj);
/* 2BCED4 */ void it_802BCED4(Item_GObj* gobj);
/* 2BCF2C */ void it_802BCF2C(Item_GObj* gobj);
/* 2BCF84 */ void it_802BCF84(Item_GObj* gobj);
/* 2BCFC4 */ void it_802BCFC4(Item_GObj* gobj, Vec3* vel);
/* 2BD10C */ void itSeakChain_Logic54_EvtUnk(Item_GObj*, Item_GObj*);
/* 2BDBF8 */ void it_802BDBF8(Item_GObj* gobj);
/* 3F7438 */ extern ItemStateTable it_803F7438[];

#endif
