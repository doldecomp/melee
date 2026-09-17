#include "card.h"

#include <placeholder.h>
#include <string.h>

#include "hsd_3B2B.h"
#include <dolphin/card.h>
#include <dolphin/os.h>

#define BANNER_SMALL 0xE00
#define BANNER_LARGE 0x1800

/// 0x20-byte header at the start of every data block on the card.
typedef struct CardBlockHeader {
    /* 0x00 */ u8 digest[0x10];
    /* 0x10 */ u8 id_hi;
    /* 0x11 */ u8 id_lo;
    /* 0x12 */ u8 seq;
    /* 0x13 */ u8 file_table[0x0C];
    /* 0x1F */ u8 pad_1F[1];
    /* 0x20 */ u8 data[];
} CardBlockHeader;

/// fn_803B1338 stages its commands in 0x28-byte stack slots.
typedef struct CardCmdBuf {
    /* 0x00 */ CardCmd cmd;
    /* 0x24 */ char pad_24[4];
} CardCmdBuf;
ASSERT_SIZE(CardCmdBuf, 0x28);

/// hsd_804D1138: the request the ring is currently completing.
typedef struct CardActiveRequest {
    /* 0x00 */ CardActiveType type;
    /* 0x04 */ CardState* state;
    /* 0x08 */ CardCallback callback;
    /* 0x0C */ s32 callback_arg;
} CardActiveRequest;
ASSERT_SIZE(CardActiveRequest, 0x10);

/* 3AA790 */ static int fn_803AA790(void);
/// Copies the command into the ring; pointed-to state and buffers are not
/// copied and must remain valid until execution completes. Returns 0 when
/// queued, or -265 when the ring is full.
/* 3AC168 */ static int fn_803AC168(const CardCmd* cmd);
/* 3AC258 */ static s32 fn_803AC258(CardState* state, s32 block_idx);
/* 3AC2A4 */ static s32 fn_803AC2A4(CardState* state);
/* 3AC2D4 */ static void fn_803AC2D4(void);
/* 3AC2E0 */ static void fn_803AC2E0(void);
/* 3AC334 */ static void fn_803AC334(void);
/* 3AC3F8 */ static void fn_803AC3F8(CardState* state, u8* data, s32 file_idx);
/* 3AC558 */ static void hsd_803AC558(CardState* state, u8* data);
/* 3AC634 */ static u32 fn_803AC634(CardState* state, s32 file_idx);
/* 3AC6B8 */ static s32 fn_803AC6B8(CardState* state, s32 file_idx);
/* 3AC7DC */ static s32 fn_803AC7DC(CardState*);
/* 3ACBE8 */ static s32 fn_803ACBE8(CardState* state, s32 block_idx);
/* 3ACC0C */ static s32 fn_803ACC0C(CardState* state, s32 block_idx,
                                    s32 block_id, s32 seq_num,
                                    void* expected_data, s32 data_size);
/* 3ACD58 */ static s32 fn_803ACD58(CardState* state, void* banner,
                                    void* icons);
/* 3ACF30 */ static s32 fn_803ACF30(CardState* state, void* comment,
                                    void* banner, void* icons);
/* 3ACFC0 */ static s32 fn_803ACFC0(CardState* state, s32 block_idx,
                                    s32 block_id, s32 seq_num, void* payload,
                                    s32 payload_size, s32 file_idx);
/* 3AD16C */ static s32 fn_803AD16C(CardState* state);
/* 3ADE4C */ static int fn_803ADE4C(CardState* state, int file_no,
                                    CardCallback callback);
/* 3ADF90 */ static int fn_803ADF90(CardState* state, s32 file_idx, u8* buf,
                                    int async, CardCallback callback);
/* 3AE7F8 */ static int fn_803AE7F8(CardState* state, s32 file_idx, u8* buf,
                                    bool async, CardCallback callback);
/* 3AF3F0 */ static int fn_803AF3F0(CardState* state, s32 file_idx, u8* buf,
                                    bool async, CardCallback callback);
/* 3B0120 */ static int fn_803B0120(CardState* state, s32 file_idx, u8* buf,
                                    bool async, CardCallback callback);
/* 3B0E9C */ static int fn_803B0E9C(CardState* state, void* banner, u8* icons,
                                    int is_new, int async);
/* 3B1338 */ static int fn_803B1338(CardState* state, int async);
/* 3B1F78 */ static int fn_803B1F78(CardState* state, const char* filename,
                                    void* banner, void* icons,
                                    CardCallback callback);
/* 3B21E8 */ static int fn_803B21E8(CardState* state, void* banner,
                                    void* icons, CardCallback callback);
/* 3B26CC */ static int fn_803B26CC(CardState* state, void* comment,
                                    void* banner, void* icons,
                                    CardCallback callback);

/* 3A949C */ static void hsd_803A949C(s32 chan, s32 card_result);
/* 3ACB74 */ static s32 fn_803ACB74(s32 seq_a, s32 seq_b);

/// @todo these don't go here
/// @{
/* 4D79C8 */ u8 hsd_804D79C8;
/* 4D79C4 */ s32 hsd_804D79C4;
/* 4D79C0 */ s32 hsd_804D79C0;
/* 4D79BC */ u8* hsd_804D79BC;
/* 4D79B8 */ u8* hsd_804D79B8;
/* 4D79B0 */ u8 hsd_804D79B0[8];
/* 4D79AC */ s32 hsd_804D79AC;
/* 4D79A8 */ s32 hsd_804D79A8;
/* 4D79A4 */ u8* hsd_804D79A4;
/* 4D79A0 */ u8* hsd_804D79A0;
/// @}

/// Command ring head (next command to run).
/* 4D7980 */ static volatile s32 curr_head;

/// Command ring tail (next free slot).
/* 4D7984 */ static volatile s32 curr_tail;

/// Result of the request in progress: negative = CARD error, 1 = data
/// verified so the queued writes are skipped, 2 = verify mismatch.
/* 4D7988 */ static volatile s32 curr_result;

/* 4D798C */ static s32 hsd_804D798C;
/* 4D7990 */ static s32 hsd_804D7990;
/* 4D7994 */ static s32 hsd_804D7994;

/// Ring tail saved before queueing a request; -1 when nothing to roll back.
/* 4D7998 */ static int hsd_804D7998;

/// 0 = running commands, 1 = async CARD call in flight, 2 = idle.
/* 4D799C */ static enum {
    running,
    running_async,
    idle,
} hsd_804D799C;

/* 4D1138 */ static CardActiveRequest active_requests;
/* 4D1148 */ static CardCmd commands[128];
/* 4D2348 */ static CardRequest requests[32];

static int checkOpen(CardState* state)
{
    int i;
    int result;

    for (i = 0; i < 10; i++) {
        result = CARDClose(&state->file_info);
        if (result != -1) {
            break;
        }
    }

    return result;
}

void hsd_803A949C(s32 chan, s32 card_result)
{
    CardState* state;
    u8* block;
    s32 result;
    s32 banner_size;
    s32 remaining;
    s32 banner_size11;
    s32 hdr_offset;
    s32 hdr_offset13;
    s32 icons_offset;
    s32 icons_start;
    s32 phys;
    s32 i;

    if (hsd_804D799C != 1) {
        return;
    }

    state = commands[curr_head].state;

    switch (commands[curr_head].type) {
    case CARD_CMD_READ_BLOCK:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
            break;
        }

        if (commands[curr_head].read.phys < 0) {
            if (checkOpen(state) < 0) {
                curr_result = card_result;
            }
            break;
        }

        if (commands[curr_head].read.phys == 0) {
            hdr_offset = (state->header_size + 0x30) % state->sector_size;
            if (commands[curr_head].read.size > 0) {
                if (hsd_803B31CC(state->sector_buf + hdr_offset,
                                 state->sector_size - hdr_offset) < 0)
                {
                    checkOpen(state);
                    curr_result = -0x105;
                    break;
                }
                if (commands[curr_head].read.data != NULL) {
                    CardBlockHeader* src =
                        (CardBlockHeader*) (hdr_offset +
                                            (u32) state->sector_buf);
                    memcpy(commands[curr_head].read.data, src->data,
                           commands[curr_head].read.size);
                }
            }
            result = checkOpen(state);
        } else {
            if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
                checkOpen(state);
                curr_result = -0x105;
                break;
            }
            if (commands[curr_head].read.size > 0 &&
                commands[curr_head].read.data != NULL)
            {
                memcpy(commands[curr_head].read.data,
                       ((CardBlockHeader*) state->sector_buf)->data,
                       commands[curr_head].read.size);
            }
            result = checkOpen(state);
        }
        if (result < 0) {
            curr_result = result;
        }
        break;

    case CARD_CMD_READ_SECTOR:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
        } else if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
            checkOpen(state);
            curr_result = -0x105;
        } else {
            result = checkOpen(state);
            if (result < 0) {
                curr_result = result;
            }
        }
        break;

    case CARD_CMD_VERIFY_BLOCK:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
            break;
        }

        if (commands[curr_head].verify.block_id == 0) {
            if (commands[curr_head].verify.size <= 0) {
                result = checkOpen(state);
                if (result < 0) {
                    curr_result = result;
                }
                break;
            }

            hdr_offset = (state->header_size + 0x30) % state->sector_size;
            if (hsd_803B31CC(state->sector_buf + hdr_offset,
                             state->sector_size - hdr_offset) < 0)
            {
                checkOpen(state);
                curr_result = 2;
                break;
            }
            result = checkOpen(state);
            if (result < 0) {
                curr_result = result;
                break;
            }
            result = curr_head;
            block = state->sector_buf + hdr_offset;
            result = commands[result].verify.block_id;
            if (((block[0x10] << 8) | block[0x11]) != result) {
                curr_result = 2;
            } else if ((s32) block[0x12] != commands[curr_head].verify.seq) {
                curr_result = 2;
            } else if (commands[curr_head].verify.size > 0 &&
                       memcmp(commands[curr_head].verify.data, (block += 0x20),
                              commands[curr_head].verify.size) != 0)
            {
                curr_result = 2;
            }
        } else {
            CardBlockHeader* header;
            if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
                checkOpen(state);
                curr_result = 2;
                break;
            }
            result = checkOpen(state);
            if (result < 0) {
                curr_result = result;
                break;
            }
            result = (((CardBlockHeader*) state->sector_buf)->id_hi << 8) |
                     ((CardBlockHeader*) state->sector_buf)->id_lo;
            header = (CardBlockHeader*) state->sector_buf;
            if (result != commands[curr_head].verify.block_id) {
                curr_result = 2;
            } else if ((s32) header->seq != commands[curr_head].verify.seq) {
                curr_result = 2;
            } else if (commands[curr_head].verify.size > 0 &&
                       memcmp(commands[curr_head].verify.data, header->data,
                              commands[curr_head].verify.size) != 0)
            {
                curr_result = 2;
            }
        }
        break;

    case CARD_CMD_VERIFY_HEADER:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
            break;
        }

        result = checkOpen(state);
        if (result < 0) {
            curr_result = result;
            break;
        }

        switch (state->icon_info.banner_format) {
        case CardBanner_Large:
            banner_size = BANNER_LARGE;
            break;
        case CardBanner_Small:
            banner_size = BANNER_SMALL;
            break;
        default:
            banner_size = 0;
            break;
        }

        if (commands[curr_head].header.index == 0) {
            if (memcmp(state->sector_buf, state->comment, 0x40) != 0) {
                curr_result = 2;
                break;
            }
            if (banner_size > 0 &&
                memcmp(state->sector_buf + 0x40,
                       commands[curr_head].header.banner, banner_size) != 0)
            {
                curr_result = 2;
                break;
            }
            icons_start = banner_size + 0x40;
            if (state->header_size > state->sector_size) {
                if (memcmp(state->sector_buf + icons_start,
                           commands[curr_head].header.icons,
                           state->sector_size - icons_start) != 0)
                {
                    curr_result = 2;
                    break;
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->sector_size,
                    &commands[curr_head]
                         .state
                         ->digest[commands[curr_head].header.index * 0x10]);
            } else if (memcmp(state->sector_buf + icons_start,
                              commands[curr_head].header.icons,
                              state->header_size - icons_start) != 0)
            {
                curr_result = 2;
            } else {
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->header_size,
                    &commands[curr_head]
                         .state
                         ->digest[commands[curr_head].header.index * 0x10]);
                if (memcmp(state->sector_buf + state->header_size,
                           commands[curr_head].state->digest, 0x30) != 0)
                {
                    curr_result = 2;
                }
            }
        } else {
            icons_offset =
                (state->sector_size * commands[curr_head].header.index) -
                0x40 - banner_size;
            remaining = state->header_size -
                        state->sector_size * commands[curr_head].header.index;
            if ((u32) remaining > state->sector_size) {
                if (memcmp(state->sector_buf,
                           (u8*) commands[curr_head].header.icons +
                               icons_offset,
                           state->sector_size) != 0)
                {
                    curr_result = 2;
                    break;
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->sector_size,
                    &commands[curr_head]
                         .state
                         ->digest[commands[curr_head].header.index * 0x10]);
            } else if (memcmp(state->sector_buf,
                              (u8*) commands[curr_head].header.icons +
                                  icons_offset,
                              remaining) != 0)
            {
                curr_result = 2;
            } else {
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf, remaining,
                    &commands[curr_head]
                         .state
                         ->digest[commands[curr_head].header.index * 0x10]);
                if (memcmp(state->sector_buf + remaining,
                           commands[curr_head].state->digest, 0x30) != 0)
                {
                    curr_result = 2;
                }
            }
        }
        break;

    case CARD_CMD_READ_HEADER:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
            break;
        }

        result = checkOpen(state);
        if (result < 0) {
            curr_result = result;
            break;
        }

        switch (state->icon_info.banner_format) {
        case CardBanner_Large:
            banner_size11 = BANNER_LARGE;
            break;
        case CardBanner_Small:
            banner_size11 = BANNER_SMALL;
            break;
        default:
            banner_size11 = 0;
            break;
        }

        if (commands[curr_head].read_header.index == 0) {
            if (commands[curr_head].read_header.comment != NULL) {
                memcpy(commands[curr_head].read_header.comment,
                       state->sector_buf, 0x40);
            }
            if (banner_size11 > 0 &&
                commands[curr_head].read_header.banner != NULL)
            {
                memcpy(commands[curr_head].read_header.banner,
                       state->sector_buf + 0x40, banner_size11);
            }
            icons_start = banner_size11 + 0x40;
            if (state->header_size > state->sector_size) {
                if (commands[curr_head].read_header.icons != NULL) {
                    memcpy(commands[curr_head].read_header.icons,
                           state->sector_buf + icons_start,
                           state->sector_size - icons_start);
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->sector_size,
                    &commands[curr_head]
                         .state->digest[commands[curr_head].read_header.index *
                                        0x10]);
            } else {
                if (commands[curr_head].read_header.icons != NULL) {
                    memcpy(commands[curr_head].read_header.icons,
                           state->sector_buf + icons_start,
                           state->header_size - icons_start);
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->header_size,
                    &commands[curr_head]
                         .state->digest[commands[curr_head].read_header.index *
                                        0x10]);
                if (memcmp(state->sector_buf + state->header_size,
                           commands[curr_head].state->digest, 0x30) != 0)
                {
                    curr_result = -0x107;
                }
            }
        } else {
            icons_offset =
                (state->sector_size * commands[curr_head].read_header.index) -
                0x40 - banner_size11;
            chan = state->header_size -
                   state->sector_size * commands[curr_head].read_header.index;
            if ((u32) chan > state->sector_size) {
                if (commands[curr_head].read_header.icons != NULL) {
                    memcpy((u8*) commands[curr_head].read_header.icons +
                               icons_offset,
                           state->sector_buf, state->sector_size);
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf,
                    commands[curr_head].state->sector_size,
                    &commands[curr_head]
                         .state->digest[commands[curr_head].read_header.index *
                                        0x10]);
            } else {
                if (commands[curr_head].read_header.icons != NULL) {
                    memcpy((u8*) commands[curr_head].read_header.icons +
                               icons_offset,
                           state->sector_buf, chan);
                }
                hsd_803B2B20(
                    commands[curr_head].state->sector_buf, chan,
                    &commands[curr_head]
                         .state->digest[commands[curr_head].read_header.index *
                                        0x10]);
                if (memcmp(state->sector_buf + chan,
                           commands[curr_head].state->digest, 0x30) != 0)
                {
                    curr_result = -0x107;
                }
            }
        }
        break;

    case CARD_CMD_WRITE_BLOCK:
        if (card_result != 0) {
            state->block_ids[commands[curr_head].write.phys] = -0x7FFF;
            state->block_seqs[commands[curr_head].write.phys] = 0;
            checkOpen(state);
            curr_result = card_result;
            break;
        }
        if (commands[curr_head].write.block_id != 0xFFFF) {
            state->block_ids[commands[curr_head].write.phys] =
                commands[curr_head].write.block_id;
            state->block_seqs[commands[curr_head].write.phys] =
                commands[curr_head].write.seq;
        } else {
            state->block_ids[commands[curr_head].write.phys] = -0x7FFF;
            state->block_seqs[commands[curr_head].write.phys] = 0;
        }
        result = checkOpen(state);
        if (result < 0) {
            curr_result = result;
        }
        break;

    case CARD_CMD_WRITE_SECTOR:
        if (card_result != 0) {
            state->block_ids[commands[curr_head].sector.phys] = -0x7FFF;
            state->block_seqs[commands[curr_head].sector.phys] = 0;
            checkOpen(state);
            curr_result = card_result;
            break;
        }
        if (commands[curr_head].sector.block_id != 0xFFFF) {
            state->block_ids[commands[curr_head].sector.phys] =
                commands[curr_head].sector.block_id;
            state->block_seqs[commands[curr_head].sector.phys] =
                commands[curr_head].sector.seq;
        } else {
            state->block_ids[commands[curr_head].sector.phys] = -0x7FFF;
            state->block_seqs[commands[curr_head].sector.phys] = 0;
        }
        result = checkOpen(state);
        if (result < 0) {
            curr_result = result;
        }
        break;

    case CARD_CMD_CREATE_FILE:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
            break;
        }
        i = 0;
        result = state->file_info.fileNo;
        do {
            if (result != -1) {
                break;
            }
            i++;
        } while (i < 10);
        state->file_no = result;
        if (state->file_no < 0) {
            curr_result = state->file_no;
        }
        result = checkOpen(state);
        if (result < 0) {
            curr_result = result;
        }
        break;

    case CARD_CMD_SET_STATUS:
        if (card_result != 0) {
            curr_result = card_result;
        }
        break;

    case CARD_CMD_WRITE_HEADER:
        if (card_result != 0) {
            checkOpen(state);
            curr_result = card_result;
        } else {
            result = checkOpen(state);
            if (result < 0) {
                curr_result = result;
            }
        }
        break;

    case CARD_CMD_SCAN_BLOCK:
        phys = commands[curr_head].read.phys;
        checkOpen(state);
        if (card_result != 0) {
            state->block_ids[phys] = -0x7FFF;
            state->block_seqs[phys] = 0;
            break;
        }

        if (phys == 0) {
            hdr_offset13 = (state->header_size + 0x30) % state->sector_size;
            if (hsd_803B31CC(state->sector_buf + hdr_offset13,
                             state->sector_size - hdr_offset13) < 0)
            {
                state->block_ids[0] = -0x7FFF;
                state->block_seqs[0] = 0;
                break;
            }
            state->block_ids[phys] =
                state->sector_buf[hdr_offset13 + 0x11] +
                (state->sector_buf[hdr_offset13 + 0x10] << 8);
            if (state->block_ids[phys] != 0) {
                state->block_ids[phys] = -0x7FFF;
                state->block_seqs[phys] = 0;
            } else {
                state->block_seqs[phys] =
                    state->sector_buf[hdr_offset13 + 0x12];
                {
                    CardBlockHeader* src13 =
                        (CardBlockHeader*) (hdr_offset13 +
                                            (u32) state->sector_buf);
                    hsd_803AC558(state, src13->file_table);
                }
            }
        } else {
            if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
                state->block_ids[phys] = -0x7FFF;
                state->block_seqs[phys] = 0;
                break;
            }
            state->block_ids[phys] =
                state->sector_buf[0x11] + (state->sector_buf[0x10] << 8);
            if (state->block_ids[phys] < 0 ||
                state->block_ids[phys] > state->num_blocks)
            {
                state->block_ids[phys] = -0x7FFF;
                state->block_seqs[phys] = 0;
            } else {
                state->block_seqs[phys] = state->sector_buf[0x12];
                hsd_803AC558(state, state->sector_buf + 0x13);
            }
        }
        break;
    default:
        break;
    }

    commands[curr_head].type = CARD_CMD_NONE;
    hsd_804D799C = 0;
    curr_head = (curr_head + 1) % 128;
}

