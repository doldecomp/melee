#include "hsd_3915.h"

#include <placeholder.h>

#include <math.h> // IWYU pragma: keep
#include <dolphin/gx.h>
#include <dolphin/gx/GXGeometry.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/state.h>

/* 4CF810 */ extern struct ParticleScreenState hsd_804CF810;

static u16 numPeakParticles;

void DrawRectangle(f32 x_min, f32 y_min, f32 w, f32 h, GXColor* color)
{
    f32 x_max;
    f32 y_max;

    GXBegin(0x80, 0, 4);

    x_max = x_min + w;
    y_max = y_min + h;

    // Send the corners in clockwise order, starting with top left

    GXPosition2f32(x_min, y_min);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXPosition2f32(x_max, y_min);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXPosition2f32(x_max, y_max);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXPosition2f32(x_min, y_max);
    GXColor4u8(color->r, color->g, color->b, color->a);
}

static u8 lbl_80408630[0x268] = {
    0x00, 0x60, 0x60, 0x66, 0x66, 0x06, 0x06, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x36, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x60, 0x63, 0x63, 0x03, 0x03, 0x06, 0x06, 0x66,
    0xFF, 0x00, 0x00, 0x00, 0x60, 0x60, 0x66, 0x66, 0x06, 0x13, 0x63, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x63, 0x40, 0x46, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x03, 0x03, 0x63, 0x63,
    0x66, 0x66, 0x06, 0xFF, 0x00, 0x00, 0x00, 0x06, 0x06, 0x66, 0x66, 0x63,
    0x63, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x62, 0x62,
    0x43, 0x43, 0x46, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x66,
    0x66, 0x06, 0x06, 0x00, 0x03, 0x63, 0xFF, 0x00, 0x00, 0x63, 0x03, 0x03,
    0x00, 0x00, 0x60, 0x60, 0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30,
    0x30, 0x66, 0x14, 0x54, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x40, 0x61, 0x61, 0x66, 0x66, 0x06, 0x06, 0x00, 0x03, 0x63, 0xFF,
    0x60, 0x20, 0x20, 0x03, 0x03, 0x26, 0x26, 0x66, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x30, 0x63, 0x63, 0x36, 0x36, 0x06, 0x10, 0x16, 0xFF,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x06, 0x06, 0x66, 0x03, 0x53, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x06, 0x02, 0x42, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x30, 0x02, 0x02, 0x06, 0x06, 0x66,
    0x66, 0x63, 0x63, 0x33, 0xFF, 0x00, 0x06, 0x60, 0x66, 0x03, 0x63, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x50, 0x16, 0x56, 0x30, 0x36,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x56, 0x56, 0x16, 0x16,
    0x14, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x03,
    0x03, 0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06,
    0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x33, 0x33, 0x60, 0x60, 0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x66, 0x66, 0x60, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x63, 0x63, 0x36, 0x36, 0x03, 0x03, 0x30, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x00, 0x00, 0x50, 0x50, 0x61, 0x61, 0x62, 0x62, 0x53, 0x53,
    0x03, 0xFF, 0x06, 0x02, 0x02, 0x60, 0x60, 0x64, 0x64, 0x06, 0x24, 0x46,
    0x46, 0x66, 0xFF, 0x06, 0x00, 0x00, 0x60, 0x60, 0x62, 0x62, 0x02, 0x32,
    0x66, 0xFF, 0x00, 0x00, 0x60, 0x00, 0x00, 0x66, 0x66, 0x06, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x36, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x66, 0x66, 0x60,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x36, 0x36,
    0x62, 0x62, 0x60, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x16, 0x56,
    0x56, 0x60, 0x32, 0x36, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x60,
    0x06, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32,
    0x32, 0x60, 0x32, 0x36, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x60, 0x60, 0x06, 0x06, 0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x63, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x66, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x22, 0x22, 0x44, 0x44, 0x63, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x06, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x50, 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x22, 0x22, 0x24, 0x24, 0x46, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x42, 0x42, 0x44, 0x44, 0x26,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x26, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x03, 0x03, 0x66,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x36, 0x03,
    0x63, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x01,
    0x01, 0x65, 0x65, 0x05, 0x30, 0x36, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
static float lbl_804D6070 = 12.0F;
static float lbl_804D6074 = 12.0F;

f32 DrawASCII(int chr, float x, float y, GXColor* color)
{
    s32 index;
    u8* glyph;
    s32 i;
    u8 p0, p1;
    PAD_STACK(16);

    if (chr >= '0' && chr <= '9') {
        index = chr - '0';
    } else if (chr >= 'A' && chr <= 'Z') {
        index = chr - 'A' + 10;
    } else if (chr >= 'a' && chr <= 'z') {
        index = chr - 'a' + 10;
    } else {
        switch (chr) {
        case '.': {
            f32 px;
            f32 py;
            GXBegin(0xB8, 0, 1);
            px = lbl_804D6070 * 0.3 + x;
            py = lbl_804D6074 * 0.9 + y;
            GXPosition2f32(px, py);
            GXColor4u8(color->r, color->g, color->b, color->a);
            return lbl_804D6070;
        }
        case ':': {
            GXBegin(0xB8, 0, 2);
            GXPosition2f32(lbl_804D6070 * 0.3 + x, lbl_804D6074 * 0.3 + y);
            GXColor4u8(color->r, color->g, color->b, color->a);
            GXPosition2f32(lbl_804D6070 * 0.3 + x, lbl_804D6074 * 0.7 + y);
            GXColor4u8(color->r, color->g, color->b, color->a);
            return lbl_804D6070;
        }
        case '-':
            index = 0x24;
            break;
        case '_':
            index = 0x25;
            break;
        case '~':
            index = 0x26;
            break;
        case '>':
            index = 0x27;
            break;
        case '/':
            index = 0x28;
            break;
        case '(':
            index = 0x29;
            break;
        case ')':
            index = 0x2A;
            break;
        case ',':
            index = 0x2B;
            break;
        case '<':
            index = 0x2C;
            break;
        case '+':
            index = 0x2D;
            break;
        case '$':
            index = 0x2E;
            break;
        default:
            return lbl_804D6070;
        }
    }

    glyph = &lbl_80408630[index * 13];
    i = 0;
    while (i < 0x29 && glyph[i] != 0xFF) {
        p0 = glyph[i++];
        p1 = glyph[i++];
        GXBegin(0xA8, 0, 2);
        GXPosition2f32(lbl_804D6070 * (0.11F * (p0 >> 4)) + x,
                       lbl_804D6074 * (0.11F * (p0 & 0xF)) + y);
        GXColor4u8(color->r, color->g, color->b, color->a);
        GXPosition2f32(lbl_804D6070 * (0.11F * (p1 >> 4)) + x,
                       lbl_804D6074 * (0.11F * (p1 & 0xF)) + y);
        GXColor4u8(color->r, color->g, color->b, color->a);
    }
    return lbl_804D6070;
}

static u8 lbl_804D6078 = 12;

void hsd_80391A04(float scale_x, float scale_y, int line_width)
{
    Mtx view_mtx;

    lbl_804D6070 = scale_x;
    lbl_804D6074 = scale_y;
    lbl_804D6078 = line_width;
    HSD_ClearVtxDesc();
    GXSetCurrentMtx(0);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx);
    GXLoadPosMtxImm(view_mtx, 0);
    HSD_StateSetLineWidth(lbl_804D6078, 5);
    HSD_StateSetPointSize(lbl_804D6078 * 2, 5);
    HSD_SetupRenderMode(0x68000002);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    HSD_StateSetCullMode(0);
}

