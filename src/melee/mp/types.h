#ifndef MELEE_MP_TYPES_H
#define MELEE_MP_TYPES_H

#include <placeholder.h>

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

#endif