int fn_803AA790(void)
{
    CardRequest* entry;
    s32 result;
    CardState* state;

    entry = &requests[hsd_804D7990];
    state = entry->state;
    hsd_804D7990 = (hsd_804D7990 + 1) % 32;

    switch (entry->type) {
    case CARD_REQ_READ_FILE:
        result = fn_803ADF90(entry->state, entry->file.file_idx,
                             entry->file.buf, 1, entry->callback);
        if (result < 0 && entry->callback != NULL) {
            entry->callback(entry->file.file_idx, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    case CARD_REQ_WRITE_FILE:
        switch (state->file_flags[entry->file.file_idx]) {
        case 0:
            result = fn_803AE7F8(entry->state, entry->file.file_idx,
                                 entry->file.buf, 1, entry->callback);
            break;
        case 1:
        case 2:
            result = fn_803AF3F0(entry->state, entry->file.file_idx,
                                 entry->file.buf, 1, entry->callback);
            break;
        case 3:
            result = fn_803B0120(entry->state, entry->file.file_idx,
                                 entry->file.buf, 1, entry->callback);
            break;
        default:
            result = -0x101;
            break;
        }
        if (result < 0 && entry->callback != NULL) {
            entry->callback(entry->file.file_idx, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    case CARD_REQ_CREATE_FILE:
        result = fn_803B1F78(entry->state, entry->create.filename,
                             entry->create.banner, entry->create.icons,
                             entry->callback);
        if (result < 0 && entry->callback != NULL) {
            entry->callback(0, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    case CARD_REQ_SET_STATUS:
        result = fn_803B21E8(entry->state, entry->status.banner,
                             entry->status.icons, entry->callback);
        if (result < 0 && entry->callback != NULL) {
            entry->callback(0, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    case CARD_REQ_OPEN_FILE:
        result = fn_803ADE4C(state, entry->open.file_no, entry->callback);
        if (result < 0 && entry->callback != NULL) {
            entry->callback(0, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    case CARD_REQ_READ_HEADER:
        result =
            fn_803B26CC(state, entry->header.comment, entry->header.banner,
                        entry->header.icons, entry->callback);
        if (result < 0 && entry->callback != NULL) {
            entry->callback(0, result);
        }
        entry->type = CARD_REQ_NONE;
        return result;
    default:
        return -0x101;
    }
}

static inline s32 retryCardFastOpen(s32 chan, s32 file_no,
                                    CARDFileInfo* file_info)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDFastOpen(chan, file_no, file_info);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardReadAsync(CARDFileInfo* file_info, void* buffer,
                                     s32 length, s32 offset,
                                     CARDCallback callback)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDReadAsync(file_info, buffer, length, offset, callback);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardWriteAsync(CARDFileInfo* file_info, void* buffer,
                                      s32 length, s32 offset,
                                      CARDCallback callback)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDWriteAsync(file_info, buffer, length, offset, callback);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardClose(CARDFileInfo* file_info)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDClose(file_info);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardCreateAsync(s32 chan, const char* filename,
                                       s32 size, CARDFileInfo* file_info,
                                       CARDCallback callback)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDCreateAsync(chan, filename, size, file_info, callback);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardGetStatus(s32 chan, s32 file_no, CARDStat* stat)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDGetStatus(chan, file_no, stat);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline s32 retryCardSetStatusAsync(s32 chan, s32 file_no,
                                          CARDStat* stat,
                                          CARDCallback callback)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDSetStatusAsync(chan, file_no, stat, callback);
        if (result != -1) {
            break;
        }
    }

    return result;
}

static inline int setupCardIcons(const CardCmd* cmd)
{
    u32 bit;
    s32 k;

    k = (bit = 0);
    while (k < 8 && cmd->state->icon_info.icon_speed[k] != 0) {
        cmd->state->stat.iconFormat =
            (cmd->state->stat.iconFormat & ~(CARD_STAT_ICON_MASK << bit)) |
            (cmd->state->icon_info.icon_format[k] << bit);
        cmd->state->stat.iconSpeed =
            (cmd->state->stat.iconSpeed & ~(CARD_STAT_SPEED_MASK << bit)) |
            (cmd->state->icon_info.icon_speed[k++] << bit);
        bit += 2;
    }
    return k;
}

static inline void unpackCardStat(const CardCmd* cmd, CARDStat* stat)
{
    s32 k;

    cmd->state->icon_info.banner_format = stat->bannerFormat & 3;
    for (k = 0; k < 8; k++) {
        cmd->state->icon_info.icon_format[k] =
            (stat->iconFormat >> (2 * k)) & CARD_STAT_ICON_MASK;
        cmd->state->icon_info.icon_speed[k] =
            (stat->iconSpeed >> (2 * k)) & CARD_STAT_SPEED_MASK;
    }
    cmd->state->header_size = hsd_803AC340(&cmd->state->icon_info);
    {
        u32 used = cmd->state->header_size + cmd->state->sector_size;
        used += 0x2F;
        cmd->state->num_blocks = stat->length / cmd->state->sector_size -
                                 used / cmd->state->sector_size;
    }
}

static void rollbackCardCommands(s32 snap)
{
    s32 saved = snap;

    while (saved != curr_tail) {
        commands[saved].type = CARD_CMD_NONE;
        saved = (saved + 1) % 128;
    }
    curr_tail = snap;
}

static inline void initHeaderBlockCommand(CardCmd* buf, CardState* state,
                                          u32 block, void* comment,
                                          void* banner, void* icons)
{
    buf->type = CARD_CMD_READ_HEADER;
    buf->state = state;
    buf->read_header.index = block;
    buf->read_header.comment = comment;
    buf->read_header.banner = banner;
    buf->read_header.icons = icons;
}

static inline s32 queueHeaderBlock(CardState* state, u32 block, void* comment,
                                   void* banner, void* icons)
{
    CardCmd buf;

    initHeaderBlockCommand(&buf, state, block, comment, banner, icons);
    return fn_803AC168(&buf);
}

static inline s32 queueHeaderBlocks(CardState* state, void* comment,
                                    void* banner, void* icons)
{
    u32 i;
    int result;

    for (i = 0; i < (0x2F + state->header_size + state->sector_size) /
                        state->sector_size;
         i++)
    {
        result = queueHeaderBlock(state, i, comment, banner, icons);
        if (result < 0) {
            return result;
        }
    }
    return 0;
}

void hsd_803AAA48(void)
{
    s32 result;
    s32 chan;
    while (true) {
        CardState** state_ptr = &active_requests.state;
        CardCmd* cmd;
        s32 type;
        BOOL intr = OSDisableInterrupts();
        BOOL intr2;
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        OSRestoreInterrupts(intr);
        if (busy) {
            return;
        }

        if (curr_result < 0) {
            while (commands[curr_head].type != CARD_CMD_NONE) {
                commands[curr_head].type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
            }
        }

        type = (cmd = &commands[curr_head])->type;

        switch ((u32) type) {
        case CARD_CMD_NONE:
            if (active_requests.type != CARD_ACTIVE_NONE) {
                if (active_requests.type == CARD_ACTIVE_WRITE_FILE_1_2) {
                    s32 file_idx = active_requests.callback_arg;
                    s32 blocks_before = fn_803AC6B8(*state_ptr, file_idx);
                    s32 file_blocks = fn_803AC634(*state_ptr, file_idx);
                    s32 total = fn_803AC7DC(*state_ptr);
                    s32 map[64];
                    s32 j;
                    for (j = 0; j < file_blocks; j++) {
                        map[j] = -1;
                    }
                    for (j = 1; j <= total; j++) {
                        s32 block_id = (*state_ptr)->block_ids[j];
                        if (block_id >= 0) {
                            s32 logical = block_id - blocks_before;
                            if (logical >= 0 && logical < file_blocks) {
                                if (map[logical] < 0) {
                                    map[logical] = j;
                                } else if (fn_803ACB74(
                                               (*state_ptr)
                                                   ->block_seqs[map[logical]],
                                               (*state_ptr)->block_seqs[j]) <
                                           0)
                                {
                                    (*state_ptr)->block_ids[map[logical]] *=
                                        -1;
                                    map[logical] = j;
                                } else {
                                    (*state_ptr)->block_ids[j] *= -1;
                                }
                            }
                        }
                    }
                }
                if (active_requests.callback != NULL) {
                    active_requests.callback(active_requests.callback_arg,
                                         curr_result);
                }
                active_requests.type = CARD_ACTIVE_NONE;
            }
            curr_result = 0;
            hsd_804D799C = 2;
            if (hsd_804D7990 == hsd_804D7994 &&
                requests[hsd_804D7990].type == CARD_REQ_NONE)
            {
                return;
            }
            if (fn_803AA790() < 0) {
                return;
            }
            hsd_804D799C = 0;
            continue;
        case CARD_CMD_VERIFY_BLOCK:
            if (curr_result == 2) {
                cmd->type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
                continue;
            }
            result = retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                       &cmd->state->file_info);
            if (result < 0) {
                curr_result = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &cmd->state->file_info, cmd->state->sector_buf,
                cmd->state->sector_size, cmd->verify.offset, hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
                retryCardClose(&cmd->state->file_info);
                continue;
            }
            return;
        case CARD_CMD_READ_HEADER:
            result = retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                       &cmd->state->file_info);
            if (result < 0) {
                curr_result = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
            if (cmd->read_header.index == 0) {
                memset(cmd->state->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &cmd->state->file_info, cmd->state->sector_buf,
                cmd->state->sector_size,
                cmd->read_header.index * cmd->state->sector_size,
                hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
                retryCardClose(&cmd->state->file_info);
                continue;
            }
            return;
        case CARD_CMD_VERIFY_HEADER:
            if (curr_result == 2) {
                cmd->type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
                continue;
            }
            result = retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                       &cmd->state->file_info);
            if (result < 0) {
                curr_result = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
            if (cmd->header.index == 0) {
                memset(cmd->state->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &cmd->state->file_info, cmd->state->sector_buf,
                cmd->state->sector_size,
                cmd->header.index * cmd->state->sector_size, hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
                retryCardClose(&cmd->state->file_info);
                continue;
            }
            return;
        case CARD_CMD_CHECK_VERIFIED:
            if (curr_result == 2) {
                curr_result = 0;
                cmd->type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
                continue;
            } else {
                curr_result = 1;
                cmd->type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
                continue;
            }
        case CARD_CMD_READ_BLOCK:
            if (curr_result != 1) {
                result =
                    retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                      &cmd->state->file_info);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardReadAsync(
                    &cmd->state->file_info, cmd->state->sector_buf,
                    cmd->state->sector_size, cmd->read.offset, hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    curr_result = result;
                    hsd_804D799C = 0;
                    retryCardClose(&cmd->state->file_info);
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_READ_SECTOR:
            if (curr_result != 1) {
                result =
                    retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                      &cmd->state->file_info);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardReadAsync(
                    &cmd->state->file_info, cmd->state->sector_buf,
                    cmd->state->sector_size, cmd->sector.offset, hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    curr_result = result;
                    hsd_804D799C = 0;
                    retryCardClose(&cmd->state->file_info);
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_CLEAR_BUF:
            if (curr_result != 1) {
                memset(cmd->clear.data, 0, cmd->clear.size);
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_WRITE_BLOCK:
            if (curr_result != 1) {
                s32 hdr_offset;
                s32 rem;
                signed int size;
                result =
                    retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                      &cmd->state->file_info);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                if (cmd->write.block_id > 0) {
                    hdr_offset = 0;
                } else {
                    hdr_offset = (cmd->state->header_size + 0x30) %
                                 cmd->state->sector_size;
                }
                size = cmd->write.size;
                if (size > 0 && cmd->write.data != NULL) {
                    memcpy(&cmd->state->sector_buf[hdr_offset + 0x20],
                           cmd->write.data, size);
                }
                rem = (cmd->state->sector_size - hdr_offset) - size - 0x20;
                if (rem != 0) {
                    memset(&cmd->state->sector_buf[hdr_offset + size + 0x20],
                           0, rem);
                }
                memset(cmd->state->sector_buf + hdr_offset, 0, 0x20);
                cmd->state->sector_buf[hdr_offset + 0x10] =
                    (u8) (cmd->write.block_id >> 8);
                cmd->state->sector_buf[hdr_offset + 0x11] =
                    (u8) cmd->write.block_id;
                cmd->state->sector_buf[hdr_offset + 0x12] =
                    (u8) cmd->write.seq;
                fn_803AC3F8(cmd->state,
                            &cmd->state->sector_buf[hdr_offset + 0x13],
                            cmd->write.file_idx);
                hsd_803B2FA0(cmd->state->sector_buf + hdr_offset,
                             cmd->state->sector_size - hdr_offset);
                hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &cmd->state->file_info, cmd->state->sector_buf,
                    cmd->state->sector_size, cmd->write.offset, hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    curr_result = result;
                    hsd_804D799C = 0;
                    retryCardClose(&cmd->state->file_info);
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_WRITE_SECTOR:
            if (curr_result != 1) {
                result =
                    retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                      &cmd->state->file_info);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                hsd_803B2FA0(cmd->state->sector_buf, cmd->state->sector_size);
                hsd_804D798C = CARDGetXferredBytes(cmd->state->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &cmd->state->file_info, cmd->state->sector_buf,
                    cmd->state->sector_size, cmd->sector.offset, hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    curr_result = result;
                    hsd_804D799C = 0;
                    retryCardClose(&cmd->state->file_info);
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_CREATE_FILE:
            intr2 = OSDisableInterrupts();
            result = retryCardCreateAsync(
                cmd->state->chan, cmd->create.filename, cmd->create.size,
                &cmd->state->file_info, hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
                continue;
            }
            return;
        case CARD_CMD_SET_STATUS:
            if (curr_result != 1) {
                int k;
                result = retryCardGetStatus(
                    cmd->state->chan, cmd->state->file_no, &cmd->state->stat);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                cmd->state->stat.commentAddr = 0;
                cmd->state->stat.iconAddr = 0x40;
                cmd->state->stat.bannerFormat =
                    (cmd->state->stat.bannerFormat & ~3) |
                    cmd->state->icon_info.banner_format;
                k = setupCardIcons(cmd);
                for (; k < 8; k++) {
                    cmd->state->stat.iconFormat =
                        cmd->state->stat.iconFormat &
                        ~(CARD_STAT_ICON_MASK << (2 * k));
                    cmd->state->stat.iconSpeed =
                        cmd->state->stat.iconSpeed &
                        ~(CARD_STAT_SPEED_MASK << (2 * k));
                }
                intr2 = OSDisableInterrupts();
                result = retryCardSetStatusAsync(
                    cmd->state->chan, cmd->state->file_no, &cmd->state->stat,
                    hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    curr_result = result;
                    hsd_804D799C = 0;
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_WRITE_HEADER:
            if (curr_result != 1) {
                s32 banner_size;
                s32 pos;
                result =
                    retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                      &cmd->state->file_info);
                if (result < 0) {
                    curr_result = result;
                    continue;
                }
                switch (cmd->state->icon_info.banner_format) {
                case CardBanner_Large:
                    banner_size = BANNER_LARGE;
                    break;
                case CardBanner_Small:
                    banner_size = BANNER_SMALL;
                    break;
                default:
                    banner_size = 0;
                    break;
                }
                if (cmd->header.index == 0) {
                    memcpy(cmd->state->sector_buf, cmd->state->comment, 0x40);
                    pos = 0x40;
                    if (banner_size > 0) {
                        memcpy(cmd->state->sector_buf + 0x40,
                               cmd->header.banner, banner_size);
                        pos = banner_size + 0x40;
                    }
                    memset(cmd->state->digest, 0, 0x30);
                    if (cmd->state->header_size > cmd->state->sector_size) {
                        memcpy(&cmd->state->sector_buf[pos], cmd->header.icons,
                               cmd->state->sector_size - pos);
                        hsd_803B2B20(
                            cmd->state->sector_buf, cmd->state->sector_size,
                            &cmd->state->digest[cmd->header.index * 0x10]);
                    } else {
                        memcpy(&cmd->state->sector_buf[pos], cmd->header.icons,
                               cmd->state->header_size - pos);
                        hsd_803B2B20(
                            cmd->state->sector_buf, cmd->state->header_size,
                            &cmd->state->digest[cmd->header.index * 0x10]);
                        memcpy(
                            &cmd->state->sector_buf[cmd->state->header_size],
                            cmd->state->digest, 0x30);
                    }
                } else {
                    u32 remaining =
                        cmd->state->header_size -
                        cmd->state->sector_size * cmd->header.index;
                    s32 icons_offset =
                        (cmd->state->sector_size * cmd->header.index - 0x40) -
                        banner_size;
                    if (remaining > cmd->state->sector_size) {
                        memcpy(cmd->state->sector_buf,
                               (u8*) cmd->header.icons + icons_offset,
                               cmd->state->sector_size);
                        hsd_803B2B20(
                            cmd->state->sector_buf, cmd->state->sector_size,
                            &cmd->state->digest[cmd->header.index * 0x10]);
                    } else {
                        memcpy(cmd->state->sector_buf,
                               (u8*) cmd->header.icons + icons_offset,
                               remaining);
                        hsd_803B2B20(
                            cmd->state->sector_buf, remaining,
                            &cmd->state->digest[cmd->header.index * 0x10]);
                        memcpy(&cmd->state->sector_buf[remaining],
                               cmd->state->digest, 0x30);
                    }
                }
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &cmd->state->file_info, cmd->state->sector_buf,
                    cmd->state->sector_size,
                    cmd->state->sector_size * cmd->header.index, hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D799C = 0;
                    retryCardClose(&cmd->state->file_info);
                    curr_result = result;
                    continue;
                }
                return;
            }
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        case CARD_CMD_GET_STATUS: {
            s32 retries;
            CARDStat stat;
            s32 i;
            s32 file_no;
            cmd->state->file_no = cmd->get_status.file_no;
            file_no = cmd->state->file_no;
            chan = cmd->state->chan;
            for (i = 0; i < 10; i++) {
                result = CARDGetStatus(chan, file_no, &stat);
                if (result != -1) {
                    break;
                }
            }
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
            } else {
                unpackCardStat(cmd, &stat);
                if (stat.iconAddr != 0x40) {
                    curr_result = -0x106;
                    hsd_804D799C = 0;
                } else {
                    cmd->type = CARD_CMD_NONE;
                    curr_head = (curr_head + 1) % 128;
                }
            }
            continue;
        }
        case CARD_CMD_SCAN_BLOCK:
            result = retryCardFastOpen(cmd->state->chan, cmd->state->file_no,
                                       &cmd->state->file_info);
            if (result < 0) {
                curr_result = result;
                continue;
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &cmd->state->file_info, cmd->state->sector_buf,
                cmd->state->sector_size, cmd->read.offset, hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
                retryCardClose(&cmd->state->file_info);
                continue;
            }
            return;
        case CARD_CMD_REPAIR:
            result = fn_803AD16C(cmd->state);
            if (result < 0) {
                curr_result = result;
                hsd_804D799C = 0;
            } else {
                cmd->type = CARD_CMD_NONE;
                curr_head = (curr_head + 1) % 128;
            }
            continue;
        case CARD_CMD_SCAN_FILE: {
            s32 blk;

            fn_803AC2D4();
            result = fn_803ACF30(cmd->state, 0, 0, 0);
            if (result < 0) {
                fn_803AC2E0();
                curr_result = result;
                hsd_804D799C = 0;
                continue;
            }
            for (blk = 0; blk <= cmd->state->num_blocks; blk++) {
                result = fn_803AC258(cmd->state, blk);
                if (result < 0) {
                    fn_803AC2E0();
                    curr_result = result;
                    hsd_804D799C = 0;
                    goto next;
                }
            }
            result = fn_803AC2A4(cmd->state);
            if (result < 0) {
                fn_803AC2E0();
                curr_result = result;
                hsd_804D799C = 0;
                continue;
            }
            fn_803AC334();
            cmd->type = CARD_CMD_NONE;
            curr_head = (curr_head + 1) % 128;
            continue;
        }
        default:
            return;
        }
    next:
        continue;
    }
}

int fn_803AC168(const CardCmd* cmd)
{
    BOOL intr;
    s32 mode;
    s32 read_idx;
    s32 head_type;

    intr = OSDisableInterrupts();
    read_idx = curr_head;
    mode = hsd_804D799C;
    head_type = commands[curr_head].type;
    OSRestoreInterrupts(intr);

    if (mode != 2) {
        if (curr_tail == read_idx) {
            if (mode != 0 || curr_tail != read_idx || head_type != 0) {
                return -265;
            }
        }
    }

    {
        s32 idx = curr_tail;
        curr_tail = (curr_tail + 1) % 128;
        memcpy(&commands[idx], cmd, sizeof(CardCmd));
    }

    if (mode == 2) {
        hsd_804D799C = 0;
    }
    return 0;
}

s32 fn_803AC258(CardState* state, s32 block_idx)
{
    CardCmd cmd;
    cmd.type = CARD_CMD_SCAN_BLOCK;
    cmd.state = state;
    cmd.read.phys = block_idx;
    cmd.read.xC = 0;
    cmd.read.data = NULL;
    cmd.read.size = 0;
    cmd.read.offset = fn_803ACBE8(state, block_idx);
    return fn_803AC168(&cmd);
}

s32 fn_803AC2A4(CardState* state)
{
    CardCmd cmd;
    cmd.type = CARD_CMD_REPAIR;
    cmd.state = state;
    return fn_803AC168(&cmd);
}

void fn_803AC2D4(void)
{
    hsd_804D7998 = curr_tail;
}

void fn_803AC2E0(void)
{
    s32 saved;

    if (hsd_804D7998 < 0) {
        return;
    }
    saved = hsd_804D7998;
    while (saved != curr_tail) {
        commands[saved].type = CARD_CMD_NONE;
        saved = (saved + 1) % 128;
    }
    curr_tail = hsd_804D7998;
}

void fn_803AC334(void)
{
    hsd_804D7998 = -1;
}

int hsd_803AC340(CardIconInfo* icon_info)
{
    u8* data = (void*) icon_info;
    int banner_size;
    int icon_size;
    int has_c8;
    int i;

    switch (data[0]) {
    case 2:
        banner_size = 0x1800;
        break;
    case 1:
        banner_size = 0xE00;
        break;
    default:
        banner_size = 0;
        break;
    }

    has_c8 = 0;
    icon_size = 0;
    for (i = 0; i < 8 && data[i + 0xA] != 0; i++) {
        switch (data[i + 0x2]) {
        case 2:
            icon_size += 0x800;
            break;
        case 1:
            has_c8 = 1;
            icon_size += 0x400;
            break;
        }
    }

    if (has_c8 != 0) {
        icon_size += 0x200;
    }

    icon_size = banner_size + icon_size;
    return icon_size + 0x40;
}

void hsd_803AC3E0(CardState* state, int file_idx, int file_size,
                  int file_flags, u8* data)
{
    state->file_flags[file_idx] = file_flags;
    state->file_sizes[file_idx] = file_size;
    state->file_data[file_idx] = data;
}

void fn_803AC3F8(CardState* state, u8* data, s32 file_idx)
{
    s32 start;
    s32 i;

    if (file_idx + 1 >= 9 || state->file_sizes[file_idx + 1] == 0) {
        start = file_idx - 2;
    } else {
        start = file_idx - 1;
    }
    if (start < 0) {
        start = 0;
    }

    for (i = 0; i < 3 && i < 9; i++) {
        s32 idx = start + i;
        data[0] = idx;
        data[1] = ((((u32) state->file_sizes[idx]) >> (0, 0x10)) & 0x3F) |
                  ((state->file_flags[idx] << 6) & 0xC0);
        data[2] = (u32) state->file_sizes[idx] >> 8;
        data[3] = state->file_sizes[idx];
        data += 4;
    }

    for (; i < 3; i++) {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
        data += 4;
    }
}

void hsd_803AC558(CardState* state, u8* data)
{
    int i;

    for (i = 0; i < 3; i++) {
        u8 file_idx = *data++;
        u8 byte1 = data[0];
        u32 size = (u32) data[1] | ((byte1 << 8) & 0x3F00);
        u32 final_size;
        u8 flags = (byte1 >> 6) & 3;
        size <<= 8;
        final_size = size | data[2];
        data += 3;

        if (final_size != 0 && state->file_sizes[file_idx] == 0) {
            state->file_flags[file_idx] = flags;
            state->file_sizes[file_idx] = final_size;
        }
    }
}

u32 fn_803AC634(CardState* state, s32 file_idx)
{
    if (state->file_sizes[file_idx] <= 0) {
        return 0;
    }

    if (file_idx == 0) {
        u32 usable;
        u32 sector_size = state->sector_size;
        s32 remaining;

        remaining = state->file_sizes[0];
        remaining =
            remaining - (s32) ((usable = sector_size - 0x20) -
                               (state->header_size + 48) % sector_size);
        if (remaining <= 0) {
            return 1;
        }
        return (remaining + sector_size - 0x21) / usable + 1;
    }

    {
        u32 sector_size = state->sector_size;
        return (state->file_sizes[file_idx] + sector_size - 0x21) /
               (sector_size - 0x20);
    }
}

static inline u32 fn_803AC6B8_first_block_count(CardState* state)
{
    if (state->file_sizes[0] <= 0) {
        return 0;
    }

    {
        u32 usable;
        u32 sector_size = state->sector_size;
        s32 remaining;

        remaining = state->file_sizes[0];
        remaining =
            remaining - (s32) ((usable = sector_size - 0x20) -
                               (state->header_size + 48) % sector_size);
        if (remaining <= 0) {
            return 1;
        }
        return (remaining + sector_size - 0x21) / usable + 1;
    }
}

s32 fn_803AC6B8(CardState* state, s32 file_idx)
{
    u32 sector_size;
    s32 remaining;
    u32 usable;
    s32 blocks;
    s32 file_size;
    s32 total;
    s32 i;

    if (file_idx >= 9) {
        return 0;
    }
    if (file_idx == 0) {
        return 0;
    }

    total = 1;
    if (state->file_sizes[0] > 0) {
        total += fn_803AC6B8_first_block_count(state) - 1;
    }

    for (i = 1; i < file_idx; i++) {
        file_size = state->file_sizes[i];
        if (file_size <= 0) {
            blocks = 0;
        } else if (i == 0) {
            sector_size = state->sector_size;
            remaining = state->file_sizes[0] -
                        (s32) ((usable = sector_size - 0x20) -
                               (state->header_size + 48) % sector_size);
            if (remaining <= 0) {
                blocks = 1;
            } else {
                blocks = (remaining + sector_size - 0x21) / usable + 1;
            }
        } else {
            sector_size = state->sector_size;
            blocks = (file_size + sector_size - 0x21) / (sector_size - 0x20);
        }
        total += blocks;
    }

    return total;
}

static inline s32 fn_803AC6B8_blocks_before(CardState* state, s32 file_idx)
{
    s32 total;
    s32 i;

    if (file_idx >= 9) {
        return 0;
    }
    if (file_idx == 0) {
        return 0;
    }

    total = 1;
    if (state->file_sizes[0] > 0) {
        total += fn_803AC634(state, 0) - 1;
    }

    for (i = 1; i < file_idx; i++) {
        total += fn_803AC634(state, i);
    }

    return total;
}

static inline s32 fn_803AC7DC_block_count(CardState* state, s32 file_idx)
{
    s32 blocks;

    if (state->file_sizes[file_idx] <= 0) {
        blocks = 0;
    } else if (file_idx == 0) {
        u32 usable;
        u32 sector_size = state->sector_size;
        s32 remaining;

        remaining = state->file_sizes[0];
        remaining =
            remaining - (s32) ((usable = sector_size - 0x20) -
                               (state->header_size + 48) % sector_size);
        if (remaining <= 0) {
            blocks = 1;
        } else {
            blocks = (remaining + sector_size - 0x21) / usable + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        blocks = (state->file_sizes[file_idx] + sector_size - 0x21) /
                 (sector_size - 0x20);
    }
    return blocks;
}

s32 fn_803AC7DC(CardState* state)
{
    s32 total = 0;
    s32 spare_blocks = 0;
    s32 i;

    if (state->file_sizes[0] > 0) {
        total = fn_803AC7DC_block_count(state, 0) - 1;
    }

    for (i = 1; i < 9; i++) {
        s32 size = state->file_sizes[i];

        if (size <= 0) {
            continue;
        }

        switch (state->file_flags[i]) {
        case 0:
            total += fn_803AC7DC_block_count(state, i) * 2;
            break;
        case 1:
            total += fn_803AC7DC_block_count(state, i);
            if (spare_blocks < fn_803AC7DC_block_count(state, i)) {
                spare_blocks = fn_803AC7DC_block_count(state, i);
            }
            break;
        case 2:
            total += fn_803AC7DC_block_count(state, i);
            if (spare_blocks < 1) {
                spare_blocks = 1;
            }
            break;
        case 3:
            total += fn_803AC7DC_block_count(state, i);
            break;
        }
    }

    return total + spare_blocks;
}

static inline s32 fn_803ACB74(s32 seq_a, s32 seq_b)
{
    if (seq_a < 0) {
        return -1;
    }
    if (seq_b < 0) {
        return 1;
    }
    if (seq_a == 0 && seq_b == 0xFF) {
        return 1;
    }
    if (seq_a == 0xFF && seq_b == 0) {
        return -1;
    }
    if (seq_a - seq_b > 0x80) {
        return -1;
    }
    if (seq_a - seq_b < -0x80) {
        return 1;
    }
    return seq_a - seq_b;
}

s32 fn_803ACBE8(CardState* state, s32 block_idx)
{
    u32 sector_size = state->sector_size;
    u32 temp = state->header_size + sector_size;
    u32 num = temp + 0x2F;

    temp = num / sector_size;
    {
        u32 sector = temp - 1;
        sector = block_idx + sector;
        return sector_size * sector;
    }
}

s32 fn_803ACC0C(CardState* state, s32 block_idx, s32 block_id, s32 seq_num,
                void* expected_data, s32 data_size)
{
    s32 result;
    s32 retries;
    u8* buf;
    u32 sector_size;
    CardBlockHeader* hdr;
    u32 read_offset;
    s32 hdr_offset;
    PAD_STACK(4);

    if (data_size == 0) {
        return 0;
    }

    sector_size = state->sector_size;
    buf = state->sector_buf;
    {
        u32 temp = state->header_size + sector_size;
        u32 num = temp + 0x2F;

        temp = num / sector_size;
        {
            u32 idx = temp - 1;
            idx = block_idx + idx;
            read_offset = sector_size * idx;
        }
    }

    for (retries = 0; retries < 10; retries++) {
        {
            s32 tmp =
                CARDRead(&state->file_info, buf, sector_size, read_offset);
            result = tmp;
        }
        if (result != -1) {
            break;
        }
    }

    if (result < 0) {
        return result;
    }

    if (block_idx == 0) {
        hdr_offset = (state->header_size + 48) % state->sector_size;
    } else {
        hdr_offset = 0;
    }

    if (hsd_803B31CC(state->sector_buf + hdr_offset,
                     state->sector_size - hdr_offset) < 0)
    {
        return 1;
    }

    hdr = (CardBlockHeader*) (state->sector_buf + hdr_offset);
    if (block_id != ((hdr->id_hi << 8) | hdr->id_lo)) {
        return 1;
    }

    if (seq_num != hdr->seq) {
        return 1;
    }

    if (memcmp(expected_data, hdr->data, data_size) != 0) {
        return 1;
    }

    return 0;
}

s32 fn_803ACD58(CardState* state, void* banner, void* icons)
{
    s32 banner_size;
    s32 i;
    s32 icons_start;

    switch (state->icon_info.banner_format) {
    case CardBanner_Large:
        banner_size = BANNER_LARGE;
        break;
    case CardBanner_Small:
        banner_size = BANNER_SMALL;
        break;
    default:
        banner_size = 0;
        break;
    }

    icons_start = banner_size + 0x40;

    {
        s32 retries;
        u8* buf;
        s32 offset;
        s32 size;
        for (i = 0; size = state->sector_size,
            i < (0x2F + state->header_size + size) / size;
             i++)
        {
            s32 result;

            offset = i * size;
            buf = state->sector_buf;
            for (retries = 0; retries < 10; retries++) {
                result = CARDRead(&state->file_info, buf, size, offset);
                if (result != -1) {
                    break;
                }
            }

            if (result < 0) {
                return result;
            }

            if (i == 0) {
                if (memcmp(state->sector_buf, state->comment, 0x40) != 0) {
                    return 1;
                }
                if (banner_size > 0) {
                    if (memcmp(state->sector_buf + 0x40, banner,
                               banner_size) != 0)
                    {
                        return 1;
                    }
                }
                {
                    u32 header_size = state->header_size;
                    u32 sector_size = state->sector_size;
                    if (header_size > sector_size) {
                        if (memcmp(state->sector_buf + icons_start, icons,
                                   sector_size - icons_start) != 0)
                        {
                            return 1;
                        }
                    } else {
                        if (memcmp(state->sector_buf + icons_start, icons,
                                   header_size - icons_start) != 0)
                        {
                            return 1;
                        }
                    }
                }
            } else {
                u32 sector_size = state->sector_size;
                u32 remaining = state->header_size - i * sector_size;
                s32 icons_offset = i * sector_size - 0x40 - banner_size;

                if (remaining > sector_size) {
                    if (memcmp(state->sector_buf, (u8*) icons + icons_offset,
                               sector_size) != 0)
                    {
                        return 1;
                    }
                } else {
                    if (memcmp(state->sector_buf, (u8*) icons + icons_offset,
                               remaining) != 0)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

s32 fn_803ACF30(CardState* state, void* comment, void* banner, void* icons)
{
    CardCmd buf;
    s32 ret;
    u32 i;
    PAD_STACK(4);

    for (i = 0; i < (0x2F + state->header_size + state->sector_size) /
                        state->sector_size;
         i++)
    {
        buf.type = CARD_CMD_READ_HEADER;
        buf.state = state;
        buf.read_header.index = i;
        buf.read_header.comment = comment;
        buf.read_header.banner = banner;
        buf.read_header.icons = icons;
        ret = fn_803AC168(&buf);
        if (ret < 0) {
            return ret;
        }
    }
    return 0;
}

static inline u8* fn_803ACFC0_header(CardState* state, s32 hdr_offset)
{
    return (u8*) (hdr_offset + (s32) state->sector_buf);
}

static inline u8* fn_803ACFC0_checksum_start(s32 hdr_offset, CardState* state)
{
    return hdr_offset + state->sector_buf;
}

s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 block_id, s32 seq_num,
                void* payload, s32 payload_size, s32 file_idx)
{
    u32 sector_size;
    s32 retries;
    u8* buf;
    s32 offset;
    s32 result;
    s32 hdr_offset;
    PAD_STACK(8);

    sector_size = state->sector_size;
    {
        u32 data_start = state->header_size + 48;
        offset =
            sector_size *
            (block_idx + (data_start + sector_size - 1) / sector_size - 1);

        if (block_idx == 0) {
            if (block_id != 0) {
                return -257;
            }

            buf = state->sector_buf;
            hdr_offset = data_start % sector_size;
            for (retries = 0; retries < 10; retries++) {
                result = CARDRead(&state->file_info, buf, sector_size, offset);
                if (result != -1) {
                    break;
                }
            }

            if (result < 0) {
                return result;
            }
        } else {
            hdr_offset = 0;
        }
    }

    if (payload_size > 0) {
        memcpy(&fn_803ACFC0_header(state, hdr_offset)[0x20], payload,
               payload_size);
    }

    {
        s32 remaining =
            (state->sector_size - hdr_offset) - payload_size - 0x20;
        if (remaining != 0) {
            s32 off = payload_size + 0x20;
            s32 addr = (s32) state->sector_buf;
            memset((u8*) (hdr_offset + off + addr), 0, remaining);
        }
    }

    memset(state->sector_buf + hdr_offset, 0, 0x20);

    (state->sector_buf + hdr_offset)[0x10] = (u8) (block_id >> 8);
    (state->sector_buf + hdr_offset)[0x11] = (u8) block_id;
    (state->sector_buf + hdr_offset)[0x12] = (u8) seq_num;

    fn_803AC3F8(state, fn_803ACFC0_header(state, hdr_offset) + 0x13, file_idx);
    hsd_803B2FA0(fn_803ACFC0_checksum_start(hdr_offset, state),
                 state->sector_size - hdr_offset);

    {
        s32 write_retries;
        u8* write_buf;
        u32 write_size;
        write_size = state->sector_size;
        write_retries = 0;
        write_buf = state->sector_buf;
        for (; write_retries < 10; write_retries++) {
            result =
                CARDWrite(&state->file_info, write_buf, write_size, offset);
            if (result != -1) {
                break;
            }
        }
    }

    return result;
}

static inline s32 fn_803AD16C_total_blocks(CardState* state)
{
    return state->num_blocks;
}

static inline s32 fn_803AD16C_logical_index(s32 blocks_before, s32 i)
{
    return blocks_before + i;
}

static inline s32 fn_803AD16C_file_size(CardState* state, s32 file_idx)
{
    return state->file_sizes[file_idx];
}

static inline int fn_803AD16C_nonnegative(s32 logical)
{
    return logical >= 0;
}

static inline void fn_803AD16C_own(void* value)
{
    (void) value;
}

static inline s32 fn_803AD16C_queue_clear(CardState* state, s32 phys,
                                          s32 offset, s32 file_idx)
{
    CardCmd cmd;

    cmd.type = CARD_CMD_WRITE_BLOCK;
    cmd.state = state;
    cmd.write.phys = phys;
    cmd.write.block_id = 0xFFFF;
    cmd.write.seq = 0;
    cmd.write.data = NULL;
    cmd.write.size = 0;
    cmd.write.offset = offset;
    cmd.write.file_idx = file_idx;
    return fn_803AC168(&cmd);
}

static inline s32 fn_803AD16C_queue_read(CardState* state, s32 phys)
{
    CardCmd cmd;
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;

    cmd.type = CARD_CMD_READ_SECTOR;
    cmd.state = state;
    cmd.sector.phys = phys;
    cmd.sector.offset = size * idx;
    return fn_803AC168(&cmd);
}

static inline s32 fn_803AD16C_queue_write(CardState* state, s32 phys,
                                          s32 block_id, s32 seq)
{
    CardCmd cmd;
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;

    cmd.type = CARD_CMD_WRITE_SECTOR;
    cmd.state = state;
    cmd.sector.phys = phys;
    cmd.sector.block_id = block_id;
    cmd.sector.seq = seq;
    cmd.sector.offset = size * idx;
    return fn_803AC168(&cmd);
}

static inline s32 fn_803AD16C_queue_write_last(CardState* state, s32 phys,
                                               s32 block_id, s32 seq)
{
    s32 tail[2];
    CardCmd cmd;
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;

    cmd.type = CARD_CMD_WRITE_SECTOR;
    cmd.state = state;
    cmd.sector.phys = phys;
    cmd.sector.block_id = block_id;
    cmd.sector.seq = seq;
    cmd.sector.offset = size * idx;
    fn_803AD16C_own(tail);
    return fn_803AC168(&cmd);
}

s32 fn_803AD16C(CardState* state)
{
    s32 ids[64];
    s32 seq[64];
    s32 newmap[64];
    s32 offset;
    s32 filemap[64];
    s32 chosen[64];
    s32 result;
    s32 file_idx;
    s32 pass;
    s32 i;
    s32 phys;
    s32 ofs;
    s32 blocks_before;
    s32 file_blocks;
    PAD_STACK(56);

    result = 0;
    for (i = 0; i <= state->num_blocks; i++) {
        newmap[i] = -1;
        ids[i] = state->block_ids[i];
        seq[i] = state->block_seqs[i];
    }

    if (state->num_blocks != fn_803AC7DC(state)) {
        return -257;
    }

    for (file_idx = 0; file_idx < 9; file_idx++) {
        file_blocks = fn_803AC634(state, file_idx);
        if (file_blocks <= 0) {
            continue;
        }

        blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

        for (i = 0; i < file_blocks; i++) {
            filemap[i] = -1;
            chosen[i] = -1;
        }

        for (pass = 0; pass <= state->num_blocks; pass++) {
            s32 cur_seq = -1;

            for (phys = 0; phys <= fn_803AD16C_total_blocks(state); phys++) {
                if (ids[phys] >= 0) {
                    s32 logical = ids[phys] - blocks_before;
                    if (logical >= 0 && logical < file_blocks) {
                        if (cur_seq == -1 ||
                            fn_803ACB74(cur_seq, seq[phys]) > 0)
                        {
                            cur_seq = seq[phys];
                        }
                    }
                }
            }
            if (cur_seq < 0) {
                break;
            }

            for (phys = 0; phys <= state->num_blocks; phys++) {
                s32 logical = ids[phys] - blocks_before;
                if (fn_803AD16C_nonnegative(logical) &&
                    logical < file_blocks && cur_seq == seq[phys])
                {
                    filemap[logical] = phys;
                }
            }

            {
                for (i = 0; i < file_blocks; i++) {
                    if (filemap[i] < 0 || cur_seq != seq[filemap[i]]) {
                        break;
                    }
                }
                if (i == file_blocks) {
                    for (i = 0; i < file_blocks; i++) {
                        chosen[i] = filemap[i];
                    }
                }
            }

            for (i = 0; i < file_blocks; i++) {
                if (filemap[i] >= 0) {
                    ids[filemap[i]] = -0x7FFF;
                }
            }
        }

        if (chosen[0] >= 0) {
            for (i = 0; i < file_blocks; i++) {
                newmap[blocks_before + i] = chosen[i];
            }
        } else {
            for (i = 0; i < file_blocks; i++) {
                {
                    s32 tmp = filemap[i];
                    if (tmp < 0) {
                        result = -0x103;
                    } else {
                        newmap[blocks_before + i] = filemap[i];
                        if (result != -0x103) {
                            result = -0x104;
                        }
                    }
                }
            }
        }
    }

    for (file_idx = 0; file_idx < 9; file_idx++) {
        if (fn_803AD16C_file_size(state, file_idx) <= 0 ||
            (state->file_flags[file_idx] != 1 &&
             state->file_flags[file_idx] != 2))
        {
            continue;
        }

        file_blocks = fn_803AC634(state, file_idx);
        blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

        for (i = 0; i < file_blocks; i++) {
            s32 block_id = fn_803AD16C_logical_index(blocks_before, i);
            if (newmap[block_id] >= 0) {
                for (phys = 1; phys <= state->num_blocks; phys++) {
                    if (phys != newmap[block_id] &&
                        state->block_ids[phys] == block_id)
                    {
                        state->block_ids[phys] = -block_id;
                    }
                }
            }
        }
    }

    for (file_idx = 0; file_idx < 9; file_idx++) {
        if (state->file_sizes[file_idx] <= 0 ||
            state->file_flags[file_idx] != 0)
        {
            continue;
        }

        file_blocks = fn_803AC634(state, file_idx);
        blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

        for (i = 0; i < file_blocks; i++) {
            s32 block_id = blocks_before + i;
            s32 src = newmap[block_id];
            s32 dup;
            s32 target_seq;
            s32 ret;

            if (newmap[block_id] < 0) {
                continue;
            }

            target_seq = state->block_seqs[src];
            dup = -1;
            for (phys = 1; phys <= state->num_blocks; phys++) {
                if (phys != newmap[block_id] &&
                    state->block_ids[phys] == block_id)
                {
                    if (dup < 0) {
                        dup = phys;
                    } else {
                        offset = fn_803ACBE8(state, phys);
                        if (phys == 0) {
                            ret = -0x101;
                        } else {
                            ret = fn_803AD16C_queue_clear(state, phys, offset,
                                                          file_idx);
                        }
                        if (ret < 0 && result == 0) {
                            result = -0x10B;
                        }
                        state->block_ids[phys] = -0x7FFF;
                        state->block_seqs[phys] = 0;
                    }
                }
            }

            if (dup == -1) {
                for (phys = state->num_blocks; phys > 0; phys--) {
                    if (state->block_ids[phys] < 0) {
                        dup = phys;
                        break;
                    }
                }
                if (dup >= 0) {
                    if (newmap[block_id] == 0 || dup == 0) {
                        ret = -0x101;
                    } else {
                        ret = fn_803AD16C_queue_read(state, newmap[block_id]);
                        do {
                            if (ret < 0) {
                                if (ret == -0x101) {
                                    continue;
                                }
                                continue;
                            }
                            {
                                ret = fn_803AD16C_queue_write(
                                    state, dup, block_id, target_seq);
                            }
                        } while (0);
                    }
                    if (ret < 0 && (result == 0 || result == -0x10B)) {
                        result = -0x102;
                    }
                }
            } else if (state->block_seqs[dup] != target_seq) {
                if (newmap[block_id] == 0 || dup == 0) {
                    ret = -0x101;
                } else {
                    {
                        s32 cmd_result =
                            fn_803AD16C_queue_read(state, newmap[block_id]);
                        ret = cmd_result;
                    }
                    do {
                        if (ret < 0) {
                            if (ret == -0x101) {
                                continue;
                            }
                            continue;
                        }
                        {
                            ret = fn_803AD16C_queue_write_last(
                                state, dup, block_id, target_seq);
                        }
                    } while (0);
                }
                if (ret < 0 && (result == 0 || result == -0x10B)) {
                    result = -0x102;
                }
            }
        }
    }

    return result;
}

int fn_803ADE4C(CardState* state, int file_no, CardCallback callback)
{
    CardCmd cmd_open;
    CardCmd cmd_scan;
    s32 result;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    PAD_STACK(16);

    hsd_804D7998 = curr_tail;
    cmd_open.type = CARD_CMD_GET_STATUS;
    cmd_open.state = state;
    cmd_open.get_status.file_no = file_no;
    result = fn_803AC168(&cmd_open);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != curr_tail) {
                commands[saved1].type = CARD_CMD_NONE;
                saved1 = (saved1 + 1) % 128;
            }
            curr_tail = snap1;
        }
        return result;
    }

    cmd_scan.type = CARD_CMD_SCAN_FILE;
    cmd_scan.state = state;
    result = fn_803AC168(&cmd_scan);
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != curr_tail) {
                commands[saved].type = CARD_CMD_NONE;
                saved = (saved + 1) % 128;
            }
            curr_tail = snap;
        }
        return result;
    }

    active_requests.type = CARD_ACTIVE_OPEN_OR_READ_HEADER;
    active_requests.state = state;
    active_requests.callback = callback;
    active_requests.callback_arg = 0;
    hsd_804D7998 = -1;
    return 0;
}

static inline s32 queueCardReadCommand(CardState* state, s32 block, void* data,
                                       s32 length, s32 offset)
{
    CardCmd command;

    command.type = CARD_CMD_READ_BLOCK;
    command.state = state;
    command.read.phys = block;
    command.read.xC = 0;
    command.read.data = data;
    command.read.size = length;
    command.read.offset = offset;
    return fn_803AC168(&command);
}

static inline s32 calculateDataBlockSize(CardState* state, s32 file_idx,
                                         s32 block_idx)
{
    if (file_idx == 0 && block_idx == 0) {
        return (state->sector_size - 0x20) -
               ((state->header_size + 0x30) % state->sector_size);
    }
    return state->sector_size - 0x20;
}

static inline s32 calculateFileBlockCount(CardState* state, s32 file_idx)
{
    s32 file_size = state->file_sizes[file_idx];

    if (file_size <= 0) {
        return 0;
    } else if (file_idx == 0) {
        u32 sector_size = state->sector_size;
        u32 usable;
        s32 rem;

        rem = state->file_sizes[0];
        usable = sector_size - 0x20;
        rem = rem - (s32) (usable - (state->header_size + 0x30) % sector_size);
        if (rem <= 0) {
            return 1;
        } else {
            return (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        return (file_size + sector_size - 0x21) / (sector_size - 0x20);
    }
}

static inline s32 retryCardRead(CARDFileInfo* info, void* buffer, s32 length,
                                s32 offset)
{
    s32 result;
    s32 retries;

    for (retries = 0; retries < 10; retries++) {
        result = CARDRead(info, buffer, length, offset);
        if (result != -1) {
            break;
        }
    }
    return result;
}

static inline void cancelQueuedCardCommands(void)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != curr_tail) {
            CardCmd* queued = &commands[saved];
            saved = (saved + 1) % 128;
            queued->type = zero = 0;
        }
        curr_tail = snap;
    }
}

static inline s32 queueCardClearCommand(CardState* state, u8* dst, s32 size)
{
    CardCmd command;

    command.type = CARD_CMD_CLEAR_BUF;
    command.state = state;
    command.clear.x8 = 0;
    command.clear.xC = 0;
    command.clear.data = dst;
    command.clear.size = size;
    command.clear.x14 = 0;
    command.clear.x0 = 0;
    return fn_803AC168(&command);
}

static inline s32 queueClearDataBlock(CardState* state, u8* dst, s32 size)
{
    return size == 0 ? 0 : queueCardClearCommand(state, dst, size);
}

static inline s32 cardDataBlockOffset(const CardState* state, u32 sector_size,
                                      s32 data_block)
{
    u32 temp = state->header_size + sector_size;
    u32 idx;
    temp = (temp + 0x2F) / sector_size;
    idx = temp - 1;
    idx = data_block + idx;
    return sector_size * idx;
}

static inline int queueReadDataBlock(CardState* state, s32 block_idx, u8* dst,
                                     s32 size)
{
    u32 sector_size = state->sector_size;
    u32 temp = state->header_size + sector_size;
    u32 num = temp + 0x2F;
    u32 idx;

    temp = num / sector_size;
    idx = temp - 1;
    idx = block_idx + idx;
    return queueCardReadCommand(state, block_idx, dst, size,
                                sector_size * idx);
}

static inline s32 readCardDataBlockFirst(CardState* state, u32 sector_size,
                                         s32 data_block, u8* dst, s32 length)
{
    s32 offset = cardDataBlockOffset(state, sector_size, data_block);
    u8* buf = state->sector_buf;
    s32 hdr_offset;
    int result = retryCardRead(&state->file_info, buf, sector_size, offset);

    if (result < 0) {
        return result;
    }

    hdr_offset =
        data_block == 0 ? (state->header_size + 0x30) % state->sector_size : 0;
    if (hsd_803B31CC(state->sector_buf + hdr_offset,
                     state->sector_size - hdr_offset) < 0)
    {
        return -0x105;
    }
    if (length != 0 && dst != NULL) {
        memcpy(dst, state->sector_buf + (hdr_offset + 0x20), length);
    }
    return 0;
}

static inline s32 readCardDataBlockFinal(CardState* state, u32 sector_size,
                                         s32 data_block, u8* dst, s32 length)
{
    u32 read_offset;
    u8* buf;
    s32 retries;
    s32 hdr_offset;
    s32 result;

    retries = 0;
    buf = state->sector_buf;
    {
        u32 temp = state->header_size + sector_size;
        u32 num = temp + 0x2F;
        temp = num / sector_size;
        {
            u32 idx = temp - 1;
            idx = data_block + idx;
            read_offset = sector_size * idx;
        }
    }
    for (; retries < 10; retries++) {
        result = CARDRead(&state->file_info, buf, sector_size, read_offset);
        if (result != -1) {
            break;
        }
    }
    if (result < 0) {
        return result;
    }

    hdr_offset =
        data_block == 0 ? (state->header_size + 0x30) % state->sector_size : 0;
    if (hsd_803B31CC(state->sector_buf + hdr_offset,
                     state->sector_size - hdr_offset) < 0)
    {
        return -0x105;
    }
    if (length != 0 && dst != NULL) {
        memcpy(dst, state->sector_buf + (hdr_offset + 0x20), length);
    }
    return 0;
}

int fn_803ADF90(CardState* state, s32 file_idx, u8* buf, int async,
                CardCallback callback)
{
    u8* dst;
    s32 remaining;
    s32 block_map[64];
    int blocks_before;
    int i;
    int logical;
    int scan_idx;
    int result;
    int file_blocks;
    s32 chunk;
    s32 total_blocks;
    s32 file_size;
    s32 status;

    PAD_STACK(44);

    status = 0;
    if (async == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

    file_size = state->file_sizes[file_idx];
    file_blocks = calculateFileBlockCount(state, file_idx);

    total_blocks = fn_803AC7DC(state);
    for (i = 0; i < file_blocks; i++) {
        block_map[i] = -1;
    }

    chunk = -1;
    for (scan_idx = 1; scan_idx <= total_blocks; scan_idx++) {
        logical = state->block_ids[scan_idx] - blocks_before;
        if (logical >= 0 && logical < file_blocks) {
            if (chunk < 0) {
                chunk = state->block_seqs[scan_idx];
            } else {
                if (chunk != state->block_seqs[scan_idx]) {
                    status = -260;
                }
                if (fn_803ACB74(chunk, state->block_seqs[scan_idx]) > 0) {
                    chunk = state->block_seqs[scan_idx];
                }
            }
            block_map[logical] = scan_idx;
        }
    }

    if (file_idx == 0 && state->block_ids[0] == 0) {
        block_map[0] = 0;
        if (chunk >= 0 && chunk != state->block_seqs[0]) {
            status = -260;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[i] < 0) {
            status = -259;
            break;
        }
    }

    if (status != 0) {
        return status;
    }

    if (async != 0) {
        hsd_804D7998 = curr_tail;
    } else {
        result =
            retryCardFastOpen(state->chan, state->file_no, &state->file_info);
        if (result < 0) {
            return result;
        }
    }

    dst = buf;
    remaining = file_size;

    for (i = 0; i < file_blocks && remaining > 0; i++) {
        chunk = calculateDataBlockSize(state, file_idx, i);

        if (remaining > chunk) {
            s32 phys = block_map[i];
            u32 sector_size;
            if (phys >= 0) {
                if (async != 0) {
                    result = queueReadDataBlock(state, phys, dst, chunk);
                    if (result < 0) {
                        cancelQueuedCardCommands();
                        return result;
                    }
                } else {
                    sector_size = state->sector_size;
                    result = readCardDataBlockFirst(state, sector_size, phys,
                                                    dst, chunk);
                    if (result < 0) {
                        if (result == -0x105) {
                            status = -259;
                        } else {
                            status = -259;
                        }
                    }
                }
            } else if (async != 0) {
                result = queueClearDataBlock(state, dst, chunk);
                if (result < 0) {
                    cancelQueuedCardCommands();
                    return result;
                }
            } else {
                memset(dst, 0, chunk);
            }

            remaining -= chunk;
            dst += chunk;
        } else {
            s32 phys = block_map[i];
            u32 sector_size;
            if (phys >= 0) {
                if (async != 0) {
                    result = queueReadDataBlock(state, phys, dst, remaining);
                    if (result < 0) {
                        cancelQueuedCardCommands();
                        return result;
                    }
                } else {
                    sector_size = state->sector_size;
                    result = readCardDataBlockFinal(state, sector_size, phys,
                                                    dst, remaining);
                    if (result < 0) {
                        if (result == -0x105) {
                            status = -259;
                        } else {
                            status = -259;
                        }
                    }
                }
            }
            remaining = 0;
        }
    }

    if (async == 0) {
        result = retryCardClose(&state->file_info);
        if (result < 0) {
            return -267;
        }
    } else {
        active_requests.type = CARD_ACTIVE_READ_FILE;
        active_requests.state = state;
        active_requests.callback = callback;
        active_requests.callback_arg = file_idx;
        hsd_804D7998 = -1;
    }

    return status;
}

static inline void fn_803AE7F8_rewind(void)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != curr_tail) {
            CardCmd* queued = &commands[saved];
            saved = (saved + 1) % 128;
            queued->type = zero = 0;
        }
        curr_tail = snap;
    }
}

static inline void fn_803AE7F8_close(CardState* state)
{
    s32 retries;

    for (retries = 0; retries < 10; retries++) {
        if (CARDClose(&state->file_info) != -1) {
            break;
        }
    }
}

int fn_803AE7F8(CardState* state, s32 file_idx, u8* buf, bool async,
                CardCallback callback)
{
    CardState* st = state;
    s32 block_map[3][64];
    UNUSED u8 pad_block_map[32];
    CardCmd cmd_done;
    s32(*block_map_ptr)[64];
    s32 blocks_before;
    s32 current_seq;
    s32 file_blocks;
    s32 file_size;
    s32 free_count;
    s32 i;
    s32 logical;
    s32 repair_result;
    s32 result;
    s32 total_blocks;
    s32 verify_failed;
    u8* data;
    PAD_STACK(24);

    repair_result = 0;
    verify_failed = 0;
    if (async == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

    file_size = st->file_sizes[file_idx];
    file_blocks = fn_803AC634(state, file_idx);
    total_blocks = fn_803AC7DC(state);

    for (i = 0; i < file_blocks; i++) {
        block_map[0][i] = -1;
        block_map[1][i] = -1;
    }

    free_count = 0;
    current_seq = -1;

    for (i = 1; i <= total_blocks; i++) {
        s32 block_id = st->block_ids[i];

        if (block_id < 0) {
            block_map[2][free_count++] = i;
            continue;
        }

        logical = block_id - blocks_before;
        if (0 <= logical && logical < file_blocks) {
            if (current_seq == -1 ||
                fn_803ACB74(current_seq, st->block_seqs[i]) < 0)
            {
                current_seq = st->block_seqs[i];
            }
            if (block_map[0][logical] < 0) {
                block_map[0][logical] = i;
            } else {
                block_map[1][logical] = i;
            }
        }
    }

    block_map_ptr = block_map;
    for (i = 0; i < file_blocks; i++) {
        if (block_map_ptr[0][i] < 0 ||
            st->block_seqs[block_map_ptr[0][i]] != current_seq)
        {
            verify_failed = 1;
            break;
        }
        if (block_map_ptr[1][i] < 0 ||
            st->block_seqs[block_map_ptr[1][i]] != current_seq)
        {
            verify_failed = 1;
            break;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map_ptr[0][i] < 0) {
            if (free_count > 0) {
                block_map_ptr[0][i] = block_map[2][--free_count];
            } else {
                return -257;
            }
        }
        if (block_map_ptr[1][i] < 0) {
            if (free_count > 0) {
                block_map_ptr[1][i] = block_map[2][--free_count];
            } else {
                repair_result = -258;
            }
        }
    }

    if (async != 0) {
        hsd_804D7998 = curr_tail;
    } else {
        s32 chan;
        s32 file_no;
        s32 open_result;
        s32 retries;

        file_no = st->file_no;
        chan = st->chan;
        for (retries = 0; retries < 10; retries++) {
            open_result = CARDFastOpen(chan, file_no, &st->file_info);
            if (open_result != -1) {
                break;
            }
        }

        if (open_result < 0) {
            return open_result;
        }
    }

    if (verify_failed == 0) {
        s32(*map)[64];
        s32 pass;

        pass = 0;
        map = block_map_ptr;
        for (; pass < 2; pass++, map++) {
            s32 remaining = file_size;

            data = buf;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys;
                s32 chunk = st->sector_size;

                chunk -= 0x20;
                if ((u32) remaining > (u32) chunk) {
                    phys = (*map)[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 cmd_result;
                            if (chunk == 0) {
                                cmd_result = 0;
                            } else {
                                s32 ofs = fn_803ACBE8(state, phys);
                                CardCmd cmd;

                                cmd.type = CARD_CMD_VERIFY_BLOCK;
                                cmd.state = state;
                                cmd.verify.block_id = blocks_before + i;
                                cmd.verify.seq = current_seq;
                                cmd.verify.data = data;
                                cmd.verify.size = chunk;
                                cmd.verify.offset = ofs;
                                cmd_result = fn_803AC168(&cmd);
                            }
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind();
                                return cmd_result;
                            }
                        } else {
                            s32 verify_result =
                                fn_803ACC0C(state, phys, blocks_before + i,
                                            current_seq, data, chunk);

                            result = verify_result;
                            if (result < 0) {
                                fn_803AE7F8_close(st);
                                return result;
                            }
                            if (result > 0) {
                                goto after_verify;
                            }
                        }
                    }

                    remaining -= st->sector_size - 0x20;
                    data += st->sector_size - 0x20;
                } else {
                    phys = (*map)[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 cmd_result;
                            if (remaining == 0) {
                                cmd_result = 0;
                            } else {
                                s32 ofs = fn_803ACBE8(state, phys);
                                CardCmd cmd;

                                cmd.type = CARD_CMD_VERIFY_BLOCK;
                                cmd.state = state;
                                cmd.verify.block_id = blocks_before + i;
                                cmd.verify.seq = current_seq;
                                cmd.verify.data = data;
                                cmd.verify.size = remaining;
                                cmd.verify.offset = ofs;
                                cmd_result = fn_803AC168(&cmd);
                            }
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind();
                                return cmd_result;
                            }
                        } else {
                            result =
                                fn_803ACC0C(state, phys, blocks_before + i,
                                            current_seq, data, remaining);
                            if (result < 0) {
                                fn_803AE7F8_close(st);
                                return result;
                            }
                            if (result > 0) {
                                goto after_verify;
                            }
                        }
                    }

                    remaining = 0;
                }
            }
        }

        if (async != 0) {
            s32 cmd_result;

            cmd_done.type = CARD_CMD_CHECK_VERIFIED;
            cmd_done.state = state;
            cmd_result = fn_803AC168(&cmd_done);
            if (cmd_result < 0) {
                fn_803AE7F8_rewind();
                return cmd_result;
            }
        } else {
            s32 retries;
            for (retries = 0; retries < 10; retries++) {
                result = CARDClose(&st->file_info);
                if (result != -1) {
                    break;
                }
            }

            if (result < 0) {
                return -267;
            }
            return 1;
        }
    }

after_verify:
    current_seq = (current_seq + 1) & 0xFF;
    {
        s32 pass;
        s32(*map)[64] = block_map_ptr;

        for (pass = 0; pass < 2; pass++, map++) {
            s32 remaining = file_size;

            data = buf;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys;
                s32 chunk;

                if ((u32) remaining > (u32) (chunk = st->sector_size - 0x20)) {
                    phys = (*map)[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 zero;
                            s32 cmd_result;
                            CardCmd init_cmd;
                            s32 ofs;
                            CardCmd cmd;

                            ofs = fn_803ACBE8(state, phys);
                            if (phys == 0) {
                                zero = 0;
                                if (blocks_before + i != 0) {
                                    cmd_result = -0x101;
                                    goto repair_full_queued;
                                }
                                init_cmd.type = CARD_CMD_READ_BLOCK;
                                init_cmd.state = state;
                                init_cmd.read.phys = zero;
                                init_cmd.read.xC = zero;
                                init_cmd.read.data = (void*) zero;
                                init_cmd.read.size = zero;
                                init_cmd.read.offset = ofs;
                                fn_803AC168(&init_cmd);
                            }
                            cmd.type = CARD_CMD_WRITE_BLOCK;
                            cmd.state = state;
                            cmd.write.phys = phys;
                            cmd.write.block_id = blocks_before + i;
                            cmd.write.seq = current_seq;
                            cmd.write.data = data;
                            cmd.write.size = chunk;
                            cmd.write.offset = ofs;
                            cmd.write.file_idx = file_idx;
                            cmd_result = fn_803AC168(&cmd);
                        repair_full_queued:
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind();
                                return cmd_result;
                            }
                        } else {
                            result = fn_803ACFC0(
                                state, phys, blocks_before + i, current_seq,
                                data, chunk, file_idx);
                            if (result < 0) {
                                st->block_ids[block_map[pass][i]] = -0x7FFF;
                                st->block_seqs[block_map[pass][i]] = 0;
                                fn_803AE7F8_close(st);
                                return pass == 0 ? -260 : -258;
                            }
                            st->block_ids[(*map)[i]] = blocks_before + i;
                            st->block_seqs[(*map)[i]] = current_seq;
                        }
                    }

                    remaining -= st->sector_size - 0x20;
                    data += st->sector_size - 0x20;
                } else {
                    phys = (*map)[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 zero;
                            s32 cmd_result;
                            CardCmd init_cmd;
                            s32 ofs;
                            CardCmd cmd;

                            ofs = fn_803ACBE8(state, phys);
                            if (phys == 0) {
                                zero = 0;
                                if (blocks_before + i != 0) {
                                    cmd_result = -0x101;
                                    goto repair_tail_queued;
                                }
                                init_cmd.type = CARD_CMD_READ_BLOCK;
                                init_cmd.state = state;
                                init_cmd.read.phys = zero;
                                init_cmd.read.xC = zero;
                                init_cmd.read.data = (void*) zero;
                                init_cmd.read.size = zero;
                                init_cmd.read.offset = ofs;
                                fn_803AC168(&init_cmd);
                            }
                            cmd.type = CARD_CMD_WRITE_BLOCK;
                            cmd.state = state;
                            cmd.write.phys = phys;
                            cmd.write.block_id = blocks_before + i;
                            cmd.write.seq = current_seq;
                            cmd.write.data = data;
                            cmd.write.size = remaining;
                            cmd.write.offset = ofs;
                            cmd.write.file_idx = file_idx;
                            cmd_result = fn_803AC168(&cmd);
                        repair_tail_queued:
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind();
                                return cmd_result;
                            }
                        } else {
                            result = fn_803ACFC0(
                                state, phys, blocks_before + i, current_seq,
                                data, remaining, file_idx);
                            if (result < 0) {
                                st->block_ids[block_map[pass][i]] = -0x7FFF;
                                st->block_seqs[block_map[pass][i]] = 0;
                                fn_803AE7F8_close(st);
                                return pass == 0 ? -260 : -258;
                            }
                            st->block_ids[(*map)[i]] = blocks_before + i;
                            st->block_seqs[(*map)[i]] = current_seq;
                        }
                    }

                    remaining = 0;
                }
            }
        }
    }

    if (async == 0) {
        s32 retries;
        for (retries = 0; retries < 10; retries++) {
            result = CARDClose(&st->file_info);
            if (result != -1) {
                break;
            }
        }

        if (result < 0) {
            return repair_result == 0 ? -267 : repair_result;
        }
    } else {
        CardActiveRequest* active = &active_requests;

        active->type = CARD_ACTIVE_WRITE_FILE;
        active->state = state;
        active->callback = callback;
        active->callback_arg = file_idx;
        hsd_804D7998 = -1;
    }

    return repair_result;
}

