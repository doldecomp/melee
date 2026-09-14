#ifndef GALE01_3A949C
#define GALE01_3A949C

#include <Runtime/platform.h>

#include <placeholder.h>

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

/// Completion callback: (file index or 0, result).
typedef void (*CardCallback)(int, int);

/// Ring commands run by hsd_803AAA48 and completed by hsd_803A949C.
typedef enum CardCmdType {
    /* 0x00 */ CARD_CMD_NONE,
    /* 0x01 */ CARD_CMD_WRITE_BLOCK,
    /* 0x02 */ CARD_CMD_READ_BLOCK,
    /* 0x03 */ CARD_CMD_3,
    /* 0x04 */ CARD_CMD_CLEAR_BUF,
    /* 0x05 */ CARD_CMD_VERIFY_BLOCK,
    /// Turns a verify mismatch into "keep going" and a match into "skip the
    /// queued writes".
    /* 0x06 */ CARD_CMD_CHECK_VERIFIED,
    /* 0x07 */ CARD_CMD_CREATE_FILE,
    /* 0x08 */ CARD_CMD_SET_STATUS,
    /* 0x09 */ CARD_CMD_WRITE_HEADER,
    /* 0x0A */ CARD_CMD_VERIFY_HEADER,
    /* 0x0B */ CARD_CMD_READ_HEADER,
    /* 0x0C */ CARD_CMD_GET_STATUS,
    /// Reads one block's header into block_ids/block_seqs.
    /* 0x0D */ CARD_CMD_SCAN_BLOCK,
    /// fn_803AD16C: drop stale copies and re-home duplicated blocks.
    /* 0x0E */ CARD_CMD_REPAIR,
    /* 0x0F */ CARD_CMD_READ_SECTOR,
    /* 0x10 */ CARD_CMD_WRITE_SECTOR,
    /// Read the header blocks, scan every block, then repair.
    /* 0x11 */ CARD_CMD_MOUNT,
} CardCmdType;

/// CARD_CMD_WRITE_BLOCK: sector = 0x20-byte block header + size bytes of
/// data.
typedef struct CardWriteArgs {
    /* 0x08 */ s32 file_idx;
    /* 0x0C */ s32 phys;
    /* 0x10 */ s32 block_id;
    /* 0x14 */ s32 seq;
    /* 0x18 */ void* data;
    /* 0x1C */ s32 offset;
    /* 0x20 */ s32 size;
} CardWriteArgs;

/// CARD_CMD_READ_BLOCK, CARD_CMD_SCAN_BLOCK: phys 0 shares the last header
/// sector; a negative phys only checks the sector.
typedef struct CardReadArgs {
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 phys;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* data;
    /* 0x1C */ s32 offset;
    /* 0x20 */ s32 size;
} CardReadArgs;

/// CARD_CMD_VERIFY_BLOCK: compare the block header and data against
/// block_id/seq/data.
typedef struct CardVerifyArgs {
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 block_id;
    /* 0x14 */ s32 seq;
    /* 0x18 */ void* data;
    /* 0x1C */ s32 offset;
    /* 0x20 */ s32 size;
} CardVerifyArgs;

/// CARD_CMD_READ_SECTOR, CARD_CMD_WRITE_SECTOR: raw sector copy through
/// sector_buf; the write records block_id/seq for phys.
typedef struct CardSectorArgs {
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 phys;
    /* 0x10 */ s32 block_id;
    /* 0x14 */ s32 seq;
    /* 0x18 */ void* x18;
    /* 0x1C */ s32 offset;
} CardSectorArgs;

/// CARD_CMD_CLEAR_BUF: memset(data, 0, size).
typedef struct CardClearArgs {
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* data;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 size;
} CardClearArgs;

/// CARD_CMD_CREATE_FILE
typedef struct CardCreateArgs {
    /* 0x08 */ const char* filename;
    /* 0x0C */ s32 size;
} CardCreateArgs;

