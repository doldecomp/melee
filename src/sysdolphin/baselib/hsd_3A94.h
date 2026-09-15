#ifndef GALE01_3A949C
#define GALE01_3A949C

#include <Runtime/platform.h>

#include <dolphin/card.h>

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
    /* 0x370 */ u8 comment[0x40];
    /* 0x3B0 */ u8 banner_format;
    /* 0x3B1 */ u8 pad_3B1[1];
    /* 0x3B2 */ u8 icon_format[8];
    /* 0x3BA */ u8 icon_speed[8];
    /* 0x3C2 */ u8 pad_3C2[2];
    /* 0x3C4 */ CARDStat stat;
    /* 0x430 */ u8 digest[0x30];
    /// Physical blocks 1..num_blocks each fill a sector; block 0 shares the
    /// last header sector.
    /* 0x460 */ s32 num_blocks;
} CardState;

/* 3AA790 */ s32 fn_803AA790(void);
/* 3AAA48 */ void hsd_803AAA48(void);
/* 3AC168 */ s32 fn_803AC168(s32* cmd_buf);
/* 3AC258 */ s32 fn_803AC258(CardState* state, s32 block_idx);
/* 3AC2A4 */ s32 fn_803AC2A4(CardState* state);
/* 3AC2D4 */ void fn_803AC2D4(void);
/* 3AC2E0 */ void fn_803AC2E0(void);
/* 3AC334 */ void fn_803AC334(void);
/* 3AC340 */ int hsd_803AC340(void* icon_info);
/* 3AC3E0 */ void hsd_803AC3E0(CardState* state, int file_idx, int file_size,
                               int file_flags, u8* data);
/* 3AC3F8 */ void fn_803AC3F8(void* card_state, u8* data, s32 file_idx);
/* 3AC558 */ void hsd_803AC558(CardState* state, u8* data);
/* 3AC634 */ u32 fn_803AC634(CardState* state, s32 file_idx);
/* 3AC6B8 */ s32 fn_803AC6B8(CardState* state, s32 file_idx);
/* 3AC7DC */ s32 fn_803AC7DC(CardState*);
/* 3ACBE8 */ s32 fn_803ACBE8(CardState* state, s32 block_idx);
/* 3ACC0C */ s32 fn_803ACC0C(CardState* state, s32 block_idx, s32 block_id,
                             s32 seq_num, void* expected_data, s32 data_size);
/* 3ACD58 */ s32 fn_803ACD58(CardState* state, void* banner, void* icons);
/* 3ACF30 */ s32 fn_803ACF30(CardState* state, s32 comment, s32 banner,
                             s32 icons);
/* 3ACFC0 */ s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 block_id,
                             s32 seq_num, void* payload, s32 payload_size,
                             s32 file_idx);
/* 3AD16C */ s32 fn_803AD16C(CardState* state);
/* 3ADE4C */ s32 fn_803ADE4C(s32 state, s32 file_no, s32 callback);
/* 3ADF90 */ s32 fn_803ADF90(CardState* state, s32 file_idx, u8* buf,
                             s32 async, void (*callback)(s32, s32));
/* 3AE7F8 */ s32 fn_803AE7F8(CardState* state, s32 file_idx, s32 buf,
                             s32 async, s32 callback);
/* 3AF3F0 */ s32 fn_803AF3F0(CardState* state, s32 file_idx, s32 buf,
                             s32 async, s32 callback);
/* 3B0120 */ s32 fn_803B0120(CardState* state, s32 file_idx, s32 buf,
                             s32 async, s32 callback);
/* 3B0E9C */ s32 fn_803B0E9C(CardState* state, s32 banner, s32 icons,
                             s32 is_new, s32 async);
/* 3B1338 */ s32 fn_803B1338(CardState* state, s32 async);
/* 3B1F78 */ s32 fn_803B1F78(CardState* state, s32 filename, s32 banner,
                             s32 icons, s32 callback);
/* 3B21E8 */ s32 fn_803B21E8(s32 state, s32 banner, s32 icons, s32 callback);
/* 3B2374 */ void hsd_803B2374(void);
/* 3B24E4 */ void hsd_803B24E4(s32* ctx, int chan, int sector_size,
                               void* work_buf);
/* 3B2550 */ int hsd_803B2550(s32* state, const char* filename,
                              void (*callback)(int, int));
/* 3B2674 */ s32 hsd_803B2674(CardState* state);
/* 3B26CC */ s32 fn_803B26CC(CardState* state, s32 comment, s32 banner,
                             s32 icons, void (*callback)(s32, s32));
/* 4D1138 */ extern u8 hsd_804D1138[0x10];
/* 4D2E70 */ extern u8 hsd_804D2E70[2084];
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
