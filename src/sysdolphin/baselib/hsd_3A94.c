#include "hsd_3A94.h"

#include <placeholder.h>
#include <string.h>

#include "hsd_3B2B.h"
#include "hsd_3B2E.h"
#include <dolphin/card.h>
#include <dolphin/os.h>

typedef struct {
    u8 x0[0x300];
} __baselib_UnkType003;

/// hsd_804D1138 viewed at CardCmd stride: entry 0 overlays the CardContext
/// header, and entry i's x10 is CardContext::cmds[i].type.
typedef struct CardBufEntry {
    s32 x0, x4, x8, xC;
    s32 x10;
    s32 x14, x18, x1C, x20;
} CardBufEntry;

/// 0x20-byte header at the start of every data block on the card.
typedef struct CardBlockHeader {
    /* 0x00 */ u8 digest[0x10];
    /* 0x10 */ u8 id_hi;
    /* 0x11 */ u8 id_lo;
    /* 0x12 */ u8 seq;
    /* 0x13 */ u8 file_table[0x0C];
    /* 0x1F */ u8 pad_1F[1];
    /* 0x20 */ u8 data[1];
} CardBlockHeader;

/**
 * One entry of the command ring processed by hsd_803AAA48.
 *
 * x8/xC/x10/x14 depend on type: block commands (1, 2, 5, 13, 15, 16) carry
 * file index, physical block, block id and sequence number; header commands
 * (7, 9, 10, 11, 12) carry filename/size, header block index, and the
 * comment/banner/icons buffers.
 */
typedef struct CardCmd {
    /* 0x00 */ s32 type;
    /* 0x04 */ CardState* state;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* data;
    /* 0x1C */ s32 offset;
    /* 0x20 */ s32 size;
} CardCmd;

/// Stack staging slot for one queued command.
typedef union CardCmdBuf {
    CardCmd cmd;
    s32 words[10];
} CardCmdBuf;

/// One entry of the request queue drained by fn_803AA790; x8/xC/x10 are
/// the request's arguments and depend on type.
typedef struct CardRequest {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ void (*callback)(s32, s32);
} CardRequest;

/// Layout of hsd_804D1138 .. hsd_804D2348: the request being completed,
/// the command ring and the request queue.
typedef struct CardContext {
    /* 0x0000 */ s32 req_type;
    /* 0x0004 */ CardState* state;
    /* 0x0008 */ void (*callback)(s32, s32);
    /* 0x000C */ s32 callback_arg;
    /* 0x0010 */ CardCmd cmds[128];
    /* 0x1210 */ CardRequest requests[32];
} CardContext;

#define CMD_S32(off)                                                          \
    (((CardBufEntry*) ((unsigned char*) op + (off)))[hsd_804D7980].x0)
#define CMD_STATE ((CardState*) CMD_S32(0x14))
#define CMD_PTR(off) ((void*) CMD_S32(off))
#define CMD_TYPE (op[hsd_804D7980].x10)
#define CARD_WRITE_BLOCK(state, block_idx, block_id, seq_num, payload,        \
                         payload_len, file_idx)                               \
    fn_803ACFC0((state), (block_idx), (block_id), (seq_num), (payload),       \
                (payload_len), (file_idx))

/* 3A949C */ static void hsd_803A949C(s32 chan, s32 card_result);
/* 3ACB74 */ static s32 fn_803ACB74(s32 seq_a, s32 seq_b);
/* 4D1148 */ extern u32 hsd_804D1148[0x80][0x9];
/* 4D2348 */ extern __baselib_UnkType003 hsd_804D2348;
/// Command ring head (next command to run) and tail (next free slot).
/* 4D7980 */ extern volatile s32 hsd_804D7980;
/* 4D7984 */ extern volatile s32 hsd_804D7984;
/// Result of the request in progress: negative = CARD error, 1 = data
/// verified so the queued writes are skipped, 2 = verify mismatch.
/* 4D7988 */ extern s32 hsd_804D7988;
/* 4D798C */ extern s32 hsd_804D798C;
/// Ring tail saved before queueing a request; -1 when nothing to roll back.
/* 4D7998 */ extern s32 hsd_804D7998;
/// 0 = running commands, 1 = async CARD call in flight, 2 = idle.
/* 4D799C */ extern s32 hsd_804D799C;
/// .sbss globals emit in reverse declaration order.
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

static inline s32 hsd_803A949C_Close(CardState* state)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDClose(&state->file_info);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}

