#ifndef GALE01_3A949C
#define GALE01_3A949C

#include <Runtime/platform.h>

#include <dolphin/card.h>

typedef enum {
    HSD_CardResult_Ok,
    HSD_CardResult_UnkN1,
    HSD_CardResult_UnkN2,
    HSD_CardResult_UnkN3,
    HSD_CardResult_UnkN4,
    HSD_CardResult_UnkN261 = -261,
} HSD_CardResult;

typedef enum {
    CardBanner_None,
    CardBanner_Small, ///< Indexed color, including its palette.
    CardBanner_Large, ///< RGB5A3 color.
} CardBannerFormat;

#define HSD_CARD_MAX_FILES 9

typedef struct {
    u8 banner_format;
    u8 unused;
    u8 icon_format[8];
    u8 icon_speed[8];
} CardIconInfo;
ASSERT_SIZE(CardIconInfo, 0x12);

/// One CARD file containing up to nine logical files. file_idx selects a
/// logical file; file_no is the SDK directory-entry number. Block positions
/// (phys) are relative to this CARD file, not hardware sector addresses.
typedef struct CardState {
    /* 0x00 */ u8* sector_buf;
    /* 0x04 */ s32 chan;
    /* 0x08 */ u32 sector_size;
    /* 0x0C */ CARDFileInfo file_info;
    /* 0x20 */ s32 file_no;

    /// Bytes of comment + banner + icons; the 0x30-byte digest follows.
    /* 0x24 */ u32 header_size;

    /* 0x28 */ int file_flags[HSD_CARD_MAX_FILES]; ///< @todo enum, not flags
    /* 0x4C */ int file_sizes[HSD_CARD_MAX_FILES];
    /* 0x70 */ u8* file_data[HSD_CARD_MAX_FILES];
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
ASSERT_SIZE(CardState, 0x464);

/// Completion callback: (file index or 0, result).
typedef void (*CardCallback)(int file_idx, int result);

/// Ring commands run by hsd_803AAA48; asynchronous CARD operations are
/// completed by hsd_803A949C. Names describe the observed operations; they
/// are not recovered original identifiers.
typedef enum CardCmdType {
    /* 0x00 */ CARD_CMD_NONE,
    /* 0x01 */ CARD_CMD_WRITE_BLOCK,
    /* 0x02 */ CARD_CMD_READ_BLOCK,
    /* 0x03 */ CARD_CMD_UNK_0x03, ///< No producer or handler identified.
    /* 0x04 */ CARD_CMD_CLEAR_BUF,
    /* 0x05 */ CARD_CMD_VERIFY_BLOCK,
    /// After queued verification, changes result 2 to 0 and otherwise sets
    /// result 1. Subsequent write commands skip their work when result is 1.
    /* 0x06 */ CARD_CMD_CHECK_VERIFIED,
    /* 0x07 */ CARD_CMD_CREATE_FILE,
    /* 0x08 */ CARD_CMD_SET_STATUS,
    /* 0x09 */ CARD_CMD_WRITE_HEADER,
    /* 0x0A */ CARD_CMD_VERIFY_HEADER,
    /* 0x0B */ CARD_CMD_READ_HEADER,
    /* 0x0C */ CARD_CMD_GET_STATUS,
    /// Reads one block's header into block_ids/block_seqs and merges its
    /// file table into file_flags/file_sizes.
    /* 0x0D */ CARD_CMD_SCAN_BLOCK,
    /// fn_803AD16C: mark stale copies negative; for file_flags 0 files also
    /// clear surplus copies and rebuild a missing or stale mirror.
    /* 0x0E */ CARD_CMD_REPAIR,
    /* 0x0F */ CARD_CMD_READ_SECTOR,
    /* 0x10 */ CARD_CMD_WRITE_SECTOR,
    /// Queues header validation and CARD_CMD_SCAN_BLOCK for each block,
    /// followed by CARD_CMD_REPAIR.
    /* 0x11 */ CARD_CMD_SCAN_FILE,
} CardCmdType;

/// CARD_CMD_WRITE_BLOCK: 0x20-byte block header followed by size bytes of
/// data; the remaining bytes in the block are cleared.
typedef struct CardWriteArgs {
    /* 0x00 */ s32 file_idx;
    /* 0x04 */ s32 phys;
    /* 0x08 */ s32 block_id;
    /* 0x0C */ s32 seq;
    /* 0x10 */ void* data;
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 size;
} CardWriteArgs;

/// CARD_CMD_READ_BLOCK, CARD_CMD_SCAN_BLOCK: phys 0 shares the last header
/// sector. For READ_BLOCK, a negative phys only loads sector_buf (no
/// checksum, no copy) so that the WRITE_HEADER after it keeps block 0's data.
typedef struct CardReadArgs {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 phys;
    /* 0x0C */ s32 xC;
    /* 0x10 */ void* data;
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 size;
} CardReadArgs;

/// CARD_CMD_VERIFY_BLOCK: compare the block header and data against
/// block_id/seq/data.
typedef struct CardVerifyArgs {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 block_id;
    /* 0x0C */ s32 seq;
    /* 0x10 */ void* data;
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 size;
} CardVerifyArgs;

/// CARD_CMD_READ_SECTOR, CARD_CMD_WRITE_SECTOR: transfer through sector_buf.
/// Reads verify the checksum; writes regenerate it and record block_id/seq
/// for phys.
typedef struct CardSectorArgs {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 phys;
    /* 0x08 */ s32 block_id;
    /* 0x0C */ s32 seq;
    /* 0x10 */ void* x10;
    /* 0x14 */ s32 offset;
} CardSectorArgs;

/// CARD_CMD_CLEAR_BUF: memset(data, 0, size).
typedef struct CardClearArgs {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ void* data;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 size;
} CardClearArgs;

/// CARD_CMD_CREATE_FILE
typedef struct CardCreateArgs {
    /* 0x00 */ const char* filename;
    /* 0x04 */ s32 size;
} CardCreateArgs;

/// CARD_CMD_WRITE_HEADER, CARD_CMD_VERIFY_HEADER: header sector index and
/// the banner/icons buffers (the comment comes from CardState).
typedef struct CardHeaderArgs {
    /* 0x00 */ s32 index;
    /* 0x04 */ void* banner;
    /* 0x08 */ void* icons;
} CardHeaderArgs;

/// CARD_CMD_READ_HEADER: destination buffers, any of which may be NULL.
typedef struct CardReadHeaderArgs {
    /* 0x00 */ s32 index;
    /* 0x04 */ void* comment;
    /* 0x08 */ void* banner;
    /* 0x0C */ void* icons;
} CardReadHeaderArgs;

/// CARD_CMD_GET_STATUS
typedef struct CardGetStatusArgs {
    /* 0x00 */ s32 file_no;
} CardGetStatusArgs;

/// One entry of the command ring hsd_804D1148.
typedef struct CardCmd {
    /* 0x00 */ CardCmdType type;
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
ASSERT_SIZE(CardCmd, 0x24);

/// Requests queued by hsd_3B27.c and started by fn_803AA790.
typedef enum CardRequestType {
    /* 0x00 */ CARD_REQ_NONE,
    /* 0x01 */ CARD_REQ_READ_FILE,
    /* 0x02 */ CARD_REQ_WRITE_FILE,
    /* 0x03 */ CARD_REQ_CREATE_FILE,
    /// Rewrites the comment/banner/icons header if it changed, then
    /// CARDSetStatus.
    /* 0x04 */ CARD_REQ_SET_STATUS,
    /* 0x05 */ CARD_REQ_OPEN_FILE,
    /// Reads the header sectors back into the caller's buffers.
    /* 0x06 */ CARD_REQ_READ_HEADER,
} CardRequestType;

/// CARD_REQ_READ_FILE, CARD_REQ_WRITE_FILE
typedef struct CardFileReqArgs {
    /* 0x00 */ s32 file_idx;
    /* 0x04 */ u8* buf;
} CardFileReqArgs;

/// CARD_REQ_CREATE_FILE
typedef struct CardCreateReqArgs {
    /* 0x00 */ const char* filename;
    /* 0x04 */ void* banner;
    /* 0x08 */ void* icons;
} CardCreateReqArgs;

/// CARD_REQ_SET_STATUS
typedef struct CardStatusReqArgs {
    /* 0x00 */ s32 x0;
    /* 0x04 */ void* banner;
    /* 0x08 */ void* icons;
} CardStatusReqArgs;

/// CARD_REQ_OPEN_FILE
typedef struct CardOpenReqArgs {
    /* 0x00 */ s32 file_no;
} CardOpenReqArgs;

/// CARD_REQ_READ_HEADER: destination buffers, any of which may be NULL.
typedef struct CardHeaderReqArgs {
    /* 0x00 */ void* comment;
    /* 0x04 */ void* banner;
    /* 0x08 */ void* icons;
} CardHeaderReqArgs;

/// One entry of the request queue hsd_804D2348. The state and buffers are
/// borrowed; they must remain valid while the request is pending or active.
typedef struct CardRequest {
    /* 0x00 */ CardRequestType type;
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
ASSERT_SIZE(CardRequest, 0x18);

/// What the queued commands complete; its callback runs when the ring
/// drains. Write suffixes refer to file_flags modes, not these tag values.
typedef enum CardActiveType {
    /* 0x00 */ CARD_ACTIVE_NONE,
    /* 0x01 */ CARD_ACTIVE_READ_FILE,
    /* 0x02 */ CARD_ACTIVE_WRITE_FILE, ///< file_flags 0

    /// Writes files with file_flags 1 or 2. On completion the older of two
    /// copies of each block is marked stale.
    /* 0x03 */ CARD_ACTIVE_WRITE_FILE_1_2,

    /* 0x04 */ CARD_ACTIVE_WRITE_FILE_3, ///< file_flags 3

    /// Set by fn_803ADE4C (open file) and fn_803B26CC (read header).
    /* 0x05 */ CARD_ACTIVE_OPEN_OR_READ_HEADER,

    /* 0x06 */ CARD_ACTIVE_CREATE_FILE,
    /* 0x07 */ CARD_ACTIVE_SET_STATUS,
} CardActiveType;

/// Drives queued requests and commands until idle or waiting for CARD I/O.
/// Async CARD calls start with interrupts disabled; the busy flag is set
/// after the call returns, before interrupts are restored. CARD completion
/// callbacks must therefore not run inline from those calls.
/* 3AAA48 */ void hsd_803AAA48(void);

/* 3AC340 */ int hsd_803AC340(CardIconInfo* icon_info);
/* 3AC3E0 */ void hsd_803AC3E0(CardState* state, int file_idx, int file_size,
                               int file_flags, u8* data);
/* 3B2374 */ void hsd_803B2374(void);
/* 3B24E4 */ void hsd_803B24E4(CardState* state, int chan, int sector_size,
                               void* work_buf);
/* 3B2550 */ int hsd_803B2550(CardState* state, const char* filename,
                              CardCallback callback);
/* 3B2674 */ int hsd_803B2674(CardState* state);

/// Queues a header read into the non-NULL destination buffers. Returns 0
/// when queued, not when complete; a negative return does not queue a
/// request or invoke the callback. The same return contract applies to
/// the create, status, read and write request functions below.
/* 3B27F4 */ int hsd_803B27F4(CardState* state, void* comment, void* banner,
                              void* icons, CardCallback callback);

/// Queues file creation. Copies 0x40 bytes from comment into state even if
/// the queue is full; filename, banner and icons are borrowed.
/* 3B286C */ int hsd_803B286C(CardState* state, const char* filename,
                              const char* comment, void* banner, void* icons,
                              CardCallback callback);
/// Queues a header/status update. Copies 0x40 bytes from comment into state
/// even if the queue is full; banner and icons are borrowed.
/* 3B2928 */ int hsd_803B2928(CardState* state, const char* comment,
                              void* banner, void* icons,
                              CardCallback callback);
/// Queues a logical-file read into the borrowed destination buffer.
/* 3B29D8 */ int hsd_803B29D8(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/// Queues a logical-file write from the borrowed source buffer.
/* 3B2A4C */ int hsd_803B2A4C(CardState* state, int file_idx, u8* buf,
                              CardCallback callback);
/* 3B2ADC */ int hsd_SetCardIconInfo(CardState* state,
                                     CardIconInfo* icon_info);
/* 3B2FA0 */ int hsd_803B2FA0(u8* data, int len);
/* 3B31CC */ int hsd_803B31CC(u8* data, int len);

#endif
