#include <dolphin/gx/types.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GXFifo.h>
#include <dolphin/gx/__GXGeometry.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/base/PPCArch.h>
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

static unk_t lbl_804D7320;
static unk_t lbl_804D7324;
static GXBool lbl_804D7328[0x4];
static OSThreadQueue GXDrawDoneThreadQueue;

static inline void GXSetMisc_inline_1(u16 arg0)
{
    __GXContexts.main->x4 = arg0;
}

static inline void GXSetMisc_inline_2()
{
    GXContext *gx = __GXContexts.main;
    gx->x0.u16[0] = !gx->x4;
    set_x2(GX_TRUE);
}

static inline void GXSetMisc_inline_3()
{
    GXContext *gx = __GXContexts.main;

    if (gx->x4)
        gx->x4F0 |= 8;
}

void GXSetMisc(s32 arg0, u32 arg1)
{
    switch (arg0)
    {
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

void GXSetDrawDone()
{
    u16 i;
    BOOL interrupt_enabled = OSDisableInterrupts();
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x45000002;

    if (__GXContexts.main->x4F0 != 0)
        __GXSetDirtyState();

    for (i = 0; i < 8; i++)
        WGPIPE.u32 = 0;

    PPCSync();
    lbl_804D7328[0] = GX_FALSE;
    OSRestoreInterrupts(interrupt_enabled);
}

void GXWaitDrawDone()
{
    u32 interrupt_enabled = OSDisableInterrupts();

    while (!lbl_804D7328[0])
        OSSleepThread(&GXDrawDoneThreadQueue);

    OSRestoreInterrupts(interrupt_enabled);
}

void GXPixModeSync()
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    GX_WRITE_U32(__GXContexts.main->x1D0[3]);
    set_x2(GX_FALSE);
}

/*
 * This function sets a threshold which is compared to the alpha of pixels written to the Embedded Frame Buffer (EFB) using the GXPoke* functions. The GXPoke* functions allow the CPU to write directly to the EFB.  The compare function order is:
 * src_alpha  func  threshold
 * for example: src_alpha > 0x80
 * The alpha compare function can be used to conditionally write pixels to the EFB using the source alpha channel as a template. If the compare function is true, the source color will be written to the EFB based on the result of the Z compare (see GXPokeZMode).
 * If the alpha compare function is false, the source color is not written to the EFB.
 * The alpha compare test happens before the Z compare and before blending (see GXPokeBlendMode).
 */
void GXPokeAlphaMode(GXCompare func, u8 threshold)
{
    __peReg[PE_POKE_AMODE0_ID] = (func << 8) | (threshold & 0xFF);
}

/*
 * This function determines what value of alpha will be read from the Embedded Frame Buffer (EFB).The mode only applies to GXPeek* functions.  The GXPeek* functions allow the CPU to directly read the EFB.
 * Note that this feature works no matter what pixel type (see GXSetPixelFmt) you are using. If you are using the EFB with alpha plane, it is recommended that you should use GX_READ_NONE so that you can
 * read correct alpha value from the EFB. If you are using the EFB with no alpha, you should set either of GX_READ_00 or GX_READ_FF in order to get certain value.
 */
void GXPokeAlphaRead(s32 mode)
{
    __peReg[PE_POKE_AMODE1_ID] = (mode & ~0x4) | 0x4;
}

/*
 * This function enables or disables alpha-buffer updates for GXPoke* functions.  The normal rendering state (GXSetAlphaUpdate) is not effected.
 */
void GXPokeAlphaUpdate(BOOL update_enable)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit11 = update_enable (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] = old & ~0x10 | (update_enable << 4) & 0xFF0;
}

