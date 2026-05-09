#include "hsd_3AA7.h"

#include "hsd_3A94.h"
#include "hsd_3B2E.h"

#include <dolphin/card.h>
#include <dolphin/os.h>

/* 4D7980 */ extern s32 hsd_804D7980;
/* 4D7984 */ extern volatile s32 hsd_804D7984;
/* 4D7998 */ extern s32 hsd_804D7998;
/* 4D799C */ extern s32 hsd_804D799C;

typedef struct CardBufEntry {
    s32 x0, x4, x8, xC;
    s32 x10;
    s32 x14, x18, x1C, x20;
} CardBufEntry;

typedef struct {
    s32 type;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} HsdCmdEntry;

typedef struct {
    u8 pad_0[0x4];
    s32 x4;
    u8 pad_8[0x4];
    s32 xC;
    s32 x10;
} Hsd803B2550Ctx;

#define CMD_QUEUE(base) ((HsdCmdEntry*) ((base) + 0x1210))

/// #fn_803AA790

/// #hsd_803AAA48

/// @todo Currently 91.67% match - volatile load scheduling in critical section
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

void hsd_803AC3E0(struct hsd_803AC3E0_arg0_t* file_desc, int file_idx,
                  int file_size, int file_offset, int file_flags)
{
    file_desc->x28[file_idx] = file_offset;
    file_desc->x4C[file_idx] = file_size;
    file_desc->x70[file_idx] = file_flags;
}

