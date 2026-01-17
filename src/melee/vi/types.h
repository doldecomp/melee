#ifndef MELEE_VI_TYPES_H
#define MELEE_VI_TYPES_H

#include <platform.h>

#include "vi/forward.h"

struct ViCharaDesc {
    /* 0x0 */ u8 p1_char_index;
    /* 0x1 */ u8 p1_costume_index;
    /* 0x2 */ u8 p2_char_index;
    /* 0x3 */ u8 p2_costume_index;
    /* 0x4 */ int spawn_count;
    /* 0x8 */ int unk;
};

struct un_804D7004_t {
    char pad_0[0xC];
}; /* size = 0xC */
STATIC_ASSERT(sizeof(struct un_804D7004_t) == 0xC);

#endif
