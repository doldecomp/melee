#include "hsd_393C.h"

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/video.h>

/// @todo misnomer - moved from particle file, not particle-related
struct ParticleConsoleState {
    /* 00 */ u8 x0_b0 : 1;
    /* 00 */ u8 x0_b1 : 1;
    /* 04 */ u8* out_buf;
    /* 08 */ u32 buf_size;
    /* 0C */ int xC;
    /* 10 */ u8 x10;
    /* 11 */ u8 x11;
    /* 12 */ u8 x12;
    /* 13 */ u8 x13;
    /* 14 */ int x14;
    /* 18 */ int x18;
    /* 1C */ int x1C;
    /* 20 */ int x20;
    /* 20 */ UNK_T x24;
};
STATIC_ASSERT(sizeof(struct ParticleConsoleState) == 0x28);

/* 4CF7E8 */ static struct ParticleConsoleState hsd_804CF7E8;

void fn_80393C14(const u8* buf, size_t size)
{
    int i;

    const u32 out_size = hsd_804CF7E8.buf_size;

    int write_pos = hsd_804CF7E8.xC;
    u8* out_buf = hsd_804CF7E8.out_buf;
    u8 line_len = hsd_804CF7E8.x11;

    for (i = 0; i < size; i++) {
        const u32 tmp = out_size - 1;
        switch (buf[i]) {
        case '\r':
            break;
        case '\n':
            if (line_len != 0 || out_buf[(write_pos + tmp) % out_size] != '\0')
            {
                out_buf[write_pos] = line_len;
                write_pos = (write_pos + 1) % out_size;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                line_len = 0;
            }
            break;
        default:
            out_buf[write_pos] = buf[i];
            if (++line_len == 0x36) {
                write_pos = (write_pos + 1) % out_size;
                out_buf[write_pos] = line_len;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                line_len = 0;
            }
            write_pos = (write_pos + 1) % out_size;
            hsd_804CF7E8.x1C++;
            break;
        }
    }
    hsd_804CF7E8.xC = write_pos;
    hsd_804CF7E8.x11 = line_len;
}

s32 hsd_80393D2C(s32 enable)
{
    struct ParticleConsoleState* sp = &hsd_804CF7E8;
    s32 old = sp->x0_b1;

    if (enable != 0) {
        sp->x0_b1 = 1;
        HSD_SetReportCallback(fn_80393C14);
    } else {
        sp->x0_b1 = 0;
        HSD_SetReportCallback(NULL);
    }
    return old;
}

void hsd_80393DA0(u8* buf, size_t size)
{
    PAD_STACK(4);
    memset(&hsd_804CF7E8, 0, sizeof(hsd_804CF7E8) - sizeof(hsd_804CF7E8.x24));
    hsd_804CF7E8.out_buf = buf;
    hsd_804CF7E8.buf_size = size;
    memset(buf, 0, size);
    hsd_804CF7E8.x0_b0 = true;
    hsd_804CF7E8.x0_b1 = true;
    HSD_SetReportCallback(fn_80393C14);
}

void hsd_80393E34(s32* col_out, s32* row_out)
{
    if (col_out != NULL) {
        *col_out = hsd_804CF7E8.x14;
    }
    if (row_out != NULL) {
        *row_out = hsd_804CF7E8.x18;
    }
}

void hsd_80393E68(u32 col, u32 row)
{
    struct ParticleConsoleState* sp = &hsd_804CF7E8;
    u32 byte_val;
    u32 buf_size;
    u8* out_buf;
    u32 sum;
    u32 pos;
    u32 counter;

    if (!sp->x0_b0) {
        return;
    }

    byte_val = sp->x11;
    counter = 0;
    buf_size = sp->buf_size;
    out_buf = sp->out_buf;
    sum = sp->xC + buf_size;
    pos = byte_val;

    while (counter < row && pos < buf_size) {
        pos++;
        byte_val = out_buf[(sum - pos) % buf_size];
        counter++;
        pos += byte_val;
    }

    sp->x18 = counter;
    sp->x1C = pos;
    sp->x20 = byte_val;

    if (col < byte_val) {
        sp->x14 = col;
    } else {
        sp->x14 = byte_val;
    }
}

