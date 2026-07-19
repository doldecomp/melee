#include "hsd_3915.h"

#include "hsd_3915.static.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/mcc.h>
#include <dolphin/os.h>
#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/list.h>
#include <baselib/memory.h>
#include <baselib/mtx.h>
#include <baselib/perf.h>
#include <baselib/psappsrt.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>
#include <baselib/state.h>
#include <baselib/video.h>
#include <MetroTRK/ppc_reg.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

/* 4CF810 */ extern struct ParticleScreenState hsd_804CF810;

static u16 numPeakParticles;

void DrawRectangle(f32 x_min, f32 y_min, f32 w, f32 h, GXColor* color)
{
    f32 x_max;
    f32 y_max;
    GXColor c;
    u8 r, g, b, a;

    GXBegin(0x80, 0, 4);

    x_max = x_min + w;
    y_max = y_min + h;

    // Send the corners in clockwise order, starting with top left

    GXWGFifo.f32 = x_min;
    GXWGFifo.f32 = y_min;
    a = color->a;
    b = color->b;
    g = color->g;
    r = color->r;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_max;
    GXWGFifo.f32 = y_min;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_max;
    GXWGFifo.f32 = y_max;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x_min;
    GXWGFifo.f32 = y_max;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXEnd();
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
            px = (f32) ((f64) lbl_804D6070 * 0.3 + (f64) x);
            py = (f32) ((f64) lbl_804D6074 * 0.9 + (f64) y);
            GXPosition2f32(px, py);
            GXColor4u8(color->r, color->g, color->b, color->a);
            return lbl_804D6070;
        }
        case ':': {
            GXBegin(0xB8, 0, 2);
            GXPosition2f32((f32) ((f64) lbl_804D6070 * 0.3 + (f64) x),
                           (f32) ((f64) lbl_804D6074 * 0.3 + (f64) y));
            GXColor4u8(color->r, color->g, color->b, color->a);
            GXPosition2f32((f32) ((f64) lbl_804D6070 * 0.3 + (f64) x),
                           (f32) ((f64) lbl_804D6074 * 0.7 + (f64) y));
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
    while (i < 0x29 && (u8) glyph[i] != 0xFF) {
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

// @TODO: Currently 98.73% match - hexval branch condition inversion
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

void hsd_80391E18(u8* list, f32 x1, f32 y1, f32 x2, f32 y2)
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

        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;

        GXWGFifo.f32 = prev_x;
        GXWGFifo.f32 = prev_y;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
    }
}

// @TODO: Currently 88.12% match - register allocation differences remain
static inline void hsd_80391F28_calc_perp_and_begin(f32 dy, f32 dx,
                                                    f32* perp_x, f32* perp_y)
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
    *perp_x = -dy / len;
    *perp_y = -dx / len;

    GXBegin(0xA8, 0, 2);
}

static inline void hsd_80391F28_calc_tick4_y(f32 perp_y, f32* tick4_y)
{
    *tick4_y = 4.0F * perp_y;
}

