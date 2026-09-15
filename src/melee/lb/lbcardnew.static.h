#ifndef MELEE_LB_LBCARDNEW_STATIC_H
#define MELEE_LB_LBCARDNEW_STATIC_H

#include <Runtime/platform.h>

#include <placeholder.h>

#include <dolphin/card.h>
#include <melee/lb/types.h>
#include <sysdolphin/baselib/hsd_3A94.h>

struct lb_80432A68_t {
    /* 0x000 */ UNK_T work_area;
    /* 0x004 */ UNK_T lib_area;
    /* 0x008 */ int chan;
    /* 0x00C */ UNK_T unk_C;
    /* 0x010 */ const char* unk_10;
    /* 0x014 */ char* comment;
    /* 0x018 */ void* banner;
    /* 0x01C */ void* icons;
    /* 0x020 */ lbCardNew_SnapshotEntry* snapshot_entries;
    /* 0x024 */ int* free_blocks;
    /* 0x028 */ int* free_files;
    /* 0x02C */ char x2C[2];
    /* 0x02C */ char x2E;
    /* 0x02C */ char x2F[4];
    /* 0x034 */ s32 unk_34;
    /* 0x038 */ struct lb_80432A68_38_t unk_38[9];
    /* 0x080 */ s32 unk_80;
    /* 0x084 */ s32 memsize;
    /* 0x088 */ s32 sectorsize;
    /* 0x08C */ s32 unused_bytes;
    /* 0x090 */ s32 unused_files;
    /* 0x094 */ CARDFileInfo file_info;
    /* 0x0A8 */ CardState card_state;
    /* 0x50C */ void (*x50C)(int);
    /* 0x510 */ struct CardTask {
        int x0;
        int x4;
        UNK_T x8;
        char* xC;
        char x10[0x20];
        u8 x18;
        char x19[7];
        u8 unk20[0x1C];
    } task_array[LbCardNewTaskArray_Max];
    /* 0x8AC */ int x8AC;
}; /* size = 0x8B0 */
ASSERT_SIZE(struct lb_80432A68_t, 0x8B0);
ASSERT_OFFSET(struct lb_80432A68_t, card_state, 0xA8);
ASSERT_OFFSET(struct lb_80432A68_t, x50C, 0x50C);

/* 432A68 */ static struct lb_80432A68_t lb_80432A68;

#endif
