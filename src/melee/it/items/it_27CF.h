#ifndef GALE01_27CF30
#define GALE01_27CF30

#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftSeak/types.h"
#include "it/items/types.h"

/* 283AE4 */ Item_GObj* it_80283AE4(Item_GObj*, Vec3*, s32);
/* 283BD4 */ void it_80283BD4(Item_GObj*);
/* 2841B4 */ HSD_GObj* it_802841B4(HSD_GObj*, Vec3*, s32);
/* 28428C */ void it_8028428C(Item_GObj*);
/* 29D968 */ void it_8029D968(Item_GObj*);
/* 29DD58 */ HSD_GObj* it_8029DD58(Item_GObj* fighter_gobj, Vec3*, u8, int,
                                   float);
/* 2A850C */ void it_802A850C(Item_GObj*, Vec3*, Vec3*, float, float, float);
/* 2A8A7C */ void it_802A8A7C(Item_GObj* gobj);
/* 2AA054 */ void it_802AA054(Item_GObj*, Vec3*, Vec3*, float, float);
/* 2AA7E4 */ HSD_GObj* it_802AA7E4(Item_GObj*);
/* 2AA7F0 */ enum_t it_802AA7F0(Item_GObj*);
/* 2AA8C0 */ HSD_GObj* it_802AA8C0(Item_GObj*, Vec3*, enum_t, float);
/* 2AAA50 */ void it_802AAA50(Item_GObj*);
/* 2AB3F0 */ void it_802AB3F0(Item_GObj*, void*, s32);
/* 2AB568 */ HSD_GObj* it_802AB568(Item_GObj*);
/* 2AB58C */ HSD_GObj* it_802AB58C(Item_GObj* owner, Vec3* pos,
                                   float facing_dir);
/* 2AB9C0 */ void it_802AB9C0(Item_GObj*);
/* 2ADDD0 */ void it_802ADDD0(Item_GObj*, s32);
/* 2AE1D0 */ void it_802AE1D0(Item_GObj*);
/* 2AE538 */ void it_802AE538(Item_GObj*);
/* 2AE608 */ void it_802AE608(Item_GObj*);
/* 2AE8A8 */ Item_GObj* it_802AE8A8(float, Fighter_GObj*, Vec3*, Fighter_Part,
                                    ItemKind);
/* 2AEAB4 */ void it_802AEAB4(Item_GObj*);
/* 2B1DEC */ s32 it_802B1DEC(u32);
/* 2B1DF8 */ u32 it_802B1DF8(Item_GObj*, Vec3*, Vec3*, s32, s32, s32);
/* 2B1FC8 */ s32 it_802B1FC8(u32);
/* 2B1FE8 */ void it_802B1FE8(u32, Vec3*);
/* 2B2560 */ HSD_GObj* it_802B2560(Item_GObj*, float, Vec3*, long, u32);
/* 2B2674 */ void it_802B2674(Item_GObj*);
/* 2B26C0 */ void it_802B26C0(Item_GObj*);
/* 2B26E0 */ void it_802B26E0(Item_GObj*);
/* 2B338C */ void it_802B338C(Item_GObj*, Vec3*, float facing_dir, u32);
/* 2BAEEC */ void it_802BAEEC(Item_GObj*);
/* 2BAF0C */ void it_802BAF0C(Item_GObj*);
/* 2BB20C */ void it_802BB20C(Item_GObj*);
/* 2BB290 */ HSD_GObj* it_802BB290(Item_GObj* gobj, Vec3* arg1,
                                   float facing_dir);
/* 2BCF84 */ void it_802BCF84(Item_GObj*);
/* 2BCFC4 */ void it_802BCFC4(Item_GObj* gobj, float* arg1,
                              itChainSegment* chainSegment, Item* item_data,
                              float arg4);
