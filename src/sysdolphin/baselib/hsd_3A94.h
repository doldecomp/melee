#ifndef GALE01_3A949C
#define GALE01_3A949C

#include <Runtime/platform.h>

#include <dolphin/card.h>

typedef struct {
    /* 0x3B0 */ u8 banner_format;
    /* 0x3B1 */ u8 pad_3B1[1];
    /* 0x3B2 */ u8 icon_format[8];
    /* 0x3BA */ u8 icon_speed[8];
} CardIconInfo;

typedef struct CardState {
    /* 0x00 */ u8* sector_buf;
    /* 0x04 */ s32 chan;
    /* 0x08 */ u32 sector_size;
    /* 0x0C */ CARDFileInfo file_info;
    /* 0x20 */ s32 file_no;
    /// Bytes of comment + banner + icons; the 0x30-byte digest follows.
    /* 0x24 */ u32 header_size;
    /* 0x28 */ int file_flags[9];
    /* 0x4C */ int file_sizes[9];
    /* 0x70 */ u8* file_data[9];
    /* 0x94 */ u8 pad_94[0xDC];
    /// Block id stored in each physical block; negated = stale copy,
    /// -0x7FFF = free.
    /* 0x170 */ s32 block_ids[64];
    /* 0x270 */ s32 block_seqs[64];
    /* 0x370 */ char comment[64];
    /* 0x3B0 */ CardIconInfo icon_info;
    /* 0x3C4 */ CARDStat stat;
    /* 0x430 */ u8 digest[0x30];
    /// Physical blocks 1..num_blocks each fill a sector; block 0 shares the
    /// last header sector.
    /* 0x460 */ s32 num_blocks;
} CardState;

/* 3AAA48 */ void hsd_803AAA48(void);
/* 3AC340 */ int hsd_803AC340(void* icon_info);
/* 3AC3E0 */ void hsd_803AC3E0(struct CardState* file_desc, int file_idx,
                               int file_size, int file_flags, u8* data);
/* 3AC340 */
/* 3AC3E0 */
/* 3B2374 */ void hsd_803B2374(void);
/* 3B24E4 */ void hsd_803B24E4(CardState* ctx, int chan, int sector_size,
                               void* work_buf);
/* 3B2550 */ int hsd_803B2550(CardState* state, const char* filename,
                              void (*callback)(int, int));
/* 3B2674 */ s32 hsd_803B2674(CardState* state);
/* 4D1138 */ extern u8 hsd_804D1138[0x10];
/* 4D7990 */ extern s32 hsd_804D7990;
/* 4D7994 */ extern s32 hsd_804D7994;
/* 4D79A0 */ extern u8* hsd_804D79A0;
/* 4D79A4 */ extern u8* hsd_804D79A4;
/* 4D79A8 */ extern s32 hsd_804D79A8;
/* 4D79AC */ extern s32 hsd_804D79AC;
/* 4D79B0 */ extern u8 hsd_804D79B0[8];
/* 4D79B8 */ extern u8* hsd_804D79B8;
/* 4D79BC */ extern u8* hsd_804D79BC;
/* 4D79C0 */ extern s32 hsd_804D79C0;
/* 4D79C4 */ extern s32 hsd_804D79C4;
/* 4D79C8 */ extern u8 hsd_804D79C8;

#endif
