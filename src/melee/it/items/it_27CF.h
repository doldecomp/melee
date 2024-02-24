#ifndef GALE01_27CF30
#define GALE01_27CF30

#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftSeak/types.h"
#include "it/items/types.h"

/* 27D670 */ void it_8027D670(Vec3* const);
/* 27D730 */ void it_8027D730(Item_GObj*);
/* 283AE4 */ HSD_GObj* it_80283AE4(s32, Vec3*, s32);
/* 283BD4 */ void it_80283BD4(Item_GObj*);
/* 2841B4 */ HSD_GObj* it_802841B4(s32, Vec3*, s32);
/* 28428C */ void it_8028428C(Item_GObj*);
/* 284854 */ HSD_GObj* it_80284854(Vec3*);
/* 286088 */ HSD_GObj* it_80286088(s32);
/* 2896CC */ HSD_GObj* it_802896CC(Vec3*);
/* 28FAF4 */ void it_8028FAF4(Item_GObj*, Vec3*);
/* 28FE90 */ void it_8028FE90(Item_GObj*);
/* 290938 */ HSD_GObj* it_80290938(HSD_JObj*);
/* 291BE0 */ HSD_GObj* it_80291BE0(Vec3*);
/* 292D48 */ HSD_GObj* it_80292D48(Vec3*);
/* 294DC0 */ HSD_GObj* it_80294DC0(Vec3*);
/* 294E78 */ void it_80294E78(Item_GObj*, float);
/* 294EB0 */ void it_80294EB0(Item_GObj*, Vec3*, Vec3*);
/* 2950D4 */ void it_802950D4(Item_GObj*, bool);
/* 29A748 */ HSD_GObj* it_8029A748(Item_GObj*, Vec3*, u8, float);
/* 29A89C */ void it_8029A89C(Item_GObj*, float);
/* 29A8F4 */ void it_8029A8F4(Item_GObj*, Vec3*, float);
/* 29D968 */ void it_8029D968(Item_GObj*);
/* 29DD58 */ HSD_GObj* it_8029DD58(Item_GObj* fighter_gobj, Vec3*, u8, int,
                                   float);
/* 29FDBC */ bool it_8029FDBC(Item_GObj* gobj);
/* 2A013C */ HSD_GObj* it_802A013C(float facing_dir, Fighter_GObj* owner_gobj,
                                   Vec3* pos, Fighter_Part, int);
/* 2A0534 */ void it_802A0534(Item_GObj* gobj, Vec3*);
/* 2A07B4 */ void it_802A07B4(Item_GObj* gobj);
/* 2A8398 */ void it_802A8398(Item_GObj*, Vec3*);
/* 2A83E0 */ HSD_GObj* it_802A83E0(float facing_dir, Fighter_GObj*, Vec3*,
                                   Fighter_Part, int);
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
/* 2AD478 */ HSD_GObj* it_802AD478(Item_GObj*, Vec3*, s32, float);
/* 2AD6B8 */ void it_802AD6B8(Item_GObj*);
/* 2ADDD0 */ void it_802ADDD0(Item_GObj*, s32);
/* 2AE1D0 */ void it_802AE1D0(Item_GObj*);
/* 2AE538 */ void it_802AE538(Item_GObj*);
/* 2AE608 */ void it_802AE608(Item_GObj*);
/* 2AE8A8 */ HSD_GObj* it_802AE8A8(float, HSD_GObj*, Vec3*, s32, s32);
/* 2AEAB4 */ void it_802AEAB4(Item_GObj*);
/* 2AF1A4 */ HSD_GObj* it_802AF1A4(float facing_dir, Fighter_GObj* owner_gobj,
                                   Vec3*, Fighter_Part, int);
/* 2AF304 */ void it_802AF304(Item_GObj* gobj);
/* 2B1DEC */ s32 it_802B1DEC(u32);
/* 2B1DF8 */ u32 it_802B1DF8(Item_GObj*, Vec3*, Vec3*, s32, s32, s32);
/* 2B1FC8 */ s32 it_802B1FC8(u32);
/* 2B1FE8 */ void it_802B1FE8(u32, Vec3*);
/* 2B2560 */ HSD_GObj* it_802B2560(Item_GObj*, float, Vec3*, long, u32);
/* 2B2674 */ void it_802B2674(Item_GObj*);
/* 2B26C0 */ void it_802B26C0(Item_GObj*);
/* 2B26E0 */ void it_802B26E0(Item_GObj*);
/* 2B338C */ void it_802B338C(Item_GObj*, Vec3*, float facing_dir, u32);
/* 2B4AC8 */ void it_802B4AC8(Item_GObj* gobj, Vec3*, float facing_dir,
                              float x);
/* 2B55C8 */ HSD_GObj* it_802B55C8(Item_GObj* owner, Vec3*, s32, s32,
                                   float facing_dir);
