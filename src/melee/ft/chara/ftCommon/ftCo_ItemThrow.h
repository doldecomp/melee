#ifndef GALE01_0949F4
#define GALE01_0949F4

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>

#include <placeholder.h>

#ifdef M2CTX
struct _m2c_stack_ftCo_80095EFC {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 sp18;
    /* 0x24 */ Vec3 sp24;
    /* 0x30 */ Vec3 sp30;
    /* 0x3C */ char pad_3C[0x1C];
}; /* size = 0x58 */
#endif

/* 0949F4 */ bool ftCo_80094E54(ftCo_Fighter* fp);
/* 094CFC */ /* static */ bool ftCo_8009515C(ftCo_GObj* gobj);
/* 094D70 */ /* static */ bool ftCo_800951D0(ftCo_GObj* gobj);
/* 094DF4 */ /* static */ bool ftCo_80095254(ftCo_GObj* gobj);
/* 094E7C */ /* static */ bool ftCo_800952DC(ftCo_GObj* gobj);
/* 094EA4 */ bool ftCo_80094EA4(ftCo_GObj* gobj);
/* 0951DC */ /* static */ bool ftCo_8009563C(ftCo_GObj* gobj);
/* 0952A0 */ /* static */ void ftCo_80095700(ftCo_GObj* gobj, enum_t arg1);
/* 0952C8 */ /* static */ UNK_RET lbl_80095728(UNK_PARAMS);
/* 0952D8 */ /* static */ UNK_RET lbl_80095738(UNK_PARAMS);
/* 0952E4 */ void ftCo_80095744(ftCo_GObj* gobj, int*);
/* 095328 */ bool ftCo_80095328(ftCo_GObj*, bool*);
/* 095394 */ void ftCo_800957F4(ftCo_GObj* gobj, FtMotionId msid);
/* 09542C */ /* static */ UNK_RET ftCo_8009588C(UNK_PARAMS);
/* 09543C */ /* static */ UNK_RET ftCo_8009589C(UNK_PARAMS);
/* 09549C */ /* static */ void ftCo_800958FC(ftCo_GObj* gobj, int);
/* 095530 */ /* static */ UNK_RET ftCo_80095990(UNK_PARAMS);
/* 095540 */ /* static */ UNK_RET ftCo_800959A0(UNK_PARAMS);
/* 0955D0 */ /* static */ void ftCo_80095A30(ftCo_GObj* gobj);
/* 0958FC */ /* static */ void ftCo_80095D5C(ftCo_Fighter* fp, Vec3* arg1);
/* 095A20 */ void ftCo_ItemThrow_Anim(ftCo_GObj* gobj);
/* 095A9C */ /* static */ void ftCo_80095EFC(ftCo_GObj* gobj);
/* 095CC0 */ void ftCo_ItemThrow_IASA(ftCo_GObj* gobj);
/* 095CC4 */ void ftCo_ItemThrow_Phys(ftCo_GObj* gobj);
/* 095CE4 */ void ftCo_LightThrowDash_Phys(ftCo_GObj* gobj);
/* 095D50 */ void ftCo_LightThrowAir_Phys(ftCo_GObj* gobj);
/* 095DA8 */ void ftCo_LightThrowDashDrop_Coll(ftCo_GObj* gobj);
/* 095DC8 */ void ftCo_LightThrow_Coll(ftCo_GObj* gobj);
/* 095EEC */ void ftCo_LightThrowAir_Coll(ftCo_GObj* gobj);
/* 096010 */ void ftCo_HeavyThrow_Coll(ftCo_GObj* gobj);
/* 0961D0 */ void ftCo_800961D0(ftCo_GObj* gobj);
/* 096250 */ void ftCo_80096250(ftCo_GObj* gobj);
/* 096374 */ void ftCo_80096374(ftCo_GObj* gobj);
/* 096498 */ void ftCo_80096498(ftCo_GObj* gobj);

#endif
