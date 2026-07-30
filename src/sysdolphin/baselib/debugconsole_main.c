#include "debugconsole_main.h"

#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/hsd_3915.h>
#include <sysdolphin/baselib/hsd_3933.h>
#include <sysdolphin/baselib/hsd_393C.h>
#include <sysdolphin/baselib/video.h>
#include <MetroTRK/ppc_reg.h>

typedef struct _ExcptNode {
    /* 0x1 */ struct _ExcptNode* next;
    /* 0x4 */ void (*callback)(struct _ExcptNode*);
} ExcptNode;

typedef struct PSNode {
    /* 0x00 */ struct PSNode* child;
    /* 0x04 */ u8 _pad[4];
    /* 0x08 */ void (*callback)(struct PSNode*);
} PSNode;

/// @todo misnomer - moved from particle file, not particle-related
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
    /* 0xC0 */ u32 xC0;
    /* 0xC4 */ s32 xC4;
    /* 0xC8 */ s32 xC8;
    /* 0xCC */ s32 xCC;
    /* 0xD0 */ void* xD0;
    /* 0xD4 */ OSContext* xD4;
};

extern u8 lbl_804088B8[];
/* 4D78C8 */ extern int hsd_804D78C8;
/* 4D78CC */ extern u32 hsd_804D78CC;

/* 4CF810 */ static struct ParticleScreenState hsd_804CF810;

typedef struct _EventData {
    /* 0x00 */ u8 _pad[0x10];
    /* 0x10 */ char** entries;
    /* 0x14 */ s32 index;
} EventData;

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

typedef union {
    f32 f;
    u8 bytes[4];
} ParticleFloatBytes;

struct ParticleScreenBuffer {
    u8 data[1];
};

struct SPREntry {
    u32 spr;
    char* name;
    char* description;
    void (*callback)(int);
};

struct lbl_8040AB00_t {
    u32 x0;
    void* x4;
    u32 x8;
    void* xC;
    u32 x10;
    void* x14;
    u32 x18;
    void* x1C;
};

static struct lbl_8040AB00_t lbl_8040AB00 = {
    0x10808000, hsd_80392194, 0x46808000, hsd_80392194,
    0x7C808000, hsd_80392194, 0xB3808000, hsd_80392194,
};
static struct lbl_8040AB00_t lbl_8040AB20 = {
    0xB3808000, hsd_80392194, 0x7C808000, hsd_80392194,
    0x46808000, hsd_80392194, 0x10808000, hsd_80392194,
};
static struct lbl_8040AB00_t lbl_8040AB40 = {
    0x10808000, hsd_80392194, 0x10808000, hsd_80392194,
    0x10808000, hsd_80392194, 0x10808000, hsd_80392194,
};

struct SPREntry lbl_8040ADD8[] = { {
                                       0x00000009,
                                       "CTR",
                                       "Count Register",
                                       NULL,
                                   },
                                   {
                                       0x000003F5,
                                       "DABR",
                                       "Data Address Breakpoint",
                                       NULL,
                                   },
                                   {
                                       0x00000013,
                                       "DAR",
                                       "Data Address Register",
                                       NULL,
                                   },
                                   {
                                       0x00000219,
                                       "DBAT0L",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000218,
                                       "DBAT0U",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021B,
                                       "DBAT1L",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021A,
                                       "DBAT1U",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021D,
                                       "DBAT2L",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021C,
                                       "DBAT2U",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021F,
                                       "DBAT3L",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x0000021E,
                                       "DBAT3U",
                                       "Data Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000016,
                                       "DEC",
                                       "Descrimenter",
                                       NULL,
                                   },
                                   {
                                       0x00000012,
                                       "DSISR",
                                       "Data Access/Alignment Exception",
                                       fn_803970D8,
                                   },
                                   {
                                       0x0000011A,
                                       "EAR",
                                       "External Access",
                                       NULL,
                                   },
                                   {
                                       0x00000211,
                                       "IBAT0L",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000210,
                                       "IBAT0U",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000213,
                                       "IBAT1L",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000212,
                                       "IBAT1U",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000215,
                                       "IBAT2L",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000214,
                                       "IBAT2U",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000217,
                                       "IBAT3L",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000216,
                                       "IBAT3U",
                                       "Inst Block Address Translation",
                                       hsd_80396E40,
                                   },
                                   {
                                       0x00000008,
                                       "LR",
                                       "Link Register",
                                       NULL,
                                   },
                                   {
                                       0x0000011F,
                                       "PVR",
                                       "Processor Version",
                                       NULL,
                                   },
                                   {
                                       0x000003BF,
                                       "SDA",
                                       "Sample Data Address",
                                       NULL,
                                   },
                                   {
                                       0x00000019,
                                       "SDR1",
                                       "Page Table Format",
                                       NULL,
                                   },
                                   {
                                       0x00000110,
                                       "SPRG0",
                                       "For Operation System",
                                       NULL,
                                   },
                                   {
                                       0x00000111,
                                       "SPRG1",
                                       "For Operation System",
                                       NULL,
                                   },
                                   {
                                       0x00000112,
                                       "SPRG2",
                                       "For Operation System",
                                       NULL,
                                   },
                                   {
                                       0x00000113,
                                       "SPRG3",
                                       "For Operation System",
                                       NULL,
                                   },
                                   {
                                       0x0000001A,
                                       "SRR0",
                                       "Machine Status Save/Restore",
                                       fn_803970DC,
                                   },
                                   {
                                       0x0000001B,
                                       "SRR1",
                                       "Machine Status Save/Restore",
                                       fn_803970DC,
                                   },
                                   {
                                       0x000003AF,
                                       "USDA",
                                       "Sample Data Address",
                                       NULL,
                                   },
                                   {
                                       0x00000001,
                                       "XER",
                                       "?",
                                       fn_803970E0,
                                   },
                                   {
                                       0x00000000,
                                       NULL,
                                       NULL,
                                       NULL,
                                   },
                                   {
                                       0x0000039B,
                                       "DMA_L",
                                       "Direct Memory Access",
                                       fn_803970E4,
                                   },
                                   {
                                       0x0000039A,
                                       "DMA_U",
                                       "Direct Memory Access",
                                       fn_803970E4,
                                   },
                                   {
                                       0x00000390,
                                       "GQR0",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000391,
                                       "GQR1",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000392,
                                       "GQR2",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000393,
                                       "GQR3",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000394,
                                       "GQR4",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000395,
                                       "GQR5",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000396,
                                       "GQR6",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x00000397,
                                       "GQR7",
                                       "Graphics Quantization",
                                       fn_803970E8,
                                   },
                                   {
                                       0x000003F0,
                                       "HID0",
                                       "Hardware Implementation Depend",
                                       fn_803970EC,
                                   },
                                   {
                                       0x000003F1,
                                       "HID1",
                                       "Hardware Implementation Depend",
                                       fn_803970EC,
                                   },
                                   {
                                       0x00000398,
                                       "HID2",
                                       "Hardware Implementation Depend",
                                       fn_803970EC,
                                   },
                                   {
                                       0x000003F2,
                                       "IABR",
                                       "Instruction Breakpoint",
                                       fn_803970F0,
                                   },
                                   {
                                       0x000003FB,
                                       "ICTC",
                                       "Instruction Cache Throttle Control",
                                       fn_803970F4,
                                   },
                                   {
                                       0x000003F9,
                                       "L2CR",
                                       "L2 Cache Control",
                                       fn_803970F8,
                                   },
                                   {
                                       0x000003B8,
                                       "MMCR0",
                                       "Perf. Moniter Mode Control",
                                       fn_803970FC,
                                   },
                                   {
                                       0x000003BC,
                                       "MMCR1",
                                       "Perf. Monitor Mode Control",
                                       fn_803970FC,
                                   },
                                   {
                                       0x000003B9,
                                       "PMC1",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003BA,
                                       "PMC2",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003BD,
                                       "PMC3",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003BE,
                                       "PMC4",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003BB,
                                       "SIA",
                                       "Sample Instruction Address",
                                       NULL,
                                   },
                                   {
                                       0x000003FC,
                                       "THRM1",
                                       "Thermal Managiment",
                                       fn_80397104,
                                   },
                                   {
                                       0x000003FD,
                                       "THRM2",
                                       "Thermal Managiment",
                                       fn_80397104,
                                   },
                                   {
                                       0x000003FE,
                                       "THRM3",
                                       "Thermal Managiment",
                                       fn_80397104,
                                   },
                                   {
                                       0x000003A8,
                                       "UMMCR0",
                                       "Perf. Moniter Mode Control",
                                       fn_803970FC,
                                   },
                                   {
                                       0x000003AC,
                                       "UMMCR1",
                                       "Perf. Moniter Mode Control",
                                       fn_803970FC,
                                   },
                                   {
                                       0x000003A9,
                                       "UPMC1",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003AA,
                                       "UPMC2",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003AD,
                                       "UPMC3",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003AE,
                                       "UPMC4",
                                       "Performance Monitor Counter",
                                       fn_80397100,
                                   },
                                   {
                                       0x000003AB,
                                       "USIA",
                                       "Sample Instruction Address",
                                       NULL,
                                   },
                                   {
                                       0x00000399,
                                       "WPAR",
                                       "Write Pipe Address",
                                       fn_80397108,
                                   } };

