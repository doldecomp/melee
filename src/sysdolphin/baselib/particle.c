#include "particle.h"

#include "particle.static.h"

#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/mcc.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/psstructs.h>
#include <baselib/state.h>
#include <MetroTRK/ppc_reg.h>

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
    Mtx sp14;

    lbl_804D6070 = scale_x;
    lbl_804D6074 = scale_y;
    lbl_804D6078 = line_width;
    HSD_ClearVtxDesc();
    GXSetCurrentMtx(0);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp14);
    GXLoadPosMtxImm(sp14, 0);
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

/// #hsd_80391E18

/// #hsd_80391F28

void hsd_80392194(u8* dst, s32 flags, void* unused1, void* unused2,
                   u8* src)
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

/// #fn_80392480

#pragma push
#pragma dont_inline on
void hsd_80392528(Event arg0)
{
    fn_80392480(arg0, 0x80);
}
#pragma pop

/// #hsd_8039254C

/// #fn_80392934

static s32 lbl_804D6088 = 4;
static s32 lbl_804D608C = 1;

void fn_80392A08(int arg0, int arg1, int arg2)
{
    lbl_804D6088 = arg0;
    lbl_804D608C = arg1;
    if (hsd_804D7888 == 0 && arg2 != 0) {
        hsd_804D787C = 0.0F;
        hsd_804D7880 = 0.0F;
        hsd_804D7884 = 0.0F;
    }
    hsd_804D7888 = arg2;
}

/// #fn_80392A3C

s32 fn_80392CCC(s32 arg0)
{
    hsd_804D7894 = arg0;
    return 0;
}

/// #fn_80392CD8

static s32 hsd_804CE728[0x106];

void fn_80392E2C(s32 arg0)
{
    s32 idx;

    if (hsd_804D7898 <= 0x100 && (u32) (arg0 - 1) <= 1U) {
        idx = hsd_804D789C + hsd_804D7898;
        hsd_804CE728[idx % 256] = arg0;
        hsd_804D7898 += 1;
    }
}

/// #hsd_80392E80

/// #hsd_803931A4

typedef struct {
    s32 x0;
    u32 x4;
    s32 x8;
} ParticleLogEntry;

static ParticleLogEntry hsd_804CEB40[0x100];

void fn_803932D0(s32 arg0, u32 arg1, s32 arg2)
{
    s32 count = hsd_804D78BC;
    ParticleLogEntry* base = hsd_804CEB40;
    s32 idx;
    ParticleLogEntry* entry;

    if (count <= 0x100 && arg1 == 0x100U) {
        idx = (hsd_804D78B8 + count) % 256;
        *(s32*) ((u8*) base + idx * (s32) sizeof(ParticleLogEntry)) = arg0;
        entry = &base[idx];
        entry->x4 = arg1;
        entry->x8 = arg2;
        hsd_804D78BC += 1;
    }
}

/// #hsd_80393328

/// #hsd_80393440

void hsd_80393840(void) {}

/// #hsd_80393844

extern int hsd_804D78A0;

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

void hsd_80393A54(int arg0)
{
    hsd_804D78C0 = arg0;
}

/// #hsd_80393A5C

static struct {
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
} hsd_804CF7E8;

void fn_80393C14(const u8* buf, size_t size)
{
    int i;

    const u32 out_size = hsd_804CF7E8.buf_size;
    const u32 tmp = out_size - 1;

    int var_r12 = hsd_804CF7E8.xC;
    u8* out_buf = hsd_804CF7E8.out_buf;
    u8 var_r9 = hsd_804CF7E8.x11;

    for (i = 0; i < size; i++) {
        switch (buf[i]) {
        case '\r':
            break;
        case '\n':
            if (var_r9 != 0 || out_buf[(var_r12 + tmp) % out_size] != '\0') {
                out_buf[var_r12] = var_r9;
                var_r12 = (var_r12 + 1) % out_size;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                var_r9 = 0;
            }
            break;
        default:
            out_buf[var_r12] = buf[i];
            if (++var_r9 == 0x36) {
                var_r12 = (var_r12 + 1) % out_size;
                out_buf[var_r12] = var_r9;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                var_r9 = 0;
            }
            var_r12 = (var_r12 + 1) % out_size;
            hsd_804CF7E8.x1C++;
            break;
        }
    }
    hsd_804CF7E8.xC = var_r12;
    hsd_804CF7E8.x11 = var_r9;
}

/// #hsd_80393D2C

