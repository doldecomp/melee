#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>

// Cpu2Efb methods.

// From GXEnum.h

#define PE_POKE_ZMODE_ID 0
#define PE_POKE_CMODE0_ID 1
#define PE_POKE_CMODE1_ID 2
#define PE_POKE_AMODE0_ID 3
#define PE_POKE_AMODE1_ID 4

#define PI_MEMSP_EFB 0x08000000

static void (*GXMisc_804D7320)(u16);
static GXDrawDoneCallback GXMisc_804D7324;
static GXBool GXMisc_804D7328[0x4];
static OSThreadQueue GXDrawDoneThreadQueue;

static inline void GXSetMisc_inline_1(u16 arg0)
{
    __GXContexts.main->x4 = arg0;
}

static inline void GXSetMisc_inline_2(void)
{
    GXContext* gx = __GXContexts.main;
    gx->x0.u16[0] = !gx->x4;
    set_x2(GX_TRUE);
}

static inline void GXSetMisc_inline_3(void)
{
    GXContext* gx = __GXContexts.main;

    if (gx->x4) {
        gx->x4F0_flags |= 8;
    }
}

void GXSetMisc(s32 arg0, u32 arg1)
{
    switch (arg0) {
    case 0:
        break;
    case 1:
        GXSetMisc_inline_1(arg1);
        GXSetMisc_inline_2();
        GXSetMisc_inline_3();
        break;
    case 2:
        __GXContexts.main->x4ED = arg1 != 0;
        break;
    }
}

void GXSetDrawDone(void)
{
    u16 i;
    bool interrupt_enabled = OSDisableInterrupts();
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x45000002;

    if (__GXContexts.main->x4F0_flags != 0) {
        __GXSetDirtyState();
    }

    for (i = 0; i < 8; i++) {
        WGPIPE.u32 = 0;
    }

    PPCSync();
    GXMisc_804D7328[0] = GX_FALSE;
    OSRestoreInterrupts(interrupt_enabled);
}

void GXWaitDrawDone(void)
{
    u32 interrupt_enabled = OSDisableInterrupts();

    while (!GXMisc_804D7328[0]) {
        OSSleepThread(&GXDrawDoneThreadQueue);
    }

    OSRestoreInterrupts(interrupt_enabled);
}

void GXPixModeSync(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x1D0[3]);
    set_x2(GX_FALSE);
}

/*
 * This function sets a threshold which is compared to the alpha of pixels
 * written to the Embedded Frame Buffer (EFB) using the GXPoke* functions. The
 * GXPoke* functions allow the CPU to write directly to the EFB.  The compare
 * function order is: src_alpha  func  threshold for example: src_alpha > 0x80
 * The alpha compare function can be used to conditionally write pixels to the
 * EFB using the source alpha channel as a template. If the compare function is
 * true, the source color will be written to the EFB based on the result of the
 * Z compare (see GXPokeZMode). If the alpha compare function is false, the
 * source color is not written to the EFB. The alpha compare test happens
 * before the Z compare and before blending (see GXPokeBlendMode).
 */
void GXPokeAlphaMode(GXCompare func, u8 threshold)
{
    __peReg[PE_POKE_AMODE0_ID] = (func << 8) | (threshold & 0xFF);
}

/*
 * This function determines what value of alpha will be read from the Embedded
 * Frame Buffer (EFB).The mode only applies to GXPeek* functions.  The GXPeek*
 * functions allow the CPU to directly read the EFB. Note that this feature
 * works no matter what pixel type (see GXSetPixelFmt) you are using. If you
 * are using the EFB with alpha plane, it is recommended that you should use
 * GX_READ_NONE so that you can read correct alpha value from the EFB. If you
 * are using the EFB with no alpha, you should set either of GX_READ_00 or
 * GX_READ_FF in order to get certain value.
 */
void GXPokeAlphaRead(s32 mode)
{
    __peReg[PE_POKE_AMODE1_ID] = (mode & ~0x4) | 0x4;
}

/*
 * This function enables or disables alpha-buffer updates for GXPoke*
 * functions. The normal rendering state (GXSetAlphaUpdate) is not effected.
 */
void GXPokeAlphaUpdate(bool update_enable)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit11 = update_enable (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] =
        (old & ~0x10) | ((update_enable << 4) & 0xFF0);
}

/*
 * This function determines how the source image, written using the GXPoke*
 * functions, is blended with the current Embedded Frame Buffer (EFB). When
 * type is set to GX_CM_NONE, no color data is written to the EFB.  When type
 * is set to GX_CM_BLEND, the source and EFB pixels are blended using the
 * following equation: dst_pix_clr = src_pix_clr * src_factor + dst_pix_clr *
 * dst_factor The dst_factor can be used only when the frame buffer has
 * GX_PF_RGBA6_Z24 as the pixel format (see GXSetPixelFmt). When type is set to
 * GX_CM_LOGIC, the source and EFB pixels are blended using logical bitwise
 * operations. This function does not effect the normal rendering state,
 * GXSetBlendMode.
 *
 * HW2 adds a new type: GX_BM_SUBTRACT.    When this type is used, the
 * destination pixel is computed as follows: dst_pix_clr = dst_pix_clr -
 * src_pix_clr [clamped to zero] Note that src_factor and dst_factor are not
 * part of the equation.
 */
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor,
                     GXBlendFactor dst_factor, GXLogicOp op)
{
    u32 old = __peReg[PE_POKE_CMODE0_ID];

    INSERT_FIELD(old, type == GX_BM_BLEND || type == GX_BM_SUBTRACT, 1, 0);
    INSERT_FIELD(old, type == GX_BM_SUBTRACT, 1, 11);
    INSERT_FIELD(old, type == GX_BM_LOGIC, 1, 1);
    INSERT_FIELD(old, op, 4, 12);
    INSERT_FIELD(old, src_factor, 3, 8);
    INSERT_FIELD(old, dst_factor, 3, 5);
    INSERT_FIELD(old, 0x41, 8, 24);

    __peReg[PE_POKE_CMODE0_ID] = old;
}

