#include "hsd_3AA7.h"

#include "hsd_3A94.h"
#include "hsd_3B2B.h"
#include "hsd_3B2E.h"

#include <dolphin/card.h>
#include <dolphin/os.h>

#define CARD_QUEUE_CMD(cmd) fn_803AC168((cmd))
#define CARD_WRITE_BLOCK(state, block_idx, file_id, seq_num, payload,         \
                         payload_len, file_idx)                               \
    fn_803ACFC0((state), (block_idx), (file_id), (seq_num), (payload),        \
                (payload_len), (file_idx))

/* 4D7980 */ extern volatile s32 hsd_804D7980;
/* 4D7984 */ extern volatile s32 hsd_804D7984;
typedef struct CardOpStatus {
    s32 status;
    s32 xferred;
} CardOpStatus;
/* 4D7988 */ extern CardOpStatus hsd_804D7988;
/* 4D7998 */ extern s32 hsd_804D7998;
/* 4D799C */ extern s32 hsd_804D799C;

typedef struct CardBufEntry {
    s32 x0, x4, x8, xC;
    s32 x10;
    s32 x14, x18, x1C, x20;
} CardBufEntry;

typedef struct CardCmd {
    /* 0x00 */ s32 type;
    /* 0x04 */ CardState* state;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
} CardCmd;

typedef struct HsdCmdEntry {
    s32 type;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} HsdCmdEntry;

typedef struct CardQueueEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ void (*x14)(s32, s32);
} CardQueueEntry;

#define CMD_QUEUE(base) ((HsdCmdEntry*) ((base) + 0x1210))

s32 fn_803AA790(void)
{
    CardQueueEntry* entry;
    s32 result;
    s32 arg0;

    entry = &((CardQueueEntry*) &hsd_804D2348)[hsd_804D7990];
    arg0 = entry->x4;
    hsd_804D7990 = (hsd_804D7990 + 1) % 32;

    switch (entry->x0) {
    case 1:
        result = fn_803ADF90((struct CardState*) entry->x4, entry->x8,
                             entry->xC, 1, (s32) entry->x14);
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(entry->x8, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 2:
        switch (((s32*) (arg0 + 0x28))[entry->x8]) {
        case 0:
            result = fn_803AE7F8((struct CardState*) entry->x4, entry->x8,
                                 entry->xC, 1, (s32) entry->x14);
            break;
        case 1:
        case 2:
            result = fn_803AF3F0(entry->x4, entry->x8, entry->xC, 1,
                                 (s32) entry->x14);
            break;
        case 3:
            result = fn_803B0120(entry->x4, entry->x8, entry->xC, 1,
                                 (s32) entry->x14);
            break;
        default:
            result = -0x101;
            break;
        }
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(entry->x8, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 3:
        result = fn_803B1F78((CardState*) entry->x4, entry->x8, entry->xC,
                             entry->x10, (s32) entry->x14);
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 4:
        result =
            fn_803B21E8(entry->x4, entry->xC, entry->x10, (s32) entry->x14);
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 5:
        result = fn_803ADE4C(arg0, entry->x8, (s32) entry->x14);
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 6:
        result = fn_803B26CC((CardState*) arg0, entry->x8, entry->xC,
                             entry->x10, (s32) entry->x14);
        if (result < 0) {
            if (entry->x14 != NULL) {
                entry->x14(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    default:
        return -0x101;
    }
}

s32 hsd_803AAA48(void)
{
    s32 result;
    s32 r;
    s32 retries;
    BOOL intr2;

    while (1) {
        CardBufEntry* op = (CardBufEntry*) hsd_804D1138;
        CardBufEntry* entry;
        CardCmd* cmd;
        s32 type;
        BOOL intr = OSDisableInterrupts();
        s32 busy;
        if (hsd_804D799C == 1) {
            busy = 1;
        } else {
            busy = 0;
        }
        result = OSRestoreInterrupts(intr);
        if (busy) {
            return result;
        }

        if (hsd_804D7988.status < 0) {
            while (op[hsd_804D7980].x10 != 0) {
                op[hsd_804D7980].x10 = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            }
        }

        entry = &op[hsd_804D7980];
        cmd = (CardCmd*) &entry->x10;
        type = cmd->type;

        switch ((u32) type) {
        case 0:
            if (op->x0 != 0) {
                if (op->x0 == 3) {
                    s32 file = op->xC;
                    s32 blocks_before = fn_803AC6B8((CardState*) op->x4, file);
                    s32 file_blocks = fn_803AC634((CardState*) op->x4, file);
                    s32 total = fn_803AC7DC((CardState*) op->x4);
                    s32 map[64];
                    s32 j;
                    for (j = 0; j < file_blocks; j++) {
                        map[j] = -1;
                    }
                    for (j = 1; j <= total; j++) {
                        s32 fidx = ((CardState*) op->x4)->x170[j];
                        if (fidx >= 0) {
                            s32 logical = fidx - blocks_before;
                            if (logical >= 0 && logical < file_blocks) {
                                if (map[logical] < 0) {
                                    map[logical] = j;
                                } else if (fn_803ACB74(
                                               ((CardState*) op->x4)
                                                   ->x270[map[logical]],
                                               ((CardState*) op->x4)
                                                   ->x270[j]) < 0)
                                {
                                    ((CardState*) op->x4)
                                        ->x170[map[logical]] *= -1;
                                    map[logical] = j;
                                } else {
                                    ((CardState*) op->x4)->x170[j] *= -1;
                                }
                            }
                        }
                    }
                }
                if ((void (*)(s32, s32)) op->x8 != NULL) {
                    ((void (*)(s32, s32)) op->x8)(op->xC, hsd_804D7988.status);
                }
                op->x0 = 0;
            }
            hsd_804D7988.status = 0;
            hsd_804D799C = 2;
            if (hsd_804D7990 != hsd_804D7994 ||
                CMD_QUEUE((u8*) hsd_804D1138)[hsd_804D7990].type != 0)
            {
                result = fn_803AA790();
                if (result >= 0) {
                    hsd_804D799C = 0;
                    continue;
                }
            }
            return result;
        case 5:
            if (hsd_804D7988.status == 2) {
                cmd->type = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            }
            for (retries = 0; retries < 10; retries++) {
                r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                 &cmd->state->file_info);
                if (r != -1) {
                    break;
                }
            }
            if (r < 0) {
                hsd_804D7988.status = r;
                continue;
            }
            hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
            intr2 = OSDisableInterrupts();
            for (retries = 0; retries < 10; retries++) {
                r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                  cmd->state->x8, cmd->x1C,
                                  (void (*)(s32, s32)) hsd_803A949C);
                if (r != -1) {
                    break;
                }
            }
            hsd_804D799C = 1;
            result = OSRestoreInterrupts(intr2);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&cmd->state->file_info) != -1) {
                        break;
                    }
                }
                continue;
            }
            return result;
        case 11:
            for (retries = 0; retries < 10; retries++) {
                r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                 &cmd->state->file_info);
                if (r != -1) {
                    break;
                }
            }
            if (r < 0) {
                hsd_804D7988.status = r;
                continue;
            }
            hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
            if (cmd->x8 == 0) {
                memset(cmd->state->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            for (retries = 0; retries < 10; retries++) {
                r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                  cmd->state->x8, cmd->x8 * cmd->state->x8,
                                  (void (*)(s32, s32)) hsd_803A949C);
                if (r != -1) {
                    break;
                }
            }
            hsd_804D799C = 1;
            result = OSRestoreInterrupts(intr2);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&cmd->state->file_info) != -1) {
                        break;
                    }
                }
                continue;
            }
            return result;
        case 10:
            if (hsd_804D7988.status == 2) {
                cmd->type = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                continue;
            }
            for (retries = 0; retries < 10; retries++) {
                r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                 &cmd->state->file_info);
                if (r != -1) {
                    break;
                }
            }
            if (r < 0) {
                hsd_804D7988.status = r;
                continue;
            }
            hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
            if (cmd->x8 == 0) {
                memset(cmd->state->digest, 0, 0x30);
            }
            intr2 = OSDisableInterrupts();
            for (retries = 0; retries < 10; retries++) {
                r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                  cmd->state->x8, cmd->x8 * cmd->state->x8,
                                  (void (*)(s32, s32)) hsd_803A949C);
                if (r != -1) {
                    break;
                }
            }
            hsd_804D799C = 1;
            result = OSRestoreInterrupts(intr2);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&cmd->state->file_info) != -1) {
                        break;
                    }
                }
                continue;
            }
            return result;
        case 6:
            if (hsd_804D7988.status == 2) {
                hsd_804D7988.status = 0;
            } else {
                hsd_804D7988.status = 1;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 2:
            if (hsd_804D7988.status != 1) {
                for (retries = 0; retries < 10; retries++) {
                    r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                     &cmd->state->file_info);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                      cmd->state->x8, cmd->x1C,
                                      (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D7988.status = r;
                    hsd_804D799C = 0;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&cmd->state->file_info) != -1) {
                            break;
                        }
                    }
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 15:
            if (hsd_804D7988.status != 1) {
                for (retries = 0; retries < 10; retries++) {
                    r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                     &cmd->state->file_info);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                      cmd->state->x8, cmd->x1C,
                                      (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D7988.status = r;
                    hsd_804D799C = 0;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&cmd->state->file_info) != -1) {
                            break;
                        }
                    }
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 4:
            if (hsd_804D7988.status != 1) {
                memset(cmd->x18, 0, cmd->x20);
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 1:
            if (hsd_804D7988.status != 1) {
                s32 hdr_offset;
                s32 rem;
                for (retries = 0; retries < 10; retries++) {
                    r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                     &cmd->state->file_info);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                if (cmd->x10 > 0) {
                    hdr_offset = 0;
                } else {
                    hdr_offset = (cmd->state->x24 + 0x30) % cmd->state->x8;
                }
                if (cmd->x20 > 0 && cmd->x18 != NULL) {
                    memcpy(cmd->state->x0 + hdr_offset + 0x20, cmd->x18,
                           cmd->x20);
                }
                rem = (cmd->state->x8 - hdr_offset) - cmd->x20 - 0x20;
                if (rem != 0) {
                    memset(cmd->state->x0 + cmd->x20 + 0x20 + hdr_offset, 0,
                           rem);
                }
                memset(cmd->state->x0 + hdr_offset, 0, 0x20);
                cmd->state->x0[hdr_offset + 0x10] = (u8) (cmd->x10 >> 8);
                cmd->state->x0[hdr_offset + 0x11] = (u8) cmd->x10;
                cmd->state->x0[hdr_offset + 0x12] = (u8) cmd->x14;
                fn_803AC3F8(cmd->state, cmd->state->x0 + hdr_offset + 0x13,
                            cmd->x8);
                hsd_803B2FA0(cmd->state->x0 + hdr_offset,
                             cmd->state->x8 - hdr_offset);
                hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDWriteAsync(&cmd->state->file_info, cmd->state->x0,
                                       cmd->state->x8, cmd->x1C,
                                       (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D7988.status = r;
                    hsd_804D799C = 0;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&cmd->state->file_info) != -1) {
                            break;
                        }
                    }
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 16:
            if (hsd_804D7988.status != 1) {
                for (retries = 0; retries < 10; retries++) {
                    r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                     &cmd->state->file_info);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                hsd_803B2FA0(cmd->state->x0, cmd->state->x8);
                hsd_804D7988.xferred = CARDGetXferredBytes(cmd->state->x4);
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDWriteAsync(&cmd->state->file_info, cmd->state->x0,
                                       cmd->state->x8, cmd->x1C,
                                       (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D7988.status = r;
                    hsd_804D799C = 0;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&cmd->state->file_info) != -1) {
                            break;
                        }
                    }
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 7:
            intr2 = OSDisableInterrupts();
            for (retries = 0; retries < 10; retries++) {
                r = CARDCreateAsync(cmd->state->x4, (char*) cmd->x8, cmd->xC,
                                    &cmd->state->file_info,
                                    (void (*)(s32, s32)) hsd_803A949C);
                if (r != -1) {
                    break;
                }
            }
            hsd_804D799C = 1;
            result = OSRestoreInterrupts(intr2);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
                continue;
            }
            return result;
        case 8:
            if (hsd_804D7988.status != 1) {
                s32 k;
                s32 bit;
                for (retries = 0; retries < 10; retries++) {
                    r = CARDGetStatus(cmd->state->x4, cmd->state->x20,
                                      &cmd->state->stat);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                cmd->state->stat.commentAddr = 0;
                cmd->state->stat.iconAddr = 0x40;
                cmd->state->stat.bannerFormat =
                    (cmd->state->stat.bannerFormat & ~3) | cmd->state->x3B0;
                bit = 0;
                for (k = 0; k < 8 && cmd->state->icon_speed[k] != 0; k++) {
                    cmd->state->stat.iconFormat =
                        (cmd->state->stat.iconFormat & ~(3 << bit)) |
                        (cmd->state->icon_format[k] << bit);
                    cmd->state->stat.iconSpeed =
                        (cmd->state->stat.iconSpeed & ~(3 << bit)) |
                        (cmd->state->icon_speed[k] << bit);
                    bit += 2;
                }
                for (; k < 8; k++) {
                    cmd->state->stat.iconFormat &= ~(3 << bit);
                    cmd->state->stat.iconSpeed &= ~(3 << bit);
                    bit += 2;
                }
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDSetStatusAsync(cmd->state->x4, cmd->state->x20,
                                           &cmd->state->stat,
                                           (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D7988.status = r;
                    hsd_804D799C = 0;
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 9:
            if (hsd_804D7988.status != 1) {
                s32 icon_size;
                s32 pos;
                for (retries = 0; retries < 10; retries++) {
                    r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                     &cmd->state->file_info);
                    if (r != -1) {
                        break;
                    }
                }
                if (r < 0) {
                    hsd_804D7988.status = r;
                    continue;
                }
                switch (cmd->state->x3B0) {
                case 2:
                    icon_size = 0x1800;
                    break;
                case 1:
                    icon_size = 0xE00;
                    break;
                default:
                    icon_size = 0;
                    break;
                }
                if (cmd->x8 == 0) {
                    memcpy(cmd->state->x0, cmd->state->x370, 0x40);
                    pos = 0x40;
                    if (icon_size > 0) {
                        memcpy(cmd->state->x0 + 0x40, (void*) cmd->xC,
                               icon_size);
                        pos = icon_size + 0x40;
                    }
                    memset(cmd->state->digest, 0, 0x30);
                    if (cmd->state->x24 > cmd->state->x8) {
                        memcpy(&cmd->state->x0[pos], (void*) cmd->x10,
                               cmd->state->x8 - pos);
                        hsd_803B2B20(cmd->state->x0, cmd->state->x8,
                                     &cmd->state->digest[cmd->x8 * 0x10]);
                    } else {
                        memcpy(&cmd->state->x0[pos], (void*) cmd->x10,
                               cmd->state->x24 - pos);
                        hsd_803B2B20(cmd->state->x0, cmd->state->x24,
                                     &cmd->state->digest[cmd->x8 * 0x10]);
                        memcpy(&cmd->state->x0[cmd->state->x24],
                               cmd->state->digest, 0x30);
                    }
                } else {
                    u32 used = cmd->state->x8 * cmd->x8;
                    u32 remaining = cmd->state->x24 - used;
                    s32 data_off = (used - 0x40) - icon_size;
                    if (remaining > cmd->state->x8) {
                        memcpy(cmd->state->x0, (u8*) cmd->x10 + data_off,
                               cmd->state->x8);
                        hsd_803B2B20(cmd->state->x0, cmd->state->x8,
                                     &cmd->state->digest[cmd->x8 * 0x10]);
                    } else {
                        memcpy(cmd->state->x0, (u8*) cmd->x10 + data_off,
                               remaining);
                        hsd_803B2B20(cmd->state->x0, remaining,
                                     &cmd->state->digest[cmd->x8 * 0x10]);
                        memcpy(&cmd->state->x0[remaining], cmd->state->digest,
                               0x30);
                    }
                }
                intr2 = OSDisableInterrupts();
                for (retries = 0; retries < 10; retries++) {
                    r = CARDWriteAsync(&cmd->state->file_info, cmd->state->x0,
                                       cmd->state->x8,
                                       cmd->x8 * cmd->state->x8,
                                       (void (*)(s32, s32)) hsd_803A949C);
                    if (r != -1) {
                        break;
                    }
                }
                hsd_804D799C = 1;
                result = OSRestoreInterrupts(intr2);
                if (r < 0) {
                    hsd_804D799C = 0;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&cmd->state->file_info) != -1) {
                            break;
                        }
                    }
                    hsd_804D7988.status = r;
                    continue;
                }
                return result;
            }
            cmd->type = 0;
            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            continue;
        case 12: {
            CARDStat stat;
            cmd->state->x20 = cmd->x8;
            for (retries = 0; retries < 10; retries++) {
                r = CARDGetStatus(cmd->state->x4, cmd->state->x20, &stat);
                if (r != -1) {
                    break;
                }
            }
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
            } else {
                s32 k;
                cmd->state->x3B0 = stat.bannerFormat & 3;
                for (k = 0; k < 8; k++) {
                    cmd->state->icon_format[k] =
                        (stat.iconFormat >> (2 * k)) & 3;
                    cmd->state->icon_speed[k] =
                        (stat.iconSpeed >> (2 * k)) & 3;
                }
                cmd->state->x24 = hsd_803AC340(&cmd->state->x3B0);
                cmd->state->x460 =
                    stat.length / cmd->state->x8 -
                    (cmd->state->x24 + cmd->state->x8 + 0x2F) / cmd->state->x8;
                if (stat.iconAddr != 0x40) {
                    hsd_804D7988.status = -0x106;
                    hsd_804D799C = 0;
                } else {
                    cmd->type = 0;
                    hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                }
            }
            continue;
        }
        case 13:
            for (retries = 0; retries < 10; retries++) {
                r = CARDFastOpen(cmd->state->x4, cmd->state->x20,
                                 &cmd->state->file_info);
                if (r != -1) {
                    break;
                }
            }
            if (r < 0) {
                hsd_804D7988.status = r;
                continue;
            }
            intr2 = OSDisableInterrupts();
            for (retries = 0; retries < 10; retries++) {
                r = CARDReadAsync(&cmd->state->file_info, cmd->state->x0,
                                  cmd->state->x8, cmd->x1C,
                                  (void (*)(s32, s32)) hsd_803A949C);
                if (r != -1) {
                    break;
                }
            }
            hsd_804D799C = 1;
            result = OSRestoreInterrupts(intr2);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&cmd->state->file_info) != -1) {
                        break;
                    }
                }
                continue;
            }
            return result;
        case 14:
            r = fn_803AD16C(cmd->state);
            if (r < 0) {
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
            } else {
                cmd->type = 0;
                hsd_804D7980 = (hsd_804D7980 + 1) % 128;
            }
            continue;
        case 17:
            fn_803AC2D4();
            r = fn_803ACF30(cmd->state, 0, 0, 0);
            if (r < 0) {
                fn_803AC2E0();
                hsd_804D7988.status = r;
                hsd_804D799C = 0;
            } else {
                s32 blk = 0;
                while (1) {
                    if (blk > cmd->state->x460) {
                        fn_803AC2A4((s32) cmd->state);
                        if (r < 0) {
                            fn_803AC2E0();
                            hsd_804D7988.status = r;
                            hsd_804D799C = 0;
                        } else {
                            fn_803AC334();
                            cmd->type = 0;
                            hsd_804D7980 = (hsd_804D7980 + 1) % 128;
                        }
                        break;
                    }
                    fn_803AC258(cmd->state, blk);
                    if (r < 0) {
                        fn_803AC2E0();
                        hsd_804D7988.status = r;
                        hsd_804D799C = 0;
                        break;
                    }
                    blk++;
                }
            }
            continue;
        default:
            return result;
        }
    }
}