static inline s32 fn_803AF3F0_chunk_size(CardState* state)
{
    return state->sector_size - 0x20;
}

static inline s32 fn_803AF3F0_queue_verify_first(CardState* state, s32 phys,
                                                 s32 block_id, s32 seq,
                                                 void* data, s32 size)
{
    if (size == 0) {
        return 0;
    }
    {
        CardCmd cmd;
        s32 ofs = fn_803ACBE8(state, phys);
        cmd.type = CARD_CMD_VERIFY_BLOCK;
        cmd.state = state;
        cmd.verify.block_id = block_id;
        cmd.verify.seq = seq;
        cmd.verify.data = data;
        cmd.verify.size = size;
        cmd.verify.offset = ofs;
        return fn_803AC168(&cmd);
    }
}

static inline s32 fn_803AF3F0_queue_verify_final(CardState* state, s32 phys,
                                                 s32 block_id, s32 seq,
                                                 void* data, s32 size)
{
    s32 result;

    if (size == 0) {
        return 0;
    }
    {
        CardCmd cmd;
        s32 ofs = fn_803ACBE8(state, phys);
        cmd.type = CARD_CMD_VERIFY_BLOCK;
        cmd.state = state;
        cmd.verify.block_id = block_id;
        cmd.verify.seq = seq;
        cmd.verify.data = data;
        cmd.verify.size = size;
        cmd.verify.offset = ofs;
        result = fn_803AC168(&cmd);
    }
    return result;
}