static void gprmsg(void)
{
    OSReport("- GPR -----------------------------------------------\n");
    OSReport("R%02d=%08X(%11d) R%02d=%08X(%11d)\n");
}

void hsd_80394314(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;

    memset(sp, 0, sizeof(*sp));
    hsd_803941E8(&((struct ParticleScreenState*) sp)->x24,
                 &((struct ParticleScreenState*) sp)->x2C);

    {
        s32 mode;
        if (((struct ParticleScreenState*) sp)->x28 != 0) {
            mode = 2;
        } else {
            mode = 1;
        }
        ((struct ParticleScreenState*) sp)->x38 = mode;
    }

    ((struct ParticleScreenState*) sp)->x34 = 0;
    ((struct ParticleScreenState*) sp)->x30 = &HSD_VIData;
    ((struct ParticleScreenState*) sp)->x3C =
        ((u16*) ((struct ParticleScreenState*) sp)->x30)[2];
    ((struct ParticleScreenState*) sp)->x40 =
        ((u16*) ((struct ParticleScreenState*) sp)->x30)[4];
    ((struct ParticleScreenState*) sp)->x44 =
        (((u16) ((struct ParticleScreenState*) sp)->x3C + 15) * 2) & 0x1FFE0;
    ((struct ParticleScreenState*) sp)->x48 =
        ((struct ParticleScreenState*) sp)->x44 *
        ((struct ParticleScreenState*) sp)->x40;
    ((struct ParticleScreenState*) sp)->x4 = 0;
    ((struct ParticleScreenState*) sp)->x8 =
        ((struct ParticleScreenState*) sp)->x40;
    ((struct ParticleScreenState*) sp)->x18 = 0;
    ((struct ParticleScreenState*) sp)->x14 = 0;
    ((struct ParticleScreenState*) sp)->x20 =
        (u32) (((struct ParticleScreenState*) sp)->x3C - 0x28) / 11;
    ((struct ParticleScreenState*) sp)->x1C =
        (u32) (((struct ParticleScreenState*) sp)->x40 - 0x50) / 14;
    ((struct ParticleScreenState*) sp)->x4C = lbl_804088B8;
    ((struct ParticleScreenState*) sp)->x50 = 0;
    ((struct ParticleScreenState*) sp)->xC4 = 0;
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
    s32 cur_x;
    s32 interlace;
    u32 r;
    u32 c;
    s32 mode;
    u8 ch;

    mode = hsd_804CF810.x0_b7;
    interlace = hsd_804CF810.x0_b6;
    r = 0;

    while (r < num_rows) {
        hsd_80393E68(col, row);
        y -= 14;

        for (cur_x = x + (c = 0) * 11; c < num_cols; c++) {
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
        }
        row++;
        r++;
    }
}