void hsd_80391F28(GXColor* color, f32 x1, f32 y1, f32 x2, f32 y2, f32 count)
{
    f32 tick6_x;
    f32 dx;
    f32 dy;
    f32 perp_x;
    f32 perp_y;
    f32 tick6_y;
    f32 tick4_x;
    f32 tick4_y;
    f32 step_y;
    f32 step_x;
    f32 len;
    s32 i;
    u8 r, g, b, a;

    dy = y2 - y1;
    dx = x2 - x1;
    hsd_80391F28_calc_perp_and_begin(dy, dx, &perp_x, &perp_y);

    step_y = dy / count;
    step_x = dx / count;

    GXWGFifo.f32 = x1;
    i = 0;
    a = color->a;
    GXWGFifo.f32 = y1;

    b = color->b;
    g = color->g;
    r = color->r;

    tick6_y = 6.0F * perp_y;
    {
        f32 tmp_tick6_x = 6.0F * perp_x;
        tick6_x = tmp_tick6_x;
    }
    tick4_x = 4.0F * perp_x;
    hsd_80391F28_calc_tick4_y(perp_y, &tick4_y);

    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    GXWGFifo.f32 = x2;
    GXWGFifo.f32 = y2;
    GXWGFifo.u8 = r;
    GXWGFifo.u8 = g;
    GXWGFifo.u8 = b;
    GXWGFifo.u8 = a;

    while ((f32) i <= count) {
        GXBegin(0xA8, 0, 2);
        GXWGFifo.f32 = x1;
        GXWGFifo.f32 = y1;
        a = color->a;
        b = color->b;
        g = color->g;
        r = color->r;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        if ((i % 5) == 0) {
            GXWGFifo.f32 = x1 + tick6_x;
            GXWGFifo.f32 = y1 + tick6_y;
        } else {
            GXWGFifo.f32 = x1 + tick4_x;
            GXWGFifo.f32 = y1 + tick4_y;
        }
        a = color->a;
        b = color->b;
        g = color->g;
        r = color->r;
        x1 += step_x;
        y1 += step_y;
        i++;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
    }
}

void hsd_80392194(u8* dst, s32 flags, void* unused1, void* unused2, u8* src)
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

typedef struct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ void (*callback)(void* dst, s32 x, s32 y, s32 val, void* self);
} GlyphEntry;

extern GlyphEntry lbl_80408898[4];

