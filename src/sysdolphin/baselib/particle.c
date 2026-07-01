#include "particle.h"

typedef struct {
    /* 0x00 */ void* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        u8 bytes[0x80];
        char text[0x80];
        struct {
            s32 count;
            u32 color;
        } bars[16];
        struct {
            f32 pos;
            u32 color;
        } gradient[16];
    } content;
} PerfDispItem;

static PerfDispItem hsd_804CE3F8[6];

#include "particle.static.h"

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

typedef struct {
    s32 x0;
    u32 x4;
    s32 x8;
} ParticleLogEntry;

typedef struct _ExcptNode {
    /* 0x1 */ struct _ExcptNode* next;
    /* 0x4 */ void (*callback)(struct _ExcptNode*);
} ExcptNode;

typedef struct _EventData {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ char** entries;
    /* 0x14 */ s32 index;
} EventData;

typedef struct _MCCPacket {
    /* 0x0 */ s32 x0;
    /* 0x4 */ u8 x4_b7 : 1;
    /* 0x4 */ u8 _x4_pad : 7;
    /* 0x5 */ u8 x5;
} MCCPacket;

typedef struct _ParticleFontData {
    /* 0x0000 */ u8 _pad0[0x700];
    /* 0x0700 */ u8 x700[0x38];
    /* 0x0738 */ u8 _pad738[0x230];
    /* 0x0968 */ u8 x968[0x38];
    /* 0x09A0 */ u8 _pad9A0[0x38];
    /* 0x09D8 */ u8 x9D8[0x38];
    /* 0x0A10 */ u8 _padA10[0x1110];
    /* 0x1B20 */ u8 x1B20[0x38];
} ParticleFontData;

typedef struct _DispData {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
} DispData;

typedef struct PSNode {
    /* 0x00 */ struct PSNode* child;
    /* 0x04 */ u8 _pad[4];
    /* 0x08 */ void (*callback)(struct PSNode*);
} PSNode;

typedef struct {
    /* 0x00 */ s32 x0;
    /* 0x04 */ void (*callback)(void* dst, s32 x, s32 y, s32 val, void* self);
} GlyphEntry;

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

typedef union {
    f32 f;
    u8 bytes[4];
} ParticleFloatBytes;

struct EventPriority {
    Event event;
    int priority;
};

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

// @TODO: Currently 90.59% match - needs register allocation fix
f32 DrawASCII(int chr, float x, float y, GXColor* color)
{
    s32 index;
    u8* glyph;
    u8* ptr;
    s32 i;
    u8 p0, p1;
    u8 r, g, b, a;
    PAD_STACK(48);

    if (chr >= '0' && chr <= '9') {
        index = chr - '0';
        goto draw_glyph;
    }
    if (chr >= 'A' && chr <= 'Z') {
        index = chr - 'A' + 10;
        goto draw_glyph;
    }
    if (chr >= 'a' && chr <= 'z') {
        index = chr - 'a' + 10;
        goto draw_glyph;
    }

    switch (chr) {
    case '.': {
        f32 px;
        f32 py;
        GXBegin(0xB8, 0, 1);
        px = (f32) ((f64) lbl_804D6070 * 0.3 + (f64) x);
        py = (f32) ((f64) lbl_804D6074 * 0.9 + (f64) y);
        GXWGFifo.f32 = px;
        GXWGFifo.f32 = py;
        a = color->a;
        b = color->b;
        g = color->g;
        r = color->r;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        return lbl_804D6070;
    }
    case ':': {
        f32 cx;
        GXBegin(0xB8, 0, 2);
        cx = (f32) ((f64) lbl_804D6070 * 0.3 + (f64) x);
        GXWGFifo.f32 = cx;
        GXWGFifo.f32 = (f32) ((f64) lbl_804D6074 * 0.3 + (f64) y);
        {
            u8 alpha = color->a;
            a = alpha;
        }
        r = color->r;
        g = color->g;
        b = color->b;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.f32 = cx;
        GXWGFifo.f32 = (f32) ((f64) lbl_804D6074 * 0.7 + (f64) y);
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        return lbl_804D6070;
    }
    case '-':
        index = 0x24;
        goto draw_glyph;
    case '_':
        index = 0x25;
        goto draw_glyph;
    case '~':
        index = 0x26;
        goto draw_glyph;
    case '>':
        index = 0x27;
        goto draw_glyph;
    case '/':
        index = 0x28;
        goto draw_glyph;
    case '(':
        index = 0x29;
        goto draw_glyph;
    case ')':
        index = 0x2A;
        goto draw_glyph;
    case ',':
        index = 0x2B;
        goto draw_glyph;
    case '<':
        index = 0x2C;
        goto draw_glyph;
    case '+':
        index = 0x2D;
        goto draw_glyph;
    case '$':
        index = 0x2E;
        goto draw_glyph;
    default:
        return lbl_804D6070;
    }

draw_glyph:
    glyph = &lbl_80408630[index * 13];
    ptr = glyph;
    i = 0;
    while (i < 0x29 && (u8) ptr[0] != 0xFF) {
        p0 = glyph[i++];
        p1 = glyph[i++];
        ptr += 2;
        GXBegin(0xA8, 0, 2);
        GXWGFifo.f32 = lbl_804D6070 * (0.11F * (s32) (p0 >> 4)) + x;
        GXWGFifo.f32 = lbl_804D6074 * (0.11F * (p0 & 0xF)) + y;
        {
            u8 alpha = color->a;
            a = alpha;
        }
        b = color->b;
        g = color->g;
        r = color->r;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
        GXWGFifo.f32 = lbl_804D6070 * (0.11F * (s32) (p1 >> 4)) + x;
        GXWGFifo.f32 = lbl_804D6074 * (0.11F * (p1 & 0xF)) + y;
        GXWGFifo.u8 = r;
        GXWGFifo.u8 = g;
        GXWGFifo.u8 = b;
        GXWGFifo.u8 = a;
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
    GXWGFifo.f32 = y1;

    a = color->a;
    b = color->b;
    g = color->g;
    r = color->r;

    tick6_y = 6.0F * perp_y;
    {
        f32 tmp_tick6_x = 6.0F * perp_x;
        tick6_x = tmp_tick6_x;
    }
    tick4_x = 4.0F * perp_x;
    tick4_y = 4.0F * perp_y;

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
    s32 col;
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
    max_x = x + 11;
    if (max_x >= w) {
        max_x = w;
    }
    if (x < 0) {
        off_x = -x;
        x = 0;
    }
    x2 = x * 2;
    data_off = off_y * 4;
    while (off_y < 14 && (u32) y < h) {
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
    volatile s32 v_h;
    s32 col;
    s32 bit_off;
    s32 bit_x;
    s32 off_x;
    GlyphEntry* table;
    u32 max_x;
    s32 x2;
    s32 data_off;
    s32 row_idx;
    u32 word;
    s32 cur_dst;
    s32 shift;
    s32 val;
    u8* bmp;
    s32 off_y;
    GlyphEntry* entry;

    v_h = h;
    v_stride = stride;
    bmp = bitmap;
    table = tbl;
    off_y = 0;
    off_x = 0;
    if (table == NULL) {
        table = lbl_80408898;
    }
    if (y < 0) {
        off_y = -y;
        y = 0;
    }
    if (y % 2 != parity) {
        y++;
        off_y++;
    }
    max_x = x + 11;
    if (max_x >= w) {
        max_x = w;
    }
    if (x < 0) {
        off_x = -x;
        x = 0;
    }
    row_idx = y / 2;
    x2 = x * 2;
    data_off = off_y * 4;
    while (off_y < 14 && (u32) y < v_h) {
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
                entry = &table[val];
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

static GXColor lbl_804D6080;
static u32 lbl_804D6084;
static const u32 lbl_804DE8E0 = 0xFFFFFFFF;

// @TODO: Currently 89.78% match - needs minor control flow and register fixes
void hsd_8039254C(void)
{
    s32 col_pos;
    s32 first;
    f32 line;
    HSD_SList* event_node;
    s32 type;
    s32 char_count;
    s32 total_ticks;
    DispItem* bar_ptr;
    f32 bar_y;
    f32 bar_x;
    f32 t2;
    GXColor default_col;
    GXColor bar_col;
    GXColor bg_col3;
    GXColor bg_col2;
    GXColor bg_col1;
    GXColor txt_col;
    GXColor bg_col0;
    GXColor* p_bar_col = &bar_col;
    GXColor* p_bg_col3 = &bg_col3;
    GXColor* p_bg_col0 = &bg_col0;
    GXColor* p_bg_col1 = &bg_col1;
    GXColor* p_txt_col = &txt_col;
    GXColor* p_bg_col2 = &bg_col2;

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
            type = item->type;
            switch (type) {
            case 0:
                if ((&item->content) == NULL) {
                    char_count = 0;
                } else {
                    char_count = 0;
                    {
                        s32 len = strlen(item->content.text);
                        s32 j = 0;
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
            case 1:
                bar_ptr = item;
                total_ticks = 0;
                {
                    s32 count;
                    while ((count = bar_ptr->content.bars[0].count) > 0) {
                        total_ticks += count;
                        bar_ptr = (DispItem*) &bar_ptr->content.bars[1];
                    }
                }
                if (total_ticks > 0) {
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
                        s32 count;
                        DispItem* bar_draw_ptr = item;
                        while ((count = bar_draw_ptr->content.bars[0].count) >
                               0) {
                            f32 prev_x;
                            prev_x = bar_x;
                            bar_col =
                                *(GXColor*) &bar_draw_ptr->content.bars[0].color;
                            bar_x +=
                                (600.0F / (f32) total_ticks) * (f32) count;
                            hsd_80391F28(p_bar_col, prev_x, bar_y, bar_x,
                                         bar_y,
                                         (f32) bar_draw_ptr->content.bars[0]
                                             .count);
                            bar_draw_ptr =
                                (DispItem*) &bar_draw_ptr->content.bars[1];
                        }
                    }
                    col_pos = 60;
                }
                break;
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
        u8* colors = &hsd_804CE3F8[0].content.bytes[4];
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
        ((f32*) &hsd_804CE3F8[1].content.bytes[0])[0] =
            hsd_804D7860 / (f32) numFrames;
        ((s32*) &hsd_804CE3F8[1].content.bytes[0])[1] = lbl_804D609C;
        ((f32*) &hsd_804CE3F8[1].content.bytes[0])[2] =
            (f32) (s32) (0.9999F + hsd_804D7860) / (f32) numFrames;
        ((s32*) &hsd_804CE3F8[1].content.bytes[0])[3] = lbl_804D60A0;
        ((f32*) &hsd_804CE3F8[1].content.bytes[0])[4] = -1.0F;
        hsd_804CE3F8[1].next = &hsd_804CE3F8[2];
        hsd_804CE3F8[2].type = 2;
        ((f32*) &hsd_804CE3F8[2].content.bytes[0])[0] =
            hsd_804D785C / (f32) numFrames;
        ((s32*) &hsd_804CE3F8[2].content.bytes[0])[1] = lbl_804D6090;
        ((f32*) &hsd_804CE3F8[2].content.bytes[0])[2] = -1.0F;
        hsd_804CE3F8[2].next = &hsd_804CE3F8[3];
        hsd_804CE3F8[3].type = 2;
        ((f32*) &hsd_804CE3F8[3].content.bytes[0])[0] =
            hsd_804D7858 / (f32) numFrames;
        ((s32*) &hsd_804CE3F8[3].content.bytes[0])[1] = green;
        ((f32*) &hsd_804CE3F8[3].content.bytes[0])[2] = -1.0F;
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

s32 fn_80392CCC(s32 channel)
{
    hsd_804D7894 = channel;
    return 0;
}

u8 fn_80392CD8(char* caller)
{
    char* msg;
    u8 err;

    err = MCCGetLastError();

    switch (err) {
    case 0:
        return err;
    case 1:
        msg = "MCC is no initialize";
        break;
    case 2:
        msg = "No responce";
        break;
    case 3:
        msg = "PING error";
        break;
    case 4:
        msg = "Could not initialize HIO";
        break;
    case 5:
        msg = "Could not read HIO mailbox";
        break;
    case 6:
        msg = "Could not write HIO mailbox";
        break;
    case 7:
        msg = "Could not read HIO memory";
        break;
    case 8:
        msg = "Could not write HIO memory";
        break;
    case 9:
        msg = "Could not read HIO status";
        break;
    case 10:
        msg = "Could not flush channelInfo";
        break;
    case 11:
        msg = "Could not load channelInfo";
        break;
    case 12:
        msg = "Not enough memory block";
        break;
    case 13:
        msg = "Invalid function parameter";
        break;
    case 14:
        msg = "Invalid channel parameter";
        break;
    case 15:
        msg = "Invalid data size";
        break;
    case 16:
        msg = "Invalid offset parameter";
        break;
    case 17:
        msg = "Channel was (already) opened";
        break;
    case 18:
        msg = "Channel was (already) closed";
        break;
    case 19:
        msg = "Channel was (already) locked";
        break;
    case 20:
        msg = "Channel was (already) unlocked";
        break;
    case 21:
        msg = "Channel (read/write) busy";
        break;
    default:
        msg = "Unknown error";
        break;
    }

    if (caller != NULL) {
        OSReport("%s: MCC Error, %s (%d)\n", caller, msg, err);
    } else {
        OSReport("MCC Error, %s (%d)\n", msg, err);
    }
    return err;
}

s32 hsd_804CE728[0x106];

void fn_80392E2C(s32 event_type)
{
    s32 idx;

    if (hsd_804D7898 <= 0x100 && (u32) (event_type - 1) <= 1U) {
        idx = hsd_804D789C + hsd_804D7898;
        hsd_804CE728[idx % 256] = event_type;
        hsd_804D7898 += 1;
    }
}

ParticleLogEntry hsd_804CEB40[0x100];
extern s32 hsd_804CF740[42];

extern s32 hsd_804D78A8;
extern s32 hsd_804D78AC;
extern int hsd_804D78A0;

// @TODO: Currently 92.84% match - needs minor register allocation fix
void hsd_80392E80(void)
{
    enum MCC_CONNECT status;
    s32 event;
    s32 head;
    u32 ticksPerUnit;
    s32 startTick;
    s32 waiting;
    s32 intr;
    s32* channel_flags;
    PAD_STACK(12);

    ticksPerUnit = *(u32*) 0x800000F8 >> 2;

    for (;;) {
        intr = OSDisableInterrupts();
        if (hsd_804D7898 == 0) {
            OSRestoreInterrupts(intr);
            break;
        }

        head = hsd_804D789C + 1;
        event = hsd_804CE728[hsd_804D789C];
        hsd_804D7898 -= 1;
        hsd_804D789C = head % 256;
        OSRestoreInterrupts(intr);

        switch (event) {
        case 2:
            OSReport("Connecting...\n");
            hsd_804D78AC = 0;
            hsd_804D78A8 = 0;
            OSReport("FIO Init...");
            if (FIOInit(hsd_804D7890, 1, 10) == 0) {
                OSReport("NG\n");
            } else {
                OSReport("OK\n");
                hsd_804D78A0 = 1;
            }
            OSReport("MCC Open...");
            if (MCCOpen(0xF, 1, (MCC_CBEvent) fn_803932D0) == 0) {
                OSReport("NG\n");
                OSReport("Reseting...\n");
                FIOExit();
                hsd_804D78A0 = 0;
                MCCExit();
                if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) ==
                    0)
                {
                    OSReport("MCCInit Failed.\n");
                }
            } else {
                OSReport("Waiting for connection...");
                waiting = 1;
                startTick = OSGetTick();
                for (;;) {
                    if (MCCGetConnectionStatus(0xF, &status) != 0 &&
                        status == 3)
                    {
                        waiting = 0;
                    } else if ((u32) ((u32) (OSGetTick() - startTick) /
                                      ticksPerUnit) < 3U)
                    {
                        continue;
                    }
                    break;
                }
                if (waiting != 0) {
                    OSReport("NG\n");
                    OSReport("Reseting...\n");
                    FIOExit();
                    hsd_804D78A0 = 0;
                    MCCExit();
                    if (MCCInit(hsd_804D7890, 0,
                                (MCC_CBSysEvent) fn_80392E2C) == 0)
                    {
                        OSReport("MCCInit Failed.\n");
                    }
                } else {
                    OSReport("OK\n");
                    channel_flags = (s32*) hsd_804CF740;
                    channel_flags[0] = 0;
                    channel_flags[1] = 0;
                    channel_flags[2] = 0;
                    channel_flags[3] = 0;
                    channel_flags[4] = 0;
                    channel_flags[5] = 0;
                    channel_flags[6] = 0;
                    channel_flags[7] = 0;
                    channel_flags[8] = 0;
                    channel_flags[9] = 0;
                    channel_flags[10] = 0;
                    channel_flags[11] = 0;
                    channel_flags[12] = 0;
                    channel_flags[13] = 0;
                    channel_flags[14] = 0;
                    channel_flags[15] = 0;
                    channel_flags[0] = 1;
                    channel_flags[8] = 1;
                    channel_flags[15] = 1;
                }
            }
            break;
        case 1:
            OSReport("Disconnecting...\n");
            if (hsd_80393328() == 0) {
                OSReport("Disconnection failed.\n");
                OSReport("Reseting...\n");
                FIOExit();
                hsd_804D78A0 = 0;
                MCCExit();
                if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) ==
                    0)
                {
                    OSReport("MCCInit Failed.\n");
                }
            } else {
                OSReport("Disconnection OK.\n");
            }
            break;
        }
    }
    hsd_80393844();
}

bool hsd_803931A4(s32 exi_channel)
{
    s32 channel;
    s32* channel_flags;
    PAD_STACK(16);

    channel_flags = (s32*) hsd_804CF740;
    channel_flags[0] = 0;
    channel_flags[1] = 0;
    channel_flags[2] = 0;
    channel_flags[3] = 0;
    channel_flags[4] = 0;
    channel_flags[5] = 0;
    channel_flags[6] = 0;
    channel_flags[7] = 0;
    channel_flags[8] = 0;
    channel_flags[9] = 0;
    channel_flags[10] = 0;
    channel_flags[11] = 0;
    channel_flags[12] = 0;
    channel_flags[13] = 0;
    channel_flags[14] = 0;
    channel_flags[15] = 0;
    channel_flags[0] = 1;
    channel_flags[8] = 1;
    channel_flags[15] = 1;

    channel = exi_channel;

    if (channel < 0) {
        hsd_804D7894 = -1;
        MCCEnumDevices((MCC_CBEnumDevices) fn_80392CCC);
        channel = hsd_804D7894;
        if ((s32) hsd_804D7894 < 0) {
            channel = 0;
        }
    }

    hsd_804D7890 = channel;
    hsd_80393A54(1);
    hsd_804D78A0 = 0;
    hsd_804D7898 = 0;
    hsd_804D789C = 0;
    hsd_804D78BC = 0;
    hsd_804D78B8 = 0;

    if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) == 0) {
        OSReport("EXI_%d:not support USB (Error=%d)\n", channel,
                 MCCGetLastError());
        return 0;
    }

    OSReport("EXI initialized (EXI_%d)\n", channel);
    return 1;
}

s32 hsd_804CF740[42];

void fn_803932D0(s32 type, u32 flags, s32 value)
{
    s32 count = hsd_804D78BC;
    ParticleLogEntry* base = hsd_804CEB40;
    s32 idx;
    ParticleLogEntry* entry;

    if (count <= 0x100 && flags == 0x100U) {
        idx = (hsd_804D78B8 + count) % 256;
        *(s32*) ((u8*) base + idx * (s32) sizeof(ParticleLogEntry)) = type;
        entry = &base[idx];
        entry->x4 = flags;
        entry->x8 = value;
        hsd_804D78BC += 1;
    }
}

s32 hsd_80393328(void)
{
    u32 ticksPerUnit;
    s32 startTick;
    s32 result;
    u8 err;

    if (hsd_804D78B4 != 0) {
        return 0;
    }
    hsd_804D78B4 = 1;
    hsd_804D78B0 = HSD_Rand() % 255;
    if (MCCNotify(0xF, hsd_804D78B0 + 256) == 0) {
        err = MCCGetLastError();
        OSReport("Error(0x%x) in MCCNotify.\n", err);
    }
    result = 1;
    startTick = OSGetTick();
    ticksPerUnit = (*(u32*) 0x800000F8 >> 2) & 0xFFFFFFFFFFFFFFFF;
    do {
        hsd_80392E80();
        if (hsd_804D78B0 == 0) {
            result = 0;
            break;
        }
    } while ((u32) (OSGetTick() - startTick) / ticksPerUnit < 3);

    if (result != 0) {
        hsd_804D78B4 = 0;
        return 0;
    }
    hsd_804D78B4 = 0;
    return 1;
}

static void (*lbl_8040A93C[32])(void*, void*) = {
    (void (*)(void*, void*)) hsd_80393440,
    (void (*)(void*, void*)) hsd_80393840,
};

// @TODO: Currently 90.11% match - needs register allocation fix
void hsd_80393440(void* request, void* response)
{
    u16 cmd;
    s32 channel_mask;
    s32 streaming;
    s32 num_blocks;
    s32 channel;
    s32 i;
    u8 free_blocks;
    u8 err;

    cmd = ((u16*) request)[3];
    channel_mask = cmd & 0xFF00;

    switch (channel_mask) {
    case 0x100:
        if (cmd & 0x80) {
            streaming = 1;
        } else {
            streaming = 0;
        }
        num_blocks = cmd & 0xF;
        for (channel = 2; channel < 16; channel++) {
            if (hsd_804CF740[channel] == 0) {
                break;
            }
        }

        if (channel == 16) {
            ((u16*) response)[3] = (u16) 0x8001;
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }

        free_blocks = MCCGetFreeBlocks(1);
        if (free_blocks == 0) {
            err = MCCGetLastError();
            if (err != 0) {
                OSReport("MCCError: %d\n", err);
            }
        }

        if (num_blocks > (s32) free_blocks) {
            ((u16*) response)[3] = (u16) (free_blocks + 0x8010);
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }

        hsd_804CF740[channel] = 1;
        ((u16*) response)[3] = channel;
        MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
        if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
            err = MCCGetLastError();
            OSReport("Error(0x%x) in MCCNotify.\n", err);
        }
        hsd_804D78AC = (hsd_804D78AC + 1) % 128;
        if (streaming != 0) {
            MCCStreamOpen(channel, num_blocks);
        } else {
            MCCOpen(channel, num_blocks, 0);
        }
        return;

    case 0x200:
        i = cmd & 0xF;
        if (hsd_804CF740[i] != 1) {
            ((u16*) response)[3] = (u16) 0x8002;
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }
        ((u16*) response)[3] = 0;
        MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
        if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
            err = MCCGetLastError();
            OSReport("Error(0x%x) in MCCNotify.\n", err);
        }
        hsd_804D78AC = (hsd_804D78AC + 1) % 128;
        hsd_804CF740[i] = 0;
        MCCClose(i);
        return;
    }
}

void hsd_80393840(void) {}

