#ifndef __GALE01_0158D0
#define __GALE01_0158D0

#include <placeholder.h>

#include "lbheap.h" // IWYU pragma: export
#include "lbmemory.h"

struct lbHeap_80431FA0_x10_t {
    /* 10 */ s32 unk_10;
    /* 14 */ Handle* unk_14;
    /* 18 */ s32 unk_18;
    /* 1C */ u32 unk_1C;
    /* 20 */ s32 unk_20;
    /* 24 */ s32 unk_24;
    /* 28 */ int status;
};
STATIC_ASSERT(sizeof(struct lbHeap_80431FA0_x10_t) == 0x1C);

struct lbHeap_80431FA0_t {
    /* 0x00 */ void* unk_0; /* inferred */
    /* 0x04 */ void* unk_4; /* inferred */
    /* 0x08 */ unsigned int unk_8;   /* inferred */
    /* 0x0C */ unsigned int unk_C;   /* inferred */
    /* 0x10 */ struct lbHeap_80431FA0_x10_t unk_10[6];
}; /* size = 0xB8 */
STATIC_ASSERT(sizeof(struct lbHeap_80431FA0_t) == 0xB8);

/* 431FA0 */ static struct lbHeap_80431FA0_t lbHeap_80431FA0;

#endif