void hsd_803A949C(s32 chan, s32 card_result)
{
    CardBufEntry* op = (CardBufEntry*) hsd_804D1138;
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

    state = ((CardState*) CMD_S32(0x14));

    switch (CMD_TYPE) {
    case 2:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }

        if (CMD_S32(0x20) < 0) {
            if (hsd_803A949C_Close(state) < 0) {
                hsd_804D7988 = card_result;
            }
            break;
        }

        if (CMD_S32(0x20) == 0) {
            hdr_offset = (state->header_size + 0x30) % state->sector_size;
            if (CMD_S32(0x30) > 0) {
                if (hsd_803B31CC(state->sector_buf + hdr_offset,
                                 state->sector_size - hdr_offset) < 0)
                {
                    hsd_803A949C_Close(state);
                    hsd_804D7988 = -0x105;
                    break;
                }
                if (CMD_PTR(0x28) != NULL) {
                    u8* src = (u8*) (hdr_offset + (u32) state->sector_buf);
                    memcpy(CMD_PTR(0x28), src + 0x20, CMD_S32(0x30));
                }
            }
            result = hsd_803A949C_Close(state);
        } else {
            if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
                hsd_803A949C_Close(state);
                hsd_804D7988 = -0x105;
                break;
            }
            if (CMD_S32(0x30) > 0 && CMD_PTR(0x28) != NULL) {
                memcpy((void*) CMD_S32(0x28), state->sector_buf + 0x20,
                       CMD_S32(0x30));
            }
            result = hsd_803A949C_Close(state);
        }
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 15:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
        } else if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = -0x105;
        } else {
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
        }
        break;

    case 5:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }

        if (CMD_S32(0x20) == 0) {
            if (CMD_S32(0x30) <= 0) {
                result = hsd_803A949C_Close(state);
                if (result < 0) {
                    hsd_804D7988 = result;
                }
                break;
            }

            hdr_offset = (state->header_size + 0x30) % state->sector_size;
            if (hsd_803B31CC(state->sector_buf + hdr_offset,
                             state->sector_size - hdr_offset) < 0)
            {
                hsd_803A949C_Close(state);
                hsd_804D7988 = 2;
                break;
            }
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
                break;
            }
            result = hsd_804D7980;
            block = state->sector_buf + hdr_offset;
            result = ((CardBufEntry*) ((u8*) op + 0x20))[result].x0;
            if (((block[0x10] << 8) | block[0x11]) != result) {
                hsd_804D7988 = 2;
            } else if ((s32) block[0x12] != CMD_S32(0x24)) {
                hsd_804D7988 = 2;
            } else if (CMD_S32(0x30) > 0 &&
                       memcmp((void*) CMD_S32(0x28), (block += 0x20),
                              CMD_S32(0x30)) != 0)
            {
                hsd_804D7988 = 2;
            }
        } else {
            if (hsd_803B31CC(state->sector_buf, state->sector_size) < 0) {
                hsd_803A949C_Close(state);
                hsd_804D7988 = 2;
                break;
            }
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
                break;
            }
            result = (((CardBlockHeader*) state->sector_buf)->id_hi << 8) |
                     ((CardBlockHeader*) state->sector_buf)->id_lo;
            block = state->sector_buf;
            if (result != CMD_S32(0x20)) {
                hsd_804D7988 = 2;
            } else if ((s32) block[0x12] != CMD_S32(0x24)) {
                hsd_804D7988 = 2;
            } else if (CMD_S32(0x30) > 0 &&
                       memcmp((void*) CMD_S32(0x28), block + 0x20,
                              CMD_S32(0x30)) != 0)
            {
                hsd_804D7988 = 2;
            }
        }
        break;

    case 10:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }

        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
            break;
        }

        switch (state->banner_format) {
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

        if (CMD_S32(0x18) == 0) {
            if (memcmp(state->sector_buf, state->comment, 0x40) != 0) {
                hsd_804D7988 = 2;
                break;
            }
            if (banner_size > 0 &&
                memcmp(state->sector_buf + 0x40, (void*) CMD_S32(0x1c),
                       banner_size) != 0)
            {
                hsd_804D7988 = 2;
                break;
            }
            icons_start = banner_size + 0x40;
            if (state->header_size > state->sector_size) {
                if (memcmp(state->sector_buf + icons_start,
                           (void*) CMD_S32(0x20),
                           state->sector_size - icons_start) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->sector_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
            } else if (memcmp(state->sector_buf + icons_start,
                              (void*) CMD_S32(0x20),
                              state->header_size - icons_start) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->header_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
                if (memcmp(state->sector_buf + state->header_size,
                           CMD_STATE->digest, 0x30) != 0)
                {
                    hsd_804D7988 = 2;
                }
            }
        } else {
            icons_offset =
                (state->sector_size * CMD_S32(0x18)) - 0x40 - banner_size;
            remaining =
                state->header_size - state->sector_size * CMD_S32(0x18);
            if ((u32) remaining > state->sector_size) {
                if (memcmp(state->sector_buf,
                           (u8*) CMD_S32(0x20) + icons_offset,
                           state->sector_size) != 0)
                {
                    hsd_804D7988 = 2;
                    break;
                }
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->sector_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
            } else if (memcmp(state->sector_buf,
                              (u8*) CMD_S32(0x20) + icons_offset,
                              remaining) != 0)
            {
                hsd_804D7988 = 2;
            } else {
                hsd_803B2B20(CMD_STATE->sector_buf, remaining,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
                if (memcmp(state->sector_buf + remaining, CMD_STATE->digest,
                           0x30) != 0)
                {
                    hsd_804D7988 = 2;
                }
            }
        }
        break;

    case 11:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }

        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
            break;
        }

        switch (state->banner_format) {
        case 2:
            banner_size11 = 0x1800;
            break;
        case 1:
            banner_size11 = 0xE00;
            break;
        default:
            banner_size11 = 0;
            break;
        }

        if (CMD_S32(0x18) == 0) {
            if (CMD_PTR(0x1c) != NULL) {
                memcpy((void*) CMD_S32(0x1c), state->sector_buf, 0x40);
            }
            if (banner_size11 > 0 && CMD_PTR(0x20) != NULL) {
                memcpy((void*) CMD_S32(0x20), state->sector_buf + 0x40,
                       banner_size11);
            }
            icons_start = banner_size11 + 0x40;
            if (state->header_size > state->sector_size) {
                if (CMD_PTR(0x24) != NULL) {
                    memcpy((void*) CMD_S32(0x24),
                           state->sector_buf + icons_start,
                           state->sector_size - icons_start);
                }
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->sector_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
            } else {
                if (CMD_PTR(0x24) != NULL) {
                    memcpy((void*) CMD_S32(0x24),
                           state->sector_buf + icons_start,
                           state->header_size - icons_start);
                }
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->header_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
                if (memcmp(state->sector_buf + state->header_size,
                           CMD_STATE->digest, 0x30) != 0)
                {
                    hsd_804D7988 = -0x107;
                }
            }
        } else {
            icons_offset =
                (state->sector_size * CMD_S32(0x18)) - 0x40 - banner_size11;
            chan = state->header_size - state->sector_size * CMD_S32(0x18);
            if ((u32) chan > state->sector_size) {
                if (CMD_PTR(0x24) != NULL) {
                    memcpy((u8*) CMD_S32(0x24) + icons_offset,
                           state->sector_buf, state->sector_size);
                }
                hsd_803B2B20(CMD_STATE->sector_buf, CMD_STATE->sector_size,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
            } else {
                if (CMD_PTR(0x24) != NULL) {
                    memcpy((u8*) CMD_S32(0x24) + icons_offset,
                           state->sector_buf, chan);
                }
                hsd_803B2B20(CMD_STATE->sector_buf, chan,
                             &CMD_STATE->digest[CMD_S32(0x18) * 0x10]);
                if (memcmp(state->sector_buf + chan, CMD_STATE->digest,
                           0x30) != 0)
                {
                    hsd_804D7988 = -0x107;
                }
            }
        }
        break;

    case 1:
        if (card_result != 0) {
            state->block_ids[CMD_S32(0x1c)] = -0x7FFF;
            state->block_seqs[CMD_S32(0x1c)] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }
        if (CMD_S32(0x20) != 0xFFFF) {
            state->block_ids[CMD_S32(0x1c)] = CMD_S32(0x20);
            state->block_seqs[CMD_S32(0x1c)] = CMD_S32(0x24);
        } else {
            state->block_ids[CMD_S32(0x1c)] = -0x7FFF;
            state->block_seqs[CMD_S32(0x1c)] = 0;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 16:
        if (card_result != 0) {
            state->block_ids[CMD_S32(0x1c)] = -0x7FFF;
            state->block_seqs[CMD_S32(0x1c)] = 0;
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
            break;
        }
        if (CMD_S32(0x20) != 0xFFFF) {
            state->block_ids[CMD_S32(0x1c)] = CMD_S32(0x20);
            state->block_seqs[CMD_S32(0x1c)] = CMD_S32(0x24);
        } else {
            state->block_ids[CMD_S32(0x1c)] = -0x7FFF;
            state->block_seqs[CMD_S32(0x1c)] = 0;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 7:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
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
            hsd_804D7988 = state->file_no;
        }
        result = hsd_803A949C_Close(state);
        if (result < 0) {
            hsd_804D7988 = result;
        }
        break;

    case 8:
        if (card_result != 0) {
            hsd_804D7988 = card_result;
        }
        break;

    case 9:
        if (card_result != 0) {
            hsd_803A949C_Close(state);
            hsd_804D7988 = card_result;
        } else {
            result = hsd_803A949C_Close(state);
            if (result < 0) {
                hsd_804D7988 = result;
            }
        }
        break;

    case 13:
        phys = CMD_S32(0x20);
        hsd_803A949C_Close(state);
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
                    u8* src13 = (u8*) (hdr_offset13 + (u32) state->sector_buf);
                    hsd_803AC558(state, src13 + 0x13);
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
    }

    CMD_TYPE = 0;
    hsd_804D799C = 0;
    hsd_804D7980 = (hsd_804D7980 + 1) % 128;
}

#define CMD_QUEUE(base) ((CardRequest*) ((base) + 0x1210))

s32 fn_803AA790(void)
{
    CardRequest* entry;
    s32 result;
    s32 state;

    entry = &((CardRequest*) &hsd_804D2348)[hsd_804D7990];
    state = entry->state;
    hsd_804D7990 = (hsd_804D7990 + 1) % 32;

    switch (entry->type) {
    case 1:
        result = fn_803ADF90((CardState*) entry->state, entry->x8,
                             (u8*) entry->xC, 1, entry->callback);
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(entry->x8, result);
            }
        }
        entry->type = 0;
        return result;
    case 2:
        switch (((s32*) (state + 0x28))[entry->x8]) {
        case 0:
            result = fn_803AE7F8((CardState*) entry->state, entry->x8,
                                 entry->xC, 1, (s32) entry->callback);
            break;
        case 1:
        case 2:
            result = fn_803AF3F0((CardState*) entry->state, entry->x8,
                                 entry->xC, 1, (s32) entry->callback);
            break;
        case 3:
            result = fn_803B0120((CardState*) entry->state, entry->x8,
                                 entry->xC, 1, (s32) entry->callback);
            break;
        default:
            result = -0x101;
            break;
        }
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(entry->x8, result);
            }
        }
        entry->type = 0;
        return result;
    case 3:
        result = fn_803B1F78((CardState*) entry->state, entry->x8, entry->xC,
                             entry->x10, (s32) entry->callback);
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(0, result);
            }
        }
        entry->type = 0;
        return result;
    case 4:
        result = fn_803B21E8(entry->state, entry->xC, entry->x10,
                             (s32) entry->callback);
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(0, result);
            }
        }
        entry->type = 0;
        return result;
    case 5:
        result = fn_803ADE4C(state, entry->x8, (s32) entry->callback);
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(0, result);
            }
        }
        entry->type = 0;
        return result;
    case 6:
        result = fn_803B26CC((CardState*) state, entry->x8, entry->xC,
                             entry->x10, entry->callback);
        if (result < 0) {
            if (entry->callback != NULL) {
                entry->callback(0, result);
            }
        }
        entry->type = 0;
        return result;
    default:
        return -0x101;
    }
}

/// @todo Fix (ideally delete) macros
#undef CMD_TYPE
#undef CMD_STATE

#define CMD_TYPE cmd[0]
#define CMD_STATE ((CardState*) cmd[1])
#define CMD_X8 cmd[2]
#define CMD_XC cmd[3]
#define CMD_X10 cmd[4]
#define CMD_X14 cmd[5]
#define CMD_X18 ((void*) cmd[6])
#define CMD_X1C cmd[7]
#define CMD_X20 cmd[8]

