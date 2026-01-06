#ifndef GALE01_1CD338
#define GALE01_1CD338

#include <placeholder.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

struct unkCastle {
    /* 0x000 */ u8 _pad[0x10C];
    /* 0x10C */ HSD_GObj* x10C[5];
    /* 0x120 */ u8 _pad2[0x134 - 0x120];
    /* 0x134 */ u8 x134[5];
};

/* 1CD338 */ void grCastle_801CD338(bool);
/* 1CD37C */ void grCastle_801CD37C(void);
/* 1CD4A0 */ void grCastle_801CD4A0(void);
/* 1CD4A4 */ void grCastle_801CD4A4(void);
/* 1CD4C8 */ bool grCastle_801CD4C8(void);
/* 1CD4D0 */ UNK_RET grCastle_801CD4D0(UNK_PARAMS);
/* 1CD5BC */ void grCastle_801CD5BC(Ground_GObj*);
/* 1CD600 */ bool grCastle_801CD600(Ground_GObj*);
/* 1CD608 */ void grCastle_801CD608(Ground_GObj*);
/* 1CD60C */ void grCastle_801CD60C(Ground_GObj*);
/* 1CD610 */ UNK_RET fn_801CD610(UNK_PARAMS);
/* 1CD658 */ void grCastle_801CD658(Ground_GObj*);
/* 1CD8A0 */ bool grCastle_801CD8A0(Ground_GObj*);
/* 1CD8A8 */ void grCastle_801CD8A8(Ground_GObj*);
/* 1CD960 */ void grCastle_801CD960(Ground_GObj*);
/* 1CD9B4 */ UNK_RET fn_801CD9B4(UNK_PARAMS);
/* 1CDA0C */ void grCastle_801CDA0C(Ground_GObj*);
/* 1CDC3C */ bool grCastle_801CDC3C(Ground_GObj*);
/* 1CDC44 */ void grCastle_801CDC44(Ground_GObj*);
/* 1CDF50 */ void grCastle_801CDF50(Ground_GObj*);
/* 1CDF54 */ UNK_RET grCastle_801CDF54(UNK_PARAMS);
/* 1CDFD8 */ UNK_RET grCastle_801CDFD8(UNK_PARAMS);
/* 1CE054 */ UNK_RET grCastle_801CE054(UNK_PARAMS);
/* 1CE19C */ UNK_RET grCastle_801CE19C(UNK_PARAMS);
/* 1CE260 */ void grCastle_801CE260(Ground_GObj*);
/* 1CE3A0 */ UNK_RET fn_801CE3A0(UNK_PARAMS);
/* 1CE3A4 */ bool grCastle_801CE3A4(Ground_GObj*);
/* 1CE3AC */ UNK_RET grCastle_801CE3AC(UNK_PARAMS);
/* 1CE578 */ void grCastle_801CE578(Ground_GObj*);
/* 1CE7E4 */ void grCastle_801CE7E4(Ground_GObj*);
/* 1CE7E8 */ void grCastle_801CE7E8(Ground_GObj*);
/* 1CE858 */ bool grCastle_801CE858(Ground_GObj*);
/* 1CE860 */ void grCastle_801CE860(Ground_GObj*);
/* 1CE8E4 */ void grCastle_801CE8E4(Ground_GObj*);
/* 1CE8E8 */ void grCastle_801CE8E8(Ground_GObj*);
/* 1CE9DC */ UNK_RET fn_801CE9DC(UNK_PARAMS);
/* 1CE9E0 */ bool grCastle_801CE9E0(Ground_GObj*);
/* 1CE9E8 */ void grCastle_801CE9E8(Ground_GObj*);
/* 1CEAC8 */ void grCastle_801CEAC8(Ground_GObj*);
/* 1CEACC */ void grCastle_801CEACC(Ground_GObj*);
/* 1CEEFC */ bool grCastle_801CEEFC(Ground_GObj*);
/* 1CEF04 */ void grCastle_801CEF04(Ground_GObj*);
/* 1CF0F0 */ void grCastle_801CF0F0(Ground_GObj*);
/* 1CF0F4 */ void grCastle_801CF0F4(Ground_GObj*);
/* 1CF300 */ bool grCastle_801CF300(Ground_GObj*);
/* 1CF308 */ void grCastle_801CF308(Ground_GObj*);
/* 1CF74C */ void grCastle_801CF74C(Ground_GObj*);
/* 1CF750 */ UNK_RET fn_801CF750(UNK_PARAMS);
/* 1CF7B0 */ UNK_RET grCastle_801CF7B0(UNK_PARAMS);
/* 1CF868 */ UNK_RET grCastle_801CF868(UNK_PARAMS);
/* 1CFAFC */ UNK_RET fn_801CFAFC(UNK_PARAMS);
/* 1CFB68 */ UNK_RET fn_801CFB68(UNK_PARAMS);
/* 1CFBD4 */ UNK_RET grCastle_801CFBD4(UNK_PARAMS);
/* 1D0298 */ UNK_RET grCastle_801D0298(UNK_PARAMS);
/* 1D02B8 */ UNK_RET grCastle_801D02B8(UNK_PARAMS);
/* 1D0520 */ UNK_RET fn_801D0520(UNK_PARAMS);
/* 1D0550 */ void grCastle_801D0550(UNK_T, unkCastle*);
/* 1D059C */ void grCastle_801D059C(UNK_T, unkCastle*);
/* 1D05E8 */ void grCastle_801D05E8(UNK_T, unkCastle*);
/* 1D0634 */ void grCastle_801D0634(UNK_T, unkCastle*);
/* 1D0680 */ void grCastle_801D0680(UNK_T, unkCastle*);
/* 1D06CC */ void grCastle_801D06CC(UNK_T, unkCastle*, Ground_GObj*);
/* 1D0744 */ void grCastle_801D0744(UNK_T, unkCastle*, Ground_GObj*);
/* 1D07BC */ void grCastle_801D07BC(UNK_T, unkCastle*, Ground_GObj*);
/* 1D0834 */ void grCastle_801D0834(UNK_T, unkCastle*, Ground_GObj*);
/* 1D08AC */ void grCastle_801D08AC(UNK_T, unkCastle*, Ground_GObj*);
/* 1D0924 */ UNK_RET fn_801D0924(UNK_PARAMS);
/* 1D09B8 */ UNK_RET fn_801D09B8(UNK_PARAMS);
/* 1D0A9C */ void grCastle_801D0A9C(Vec3* arg0, f32 arg8);
/* 1D0B04 */ DynamicsDesc* grCastle_801D0B04(enum_t);
/* 1D0B0C */ bool grCastle_801D0B0C(Vec3* v, int arg1, HSD_JObj* jobj);
/* 1D0BBC */ UNK_RET grCastle_801D0BBC(UNK_PARAMS);
/* 1D0D24 */ UNK_RET grCastle_801D0D24(UNK_PARAMS);
/* 1D0D84 */ UNK_RET grCastle_801D0D84(UNK_PARAMS);
/* 1D0FF0 */ float grCastle_801D0FF0(void);
/* 3B7F28 */ extern unkCastleCallback grCs_803B7F28[];
/* 3B7F3C */ extern unkCastleCallback2 grCs_803B7F3C[];

#endif
