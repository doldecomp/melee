#ifndef GALE01_2599EC
#define GALE01_2599EC

#include <placeholder.h>

#include "platform.h"

struct mnStageSel_803F06D0_t {
    char pad_0[0xB];
    u8 xB;
    char pad_C[0x1C - 0xC];
};
STATIC_ASSERT(sizeof(struct mnStageSel_803F06D0_t) == 0x1C);

static struct mnStageSel_803F06D0_t
    mnStageSel_803F06D0[0x378 / sizeof(struct mnStageSel_803F06D0_t)];

#endif
