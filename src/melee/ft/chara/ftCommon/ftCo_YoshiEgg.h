#ifndef GALE01_09D7E4
#define GALE01_09D7E4

#include <platform.h>
#include "ftCommon/forward.h"

#include "ft/ftcolltypes.h"

#include <placeholder.h>

#ifdef M2CTX
struct _m2c_stack_ftCo_800BBED4 {
    /* 0x00 */ char pad_0[0x2C];
    /* 0x2C */ struct UNK_SAMUS_S2 x2C;
    /* 0x54 */ Vec3 vec;
    /* 0x60 */ char pad_60[0x18];
}; /* size = 0x78 */
#endif

/* 09D7E4 */ /* static */ void ftCo_800BBC88(ftCo_GObj* gobj);
/* 0BBCC0 */ /* static */ void ftCo_800BBCC0(ftCo_GObj* gobj);
/* 09DA30 */ void ftCo_800BBED4(ftCo_GObj* arg0, ftCo_GObj* arg1);
/* 09DD0C */ void ftCo_YoshiEgg_Anim(ftCo_GObj* gobj);
/* 09DE60 */ void ftCo_YoshiEgg_IASA(ftCo_GObj* gobj);
/* 09DE64 */ void ftCo_YoshiEgg_Phys(ftCo_GObj* gobj);
/* 09DE9C */ void ftCo_YoshiEgg_Coll(ftCo_GObj* gobj);
/* 0BC388 */ void ftCo_800BC388(ftCo_GObj* gobj);
/* 0BC3AC */ void ftCo_800BC3AC(ftCo_GObj* gobj);
/* 0BC3D0 */ void ftCo_800BC3D0(ftCo_GObj* gobj);

#endif