// @TODO: Currently 99.29% match - stack frame/register allocation differences
// remain
void hsd_80393844(void)
{
    ParticleLogEntry* base = hsd_804CEB40;
    u8* resp_status = (u8*) (base + 0x100) + 0x44;
    u8* req_status = (u8*) (base + 0x100) + 0x84;
    s32 type;
    u32 flags;
    s32 value;
    BOOL irq;
    u8 err;

    for (;;) {
        irq = OSDisableInterrupts();
        if (hsd_804D78BC == 0) {
            OSRestoreInterrupts(irq);
            return;
        }

        {
            s32 idx = hsd_804D78B8;
            type = base[idx].x0;
            flags = base[idx].x4;
            value = base[idx].x8;
            hsd_804D78BC -= 1;
            hsd_804D78B8 = (idx + 1) % 256;
        }

        OSRestoreInterrupts(irq);

        if (flags != 0x100 || type != 0xF) {
            continue;
        }

        if ((value & 0xFFFFFF00) == 0x100) {
            if (MCCNotify(0xF, (u8) value | 0x200) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
        } else if ((value & 0xFFFFFF00) == 0x200) {
            if ((u32) hsd_804D78B0 == (u8) value) {
                hsd_804D78B0 = 0;
            }
        } else if ((value & 0xFFFFFF80) == 0x80) {
            memset((u8*) &base[0x10A].x8, 0, 0x20);
            hsd_804D78A8 = value & 0x7F;
            if (MCCRead(0xF, hsd_804D78A8 << 5, (u8*) &base[0x10A].x8, 0x20,
                        0) != 0 &&
                !((*req_status >> 7) & 1))
            {
                u8 cmd;
                memset((u8*) &base[0x105].x4, 0, 0x20);
                ((MCCPacket*) &base[0x105].x4)->x4_b7 = 1;
                *(s32*) &base[0x105].x4 = *(s32*) &base[0x10A].x8;
                cmd = ((u8*) &base[0x10A].x8)[5];
                if (((u8*) &base[0x105].x4)[5] = cmd, cmd < 0x20U) {
                    if (lbl_8040A93C[cmd] != NULL) {
                        lbl_8040A93C[cmd]((u8*) &base[0x10A].x8,
                                          (u8*) &base[0x105].x4);
                    }
                }
            }
        }
    }
}

bool hsd_80393A04(void)
{
    if (hsd_804D78A0 == 0) {
        return 0;
    }
    if (FIOQuery() == 0) {
        hsd_804D78A0 = 0;
        return 0;
    }
    return 1;
}

void hsd_80393A54(int level)
{
    hsd_804D78C0 = level;
}

// @TODO: Currently 95.53% match - lis hoisting, extra li r0, BSS relocation
// encoding
int hsd_80393A5C(char* filename, int data, int size)
{
    u32* data_p;
    int ready;
    u32 start;
    int fd;
    f32 written_f;
    f32 elapsed;

    if (hsd_804D78A0 == 0) {
        ready = 0;
    } else if (FIOQuery() == 0) {
        hsd_804D78A0 = ready = 0;
    } else {
        ready = 1;
    }

    if (ready == 0) {
        return -5;
    }

    if (*filename == '/') {
        filename++;
    }

    start = OSGetTick();
    fd = FIOFopen(filename, 0xA02);

    if ((u32) (fd + 0x10000) == 0xFFFF) {
        OSReport("cannot open file\n");
        return -1;
    }

    data_p = (u32*) data;
    written_f = (f32) (u32) FIOFwrite(fd, data_p, size);

    if ((f32) (s32) size != written_f) {
        OSReport("cannot save file\n");
        FIOFclose(fd);
        return (s32) written_f;
    }

    FIOFclose(fd);
    elapsed = (f32) (OSGetTick() - start) / (f32) (*(u32*) 0x800000F8 >> 2);
    OSReport("Done %s size:%d time:%f spped:%fkbps\n", filename, size, elapsed,
             8.0F * (f32) size / elapsed * (1.0F / 1024.0F));
    return size;
}

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

#pragma push
#pragma dont_inline on
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
#pragma pop

#pragma push
#pragma pool_data off
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
#pragma pop

#pragma push
#pragma dont_inline on
void hsd_80393E34(s32* col_out, s32* row_out)
{
    if (col_out != NULL) {
        *col_out = hsd_804CF7E8.x14;
    }
    if (row_out != NULL) {
        *row_out = hsd_804CF7E8.x18;
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
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
#pragma pop

#pragma push
#pragma dont_inline on
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

    pos_ptr = &sp->x1C;
    buf_size = sp->buf_size;

    if ((u32) sp->x1C >= buf_size) {
        hsd_80393E68(sp->x14 + col_delta, sp->x18 + row_delta);
        return;
    }

    out_buf = sp->out_buf;
    pos = sp->x1C;
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
            u32 col = sp->x14;
            col_delta = -col_delta;
            if (col > (u32) col_delta) {
                sp->x14 = col - (u32) col_delta;
            } else {
                sp->x14 = 0;
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
#pragma pop

#pragma push
#pragma pool_data off
#pragma dont_inline on
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
#pragma pop

#pragma push
#pragma dont_inline on
u8 hsd_80394128(s32 col, s32 row)
{
    u8 result;

    hsd_80393E68(col, row);
    if (!hsd_804CF7E8.x0_b0) {
        result = 0;
    } else if ((u32) hsd_804CF7E8.x1C > hsd_804CF7E8.buf_size) {
        result = 0;
    } else if ((u32) hsd_804CF7E8.x14 < (u32) hsd_804CF7E8.x20) {
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
#pragma pop

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

extern u8 lbl_804088B8[];

// @TODO: Currently 99.61% match - .bss.0 relocation symbol instead of
/// hsd_804CF810
void hsd_80394314(void)
{
    memset(&hsd_804CF810, 0, 0xD8);
    hsd_803941E8(&hsd_804CF810.x24, &hsd_804CF810.x2C);

    {
        s32 mode;
        if (hsd_804CF810.x28 != 0) {
            mode = 2;
        } else {
            mode = 1;
        }
        hsd_804CF810.x38 = mode;
    }

    hsd_804CF810.x34 = 0;
    hsd_804CF810.x30 = &HSD_VIData;
    hsd_804CF810.x3C = ((u16*) hsd_804CF810.x30)[2];
    hsd_804CF810.x40 = ((u16*) hsd_804CF810.x30)[4];
    hsd_804CF810.x44 = (((u16) hsd_804CF810.x3C + 15) * 2) & 0x1FFE0;
    hsd_804CF810.x48 = hsd_804CF810.x44 * hsd_804CF810.x40;
    hsd_804CF810.x4 = 0;
    hsd_804CF810.x8 = hsd_804CF810.x40;
    hsd_804CF810.x18 = 0;
    hsd_804CF810.x14 = 0;
    hsd_804CF810.x20 = (u32) (hsd_804CF810.x3C - 0x28) / 11;
    hsd_804CF810.x1C = (u32) (hsd_804CF810.x40 - 0x50) / 14;
    hsd_804CF810.x4C = lbl_804088B8;
    hsd_804CF810.x50 = 0;
    hsd_804CF810.xC4 = 0;
}

// @TODO: Currently 94.99% match - obj file has extra addi for lis/addi
/// pair resolution; linked code matches 100%
void hsd_80394434(void* text)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32* x4_ptr = (s32*) sp + 1;
    s32 x = sp->x4;
    s32 y = sp->x8;
    s32 mode = sp->x0_b7;
    s32 interlace = sp->x0_b6;
    u8* font = (u8*) sp->x4C;
    s8* ptr = text;

    while (*ptr != 0) {
        switch (*ptr) {
        case '\r':
            break;
        case '\n':
            x = *x4_ptr;
            y += 14;
            /* fallthrough */
        default:
            if (mode != 0) {
                hsd_803922FC(font + (*ptr & 0x7F) * 0x38, x, y, interlace,
                             (&sp->x24)[sp->x34], sp->x3C, sp->x40, sp->x44,
                             sp->x50);
            } else {
                hsd_803921B8(font + (*ptr & 0x7F) * 0x38, x, y,
                             (&sp->x24)[sp->x34], sp->x3C, sp->x40, sp->x44,
                             sp->x50);
            }
            x += 11;
            break;
        }
        ptr++;
    }
}

// @TODO: Currently 91.32% match - needs register allocation fix
void hsd_80394544(s32 col, s32 row, u32 num_cols, u32 num_rows, s32 x, s32 y,
                  s32 xfb_buf, s32 xfb_w, s32 xfb_h, s32 xfb_stride,
                  s32 font_data, void* color_data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 mode;
    s32 interlace;
    u32 r;
    u32 c;
    s32 cur_x;
    u8 ch;

    mode = sp->x0_b7;
    interlace = sp->x0_b6;
    r = 0;

    while (r < num_rows) {
        hsd_80393E68(col, row);
        c = 0;
        cur_x = x + 0 * 11;
        y -= 14;

        while (c < num_cols) {
            ch = hsd_80394068();
            if (ch == 0) {
                break;
            }
            if (mode != 0) {
                hsd_803922FC((void*) (font_data + (ch & 0x7F) * 0x38), cur_x,
                             y, interlace, xfb_buf, xfb_w, xfb_stride, xfb_h,
                             color_data);
            } else {
                hsd_803921B8((void*) (font_data + (ch & 0x7F) * 0x38), cur_x,
                             y, xfb_buf, xfb_w, xfb_stride, xfb_h, color_data);
            }
            cur_x += 11;
            c++;
        }
        row++;
        r++;
    }
}

extern u8 lbl_8040AB40[];

// @TODO: Currently 88.35% match - register allocation/loop counter
// differences remain
#pragma push
#pragma global_optimizer off
void hsd_80394668(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    PAD_STACK(24);

    if ((u32) sp->x2C != 0) {
        /* Copy XFB data with brightness adjustment */
        u8* src = (u8*) sp->x2C;
        u32 size = sp->x48;
        u32 count = (size + 1) >> 1;
        s32 pos = 0;
        s32* dst_base = (s32*) sp + sp->x34;
        u8* dst = 0;
        dst += dst_base[9];

        if (size > 0) {
            while (count != 0) {
                u8* s1 = src + pos;
                u8* d1 = dst + pos;
                pos += 2;
                d1[0] = (u8) (((s1[0] - 0x10) & 0xFFFFFF) + 0x10);
                d1[1] = s1[1];
                count--;
            }
        }
    } else {
        /* Draw console text to framebuffer */
        void* saved_color;
        s32 row;
        s32* x4_ptr = &sp->x4;
        void** x50_ptr = &sp->x50;
        s32* x40_ptr = &sp->x40;
        s32* x8_ptr = &sp->x8;

        saved_color = *x50_ptr;
        *x50_ptr = lbl_8040AB40;
        row = 0;

        while (row <= sp->x1C) {
            s32 y_off;
            s32 cur_x;
            s32 col;
            y_off = (row + 1) * 14;
            col = 0;
            cur_x = 0x14;

            while (col < sp->x20) {
                *x4_ptr = cur_x;
                *x8_ptr = (*x40_ptr - 0x28) - y_off;
                {
                    s32 interlace = sp->x0_b6;
                    if (sp->x0_b7 != 0) {
                        hsd_803922FC(((ParticleFontData*) sp->x4C)->x700,
                                     *x4_ptr, *x8_ptr, interlace,
                                     (&sp->x24)[sp->x34], sp->x3C, *x40_ptr,
                                     sp->x44, *x50_ptr);
                    } else {
                        hsd_803921B8(((ParticleFontData*) sp->x4C)->x700,
                                     *x4_ptr, *x8_ptr, (&sp->x24)[sp->x34],
                                     sp->x3C, *x40_ptr, sp->x44, *x50_ptr);
                    }
                }
                cur_x += 11;
                col++;
            }
            row++;
        }
        *x50_ptr = saved_color;
    }
}
#pragma pop

// @TODO: Currently 96.16% match - register swap in second loop (r29/r30)
void hsd_80394950(OSContext* ctx)
{
    OSContext tmp;
    OSContext* saved;
    BOOL irq;
    s32 i;
    u8* p;

    if (!(ctx->state & OS_CONTEXT_STATE_FPSAVED)) {
        return;
    }

    irq = OSDisableInterrupts();
    saved = OSGetCurrentContext();
    OSClearContext(&tmp);
    OSSetCurrentContext(&tmp);

    OSReport("- FPR -----------------------------------------------\n");

    i = 0;
    p = (u8*) ctx;
    do {
        f64 fval = *(f64*) (p + 0x90);
        OSReport("R%02d=%08X:%08X (%e)\n", i, *(u32*) (p + 0x90),
                 *(u32*) (p + 0x94), fval);
        i++;
        p += 8;
    } while (i < 32);

    OSReport("- PSF -----------------------------------------------\n");

    i = 0;
    p = (u8*) ctx;
    do {
        OSReport("R%02d=%08X:%08X (%e, %e)\n", i, ((u32*) p)[0x24],
                 ((u32*) p)[0x25], ((f32*) p)[0x24], ((f32*) p)[0x25]);
        i++;
        p += 8;
    } while (i < 32);

    OSClearContext(&tmp);
    OSSetCurrentContext(saved);
    OSRestoreInterrupts(irq);
}

// @TODO: Currently 99.94% match - minor relocation difference
void Exception_ReportStackTrace(OSContext* ctx, int max_depth)
{
    u32 i;
    u32* sp;

    OSReport("- STACK ---------------------------------\n");
    OSReport(" Address:  Back Chain  LR Save\n");

    sp = (u32*) ctx->gpr[1];
    i = 0;

    while (sp != NULL && (u32) (sp + 0x4000) != 0xFFFF && i < (u32) max_depth)
    {
        if ((u32) sp < 0x80000000u) {
            break;
        }
        if ((s64) (u32) sp >= (s64) OSGetPhysicalMemSize() + 0x800000000) {
            break;
        }
        OSReport("%08X:   %08X   %08X\n", sp, sp[0], sp[1]);
        sp = (u32*) sp[0];
        i++;
    }
}

// @TODO: Currently 99.81% match - instructions match, string relocations
// differ
void Exception_ReportCodeline(u16 error, int dsisr, int dar, OSContext* ctx)
{
    char* exception_type;
    char* around_or_at;
    int srr1;

    OSReport("- UNHANDLED EXCEPTION -------------------------------\n");
    OSReport("DSISR=%08X DAR=%08X\n", dsisr, dar);
    error = (u16) error;
    OSReport("ERROR %d: ", error);

    switch (error) {
    case 0:
        OSReport("(SYSTEM RESET)\n");
        return;
    case 1:
        OSReport("(MACHINE CHECK)\n");
        return;
    case 2:
        OSReport("(DSI)\n");
        OSReport("Instruction at %08X (read from SRR0) attempted\n"
                 "to access invalid address %08X (read from DAR)\n",
                 ctx->srr0, dar);
        if (dsisr & 0x02000000) {
            OSReport("Store operation.\n");
        } else {
            OSReport("Load operation.\n");
        }
        if (dsisr & 0x40000000) {
            OSReport("No appropriate page entry or DBAT exist.\n");
        }
        if (dsisr & 0x08000000) {
            OSReport("Memory access is not permitted by the page or DBAT.\n");
        }
        if (dsisr & 0x400000) {
            OSReport("DABR match occurs.\n");
        }
        return;
    case 3:
        OSReport("(ISI)\n");
        OSReport("Attempted to fetch instruction from invalid address\n"
                 "%08X (read from SRR0)\n",
                 ctx->srr0);
        if (ctx->srr1 & 0x40000000) {
            OSReport("No appropriate page entry or IBAT exist.\n");
        }
        if (ctx->srr1 & 0x10000000) {
            OSReport("Illegal address.\n");
        }
        if (ctx->srr1 & 0x08000000) {
            OSReport("Memory access is not permitted by the page or IBAT.\n");
        }
        break;
    case 4:
        OSReport("(EXTERNAL INTERRUPT)\n");
        return;
    case 5:
        OSReport("(ALIGNMNET)\n");
        OSReport("Instruction at %08X (read from SRR0) attempted\n"
                 "to access unaligned address %08X (read from DAR)\n",
                 ctx->srr0, dar);
        return;
    case 6:
        OSReport("(PROGRAM)\n");
        srr1 = ctx->srr1;
        around_or_at = (srr1 & 0x10000) ? "around" : "at";
        if (srr1 & 0x100000) {
            exception_type = "IEEE floating point enabled program exception";
        } else if (srr1 & 0x80000) {
            exception_type = "Illegal instruction";
        } else if (srr1 & 0x40000) {
            exception_type = "Privileged instruction";
        } else if (srr1 & 0x20000) {
            exception_type = "Trap program exception";
        } else {
            exception_type = "Unknown type of program exception";
        }
        OSReport("%s %s %08X (read from SRR0)\n", exception_type, around_or_at,
                 ctx->srr0);
        return;
    case 7:
        OSReport("(FLOATING POINT)\n");
        return;
    case 8:
        OSReport("(DECREMENTER)\n");
        return;
    case 9:
        OSReport("(SYSTEM CALL)\n");
        return;
    case 10:
        OSReport("(TRACE)\n");
        return;
    case 11:
        OSReport("(PERFORMANCE MONITOR)\n");
        return;
    case 12:
        OSReport("(BREAKPOINT)\n");
        return;
    case 13:
        OSReport("(SYSTEM INTERRPUT)\n");
        return;
    case 14:
        OSReport("(THERMAL INTERRPUT)\n");
        return;
    default:
        OSReport("(UNKNOWN)\n");
        break;
    }
}

// @TODO: Currently 97.87% match - lwz r0 + mr r4 instead of lwz r4
void fn_80394DF4(void* node_ptr)
{
    ExcptNode* node = node_ptr;
    ExcptNode* prev;
    ExcptNode* head;

    if (node == NULL) {
        return;
    }
    head = (ExcptNode*) hsd_804CF810.xD0;
    if (head == NULL) {
        return;
    }
    if (head == node) {
        hsd_804CF810.xD0 = head->next;
        node->next = NULL;
        hsd_804CF810.x0_b5 = 1;
        return;
    }
    prev = head;
    while (prev != NULL) {
        if (prev->next == node) {
            prev->next = node->next;
            node->next = NULL;
            hsd_804CF810.x0_b5 = 1;
            return;
        }
        prev = prev->next;
    }
}

void hsd_80394E8C(void* node_ptr)
{
    void** head;
    ExcptNode* node = node_ptr;

    if (hsd_804D78C8 < 1) {
        return;
    }
    head = (void**) &hsd_804CF810.xD0;
    if (*head == node_ptr) {
        return;
    }
    if (*head == NULL) {
        *head = node_ptr;
        node->next = NULL;
    } else {
        fn_80394DF4(node_ptr);
        node->next = ((ExcptNode*) *head)->next;
        ((ExcptNode*) *head)->next = NULL;
        *head = node_ptr;
    }
    if (node->callback != NULL) {
        node->callback(node);
    }
    hsd_804CF810.x0_b5 = 1;
}

extern u8 lbl_8040AB00[];
extern u8 lbl_8040AB20[];

// @TODO: Currently 94.46% match - BSS relocation and register allocation
// differences remain
void hsd_80394F48(void* data)
{
    u8* base_color = lbl_8040AB00;
    struct ParticleScreenState* sp = &hsd_804CF810;
    EventData* dp = data;
    s32 num_entries;
    void** px50;
    s32* pxC8;
    s32* pxCC;
    s32* px4;
    s32* px40;
    s32* px8;
    s32 col_start;
    s32 row_start;
    void* hi_color;
    s32 x_base;
    s32 entry_idx;
    s32 cur_row;
    s32 i;
    s32 b6;

    PAD_STACK(64);

    num_entries = strlen(dp->entries[0]);
    px50 = &sp->x50;
    pxC8 = &sp->xC8;
    pxCC = &sp->xCC;
    px4 = &sp->x4;
    px40 = &sp->x40;
    px8 = &sp->x8;
    *px50 = base_color;
    col_start = *pxC8;
    row_start = *pxCC;

    *px4 = col_start * 11 + 0x14;
    *px8 = (*px40 - 0x28) - (row_start + 1) * 14;

    b6 = sp->x0_b6;
    if (sp->x0_b7 != 0) {
        hsd_803922FC(((ParticleFontData*) sp->x4C)->x968, *px4, *px8, b6,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    } else {
        hsd_803921B8(((ParticleFontData*) sp->x4C)->x968, *px4, *px8,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    }

    i = 0;
    *px4 += 11;
    while (i < num_entries) {
        b6 = sp->x0_b6;
        if (sp->x0_b7 != 0) {
            hsd_803922FC(((ParticleFontData*) sp->x4C)->x9D8, *px4, *px8, b6,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        } else {
            hsd_803921B8(((ParticleFontData*) sp->x4C)->x9D8, *px4, *px8,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        }
        i++;
        *px4 += 11;
    }

    b6 = sp->x0_b6;
    if (sp->x0_b7 != 0) {
        hsd_803922FC(((ParticleFontData*) sp->x4C)->x968, *px4, *px8, b6,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    } else {
        hsd_803921B8(((ParticleFontData*) sp->x4C)->x968, *px4, *px8,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    }

    *px4 += 11;
    entry_idx = 0;
    x_base = col_start * 11 + 0x14;
    hi_color = base_color + 0x20;
    cur_row = row_start - 1;

    while (dp->entries[entry_idx] != 0) {
        *px4 = x_base;
        *px8 = (*px40 - 0x28) - (cur_row + 1) * 14;
        cur_row--;

        b6 = sp->x0_b6;
        if (sp->x0_b7 != 0) {
            hsd_803922FC(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8, b6,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        } else {
            hsd_803921B8(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        }

        if (entry_idx == dp->index) {
            *px50 = hi_color;
        } else {
            *px50 = base_color;
        }

        *px4 += 11;
        hsd_80394434(dp->entries[entry_idx]);

        *px4 += strlen(dp->entries[entry_idx]) * 11;
        *px50 = base_color;

        b6 = sp->x0_b6;
        if (sp->x0_b7 != 0) {
            hsd_803922FC(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8, b6,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        } else {
            hsd_803921B8(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        }
        entry_idx++;
    }

    *px50 = base_color;
    *px4 = x_base;
    *px8 = (*px40 - 0x28) - (cur_row + 1) * 14;

    b6 = sp->x0_b6;
    if (sp->x0_b7 != 0) {
        hsd_803922FC(((ParticleFontData*) sp->x4C)->x968, *px4, *px8, b6,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    } else {
        hsd_803921B8(((ParticleFontData*) sp->x4C)->x968, *px4, *px8,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    }

    {
        s32 j = 0;
        *px4 += 11;
        while (j < num_entries) {
            b6 = sp->x0_b6;
            if (sp->x0_b7 != 0) {
                hsd_803922FC(((ParticleFontData*) sp->x4C)->x9D8, *px4, *px8,
                             b6, (&sp->x24)[sp->x34], sp->x3C, *px40,
                             sp->x44, *px50);
            } else {
                hsd_803921B8(((ParticleFontData*) sp->x4C)->x9D8, *px4, *px8,
                             (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44,
                             *px50);
            }
            j++;
            *px4 += 11;
        }
    }

    b6 = sp->x0_b6;
    if (sp->x0_b7 != 0) {
        hsd_803922FC(((ParticleFontData*) sp->x4C)->x968, *px4, *px8, b6,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    } else {
        hsd_803921B8(((ParticleFontData*) sp->x4C)->x968, *px4, *px8,
                     (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
    }

    *px4 += 11;
    *pxC8 += 4;
    *pxCC -= dp->index + 1;
}

s32 hsd_80395550(void* event_ptr)
{
    EventData* data = event_ptr;
    u32 flags = hsd_804CF810.xBC;
    u32 bit = 1;

    while (bit <= flags) {
        switch (flags & bit) {
        case 0x8: {
            s32 counter = data->index;
            if (counter > 0) {
                data->index = counter - 1;
            } else {
                char** base = data->entries;
                s32 count = 0;
                while (base[count + 1] != 0) {
                    count++;
                }
                data->index = count;
            }
            return 1;
        }
        case 0x4: {
            s32 idx = data->index;
            char** base = data->entries;
            if (base[idx + 1] != 0) {
                data->index = idx + 1;
            } else {
                data->index = 0;
            }
            return 1;
        }
        case 0x100:
            return 2;
        case 0x200:
        case 0x1000:
            return -1;
        default:
            bit <<= 1;
            break;
        }
    }
    return 0;
}

extern u8 lbl_8040AB20[];
extern u8 lbl_8040B8AC[];
extern u8 lbl_8040B904[];

void hsd_80395644(void)
{
    struct ParticleScreenState* sp =
        (struct ParticleScreenState*) &hsd_804CF810;
    void* saved;
    void** p = &sp->x50;
    s32 val_x20;
    s32 val_x1C;

    PAD_STACK(16);
    saved = *p;
    *p = lbl_8040AB20;
    val_x20 = sp->x20;
    val_x1C = sp->x1C;
    sp->x4 = (val_x20 - 21) * 11 + 20;
    sp->x8 = (sp->x40 - 40) - (val_x1C + 1) * 14;
    if (hsd_804D78C8 >= 1) {
        hsd_80394434(lbl_8040B8AC);
    }
    *p = saved;
}

s32 hsd_803956D8(void* disp_ptr)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    DispData* data = disp_ptr;
    s32 val;

    if (sp->xBC & 0x1000) {
        hsd_80394E8C(lbl_8040B904);
        sp->x14 = 0;
        data->x10 = 0;
        return 1;
    }

    val = data->x10;
    if (val < 120) {
        data->x10 = val + 1;
    } else {
        data->x10 = 0;
        {
            s32* pp = &sp->x14;
            *pp += sp->x1C;
            if (!(u8) hsd_80394128(0, *pp)) {
                if (!(u8) hsd_80394128(0, *pp + 1)) {
                    *pp = 0;
                    hsd_80394E8C(lbl_8040B904);
                }
            }
        }
        return 1;
    }
    return 0;
}

// @TODO: BSS relocation and register allocation differences remain
void hsd_803957C0(u8 input)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32* x10_ptr = &sp->x10;
    s32* x4_ptr;
    s32* x8_ptr;
    s32* x40_ptr;
    void** x50_ptr;
    s32 col;
    s32 row;
    s32 b6;
    u8 ch;
    void* saved;
    s32 saved_ch;
    PAD_STACK(24);

    ch = input;
    saved_ch = input;
    col = sp->x0C + sp->x18;
    row = *x10_ptr + sp->x14;

    while (col >= 0) {
        ch = (u8) hsd_80394128(col, row);
        if (ch != 0) {
            break;
        }
        col--;
    }

    if (ch == 0) {
        if (col < 0) {
            col = 0;
        }
        ch = ' ';
    }

    saved = sp->x50;
    sp->x50 = lbl_8040AB20;
    sp->x8 = (sp->x40 - 40) - (*x10_ptr + 1) * 14;
    sp->x4 = col * 11 + 20;

    x50_ptr = &sp->x50;
    {
        struct ParticleScreenState* draw_sp = &hsd_804CF810;
        x4_ptr = &draw_sp->x4;
        x40_ptr = &draw_sp->x40;
        x8_ptr = &draw_sp->x8;
        b6 = draw_sp->x0_b6;

        if (draw_sp->x0_b7) {
            hsd_803922FC((void*) ((u8*) draw_sp->x4C + (ch & 0x7F) * 0x38),
                         *x4_ptr, *x8_ptr, b6, (&draw_sp->x24)[draw_sp->x34],
                         draw_sp->x3C, *x40_ptr, draw_sp->x44, *x50_ptr);
        } else {
            hsd_803921B8((void*) ((u8*) draw_sp->x4C + (ch & 0x7F) * 0x38),
                         *x4_ptr, *x8_ptr, (&draw_sp->x24)[draw_sp->x34],
                         draw_sp->x3C, *x40_ptr, draw_sp->x44, *x50_ptr);
        }
    }

    if ((u32) sp->xD0 == saved_ch) {
        struct ParticleScreenState* final_sp = &hsd_804CF810;
        *x4_ptr = (final_sp->x20 - 0x27) * 11 + 20;
        *x8_ptr = (*x40_ptr - 40) - (final_sp->x1C + 1) * 14;
        hsd_80394434("<<PUSH START BUTTON TO SEE INSTRUCTION>>");
    }

    *x50_ptr = saved;
}

#pragma push
#pragma dont_inline on
s32 hsd_80395970(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 saved_x;
    s32 saved_y;
    s32 result;
    s32 i;
    u8 ch;

    result = 0;
    hsd_80393E34(&saved_x, &saved_y);
    hsd_80393E68(sp->x0C + sp->x18, sp->x10 + sp->x14);

    for (i = 0; i < 8; i++) {
        ch = hsd_80394068();
        if (ch == 0) {
            ch = hsd_80394068();
            if (ch == 0) {
                break;
            }
        }
        if (ch >= '0' && ch <= '9') {
            result = (result << 4) + ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            result = (result << 4) + ch - 'A' + 10;
        } else if (ch >= 'a' && ch <= 'f') {
            result = (result << 4) + ch - 'a' + 10;
        } else {
            break;
        }
    }

    result = (result & 0x0FFFFFF0) | (s32) 0x80000000;
    hsd_80393E68(saved_x, saved_y);
    return result;
}

#pragma pop

extern u8 lbl_8040BA5C[];

extern struct {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ u32 x10;
} lbl_8040BAF0;

extern struct {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ u32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* x18;
} lbl_8040BC3C;

s32 hsd_80395A78(void)
{
    u32 bit;
    s32 new_col;
    s32 new_scroll;
    PAD_STACK(8);

    bit = 1;
    while (bit <= hsd_804CF810.xBC) {
        switch (hsd_804CF810.xBC & bit) {
        case 0x8:
            if (hsd_804CF810.x10 < hsd_804CF810.x1C - 1) {
                hsd_804CF810.x10 = hsd_804CF810.x10 + 1;
            } else {
                hsd_804CF810.x14 += 1;
            }
            return 1;
        case 0x4:
            if (hsd_804CF810.x10 > 0) {
                hsd_804CF810.x10 -= 1;
            } else if (hsd_804CF810.x14 > 0) {
                hsd_804CF810.x14 -= 1;
            } else {
                break;
            }
            return 1;
        case 0x1:
            if (hsd_804CF810.x0C > 0) {
                hsd_804CF810.x0C -= 1;
            } else if (hsd_804CF810.x18 > 0) {
                hsd_804CF810.x18 -= 1;
            } else {
                break;
            }
            while (!(u8) hsd_80394128(hsd_804CF810.x0C + hsd_804CF810.x18,
                                      hsd_804CF810.x10 + hsd_804CF810.x14)) {
                if (hsd_804CF810.x0C > 0) {
                    hsd_804CF810.x0C -= 1;
                } else if (hsd_804CF810.x18 > 0) {
                    hsd_804CF810.x18 -= 1;
                } else {
                    break;
                }
            }
            return 1;
        case 0x2:
            new_col = hsd_804CF810.x0C;
            new_scroll = hsd_804CF810.x18;
            if ((u32) new_col < (u32) (hsd_804CF810.x20 - 1)) {
                new_col += 1;
            } else {
                new_scroll += 1;
            }
            if ((u8) hsd_80394128(new_col + new_scroll,
                                  hsd_804CF810.x10 + hsd_804CF810.x14)) {
                hsd_804CF810.x0C = new_col;
                hsd_804CF810.x18 = new_scroll;
                return 1;
            }
            break;
        case 0x100:
            lbl_8040BC3C.x10 = hsd_80395970();
            lbl_8040BC3C.x18 = &lbl_8040BAF0;
            if ((ExcptNode*) &lbl_8040BC3C != NULL) {
                fn_80394DF4((ExcptNode*) &lbl_8040BC3C);
                ((ExcptNode*) &lbl_8040BC3C)->next =
                    (ExcptNode*) hsd_804CF810.xD0;
                hsd_804CF810.xD0 = &lbl_8040BC3C;
                if (((ExcptNode*) &lbl_8040BC3C)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BC3C)
                        ->callback((ExcptNode*) &lbl_8040BC3C);
                }
                hsd_804CF810.x0_b5 = 1;
            }
            return 1;
        case 0x400:
            lbl_8040BC3C.x18 = &lbl_8040BAF0;
            if ((ExcptNode*) &lbl_8040BC3C != NULL) {
                fn_80394DF4((ExcptNode*) &lbl_8040BC3C);
                ((ExcptNode*) &lbl_8040BC3C)->next =
                    (ExcptNode*) hsd_804CF810.xD0;
                hsd_804CF810.xD0 = &lbl_8040BC3C;
                if (((ExcptNode*) &lbl_8040BC3C)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BC3C)
                        ->callback((ExcptNode*) &lbl_8040BC3C);
                }
                hsd_804CF810.x0_b5 = 1;
            }
            return 1;
        case 0x1000:
            if ((ExcptNode*) lbl_8040BA5C != NULL) {
                fn_80394DF4((ExcptNode*) lbl_8040BA5C);
                ((ExcptNode*) lbl_8040BA5C)->next =
                    (ExcptNode*) hsd_804CF810.xD0;
                hsd_804CF810.xD0 = lbl_8040BA5C;
                if (((ExcptNode*) lbl_8040BA5C)->callback != NULL) {
                    ((ExcptNode*) lbl_8040BA5C)
                        ->callback((ExcptNode*) lbl_8040BA5C);
                }
                hsd_804CF810.x0_b5 = 1;
            }
            return 1;
        default:
            break;
        }
        bit <<= 1;
    }
    return 0;
}
extern u8 lbl_8040BEC4[];

static inline void ps_remove_node(struct ParticleScreenState* sp, void* node)
{
    void** head_ptr;
    void* cur;

    if (node == NULL) {
        return;
    }
    if (*(head_ptr = &sp->xD0) == NULL) {
        return;
    }
    while ((cur = *head_ptr) != NULL && cur != node) {
        void* next = *(void**) cur;
        *(void**) cur = NULL;
        *head_ptr = next;
    }
    if (cur == node) {
        void* next = *(void**) node;
        *(void**) node = NULL;
        *head_ptr = next;
    }
    sp->x0_b5 = 1;
}

// @TODO: Currently 99.38% match - remaining register allocation differences
s32 hsd_80395D88(void* data)
{
    char* msg = (char*) lbl_8040AB00;
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 result;

    result = hsd_80395550(data);

    switch (result) {
    case 1:
        return 1;
    case 2: {
        u32 cmd = *(u32*) ((u8*) data + 0x14);
        switch (cmd) {
        case 0:
            sp->xBC = 8;
            return 0;
        case 1:
            sp->xBC = 4;
            return 0;
        case 2:
            sp->xBC = 1;
            return 0;
        case 3:
            sp->xBC = 2;
            return 0;
        case 4:
            sp->xBC = 0x100;
            goto remove_return_0;
        case 5:
            sp->xBC = 0x400;
        remove_return_0:
            ps_remove_node(sp, data);
            return 0;
        case 6: {
            s32 i;
            OSContext* ctx;
            OSContext** ctx_ptr;
            s32 saved;

            if (*(ctx_ptr = &sp->xD4) != NULL) {
                saved = hsd_80393D2C(1);
                ctx = *ctx_ptr;
                OSReport(msg + 0x728);
                i = 0;
                do {
                    OSReport(msg + 0x760, i, ctx->gpr[i], ctx->gpr[i],
                             i + 0x10, ctx->gpr[i + 0x10],
                             ctx->gpr[i + 0x10]);
                    i++;
                } while (i < 0x10);
                hsd_80394950(*ctx_ptr);
                ctx = *ctx_ptr;
                OSReport(msg + 0x828);
                OSReport(msg + 0x860, ((u32*) ctx)[0x198 / 4],
                         ((u32*) ctx)[0x19C / 4]);
                OSReport(msg + 0x878, ((u32*) ctx)[0x80 / 4],
                         ((u32*) ctx)[0x84 / 4]);
                OSReport(msg + 0x890, ((u32*) ctx)[0x88 / 4],
                         ((u32*) ctx)[0x8C / 4]);
                OSReport(msg + 0x8A8, ((u32*) ctx)[0x194 / 4]);
                i = 0;
                do {
                    OSReport(msg + 0x8B4, i, ((u32*) ctx)[i], i + 4,
                             ((u32*) ctx)[0x1B4 / 4 + i]);
                    i++;
                } while (i < 4);
                hsd_80393D2C(saved);
            }
            ps_remove_node(sp, data);
            return 1;
        }
        case 7:
            hsd_80394E8C(lbl_8040BEC4);
            return 1;
        case 8: {
            void** head_ptr;
            ExcptNode* cur;
            cur = *(head_ptr = &sp->xD0);
            while (cur != NULL) {
                ExcptNode* next = cur->next;
                cur->next = NULL;
                cur = next;
            }
            *head_ptr = NULL;
            sp->x0_b5 = 1;
            return 1;
        }
        default:
            break;
        }
        break;
    }
    case -1:
        ps_remove_node(sp, data);
        return 1;
    }
    return 0;
}

void hsd_80396130(void)
{
    u32 old = lbl_8040BC3C.x10;
    u32 memsize;

    memsize = OSGetPhysicalMemSize();
    old &= 0x0FFFFFFF;
    lbl_8040BAF0.x10 = (old + memsize) % memsize + 0x80000000;
    PAD_STACK(16);
}

static char* lbl_804D62CC = "+- MEMORY DUMP ------------------------------+";
static char* lbl_804D62D0 = "|%08X=%08X:%08X:%08X:%08X|";
static char* lbl_804D62D4 = "+--------------------------------------------+";

static inline s32 hsd_80396188_calc_col(void)
{
    return ((hsd_804CF810.x20 - 0x2E) / 2) * 11 + 20;
}

// @TODO: Currently 95.83% match - needs register allocation fix
static inline void hsd_80396188_draw_rows(char* buf, s32 col, u32** addr)
{
    s32 i;

    hsd_80394434(lbl_804D62CC);
    i = 0;
    do {
        s32 row = 4 - i;
        hsd_804CF810.x4 = col;
        hsd_804CF810.x8 = (hsd_804CF810.x40 - 0x28) - (row + 1) * 14;
        sprintf(buf, lbl_804D62D0, *addr, (*addr)[0], (*addr)[1], (*addr)[2],
                (*addr)[3]);
        hsd_80394434(buf);
        {
            u32 memsize = OSGetPhysicalMemSize();
            *addr = (u32*) ((((u32) *addr & 0x0FFFFFFF) + memsize + 0x10) %
                                memsize +
                            0x80000000);
        }
        i++;
    } while (i < 4);
    hsd_804CF810.x4 = col;
}

void hsd_80396188(void)
{
    void* saved;
    s32 col;
    u32* addr;
    char buf[64];
    PAD_STACK(20);

    addr = (u32*) lbl_8040BAF0.x10;
    saved = hsd_804CF810.x50;
    col = hsd_80396188_calc_col();
    hsd_804CF810.x50 = lbl_8040AB00;
    hsd_804CF810.x4 = col;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 0x7C;
    hsd_80396188_draw_rows(buf, col, &addr);
    hsd_804CF810.x8 = hsd_804CF810.x40 - 0x36;
    hsd_80394434(lbl_804D62D4);
    hsd_804CF810.x50 = saved;
}

extern ExcptNode lbl_8040BBE8[];

static char lbl_804D62D8[] = "\n";
static char lbl_804D62DC[] = "[%08X";
static char lbl_804D62E4[] = ":";
static char lbl_804D62E8[] = "%02X";
static char lbl_804D62F0[] = "]\n";

s32 hsd_803962A8(void* data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    u32 bit;
    s32 old8, old4, old1, old2;
    u32 *ptr8, *ptr4, *ptr1, *ptr2;
    u8* addr;
    s32 i, j, k;
    PAD_STACK(32);

    bit = 1;
    while (bit <= sp->xBC) {
        switch (sp->xBC & bit) {
        case 0x8: {
            ptr8 = &lbl_8040BAF0.x10;
            old8 = *ptr8;
            {
                u32 memsize = OSGetPhysicalMemSize();
                old8 &= 0x0FFFFFFF;
                *ptr8 = ((old8 + memsize - 0x10) % memsize) + 0x80000000;
            }
            return 1;
        }
        case 0x4: {
            ptr4 = &lbl_8040BAF0.x10;
            old4 = *ptr4;
            {
                u32 memsize = OSGetPhysicalMemSize();
                old4 &= 0x0FFFFFFF;
                *ptr4 = ((old4 + memsize + 0x10) % memsize) + 0x80000000;
            }
            return 1;
        }
        case 0x1: {
            ptr1 = &lbl_8040BAF0.x10;
            old1 = *ptr1;
            {
                u32 memsize = OSGetPhysicalMemSize();
                old1 &= 0x0FFFFFFF;
                *ptr1 = ((old1 + memsize - 0x40) % memsize) + 0x80000000;
            }
            return 1;
        }
        case 0x2: {
            ptr2 = &lbl_8040BAF0.x10;
            old2 = *ptr2;
            {
                u32 memsize = OSGetPhysicalMemSize();
                old2 &= 0x0FFFFFFF;
                *ptr2 = ((old2 + memsize + 0x40) % memsize) + 0x80000000;
            }
            return 1;
        }
        case 0x400:
            hsd_80393D2C(1);
            addr = (u8*) lbl_8040BAF0.x10;
            if ((u8) hsd_80394128(0, 0)) {
                OSReport(lbl_804D62D8);
            }
            i = 0;
            do {
                OSReport(lbl_804D62DC, (u32) addr);
                j = 0;
                do {
                    OSReport(lbl_804D62E4);
                    k = 0;
                    do {
                        OSReport(lbl_804D62E8, *addr++);
                        k++;
                    } while (k < 4);
                    j++;
                } while (j < 4);
                OSReport(lbl_804D62F0);
                i++;
            } while (i < 4);
            hsd_80393D2C(0);
            ps_remove_node(sp, data);
            sp->x0C = 0;
            sp->x10 = 0;
            sp->x18 = 0;
            sp->x14 = 0;
            return 1;
        case 0x100:
            lbl_8040BC3C.x10 = (s32) lbl_8040BAF0.x10;
            lbl_8040BC3C.x18 = &lbl_8040BAF0;
            if (&lbl_8040BC3C != NULL) {
                fn_80394DF4(&lbl_8040BC3C);
                ((ExcptNode*) &lbl_8040BC3C)->next = (ExcptNode*) sp->xD0;
                sp->xD0 = &lbl_8040BC3C;
                if (((ExcptNode*) &lbl_8040BC3C)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BC3C)
                        ->callback((ExcptNode*) &lbl_8040BC3C);
                }
                sp->x0_b5 = 1;
            }
            return 1;
        case 0x200:
            ps_remove_node(sp, data);
            return 1;
        case 0x1000:
            if (lbl_8040BBE8 != NULL) {
                fn_80394DF4(lbl_8040BBE8);
                lbl_8040BBE8->next = (ExcptNode*) sp->xD0;
                sp->xD0 = lbl_8040BBE8;
                if (lbl_8040BBE8->callback != NULL) {
                    lbl_8040BBE8->callback(lbl_8040BBE8);
                }
                sp->x0_b5 = 1;
            }
            return 1;
        default:
            bit <<= 1;
            break;
        }
    }
    return 0;
}

s32 hsd_803966A0(void* data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 result;

    result = hsd_80395550(data);
    switch (result) {
    case 1:
        return 1;
    case 2: {
        u32 cmd = *(u32*) ((u8*) data + 0x14);
        switch (cmd) {
        case 0:
            sp->xBC = 8;
            break;
        case 1:
            sp->xBC = 4;
            break;
        case 2:
            sp->xBC = 1;
            break;
        case 3:
            sp->xBC = 2;
            break;
        case 4:
            sp->xBC = 0x100;
            break;
        case 5:
            sp->xBC = 0x400;
            break;
        case 6:
            sp->xBC = 0x200;
            break;
        }
        ps_remove_node(sp, data);
        return 0;
    }
    case -1:
        ps_remove_node(sp, data);
        return 1;
    default:
        return 0;
    }
}

void hsd_80396868(void)
{
    lbl_8040BC3C.x10 = (lbl_8040BC3C.x10 & 0x0FFFFFF0) | 0x80000000;
}

static char* lbl_804D62F4 = "+--------------------------+";
static char* lbl_804D62F8 = "| INPUT ADDRESS : 8%07X |";

// @TODO: Currently 92.87% match - .bss.0 relocation caps match percentage
void hsd_80396884(void)
{
    char buf[32];
    void* saved;
    s32 x_base;
    u8 ch;
    s32 b6;
    PAD_STACK(28);

    x_base = (hsd_804CF810.x20 - 30) / 2;
    sprintf(buf, "| INPUT ADDRESS : 8%07X |", lbl_8040BC3C.x10 & 0x0FFFFFFF);
    saved = hsd_804CF810.x50;
    hsd_804CF810.x50 = lbl_8040AB00;
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 82;
    hsd_80394434("+--------------------------+");
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 68;
    hsd_80394434(buf);
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 54;
    hsd_80394434("+--------------------------+");
    hsd_804CF810.x4 = (lbl_8040BC3C.x14 + 19 + x_base) * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 68;
    hsd_804CF810.x50 = lbl_8040AB20;
    b6 = hsd_804CF810.x0_b6;
    ch = *(&buf[19] + lbl_8040BC3C.x14);
    if (hsd_804CF810.x0_b7) {
        void* bitmap = (void*) ((u8*) hsd_804CF810.x4C + (ch & 0x7F) * 0x38);
        s32 dst = (&hsd_804CF810.x24)[hsd_804CF810.x34];
        hsd_803922FC(bitmap, hsd_804CF810.x4, hsd_804CF810.x8, b6, dst,
                     hsd_804CF810.x3C, hsd_804CF810.x40, hsd_804CF810.x44,
                     hsd_804CF810.x50);
    } else {
        void* bitmap = (void*) ((u8*) hsd_804CF810.x4C + (ch & 0x7F) * 0x38);
        s32 dst = (&hsd_804CF810.x24)[hsd_804CF810.x34];
        hsd_803921B8(bitmap, hsd_804CF810.x4, hsd_804CF810.x8, dst,
                     hsd_804CF810.x3C, hsd_804CF810.x40, hsd_804CF810.x44,
                     hsd_804CF810.x50);
    }
    hsd_804CF810.x50 = saved;
}

s32 hsd_80396A20(void* data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    ExcptNode* node = data;
    u32 val = lbl_8040BC3C.x10;
    s32 shift = 24 - (lbl_8040BC3C.x14 * 4);
    u32 bit = 1;
    s32 mask = 0xF << shift;

    while (bit <= sp->xBC) {
        switch (sp->xBC & bit) {
        case 0x8:
            lbl_8040BC3C.x10 =
                (val & ~mask) | ((((val >> shift) - 1) & 0xF) << shift);
            return 1;
        case 0x4:
            lbl_8040BC3C.x10 =
                (val & ~mask) | ((((val >> shift) + 1) & 0xF) << shift);
            return 1;
        case 0x1:
            if (lbl_8040BC3C.x14 > 0) {
                lbl_8040BC3C.x14 = lbl_8040BC3C.x14 - 1;
            }
            return 1;
        case 0x2:
            if (lbl_8040BC3C.x14 < 5) {
                lbl_8040BC3C.x14 = lbl_8040BC3C.x14 + 1;
            }
            return 1;
        case 0x100:
            if ((lbl_8040BC3C.x10 & 0x0FFFFFFF) < OSGetPhysicalMemSize()) {
                hsd_80394E8C(lbl_8040BC3C.x18);
                return 1;
            }
            goto default_case;
        case 0x400:
            lbl_8040BC3C.x10 = val & ~mask;
            return 1;
        case 0x200:
            ps_remove_node(sp, node);
            return 1;
        case 0x1000: {
            extern ExcptNode lbl_8040BD74[];
            if (lbl_8040BD74 != NULL) {
                fn_80394DF4(lbl_8040BD74);
                lbl_8040BD74->next = sp->xD0;
                sp->xD0 = lbl_8040BD74;
                if (lbl_8040BD74->callback != NULL) {
                    lbl_8040BD74->callback(lbl_8040BD74);
                }
                sp->x0_b5 = 1;
            }
            return 1;
        }
        default:
        default_case:
            bit <<= 1;
            break;
        }
    }
    return 0;
}

s32 hsd_80396C78(void* data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 result;
    DispData* disp = data;

    result = hsd_80395550(data);
    switch (result) {
    case 1:
        return 1;
    case 2:
        switch (disp->x14) {
        case 0:
            sp->xBC = 8;
            break;
        case 1:
            sp->xBC = 4;
            break;
        case 2:
            sp->xBC = 1;
            break;
        case 3:
            sp->xBC = 2;
            break;
        case 4:
            sp->xBC = 0x100;
            break;
        case 5:
            sp->xBC = 0x400;
            break;
        case 6:
            sp->xBC = 0x200;
            break;
        }
        ps_remove_node(sp, data);
        return 0;
    case -1:
        ps_remove_node(sp, data);
        return 1;
    default:
        return 0;
    }
}

static char* lbl_804D62FC = "+- DBAT ------------------------+";
static char* lbl_804D6300 = "+- IBAT ------------------------+";
static char* lbl_804D6304 = "| %d BL xxxxxxxxxxx  %c%c %c%c%c%c %s |";
static char* lbl_804D6308 = "|   BEPI %08X BRPN %08X |";
static char* lbl_804D630C = "+-------------------------------+";
static char lbl_804D6310[] = "N/A";
static char lbl_804D6314[] = "R/W";
static char lbl_804D6318[] = "R/O";

// @TODO: Currently 86.10% match - .bss.0 relocation affects register
// allocation
void hsd_80396E40(s32 keycode)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    void** px50 = &sp->x50;
    s32* px4 = &sp->x4;
    s32* px40 = &sp->x40;
    s32* px8 = &sp->x8;
    char buf[64];
    void* saved;
    s32 row;
    s32 i;
    s32 spr_u;
    s32 spr_l;
    s32 bat_u;
    s32 bat_l;
    char* perm;
    s32 var_g;
    s32 var_m;
    s32 var_i;
    s32 var_w;
    s32 var_u;
    s32 var_s;
    s32 bit;
    char* ptr;
    s32 j;
    char ch;

    saved = *px50;
    row = sp->x1C - 1;
    *px50 = lbl_8040AB00;
    *px4 = 0x106;
    *px8 = (*px40 - 0x28) - (row + 1) * 14;
    row--;
    if (keycode < 0x220 && keycode >= 0x218) {
        hsd_80394434("+- DBAT ------------------------+");
    } else {
        hsd_80394434("+- IBAT ------------------------+");
    }
    i = 0;
    spr_u = 0x219;
    spr_l = 0x218;
    do {
        bat_u = baselib_mfspr(spr_u);
        bat_l = baselib_mfspr(spr_l);
        switch (bat_u & 2) {
        case 0:
            perm = lbl_804D6310;
            break;
        case 2:
            perm = lbl_804D6314;
            break;
        default:
        case 1:
            perm = lbl_804D6318;
            break;
        }
        if (bat_l & 8) {
            var_g = 'G';
        } else {
            var_g = 'G';
        }
        if (bat_l & 0x10) {
            var_m = 'M';
        } else {
            var_m = 'm';
        }
        if (bat_l & 0x20) {
            var_i = 'I';
        } else {
            var_i = 'i';
        }
        if (bat_l & 0x40) {
            var_w = 'W';
        } else {
            var_w = 'w';
        }
        if (bat_l & 1) {
            var_u = 'U';
        } else {
            var_u = 'u';
        }
        if (bat_l & 2) {
            var_s = 'S';
        } else {
            var_s = 's';
        }
        sprintf(buf, "| %d BL xxxxxxxxxxx  %c%c %c%c%c%c %s |", i, (int) var_s,
                (int) var_u, (int) var_w, (int) var_i, (int) var_m,
                (int) var_g, perm);
        ptr = buf;
        for (j = 0; j < 11; j++) {
            if (bat_l & (1 << (0x1F - (j + 0x13)))) {
                ch = '1';
            } else {
                ch = '0';
            }
            ptr[7] = ch;
            ptr++;
        }
        *px4 = 0x106;
        *px8 = (*px40 - 0x28) - (row + 1) * 14;
        row--;
        hsd_80394434(buf);
        sprintf(buf, "|   BEPI %08X BRPN %08X |", bat_l & 0xFFFC0000,
                bat_u & 0xFFFC0000);
        *px4 = 0x106;
        *px8 = (*px40 - 0x28) - (row + 1) * 14;
        row--;
        hsd_80394434(buf);
        i++;
        spr_u += 2;
        spr_l += 2;
    } while (i < 4);
    *px4 = 0x106;
    *px8 = (*px40 - 0x28) - (row + 1) * 14;
    hsd_80394434("+-------------------------------+");
    *px50 = saved;
}

void fn_803970D8(void) {}

void fn_803970DC(void) {}

void fn_803970E0(void) {}

void fn_803970E4(void) {}

void fn_803970E8(void) {}

void fn_803970EC(void) {}

void fn_803970F0(void) {}

void fn_803970F4(void) {}

void fn_803970F8(void) {}

void fn_803970FC(void) {}

void fn_80397100(void) {}

void fn_80397104(void) {}

void fn_80397108(void) {}

void fn_8039710C(void) {}

static char* lbl_804D631C = "+- SPR --------------+";
static char* lbl_804D6320 = "| NO   NAME    VAL   |";
static char* lbl_804D6324 = "|%4d %s%s %08X|";
static char* lbl_804D6328 = "+---- gekko only ----+";
static char* lbl_804D632C = "|                    |";
static char* lbl_804D6330 = "+--------------------+";
#define SPR_BOX_TOP() lbl_804D631C
#define SPR_BOX_HEADER() lbl_804D6320
#define SPR_VALUE_FMT() lbl_804D6324
#define SPR_GEKKO_ONLY() lbl_804D6328
#define SPR_BLANK_ROW() lbl_804D632C
#define SPR_BOX_BOTTOM() lbl_804D6330
static char lbl_804D6334[] = "     ";
static char lbl_804D633C[] = "    ";
static char lbl_804D6344[] = "   ";
static char lbl_804D6348[] = "  ";
static char lbl_804D634C[] = " ";
static char lbl_804D6350[8] = "";

// @TODO: Currently 85.84% match - .bss.0 relocation causes register shift
void hsd_80397110(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    extern u8 lbl_8040BEC4[];
    u8* base = lbl_8040AB00;
    void* saved;
    s32 offset;
    void** px50 = &sp->x50;
    s32* px4 = &sp->x4;
    s32* px40 = &sp->x40;
    s32* px8 = &sp->x8;
    char buf[32];
    s32 row;
    u32 i;
    u32* spr_entry;
    char* padding;
    PAD_STACK(32);

    saved = *px50;
    row = sp->x1C - 1;
    *px50 = base;
    *px4 = 20;
    *px8 = (*px40 - 0x28) - (row + 1) * 14;
    row--;
    hsd_80394434(SPR_BOX_TOP());
    *px4 = 20;
    *px8 = (*px40 - 0x28) - (row + 1) * 14;
    row--;
    hsd_80394434(SPR_BOX_HEADER());
    {
        u32* bec4 = (u32*) lbl_8040BEC4;
        i = 0;
        offset = 0;
        while (row > 0) {
            u32 spr_off = bec4[4];
            if (spr_off + i >= 0x45) {
                break;
            }
            spr_entry = (u32*) (base + (spr_off * 16) + offset + 0x2D8);
            if (i == bec4[5]) {
                if (spr_entry[3] != 0) {
                    ((void (*)(u32)) spr_entry[3])(spr_entry[0]);
                }
                *px50 = base + 0x20;
            } else {
                *px50 = base;
            }
            *px4 = 20;
            *px8 = (*px40 - 0x28) - (row + 1) * 14;
            row--;
            if (spr_entry[0] == 0) {
                hsd_80394434(SPR_GEKKO_ONLY());
            } else {
                s32 name_len = strlen((char*) spr_entry[1]);
                switch (name_len) {
                case 1:
                    padding = lbl_804D6334;
                    break;
                case 2:
                    padding = lbl_804D633C;
                    break;
                case 3:
                    padding = lbl_804D6344;
                    break;
                case 4:
                    padding = lbl_804D6348;
                    break;
                case 5:
                    padding = lbl_804D634C;
                    break;
                default:
                    padding = lbl_804D6350;
                    break;
                }
                sprintf(buf, SPR_VALUE_FMT(), spr_entry[0],
                        (char*) spr_entry[1], padding,
                        baselib_mfspr(spr_entry[0]));
                hsd_80394434(buf);
            }
            offset += 16;
            i++;
        }
    }
    *px50 = base;
    while (row > 0) {
        *px4 = 20;
        *px8 = (*px40 - 0x28) - (row + 1) * 14;
        row--;
        hsd_80394434(SPR_BLANK_ROW());
    }
    *px4 = 20;
    *px8 = (*px40 - 0x28) - (row + 1) * 14;
    hsd_80394434(SPR_BOX_BOTTOM());
    *px50 = saved;
}

s32 fn_80397374(void* data)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    extern u8 lbl_8040BEC4[];
    u32 bit = 1;
    u32 spr_off = *(u32*) (lbl_8040BEC4 + 0x10);
    u32 sel = *(u32*) (lbl_8040BEC4 + 0x14);

    while (bit <= sp->xBC) {
        switch (sp->xBC & bit) {
        case 0x8:
            if (sel != 0) {
                sel--;
            } else if (spr_off != 0) {
                spr_off--;
            } else {
                u32 max = sp->x1C - 4;
                sel = max;
                spr_off = 0x44;
                spr_off = spr_off - max;
            }
            *(u32*) (lbl_8040BEC4 + 0x10) = spr_off;
            *(u32*) (lbl_8040BEC4 + 0x14) = sel;
            if (sp->x1C) {
            }
            return 1;
        case 0x4:
            if (sel < (u32) (sp->x1C - 4)) {
                sel++;
            } else if (spr_off + sel < 0x43) {
                spr_off++;
            } else {
                sel = 0;
                spr_off = 0;
            }
            *(u32*) (lbl_8040BEC4 + 0x10) = spr_off;
            *(u32*) (lbl_8040BEC4 + 0x14) = sel;
            return 1;
        case 0x1:
        case 0x2:
        case 0x100:
        case 0x800:
        case 0x400:
        case 0x1000:
            return 1;
        case 0x200:
            ps_remove_node(sp, data);
            return 1;
        default:
            bit <<= 1;
            break;
        }
    }
    return 0;
}

void hsd_80397520(void* node_ptr)
{
    PSNode* child1;
    PSNode* child2;
    PSNode* node = node_ptr;

    if (node == NULL) {
        return;
    }
    if ((child1 = node->child) != NULL && child1 != NULL) {
        if ((child2 = child1->child) != NULL && child2 != NULL) {
            if (child2->child != NULL) {
                hsd_80397520(child2->child);
            }
            if (child2->callback != NULL) {
                child2->callback(child2);
            }
        }
        if (child1->callback != NULL) {
            child1->callback(child1);
        }
    }
    if (node->callback != NULL) {
        node->callback(node);
    }
}

// @TODO: Currently 94.61% match - register allocation differences remain
void hsd_803975D4(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    u32 reset_mask;
    PADStatus* cur_pads;
    s32 port;
    u16 buttons;
    u16 new_press;

    reset_mask = 0;
    if (OSGetResetSwitchState() != 0) {
        sp->xC4 = 1;
    } else if (sp->xC4 != 0) {
        OSResetSystem(1, 0, 0);
        for (;;) {
        }
    }
    cur_pads = (PADStatus*) ((u8*) sp + 0x54);
    memcpy(&sp->_pad4[0x30], cur_pads, 0x30);
    PADRead(cur_pads);
    PADClamp(cur_pads);
    for (port = 0; port < 4; port++) {
        if ((s8) sp->_pad4[0xA + port * 0xC] == -1) {
            reset_mask |= 0x80000000 >> port;
        }
    }
    if (reset_mask != 0) {
        PADReset(reset_mask);
    }
    port = 0;
    if ((s8) sp->_pad4[0x3A] != 0) {
        goto port1;
    }
    if ((s8) sp->_pad4[0xA] == 0) {
        goto port_done;
    }
port1:
    port = 1;
    if ((s8) sp->_pad4[0x46] != 0) {
        goto port2;
    }
    if ((s8) sp->_pad4[0x16] == 0) {
        goto port_done;
    }
port2:
    port = 2;
    if ((s8) sp->_pad4[0x52] != 0) {
        goto port3;
    }
    if ((s8) sp->_pad4[0x22] == 0) {
        goto port_done;
    }
port3:
    port = 3;
    if ((s8) sp->_pad4[0x5E] != 0) {
        goto port4;
    }
    if ((s8) sp->_pad4[0x2E] == 0) {
        goto port_done;
    }
port4:
    port = 4;
port_done:
    if (port == 4) {
        sp->xBC = 0;
        sp->xC0 = 0;
        return;
    }
    *(s32*) ((u8*) sp + 0xB4) = port;
    buttons =
        ((PADStatus*) ((u8*) sp + 0x54))[*(s32*) ((u8*) sp + 0xB4)].button;
    new_press =
        ((PADStatus*) ((u8*) sp + 0x84))[*(s32*) ((u8*) sp + 0xB4)].button ^
        buttons;
    sp->xC0 = buttons;
    new_press = buttons & new_press;
    if (new_press != 0) {
        *(s32*) ((u8*) sp + 0xB8) = 0;
    } else if (((PADStatus*) ((u8*) sp + 0x54))[*(s32*) ((u8*) sp + 0xB4)]
                   .button != 0)
    {
        *(s32*) ((u8*) sp + 0xB8) += 1;
        if (*(s32*) ((u8*) sp + 0xB8) > 30) {
            new_press =
                ((PADStatus*) ((u8*) sp + 0x54))[*(s32*) ((u8*) sp + 0xB4)]
                    .button;
        }
    }
    sp->xBC = new_press;
}

// @TODO: Currently 98.70% match - register allocation and relocation
// differences
static inline PSNode* ps_node_child(PSNode* node)
{
    return node->child;
}

void* fn_80397814(void* arg)
{
    u8* base = lbl_8040AB00;
    void* ctx;
    struct ParticleScreenState* sp = &hsd_804CF810;
    u32 retrace;
    u32 next_retrace;
    u32* keybuf;
    PAD_STACK(160);

    ctx = arg;
    hsd_80393D2C(0);
    hsd_80394314();
    PADSetSamplingRate(0);

    /* Wait for first retrace */
    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    keybuf = &sp->xC0;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0x70);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0x808);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0x104);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0x201);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0);

    retrace = VIGetRetraceCount();
    do {
        next_retrace = VIGetRetraceCount();
    } while (next_retrace == retrace);
    retrace = next_retrace;
    do {
        hsd_803975D4();
        do {
            next_retrace = VIGetRetraceCount();
        } while (next_retrace == retrace);
        retrace = next_retrace;
    } while (*keybuf != 0x402);

    /* Configure video */
    sp->xD4 = ctx;
    VIConfigure(sp->x30);
    VISetBlack(0);

    /* Clear display list */
    {
        ExcptNode** head = &sp->xD0;
        ExcptNode* next;
        ExcptNode* cur;
        keybuf = (u32*) head;
        cur = *head;
        while (cur != NULL) {
            next = cur->next;
            cur->next = NULL;
            cur = next;
        }
        *head = NULL;
    }

    /* Link exception node */
    if (base + 0xDC4 != NULL) {
        ((ExcptNode*) (base + 0xDC4))->next = NULL;
        *(void**) keybuf = base + 0xDC4;
        if (((ExcptNode*) (base + 0xDC4))->callback != NULL) {
            ((ExcptNode*) (base + 0xDC4))
                ->callback((ExcptNode*) (base + 0xDC4));
        }
    }

    /* Set initialized flag */
    sp->x0_b5 = 1;
    hsd_80394668();

    /* Initial display setup */
    {
        s32* fb_ptr;
        s32* fb2_ptr;
        u32 retrace2;
        u32 next_retrace2;
        s32* col_ptr;
        s32* x18_ptr;
        s32* x14_ptr;
        s32* x20_ptr;
        s32* nrows_ptr;
        s32* fb_array;
        s32* x3C_ptr;
        s32* c8_ptr;
        s32* cc_ptr;
        s32* size_ptr;
        void* lbl_ptr;
        s32 fb_idx;
        PSNode* node;

        fb_ptr = (s32*) &sp->x40;
        fb2_ptr = (s32*) &sp->x44;
        col_ptr = &sp->x34;
        x18_ptr = &sp->x18;
        x14_ptr = &sp->x14;
        x20_ptr = &sp->x20;
        nrows_ptr = &sp->x1C;
        fb_array = &sp->x24;
        x3C_ptr = &sp->x3C;

        hsd_80394544(*x18_ptr, *x14_ptr, *x20_ptr, *nrows_ptr, 20,
                     *fb_ptr - 40, fb_array[*col_ptr], *x3C_ptr, *fb_ptr,
                     *fb2_ptr, (s32) lbl_804088B8, NULL);

        sp->xC8 = 0;
        c8_ptr = &sp->xC8;
        cc_ptr = &sp->xCC;
        *cc_ptr = *nrows_ptr - 1;

        /* Process display node */
        {
            PSNode* tmp = *(PSNode**) keybuf;
            node = tmp;
        }
        if (node != NULL) {
            if (node->child != NULL) {
                hsd_80397520(node->child);
            }
            if (node->callback != NULL) {
                node->callback(node);
            }
        }

        /* Flush and display first frame */
        size_ptr = &sp->x48;
        fb_idx = *col_ptr;
        DCFlushRange((void*) fb_array[fb_idx], *size_ptr);
        fb_idx = *col_ptr;
        VISetNextFrameBuffer((void*) fb_array[fb_idx]);
        VIFlush();

        retrace2 = VIGetRetraceCount();
        do {
            next_retrace2 = VIGetRetraceCount();
        } while (next_retrace2 == retrace2);
        retrace2 = next_retrace2;
        lbl_ptr = lbl_804088B8;

        /* Main rendering loop */
        while (*keybuf != 0) {
            void* disp_node;
            s32 result;

            hsd_803975D4();
        restart_walk:
            sp->x0_b5 = 0;

            /* Walk display callback list */
            disp_node = *(void**) keybuf;
            result = 0;
            while (disp_node != NULL && !sp->x0_b5) {
                if (*(void* (**) (void*) )((u8*) disp_node + 0xC) != NULL) {
                    result = (s32) (*(void* (**) (void*) )((u8*) disp_node +
                                                           0xC))(disp_node);
                    if (result == 0) {
                    } else {
                        goto walk_done;
                    }
                }
                disp_node = *(void**) disp_node;
            }

            if (sp->x0_b5) {
                goto restart_walk;
            }
            result = 0;
        walk_done:

            if (result != 0) {
                /* Advance frame buffer index */
                s32 idx = *col_ptr;
                s32 nbufs = sp->x38;
                idx = (idx + 1) % nbufs;
                *col_ptr = idx;

                hsd_80394668();

                hsd_80394544(*x18_ptr, *x14_ptr, *x20_ptr, *nrows_ptr, 20,
                             *fb_ptr - 40, (&sp->x24)[*col_ptr], *x3C_ptr,
                             *fb_ptr, *fb2_ptr, (s32) lbl_ptr, NULL);

                *c8_ptr = 0;
                *cc_ptr = *nrows_ptr - 1;

                /* Process display node */
                node = *(PSNode**) keybuf;
                if (node != NULL) {
                    if (node->child != NULL) {
                        hsd_80397520(ps_node_child(node));
                    }
                    if (node->callback != NULL) {
                        node->callback(node);
                    }
                }

                /* Flush and display */
                fb_idx = *col_ptr;
                DCFlushRange((void*) (&sp->x24)[fb_idx], *size_ptr);
                fb_idx = *col_ptr;
                VISetNextFrameBuffer((void*) (&sp->x24)[fb_idx]);
                VIFlush();
            }

            do {
                next_retrace2 = VIGetRetraceCount();
            } while (next_retrace2 == retrace2);
            retrace2 = next_retrace2;
        }
    }

    OSPanic((char*) base + 0x13E0, 2228, (char*) base + 0x13F4);

    return NULL;
}

u8 hsd_804CF8E8[0x1000];

void hsd_80397DA4(OSContext* ctx)
{
    OSThread thread;
    OSCreateThread(&thread, fn_80397814, ctx, hsd_804CF8E8 + 0xFFC,
                   sizeof(hsd_804CF8E8), 0, 1);
    OSResumeThread(&thread);
}

void Exception_StoreDebugLevel(int level)
{
    hsd_804D78C8 = level;
}

void hsd_80397DFC(u32 size)
{
    hsd_804D78CC = (size + 0xF) >> 4;
}

static s8 lbl_8040BF10[0x32] =
    "unsupported no. of special purpose register (%d).";

int baselib_mfspr(int spr)
{
    register int result;
    switch (spr) {
#ifdef MWERKS_GEKKO
    case 0x1:
        asm { mfxer result }
        break;
    case 0x8:
        asm { mflr result }
        break;
    case 0x9:
        asm { mfctr result }
        break;
    case 0x12:
        asm { mfdsisr result }
        break;
    case 0x13:
        asm { mfdar result }
        break;
    case 0x16:
        asm { mfdec result }
        break;
    case 0x19:
        asm { mfsdr1 result }
        break;
    case 0x1A:
        asm { mfsrr0 result }
        break;
    case 0x1B:
        asm { mfsrr1 result }
        break;
    case 0x110:
        asm { mfsprg result, 0 }
        break;
    case 0x111:
        asm { mfsprg result, 1 }
        break;
    case 0x112:
        asm { mfsprg result, 2 }
        break;
    case 0x113:
        asm { mfsprg result, 3 }
        break;
    case 0x118:
        asm { mfspr result, 0x118 } ///< unknown spr?
        break;
    case 0x11A:
        asm { mfear result }
        break;
    case 0x11F:
        asm { mfspr result, pvr }
        break;
    case 0x210:
        asm { mfibatu result, 0 }
        break;
    case 0x211:
        asm { mfibatl result, 0 }
        break;
    case 0x212:
        asm { mfibatu result, 1 }
        break;
    case 0x213:
        asm { mfibatl result, 1 }
        break;
    case 0x214:
        asm { mfibatu result, 2 }
        break;
    case 0x215:
        asm { mfibatl result, 2 }
        break;
    case 0x216:
        asm { mfibatu result, 3 }
        break;
    case 0x217:
        asm { mfibatl result, 3 }
        break;
    case 0x218:
        asm { mfdbatu result, 0 }
        break;
    case 0x219:
        asm { mfdbatl result, 0 }
        break;
    case 0x21A:
        asm { mfdbatu result, 1 }
        break;
    case 0x21B:
        asm { mfdbatl result, 1 }
        break;
    case 0x21C:
        asm { mfdbatu result, 2 }
        break;
    case 0x21D:
        asm { mfdbatl result, 2 }
        break;
    case 0x21E:
        asm { mfdbatu result, 3 }
        break;
    case 0x21F:
        asm { mfdbatl result, 3 }
        break;
    case 0x390:
        asm { mfspr result, gqr0 }
        break;
    case 0x391:
        asm { mfspr result, gqr1 }
        break;
    case 0x392:
        asm { mfspr result, gqr2 }
        break;
    case 0x393:
        asm { mfspr result, gqr3 }
        break;
    case 0x394:
        asm { mfspr result, gqr4 }
        break;
    case 0x395:
        asm { mfspr result, gqr5 }
        break;
    case 0x396:
        asm { mfspr result, gqr6 }
        break;
    case 0x397:
        asm { mfspr result, gqr7 }
        break;
    case 0x398:
        asm { mfspr result, SPR_HID2
        } ///< hid2 gives incorrect codegen? compiler bug?
        break;
    case 0x399:
        asm { mfspr result, wpar }
        break;
    case 0x39A:
        asm { mfspr result, dma_u }
        break;
    case 0x39B:
        asm { mfspr result, dma_l }
        break;
    case 0x3A8:
        asm { mfspr result, ummcr0 }
        break;
    case 0x3A9:
        asm { mfspr result, upmc1 }
        break;
    case 0x3AA:
        asm { mfspr result, upmc2 }
        break;
    case 0x3AB:
        asm { mfspr result, usia }
        break;
    case 0x3AC:
        asm { mfspr result, ummcr1 }
        break;
    case 0x3AD:
        asm { mfspr result, upmc3 }
        break;
    case 0x3AE:
        asm { mfspr result, upmc4 }
        break;
    case 0x3AF:
        asm { mfspr result, SPR_USDA } ///< usda not recognized by compiler?
        break;
    case 0x3B8:
        asm { mfspr result, mmcr0 }
        break;
    case 0x3B9:
        asm { mfspr result, pmc1 }
        break;
    case 0x3BA:
        asm { mfspr result, pmc2 }
        break;
    case 0x3BB:
        asm { mfspr result, sia }
        break;
    case 0x3BC:
        asm { mfspr result, mmcr1 }
        break;
    case 0x3BD:
        asm { mfspr result, pmc3 }
        break;
    case 0x3BE:
        asm { mfspr result, pmc4 }
        break;
    case 0x3BF:
        asm { mfspr result, sda }
        break;
    case 0x3F0:
        asm { mfspr result, hid0 }
        break;
    case 0x3F1:
        asm { mfspr result, hid1 }
        break;
    case 0x3F2:
        asm { mfspr result, iabr }
        break;
    case 0x3F5:
        asm { mfspr result, dabr }
        break;
    case 0x3F9:
        asm { mfspr result, l2cr }
        break;
    case 0x3FB:
        asm { mfspr result, ictc }
        break;
    case 0x3FC:
        asm { mfspr result, thrm1 }
        break;
    case 0x3FD:
        asm { mfspr result, thrm2 }
        break;
    case 0x3FE:
        asm { mfspr result, thrm3 }
        break;
#endif
    default:
        OSReport("unsupported no. of special purpose register (%d).", spr);
        return 0;
    }
    return result;
}

void fn_803982E4(HSD_GObj* gobj, int unused)
{
    HSD_CObjSetCurrent(gobj->hsd_obj);
    fn_80392934();
    hsd_8039254C();
}

static HSD_CObjDesc lbl_8040BF70 = { 0 };

HSD_GObj* hsd_80398310(u16 class_id, u8 p_link, u8 obj_kind, u32 gx_link)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(class_id, p_link, obj_kind);
    if (gobj == NULL) {
        return NULL;
    }
    cobj = HSD_CObjLoadDesc(&lbl_8040BF70);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, fn_803982E4, gx_link);
    hsd_80392528((Event) fn_80392A3C);
    fn_80392A08(4, 1, 0);
    return gobj;
}

void hsd_803983A4(HSD_Generator* gen)
{
    HSD_JObj* jobj;

    if (gen == NULL) {
        return;
    }

    if (gen->kind & 0x800) {
        return;
    }

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }
}

HSD_JObj* hsd_804D08E8[8];

// @TODO: Currently 96.40% match - lis hoisting and r29/r30 register swap
void psInitDataBankLoad(int bank, int* cmdBank, int* texBank, u32* ref,
                        int* formBank)
{
    s32* base = (s32*) hsd_804D08E8;
    u16 version;

    if (formBank != NULL && *formBank != *texBank) {
        OSPanic("particle.c", 177,
                "illigal form data (strange number of group)\n");
    }

    (base + bank)[0x60 / 4] = (s32) ref;
    (base + bank)[0x164 / 4] = *texBank;
    (base + bank)[0x268 / 4] = (s32) (texBank + 1);

    if (formBank != NULL) {
        (base + bank)[0x36C / 4] = (s32) (formBank + 1);
    } else {
        (base + bank)[0x36C / 4] = 0;
    }

    version = *(u16*) cmdBank;
    switch (version) {
    case 0:
        (base + bank)[0x470 / 4] = cmdBank[1];
        (base + bank)[0x574 / 4] = (s32) (cmdBank + 2);
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43: {
        s32 count = cmdBank[1];
        (base + bank)[0x470 / 4] = cmdBank[2] + count;
        (base + bank)[0x574 / 4] = (s32) (cmdBank + 3 - count);
        break;
    }
    default:
        OSPanic("particle.c", 207, "psInitDataBanks: unknown version\n");
    }
}

// @TODO: Currently 75.74% match - register allocation and branch structure
// differences
void psInitDataBankLocate(HSD_Archive* cmdBank, HSD_Archive* texBank,
                          int* formBank)
{
    s32 num;
    s32 num2;
    s32* ptr;
    s32* base;
    s32 i;
    s32 version;

    version = *(u16*) cmdBank;
    if (version < 0x40) {
        if (version == 0) {
            goto version0;
        }
        goto done_cmd;
    }
    if (version >= 0x44) {
        goto done_cmd;
    }
    goto version40;

version0:
    num2 = ((s32*) cmdBank)[1];
    base = (s32*) ((u8*) cmdBank + 8);
    num = 0;
    if (num2 > 0) {
        for (i = 0; i < num2; i++) {
            ((s32*) cmdBank)[i + 2] += (s32) cmdBank;
        }
    }
    goto done_cmd;

version40:
    num = ((s32*) cmdBank)[1];
    base = (s32*) ((u8*) cmdBank + 12) - num;
    num2 = ((s32*) cmdBank)[2] + num;
    ptr = (s32*) cmdBank;
    i = 0;
    while (i < ((s32*) cmdBank)[2]) {
        if (ptr[3] != 0) {
            ptr[3] += (s32) cmdBank;
        }
        ptr++;
        i++;
    }

done_cmd:
    /* Phase 2: Fix cmdList kind bits */
    {
        s32 count = num2 - num;
        ptr = base + num;
        if (num < num2) {
            for (i = 0; i < count; i++) {
                s32* cmd = (s32*) ptr[0];
                if (cmd != NULL) {
                    cmd[2] = cmd[2] & 0xF1FFFFFF;
                    cmd = (s32*) ptr[0];
                    cmd[2] = cmd[2] | 0x08000000;
                }
                ptr++;
            }
        }
    }

    /* Phase 3: texBank relocation */
    {
        s32 num_groups = ((s32*) texBank)[0];
        s32* groups = (s32*) texBank + 1;
        s32* cur = groups;
        s32 k;

        if (num_groups >= 1) {
            k = num_groups;
            do {
                if (cur[0] != 0) {
                    cur[0] += (s32) texBank;
                }
                cur++;
            } while (--k != 0);
        }

        cur = groups;
        if (num_groups > 0) {
            for (k = 0; k < num_groups; k++) {
                HSD_PSTexGroup* tg = (HSD_PSTexGroup*) cur[0];
                if (tg == NULL) {
                    goto next_group;
                }

                /* Relocate texture pointers in the group */
                {
                    s32 ti;
                    s32 ofs;
                    for (ti = 0, ofs = 0;
                         (u32) ti < ((HSD_PSTexGroup*) cur[0])->num;
                         ti++, ofs += 4)
                    {
                        u32* entry_ptr =
                            (u32*) ((u8*) ((HSD_PSTexGroup*) cur[0]) + 24 +
                                    ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                    tg = (HSD_PSTexGroup*) cur[0];
                }

                /* Check format for palette relocation */
                {
                    u32 fmt = tg->fmt;
                    if (fmt != 8 && (fmt - 9) > 1) {
                        goto next_group;
                    }
                }

                /* Palette relocation */
                if (tg->palflag & 1) {
                    /* Single palette pointer */
                    s32 ofs = tg->num * 4 + 24;
                    if (*(u32*) ((u8*) tg + ofs) == 0U) {
                        goto next_group;
                    }
                    *(u32*) ((u8*) tg + ofs) += (u32) texBank;
                } else if (tg->palnum != 0) {
                    /* Multiple palette pointers (palnum > 0) */
                    s32 ti;
                    s32 ofs;
                    ti = (s32) tg->num;
                    ofs = ti * 4;
                    for (; (u32) ti < ((HSD_PSTexGroup*) cur[0])->num +
                                          ((HSD_PSTexGroup*) cur[0])->palnum;
                         ti++, ofs += 4)
                    {
                        HSD_PSTexGroup* tg2 = (HSD_PSTexGroup*) cur[0];
                        u32* entry_ptr = (u32*) ((u8*) tg2 + 24 + ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                } else {
                    /* palnum == 0: relocate double the num entries */
                    s32 ti;
                    s32 ofs;
                    ti = (s32) tg->num;
                    ofs = ti * 4;
                    for (; (u32) ti < ((HSD_PSTexGroup*) cur[0])->num * 2;
                         ti++, ofs += 4)
                    {
                        HSD_PSTexGroup* tg2 = (HSD_PSTexGroup*) cur[0];
                        u32* entry_ptr = (u32*) ((u8*) tg2 + 24 + ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                }

            next_group:
                cur++;
            }
        }

        /* Phase 4: formBank relocation */
        if (formBank == NULL) {
            return;
        }
        if (num_groups >= 1) {
            s32* groups = (s32*) formBank + 1;

            for (i = 0; i < num_groups; i++) {
                if (groups[0] == 0) {
                    goto next_form;
                }
                groups[0] += (s32) formBank;
                {
                    HSD_PSFormGroup* fg = (HSD_PSFormGroup*) groups[0];
                    u32* p2 = (u32*) fg;
                    s32 fi;
                    for (fi = 0; (u32) fi < fg->num; fi++) {
                        if (p2[1] != 0U) {
                            p2[1] += (u32) formBank;
                        }
                        p2++;
                    }
                }
            next_form:
                groups++;
            }
        }
    }
}

void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref,
                    int* formBank)
{
    if (bank < 65) {
        psInitDataBankLocate((HSD_Archive*) cmdBank, (HSD_Archive*) texBank,
                             formBank);
        psInitDataBankLoad(bank, cmdBank, texBank, ref, formBank);
    }
}

// @TODO: Currently 62.67% match - ASM bytes identical, relocation differences
void hsd_80398A08(u32 unused)
{
    extern u16 hsd_804D78DC;
    s32 i;

    HSD_ObjAllocInit(&hsd_804D0F60.alloc_data, 0x98, 4);
    PAD_STACK(24);

    i = 0;
    hsd_804D0908[0] = NULL;
    hsd_804D0908[1] = NULL;
    hsd_804D0908[2] = NULL;
    hsd_804D0908[3] = NULL;
    hsd_804D0908[4] = NULL;
    hsd_804D0908[5] = NULL;
    hsd_804D0908[6] = NULL;
    hsd_804D0908[7] = NULL;
    hsd_804D0908[8] = NULL;
    hsd_804D0908[9] = NULL;
    hsd_804D0908[10] = NULL;
    hsd_804D0908[11] = NULL;
    hsd_804D0908[12] = NULL;
    hsd_804D0908[13] = NULL;
    hsd_804D0908[14] = NULL;
    hsd_804D0908[15] = NULL;
    hsd_804D78E2 = i;
    hsd_804D78DC = i;
    for (; i < 0x41; i++) {
        psNumCmdList[i] = 0;
        psFormGroupArray[i] = NULL;
        ptclref_804D0E5C[i] = NULL;
        psTexGroupArray[i] = NULL;
        psCmdListArray[i] = NULL;
        hsd_804D0908[0x10 + i] = NULL;
    }
    hsd_804D78D4 = 0;
    hsd_804D08E8[0] = NULL;
    hsd_804D08E8[1] = NULL;
    hsd_804D08E8[2] = NULL;
    hsd_804D08E8[3] = NULL;
    hsd_804D08E8[4] = NULL;
    hsd_804D08E8[5] = NULL;
    hsd_804D08E8[6] = NULL;
    hsd_804D08E8[7] = NULL;
}

HSD_Particle* hsd_80398C04(HSD_Particle** head, int linkNo, int bank, u32 kind,
                           u16 texGroup, u8* list, int life, int palflag,
                           f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
                           f32 size, f32 grav, f32 fric, HSD_Generator* gp,
                           int flgInterpret)
{
    HSD_Particle* pp;
    HSD_Particle** slot;
    s16 cmd_wait;

    pp = HSD_ObjAlloc(&hsd_804D0F60.alloc_data);
    if (pp != NULL) {
        memset(pp, 0, 0x98);
    }
    if (pp == NULL) {
        return NULL;
    }

    hsd_804D78E2 += 1;
    if (hsd_804D78E2 > numPeakParticles) {
        numPeakParticles = hsd_804D78E2;
    }

    if (gp != NULL) {
        pp->idnum = gp->idnum;
    } else {
        pp->idnum = hsd_8039D1EC();
    }

    pp->appsrt = NULL;
    if (gp != NULL && gp->appsrt != NULL) {
        psAttachParticleAppSRT(pp, gp->appsrt);
    }

    if (head == NULL) {
        slot = (HSD_Particle**) &hsd_804D0908[linkNo];
        pp->next = *slot;
        *slot = pp;
    } else {
        pp->next = *head;
        *head = pp;
    }

    pp->bank = bank;
    pp->linkNo = linkNo;
    pp->kind = kind;
    pp->texGroup = texGroup;
    pp->pos.x = x;
    pp->pos.y = y;
    pp->pos.z = z;
    pp->vel.x = vx;
    pp->vel.y = vy;
    pp->vel.z = vz;
    pp->size = size;
    pp->grav = grav;
    pp->fric = fric;
    pp->life = (u16) (life + 1);
    pp->cmdList = list;
    pp->cmdMarkPtr = 0;
    pp->cmdPtr = 0;

    if (palflag != 0) {
        pp->kind = pp->kind | 0x10;
    }

    if (list != NULL) {
        cmd_wait = 1;
    } else {
        cmd_wait = 0;
    }
    pp->cmdWait = cmd_wait;
    pp->poseNum = 0;
    pp->palNum = 0xFF;
    pp->primCol.a = 0xFF;
    pp->primCol.b = 0xFF;
    pp->primCol.g = 0xFF;
    pp->primCol.r = 0xFF;
    pp->envCol.a = 0;
    pp->envCol.b = 0;
    pp->envCol.g = 0;
    pp->envCol.r = 0;
    pp->envColCount = 0;
    pp->primColCount = 0;
    pp->sizeCount = 0;
    pp->envColRemain = 0;
    pp->primColRemain = 0;
    pp->aCmpMode = 0x33;
    pp->aCmpParam1 = 1;
    pp->aCmpParam2 = 0xFF;
    pp->aCmpRemain = 0;
    pp->aCmpCount = 0;
    pp->rotateCount = 0;
    pp->rotateTarget = 0.0F;
    pp->rotate = 0.0F;
    pp->gen = gp;
    if (gp != NULL) {
        gp->numChild = gp->numChild + 1;
    }

    pp->pJObjOfs = 0;
    pp->matColRemain = 0;
    pp->matColCount = 0;
    pp->matRGB = 0xFF;
    pp->matA = 0xFF;
    pp->ambColRemain = 0;
    pp->ambColCount = 0;
    pp->ambRGB = 0xFF;
    pp->ambA = 0xFF;
    pp->trail = 1.0F;
    pp->userdata = NULL;

    if (gp != NULL) {
        if (gp->userfunc != NULL) {
            if (gp->userfunc->hookCreate != NULL) {
                gp->userfunc->hookCreate(pp);
            }
        }
    }

    pp->callback = NULL;
    if (flgInterpret != 0) {
        hsd_8039930C(pp, 0);
    }
    return pp;
}

#pragma push
#pragma dont_inline on
void hsd_80398F0C(s32 linkNo, s32 bank, s32 kind, u16 texGroup, s32 cmdList,
                  s32 life, s32 zero, s32 gen, f32 pos_x, f32 pos_y, f32 pos_z,
                  f32 vel_x, f32 vel_y, f32 vel_z, f32 fric, f32 rate,
                  f32 angle3)
{
    hsd_80398C04(0, linkNo, bank, kind, texGroup, (u8*) cmdList, life, zero,
                 pos_x, pos_y, pos_z, vel_x, vel_y, vel_z, fric, rate, angle3,
                 (HSD_Generator*) gen, 1);
}
#pragma pop

// @TODO: Currently 95.03% match - ASM bytes identical, relocation differences
void hsd_80398F8C(HSD_Particle* pp, f32 angle)
{
    f32 vx = pp->vel.x;
    f32 vz = pp->vel.z;
    f32 vy = pp->vel.y;
    f32 sin_a, cos_a;
    f32 sin_e, cos_e;
    f32 rand_angle;
    f32 cos_rand, sin_rand;
    f32 sin_angle, cos_angle;
    f32 abs_z;
    f32 temp;
    f32 abs_temp;
    PAD_STACK(16);

    {
        f32 azimuth;

        abs_z = vz;
        *(s32*) &abs_z &= 0x7FFFFFFF;
        if (abs_z < 1.1754944e-38F) {
            if (vy >= 0.0F) {
                azimuth = 1.5707964F;
            } else {
                azimuth = -1.5707964F;
            }
        } else {
            azimuth = atan2f(vy, vz);
        }

        sin_a = sinf(azimuth);
        cos_a = cosf(azimuth);
    }

    {
        f32 azimuth;

        temp = vy * sin_a + vz * cos_a;
        abs_temp = temp;
        *(s32*) &abs_temp &= 0x7FFFFFFF;
        if (abs_temp < 1.1754944e-38F) {
            if (vx >= 0.0F) {
                azimuth = 1.5707964F;
            } else {
                azimuth = -1.5707964F;
            }
        } else {
            azimuth = atan2f(vx, temp);
        }

        sin_e = sinf(azimuth);
        cos_e = cosf(azimuth);
    }

    vx = (vx * vx + vy * vy) + vz * vz;
    vx = sqrtf(vx);

    rand_angle = (f32) (3.141592653589793 * HSD_Randf() * 2.0);

    sin_angle = vx * sinf(angle);
    cos_rand = sin_angle * cosf(rand_angle);
    sin_rand = sin_angle * sinf(rand_angle);
    cos_angle = vx * cosf(angle);

    pp->vel.x = cos_rand * cos_e + cos_angle * sin_e;
    pp->vel.y = cos_e * (cos_angle * sin_a) +
                (sin_e * (-cos_rand * sin_a) + sin_rand * cos_a);
    pp->vel.z = cos_e * (cos_angle * cos_a) +
                (sin_e * (-cos_rand * cos_a) - sin_rand * sin_a);
}

s32 hsd_803991D8(HSD_Generator* gen, HSD_JObj* jobj, f32 force, f32 range)
{
    f32 dx, dy, dz;
    f32 dist_sq;
    f32 scale;

    if (jobj == NULL || range < 0.0F) {
        return 0;
    }

    HSD_JObjSetupMatrix(jobj);

    dx = jobj->mtx[0][3] - gen->fric;
    dy = jobj->mtx[1][3] - gen->size;
    dz = jobj->mtx[2][3] - gen->radius;
    dist_sq = dx * dx + dy * dy + dz * dz;

    if (dist_sq <= range * range) {
        return 1;
    }

    if (dist_sq == 0.0F) {
        return 0;
    }

    scale = force / dist_sq;
    gen->pos.z += scale * dx;
    gen->vel.x += scale * dy;
    gen->vel.y += scale * dz;
    return 0;
}

// @TODO: Currently 93.95% match - register allocation differences (stmw
// r20 vs r21), r27/r28 swap, and PC advance codegen patterns
void* hsd_8039930C(void* pp_arg, void* prev_arg)
{
    HSD_Particle* pp = pp_arg;
    HSD_Particle* prev = prev_arg;
    u8* pc;
    int operand;
    u8 opcode;
    u8 cls;
    HSD_Particle* child;
    HSD_Generator* gchild;
    HSD_PSCmdList* cl;
    HSD_PSTexGroup* tg;
    PAD_STACK(464);

#define fval (*(f32*) &hsd_804D78D0)
#define fbytes (*(ParticleFloatBytes*) &hsd_804D78D0).bytes

    /* Early exit: bit 11 of kind set */
    if (pp->kind & 0x800) {
        return pp->next;
    }

    /* --- Timer interpolation --- */

    /* Size interpolation */
    if (pp->sizeCount != 0) {
        pp->size += (pp->sizeTarget - pp->size) / (f32) pp->sizeCount;
        pp->sizeCount--;
    }

    /* Primary color countdown */
    if (pp->primColCount != 0) {
        pp->primColRemain--;
        if (pp->primColRemain == 0) {
            pp->primColCount = 0;
            pp->primCol.r = pp->primColTarget.r;
            pp->primCol.g = pp->primColTarget.g;
            pp->primCol.b = pp->primColTarget.b;
            pp->primCol.a = pp->primColTarget.a;
        }
    }

    /* Environment color countdown */
    if (pp->envColCount != 0) {
        pp->envColRemain--;
        if (pp->envColRemain == 0) {
            pp->envColCount = 0;
            pp->envCol.r = pp->envColTarget.r;
            pp->envCol.g = pp->envColTarget.g;
            pp->envCol.b = pp->envColTarget.b;
            pp->envCol.a = pp->envColTarget.a;
        }
    }

    /* Material color countdown */
    if (pp->matColCount != 0) {
        pp->matColRemain--;
        if (pp->matColRemain == 0) {
            pp->matColCount = 0;
            pp->matRGB = pp->matRGBTarget;
            pp->matA = pp->matATarget;
        }
    }

    /* Ambient color countdown */
    if (pp->ambColCount != 0) {
        pp->ambColRemain--;
        if (pp->ambColRemain == 0) {
            pp->ambColCount = 0;
            pp->ambRGB = pp->ambRGBTarget;
            pp->ambA = pp->ambATarget;
        }
    }

    /* Alpha compare countdown */
    if (pp->aCmpCount != 0) {
        pp->aCmpRemain--;
        if (pp->aCmpRemain == 0) {
            pp->aCmpCount = 0;
            pp->aCmpParam1 = pp->aCmpParam1Target;
            pp->aCmpParam2 = pp->aCmpParam2Target;
        }
    }

    /* Rotate interpolation */
    if (pp->rotateCount != 0) {
        pp->rotate += (pp->rotateTarget - pp->rotate) / (f32) pp->rotateCount;
        pp->rotateCount--;
    }

    /* --- Command wait check --- */
    if (pp->cmdWait == 0) {
        goto do_life;
    }
    if (--pp->cmdWait != 0) {
        goto do_life;
    }

    /* --- Bytecode loop --- */
    operand = 0;
    pc = pp->cmdList + pp->cmdPtr;

    for (;;) {
        opcode = *pc++;

        if (opcode < 0x80) {
            /* Low opcode range */
            operand = opcode & 0x1F;
            if (opcode & 0x20) {
                operand = (operand << 8) + *pc++;
            }
            switch (opcode & 0xC0) {
            case 0x00:
                /* Wait/nop: operand is wait count */
                break;
            case 0x40: {
                /* Texture command */
                u8 pn = *pc++;
                pp->poseNum = pn;
                {
                    HSD_PSTexGroup** tga;
                    HSD_PSTexGroup* texGrp;
                    u8 bank = pp->bank;
                    u8 tgIdx = pp->texGroup;

                    tga = psTexGroupArray[bank];
                    texGrp = tga[tgIdx];
                    if (texGrp != NULL && texGrp->texTable != NULL) {
                        if (texGrp->texTable[pp->poseNum] != NULL) {
                            pp->kind |= DispTexture;
                        }
                    }
                }
                break;
            }
            }
        } else {
            /* High opcode: classify */
            operand = 0;
            cls = opcode & 0xF8;
            if (cls > 0x98) {
                cls = opcode & 0xF0;
                if (cls != 0xC0 && cls != 0xD0) {
                    cls = opcode;
                }
            }

            switch (cls) {
            case 0x80:
                /* Set position */
                if (opcode & 1) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.x = fval;
                }
                if (opcode & 2) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.y = fval;
                }
                if (opcode & 4) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.z = fval;
                }
                break;

            case 0x88:
                /* Add to position */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.x += fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.y += fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.z += fval;
                }
                break;

            case 0x90:
                /* Set velocity */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.x = fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.y = fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.z = fval;
                }
                break;

            case 0x98:
                /* Add to velocity */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.x += fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.y += fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.z += fval;
                }
                break;

            case 0xA0:
                /* Set size interpolation target */
                {
                    pp->sizeCount = *pc++;
                    {
                        u16 cnt = pp->sizeCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->sizeCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->sizeTarget = fval;
                    if (pp->sizeCount == 0) {
                        pp->size = pp->sizeTarget;
                    }
                }
                break;

            case 0xA1:
                /* Clear DispTexture flag */
                pp->kind &= ~DispTexture;
                break;

            case 0xA2:
                /* Set gravity */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->grav = fval;
                if (pp->grav == 0.0F) {
                    pp->kind &= ~1;
                } else {
                    pp->kind |= 1;
                }
                break;

            case 0xA3:
                /* Set friction */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->fric = fval;
                if (pp->fric == 1.0F) {
                    pp->kind &= ~2;
                } else {
                    pp->kind |= 2;
                }
                break;

            case 0xA4:
                /* Spawn child particle by cmdList ID */
                {
                    int linkNo = pp->linkNo;
                    int bank = pp->bank;
                    int idx;
                    int palflag;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        psAttachParticleAppSRT(child, pp->appsrt);
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xF1:
                /* Spawn child particle from ptclref remap */
                {
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    bank = pp->bank;
                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (ptclref_804D0E5C[bank] != NULL) {
                        idx = ptclref_804D0E5C[bank][idx];
                    }

                    linkNo = pp->linkNo;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        psAttachParticleAppSRT(child, pp->appsrt);
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xA5:
                /* Spawn child generator */
                {
                    int idx;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;
                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild != NULL) {
                        HSD_psAppSRT* srt;
                        gchild->idnum = pp->idnum;
                        if (pp->gen != NULL) {
                            HSD_JObj* jobj = pp->gen->jobj;
                            gchild->jobj = jobj;
                            ref_INC(jobj);
                        }
                        gchild->type |= 0x100;
                        if (pp->gen != NULL) {
                            gchild->type |= pp->gen->type & 0x1E00;
                            if (gchild->kind & (1 << 17)) {
                                gchild->type &= ~(1 << 9);
                            }
                        }
                        if ((srt = pp->appsrt) != NULL) {
                            psAttachGeneratorAppSRT(gchild, srt);
                        }
                        if (pp->appsrt != NULL) {
                            if (gchild->appsrt == NULL) {
                                break;
                            }
                            if (pp->appsrt == gchild->appsrt) {
                                gchild->pos.x = pp->pos.x;
                                gchild->pos.y = pp->pos.y;
                                gchild->pos.z = pp->pos.z;
                            } else {
                                gchild->appsrt->translate.x =
                                    pp->appsrt->translate.x;
                                gchild->appsrt->translate.y =
                                    pp->appsrt->translate.y;
                                gchild->appsrt->translate.z =
                                    pp->appsrt->translate.z;
                            }
                        } else if (gchild->appsrt != NULL) {
                            gchild->appsrt->translate.x = pp->pos.x;
                            gchild->appsrt->translate.y = pp->pos.y;
                            gchild->appsrt->translate.z = pp->pos.z;
                        } else {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        }
                    }
                }
                break;

            case 0xEF:
                /* Spawn generator with kind flags */
                {
                    int idx;
                    u8 flags;
                    HSD_psAppSRT* srt;

                    idx = (pc[0] << 8) + pc[1];
                    flags = pc[2];
                    pc += 3;
                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild == NULL) {
                        break;
                    }
                    gchild->idnum = pp->idnum;
                    if (pp->gen != NULL) {
                        HSD_JObj* jobj = pp->gen->jobj;
                        gchild->jobj = jobj;
                        ref_INC(jobj);
                    }
                    gchild->type |= 0x100;
                    if (pp->gen != NULL) {
                        gchild->type |= pp->gen->type & 0x1E00;
                        if (gchild->kind & (1 << 17)) {
                            gchild->type &= ~(1 << 9);
                        }
                    }
                    if ((srt = pp->appsrt) != NULL) {
                        psAttachGeneratorAppSRT(gchild, srt);
                    }
                    gchild->kind &= 0xF1FFFFFF;
                    gchild->kind |= ((flags & 7) << 25);
                    if (pp->appsrt != NULL) {
                        if (gchild->appsrt == NULL) {
                            break;
                        }
                        if (pp->appsrt == gchild->appsrt) {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        } else {
                            gchild->appsrt->translate.x =
                                pp->appsrt->translate.x;
                            gchild->appsrt->translate.y =
                                pp->appsrt->translate.y;
                            gchild->appsrt->translate.z =
                                pp->appsrt->translate.z;
                        }
                    } else if (gchild->appsrt != NULL) {
                        gchild->appsrt->translate.x = pp->pos.x;
                        gchild->appsrt->translate.y = pp->pos.y;
                        gchild->appsrt->translate.z = pp->pos.z;
                    } else {
                        gchild->pos.x = pp->pos.x;
                        gchild->pos.y = pp->pos.y;
                        gchild->pos.z = pp->pos.z;
                    }
                }
                break;

            case 0xF0:
                /* Spawn generator with kind flags + ptclref remap */
                {
                    int idx;
                    u8 flags;
                    HSD_psAppSRT* srt;

                    idx = (pc[0] << 8) + pc[1];
                    flags = pc[2];
                    pc += 3;

                    if (ptclref_804D0E5C[pp->bank] != NULL) {
                        idx = ptclref_804D0E5C[pp->bank][idx];
                    }

                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild == NULL) {
                        break;
                    }
                    gchild->idnum = pp->idnum;
                    if (pp->gen != NULL) {
                        HSD_JObj* jobj = pp->gen->jobj;
                        gchild->jobj = jobj;
                        ref_INC(jobj);
                    }
                    gchild->type |= 0x100;
                    if (pp->gen != NULL) {
                        gchild->type |= pp->gen->type & 0x1E00;
                        if (gchild->kind & (1 << 17)) {
                            gchild->type &= ~(1 << 9);
                        }
                    }
                    if ((srt = pp->appsrt) != NULL) {
                        psAttachGeneratorAppSRT(gchild, srt);
                    }
                    gchild->kind &= 0xF1FFFFFF;
                    gchild->kind |= ((flags & 7) << 25);
                    if (pp->appsrt != NULL) {
                        if (gchild->appsrt == NULL) {
                            break;
                        }
                        if (pp->appsrt == gchild->appsrt) {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        } else {
                            gchild->appsrt->translate.x =
                                pp->appsrt->translate.x;
                            gchild->appsrt->translate.y =
                                pp->appsrt->translate.y;
                            gchild->appsrt->translate.z =
                                pp->appsrt->translate.z;
                        }
                    } else if (gchild->appsrt != NULL) {
                        gchild->appsrt->translate.x = pp->pos.x;
                        gchild->appsrt->translate.y = pp->pos.y;
                        gchild->appsrt->translate.z = pp->pos.z;
                    } else {
                        gchild->pos.x = pp->pos.x;
                        gchild->pos.y = pp->pos.y;
                        gchild->pos.z = pp->pos.z;
                    }
                }
                break;

            case 0xA6:
                /* Set life with random offset */
                {
                    int baseLife;
                    int randomRange;
                    baseLife = (pc[0] << 8) + pc[1];
                    randomRange = (pc[2] << 8) + pc[3];
                    pc += 4;
                    pp->life =
                        baseLife + (s32) ((f32) randomRange * HSD_Randf());
                }
                break;

            case 0xA7:
                /* Conditional kill */
                {
                    u8 threshold = *pc++;
                    if (threshold >= (s32) (256.0F * HSD_Randf())) {
                        pp->life = 1;
                        goto exit_loop;
                    }
                }
                break;

            case 0xA8:
                /* Position random offset */
                {
                    u8* pc2;
                    fbytes[0] = *pc++;
                    fbytes[1] = *pc++;
                    fbytes[2] = *pc++;
                    fbytes[3] = *pc++;
                    pp->pos.x += 2.0F * fval * HSD_Randf() - fval;
                    pc2 = pc + 4;
                    fbytes[0] = pc[0];
                    fbytes[1] = pc[1];
                    fbytes[2] = pc[2];
                    fbytes[3] = pc[3];
                    pp->pos.y += 2.0F * fval * HSD_Randf() - fval;
                    pc = pc2 + 4;
                    fbytes[0] = pc2[0];
                    fbytes[1] = pc2[1];
                    fbytes[2] = pc2[2];
                    fbytes[3] = pc2[3];
                    pp->pos.z += 2.0F * fval * HSD_Randf() - fval;
                }
                break;

            case 0xA9:
                /* Call force function with float parameter */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                hsd_80398F8C(pp, fval);
                break;

            case 0xAA:
                /* Spawn child particle with random ptclref index */
                {
                    int baseIdx;
                    int randomRange;
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    baseIdx = (pc[0] << 8) + pc[1];
                    randomRange = (pc[2] << 8) + pc[3];
                    pc += 4;

                    idx = baseIdx + (s32) ((f32) randomRange * HSD_Randf());

                    if (ptclref_804D0E5C[pp->bank] != NULL) {
                        idx = ptclref_804D0E5C[pp->bank][idx];
                    }

                    linkNo = pp->linkNo;
                    bank = pp->bank;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        {
                            HSD_psAppSRT* srt;
                            if ((srt = pp->appsrt) != NULL) {
                                psAttachParticleAppSRT(child, srt);
                            }
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xAB:
                /* Velocity scale */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->vel.x *= fval;
                pp->vel.y *= fval;
                pp->vel.z *= fval;
                break;

            case 0xAC:
                /* Size interpolation with random */
                {
                    f32 range;
                    pp->sizeCount = *pc++;
                    {
                        u16 cnt = pp->sizeCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->sizeCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pp->sizeTarget = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    range = fval;
                    pc += 8;
                    pp->sizeTarget += range * HSD_Randf();
                    if (pp->sizeCount == 0) {
                        pp->size = pp->sizeTarget;
                    }
                }
                break;

            case 0xAD:
                /* Set PrimEnv flag */
                pp->kind |= PrimEnv;
                break;

            case 0xAE:
                /* Clear Mirror flags */
                pp->kind &= ~(MirrorS | MirrorT);
                break;

            case 0xAF:
                /* Set MirrorS */
                pp->kind &= ~MirrorT;
                pp->kind |= MirrorS;
                break;

            case 0xB0:
                /* Set MirrorT */
                pp->kind &= ~MirrorS;
                pp->kind |= MirrorT;
                break;

            case 0xB1:
                /* Set MirrorS | MirrorT */
                pp->kind |= (MirrorS | MirrorT);
                break;

            case 0xB2:
                /* AppSRT matrix transform and detach */
                {
                    HSD_psAppSRT* srt = pp->appsrt;
                    if (srt == NULL) {
                        break;
                    }
                    if ((u8) srt->xA2 != 0) {
                        break;
                    }
                    hsd_803983A4(srt->gp);
                    srt = pp->appsrt;
                    HSD_MtxSRT(srt->mmtx, &srt->scale, (Vec3*) &srt->rot,
                               &srt->translate, NULL);
                    pp->pos.x = pp->appsrt->mmtx[0][1] * pp->pos.y +
                                pp->appsrt->mmtx[0][0] * pp->pos.x +
                                pp->appsrt->mmtx[0][2] * pp->pos.z +
                                pp->appsrt->mmtx[0][3];
                    pp->pos.y = pp->appsrt->mmtx[1][1] * pp->pos.y +
                                pp->appsrt->mmtx[1][0] * pp->pos.x +
                                pp->appsrt->mmtx[1][2] * pp->pos.z +
                                pp->appsrt->mmtx[1][3];
                    pp->pos.z = pp->appsrt->mmtx[2][1] * pp->pos.y +
                                pp->appsrt->mmtx[2][0] * pp->pos.x +
                                pp->appsrt->mmtx[2][2] * pp->pos.z +
                                pp->appsrt->mmtx[2][3];
                    psRemoveParticleAppSRT(pp);
                }
                break;

            case 0xB3:
                /* Alpha compare interpolation setup */
                {
                    s32 step;

                    if (pp->aCmpCount != 0) {
                        step =
                            ((s32) pp->aCmpRemain << 16) / (s32) pp->aCmpCount;
                        pp->aCmpParam1 =
                            (u8) ((((s32) pp->aCmpParam1Target << 16) +
                                   step * ((s32) pp->aCmpParam1 -
                                           (s32) pp->aCmpParam1Target)) >>
                                  16);
                        pp->aCmpParam2 =
                            (u8) ((((s32) pp->aCmpParam2Target << 16) +
                                   step * ((s32) pp->aCmpParam2 -
                                           (s32) pp->aCmpParam2Target)) >>
                                  16);
                    }
                    {
                        pp->aCmpCount = *pc++;
                        {
                            u16 cnt = pp->aCmpCount;
                            if (cnt & 0x80) {
                                cnt = ((cnt & 0x7F) << 8) + *pc++;
                                pp->aCmpCount = cnt;
                            }
                        }
                    }
                    pp->aCmpMode = *pc++;
                    pp->aCmpParam1Target = *pc++;
                    pp->aCmpParam2Target = *pc++;
                    if (pp->aCmpCount == 0) {
                        pp->aCmpParam1 = pp->aCmpParam1Target;
                        pp->aCmpParam2 = pp->aCmpParam2Target;
                        pp->aCmpRemain = 0;
                        pp->aCmpCount = 0;
                    } else {
                        pp->aCmpRemain = pp->aCmpCount;
                    }
                }
                break;

            case 0xB4:
                /* Set TexInterpNear */
                pp->kind |= TexInterpNear;
                break;

            case 0xB5:
                /* Clear TexInterpNear */
                pp->kind &= ~TexInterpNear;
                break;

            case 0xB6:
                /* Rotate interpolation setup */
                {
                    pp->rotateCount = *pc++;
                    {
                        u16 cnt = pp->rotateCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->rotateCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->rotateTarget += fval;
                    if (pp->rotateCount == 0) {
                        pp->rotate = pp->rotateTarget;
                    }
                }
                break;

            case 0xB7:
                /* Aim velocity toward JObj */
                {
                    int idx = *pc++;
                    HSD_JObj* jobj;
                    f32 vel_mag_sq, vel_mag;
                    f32 dx, dy, dz, dist_sq, dist;

                    jobj = hsd_804D08E8[idx + pp->pJObjOfs];
                    if (jobj == NULL) {
                        break;
                    }
                    HSD_JObjSetupMatrix(jobj);
                    vel_mag_sq = pp->vel.x * pp->vel.x + pp->vel.y * pp->vel.y;
                    dx = jobj->mtx[0][3] - pp->pos.x;
                    vel_mag_sq += pp->vel.z * pp->vel.z;
                    dy = jobj->mtx[1][3] - pp->pos.y;
                    dz = jobj->mtx[2][3] - pp->pos.z;
                    vel_mag = sqrtf(vel_mag_sq);
                    dist_sq = dy * dy + dx * dx;
                    dist_sq += dz * dz;
                    if (dist_sq == 0.0F) {
                        break;
                    }
                    dist = sqrtf(dist_sq);
                    {
                        f32 scale = vel_mag / dist;
                        pp->vel.x = dx * scale;
                        pp->vel.y = dy * scale;
                        pp->vel.z = dz * scale;
                    }
                }
                break;

            case 0xB8:
                /* Force toward JObj with kill on proximity */
                {
                    int idx = *pc++;
                    f32 force, range;

                    ((u8*) &fval)[0] = *pc++;
                    ((u8*) &fval)[1] = *pc++;
                    ((u8*) &fval)[2] = *pc++;
                    ((u8*) &fval)[3] = *pc++;
                    force = fval;
                    ((u8*) &fval)[0] = *pc++;
                    ((u8*) &fval)[1] = *pc++;
                    ((u8*) &fval)[2] = *pc++;
                    ((u8*) &fval)[3] = *pc++;
                    range = fval;
                    {
                        HSD_JObj* jobj = hsd_804D08E8[idx + pp->pJObjOfs];
                        if (hsd_803991D8((HSD_Generator*) pp, jobj, force,
                                         range) != 0)
                        {
                            pp->life = 1;
                            goto exit_loop;
                        }
                    }
                }
                break;

            case 0xB9:
                /* Spawn child particle + inherit pos and vel */
                {
                    int linkNo = pp->linkNo;
                    int bank = pp->bank;
                    int idx;
                    int palflag;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        HSD_psAppSRT* srt;
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->vel.x = pp->vel.x;
                        child->vel.y = pp->vel.y;
                        child->vel.z = pp->vel.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        if ((srt = pp->appsrt) != NULL) {
                            psAttachParticleAppSRT(child, srt);
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xF2:
                /* Spawn child + inherit pos/vel + ptclref remap */
                {
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    bank = pp->bank;
                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (ptclref_804D0E5C[bank] != NULL) {
                        idx = ptclref_804D0E5C[bank][idx];
                    }

                    linkNo = pp->linkNo;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->vel.x = pp->vel.x;
                        child->vel.y = pp->vel.y;
                        child->vel.z = pp->vel.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        {
                            HSD_psAppSRT* srt;
                            if ((srt = pp->appsrt) != NULL) {
                                psAttachParticleAppSRT(child, srt);
                            }
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xBA:
                /* PrimCol delta with random */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.r + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.g + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.b + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.a + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.a = (u8) (s32) val;

                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    } else {
                        pp->primColRemain = pp->primColCount;
                    }
                }
                break;

            case 0xBB:
                /* EnvCol delta with random */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.r + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.g + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.b + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.a + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.a = (u8) (s32) val;

                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    } else {
                        pp->envColRemain = pp->envColCount;
                    }
                }
                break;

            case 0xBC:
                /* PoseNum with random */
                {
                    int randRange;

                    pp->poseNum = *pc++;
                    randRange = *pc++;
                    pp->poseNum = (u8) (s32) ((f32) randRange * HSD_Randf() +
                                              (f32) pp->poseNum);
                    {
                        u8 bank = pp->bank;
                        u8 tgIdx = pp->texGroup;
                        HSD_PSTexGroup** tga;
                        HSD_PSTexGroup* texGrp;

                        tga = psTexGroupArray[bank];
                        texGrp = tga[tgIdx];
                        if (texGrp != NULL && texGrp->texTable != NULL) {
                            if (texGrp->texTable[pp->poseNum] != NULL) {
                                pp->kind |= DispTexture;
                            }
                        }
                    }
                }
                break;

            case 0xBD:
                /* Normalize velocity to target speed */
                {
                    f32 base_speed, random_range, target_speed;
                    f32 mag;

                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    base_speed = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    random_range = fval;
                    pc += 8;
                    target_speed = base_speed + random_range * HSD_Randf();
                    mag = pp->vel.x * pp->vel.x + pp->vel.y * pp->vel.y +
                          pp->vel.z * pp->vel.z;
                    mag = sqrtf(mag);
                    if (mag > 0.0F) {
                        target_speed /= mag;
                        pp->vel.x *= target_speed;
                        pp->vel.y *= target_speed;
                        pp->vel.z *= target_speed;
                    }
                }
                break;

            case 0xBE:
                /* Velocity component multiply */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pp->vel.x *= fval;
                ((u8*) &fval)[0] = pc[4];
                ((u8*) &fval)[1] = pc[5];
                ((u8*) &fval)[2] = pc[6];
                ((u8*) &fval)[3] = pc[7];
                pp->vel.y *= fval;
                ((u8*) &fval)[0] = pc[8];
                ((u8*) &fval)[1] = pc[9];
                ((u8*) &fval)[2] = pc[10];
                ((u8*) &fval)[3] = pc[11];
                pc += 12;
                pp->vel.z *= fval;
                break;

            case 0xBF:
                /* JObj offset */
                {
                    u8 idx = *pc++;
                    pp->kind |= (((idx + pp->pJObjOfs) & 7) << 12) | 0x8000;
                }
                break;

            case 0xC0:
                /* PrimCol selective channel setup */
                {
                    s32 step;
                    u16 cnt;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }
                    pp->primColCount = *pc++;
                    cnt = pp->primColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->primColCount = cnt;
                    }
                    pp->primColTarget = pp->primCol;
                    if (opcode & 1) {
                        pp->primColTarget.r = *pc++;
                    }
                    if (opcode & 2) {
                        pp->primColTarget.g = *pc++;
                    }
                    if (opcode & 4) {
                        pp->primColTarget.b = *pc++;
                    }
                    if (opcode & 8) {
                        pp->primColTarget.a = *pc++;
                    }
                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                        pp->primColRemain = 0;
                    } else {
                        pp->primColRemain = pp->primColCount;
                    }
                }
                break;

            case 0xD0:
                /* EnvCol selective channel setup */
                {
                    s32 step;
                    u16 cnt;

                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }
                    pp->envColCount = *pc++;
                    cnt = pp->envColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->envColCount = cnt;
                    }
                    pp->envColTarget = pp->envCol;
                    if (opcode & 1) {
                        pp->envColTarget.r = *pc++;
                    }
                    if (opcode & 2) {
                        pp->envColTarget.g = *pc++;
                    }
                    if (opcode & 4) {
                        pp->envColTarget.b = *pc++;
                    }
                    if (opcode & 8) {
                        pp->envColTarget.a = *pc++;
                    }
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                        pp->envColRemain = 0;
                    } else {
                        pp->envColRemain = pp->envColCount;
                    }
                }
                break;

            case 0xE0:
                /* Dual delta PrimCol + EnvCol */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }
                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();

                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.r;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.r = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.r;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.g;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.g = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.g;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.b;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.b = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.b;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.a;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.a = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.a;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.a = (u8) (s32) val;

                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    }
                    pp->primColRemain = pp->primColCount;
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    }
                    pp->envColRemain = pp->envColCount;
                }
                break;

            case 0xE9:
                /* Dual PrimCol + EnvCol interp + selective random delta */
                {
                    s32 step;
                    int timing;
                    int flags;
                    f32 scale;
                    s8 delta;
                    f32 delta_float;
                    f32 val;

                    /* Interpolate primCol */
                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }

                    /* Interpolate envCol */
                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    /* Read timing and flags from bytecode */
                    flags = *pc++;
                    timing = *pc++;

                    /* Compute scale from timing */
                    if (timing != 0) {
                        scale =
                            (f32) (s32) ((f32) (timing + 1) * HSD_Randf()) /
                            (f32) timing;
                    } else {
                        scale = HSD_Randf();
                    }

                    /* R channel delta */
                    if (flags & 0x01) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.r;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.r = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.r;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.r = (u8) (s32) val;
                        }
                    }

                    /* G channel delta */
                    if (flags & 0x02) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.g;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.g = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.g;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.g = (u8) (s32) val;
                        }
                    }

                    /* B channel delta */
                    if (flags & 0x04) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.b;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.b = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.b;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.b = (u8) (s32) val;
                        }
                    }

                    /* A channel delta (separate random) */
                    if (flags & 0x08) {
                        f32 a_rand;
                        a_rand = HSD_Randf();
                        delta = (s8) *pc++;
                        delta_float =
                            (f32) (s32) ((f32) (timing + 1) * a_rand) /
                            (f32) timing * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.a;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.a = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.a;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.a = (u8) (s32) val;
                        }
                    }

                    /* Final: sync current from target if count is 0 */
                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    }
                    pp->primColRemain = pp->primColCount;
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    }
                    pp->envColRemain = pp->envColCount;
                }
                break;

            case 0xE1:
                /* Callback set */
                {
                    int idx = *pc++;
                    if (idx == 0) {
                        pp->callback = NULL;
                    } else {
                        pp->callback = psCallback[idx - 1];
                    }
                }
                break;

            case 0xEC:
                /* UserData set */
                {
                    int idx = *pc++;
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    if (pp->gen->userfunc != NULL &&
                        pp->gen->userfunc->setUserData != NULL)
                    {
                        pp->gen->userfunc->setUserData(pp, idx, fval);
                    } else if (pp->userdata != NULL) {
                        pp->userdata[idx] = fval;
                    }
                }
                break;

            case 0xE2:
                /* Set TexEdge (kill) bit */
                pp->kind |= TexEdge;
                break;

            case 0xE3:
                /* Set palNum */
                pp->palNum = *pc++;
                break;

            case 0xE4:
                /* TexFlipS control */
                {
                    u8 mode = *pc++ & 0x3;
                    switch (mode) {
                    case 0:
                        pp->kind &= ~TexFlipS;
                        break;
                    case 1:
                        pp->kind |= TexFlipS;
                        break;
                    case 2:
                        pp->kind ^= TexFlipS;
                        break;
                    case 3:
                        if (HSD_Randf() < 0.5F) {
                            pp->kind &= ~TexFlipS;
                        } else {
                            pp->kind |= TexFlipS;
                        }
                        break;
                    }
                }
                break;

            case 0xE5:
                /* TexFlipT control */
                {
                    u8 mode = *pc++ & 0x3;
                    switch (mode) {
                    case 0:
                        pp->kind &= ~TexFlipT;
                        break;
                    case 1:
                        pp->kind |= TexFlipT;
                        break;
                    case 2:
                        pp->kind ^= TexFlipT;
                        break;
                    case 3:
                        if (HSD_Randf() < 0.5F) {
                            pp->kind &= ~TexFlipT;
                        } else {
                            pp->kind |= TexFlipT;
                        }
                        break;
                    }
                }
                break;

            case 0xE6:
                /* Set DirVec */
                pp->kind |= DirVec;
                break;

            case 0xE7:
                /* Clear DirVec */
                pp->kind &= ~DirVec;
                break;

            case 0xE8:
                /* Trail control */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                if (fval < 0.0F) {
                    pp->kind &= ~Trail;
                } else {
                    pp->kind |= Trail;
                    pp->trail = fval;
                }
                break;

            case 0xEA:
                /* MatCol interpolation setup */
                {
                    s32 step;
                    u16 cnt;
                    u8 flags;

                    if (pp->matColCount != 0) {
                        step = ((s32) pp->matColRemain << 16) /
                               (s32) pp->matColCount;
                        pp->matRGB = (u8) ((((s32) pp->matRGBTarget << 16) +
                                            step * ((s32) pp->matRGB -
                                                    (s32) pp->matRGBTarget)) >>
                                           16);
                        pp->matA = (u8) ((((s32) pp->matATarget << 16) +
                                          step * ((s32) pp->matA -
                                                  (s32) pp->matATarget)) >>
                                         16);
                    }
                    pp->matColCount = *pc++;
                    cnt = pp->matColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->matColCount = cnt;
                    }
                    flags = *pc++;
                    pp->matRGBTarget = pp->matRGB;
                    if (flags & 1) {
                        pp->matRGBTarget = *pc++;
                    }
                    if (flags & 8) {
                        pp->matATarget = *pc++;
                    }
                    if (pp->matColCount == 0) {
                        pp->matRGB = pp->matRGBTarget;
                        pp->matColRemain = 0;
                    } else {
                        pp->matColRemain = pp->matColCount;
                    }
                }
                break;

            case 0xEB:
                /* AmbCol interpolation setup */
                {
                    s32 step;
                    u16 cnt;
                    u8 flags;

                    if (pp->ambColCount != 0) {
                        step = ((s32) pp->ambColRemain << 16) /
                               (s32) pp->ambColCount;
                        pp->ambRGB = (u8) ((((s32) pp->ambRGBTarget << 16) +
                                            step * ((s32) pp->ambRGB -
                                                    (s32) pp->ambRGBTarget)) >>
                                           16);
                        pp->ambA = (u8) ((((s32) pp->ambATarget << 16) +
                                          step * ((s32) pp->ambA -
                                                  (s32) pp->ambATarget)) >>
                                         16);
                    }
                    pp->ambColCount = *pc++;
                    cnt = pp->ambColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->ambColCount = cnt;
                    }
                    flags = *pc++;
                    pp->ambRGBTarget = pp->ambRGB;
                    if (flags & 1) {
                        pp->ambRGBTarget = *pc++;
                    }
                    if (flags & 8) {
                        pp->ambATarget = *pc++;
                    }
                    if (pp->ambColCount == 0) {
                        pp->ambRGB = pp->ambRGBTarget;
                        pp->ambColRemain = 0;
                    } else {
                        pp->ambColRemain = pp->ambColCount;
                    }
                }
                break;

            case 0xED:
                /* Rotate interpolation with random */
                {
                    f32 base_val;
                    f32 range_val;
                    int timing;
                    f32 result;

                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    base_val = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    range_val = fval;
                    timing = pc[8];
                    pc += 9;

                    if (timing != 0) {
                        s32 randi = (s32) ((f32) (timing + 1) * HSD_Randf());
                        result =
                            base_val + range_val * (f32) randi / (f32) timing;
                    } else {
                        result = base_val + range_val * HSD_Randf();
                    }
                    pp->rotateTarget += result;
                    pp->rotate += result;
                }
                break;

            case 0xFA:
                /* Loop mark */
                pp->loopCount = *pc++;
                pp->cmdLoopPtr = (u16) (pc - pp->cmdList);
                break;

            case 0xFB:
                /* Loop back */
                if (--pp->loopCount != 0) {
                    pc = pp->cmdList + pp->cmdLoopPtr;
                }
                break;

            case 0xFC:
                /* Mark set */
                pp->cmdMarkPtr = (u16) (pc - pp->cmdList);
                break;

            case 0xFD:
                /* Mark jump */
                pc = pp->cmdList + pp->cmdMarkPtr;
                break;

            case 0xFE:
            case 0xFF:
                /* End: set life to 1 */
                pp->life = 1;
                goto exit_loop;

            default:
                break;
            }
        }

        /* Loop continuation check */
        if (operand != 0) {
            break;
        }
    }