// @TODO: Currently 72.88% match - needs register allocation fixes
void hsd_803921B8(void* bitmap, s32 x, s32 y, s32 dst, s32 w, s32 h,
                  s32 stride, void* tbl)
{
    volatile s32 v_stride;
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

    v_stride = stride;
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
        cur_dst = dst + (y * v_stride) + x2;
        while ((u32) col < max_x) {
            word =
                *(u32*) (bmp + data_off + (((u32) bit_x >> 2) & 0x3FFFFFFC));
            shift = cur_dst;
            bit_off = bit_x & 0xF;
            while (bit_off < 16 && (u32) col < max_x) {
                val = (word >> ((15 - bit_off) * 2)) & 3;
                entry = &table[val];
                entry->callback((void*) shift, col, y, val, entry);
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

// @TODO: Currently 85% match - needs register allocation fixes
void hsd_803922FC(void* bitmap, s32 x, s32 y, s32 parity, s32 dst, s32 w,
                  s32 h, s32 stride, void* tbl)
{
    volatile s32 v_stride;
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
    v_stride = stride;
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
        cur_dst = dst + (row_idx * v_stride) + x2;
        while ((u32) col < max_x) {
            word =
                *(u32*) (bmp + data_off + (((u32) bit_x >> 2) & 0x3FFFFFFC));
            shift = cur_dst;
            bit_off = bit_x & 0xF;
            while (bit_off < 16 && (u32) col < max_x) {
                val = (word >> ((15 - bit_off) * 2)) & 3;
                entry = &((GlyphEntry*) tbl)[val];
                entry->callback((void*) shift, col, y, val, entry);
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

void hsd_80392474(void)
{
    hsd_804D7850 = NULL;
}

struct EventPriority {
    Event event;
    int priority;
};

HSD_SList* fn_80392480(Event event, int priority)
{
    HSD_SList* prev = NULL;
    HSD_SList* cur = hsd_804D7850;

    goto loop_5;
block_1: {
    HSD_SList* ret = cur->data;
    if (event != (Event) ret->next) {
        if (((struct EventPriority*) ret)->priority <= priority) {
            prev = cur;
        }
        cur = cur->next;
    loop_5:
        if (cur != NULL) {
            goto block_1;
        }
        {
            struct EventPriority* data = HSD_MemAlloc(8);
            data->event = event;
            data->priority = priority;
            if (prev != NULL) {
                return HSD_SListAllocAndAppend(prev, data);
            }
            ret = HSD_SListAllocAndPrepend(hsd_804D7850, data);
        }
        hsd_804D7850 = ret;
    }
    return ret;
}
}

#pragma push
#pragma dont_inline on
void hsd_80392528(Event event)
{
    fn_80392480(event, 0x80);
}
#pragma pop

static u32 lbl_804D6084;
static const u32 lbl_804DE8E0 = 0xFFFFFFFF;

typedef struct {
    s32 count;
    u32 color;
} DispBar;

typedef struct _DispItem {
    /* 0x00 */ struct _DispItem* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        char text[128];
        DispBar bars[1];
        u8 gradient[8];
    } content;
} DispItem;

typedef DispItem* (*DispCallback)(void*);

// @TODO: Currently 89.78% match - needs minor control flow and register fixes
void hsd_8039254C(void)
{
    static GXColor lbl_804D6080 = { 0x40, 0x40, 0x40 };
    f32 line;
    f32 bar_y;
    f32 bar_x;
    f32 t2;
    GXColor default_col;
    GXColor bg_col0;
    GXColor bg_col1;
    GXColor txt_col;
    GXColor bg_col2;
    GXColor bg_col3;
    GXColor bar_col;
    s32 char_count;
    s32 count;
    GXColor* p_bg_col0;
    GXColor* p_bg_col1;
    GXColor* p_txt_col;
    GXColor* p_bg_col2;
    GXColor* p_bg_col3;
    GXColor* p_bar_col;
    s32 col_pos;
    s32 first;
    HSD_SList* event_node;

    p_bar_col = &bar_col;
    p_bg_col3 = &bg_col3;
    p_bg_col2 = &bg_col2;
    p_bg_col1 = &bg_col1;
    p_txt_col = &txt_col;
    p_bg_col0 = &bg_col0;
    col_pos = 60;
    first = 1;
    line = 1.0F;
    event_node = (HSD_SList*) hsd_804D7850;
    default_col = *(GXColor*) &lbl_804DE8E0;

    while (event_node != NULL) {
        DispItem* item;
        DispCallback cb;
        cb = (DispCallback) ((void**) event_node->data)[0];
        item = cb(event_node->data);

        while (item != NULL) {
            if (first != 0) {
                if (lbl_804D6080.a != 0) {
                    hsd_80391A04(10.0F, 10.0F, 6);
                    bg_col0 = lbl_804D6080;
                    DrawRectangle(-10.0F, 5.0F, 620.0F, 10.0F, p_bg_col0);
                }
                first = 0;
            }
            switch (item->type) {
            case 0:
                if ((&item->content) == NULL) {
                    char_count = 0;
                } else {
                    char_count = 0;
                    {
                        s32 j = 0;
                        s32 len = strlen(item->content.text);
                        char_count = j;
                        while (j < len) {
                            if ((s8) item->content.text[j] != '\\') {
                                char_count++;
                            } else {
                                j++;
                                {
                                    char* tmp = item->content.text;
                                    switch ((s8) tmp[j]) {
                                    case 'c':
                                    case 'C':
                                        j += 6;
                                        break;
                                    }
                                }
                            }
                            j++;
                        }
                    }
                }
                if (col_pos + char_count > 60) {
                    line -= 1.0F;
                    col_pos = 0;
                    if (lbl_804D6080.a != 0) {
                        bg_col1 = lbl_804D6080;
                        DrawRectangle(-10.0F, (10.0F * line) - 5.0F, 620.0F,
                                      10.0F, p_bg_col1);
                    }
                }
                hsd_80391A04(10.0F, 10.0F, 6);
                txt_col = default_col;
                hsd_80391AC8(item->content.text, p_txt_col,
                             (f32) (col_pos * 10), 10.0F * line);
                col_pos = col_pos + (2 + char_count);
                break;
            case 2:
                if (col_pos != 0) {
                    line = (f32) ((f64) line - 0.5);
                    if (lbl_804D6080.a != 0) {
                        bg_col2 = lbl_804D6080;
                        DrawRectangle(-10.0F, (10.0F * line) - 5.0F, 620.0F,
                                      5.0F, p_bg_col2);
                    }
                }
                hsd_80391A04(10.0F, 10.0F, 24);
                t2 = (10.0F * line) + 2.0F;
                hsd_80391E18(item->content.gradient, 0.0F, t2, 600.0F, t2);
                col_pos = 60;
                break;
            case 1: {
                DispItem* bar_ptr;
                DispItem* bar_draw_ptr;

                bar_ptr = item;
                char_count = 0;
                {
                    while ((count = bar_ptr->content.bars[0].count) > 0) {
                        char_count += count;
                        bar_ptr = (DispItem*) ((DispBar*) bar_ptr + 1);
                    }
                }
                if (char_count > 0) {
                    if (col_pos != 0) {
                        line = (f32) ((f64) line - 0.5);
                        if (lbl_804D6080.a != 0) {
                            bg_col3 = lbl_804D6080;
                            DrawRectangle(-10.0F, (10.0F * line) - 5.0F,
                                          620.0F, 5.0F, p_bg_col3);
                        }
                    }
                    hsd_80391A04(10.0F, 10.0F, 12);
                    bar_y = (10.0F * line) + 2.0F;
                    bar_x = 0.0F;
                    {
                        bar_draw_ptr = item;
                        while ((count = bar_draw_ptr->content.bars[0].count) >
                               0)
                        {
                            f32 prev_x;
                            prev_x = bar_x;
                            bar_col =
                                *(GXColor*) &bar_draw_ptr->content.bars[0]
                                     .color;
                            bar_x += (600.0F / (f32) char_count) * (f32) count;
                            hsd_80391F28(
                                p_bar_col, prev_x, bar_y, bar_x, bar_y,
                                (f32) bar_draw_ptr->content.bars[0].count);
                            bar_draw_ptr =
                                (DispItem*) ((DispBar*) bar_draw_ptr + 1);
                        }
                    }
                    col_pos = 60;
                }
                break;
            }
            }
            item = item->next;
        }
        event_node = event_node->next;
    }
}

void fn_80392934(void)
{
    f32 cpu;
    f32 draw;
    f32 total;

    cpu = HSD_PerfLastStat.cpu_time;
    hsd_804D7858 = cpu;
    draw = HSD_PerfLastStat.draw_time;
    hsd_804D785C = draw;
    total = HSD_PerfLastStat.total_time;
    hsd_804D7860 = total;

    if (hsd_804D7864 < cpu || hsd_804D7870-- < 0) {
        hsd_804D7864 = cpu;
        hsd_804D7870 = 60;
    }
    if (hsd_804D7868 < draw || hsd_804D7874-- < 0) {
        hsd_804D7868 = draw;
        hsd_804D7874 = 60;
    }
    if (hsd_804D786C < total || hsd_804D7878-- < 0) {
        hsd_804D786C = total;
        hsd_804D7878 = 60;
    }
    if (hsd_804D787C < cpu) {
        hsd_804D787C = cpu;
    }
    if (hsd_804D7880 < draw) {
        hsd_804D7880 = draw;
    }
    if (hsd_804D7884 < total) {
        hsd_804D7884 = total;
    }
}

static s32 lbl_804D6088 = 4;
static s32 lbl_804D608C = 1;

#pragma push
#pragma dont_inline on
void fn_80392A08(int mode, int scale, int enable)
{
    lbl_804D6088 = mode;
    lbl_804D608C = scale;
    if (hsd_804D7888 == 0 && enable != 0) {
        hsd_804D787C = 0.0F;
        hsd_804D7880 = 0.0F;
        hsd_804D7884 = 0.0F;
    }
    hsd_804D7888 = enable;
}
#pragma pop

static s32 lbl_804D6090 = -1;
static s32 lbl_804D6094 = (s32) 0xFF0000FF;
static s32 lbl_804D6098 = 0x00FF00FF;
static s32 lbl_804D609C = 0x00FFFFFF;
static s32 lbl_804D60A0 = 0x8080FF;
static s32 lbl_804D60A4 = (s32) 0xC0C000FF;

// @TODO: Currently 89.63% match - needs register allocation and expression
// fixes
static inline PerfDispItem* get_perf_disp_item(s32 count)
{
    return &hsd_804CE3F8[count];
}

void* fn_80392A3C(void)
{
    volatile s32 green;
    s32 numFrames;
    s32 bar_count;
    s32 count;
    PerfDispItem* entry;
    PerfDispItem* entry2;

    count = 0;
    numFrames = lbl_804D6088;
    if (0 != numFrames) {
        u8* counts = &hsd_804CE3F8[0].content.bytes[0];
        u8* colors_base = &hsd_804CE3F8[0].content.bytes[4];
        u8* colors = colors_base;
        hsd_804CE3F8[0].type = 1;
        *(s32*) counts = 1;
        bar_count = count;
        bar_count++;
        green = lbl_804D6098;
        *(s32*) colors = green;
        if (numFrames > 1) {
            s32 val = numFrames - 1;
            if (val > 3) {
                val = 3;
            }
            *(s32*) (counts + bar_count * 8) = val;
            *(s32*) (colors + bar_count * 8) = lbl_804D60A4;
            bar_count = 2;
        }
        if (numFrames > 4) {
            *(s32*) (counts + bar_count * 8) = numFrames - 4;
            *(s32*) (colors + bar_count * 8) = lbl_804D6094;
            bar_count++;
        }
        *(s32*) (counts + bar_count * 8) = -1;
        hsd_804CE3F8[0].next = &hsd_804CE3F8[1];
        hsd_804CE3F8[1].type = 2;
        count = 4;
        hsd_804CE3F8[1].content.gradient[0].pos =
            hsd_804D7860 / (f32) numFrames;
        hsd_804CE3F8[1].content.gradient[0].color = lbl_804D609C;
        hsd_804CE3F8[1].content.gradient[1].pos =
            (f32) (s32) (0.9999F + hsd_804D7860) / (f32) numFrames;
        hsd_804CE3F8[1].content.gradient[1].color = lbl_804D60A0;
        hsd_804CE3F8[1].content.gradient[2].pos = -1.0F;
        hsd_804CE3F8[1].next = &hsd_804CE3F8[2];
        hsd_804CE3F8[2].type = 2;
        hsd_804CE3F8[2].content.gradient[0].pos =
            hsd_804D785C / (f32) numFrames;
        hsd_804CE3F8[2].content.gradient[0].color = lbl_804D6090;
        hsd_804CE3F8[2].content.gradient[1].pos = -1.0F;
        hsd_804CE3F8[2].next = &hsd_804CE3F8[3];
        hsd_804CE3F8[3].type = 2;
        hsd_804CE3F8[3].content.gradient[0].pos =
            hsd_804D7858 / (f32) numFrames;
        hsd_804CE3F8[3].content.gradient[0].color = green;
        hsd_804CE3F8[3].content.gradient[1].pos = -1.0F;
        hsd_804CE3F8[3].next = &hsd_804CE3F8[4];
    }
    if (lbl_804D608C != 0) {
        hsd_804CE3F8[count].type = 0;
        entry = get_perf_disp_item(count);
        sprintf(entry->content.text,
                "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f  "
                "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f",
                hsd_804D7858, hsd_804D785C, hsd_804D7860, hsd_804D7864,
                hsd_804D7868, hsd_804D786C);
        entry->next = &hsd_804CE3F8[count + 1];
        count++;
        if (hsd_804D7888 != 0) {
            hsd_804CE3F8[count].type = 0;
            entry2 = &hsd_804CE3F8[count];
            sprintf(entry2->content.text,
                    "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f",
                    hsd_804D787C, hsd_804D7880, hsd_804D7884);
            entry2->next = &hsd_804CE3F8[count + 1];
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    hsd_804CE3F8[count - 1].next = NULL;
    return hsd_804CE3F8;
}
