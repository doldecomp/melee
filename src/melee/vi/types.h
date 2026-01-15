#ifndef MELEE_VI_TYPES_H
#define MELEE_VI_TYPES_H

#include <platform.h>

/// Video input data passed to OnEnter callbacks
struct un_804D7004_t {
    /* 0x00 */ u8 char_index;
    /* 0x01 */ u8 costume_id;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ u8 pad_4[8];
}; /* size = 0xC */
STATIC_ASSERT(sizeof(struct un_804D7004_t) == 0xC);

#endif