exit_loop:
    /* Save bytecode state */
    pp->cmdPtr = (u16) (pc - pp->cmdList);
    pp->cmdWait = operand;

do_life:
    /* Life countdown */
    if (--pp->life == 0) {
        /* Call hookDelete if available */
        if (pp->gen != NULL && pp->gen->userfunc != NULL &&
            pp->gen->userfunc->hookDelete != NULL)
        {
            pp->gen->userfunc->hookDelete(pp);
        }

        /* Unlink from list */
        if (prev == NULL) {
            hsd_804D0908[pp->linkNo] = pp->next;
        } else {
            prev->next = pp->next;
        }

        /* Decrement generator child count */
        {
            HSD_Particle* next_pp = pp->next;
            if (pp->gen != NULL) {
                pp->gen->numChild--;
            }

            /* Free appsrt */
            if (pp->appsrt != NULL) {
                if (psRemoveParticleAppSRT(pp) == 0 && prev == NULL) {
                    HSD_Particle* head = hsd_804D0908[pp->linkNo];
                    if (head != next_pp) {
                        next_pp = head;
                    }
                }
            }

            /* Free particle */
            hsd_8039D048(pp);
            HSD_ObjFree(&hsd_804D0F60.alloc_data, pp);
            numActiveParticles--;
            return next_pp;
        }
    }

    /* --- Physics update --- */
    if (pp->kind & Tornado) {
        /* Tornado rotational physics */
        HSD_Generator* gp = pp->gen;
        f32 sinA, sinB, cosA, cosB;
        f32 R;
        f32 d, e, nd, vz;
        f32 t0, t1, t2, t3, t4;

        sinA = sinf(pp->grav);
        sinB = sinf(pp->fric);
        cosA = cosf(pp->grav);
        cosB = cosf(pp->fric);

        pp->vel.z += gp->aux.tornado.vel;

        R = gp->radius;
        if (R < 0.0F) {
            R = -R;
        }
        {
            f32 ang = gp->angle;
            if (ang < 0.0F) {
                ang = -ang;
            }
            R = pp->vel.z * tanf(ang) + R;
        }
        pp->vel.x += gp->grav;
        R *= pp->vel.y;

        d = R * cosf(pp->vel.x);
        e = R * sinf(pp->vel.x);
        nd = -d;
        vz = pp->vel.z;

        /* Rotation matrix application */
        t0 = vz * sinB;
        t1 = e * cosA;
        t2 = nd * sinA;
        t3 = d * cosB + t0;
        t0 = vz * sinA;
        t1 = sinB * t2 + t1;
        pp->pos.x = gp->pos.x + t3;
        t2 = nd * cosA;
        t4 = e * sinA;
        t1 = cosB * t0 + t1;
        t0 = vz * cosA;
        t4 = sinB * t2 - t4;
        pp->pos.y = gp->pos.y + t1;
        t4 = cosB * t0 + t4;
        pp->pos.z = gp->pos.z + t4;
    } else {
        /* Simple physics */
        if (pp->kind & 1) {
            pp->vel.y -= pp->grav;
        }
        if (pp->kind & 2) {
            pp->vel.x *= pp->fric;
            pp->vel.y *= pp->fric;
            pp->vel.z *= pp->fric;
        }
        pp->pos.x += pp->vel.x;
        pp->pos.y += pp->vel.y;
        pp->pos.z += pp->vel.z;
    }

    /* JObj attachment - update JObj position to match particle */
    if (pp->kind & 0x8000) {
        s32 jobj_idx = (pp->kind >> 12) & 7;
        HSD_JObj* jobj;
        HSD_JObj** jobj_slot;

        /* Allocate JObj if slot is empty */
        if (hsd_804D08E8[jobj_idx] == NULL) {
            HSD_JObj* new_jobj = HSD_JObjAlloc();
            if (new_jobj != NULL) {
                hsd_8039CF4C(jobj_idx + 1, new_jobj);
                HSD_JObjUnref(new_jobj);
            }
        }

        jobj_slot = &hsd_804D08E8[jobj_idx];
        jobj = *jobj_slot;

        if (jobj != NULL) {
            HSD_JObjSetupMatrix(jobj);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationX(jobj, pp->pos.x - jobj->mtx[0][3]);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationY(jobj, pp->pos.y - jobj->mtx[1][3]);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationZ(jobj, pp->pos.z - jobj->mtx[2][3]);
        }
    }

    /* Callback */
    if (pp->callback != NULL) {
        int result = pp->callback(pp);
        if (result == -1) {
            goto do_life;
        }
    }

    return pp->next;