#pragma push
#pragma global_optimizer off
void hsd_80394668(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    s32 pos;
    PAD_STACK(24);

    {
        s32* dst_base;
        struct ParticleScreenBuffer* dst;
        u32 size;
        struct ParticleScreenBuffer* src;

        src = (struct ParticleScreenBuffer*) sp->x2C;
        if ((u32) src != 0) {
            /* Copy XFB data with brightness adjustment */
            dst_base = (s32*) sp + sp->x34;
            dst = (struct ParticleScreenBuffer*) dst_base[9];
            size = sp->x48;

            for (pos = 0; pos < size; pos += 2) {
                u8* s1 = src->data + pos;
                u8* d1 = dst->data + pos;
                d1[0] = (u8) (((s1[0] - 0x10) & 0xFFFFFF) + 0x10);
                d1[1] = s1[1];
            }
        } else {
            /* Draw console text to framebuffer */
            void* saved_color;
            s32 cur_x;
            s32 y_off;
            void** x50_ptr;
            s32* x40_ptr;
            s32* x8_ptr;
            s32* x4_ptr;
            s32 row;
            s32 col;

            x50_ptr = &sp->x50;
            saved_color = *x50_ptr;
            *x50_ptr = &lbl_8040AB40;
            x4_ptr = &sp->x4;
            x40_ptr = &sp->x40;
            x8_ptr = &sp->x8;
            row = 0;

            while (row <= sp->x1C) {
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
                                         (&sp->x24)[sp->x34], sp->x3C,
                                         *x40_ptr, sp->x44, *x50_ptr);
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
}
#pragma pop

void hsd_80394950(OSContext* ctx)
{
    OSContext tmp;
    OSContext* saved;
    BOOL irq;
    int i;
    u8* p;

    if (!(ctx->state & OS_CONTEXT_STATE_FPSAVED)) {
        return;
    }

    irq = OSDisableInterrupts();
    saved = OSGetCurrentContext();
    OSClearContext(&tmp);
    OSSetCurrentContext(&tmp);

    OSReport("- FPR -----------------------------------------------\n");

    for (i = 0; i < 32; i++) {
        f64 fval = ctx->fpr[i];
        OSReport("R%02d=%08X:%08X (%e)\n", i, *(u32*) &ctx->fpr[i],
                 *((u32*) &ctx->fpr[i] + 1), fval);
    }

    OSReport("- PSF -----------------------------------------------\n");

    i = 0;
    p = (u8*) ctx;
    do {
        u32 val0 = ((u32*) p)[0x24];
        u32 val1 = ((u32*) p)[0x25];
        OSReport("R%02d=%08X:%08X (%e, %e)\n", i, val0, val1, ((f32*) p)[0x24],
                 ((f32*) p)[0x25]);
        i++;
        p += 8;
    } while (i < 32);

    OSClearContext(&tmp);
    OSSetCurrentContext(saved);
    OSRestoreInterrupts(irq);
}

/// unused function to force data ordering for these report strings
static void unused(OSContext* ctx)
{
    OSReport("- MISC ----------------------------------------------\n");
    OSReport("SRR0=%08X SRR1=%08X\n", ctx->srr0, ctx->srr1);
    OSReport("CR  =%08X LR  =%08X\n", ctx->cr, ctx->lr);
    OSReport("CTR =%08X XER =%08X\n", ctx->ctr, ctx->xer);
    OSReport("FPSCR=%08X\n", ctx->fpscr);
    OSReport("GQR%d=%08X GQR%d=%08X\n", 0, ctx->gqr[0], 1, ctx->gqr[1]);
}

void Exception_ReportStackTrace(OSContext* ctx, int max_depth)
{
    u32 i;
    u32* sp;

    OSReport("- STACK ---------------------------------------------\n");
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

void fn_80394DF4(void* node_ptr)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    ExcptNode* node = node_ptr;
    ExcptNode* prev;
    ExcptNode* head;
    ExcptNode** head_ptr;

    if (node == NULL || (head = *(head_ptr = (ExcptNode**) &sp->xD0)) == NULL)
    {
        return;
    }
    if (head == node) {
        *head_ptr = head->next;
        node->next = NULL;
        sp->x0_b5 = 1;
        return;
    }
    prev = head;
    while (prev != NULL) {
        if (prev->next == node) {
            prev->next = node->next;
            node->next = NULL;
            sp->x0_b5 = 1;
            return;
        }
        prev = prev->next;
    }
}

extern struct lbl_8040BEC4_t {
    UNK_T x0; // next?
    void (*x4)(struct lbl_8040BEC4_t*);
    UNK_T x8;
    UNK_T xC;
    int x10;
    int x14;
    u32 pad;
} lbl_8040BEC4;

extern struct lbl_8040B904_t {
    UNK_T x0;
    void (*x4)(struct lbl_8040B904_t*);
    UNK_T x8;
    UNK_T xC;
} lbl_8040B904;

static void hsd_80394E8C(struct lbl_8040B904_t* node_ptr)
{
    struct lbl_8040B904_t** head;

    if (hsd_804D78C8 < 1) {
        return;
    }
    head = (void*) &hsd_804CF810.xD0;
    if (*head == node_ptr) {
        return;
    }
    if (*head == NULL) {
        *head = node_ptr;
        node_ptr->x0 = NULL;
    } else {
        fn_80394DF4(node_ptr);
        node_ptr->x0 = (*head)->x0;
        (*head)->x0 = NULL;
        *head = node_ptr;
    }
    if (node_ptr->x4 != NULL) {
        node_ptr->x4(node_ptr);
    }
    hsd_804CF810.x0_b5 = 1;
}

// @TODO: Currently 94.46% match - BSS relocation and register allocation
// differences remain
void hsd_80394F48(void* data)
{
    u8* base_color = (u8*) &lbl_8040AB00;
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
    x_base = col_start * 11 + 0x14;
    hi_color = base_color + 0x20;
    cur_row = row_start - 1;

    for (i = 0; dp->entries[i] != 0; i++) {
        *px4 = x_base;
        *px8 = (*px40 - 0x28) - (cur_row-- + 1) * 14;

        b6 = sp->x0_b6;
        if (sp->x0_b7 != 0) {
            hsd_803922FC(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8, b6,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        } else {
            hsd_803921B8(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        }

        if (i == dp->index) {
            *px50 = hi_color;
        } else {
            *px50 = base_color;
        }

        *px4 += 11;
        hsd_80394434(dp->entries[i]);

        *px4 += strlen(dp->entries[i]) * 11;
        *px50 = base_color;

        b6 = sp->x0_b6;
        if (sp->x0_b7 != 0) {
            hsd_803922FC(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8, b6,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        } else {
            hsd_803921B8(((ParticleFontData*) sp->x4C)->x1B20, *px4, *px8,
                         (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44, *px50);
        }
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
                             b6, (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44,
                             *px50);
            } else {
                hsd_803921B8(((ParticleFontData*) sp->x4C)->x9D8, *px4, *px8,
                             (&sp->x24)[sp->x34], sp->x3C, *px40, sp->x44,
                             *px50);
            }
            j++;
            *px4 += 11;
        }
    }

    b6 = hsd_804CF810.x0_b6;
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

extern u8 lbl_8040B8AC[];

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
    *p = &lbl_8040AB20;
    val_x20 = sp->x20;
    val_x1C = sp->x1C;
    sp->x4 = (val_x20 - 21) * 11 + 20;
    sp->x8 = (sp->x40 - 40) - (val_x1C + 1) * 14;
    if (hsd_804D78C8 >= 1) {
        hsd_80394434("<< Push START Button >>");
    }
    *p = saved;
}

static struct {
    ExcptNode* x0;
    UNK_T x4;
    UNK_T x8;
    UNK_T xC;
    UNK_T x10;
} lbl_8040B8C4 = {
    0x00000000, 0x00000000, hsd_80395644, hsd_803956D8, 0x00000000,
};

static void hsd_803957C0_inline(void)
{
    hsd_80394434("<<PUSH START BUTTON TO SEE INSTRUCTION>>");
}

struct lbl_8040B904_t lbl_8040B904 = {
    0x00000000,
    0x00000000,
    hsd_803957C0,
    hsd_80395A78,
};

s32 hsd_803956D8(void* disp_ptr)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    DispData* data = disp_ptr;
    s32 val;

    if (sp->xBC & 0x1000) {
        hsd_80394E8C(&lbl_8040B904);
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
                    hsd_80394E8C(&lbl_8040B904);
                }
            }
        }
        return 1;
    }
    return 0;
}