void hsd_80393EF4(int col_delta, int row_delta)
{
    u32 byte_val;
    u32 buf_size;
    int* pos_ptr;
    u32 counter;
    u32 pos;
    u32 sum;
    u8* out_buf;
    struct ParticleConsoleState* sp = &hsd_804CF7E8;

    if (!sp->x0_b0) {
        return;
    }

    buf_size = sp->buf_size;

    if ((u32) * (pos_ptr = &sp->x1C) >= buf_size) {
        hsd_80393E68(sp->x14 + col_delta, sp->x18 + row_delta);
        return;
    }

    out_buf = sp->out_buf;
    pos = *pos_ptr;
    byte_val = sp->x20;
    sum = sp->xC + buf_size;

    if (row_delta > 0) {
        counter = 0;

        while (counter < (u32) row_delta && pos < buf_size) {
            pos++;
            byte_val = out_buf[(sum - pos) % buf_size];
            counter++;
            pos += byte_val;
        }

        sp->x18 += counter;
        *pos_ptr = pos;

        if (col_delta >= 0) {
            int* col_ptr = &sp->x14;
            *col_ptr += col_delta;
            if ((u32) *col_ptr > byte_val) {
                *col_ptr = byte_val;
            }
        } else {
            int* col_ptr;
            u32 col = *(col_ptr = &sp->x14);
            col_delta = -col_delta;
            if (col > (u32) col_delta) {
                *col_ptr = col - (u32) col_delta;
            } else {
                *col_ptr = 0;
            }
        }
    } else if (row_delta < 0) {
        if (col_delta < 0 && (u32) sp->x14 < (u32) -col_delta) {
            col_delta = 0;
        } else {
            col_delta = sp->x14 + col_delta;
        }

        if (row_delta < 0 && (u32) sp->x18 < (u32) -row_delta) {
            row_delta = 0;
        } else {
            row_delta = sp->x18 + row_delta;
        }

        hsd_80393E68(col_delta, row_delta);
    }
}

u8 hsd_80394068(void)
{
    u8 result;

    if (!hsd_804CF7E8.x0_b0) {
        return 0;
    }
    if ((u32) hsd_804CF7E8.x1C > hsd_804CF7E8.buf_size) {
        return 0;
    }
    if ((u32) hsd_804CF7E8.x14 < (u32) hsd_804CF7E8.x20) {
        result =
            hsd_804CF7E8.out_buf[(hsd_804CF7E8.x14 +
                                  (hsd_804CF7E8.xC + hsd_804CF7E8.buf_size -
                                   hsd_804CF7E8.x1C)) %
                                 hsd_804CF7E8.buf_size];
        hsd_804CF7E8.x14++;
    } else {
        result = 0;
        hsd_80393EF4(0, -1);
        hsd_804CF7E8.x14 = 0;
    }
    return result;
}

u8 hsd_80394128(s32 col, s32 row)
{
    struct ParticleConsoleState* sp = &hsd_804CF7E8;
    u8 result;

    hsd_80393E68(col, row);
    if (!(result = sp->x0_b0)) {
        result = 0;
        goto exit;
    }
    if ((u32) sp->x1C > sp->buf_size) {
        result = 0;
        goto exit;
    }
    {
        int* x14_ptr = &hsd_804CF7E8.x14;
        if ((u32) hsd_804CF7E8.x14 < (u32) hsd_804CF7E8.x20) {
            result = hsd_804CF7E8
                         .out_buf[(hsd_804CF7E8.x14 +
                                   (hsd_804CF7E8.xC + hsd_804CF7E8.buf_size -
                                    hsd_804CF7E8.x1C)) %
                                  hsd_804CF7E8.buf_size];
            *x14_ptr = hsd_804CF7E8.x14 + 1;
        } else {
            result = 0;
            hsd_80393EF4(0, -1);
            *x14_ptr = (s32) result;
        }
    }
exit:
    return result;
}

s32 hsd_803941E8(void* xfb_out_ptr, void* xfb_cur_ptr)
{
    s32* xfb_out = xfb_out_ptr;
    u32* xfb_cur = xfb_cur_ptr;
    s32 last_draw;
    u8* vi_base;
    s32 nb_xfb;
    s32 i;
    u32 buf;
    PAD_STACK(8);

    HSD_VIWaitXFBFlushNoYield();
    last_draw = HSD_VIGetXFBLastDrawDone();

    if (last_draw != -1) {
        *xfb_cur = (u32) HSD_VIData.xfb[last_draw].buffer;
    }

    vi_base = (u8*) &HSD_VIData;
    nb_xfb = HSD_VIData.nb_xfb;
    for (i = 0; i < nb_xfb; i++) {
        if (i == last_draw) {
            goto next1;
        }
        buf = *(u32*) (vi_base + 0x58);
        xfb_out[0] = buf;
        if (buf != 0) {
            break;
        }
    next1:
        vi_base += 0x60;
    }

    i++;
    vi_base = (u8*) &HSD_VIData + i * 0x60;
    for (; i < nb_xfb; i++) {
        if (i == last_draw) {
            goto next2;
        }
        buf = *(u32*) (vi_base + 0x58);
        xfb_out[1] = buf;
        if (buf != 0) {
            break;
        }
    next2:
        vi_base += 0x60;
    }

    if ((u32) xfb_out[0] == 0) {
        if (xfb_cur != NULL) {
            xfb_out[0] = (s32) *xfb_cur;
            *xfb_cur = 0;
        } else {
            return 0;
        }
    }

    if ((u32) xfb_out[1] != 0) {
        return 2;
    }
    return 1;
}