static inline s32 retryCardFastOpen(s32 chan, s32 file_no,
                                    CARDFileInfo* file_info)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDFastOpen(chan, file_no, file_info);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardReadAsync(CARDFileInfo* file_info, void* buffer,
                                     s32 length, s32 offset,
                                     CARDCallback callback)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDReadAsync(file_info, buffer, length, offset, callback);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardWriteAsync(CARDFileInfo* file_info, void* buffer,
                                      s32 length, s32 offset,
                                      CARDCallback callback)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDWriteAsync(file_info, buffer, length, offset, callback);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardClose(CARDFileInfo* file_info)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDClose(file_info);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardCreateAsync(s32 chan, char* filename, s32 size,
                                       CARDFileInfo* file_info,
                                       CARDCallback callback)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDCreateAsync(chan, filename, size, file_info, callback);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardGetStatus(s32 chan, s32 file_no, CARDStat* stat)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDGetStatus(chan, file_no, stat);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline s32 retryCardSetStatusAsync(s32 chan, s32 file_no,
                                          CARDStat* stat,
                                          CARDCallback callback)
{
    s32 i;
    s32 result;

    i = 0;
    do {
        result = CARDSetStatusAsync(chan, file_no, stat, callback);
        if (result != -1) {
            break;
        }
        i++;
    } while (i < 10);

    return result;
}
static inline int setupCardIcons(const s32* cmd)
{
    u32 bit;
    s32 k;

    k = (bit = 0);
    for (; k < 8 && CMD_STATE->icon_speed[(int) k] != 0;) {
        CMD_STATE->stat.iconFormat =
            (CMD_STATE->stat.iconFormat & ~(CARD_STAT_ICON_MASK << bit)) |
            (CMD_STATE->icon_format[(int) k] << bit);
        CMD_STATE->stat.iconSpeed =
            (CMD_STATE->stat.iconSpeed & ~(CARD_STAT_SPEED_MASK << bit)) |
            (CMD_STATE->icon_speed[k++] << bit);
        bit += 2;
    }
    return k;
}
static inline void unpackCardStat(const s32* cmd, CARDStat* stat)
{
    s32 k;

    CMD_STATE->banner_format = stat->bannerFormat & 3;
    for (k = 0; k < 8; k++) {
        CMD_STATE->icon_format[k] =
            (stat->iconFormat >> (2 * k)) & CARD_STAT_ICON_MASK;
        CMD_STATE->icon_speed[k] =
            (stat->iconSpeed >> (2 * k)) & CARD_STAT_SPEED_MASK;
    }
    CMD_STATE->header_size = hsd_803AC340(&CMD_STATE->banner_format);
    {
        u32 used = CMD_STATE->header_size + CMD_STATE->sector_size;
        used += 0x2F;
        CMD_STATE->num_blocks = stat->length / CMD_STATE->sector_size -
                                used / CMD_STATE->sector_size;
    }
}
static inline void rollbackCardCommands(CardContext* context, s32 snap)
{
    s32 saved = snap;

    while (saved != hsd_804D7984) {
        ((CardBufEntry*) &context->state)[saved].xC = 0;
        saved = (saved + 1) % 128;
    }
    hsd_804D7984 = snap;
}
static inline void initHeaderBlockCommand(CardCmd* buf, CardState* state,
                                          u32 block, s32 comment, s32 banner,
                                          s32 icons)
{
    buf->type = 11;
    buf->state = state;
    buf->x8 = block;
    buf->xC = comment;
    buf->x10 = banner;
    buf->x14 = icons;
}
static inline s32 queueHeaderBlock(CardState* state, u32 block, s32 comment,
                                   s32 banner, s32 icons)
{
    CardCmd buf;

    initHeaderBlockCommand(&buf, state, block, comment, banner, icons);
    return fn_803AC168((s32*) &buf);
}
static inline s32 queueHeaderBlocks(CardState* state, s32 comment, s32 banner,
                                    s32 icons)
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
    while (1) {
        CardContext* ctx = (CardContext*) hsd_804D1138;
        CardState** state_ptr = &ctx->state;
        s32* cmd;
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

        if (hsd_804D7988 < 0) {
            while (((CardBufEntry*) hsd_804D1138)[hsd_804D7980].x10 != 0) {
                ((CardBufEntry*) hsd_804D1138)[hsd_804D7980].x10 = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            }
        }

        cmd = (s32*) &((CardBufEntry*) ctx)[hsd_804D7980];
        type = *(cmd += 4);

        switch ((u32) type) {
        case 0:
            if (ctx->req_type != 0) {
                if (ctx->req_type == 3) {
                    s32 file_idx = ctx->callback_arg;
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
                if (ctx->callback != 0) {
                    ctx->callback(ctx->callback_arg, hsd_804D7988);
                }
                ctx->req_type = 0;
            }
            hsd_804D7988 = 0;
            hsd_804D799C = 2;
            if (hsd_804D7990 == hsd_804D7994 &&
                CMD_QUEUE((u8*) ctx)[hsd_804D7990].type == 0)
            {
                return;
            }
            if (fn_803AA790() < 0) {
                return;
            }
            hsd_804D799C = 0;
            continue;
        case 5:
            if (hsd_804D7988 == 2) {
                CMD_TYPE = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            }
            result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                       &CMD_STATE->file_info);
            if (result < 0) {
                hsd_804D7988 = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(&CMD_STATE->file_info,
                                        CMD_STATE->sector_buf,
                                        CMD_STATE->sector_size, CMD_X1C,
                                        (void (*)(s32, s32)) hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                retryCardClose(&CMD_STATE->file_info);
                continue;
            }
            return;
        case 11:
            result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                       &CMD_STATE->file_info);
            if (result < 0) {
                hsd_804D7988 = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
            if (CMD_X8 == 0) {
                memset(CMD_STATE->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &CMD_STATE->file_info, CMD_STATE->sector_buf,
                CMD_STATE->sector_size, CMD_X8 * CMD_STATE->sector_size,
                (void (*)(s32, s32)) hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                retryCardClose(&CMD_STATE->file_info);
                continue;
            }
            return;
        case 10:
            if (hsd_804D7988 == 2) {
                CMD_TYPE = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            }
            result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                       &CMD_STATE->file_info);
            if (result < 0) {
                hsd_804D7988 = result;
                continue;
            }
            hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
            if (CMD_X8 == 0) {
                memset(CMD_STATE->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(
                &CMD_STATE->file_info, CMD_STATE->sector_buf,
                CMD_STATE->sector_size, CMD_X8 * CMD_STATE->sector_size,
                (void (*)(s32, s32)) hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                retryCardClose(&CMD_STATE->file_info);
                continue;
            }
            return;
        case 6:
            if (hsd_804D7988 == 2) {
                hsd_804D7988 = 0;
                CMD_TYPE = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            } else {
                hsd_804D7988 = 1;
                CMD_TYPE = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            }
        case 2:
            if (hsd_804D7988 != 1) {
                result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                           &CMD_STATE->file_info);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardReadAsync(&CMD_STATE->file_info,
                                            CMD_STATE->sector_buf,
                                            CMD_STATE->sector_size, CMD_X1C,
                                            (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    retryCardClose(&CMD_STATE->file_info);
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 15:
            if (hsd_804D7988 != 1) {
                result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                           &CMD_STATE->file_info);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardReadAsync(&CMD_STATE->file_info,
                                            CMD_STATE->sector_buf,
                                            CMD_STATE->sector_size, CMD_X1C,
                                            (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    retryCardClose(&CMD_STATE->file_info);
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 4:
            if (hsd_804D7988 != 1) {
                memset(CMD_X18, 0, CMD_X20);
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 1:
            if (hsd_804D7988 != 1) {
                s32 hdr_offset;
                s32 rem;
                signed int size;
                result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                           &CMD_STATE->file_info);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                if (CMD_X10 > 0) {
                    hdr_offset = 0;
                } else {
                    hdr_offset = (CMD_STATE->header_size + 0x30) %
                                 CMD_STATE->sector_size;
                }
                size = CMD_X20;
                if (size > 0 && CMD_X18 != NULL) {
                    memcpy(&CMD_STATE->sector_buf[hdr_offset + 0x20], CMD_X18,
                           size);
                }
                rem = (CMD_STATE->sector_size - hdr_offset) - size - 0x20;
                if (rem != 0) {
                    memset(&CMD_STATE->sector_buf[hdr_offset + size + 0x20], 0,
                           rem);
                }
                memset(CMD_STATE->sector_buf + hdr_offset, 0, 0x20);
                CMD_STATE->sector_buf[hdr_offset + 0x10] = (u8) (CMD_X10 >> 8);
                CMD_STATE->sector_buf[hdr_offset + 0x11] = (u8) CMD_X10;
                CMD_STATE->sector_buf[hdr_offset + 0x12] = (u8) CMD_X14;
                fn_803AC3F8(CMD_STATE,
                            &CMD_STATE->sector_buf[hdr_offset + 0x13], CMD_X8);
                hsd_803B2FA0(CMD_STATE->sector_buf + hdr_offset,
                             CMD_STATE->sector_size - hdr_offset);
                hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &CMD_STATE->file_info, CMD_STATE->sector_buf,
                    CMD_STATE->sector_size, CMD_X1C,
                    (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    retryCardClose(&CMD_STATE->file_info);
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 16:
            if (hsd_804D7988 != 1) {
                result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                           &CMD_STATE->file_info);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                hsd_803B2FA0(CMD_STATE->sector_buf, CMD_STATE->sector_size);
                hsd_804D798C = CARDGetXferredBytes(CMD_STATE->chan);
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &CMD_STATE->file_info, CMD_STATE->sector_buf,
                    CMD_STATE->sector_size, CMD_X1C,
                    (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    retryCardClose(&CMD_STATE->file_info);
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 7:
            intr2 = OSDisableInterrupts();
            result = retryCardCreateAsync(CMD_STATE->chan, (char*) CMD_X8,
                                          CMD_XC, &CMD_STATE->file_info,
                                          (void (*)(s32, s32)) hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                continue;
            }
            return;
        case 8:
            if (hsd_804D7988 != 1) {
                int k;
                result = retryCardGetStatus(
                    CMD_STATE->chan, CMD_STATE->file_no, &CMD_STATE->stat);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                CMD_STATE->stat.commentAddr = 0;
                CMD_STATE->stat.iconAddr = 0x40;
                CMD_STATE->stat.bannerFormat =
                    (CMD_STATE->stat.bannerFormat & ~3) |
                    CMD_STATE->banner_format;
                k = setupCardIcons(cmd);
                for (; k < 8; k++) {
                    CMD_STATE->stat.iconFormat =
                        CMD_STATE->stat.iconFormat &
                        ~(CARD_STAT_ICON_MASK << (2 * k));
                    CMD_STATE->stat.iconSpeed =
                        CMD_STATE->stat.iconSpeed &
                        ~(CARD_STAT_SPEED_MASK << (2 * k));
                }
                intr2 = OSDisableInterrupts();
                result = retryCardSetStatusAsync(
                    CMD_STATE->chan, CMD_STATE->file_no, &CMD_STATE->stat,
                    (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 9:
            if (hsd_804D7988 != 1) {
                s32 banner_size;
                s32 pos;
                result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                           &CMD_STATE->file_info);
                if (result < 0) {
                    hsd_804D7988 = result;
                    continue;
                }
                switch (CMD_STATE->banner_format) {
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
                if (CMD_X8 == 0) {
                    memcpy(CMD_STATE->sector_buf, CMD_STATE->comment, 0x40);
                    pos = 0x40;
                    if (banner_size > 0) {
                        memcpy(CMD_STATE->sector_buf + 0x40, (void*) CMD_XC,
                               banner_size);
                        pos = banner_size + 0x40;
                    }
                    memset(CMD_STATE->digest, 0, 0x30);
                    if (CMD_STATE->header_size > CMD_STATE->sector_size) {
                        memcpy(&CMD_STATE->sector_buf[pos], (void*) CMD_X10,
                               CMD_STATE->sector_size - pos);
                        hsd_803B2B20(CMD_STATE->sector_buf,
                                     CMD_STATE->sector_size,
                                     &CMD_STATE->digest[CMD_X8 * 0x10]);
                    } else {
                        memcpy(&CMD_STATE->sector_buf[pos], (void*) CMD_X10,
                               CMD_STATE->header_size - pos);
                        hsd_803B2B20(CMD_STATE->sector_buf,
                                     CMD_STATE->header_size,
                                     &CMD_STATE->digest[CMD_X8 * 0x10]);
                        memcpy(&CMD_STATE->sector_buf[CMD_STATE->header_size],
                               CMD_STATE->digest, 0x30);
                    }
                } else {
                    u32 remaining = CMD_STATE->header_size -
                                    CMD_STATE->sector_size * CMD_X8;
                    s32 icons_offset =
                        (CMD_STATE->sector_size * CMD_X8 - 0x40) - banner_size;
                    if (remaining > CMD_STATE->sector_size) {
                        memcpy(CMD_STATE->sector_buf,
                               (u8*) CMD_X10 + icons_offset,
                               CMD_STATE->sector_size);
                        hsd_803B2B20(CMD_STATE->sector_buf,
                                     CMD_STATE->sector_size,
                                     &CMD_STATE->digest[CMD_X8 * 0x10]);
                    } else {
                        memcpy(CMD_STATE->sector_buf,
                               (u8*) CMD_X10 + icons_offset, remaining);
                        hsd_803B2B20(CMD_STATE->sector_buf, remaining,
                                     &CMD_STATE->digest[CMD_X8 * 0x10]);
                        memcpy(&CMD_STATE->sector_buf[remaining],
                               CMD_STATE->digest, 0x30);
                    }
                }
                intr2 = OSDisableInterrupts();
                result = retryCardWriteAsync(
                    &CMD_STATE->file_info, CMD_STATE->sector_buf,
                    CMD_STATE->sector_size, CMD_STATE->sector_size * CMD_X8,
                    (void (*)(s32, s32)) hsd_803A949C);
                hsd_804D799C = 1;
                OSRestoreInterrupts(intr2);
                if (result < 0) {
                    hsd_804D799C = 0;
                    retryCardClose(&CMD_STATE->file_info);
                    hsd_804D7988 = result;
                    continue;
                }
                return;
            }
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 12: {
            s32 retries;
            CARDStat stat;
            s32 i;
            s32 file_no;
            CMD_STATE->file_no = CMD_X8;
            file_no = CMD_STATE->file_no;
            chan = CMD_STATE->chan;
            for (i = 0; i < 10; i++) {
                result = CARDGetStatus(chan, file_no, &stat);
                if (result != -1) {
                    break;
                }
            }
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
            } else {
                unpackCardStat(cmd, &stat);
                if (stat.iconAddr != 0x40) {
                    hsd_804D7988 = -0x106;
                    hsd_804D799C = 0;
                } else {
                    CMD_TYPE = 0;
                    hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                }
            }
            continue;
        }
        case 13:
            result = retryCardFastOpen(CMD_STATE->chan, CMD_STATE->file_no,
                                       &CMD_STATE->file_info);
            if (result < 0) {
                hsd_804D7988 = result;
                continue;
            }
            intr2 = OSDisableInterrupts();
            result = retryCardReadAsync(&CMD_STATE->file_info,
                                        CMD_STATE->sector_buf,
                                        CMD_STATE->sector_size, CMD_X1C,
                                        (void (*)(s32, s32)) hsd_803A949C);
            hsd_804D799C = 1;
            OSRestoreInterrupts(intr2);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                retryCardClose(&CMD_STATE->file_info);
                continue;
            }
            return;
        case 14:
            result = fn_803AD16C(CMD_STATE);
            if (result < 0) {
                hsd_804D7988 = result;
                hsd_804D799C = 0;
            } else {
                CMD_TYPE = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            }
            continue;
        case 17: {
            s32 blk;

            fn_803AC2D4();
            result = fn_803ACF30(CMD_STATE, 0, 0, 0);
            if (result < 0) {
                fn_803AC2E0();
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                continue;
            }
            for (blk = 0; blk <= CMD_STATE->num_blocks; blk++) {
                result = fn_803AC258(CMD_STATE, blk);
                if (result < 0) {
                    fn_803AC2E0();
                    hsd_804D7988 = result;
                    hsd_804D799C = 0;
                    goto next;
                }
            }
            result = fn_803AC2A4(CMD_STATE);
            if (result < 0) {
                fn_803AC2E0();
                hsd_804D7988 = result;
                hsd_804D799C = 0;
                continue;
            }
            fn_803AC334();
            CMD_TYPE = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        }
        default:
            return;
        }
    next:
        continue;
    }
}

s32 fn_803AC168(s32* cmd_buf)
{
    BOOL intr;
    s32 mode;
    s32 read_idx;
    s32 head_type;

    intr = OSDisableInterrupts();
    read_idx = hsd_804D7980;
    mode = hsd_804D799C;
    head_type = (s32) hsd_804D1148[hsd_804D7980][0];
    OSRestoreInterrupts(intr);

    if (mode != 2) {
        if (hsd_804D7984 == read_idx) {
            if (mode != 0 || hsd_804D7984 != read_idx || head_type != 0) {
                return -265;
            }
        }
    }

    {
        s32 idx = hsd_804D7984;
        hsd_804D7984 = (hsd_804D7984 + 1) % 128;
        memcpy((u8*) hsd_804D1148[idx], cmd_buf, sizeof(CardCmd));
    }

    if (mode == 2) {
        hsd_804D799C = 0;
    }
    return 0;
}

s32 fn_803AC258(CardState* state, s32 block_idx)
{
    CardCmd cmd;
    cmd.type = 13;
    cmd.state = state;
    cmd.x10 = block_idx;
    cmd.x14 = 0;
    cmd.data = NULL;
    cmd.size = 0;
    cmd.offset = fn_803ACBE8(state, block_idx);
    return fn_803AC168((s32*) &cmd);
}

s32 fn_803AC2A4(CardState* state)
{
    CardCmd cmd;
    cmd.type = 14;
    cmd.state = state;
    return fn_803AC168((s32*) &cmd);
}

void fn_803AC2D4(void)
{
    hsd_804D7998 = hsd_804D7984;
}

void fn_803AC2E0(void)
{
    s32 saved;

    if (hsd_804D7998 < 0) {
        return;
    }
    saved = hsd_804D7998;
    while (saved != hsd_804D7984) {
        hsd_804D1148[saved][0] = 0;
        saved = (saved + 1) % 128;
    }
    hsd_804D7984 = hsd_804D7998;
}

void fn_803AC334(void)
{
    hsd_804D7998 = -1;
}

int hsd_803AC340(void* icon_info)
{
    u8* data = icon_info;
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
    i = 0;
    while (i < 8 && data[i + 0xA] != 0) {
        switch (data[i + 0x2]) {
        case 2:
            icon_size += 0x800;
            break;
        case 1:
            has_c8 = 1;
            icon_size += 0x400;
            break;
        }
        i++;
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

void fn_803AC3F8(void* card_state, u8* data, s32 file_idx)
{
    CardState* state = card_state;
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
        return (u32) (remaining + sector_size - 0x21) / usable + 1;
    }

    {
        u32 sector_size = state->sector_size;
        return (u32) (state->file_sizes[file_idx] + sector_size - 0x21) /
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
        return (u32) (remaining + sector_size - 0x21) / usable + 1;
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
                blocks = (u32) (remaining + sector_size - 0x21) / usable + 1;
            }
        } else {
            sector_size = state->sector_size;
            blocks =
                (u32) (file_size + sector_size - 0x21) / (sector_size - 0x20);
        }
        total += blocks;
    }

    return total;
}

static inline s32 fn_803AC6B8_blocks_before(CardState* state, s32 file_idx)
{
    u8* total;
    s32 i;

    if (file_idx >= 9) {
        return 0;
    }
    if (file_idx == 0) {
        return 0;
    }

    total = (u8*) 1;
    if (state->file_sizes[0] > 0) {
        total = (u8*) &((CardState*) fn_803AC634(state, 0))->sector_size;
        total -= 8;
    }

    for (i = 1; i < file_idx; i++) {
        total += fn_803AC634(state, i);
    }

    return (s32) total;
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
            blocks = (u32) (remaining + sector_size - 0x21) / usable + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        blocks = (u32) (state->file_sizes[file_idx] + sector_size - 0x21) /
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
    u8* hdr;
    u32 read_offset;
    s32 hdr_offset;
    PAD_STACK(4);

    if (data_size == 0) {
        return 0;
    }

    sector_size = state->sector_size;
    retries = 0;
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

    for (; retries < 10; retries++) {
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

    hdr = state->sector_buf + hdr_offset;
    if (block_id != ((hdr[0x10] << 8) | hdr[0x11])) {
        return 1;
    }

    if (seq_num != hdr[0x12]) {
        return 1;
    }

    if (memcmp(expected_data, hdr + 0x20, data_size) != 0) {
        return 1;
    }

    return 0;
}

s32 fn_803ACD58(CardState* state, void* banner, void* icons)
{
    s32 banner_size;
    s32 i;
    s32 icons_start;

    switch (state->banner_format) {
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

s32 fn_803ACF30(CardState* state, s32 comment, s32 banner, s32 icons)
{
    CardCmd buf;
    s32 ret;
    u32 i;
    PAD_STACK(4);

    for (i = 0; i < (0x2F + state->header_size + state->sector_size) /
                        state->sector_size;
         i++)
    {
        buf.type = 11;
        buf.state = state;
        buf.x8 = i;
        buf.xC = comment;
        buf.x10 = banner;
        buf.x14 = icons;
        ret = fn_803AC168((s32*) &buf);
        if (ret < 0) {
            return ret;
        }
    }
    return 0;
}

typedef u8* CardSectorPtr;

static inline u8* fn_803ACFC0_header(CardState* state, s32 hdr_offset)
{
    return (CardSectorPtr) (hdr_offset + (s32) state->sector_buf);
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
            memset((CardSectorPtr) (hdr_offset + off + addr), 0, remaining);
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

static inline int fn_803AD16C_file_type_nonzero(CardState* state, s32 file_idx)
{
    return state->file_flags[file_idx] != 0;
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

static inline s32 fn_803AD16C_seq_at(s32* seq, s32 phys)
{
    return seq[phys];
}

static inline int fn_803AD16C_nonnegative(s32 logical)
{
    return logical >= 0;
}

static inline s32 fn_803AD16C_queue_cmd(s32* cmd)
{
    return fn_803AC168(cmd);
}

static inline int fn_803AD16C_same(s32 lhs, s32 rhs)
{
    return lhs == rhs;
}

static inline void fn_803AD16C_own(void* value)
{
    (void) value;
}

static inline s32 fn_803AD16C_queue_clear(CardState* state, s32 phys,
                                          s32 offset, s32 file_idx)
{
    s32 cmd[9];

    cmd[0] = 1;
    cmd[1] = (s32) state;
    cmd[3] = phys;
    cmd[4] = 0xFFFF;
    cmd[5] = 0;
    cmd[6] = 0;
    cmd[8] = 0;
    cmd[7] = offset;
    cmd[2] = file_idx;
    return fn_803AD16C_queue_cmd(cmd);
}

static inline s32 fn_803AD16C_queue_read(CardState* state, s32 phys)
{
    s32 cmd[8];
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;
    s32 offset;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;
    offset = size * idx;

    cmd[0] = 0xF;
    cmd[1] = (s32) state;
    cmd[3] = phys;
    cmd[7] = offset;
    return fn_803AC168(cmd);
}

static inline s32 fn_803AD16C_queue_write(CardState* state, s32 phys,
                                          s32 block_id, s32 seq)
{
    s32 cmd[8];
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;
    s32 offset;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;
    offset = size * idx;

    cmd[0] = 0x10;
    cmd[1] = (s32) state;
    cmd[3] = phys;
    cmd[4] = block_id;
    cmd[5] = seq;
    cmd[7] = offset;
    return fn_803AC168(cmd);
}

static inline s32 fn_803AD16C_queue_write_last(CardState* state, s32 phys,
                                               s32 block_id, s32 seq)
{
    s32 tail[2];
    s32 cmd[8];
    u32 size = state->sector_size;
    u32 temp = state->header_size + size;
    u32 num = temp + 0x2F;
    u32 idx;
    s32 offset;

    temp = num / size;
    idx = temp - 1;
    idx = phys + idx;
    offset = size * idx;

    cmd[0] = 0x10;
    cmd[1] = (s32) state;
    cmd[3] = phys;
    cmd[4] = block_id;
    cmd[5] = seq;
    cmd[7] = offset;
    fn_803AD16C_own(tail);
    return fn_803AC168(cmd);
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
                            fn_803ACB74(cur_seq,
                                        fn_803AD16C_seq_at(seq, phys)) > 0)
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
            fn_803AD16C_file_type_nonzero(state, file_idx))
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

            if (fn_803AD16C_same(file_idx, file_idx)) {
                (void) block_id;
            }

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

s32 fn_803ADE4C(s32 state, s32 file_no, s32 callback)
{
    CardCmd cmd_open;
    CardCmd cmd_mount;
    s32 result;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(16);

    hsd_804D7998 = hsd_804D7984;
    cmd_open.type = 12;
    cmd_open.state = (CardState*) state;
    cmd_open.x8 = file_no;
    result = fn_803AC168((s32*) &cmd_open);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved1].x10 = 0;
                saved1 = (saved1 + 1) % 128;
            }
            hsd_804D7984 = snap1;
        }
        return result;
    }

    cmd_mount.type = 17;
    cmd_mount.state = (CardState*) state;
    result = fn_803AC168((s32*) &cmd_mount);
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved].x10 = 0;
                saved = (saved + 1) % 128;
            }
            hsd_804D7984 = snap;
        }
        return result;
    }

    entries[0].x0 = 5;
    entries[0].x4 = state;
    entries[0].x8 = callback;
    entries[0].xC = 0;
    hsd_804D7998 = -1;
    return 0;
}

static inline s32 queueCardReadCommand(CardState* state, s32 block, void* data,
                                       s32 length, s32 offset)
{
    CardCmd command;

    command.type = 2;
    command.state = state;
    command.x10 = block;
    command.x14 = 0;
    command.data = data;
    command.size = length;
    command.offset = offset;
    return fn_803AC168((s32*) &command);
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
            return (u32) (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        return (u32) (file_size + sector_size - 0x21) / (sector_size - 0x20);
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

static inline void cancelQueuedCardCommands(CardBufEntry* entries)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != hsd_804D7984) {
            CardBufEntry* queued = &entries[saved];
            saved = (saved + 1) % 128;
            queued->x10 = zero = 0;
        }
        hsd_804D7984 = snap;
    }
}

static inline s32 queueCardClearCommand(CardState* state, u8* dst, s32 size)
{
    CardCmd command;

    command.type = 4;
    command.state = state;
    command.x10 = 0;
    command.x14 = 0;
    command.data = dst;
    command.size = size;
    command.offset = 0;
    command.x8 = 0;
    return fn_803AC168((s32*) &command);
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

s32 fn_803ADF90(CardState* state, s32 file_idx, u8* buf, s32 async,
                void (*callback)(s32, s32))
{
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
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
        hsd_804D7998 = hsd_804D7984;
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
                        cancelQueuedCardCommands(entries);
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
                    cancelQueuedCardCommands(entries);
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
                        cancelQueuedCardCommands(entries);
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
        entries[0].x0 = 1;
        entries[0].x4 = (s32) state;
        entries[0].x8 = (s32) callback;
        entries[0].xC = file_idx;
        hsd_804D7998 = -1;
    }

    return status;
}

static inline void fn_803AE7F8_rewind(CardBufEntry* entries)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != hsd_804D7984) {
            CardBufEntry* queued = &entries[saved];
            saved = (saved + 1) % 128;
            queued->x10 = zero = 0;
        }
        hsd_804D7984 = snap;
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

s32 fn_803AE7F8(CardState* state, s32 file_idx, s32 buf, s32 async,
                s32 callback)
{
    CardState* st = state;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    s32 block_map[3][64];
    UNUSED u8 pad_block_map[32];
    CardCmd cmd_done;
    s32* block_map_ptr;
    s32 blocks_before;
    s32 current_seq;
    s32 file_blocks;
    s32 file_size;
    s32 free_count;
    s32 i;
    s32 logical;
    CardState* row;
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

    for (i = 1, row = (CardState*) ((s32*) st + 1); i <= total_blocks;
         row = (CardState*) ((s32*) row + 1), i++)
    {
        s32 block_id = row->block_ids[0];

        if (block_id < 0) {
            block_map[2][free_count++] = i;
            continue;
        }

        logical = block_id - blocks_before;
        if (0 <= logical && logical < file_blocks) {
            if (current_seq == -1 ||
                fn_803ACB74(current_seq, row->block_seqs[0]) < 0)
            {
                current_seq = row->block_seqs[0];
            }
            if (block_map[0][logical] < 0) {
                block_map[0][logical] = i;
            } else {
                block_map[1][logical] = i;
            }
        }
    }

    block_map_ptr = block_map[0];
    for (i = 0; i < file_blocks; i++) {
        if (block_map_ptr[i] < 0 ||
            st->block_seqs[block_map_ptr[i]] != current_seq)
        {
            verify_failed = 1;
            break;
        }
        if (block_map_ptr[64 + i] < 0 ||
            st->block_seqs[block_map_ptr[64 + i]] != current_seq)
        {
            verify_failed = 1;
            break;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map_ptr[i] < 0) {
            if (free_count > 0) {
                block_map_ptr[i] = block_map[2][--free_count];
            } else {
                return -257;
            }
        }
        if (block_map_ptr[64 + i] < 0) {
            if (free_count > 0) {
                block_map_ptr[64 + i] = block_map[2][--free_count];
            } else {
                repair_result = -258;
            }
        }
    }

    if (async != 0) {
        hsd_804D7998 = hsd_804D7984;
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
        s32* map;
        s32 pass;

        pass = 0;
        map = block_map_ptr;
        for (; pass < 2; pass++, map += 64) {
            s32 remaining = file_size;

            data = (u8*) buf;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys;
                s32 chunk = st->sector_size;

                chunk -= 0x20;
                if ((u32) remaining > (u32) chunk) {
                    phys = map[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 cmd_result;
                            if (chunk == 0) {
                                cmd_result = 0;
                            } else {
                                s32 ofs = fn_803ACBE8(state, phys);
                                CardCmd cmd;

                                cmd.type = 5;
                                cmd.state = state;
                                cmd.x10 = blocks_before + i;
                                cmd.x14 = current_seq;
                                cmd.data = data;
                                cmd.size = chunk;
                                cmd.offset = ofs;
                                cmd_result = fn_803AC168((s32*) &cmd);
                            }
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind(entries);
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
                    phys = map[i];
                    if (phys >= 0) {
                        if (async != 0) {
                            s32 cmd_result;
                            if (remaining == 0) {
                                cmd_result = 0;
                            } else {
                                s32 ofs = fn_803ACBE8(state, phys);
                                CardCmd cmd;

                                cmd.type = 5;
                                cmd.state = state;
                                cmd.x10 = blocks_before + i;
                                cmd.x14 = current_seq;
                                cmd.data = data;
                                cmd.size = remaining;
                                cmd.offset = ofs;
                                cmd_result = fn_803AC168((s32*) &cmd);
                            }
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind(entries);
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

            cmd_done.type = 6;
            cmd_done.state = state;
            cmd_result = fn_803AC168((s32*) &cmd_done);
            if (cmd_result < 0) {
                fn_803AE7F8_rewind(entries);
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
        s32* map = block_map_ptr;

        for (pass = 0; pass < 2; pass++, map += 64) {
            s32 remaining = file_size;

            data = (u8*) buf;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys;
                s32 chunk;

                if ((u32) remaining > (u32) (chunk = st->sector_size - 0x20)) {
                    phys = map[i];
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
                                init_cmd.type = 2;
                                init_cmd.state = state;
                                init_cmd.x10 = zero;
                                init_cmd.x14 = zero;
                                init_cmd.data = (void*) zero;
                                init_cmd.size = zero;
                                init_cmd.offset = ofs;
                                fn_803AC168((s32*) &init_cmd);
                            }
                            cmd.type = 1;
                            cmd.state = state;
                            cmd.xC = phys;
                            cmd.x10 = blocks_before + i;
                            cmd.x14 = current_seq;
                            cmd.data = data;
                            cmd.size = chunk;
                            cmd.offset = ofs;
                            cmd.x8 = file_idx;
                            cmd_result = fn_803AC168((s32*) &cmd);
                        repair_full_queued:
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind(entries);
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
                            st->block_ids[map[i]] = blocks_before + i;
                            st->block_seqs[map[i]] = current_seq;
                        }
                    }

                    remaining -= st->sector_size - 0x20;
                    data += st->sector_size - 0x20;
                } else {
                    phys = map[i];
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
                                init_cmd.type = 2;
                                init_cmd.state = state;
                                init_cmd.x10 = zero;
                                init_cmd.x14 = zero;
                                init_cmd.data = (void*) zero;
                                init_cmd.size = zero;
                                init_cmd.offset = ofs;
                                fn_803AC168((s32*) &init_cmd);
                            }
                            cmd.type = 1;
                            cmd.state = state;
                            cmd.xC = phys;
                            cmd.x10 = blocks_before + i;
                            cmd.x14 = current_seq;
                            cmd.data = data;
                            cmd.size = remaining;
                            cmd.offset = ofs;
                            cmd.x8 = file_idx;
                            cmd_result = fn_803AC168((s32*) &cmd);
                        repair_tail_queued:
                            if (cmd_result < 0) {
                                fn_803AE7F8_rewind(entries);
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
                            st->block_ids[map[i]] = blocks_before + i;
                            st->block_seqs[map[i]] = current_seq;
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
        CardBufEntry* entry = entries;

        entry->x0 = 2;
        entry->x4 = (s32) state;
        entry->x8 = callback;
        entry->xC = file_idx;
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
        cmd.type = 5;
        cmd.state = state;
        cmd.x10 = block_id;
        cmd.x14 = seq;
        cmd.data = data;
        cmd.size = size;
        cmd.offset = ofs;
        return fn_803AC168((s32*) &cmd);
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
        cmd.type = 5;
        cmd.state = state;
        cmd.x10 = block_id;
        cmd.x14 = seq;
        cmd.data = data;
        cmd.size = size;
        cmd.offset = ofs;
        result = fn_803AC168((s32*) &cmd);
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
        init_cmd.type = 2;
        init_cmd.state = state;
        init_cmd.x10 = zero;
        init_cmd.x14 = zero;
        init_cmd.data = (void*) zero;
        init_cmd.size = zero;
        init_cmd.offset = ofs;
        fn_803AC168((s32*) &init_cmd);
    }
    cmd.type = 1;
    cmd.state = state;
    cmd.xC = phys;
    cmd.x10 = block_id;
    cmd.x14 = seq;
    cmd.data = data;
    cmd.size = size;
    cmd.offset = ofs;
    cmd.x8 = file_idx;
    return fn_803AC168((s32*) &cmd);
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
        init_cmd.type = 2;
        init_cmd.state = state;
        init_cmd.x10 = zero;
        init_cmd.x14 = zero;
        init_cmd.data = (void*) zero;
        init_cmd.size = zero;
        init_cmd.offset = ofs;
        fn_803AC168((s32*) &init_cmd);
    }
    cmd.type = 1;
    cmd.state = state;
    cmd.xC = phys;
    cmd.x10 = block_id;
    cmd.x14 = seq;
    cmd.data = data;
    cmd.size = size;
    cmd.offset = ofs;
    cmd.x8 = file_idx;
    result = fn_803AC168((s32*) &cmd);
    return result;
}

static inline void fn_803AF3F0_rewind(CardBufEntry* entries)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != hsd_804D7984) {
            CardBufEntry* queued = &entries[saved];
            saved = (saved + 1) % 128;
            queued->x10 = zero = 0;
        }
        hsd_804D7984 = snap;
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
                (u32) (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->sector_size;
        *file_blocks =
            (u32) (state->file_sizes[file_idx] + sector_size - 0x21) /
            (sector_size - 0x20);
    }

    *total_blocks = fn_803AC7DC(state);
}

s32 fn_803AF3F0(CardState* state, s32 file_idx, s32 buf, s32 async,
                s32 callback)
{
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
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
        hsd_804D7998 = hsd_804D7984;
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
        data = (u8*) buf;
        for (i = 0; i < file_blocks && remaining > 0; i++) {
            if ((u32) remaining > (u32) fn_803AF3F0_chunk_size(state)) {
                if (async != 0) {
                    s32 block = block_map[0][i];
                    s32 cmd_result = fn_803AF3F0_queue_verify_first(
                        state, block, blocks_before + i, current_seq, data,
                        fn_803AF3F0_chunk_size(state));
                    if (cmd_result < 0) {
                        fn_803AF3F0_rewind(entries);
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
                        fn_803AF3F0_rewind(entries);
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
            cmd.type = 6;
            cmd.state = state;
            cmd_result = fn_803AC168((s32*) &cmd);
            if (cmd_result < 0) {
                fn_803AF3F0_rewind(entries);
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
                    fn_803AF3F0_rewind(entries);
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
        data = (u8*) buf;
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
                    fn_803AF3F0_rewind(entries);
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
                    fn_803AF3F0_rewind(entries);
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
        CardBufEntry* entry = entries;

        entry->x0 = 3;
        entry->x4 = (s32) state;
        entry->x8 = callback;
        entry->xC = file_idx;
        hsd_804D7998 = -1;
    }

    return 0;
}

static inline s32 fn_803B0120_first_chunk(CardState* state)
{
    u32 sector_size = state->sector_size;

    return (s32) (sector_size - 0x20) -
           (s32) ((u32) (state->header_size + 0x30) % sector_size);
}

static inline void fn_803B0120_rewind(CardBufEntry* entries)
{
    s32 snap = hsd_804D7998;

    if (snap >= 0) {
        s32 saved = snap;
        s32 zero;

        while (saved != hsd_804D7984) {
            CardBufEntry* queued = &entries[saved];
            saved = (saved + 1) % 128;
            queued->x10 = zero = 0;
        }
        hsd_804D7984 = snap;
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
        cmd.type = 5;
        cmd.state = state;
        cmd.x10 = block_id;
        cmd.x14 = seq;
        cmd.data = data;
        cmd.size = size;
        cmd.offset = ofs;
        result = fn_803AC168((s32*) &cmd);
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
        init_cmd.type = 2;
        init_cmd.state = state;
        init_cmd.x10 = zero;
        init_cmd.x14 = zero;
        init_cmd.data = (void*) zero;
        init_cmd.size = zero;
        init_cmd.offset = ofs;
        fn_803AC168((s32*) &init_cmd);
    }
    cmd.type = 1;
    cmd.state = state;
    cmd.xC = phys;
    cmd.x10 = block_id;
    cmd.x14 = seq;
    cmd.data = data;
    cmd.size = size;
    cmd.offset = ofs;
    cmd.x8 = file_idx;
    result = fn_803AC168((s32*) &cmd);
    return result;
}

s32 fn_803B0120(CardState* state, s32 file_idx, s32 buf, s32 async,
                s32 callback)
{
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
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
        hsd_804D7998 = hsd_804D7984;
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
        data = (u8*) buf;
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
                        fn_803B0120_rewind(entries);
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
                        fn_803B0120_rewind(entries);
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
            cmd.type = 6;
            cmd.state = state;
            cmd_result = fn_803AC168((s32*) &cmd);
            if (cmd_result < 0) {
                fn_803B0120_rewind(entries);
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
                fn_803B0120_rewind(entries);
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
        data = (u8*) buf;
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
                    fn_803B0120_rewind(entries);
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
                    fn_803B0120_rewind(entries);
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
        entries[0].x0 = 4;
        entries[0].x4 = (s32) state;
        entries[0].x8 = callback;
        entries[0].xC = file_idx;
        hsd_804D7998 = -1;
    }
    PAD_STACK(4);

    return 0;
}

static inline s32 fn_803B0E9C_read_icons(CardState* state, CardCmd* cmd,
                                         s32 banner, s32 icons)
{
    u32 block_idx;
    s32 result;

    for (block_idx = 0;
         block_idx <
         (0x2F + state->header_size + state->sector_size) / state->sector_size;
         block_idx++)
    {
        cmd->type = 10;
        cmd->state = state;
        cmd->xC = banner;
        cmd->x10 = icons;
        cmd->x8 = block_idx;
        result = fn_803AC168((s32*) cmd);
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

s32 fn_803B0E9C(CardState* state, s32 banner, s32 icons, s32 is_new, s32 async)
{
    u8 digest[0x30];
    CardCmd cmd_done;
    CardCmd cmd_clear;
    UNUSED u8 pad_cmd_clear[4];
    CardCmd cmd_patch;
    UNUSED u8 pad_cmd_patch[8];
    CardCmd cmd_write_icon;
    UNUSED u8 pad_cmd_write_icon[16];
    CardCmd cmd_read_icon;
    UNUSED u8 pad_cmd_read_icon[8];
    s32 remaining;
    s32 payload_pos;
    s32 block_idx;
    s32 result;
    s32 has_blocks;
    u32 sector_size;

    state->header_size = hsd_803AC340(&state->banner_format);

    if (is_new == 0) {
        if (async != 0) {
            result =
                fn_803B0E9C_read_icons(state, &cmd_read_icon, banner, icons);
            if (result < 0) {
                return result;
            }

            {
                cmd_done.type = 6;
                cmd_done.state = state;
                result = fn_803AC168((s32*) &cmd_done);
            }
            if (result < 0) {
                return result;
            }
        } else {
            result = fn_803ACD58(state, (UNK_T) banner, (UNK_T) icons);
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
                    cmd_clear.type = 4;
                    cmd_clear.state = state;
                    cmd_clear.x10 = zero;
                    cmd_clear.x14 = zero;
                    cmd_clear.data = clear_buf;
                    cmd_clear.size = sector_size;
                    cmd_clear.offset = zero;
                    cmd_clear.x8 = zero;
                    result = fn_803AC168((s32*) &cmd_clear);
                } else {
                    if (state->file_sizes[0] > 0) {
                        has_blocks = 1;
                    } else {
                        has_blocks = 0;
                    }
                    cmd_patch.type = 2;
                    cmd_patch.state = state;
                    cmd_patch.x10 = -1;
                    cmd_patch.x14 = 0;
                    cmd_patch.data = NULL;
                    cmd_patch.size = has_blocks;
                    cmd_patch.offset = async * sector_size;
                    result = fn_803AC168((s32*) &cmd_patch);
                }
                if (result < 0) {
                    return result;
                }
            }

            {
                cmd_write_icon.type = 9;
                cmd_write_icon.state = state;
                cmd_write_icon.x8 = async;
                cmd_write_icon.xC = banner;
                cmd_write_icon.x10 = icons;
                result = fn_803AC168((s32*) &cmd_write_icon);
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

    memcpy(state->sector_buf, state->comment, 0x40);
    payload_pos = 0x40;
    switch (state->banner_format) {
    case 2: {
        void* dst = state->sector_buf + 0x40;
        memcpy(dst, (UNK_T) banner, 0x1800);
    }
        payload_pos = 0x1840;
        break;
    case 1: {
        void* dst = state->sector_buf + 0x40;
        memcpy(dst, (UNK_T) banner, 0xE00);
    }
        payload_pos = 0xE40;
        break;
    }

    memset(digest, 0, sizeof(digest));
    block_idx = 0;
    remaining = state->header_size - payload_pos;

    while (remaining >= 0) {
        sector_size = state->sector_size;
        if ((u32) (payload_pos + remaining) > sector_size) {
            memcpy(state->sector_buf + payload_pos, (s32*) icons,
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

        memcpy(state->sector_buf + payload_pos, (void*) icons, remaining);
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
        init_buf->cmd.type = 2;
        init_buf->cmd.state = state;
        init_buf->cmd.x10 = 0;
        init_buf->cmd.x14 = 0;
        init_buf->cmd.data = NULL;
        init_buf->cmd.size = 0;
        init_buf->cmd.offset = ofs;
        fn_803AC168(init_buf->words);
    }
    buf->cmd.type = 1;
    buf->cmd.state = state;
    buf->cmd.xC = phys;
    buf->cmd.x10 = block_id;
    buf->cmd.x14 = 0;
    buf->cmd.data = data;
    buf->cmd.size = size;
    buf->cmd.offset = ofs;
    buf->cmd.x8 = file_idx;
    result = fn_803AC168(buf->words);
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
        init_buf->cmd.type = 2;
        init_buf->cmd.state = state;
        init_buf->cmd.x10 = 0;
        init_buf->cmd.x14 = 0;
        init_buf->cmd.data = NULL;
        init_buf->cmd.size = 0;
        init_buf->cmd.offset = ofs;
        fn_803AC168(init_buf->words);
    }
    buf->cmd.type = 1;
    buf->cmd.state = state;
    buf->cmd.xC = phys;
    buf->cmd.x10 = block_id;
    buf->cmd.x14 = 0;
    buf->cmd.data = data;
    buf->cmd.size = size;
    buf->cmd.offset = ofs;
    buf->cmd.x8 = file_idx;
    result = fn_803AC168(buf->words);
    return result;
}

s32 fn_803B1338(CardState* state, s32 async)
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
                    cmd0.cmd.type = 2;
                    cmd0.cmd.state = state;
                    cmd0.cmd.x10 = 0;
                    cmd0.cmd.x14 = 0;
                    cmd0.cmd.data = NULL;
                    cmd0.cmd.size = 0;
                    cmd0.cmd.offset = ofs0;
                    fn_803AC168(cmd0.words);
                    cmd1.cmd.type = 1;
                    cmd1.cmd.state = state;
                    cmd1.cmd.xC = 0;
                    cmd1.cmd.x10 = 0;
                    cmd1.cmd.x14 = 0;
                    cmd1.cmd.data = NULL;
                    cmd1.cmd.size = 0;
                    cmd1.cmd.offset = ofs0;
                    cmd1.cmd.x8 = 0;
                    result = fn_803AC168(cmd1.words);
                } else {
                    s32 ofs0 =
                        sector_size *
                        ((data_start + sector_size - 1) / sector_size - 1);
                    cmd2.cmd.type = 2;
                    cmd2.cmd.state = state;
                    cmd2.cmd.x10 = 0;
                    cmd2.cmd.x14 = 0;
                    cmd2.cmd.data = NULL;
                    cmd2.cmd.size = 0;
                    cmd2.cmd.offset = ofs0;
                    fn_803AC168(cmd2.words);
                    cmd3.cmd.type = 1;
                    cmd3.cmd.state = state;
                    cmd3.cmd.xC = 0;
                    cmd3.cmd.x10 = 0;
                    cmd3.cmd.x14 = 0;
                    cmd3.cmd.data = fdata;
                    cmd3.cmd.size = sector_size - hdr_offset - 0x20;
                    cmd3.cmd.offset = ofs0;
                    cmd3.cmd.x8 = 0;
                    result = fn_803AC168(cmd3.words);
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
                        result = CARD_WRITE_BLOCK(state, phys, block_id, 0,
                                                  NULL, 0, 0);
                    } else {
                        result = CARD_WRITE_BLOCK(
                            state, phys, block_id, 0, fdata + offset,
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

s32 fn_803B1F78(CardState* state, s32 filename, s32 banner, s32 icons,
                s32 callback)
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
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(12);

    hsd_804D7998 = hsd_804D7984;
    file_size = state->sector_size * hsd_803B2674(state);
    cmd_create.type = 7;
    cmd_create.state = state;
    cmd_create.x8 = filename;
    cmd_create.xC = file_size;
    result = fn_803AC168((s32*) &cmd_create);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved1].x10 = 0;
                saved1 = (saved1 + 1) % 128;
            }
            hsd_804D7984 = snap1;
        }
        return result;
    }

    result = fn_803B0E9C(state, banner, icons, 1, 1);
    if (result < 0) {
        snap2 = hsd_804D7998;
        if (snap2 >= 0) {
            saved2 = snap2;
            while (saved2 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved2].x10 = 0;
                saved2 = (saved2 + 1) % 128;
            }
            hsd_804D7984 = snap2;
        }
        return result;
    }

    result = fn_803B1338(state, 1);
    if (result < 0) {
        snap3 = hsd_804D7998;
        if (snap3 >= 0) {
            saved3 = snap3;
            while (saved3 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved3].x10 = 0;
                saved3 = (saved3 + 1) % 128;
            }
            hsd_804D7984 = snap3;
        }
        return result;
    }

    cmd_set_status.type = 8;
    cmd_set_status.state = state;
    result = fn_803AC168((s32*) &cmd_set_status);
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved].x10 = 0;
                saved = (saved + 1) % 128;
            }
            hsd_804D7984 = snap;
        }
        return result;
    }

    entries[0].x0 = 6;
    entries[0].x4 = (s32) state;
    entries[0].x8 = callback;
    result = 0;
    entries[0].xC = result;
    if (result < 0) {
        snap4 = hsd_804D7998;
        if (snap4 >= 0) {
            saved4 = snap4;
            while (saved4 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved4].x10 = 0;
                saved4 = (saved4 + 1) % 128;
            }
            hsd_804D7984 = snap4;
        }
        return 0;
    }
    hsd_804D7998 = -1;
    return 0;
}

s32 fn_803B21E8(s32 state, s32 banner, s32 icons, s32 callback)
{
    CardCmd cmd_set_status;
    s32 result;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    s32 saved2;
    s32 snap2;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(8);

    hsd_804D7998 = hsd_804D7984;
    result = fn_803B0E9C((CardState*) state, banner, icons, 0, 1);
    if (result < 0) {
        snap1 = hsd_804D7998;
        if (snap1 >= 0) {
            saved1 = snap1;
            while (saved1 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved1].x10 = 0;
                saved1 = (saved1 + 1) % 128;
            }
            hsd_804D7984 = snap1;
        }
        return result;
    }

    cmd_set_status.type = 8;
    cmd_set_status.state = (CardState*) state;
    result = fn_803AC168((s32*) &cmd_set_status);
    if (result < 0) {
        snap2 = hsd_804D7998;
        if (snap2 >= 0) {
            saved2 = snap2;
            while (saved2 != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved2].x10 = 0;
                saved2 = (saved2 + 1) % 128;
            }
            hsd_804D7984 = snap2;
        }
        return result;
    }

    entries[0].x0 = 7;
    entries[0].x4 = state;
    entries[0].x8 = callback;
    result = 0;
    entries[0].xC = result;
    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != hsd_804D7984) {
                ((CardBufEntry*) hsd_804D1138)[saved].x10 = 0;
                saved = (saved + 1) % 128;
            }
            hsd_804D7984 = snap;
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
    memset(&hsd_804D2348, 0, sizeof(hsd_804D2348));
    hsd_804D7980 = 0;
    hsd_804D7984 = 0;
    hsd_804D799C = 2;
    for (i = 0; i < 128; i++) {
        hsd_804D1148[i][0] = 0;
    }
    hsd_804D7988 = 0;
}