#undef fbytes
#undef fval
}

void hsd_8039CEAC(u32 mask)
{
    void* cur;
    void* prev;
    s32 i;
    u32 bits;
    void* next;

    bits = mask;
    for (i = 0; i < 16; i++) {
        if (!(bits & 0x10000)) {
            cur = hsd_804D0908[i];
            prev = NULL;
            while (cur != NULL) {
                next = hsd_8039930C(cur, prev);
                if (prev == NULL) {
                    if (hsd_804D0908[i] != next) {
                        prev = cur;
                    }
                } else {
                    if (next != *(void**) prev) {
                        prev = cur;
                    }
                }
                cur = next;
            }
        }
        bits >>= 1;
    }
}

void hsd_8039CF4C(s32 index, HSD_JObj* jobj)
{
    if (index < 0 || index > 8) {
        return;
    }

    if (index != 0) {
        HSD_JObj** p = hsd_804D08E8;
        HSD_JObj* old;
        p += index;
        old = *--p;
        if (old != jobj) {
            if (old != NULL) {
                HSD_JObjUnref(jobj);
            }
            *p = jobj;
            ref_INC(jobj);
        }
    } else {
        s32 i;
        for (i = 0; i < 8; i++) {
            if (hsd_804D08E8[i] == jobj) {
                HSD_JObjUnref(hsd_804D08E8[i]);
                hsd_804D08E8[i] = NULL;
            }
        }
    }
}

