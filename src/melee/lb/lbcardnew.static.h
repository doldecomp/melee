
#include <placeholder.h>
#include <platform.h>

#include <dolphin/card.h>
#include <sysdolphin/baselib/cobj.h>
#include <melee/lb/types.h>

struct lb_80432A68_t {
    /* 0x000 */ UNK_T work_area;
    /* 0x004 */ UNK_T lib_area;
    /* 0x008 */ int chan;
    /* 0x00C */ UNK_T unk_C;
    /* 0x010 */ const char* unk_10;
    /* 0x014 */ const char* unk_14;
    /* 0x018 */ s32 unk_18;
    /* 0x01C */ s32 unk_1C;
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
    /* 0x0A8 */ s32 unk_A8;
    /* 0x098 */ u8 pad_AC[0xD0 - 0xAC]; /* maybe part of unk_80[0x123]? */
    /* 0x0A8 */ int xD0[9];
    /* 0x0A8 */ volatile int xF4[9];
    /* 0x098 */ u8
        pad_500[0x50C - 0xF4 - 9 * 4]; /* maybe part of unk_80[0x123]? */
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

/* 432A68 */ static struct lb_80432A68_t lb_80432A68;