// @TODO: BSS relocation and register allocation differences remain
void hsd_803957C0(void* input)
{
    s32 col;
    s32 row;
    s32 b6;
    u8 ch;
    void* saved;
    PAD_STACK(24);

    col = hsd_804CF810.x0C + hsd_804CF810.x18;
    row = hsd_804CF810.x10 + hsd_804CF810.x14;

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

    saved = hsd_804CF810.x50;
    hsd_804CF810.x50 = &lbl_8040AB20;
    hsd_804CF810.x8 = (hsd_804CF810.x40 - 40) - (hsd_804CF810.x10 + 1) * 14;
    hsd_804CF810.x4 = col * 11 + 20;

    {
        struct ParticleScreenState* draw_sp = &hsd_804CF810;
        b6 = draw_sp->x0_b6;

        if (draw_sp->x0_b7) {
            hsd_803922FC((void*) ((u8*) draw_sp->x4C + (ch & 0x7F) * 0x38),
                         hsd_804CF810.x4, hsd_804CF810.x8, b6,
                         (&hsd_804CF810.x24)[draw_sp->x34], draw_sp->x3C,
                         hsd_804CF810.x40, hsd_804CF810.x44, hsd_804CF810.x50);
        } else {
            hsd_803921B8((void*) ((u8*) draw_sp->x4C + (ch & 0x7F) * 0x38),
                         hsd_804CF810.x4, hsd_804CF810.x8,
                         (&hsd_804CF810.x24)[draw_sp->x34], draw_sp->x3C,
                         hsd_804CF810.x40, hsd_804CF810.x44, hsd_804CF810.x50);
        }
    }

    if (hsd_804CF810.xD0 == input) {
        int x1C = hsd_804CF810.x1C;
        hsd_804CF810.x4 = (hsd_804CF810.x20 - 0x27) * 11 + 20;
        hsd_804CF810.x8 = (hsd_804CF810.x40 - 40) - (x1C + 1) * 14;
        hsd_803957C0_inline();
    }

    hsd_804CF810.x50 = saved;
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

extern struct lbl_8040BA5C_t {
    void* x0;
    u32 x4;
    void* x8;
    void* xC;
    char** x10;
    u32 x14;
} lbl_8040BA5C;

extern struct lbl_8040BAF0_t {
    /* 0x00 */ void* x0;
    /* 0x04 */ void* x4;
    /* 0x08 */ void* x8;
    /* 0x0C */ void* xC;
    /* 0x10 */ u32 x10;
} lbl_8040BAF0;

extern struct lbl_8040BC3C_t {
    /* 0x00 */ void* x0;
    /* 0x04 */ void* x4;
    /* 0x08 */ void* x8;
    /* 0x0C */ void* xC;
    /* 0x10 */ u32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ void* x18;
} lbl_8040BC3C;

bool hsd_80395A78(void)
{
    u32 bit;
    s32 new_col;
    s32 new_scroll;
    s32 sum;
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
            return true;
        case 0x4:
            if (hsd_804CF810.x10 > 0) {
                hsd_804CF810.x10 -= 1;
            } else if (hsd_804CF810.x14 > 0) {
                hsd_804CF810.x14 -= 1;
            } else {
                break;
            }
            return true;
        case 0x1:
            if (hsd_804CF810.x0C > 0) {
                hsd_804CF810.x0C -= 1;
            } else if (hsd_804CF810.x18 > 0) {
                hsd_804CF810.x18 -= 1;
            } else {
                break;
            }
            while (!(u8) hsd_80394128(hsd_804CF810.x0C + hsd_804CF810.x18,
                                      hsd_804CF810.x10 + hsd_804CF810.x14))
            {
                if (hsd_804CF810.x0C > 0) {
                    hsd_804CF810.x0C -= 1;
                } else if (hsd_804CF810.x18 > 0) {
                    hsd_804CF810.x18 -= 1;
                } else {
                    break;
                }
            }
            return true;
        case 0x2:
            new_col = hsd_804CF810.x0C;
            new_scroll = hsd_804CF810.x18;
            if ((u32) new_col < (u32) (hsd_804CF810.x20 - 1)) {
                new_col += 1;
            } else {
                new_scroll += 1;
            }
            sum = new_col + new_scroll;
            if ((u8) hsd_80394128(sum, hsd_804CF810.x10 + hsd_804CF810.x14)) {
                hsd_804CF810.x0C = new_col;
                hsd_804CF810.x18 = new_scroll;
                return true;
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
            return true;
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
            return true;
        case 0x1000:
            if ((ExcptNode*) &lbl_8040BA5C != NULL) {
                fn_80394DF4((ExcptNode*) &lbl_8040BA5C);
                ((ExcptNode*) &lbl_8040BA5C)->next =
                    (ExcptNode*) hsd_804CF810.xD0;
                hsd_804CF810.xD0 = (void*) &lbl_8040BA5C;
                if (((ExcptNode*) &lbl_8040BA5C)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BA5C)
                        ->callback((ExcptNode*) &lbl_8040BA5C);
                }
                hsd_804CF810.x0_b5 = 1;
            }
            return true;
        default:
            break;
        }
        bit <<= 1;
    }
    return false;
}

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