void hsd_8039D048(void* particle)
{
    u32 flags = ((HSD_Particle*) particle)->kind;
    if (flags & 0x8000) {
        HSD_JObj** p = &hsd_804D08E8[(flags >> 12) & 7];
        if (*p != NULL) {
            HSD_JObjUnref(*p);
            *p = NULL;
        }
    }
}

// @TODO: Currently 95.10% match - lwzu vs lwz+addi addressing, lwzx vs add+lwz
void hsd_8039D0A0(HSD_Generator* gen)
{
    HSD_Particle* prev;
    HSD_Particle* prt;
    HSD_Particle* next;
    HSD_Particle** head;
    HSD_JObj** jobj_base;
    s8* base;
    u16 idnum;

    prev = NULL;
    base = (s8*) hsd_804D08E8;
    idnum = gen->idnum;
    head = (HSD_Particle**) (base + gen->linkNo * 4);
    jobj_base = (HSD_JObj**) base;
    prt = head[8];
    head = (HSD_Particle**) ((u32) head + 0x20);

    while (prt != NULL) {
        next = prt->next;
        if (prt->idnum == idnum && prt->gen != NULL && prt->gen == gen) {
            if (prt->gen != NULL && prt->gen->userfunc != NULL &&
                prt->gen->userfunc->hookDelete != NULL)
            {
                prt->gen->userfunc->hookDelete(prt);
            }

            if (prev == NULL) {
                *head = prt->next;
            } else {
                prev->next = prt->next;
            }

            if (prt->gen != NULL) {
                prt->gen->numChild--;
            }

            if (prt->appsrt != NULL) {
                psRemoveParticleAppSRT(prt);
            }

            if (prt->kind & 0x8000) {
                s32 jidx = (prt->kind >> 12) & 7;
                if (jobj_base[jidx] != NULL) {
                    HSD_JObjUnref(jobj_base[jidx]);
                    jobj_base[jidx] = NULL;
                }
            }

            HSD_ObjFree((HSD_ObjAllocData*) (base + 0x20), prt);
            hsd_804D78E2--;
        } else {
            prev = prt;
        }
        prt = next;
    }
}