/*
 * This function determines how the source image, written using the GXPoke* functions, is blended with the current Embedded Frame Buffer (EFB).
 * When type is set to GX_CM_NONE, no color data is written to the EFB.  When type is set to GX_CM_BLEND, the source and EFB pixels are blended using the following equation:
 * dst_pix_clr = src_pix_clr * src_factor + dst_pix_clr * dst_factor
 * The dst_factor can be used only when the frame buffer has GX_PF_RGBA6_Z24 as the pixel format (see GXSetPixelFmt).
 * When type is set to GX_CM_LOGIC, the source and EFB pixels are blended using logical bitwise operations.
 * This function does not effect the normal rendering state, GXSetBlendMode.
 *
 * HW2 adds a new type: GX_BM_SUBTRACT.    When this type is used, the destination pixel is computed as follows:
 * dst_pix_clr = dst_pix_clr - src_pix_clr [clamped to zero]
 * Note that src_factor and dst_factor are not part of the equation.
 */
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op)
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
 * This function enables or disables color-buffer updates when writing the Embedded Frame Buffer (EFB) using the GXPoke* functions.  The GXPoke* functions allow direct access the the EFB by the CPU.
 */
void GXPokeColorUpdate(BOOL update_enable)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit12 = update_enable (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] = (old & ~8) | ((update_enable) << 3) & 0x7F8;
}

/*
 * This function sets a constant alpha value for writing to the Embedded Frame Buffer (EFB) using the GXPoke* functions.
 * The GXPoke* functions allow the CPU direct access to the EFB. The EFB pixel type must have an alpha channel for this function to be effective, see GXSetPixelFmt.
 * The blending operations (see GXPokeBlendMode) still use source alpha but when writing the pixel color, the constant alpha will replace the pixel alpha in the EFB.
 */
void GXPokeDstAlpha(BOOL enable, u8 alpha)
{
    __peReg[PE_POKE_CMODE1_ID] = alpha | (enable << 8) & 0xFF00 & ~0xFF;
}

/*
 * The dither enable is only valid when the pixel format (see GXSetPixelFmt) is either GX_PF_RGBA6_Z24 or GX_PF_RGB565_Z16.
 * This function enables dithering when writing the Embedded Frame Buffer (EFB) using GXPoke* functions.  The GXPoke* functions allow the CPU to write directly to the EFB.
 * A 4x4 Bayer matrix is used for dithering.
 */
void GXPokeDither(s32 dither)
{
    u16 old = __peReg[PE_POKE_CMODE0_ID];

    // PEReg[2].bit13 = dither (PowerPC bit-ordering)
    __peReg[PE_POKE_CMODE0_ID] = (old & ~4) | (dither << 2) & 0x3FC;
}

/*
 * This function sets the Z-buffer compare mode when writing the Embedded Frame Buffer (EFB) using the GXPoke* functions.   The GXPoke* functions allow the CPU to directly write the EFB.
 * The result of the Z compare is used to conditionally write color values to the EFB.   The Z value will be updated according to the result of the compare if Z update is enabled.
 * When compare_enable is set to GX_DISABLE, poke Z buffering is disabled and the Z buffer is not updated.
 * The func parameter determines the comparison that is performed.  In the comparison function, the poked Z value is on the left while the Z value from the Z buffer is on the right.  If the result of the comparison is false, the poked Z value is discarded.
 * The parameter update_enable determines whether or not the Z buffer is updated with the new Z value after a comparison is performed.
 * The normal rendering Z mode (GXSetZMode) is not affected by this function.
 */
void GXPokeZMode(BOOL compare_enable, GXCompare func, BOOL update_enable)
{
    __peReg[PE_POKE_ZMODE_ID] = ((u8)compare_enable & ~0xE | (func << 1)) & ~0x10 | ((update_enable * 0x10) & 0xFF0);
}