static inline void ps_clear_nodes(struct ParticleScreenState* sp)
{
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
}

bool hsd_80395D88(void* data)
{
    switch (hsd_80395550(data)) {
    case 1:
        return true;
    case 2: {
        u32 cmd = *(u32*) ((u8*) data + 0x14);
        switch (cmd) {
        case 0:
            hsd_804CF810.xBC = 8;
            return false;
        case 1:
            hsd_804CF810.xBC = 4;
            return false;
        case 2:
            hsd_804CF810.xBC = 1;
            return false;
        case 3:
            hsd_804CF810.xBC = 2;
            return false;
        case 4:
            hsd_804CF810.xBC = 0x100;
            goto remove_return_0;
        case 5:
            hsd_804CF810.xBC = 0x400;
        remove_return_0:
            ps_remove_node(&hsd_804CF810, data);
            return false;
        case 6: {
            int i;
            OSContext* ctx;
            OSContext** ctx_ptr;
            int saved;

            if (*(ctx_ptr = &hsd_804CF810.xD4) != NULL) {
                saved = hsd_80393D2C(1);
                ctx = *ctx_ptr;
                OSReport(
                    "- GPR -----------------------------------------------\n");
                i = 0;
                do {
                    OSReport("R%02d=%08X(%11d) R%02d=%08X(%11d)\n", i,
                             ctx->gpr[i], ctx->gpr[i], i + 0x10,
                             ctx->gpr[i + 0x10], ctx->gpr[i + 0x10]);
                    i++;
                } while (i < 0x10);
                hsd_80394950(*ctx_ptr);
                ctx = *ctx_ptr;
                OSReport(
                    "- MISC ----------------------------------------------\n");
                OSReport("SRR0=%08X SRR1=%08X\n", ((u32*) ctx)[0x198 / 4],
                         ((u32*) ctx)[0x19C / 4]);
                OSReport("CR  =%08X LR  =%08X\n", ((u32*) ctx)[0x80 / 4],
                         ((u32*) ctx)[0x84 / 4]);
                OSReport("CTR =%08X XER =%08X\n", ((u32*) ctx)[0x88 / 4],
                         ((u32*) ctx)[0x8C / 4]);
                OSReport("FPSCR=%08X\n", ((u32*) ctx)[0x194 / 4]);
                i = 0;
                do {
                    OSReport("GQR%d=%08X GQR%d=%08X\n", i, ((u32*) ctx)[i],
                             i + 4, ((u32*) ctx)[0x1B4 / 4 + i]);
                    i++;
                } while (i < 4);
                hsd_80393D2C(saved);
            }
            ps_remove_node(&hsd_804CF810, data);
            return true;
        }
        case 7:
            hsd_80394E8C((void*) &lbl_8040BEC4);
            return true;
        case 8:
            ps_clear_nodes(&hsd_804CF810);
            return true;
        default:
            break;
        }
        break;
    }
    case -1:
        ps_remove_node(&hsd_804CF810, data);
        return true;
    }
    return false;
}

extern char lbl_8040B938[];
extern char lbl_8040B954[];
extern char lbl_8040B970[];
extern char lbl_8040B98C[];
extern char lbl_8040B9A8[];
extern char lbl_8040B9C4[];
extern char lbl_8040B9E0[];
extern char lbl_8040B9FC[];
extern char lbl_8040BA18[];

static char* lbl_8040BA34[] = {
    "MOVE CURSOR UP        (UP)", "MOVE CURSOR DOWN    (DOWN)",
    "MOVE CURSOR LEFT    (LEFT)", "MOVE CURSOR RIGHT  (RIGHT)",
    "MEM DUMP AT CURSOR     (A)", "MEM DUMP               (X)",
    "DUMP CPU CONTEXT          ", "SPR                       ",
    "QUIT                      ", NULL,
};

struct lbl_8040BA5C_t lbl_8040BA5C = {
    0, 0, hsd_80394F48, hsd_80395D88, lbl_8040BA34,
};

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

extern struct lbl_8040BAF0_t lbl_8040BAF0;

static inline s32 hsd_80396188_calc_col(void)
{
    return ((hsd_804CF810.x20 - 0x2E) / 2) * 11 + 20;
}

// @TODO: Currently 96.11% match - needs register allocation fix
static inline void hsd_80396188_draw_rows(char* buf, s32 col, u32** addr,
                                          s32* i)
{
    s32* x8 = &hsd_804CF810.x8;
    s32* x4 = &hsd_804CF810.x4;
    s32* x40 = &hsd_804CF810.x40;

    hsd_80394434(lbl_804D62CC);
    *i = 0;
    do {
        s32 row = 4 - *i;
        *x4 = col;
        *x8 = (*x40 - 0x28) - (row + 1) * 14;
        sprintf(buf, lbl_804D62D0, *addr, (*addr)[0], (*addr)[1], (*addr)[2],
                (*addr)[3]);
        hsd_80394434(buf);
        {
            u32 memsize = OSGetPhysicalMemSize();
            *addr = (u32*) ((((u32) *addr & 0x0FFFFFFF) + memsize + 0x10) %
                                memsize +
                            0x80000000);
        }
        (*i)++;
    } while (*i < 4);
    *x4 = col;
}