static inline s32 fn_803AF3F0_queue_write_first(CardState* state, s32 phys,
                                                s32 block_id, s32 seq,
                                                void* data, s32 size,
                                                s32 file_idx)
{
    CardCmd cmd;
    s32 ofs = fn_803ACBE8(state, phys);
    CardCmd init_cmd;

    if (phys == 0) {
        s32 zero = 0;

        if (block_id != 0) {
            return -0x101;
        }
        init_cmd.type = CARD_CMD_READ_BLOCK;
        init_cmd.state = state;
        init_cmd.read.phys = zero;
        init_cmd.read.xC = zero;
        init_cmd.read.data = (void*) zero;
        init_cmd.read.size = zero;
        init_cmd.read.offset = ofs;
        fn_803AC168(&init_cmd);
    }
    cmd.type = CARD_CMD_WRITE_BLOCK;
    cmd.state = state;
    cmd.write.phys = phys;
    cmd.write.block_id = block_id;
    cmd.write.seq = seq;
    cmd.write.data = data;
    cmd.write.size = size;
    cmd.write.offset = ofs;
    cmd.write.file_idx = file_idx;
    return fn_803AC168(&cmd);
}

static inline s32 fn_803AF3F0_queue_write_final(CardState* state, s32 phys,
                                                s32 block_id, s32 seq,
                                                void* data, s32 size,
                                                s32 file_idx)
{
    CardCmd cmd;
    s32 ofs = fn_803ACBE8(state, phys);
    CardCmd init_cmd;
    s32 result;

    if (phys == 0) {
        s32 zero = 0;

        if (block_id != 0) {
            return -0x101;
        }
        init_cmd.type = CARD_CMD_READ_BLOCK;
        init_cmd.state = state;
        init_cmd.read.phys = zero;
        init_cmd.read.xC = zero;
        init_cmd.read.data = (void*) zero;
        init_cmd.read.size = zero;
        init_cmd.read.offset = ofs;
        fn_803AC168(&init_cmd);
    }
    cmd.type = CARD_CMD_WRITE_BLOCK;
    cmd.state = state;
    cmd.write.phys = phys;
    cmd.write.block_id = block_id;
    cmd.write.seq = seq;
    cmd.write.data = data;
    cmd.write.size = size;
    cmd.write.offset = ofs;
    cmd.write.file_idx = file_idx;
    result = fn_803AC168(&cmd);
    return result;
}

