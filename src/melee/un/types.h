#ifndef MELEE_UN_TYPES_H
#define MELEE_UN_TYPES_H

#include <platform.h>
#include "un/forward.h" // IWYU pragma: export

struct un_80302AB0_t {
    /*  +0 */ char pad_0[0x26];
    /* +26 */ u8 x26;
};

struct un_80302B10_t {
    /* +0 */ char pad_0[0x8];
    /* +8 */ float x8;
    /* +C */ float xC;
};

struct un_80302DF8_t {
    /* +0 */ char pad_0[0xC];
    /* +C */ int xC;
};

struct un_80304334_t {
    /* +0 */ char pad_0[1];
    /* +1 */ u8 x1;
};

#endif
