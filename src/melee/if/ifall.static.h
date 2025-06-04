#ifndef __GALE01_2F3394
#define __GALE01_2F3394

#include <placeholder.h>

#include <baselib/forward.h>

#include "ifall.h" // IWYU pragma: export

struct ifAll_804A0FD8_x18_t {
    char pad_0[0xC];
};
STATIC_ASSERT(sizeof(struct ifAll_804A0FD8_x18_t) == 0xC);

struct ifAll_804A0FD8_t {
    /* 0x00 */ HSD_GObj* gobj;
    /* 0x04 */ HSD_GObj* gobj_2;
    /* 0x08 */ char pad_8[4];
    /* 0x0C */ UNK_T xC;
    /* 0x10 */ char pad_10[0x8];
    /* 0x18 */ struct ifAll_804A0FD8_x18_t x18[2];
};

/* 4D6D58 */ static u8 ifAll_804D6D58;
/* 4D6D5C */ static HSD_Archive* ifAll_804D6D5C;
/* 4A0FD8 */ static struct ifAll_804A0FD8_t ifAll_804A0FD8;

#endif