void hsd_80393DA0(u8* arg0, size_t arg1)
{
    PAD_STACK(4);
    memset(&hsd_804CF7E8, 0, sizeof(hsd_804CF7E8));
    hsd_804CF7E8.out_buf = arg0;
    hsd_804CF7E8.buf_size = arg1;
    memset(arg0, 0, arg1);
    hsd_804CF7E8.x0_b0 = true;
    hsd_804CF7E8.x0_b1 = true;
    HSD_SetReportCallback(fn_80393C14);
}

void hsd_80393E34(s32* arg0, s32* arg1)
{
    if (arg0 != NULL) {
        *arg0 = hsd_804CF7E8.x14;
    }
    if (arg1 != NULL) {
        *arg1 = hsd_804CF7E8.x18;
    }
}

/// #hsd_80393E68

/// #hsd_80393EF4

/// #hsd_80394068

/// #hsd_80394128

/// #hsd_803941E8

/// #hsd_80394314

/// #hsd_80394434

/// #hsd_80394544

/// #hsd_80394668

/// #hsd_80394950

/// #Exception_ReportStackTrace

/// #Exception_ReportCodeline

/// #fn_80394DF4

/// #hsd_80394E8C

/// #hsd_80394F48

/// #hsd_80395550

/// #hsd_80395644

/// #hsd_803956D8

/// #hsd_803957C0

/// #hsd_80395970

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

/// #hsd_80397520

/// #hsd_803975D4

/// #fn_80397814

static u8 hsd_804CF8E8[0x1000];

void hsd_80397DA4(OSContext* arg0)
{
    OSThread sp10;
    OSCreateThread(&sp10, fn_80397814, arg0, hsd_804CF8E8 + 0xFFC,
                   sizeof(hsd_804CF8E8), 0, 1);
    OSResumeThread(&sp10);
}

void Exception_StoreDebugLevel(int arg0)
{
    hsd_804D78C8 = arg0;
}

void hsd_80397DFC(u32 arg0)
{
    hsd_804D78CC = (arg0 + 0xF) >> 4;
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

void fn_803982E4(HSD_GObj* arg0, int unused)
{
    HSD_CObjSetCurrent(arg0->hsd_obj);
    fn_80392934();
    hsd_8039254C();
}

static HSD_CObjDesc lbl_8040BF70 = { 0 };

HSD_GObj* hsd_80398310(u16 arg0, u8 arg1, u8 arg2, u32 arg3)
{
    HSD_GObj* temp_r3;
    HSD_CObj* cobj;

    temp_r3 = GObj_Create(arg0, arg1, arg2);
    if (temp_r3 == NULL) {
        return NULL;
    }
    cobj = HSD_CObjLoadDesc(&lbl_8040BF70);
    HSD_GObjObject_80390A70(temp_r3, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r3, fn_803982E4, arg3);
    hsd_80392528(fn_80392A3C);
    fn_80392A08(4, 1, 0);
    return temp_r3;
}

/// #hsd_803983A4

/// #psInitDataBankLoad

/// #psInitDataBankLocate

/// #psInitDataBank

/// #hsd_80398A08

/// #hsd_80398C04

/// #hsd_80398F0C

/// #hsd_80398F8C

/// #hsd_803991D8

/// #hsd_8039930C

/// #hsd_8039CEAC

/// #hsd_8039CF4C

static HSD_JObj* hsd_804D08E8[8];

void hsd_8039D048(void* arg0)
{
    u32 flags = *(u32*) ((u8*) arg0 + 4);
    if (flags & 0x8000) {
        HSD_JObj** p = &hsd_804D08E8[(flags >> 12) & 7];
        if (*p != NULL) {
            HSD_JObjUnref(*p);
            *p = NULL;
        }
    }
}

/// #hsd_8039D0A0

void hsd_8039D1E4(UNK_T arg0, int arg1)
{
    M2C_FIELD(arg0, int*, 0x58) = arg1;
}

u16 hsd_8039D1EC(void)
{
    hsd_804D78E0++;
    if (hsd_804D78E0 < 256) {
        hsd_804D78E0 = 256;
    }
    return hsd_804D78E0;
}

/// #hsd_8039D214

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

/// #hsd_8039D3AC

/// #hsd_8039D4DC

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

/// #hsd_8039D5DC

/// #hsd_8039D688

/// #hsd_8039D71C

/// #hsd_8039D9C8

/// #hsd_8039DAD4

/// #hsd_8039EE24

/// #hsd_8039EFAC

/// #hsd_8039F05C

/// #hsd_8039F6CC
