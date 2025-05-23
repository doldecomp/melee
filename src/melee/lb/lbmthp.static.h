#ifndef __GALE01_01E8F8
#define __GALE01_01E8F8

#include "lbmthp.h" // IWYU pragma: export

struct lbl_804333E0_t {
    /* 0x000 */ char pad_0[0x84];
    /* 0x084 */ s32 unk_84;        /* inferred */
    /* 0x088 */ char pad_88[0x80]; /* maybe part of unk_84[0x21]? */
    /* 0x108 */ s32 unk_108;
    /* 0x10C */ s32 unk_10C;
    /* 0x110 */ s32 unk_110;
    /* 0x114 */ char pad_114[0x20]; /* maybe part of unk_110[9]? */
    /* 0x134 */ s32 unk_134;
    /* 0x138 */ char pad_138[0xC]; /* maybe part of unk_134[4]? */
    /* 0x144 */ s32 unk_144;
    /* 0x148 */ s32 unk_148;
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ char pad_150[0x88]; /* maybe part of unk_14C[0x23]? */
}; /* size = 0x1D8 */
STATIC_ASSERT(sizeof(struct lbl_804333E0_t) == 0x1D8);

/* 4333E0 */ static struct lbl_804333E0_t lbl_804333E0;
/* 4D7CC0 */ static float lb_804D7CC0;

#endif
