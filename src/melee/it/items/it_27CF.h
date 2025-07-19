#ifndef GALE01_27CF30
#define GALE01_27CF30

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

#include "ftSeak/types.h"
#include "it/itCommonItems.h"
#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 283AE4 */ Item_GObj* it_80283AE4(Item_GObj*, Vec3*, s32);
/* 283BD4 */ void it_80283BD4(Item_GObj*);
/* 2841B4 */ HSD_GObj* it_802841B4(HSD_GObj*, Vec3*, s32);
/* 28428C */ void it_8028428C(Item_GObj*);
/* 29D968 */ void it_8029D968(Item_GObj*);
/* 29DD58 */ HSD_GObj* it_8029DD58(Item_GObj* fighter_gobj, Vec3*, u8, int,
                                   float);
/* 2A850C */ void it_802A850C(Item_GObj*, Vec3*, Vec3*, float, float, float);
/* 2A8A7C */ void it_802A8A7C(Item_GObj* gobj);
/* 2ADDD0 */ void it_802ADDD0(Item_GObj*, s32);
/* 2AE1D0 */ void it_802AE1D0(Item_GObj*);
/* 2AE538 */ void it_802AE538(Item_GObj*);
/* 2AE608 */ void it_802AE608(Item_GObj*);
/* 2AE8A8 */ Item_GObj* it_802AE8A8(float, Fighter_GObj*, Vec3*, Fighter_Part,
                                    ItemKind);
/* 2AEAB4 */ void it_802AEAB4(Item_GObj*);
/* 2B2560 */ HSD_GObj* it_802B2560(Item_GObj*, float, Vec3*, long, u32);
/* 2B2674 */ void it_802B2674(Item_GObj*);
/* 2B26C0 */ void it_802B26C0(Item_GObj*);
/* 2B26E0 */ void it_802B26E0(Item_GObj*);
/* 2BAEEC */ void it_802BAEEC(Item_GObj*);
/* 2BAF0C */ void it_802BAF0C(Item_GObj*);
/* 2BB20C */ void it_802BB20C(Item_GObj*);
/* 2BB290 */ HSD_GObj* it_802BB290(Item_GObj* gobj, Vec3* arg1,
                                   float facing_dir);
/* 2BCF84 */ void it_802BCF84(Item_GObj*);
/* 2BCFC4 */ void it_802BCFC4(Item_GObj* gobj, float* arg1,
                              itChainSegment* chainSegment, Item* item_data,
                              float arg4);
/* 2BDBF8 */ void it_802BDBF8(Item_GObj* gobj);
/* 2BDC18 */ void it_802BDC18(Item_GObj* gobj);
/* 2BDC38 */ bool it_802BDC38(Item_GObj* gobj);
/* 2C0510 */ void it_802C0510(Item_GObj*, Vec3*, s32, s32, float facing_dir);
/* 2C0850 */ u32 it_802C0850(Item_GObj*, Vec3*, u32, s32,
                             float facing_direction);
/* 2C0DBC */ void it_802C0DBC(u32 arg0);
/* 2C61F4 */ HSD_GObj* it_802C61F4(Item_GObj*, Vec3*, s32, float);
/* 2C6328 */ void it_802C6328(Item_GObj*);
/* 2C6374 */ void it_802C6374(Item_GObj*);
/* 2C6394 */ void it_802C6394(Item_GObj*);
/* 2C6430 */ void it_802C6430(Item_GObj*);
/* 2C6458 */ void it_802C6458(Item_GObj*);
/* 2C6480 */ void it_802C6480(Item_GObj*);
/* 2C64A8 */ void it_802C64A8(Item_GObj*);
/* 2C65E4 */ HSD_GObj* it_802C65E4(Item_GObj*, Vec3*, s32, float);
/* 2C6718 */ void it_802C6718(Item_GObj*);
/* 2C6764 */ void it_802C6764(Item_GObj*);
/* 2C6784 */ void it_802C6784(Item_GObj*);
/* 2C68F8 */ HSD_GObj* it_802C68F8(Item_GObj*, Vec3*, s32, float);
/* 2C6A2C */ void it_802C6A2C(Item_GObj*);
/* 2C6A78 */ void it_802C6A78(Item_GObj*);
/* 2C6A98 */ void it_802C6A98(Item_GObj*);
/* 2C6C38 */ HSD_GObj* it_802C6C38(Item_GObj*, Vec3*, enum_t part, float);
/* 2C6D6C */ void it_802C6D6C(Item_GObj*);
/* 2C6DB8 */ void it_802C6DB8(Item_GObj*);
/* 2C6DD8 */ void it_802C6DD8(Item_GObj*);
/* 2C6E50 */ void it_802C6E50(Item_GObj*);
/* 2C7340 */ void it_802C7340(Item_GObj*);
/* 2C738C */ void it_802C738C(Item_GObj*);
/* 2C73AC */ void it_802C73AC(Item_GObj*);
/* 2C7424 */ void it_802C7424(Item_GObj*);
/* 2C7774 */ HSD_GObj* it_802C7774(float, HSD_GObj*, Vec3*, s32, u32);
/* 2C7A84 */ void it_802C7A84(Item_GObj*);
/* 2C7AD0 */ void it_802C7AD0(Item_GObj*);
/* 2C7AF0 */ void it_802C7AF0(Item_GObj*);
/* 2F2F34 */ void it_802F2F34(HSD_GObj*, it_27CF_DatAttrs*);
/* 2F3020 */ void it_802F3020(HSD_GObj*);
/* 2F3078 */ bool it_802F3078(HSD_GObj*);
/* 2F3120 */ void it_802F3120(HSD_GObj*);
/* 2F3150 */ bool it_802F3150(HSD_GObj*);
/* 2F317C */ void it_802F317C(HSD_GObj*);
/* 2F31B8 */ bool it_802F31B8(HSD_GObj*);
/* 2F3260 */ void it_802F3260(HSD_GObj*);
/* 2F3264 */ bool it_802F3264(HSD_GObj*);
/* 2F3290 */ void it_802F3290(Item_GObj*);
/* 2F32F8 */ bool it_802F32F8(HSD_GObj*);
/* 2F3330 */ bool it_802F3330(Item_GObj*);
/* 2F3374 */ void it_802F3374(Item_GObj*, HSD_GObj*);
/* 3F94A0 */ extern ItemStateTable it_803F94A0[];

#endif
