#ifndef GALE01_0C3A14
#define GALE01_0C3A14

#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>

#include "ft/types.h"

#include <m2c_macros.h>
#include <placeholder.h>
#include <stdbool.h>

struct _m2c_stack_ftCo_800C3A14 {
    /* 0x000 */ char pad_0[0x14];
    /* 0x014 */ M2C_UNK sp14; /* inferred */
    /* 0x014 */ char pad_14[8];
    /* 0x01C */ CollData sp1C; /* inferred */
    /* 0x1BC */ char pad_1BC[4];
}; /* size = 0x1C0 */

struct _m2c_stack_ftCo_AirCatch_Anim {
    /* 0x00 */ char pad_0[0x2C];
    /* 0x2C */ Vec3 sp2C; /* inferred */
    /* 0x38 */ char pad_38[4];
    /* 0x3C */ Vec3 sp3C; /* inferred */
    /* 0x48 */ char pad_48[0xC];
    /* 0x54 */ Vec3 sp54; /* inferred */
    /* 0x60 */ char pad_60[4];
    /* 0x64 */ Vec3 sp64; /* inferred */
    /* 0x70 */ char pad_70[0x20];
}; /* size = 0x90 */

/* 0C3A14 */ bool ftCo_800C3A14(ftCo_GObj* gobj);
/* 0C3B10 */ bool ftCo_800C3B10(ftCo_GObj* gobj);
/* 0C3BE8 */ void ftCo_800C3BE8(ftCo_GObj* gobj);
/* 0C3CC0 */ void ftCo_800C3CC0(ftCo_GObj* gobj);
/* 0C3D6C */ void ftCo_AirCatch_Anim(ftCo_GObj* gobj);
/* 0C4380 */ void ftCo_AirCatchHit_Anim(ftCo_GObj* gobj);
/* 0C4384 */ void ftCo_AirCatch_IASA(ftCo_GObj* gobj);
/* 0C4388 */ void ftCo_AirCatchHit_IASA(ftCo_GObj* gobj);
/* 0C438C */ void ftCo_AirCatch_Phys(ftCo_GObj* gobj);
/* 0C4438 */ void ftCo_AirCatchHit_Phys(ftCo_GObj* gobj);
/* 0C447C */ void ftCo_AirCatch_Coll(ftCo_GObj* gobj);

#endif
