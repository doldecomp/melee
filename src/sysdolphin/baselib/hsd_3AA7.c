#include "hsd_3AA7.h"

#include "hsd_3A94.h"
#include "hsd_3B2B.h"
#include "hsd_3B2E.h"

#include <dolphin/card.h>
#include <dolphin/os.h>

/* 4D7980 */ extern s32 hsd_804D7980;
/* 4D7984 */ extern volatile s32 hsd_804D7984;
/* 4D7988 */ extern s32 hsd_804D7988;
/* 4D7998 */ extern s32 hsd_804D7998;
/* 4D799C */ extern s32 hsd_804D799C;

typedef struct CardBufEntry {
    s32 x0, x4, x8, xC;
    s32 x10;
    s32 x14, x18, x1C, x20;
} CardBufEntry;

typedef struct CardQueueEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ void (*x14)(s32, s32);
} CardQueueEntry;

s32 fn_803AA790(void)
{
    CardQueueEntry* entry;
    s32 idx;
    s32 result;
    s32 arg0;
    s32 sub_state;
    void (*cb)(s32, s32);

    idx = hsd_804D7990;
    entry = (CardQueueEntry*) ((u8*) &hsd_804D2348 + idx * 0x18);
    arg0 = entry->x4;
    hsd_804D7990 = (idx + 1) % 32;

    switch (entry->x0) {
    case 1:
        result = fn_803ADF90((struct CardState*) entry->x4, entry->x8,
                             entry->xC, 1, (s32) entry->x14);
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(entry->x8, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 2:
        sub_state = ((s32*) (arg0 + 0x28))[entry->x8];
        switch (sub_state) {
        case 3:
            result = fn_803B0120(entry->x4, entry->x8, entry->xC, 1,
                                 (s32) entry->x14);
            break;
        case 0:
            result = fn_803AE7F8((struct CardState*) entry->x4, entry->x8,
                                 entry->xC, 1, (s32) entry->x14);
            break;
        default:
            if (sub_state > 0 && sub_state < 3) {
                result = fn_803AF3F0(entry->x4, entry->x8, entry->xC, 1,
                                     (s32) entry->x14);
            } else {
                result = -0x101;
            }
            break;
        }
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(entry->x8, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 3:
        result = fn_803B1F78((CardState*) entry->x4, entry->x8, entry->xC,
                             entry->x10, (s32) entry->x14);
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 4:
        result =
            fn_803B21E8(entry->x4, entry->xC, entry->x10, (s32) entry->x14);
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 5:
        result = fn_803ADE4C(arg0, entry->x8, (s32) entry->x14);
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    case 6:
        result = fn_803B26CC((CardState*) arg0, entry->x8, entry->xC,
                             entry->x10, (s32) entry->x14);
        if (result < 0) {
            cb = entry->x14;
            if (cb != NULL) {
                cb(0, result);
            }
        }
        entry->x0 = 0;
        return result;
    default:
        return -0x101;
    }
}

/// #hsd_803AAA48

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
        u8* dest = (u8*) hsd_804D1148 + hsd_804D7984 * 36;
        hsd_804D7984 = (hsd_804D7984 + 1) % 128;
        memcpy(dest, cmd_buf, 36);
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
    file_desc->x70[file_idx] = data_size;
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
    int i;
    for (i = 0; i < 3; i++) {
        u8 file_idx = data[0];
        u8 byte1 = data[1];
        u32 size = (((u32) data[2] | ((byte1 << 8) & 0x3F00)) << 8) | data[3];
        u8 flags = byte1 >> 6;

        if (size != 0 && file_desc->x4C[file_idx] == 0) {
            file_desc->x28[file_idx] = flags;
            file_desc->x4C[file_idx] = size;
        }
        data += 4;
    }
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
    s32 first_size;
    s32 total;
    s32 i;
    u32 sector_size;
    u32 usable;
    s32 remaining;
    s32 cur_size;
    s32 cur_blocks;

    if (file_count >= 9) {
        return 0;
    }
    if (file_count == 0) {
        return 0;
    }

    first_size = file_desc->x4C[0];
    total = 1;
    if (first_size > 0) {
        sector_size = file_desc->x8;
        remaining = first_size - (s32) ((sector_size - 0x20) -
                                        (file_desc->x24 + 0x30) % sector_size);
        usable = sector_size - 0x20;
        if (remaining <= 0) {
            total = 1;
        } else {
            total = (u32) (remaining + sector_size - 0x21) / usable + 1;
        }
    }

    for (i = 1; i < file_count; i++) {
        cur_size = file_desc->x4C[i];
        if (cur_size <= 0) {
            cur_blocks = 0;
        } else if (i == 0) {
            sector_size = file_desc->x8;
            remaining =
                first_size - (s32) ((sector_size - 0x20) -
                                    (file_desc->x24 + 0x30) % sector_size);
            usable = sector_size - 0x20;
            if (remaining <= 0) {
                cur_blocks = 1;
            } else {
                cur_blocks =
                    (u32) (remaining + sector_size - 0x21) / usable + 1;
            }
        } else {
            sector_size = file_desc->x8;
            cur_blocks =
                (u32) (cur_size + sector_size - 0x21) / (sector_size - 0x20);
        }
        total += cur_blocks;
    }

    return total;
}

s32 fn_803AC7DC(CardState* state)
{
    s32 total = 0;
    s32 extra = 0;
    s32 i;

    if (state->x4C[0] > 0) {
        total = (s32) fn_803AC634(state, 0) - 1;
    }

    for (i = 1; i < 9; i++) {
        s32 size = state->x4C[i];

        if (size <= 0) {
            continue;
        }

        switch (state->x28[i]) {
        case 0:
            total += fn_803AC634(state, i) * 2;
            break;
        case 1:
            total += fn_803AC634(state, i);
            if (extra < (s32) fn_803AC634(state, i)) {
                extra = (s32) fn_803AC634(state, i);
            }
            break;
        case 2:
            total += fn_803AC634(state, i);
            if (extra < 1) {
                extra = 1;
            }
            break;
        case 3:
            total += fn_803AC634(state, i);
            break;
        }
    }

    return total + extra;
}

s32 fn_803ACB74(s32 seq_a, s32 seq_b)
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
    u32 sector_size;
    s32 retries;
    u8* buf;
    s32 offset;
    s32 result;
    u8* data;
    PAD_STACK(8);

    if (data_size == 0) {
        return 0;
    }

    sector_size = state->x8;
    retries = 0;
    buf = state->x0;
    offset = sector_size *
             (block_idx + (state->x24 + sector_size + 0x2F) / sector_size - 1);

    do {
        result =
            CARDRead((CARDFileInfo*) state->_pad1, buf, sector_size, offset);
        if (result != -1) {
            break;
        }
        retries++;
    } while (retries < 10);

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

/// @todo Currently 95.49% match - compiler hoists state+0x370 to r31, shifting
/// regalloc
s32 fn_803ACD58(CardState* state, void* icon_data, void* file_data)
{
    s32 icon_size;
    s32 hdr_plus_icon;
    s32 i;
    u8* state_bytes = (u8*) state;

    switch (state_bytes[0x3B0]) {
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

    for (i = 0; i < (state->x24 + state->x8 + 0x2F) / state->x8; i++) {
        s32 offset;
        u8* buf;
        s32 retries;
        s32 result;

        offset = i * state->x8;
        buf = state->x0;
        retries = 0;

        do {
            result =
                CARDRead((CARDFileInfo*) state->_pad1, buf, state->x8, offset);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);

        if (result < 0) {
            return result;
        }

        if (i == 0) {
            if (memcmp(state->x0, state_bytes + 0x370, 0x40) != 0) {
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
            s32 file_offset = i * ss;
            u32 remaining = state->x24 - file_offset;
            s32 data_offset = file_offset - 0x40 - icon_size;

            if (remaining > ss) {
                if (memcmp(state->x0, (u8*) file_data + data_offset, ss) != 0)
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

    return 0;
}

s32 fn_803ACF30(CardState* state, s32 file_id, s32 seq_num, s32 version)
{
    s32 buf[9];
    s32 ret;
    u32 i;
    PAD_STACK(4);

    i = 0;
    while (i < (u32) (((state->x24 + state->x8) + 0x2F) / state->x8)) {
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
        i++;
    }
    return 0;
}

/// @todo Currently 87.18% match - expression ordering and stbx vs stb+disp in
/// byte stores
s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 file_id, s32 seq_num,
                void* payload, s32 payload_size, s32 version)
{
    u32 sector_size;
    s32 retries;
    u8* buf;
    s32 offset;
    s32 result;
    s32 hdr_offset;
    u8* data;
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
            retries = 0;

            do {
                result = CARDRead((CARDFileInfo*) state->_pad1, buf,
                                  sector_size, offset);
                if (result != -1) {
                    break;
                }
                retries++;
            } while (retries < 10);

            if (result < 0) {
                return result;
            }
        } else {
            hdr_offset = 0;
        }
    }

    if (payload_size > 0) {
        memcpy(state->x0 + hdr_offset + 0x20, payload, payload_size);
    }

    {
        s32 remaining = (state->x8 - hdr_offset) - payload_size - 0x20;
        if (remaining != 0) {
            memset(state->x0 + payload_size + 0x20 + hdr_offset, 0, remaining);
        }
    }

    memset(state->x0 + hdr_offset, 0, 0x20);

    data = state->x0 + hdr_offset;
    data[0x10] = (u8) (file_id >> 8);

    data = state->x0 + hdr_offset;
    data[0x11] = (u8) file_id;

    data = state->x0 + hdr_offset;
    data[0x12] = (u8) seq_num;

    fn_803AC3F8(state, state->x0 + hdr_offset + 0x13, version);
    hsd_803B2FA0(state->x0 + hdr_offset, state->x8 - hdr_offset);

    {
        u32 write_size = state->x8;
        retries = 0;
        buf = state->x0;

        do {
            result = CARDWrite((CARDFileInfo*) state->_pad1, buf, write_size,
                               offset);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);
    }

    return result;
}

/// #fn_803AD16C

s32 fn_803ADE4C(s32 card_state, s32 channel, s32 callback)
{
    s32 buf1[9];
    s32 buf2[9];
    s32 result;
    s32 saved;
    s32 snap;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(16);

    buf1[0] = 12;
    buf1[1] = card_state;
    hsd_804D7998 = hsd_804D7984;
    buf1[2] = channel;
    result = fn_803AC168(buf1);
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

    buf2[0] = 17;
    buf2[1] = card_state;
    result = fn_803AC168(buf2);
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
    entries[0].x4 = card_state;
    entries[0].x8 = callback;
    entries[0].xC = 0;
    hsd_804D7998 = -1;
    return 0;
}

typedef struct {
    u8* x0;
    s32 x4;
    u32 x8;
    CARDFileInfo file_info;
    s32 x20;
    u32 x24;
    s32 x28[9];
    s32 x4C[9];
    s32 x70[9];
    u8 pad_94[0xDC];
    s32 x170[64];
    s32 x270[64];
    u8 x370[0x40];
    u8 x3B0;
    u8 pad_3B1[0xAF];
    s32 x460;
} CardStateExt;

s32 fn_803ADF90(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardStateExt* state = (CardStateExt*) arg0;
    CardBufEntry* entry;
    s32 block_map[64];
    s32 blocks_before;
    s32 callback_seq;
    s32 file_blocks;
    s32 i;
    s32 logical;
    s32 remaining;
    s32 result;
    s32 seq_num;
    u8* dst;

    callback_seq = 0;
    if (arg3 == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy = hsd_804D799C == 1;
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    if (arg1 >= 9 || arg1 == 0) {
        blocks_before = 0;
    } else {
        blocks_before = 1;
        if (state->x4C[0] > 0) {
            blocks_before = fn_803AC634(arg0, 0);
        }
        for (i = 1; i < arg1; i++) {
            blocks_before += fn_803AC634(arg0, i);
        }
    }

    if (state->x4C[arg1] > 0) {
        file_blocks = fn_803AC634(arg0, arg1);
    } else {
        file_blocks = 0;
    }

    for (i = 0; i < file_blocks; i++) {
        block_map[i] = -1;
    }

    seq_num = -1;
    for (i = 0; i < fn_803AC7DC((CardState*) arg0); i++) {
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
            block_map[logical] = i + 1;
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
        }
    }

    if (callback_seq != 0) {
        return callback_seq;
    }

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 retries = 0;

        do {
            result = CARDFastOpen(state->x4, state->x20, &state->file_info);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);

        if (result < 0) {
            return result;
        }
    }

    dst = (u8*) arg2;
    remaining = state->x4C[arg1];

    for (i = 0; i < file_blocks && remaining > 0; i++) {
        s32 chunk;
        s32 data_block = block_map[i];

        if (arg1 == 0 && i == 0) {
            chunk = (state->x8 - 0x20) - ((state->x24 + 0x30) % state->x8);
        } else {
            chunk = state->x8 - 0x20;
        }

        if (remaining > chunk) {
            if (data_block >= 0) {
                if (arg3 != 0) {
                    s32 cmd[9] = { 0 };

                    cmd[0] = 2;
                    cmd[1] = (s32) arg0;
                    cmd[4] = data_block;
                    cmd[6] = (s32) dst;
                    cmd[7] =
                        state->x8 *
                        (data_block +
                         ((state->x24 + state->x8 + 0x2F) / state->x8) - 1);
                    cmd[8] = chunk;
                    result = fn_803AC168(cmd);
                    if (result < 0) {
                        if (hsd_804D7998 >= 0) {
                            fn_803AC2E0();
                        }
                        return result;
                    }
                } else {
                    s32 offset;
                    s32 retries = 0;

                    offset =
                        state->x8 *
                        (data_block +
                         ((state->x24 + state->x8 + 0x2F) / state->x8) - 1);
                    do {
                        result = CARDRead(&state->file_info, state->x0,
                                          state->x8, offset);
                        if (result != -1) {
                            break;
                        }
                        retries++;
                    } while (retries < 10);

                    if (result < 0) {
                        callback_seq = -259;
                    } else {
                        s32 read_ofs = data_block == 0
                                           ? (state->x24 + 0x30) % state->x8
                                           : 0;
                        if (hsd_803B31CC(state->x0 + read_ofs,
                                         state->x8 - read_ofs) < 0)
                        {
                            callback_seq = -259;
                        } else if (chunk != 0 && dst != NULL) {
                            memcpy(dst, state->x0 + read_ofs + 0x20, chunk);
                        }
                    }
                }
            } else if (arg3 != 0) {
                if (chunk != 0) {
                    s32 cmd[9] = { 0 };

                    cmd[0] = 4;
                    cmd[1] = (s32) arg0;
                    cmd[6] = (s32) dst;
                    cmd[8] = chunk;
                    result = fn_803AC168(cmd);
                    if (result < 0) {
                        if (hsd_804D7998 >= 0) {
                            fn_803AC2E0();
                        }
                        return result;
                    }
                }
            } else {
                memset(dst, 0, chunk);
            }

            remaining -= chunk;
            dst += chunk;
        } else {
            if (data_block >= 0) {
                if (arg3 != 0) {
                    s32 cmd[9] = { 0 };

                    cmd[0] = 2;
                    cmd[1] = (s32) arg0;
                    cmd[4] = data_block;
                    cmd[6] = (s32) dst;
                    cmd[7] =
                        state->x8 *
                        (data_block +
                         ((state->x24 + state->x8 + 0x2F) / state->x8) - 1);
                    cmd[8] = remaining;
                    result = fn_803AC168(cmd);
                    if (result < 0) {
                        if (hsd_804D7998 >= 0) {
                            fn_803AC2E0();
                        }
                        return result;
                    }
                } else {
                    s32 offset;
                    s32 retries = 0;
                    s32 read_ofs;

                    offset =
                        state->x8 *
                        (data_block +
                         ((state->x24 + state->x8 + 0x2F) / state->x8) - 1);
                    do {
                        result = CARDRead(&state->file_info, state->x0,
                                          state->x8, offset);
                        if (result != -1) {
                            break;
                        }
                        retries++;
                    } while (retries < 10);

                    if (result < 0) {
                        callback_seq = -259;
                    } else {
                        read_ofs = data_block == 0
                                       ? (state->x24 + 0x30) % state->x8
                                       : 0;
                        if (hsd_803B31CC(state->x0 + read_ofs,
                                         state->x8 - read_ofs) < 0)
                        {
                            callback_seq = -259;
                        } else if (remaining != 0 && dst != NULL) {
                            memcpy(dst, state->x0 + read_ofs + 0x20,
                                   remaining);
                        }
                    }
                }
            }
            remaining = 0;
        }
    }

    if (arg3 == 0) {
        s32 retries = 0;

        do {
            result = CARDClose(&state->file_info);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);

        if (result < 0) {
            return -267;
        }
    } else {
        entry = (CardBufEntry*) hsd_804D1138;
        entry[0].x0 = 1;
        entry[0].x4 = (s32) arg0;
        entry[0].x8 = arg4;
        entry[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return callback_seq;
}

s32 fn_803AE7F8(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardStateExt* state = (CardStateExt*) arg0;
    CardBufEntry* entry;
    s32 primary[64];
    s32 secondary[64];
    s32 free_blocks[64];
    s32 blocks_before;
    s32 current_seq;
    s32 file_blocks;
    s32 free_count;
    s32 i;
    s32 logical;
    s32 repair_result;
    s32 result;
    s32 total_blocks;
    u8* data;

    repair_result = 0;
    if (arg3 == 0) {
        BOOL intr = OSDisableInterrupts();
        s32 busy = hsd_804D799C == 1;
        OSRestoreInterrupts(intr);
        if (busy) {
            return -264;
        }
    }

    if (arg1 >= 9 || arg1 == 0) {
        blocks_before = 0;
    } else {
        blocks_before = 1;
        if (state->x4C[0] > 0) {
            blocks_before = fn_803AC634(arg0, 0);
        }
        for (i = 1; i < arg1; i++) {
            blocks_before += fn_803AC634(arg0, i);
        }
    }

    if (state->x4C[arg1] > 0) {
        file_blocks = fn_803AC634(arg0, arg1);
    } else {
        file_blocks = 0;
    }

    for (i = 0; i < file_blocks; i++) {
        primary[i] = -1;
        secondary[i] = -1;
    }

    current_seq = -1;
    free_count = 0;
    total_blocks = fn_803AC7DC((CardState*) arg0);
    for (i = 0; i < total_blocks; i++) {
        s32 phys = i + 1;
        s32 file_idx = state->x170[phys];

        if (file_idx < 0) {
            free_blocks[free_count++] = phys;
            continue;
        }

        logical = file_idx - blocks_before;
        if (logical >= 0 && logical < file_blocks) {
            if (current_seq == -1 ||
                fn_803ACB74(current_seq, state->x270[phys]) < 0)
            {
                current_seq = state->x270[phys];
            }
            if (primary[logical] < 0) {
                primary[logical] = phys;
            } else {
                secondary[logical] = phys;
            }
        }
    }

    for (i = 0; i < file_blocks; i++) {
        if (primary[i] < 0) {
            if (free_count <= 0) {
                return -257;
            }
            primary[i] = free_blocks[--free_count];
        }
        if (secondary[i] < 0) {
            if (free_count <= 0) {
                repair_result = -258;
            } else {
                secondary[i] = free_blocks[--free_count];
            }
        }
    }

    if (arg3 != 0) {
        hsd_804D7998 = hsd_804D7984;
    } else {
        s32 retries = 0;

        do {
            result = CARDFastOpen(state->x4, state->x20, &state->file_info);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);

        if (result < 0) {
            return result;
        }
    }

    if (current_seq >= 0) {
        s32* maps[2];
        s32 pass;
        s32 verify_failed;

        maps[0] = primary;
        maps[1] = secondary;
        verify_failed = 0;
        for (pass = 0; pass < 2 && !verify_failed; pass++) {
            s32 remaining = state->x4C[arg1];
            s32* map = maps[pass];

            data = (u8*) arg2;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys = map[i];
                s32 chunk = state->x8 - 0x20;

                if (remaining < chunk) {
                    chunk = remaining;
                }

                if (phys >= 0) {
                    if (arg3 != 0) {
                        s32 cmd[9] = { 0 };

                        cmd[0] = 5;
                        cmd[1] = (s32) arg0;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] =
                            state->x8 *
                            (phys +
                             ((state->x24 + state->x8 + 0x2F) / state->x8) -
                             1);
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                        if (result < 0) {
                            if (hsd_804D7998 >= 0) {
                                fn_803AC2E0();
                            }
                            return result;
                        }
                    } else {
                        result = fn_803ACC0C((CardState*) arg0, phys,
                                             blocks_before + i, current_seq,
                                             data, chunk);
                        if (result < 0) {
                            s32 retries = 0;

                            do {
                                if (CARDClose(&state->file_info) != -1) {
                                    break;
                                }
                                retries++;
                            } while (retries < 10);
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
            }
        }

        if (!verify_failed) {
            if (arg3 != 0) {
                s32 cmd[9] = { 0 };

                cmd[0] = 6;
                cmd[1] = (s32) arg0;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    if (hsd_804D7998 >= 0) {
                        fn_803AC2E0();
                    }
                    return result;
                }
            } else {
                s32 retries = 0;

                do {
                    result = CARDClose(&state->file_info);
                    if (result != -1) {
                        break;
                    }
                    retries++;
                } while (retries < 10);

                if (result < 0) {
                    return -267;
                }
                return 1;
            }
        }
    }

    current_seq = (u8) (current_seq + 1);
    {
        s32* maps[2];
        s32 pass;

        maps[0] = primary;
        maps[1] = secondary;
        for (pass = 0; pass < 2; pass++) {
            s32 remaining = state->x4C[arg1];
            s32* map = maps[pass];

            data = (u8*) arg2;
            for (i = 0; i < file_blocks && remaining > 0; i++) {
                s32 phys = map[i];
                s32 chunk = state->x8 - 0x20;

                if (remaining < chunk) {
                    chunk = remaining;
                }

                if (phys >= 0) {
                    if (arg3 != 0) {
                        s32 cmd[9] = { 0 };

                        cmd[0] = 1;
                        cmd[1] = (s32) arg0;
                        cmd[2] = arg1;
                        cmd[3] = phys;
                        cmd[4] = blocks_before + i;
                        cmd[5] = current_seq;
                        cmd[6] = (s32) data;
                        cmd[7] =
                            state->x8 *
                            (phys +
                             ((state->x24 + state->x8 + 0x2F) / state->x8) -
                             1);
                        cmd[8] = chunk;
                        result = fn_803AC168(cmd);
                        if (result < 0) {
                            if (hsd_804D7998 >= 0) {
                                fn_803AC2E0();
                            }
                            return result;
                        }
                    } else {
                        result = fn_803ACFC0((CardState*) arg0, phys,
                                             blocks_before + i, current_seq,
                                             data, chunk, arg1);
                        if (result < 0) {
                            state->x170[phys] = -0x7FFF;
                            state->x270[phys] = 0;
                            {
                                s32 retries = 0;

                                do {
                                    if (CARDClose(&state->file_info) != -1) {
                                        break;
                                    }
                                    retries++;
                                } while (retries < 10);
                            }
                            return pass == 0 ? -260 : -258;
                        }
                    }

                    state->x170[phys] = blocks_before + i;
                    state->x270[phys] = current_seq;
                }

                remaining -= chunk;
                data += chunk;
            }
        }
    }

    if (arg3 == 0) {
        s32 retries = 0;

        do {
            result = CARDClose(&state->file_info);
            if (result != -1) {
                break;
            }
            retries++;
        } while (retries < 10);

        if (result < 0) {
            return repair_result == 0 ? -267 : repair_result;
        }
    } else {
        entry = (CardBufEntry*) hsd_804D1138;
        entry[0].x0 = 2;
        entry[0].x4 = (s32) arg0;
        entry[0].x8 = arg4;
        entry[0].xC = arg1;
        hsd_804D7998 = -1;
    }

    return repair_result;
}

/// #fn_803AF3F0

/// #fn_803B0120

s32 fn_803B0E9C(struct CardState* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    CardStateExt* state = (CardStateExt*) arg0;
    u8 digest[0x30];
    s32 block_idx;
    s32 digest_idx;
    s32 remaining;
    s32 payload_pos;
    s32 result;
    u32 sector_size;
    u8* file_data;

    state->x24 = hsd_803AC340(state->x370);
    file_data = (u8*) arg2;

    if (arg3 == 0) {
        if (arg4 != 0) {
            u32 blocks;

            for (block_idx = 0; block_idx < 10; block_idx++) {
                s32 cmd[9] = { 0 };

                blocks = (state->x24 + state->x8 + 0x2F) / state->x8;
                if ((u32) block_idx >= blocks) {
                    break;
                }

                cmd[0] = 10;
                cmd[1] = (s32) state;
                cmd[2] = block_idx;
                cmd[3] = arg1;
                cmd[4] = arg2;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    return result;
                }
            }

            result = fn_803AC168((s32[9]) { 6, (s32) state });
            if (result < 0) {
                return result;
            }
        } else {
            result =
                fn_803ACD58((CardState*) state, (void*) arg1, (void*) arg2);
            if (result < 0) {
                return result;
            }
            if (result == 0) {
                return 1;
            }
        }
    }

    if (arg4 != 0) {
        u32 blocks = (state->x24 + state->x8 + 0x2F) / state->x8;

        for (block_idx = 0; (u32) block_idx < blocks; block_idx++) {
            if ((u32) (block_idx + 1) == blocks) {
                if (arg3 != 0) {
                    s32 cmd[9] = { 0 };

                    cmd[0] = 4;
                    cmd[1] = (s32) state;
                    cmd[6] = (s32) state->x0;
                    cmd[8] = state->x8;
                    result = fn_803AC168(cmd);
                } else {
                    s32 cmd[9] = { 0 };

                    cmd[0] = 2;
                    cmd[1] = (s32) state;
                    cmd[4] = -1;
                    cmd[7] = block_idx * state->x8;
                    cmd[8] = state->x4C[0] > 0;
                    result = fn_803AC168(cmd);
                }
                if (result < 0) {
                    return result;
                }
            }

            {
                s32 cmd[9] = { 0 };

                cmd[0] = 9;
                cmd[1] = (s32) state;
                cmd[2] = block_idx;
                cmd[3] = arg1;
                cmd[4] = arg2;
                result = fn_803AC168(cmd);
                if (result < 0) {
                    return result;
                }
            }
        }
        return 0;
    }

    sector_size = state->x8;
    if (state->x24 + 0x30 < sector_size) {
        if (arg3 != 0) {
            memset(state->x0, 0, sector_size);
        } else {
            s32 retries = 0;

            do {
                result =
                    CARDRead(&state->file_info, state->x0, sector_size, 0);
                if (result != -1) {
                    break;
                }
                retries++;
            } while (retries < 10);

            if (result < 0) {
                return result;
            }
        }
    }

    memcpy(state->x0, state->x370, 0x40);
    payload_pos = 0x40;
    switch (state->x3B0) {
    case 2:
        memcpy(state->x0 + 0x40, (void*) arg1, 0x1800);
        payload_pos = 0x1840;
        break;
    case 1:
        memcpy(state->x0 + 0x40, (void*) arg1, 0xE00);
        payload_pos = 0xE40;
        break;
    }

    memset(digest, 0, sizeof(digest));
    block_idx = 0;
    digest_idx = 0;
    remaining = state->x24 - payload_pos;

    while (remaining >= 0) {
        sector_size = state->x8;
        if ((u32) (payload_pos + remaining) > sector_size) {
            s32 copied = sector_size - payload_pos;
            s32 retries;
            s32 offset;

            memcpy(state->x0 + payload_pos, file_data, copied);
            file_data += copied;
            remaining -= copied;
            hsd_803B2B20(state->x0, sector_size, &digest[digest_idx]);

            retries = 0;
            offset = sector_size * block_idx;
            do {
                result = CARDWrite(&state->file_info, state->x0, sector_size,
                                   offset);
                if (result != -1) {
                    break;
                }
                retries++;
            } while (retries < 10);

            if (result < 0) {
                return result;
            }

            payload_pos = 0;
            block_idx++;
            digest_idx += 0x10;

            if (remaining + 0x30 < (s32) state->x24) {
                if (arg3 != 0) {
                    memset(state->x0, 0, state->x8);
                } else {
                    s32 retries2 = 0;
                    s32 offset2 = state->x8 * block_idx;

                    do {
                        result = CARDRead(&state->file_info, state->x0,
                                          state->x8, offset2);
                        if (result != -1) {
                            break;
                        }
                        retries2++;
                    } while (retries2 < 10);

                    if (result < 0) {
                        return result;
                    }
                }
            }
            continue;
        }

        memcpy(state->x0 + payload_pos, file_data, remaining);
        payload_pos += remaining;
        hsd_803B2B20(state->x0, payload_pos, &digest[digest_idx]);
        memcpy(state->x0 + payload_pos, digest, 0x30);
        remaining = -1;

        {
            s32 retries = 0;
            s32 offset = state->x8 * block_idx;

            do {
                result =
                    CARDWrite(&state->file_info, state->x0, state->x8, offset);
                if (result != -1) {
                    break;
                }
                retries++;
            } while (retries < 10);
        }

        if (result < 0) {
            return result;
        }

        block_idx++;
        digest_idx += 0x10;
    }

    return 0;
}

/// #fn_803B1338

/// @todo Currently 90.28% match - stwx vs stw+disp in rollback (same as
/// fn_803ADE4C)
s32 fn_803B1F78(CardState* state, s32 channel, s32 file_id, s32 seq_num,
                s32 callback)
{
    s32 buf1[9];
    s32 buf2[9];
    s32 result;
    s32 blocks;
    s32 saved;
    s32 snap;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(8);

    hsd_804D7998 = hsd_804D7984;
    blocks = hsd_803B2674(state);
    buf1[0] = 7;
    buf1[1] = (s32) state;
    buf1[2] = channel;
    buf1[3] = state->x8 * blocks;
    result = fn_803AC168(buf1);
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

    result = fn_803B0E9C(state, file_id, seq_num, 1, 1);
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

    result = fn_803B1338(state, 1);
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

    buf2[0] = 8;
    buf2[1] = (s32) state;
    result = fn_803AC168(buf2);
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

    entries[0].x0 = 6;
    entries[0].x4 = (s32) state;
    entries[0].x8 = callback;
    result = 0;
    entries[0].xC = result;
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
        return 0;
    }
    hsd_804D7998 = -1;
    return 0;
}

/// @todo Currently 94.85% match - stwx vs stw+disp in rollback (same as
/// fn_803ADE4C)
s32 fn_803B21E8(s32 card_state, s32 file_id, s32 seq_num, s32 callback)
{
    s32 buf[9];
    s32 result;
    s32 saved;
    s32 snap;
    CardBufEntry* entries = (CardBufEntry*) hsd_804D1138;
    PAD_STACK(8);

    hsd_804D7998 = hsd_804D7984;
    result = fn_803B0E9C((CardState*) card_state, file_id, seq_num, 0, 1);
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

    buf[0] = 8;
    buf[1] = card_state;
    result = fn_803AC168(buf);
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
                entries[saved].x10 = 0;
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
    s32 i;

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

void hsd_803B24E4(s32* ctx, int channel, int file_no, void* work_buf)
{
    memset(ctx, 0, 0x464);
    ctx[8] = -1;
    ctx[1] = channel;
    ctx[2] = file_no;
    ctx[0] = (s32) work_buf;
}

int hsd_803B2550(s32* arg0, const char* arg1, void (*arg2)(int, int))
{
    u8* base = hsd_804D1138;
    s32 chan = arg0[1];
    s32 retries = 0;
    s32 result;
    s32 write_idx;

    do {
        result = CARDOpen(chan, (char*) arg1, (CARDFileInfo*) (arg0 + 3));
        if (result != -1) {
            break;
        }
        retries++;
    } while (retries < 10);

    if (result < 0) {
        return result;
    }

    result = 0;
    {
        s32 tmp = arg0[4];
        if (tmp == -1) {
            do {
                result++;
            } while (result < 10);
        }
        if (tmp < 0) {
            return tmp;
        }
        write_idx = tmp;
    }

    chan = 0;
    do {
        if (CARDClose((CARDFileInfo*) (arg0 + 3)) != -1) {
            break;
        }
        chan++;
    } while (chan < 10);

    {
        s32 read_idx = hsd_804D7990;
        retries = hsd_804D7994;

        if (read_idx == retries) {
            if (*(s32*) (base + read_idx * 0x18 + 0x1210) != 0) {
                return -265;
            }
        }
    }

    {
        u8* entry = base + retries * 0x18;
        s32 next = retries + 1;
        *(s32*) (entry + 0x1210) = 5;
        *(s32*) (entry + 0x1214) = (s32) arg0;
        *(s32*) (entry + 0x1218) = write_idx;
        *(s32*) (entry + 0x1224) = (s32) arg2;
        hsd_804D7994 = next % 32;
    }

    return 0;
}

s32 hsd_803B2674(CardState* state)
{
    s32 blocks;

    state->x24 = hsd_803AC340((u8*) state + 0x3B0);

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
    PAD_STACK(16);

    state->x24 = hsd_803AC340((u8*) state + 0x3B0);
    i = 0;
    hsd_804D7998 = hsd_804D7984;

    for (i = 0; i < (state->x24 + state->x8 + 0x2F) / state->x8; i++) {
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