static inline int hexval(int ch)
{
    if (ch < 0x47) {
        if (ch < 0x0A) {
            if (ch >= 0) {
                goto sub_30;
            }
            goto ret_zero;
        }
        if (ch >= 0x41) {
            goto sub_37;
        }
        goto ret_zero;
    }
    if (ch < 0x67) {
        if (ch >= 0x61) {
            goto sub_57;
        }
        goto ret_zero;
    }
    goto ret_zero;
sub_30:
    return ch - 0x30;
sub_57:
    return ch - 0x57;
sub_37:
    return ch - 0x37;
ret_zero:
    return 0;
}

s32 hsd_80391AC8(char* str, GXColor* color, f32 x, f32 y)
{
    GXColor col;
    GXColor* col_ptr;
    s32 i;
    u8* p;

    if (str == NULL) {
        return (s32) x;
    }
    col_ptr = &col;
    for (i = 0; (s8) str[i] != 0; i++) {
        if ((s8) str[i] != '\\') {
            *col_ptr = *color;
            x += DrawASCII((s8) str[i], x, y, col_ptr);
        } else {
            switch ((s8) str[++i]) {
            case 'c':
            case 'C':
                p = (u8*) (str + i);
                color->r = (u8) (hexval(p[2]) + hexval(p[1]) * 16);
                color->g = (u8) (hexval(p[4]) + hexval(p[3]) * 16);
                color->b = (u8) (hexval(p[6]) + hexval(p[5]) * 16);
                i += 6;
                color->a = 0xFF;
                break;
            }
        }
    }
    return (s32) x;
}