/* 2BD158 */ void it_802BD158(Item_GObj* gobj, Vec3*, int, float);
/* 2BDBF8 */ void it_802BDBF8(Item_GObj* gobj);
/* 2BDC18 */ void it_802BDC18(Item_GObj* gobj);
/* 2BDC38 */ bool it_802BDC38(Item_GObj* gobj);
/* 2BDE18 */ HSD_GObj* it_802BDE18(Item_GObj*, Vec3*, Fighter_Part, enum_t,
                                   float);
/* 2BDF40 */ void it_802BDF40(Item_GObj* gobj);
/* 2BDFA0 */ void it_802BDFA0(Item_GObj* gobj);
/* 2BDFC0 */ void it_802BDFC0(Item_GObj* gobj);
/* 2BE100 */ void it_802BE100(Item_GObj* gobj);
/* 2BE214 */ void it_802BE214(Item_GObj* gobj, Vec3* pos, enum_t,
                              float facing_dir);
/* 2BE598 */ void it_802BE598(Item_GObj*);
/* 2BE5B8 */ void it_802BE5B8(Item_GObj*);
/* 2BE5D8 */ void it_802BE5D8(void*, float);
/* 2BE958 */ void it_802BE958(void*);
/* 2BE9D8 */ HSD_GObj* it_802BE9D8(float, HSD_GObj*, Vec3*, s32);
/* 2BFE5C */ void it_802BFE5C(Item_GObj*, Vec3*, float);
/* 2BFEC4 */ void it_802BFEC4(void*);
/* 2C0010 */ void it_802C0010(Item_GObj*, void*);
/* 2C0510 */ void it_802C0510(Item_GObj*, Vec3*, s32, s32, float facing_dir);
/* 2C0850 */ u32 it_802C0850(Item_GObj*, Vec3*, u32, s32,
                             float facing_direction);
/* 2C0DBC */ void it_802C0DBC(u32 arg0);
/* 2C3AF0 */ HSD_GObj* it_802C3AF0(Item_GObj*);
/* 2C3BAC */ HSD_GObj* it_802C3BAC(Item_GObj*, Vec3*, float facing_dir, float);
/* 2C3D44 */ void it_802C3D44(Item_GObj*);
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
/* 2C720C */ HSD_GObj* it_802C720C(Item_GObj*, Vec3*, s32, float);
/* 2C7340 */ void it_802C7340(Item_GObj*);
/* 2C738C */ void it_802C738C(Item_GObj*);
/* 2C73AC */ void it_802C73AC(Item_GObj*);
/* 2C7424 */ void it_802C7424(Item_GObj*);
/* 2C7774 */ HSD_GObj* it_802C7774(float, HSD_GObj*, Vec3*, s32, u32);
/* 2C7A84 */ void it_802C7A84(Item_GObj*);
/* 2C7AD0 */ void it_802C7AD0(Item_GObj*);
/* 2C7AF0 */ void it_802C7AF0(Item_GObj*);
/* 2F2094 */ Item_GObj* it_802F2094(int, Vec3*, int, int);
/* 2F2F34 */ UNK_RET it_802F2F34(UNK_PARAMS);
/* 2F3020 */ UNK_RET it_802F3020(UNK_PARAMS);
/* 2F3078 */ UNK_RET it_802F3078(UNK_PARAMS);
/* 2F3120 */ UNK_RET it_802F3120(UNK_PARAMS);
/* 2F3150 */ UNK_RET it_802F3150(UNK_PARAMS);
/* 2F317C */ UNK_RET it_802F317C(UNK_PARAMS);
/* 2F31B8 */ UNK_RET it_802F31B8(UNK_PARAMS);
/* 2F3260 */ UNK_RET it_802F3260(UNK_PARAMS);
/* 2F3264 */ UNK_RET it_802F3264(UNK_PARAMS);
/* 2F3290 */ UNK_RET it_802F3290(UNK_PARAMS);
/* 2F32F8 */ UNK_RET it_802F32F8(UNK_PARAMS);
/* 2F3330 */ bool it_802F3330(Item_GObj*);
/* 2F3374 */ void it_802F3374(Item_GObj*, Item_GObj*);
/* 3F94A0 */ extern ItemStateTable it_803F94A0[];

#endif
