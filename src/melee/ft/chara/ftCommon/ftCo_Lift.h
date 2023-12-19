#ifndef GALE01_0968E0
#define GALE01_0968E0

#include <platform.h>
#include "ftCommon/forward.h"

#include <placeholder.h>

#ifdef M2CTX
struct _m2c_stack_ftCo_800974C4 {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ Vec3 vec; /* inferred */
    /* 0x1C */ char pad_1C[4];
}; /* size = 0x20 */
struct _m2c_stack_ft_8009750C {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ Vec3 vec;
    /* 0x1C */ char pad_1C[0xC];
}; /* size = 0x28 */
#endif

/* 0968E0 */ void ftCo_LiftWait_Anim(ftCo_GObj* gobj);
/* 0968E4 */ void ftCo_LiftWait_IASA(ftCo_GObj* gobj);
/* 096934 */ void ftCo_LiftWait_Phys(ftCo_GObj* gobj);
/* 0969BC */ void ftCo_LiftWait_Coll(ftCo_GObj* gobj);
/* 096D9C */ void ftCo_80096D9C(ftCo_GObj* gobj);
/* 096E68 */ void ftCo_80096E68(ftCo_GObj* gobj);
/* 096EF8 */ bool ftCo_80096EF8(ftCo_GObj* gobj);
/* 096F48 */ void ftCo_80096F48(ftCo_GObj* gobj);
/* 096FD0 */ void ftCo_LiftWalk_Anim(ftCo_GObj* gobj);
/* 097074 */ void ftCo_LiftWalk_IASA(ftCo_GObj* gobj);
/* 097098 */ void ftCo_LiftWalk_Phys(ftCo_GObj* gobj);
/* 0970B8 */ void ftCo_LiftWalk_Coll(ftCo_GObj* gobj);
/* 0970E0 */ bool ftCo_800970E0(ftCo_GObj* gobj);
/* 097130 */ void ftCo_80097130(ftCo_GObj* gobj);
/* 0971B0 */ void ftCo_LiftTurn_Anim(ftCo_GObj* gobj);
/* 097458 */ void ftCo_LiftTurn_IASA(ftCo_GObj* gobj);
/* 09747C */ void ftCo_LiftTurn_Phys(ftCo_GObj* gobj);
/* 09749C */ void ftCo_LiftTurn_Coll(ftCo_GObj* gobj);
/* 0974C4 */ void ftCo_800974C4(ftCo_GObj* gobj);
/* 09750C */ void ftCo_8009750C(ftCo_GObj* gobj);

#endif
