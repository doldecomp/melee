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

extern char* ftCo_804D3B08; // = "jobj.h"
extern char* ftCo_804D3B10; // = "jobj"
extern char* ftCo_804D3B18; // = "jobj.h"
extern char* ftCo_804D3B20; // = "jobj"

/* 0968E0 */ void ftCo_LiftWait_Anim(ftCo_GObj* gobj);
/* 0968E4 */ void ftCo_LiftWait_IASA(ftCo_GObj* gobj);
/* 096934 */ void ftCo_LiftWait_Phys(ftCo_GObj* gobj);
/* 0969BC */ void ftCo_LiftWait_Coll(ftCo_GObj* gobj);
/* 096D9C */ void ftCo_80096D9C(ftCo_GObj* gobj);
/* 096E68 */ void ftCo_80096E68(ftCo_GObj* gobj);
/* 096EF8 */ bool ftCo_80096EF8(ftCo_GObj* gobj);
/* 096F48 */ void ftCo_80096F48(ftCo_GObj* gobj);

#endif