s32 fn_803AC168(s32* cmd_buf)
{
    BOOL state;
    s32 mode;
    s32 read_idx;
    s32 old_entry;

    state = OSDisableInterrupts();
    read_idx = hsd_804D7980;
    mode = hsd_804D799C;
    old_entry = (s32) hsd_804D1148[hsd_804D7984][0];
    OSRestoreInterrupts(state);

    if (mode != 2) {
        if (hsd_804D7984 == read_idx) {
            if (mode != 0 || hsd_804D7984 != read_idx || old_entry != 0) {
                return -265;
            }
        }
    }

    {
        s32 idx = hsd_804D7984;
        hsd_804D7984 = (hsd_804D7984 + 1) % 128;
        memcpy((u8*) hsd_804D1148[idx], cmd_buf, 36);
    }

    if (mode == 2) {
        hsd_804D799C = 0;
    }
    return 0;
}

void fn_803AC258(CardState* card_state, s32 block_idx)
{
    s32 buf[9];
    buf[0] = 13;
    buf[1] = (s32) card_state;
    buf[4] = block_idx;
    buf[5] = 0;
    buf[6] = 0;
    buf[8] = 0;
    buf[7] = fn_803ACBE8(card_state, block_idx);
    fn_803AC168(buf);
}

void fn_803AC2A4(s32 card_state)
{
    s32 buf[9];
    buf[0] = 14;
    buf[1] = card_state;
    fn_803AC168(buf);
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

/// @todo Currently 99.50% match - return expression register allocation (add
/// dest r6 vs r3)
int hsd_803AC340(void* header)
{
    u8* data = header;
    int base_size;
    int extra_size;
    int has_small;
    int i;

    switch (data[0]) {
    case 2:
        base_size = 0x1800;
        break;
    case 1:
        base_size = 0xE00;
        break;
    default:
        base_size = 0;
        break;
    }

    has_small = 0;
    extra_size = 0;
    i = 0;
    while (i < 8 && data[i + 0xA] != 0) {
        switch (data[i + 0x2]) {
        case 2:
            extra_size += 0x800;
            break;
        case 1:
            has_small = 1;
            extra_size += 0x400;
            break;
        }
        i++;
    }

    if (has_small != 0) {
        extra_size += 0x200;
    }

    extra_size = base_size + extra_size;
    return extra_size + 0x40;
}

void hsd_803AC3E0(struct CardState* file_desc, int file_idx, int file_size,
                  int file_flags, int data_size)
{
    file_desc->x28[file_idx] = file_flags;
    file_desc->x4C[file_idx] = file_size;
    file_desc->x70[file_idx].size = data_size;
}

void fn_803AC3F8(void* arg0, u8* data, s32 file_idx)
{
    struct CardState* file_desc = arg0;
    s32 start;
    s32 i;

    if (file_idx + 1 >= 9 || file_desc->x4C[file_idx + 1] == 0) {
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
        data[1] = ((((u32) file_desc->x4C[idx]) >> ((0, 0x10))) & 0x3F) |
                  ((file_desc->x28[idx] << 6) & 0xC0);
        data[2] = (u32) file_desc->x4C[idx] >> 8;
        data[3] = file_desc->x4C[idx];
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

void hsd_803AC558(struct CardState* file_desc, u8* data)
{
    u8* cur = data + 1;
    int i;

    for (i = 0; i < 3; i++) {
        u8 byte1 = cur[0];
        u8 file_idx = cur[-1];
        u8 mid = cur[1];
        u32 size = (u32) mid | ((byte1 << 8) & 0x3F00);
        u8 low = cur[2];
        u8 flags = (byte1 >> 6) & 3;
        size <<= 8;
        size |= low;
        cur += 3;

        if (size != 0 && file_desc->x4C[file_idx] == 0) {
            file_desc->x28[file_idx] = flags;
            file_desc->x4C[file_idx] = size;
        }
        cur++;
    }
}

static inline s32 fn_803AC634_remaining(u32 sector_size,
                                        struct CardState* file_desc,
                                        s32 remaining)
{
    u32 usable = sector_size - 0x20;
    return remaining - (s32) (usable - (file_desc->x24 + 48) % sector_size);
}

u32 fn_803AC634(struct CardState* file_desc, s32 file_idx)
{
    if (file_desc->x4C[file_idx] <= 0) {
        return 0;
    }

    if (file_idx == 0) {
        u32 sector_size = file_desc->x8;
        u32 usable;
        s32 remaining;

        remaining = file_desc->x4C[0];
        remaining = remaining - (s32) ((sector_size - 0x20) -
                                       (file_desc->x24 + 48) % sector_size);
        usable = sector_size - 0x20;
        if (remaining <= 0) {
            return 1;
        }
        return (u32) (remaining + sector_size - 0x21) / usable + 1;
    }

    {
        u32 sector_size = file_desc->x8;
        return (u32) (file_desc->x4C[file_idx] + sector_size - 0x21) /
               (sector_size - 0x20);
    }
}

s32 fn_803AC6B8(struct CardState* file_desc, s32 file_count)
{
    s32 total;
    s32 i;

    if (file_count >= 9) {
        return 0;
    }
    if (file_count == 0) {
        return 0;
    }

    total = 1;
    if (file_desc->x4C[0] > 0) {
        total = fn_803AC634(file_desc, 0);
    }

    for (i = 1; i < file_count; i++) {
        total += fn_803AC634(file_desc, i);
    }

    return total;
}

inline u32 fn_803AC7DC_block_count(struct CardState* file_desc, s32 file_idx)
{
    if (file_desc->x4C[file_idx] <= 0) {
        return 0;
    }

    if (file_idx == 0) {
        u32 sector_size = file_desc->x8;
        s32 remaining;
        u32 usable;

        remaining = file_desc->x4C[0];
        remaining = fn_803AC634_remaining(sector_size, file_desc, remaining);
        usable = sector_size - 0x20;
        if (remaining <= 0) {
            return 1;
        }
        return (u32) (remaining + sector_size - 0x21) / usable + 1;
    }

    {
        u32 sector_size = file_desc->x8;
        return (u32) (file_desc->x4C[file_idx] + sector_size - 0x21) /
               (sector_size - 0x20);
    }
}

s32 fn_803AC7DC(CardState* state)
{
    s32 total = 0;
    s32 extra = 0;
    s32 i;

    if (state->x4C[0] > 0) {
        total = (s32) fn_803AC7DC_block_count(state, 0) - 1;
    }

    for (i = 1; i < 9; i++) {
        s32 size = state->x4C[i];

        if (size <= 0) {
            continue;
        }

        switch (state->x28[i]) {
        case 0:
            total += fn_803AC7DC_block_count(state, i) * 2;
            break;
        case 1:
            total += fn_803AC7DC_block_count(state, i);
            if (extra < (s32) fn_803AC7DC_block_count(state, i)) {
                extra = (s32) fn_803AC7DC_block_count(state, i);
            }
            break;
        case 2:
            total += fn_803AC7DC_block_count(state, i);
            if (extra < 1) {
                extra = 1;
            }
            break;
        case 3:
            total += fn_803AC7DC_block_count(state, i);
            break;
        }
    }

    return total + extra;
}

inline s32 fn_803ACB74(s32 seq_a, s32 seq_b)
{
    s32 diff;

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
    diff = seq_a - seq_b;
    if (diff > 0x80) {
        return -1;
    }
    if (diff < -0x80) {
        return 1;
    }
    return diff;
}

s32 fn_803ACBE8(CardState* state, s32 block_idx)
{
    u32 size = state->x8;
    u32 temp = state->x24 + size;
    u32 num = temp + 0x2F;

    temp = num / size;
    {
        u32 idx = temp - 1;
        idx = block_idx + idx;
        return size * idx;
    }
}
s32 fn_803ACC0C(CardState* state, s32 block_idx, s32 file_id, s32 seq_num,
                void* expected_data, s32 data_size)
{
    s32 result;
    u8* buf;
    u32 sector_size;
    s32 retries;
    u8* data;
    u32 read_offset;
    s32 offset;
    PAD_STACK(4);

    if (data_size == 0) {
        return 0;
    }

    sector_size = state->x8;
    retries = 0;
    buf = state->x0;
    read_offset = state->x24 + sector_size;
    read_offset = (read_offset + 0x2F) / sector_size;
    read_offset = sector_size * (block_idx + read_offset - 1);

    for (; retries < 10; retries++) {
        {
            s32 tmp = CARDRead(&state->file_info, buf, sector_size, read_offset);
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
        offset = (state->x24 + 48) % state->x8;
    } else {
        offset = 0;
    }

    if (hsd_803B31CC(state->x0 + offset, state->x8 - offset) < 0) {
        return 1;
    }

    data = state->x0 + offset;
    if (file_id != ((data[0x10] << 8) | data[0x11])) {
        return 1;
    }

    if (seq_num != data[0x12]) {
        return 1;
    }

    if (memcmp(expected_data, data + 0x20, data_size) != 0) {
        return 1;
    }

    return 0;
}

s32 fn_803ACD58(CardState* state, void* icon_data, void* file_data)
{
    s32 icon_size;
    s32 i;
    s32 hdr_plus_icon;

    switch (state->x3B0) {
    case 2:
        icon_size = 0x1800;
        break;
    case 1:
        icon_size = 0xE00;
        break;
    default:
        icon_size = 0;
        break;
    }

    hdr_plus_icon = icon_size + 0x40;

    {
        s32 retries;
        u8* buf;
        s32 offset;
        s32 size;
        for (i = 0; size = state->x8, i < (0x2F + state->x24 + size) / size;
             i++)
        {
            s32 result;

            offset = i * size;
            buf = state->x0;
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
                if (memcmp(state->x0, state->x370, 0x40) != 0) {
                    return 1;
                }
                if (icon_size > 0) {
                    if (memcmp(state->x0 + 0x40, icon_data, icon_size) != 0) {
                        return 1;
                    }
                }
                {
                    u32 total_size = state->x24;
                    u32 ss = state->x8;
                    if (total_size > ss) {
                        if (memcmp(state->x0 + hdr_plus_icon, file_data,
                                   ss - hdr_plus_icon) != 0)
                        {
                            return 1;
                        }
                    } else {
                        if (memcmp(state->x0 + hdr_plus_icon, file_data,
                                   total_size - hdr_plus_icon) != 0)
                        {
                            return 1;
                        }
                    }
                }
            } else {
                u32 ss = state->x8;
                u32 remaining = state->x24 - i * ss;
                s32 data_offset = i * ss - 0x40 - icon_size;

                if (remaining > ss) {
                    if (memcmp(state->x0, (u8*) file_data + data_offset, ss) !=
                        0)
                    {
                        return 1;
                    }
                } else {
                    if (memcmp(state->x0, (u8*) file_data + data_offset,
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

s32 fn_803ACF30(CardState* state, s32 file_id, s32 seq_num, s32 version)
{
    s32 buf[9];
    s32 ret;
    u32 i;
    PAD_STACK(4);

    for (i = 0; i < (0x2F + state->x24 + state->x8) / state->x8; i++) {
        buf[0] = 11;
        buf[1] = (s32) state;
        buf[2] = i;
        buf[3] = file_id;
        buf[4] = seq_num;
        buf[5] = version;
        ret = fn_803AC168(buf);
        if (ret < 0) {
            return ret;
        }
    }
    return 0;
}

static inline u8* fn_803ACFC0_payload_dst(CardState* state, s32 hdr_offset)
{
    return hdr_offset + state->x0 + 0x20;
}

static inline u8* fn_803ACFC0_header(CardState* state, s32 hdr_offset)
{
    return hdr_offset + state->x0;
}

static inline u8* fn_803ACFC0_checksum_start(s32 hdr_offset, CardState* state)
{
    return hdr_offset + state->x0;
}


s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 file_id, s32 seq_num,
                void* payload, s32 payload_size, s32 version)
{
    u32 sector_size;
    s32 retries;
    u8* buf;
    s32 offset;
    s32 result;
    s32 hdr_offset;
    PAD_STACK(8);

    sector_size = state->x8;
    {
        u32 hdr_start = state->x24 + 48;
        offset = sector_size *
                 (block_idx + (hdr_start + sector_size - 1) / sector_size - 1);

        if (block_idx == 0) {
            if (file_id != 0) {
                return -257;
            }

            buf = state->x0;
            hdr_offset = hdr_start % sector_size;
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
        s32 remaining = (state->x8 - hdr_offset) - payload_size - 0x20;
        if (remaining != 0) {
            buf = state->x0 + payload_size + 0x20;
            memset(hdr_offset + buf, 0, remaining);
        }
    }

    memset(state->x0 + hdr_offset, 0, 0x20);

    (state->x0 + hdr_offset)[0x10] = (u8) (file_id >> 8);
    (state->x0 + hdr_offset)[0x11] = (u8) file_id;
    (state->x0 + hdr_offset)[0x12] = (u8) seq_num;

    fn_803AC3F8(state, fn_803ACFC0_header(state, hdr_offset) + 0x13, version);
    hsd_803B2FA0(fn_803ACFC0_checksum_start(hdr_offset, state),
                 state->x8 - hdr_offset);

    {
        s32 write_retries;
        u8* write_buf;
        u32 write_size;
        write_size = state->x8;
        write_retries = 0;
        write_buf = state->x0;
        for (; write_retries < 10; write_retries++) {
            result = CARDWrite(&state->file_info, write_buf, write_size, offset);
            if (result != -1) {
                break;
            }
        }
    }

    return result;
}

static inline int fn_803AD16C_file_type_nonzero(CardState* state, s32 file_id)
{
    return state->x28[file_id] != 0;
}

static inline s32 fn_803AD16C_total_blocks(CardState* state)
{
    return state->x460;
}

static inline s32 fn_803AD16C_logical_index(s32 blocks_before, s32 i)
{
    return blocks_before + i;
}

static inline s32 fn_803AD16C_file_size(CardState* state, s32 file_id)
{
    return state->x4C[file_id];
}

static inline s32 fn_803AD16C_seq_at(s32* seq, s32 phys)
{
    return seq[phys];
}

static inline int fn_803AD16C_nonnegative(s32 logical)
{
    return logical >= 0;
}

s32 fn_803AD16C(CardState* state)
{
    s32 work[64];
    s32 seq[64];
    s32 newmap[64];
    s32 pad;
    s32 filemap[64];
    s32 chosen[64];
    s32 result;
    s32 file_id;
    s32 pass;
    s32 i;
    s32 phys;
    s32 blocks_before;
    s32 file_blocks;
    PAD_STACK(56);

    result = 0;
    for (i = 0; i <= state->x460; i++) {
        newmap[i] = -1;
        work[i] = state->x170[i];
        seq[i] = state->x270[i];
    }

    if (state->x460 != fn_803AC7DC(state)) {
        return -257;
    }

    for (file_id = 0; file_id < 9; file_id++) {
        file_blocks = fn_803AC634(state, file_id);
        if (file_blocks <= 0) {
            continue;
        }

        blocks_before = fn_803AC6B8(state, file_id);

        for (i = 0; i < file_blocks; i++) {
            filemap[i] = -1;
            chosen[i] = -1;
        }

        for (pass = 0; pass <= state->x460; pass++) {
            s32 cur_seq = -1;

            for (phys = 0; phys <= fn_803AD16C_total_blocks(state); phys++) {
                if (work[phys] >= 0) {
                    s32 logical = work[phys] - blocks_before;
                    if (logical >= 0 && logical < file_blocks) {
                        if (cur_seq == -1 ||
                            fn_803ACB74(
                                cur_seq, fn_803AD16C_seq_at(seq, phys)) > 0)
                        {
                            cur_seq = seq[phys];
                        }
                    }
                }
            }
            if (cur_seq < 0) {
                break;
            }

            for (phys = 0; phys <= state->x460; phys++) {
                s32 logical = work[phys] - blocks_before;
                if (fn_803AD16C_nonnegative(logical) && logical < file_blocks &&
                    cur_seq == seq[phys])
                {
                    filemap[logical] = phys;
                }
            }

            {
                s32 count = 0;
                for (i = 0; i < file_blocks; i++) {
                    if (filemap[i] >= 0 && cur_seq == seq[filemap[i]]) {
                        count++;
                    } else {
                        break;
                    }
                }
                if (count == file_blocks) {
                    for (i = 0; i < file_blocks; i++) {
                        chosen[i] = filemap[i];
                    }
                }
            }

            for (i = 0; i < file_blocks; i++) {
                if (filemap[i] >= 0) {
                    work[filemap[i]] = -0x7FFF;
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

    for (file_id = 0; file_id < 9; file_id++) {
        if (fn_803AD16C_file_size(state, file_id) <= 0 ||
            (state->x28[file_id] != 1 && state->x28[file_id] != 2))
        {
            continue;
        }

        file_blocks = fn_803AC634(state, file_id);
        blocks_before = fn_803AC6B8(state, file_id);

        for (i = 0; i < file_blocks; i++) {
            s32 logical = fn_803AD16C_logical_index(blocks_before, i);
            if (newmap[logical] >= 0) {
                for (phys = 1; phys <= state->x460; phys++) {
                    if (phys != newmap[logical] &&
                        state->x170[phys] == logical)
                    {
                        state->x170[phys] = -logical;
                    }
                }
            }
        }
    }

    for (file_id = 0; file_id < 9; file_id++) {
        if (state->x4C[file_id] <= 0 ||
            fn_803AD16C_file_type_nonzero(state, file_id)) {
            continue;
        }

        file_blocks = fn_803AC634(state, file_id);
        blocks_before = fn_803AC6B8(state, file_id);

        for (i = 0; i < file_blocks; i++) {
            s32 logical = blocks_before + i;
            s32 src = newmap[logical];
            s32 dup;
            s32 target_seq;
            s32 ret;

            if (src < 0) {
                continue;
            }

            target_seq = state->x270[src];
            dup = -1;
            for (phys = 1; phys <= state->x460; phys++) {
                if (phys != src && state->x170[phys] == logical) {
                    if (dup < 0) {
                        dup = phys;
                    } else {
                        if (phys == 0) {
                            ret = -0x101;
                        } else {
                            s32 cmd[9];
                            cmd[0] = 1;
                            cmd[1] = (s32) state;
                            cmd[3] = phys;
                            cmd[4] = 0xFFFF;
                            cmd[5] = 0;
                            cmd[6] = 0;
                            cmd[8] = 0;
                            cmd[7] = fn_803ACBE8(state, phys);
                            cmd[2] = file_id;
                            ret = fn_803AC168(cmd);
                        }
                        if (ret < 0 && result == 0) {
                            result = -0x10B;
                        }
                        state->x170[phys] = -0x7FFF;
                        state->x270[phys] = 0;
                    }
                }
            }

            if (dup == -1) {
                for (phys = state->x460; phys > 0; phys--) {
                    if (state->x170[phys] < 0) {
                        dup = phys;
                        break;
                    }
                }
                if (dup >= 0) {
                    if (src == 0 || dup == 0) {
                        ret = -0x101;
                    } else {
                        s32 cmd[9];
                        cmd[0] = 0xF;
                        cmd[1] = (s32) state;
                        cmd[3] = src;
                        cmd[7] = fn_803ACBE8(state, src);
                        ret = fn_803AC168(cmd);
                        if (ret >= 0) {
                            s32 cmd2[9];
                            cmd2[0] = 0x10;
                            cmd2[1] = (s32) state;
                            cmd2[3] = dup;
                            cmd2[4] = logical;
                            cmd2[5] = target_seq;
                            cmd2[7] = fn_803ACBE8(state, dup);
                            ret = fn_803AC168(cmd2);
                        }
                    }
                    if (ret < 0 && (result == 0 || result == -0x10B)) {
                        result = -0x102;
                    }
                }
            } else if (state->x270[dup] != target_seq) {
                if (src == 0 || dup == 0) {
                    ret = -0x101;
                } else {
                    s32 cmd[9];
                    cmd[0] = 0xF;
                    cmd[1] = (s32) state;
                    cmd[3] = src;
                    cmd[7] = fn_803ACBE8(state, src);
                    ret = fn_803AC168(cmd);
                    if (ret >= 0) {
                        s32 cmd2[9];
                        cmd2[0] = 0x10;
                        cmd2[1] = (s32) state;
                        cmd2[3] = dup;
                        cmd2[4] = logical;
                        cmd2[5] = target_seq;
                        cmd2[7] = fn_803ACBE8(state, dup);
                        ret = fn_803AC168(cmd2);
                    }
                }
                if (ret < 0 && (result == 0 || result == -0x10B)) {
                    result = -0x102;
                }
            }
        }
    }

    return result;
}

s32 fn_803ADE4C(s32 card_state, s32 channel, s32 callback)
{
    s32 buf1[9];
    s32 buf2[9];
    s32 result;
    s32 saved;
    s32 snap;
    s32 saved1;
    s32 snap1;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(16);

    hsd_804D7998 = hsd_804D7984;
    buf1[0] = 12;
    buf1[1] = card_state;
    buf1[2] = channel;
    result = fn_803AC168(buf1);
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

    buf2[0] = 17;
    buf2[1] = card_state;
    result = fn_803AC168(buf2);
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
    entries[0].x4 = card_state;
    entries[0].x8 = callback;
    entries[0].xC = 0;
    hsd_804D7998 = -1;
    return 0;
}

static inline s32 fn_803ADF90_read(CardState* state, void* buf, s32 offset)
{
    return CARDRead(&state->file_info, buf, state->x8, offset);
}

s32 fn_803ADF90(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardState* state = arg0;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    s32 block_map[64];
    s32 blocks_before;
    s32 saved;
    s32 i;
    s32 logical;
    u8* dst;
    s32 result;
    s32 file_blocks;
    s32 seq_num;
    s32 snap;
    s32 total_blocks;
    s32 ofs;
    s32 remaining;
    s32 file_size;
    s32 callback_seq;

    PAD_STACK(60);

    callback_seq = 0;
    if (arg3 == 0) {
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

    blocks_before = fn_803AC6B8(arg0, arg1);

    file_size = state->x4C[arg1];
    remaining = file_size;
    if (file_size <= 0) {
        file_blocks = 0;
    } else if (arg1 == 0) {
        u32 sector_size = state->x8;
        u32 usable;
        s32 rem;

        rem = state->x4C[0];
        usable = sector_size - 0x20;
        rem = rem - (s32) (usable - (state->x24 + 0x30) % sector_size);
        if (rem <= 0) {
            file_blocks = 1;
        } else {
            file_blocks =
                (u32) (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->x8;
        file_blocks =
            (u32) (remaining + sector_size - 0x21) / (sector_size - 0x20);
    }

    total_blocks = fn_803AC7DC(arg0);
    for (i = 0; i < file_blocks; i++) {
        block_map[i] = -1;
    }

    seq_num = -1;
    for (i = 1; i <= total_blocks; i++) {
        logical = state->x170[i] - blocks_before;
        if (logical >= 0 && logical < file_blocks) {
            if (seq_num < 0) {
                seq_num = state->x270[i];
            } else {
                if (seq_num != state->x270[i]) {
                    callback_seq = -260;
                }
                if (fn_803ACB74(seq_num, state->x270[i]) > 0) {
                    seq_num = state->x270[i];
                }
            }
            block_map[logical] = i;
        }
    }

    if (arg1 == 0 && state->x170[0] == 0) {
        block_map[0] = 0;
        if (seq_num >= 0 && seq_num != state->x270[0]) {
            callback_seq = -260;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[i] < 0) {
            callback_seq = -259;
            break;
        }
    }

    if (callback_seq != 0) {
        return callback_seq;
    }

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 retries;
        s32 ofs = state->x20;
        s32 fd = state->x4;
        for (retries = 0; retries < 10; retries++) {
            result = CARDFastOpen(fd, ofs, &state->file_info);
            if (result != -1) {
                break;
            }
        }

        if (result < 0) {
            return result;
        }
    }

    dst = (u8*) arg2;

    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 chunk;

        if (arg1 == 0 && i == 0) {
            chunk = (state->x8 - 0x20) - ((state->x24 + 0x30) % state->x8);
        } else {
            chunk = state->x8 - 0x20;
        }

        if (remaining > chunk) {
            s32 data_block = block_map[i];
            if (data_block >= 0) {
                if (arg3 != 0) {
                    s32 cmd[9];

                    ofs = fn_803ACBE8(arg0, data_block);
                    cmd[0] = 2;
                    cmd[1] = (s32) arg0;
                    cmd[4] = data_block;
                    cmd[5] = 0;
                    cmd[6] = (s32) dst;
                    cmd[8] = chunk;
                    cmd[7] = ofs;
                    result = fn_803AC168(cmd);
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    s32 offset;
                    s32 retries;
                    u8* buf = state->x0;

                    offset = fn_803ACBE8(arg0, data_block);
                    for (retries = 0; retries < 10; retries++) {
                        result = fn_803ADF90_read(state, buf, offset);
                        if (result != -1) {
                            break;
                        }
                    }

                    if (result >= 0) {
                        s32 read_ofs = data_block == 0
                                           ? (state->x24 + 0x30) % state->x8
                                           : 0;
                        if (hsd_803B31CC(state->x0 + read_ofs,
                                         state->x8 - read_ofs) < 0)
                        {
                            result = -0x105;
                        } else {
                            if (chunk != 0 && dst != NULL) {
                                memcpy(dst, state->x0 + (read_ofs + 0x20),
                                       chunk);
                            }
                            result = 0;
                        }
                    }
                    if (result < 0) {
                        if (result == -0x105) {
                            callback_seq = -259;
                        } else {
                            callback_seq = -259;
                        }
                    }
                }
            } else if (arg3 != 0) {
                if (chunk == 0) {
                    result = 0;
                } else {
                    s32 cmd[9];

                    cmd[0] = 4;
                    cmd[1] = (s32) arg0;
                    cmd[2] = 0;
                    cmd[4] = 0;
                    cmd[5] = 0;
                    cmd[6] = (s32) dst;
                    cmd[8] = chunk;
                    cmd[7] = 0;
                    result = fn_803AC168(cmd);
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                memset(dst, 0, chunk);
            }

            remaining -= chunk;
            dst += chunk;
        } else {
            s32 data_block = block_map[i];
            if (data_block >= 0) {
                if (arg3 != 0) {
                    s32 cmd[9];

                    ofs = fn_803ACBE8(arg0, data_block);
                    cmd[0] = 2;
                    cmd[1] = (s32) arg0;
                    cmd[4] = data_block;
                    cmd[5] = 0;
                    cmd[6] = (s32) dst;
                    cmd[8] = remaining;
                    cmd[7] = ofs;
                    result = fn_803AC168(cmd);
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    s32 offset;
                    s32 retries;
                    s32 read_ofs;
                    CARDFileInfo* info = &state->file_info;
                    u8* buf = state->x0;

                    offset = fn_803ACBE8(arg0, data_block);
                    for (retries = 0; retries < 10; retries++) {
                        result = CARDRead(info, buf, state->x8, offset);
                        if (result != -1) {
                            break;
                        }
                    }

                    if (result >= 0) {
                        read_ofs = data_block == 0
                                       ? (state->x24 + 0x30) % state->x8
                                       : 0;
                        if (hsd_803B31CC(state->x0 + read_ofs,
                                         state->x8 - read_ofs) < 0)
                        {
                            result = -0x105;
                        } else {
                            if (remaining != 0 && dst != NULL) {
                                memcpy(dst, state->x0 + (read_ofs + 0x20),
                                       remaining);
                            }
                            result = 0;
                        }
                    }
                    if (result < 0) {
                        if (result == -0x105) {
                            callback_seq = -259;
                        } else {
                            callback_seq = -259;
                        }
                    }
                }
            }
            remaining = 0;
        }
    }

    if (arg3 == 0) {
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
    } else {
        entries[0].x0 = 1;
        entries[0].x4 = (s32) arg0;
        entries[0].x8 = arg4;
        entries[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return callback_seq;
}

s32 fn_803AE7F8(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardState* state = arg0;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    s32 saved;
    s32 snap;
    s32 block_map[3][64];
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
    PAD_STACK(80);

    repair_result = 0;
    verify_failed = 0;
    if (arg3 == 0) {
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

    blocks_before = fn_803AC6B8(arg0, arg1);

    file_size = state->x4C[arg1];
    if (file_size <= 0) {
        file_blocks = 0;
    } else if (arg1 == 0) {
        u32 sector_size = state->x8;
        s32 rem = file_size - (s32) ((sector_size - 0x20) -
                                     (state->x24 + 0x30) % sector_size);
        if (rem <= 0) {
            file_blocks = 1;
        } else {
            u32 blocks =
                (u32) (rem + sector_size - 0x21) / (sector_size - 0x20);
            file_blocks = blocks + 1;
        }
    } else {
        u32 sector_size = state->x8;
        file_blocks =
            (u32) (file_size + sector_size - 0x21) / (sector_size - 0x20);
    }

    total_blocks = fn_803AC7DC(arg0);

    for (i = 0; i < file_blocks; i++) {
        block_map[0][i] = -1;
        block_map[1][i] = -1;
    }

    current_seq = -1;
    free_count = 0;

    for (i = 1; i <= total_blocks; i++) {
        s32 file_idx = state->x170[i];

        if (file_idx < 0) {
            block_map[2][free_count++] = i;
            continue;
        }

        logical = file_idx - blocks_before;
        if (logical >= 0 && logical < file_blocks) {
            if (current_seq == -1 ||
                fn_803ACB74(current_seq, state->x270[i]) < 0)
            {
                current_seq = state->x270[i];
            }
            if (block_map[0][logical] < 0) {
                block_map[0][logical] = i;
            } else {
                block_map[1][logical] = i;
            }
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[0][i] < 0 || state->x270[block_map[0][i]] != current_seq) {
            verify_failed = 1;
            break;
        }
        if (block_map[1][i] < 0 || state->x270[block_map[1][i]] != current_seq) {
            verify_failed = 1;
            break;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[0][i] < 0) {
            if (free_count <= 0) {
                return -257;
            }
            block_map[0][i] = block_map[2][--free_count];
        }
        if (block_map[1][i] < 0) {
            if (free_count <= 0) {
                repair_result = -258;
            } else {
                block_map[1][i] = block_map[2][--free_count];
            }
        }
    }

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 retries;
        s32 fd = state->x4;
        s32 ofs = state->x20;
        for (retries = 0; retries < 10; retries++) {
            result = CARDFastOpen(fd, ofs, &state->file_info);
            if (result != -1) {
                break;
            }
        }

        if (result < 0) {
            return result;
        }
    }

    if (verify_failed == 0) {
        s32 pass;
        s32* map = block_map[0];

        for (pass = 0; pass < 2; pass++, map += 64) {
            s32 remaining = file_size;

            data = (u8*) arg2;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys = map[i];
                s32 chunk = state->x8 - 0x20;

                if (remaining > chunk) {
                    if (phys >= 0) {
                        if (arg3 != 0) {
                            if (chunk != 0) {
                                s32 cmd[9];

                                cmd[0] = 5;
                                cmd[1] = (s32) arg0;
                                cmd[4] = blocks_before + i;
                                cmd[5] = current_seq;
                                cmd[6] = (s32) data;
                                cmd[7] = fn_803ACBE8(arg0, phys);
                                cmd[8] = chunk;
                                result = fn_803AC168(cmd);
                            } else {
                                result = 0;
                            }
                            if (result < 0) {
                                snap = hsd_804D7998;
                                if (snap >= 0) {
                                    saved = snap;
                                    while (saved != hsd_804D7984) {
                                        entries[saved].x10 = 0;
                                        saved = (saved + 1) % 128;
                                    }
                                    hsd_804D7984 = snap;
                                }
                                return result;
                            }
                        } else {
                            result = fn_803ACC0C(arg0, phys, blocks_before + i,
                                                 current_seq, data, chunk);
                            if (result < 0) {
                                s32 retries;
                                for (retries = 0; retries < 10; retries++) {
                                    if (CARDClose(&state->file_info) != -1) {
                                        break;
                                    }
                                }
                                return result;
                            }
                            if (result > 0) {
                                verify_failed = 1;
                                break;
                            }
                        }
                    }

                    remaining -= chunk;
                    data += chunk;
                } else {
                    if (phys >= 0) {
                        if (arg3 != 0) {
                            if (remaining != 0) {
                                s32 cmd[9];

                                cmd[0] = 5;
                                cmd[1] = (s32) arg0;
                                cmd[4] = blocks_before + i;
                                cmd[5] = current_seq;
                                cmd[6] = (s32) data;
                                cmd[7] = fn_803ACBE8(arg0, phys);
                                cmd[8] = remaining;
                                result = fn_803AC168(cmd);
                            } else {
                                result = 0;
                            }
                            if (result < 0) {
                                snap = hsd_804D7998;
                                if (snap >= 0) {
                                    saved = snap;
                                    while (saved != hsd_804D7984) {
                                        entries[saved].x10 = 0;
                                        saved = (saved + 1) % 128;
                                    }
                                    hsd_804D7984 = snap;
                                }
                                return result;
                            }
                        } else {
                            result = fn_803ACC0C(arg0, phys, blocks_before + i,
                                                 current_seq, data, remaining);
                            if (result < 0) {
                                s32 retries;
                                for (retries = 0; retries < 10; retries++) {
                                    if (CARDClose(&state->file_info) != -1) {
                                        break;
                                    }
                                }
                                return result;
                            }
                            if (result > 0) {
                                verify_failed = 1;
                                break;
                            }
                        }
                    }

                    remaining = 0;
                }
            }
        }

        if (verify_failed == 0) {
            if (arg3 != 0) {
                s32 cmd[9];

                cmd[0] = 6;
                cmd[1] = (s32) arg0;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
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
    }

    current_seq = (u8) (current_seq + 1);
    {
        s32 pass;
        s32* map = block_map[0];

        for (pass = 0; pass < 2; pass++, map += 64) {
            s32 remaining = file_size;

            data = (u8*) arg2;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys = map[i];
                s32 chunk = state->x8 - 0x20;

                if (remaining > chunk) {
                    if (phys >= 0) {
                        if (arg3 != 0) {
                            s32 ofs = fn_803ACBE8(arg0, phys);
                            if (phys == 0 && blocks_before + i != 0) {
                                result = -0x101;
                            } else {
                                if (phys == 0) {
                                    s32 cmd[9];
                                    cmd[0] = 2;
                                    cmd[1] = (s32) arg0;
                                    cmd[4] = 0;
                                    cmd[5] = 0;
                                    cmd[6] = 0;
                                    cmd[7] = ofs;
                                    cmd[8] = 0;
                                    fn_803AC168(cmd);
                                }
                                {
                                    s32 cmd[9];
                                    cmd[0] = 1;
                                    cmd[1] = (s32) arg0;
                                    cmd[2] = arg1;
                                    cmd[3] = phys;
                                    cmd[4] = blocks_before + i;
                                    cmd[5] = current_seq;
                                    cmd[6] = (s32) data;
                                    cmd[7] = ofs;
                                    cmd[8] = chunk;
                                    result = fn_803AC168(cmd);
                                }
                            }
                            if (result < 0) {
                                snap = hsd_804D7998;
                                if (snap >= 0) {
                                    saved = snap;
                                    while (saved != hsd_804D7984) {
                                        entries[saved].x10 = 0;
                                        saved = (saved + 1) % 128;
                                    }
                                    hsd_804D7984 = snap;
                                }
                                return result;
                            }
                        } else {
                            result =
                                fn_803ACFC0(arg0, phys, blocks_before + i,
                                            current_seq, data, chunk, arg1);
                            if (result < 0) {
                                state->x170[phys] = -0x7FFF;
                                state->x270[phys] = 0;
                                {
                                    s32 retries;
                                    for (retries = 0; retries < 10; retries++)
                                    {
                                        if (CARDClose(&state->file_info) != -1)
                                        {
                                            break;
                                        }
                                    }
                                }
                                return pass == 0 ? -260 : -258;
                            }
                        }

                        state->x170[phys] = blocks_before + i;
                        state->x270[phys] = current_seq;
                    }

                    remaining -= chunk;
                    data += chunk;
                } else {
                    if (phys >= 0) {
                        if (arg3 != 0) {
                            s32 ofs = fn_803ACBE8(arg0, phys);
                            if (phys == 0 && blocks_before + i != 0) {
                                result = -0x101;
                            } else {
                                if (phys == 0) {
                                    s32 cmd[9];
                                    cmd[0] = 2;
                                    cmd[1] = (s32) arg0;
                                    cmd[4] = 0;
                                    cmd[5] = 0;
                                    cmd[6] = 0;
                                    cmd[7] = ofs;
                                    cmd[8] = 0;
                                    fn_803AC168(cmd);
                                }
                                {
                                    s32 cmd[9];
                                    cmd[0] = 1;
                                    cmd[1] = (s32) arg0;
                                    cmd[2] = arg1;
                                    cmd[3] = phys;
                                    cmd[4] = blocks_before + i;
                                    cmd[5] = current_seq;
                                    cmd[6] = (s32) data;
                                    cmd[7] = ofs;
                                    cmd[8] = remaining;
                                    result = fn_803AC168(cmd);
                                }
                            }
                            if (result < 0) {
                                snap = hsd_804D7998;
                                if (snap >= 0) {
                                    saved = snap;
                                    while (saved != hsd_804D7984) {
                                        entries[saved].x10 = 0;
                                        saved = (saved + 1) % 128;
                                    }
                                    hsd_804D7984 = snap;
                                }
                                return result;
                            }
                        } else {
                            result = fn_803ACFC0(arg0, phys, blocks_before + i,
                                                 current_seq, data, remaining,
                                                 arg1);
                            if (result < 0) {
                                state->x170[phys] = -0x7FFF;
                                state->x270[phys] = 0;
                                {
                                    s32 retries;
                                    for (retries = 0; retries < 10; retries++)
                                    {
                                        if (CARDClose(&state->file_info) != -1)
                                        {
                                            break;
                                        }
                                    }
                                }
                                return pass == 0 ? -260 : -258;
                            }
                        }

                        state->x170[phys] = blocks_before + i;
                        state->x270[phys] = current_seq;
                    }

                    remaining = 0;
                }
            }
        }
    }

    if (arg3 == 0) {
        s32 retries;
        for (retries = 0; retries < 10; retries++) {
            result = CARDClose(&state->file_info);
            if (result != -1) {
                break;
            }
        }

        if (result < 0) {
            return repair_result == 0 ? -267 : repair_result;
        }
    } else {
        entries[0].x0 = 2;
        entries[0].x4 = (s32) arg0;
        entries[0].x8 = arg4;
        entries[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return repair_result;
}

static inline s32 fn_803AF3F0_blocks_before(CardState* state, s32 file_count)
{
    s32 total;
    s32 i;

    if (file_count >= 9) {
        return 0;
    }
    if (file_count == 0) {
        return 0;
    }

    total = 1;
    if (state->x4C[0] > 0) {
        total = fn_803AC634(state, 0);
    }

    for (i = 1; i < file_count; i++) {
        total += fn_803AC634(state, i);
    }

    return total;
}

static inline s32 fn_803AF3F0_chunk_size(CardState* state)
{
    return state->x8 - 0x20;
}

s32 fn_803AF3F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardState* state = (CardState*) arg0;
    s32 file_size;
    s32 block_map[3][64];
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    s32 blocks_before;
    s32 file_blocks;
    s32 total_blocks;
    s32 current_seq;
    s32 secondary_count;
    s32 free_count;
    s32 i;
    s32 remaining;
    s32 result;
    s32 saved;
    s32 seq_match;
    s32 snap;
    u8* data;
    PAD_STACK(84);

    seq_match = 0;
    if (arg3 == 0) {
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

    blocks_before = fn_803AF3F0_blocks_before(state, arg1);

    file_size = state->x4C[arg1];
    if (file_size <= 0) {
        file_blocks = 0;
    } else if (arg1 == 0) {
        u32 sector_size = state->x8;
        s32 rem = file_size - (s32) ((sector_size - 0x20) -
                                     (state->x24 + 0x30) % sector_size);
        if (rem <= 0) {
            file_blocks = 1;
        } else {
            file_blocks =
                (u32) (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->x8;
        file_blocks =
            (u32) (file_size + sector_size - 0x21) / (sector_size - 0x20);
    }

    total_blocks = fn_803AC7DC(state);

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 retries;
        s32 fd = state->x4;
        s32 ofs = state->x20;
        for (retries = 0; retries < 10; retries++) {
            result = CARDFastOpen(fd, ofs, &state->file_info);
            if (result != -1) {
                break;
            }
        }
        if (result < 0) {
            return result;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        block_map[0][i] = -1;
        block_map[1][i] = -1;
    }

    secondary_count = 0;
    current_seq = -1;
    free_count = 0;
    for (i = 0; i < total_blocks; i++) {
        s32 arg1x = state->x170[i + 1];

        if (arg1x >= 0) {
            s32 logical = arg1x - blocks_before;
            if (logical >= 0 && logical < file_blocks) {
                if (current_seq < 0 ||
                    fn_803ACB74(current_seq, state->x270[i + 1]) < 0)
                {
                    current_seq = state->x270[i + 1];
                }
                block_map[0][logical] = i + 1;
            }
        } else {
            s32 logical = -(arg1x + blocks_before);
            if (logical >= 0 && logical < file_blocks) {
                block_map[1][secondary_count++] = i + 1;
            } else {
                block_map[2][free_count++] = i + 1;
            }
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[0][i] < 0 ||
            state->x270[block_map[0][i]] != current_seq)
        {
            seq_match = 1;
            break;
        }
    }

    if (seq_match == 0) {
        remaining = file_size;
        data = (u8*) arg2;
        for (i = 0; i < file_blocks && remaining > 0; i++) {
            s32 chunk = fn_803AF3F0_chunk_size(state);

            if (remaining > chunk) {
                if (arg3 != 0) {
                    if (chunk != 0) {
                        s32 cmd[9];
                        s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                        cmd[0] = 5;
                        cmd[1] = (s32) state;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                    }
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    result = fn_803ACC0C(state, block_map[0][i],
                                         blocks_before + i, current_seq, data,
                                         chunk);
                    if (result < 0) {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                        return result;
                    }
                    if (result > 0) {
                        break;
                    }
                }
                remaining -= chunk;
                data += chunk;
            } else {
                if (arg3 != 0) {
                    if (remaining != 0) {
                        s32 cmd[9];
                        s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                        cmd[0] = 5;
                        cmd[1] = (s32) state;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = remaining;
                        result = fn_803AC168(cmd);
                    }
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    result = fn_803ACC0C(state, block_map[0][i],
                                         blocks_before + i, current_seq, data,
                                         remaining);
                    if (result < 0) {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                        return result;
                    }
                    if (result > 0) {
                        break;
                    }
                }
                remaining = 0;
            }
        }

        if (i >= file_blocks || remaining <= 0) {
            if (arg3 != 0) {
                s32 cmd[9];
                cmd[0] = 6;
                cmd[1] = (s32) state;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
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
    }

    if (secondary_count > file_blocks) {
        for (i = file_blocks; i < secondary_count; i++) {
            if (arg3 != 0) {
                if (block_map[1][i] != 0) {
                    s32 cmd[9];
                    s32 ofs = fn_803ACBE8(state, block_map[1][i]);
                    cmd[0] = 1;
                    cmd[1] = (s32) state;
                    cmd[2] = arg1;
                    cmd[3] = block_map[1][i];
                    cmd[4] = 0xFFFF;
                    cmd[5] = 0;
                    cmd[6] = 0;
                    cmd[7] = ofs;
                    cmd[8] = 0;
                    result = fn_803AC168(cmd);
                } else {
                    result = -257;
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                result =
                    fn_803ACFC0(state, block_map[1][i], 0xFFFF, 0, NULL, 0,
                                 arg1);
                state->x170[block_map[1][i]] = -0x7FFF;
                state->x270[block_map[1][i]] = 0;
                if (result < 0) {
                    s32 retries;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&state->file_info) != -1) {
                            break;
                        }
                    }
                    return result;
                }
            }
        }
    } else if (secondary_count < file_blocks) {
        while (secondary_count < file_blocks && free_count > 0) {
            block_map[1][secondary_count++] = block_map[2][--free_count];
        }
        for (i = 0; secondary_count < file_blocks && i < file_blocks; i++) {
            if (block_map[0][i] >= 0) {
                block_map[1][secondary_count++] = block_map[0][i];
                block_map[0][i] = -1;
            }
        }
        if (secondary_count < file_blocks) {
            if (arg3 == 0) {
                s32 retries;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&state->file_info) != -1) {
                        break;
                    }
                }
            }
            return -257;
        }
    }

    current_seq = (u8) (current_seq + 1);
    remaining = file_size;
    data = (u8*) arg2;
    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 chunk = state->x8 - 0x20;

        if (remaining > chunk) {
            if (arg3 != 0) {
                s32 ofs = fn_803ACBE8(state, block_map[1][i]);
                if (block_map[1][i] == 0 && blocks_before + i != 0) {
                    result = -0x101;
                } else {
                    if (block_map[1][i] == 0) {
                        s32 cmd[9];
                        cmd[0] = 2;
                        cmd[1] = (s32) state;
                        cmd[4] = 0;
                        cmd[5] = 0;
                        cmd[6] = 0;
                        cmd[7] = ofs;
                        cmd[8] = 0;
                        fn_803AC168(cmd);
                    }
                    {
                        s32 cmd[9];
                        cmd[0] = 1;
                        cmd[1] = (s32) state;
                        cmd[2] = arg1;
                        cmd[3] = block_map[1][i];
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                    }
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                result = fn_803ACFC0(state, block_map[1][i], blocks_before + i,
                                     current_seq, data, chunk, arg1);
                if (result < 0) {
                    state->x170[block_map[1][i]] = -0x7FFF;
                    state->x270[block_map[1][i]] = 0;
                    {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                    }
                    return result;
                }
                state->x170[block_map[1][i]] = blocks_before + i;
                state->x270[block_map[1][i]] = current_seq;
            }
            remaining -= chunk;
            data += chunk;
        } else {
            if (arg3 != 0) {
                s32 ofs = fn_803ACBE8(state, block_map[1][i]);
                if (block_map[1][i] == 0 && blocks_before + i != 0) {
                    result = -0x101;
                } else {
                    if (block_map[1][i] == 0) {
                        s32 cmd[9];
                        cmd[0] = 2;
                        cmd[1] = (s32) state;
                        cmd[4] = 0;
                        cmd[5] = 0;
                        cmd[6] = 0;
                        cmd[7] = ofs;
                        cmd[8] = 0;
                        fn_803AC168(cmd);
                    }
                    {
                        s32 cmd[9];
                        cmd[0] = 1;
                        cmd[1] = (s32) state;
                        cmd[2] = arg1;
                        cmd[3] = block_map[1][i];
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = remaining;
                        result = fn_803AC168(cmd);
                    }
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                result = fn_803ACFC0(state, block_map[1][i], blocks_before + i,
                                     current_seq, data, remaining, arg1);
                if (result < 0) {
                    state->x170[block_map[1][i]] = -0x7FFF;
                    state->x270[block_map[1][i]] = 0;
                    {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                    }
                    return result;
                }
                state->x170[block_map[1][i]] = blocks_before + i;
                state->x270[block_map[1][i]] = current_seq;
            }
            remaining = 0;
        }
    }

    if (arg3 == 0) {
        s32 retries;
        for (i = 0; i < file_blocks; i++) {
            if (block_map[0][i] >= 0) {
                state->x170[block_map[0][i]] = -state->x170[block_map[0][i]];
            }
        }
        for (retries = 0; retries < 10; retries++) {
            result = CARDClose(&state->file_info);
            if (result != -1) {
                break;
            }
        }
        if (result < 0) {
            return -267;
        }
    } else {
        entries[0].x0 = 3;
        entries[0].x4 = (s32) state;
        entries[0].x8 = arg4;
        entries[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return 0;
}

static inline void fn_803B0120_blk97637(s32 arg1, CardState * state, s32 *file_size)
{
    {
        s32 size = state->x4C[arg1];
        (*file_size) = size;
    }
}

s32 fn_803B0120(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 snap;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    s32 saved;
    CardState* state = (CardState*) arg0;
    s32 block_map[3][64];
    s32* secondary_ptr;
    s32* free_ptr;
    s32 blocks_before;
    s32 file_blocks;
    s32 file_size;
    s32 total_blocks;
    s32 current_seq;
    s32 needs_rewrite;
    s32 secondary_count;
    s32 free_count;
    s32 i;
    s32 remaining;
    s32 result;
    u8* data;
    PAD_STACK(96);

    needs_rewrite = 0;
    if (arg3 == 0) {
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

    blocks_before = fn_803AC6B8(state, arg1);

    fn_803B0120_blk97637(arg1, state, &file_size);
    if (file_size <= 0) {
        file_blocks = 0;
    } else if (arg1 == 0) {
        u32 sector_size = state->x8;
        s32 rem = (sector_size - 0x20) -
                  (s32) ((state->x24 + 0x30) % sector_size);
        rem = state->x4C[0] - rem;
        if (rem <= 0) {
            file_blocks = 1;
        } else {
            file_blocks =
                (u32) (rem + sector_size - 0x21) / (sector_size - 0x20) + 1;
        }
    } else {
        u32 sector_size = state->x8;
        file_blocks =
            (u32) (file_size + sector_size - 0x21) / (sector_size - 0x20);
    }

    total_blocks = fn_803AC7DC(state);

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 ofs = state->x20;
        s32 retries;
        s32 fd = state->x4;
        s32 r;
        for (retries = 0; retries < 10; retries++) {
            r = CARDFastOpen(fd, ofs, &state->file_info);
            if (r != -1) {
                break;
            }
        }
        if (r < 0) {
            return r;
        }
    }

    for (i = 0; i < file_blocks; i++) {
        block_map[0][i] = -1;
        block_map[1][i] = -1;
    }

    current_seq = -1;
    if (arg1 == 0) {
        if (state->x170[0] == 0) {
            current_seq = state->x270[0];
        } else {
            needs_rewrite = 1;
        }
        block_map[0][0] = 0;
    }

    secondary_count = 0;
    free_count = 0;
    secondary_ptr = block_map[0];
    free_ptr = block_map[0];
    for (i = 1; i <= total_blocks; i++) {
        s32 file_idx = state->x170[i];

        if (file_idx >= 0) {
            s32 logical = file_idx - blocks_before;
            if (arg1 == 0 && logical == 0) {
                secondary_ptr[64] = i;
                secondary_ptr++;
                secondary_count++;
            } else if (logical >= 0 && logical < file_blocks) {
                if (current_seq < 0 ||
                    fn_803ACB74(current_seq, state->x270[i]) < 0)
                {
                    current_seq = state->x270[i];
                }
                block_map[0][logical] = i;
            }
        } else {
            s32 logical = -(file_idx + blocks_before);
            if (logical >= 0 && logical < file_blocks) {
                secondary_ptr[64] = i;
                secondary_ptr++;
                secondary_count++;
            } else {
                free_ptr[128] = i;
                free_ptr++;
                free_count++;
            }
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (block_map[0][i] < 0) {
            needs_rewrite = 1;
            if (secondary_count > 0) {
                secondary_ptr--;
                secondary_count--;
                block_map[0][i] = secondary_ptr[64];
                secondary_ptr[64] = -1;
            } else if (free_count > 0) {
                free_ptr--;
                free_count--;
                block_map[0][i] = free_ptr[128];
                free_ptr[128] = -1;
            } else {
                if (arg3 == 0) {
                    s32 retries;
                    for (retries = 0; retries < 10; retries++) {
                        if (CARDClose(&state->file_info) != -1) {
                            break;
                        }
                    }
                }
                return -257;
            }
        }
    }

    if (needs_rewrite == 0) {
        for (i = 0; i < file_blocks; i++) {
            if (block_map[0][i] < 0 ||
                state->x270[block_map[0][i]] != current_seq)
            {
                needs_rewrite = 1;
                break;
            }
        }
    }

    current_seq = (u8) (current_seq + 1);

    if (needs_rewrite == 0) {
        remaining = file_size;
        data = (u8*) arg2;
        for (i = 0; i < file_blocks && remaining > 0; i++) {
            s32 logical = blocks_before + i;
            s32 chunk;
            if (logical == 0) {
                chunk = (state->x8 - 0x20) - ((state->x24 + 0x30) % state->x8);
            } else {
                chunk = state->x8 - 0x20;
            }

            if (remaining > chunk) {
                if (arg3 != 0) {
                    if (chunk != 0) {
                        s32 cmd[9];
                        s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                        cmd[0] = 5;
                        cmd[1] = (s32) state;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                    }
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    result =
                        fn_803ACC0C(state, block_map[0][i], blocks_before + i,
                                    current_seq, data, chunk);
                    if (result < 0) {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                        return result;
                    }
                    if (result > 0) {
                        break;
                    }
                }
                remaining -= chunk;
                data += chunk;
            } else {
                if (arg3 != 0) {
                    if (remaining != 0) {
                        s32 cmd[9];
                        s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                        cmd[0] = 5;
                        cmd[1] = (s32) state;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = remaining;
                        result = fn_803AC168(cmd);
                    }
                    if (result < 0) {
                        snap = hsd_804D7998;
                        if (snap >= 0) {
                            saved = snap;
                            while (saved != hsd_804D7984) {
                                entries[saved].x10 = 0;
                                saved = (saved + 1) % 128;
                            }
                            hsd_804D7984 = snap;
                        }
                        return result;
                    }
                } else {
                    result =
                        fn_803ACC0C(state, block_map[0][i], blocks_before + i,
                                    current_seq, data, remaining);
                    if (result < 0) {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                        return result;
                    }
                    if (result > 0) {
                        break;
                    }
                }
                remaining = 0;
            }
        }

        if (i >= file_blocks || remaining <= 0) {
            if (arg3 != 0) {
                s32 cmd[9];
                cmd[0] = 6;
                cmd[1] = (s32) state;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
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
    }
    while (secondary_count > 0) {
        secondary_count--;
        if (arg3 != 0) {
            if (block_map[1][secondary_count] != 0) {
                s32 cmd[9];
                s32 ofs = fn_803ACBE8(state, block_map[1][secondary_count]);
                cmd[0] = 1;
                cmd[1] = (s32) state;
                cmd[2] = arg1;
                cmd[3] = block_map[1][secondary_count];
                cmd[4] = 0xFFFF;
                cmd[5] = 0;
                cmd[6] = 0;
                cmd[7] = ofs;
                cmd[8] = 0;
                result = fn_803AC168(cmd);
            } else {
                result = -257;
            }
            if (result < 0) {
                snap = hsd_804D7998;
                if (snap >= 0) {
                    saved = snap;
                    while (saved != hsd_804D7984) {
                        entries[saved].x10 = 0;
                        saved = (saved + 1) % 128;
                    }
                    hsd_804D7984 = snap;
                }
                return result;
            }
        } else {
            result = fn_803ACFC0(state, block_map[1][secondary_count], 0xFFFF,
                                 0, NULL, 0, arg1);
            state->x170[block_map[1][secondary_count]] = -0x7FFF;
            state->x270[block_map[1][secondary_count]] = 0;
            if (result < 0) {
                s32 retries;
                for (retries = 0; retries < 10; retries++) {
                    if (CARDClose(&state->file_info) != -1) {
                        break;
                    }
                }
                return result;
            }
        }
    }

    remaining = file_size;
    data = (u8*) arg2;
    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 logical = blocks_before + i;
        s32 chunk;
        if (logical == 0) {
            chunk = (state->x8 - 0x20) - ((state->x24 + 0x30) % state->x8);
        } else {
            chunk = state->x8 - 0x20;
        }

        if (remaining > chunk) {
            if (arg3 != 0) {
                s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                if (block_map[0][i] == 0 && logical != 0) {
                    result = -0x101;
                } else {
                    if (block_map[0][i] == 0) {
                        s32 cmd[9];
                        cmd[0] = 2;
                        cmd[1] = (s32) state;
                        cmd[4] = 0;
                        cmd[5] = 0;
                        cmd[6] = 0;
                        cmd[7] = ofs;
                        cmd[8] = 0;
                        fn_803AC168(cmd);
                    }
                    {
                        s32 cmd[9];
                        cmd[0] = 1;
                        cmd[1] = (s32) state;
                        cmd[2] = arg1;
                        cmd[3] = block_map[0][i];
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                    }
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                {
                    s32 block = block_map[0][i];
                    result = fn_803ACFC0(state, block, blocks_before + i,
                                         current_seq, data, chunk, arg1);
                }
                if (result < 0) {
                    state->x170[block_map[0][i]] = -0x7FFF;
                    state->x270[block_map[0][i]] = 0;
                    {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                    }
                    return result;
                }
                state->x170[block_map[0][i]] = blocks_before + i;
                state->x270[block_map[0][i]] = current_seq;
            }
            remaining -= chunk;
            data += chunk;
        } else {
            if (arg3 != 0) {
                s32 ofs = fn_803ACBE8(state, block_map[0][i]);
                if (block_map[0][i] == 0 && logical != 0) {
                    result = -0x101;
                } else {
                    if (block_map[0][i] == 0) {
                        s32 cmd[9];
                        cmd[0] = 2;
                        cmd[1] = (s32) state;
                        cmd[4] = 0;
                        cmd[5] = 0;
                        cmd[6] = 0;
                        cmd[7] = ofs;
                        cmd[8] = 0;
                        fn_803AC168(cmd);
                    }
                    {
                        s32 cmd[9];
                        cmd[0] = 1;
                        cmd[1] = (s32) state;
                        cmd[2] = arg1;
                        cmd[3] = block_map[0][i];
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] = ofs;
                        cmd[8] = remaining;
                        result = fn_803AC168(cmd);
                    }
                }
                if (result < 0) {
                    snap = hsd_804D7998;
                    if (snap >= 0) {
                        saved = snap;
                        while (saved != hsd_804D7984) {
                            entries[saved].x10 = 0;
                            saved = (saved + 1) % 128;
                        }
                        hsd_804D7984 = snap;
                    }
                    return result;
                }
            } else {
                result = fn_803ACFC0(state, block_map[0][i], blocks_before + i,
                                     current_seq, data, remaining, arg1);
                if (result < 0) {
                    state->x170[block_map[0][i]] = -0x7FFF;
                    state->x270[block_map[0][i]] = 0;
                    {
                        s32 retries;
                        for (retries = 0; retries < 10; retries++) {
                            if (CARDClose(&state->file_info) != -1) {
                                break;
                            }
                        }
                    }
                    return result;
                }
                state->x170[block_map[0][i]] = blocks_before + i;
                state->x270[block_map[0][i]] = current_seq;
            }
            remaining = 0;
        }
    }

    if (arg3 == 0) {
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
    } else {
        CardBufEntry* entry = (CardBufEntry*) hsd_804D1138;
        entries[0].x0 = 4;
        entries[0].x4 = (s32) state;
        entries[0].x8 = arg4;
        entries[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return 0;
}

static inline void* fn_803B0E9C_payload_dst(s32 payload_pos,
                                             struct CardState* state)
{
    return state->x0 + payload_pos;
}

s32 fn_803B0E9C(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    u8 digest[0x30];
    s32 cmd_done[9];
    s32 cmd_clear[9];
    UNUSED u8 pad_cmd_clear[4];
    s32 cmd_patch[9];
    UNUSED u8 pad_cmd_patch[8];
    s32 cmd_write_icon[9];
    UNUSED u8 pad_cmd_write_icon[16];
    s32 cmd_read_icon[9];
    UNUSED u8 pad_cmd_read_icon[20];
    s32 payload_pos;
    s32 remaining;
    s32 block_idx;
    s32 digest_idx;
    s32 result;
    u32 sector_size;

    arg0->x24 = hsd_803AC340(&arg0->x3B0);

    if (arg3 == 0) {
        if (arg4 != 0) {
            for (block_idx = 0;
                 (u32) block_idx < (0x2F + arg0->x24 + arg0->x8) / arg0->x8;)
            {
                cmd_read_icon[0] = 10;
                cmd_read_icon[1] = (s32) arg0;
                cmd_read_icon[3] = arg1;
                cmd_read_icon[4] = arg2;
                cmd_read_icon[2] = block_idx;
                result = fn_803AC168(cmd_read_icon);
                if (result >= 0) {
                    block_idx++;
                    continue;
                }
                goto check_read_result;
            }
            result = 0;
        check_read_result:
            if (result < 0) {
                return result;
            }

            {
                cmd_done[0] = 6;
                cmd_done[1] = (s32) arg0;
                result = fn_803AC168(cmd_done);
            }
            if (result < 0) {
                return result;
            }
        } else {
            result = fn_803ACD58(arg0, (void*) arg1, (void*) arg2);
            if (result < 0) {
                return result;
            }
            if (result == 0) {
                return 1;
            }
        }
    }

    if (arg4 != 0) {
        for (arg4 = 0; sector_size = arg0->x8,
            (u32) arg4 < (0x2F + arg0->x24 + sector_size) / sector_size;
             arg4++)
        {
            if ((u32) (arg4 + 1) ==
                (0x2F + arg0->x24 + sector_size) / sector_size)
            {
                if (arg3 != 0) {
                    void* clear_buf = arg0->x0;
                    s32 zero = 0;
                    cmd_clear[0] = 4;
                    cmd_clear[1] = (s32) arg0;
                    cmd_clear[4] = zero;
                    cmd_clear[5] = zero;
                    cmd_clear[6] = (s32) clear_buf;
                    cmd_clear[8] = sector_size;
                    cmd_clear[7] = zero;
                    cmd_clear[2] = zero;
                    result = fn_803AC168(cmd_clear);
                } else {
                    s32 has_blocks;

                    if (arg0->x4C[0] > 0) {
                        has_blocks = 1;
                    } else {
                        has_blocks = 0;
                    }
                    cmd_patch[0] = 2;
                    cmd_patch[1] = (s32) arg0;
                    cmd_patch[4] = -1;
                    cmd_patch[5] = 0;
                    cmd_patch[6] = 0;
                    cmd_patch[8] = has_blocks;
                    cmd_patch[7] = arg4 * sector_size;
                    result = fn_803AC168(cmd_patch);
                }
                if (result < 0) {
                    return result;
                }
            }

            {
                cmd_write_icon[0] = 9;
                cmd_write_icon[1] = (s32) arg0;
                cmd_write_icon[2] = arg4;
                cmd_write_icon[3] = arg1;
                cmd_write_icon[4] = arg2;
                result = fn_803AC168(cmd_write_icon);
                if (result < 0) {
                    return result;
                }
            }
        }
        return 0;
    }

    sector_size = arg0->x8;
    if (arg0->x24 + 0x30 < sector_size) {
        if (arg3 != 0) {
            memset(arg0->x0, 0, sector_size);
        } else {
            s32 retries;
            for (retries = 0; retries < 10; retries++) {
                {
                    CARDFileInfo* info = &arg0->file_info;
                    result = CARDRead(info, arg0->x0, sector_size, 0);
                }
                if (result != -1) {
                    break;
                }
            }

            if (result < 0) {
                return result;
            }
        }
    }

    memcpy(arg0->x0, arg0->x370, 0x40);
    payload_pos = 0x40;
    switch (arg0->x3B0) {
    case 2: {
        void* dst = arg0->x0 + 0x40;
        memcpy(dst, (void*) arg1, 0x1800);
    }
        payload_pos = 0x1840;
        break;
    case 1: {
        void* dst = arg0->x0 + 0x40;
        memcpy(dst, (void*) arg1, 0xE00);
    }
        payload_pos = 0xE40;
        break;
    }

    memset(digest, 0, sizeof(digest));
    block_idx = 0;
    digest_idx = 0;
    remaining = arg0->x24 - payload_pos;

    while (remaining >= 0) {
        sector_size = arg0->x8;
        if ((u32) (payload_pos + remaining) > sector_size) {
            s32 copied = sector_size - payload_pos;
            s32 retries;
            s32 offset;
            u32 write_size;
            u8* buf;

            memcpy(fn_803B0E9C_payload_dst(payload_pos, arg0), (s32*) arg2,
                   copied);
            arg2 += copied;
            remaining -= copied;
            hsd_803B2B20(arg0->x0, sector_size, &digest[digest_idx]);

            write_size = arg0->x8;
            buf = arg0->x0;
            offset = write_size * block_idx;
            for (retries = 0; retries < 10; retries++) {
                result = CARDWrite(&arg0->file_info, buf, write_size, offset);
                if (result != -1) {
                    break;
                }
            }

            if (result < 0) {
                return result;
            }

            payload_pos = 0;
            block_idx++;
            digest_idx += 0x10;

            if (remaining + 0x30 < (s32) arg0->x24) {
                if (arg3 != 0) {
                    memset(arg0->x0, 0, arg0->x8);
                } else {
                    s32 retries2;
                    u32 read_size = arg0->x8;
                    u8* buf = arg0->x0;

                    for (retries2 = 0; retries2 < 10; retries2++) {
                        result = CARDRead(&arg0->file_info, buf, read_size,
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

        memcpy(arg0->x0 + payload_pos, (void*) arg2, remaining);
        payload_pos += remaining;
        hsd_803B2B20(arg0->x0, payload_pos, &digest[digest_idx]);
        memcpy(arg0->x0 + payload_pos, digest, 0x30);
        remaining = -1;

        {
            s32 retries;
            u32 write_size = arg0->x8;
            u8* buf = arg0->x0;
            s32 offset = write_size * block_idx;

            for (retries = 0; retries < 10; retries++) {
                result = CARDWrite(&arg0->file_info, buf, write_size, offset);
                if (result != -1) {
                    break;
                }
            }
        }

        if (result < 0) {
            return result;
        }

        block_idx++;
        digest_idx += 0x10;
    }

    return 0;
}

s32 fn_803B1338(CardState* state, s32 arg1)
{
    s32 result;
    s32 offset;
    s32 logical;
    s32 max_redun;
    s32 file0_blocks;
    s32 file_blocks;
    s32 file_id;
    s32 i;
    s32 phys;
    u8* fdata;
    PAD_STACK(232);

    max_redun = 0;
    phys = 1;
    logical = 1;

    if ((s32) fn_803AC634(state, 0) != 0) {
        s32 hdr_offset;
        u32 hdr_base;
        u32 sector_size;
        file0_blocks = fn_803AC634(state, 0);
        offset = 0;
        sector_size = state->x8;
        hdr_base = state->x24 + 0x30;
        hdr_offset = hdr_base % sector_size;
        if (arg1 != 0) {
            fdata = state->x70[0].ptr;
            if (fdata == NULL) {
                s32 ofs0 = sector_size *
                           ((hdr_base + sector_size - 1) / sector_size - 1);
                s32 cmd[9];
                cmd[0] = 2;
                cmd[1] = (s32) state;
                cmd[4] = 0;
                cmd[5] = 0;
                cmd[6] = 0;
                cmd[8] = 0;
                cmd[7] = ofs0;
                fn_803AC168(cmd);
                {
                    s32 cmd2[9];
                    cmd2[0] = 1;
                    cmd2[1] = (s32) state;
                    cmd2[3] = 0;
                    cmd2[4] = 0;
                    cmd2[5] = 0;
                    cmd2[6] = 0;
                    cmd2[8] = 0;
                    cmd2[7] = ofs0;
                    cmd2[2] = 0;
                    result = fn_803AC168(cmd2);
                }
            } else {
                s32 ofs0 = sector_size *
                           ((hdr_base + sector_size - 1) / sector_size - 1);
                s32 cmd[9];
                cmd[0] = 2;
                cmd[1] = (s32) state;
                cmd[4] = 0;
                cmd[5] = 0;
                cmd[6] = 0;
                cmd[8] = 0;
                cmd[7] = ofs0;
                fn_803AC168(cmd);
                {
                    s32 cmd2[9];
                    cmd2[0] = 1;
                    cmd2[1] = (s32) state;
                    cmd2[3] = 0;
                    cmd2[4] = 0;
                    cmd2[5] = 0;
                    cmd2[6] = (s32) fdata;
                    cmd2[8] = sector_size - hdr_offset - 0x20;
                    cmd2[7] = ofs0;
                    cmd2[2] = 0;
                    result = fn_803AC168(cmd2);
                }
                offset = state->x8 - hdr_offset - 0x20;
            }
            if (result < 0) {
                return result;
            }
        } else {
            fdata = state->x70[0].ptr;
            if (fdata == NULL) {
                result = fn_803ACFC0(state, 0, 0, 0, NULL, 0, 0);
            } else {
                result = fn_803ACFC0(state, 0, 0, 0, fdata,
                                     sector_size - hdr_offset - 0x20, 0);
                offset = state->x8 - hdr_offset - 0x20;
            }
        }
        if (result < 0 && result != -0x105) {
            state->x170[0] = -0x7FFF;
            state->x270[0] = 0;
            return result;
        }

        for (i = 1; i < file0_blocks; i++) {
            if (arg1 != 0) {
                fdata = state->x70[0].ptr;
                if (fdata == NULL) {
                    s32 ofs = fn_803ACBE8(state, logical);
                    if (logical == 0 && phys != 0) {
                        result = -0x101;
                    } else {
                        if (logical == 0) {
                            s32 cmd[9];
                            cmd[0] = 2;
                            cmd[1] = (s32) state;
                            cmd[4] = 0;
                            cmd[5] = 0;
                            cmd[6] = 0;
                            cmd[8] = 0;
                            cmd[7] = ofs;
                            fn_803AC168(cmd);
                        }
                        {
                            s32 cmd[9];
                            cmd[0] = 1;
                            cmd[1] = (s32) state;
                            cmd[3] = logical;
                            cmd[4] = phys;
                            cmd[5] = 0;
                            cmd[6] = 0;
                            cmd[8] = 0;
                            cmd[7] = ofs;
                            cmd[2] = 0;
                            result = fn_803AC168(cmd);
                        }
                    }
                } else {
                    u8* wdata = fdata + offset;
                    s32 chunk = state->x8 - 0x20;
                    s32 ofs = fn_803ACBE8(state, logical);
                    if (logical == 0 && phys != 0) {
                        result = -0x101;
                    } else {
                        if (logical == 0) {
                            s32 cmd[9];
                            cmd[0] = 2;
                            cmd[1] = (s32) state;
                            cmd[4] = 0;
                            cmd[5] = 0;
                            cmd[6] = 0;
                            cmd[8] = 0;
                            cmd[7] = ofs;
                            fn_803AC168(cmd);
                        }
                        {
                            s32 cmd[9];
                            cmd[0] = 1;
                            cmd[1] = (s32) state;
                            cmd[3] = logical;
                            cmd[4] = phys;
                            cmd[5] = 0;
                            cmd[6] = (s32) wdata;
                            cmd[8] = chunk;
                            cmd[7] = ofs;
                            cmd[2] = 0;
                            result = fn_803AC168(cmd);
                        }
                        offset += state->x8;
                        offset -= 0x20;
                    }
                }
                if (result < 0) {
                    return result;
                }
            } else {
                fdata = state->x70[0].ptr;
                if (fdata == NULL) {
                    result =
                        CARD_WRITE_BLOCK(state, logical, phys, 0, NULL, 0, 0);
                } else {
                    result =
                        CARD_WRITE_BLOCK(state, logical, phys, 0,
                                         fdata + offset, state->x8 - 0x20, 0);
                    offset += state->x8;
                    offset -= 0x20;
                }
                if (result < 0) {
                    state->x170[logical] = -0x7FFF;
                    state->x270[logical] = 0;
                    return result;
                }
                state->x170[logical] = phys;
                state->x270[logical] = 0;
            }
            logical++;
            phys++;
        }
    }

    for (file_id = 1; file_id < 9; file_id++) {
        file_blocks = fn_803AC634(state, file_id);
        offset = 0;
        if (file_blocks > 0) {
            for (i = 0; i < file_blocks; i++) {
                if (arg1 != 0) {
                    fdata = state->x70[file_id].ptr;
                    if (fdata == NULL) {
                        s32 ofs = fn_803ACBE8(state, logical);
                        if (logical == 0 && phys != 0) {
                            result = -0x101;
                        } else {
                            if (logical == 0) {
                                s32 cmd[9];
                                cmd[0] = 2;
                                cmd[1] = (s32) state;
                                cmd[4] = 0;
                                cmd[5] = 0;
                                cmd[6] = 0;
                                cmd[8] = 0;
                                cmd[7] = ofs;
                                fn_803AC168(cmd);
                            }
                            {
                                s32 cmd[9];
                                cmd[0] = 1;
                                cmd[1] = (s32) state;
                                cmd[3] = logical;
                                cmd[4] = phys;
                                cmd[5] = 0;
                                cmd[6] = 0;
                                cmd[8] = 0;
                                cmd[7] = ofs;
                                cmd[2] = file_id;
                                result = CARD_QUEUE_CMD(cmd);
                            }
                        }
                    } else {
                        u8* wdata = fdata + offset;
                        s32 chunk = state->x8 - 0x20;
                        s32 ofs = fn_803ACBE8(state, logical);
                        if (logical == 0 && phys != 0) {
                            result = -0x101;
                        } else {
                            if (logical == 0) {
                                s32 cmd[9];
                                cmd[0] = 2;
                                cmd[1] = (s32) state;
                                cmd[4] = 0;
                                cmd[5] = 0;
                                cmd[6] = 0;
                                cmd[8] = 0;
                                cmd[7] = ofs;
                                fn_803AC168(cmd);
                            }
                            {
                                s32 cmd[9];
                                cmd[0] = 1;
                                cmd[1] = (s32) state;
                                cmd[3] = logical;
                                cmd[4] = phys;
                                cmd[5] = 0;
                                cmd[6] = (s32) wdata;
                                cmd[8] = chunk;
                                cmd[7] = ofs;
                                cmd[2] = file_id;
                                result = CARD_QUEUE_CMD(cmd);
                            }
                            offset += state->x8;
                            offset -= 0x20;
                        }
                    }
                    if (result < 0) {
                        return result;
                    }
                } else {
                    fdata = state->x70[file_id].ptr;
                    if (fdata == NULL) {
                        result = fn_803ACFC0(state, logical, phys, 0, NULL, 0,
                                             file_id);
                    } else {
                        result = fn_803ACFC0(state, logical, phys, 0,
                                             fdata + offset, state->x8 - 0x20,
                                             file_id);
                        offset += state->x8;
                        offset -= 0x20;
                    }
                    if (result < 0) {
                        state->x170[logical] = -0x7FFF;
                        state->x270[logical] = 0;
                        return result;
                    }
                    state->x170[logical] = phys;
                    state->x270[logical] = 0;
                }
                logical++;
                phys++;
            }
            switch (state->x28[file_id]) {
            case 1:
                if (max_redun < file_blocks) {
                    max_redun = file_blocks;
                }
                break;
            case 2:
                if (max_redun < 1) {
                    max_redun = 1;
                }
                break;
            }
        }
    }

    for (i = 0; i < max_redun; i++) {
        if (arg1 != 0) {
            s32 ofs = fn_803ACBE8(state, logical);
            if (logical == 0) {
                result = -257;
            } else {
                s32 cmd[9];
                cmd[0] = 1;
                cmd[1] = (s32) state;
                cmd[3] = logical;
                cmd[4] = 0xFFFF;
                cmd[5] = 0;
                cmd[6] = 0;
                cmd[8] = 0;
                cmd[7] = ofs;
                cmd[2] = file_id;
                result = fn_803AC168(cmd);
            }
            if (result < 0) {
                return result;
            }
        } else {
            result = fn_803ACFC0(state, logical, 0xFFFF, 0, NULL, 0, file_id);
            state->x170[logical] = -0x7FFF;
            state->x270[logical] = 0;
            if (result < 0) {
                return result;
            }
        }
        phys++;
        logical++;
    }

    phys = 1;
    if ((s32) fn_803AC634(state, 0) != 0) {
        phys = fn_803AC634(state, 0);
    }
    for (file_id = 1; file_id < 9; file_id++) {
        file_blocks = fn_803AC634(state, file_id);
        offset = 0;
        if (file_blocks > 0) {
            switch (state->x28[file_id]) {
            case 0:
                for (i = 0; i < file_blocks; i++) {
                    if (arg1 != 0) {
                        fdata = state->x70[file_id].ptr;
                        if (fdata == NULL) {
                            s32 ofs = fn_803ACBE8(state, logical);
                            if (logical == 0 && phys != 0) {
                                result = -0x101;
                            } else {
                                if (logical == 0) {
                                    s32 cmd[9];
                                    cmd[0] = 2;
                                    cmd[1] = (s32) state;
                                    cmd[4] = 0;
                                    cmd[5] = 0;
                                    cmd[6] = 0;
                                    cmd[8] = 0;
                                    cmd[7] = ofs;
                                    fn_803AC168(cmd);
                                }
                                {
                                    s32 cmd[9];
                                    cmd[0] = 1;
                                    cmd[1] = (s32) state;
                                    cmd[3] = logical;
                                    cmd[4] = phys;
                                    cmd[5] = 0;
                                    cmd[6] = 0;
                                    cmd[8] = 0;
                                    cmd[7] = ofs;
                                    cmd[2] = file_id;
                                    result = fn_803AC168(cmd);
                                }
                            }
                        } else {
                            u8* wdata = fdata + offset;
                            s32 chunk = state->x8 - 0x20;
                            s32 ofs = fn_803ACBE8(state, logical);
                            if (logical == 0 && phys != 0) {
                                result = -0x101;
                            } else {
                                if (logical == 0) {
                                    s32 cmd[9];
                                    cmd[0] = 2;
                                    cmd[1] = (s32) state;
                                    cmd[4] = 0;
                                    cmd[5] = 0;
                                    cmd[6] = 0;
                                    cmd[8] = 0;
                                    cmd[7] = ofs;
                                    fn_803AC168(cmd);
                                }
                                {
                                    s32 cmd[9];
                                    cmd[0] = 1;
                                    cmd[1] = (s32) state;
                                    cmd[3] = logical;
                                    cmd[4] = phys;
                                    cmd[5] = 0;
                                    cmd[6] = (s32) wdata;
                                    cmd[8] = chunk;
                                    cmd[7] = ofs;
                                    cmd[2] = file_id;
                                    result = fn_803AC168(cmd);
                                }
                                offset += state->x8;
                                offset -= 0x20;
                            }
                        }
                        if (result < 0) {
                            return result;
                        }
                    } else {
                        fdata = state->x70[file_id].ptr;
                        if (fdata == NULL) {
                            s32 write_result = fn_803ACFC0(
                                state, logical, phys, 0, NULL, 0, file_id);
                            result = write_result;
                        } else {
                            s32 write_result = fn_803ACFC0(
                                state, logical, phys, 0, fdata + offset,
                                state->x8 - 0x20, file_id);
                            result = write_result;
                            offset += state->x8;
                            offset -= 0x20;
                        }
                        if (result < 0) {
                            state->x170[logical] = -0x7FFF;
                            state->x270[logical] = 0;
                            return result;
                        }
                        state->x170[logical] = phys;
                        state->x270[logical] = 0;
                    }
                    logical++;
                    phys++;
                }
                break;
            case 1:
            case 2:
            case 3:
                phys += file_blocks;
                break;
            }
        }
    }

    return 0;
}

s32 fn_803B1F78(CardState* state, s32 channel, s32 file_id, s32 seq_num,
                s32 callback)
{
    s32 buf1[9];
    s32 buf2[9];
    s32 result;
    s32 blocks;
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
    blocks = state->x8 * hsd_803B2674(state);
    buf1[0] = 7;
    buf1[1] = (s32) state;
    buf1[2] = channel;
    buf1[3] = blocks;
    result = fn_803AC168(buf1);
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

    result = fn_803B0E9C(state, file_id, seq_num, 1, 1);
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

    buf2[0] = 8;
    buf2[1] = (s32) state;
    result = fn_803AC168(buf2);
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

s32 fn_803B21E8(s32 card_state, s32 file_id, s32 seq_num, s32 callback)
{
    s32 buf[9];
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
    result = fn_803B0E9C((CardState*) card_state, file_id, seq_num, 0, 1);
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

    buf[0] = 8;
    buf[1] = card_state;
    result = fn_803AC168(buf);
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
    entries[0].x4 = card_state;
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
    hsd_804D7988.status = 0;
}

void hsd_803B24E4(s32* ctx, int channel, int file_no, void* work_buf)
{
    memset(ctx, 0, 0x464);
    ctx[8] = -1;
    ctx[1] = channel;
    ctx[2] = file_no;
    ctx[0] = (s32) work_buf;
}

inline HsdCmdEntry* hsd_803B2550_inline(u8* arg0, s32 arg1)
{
    return &((HsdCmdEntry*) (arg0 + 0x1210))[arg1];
}

int hsd_803B2550(s32* arg0, const char* arg1, void (*arg2)(int, int))
{
    s32 new_var;
    u8* base = hsd_804D1138;
    s32 chan = arg0[1];
    s32 new_var3;
    s32 new_var2;
    s32 retries;
    s32 result;
    s32 write_idx;
    new_var2 = chan;
    for (retries = 0; retries < 10; retries++) {
        result = CARDOpen(new_var2, (char*) arg1, (CARDFileInfo*) (arg0 + 3));
        if (result != -1) {
            break;
        }
    }

    if (result < 0) {
        return result;
    }

    result = 0;
    {
        s32 tmp = arg0[4];
        do {
            if (tmp != -1) {
                break;
            }
            result++;
        } while (result < 10);
        write_idx = arg0[4];
        retries = (new_var = (new_var3 = arg0[4]));
        write_idx = retries;
        if (tmp < 0) {
            return new_var;
        }
    }

    for (chan = 0; chan < 10; chan++) {
        if (CARDClose((CARDFileInfo*) (arg0 + 3)) != -1) {
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
        HsdCmdEntry* entry = hsd_803B2550_inline(base, retries);
        s32 next = retries + 1;
        entry->type = 5;
        entry->f1 = (s32) arg0;
        entry->f2 = write_idx;
        entry->f5 = (s32) arg2;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

s32 hsd_803B2674(CardState* state)
{
    s32 blocks;

    state->x24 = hsd_803AC340(&state->x3B0);

    blocks = (0x2F + state->x24 + state->x8) / state->x8;
    blocks += fn_803AC7DC(state);

    return blocks;
}

s32 fn_803B26CC(CardState* state, s32 file_id, s32 seq_num, s32 version,
                s32 callback)
{
    s32 buf[9];
    u32 i;
    s32 result;
    s32 saved;
    s32 snap;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(12);

    state->x24 = hsd_803AC340(&state->x3B0);

    result = 0;
    for (i = 0, hsd_804D7998 = hsd_804D7984;
         i < (0x2F + state->x24 + state->x8) / state->x8; i++) {
        buf[0] = 11;
        buf[1] = (s32) state;
        buf[2] = (s32) i;
        buf[3] = file_id;
        buf[4] = seq_num;
        buf[5] = version;
        result = fn_803AC168(buf);
        if (result < 0) {
            break;
        }
    }

    if (result < 0) {
        snap = hsd_804D7998;
        if (snap >= 0) {
            saved = snap;
            while (saved != hsd_804D7984) {
                entries[saved].x10 = 0;
                saved = (saved + 1) % 128;
            }
            hsd_804D7984 = snap;
        }
        return result;
    }

    entries[0].x0 = 5;
    entries[0].x4 = (s32) state;
    entries[0].x8 = callback;
    entries[0].xC = 0;
    hsd_804D7998 = -1;
    return 0;
}