void hsd_80396188(void)
{
    void* saved;
    s32 col;
    s32 i;
    u32* addr;
    char buf[64];
    void* tmp;
    PAD_STACK(20);

    addr = (u32*) lbl_8040BAF0.x10;
    saved = hsd_804CF810.x50;
    col = ((hsd_804CF810.x20 - 0x2E) / 2) * 11 + 20;
    hsd_804CF810.x50 = &lbl_8040AB00;
    hsd_804CF810.x4 = col;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 0x7C;
    hsd_80396188_draw_rows(buf, col, &addr, &i);
    hsd_804CF810.x8 = hsd_804CF810.x40 - 0x36;
    hsd_80394434(lbl_804D62D4);
    hsd_804CF810.x50 = saved;
}

extern struct lbl_8040BA5C_t lbl_8040BBE8;

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
    while (bit <= hsd_804CF810.xBC) {
        switch (hsd_804CF810.xBC & bit) {
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
            ps_remove_node(&hsd_804CF810, data);
            hsd_804CF810.x0C = 0;
            hsd_804CF810.x10 = 0;
            hsd_804CF810.x18 = 0;
            hsd_804CF810.x14 = 0;
            return 1;
        case 0x100:
            lbl_8040BC3C.x10 = (s32) lbl_8040BAF0.x10;
            lbl_8040BC3C.x18 = &lbl_8040BAF0;
            if (&lbl_8040BC3C != NULL) {
                fn_80394DF4(&lbl_8040BC3C);
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
        case 0x200:
            ps_remove_node(&hsd_804CF810, data);
            return 1;
        case 0x1000:
            if (&lbl_8040BBE8 != NULL) {
                fn_80394DF4((void*) &lbl_8040BBE8);
                ((ExcptNode*) &lbl_8040BBE8)->next =
                    (ExcptNode*) hsd_804CF810.xD0;
                hsd_804CF810.xD0 = (ExcptNode*) &lbl_8040BBE8;
                if (((ExcptNode*) &lbl_8040BBE8)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BBE8)
                        ->callback((ExcptNode*) &lbl_8040BBE8);
                }
                hsd_804CF810.x0_b5 = 1;
            }
            return 1;
        default:
            bit <<= 1;
            break;
        }
    }
    return 0;
}

struct lbl_8040BAF0_t lbl_8040BAF0 = {
    0x00000000, hsd_80396130, hsd_80396188, hsd_803962A8, 0x00000000,
};

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

static char* lbl_8040BBC8[] = {
    "ADDRESS - 10h      (UP)", "ADDRESS + 10h    (DOWN)",
    "ADDRESS - 40h    (LEFT)", "ADDRESS + 40h   (RIGHT)",
    "NEW ADDRESS         (A)", "DUMP TO CONSOLE     (X)",
    "CLOSE               (B)", NULL,
};

struct lbl_8040BA5C_t lbl_8040BBE8 = {
    0x00000000,   0x00000000,   hsd_80394F48,
    hsd_803966A0, lbl_8040BBC8, 0x00000000,
};

static char* lbl_804D62F4 = "+--------------------------+";
static char* lbl_804D62F8 = "| INPUT ADDRESS : 8%07X |";

void hsd_80396884(void)
{
    char buf[32];
    s32 b6;
    s32 x_base;
    u8 ch;
    void* saved;
    PAD_STACK(28);

    x_base = (hsd_804CF810.x20 - 30) / 2;
    sprintf(buf, lbl_804D62F8, lbl_8040BC3C.x10 & 0x0FFFFFFF);
    saved = hsd_804CF810.x50;
    hsd_804CF810.x50 = &lbl_8040AB00;
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 82;
    hsd_80394434(lbl_804D62F4);
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 68;
    hsd_80394434(buf);
    hsd_804CF810.x4 = x_base * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 54;
    hsd_80394434(lbl_804D62F4);
    hsd_804CF810.x4 = (lbl_8040BC3C.x14 + 19 + x_base) * 11 + 20;
    hsd_804CF810.x8 = hsd_804CF810.x40 - 68;
    hsd_804CF810.x50 = &lbl_8040AB20;
    b6 = hsd_804CF810.x0_b6;
    ch = *(&buf[19] + lbl_8040BC3C.x14);
    if (hsd_804CF810.x0_b7) {
        void* bitmap = (void*) ((u8*) hsd_804CF810.x4C + (ch & 0x7F) * 0x38);
        s32 x = hsd_804CF810.x4;
        s32 dst = (&hsd_804CF810.x24)[hsd_804CF810.x34];
        hsd_803922FC(bitmap, x, hsd_804CF810.x8, b6, dst, hsd_804CF810.x3C,
                     hsd_804CF810.x40, hsd_804CF810.x44, hsd_804CF810.x50);
    } else {
        void* bitmap = (void*) ((u8*) hsd_804CF810.x4C + (ch & 0x7F) * 0x38);
        s32 x = hsd_804CF810.x4;
        s32 dst = (&hsd_804CF810.x24)[hsd_804CF810.x34];
        hsd_803921B8(bitmap, x, hsd_804CF810.x8, dst, hsd_804CF810.x3C,
                     hsd_804CF810.x40, hsd_804CF810.x44, hsd_804CF810.x50);
    }
    hsd_804CF810.x50 = saved;
}

extern struct lbl_8040BC3C_t lbl_8040BC3C;

extern struct lbl_8040BA5C_t lbl_8040BD74;

