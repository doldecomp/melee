#ifndef MELEE_MP_TYPES_H
#define MELEE_MP_TYPES_H

#include <placeholder.h>

#include "gr/forward.h"
#include "mp/forward.h" // IWYU pragma: export

struct mp_UnkStruct0 {
    /*  +0 */ mp_UnkStruct0* next;
    /*  +4 */ int x4;
    /*  +8 */ float x8;
    /*  +C */ float xC;
    /* +10 */ int x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ int x1C;
    /* +20 */ int x20;
    /* +24 */ short x24;
    /* +26 */ short x26;
    /* +28 */ short x28;
    /* +2A */ short x2A;
    /* +2C */ mp_UnkStruct3* ptr;
};

struct mp_UnkStruct1 {
    /* +0 */ int x0;
    /* +4 */ short x4;
    /* +6 */ short x6;
};

struct mp_UnkStruct2 {
    /* +0 */ mp_UnkStruct1* x0;
    /* +4 */ int x4;
};

struct mpisland {
    /*  +0 */ int x0[8];
    /* +20 */ int x20[8];
};

struct mp_UnkStruct3 {
    int x0;
    int x4;
    int xC;
};

struct mp_UnkStruct5 {
    /*  +0 */ u8 x0[0x4];
    /*  +4 */ ushort x4;
    /*  +6 */ ushort x6;
    /*  +8 */ int x8;
    /*  +C */ int xC;
    /* +10 */ int x10;
    /* +14 */ int x14;
    /* +18 */ int x18;
    /* +1C */ int x1C;
    /* +20 */ u8 x20[0x28 - 0x20];
    /* +28 */ short x28;
    /* +2A */ short x2A;
    /* +2C */ ushort x2C;
    /* +30 */ int x30;
    /* +34 */ int x34;
    /* +38 */ int x38;
    /* +3C */ int x3C;
};

struct mp_UnkStruct6 {
    /* +0 */ short x0;
    /* +2 */ short x2;
    /* +4 */ short* x4;
};

struct mpLib_804D64B8_t {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ f32 unk_8;      /* inferred */
    /* 0x0C */ f32 unk_C;      /* inferred */
    /* 0x10 */ char pad_10[8]; /* maybe part of unk_C[3]? */
}; /* size = 0x18 */
STATIC_ASSERT(sizeof(struct mpLib_804D64B8_t) == 0x18);

struct mpLib_804D64C0_t {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ void (*x24)(void*, int);
    /* 0x28 */ Ground* x28;
    /* 0x2C */ int unk_2C; /* inferred */
    /* 0x30 */ int unk_30; /* inferred */
}; /* size = 0x34 */
STATIC_ASSERT(sizeof(struct mpLib_804D64C0_t) == 0x34);

struct mp_UnkStruct7 {
    /* +0 */ struct mp_UnkStruct7* next;
    /* +4 */ s32 x4;
    /* +8 */ s32 x8;
    /* +C */ u8 xC[0x10 - 0xC];
    /* +10 */ float x10;
    /* +14 */ float x14;
    /* +18 */ float x18;
    /* +1C */ float x1C;
};

#endif