void hsd_803B24E4(s32* ctx, int chan, int sector_size, void* work_buf)
{
    memset((CardState*) ctx, 0, sizeof(CardState));
    ((CardState*) ctx)->file_no = -1;
    ((CardState*) ctx)->chan = chan;
    ((CardState*) ctx)->sector_size = sector_size;
    ((CardState*) ctx)->sector_buf = work_buf;
}

static inline CardRequest* hsd_803B2550_inline(u8* base, s32 idx)
{
    return &((CardRequest*) (base + 0x1210))[idx];
}

int hsd_803B2550(s32* state, const char* filename, void (*callback)(int, int))
{
    s32 new_var;
    u8* base = hsd_804D1138;
    s32 chan = state[1];
    s32 new_var3;
    s32 new_var2;
    s32 retries;
    s32 result;
    s32 file_no;
    new_var2 = chan;
    for (retries = 0; retries < 10; retries++) {
        result =
            CARDOpen(new_var2, (char*) filename, (CARDFileInfo*) (state + 3));
        if (result != -1) {
            break;
        }
    }

    if (result < 0) {
        return result;
    }

    result = 0;
    {
        s32 tmp = state[4];
        do {
            if (tmp != -1) {
                break;
            }
            result++;
        } while (result < 10);
        file_no = state[4];
        retries = (new_var = (new_var3 = state[4]));
        file_no = retries;
        if (tmp < 0) {
            return new_var;
        }
    }

    for (chan = 0; chan < 10; chan++) {
        if (CARDClose((CARDFileInfo*) (state + 3)) != -1) {
            break;
        }
    }

    {
        s32 read_idx = hsd_804D7990;
        retries = hsd_804D7994;

        if (read_idx == retries) {
            if (CMD_QUEUE(base)[read_idx].type != 0) {
                return -265;
            }
        }
    }

    {
        CardRequest* entry = hsd_803B2550_inline(base, retries);
        s32 next = retries + 1;
        entry->type = 5;
        entry->state = (s32) state;
        entry->x8 = file_no;
        entry->callback = (void (*)(s32, s32)) callback;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

s32 hsd_803B2674(CardState* state)
{
    s32 blocks;

    state->header_size = hsd_803AC340(&state->banner_format);

    blocks =
        (0x2F + state->header_size + state->sector_size) / state->sector_size;
    blocks += fn_803AC7DC(state);

    return blocks;
}

s32 fn_803B26CC(CardState* state, s32 comment, s32 banner, s32 icons,
                void (*callback)(s32, s32))
{
    s32 result;
    CardContext* context = (CardContext*) hsd_804D1138;
    PAD_STACK(8);

    state->header_size = hsd_803AC340(&state->banner_format);
    hsd_804D7998 = hsd_804D7984;

    result = queueHeaderBlocks(state, comment, banner, icons);

    if (result < 0) {
        if (hsd_804D7998 >= 0) {
            rollbackCardCommands(context, hsd_804D7998);
        }
        return result;
    }

    context->req_type = 5;
    context->state = state;
    context->callback = callback;
    context->callback_arg = 0;
    hsd_804D7998 = -1;
    return 0;
}