/*
 * This function enables or disables color-buffer updates when writing the
 * Embedded Frame Buffer (EFB) using the GXPoke* functions.  The GXPoke*
 * functions allow direct access the the EFB by the CPU.
 */
void GXPokeColorUpdate(bool update_enable)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit12 = update_enable (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] = (old & ~8) | (((update_enable) << 3) & 0x7F8);
}

/*
 * This function sets a constant alpha value for writing to the Embedded Frame
 * Buffer (EFB) using the GXPoke* functions. The GXPoke* functions allow the
 * CPU direct access to the EFB. The EFB pixel type must have an alpha channel
 * for this function to be effective, see GXSetPixelFmt. The blending
 * operations (see GXPokeBlendMode) still use source alpha but when writing the
 * pixel color, the constant alpha will replace the pixel alpha in the EFB.
 */
void GXPokeDstAlpha(bool enable, u8 alpha)
{
    __peReg[PE_POKE_CMODE1_ID] = alpha | ((enable << 8) & 0xFF00 & ~0xFF);
}

/*
 * The dither enable is only valid when the pixel format (see GXSetPixelFmt) is
 * either GX_PF_RGBA6_Z24 or GX_PF_RGB565_Z16. This function enables dithering
 * when writing the Embedded Frame Buffer (EFB) using GXPoke* functions.  The
 * GXPoke* functions allow the CPU to write directly to the EFB. A 4x4 Bayer
 * matrix is used for dithering.
 */
void GXPokeDither(s32 dither)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit13 = dither (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] = (old & ~4) | ((dither << 2) & 0x3FC);
}

/*
 * This function sets the Z-buffer compare mode when writing the Embedded Frame
 * Buffer (EFB) using the GXPoke* functions.   The GXPoke* functions allow the
 * CPU to directly write the EFB. The result of the Z compare is used to
 * conditionally write color values to the EFB.   The Z value will be updated
 * according to the result of the compare if Z update is enabled. When
 * compare_enable is set to GX_DISABLE, poke Z buffering is disabled and the Z
 * buffer is not updated. The func parameter determines the comparison that is
 * performed.  In the comparison function, the poked Z value is on the left
 * while the Z value from the Z buffer is on the right.  If the result of the
 * comparison is false, the poked Z value is discarded. The parameter
 * update_enable determines whether or not the Z buffer is updated with the new
 * Z value after a comparison is performed. The normal rendering Z mode
 * (GXSetZMode) is not affected by this function.
 */
void GXPokeZMode(bool compare_enable, GXCompare func, bool update_enable)
{
    __peReg[PE_POKE_ZMODE_ID] =
        ((((u8) compare_enable & ~0xE) | (func << 1)) & ~0x10) |
        ((update_enable * 0x10) & 0xFF0);
}

void GXTokenInterruptHandler(__OSInterrupt _, OSContext* current_ctx)
{
    u16 temp_r31 = __peReg[7];
    if (GXMisc_804D7320 != NULL) {
        OSContext temp_ctx;
        OSClearContext(&temp_ctx);
        OSSetCurrentContext(&temp_ctx);
        GXMisc_804D7320(temp_r31);
        OSClearContext(&temp_ctx);
        OSSetCurrentContext(current_ctx);
    }
    __peReg[5] = (__peReg[5] & ~4) | 4;
}

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb)
{
    GXDrawDoneCallback previous = GXMisc_804D7324;
    bool intr = OSDisableInterrupts();
    GXMisc_804D7324 = cb;
    OSRestoreInterrupts(intr);
    return previous;
}

void GXFinishInterruptHandler(__OSInterrupt _, OSContext* current_ctx)
{
    __peReg[5] = (__peReg[5] & ~8) | 8;
    GXMisc_804D7328[0] = GX_TRUE;
    if (GXMisc_804D7324 != NULL) {
        OSContext temp_ctx;
        OSClearContext(&temp_ctx);
        OSSetCurrentContext(&temp_ctx);
        GXMisc_804D7324();
        OSClearContext(&temp_ctx);
        OSSetCurrentContext(current_ctx);
    }
    OSWakeupThread(&GXDrawDoneThreadQueue);
}

void __GXPEInit(void)
{
    __OSSetInterruptHandler(OS_INTR_PI_PE_TOKEN, GXTokenInterruptHandler);
    __OSSetInterruptHandler(OS_INTR_PI_PE_FINISH, GXFinishInterruptHandler);
    OSInitThreadQueue(&GXDrawDoneThreadQueue);
    __OSUnmaskInterrupts(0x2000);
    __OSUnmaskInterrupts(0x1000);
    __peReg[5] =
        ((((((((__peReg[5] & ~4) | 4) & ~8) | 8) & ~1) | 1) & ~2) | 2);
}
