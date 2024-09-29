#ifndef __GALE01_225374
#define __GALE01_225374

#include "db_2253.h" // IWYU pragma: export

struct lbl_8049FAA0_t {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ s32 unk_8;     /* inferred */
    /* 0x0C */ char pad_C[8]; /* maybe part of unk_8[3]? */
    /* 0x14 */ s32 unk_14;
    char pad_18[0x8];
    /* 0x20:0 */ u8 x20_b0 : 1;
    /* 0x20:1 */ u8 x20_b1 : 1;
    /* 0x20:2 */ u8 x20_b2 : 1;
}; /* size = 0x18 */

/* 453004 */ extern UNK_T cm_80453004;
/* 49FAA0 */ static struct lbl_8049FAA0_t lbl_8049FAA0;
/* 4D6B50 */ static IntVec2 lbl_804D6B50;
/* 4D6B5C */ static s8 lbl_804D6B5C;
/* 4D6B8C */ static UnkFlagStruct lbl_804D6B8C;

#endif