void hsd_80391E18(const u8* list, f32 x1, f32 y1, f32 x2, f32 y2)
{
    f32 dx;
    f32 dy;
    f64 t;
    f32 prev_x;
    f32 prev_y;
    u32 color;
    u8 r, g, b, a;
    PAD_STACK(8);

    if (list == NULL) {
        return;
    }

    prev_x = x1;
    prev_y = y1;
    dx = x2 - x1;
    dy = y2 - y1;

    for (;;) {
        t = *(f32*) list;
        color = *(u32*) (list + 4);
        list += 8;

        if (t < 0.0) {
            break;
        }

        GXBegin(0xA8, 0, 2);

        GXWGFifo.f32 = prev_x;
        GXWGFifo.f32 = prev_y;

        prev_x = t * dx + x1;
        prev_y = t * dy + y1;

        r = ((u8*) &color)[0];
        g = ((u8*) &color)[1];
        b = ((u8*) &color)[2];
        a = ((u8*) &color)[3];

        GXColor4u8(r, g, b, a);
        GXPosition2f32(prev_x, prev_y);
        GXColor4u8(r, g, b, a);
    }
}

/// Newton-Raphson `sqrtf`; the volatile round-trip pins the single-precision
/// result.
static inline f32 hsd_80391F28_len(f32 dy, f32 dx)
{
    f32 len;

    len = (dx * dx) + (dy * dy);
    if (len > 0.0F) {
        f64 e = __frsqrte(len);
        e = 0.5 * e * -(len * (e * e) - 3.0);
        e = 0.5 * e * -(len * (e * e) - 3.0);
        e = 0.5 * e * -(len * (e * e) - 3.0);
        e = len * e;
        {
            volatile f32 temp = (f32) e;
            len = temp;
        }
    }
    return len;
}

/// Draws a line from (x1,y1) to (x2,y2) with a tick mark every step; every
/// fifth tick is drawn longer.
void hsd_80391F28(GXColor* color, f32 x1, f32 y1, f32 x2, f32 y2, f32 count)
{
    f32 tick6_x;
    f32 tick6_y;
    f32 dy;
    f32 tick4_x;
    f32 dx;
    f32 x;
    f32 y;
    f32 perp_x;
    f32 perp_y;
    f32 tick4_y;
    f32 len;
    s32 i;

    dy = y2 - y1;
    dx = x2 - x1;

    len = hsd_80391F28_len(dy, dx);
    perp_x = -dy / len;
    perp_y = -dx / len;

    GXBegin(0xA8, 0, 2);

    tick6_y = 6.0F * perp_y;
    tick6_x = 6.0F * perp_x;
    tick4_x = 4.0F * perp_x;
    tick4_y = 4.0F * perp_y;

    GXPosition2f32(x1, y1);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXPosition2f32(x2, y2);
    GXColor4u8(color->r, color->g, color->b, color->a);

    x = x1;
    y = y1;

    for (i = 0; (f32) i <= count; i++) {
        GXBegin(0xA8, 0, 2);
        GXPosition2f32(x, y);
        GXColor4u8(color->r, color->g, color->b, color->a);
        if ((i % 5) == 0) {
            GXPosition2f32(x + tick6_x, y + tick6_y);
        } else {
            GXPosition2f32(x + tick4_x, y + tick4_y);
        }
        GXColor4u8(color->r, color->g, color->b, color->a);
        x += dx / count;
        y += dy / count;
    }
}

void hsd_80392194(u8* dst, s32 flags, s32 unused1, s32 unused2, const u8* src)
{
    u8 b;
    dst[0] = src[0];
    if (flags & 1) {
        b = src[2];
    } else {
        b = src[1];
    }
    dst[1] = b;
}