static inline void fn_803AF3F0_rewind(void)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != curr_tail) {
            CardCmd* queued = &commands[saved];
            saved = (saved + 1) % 128;
            queued->type = zero = 0;
        }
        curr_tail = snap;
    }
}

static inline void fn_803AF3F0_close(CardState* state)
{
    s32 retries;

    for (retries = 0; retries < 10; retries++) {
        if (CARDClose(&state->file_info) != -1) {
            break;
        }
    }
}

static inline s32 fn_803AF3F0_open(s32 chan, s32 file_no, CARDFileInfo* info)
{
    s32 retries;
    s32 open_result;

    for (retries = 0; retries < 10; retries++) {
        open_result = CARDFastOpen(chan, file_no, info);
        if (open_result != -1) {
            break;
        }
    }
    return open_result;
}

static inline void fn_803AF3F0_check_seq(CardState* state, const s32* primary,
                                         s32 count, s32 current_seq,
                                         s32* needs_rewrite)
{
    s32 i;

    for (i = 0; i < count; i++) {
        if (primary[i] < 0 || state->block_seqs[primary[i]] != current_seq) {
            *needs_rewrite = 1;
            break;
        }
    }
}

static inline void fn_803AF3F0_calc_file_blocks(s32 file_idx, CardState* state,
                                                s32* file_blocks,
                                                s32* total_blocks)
{
    if (state->file_sizes[file_idx] <= 0) {
        *file_blocks = 0;
    } else if (file_idx == 0) {
        u32 sector_size = state->sector_size;
        u32 usable;
        s32 rem;

        rem = state->file_sizes[0];
        usable = sector_size - 0x20;
        rem = rem - (s32) (usable - (state->header_size + 0x30) % sector_size);
        if (rem <= 0) {
            *file_blocks = 1;
        } else {
            *file_blocks =
                (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        *file_blocks = (state->file_sizes[file_idx] + sector_size - 0x21) /
                       (sector_size - 0x20);
    }

    *total_blocks = fn_803AC7DC(state);
}

int fn_803AF3F0(CardState* state, s32 file_idx, u8* buf, bool async,
                CardCallback callback)
{
    s32 block_map[3][64];
    s32 needs_rewrite;
    s32 blocks_before;
    s32 file_blocks;
    s32 file_size;
    s32 result;
    s32 current_seq;
    s32 secondary_count;
    s32 free_count;
    s32 i;
    s32 remaining;
    s32 total_blocks;
    u8* data;
    struct {
        s32 v;
    } free_blk;
    struct {
        s32 v;
    } write_blk;
    PAD_STACK(16);

    needs_rewrite = 0;
    if (async == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

    file_size = state->file_sizes[file_idx];
    fn_803AF3F0_calc_file_blocks(file_idx, state, &file_blocks, &total_blocks);

    if (async != 0) {
        hsd_804D7998 = curr_tail;
    } else {
        s32 open_result =
            fn_803AF3F0_open(state->chan, state->file_no, &state->file_info);

        if (open_result < 0) {
            return open_result;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        block_map[0][i] = -1;
        block_map[1][i] = -1;
    }

    current_seq = -1;
    {
        secondary_count = 0;
        free_count = 0;
        for (i = 1; i <= total_blocks; i++) {
            s32 block_id = state->block_ids[i];

            if (block_id >= 0) {
                s32 logical = block_id - blocks_before;
                if (0 <= logical && logical < file_blocks) {
                    if (fn_803ACB74(current_seq, state->block_seqs[i]) < 0) {
                        current_seq = state->block_seqs[i];
                    }
                    block_map[0][logical] = i;
                }
            } else {
                s32 logical = -(block_id + blocks_before);
                if (0 <= logical && logical < file_blocks) {
                    block_map[1][secondary_count] = i;
                    secondary_count++;
                } else {
                    block_map[2][free_count] = i;
                    free_count++;
                }
            }
        }
    }

    fn_803AF3F0_check_seq(state, block_map[0], file_blocks, current_seq,
                          &needs_rewrite);

    if (needs_rewrite == 0) {
        remaining = file_size;
        data = buf;
        for (i = 0; i < file_blocks && remaining > 0; i++) {
            if ((u32) remaining > (u32) fn_803AF3F0_chunk_size(state)) {
                if (async != 0) {
                    s32 block = block_map[0][i];
                    s32 cmd_result = fn_803AF3F0_queue_verify_first(
                        state, block, blocks_before + i, current_seq, data,
                        fn_803AF3F0_chunk_size(state));
                    if (cmd_result < 0) {
                        fn_803AF3F0_rewind();
                        return cmd_result;
                    }
                } else {
                    s32 verify_result = fn_803ACC0C(
                        state, block_map[0][i], blocks_before + i, current_seq,
                        data, fn_803AF3F0_chunk_size(state));
                    if (verify_result < 0) {
                        fn_803AF3F0_close(state);
                        return verify_result;
                    }
                    if (verify_result > 0) {
                        goto after_verify;
                    }
                }
                remaining -= fn_803AF3F0_chunk_size(state);
                data += fn_803AF3F0_chunk_size(state);
            } else {
                if (async != 0) {
                    s32 cmd_result = fn_803AF3F0_queue_verify_final(
                        state, block_map[0][i], blocks_before + i, current_seq,
                        data, remaining);
                    if (cmd_result < 0) {
                        fn_803AF3F0_rewind();
                        return cmd_result;
                    }
                } else {
                    s32 verify_result =
                        fn_803ACC0C(state, block_map[0][i], blocks_before + i,
                                    current_seq, data, remaining);
                    if (verify_result < 0) {
                        fn_803AF3F0_close(state);
                        return verify_result;
                    }
                    if (verify_result > 0) {
                        goto after_verify;
                    }
                }
                remaining = 0;
            }
        }

        if (async != 0) {
            CardCmd cmd;
            s32 cmd_result;
            cmd.type = CARD_CMD_CHECK_VERIFIED;
            cmd.state = state;
            cmd_result = fn_803AC168(&cmd);
            if (cmd_result < 0) {
                fn_803AF3F0_rewind();
                return cmd_result;
            }
        } else {
            s32 retries;
            for (retries = 0; retries < 10; retries++) {
                result = CARDClose(&state->file_info);
                if (result != -1) {
                    break;
                }
            }
            if (result < 0) {
                return -267;
            }
            return 1;
        }
    }
after_verify:

    if (secondary_count > file_blocks) {
        for (i = file_blocks; i < secondary_count; i++) {
            if (async != 0) {
                s32 cmd_result;

                free_blk.v = block_map[1][i];
                cmd_result = fn_803AF3F0_queue_write_final(
                    state, free_blk.v, 0xFFFF, 0, NULL, 0, file_idx);
                if (cmd_result < 0) {
                    fn_803AF3F0_rewind();
                    return cmd_result;
                }
            } else {
                result = fn_803ACFC0(state, block_map[1][i], 0xFFFF, 0, NULL,
                                     0, file_idx);
                state->block_ids[block_map[1][i]] = -0x7FFF;
                state->block_seqs[block_map[1][i]] = 0;
                if (result < 0) {
                    fn_803AF3F0_close(state);
                    return result;
                }
            }
        }
    } else if (secondary_count < file_blocks) {
        while (secondary_count < file_blocks && free_count > 0) {
            block_map[1][secondary_count++] = block_map[2][--free_count];
        }
        if (secondary_count < file_blocks) {
            for (i = 0; i < file_blocks && secondary_count < file_blocks; i++)
            {
                s32 primary = block_map[0][i];
                if (0 <= primary) {
                    block_map[1][secondary_count++] = primary;
                    block_map[0][i] = -1;
                }
            }
            if (secondary_count < file_blocks) {
                if (async == 0) {
                    fn_803AF3F0_close(state);
                }
                return -257;
            }
        }
    }

    {
        s32 next = current_seq + 1;
        remaining = file_size;
        data = buf;
        current_seq = next & 0xFF;
    }
    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 chunk;
        (void) (remaining != 0);

        if ((u32) remaining > (u32) (chunk = fn_803AF3F0_chunk_size(state))) {
            if (async != 0) {
                s32 cmd_result;

                write_blk.v = block_map[1][i];
                cmd_result = fn_803AF3F0_queue_write_first(
                    state, write_blk.v, blocks_before + i, current_seq, data,
                    chunk, file_idx);
                if (cmd_result < 0) {
                    fn_803AF3F0_rewind();
                    return cmd_result;
                }
            } else {
                s32 write_result = fn_803ACFC0(
                    state, block_map[1][i], blocks_before + i, current_seq,
                    data, fn_803AF3F0_chunk_size(state), file_idx);
                if (write_result < 0) {
                    state->block_ids[block_map[1][i]] = -0x7FFF;
                    state->block_seqs[block_map[1][i]] = 0;
                    fn_803AF3F0_close(state);
                    return write_result;
                }
                state->block_ids[block_map[1][i]] = blocks_before + i;
                state->block_seqs[block_map[1][i]] = current_seq;
            }
            remaining -= state->sector_size - 0x20;
            data += fn_803AF3F0_chunk_size(state);
        } else {
            if (async != 0) {
                s32 block = block_map[1][i];
                s32 cmd_result = fn_803AF3F0_queue_write_final(
                    state, block, blocks_before + i, current_seq, data,
                    remaining, file_idx);
                if (cmd_result < 0) {
                    fn_803AF3F0_rewind();
                    return cmd_result;
                }
            } else {
                s32 write_result =
                    fn_803ACFC0(state, block_map[1][i], blocks_before + i,
                                current_seq, data, remaining, file_idx);
                if (write_result < 0) {
                    state->block_ids[block_map[1][i]] = -0x7FFF;
                    state->block_seqs[block_map[1][i]] = 0;
                    fn_803AF3F0_close(state);
                    return write_result;
                }
                state->block_ids[block_map[1][i]] = blocks_before + i;
                state->block_seqs[block_map[1][i]] = current_seq;
            }
            remaining = 0;
        }
    }

    if (async == 0) {
        for (i = 0; i < file_blocks; i++) {
            if (block_map[0][i] >= 0) {
                state->block_ids[block_map[0][i]] =
                    -state->block_ids[block_map[0][i]];
            }
        }
        {
            s32 retries;
            s32 close_result;

            for (retries = 0; retries < 10; retries++) {
                close_result = CARDClose(&state->file_info);
                if (close_result != -1) {
                    break;
                }
            }
            if (close_result < 0) {
                return -267;
            }
        }
    } else {
        CardActiveRequest* active = &active_requests;

        active->type = CARD_ACTIVE_WRITE_FILE_1_2;
        active->state = state;
        active->callback = callback;
        active->callback_arg = file_idx;
        hsd_804D7998 = -1;
    }

    return 0;
}

static inline s32 fn_803B0120_first_chunk(CardState* state)
{
    u32 sector_size = state->sector_size;

    return (s32) (sector_size - 0x20) -
           (s32) ((state->header_size + 0x30) % sector_size);
}

static inline void fn_803B0120_rewind(void)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != curr_tail) {
            CardCmd* queued = &commands[saved];
            saved = (saved + 1) % 128;
            queued->type = zero = 0;
        }
        curr_tail = snap;
    }
}

