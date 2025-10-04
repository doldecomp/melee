#ifndef MELEE_MP_TYPES_H
#define MELEE_MP_TYPES_H

#include <placeholder.h>

#include "gr/forward.h"
#include "mp/forward.h" // IWYU pragma: export

#include <dolphin/mtx.h>

struct mpIsland_80458E88_t {
    /*  +0 */ mp_UnkStruct0* next;
    /*  +4 */ int x4;
    /*  +8 */ S32Vec3 x8;
    /* +14 */ S32Vec3 x14;
    /* +20 */ int x20;
    /* +24 */ short x24;
    /* +26 */ short x26;
    /* +28 */ short x28;
    /* +2A */ short x2A;
    /* +2C */ mp_UnkStruct3* ptr;
};

struct mp_UnkStruct0 {
    /*  +0 */ mp_UnkStruct0* next;
    /*  +4 */ u16 x4;
    /*  +6 */ u16 x6;
    /*  +8 */ Vec3 x8;
    /* +14 */ Vec3 x14;
    /* +20 */ int x20;
    /* +24 */ short x24;
    /* +26 */ short x26;
    /* +28 */ short x28;
    /* +2A */ short x2A;
    /* +2C */ mp_UnkStruct3* ptr;
};

struct mp_UnkStruct1 {
    /* +0 */ u16 x0;
    /* +2 */ u16 x2;
    /* +4 */ short x4;
    /* +6 */ short x6;
    /* +8 */ short x8;
    /* +A */ s16 xA;
    /* +C */ u8 pad_xC[0xE - 0xC];
    /* +E */ u16 xE;
};

struct mp_UnkStruct2 {
    /* +0 */ mp_UnkStruct1* x0;
    /* +4 */ u32 x4;
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

struct mp_UnkStruct6 {
    /* +0 */ short x0;
    /* +2 */ short x2;
    /* +4 */ short* x4;
};

struct mpLib_Point {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ Vec2 pos;
    /* 0x10 */ char pad_10[8]; /* maybe part of unk_C[3]? */
}; /* size = 0x18 */
STATIC_ASSERT(sizeof(struct mpLib_Point) == 0x18);

struct mpLib_804D64C0_t {
    /* 0x00 */ mpLib_804D64C0_t* next;
    /* 0x04 */ struct mpLib_804D64C0_x4_t {
        s16 x0;
        s16 x2;
        u8 pad_x4[0x10 - 0x4];
        s16 x10;
        s16 x12;
        u8 pad_x14[0x24 - 0x14];
        s16 x24;
        s16 x26;
    }* x4;
    /* 0x08 */ u32 flags;
    /* 0x0C */ s16 xC;
    /* 0x0E */ u8 xE : 1;
    /* 0x10 */ float x10;
    /* 0x14 */ float x14;
    /* 0x18 */ float x18;
    /* 0x1C */ float x1C;
    /* 0x20 */ char pad_20[0x4];
    /* 0x24 */ mpLib_Callback x24;
    /* 0x28 */ Ground* x28;
    /* 0x2C */ int unk_2C; /* inferred */
    /* 0x30 */ int unk_30; /* inferred */
}; /* size = 0x34 */
STATIC_ASSERT(sizeof(struct mpLib_804D64C0_t) == 0x34);

#endif
