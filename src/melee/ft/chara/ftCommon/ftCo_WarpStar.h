#ifndef GALE01_0C4724
#define GALE01_0C4724

#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>

struct _m2c_stack_ftCo_800C4C60 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ float sp18; /* inferred */
    /* 0x1C */ Vec3 vec;   /* inferred */
    /* 0x28 */ char pad_28[0x10];
}; /* size = 0x38 */

/* 0C4724 */ void ftCo_800C4724(ftCo_GObj* gobj);
/* 0C4900 */ void ftCo_WarpStarJump_Anim(ftCo_GObj* gobj);
/* 0C4964 */ void ftCo_WarpStarJump_IASA(ftCo_GObj* gobj);
/* 0C4968 */ void ftCo_WarpStarJump_Phys(ftCo_GObj* gobj);
/* 0C4A14 */ void ftCo_WarpStarJump_Coll(ftCo_GObj* gobj);
/* 0C4A18 */ void ftCo_WarpStarJump_Cam(ftCo_GObj* gobj);
/* 0C4BA4 */ void ftCo_WarpStarFall_Anim(ftCo_GObj* gobj);
/* 0C4BA8 */ void ftCo_WarpStarFall_IASA(ftCo_GObj* gobj);
/* 0C4BAC */ void ftCo_WarpStarFall_Phys(ftCo_GObj* gobj);
/* 0C4C30 */ void ftCo_WarpStarFall_Coll(ftCo_GObj* gobj);
/* 0C4E2C */ void ftCo_WarpStarFall_Cam(ftCo_GObj* gobj);

#endif