static inline void fn_803B0120_close(CardState* state)
{
    s32 retries;

    for (retries = 0; retries < 10; retries++) {
        if (CARDClose(&state->file_info) != -1) {
            break;
        }
    }
}

static inline s32 fn_803B0120_close_result(CardState* state)
{
    s32 result;
    s32 retries;
    s32 ret;

    for (retries = 0; retries < 10; retries++) {
        result = CARDClose(&state->file_info);
        if (result != -1) {
            break;
        }
    }
    ret = result;
    return ret;
}

static inline s32 fn_803B0120_block_offset(CardState* state, s32 block_idx)
{
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx = num / size - 1;
    u32 pos = block_idx + idx;

    (void) temp;
    (void) idx;
    return size * pos;
}

static inline s32 fn_803B0120_queue_verify(CardState* state, s32 phys,
                                           s32 block_id, s32 seq, void* data,
                                           s32 size)
{
    s32 result;

    if (size == 0) {
        return 0;
    }
    {
        CardCmd cmd;
        s32 ofs = fn_803B0120_block_offset(state, phys);
        cmd.type = CARD_CMD_VERIFY_BLOCK;
        cmd.state = state;
        cmd.verify.block_id = block_id;
        cmd.verify.seq = seq;
        cmd.verify.data = data;
        cmd.verify.size = size;
        cmd.verify.offset = ofs;
        result = fn_803AC168(&cmd);
    }
    return result;
}

static inline s32 fn_803B0120_queue_write(CardState* state, s32 phys,
                                          s32 block_id, s32 seq, void* data,
                                          s32 size, s32 file_idx)
{
    CardCmd cmd;
    s32 ofs = fn_803ACBE8(state, phys);
    CardCmd init_cmd;
    s32 result;

    if (phys == 0) {
        s32 zero = 0;

        if (block_id != 0) {
            return -0x101;
        }
        init_cmd.type = CARD_CMD_READ_BLOCK;
        init_cmd.state = state;
        init_cmd.read.phys = zero;
        init_cmd.read.xC = zero;
        init_cmd.read.data = (void*) zero;
        init_cmd.read.size = zero;
        init_cmd.read.offset = ofs;
        fn_803AC168(&init_cmd);
    }
    cmd.type = CARD_CMD_WRITE_BLOCK;
    cmd.state = state;
    cmd.write.phys = phys;
    cmd.write.block_id = block_id;
    cmd.write.seq = seq;
    cmd.write.data = data;
    cmd.write.size = size;
    cmd.write.offset = ofs;
    cmd.write.file_idx = file_idx;
    result = fn_803AC168(&cmd);
    return result;
}

int fn_803B0120(CardState* state, s32 file_idx, u8* buf, bool async,
                CardCallback callback)
{
    s32 block_map[3][64];
    s32 needs_rewrite;
    s32 blocks_before;
    s32 file_blocks;
    s32 file_size;
    s32 total_blocks;
    s32 current_seq;
    s32 block_id;
    s32 seq;
    s32 i;
    s32 secondary_count;
    s32 free_count;
    s32 logical;
    s32 remaining;
    s32 result;
    u8* data;
    s32 j;
    PAD_STACK(16);

    needs_rewrite = 0;
    if (async == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    blocks_before = fn_803AC6B8_blocks_before(state, file_idx);

    {
        s32 size = state->file_sizes[file_idx];
        file_size = size;
    }
    file_blocks = calculateFileBlockCount(state, file_idx);
    total_blocks = fn_803AC7DC(state);

    if (async != 0) {
        hsd_804D7998 = curr_tail;
    } else {
        s32 open_result =
            fn_803AF3F0_open(state->chan, state->file_no, &state->file_info);
        if (open_result < 0) {
            return open_result;
        }
    }

    for (j = 0; j < file_blocks; j++) {
        block_map[0][j] = -1;
        block_map[1][j] = -1;
    }

    current_seq = -1;
    if (file_idx == 0) {
        if (state->block_ids[0] == 0) {
            current_seq = state->block_seqs[0];
        } else {
            needs_rewrite = 1;
        }
        block_map[0][0] = 0;
    }

    {
        secondary_count = 0;
        free_count = 0;
        for (i = 1; i <= total_blocks; i++) {
            block_id = state->block_ids[i];

            if (block_id >= 0) {
                logical = block_id - blocks_before;
                if (file_idx == 0 && logical == 0) {
                    block_map[1][secondary_count] = i;
                    secondary_count++;
                } else if (logical >= 0 && logical < file_blocks) {
                    seq = state->block_seqs[i];
                    if (fn_803ACB74(current_seq, seq) < 0) {
                        current_seq = seq;
                    }
                    block_map[0][logical] = i;
                }
            } else {
                logical = -(block_id + blocks_before);
                if (logical >= 0 && logical < file_blocks) {
                    block_map[1][secondary_count] = i;
                    secondary_count++;
                } else {
                    block_map[2][free_count] = i;
                    free_count++;
                }
            }
        }
    }

    {
        for (i = 0; i < file_blocks; i++) {
            if (block_map[0][i] < 0) {
                needs_rewrite = 1;
                if (secondary_count > 0) {
                    secondary_count--;
                    block_map[0][i] = block_map[1][secondary_count];
                    block_map[1][secondary_count] = -1;
                } else if (free_count > 0) {
                    free_count--;
                    block_map[0][i] = block_map[2][free_count];
                    block_map[2][free_count] = -1;
                } else {
                    if (async == 0) {
                        fn_803B0120_close(state);
                    }
                    return -257;
                }
            }
        }
    }

    if (needs_rewrite == 0) {
        for (i = 0; i < file_blocks; i++) {
            if (block_map[0][i] < 0 ||
                state->block_seqs[block_map[0][i]] != current_seq)
            {
                needs_rewrite = 1;
                break;
            }
        }
    }

    if (needs_rewrite == 0) {
        remaining = file_size;
        data = buf;
        for (i = 0; i < file_blocks && remaining > 0; i++) {
            s32 block_id = blocks_before + i;
            s32 chunk;
            if (block_id == 0) {
                chunk = fn_803B0120_first_chunk(state);
            } else {
                chunk = state->sector_size - 0x20;
            }

            if (remaining > chunk) {
                if (async != 0) {
                    s32 cmd_result = fn_803B0120_queue_verify(
                        state, block_map[0][i], blocks_before + i, current_seq,
                        data, chunk);
                    if (cmd_result < 0) {
                        fn_803B0120_rewind();
                        return cmd_result;
                    }
                } else {
                    s32 verify_result =
                        fn_803ACC0C(state, block_map[0][i], blocks_before + i,
                                    current_seq, data, chunk);
                    result = verify_result;
                    if (result < 0) {
                        fn_803B0120_close(state);
                        return result;
                    }
                    if (result > 0) {
                        goto verify_done;
                    }
                }
                remaining -= chunk;
                data += chunk;
            } else {
                if (async != 0) {
                    s32 cmd_result = fn_803B0120_queue_verify(
                        state, block_map[0][i], blocks_before + i, current_seq,
                        data, remaining);
                    if (cmd_result < 0) {
                        fn_803B0120_rewind();
                        return cmd_result;
                    }
                } else {
                    result =
                        fn_803ACC0C(state, block_map[0][i], blocks_before + i,
                                    current_seq, data, remaining);
                    if (result < 0) {
                        fn_803B0120_close(state);
                        return result;
                    }
                    if (result > 0) {
                        goto verify_done;
                    }
                }
                remaining = 0;
            }
        }

        if (async != 0) {
            CardCmd cmd;
            s32 cmd_result;
            cmd.type = CARD_CMD_CHECK_VERIFIED;
            cmd.state = state;
            cmd_result = fn_803AC168(&cmd);
            if (cmd_result < 0) {
                fn_803B0120_rewind();
                return cmd_result;
            }
        } else {
            s32 retries;
            for (retries = 0; retries < 10; retries++) {
                result = CARDClose(&state->file_info);
                if (result != -1) {
                    break;
                }
            }
            if (result < 0) {
                return -267;
            }
            return 1;
        }

    verify_done:;
    }
    while (secondary_count > 0) {
        secondary_count--;
        if (async != 0) {
            s32 block = block_map[1][secondary_count];
            s32 cmd_result = fn_803B0120_queue_write(state, block, 0xFFFF, 0,
                                                     NULL, 0, file_idx);
            if (cmd_result < 0) {
                fn_803B0120_rewind();
                return cmd_result;
            }
        } else {
            s32* secondary = block_map[1];
            s32* block = &secondary[secondary_count];
            result = fn_803ACFC0(state, *block, 0xFFFF, 0, NULL, 0, file_idx);
            state->block_ids[*block] = -0x7FFF;
            state->block_seqs[*block] = 0;
            if (result < 0) {
                fn_803B0120_close(state);
            }
            return result;
        }
    }

    {
        s32 next = current_seq + 1;
        remaining = file_size;
        data = buf;
        seq = next & 0xFF;
    }
    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 block_id = blocks_before + i;
        s32 chunk;
        if (block_id == 0) {
            chunk = fn_803B0120_first_chunk(state);
        } else {
            chunk = state->sector_size - 0x20;
        }

        if (remaining > chunk) {
            if (async != 0) {
                s32 block = block_map[0][i];
                s32 cmd_result = fn_803B0120_queue_write(
                    state, block, block_id, seq, data, chunk, file_idx);
                if (cmd_result < 0) {
                    fn_803B0120_rewind();
                    return cmd_result;
                }
            } else {
                s32 write_result =
                    fn_803ACFC0(state, block_map[0][i], blocks_before + i, seq,
                                data, chunk, file_idx);
                result = write_result;
                if (result < 0) {
                    state->block_ids[block_map[0][i]] = -0x7FFF;
                    state->block_seqs[block_map[0][i]] = 0;
                    fn_803B0120_close(state);
                    return result;
                }
                state->block_ids[block_map[0][i]] = blocks_before + i;
                state->block_seqs[block_map[0][i]] = seq;
            }
            remaining -= chunk;
            data += chunk;
        } else {
            if (async != 0) {
                s32 block = block_map[0][i];
                s32 cmd_result = fn_803B0120_queue_write(
                    state, block, block_id, seq, data, remaining, file_idx);
                if (cmd_result < 0) {
                    fn_803B0120_rewind();
                    return cmd_result;
                }
            } else {
                s32 write_result =
                    fn_803ACFC0(state, block_map[0][i], blocks_before + i, seq,
                                data, remaining, file_idx);
                result = write_result;
                if (result < 0) {
                    state->block_ids[block_map[0][i]] = -0x7FFF;
                    state->block_seqs[block_map[0][i]] = 0;
                    fn_803B0120_close(state);
                    return result;
                }
                state->block_ids[block_map[0][i]] = blocks_before + i;
                state->block_seqs[block_map[0][i]] = seq;
            }
            remaining = 0;
        }
    }

    if (async == 0) {
        result = fn_803B0120_close_result(state);
        if (result < 0) {
            return -267;
        }
    } else {
        active_requests.type = CARD_ACTIVE_WRITE_FILE_3;
        active_requests.state = state;
        active_requests.callback = callback;
        active_requests.callback_arg = file_idx;
        hsd_804D7998 = -1;
    }
    PAD_STACK(4);

    return 0;
}

static inline s32 queueVerifyCardHeader(CardState* state, CardCmd* cmd,
                                        void* banner, void* icons)
{
    u32 block_idx;
    s32 result;

    for (block_idx = 0;
         block_idx <
         (0x2F + state->header_size + state->sector_size) / state->sector_size;
         block_idx++)
    {
        cmd->type = CARD_CMD_VERIFY_HEADER;
        cmd->state = state;
        cmd->header.banner = banner;
        cmd->header.icons = icons;
        cmd->header.index = block_idx;
        result = fn_803AC168(cmd);
        if (result < 0) {
            return result;
        }
    }
    return 0;
}