static u16 lbl_804D6368 = 0x100;

void hsd_8039D1E4(HSD_Generator* gen, void* userfunc)
{
    gen->userfunc = userfunc;
}

u16 hsd_8039D1EC(void)
{
    lbl_804D6368++;
    if (lbl_804D6368 < 256) {
        lbl_804D6368 = 256;
    }
    return lbl_804D6368;
}

void hsd_8039D214(HSD_Generator* gen)
{
    HSD_JObj* jobj;

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }
}

void hsd_8039D354(u32 unused)
{
    HSD_ObjAllocInit(&hsd_804D0F90.alloc_data, 0x94, 4);
    hsd_804D78FC = NULL;
    hsd_804D78E0 = 0;
    hsd_804D78DA = 0;
    hsd_804D78F4 = 0;
    hsd_804D78F0 = 0;
    hsd_804D78E8 = 0;
    hsd_804D78EC = 0;
    hsd_804D78F8 = 0;
    hsd_804D7900 = 0;
}

HSD_Generator* hsd_8039D3AC(HSD_Generator* gen, HSD_Generator* prev)
{
    if (gen->type & 0x80) {
        hsd_8039D0A0(gen);
    }
    if (gen->numChild != 0) {
        gen->random = 0.0F;
        gen->genLife = 1;
        return gen;
    }
    if (gen->type & 0x100) {
        if (gen->jobj != NULL) {
            if (gen->type & 0x1800) {
                HSD_psAppSRT* srt = gen->appsrt;
                if (srt != NULL) {
                    if (srt->gp == gen) {
                        if (srt->usedCount != 1) {
                            gen->random = 0.0F;
                            gen->genLife = 1;
                            return gen;
                        }
                    }
                }
            }
        }
    }
    if (prev == NULL) {
        hsd_804D78FC = gen->next;
    } else {
        prev->next = gen->next;
    }
    if (gen->appsrt != NULL) {
        psRemoveGeneratorSRT(gen);
    }
    if (gen->jobj != NULL) {
        HSD_JObjUnref(gen->jobj);
        gen->jobj = NULL;
    }
    HSD_ObjFree(&hsd_804D0F90.alloc_data, gen);
    hsd_804D78E0--;
    return prev;
}

