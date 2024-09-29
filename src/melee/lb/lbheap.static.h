#ifndef __GALE01_0158D0
#define __GALE01_0158D0

#include <placeholder.h>

#include "lbheap.h" // IWYU pragma: export

struct lbHeap_80431FA0_x10_t {
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
};
STATIC_ASSERT(sizeof(struct lbHeap_80431FA0_x10_t) == 0x1C);

struct lbHeap_80431FA0_t {
    /* 0x00 */ void* unk_0; /* inferred */
    /* 0x04 */ void* unk_4; /* inferred */
    /* 0x08 */ u32 unk_8;   /* inferred */
    /* 0x0C */ u32 unk_C;   /* inferred */
    /* 0x10 */ struct lbHeap_80431FA0_x10_t unk_10[6];
}; /* size = 0xB8 */
STATIC_ASSERT(sizeof(struct lbHeap_80431FA0_t) == 0xB8);

/* 431FA0 */ static struct lbHeap_80431FA0_t lbHeap_80431FA0;

#endif
