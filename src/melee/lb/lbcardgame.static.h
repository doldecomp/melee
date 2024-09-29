#ifndef __GALE01_019880
#define __GALE01_019880

#include <platform.h>
#include <placeholder.h>

#include "lbcardgame.h" // IWYU pragma: export

struct lb_80433318_t {
    /* +0 */ UNK_T x0;
    /* +4 */ UNK_T x4;
    /* +8 */ int x8;
    /* +C */ u8 _C[0x5C];
};
STATIC_ASSERT(sizeof(struct lb_80433318_t) == 0x68);

struct lb_804329F0_t {
    /* 0x00 */ char pad_0[8];
    /* 0x08 */ s32 unk_8; /* inferred */
    /* 0x0C */ s32 unk_C; /* inferred */
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ char pad_14[4];
}; /* size = 0x18 */

struct lb_80432A68_38_t {
    /* 0x0 */ s32 unk_0;
    /* 0x4 */ s32 unk_4;
};
STATIC_ASSERT(sizeof(struct lb_80432A68_38_t) == 0x8);

struct lb_80432A68_t {
    /* 0x000 */ s32 unk_0; /* inferred */
    /* 0x004 */ s32 unk_4; /* inferred */
    /* 0x008 */ s32 unk_8;
    /* 0x00C */ s32 unk_C;
    /* 0x010 */ s32 unk_10;
    /* 0x014 */ s32 unk_14;
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ s32 unk_1C;
    /* 0x020 */ s32 unk_20;
    /* 0x024 */ s32 unk_24;
    /* 0x028 */ s32 unk_28;
    /* 0x02C */ char pad_2C[8]; /* maybe part of unk_28[3]? */
    /* 0x034 */ s32 unk_34;
    /* 0x038 */ struct lb_80432A68_38_t unk_38[8];
    /* 0x078 */ char pad_78[8];
    /* 0x080 */ s32 unk_80;
    /* 0x084 */ char pad_84[0x488]; /* maybe part of unk_80[0x123]? */
    /* 0x50C */ s32 unk_50C;
    /* 0x510 */ s32 unk_510;
    /* 0x514 */ char pad_514[0x50]; /* maybe part of unk_510[0x15]? */
    /* 0x564 */ s32 unk_564;
    /* 0x568 */ char pad_568[0x50]; /* maybe part of unk_564[0x15]? */
    /* 0x5B8 */ s32 unk_5B8;
    /* 0x5BC */ char pad_5BC[0x50]; /* maybe part of unk_5B8[0x15]? */
    /* 0x60C */ s32 unk_60C;
    /* 0x610 */ char pad_610[0x50]; /* maybe part of unk_60C[0x15]? */
    /* 0x660 */ s32 unk_660;
    /* 0x664 */ char pad_664[0x50]; /* maybe part of unk_660[0x15]? */
    /* 0x6B4 */ s32 unk_6B4;
    /* 0x6B8 */ char pad_6B8[0x50]; /* maybe part of unk_6B4[0x15]? */
    /* 0x708 */ s32 unk_708;
    /* 0x70C */ char pad_70C[0x50]; /* maybe part of unk_708[0x15]? */
    /* 0x75C */ s32 unk_75C;
    /* 0x760 */ char pad_760[0x150]; /* maybe part of unk_75C[0x55]? */
}; /* size = 0x8B0 */
STATIC_ASSERT(sizeof(struct lb_80432A68_t) == 0x8B0);

/* 4329F0 */ static struct lb_804329F0_t lb_804329F0[5];
/* 432A68 */ static struct lb_80432A68_t lb_80432A68;
/* 433318 */ static struct lb_80433318_t lb_80433318;

#endif
