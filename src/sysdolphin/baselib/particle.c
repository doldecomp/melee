#include "particle.h"

#include "particle.static.h"

#include <dolphin/gx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/mcc.h>
#include <dolphin/os.h>
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

typedef struct {
    s32 x0;
    u32 x4;
    s32 x8;
} ParticleLogEntry;

typedef struct {
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
} ParticleConsoleState;

typedef struct _ExcptNode {
    /* 0x0 */ struct _ExcptNode* next;
    /* 0x4 */ void (*callback)(struct _ExcptNode*);
} ExcptNode;

typedef struct _EventData {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ u32* entries;
    /* 0x14 */ s32 index;
} EventData;

typedef struct _DispData {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ s32 x10;
} DispData;

typedef struct PSNode {
    /* 0x00 */ struct PSNode* child;
    /* 0x04 */ u8 _pad[4];
    /* 0x08 */ void (*callback)(struct PSNode*);
} PSNode;

HSD_ObjAllocData hsd_804D0F60;
HSD_ObjAllocData hsd_804D0F90;

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

/// #DrawASCII

static float lbl_804D6070 = 12.0f;
static float lbl_804D6074 = 12.0f;
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

/// #hsd_80391AC8

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

/// #hsd_80391F28

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

/// #hsd_803921B8

/// #hsd_803922FC

void hsd_80392474(void)
{
    hsd_804D7850 = 0;
}

/// @@todo: Currently 97.38% match - beq vs bne+b for early return
int fn_80392480(Event event, int priority)
{
    HSD_SList* prev;
    HSD_SList* cur;
    int* data;

    prev = NULL;
    cur = (HSD_SList*) hsd_804D7850;
    while (cur != NULL) {
        data = cur->data;
        if (event == (Event) data[0]) {
            return (int) data;
        }
        if (data[1] <= priority) {
            prev = cur;
        }
        cur = cur->next;
    }
    data = HSD_MemAlloc(8);
    data[0] = (int) event;
    data[1] = priority;
    if (prev != NULL) {
        return (int) HSD_SListAllocAndAppend(prev, data);
    }
    {
        HSD_SList* result =
            HSD_SListAllocAndPrepend((HSD_SList*) hsd_804D7850, data);
        hsd_804D7850 = (u32) result;
    }
}

#pragma push
#pragma dont_inline on
void hsd_80392528(Event event)
{
    fn_80392480(event, 0x80);
}
#pragma pop

/// #hsd_8039254C

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

/// #fn_80392A3C

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

static s32 hsd_804CE728[0x106];

void fn_80392E2C(s32 event_type)
{
    s32 idx;

    if (hsd_804D7898 <= 0x100 && (u32) (event_type - 1) <= 1U) {
        idx = hsd_804D789C + hsd_804D7898;
        hsd_804CE728[idx % 256] = event_type;
        hsd_804D7898 += 1;
    }
}

/// #hsd_80392E80

static ParticleLogEntry hsd_804CEB40[0x100];
static s32 hsd_804CF740[16];

extern int hsd_804D78A0;