static inline s32 fn_803B0E9C_write_block(CardState* state, s32 block_idx)
{
    u32 write_size = state->sector_size;
    s32 offset = write_size * block_idx;
    u8* buf = state->sector_buf;
    s32 retries;
    s32 result;

    for (retries = 0; retries < 10; retries++) {
        result = CARDWrite(&state->file_info, buf, write_size, offset);
        if (result != -1) {
            break;
        }
    }
    return result;
}

static inline s32 fn_803B0E9C_write_block_final(CardState* state,
                                                s32 block_idx)
{
    u32 write_size = state->sector_size;
    s32 retries;
    s32 result;
    s32 offset = write_size * block_idx;
    u8* buf = state->sector_buf;

    for (retries = 0; retries < 10; retries++) {
        result = CARDWrite(&state->file_info, buf, write_size, offset);
        if (result != -1) {
            break;
        }
    }
    return result;
}

static inline s32 fn_803B0E9C_read_first(CardState* state, u32 sector_size)
{
    u32 read_size = sector_size;
    u8* buf = state->sector_buf;
    s32 retries;
    s32 result;

    for (retries = 0; retries < 10; retries++) {
        result = CARDRead(&state->file_info, buf, read_size, 0);
        if (result != -1) {
            break;
        }
    }
    return result;
}

int fn_803B0E9C(CardState* state, void* banner, u8* icons, int is_new,
                int async)
{
    u8 digest[0x30];
    CardCmd cmd_done;
    CardCmd cmd_clear;
    UNUSED u8 pad_cmd_clear[4];
    CardCmd cmd_patch;
    UNUSED u8 pad_cmd_patch[8];
    CardCmd cmd_write_header;
    UNUSED u8 pad_cmd_write_header[16];
    CardCmd cmd_verify_header;
    UNUSED u8 pad_cmd_verify_header[8];
    s32 remaining;
    s32 payload_pos;
    s32 block_idx;
    s32 result;
    s32 has_blocks;
    u32 sector_size;

    state->header_size = hsd_803AC340(&state->icon_info);

    if (is_new == 0) {
        if (async != 0) {
            result = queueVerifyCardHeader(state, &cmd_verify_header, banner,
                                           icons);
            if (result < 0) {
                return result;
            }

            {
                cmd_done.type = CARD_CMD_CHECK_VERIFIED;
                cmd_done.state = state;
                result = fn_803AC168(&cmd_done);
            }
            if (result < 0) {
                return result;
            }
        } else {
            result = fn_803ACD58(state, banner, icons);
            if (result < 0) {
                return result;
            }
            if (result == 0) {
                return 1;
            }
        }
    }

    if (async != 0) {
        for (async = 0; sector_size = state->sector_size,
            (u32) async < (0x2F + state->header_size + sector_size) /
                                sector_size;
             async++)
        {
            if ((u32) (async + 1) ==
                (0x2F + state->header_size + sector_size) / sector_size)
            {
                if (is_new != 0) {
                    void* clear_buf = state->sector_buf;
                    s32 zero = 0;
                    cmd_clear.type = CARD_CMD_CLEAR_BUF;
                    cmd_clear.state = state;
                    cmd_clear.clear.x8 = zero;
                    cmd_clear.clear.xC = zero;
                    cmd_clear.clear.data = clear_buf;
                    cmd_clear.clear.size = sector_size;
                    cmd_clear.clear.x14 = zero;
                    cmd_clear.clear.x0 = zero;
                    result = fn_803AC168(&cmd_clear);
                } else {
                    if (state->file_sizes[0] > 0) {
                        has_blocks = 1;
                    } else {
                        has_blocks = 0;
                    }
                    cmd_patch.type = CARD_CMD_READ_BLOCK;
                    cmd_patch.state = state;
                    cmd_patch.read.phys = -1;
                    cmd_patch.read.xC = 0;
                    cmd_patch.read.data = NULL;
                    cmd_patch.read.size = has_blocks;
                    cmd_patch.read.offset = async * sector_size;
                    result = fn_803AC168(&cmd_patch);
                }
                if (result < 0) {
                    return result;
                }
            }

            {
                cmd_write_header.type = CARD_CMD_WRITE_HEADER;
                cmd_write_header.state = state;
                cmd_write_header.header.index = async;
                cmd_write_header.header.banner = banner;
                cmd_write_header.header.icons = icons;
                result = fn_803AC168(&cmd_write_header);
                if (result < 0) {
                    return result;
                }
            }
        }
        return 0;
    }

    sector_size = state->sector_size;
    if (state->header_size + 0x30 < sector_size) {
        if (is_new != 0) {
            memset(state->sector_buf, 0, sector_size);
        } else {
            result = fn_803B0E9C_read_first(state, sector_size);
            if (result < 0) {
                return result;
            }
        }
    }

    memcpy(state->sector_buf, state->comment, sizeof(state->comment));
    payload_pos = 0x40;
    switch (state->icon_info.banner_format) {
    case CardBanner_Large: {
        void* dst = state->sector_buf + 0x40;
        memcpy(dst, banner, BANNER_LARGE);
    }
        payload_pos = BANNER_LARGE + sizeof(state->comment);
        break;
    case CardBanner_Small: {
        void* dst = state->sector_buf + 0x40;
        memcpy(dst, banner, BANNER_SMALL);
    }
        payload_pos = BANNER_SMALL + sizeof(state->comment);
        break;
    }

    memset(digest, 0, sizeof(digest));
    block_idx = 0;
    remaining = state->header_size - payload_pos;

    while (remaining >= 0) {
        sector_size = state->sector_size;
        if ((u32) (payload_pos + remaining) > sector_size) {
            memcpy(state->sector_buf + payload_pos, icons,
                   sector_size - payload_pos);
            sector_size = state->sector_size;
            icons += sector_size - payload_pos;
            remaining -= sector_size - payload_pos;
            hsd_803B2B20(state->sector_buf, sector_size,
                         &digest[block_idx * 0x10]);

            result = fn_803B0E9C_write_block(state, block_idx);

            if (result < 0) {
                return result;
            }

            payload_pos = 0;
            block_idx++;

            if (remaining + 0x30 < (s32) state->header_size) {
                if (is_new != 0) {
                    memset(state->sector_buf, 0, state->sector_size);
                } else {
                    u32 read_size = state->sector_size;
                    s32 retries2;
                    u8* buf = state->sector_buf;

                    for (retries2 = 0; retries2 < 10; retries2++) {
                        result = CARDRead(&state->file_info, buf, read_size,
                                          read_size * block_idx);
                        if (result != -1) {
                            break;
                        }
                    }

                    if (result < 0) {
                        return result;
                    }
                }
            }
            continue;
        }

        memcpy(state->sector_buf + payload_pos, icons, remaining);
        payload_pos += remaining;
        hsd_803B2B20(state->sector_buf, payload_pos,
                     &digest[block_idx * 0x10]);
        memcpy(state->sector_buf + payload_pos, digest, 0x30);
        remaining = -1;

        result = fn_803B0E9C_write_block_final(state, block_idx);

        if (result < 0) {
            return result;
        }

        block_idx++;
    }

    return 0;
}

static inline s32 fn_803B1338_queue_write(CardState* state, s32 phys,
                                          s32 block_id, void* data, s32 size,
                                          s32 file_idx, CardCmdBuf* init_buf,
                                          CardCmdBuf* buf)
{
    s32 ofs = fn_803ACBE8(state, phys);
    s32 result;

    if (phys == 0) {
        if (block_id != 0) {
            return -0x101;
        }
        init_buf->cmd.type = CARD_CMD_READ_BLOCK;
        init_buf->cmd.state = state;
        init_buf->cmd.read.phys = 0;
        init_buf->cmd.read.xC = 0;
        init_buf->cmd.read.data = NULL;
        init_buf->cmd.read.size = 0;
        init_buf->cmd.read.offset = ofs;
        fn_803AC168(&init_buf->cmd);
    }
    buf->cmd.type = CARD_CMD_WRITE_BLOCK;
    buf->cmd.state = state;
    buf->cmd.write.phys = phys;
    buf->cmd.write.block_id = block_id;
    buf->cmd.write.seq = 0;
    buf->cmd.write.data = data;
    buf->cmd.write.size = size;
    buf->cmd.write.offset = ofs;
    buf->cmd.write.file_idx = file_idx;
    result = fn_803AC168(&buf->cmd);
    return result;
}

static inline u8* fn_803B1338_data_at(u8* file_payload, s32 offset)
{
    return file_payload + offset;
}

static inline s32 fn_803B1338_data_size(CardState* state)
{
    return state->sector_size - 0x20;
}

static inline s32 fn_803B1338_queue_write_data(CardState* state, s32 phys,
                                               s32 block_id, u8* fdata,
                                               s32 offset, s32 file_idx,
                                               CardCmdBuf* init_buf,
                                               CardCmdBuf* buf)
{
    s32 ofs = fn_803ACBE8(state, phys);
    u8* data = fn_803B1338_data_at(fdata, offset);
    s32 size = fn_803B1338_data_size(state);
    s32 result;

    if (phys == 0) {
        if (block_id != 0) {
            return -0x101;
        }
        init_buf->cmd.type = CARD_CMD_READ_BLOCK;
        init_buf->cmd.state = state;
        init_buf->cmd.read.phys = 0;
        init_buf->cmd.read.xC = 0;
        init_buf->cmd.read.data = NULL;
        init_buf->cmd.read.size = 0;
        init_buf->cmd.read.offset = ofs;
        fn_803AC168(&init_buf->cmd);
    }
    buf->cmd.type = CARD_CMD_WRITE_BLOCK;
    buf->cmd.state = state;
    buf->cmd.write.phys = phys;
    buf->cmd.write.block_id = block_id;
    buf->cmd.write.seq = 0;
    buf->cmd.write.data = data;
    buf->cmd.write.size = size;
    buf->cmd.write.offset = ofs;
    buf->cmd.write.file_idx = file_idx;
    result = fn_803AC168(&buf->cmd);
    return result;
}

int fn_803B1338(CardState* state, int async)
{
    PAD_STACK(72);
    {
        CardCmdBuf cmd0;
        CardCmdBuf cmd1;
        CardCmdBuf cmd2;
        CardCmdBuf cmd3;
        CardCmdBuf cmd4;
        CardCmdBuf cmd5;
        CardCmdBuf cmd6;
        CardCmdBuf cmd7;
        CardCmdBuf cmd8;
        CardCmdBuf cmd9;
        CardCmdBuf cmd10;
        CardCmdBuf cmd11;
        CardCmdBuf cmd12;
        CardCmdBuf cmd13;
        CardCmdBuf cmd14;
        CardCmdBuf cmd15;
        CardCmdBuf cmd16;
        CardCmdBuf cmd17;
        s32 result;
        s32 phys;
        s32 spare_blocks;
        s32 file_blocks;
        s32 index;
        s32 block_id;
        u8* fdata;
        PAD_STACK(40);

        spare_blocks = 0;
        block_id = 1;
        phys = 1;

        if ((s32) fn_803AC634(state, 0) != 0) {
            s32 i;
            s32 offset;
            s32 hdr_offset;
            u32 data_start;
            u32 sector_size;
            file_blocks = fn_803AC634(state, 0);
            offset = 0;
            sector_size = state->sector_size;
            data_start = state->header_size + 0x30;
            hdr_offset = data_start % sector_size;
            if (async != 0) {
                fdata = state->file_data[0];
                if (fdata == NULL) {
                    s32 ofs0 =
                        sector_size *
                        ((data_start + sector_size - 1) / sector_size - 1);
                    cmd0.cmd.type = CARD_CMD_READ_BLOCK;
                    cmd0.cmd.state = state;
                    cmd0.cmd.read.phys = 0;
                    cmd0.cmd.read.xC = 0;
                    cmd0.cmd.read.data = NULL;
                    cmd0.cmd.read.size = 0;
                    cmd0.cmd.read.offset = ofs0;
                    fn_803AC168(&cmd0.cmd);
                    cmd1.cmd.type = CARD_CMD_WRITE_BLOCK;
                    cmd1.cmd.state = state;
                    cmd1.cmd.write.phys = 0;
                    cmd1.cmd.write.block_id = 0;
                    cmd1.cmd.write.seq = 0;
                    cmd1.cmd.write.data = NULL;
                    cmd1.cmd.write.size = 0;
                    cmd1.cmd.write.offset = ofs0;
                    cmd1.cmd.write.file_idx = 0;
                    result = fn_803AC168(&cmd1.cmd);
                } else {
                    s32 ofs0 =
                        sector_size *
                        ((data_start + sector_size - 1) / sector_size - 1);
                    cmd2.cmd.type = CARD_CMD_READ_BLOCK;
                    cmd2.cmd.state = state;
                    cmd2.cmd.read.phys = 0;
                    cmd2.cmd.read.xC = 0;
                    cmd2.cmd.read.data = NULL;
                    cmd2.cmd.read.size = 0;
                    cmd2.cmd.read.offset = ofs0;
                    fn_803AC168(&cmd2.cmd);
                    cmd3.cmd.type = CARD_CMD_WRITE_BLOCK;
                    cmd3.cmd.state = state;
                    cmd3.cmd.write.phys = 0;
                    cmd3.cmd.write.block_id = 0;
                    cmd3.cmd.write.seq = 0;
                    cmd3.cmd.write.data = fdata;
                    cmd3.cmd.write.size = sector_size - hdr_offset - 0x20;
                    cmd3.cmd.write.offset = ofs0;
                    cmd3.cmd.write.file_idx = 0;
                    result = fn_803AC168(&cmd3.cmd);
                    offset = state->sector_size - hdr_offset - 0x20;
                }
                if (result < 0) {
                    return result;
                }
            } else {
                fdata = state->file_data[0];
                if (fdata == NULL) {
                    result = fn_803ACFC0(state, 0, 0, 0, NULL, 0, 0);
                } else {
                    result = fn_803ACFC0(state, 0, 0, 0, fdata,
                                         sector_size - hdr_offset - 0x20, 0);
                    offset = state->sector_size - hdr_offset - 0x20;
                }
                if (result < 0 && result != -0x105) {
                    state->block_ids[0] = -0x7FFF;
                    state->block_seqs[0] = 0;
                    return result;
                }
            }

            for (i = 1; i < file_blocks; i++) {
                if (async != 0) {
                    fdata = state->file_data[0];
                    if (fdata == NULL) {
                        result = fn_803B1338_queue_write(
                            state, phys, block_id, NULL, 0, 0, &cmd4, &cmd5);
                    } else {
                        s32 chunk;
                        u8* wdata;
                        wdata = fn_803B1338_data_at(fdata, offset);
                        chunk = fn_803B1338_data_size(state);
                        result = fn_803B1338_queue_write(state, phys, block_id,
                                                         wdata, chunk, 0,
                                                         &cmd6, &cmd7);
                        offset = state->sector_size + offset;
                        offset -= 0x20;
                    }
                    if (result < 0) {
                        return result;
                    }
                } else {
                    fdata = state->file_data[0];
                    if (fdata == NULL) {
                        result =
                            fn_803ACFC0(state, phys, block_id, 0, NULL, 0, 0);
                    } else {
                        result = fn_803ACFC0(state, phys, block_id, 0,
                                             fdata + offset,
                                             state->sector_size - 0x20, 0);
                        offset = state->sector_size + offset;
                        offset -= 0x20;
                    }
                    if (result < 0) {
                        state->block_ids[phys] = -0x7FFF;
                        state->block_seqs[phys] = 0;
                        return result;
                    }
                    state->block_ids[phys] = block_id;
                    state->block_seqs[phys] = 0;
                }
                phys++;
                block_id++;
            }
        }

        for (index = 1; index < 9; index++) {
            s32 j;
            s32 offset;
            file_blocks = fn_803AC7DC_block_count(state, index);
            offset = 0;
            if (file_blocks > 0) {
                for (j = 0; j < file_blocks; j++) {
                    if (async != 0) {
                        fdata = state->file_data[index];
                        if (fdata == NULL) {
                            result = fn_803B1338_queue_write(
                                state, phys, block_id, NULL, 0, index, &cmd8,
                                &cmd9);
                        } else {
                            result = fn_803B1338_queue_write_data(
                                state, phys, block_id, fdata, offset, index,
                                &cmd10, &cmd11);
                            offset = state->sector_size + offset;
                            offset -= 0x20;
                        }
                        if (result < 0) {
                            return result;
                        }
                    } else {
                        fdata = state->file_data[index];
                        if (fdata == NULL) {
                            result = fn_803ACFC0(state, phys, block_id, 0,
                                                 NULL, 0, index);
                        } else {
                            result = fn_803ACFC0(
                                state, phys, block_id, 0, fdata + offset,
                                state->sector_size - 0x20, index);
                            offset = state->sector_size + offset;
                            offset -= 0x20;
                        }
                        if (result < 0) {
                            state->block_ids[phys] = -0x7FFF;
                            state->block_seqs[phys] = 0;
                            return result;
                        }
                        state->block_ids[phys] = block_id;
                        state->block_seqs[phys] = 0;
                    }
                    phys++;
                    block_id++;
                }
                switch (state->file_flags[index]) {
                case 0:
                    break;
                case 1:
                    if (spare_blocks < file_blocks) {
                        spare_blocks = file_blocks;
                    }
                    break;
                case 2:
                    if (spare_blocks < 1) {
                        spare_blocks = 1;
                    }
                    break;
                case 3:
                    break;
                }
            }
        }

        {
            s32 i;
            for (i = 0; i < spare_blocks; i++) {
                if (async != 0) {
                    result = fn_803B1338_queue_write(state, phys, 0xFFFF, NULL,
                                                     0, index, &cmd12, &cmd13);
                    if (result < 0) {
                        return result;
                    }
                } else {
                    result =
                        fn_803ACFC0(state, phys, 0xFFFF, 0, NULL, 0, index);
                    state->block_ids[phys] = -0x7FFF;
                    state->block_seqs[phys] = 0;
                    if (result < 0) {
                        return result;
                    }
                }
                block_id++;
                phys++;
            }
        }

        {
            s32 block_idx;
            s32 file_id;

            index = 1;
            if ((s32) fn_803AC634(state, 0) != 0) {
                index += fn_803AC634(state, 0) - 1;
            }
            for (file_id = 1; file_id < 9; file_id++) {
                s32 offset;
                file_blocks = fn_803AC634(state, file_id);
                offset = 0;
                if (file_blocks > 0) {
                    switch (state->file_flags[file_id]) {
                    case 0:
                        for (block_idx = 0; block_idx < file_blocks;
                             block_idx++)
                        {
                            if (async != 0) {
                                fdata = state->file_data[file_id];
                                if (fdata == NULL) {
                                    result = fn_803B1338_queue_write(
                                        state, phys, index, NULL, 0, file_id,
                                        &cmd14, &cmd15);
                                } else {
                                    result = fn_803B1338_queue_write_data(
                                        state, phys, index, fdata, offset,
                                        file_id, &cmd16, &cmd17);
                                    offset = state->sector_size + offset;
                                    offset -= 0x20;
                                }
                                if (result < 0) {
                                    return result;
                                }
                            } else {
                                fdata = state->file_data[file_id];
                                if (fdata == NULL) {
                                    result = fn_803ACFC0(state, phys, index, 0,
                                                         NULL, 0, file_id);
                                } else {
                                    result = fn_803ACFC0(
                                        state, phys, index, 0, fdata + offset,
                                        state->sector_size - 0x20, file_id);
                                    offset = state->sector_size + offset;
                                    offset -= 0x20;
                                }
                                if (result < 0) {
                                    state->block_ids[phys] = -0x7FFF;
                                    state->block_seqs[phys] = 0;
                                    return result;
                                }
                                state->block_ids[phys] = index;
                                state->block_seqs[phys] = 0;
                            }
                            phys++;
                            index++;
                        }
                        break;
                    case 1:
                    case 2:
                    case 3:
                        index += file_blocks;
                        break;
                    }
                }
            }
        }

        return 0;
    }
}