s32 hsd_80396A20(void* data)
{
    ExcptNode* node = data;
    u32 val = lbl_8040BC3C.x10;
    s32 shift = 24 - (lbl_8040BC3C.x14 * 4);
    u32 bit = 1;
    s32 mask = 0xF << shift;

    while (bit <= hsd_804CF810.xBC) {
        switch (hsd_804CF810.xBC & bit) {
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
                lbl_8040BC3C.x14--;
            }
            return 1;
        case 0x2:
            if (lbl_8040BC3C.x14 < 5) {
                lbl_8040BC3C.x14++;
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
            ps_remove_node(&hsd_804CF810, node);
            return 1;
        case 0x1000: {
            if (&lbl_8040BD74 != NULL) {
                fn_80394DF4(&lbl_8040BD74);
                lbl_8040BD74.x0 = hsd_804CF810.xD0;
                hsd_804CF810.xD0 = &lbl_8040BD74;
                if (((ExcptNode*) &lbl_8040BD74)->callback != NULL) {
                    ((ExcptNode*) &lbl_8040BD74)
                        ->callback((void*) &lbl_8040BD74);
                }
                hsd_804CF810.x0_b5 = 1;
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

struct lbl_8040BC3C_t lbl_8040BC3C = {
    0x00000000, hsd_80396868, hsd_80396884, hsd_80396A20,
    0x00000000, 0x00000000,   0x00000000,
};

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

static char* lbl_8040BD54[] = {
    "DECREMENT NUM AT CURSOR   (UP)", "INCREMENT NUM AT CURSOR (DOWN)",
    "MOVE CURSOR TO LEFT     (LEFT)", "MOVE CURSOR TO RIGHT   (RIGHT)",
    "MEMORY DUMP                (A)", "CLEAR NUM AT CURSOR        (X)",
    "CLOSE                      (B)", NULL,
};

struct lbl_8040BA5C_t lbl_8040BD74 = {
    0x00000000, 0x00000000, hsd_80394F48, hsd_80396C78, lbl_8040BD54,
};

static char* lbl_804D62FC = "+- DBAT ------------------------+";
static char* lbl_804D6300 = "+- IBAT ------------------------+";

static char* lbl_804D6304 = "| %d BL xxxxxxxxxxx  %c%c %c%c%c%c %s |";
static char* lbl_804D6308 = "|   BEPI %08X BRPN %08X |";
static char* lbl_804D630C = "+-------------------------------+";

// @TODO: Currently 86.10% match - .bss.0 relocation affects register
// allocation
void hsd_80396E40(int keycode)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
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

    saved = hsd_804CF810.x50;
    row = sp->x1C - 1;
    hsd_804CF810.x50 = &lbl_8040AB00;
    hsd_804CF810.x4 = 0x106;
    hsd_804CF810.x8 = (hsd_804CF810.x40 - 0x28) - (row + 1) * 14;
    row--;
    if (keycode < 0x220 && keycode >= 0x218) {
        hsd_80394434(lbl_804D62FC);
    } else {
        hsd_80394434(lbl_804D6300);
    }
    i = 0;
    spr_u = 0x219;
    spr_l = 0x218;
    do {
        bat_u = baselib_mfspr(spr_u);
        bat_l = baselib_mfspr(spr_l);
        switch (bat_u & 2) {
        case 0:
            perm = "N/A";
            break;
        case 2:
            perm = "R/W";
            break;
        default:
        case 1:
            perm = "R/O";
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
        sprintf(buf, lbl_804D6304, i, var_s, var_u, var_w, var_i, var_m, var_g,
                perm);
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
        hsd_804CF810.x4 = 0x106;
        hsd_804CF810.x8 = (hsd_804CF810.x40 - 0x28) - (row + 1) * 14;
        row--;
        hsd_80394434(buf);
        sprintf(buf, lbl_804D6308, bat_l & 0xFFFC0000, bat_u & 0xFFFC0000);
        hsd_804CF810.x4 = 0x106;
        hsd_804CF810.x8 = (hsd_804CF810.x40 - 0x28) - (row + 1) * 14;
        row--;
        hsd_80394434(buf);
        i++;
        spr_u += 2;
        spr_l += 2;
    } while (i < 4);
    hsd_804CF810.x4 = 0x106;
    hsd_804CF810.x8 = (hsd_804CF810.x40 - 0x28) - (row + 1) * 14;
    hsd_80394434(lbl_804D630C);
    hsd_804CF810.x50 = saved;
}

void fn_803970D8(int unused) {}

void fn_803970DC(int unused) {}

void fn_803970E0(int unused) {}

void fn_803970E4(int unused) {}

void fn_803970E8(int unused) {}

void fn_803970EC(int unused) {}

void fn_803970F0(int unused) {}

void fn_803970F4(int unused) {}

void fn_803970F8(int unused) {}

void fn_803970FC(int unused) {}

void fn_80397100(int unused) {}

void fn_80397104(int unused) {}

void fn_80397108(int unused) {}

static void fn_8039710C(struct lbl_8040BEC4_t* unused) {}

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

void hsd_80397110(void)
{
    struct ParticleScreenState* sp = &hsd_804CF810;
    struct lbl_8040AB00_t* saved;
    u32 offset;
    void** px50 = &sp->x50;
    s32* px4 = &sp->x4;
    s32* px40 = &sp->x40;
    s32* px8 = &sp->x8;
    char buf[32];
    s32 row;
    u32 i;
    struct SPREntry* spr_entry;
    char* padding;
    PAD_STACK(32);

    saved = *px50;
    row = sp->x1C - 1;
    *px50 = &lbl_8040AB00;
    *px4 = 20;
    *px8 = (*px40 - 0x28) - (row-- + 1) * 14;
    hsd_80394434(SPR_BOX_TOP());
    *px4 = 20;
    *px8 = (*px40 - 0x28) - (row-- + 1) * 14;
    hsd_80394434(SPR_BOX_HEADER());
    {
        i = 0;
        offset = 0;
        while (row > 0) {
            u32 spr_off = lbl_8040BEC4.x10;
            if (spr_off + i >= 0x45) {
                break;
            }
            spr_entry =
                (struct SPREntry*) ((unsigned char*) (lbl_8040ADD8 + spr_off) +
                                    offset);
            if (i == lbl_8040BEC4.x14) {
                if (spr_entry->callback != 0) {
                    spr_entry->callback(spr_entry->spr);
                }
                *px50 = &lbl_8040AB20;
            } else {
                *px50 = &lbl_8040AB00;
            }
            *px4 = 20;
            *px8 = (*px40 - 0x28) - (row-- + 1) * 14;
            if (spr_entry->spr == 0) {
                hsd_80394434(SPR_GEKKO_ONLY());
            } else {
                s32 name_len = strlen(spr_entry->name);
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
                sprintf(buf, SPR_VALUE_FMT(), spr_entry->spr, spr_entry->name,
                        padding, baselib_mfspr(spr_entry->spr));
                hsd_80394434(buf);
            }
            offset += sizeof(*spr_entry);
            i++;
        }
    }
    *px50 = &lbl_8040AB00;
    while (row > 0) {
        *px4 = 20;
        *px8 = (*px40 - 0x28) - (row-- + 1) * 14;
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
    u32 bit = 1;
    u32 spr_off = lbl_8040BEC4.x10;
    u32 sel = lbl_8040BEC4.x14;

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
            lbl_8040BEC4.x10 = spr_off;
            lbl_8040BEC4.x14 = sel;
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
            lbl_8040BEC4.x10 = spr_off;
            lbl_8040BEC4.x14 = sel;
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

// @TODO: Currently 99.78% match - register allocation differences remain
void hsd_803975D4(void)
{
    struct ParticleInputState {
        u8 _pad[0x54];
        PADStatus pads[8];
        s32 port;
        s32 repeat;
    };
    struct ParticleScreenState* sp = &hsd_804CF810;
    PADStatus* cur_pads;
    PADStatus* pads;
    u32 reset_mask;
    s32 port;
    u16 buttons;
    u16 changed;
    u32 new_press;

    reset_mask = 0;
    if (OSGetResetSwitchState() != 0) {
        sp->xC4 = 1;
    } else if (sp->xC4 != 0) {
        OSResetSystem(1, 0, 0);
        for (;;) {
        }
    }
    cur_pads = (PADStatus*) sp->_pad4;
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
    for (port = 0; port < 4; port++) {
        if ((s8) sp->_pad4[0x3A + port * 0xC] == 0 &&
            (s8) sp->_pad4[0xA + port * 0xC] == 0)
        {
            break;
        }
    }
    if (port == 4) {
        sp->xBC = 0;
        sp->xC0 = 0;
        return;
    }
    ((struct ParticleInputState*) sp)->port = port;
    pads = ((struct ParticleInputState*) sp)->pads;
    buttons = pads[((struct ParticleInputState*) sp)->port].button;
    changed =
        pads[((struct ParticleInputState*) sp)->port + 4].button ^ buttons;
    sp->xC0 = buttons;
    new_press = (u16) (buttons & changed);
    if (new_press != 0) {
        ((struct ParticleInputState*) sp)->repeat = 0;
    } else if (pads[((struct ParticleInputState*) sp)->port].button != 0) {
        ((struct ParticleInputState*) sp)->repeat += 1;
        if (((struct ParticleInputState*) sp)->repeat > 30) {
            new_press = pads[((struct ParticleInputState*) sp)->port].button;
        }
    }
    sp->xBC = new_press;
}

static inline PSNode* ps_node_child(PSNode* node)
{
    return node->child;
}

struct lbl_8040BEC4_t lbl_8040BEC4 = {
    0x00000000,
    fn_8039710C,
    hsd_80397110,
    fn_80397374,
};

void* fn_80397814(void* arg)
{
    u8* base = (u8*) &lbl_8040AB00;
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
    keybuf = &hsd_804CF810.xC0;
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
    hsd_804CF810.xD4 = ctx;
    VIConfigure(hsd_804CF810.x30);
    VISetBlack(0);

    /* Clear display list */
    {
        ExcptNode** head = (ExcptNode**) &hsd_804CF810.xD0;
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
    if (&lbl_8040B8C4 != NULL) {
        ((ExcptNode*) &lbl_8040B8C4)->next = NULL;
        hsd_804CF810.xD0 = &lbl_8040B8C4;
        if (((ExcptNode*) &lbl_8040B8C4)->callback != NULL) {
            ((ExcptNode*) &lbl_8040B8C4)->callback((ExcptNode*) &lbl_8040B8C4);
        }
    }

    /* Set initialized flag */
    hsd_804CF810.x0_b5 = 1;
    hsd_80394668();

    /* Initial display setup */
    {
        u32 retrace2;
        u32 next_retrace2;
        s32* size_ptr;
        void* lbl_ptr;
        s32 fb_idx;
        PSNode* node;

        hsd_80394544(hsd_804CF810.x18, hsd_804CF810.x14, hsd_804CF810.x20,
                     hsd_804CF810.x1C, 20, hsd_804CF810.x40 - 40,
                     (&hsd_804CF810.x24)[hsd_804CF810.x34], hsd_804CF810.x3C,
                     hsd_804CF810.x40, hsd_804CF810.x44, (s32) lbl_804088B8,
                     NULL);

        hsd_804CF810.xC8 = 0;
        hsd_804CF810.xCC = hsd_804CF810.x1C - 1;

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
        fb_idx = hsd_804CF810.x34;
        DCFlushRange((void*) (&hsd_804CF810.x24)[fb_idx], *size_ptr);
        fb_idx = hsd_804CF810.x34;
        VISetNextFrameBuffer((void*) (&hsd_804CF810.x24)[fb_idx]);
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
                    switch (result) {
                    case 0:
                        break;
                    default:
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
                s32 idx = hsd_804CF810.x34;
                idx = (idx + 1) % hsd_804CF810.x38;
                hsd_804CF810.x34 = idx;

                hsd_80394668();

                hsd_80394544(
                    hsd_804CF810.x18, hsd_804CF810.x14, hsd_804CF810.x20,
                    hsd_804CF810.x1C, 20, hsd_804CF810.x40 - 40,
                    (&sp->x24)[hsd_804CF810.x34], hsd_804CF810.x3C,
                    hsd_804CF810.x40, hsd_804CF810.x44, (s32) lbl_ptr, NULL);

                hsd_804CF810.xC8 = 0;
                hsd_804CF810.xCC = hsd_804CF810.x1C - 1;

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
                fb_idx = hsd_804CF810.x34;
                DCFlushRange((void*) (&sp->x24)[fb_idx], *size_ptr);
                fb_idx = hsd_804CF810.x34;
                VISetNextFrameBuffer((void*) (&sp->x24)[fb_idx]);
                VIFlush();
            }

            do {
                next_retrace2 = VIGetRetraceCount();
            } while (next_retrace2 == retrace2);
            retrace2 = next_retrace2;
        }
    }

    OSPanic("debugconsole_main.c", 2228, "debug thread finished.");

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
