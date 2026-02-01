#ifndef __GALE01_2BAEEC
#define __GALE01_2BAEEC

#include "platform.h"

#include <dolphin/mtx.h>

struct _m2c_stack_it_802BCA30 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 vec;
    /* 0x24 */ Mtx mtx;
    /* 0x54 */ char pad_54[0x14];
}; /* size = 0x68 */
STATIC_ASSERT(sizeof(struct _m2c_stack_it_802BCA30) == 0x68);

Vec3 it_803B868C = { 0 };

#endif
