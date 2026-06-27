#ifndef GALE01_2BE598
#define GALE01_2BE598

#include "it/forward.h"

#include "it/itCharItems.h"
#include "it/items/types.h"
#include "it/itYoyo.h"

#include <dolphin/mtx.h>

/* 2BE598 */ void it_802BE598(Item_GObj*);
/* 2BE5B8 */ void it_802BE5B8(Item_GObj*);
/* 2BE5D8 */ void it_802BE5D8(void*, float);
/* 2BE65C */ HSD_GObj* it_802BE65C(Item* ip, HSD_JObj* bone_jobj);
/* 2BE958 */ void it_802BE958(Item_GObj*);
/* 2BE9D8 */ HSD_GObj* it_802BE9D8(HSD_GObj*, f32, Vec3*, s32);
/* 2BEB38 */ void itNessyoyo_UnkMotion0_Phys(Item_GObj* gobj);
/* 2BEB5C */ void itNessyoyo_UnkMotion1_Phys(Item_GObj* gobj);
/* 2BEC58 */ void itNessyoyo_UnkMotion2_Phys(Item_GObj* gobj);
/* 2BED54 */ void itNessyoyo_UnkMotion3_Phys(Item_GObj* gobj);
/* 2BEE88 */ bool itNessyoyo_UnkMotion3_Anim(Item_GObj* gobj);
/* 2BF030 */ s32 it_802BF030(ItemLink*, s32, f32);
/* 2BF180 */ void it_802BF180(ItemLink*, Vec3*, itYoyoAttributes*, f32);
/* 2BF28C */ s32 it_802BF28C(ItemLink*, Vec3*, itYoyoAttributes*, Item*);
/* 2BF4A0 */ s32 it_802BF4A0(ItemLink*, Vec3*, itYoyoAttributes*, Item*);
/* 2BF800 */ bool it_802BF800(ItemLink*, Vec3*, itYoyoAttributes*, Item*, f32);
/* 2BF900 */ void it_802BF900(Item* item);
/* 2BFAFC */ void it_802BFAFC(Item*, Vec3*);
/* 2BFE34 */ void itNessYoyo_Logic59_PickedUp(Item_GObj*);
/* 2BFE5C */ void it_802BFE5C(Item_GObj*, Vec3*, float);
/* 2BFEC4 */ void it_802BFEC4(Item_GObj*);
/* 2C0010 */ void it_802C0010(Item_GObj*, Vec3*);
/* 2C016C */ void it_2725_Logic59_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F7558 */ extern ItemStateTable it_803F7558[];

#endif