void hsd_8039D4DC(HSD_Generator* gen)
{
    HSD_Generator* cur;

    cur = hsd_804D78FC;
    hsd_804D78F8 = 0;
    while (cur != NULL) {
        if (cur == gen) {
            hsd_804D78F8 =
                (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
            if (hsd_804D78F8 != 0) {
                while (((HSD_Generator*) hsd_804D78F8)->next != NULL) {
                    hsd_804D78F8 = (u32) ((HSD_Generator*) hsd_804D78F8)->next;
                }
            } else if (hsd_804D78FC != NULL) {
                hsd_804D78F8 = (u32) hsd_804D78FC;
                while (((HSD_Generator*) hsd_804D78F8)->next != NULL) {
                    hsd_804D78F8 = (u32) ((HSD_Generator*) hsd_804D78F8)->next;
                }
            }
            return;
        }
        hsd_804D78F8 = (u32) cur;
        cur = cur->next;
    }
}

void hsd_8039D580(HSD_JObj* jobj)
{
    HSD_Generator* next;
    HSD_Generator* cur;

    if (jobj != NULL) {
        cur = hsd_804D78FC;
        while (cur != NULL) {
            next = cur->next;
            if (cur->jobj == jobj) {
                hsd_8039D4DC(cur);
            }
            cur = next;
        }
    }
}

void hsd_8039D5DC(HSD_JObj* jobj)
{
    HSD_Generator* next;
    HSD_Generator* gen;

    if (jobj == NULL) {
        return;
    }
    gen = hsd_804D78FC;
    while (gen != NULL) {
        next = gen->next;
        if (gen->jobj == jobj) {
            hsd_8039D4DC(gen);
        }
        gen = next;
    }
    if (jobj->flags & 0x1000) {
        return;
    }
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        hsd_8039D5DC(jobj);
        jobj = jobj == NULL ? NULL : jobj->next;
    }
}

void hsd_8039D688(HSD_JObj* jobj, f32** unused1, s32 unused2)
{
    HSD_Generator* next;
    HSD_Generator* gen;

    gen = hsd_804D78FC;
    hsd_804D78F8 = 0;
    while (gen != NULL) {
        next = gen->next;
        if (gen->jobj == jobj) {
            if (gen->appsrt != NULL) {
                u16 type = gen->type;
                if (type & 0x100) {
                    gen->type = type | 0x80;
                }
            }
            hsd_804D78F8 =
                (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
        } else {
            hsd_804D78F8 = (u32) gen;
        }
        gen = next;
    }
}

void hsd_8039D71C(HSD_Generator* gen)
{
    HSD_JObj* jobj;
    Mtx mtx;
    Vec3 col;
    f32 col0_x, col0_y, col0_z;
    f32 col1_x, col1_y, col1_z;
    PAD_STACK(12);

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }

    col.x = jobj->mtx[0][0];
    col.y = jobj->mtx[1][0];
    col.z = jobj->mtx[2][0];
    PSVECNormalize(&col, &col);
    col0_x = col.x;
    col0_y = col.y;
    col0_z = col.z;

    col.x = jobj->mtx[0][1];
    col.y = jobj->mtx[1][1];
    col.z = jobj->mtx[2][1];
    PSVECNormalize(&col, &col);
    col1_x = col.x;
    col1_y = col.y;
    col1_z = col.z;

    col.x = jobj->mtx[0][2];
    col.y = jobj->mtx[1][2];
    col.z = jobj->mtx[2][2];
    PSVECNormalize(&col, &col);

    {
        f32 cx = col.x;
        f32 cy = col.y;
        f32 cz = col.z;
        f32 vx = gen->vel.x;
        f32 vy = gen->vel.y;
        f32 vz = gen->vel.z;
        gen->vel.x = col0_x * vx + col1_x * vy + cx * vz;
        gen->vel.y = col0_y * vx + col1_y * vy + cy * vz;
        gen->vel.z = col0_z * vx + col1_z * vy + cz * vz;
    }

    if ((gen->type & 0xF) == 1) {
        f32 ax = gen->aux.line.x2;
        f32 ay = gen->aux.line.y2;
        f32 az = gen->aux.line.z2;
        gen->aux.line.x2 =
            jobj->mtx[0][0] * ax + jobj->mtx[0][1] * ay + jobj->mtx[0][2] * az;
        gen->aux.line.y2 =
            jobj->mtx[1][0] * ax + jobj->mtx[1][1] * ay + jobj->mtx[1][2] * az;
        gen->aux.line.z2 =
            jobj->mtx[2][0] * ax + jobj->mtx[2][1] * ay + jobj->mtx[2][2] * az;
    }
}

HSD_Generator* hsd_8039D9C8(void)
{
    HSD_Generator* gen;
    PAD_STACK(8);

    gen = HSD_ObjAlloc(&hsd_804D0F90.alloc_data);
    if (gen != NULL) {
        memset(gen, 0, 0x94);
    }
    if (gen == NULL) {
        return NULL;
    }

    hsd_804D78E0++;
    if (hsd_804D78E0 > hsd_804D78DA) {
        hsd_804D78DA = hsd_804D78E0;
    }

    if ((HSD_Generator*) hsd_804D78F8 == NULL ||
        ((HSD_Generator*) hsd_804D78F8)->next == NULL)
    {
        if (hsd_804D78FC == NULL) {
            gen->next = NULL;
            hsd_804D78FC = gen;
        } else {
            gen->next = hsd_804D78FC->next;
            hsd_804D78FC->next = gen;
        }
    } else {
        gen->next = ((HSD_Generator*) hsd_804D78F8)->next->next;
        ((HSD_Generator*) hsd_804D78F8)->next->next = gen;
    }

    lbl_804D6368++;
    if (lbl_804D6368 < 0x100) {
        lbl_804D6368 = 0x100;
    }
    gen->idnum = lbl_804D6368;
    gen->appsrt = NULL;
    gen->userfunc = NULL;
    return gen;
}

