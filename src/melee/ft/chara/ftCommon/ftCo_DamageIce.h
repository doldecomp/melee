#ifndef GALE01_0912A8
#define GALE01_0912A8

#include <platform.h>
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include <placeholder.h>

#ifdef M2CTX
#include <dolphin/mtx/types.h>

struct _m2c_stack_ftCo_80090B60 {
    /* 0x000 */ char pad_0[0x28];
    /* 0x028 */ s32 sp28;          /* inferred */
    /* 0x02C */ s32 sp2C;          /* inferred */
    /* 0x030 */ s32 sp30;          /* inferred */
    /* 0x034 */ Fighter_Part part; /* inferred */
    /* 0x038 */ s32 sp38;          /* inferred */
    /* 0x03C */ s32 sp3C;          /* inferred */
    /* 0x040 */ s32 sp40;          /* inferred */
    /* 0x044 */ s32 sp44;          /* inferred */
    /* 0x048 */ s32 sp48;          /* inferred */
    /* 0x04C */ s32 sp4C;          /* inferred */
    /* 0x050 */ s32 sp50;          /* inferred */
    /* 0x054 */ s32 sp54;          /* inferred */
    /* 0x058 */ f32 sp58;          /* inferred */
    /* 0x05C */ f32 sp5C;          /* inferred */
    /* 0x060 */ char pad_60[8];    /* maybe part of sp5C[3]? */
    /* 0x068 */ Mtx mtx0;
    /* 0x098 */ s32 sp98; /* inferred */
    /* 0x09C */ s32 sp9C; /* inferred */
    /* 0x0A0 */ s32 spA0; /* inferred */
    /* 0x0A4 */ s32 spA4; /* inferred */
    /* 0x0A8 */ char pad_A8[4];
    /* 0x0AC */ Mtx mtx1;
    /* 0x0DC */ Quaternion rot;
    /* 0x0EC */ Mtx mtx2;
    /* 0x11C */ Mtx mtx3;
    /* 0x14C */ Mtx mtx4;
    /* 0x17C */ Mtx mtx5;
    /* 0x1AC */ Vec3 trans;
    /* 0x1B8 */ char pad_1B8[0x18];
}; /* size = 0x1D0 */

struct _m2c_stack_ftCo_80091854 {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ f32 sp24; /* inferred */
    /* 0x28 */ Vec3 vec;
    /* 0x34 */ char pad_34[0xC];
}; /* size = 0x40 */
#endif

#ifdef MWERKS_GEKKO
/* static */ extern char* ftCo_804D3AE8; // = "jobj.h"
/* static */ extern char* ftCo_804D3AF0; // = "jobj"
#endif

/* static */ extern Vec3 const ftCo_803B74B0; // = { 0 }
/* static */ extern Vec3 const ftCo_803B74BC; // = { 0 }

/* 090984 */ void ftCo_80090984(ftCo_GObj* gobj);
/* 0909D0 */ /* static */ void ftCo_800909D0(ftCo_Fighter* fp);
/* 090AC0 */ /* static */ void ftCo_80090AC0(ftCo_Fighter* fp);
/* 090B48 */ /* static */ void ftCo_80090B48(ftCo_GObj* gobj);
/* 090B60 */ void ftCo_80090B60(ftCo_GObj* gobj);
/* 091030 */ void ftCo_80091030(ftCo_GObj* gobj);
/* 091274 */ /* static */ void ftCo_80091274(ftCo_GObj* gobj);
/* 0912A8 */ void ftCo_DamageIce_Anim(ftCo_GObj* gobj);
/* 0913DC */ void ftCo_DamageIce_IASA(ftCo_GObj* gobj);
/* 0913E0 */ void ftCo_DamageIce_Phys(ftCo_GObj* gobj);
/* 09144C */ void ftCo_DamageIce_Coll(ftCo_GObj* gobj);
/* 0914A4 */ void ftCo_800914A4(ftCo_GObj* gobj);
/* 091620 */ /* static */ UNK_RET ftCo_80091620(UNK_PARAMS);
/* 091854 */ void ftCo_80091854(ftCo_GObj* gobj);
/* 091988 */ void ftCo_DamageIceJump_Anim(ftCo_GObj* gobj);
/* 0919D8 */ void ftCo_DamageIceJump_IASA(ftCo_GObj* gobj);
/* 0919DC */ void ftCo_DamageIceJump_Phys(ftCo_GObj* gobj);
/* 0919FC */ void ftCo_DamageIceJump_Coll(ftCo_GObj* gobj);

#endif