#pragma push
asm void GXTokenInterruptHandler()
{ // clang-format off
    nofralloc
/* 8033CE80 00339A60  7C 08 02 A6 */	mflr r0
/* 8033CE84 00339A64  90 01 00 04 */	stw r0, 4(r1)
/* 8033CE88 00339A68  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 8033CE8C 00339A6C  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 8033CE90 00339A70  93 C1 02 D8 */	stw r30, 0x2d8(r1)
/* 8033CE94 00339A74  7C 9E 23 78 */	mr r30, r4
/* 8033CE98 00339A78  80 0D BC 80 */	lwz r0, lbl_804D7320(r13)
/* 8033CE9C 00339A7C  80 6D BC 58 */	lwz r3, __peReg(r13)
/* 8033CEA0 00339A80  28 00 00 00 */	cmplwi r0, 0
/* 8033CEA4 00339A84  A3 E3 00 0E */	lhz r31, 0xe(r3)
/* 8033CEA8 00339A88  41 82 00 34 */	beq lbl_8033CEDC
/* 8033CEAC 00339A8C  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CEB0 00339A90  48 00 83 A5 */	bl OSClearContext
/* 8033CEB4 00339A94  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CEB8 00339A98  48 00 81 D5 */	bl OSSetCurrentContext
/* 8033CEBC 00339A9C  81 8D BC 80 */	lwz r12, lbl_804D7320(r13)
/* 8033CEC0 00339AA0  38 7F 00 00 */	addi r3, r31, 0
/* 8033CEC4 00339AA4  7D 88 03 A6 */	mtlr r12
/* 8033CEC8 00339AA8  4E 80 00 21 */	blrl 
/* 8033CECC 00339AAC  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CED0 00339AB0  48 00 83 85 */	bl OSClearContext
/* 8033CED4 00339AB4  7F C3 F3 78 */	mr r3, r30
/* 8033CED8 00339AB8  48 00 81 B5 */	bl OSSetCurrentContext
lbl_8033CEDC:
/* 8033CEDC 00339ABC  80 6D BC 58 */	lwz r3, __peReg(r13)
/* 8033CEE0 00339AC0  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 8033CEE4 00339AC4  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 8033CEE8 00339AC8  60 00 00 04 */	ori r0, r0, 4
/* 8033CEEC 00339ACC  B0 03 00 00 */	sth r0, 0(r3)
/* 8033CEF0 00339AD0  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 8033CEF4 00339AD4  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 8033CEF8 00339AD8  83 C1 02 D8 */	lwz r30, 0x2d8(r1)
/* 8033CEFC 00339ADC  7C 08 03 A6 */	mtlr r0
/* 8033CF00 00339AE0  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 8033CF04 00339AE4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void GXSetDrawDoneCallback()
{ // clang-format off
    nofralloc
/* 8033CF08 00339AE8  7C 08 02 A6 */	mflr r0
/* 8033CF0C 00339AEC  90 01 00 04 */	stw r0, 4(r1)
/* 8033CF10 00339AF0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033CF14 00339AF4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033CF18 00339AF8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033CF1C 00339AFC  7C 7E 1B 78 */	mr r30, r3
/* 8033CF20 00339B00  83 ED BC 84 */	lwz r31, lbl_804D7324(r13)
/* 8033CF24 00339B04  48 00 A4 41 */	bl OSDisableInterrupts
/* 8033CF28 00339B08  93 CD BC 84 */	stw r30, lbl_804D7324(r13)
/* 8033CF2C 00339B0C  48 00 A4 61 */	bl OSRestoreInterrupts
/* 8033CF30 00339B10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033CF34 00339B14  7F E3 FB 78 */	mr r3, r31
/* 8033CF38 00339B18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033CF3C 00339B1C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033CF40 00339B20  7C 08 03 A6 */	mtlr r0
/* 8033CF44 00339B24  38 21 00 18 */	addi r1, r1, 0x18
/* 8033CF48 00339B28  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/PoUPM
#pragma push
asm void GXFinishInterruptHandler()
{ // clang-format off
    nofralloc
/* 8033CF4C 00339B2C  7C 08 02 A6 */	mflr r0
/* 8033CF50 00339B30  38 60 00 01 */	li r3, 1
/* 8033CF54 00339B34  90 01 00 04 */	stw r0, 4(r1)
/* 8033CF58 00339B38  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 8033CF5C 00339B3C  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 8033CF60 00339B40  3B E4 00 00 */	addi r31, r4, 0
/* 8033CF64 00339B44  80 AD BC 58 */	lwz r5, __peReg(r13)
/* 8033CF68 00339B48  A0 05 00 0A */	lhz r0, 0xa(r5)
/* 8033CF6C 00339B4C  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8033CF70 00339B50  60 00 00 08 */	ori r0, r0, 8
/* 8033CF74 00339B54  B0 05 00 0A */	sth r0, 0xa(r5)
/* 8033CF78 00339B58  80 0D BC 84 */	lwz r0, lbl_804D7324(r13)
/* 8033CF7C 00339B5C  98 6D BC 88 */	stb r3, lbl_804D7328(r13)
/* 8033CF80 00339B60  28 00 00 00 */	cmplwi r0, 0
/* 8033CF84 00339B64  41 82 00 30 */	beq lbl_8033CFB4
/* 8033CF88 00339B68  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CF8C 00339B6C  48 00 82 C9 */	bl OSClearContext
/* 8033CF90 00339B70  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CF94 00339B74  48 00 80 F9 */	bl OSSetCurrentContext
/* 8033CF98 00339B78  81 8D BC 84 */	lwz r12, lbl_804D7324(r13)
/* 8033CF9C 00339B7C  7D 88 03 A6 */	mtlr r12
/* 8033CFA0 00339B80  4E 80 00 21 */	blrl 
/* 8033CFA4 00339B84  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CFA8 00339B88  48 00 82 AD */	bl OSClearContext
/* 8033CFAC 00339B8C  7F E3 FB 78 */	mr r3, r31
/* 8033CFB0 00339B90  48 00 80 DD */	bl OSSetCurrentContext
lbl_8033CFB4:
/* 8033CFB4 00339B94  38 6D BC 8C */	addi r3, r13, GXDrawDoneThreadQueue
/* 8033CFB8 00339B98  48 00 EB 49 */	bl OSWakeupThread
/* 8033CFBC 00339B9C  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 8033CFC0 00339BA0  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 8033CFC4 00339BA4  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 8033CFC8 00339BA8  7C 08 03 A6 */	mtlr r0
/* 8033CFCC 00339BAC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/PIzZj // 3200 (0%)
#pragma push
asm void __GXPEInit()
{ // clang-format off
    nofralloc
/* 8033CFD0 00339BB0  7C 08 02 A6 */	mflr r0
/* 8033CFD4 00339BB4  3C 60 80 34 */	lis r3, GXTokenInterruptHandler@ha
/* 8033CFD8 00339BB8  90 01 00 04 */	stw r0, 4(r1)
/* 8033CFDC 00339BBC  38 83 CE 80 */	addi r4, r3, GXTokenInterruptHandler@l
/* 8033CFE0 00339BC0  38 60 00 12 */	li r3, 0x12
/* 8033CFE4 00339BC4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033CFE8 00339BC8  48 00 A3 C9 */	bl __OSSetInterruptHandler
/* 8033CFEC 00339BCC  3C 60 80 34 */	lis r3, GXFinishInterruptHandler@ha
/* 8033CFF0 00339BD0  38 83 CF 4C */	addi r4, r3, GXFinishInterruptHandler@l
/* 8033CFF4 00339BD4  38 60 00 13 */	li r3, 0x13
/* 8033CFF8 00339BD8  48 00 A3 B9 */	bl __OSSetInterruptHandler
/* 8033CFFC 00339BDC  38 6D BC 8C */	addi r3, r13, GXDrawDoneThreadQueue
/* 8033D000 00339BE0  48 00 DD 2D */	bl OSInitThreadQueue
/* 8033D004 00339BE4  38 60 20 00 */	li r3, 0x2000
/* 8033D008 00339BE8  48 00 A7 AD */	bl __OSUnmaskInterrupts
/* 8033D00C 00339BEC  38 60 10 00 */	li r3, 0x1000
/* 8033D010 00339BF0  48 00 A7 A5 */	bl __OSUnmaskInterrupts
/* 8033D014 00339BF4  80 6D BC 58 */	lwz r3, __peReg(r13)
/* 8033D018 00339BF8  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 8033D01C 00339BFC  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 8033D020 00339C00  60 00 00 04 */	ori r0, r0, 4
/* 8033D024 00339C04  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8033D028 00339C08  60 00 00 08 */	ori r0, r0, 8
/* 8033D02C 00339C0C  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033D030 00339C10  60 00 00 01 */	ori r0, r0, 1
/* 8033D034 00339C14  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 8033D038 00339C18  60 00 00 02 */	ori r0, r0, 2
/* 8033D03C 00339C1C  B0 03 00 00 */	sth r0, 0(r3)
/* 8033D040 00339C20  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033D044 00339C24  38 21 00 08 */	addi r1, r1, 8
/* 8033D048 00339C28  7C 08 03 A6 */	mtlr r0
/* 8033D04C 00339C2C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