// @TODO: Currently 86.32% match - register allocation, shape/velocity
// switch case logic, Newton-Raphson sqrt inlining, trig matrix layout
f32 hsd_8039DAD4(HSD_Generator* gen)
{
    Mtx rot_mtx;
    Vec3 vel_out;
    Vec3 tmpvec;
    Vec3 emit_pos;
    Vec3 vel_copy;
    Mtx jobj_mtx;
    Vec3 look_dir;
    Vec3 cam_up;
    Vec3 cross1;
    Vec3 vel_norm;
    Mtx trig_mtx;
    f64 eps;
    f32 vel_mag_sq;
    f32 angle1;
    f32 sin_az;
    f32 cos_az;
    f32 sin_el;
    f32 angle_step;
    f32 cur_angle;
    f32 radius;
    f32 cone_angle;
    f32 elevation;
    f32 tmp;
    f32 angle3;
    PAD_STACK(16);

    angle3 = 0.0F;
    vel_mag_sq = angle3;

    if (gen->count < 0.0F) {
        return gen->count;
    }

    /* Copy velocity */
    vel_copy.x = gen->vel.x;
    vel_copy.y = gen->vel.y;
    vel_copy.z = gen->vel.z;

    /* Compute velocity magnitude */
    vel_mag_sq = vel_copy.x * vel_copy.x + vel_copy.y * vel_copy.y +
                 vel_copy.z * vel_copy.z;
    if (vel_mag_sq > 0.0F) {
        f64 e = __frsqrte(vel_mag_sq);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        vel_mag_sq = (f32) (vel_mag_sq * e);
    }

    /* Initialize rotation matrix */
    PSMTXIdentity(rot_mtx);

    /* JObj-based rotation: type & 0x100 and jobj!=NULL and type & 0x400
       and !(kind & 0x3C000) */
    if ((gen->type & 0x100) && gen->jobj != NULL && (gen->type & 0x400) &&
        !(gen->kind & 0x30000))
    {
        PSMTXCopy((void*) ((u8*) gen->jobj + 0x44), jobj_mtx);

        /* Extract and normalize each column of the 3x3 rotation */
        tmpvec.x = jobj_mtx[0][0];
        tmpvec.y = jobj_mtx[1][0];
        tmpvec.z = jobj_mtx[2][0];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][0] = tmpvec.x;
        rot_mtx[1][0] = tmpvec.y;
        rot_mtx[2][0] = tmpvec.z;

        tmpvec.x = jobj_mtx[0][1];
        tmpvec.y = jobj_mtx[1][1];
        tmpvec.z = jobj_mtx[2][1];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][1] = tmpvec.x;
        rot_mtx[1][1] = tmpvec.y;
        rot_mtx[2][1] = tmpvec.z;

        tmpvec.x = jobj_mtx[0][2];
        tmpvec.y = jobj_mtx[1][2];
        tmpvec.z = jobj_mtx[2][2];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][2] = tmpvec.x;
        rot_mtx[1][2] = tmpvec.y;
        rot_mtx[2][2] = tmpvec.z;

        rot_mtx[0][3] = 0.0F;
        rot_mtx[1][3] = 0.0F;
        rot_mtx[2][3] = 0.0F;
    }

    /* Billboard orientation: kind & 0x10000 */
    if (gen->kind & 0x10000) {
        HSD_ASSERT(677, hsd_804D78F0);
        {
            HSD_CObj* cobj = (HSD_CObj*) hsd_804D78F0;
            void* view = *(void**) ((u8*) cobj + 0x24);
            look_dir.x = *(f32*) ((u8*) view + 0x0C) - gen->pos.x;
            view = *(void**) ((u8*) cobj + 0x24);
            look_dir.y = *(f32*) ((u8*) view + 0x10) - gen->pos.y;
            view = *(void**) ((u8*) cobj + 0x24);
            look_dir.z = *(f32*) ((u8*) view + 0x14) - gen->pos.z;
        }
        PSVECNormalize(&look_dir, &look_dir);
        HSD_CObjGetUpVector((HSD_CObj*) hsd_804D78F0, &cam_up);
        PSVECNormalize(&cam_up, &cam_up);
        PSVECCrossProduct(&cam_up, &look_dir, &cross1);
        PSVECCrossProduct(&look_dir, &cross1, &cam_up);

        rot_mtx[0][0] = cross1.x;
        rot_mtx[1][0] = cross1.y;
        rot_mtx[2][0] = cross1.z;
        rot_mtx[0][1] = cam_up.x;
        rot_mtx[1][1] = cam_up.y;
        rot_mtx[2][1] = cam_up.z;
        rot_mtx[0][2] = look_dir.x;
        rot_mtx[1][2] = look_dir.y;
        rot_mtx[2][2] = look_dir.z;
    }

    /* Velocity-based rotation */
    if ((gen->type & 0xF) != 1 && vel_mag_sq > 0.0F) {
        vel_norm.x = gen->vel.x;
        vel_norm.y = gen->vel.y;
        vel_norm.z = gen->vel.z;
        PSVECNormalize(&vel_norm, &vel_norm);

        tmp = vel_norm.z;
        *(s32*) &tmp &= 0x7FFFFFFF;
        if (tmp < 1.1754944e-38F) {
            if (vel_norm.y >= 0.0F) {
                sin_az = 1.5707964F;
            } else {
                sin_az = -1.5707964F;
            }
        } else {
            sin_az = atan2f(vel_norm.y, vel_norm.z);
        }
        cos_az = sinf(sin_az);
        sin_az = cosf(sin_az);

        tmp = vel_norm.z * sin_az + vel_norm.y * cos_az;
        *(s32*) &tmp &= 0x7FFFFFFF;
        if (tmp < 1.1754944e-38F) {
            if (vel_norm.x >= 0.0F) {
                elevation = 1.5707964F;
            } else {
                elevation = -1.5707964F;
            }
        } else {
            elevation =
                atan2f(vel_norm.x, vel_norm.z * sin_az + vel_norm.y * cos_az);
        }
        sin_el = sinf(elevation);
        {
            f32 cos_el = cosf(elevation);
            f32 neg_cos_az = -cos_az;
            f32 neg_sin_az_s = -sin_az;

            trig_mtx[0][0] = cos_el;
            trig_mtx[0][1] = 0.0F;
            trig_mtx[0][2] = sin_el;
            trig_mtx[0][3] = 0.0F;
            trig_mtx[1][0] = neg_cos_az * sin_el;
            trig_mtx[1][1] = sin_az;
            trig_mtx[1][2] = cos_az * cos_el;
            trig_mtx[1][3] = 0.0F;
            trig_mtx[2][0] = neg_sin_az_s * sin_el;
            trig_mtx[2][1] = neg_cos_az;
            trig_mtx[2][2] = sin_az * cos_el;
            trig_mtx[2][3] = 0.0F;
        }
        PSMTXConcat(rot_mtx, trig_mtx, rot_mtx);
    }

    /* Type 2: extract Euler angles from rotation matrix */
    if ((gen->type & 0xF) == 2) {
        tmp = rot_mtx[2][2];
        *(s32*) &tmp &= 0x7FFFFFFF;
        if (tmp < 1.1754944e-38F) {
            if (rot_mtx[1][2] >= 0.0F) {
                angle1 = 1.5707964F;
            } else {
                angle1 = -1.5707964F;
            }
        } else {
            angle1 = atan2f(rot_mtx[1][2], rot_mtx[2][2]);
        }
        {
            f32 c1 = cosf(angle1);
            f32 s1 = sinf(angle1);
            f32 comb = rot_mtx[2][2] * c1 + rot_mtx[1][2] * s1;
            *(s32*) &comb &= 0x7FFFFFFF;
            if (comb < 1.1754944e-38F) {
                if (rot_mtx[0][2] >= 0.0F) {
                    angle3 = 1.5707964F;
                } else {
                    angle3 = -1.5707964F;
                }
            } else {
                angle3 = atan2f(rot_mtx[0][2],
                                rot_mtx[2][2] * c1 + rot_mtx[1][2] * s1);
            }
        }
    }

    /* Angle step computation (pre-loop) */
    if (gen->angle < 0.0F) {
        switch (gen->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            f32 min_a = gen->aux.disc.minAngle;
            f32 rnd = HSD_Randf();
            f32 range = gen->aux.disc.maxAngle - min_a;
            angle_step = range / (f32) (s32) gen->count;
            cur_angle = angle_step * rnd + min_a;
            break;
        }
        case 6:
        case 7: {
            f32 min_a = gen->aux.cone.minAngle;
            f32 rnd = HSD_Randf();
            f32 range = gen->aux.cone.maxAngle - min_a;
            angle_step = range / (f32) (s32) gen->count;
            cur_angle = angle_step * rnd + min_a;
            break;
        }
        default: {
            f32 rnd = HSD_Randf();
            cur_angle = (f32) ((f64) 6.2831855F * (f64) rnd);
            angle_step =
                (f32) ((f64) 6.2831855F / (f64) (f32) (s32) gen->count);
            break;
        }
        }
    }

    /* Main particle emission loop */
    eps = 1e-10;
    while (gen->count >= 1.0F) {
        switch (gen->type & 0xF) {
        case 0: /* point, disc, cone, sphere, etc. */
        case 3:
        case 4:
        case 6:
        case 7: {
            /* Compute radius */
            if (gen->radius < 0.0F) {
                sin_az = -gen->radius;
                radius = 0.0F;
            } else {
                radius = HSD_Randf();
                if ((gen->type & 0xF) == 3 || (gen->type & 0xF) == 4) {
                    if (radius > 0.0F) {
                        f64 e = __frsqrte(radius);
                        e = 0.5 * e * -(radius * (e * e) - 3.0);
                        e = 0.5 * e * -(radius * (e * e) - 3.0);
                        e = 0.5 * e * -(radius * (e * e) - 3.0);
                        radius = (f32) (radius * e);
                    }
                }
                sin_az = radius * gen->radius;
            }

            /* Compute emission angle per shape */
            if ((gen->type & 0xF) == 6) {
                /* Cone/sphere shape 6 */
                if (gen->angle < 0.0F) {
                    emit_pos.z = sin_az;
                    cur_angle += angle_step;
                    tmp = sin_az;
                    *(s32*) &tmp &= 0x7FFFFFFF;
                    if (tmp < 1.1754944e-38F) {
                        if (gen->aux.cone.height >= 0.0F) {
                            cone_angle = -gen->angle;
                        } else {
                            cone_angle = (f32) (M_PI - gen->angle);
                        }
                    } else {
                        cone_angle = (f32) (M_PI - atan2f(gen->aux.cone.height,
                                                          sin_az)) -
                                     gen->angle;
                    }
                } else {
                    cur_angle = gen->aux.cone.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.cone.maxAngle - cur_angle;
                        cone_angle = radius * gen->angle;
                        cur_angle = range * rnd + cur_angle;
                    }
                    emit_pos.z = sin_az;
                    tmp = sin_az;
                    *(s32*) &tmp &= 0x7FFFFFFF;
                    if (tmp < 1.1754944e-38F) {
                        if (gen->aux.cone.height >= 0.0F) {
                            cone_angle = gen->angle;
                        } else {
                            cone_angle = (f32) (M_PI + gen->angle);
                        }
                    } else {
                        cone_angle = gen->angle +
                                     (f32) (M_PI - atan2f(gen->aux.cone.height,
                                                          sin_az));
                    }
                }
            } else if ((gen->type & 0xF) == 7) {
                /* Shape 7 */
                if (gen->angle < 0.0F) {
                    cone_angle = (f32) (M_PI - gen->angle);
                    cur_angle += angle_step;
                } else {
                    cur_angle = gen->aux.disc.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.disc.maxAngle - cur_angle;
                        cone_angle = (f32) (M_PI + gen->angle);
                        cur_angle = range * rnd + cur_angle;
                    }
                }
            } else {
                /* Shapes 0, 3, 4 */
                if (gen->angle < 0.0F) {
                    cone_angle = -gen->angle;
                    cur_angle += angle_step;
                    cone_angle = radius * cone_angle;
                } else {
                    cur_angle = gen->aux.disc.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.disc.maxAngle - cur_angle;
                        cone_angle = radius * gen->angle;
                        cur_angle = range * rnd + cur_angle;
                    }
                }
            }

            /* Compute emission position and velocity from angle */
            {
                f32 cos_a = cosf(cur_angle);
                f32 sin_a = sinf(cur_angle);
                emit_pos.x = sin_az * cos_a;
                emit_pos.y = sin_az * sin_a;
            }

            /* Shape 6,7: z from random, scale by height */
            if ((gen->type & 0xF) == 6 || (gen->type & 0xF) == 7) {
                f32 rnd = HSD_Randf();
                emit_pos.z = rnd;
                if ((gen->type & 0xF) == 6) {
                    emit_pos.x *= (1.0F - rnd);
                    emit_pos.y *= (1.0F - rnd);
                }
                emit_pos.z *= gen->aux.cone.height;
            } else {
                emit_pos.z = 0.0F;
            }

            /* Compute velocity direction from cone angle */
            {
                f32 sin_ca = vel_mag_sq * sinf(cone_angle);
                vel_out.x = sin_ca * cosf(cur_angle);
                vel_out.y = sin_ca * sinf(cur_angle);
                vel_out.z = vel_mag_sq * cosf(cone_angle);
            }

            /* Shape 3: scale velocity by radius factor */
            if ((gen->type & 0xF) == 3) {
                vel_out.x *= radius;
                vel_out.y *= radius;
                vel_out.z *= radius;
            }

            /* Apply rotation matrix to emission position */
            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            /* Apply rotation matrix to velocity */
            PSMTXMultVec(rot_mtx, &vel_out, &vel_out);

            /* Spawn particle */
            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 1: /* line */
        {
            f32 rnd = HSD_Randf();
            emit_pos.x = rnd * gen->aux.line.x2;
            emit_pos.y = rnd * gen->aux.line.y2;
            emit_pos.z = rnd * gen->aux.line.z2;

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            PSMTXMultVec(rot_mtx, &vel_copy, &vel_out);

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 2: /* tornado */
        {
            if (gen->radius < 0.0F) {
                sin_az = 0.0F;
            } else {
                sin_az = HSD_Randf();
            }
            if (gen->angle < 0.0F) {
                cur_angle += angle_step;
            } else {
                f32 rnd = HSD_Randf();
                cur_angle = (f32) (M_TAU * (f64) rnd);
            }
            gen->aux.line.x2 = vel_mag_sq;
            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind | 4, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen, 0.0F,
                         0.0F, 0.0F, cur_angle, sin_az, 0.0F, gen->size,
                         angle1, angle3);
            break;
        }

        case 5: /* rect */
        {
            Vec3 vel_temp;
            f32 rx = HSD_Randf();
            f32 ry = HSD_Randf();
            f32 rz = HSD_Randf();
            emit_pos.x = rx;
            emit_pos.y = ry;
            emit_pos.z = rz;

            switch (gen->aux.rect.flag) {
            case 0: /* default: no modification */
                break;
            case 1: /* +x */
                if (emit_pos.x > 0.5F) {
                    emit_pos.x = 1.0F;
                } else {
                    emit_pos.x = 0.0F;
                }
                break;
            case 2: /* +y */
                if (emit_pos.y > 0.5F) {
                    emit_pos.y = 1.0F;
                } else {
                    emit_pos.y = 0.0F;
                }
                break;
            case 3: /* xy split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.x;
                f32 b2 = gen->aux.rect.y;
                if (rnd < a2 / (a2 + b2)) {
                    if (emit_pos.y > 0.5F) {
                        emit_pos.y = 1.0F;
                    } else {
                        emit_pos.y = 0.0F;
                    }
                } else {
                    if (emit_pos.x > 0.5F) {
                        emit_pos.x = 1.0F;
                    } else {
                        emit_pos.x = 0.0F;
                    }
                }
                break;
            }
            case 4: /* +z */
                if (emit_pos.z > 0.5F) {
                    emit_pos.z = 1.0F;
                } else {
                    emit_pos.z = 0.0F;
                }
                break;
            case 5: /* xz split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.x;
                f32 b2 = gen->aux.rect.z;
                if (rnd < a2 / (a2 + b2)) {
                    if (emit_pos.z > 0.5F) {
                        emit_pos.z = 1.0F;
                    } else {
                        emit_pos.z = 0.0F;
                    }
                } else {
                    if (emit_pos.x > 0.5F) {
                        emit_pos.x = 1.0F;
                    } else {
                        emit_pos.x = 0.0F;
                    }
                }
                break;
            }
            case 6: /* yz split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.y;
                f32 b2 = gen->aux.rect.z;
                if (rnd < a2 / (a2 + b2)) {
                    if (emit_pos.z > 0.5F) {
                        emit_pos.z = 1.0F;
                    } else {
                        emit_pos.z = 0.0F;
                    }
                } else {
                    if (emit_pos.y > 0.5F) {
                        emit_pos.y = 1.0F;
                    } else {
                        emit_pos.y = 0.0F;
                    }
                }
                break;
            }
            case 7: /* 3-way split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.z;
                f32 b2 = gen->aux.rect.y;
                f32 c2 = gen->aux.rect.x;
                f32 ab = b2 * a2;
                f32 ca = c2 * b2;
                f32 total = c2 * (b2 + a2) + ab;
                f32 r0 = 1.0F / total;
                f32 t1 = r0 * ca;
                if (rnd < t1) {
                    if (emit_pos.z > 0.5F) {
                        emit_pos.z = 1.0F;
                    } else {
                        emit_pos.z = 0.0F;
                    }
                } else {
                    f32 t2 = r0 * c2 * a2;
                    t2 = 1.0F - t2;
                    if (rnd < t2) {
                        if (emit_pos.y > 0.5F) {
                            emit_pos.y = 1.0F;
                        } else {
                            emit_pos.y = 0.0F;
                        }
                    } else {
                        if (emit_pos.x > 0.5F) {
                            emit_pos.x = 1.0F;
                        } else {
                            emit_pos.x = 0.0F;
                        }
                    }
                }
                break;
            }
            default:
                break;
            }

            /* Common rect post-processing */
            {
                f32 px = emit_pos.x - 0.5F;
                f32 py = emit_pos.y - 0.5F;
                f32 pz = emit_pos.z - 0.5F;
                emit_pos.x = px;
                emit_pos.y = py;
                emit_pos.z = pz;

                /* Multiply by rect's 3x3 matrix */
                vel_temp.x = gen->aux.rect.yx * py + gen->aux.rect.xx * px +
                             gen->aux.rect.zx * pz;
                vel_temp.y = gen->aux.rect.yy * py + gen->aux.rect.xy * px +
                             gen->aux.rect.zy * pz;
                vel_temp.z = gen->aux.rect.yz * py + gen->aux.rect.xz * px +
                             gen->aux.rect.zz * pz;
            }

            PSMTXMultVec(rot_mtx, &vel_temp, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            /* Compute velocity from rect axes */
            {
                f32 zx = gen->aux.rect.zx;
                f32 zy = gen->aux.rect.zy;
                f32 zz = gen->aux.rect.zz;
                f32 mag = zx * zx + zy * zy + zz * zz;
                if (mag > 0.0F) {
                    f64 e = __frsqrte(mag);
                    e = 0.5 * e * -(mag * (e * e) - 3.0);
                    e = 0.5 * e * -(mag * (e * e) - 3.0);
                    e = 0.5 * e * -(mag * (e * e) - 3.0);
                    mag = (f32) (mag * e);
                }
                {
                    f32 scale = vel_mag_sq / mag;
                    vel_out.x = zx * scale;
                    vel_out.y = zy * scale;
                    vel_out.z = zz * scale;
                }
            }

            PSMTXMultVec(rot_mtx, &vel_out, &vel_out);

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 8: /* sphere emission */
        {
            f32 r0 = gen->aux.cone.height;
            if (0.0F == r0) {
                goto sphere_random;
            }
            {
                f32 diff = r0 - (f32) M_PI;
                f32 absdiff = __fabsf(diff);
                if (absdiff < (f32) eps) {
                    goto sphere_random;
                }
            }
            /* Non-random sphere emission */
            {
                f32 rnd = HSD_Randf();
                if (rnd > 0.0F) {
                    f64 e = __frsqrte(rnd);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    rnd = (f32) (rnd * e);
                }
                radius = (f32) (M_PI * rnd);
                {
                    f32 rnd2 = HSD_Randf();
                    if (rnd2 < 0.5F) {
                        radius = (f32) (M_PI - radius);
                    }
                }
                goto sphere_common;
            }
        sphere_random: {
            f32 rnd = HSD_Randf();
            if (rnd > 0.0F) {
                f64 e = __frsqrte(rnd);
                e = 0.5 * e * -(rnd * (e * e) - 3.0);
                e = 0.5 * e * -(rnd * (e * e) - 3.0);
                e = 0.5 * e * -(rnd * (e * e) - 3.0);
                rnd = (f32) (rnd * e);
            }
            radius = gen->aux.cone.height * rnd;
        }
        sphere_common: {
            f32 rnd = HSD_Randf();
            f32 az_angle;
            f32 r2 = gen->radius;
            az_angle = (f32) ((f64) M_TAU * (f64) rnd);
            cone_angle = (f32) ((f64) M_TAU * az_angle);

            if (r2 < 0.0F) {
                sin_az = -r2;
            } else {
                if (rnd > 0.0F) {
                    f64 e = __frsqrte(rnd);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    e = 0.5 * e * -(rnd * (e * e) - 3.0);
                    rnd = (f32) (rnd * e);
                }
                sin_az = r2 * rnd;
            }
        }
            {
                f32 cos_r;
                f32 sin_r;
                cos_r = cosf(cone_angle);
                cos_az = sinf(radius);
                vel_out.x = cos_az * cos_r;
                sin_el = cosf(cone_angle);
                sin_r = sinf(radius);
                vel_out.y = cos_az * sin_r;
                vel_out.z = cosf(radius);
            }

            PSMTXMultVec(rot_mtx, &vel_out, &emit_pos);

            /* Scale position by aux.rect.x */
            vel_out.x = emit_pos.x * gen->aux.rect.x;
            vel_out.y = emit_pos.y * gen->aux.rect.x;
            vel_out.z = emit_pos.z * gen->aux.rect.x;

            /* Scale velocity if needed */
            if (gen->radius >= 0.0F && gen->aux.rect.x < 0.0F) {
                f32 scale = sin_az / gen->radius;
                vel_out.x *= scale;
                vel_out.y *= scale;
                vel_out.z *= scale;
            }

            emit_pos.x = sin_az * emit_pos.x + gen->pos.x;
            emit_pos.y = sin_az * emit_pos.y + gen->pos.y;
            emit_pos.z = sin_az * emit_pos.z + gen->pos.z;

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        default: /* shape > 8 */
        {
            void (*callback)(HSD_Generator*, Mtx);
            callback = (void (*)(HSD_Generator*, Mtx))(Event) gen->callback;
            if (callback != NULL) {
                callback(gen, rot_mtx);
            }
            break;
        }
        }

        gen->count -= 1.0F;
    }

    return gen->count;
}

void hsd_8039EE24(u32 mask)
{
    HSD_Generator* gp;
    HSD_Generator* gen;

    while (hsd_804D78F4 != 0) {
        gp = (HSD_Generator*) ((HSD_SList*) hsd_804D78F4)->data;
        hsd_8039D71C(gp);
        hsd_804D78F4 = (u32) HSD_SListRemove((HSD_SList*) hsd_804D78F4);
        if (gp->jobj != NULL) {
            HSD_JObjUnref(gp->jobj);
            gp->jobj = NULL;
        }
    }

    gen = hsd_804D78FC;
    hsd_804D78F8 = 0;

    while (gen != NULL) {
        if (mask & (1 << (gen->linkNo + 16))) {
            hsd_804D78F8 = (u32) gen;
            gen = gen->next;
            continue;
        }
        if (gen->kind & 0x800) {
            hsd_804D78F8 = (u32) gen;
            gen = gen->next;
            continue;
        }
        hsd_8039D214(gen);
        if (gen->random < 0.0F) {
            gen->count -= gen->random;
        } else {
            gen->count += gen->random * HSD_Randf();
        }
        if (gen->count >= 1.0F) {
            gen->count = hsd_8039DAD4(gen);
        }
        if (gen->genLife != 0) {
            u16 life = gen->genLife - 1;
            gen->genLife = life;
            if (life == 0) {
                hsd_804D78F8 =
                    (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
                if (hsd_804D78F8 != 0) {
                    gen = ((HSD_Generator*) hsd_804D78F8)->next;
                } else {
                    gen = hsd_804D78FC;
                }
                continue;
            }
        }
        hsd_804D78F8 = (u32) gen;
        gen = gen->next;
    }
}

HSD_Generator* hsd_8039EFAC(s32 linkNo, s32 bank, s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(linkNo, bank, gfx_id);
    if (gen == NULL) {
        return NULL;
    }
    if (gen != NULL) {
        gen->jobj = jobj;
        if (jobj != NULL) {
            ref_INC(jobj);
        }
    }
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    return gen;
}

// @TODO: Currently 80.79% match - .bss.0 section anchor hoist causes
// register-allocation cascade (extra saved reg + frame shift)
static inline s32 ps_get_cmdlist_bound(s32 bank)
{
    return (s32) psCmdListArray[bank];
}

HSD_Generator* hsd_8039F05C(s32 linkNo, s32 bank, s32 idx)
{
    HSD_PSCmdList*** cmdListSlot;
    HSD_PSTexGroup* tg;
    HSD_Generator* gen;
    f32 vel_mag;
    f32 horiz_mag;
    f32 abs_vx;
    f32 mag;
    f32 f0, f1, f3;
    u32 shape;

    if (bank >= 0x41) {
        return NULL;
    }
    if (linkNo >= 8) {
        return NULL;
    }
    if (idx >= ps_get_cmdlist_bound(bank)) {
        return NULL;
    }

    cmdListSlot = (HSD_PSCmdList***) &ptclref_804D0E5C[bank];
#define CMDLIST_ENTRY ((*cmdListSlot)[idx])
    if (CMDLIST_ENTRY == NULL) {
        return NULL;
    }

    gen = hsd_8039D9C8();
    if (gen != NULL) {
        gen->type = CMDLIST_ENTRY->type;
        gen->bank = bank;
        gen->linkNo = linkNo;
        gen->kind = CMDLIST_ENTRY->kind;
        gen->texGroup = CMDLIST_ENTRY->texGroup;
        gen->life = CMDLIST_ENTRY->life;
        gen->genLife = CMDLIST_ENTRY->genLife;
        gen->pos.z = 0.0F;
        gen->pos.y = 0.0F;
        gen->pos.x = 0.0F;
        gen->vel.x = CMDLIST_ENTRY->vx;
        gen->vel.y = CMDLIST_ENTRY->vy;
        gen->vel.z = CMDLIST_ENTRY->vz;
        gen->grav = CMDLIST_ENTRY->grav;
        gen->fric = CMDLIST_ENTRY->fric;
        gen->size = CMDLIST_ENTRY->size;
        gen->cmdList = CMDLIST_ENTRY->cmdList;
        gen->radius = CMDLIST_ENTRY->radius;
        gen->angle = CMDLIST_ENTRY->angle;
        gen->random = CMDLIST_ENTRY->random;

        if (gen->kind & 0x100) {
            f1 = gen->random;
            if (f1 < 0.0F) {
                f3 = 1.0F;
                if ((1.0F + f1) > 1.1920929e-7F) {
                } else {
                    f3 = 0.0F;
                }
                gen->count = f3;
            } else {
                gen->count = 0.9999999F;
            }
        } else if (gen->random < 0.0F) {
            gen->count = 0.0F;
        } else {
            gen->count = HSD_Randf();
        }

        tg = psTexGroupArray[bank][gen->texGroup];
        if (tg != NULL && tg->palflag != 0) {
            gen->kind |= 0x10;
        }

        gen->jobj = NULL;
        gen->numChild = 0;

        shape = gen->type & 0xF;
        switch (shape) {
        case 0:
        case 3:
        case 4: {
            HSD_PSCmdList* c = CMDLIST_ENTRY;
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gen->aux.disc.minAngle = 0.0F;
                gen->aux.disc.maxAngle = 6.2831855F;
            } else {
                gen->aux.disc.minAngle = p1;
                gen->aux.disc.maxAngle = CMDLIST_ENTRY->param2;
            }
            break;
        }
        case 1:
            gen->aux.line.x2 = CMDLIST_ENTRY->param1;
            gen->aux.line.y2 = CMDLIST_ENTRY->param2;
            gen->aux.line.z2 = CMDLIST_ENTRY->param3;
            break;
        case 6:
        case 7: {
            HSD_PSCmdList* c = CMDLIST_ENTRY;
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gen->aux.cone.minAngle = 0.0F;
                gen->aux.cone.maxAngle = 6.2831855F;
            } else {
                gen->aux.cone.minAngle = p1;
                gen->aux.cone.maxAngle = CMDLIST_ENTRY->param2;
            }
            gen->aux.cone.height = CMDLIST_ENTRY->param3;
            break;
        }
        case 5: {
            f0 = CMDLIST_ENTRY->param1;
            gen->aux.disc.minAngle = f0;
            gen->aux.rect.xx = f0;
            f0 = CMDLIST_ENTRY->param2;
            gen->aux.disc.maxAngle = f0;
            gen->aux.rect.yy = f0;
            f0 = CMDLIST_ENTRY->param3;
            gen->aux.line.z2 = f0;
            gen->aux.rect.zz = f0;
            gen->aux.rect.zy = 0.0F;
            gen->aux.rect.zx = 0.0F;
            gen->aux.rect.yz = 0.0F;
            gen->aux.rect.yx = 0.0F;
            gen->aux.rect.xz = 0.0F;
            gen->aux.rect.xy = 0.0F;
            gen->aux.rect.flag = 0;
            if (CMDLIST_ENTRY->param1 < 0.0F) {
                gen->aux.rect.flag |= 1;
            }
            if (CMDLIST_ENTRY->param2 < 0.0F) {
                gen->aux.rect.flag |= 2;
            }
            if (CMDLIST_ENTRY->param3 < 0.0F) {
                gen->aux.rect.flag |= 4;
            }
            break;
        }
        case 8: {
            f32 vx = gen->vel.x;
            f32 vy = gen->vel.y;
            f32 vz = gen->vel.z;
            mag = (vz * vz) + (vx * vx + vy * vy);
            if (mag > 0.0F) {
                f64 x = __frsqrte((f64) mag);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                vel_mag = (f32) ((f64) mag * x);
                mag = vel_mag;
            }
            gen->aux.sphere.speed = mag;

            f0 = gen->vel.x;
            f1 = gen->vel.z;
            mag = (f0 * f0) + (f1 * f1);
            if (mag > 0.0F) {
                f64 x = __frsqrte((f64) mag);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                x = 0.5 * x * -(((f64) mag * (x * x)) - 3.0);
                horiz_mag = (f32) ((f64) mag * x);
                mag = horiz_mag;
            }

            if (mag < 1.1754944e-38F) {
                if (gen->vel.y >= 0.0F) {
                    gen->aux.sphere.latMid = 1.5707964F;
                } else {
                    gen->aux.sphere.latMid = -1.5707964F;
                }
            } else {
                gen->aux.sphere.latMid = atan2f(gen->vel.y, mag);
            }

            abs_vx = gen->vel.x;
            *(s32*) &abs_vx &= 0x7FFFFFFF;
            if (abs_vx < 1.1754944e-38F) {
                if (gen->vel.z >= 0.0F) {
                    gen->aux.sphere.lonMid = 1.5707964F;
                } else {
                    gen->aux.sphere.lonMid = -1.5707964F;
                }
            } else {
                gen->aux.sphere.lonMid = atan2f(gen->vel.z, gen->vel.x);
            }
            gen->aux.sphere.latRange = CMDLIST_ENTRY->param1;
            f1 = gen->aux.sphere.latRange;
            if (f1 < 0.0F) {
                gen->aux.sphere.latRange = -f1;
                gen->aux.sphere.speed = -gen->aux.sphere.speed;
            }
            gen->aux.sphere.lonRange = CMDLIST_ENTRY->param2;
            break;
        }
        default:
            if ((void (*)(HSD_Generator*)) hsd_804D78EC != NULL) {
                ((void (*)(HSD_Generator*)) hsd_804D78EC)(gen);
            }
            break;
        }

        if (gen->kind & 0x20000) {
            gen->type |= 0x800;
            psAddGeneratorAppSRT_begin(gen, 0);
            if (gen->appsrt != NULL) {
                gen->appsrt->xA2 = 1;
                gen->appsrt->gp = gen;
            }
        }

        if ((void (*)(HSD_Generator*)) hsd_804D7900 != NULL) {
            ((void (*)(HSD_Generator*)) hsd_804D7900)(gen);
        }
    }
#undef CMDLIST_ENTRY
    return gen;
}

HSD_Generator* hsd_8039F6CC(s32 linkNo, s32 bank, s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(linkNo, bank, gfx_id);
    if (gen == NULL) {
        return NULL;
    }
    if (gen != NULL) {
        gen->jobj = jobj;
        if (jobj != NULL) {
            ref_INC(jobj);
        }
    }
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    hsd_804D78F4 =
        (u32) HSD_SListAllocAndAppend((HSD_SList*) hsd_804D78F4, gen);
    return gen;
}