/// @@todo: Currently 99.75% match - BSS relocation encoding difference
bool hsd_803931A4(s32 exi_channel)
{
    s32 channel;
    PAD_STACK(16);

    hsd_804CF740[0] = 0;
    hsd_804CF740[1] = 0;
    hsd_804CF740[2] = 0;
    hsd_804CF740[3] = 0;
    hsd_804CF740[4] = 0;
    hsd_804CF740[5] = 0;
    hsd_804CF740[6] = 0;
    hsd_804CF740[7] = 0;
    hsd_804CF740[8] = 0;
    hsd_804CF740[9] = 0;
    hsd_804CF740[10] = 0;
    hsd_804CF740[11] = 0;
    hsd_804CF740[12] = 0;
    hsd_804CF740[13] = 0;
    hsd_804CF740[14] = 0;
    hsd_804CF740[15] = 0;
    hsd_804CF740[0] = 1;
    hsd_804CF740[8] = 1;
    hsd_804CF740[15] = 1;

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

/// @@todo: Currently 95.28% match - r30/r31 register swap and OSReport arg setup
s32 hsd_80393328(void)
{
    s32 startTick;
    u32 ticksPerUnit;
    s32 result;

    if (hsd_804D78B4 != 0) {
        return 0;
    }
    hsd_804D78B4 = 1;
    hsd_804D78B0 = HSD_Rand() % 255;
    if (MCCNotify(0xF, hsd_804D78B0 + 256) == 0) {
        OSReport("Error(0x%x) in MCCNotify.\n", MCCGetLastError());
    }
    result = 1;
    startTick = OSGetTick();
    ticksPerUnit = *(u32*) 0x800000F8 >> 2;
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

/// #hsd_80393440

void hsd_80393840(void) {}

/// #hsd_80393844

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

/// @@todo: Currently 95.44% match - signed/unsigned float conversion swap
int hsd_80393A5C(char* filename, int data, int size)
{
    int ready;
    s32 start;
    int fd;
    f32 written_f;
    f32 elapsed;

    if (hsd_804D78A0 == 0) {
        ready = 0;
    } else if (FIOQuery() == 0) {
        ready = 0;
        hsd_804D78A0 = 0;
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

    written_f = (f32) (s32) FIOFwrite(fd, (void*) data, size);

    if (written_f != (f32) (u32) size) {
        OSReport("cannot save file\n");
        FIOFclose(fd);
        return (s32) written_f;
    }

    FIOFclose(fd);
    elapsed = (f32) (OSGetTick() - start) / (f32) (*(u32*) 0x800000F8 >> 2);
    OSReport("Done %s size:%d time:%f spped:%fkbps\n", filename, size, elapsed,
             8.0F * (f32) (u32) size / elapsed * (1.0F / 1024.0F));
    return size;
}

extern ParticleConsoleState hsd_804CF7E8;

void fn_80393C14(const u8* buf, size_t size)
{
    int i;

    const u32 out_size = hsd_804CF7E8.buf_size;
    const u32 tmp = out_size - 1;

    int write_pos = hsd_804CF7E8.xC;
    u8* out_buf = hsd_804CF7E8.out_buf;
    u8 line_len = hsd_804CF7E8.x11;

    for (i = 0; i < size; i++) {
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

/// @@todo: Currently 94.34% match - lbzu vs addi+lbz addressing pattern
s32 hsd_80393D2C(s32 enable)
{
    s32 old = hsd_804CF7E8.x0_b1;

    if (enable != 0) {
        hsd_804CF7E8.x0_b1 = 1;
        HSD_SetReportCallback(fn_80393C14);
    } else {
        hsd_804CF7E8.x0_b1 = 0;
        HSD_SetReportCallback(NULL);
    }
    return old;
}

void hsd_80393DA0(u8* buf, size_t size)
{
    PAD_STACK(4);
    memset(&hsd_804CF7E8, 0, sizeof(hsd_804CF7E8));
    hsd_804CF7E8.out_buf = buf;
    hsd_804CF7E8.buf_size = size;
    memset(buf, 0, size);
    hsd_804CF7E8.x0_b0 = true;
    hsd_804CF7E8.x0_b1 = true;
    HSD_SetReportCallback(fn_80393C14);
}

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
    u32 byte_val;
    u32 buf_size;
    u8* out_buf;
    u32 sum;
    u32 pos;
    u32 counter;

    if (!hsd_804CF7E8.x0_b0) {
        return;
    }

    byte_val = hsd_804CF7E8.x11;
    buf_size = hsd_804CF7E8.buf_size;
    out_buf = hsd_804CF7E8.out_buf;
    sum = hsd_804CF7E8.xC + buf_size;
    pos = byte_val;
    counter = 0;

    while (counter < row && pos < buf_size) {
        pos++;
        byte_val = out_buf[(sum - pos) % buf_size];
        counter++;
        pos += byte_val;
    }

    hsd_804CF7E8.x18 = counter;
    hsd_804CF7E8.x1C = pos;
    hsd_804CF7E8.x20 = byte_val;

    if (col < byte_val) {
        hsd_804CF7E8.x14 = col;
    } else {
        hsd_804CF7E8.x14 = byte_val;
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
void hsd_80393EF4(int col_delta, int row_delta)
{
    u32 byte_val;
    u32 buf_size;
    u32 counter;
    u32 pos;
    u32 sum;
    u8* out_buf;

    if (!hsd_804CF7E8.x0_b0) {
        return;
    }

    buf_size = hsd_804CF7E8.buf_size;

    if ((u32) hsd_804CF7E8.x1C >= buf_size) {
        hsd_80393E68(hsd_804CF7E8.x14 + col_delta,
                     hsd_804CF7E8.x18 + row_delta);
        return;
    }

    out_buf = hsd_804CF7E8.out_buf;
    pos = hsd_804CF7E8.x1C;
    byte_val = hsd_804CF7E8.x20;
    sum = hsd_804CF7E8.xC + buf_size;

    if (row_delta > 0) {
        counter = 0;

        while (counter < (u32) row_delta && pos < buf_size) {
            pos++;
            byte_val = out_buf[(sum - pos) % buf_size];
            counter++;
            pos += byte_val;
        }

        hsd_804CF7E8.x18 += counter;
        hsd_804CF7E8.x1C = pos;

        if (col_delta >= 0) {
            hsd_804CF7E8.x14 += col_delta;
            if ((u32) hsd_804CF7E8.x14 > byte_val) {
                hsd_804CF7E8.x14 = byte_val;
            }
        } else {
            if ((u32) hsd_804CF7E8.x14 > (u32) -col_delta) {
                hsd_804CF7E8.x14 -= (u32) -col_delta;
            } else {
                hsd_804CF7E8.x14 = 0;
            }
        }
    } else if (row_delta < 0) {
        if (col_delta < 0 && (u32) hsd_804CF7E8.x14 < (u32) -col_delta) {
            col_delta = 0;
        } else {
            col_delta = hsd_804CF7E8.x14 + col_delta;
        }

        if (row_delta < 0 && (u32) hsd_804CF7E8.x18 < (u32) -row_delta) {
            row_delta = 0;
        } else {
            row_delta = hsd_804CF7E8.x18 + row_delta;
        }

        hsd_80393E68(col_delta, row_delta);
    }
}
#pragma pop

#pragma push
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
        u32 idx;
        idx = (hsd_804CF7E8.x14 +
               (hsd_804CF7E8.xC + hsd_804CF7E8.buf_size - hsd_804CF7E8.x1C)) %
              hsd_804CF7E8.buf_size;
        result = hsd_804CF7E8.out_buf[idx];
        hsd_804CF7E8.x14++;
    } else {
        result = 0;
        hsd_80393EF4(0, -1);
        hsd_804CF7E8.x14 = 0;
    }
    return result;
}
#pragma pop

ParticleConsoleState hsd_804CF7E8;

/// #hsd_803941E8

struct ParticleScreenState {
    /* 0x00 */ u8 x0_b7 : 1;
    /* 0x00 */ u8 x0_b6 : 1;
    /* 0x00 */ u8 x0_b5 : 1;
    /* 0x00 */ u8 x0_rest : 5;
    /* 0x01 */ u8 _pad0[0x3];
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 x0C;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ u32 x28;
    /* 0x2C */ s32 x2C;
    /* 0x30 */ void* x30;
    /* 0x34 */ s32 x34;
    /* 0x38 */ s32 x38;
    /* 0x3C */ s32 x3C;
    /* 0x40 */ s32 x40;
    /* 0x44 */ s32 x44;
    /* 0x48 */ s32 x48;
    /* 0x4C */ void* x4C;
    /* 0x50 */ void* x50;
    /* 0x54 */ u8 _pad4[0x68];
    /* 0xBC */ u32 xBC;
    /* 0xC0 */ u8 _pad4b[0x4];
    /* 0xC4 */ s32 xC4;
    /* 0xC8 */ u8 _pad4c[0x8];
    /* 0xD0 */ void* xD0;
    /* 0xD4 */ u8 _pad5[0x4];
};
struct ParticleScreenState hsd_804CF810;

extern u8 lbl_804088B8[];

/// @@todo: Currently 99.61% match - .bss.0 relocation symbol instead of
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

/// @@todo: Currently 91.67% match - .bss.0 relocation causes add+lwz instead of
/// addi+lwzx
void hsd_80394434(void* text)
{
    s32 x = hsd_804CF810.x4;
    s32 y = hsd_804CF810.x8;
    s32 mode = hsd_804CF810.x0_b7;
    s32 interlace = hsd_804CF810.x0_b6;
    u8* font = (u8*) hsd_804CF810.x4C;
    s8* ptr = text;

    while (*ptr != 0) {
        switch (*ptr) {
        case '\r':
            break;
        case '\n':
            x = hsd_804CF810.x4;
            y += 14;
            /* fallthrough */
        default:
            if (mode != 0) {
                hsd_803922FC(font + (*ptr & 0x7F) * 0x38, x, y, interlace,
                             (&hsd_804CF810.x24)[hsd_804CF810.x34],
                             hsd_804CF810.x3C, hsd_804CF810.x40,
                             hsd_804CF810.x44, hsd_804CF810.x50);
            } else {
                hsd_803921B8(font + (*ptr & 0x7F) * 0x38, x, y,
                             (&hsd_804CF810.x24)[hsd_804CF810.x34],
                             hsd_804CF810.x3C, hsd_804CF810.x40,
                             hsd_804CF810.x44, hsd_804CF810.x50);
            }
            x += 11;
            break;
        }
        ptr++;
    }
}

/// #hsd_80394544

/// #hsd_80394668

/// @@todo: Currently 83.27% match - instruction scheduling in loop bodies
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

    OSReport("- FPR ---------------------------------\n");

    i = 0;
    p = (u8*) ctx;
    do {
        OSReport("R%02d=%08X:%08X (%e)\n", i, *(u32*) (p + 0x90),
                 *(u32*) (p + 0x94), *(f64*) (p + 0x90));
        i++;
        p += 8;
    } while (i < 32);

    OSReport("- PSF ---------------------------------\n");

    i = 0;
    p = (u8*) ctx;
    do {
        OSReport("R%02d=%08X:%08X (%e, %e)\n", i, *(u32*) (p + 0x90),
                 *(u32*) (p + 0x94), *(f32*) (p + 0x90), *(f32*) (p + 0x94));
        i++;
        p += 8;
    } while (i < 32);

    OSClearContext(&tmp);
    OSSetCurrentContext(saved);
    OSRestoreInterrupts(irq);
}

/// @@todo: Currently 99.94% match - minor relocation difference
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

/// #Exception_ReportCodeline

/// @@todo: Currently 97.87% match - lwz r0 + mr r4 instead of lwz r4
void fn_80394DF4(void* node_ptr)
{
    ExcptNode* node = node_ptr;
    ExcptNode* head;
    ExcptNode* prev;

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

/// #hsd_80394F48

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
                u32* base = data->entries;
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
            u32* base = data->entries;
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

/// @@todo: Currently 99.78% match - minor addressing difference
void hsd_80395644(void)
{
    void* saved;
    void** p = &hsd_804CF810.x50;
    s32 val_x20;
    s32 val_x1C;

    PAD_STACK(16);
    saved = *p;
    *p = lbl_8040AB20;
    val_x20 = hsd_804CF810.x20;
    val_x1C = hsd_804CF810.x1C;
    hsd_804CF810.x4 = (val_x20 - 21) * 11 + 20;
    hsd_804CF810.x8 = (hsd_804CF810.x40 - 40) - (val_x1C + 1) * 14;
    if (hsd_804D78C8 >= 1) {
        hsd_80394434(lbl_8040B8AC);
    }
    *p = saved;
}

/// @@todo: Currently 99.78% match - minor addressing difference
s32 hsd_803956D8(void* disp_ptr)
{
    DispData* data = disp_ptr;
    s32 val;

    if (hsd_804CF810.xBC & 0x1000) {
        hsd_80394E8C(lbl_8040B904);
        hsd_804CF810.x14 = 0;
        data->x10 = 0;
        return 1;
    }

    val = data->x10;
    if (val < 120) {
        data->x10 = val + 1;
        return 0;
    }

    data->x10 = 0;
    hsd_804CF810.x14 += hsd_804CF810.x1C;
    if (!(u8) hsd_80394128(0, hsd_804CF810.x14)) {
        if (!(u8) hsd_80394128(0, hsd_804CF810.x14 + 1)) {
            hsd_804CF810.x14 = 0;
            hsd_80394E8C(lbl_8040B904);
        }
    }
    return 1;
}

/// #hsd_803957C0

/// @@todo: Currently 79.44% match - BSS layout offsets and epilogue ordering
#pragma push
#pragma dont_inline on
s32 hsd_80395970(void)
{
    s32 saved_x;
    s32 saved_y;
    s32 i;
    s32 result;
    u8 ch;

    result = 0;
    hsd_80393E34(&saved_x, &saved_y);
    hsd_80393E68(hsd_804CF810.x0C + hsd_804CF810.x18,
                 hsd_804CF810.x10 + hsd_804CF810.x14);

    for (i = 0; i < 8; i++) {
        ch = hsd_80394068();
        if (ch == 0) {
            ch = hsd_80394068();
            if (ch == 0) {
                break;
            }
        }
        if (ch >= '0' && ch <= '9') {
            result = (result << 4) + (ch - '0');
        } else if (ch >= 'A' && ch <= 'F') {
            result = (result << 4) + (ch - 'A' + 10);
        } else if (ch >= 'a' && ch <= 'f') {
            result = (result << 4) + (ch - 'a' + 10);
        } else {
            break;
        }
    }

    hsd_80393E68(saved_x, saved_y);
    return (result & 0x0FFFFFF0) | (s32) 0x80000000;
}

#pragma pop

/// #hsd_80395A78

/// #hsd_80395D88

extern struct {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ u32 x10;
} lbl_8040BAF0;

extern struct {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ u32 x10;
} lbl_8040BC3C;

void hsd_80396130(void)
{
    u32 old = lbl_8040BC3C.x10;
    u32 memsize;

    memsize = OSGetPhysicalMemSize();
    old &= 0x0FFFFFFF;
    lbl_8040BAF0.x10 = (old + memsize) % memsize + 0x80000000;
    PAD_STACK(16);
}

/// #hsd_80396188

/// #hsd_803962A8

/// #hsd_803966A0

void hsd_80396868(void)
{
    lbl_8040BC3C.x10 = (lbl_8040BC3C.x10 & 0x0FFFFFF0) | 0x80000000;
}

/// #hsd_80396884

/// #hsd_80396A20

/// #hsd_80396C78

/// #hsd_80396E40

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

/// #hsd_80397110

/// #fn_80397374

/// @@todo: Currently 96.89% match - lwz directly to non-volatile + dead beq
void hsd_80397520(void* node_ptr)
{
    PSNode* child1;
    PSNode* child2;
    PSNode* node = node_ptr;

    if (node == NULL) {
        return;
    }
    child1 = node->child;
    if (child1 != NULL) {
        child2 = child1->child;
        if (child2 != NULL) {
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

/// #hsd_803975D4

/// #fn_80397814

static u8 hsd_804CF8E8[0x1000];

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
    hsd_80392528(fn_80392A3C);
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

static HSD_JObj* hsd_804D08E8[8];

/// @@todo: Currently 96.40% match - lis hoisting and r29/r30 register swap
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

/// #psInitDataBankLocate

void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref,
                    int* formBank)
{
    if (bank < 65) {
        psInitDataBankLocate((HSD_Archive*) cmdBank, (HSD_Archive*) texBank,
                             formBank);
        psInitDataBankLoad(bank, cmdBank, texBank, ref, formBank);
    }
}

/// #hsd_80398A08

/// #hsd_80398C04

/// @@todo: Currently 76.78% match - float stack parameter calling convention
void hsd_80398F0C(s32 bank, s32 id, s32 link_no, s32 pos_x, s32 pos_y,
                  s32 pos_z, s32 vel_x, s32 vel_y, f32 rate)
{
    hsd_80398C04(0, bank, id, link_no, pos_x, pos_y, pos_z, vel_x, rate, vel_y,
                 1);
}

/// #hsd_80398F8C

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

/// #hsd_8039930C

static void* hsd_804D0908[16];

/// @@todo: Currently 96.0% match - prologue instruction scheduling
void hsd_8039CEAC(u32 mask)
{
    void** bins;
    void* cur;
    void* prev;
    s32 i;
    u32 bits;
    void* next;

    bins = hsd_804D0908;
    bits = mask;
    i = 0;
    do {
        if (!(bits & 0x10000)) {
            cur = *bins;
            prev = NULL;
            while (cur != NULL) {
                next = hsd_8039930C(cur, prev);
                if (prev == NULL) {
                    if (*bins != next) {
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
        i++;
        bits >>= 1;
        bins++;
    } while (i < 16);
}

/// @@todo: Currently 96.59% match - instruction scheduling in address
/// computation
void hsd_8039CF4C(s32 index, HSD_JObj* jobj)
{
    if (index < 0 || index > 8) {
        return;
    }

    if (index != 0) {
        HSD_JObj** p = &hsd_804D08E8[index];
        HSD_JObj* old = *--p;
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

/// @@todo: Currently 93.38% match - BSS layout (offset) differences
void hsd_8039D0A0(HSD_Generator* gen)
{
    HSD_Particle* prev;
    HSD_Particle* prt;
    HSD_Particle* next;
    HSD_Particle** head;
    u16 idnum;

    prev = NULL;
    idnum = gen->idnum;
    head = (HSD_Particle**) &hsd_804D0908[gen->linkNo];
    prt = (HSD_Particle*) *head;

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
                HSD_JObj** jobj_ptr = &hsd_804D08E8[(prt->kind >> 12) & 7];
                if (*jobj_ptr != NULL) {
                    HSD_JObjUnref(*jobj_ptr);
                    *jobj_ptr = NULL;
                }
            }

            HSD_ObjFree(&hsd_804D0F60, prt);
            hsd_804D78E2--;
        } else {
            prev = prt;
        }
        prt = next;
    }
}

void hsd_8039D1E4(HSD_Generator* gen, void* userfunc)
{
    gen->userfunc = userfunc;
}

u16 hsd_8039D1EC(void)
{
    hsd_804D78E0++;
    if (hsd_804D78E0 < 256) {
        hsd_804D78E0 = 256;
    }
    return hsd_804D78E0;
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
    HSD_ObjAllocInit(&hsd_804D0F90, 0x94, 4);
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
    HSD_ObjFree(&hsd_804D0F90, gen);
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

/// @@todo: Currently 94.68% match - Vec3 col stack offset wrong (sp+0x4C
/// vs sp+0x1C), causing velocity transform scheduling differences
void hsd_8039D71C(HSD_Generator* gen)
{
    HSD_JObj* jobj;
    Vec3 col;
    f32 col0_x, col0_y, col0_z;
    f32 col1_x, col1_y, col1_z;
    PAD_STACK(64);

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
        f32 vy = gen->vel.y;
        f32 vx = gen->vel.x;
        f32 vz = gen->vel.z;
        gen->vel.x = col1_x * vy + col0_x * vx + col.x * vz;
        gen->vel.y = col1_y * vy + col0_y * vx + col.y * vz;
        gen->vel.z = col1_z * vy + col0_z * vx + col.z * vz;
    }

    if ((gen->type & 0xF) == 1) {
        f32 ay = gen->aux.line.y2;
        f32 ax = gen->aux.line.x2;
        f32 az = gen->aux.line.z2;
        gen->aux.line.x2 =
            jobj->mtx[0][1] * ay + jobj->mtx[0][0] * ax + jobj->mtx[0][2] * az;
        gen->aux.line.y2 =
            jobj->mtx[1][1] * ay + jobj->mtx[1][0] * ax + jobj->mtx[1][2] * az;
        gen->aux.line.z2 =
            jobj->mtx[2][1] * ay + jobj->mtx[2][0] * ax + jobj->mtx[2][2] * az;
    }
}

static u16 lbl_804D6368 = 0x100;

HSD_Generator* hsd_8039D9C8(void)
{
    HSD_Generator* gen;
    PAD_STACK(8);

    gen = HSD_ObjAlloc(&hsd_804D0F90);
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

/// #hsd_8039DAD4

/// @@todo: Currently 98.57% match - register allocation (r30 vs r31 for gen)
void hsd_8039EE24(u32 mask)
{
    HSD_Generator* gen;

    while (hsd_804D78F4 != 0) {
        gen = (HSD_Generator*) ((HSD_SList*) hsd_804D78F4)->data;
        hsd_8039D71C(gen);
        hsd_804D78F4 = (u32) HSD_SListRemove((HSD_SList*) hsd_804D78F4);
        if (gen->jobj != NULL) {
            HSD_JObjUnref(gen->jobj);
            gen->jobj = NULL;
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

/// @@todo: Currently 95.45% match - 2 dead beq instructions in target
HSD_Generator* hsd_8039EFAC(s32 bank, s32 id, s32 link, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(bank, id, link);
    if (gen == NULL) {
        return NULL;
    }
    gen->jobj = jobj;
    ref_INC(jobj);
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    return gen;
}

/// #hsd_8039F05C

/// @@todo: Currently 95.83% match - dead beq instructions in target
HSD_Generator* hsd_8039F6CC(s32 bank, s32 id, s32 link, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(bank, id, link);
    if (gen == NULL) {
        return NULL;
    }
    gen->jobj = jobj;
    ref_INC(jobj);
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    hsd_804D78F4 =
        (u32) HSD_SListAllocAndAppend((HSD_SList*) hsd_804D78F4, gen);
    return gen;
}
