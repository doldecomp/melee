/// @todo Move to C file
#ifndef __GALE01_1A3680
#define __GALE01_1A3680

#include <baselib/gobj.h>
#include <platform.h>

#include "baselib/forward.h"

#include "gm_1601.h" // IWYU pragma: keep

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

/* 1A3F48 */ static void gm_801A3F48(MinorScene*);
/* 1A4014 */ static void gm_801A4014(MajorScene* scene);
/* 1A42B4 */ static u8 gm_801A42B4(void);
/* 1A42C4 */ static u8 gm_801A42C4(void);
/* 1A42E8 */ static void gm_801A42E8(s8 arg0);
/* 1A4310 */ static UNK_RET gm_800A4310(UNK_PARAMS);
/* 1A4624 */ static u8 gm_801A4624(void);
/* 1A4B88 */ static void gm_801A4B88(struct MinorSceneInfo*);
/* 1A4BB8 */ static s32 gm_801A4BB8(void);
/* 1A4BD4 */ static void gm_801A4BD4(void);
/* 1A4CE0 */ static MinorSceneHandler* gm_801A4CE0(u8);
/* 1A4D34 */ static void gm_801A4D34(void*, struct MinorSceneInfo*);
/* 1A50A0 */ static MinorSceneHandler* gm_801A50A0(void);
/* 1A50AC */ static MajorScene* gm_801A50AC(void);
/* 1A5244 */ static s8* gm_801A5244(void);
/* 1A5614 */ static void gm_801A5614(void);
/* 1ACC90 */ static void gm_801ACC90(void);
/* 1B6320 */ static UNK_T gm_801B6320(void);
/* 1B9FB8 */ static void fn_801B9FB8(void* arg0);
/* 1BBFE4 */ static void gm_801BBFE4(void);
/* 1BEFB0 */ static u8 gm_801BEFB0(void);
/* 1BEFC0 */ static void gm_801BEFC0(s8 arg0);
/* 1BEFD0 */ static u8 gm_801BEFD0(void);
/* 1BEFE0 */ static void gm_801BEFE0(s8 arg0);
/* 1BF684 */ static void gm_801BF684(s16 arg0);
/* 1BF694 */ static u8 gm_801BF694(void);
/* 2A3EF4 */ static void gm_801A3EF4(void);
/* 3DA788 */ static u32 gm_803DA788[64] = { 0 };
/* 3DA920 */ extern MinorSceneHandler gm_803DA920[];
/* 3DACA4 */ extern MajorScene gm_803DACA4;
/* 3DBFD8 */ extern struct gm_803DBFD8_t gm_803DBFD8;
/* 3DD0F0 */ extern HSD_CObjDesc gm_803DD0F0;
/* 3DD248 */ extern HSD_Archive gm_803DD248;
/* 3DD2C0 */ extern int gm_803DD2C0[74];
/* 479C30 */ static gm_controller_map gm_80479C30[4];
/* 479CF0 */ static gm_controller_map controller_union;
/* 479D20 */ void (*gm_80479D20)(s32);
/* 479D24 */ s32 gm_80479D24;
/* 479D30 */ static GameState gm_80479D30;

#endif
