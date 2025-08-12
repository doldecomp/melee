#ifndef GALE01_2A2418
#define GALE01_2A2418

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "it/itCharItems.h"
#include "it/items/types.h"
#include "it/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

// /* 2A2418 */ void it_802A2418(Item_GObj*);
// /* 2A2B10 */ void it_802A2B10(Item_GObj* gobj);
// /* 2A2BA4 */ Item_GObj* it_802A2BA4(Fighter_GObj*, Vec3*, float, int);
// /* 2A7688 */ void it_2725_Logic20_PickedUp(Item_GObj*);
// /* 2A78B8 */ void it_802A78B8(HSD_GObj*, Vec3*, float);
// /* 2A7AAC */ void it_802A7AAC(HSD_GObj*);
// /* 2A7AF0 */ void it_802A7AF0(HSD_GObj*);
// /* 2A7B34 */ void it_802A7B34(HSD_GObj*);
// /* 2A7D40 */ void it_802A7D40(Item_GObj*, Item_GObj*);
/* 3F6998 */ extern ItemStateTable it_803F6998[];

/* 802A2418 */ void it_802A2418(Item_GObj* arg0);
/* 802A2428 */ void it_802A2428(Item_GObj* arg0);
/* 802A2474 */ void it_802A2474(void* arg0);
/* 802A24A0 */ void it_802A24A0(HSD_GObj* gobj, int arg1);
/* 802A24D0 */ void it_802A24D0(ItemLink* arg0, f32 arg8);
/* 802A2568 */ HSD_JObj* it_802A2568(Item* arg0, HSD_JObj* arg1, s32 arg2,
                                     f32 arg8);
/* 802A2B10 */ void it_802A2B10(Item_GObj* gobj);
/* 802A2BA4 */ Item_GObj* it_802A2BA4(Fighter_GObj* arg0, Vec3* arg1, f32 arg2,
                                      s32 arg3);
/* 802A2D88 */ bool itLinkhookshot_UnkMotion8_Anim(Item_GObj* arg0);
/* 802A2ED0 */ void itLinkhookshot_UnkMotion0_Phys(Item_GObj* arg0);
/* 802A2EE4 */ void it_802A2EE4(Item_GObj* arg0);
/* 802A30FC */ void itLinkhookshot_UnkMotion1_Phys(Item_GObj* arg0);
/* 802A3240 */ void itLinkhookshot_UnkMotion2_Phys(Item_GObj* arg0);
/* 802A3254 */ void it_802A3254(Item_GObj* arg0);
/* 802A338C */ void itLinkhookshot_UnkMotion3_Phys(Item_GObj* arg0);
/* 802A34EC */ void itLinkhookshot_UnkMotion4_Phys(Item_GObj* arg0);
/* 802A3500 */ void it_802A3500(Item_GObj* arg0);
/* 802A361C */ void itLinkhookshot_UnkMotion5_Phys(Item_GObj* arg0);
/* 802A3630 */ void it_802A3630(Item_GObj* arg0);
/* 802A3814 */ void itLinkhookshot_UnkMotion6_Phys(Item_GObj* arg0);
/* 802A3828 */ void it_802A3828(Item_GObj* arg0);
/* 802A39E8 */ void itLinkhookshot_UnkMotion7_Phys(Item_GObj* arg0);
/* 802A39FC */ void it_802A39FC(Item_GObj* arg0);
/* 802A3C84 */ void itLinkhookshot_UnkMotion8_Phys(Item_GObj* arg0);
/* 802A3C98 */ float it_802A3C98(Vec3* arg0, Vec3* arg1, Vec3* arg2);
/* 802A3D90 */ s32 it_802A3D90(ItemLink* arg0);
/* 802A3E50 */ s32 it_802A3E50(ItemLink* arg0, enum FighterKind arg1,
                               f32 arg8);
/* 802A40D0 */ s32 it_802A40D0(ItemLink* arg0, f32 arg8);
/* 802A42F4 */ s32 it_802A42F4(ItemLink* arg0, f32 arg8);
/* 802A43B8 */ void it_802A43B8(ItemLink* arg0);
/* 802A43EC */ void it_802A43EC(ItemLink* arg0);
/* 802A4420 */ void it_802A4420(ItemLink* arg0);
/* 802A4454 */ void it_802A4454(ItemLink* arg0);
/* 802A44CC */ void it_802A44CC(ItemLink* arg0, Vec3* arg1,
                                itLinkHookshotAttributes* arg2, f32 arg8);
/* 802A4758 */ void it_802A4758(ItemLink* arg0, Vec3* arg1,
                                itLinkHookshotAttributes* arg2, f32 arg8);
/* 802A49B0 */ void it_802A49B0(ItemLink* arg0, Vec3* arg1,
                                itLinkHookshotAttributes* arg2, f32 arg8);
/* 802A4BFC */ s32 it_802A4BFC(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2, Fighter* arg3);
/* 802A5320 */ s32 it_802A5320(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2, Fighter* arg3);
/* 802A5770 */ void it_802A5770(ItemLink* arg0, Vec3* arg1,
                                itLinkHookshotAttributes* arg2, Fighter* arg3);
/* 802A5AE0 */ s32 it_802A5AE0(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2);
/* 802A5E28 */ s32 it_802A5E28(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2, f32 arg8);
/* 802A5FE0 */ s32 it_802A5FE0(ItemLink* arg0, ItemLink* arg1, Vec3* arg2,
                               itLinkHookshotAttributes* arg3, f32 arg8);
/* 802A6474 */ void it_802A6474(ItemLink* arg0, ItemLink* arg1, Vec3* arg2,
                                itLinkHookshotAttributes* arg3);
/* 802A678C */ s32 it_802A678C(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2, f32 arg8);
/* 802A6944 */ void it_802A6944(Item*, f32);
/* 802A6A78 */ s32 it_802A6A78(ItemLink* arg0, Vec3* arg1,
                               itLinkHookshotAttributes* arg2, Fighter* arg3);
/* 802A6DC8 */ void it_802A6DC8(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2);
/* 802A6F80 */ void it_802A6F80(HSD_JObj* arg0, Vec3* arg1, Vec3* arg2,
                                f32 val);
/* 802A7168 */ void it_802A7168(Item* arg0, Vec3* arg1, f32 arg8);
/* 802A7384 */ void it_802A7384(Item* arg0, Vec3* arg1, f32 arg8);
/* 802A7688 */ void it_2725_Logic20_PickedUp(Item_GObj* arg0);
/* 802A76EC */ void it_802A76EC(HSD_GObj* arg0);
/* 802A7764 */ void it_802A7764(HSD_GObj* arg0);
/* 802A77DC */ void it_802A77DC(Item_GObj* gobj);
/* 802A7840 */ void it_802A7840(HSD_GObj* arg0);
/* 802A78B8 */ void it_802A78B8(HSD_GObj* arg0, Vec3* arg1, f32 arg2);
/* 802A793C */ void it_802A793C(HSD_GObj* arg0);
/* 802A79A0 */ void it_802A79A0(HSD_GObj* arg0);
/* 802A7A04 */ void it_802A7A04(HSD_GObj* arg0);
/* 802A7AAC */ void it_802A7AAC(HSD_GObj* arg0);
/* 802A7AF0 */ void it_802A7AF0(HSD_GObj* arg0);
/* 802A7B34 */ void it_802A7B34(HSD_GObj* arg0);
/* 802A7D40 */ void it_802A7D40(Item_GObj* arg0, Item_GObj* arg1);
extern Vec3 it_803B8650;

#endif