void fn_803AC3F8(void* arg0, u8* data, s32 file_idx)
{
    struct hsd_803AC3E0_arg0_t* file_desc = arg0;
    s32 i;
    s32 start;

    if (file_idx + 1 >= 9 || file_desc->x4C[file_idx + 1] == 0) {
        start = file_idx - 2;
    } else {
        start = file_idx - 1;
    }
    if (start < 0) {
        start = 0;
    }

    for (i = 0; i < 3 && start + i < 9; i++) {
        s32 idx = start + i;
        data[0] = idx;
        data[1] = ((u32) file_desc->x4C[idx] >> 0x10 & 0x3F) |
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

void hsd_803AC558(struct hsd_803AC3E0_arg0_t* file_desc, u8* data)
{
    s32 file_size;
    s32 file_size_2;
    s32 file_size_3;
    u8 flags;
    u8 flags_2;
    u8 flags_3;
    u8 flags_size;
    u8 flags_size_2;
    u8 flags_size_3;
    u8 file_idx;
    u8 file_idx_2;
    u8 file_idx_3;
    u8* p;
    u8 size_mid;
    u8 size_mid_2;
    u8 size_mid_3;

    p = data + 1;
    flags_size = p[0];
    file_idx = data[0];
    size_mid = p[1];
    flags = (flags_size >> 6) & 3;
    file_size =
        ((((s32) size_mid & ~0x3F00) | ((flags_size << 8) & 0x3F00)) << 8) | p[2];
    if (file_size != 0 && file_desc->x4C[file_idx] == 0) {
        file_desc->x28[file_idx] = flags;
        file_desc->x4C[file_idx] = file_size;
    }

    p += 3;
    flags_size_2 = p[1];
    file_idx_2 = p[0];
    size_mid_2 = p[2];
    flags_2 = (flags_size_2 >> 6) & 3;
    file_size_2 =
        ((((s32) size_mid_2 & ~0x3F00) | ((flags_size_2 << 8) & 0x3F00)) << 8) |
        p[3];
    p += 4;
    if (file_size_2 != 0 && file_desc->x4C[file_idx_2] == 0) {
        file_desc->x28[file_idx_2] = flags_2;
        file_desc->x4C[file_idx_2] = file_size_2;
    }

    flags_size_3 = p[1];
    file_idx_3 = p[0];
    size_mid_3 = p[2];
    flags_3 = (flags_size_3 >> 6) & 3;
    file_size_3 =
        ((((s32) size_mid_3 & ~0x3F00) | ((flags_size_3 << 8) & 0x3F00)) << 8) |
        p[3];
    if (file_size_3 != 0 && file_desc->x4C[file_idx_3] == 0) {
        file_desc->x28[file_idx_3] = flags_3;
        file_desc->x4C[file_idx_3] = file_size_3;
    }
}

u32 fn_803AC634(struct hsd_803AC3E0_arg0_t* file_desc, s32 file_idx)
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

s32 fn_803AC6B8(struct hsd_803AC3E0_arg0_t* file_desc, s32 file_count)
{
    s32 add_blocks;
    s32 blocks;
    s32 ctr;
    s32 file_size;
    s32 file_size_2;
    s32 i;
    s32 positive;
    s32 remaining;
    int* file_size_p;
    u32 sector_size;
    u32 usable;

    if (file_count >= 9) {
        return 0;
    }
    if (file_count == 0) {
        return 0;
    }
    file_size = file_desc->x4C[0];
    blocks = 1;
    positive = file_size > 0;
    if (positive != 0) {
        if (positive == 0) {
            add_blocks = 0;
        } else {
            sector_size = file_desc->x8;
            usable = sector_size - 0x20;
            remaining = file_size - (s32) (usable -
                                           (file_desc->x24 + 0x30) %
                                               sector_size);
            if (remaining <= 0) {
                add_blocks = 1;
            } else {
                add_blocks = (u32) (remaining + sector_size - 0x21) / usable + 1;
            }
        }
        blocks = add_blocks;
    }
    ctr = file_count - 1;
    file_size_p = &file_desc->x4C[1];
    i = 1;
    if (file_count > 1) {
        do {
            file_size_2 = *file_size_p;
            if (file_size_2 <= 0) {
                add_blocks = 0;
            } else if (i == 0) {
                sector_size = file_desc->x8;
                usable = sector_size - 0x20;
                remaining = file_size - (s32) (usable -
                                               (file_desc->x24 + 0x30) %
                                                   sector_size);
                if (remaining <= 0) {
                    add_blocks = 1;
                } else {
                    add_blocks =
                        (u32) (remaining + sector_size - 0x21) / usable + 1;
                }
            } else {
                sector_size = file_desc->x8;
                add_blocks = (u32) (file_size_2 + sector_size - 0x21) /
                             (sector_size - 0x20);
            }
            blocks += add_blocks;
            file_size_p++;
            i++;
            ctr--;
        } while (ctr != 0);
    }
    return blocks;
}

/// #fn_803AC7DC

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
/// @todo Currently 95.90% match - arg0/arg1 register swap (r27/r22 vs r26/r27)
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

/// @todo Currently 93.89% match - mwcc reassociates addition order in loop
/// cond
s32 fn_803ACF30(CardState* state, s32 file_id, s32 seq_num, s32 version)
{
    s32 buf[9];
    u32 i;
    s32 ret;
    PAD_STACK(4);

    for (i = 0; i < (state->x24 + state->x8 + 0x2F) / state->x8; i++) {
        buf[0] = 11;
        buf[1] = (s32) state;
        buf[2] = (s32) i;
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

/// @todo Currently 93.46% match - stwx vs stw+disp in rollback, reg swap in
/// 2nd path
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

/// #fn_803ADF90

/// #fn_803AE7F8

/// #fn_803AF3F0

/// #fn_803B0120

/// #fn_803B0E9C

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

    result = fn_803B0E9C((s32) state, file_id, seq_num, 1, 1);
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
    result = fn_803B0E9C(card_state, file_id, seq_num, 0, 1);
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

/// #hsd_803B2374

void hsd_803B24E4(s32* ctx, int channel, int file_no, void* work_buf)
{
    memset(ctx, 0, 0x464);
    ctx[8] = -1;
    ctx[1] = channel;
    ctx[2] = file_no;
    ctx[0] = (s32) work_buf;
}

int hsd_803B2550(s32* arg0, char* arg1, void (*arg2)(int, int))
{
    Hsd803B2550Ctx* ctx;
    s32 close_retries;
    s32 read_idx;
    s32 result;
    s32 retries;
    s32 write_idx;
    u8* base;
    HsdCmdEntry* entry;

    ctx = (Hsd803B2550Ctx*) arg0;
    retries = 0;
    do {
        result = CARDOpen(ctx->x4, arg1, (CARDFileInfo*) ((u8*) ctx + 0xC));
        if (result != -1) {
            break;
        }
        retries++;
    } while (retries < 10);
    if (result < 0) {
        return result;
    }

    retries = 0;
    do {
        result = ctx->x10;
        if (result != -1) {
            break;
        }
        retries++;
    } while (retries < 10);
    if (result < 0) {
        return result;
    }

    close_retries = 0;
    do {
        result = CARDClose((CARDFileInfo*) ((u8*) ctx + 0xC));
        if (result != -1) {
            break;
        }
        close_retries++;
    } while (close_retries < 10);

    base = hsd_804D1138;
    read_idx = hsd_804D7990;
    write_idx = hsd_804D7994;
    if (read_idx == write_idx) {
        if (CMD_QUEUE(base)[read_idx].type != 0) {
            return -265;
        }
    }

    entry = &CMD_QUEUE(base)[write_idx];
    entry->type = 5;
    entry->f1 = (s32) arg0;
    entry->f2 = ctx->x10;
    entry->f5 = (s32) arg2;
    hsd_804D7994 = (write_idx + 1) % 32;
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

/// @todo Currently 87.04% match - result saved to r27 instead of staying in r3
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