/// CARD_CMD_WRITE_HEADER, CARD_CMD_VERIFY_HEADER: header sector index and
/// the banner/icons buffers (the comment comes from CardState).
typedef struct CardHeaderArgs {
    /* 0x08 */ s32 index;
    /* 0x0C */ void* banner;
    /* 0x10 */ void* icons;
} CardHeaderArgs;

/// CARD_CMD_READ_HEADER: destination buffers, any of which may be NULL.
typedef struct CardReadHeaderArgs {
    /* 0x08 */ s32 index;
    /* 0x0C */ void* comment;
    /* 0x10 */ void* banner;
    /* 0x14 */ void* icons;
} CardReadHeaderArgs;

/// CARD_CMD_GET_STATUS
typedef struct CardGetStatusArgs {
    /* 0x08 */ s32 file_no;
} CardGetStatusArgs;

/// One entry of the command ring hsd_804D1148.
typedef struct CardCmd {
    /* 0x00 */ s32 type; ///< CardCmdType
    /* 0x04 */ CardState* state;
    union {
        /* 0x08 */ CardWriteArgs write;
        /* 0x08 */ CardReadArgs read;
        /* 0x08 */ CardVerifyArgs verify;
        /* 0x08 */ CardSectorArgs sector;
        /* 0x08 */ CardClearArgs clear;
        /* 0x08 */ CardCreateArgs create;
        /* 0x08 */ CardHeaderArgs header;
        /* 0x08 */ CardReadHeaderArgs read_header;
        /* 0x08 */ CardGetStatusArgs get_status;
    };
} CardCmd;

/// The 0x20-byte prefix of a CardCmd that fn_803AD16C builds its sector
/// commands in.
typedef struct CardSectorCmd {
    /* 0x00 */ s32 type;
    /* 0x04 */ CardState* state;
    /* 0x08 */ CardSectorArgs sector;
} CardSectorCmd;

/// Requests queued by hsd_3B27.c and started by fn_803AA790.
typedef enum CardRequestType {
    /* 0x00 */ CARD_REQ_NONE,
    /* 0x01 */ CARD_REQ_READ_FILE,
    /* 0x02 */ CARD_REQ_WRITE_FILE,
    /* 0x03 */ CARD_REQ_CREATE_FILE,
    /* 0x04 */ CARD_REQ_SET_STATUS,
    /* 0x05 */ CARD_REQ_OPEN_FILE,
    /// Reads the header sectors back into the caller's buffers.
    /* 0x06 */ CARD_REQ_READ_HEADER,
} CardRequestType;

/// CARD_REQ_READ_FILE, CARD_REQ_WRITE_FILE
typedef struct CardFileReqArgs {
    /* 0x08 */ s32 file_idx;
    /* 0x0C */ u8* buf;
} CardFileReqArgs;

/// CARD_REQ_CREATE_FILE
typedef struct CardCreateReqArgs {
    /* 0x08 */ const char* filename;
    /* 0x0C */ void* banner;
    /* 0x10 */ void* icons;
} CardCreateReqArgs;

/// CARD_REQ_SET_STATUS
typedef struct CardStatusReqArgs {
    /* 0x08 */ s32 x8;
    /* 0x0C */ void* banner;
    /* 0x10 */ void* icons;
} CardStatusReqArgs;

/// CARD_REQ_OPEN_FILE
typedef struct CardOpenReqArgs {
    /* 0x08 */ s32 file_no;
} CardOpenReqArgs;

/// CARD_REQ_READ_HEADER: destination buffers, any of which may be NULL.
typedef struct CardHeaderReqArgs {
    /* 0x08 */ const char* comment;
    /* 0x0C */ void* banner;
    /* 0x10 */ void* icons;
} CardHeaderReqArgs;

/// One entry of the request queue hsd_804D2348.
typedef struct CardRequest {
    /* 0x00 */ s32 type; ///< CardRequestType
    /* 0x04 */ CardState* state;
    union {
        /* 0x08 */ CardFileReqArgs file;
        /* 0x08 */ CardCreateReqArgs create;
        /* 0x08 */ CardStatusReqArgs status;
        /* 0x08 */ CardOpenReqArgs open;
        /* 0x08 */ CardHeaderReqArgs header;
    };
    /* 0x14 */ CardCallback callback;
} CardRequest;