typedef void (*GlyphFn)(u8* dst, s32 flags, s32 unused1, s32 unused2,
                        const u8* src);

typedef struct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ GlyphFn callback;
} GlyphEntry;

GlyphEntry lbl_80408898[4] = {
    { 0x10808000, hsd_80392194 },
    { 0x46808000, hsd_80392194 },
    { 0x7C808000, hsd_80392194 },
    { 0xB3808000, hsd_80392194 },
};

DebugFontGlyph HSD_DebugFontAtlas[] = {
#include <sysdolphin/baselib/debug_font.inc>
};

void hsd_803921B8(void* bitmap, s32 x, s32 y, s32 dst, s32 w, s32 h,
                  s32 stride, void* tbl)
{
    s32 bit_x;
    s32 cur_dst;
    u32 max_x;
    s32 off_x;
    s32 off_y;
    GlyphEntry* table;
    s32 bit_off;
    s32 x2;
    s32 data_off;
    u32 word;
    s32 shift;
    s32 val;
    u8* bmp;
    GlyphEntry* entry;

    bmp = bitmap;
    off_y = 0;
    off_x = 0;
    if ((table = tbl) == NULL) {
        table = lbl_80408898;
    }
    if (y < 0) {
        off_y = -y;
        y = 0;
    }
    max_x = (u32) (x + 11) < w ? x + 11 : w;
    if (x < 0) {
        off_x = -x;
        x = 0;
    }
    x2 = x * 2;
    data_off = off_y * 4;
    while (off_y < 14 && (u32) y < h) {
        s32 col;
        col = x;
        bit_x = off_x;
        cur_dst = dst + (s32) ((u32) y * (u32) stride) + x2;
        while ((u32) col < max_x) {
            word =
                *(u32*) (bmp + data_off + (((u32) bit_x >> 2) & 0x3FFFFFFC));
            shift = cur_dst;
            bit_off = bit_x & 0xF;
            while (bit_off < 16 && (u32) col < max_x) {
                val = (word >> ((15 - bit_off) * 2)) & 3;
                entry = &table[val];
                entry->callback((u8*) shift, col, y, val, (const u8*) entry);
                bit_off++;
                bit_x++;
                shift += 2;
                cur_dst += 2;
                col++;
            }
        }
        off_y++;
        data_off += 4;
        y++;
    }
}

void hsd_803922FC(void* bitmap, s32 x, s32 y, s32 parity, s32 dst, s32 w,
                  s32 h, s32 stride, void* tbl)
{
    s32 bit_x;
    s32 cur_dst;
    u32 max_x;
    s32 off_x;
    s32 off_y;
    s32 bit_off;
    s32 x2;
    s32 data_off;
    s32 row_idx;
    u32 word;
    s32 shift;
    s32 val;
    u8* bmp;
    GlyphEntry* entry;

    bmp = bitmap;
    off_y = 0;
    off_x = 0;
    if (tbl == NULL) {
        tbl = lbl_80408898;
    }
    if (y < 0) {
        off_y = -y;
        y = 0;
    }
    if (y % 2 != parity) {
        y++;
        off_y++;
    }
    max_x = (u32) (x + 11) < w ? x + 11 : w;
    if (x < 0) {
        off_x = -x;
        x = 0;
    }
    row_idx = y / 2;
    x2 = x * 2;
    data_off = off_y * 4;
    while (off_y < 14 && (u32) y < h) {
        s32 col;
        col = x;
        bit_x = off_x;
        cur_dst = dst + (s32) ((u32) row_idx * (u32) stride) + x2;
        while ((u32) col < max_x) {
            word =
                *(u32*) (bmp + data_off + (((u32) bit_x >> 2) & 0x3FFFFFFC));
            shift = cur_dst;
            bit_off = bit_x & 0xF;
            while (bit_off < 16 && (u32) col < max_x) {
                val = (word >> ((15 - bit_off) * 2)) & 3;
                entry = &((GlyphEntry*) tbl)[val];
                entry->callback((u8*) shift, col, y, val, (const u8*) entry);
                bit_off++;
                bit_x++;
                shift += 2;
                cur_dst += 2;
                col++;
            }
        }
        off_y += 2;
        data_off += 8;
        row_idx++;
        y += 2;
    }
}
