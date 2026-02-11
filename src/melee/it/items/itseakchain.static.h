#ifndef __GALE01_2BAEEC
#define __GALE01_2BAEEC

#include "platform.h"

#include "it/forward.h"

#include "it/itCharItems.h"

#include <dolphin/mtx.h>

struct _m2c_stack_it_802BCA30 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 vec;
    /* 0x24 */ Mtx mtx;
    /* 0x54 */ char pad_54[0x14];
};
STATIC_ASSERT(sizeof(struct _m2c_stack_it_802BCA30) == 0x68);

struct _m2c_stack_fn_802BB694 {
    /* 0x10 */ Mtx mtx0;
    char pad_0[0xC];
    /* 0x3C */ float z;
    /* 0x40 */ Vec3 vec;
    /* 0x4C */ char pad_4C[0x14];
};
STATIC_ASSERT(sizeof(struct _m2c_stack_fn_802BB694) == 0x60);

struct _m2c_stack_fn_802BB784 {
    char pad_0[0xC];
    Mtx mtx;
    char pad_x[0x4];
    /* 0x3C */ Vec3 vec;
    /* 0x4C */ char pad_4C[0x1C];
}; /* size = 0x68 */
STATIC_ASSERT(sizeof(struct _m2c_stack_fn_802BB784) == 0x68);

Vec3 it_803B868C = { 0 };

/* 2BC080 */ void it_802BC080(ItemLink*, Vec3*, Item*);
/* 2BCB88 */ int it_802BCB88(Item*, Vec3*);

#endif