/// What the queued commands complete; its callback runs when the ring
/// drains.
typedef enum CardActiveType {
    /* 0x00 */ CARD_ACTIVE_NONE,
    /* 0x01 */ CARD_ACTIVE_READ_FILE,
    /* 0x02 */ CARD_ACTIVE_WRITE_FILE,
    /// Writes of file_flags 1/2 files rebuild block_ids on completion.
    /* 0x03 */ CARD_ACTIVE_WRITE_FILE_1,
    /* 0x04 */ CARD_ACTIVE_WRITE_FILE_3,
    /// Also what fn_803B26CC's header read completes as.
    /* 0x05 */ CARD_ACTIVE_OPEN_FILE,
    /* 0x06 */ CARD_ACTIVE_CREATE_FILE,
    /* 0x07 */ CARD_ACTIVE_SET_STATUS,
} CardActiveType;

/// hsd_804D1138: the request the ring is currently completing.
typedef struct CardActiveRequest {
    /* 0x00 */ s32 type; ///< CardActiveType
    /* 0x04 */ CardState* state;
    /* 0x08 */ CardCallback callback;
    /* 0x0C */ s32 callback_arg;
} CardActiveRequest;

/// hsd_804D1138, hsd_804D1148 and hsd_804D2348 are contiguous; the ring
/// runner and the request builders address all three from hsd_804D1138.
typedef struct CardContext {
    /* 0x0000 */ CardActiveRequest active;
    /* 0x0010 */ CardCmd cmds[128];
    /* 0x1210 */ CardRequest requests[32];
} CardContext;

/* 3AA790 */ int fn_803AA790(void);
/* 3AAA48 */ void hsd_803AAA48(void);
/* 3AC168 */ int fn_803AC168(const CardCmd* cmd);
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
/* 3ACF30 */ s32 fn_803ACF30(CardState* state, void* comment, void* banner,
                             void* icons);
/* 3ACFC0 */ s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 block_id,
                             s32 seq_num, void* payload, s32 payload_size,
                             s32 file_idx);
/* 3AD16C */ s32 fn_803AD16C(CardState* state);
/* 3ADE4C */ int fn_803ADE4C(CardState* state, int file_no,
                             CardCallback callback);
/* 3ADF90 */ int fn_803ADF90(CardState* state, s32 file_idx, u8* buf,
                             int async, CardCallback callback);
/* 3AE7F8 */ int fn_803AE7F8(CardState* state, s32 file_idx, u8* buf,
                             int async, CardCallback callback);
/* 3AF3F0 */ int fn_803AF3F0(CardState* state, s32 file_idx, u8* buf,
                             int async, CardCallback callback);
/* 3B0120 */ int fn_803B0120(CardState* state, s32 file_idx, u8* buf,
                             int async, CardCallback callback);
/* 3B0E9C */ int fn_803B0E9C(CardState* state, void* banner, u8* icons,
                             int is_new, int async);
/* 3B1338 */ int fn_803B1338(CardState* state, int async);
/* 3B1F78 */ int fn_803B1F78(CardState* state, const char* filename,
                             void* banner, void* icons, CardCallback callback);
/* 3B21E8 */ int fn_803B21E8(CardState* state, void* banner, void* icons,
                             CardCallback callback);
/* 3B2374 */ void hsd_803B2374(void);
/* 3B24E4 */ void hsd_803B24E4(CardState* state, int chan, int sector_size,
                               void* work_buf);
/* 3B2550 */ int hsd_803B2550(CardState* state, const char* filename,
                              CardCallback callback);
/* 3B2674 */ int hsd_803B2674(CardState* state);
/* 3B26CC */ int fn_803B26CC(CardState* state, void* comment, void* banner,
                             void* icons, CardCallback callback);
/* 4D1138 */ extern CardActiveRequest hsd_804D1138;
/* 4D1148 */ extern CardCmd hsd_804D1148[128];
/* 4D2348 */ extern CardRequest hsd_804D2348[32];
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
