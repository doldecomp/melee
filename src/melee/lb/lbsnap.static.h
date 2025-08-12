#ifndef __GALE01_01D2BC
#define __GALE01_01D2BC

#include "lbsnap.h" // IWYU pragma: export

#include <placeholder.h>
#include <platform.h>

#include "it/types.h"

struct Unk80433380_48_10 {
    unsigned int unk0;
    s16 unk4;
    u16 unk6;
};
STATIC_ASSERT(sizeof(struct Unk80433380_48_10) == 0x8);

struct Unk80433380_48 {
    int unk0;
    int num;
    int unk8;
    int unkC;
    struct Unk80433380_48_10 unk10[0x7F];
};
STATIC_ASSERT(sizeof(struct Unk80433380_48) == 0x408);

struct Unk80433380_0 {
    s32 x0;
    u16 x4;
    u16 x6;
    u8 x8;
    s32 xC;
    u16 x10;
    struct it_8026C47C_arg0_t x14;
    s32 x34;
    char x38[4];
};

struct Unk80433380 {
    /* 0x00 */ struct Unk80433380_0* x0;
    /* 0x04 */ char x4_string[0x40];
    /* 0x44 */ int* x44_LbMcSnap_MemSnapIconData;
    /* 0x48 */ struct Unk80433380_48* x48;
    /* 0x4C */ int x4C_cardState[2];
    /* 0x54 */ int x54_stateChanged[3];
}; /* size = 0x60 */
STATIC_ASSERT(sizeof(struct Unk80433380) == 0x60);

struct Unk803BACC8 {
    char pad0[0x14];
    int x14;
    char pad18[0x1C - 0x18];
    struct Unk80433380_0* x1C;
};

static struct Unk80433380 lbSnap_80433380;
static struct Unk803BACC8 lbSnap_803BACC8 = {
    { 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3 }, 0, { 0, 0, 0, 3 }, (void*) -1
};

#endif
