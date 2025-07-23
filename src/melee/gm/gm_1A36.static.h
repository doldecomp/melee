/// @todo Move to C file
#ifndef __GALE01_1A3680
#define __GALE01_1A3680

#include <baselib/gobj.h>
#include <platform.h>

#include "baselib/forward.h"

#include "gm_unsplit.h" // IWYU pragma: keep

#include "baselib/cobj.h"

#include <baselib/archive.h>

#include <melee/gm/types.h>
#include <melee/sc/types.h>

typedef struct gm_controller_map gm_controller_map;
struct gm_controller_map {
    u64 button;
    u64 trigger;
    u64 repeat;
    u64 release;
    u64 unk;
    s32 x28;
    s32 x2C;
};

struct gm_803DBFD8_t {
    /* +0 */ char pad_0[0x10F0];
};
STATIC_ASSERT(sizeof(struct gm_803DBFD8_t) == 0x10F0);

/* 3DA788 */ static u32 gm_803DA788[64] = { 0 };

/* 3DBFD8 */ extern struct gm_803DBFD8_t gm_803DBFD8;
/* 3DD248 */ extern HSD_Archive gm_803DD248;
/* 3DD2C0 */ extern int gm_803DD2C0[74];

/// @todo The fact that mn_80229624() is passed 4 and thus indexes
/// gm_80479C30[4] may imply controller_union is intended to be part of the
/// array.
// .bss
/* 479C30 */ static gm_controller_map gm_80479C30[4];
/* 479CF0 */ static gm_controller_map controller_union;

/* 479D20 */ void (*gm_80479D20)(s32);
/* 479D24 */ s32 gm_80479D24;

#endif