/* 2B56E4 */ void it_802B56E4(Item_GObj*, Vec3*, float, float, float);
/* 2B5974 */ void it_802B5974(Item_GObj*);
/* 2B62D0 */ void it_802B62D0(Item_GObj*, Vec3* pos, bool, float facing_dir);
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
/* 2BD45C */ void it_802BD45C(Item_GObj* gobj);
/* 2BD4AC */ HSD_GObj* it_802BD4AC(Item_GObj*, Vec3*, u8, s32, float);
/* 2BDB94 */ void it_802BDB94(Item_GObj* gobj);
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
/* 2C1590 */ Item_GObj* it_802C1590(Item_GObj*, Vec3*, enum_t,
                                    float facing_dir);
/* 2C16F8 */ void it_802C16F8(Item_GObj*);
/* 2C17DC */ void it_802C17DC(Item_GObj*);
/* 2C3AF0 */ HSD_GObj* it_802C3AF0(Item_GObj*);
/* 2C3BAC */ HSD_GObj* it_802C3BAC(Item_GObj*, Vec3*, float facing_dir, float);
/* 2C3D44 */ void it_802C3D44(Item_GObj*);
/* 2C49E0 */ void it_802C49E0(Item_GObj*);
/* 2C4A40 */ HSD_GObj* it_802C4A40(Item_GObj*, Vec3*, float);
/* 2C5000 */ HSD_GObj* it_802C5000(Item_GObj*, Vec3*, s32, s32, float);
/* 2C519C */ void it_802C519C(Item_GObj*, Vec3*, s32, s32, float, float);
/* 2C53F0 */ void it_802C53F0(Item_GObj*, Vec3*, float, float, float);
/* 2C573C */ void it_802C573C(Item_GObj*);
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
/* 2C6F40 */ HSD_GObj* it_802C6F40(Item_GObj*, Vec3*, s32, float);
/* 2C7074 */ void it_802C7074(Item_GObj*);
/* 2C70C0 */ void it_802C70C0(Item_GObj*);
/* 2C70E0 */ void it_802C70E0(Item_GObj*);
/* 2C7158 */ void it_802C7158(Item_GObj*);
/* 2C720C */ HSD_GObj* it_802C720C(Item_GObj*, Vec3*, s32, float);
/* 2C7340 */ void it_802C7340(Item_GObj*);
/* 2C738C */ void it_802C738C(Item_GObj*);
/* 2C73AC */ void it_802C73AC(Item_GObj*);
/* 2C7424 */ void it_802C7424(Item_GObj*);
/* 2C7774 */ HSD_GObj* it_802C7774(float, HSD_GObj*, Vec3*, s32, u32);
/* 2C7A84 */ void it_802C7A84(Item_GObj*);
/* 2C7AD0 */ void it_802C7AD0(Item_GObj*);
/* 2C7AF0 */ void it_802C7AF0(Item_GObj*);
/* 2C7D60 */ HSD_GObj* it_802C7D60(Item_GObj*, Vec3*, s32, float);
/* 2C7E94 */ void it_802C7E94(Item_GObj*);
/* 2C7EE0 */ void it_802C7EE0(Item_GObj*);
/* 2C7F00 */ void it_802C7F00(Item_GObj*);
/* 2C8038 */ HSD_GObj* it_802C8038(Item_GObj*, Vec3*, s32, s32, float, float);
/* 2C8158 */ void it_802C8158(Item_GObj*);
/* 2C81C8 */ void it_802C81C8(Item_GObj*);
/* 2C81E8 */ void it_802C81E8(Item_GObj*);
/* 2C837C */ HSD_GObj* it_802C837C(Item_GObj*, Vec3*, enum_t, u32, float);
/* 2C8B28 */ HSD_GObj* it_802C8B28(Item_GObj*, Vec3*, u32, float);
/* 2C8C34 */ void it_802C8C34(Item_GObj*);
/* 2D09D0 */ void it_802D09D0(Item_GObj*);
/* 2D8618 */ void it_802D8618(s32, Vec3*, s32, s32);
/* 2E5F8C */ s32 it_802E5F8C(Item_GObj*, Vec3*, s32, bool, float, float);
/* 2F0340 */ u32 it_802F0340(Item_GObj*, Vec3*, Vec3*, u32, u32, float);
/* 2F046C */ void it_802F046C(s32);
/* 2F0AE0 */ void it_802F0AE0(Item_GObj* fighter_gobj, Vec3*, Vec3*, enum_t,
                              bool, float facing_dir, float, float);
/* 2F2094 */ s32 it_802F2094(s32, Vec3*, s32, s32);
/* 2F3330 */ bool it_802F3330(Item_GObj*);
/* 2F3374 */ void it_802F3374(Item_GObj*, Item_GObj*);
/* 3F94A0 */ extern ItemStateTable it_803F94A0[];

#endif
