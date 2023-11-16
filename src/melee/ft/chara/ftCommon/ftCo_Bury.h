#ifndef GALE01_0C0874
#define GALE01_0C0874

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "lb/forward.h"

#include "lb/lbcollision.h"

#include <placeholder.h>

struct _m2c_stack_ftCo_800C08A0 {
    /* 0x000 */ char pad_0[0x1C];
    /* 0x01C */ HitCapsule hit; /* inferred */
    /* 0x154 */ char pad_154[0x24];
}; /* size = 0x178 */

/* 0C1D38 */ bool ftCo_800C1D38(ftCo_GObj* gobj);
/* 0C0874 */ void ftCo_800C0874(ftCo_GObj* gobj, UNK_T arg1,
                                ftCommon_BuryType arg2);
/* 0C08A0 */ void ftCo_800C08A0(ftCo_GObj* gobj, int arg1,
                                lb_UnkAnimStruct* arg2,
                                ftCommon_BuryType arg3);
/* 0C09B4 */ void ftCo_800C09B4(ftCo_GObj* gobj);
/* 0C0A28 */ bool ftCo_800C0A28(ftCo_GObj* gobj, UNK_T arg1,
                                ftCommon_BuryType arg2);
/* 0C0A98 */ void ftCo_800C0A98(ftCo_GObj* gobj);
/* 0C0B20 */ void ftCo_800C0B20(ftCo_GObj* gobj);
/* 0C0C88 */ bool ftCo_800C0C88(enum_t);
/* 0C0CB8 */ bool ftCo_800C0CB8(ftCo_GObj* gobj);
/* 0C0D0C */ void ftCo_800C0D0C(ftCo_GObj* gobj);
/* 0C0F34 */ void ftCo_Bury_Anim(ftCo_GObj* gobj);
/* 0C0FC8 */ void ftCo_Bury_IASA(ftCo_GObj* gobj);
/* 0C0FCC */ void ftCo_800C0FCC(HSD_GObj* arg0, ftCo_GObj* arg1);
/* 0C1194 */ void ftCo_Bury_Phys(ftCo_GObj* gobj);
/* 0C11E4 */ void ftCo_Bury_Coll(ftCo_GObj* gobj);
/* 0C124C */ void ftCo_800C124C(ftCo_GObj* gobj);

#endif