int fn_803B1F78(CardState* state, const char* filename, void* banner,
                void* icons, CardCallback callback)
{
    CardCmd cmd_create;
    CardCmd cmd_set_status;
    s32 result;
    s32 file_size;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    s32 saved2;
    s32 snap2;
    s32 saved3;
    s32 snap3;
    s32 saved4;
    s32 snap4;
    PAD_STACK(12);

    hsd_804D7998 = curr_tail;
    file_size = state->sector_size * hsd_803B2674(state);
    cmd_create.type = CARD_CMD_CREATE_FILE;
    cmd_create.state = state;
    cmd_create.create.filename = filename;
    cmd_create.create.size = file_size;
    result = fn_803AC168(&cmd_create);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != curr_tail) {
                commands[saved1].type = CARD_CMD_NONE;
                saved1 = (saved1 + 1) % 128;
            }
            curr_tail = snap1;
        }
        return result;
    }

    result = fn_803B0E9C(state, banner, icons, 1, 1);
    if (result < 0) {
        snap2 = hsd_804D7998;
        if (snap2 >= 0) {
            saved2 = snap2;
            while (saved2 != curr_tail) {
                commands[saved2].type = CARD_CMD_NONE;
                saved2 = (saved2 + 1) % 128;
            }
            curr_tail = snap2;
        }
        return result;
    }

    result = fn_803B1338(state, 1);
    if (result < 0) {
        snap3 = hsd_804D7998;
        if (snap3 >= 0) {
            saved3 = snap3;
            while (saved3 != curr_tail) {
                commands[saved3].type = CARD_CMD_NONE;
                saved3 = (saved3 + 1) % 128;
            }
            curr_tail = snap3;
        }
        return result;
    }

    cmd_set_status.type = CARD_CMD_SET_STATUS;
    cmd_set_status.state = state;
    result = fn_803AC168(&cmd_set_status);
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != curr_tail) {
                commands[saved].type = CARD_CMD_NONE;
                saved = (saved + 1) % 128;
            }
            curr_tail = snap;
        }
        return result;
    }

    active_requests.type = CARD_ACTIVE_CREATE_FILE;
    active_requests.state = state;
    active_requests.callback = callback;
    result = 0;
    active_requests.callback_arg = result;
    if (result < 0) {
        snap4 = hsd_804D7998;
        if (snap4 >= 0) {
            saved4 = snap4;
            while (saved4 != curr_tail) {
                commands[saved4].type = CARD_CMD_NONE;
                saved4 = (saved4 + 1) % 128;
            }
            curr_tail = snap4;
        }
        return 0;
    }
    hsd_804D7998 = -1;
    return 0;
}

int fn_803B21E8(CardState* state, void* banner, void* icons,
                CardCallback callback)
{
    CardCmd cmd_set_status;
    s32 result;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    s32 saved2;
    s32 snap2;
    PAD_STACK(8);

    hsd_804D7998 = curr_tail;
    result = fn_803B0E9C(state, banner, icons, 0, 1);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != curr_tail) {
                commands[saved1].type = CARD_CMD_NONE;
                saved1 = (saved1 + 1) % 128;
            }
            curr_tail = snap1;
        }
        return result;
    }

    cmd_set_status.type = CARD_CMD_SET_STATUS;
    cmd_set_status.state = state;
    result = fn_803AC168(&cmd_set_status);
    if (result < 0) {
        snap2 = hsd_804D7998;
        if (snap2 >= 0) {
            saved2 = snap2;
            while (saved2 != curr_tail) {
                commands[saved2].type = CARD_CMD_NONE;
                saved2 = (saved2 + 1) % 128;
            }
            curr_tail = snap2;
        }
        return result;
    }

    active_requests.type = CARD_ACTIVE_SET_STATUS;
    active_requests.state = state;
    active_requests.callback = callback;
    result = 0;
    active_requests.callback_arg = result;
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != curr_tail) {
                commands[saved].type = CARD_CMD_NONE;
                saved = (saved + 1) % 128;
            }
            curr_tail = snap;
        }
        return 0;
    }
    hsd_804D7998 = -1;
    return 0;
}

void hsd_803B2374(void)
{
    int i;

    hsd_804D7990 = 0;
    hsd_804D7994 = 0;
    memset(requests, 0, sizeof(requests));
    curr_head = 0;
    curr_tail = 0;
    hsd_804D799C = 2;
    for (i = 0; i < 128; i++) {
        commands[i].type = CARD_CMD_NONE;
    }
    curr_result = 0;
}

void hsd_803B24E4(CardState* state, int chan, int sector_size, void* work_buf)
{
    memset(state, 0, sizeof(*state));
    state->file_no = -1;
    state->chan = chan;
    state->sector_size = sector_size;
    state->sector_buf = work_buf;
}

static inline s32 openWithRetry(s32 chan, const char* filename,
                               CardState* state)
{
    s32 i;
    s32 result;

    for (i = 0; i < 10; i++) {
        result = CARDOpen(chan, (char*) filename, &state->file_info);
        if (result != -1) {
            break;
        }
    }

    return result;
}

int hsd_803B2550(CardState* state, const char* filename, CardCallback callback)
{
    s32 new_var;
    s32 chan = state->chan;
    s32 new_var3;
    s32 new_var2;
    s32 retries;
    s32 result;
    s32 file_no;
    new_var2 = chan;
    result = openWithRetry(new_var2, filename, state);

    if (result < 0) {
        return result;
    }

    result = 0;
    {
        s32 tmp = state->file_info.fileNo;
        do {
            if (tmp != -1) {
                break;
            }
            result++;
        } while (result < 10);
        file_no = state->file_info.fileNo;
        retries = (new_var = (new_var3 = state->file_info.fileNo));
        file_no = retries;
        if (tmp < 0) {
            return new_var;
        }
    }

    for (chan = 0; chan < 10; chan++) {
        if (CARDClose(&state->file_info) != -1) {
            break;
        }
    }

    {
        s32 read_idx = hsd_804D7990;
        retries = hsd_804D7994;

        if (read_idx == retries) {
            if (requests[read_idx].type != CARD_REQ_NONE) {
                return -265;
            }
        }
    }

    {
        s32 next = retries + 1;
        requests[retries].type = CARD_REQ_OPEN_FILE;
        requests[retries].state = state;
        requests[retries].open.file_no = file_no;
        requests[retries].callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2674(CardState* state)
{
    s32 blocks;

    state->header_size = hsd_803AC340(&state->icon_info);

    blocks =
        (0x2F + state->header_size + state->sector_size) / state->sector_size;
    blocks += fn_803AC7DC(state);

    return blocks;
}

int fn_803B26CC(CardState* state, void* comment, void* banner, void* icons,
                CardCallback callback)
{
    s32 result;
    PAD_STACK(8);

    state->header_size = hsd_803AC340(&state->icon_info);
    hsd_804D7998 = curr_tail;

    result = queueHeaderBlocks(state, comment, banner, icons);

    if (result < 0) {
        if (hsd_804D7998 >= 0) {
            rollbackCardCommands(hsd_804D7998);
        }
        return result;
    }

    active_requests.type = CARD_ACTIVE_OPEN_OR_READ_HEADER;
    active_requests.state = state;
    active_requests.callback = callback;
    active_requests.callback_arg = 0;
    hsd_804D7998 = -1;
    return 0;
}

int hsd_803B27F4(CardState* state, void* comment, void* banner, void* icons,
                 CardCallback callback)
{
    s32 read_idx = hsd_804D7990;
    s32 write_idx = hsd_804D7994;

    if (read_idx == write_idx) {
        if (requests[read_idx].type != CARD_REQ_NONE) {
            return -265;
        }
    }

    {
        s32 next = write_idx + 1;
        requests[write_idx].type = CARD_REQ_READ_HEADER;
        requests[write_idx].state = state;
        requests[write_idx].header.comment = comment;
        requests[write_idx].header.banner = banner;
        requests[write_idx].header.icons = icons;
        requests[write_idx].callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B286C(CardState* state, const char* filename, const char* comment,
                 void* banner, void* icons, CardCallback callback)
{

    memcpy(state->comment, comment, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (requests[read_idx].type != CARD_REQ_NONE) {
                return -265;
            }
        }

        requests[write_idx].type = CARD_REQ_CREATE_FILE;
        requests[write_idx].state = state;
        requests[write_idx].create.filename = filename;
        requests[write_idx].create.banner = banner;
        requests[write_idx].create.icons = icons;
        requests[write_idx].callback = callback;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B2928(CardState* state, const char* comment, void* banner,
                 void* icons, CardCallback callback)
{

    memcpy(state->comment, comment, 64);

    {
        s32 write_idx;
        s32 read_idx = hsd_804D7990;

        if (read_idx == (write_idx = hsd_804D7994)) {
            if (requests[read_idx].type != CARD_REQ_NONE) {
                return -265;
            }
        }

        requests[write_idx].type = CARD_REQ_SET_STATUS;
        requests[write_idx].state = state;
        requests[write_idx].status.banner = banner;
        requests[write_idx].status.icons = icons;
        requests[write_idx].callback = callback;
        hsd_804D7994 = (write_idx + 1) % 32;
    }

    return 0;
}

int hsd_803B29D8(CardState* state, int file_idx, u8* buf,
                 CardCallback callback)
{
    s32 read_idx = hsd_804D7990;
    s32 write_idx = hsd_804D7994;

    if (read_idx == write_idx) {
        if (requests[read_idx].type != CARD_REQ_NONE) {
            return -265;
        }
    }

    {
        s32 next = write_idx + 1;
        requests[write_idx].type = CARD_REQ_READ_FILE;
        requests[write_idx].state = state;
        requests[write_idx].file.file_idx = file_idx;
        requests[write_idx].file.buf = buf;
        requests[write_idx].callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_803B2A4C(CardState* state, int file_idx, u8* buf,
                 CardCallback callback)
{
    s32 read_idx;
    s32 write_idx;

    if (state->file_sizes[file_idx] <= 0) {
        return -257;
    }

    read_idx = hsd_804D7990;
    write_idx = hsd_804D7994;

    if (read_idx == write_idx) {
        if (requests[read_idx].type != CARD_REQ_NONE) {
            return -265;
        }
    }

    {
        s32 next = write_idx + 1;
        requests[write_idx].type = CARD_REQ_WRITE_FILE;
        requests[write_idx].state = state;
        requests[write_idx].file.file_idx = file_idx;
        requests[write_idx].file.buf = buf;
        requests[write_idx].callback = callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

int hsd_SetCardIconInfo(CardState* state, CardIconInfo* icon_info)
{
    memcpy(&state->icon_info, icon_info, sizeof(state->icon_info));
    state->header_size = hsd_803AC340(&state->icon_info);
    return 0;
}

void hsd_803B2B20(u8* src, int len, void* dest)
{
    int i;
    const int spCount = 16;
    u8 sp[spCount];
    sp[0x0] = 0x01;
    sp[0x1] = 0x23;
    sp[0x2] = 0x45;
    sp[0x3] = 0x67;
    sp[0x4] = 0x89;
    sp[0x5] = 0xab;
    sp[0x6] = 0xcd;
    sp[0x7] = 0xef;
    sp[0x8] = 0xfe;
    sp[0x9] = 0xdc;
    sp[0xa] = 0xba;
    sp[0xb] = 0x98;
    sp[0xc] = 0x76;
    sp[0xd] = 0x54;
    sp[0xe] = 0x32;
    sp[0xf] = 0x10;

    for (i = 0; i < len; i++) {
        sp[i % spCount] += *src++;
    }

    for (i = 1; i < spCount; i++) {
        if (sp[i - 1] == sp[i]) {
            sp[i] = sp[i] ^ 0xff;
        }
    }

    memcpy(dest, sp, sizeof(sp));
}

/// @todo There could be a split here but the following functions are only used
/// in hsd_3A94
static s32 lbl_80430BD0[13] ATTRIBUTE_ALIGN(8) = {
    0x26, 0xFF, 0xE8, 0xEF, 0x42, 0xD6, 0x01,
    0x54, 0x14, 0xA3, 0x80, 0xFD, 0x6E,
};

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
static int fn_803B2E04(u8 prev, s32 cur)
{
    u32 mod7;
    u32 val;
    u32 key;

    key = lbl_80430BD0[prev % 13];
    val = prev ^ cur;
    val ^= key;
    mod7 = prev % 7;

    switch (mod7) {
    case 0:
        return (u8) ((val & 1) | ((val << 3) & 0x10) | ((val >> 1U) & 2) |
                     ((val << 2) & 0x20) | ((val >> 2U) & 4) |
                     ((val << 1) & 0x40) | ((val >> 3U) & 8) | (val & 0x80));
    case 1:
        return (u8) (((val << 3) & 8) | ((val >> 1U) & 1) | (val & 4) |
                     ((val << 3) & 0x40) | ((val << 1) & 0x20) |
                     ((val >> 1U) & 0x10) | ((val << 1) & 0x80) |
                     ((val >> 6U) & 2));
    case 2:
        return (u8) (((val << 6) & 0x40) | ((val << 4) & 0x20) |
                     ((val >> 2U) & 1) | ((val >> 2U) & 2) |
                     ((val >> 1U) & 8) | ((val << 2) & 0x80) |
                     ((val >> 4U) & 4) | ((val >> 3U) & 0x10));
    case 3:
        return (u8) (((val << 1) & 2) | ((val << 2) & 8) |
                     ((val << 5) & 0x80) | ((val << 1) & 0x10) |
                     ((val >> 4U) & 1) | ((val >> 3U) & 4) |
                     ((val >> 1U) & 0x20) | ((val >> 1U) & 0x40));
    case 4:
        return (u8) (((val << 7) & 0x80) | ((val << 1) & 4) |
                     ((val << 3) & 0x20) | ((val >> 3U) & 1) |
                     ((val << 2) & 0x40) | ((val >> 4U) & 2) |
                     ((val >> 2U) & 0x10) | ((val >> 4U) & 8));
    case 5:
        return (u8) (((val & 1) << 5) | ((val << 5) & 0x40) |
                     ((val << 2) & 0x10) | (val & 8) | ((val << 3) & 0x80) |
                     ((val >> 5U) & 1) | ((val >> 5U) & 2) |
                     ((val >> 5U) & 4));
    case 6:
        return (u8) (((val << 2) & 4) | (val & 2) | ((val & 4) << 4) |
                     ((val << 4) & 0x80) | (val & 0x10) | ((val >> 2U) & 8) |
                     ((val >> 6U) & 1) | ((val >> 2U) & 0x20));
    }
    return val;
}

#ifdef MUST_MATCH
#pragma pop
#endif

int hsd_803B2FA0(u8* data, int len)
{
    u8* ptr;
    int i;

    if (data == NULL) {
        return -1;
    }

    hsd_803B2B20(data + 16, len - 16, data);

    for (i = 16; i < len; i++) {
        ptr = data + i;
        *ptr = fn_803B2E04(ptr[-1], *ptr);
    }

    return 0;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
static int fn_803B302C(u32 prev, u32 cur)
{
    u32 mod7;

    mod7 = (u8) prev % 7;

    switch (mod7) {
    case 0:
        cur = (u8) ((cur & 1) | ((cur << 1) & 4) | ((cur << 2) & 0x10) |
                    ((cur << 3) & 0x40) | ((cur >> 3U) & 2) |
                    ((cur >> 2U) & 8) | ((cur >> 1U) & 0x20) | (cur & 0x80));
        break;
    case 1:
        cur = (u8) (((cur << 1) & 2) | ((cur << 6) & 0x80) | (cur & 4) |
                    ((cur >> 3U) & 1) | ((cur << 1) & 0x20) |
                    ((cur >> 1U) & 0x10) | ((cur >> 3U) & 8) |
                    ((cur >> 1U) & 0x40));
        break;
    case 2:
        cur = (u8) (((cur & 1) << 2) | ((cur << 2) & 8) | ((cur << 4) & 0x40) |
                    ((cur << 1) & 0x10) | ((cur << 3) & 0x80) |
                    ((cur >> 4U) & 2) | ((cur >> 6U) & 1) |
                    ((cur >> 2U) & 0x20));
        break;
    case 3:
        cur = (u8) (((cur << 4) & 0x10) | ((cur >> 1U) & 1) |
                    ((cur << 3) & 0x20) | ((cur >> 2U) & 2) |
                    ((cur >> 1U) & 8) | ((cur << 1) & 0x40) |
                    ((cur << 1) & 0x80) | ((cur >> 5U) & 4));
        break;
    case 4:
        cur = (u8) (((cur << 3) & 8) | ((cur << 4) & 0x20) |
                    ((cur >> 1U) & 2) | ((cur << 4) & 0x80) |
                    ((cur << 2) & 0x40) | ((cur >> 3U) & 4) |
                    ((cur >> 2U) & 0x10) | ((cur >> 7U) & 1));
        break;
    case 5:
        cur = (u8) (((cur & 1) << 5) | ((cur << 5) & 0x40) | ((cur & 4) << 5) |
                    (cur & 8) | ((cur >> 2U) & 4) | ((cur >> 5U) & 1) |
                    ((cur >> 5U) & 2) | ((cur >> 3U) & 0x10));
        break;
    case 6:
        cur = (u8) (((cur << 6) & 0x40) | (cur & 2) | ((cur >> 2U) & 1) |
                    ((cur << 2) & 0x20) | (cur & 0x10) | ((cur << 2) & 0x80) |
                    ((cur >> 4U) & 4) | ((cur >> 4U) & 8));
        break;
    }

    cur ^= lbl_80430BD0[(u8) prev % 13];
    cur ^= prev;
    return cur;
}

#ifdef MUST_MATCH
#pragma pop
#endif

int hsd_803B31CC(u8* data, int len)
{
    u32 prev;
    u8* ptr;
    int i;
    u32 cur;
    u8 check[16];
    int k;

    if (data == NULL) {
        return -1;
    }

    prev = data[15];

    for (i = 16; i < len; i++) {
        ptr = data + i;
        cur = *ptr;
        *ptr = fn_803B302C(prev, *ptr);
        prev = cur;
    }

    hsd_803B2B20(data + 16, len - 16, check);

    for (k = 0; k < 16; k++) {
        if (check[k] != data[k]) {
            return -1;
        }
    }

    return 0;
}
