#ifndef __GALE01_2BAEEC
#define __GALE01_2BAEEC

#include "platform.h"

#include "it/itCharItems.h"
#include "it/types.h"

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

struct _m2c_stack_fn_802BB574 {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ Mtx mtx;
    /* 0x40 */ Vec3 vec;
    /* 0x4C */ char pad_4C[0x1C];
};
STATIC_ASSERT(sizeof(struct _m2c_stack_fn_802BB574) == 0x68);

struct _m2c_stack_fn_802BB44C {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ Mtx mtx;
    /* 0x40 */ Vec3 vec;
    /* 0x4C */ char pad_4C[0x1C];
};
STATIC_ASSERT(sizeof(struct _m2c_stack_fn_802BB44C) == 0x68);

struct _m2c_stack_it_802BCB88 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Mtx mtx;
    /* 0x48 */ Vec3 delta;
    /* 0x54 */ Vec3 pos0;
    /* 0x60 */ Vec3 pos1;
    /* 0x6C */ Vec3 pos2;
    /* 0x78 */ char pad_78[0x28];
}; /* size = 0xA0 */
STATIC_ASSERT(sizeof(struct _m2c_stack_it_802BCB88) == 0xA0);

struct _m2c_stack_it_802BCFC4 {
    /* 0x00 */ char pad_0[0x1C];
    /* 0x1C */ Mtx mtx;        /* inferred */
    /* 0x4C */ char pad_4C[8]; /* maybe part of sp48[3]? */
    /* 0x54 */ Vec3 pos;       /* inferred */
    /* 0x60 */ char pad_60[0x20];
}; /* size = 0x80 */
STATIC_ASSERT(sizeof(struct _m2c_stack_it_802BCFC4) == 0x80);

struct _m2c_stack_it_802BB290 {
    /* 0x00 */ char pad_0[0x40];
    /* 0x40 */ SpawnItem spawn;
    char pad[0xA8 - 0x8C];
}; /* size = 0xA8 */
STATIC_ASSERT(sizeof(struct _m2c_stack_it_802BB290) == 0xA8);

Vec3 it_803B8680 = { 0 };
Vec3 it_803B868C = { 0 };

/* 2BC080 */ void it_802BC080(ItemLink*, Vec3*, Item*);
/* 2BCB88 */ void it_802BCB88(Item*, Vec3*);

#endif
