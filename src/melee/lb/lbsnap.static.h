#ifndef __GALE01_01D2BC
#define __GALE01_01D2BC

#include <platform.h>
#include <placeholder.h>

#include "lbsnap.h" // IWYU pragma: export

struct Unk80433380_48 {
    s32 unk0;
    char pad_4[0x408 - 0x4];
};

struct Unk80433380 {
    /* 0x00 */ s32 unk_0;        /* inferred */
    /* 0x04 */ char pad_4[0x44]; /* maybe part of unk_0[0x12]? */
    /* 0x48 */ struct Unk80433380_48* x48;
    /* 0x4C */ s32 x4C_cardState[2];
    /* 0x54 */ s32 x54_stateChanged[3];
}; /* size = 0x60 */
STATIC_ASSERT(sizeof(struct Unk80433380) == 0x60);

struct Unk80433380 lb_80433380;

#endif
