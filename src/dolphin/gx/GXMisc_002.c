// https://github.com/ogamespec/dolwin-docs/blob/0d1ea56663af6281e2b407f47dd6987f0e79c50c/RE/GX/GXMisc.c

#include <dolphin/gx/__gx.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/base/PPCArch.h>

// Cpu2Efb methods.

// From GXEnum.h

// Compare function.
typedef enum
{
    GX_NEVER,
    GX_LESS,
    GX_EQUAL,
    GX_LEQUAL,
    GX_GREATER,
    GX_NEQUAL,
    GX_GEQUAL,
    GX_ALWAYS
} GXCompare;

/*
 * Determines value of alpha read from a frame buffer with no alpha channel.
 * GX_READ_00 or GX_READ_FF returns 0x00 or 0xFF respectedly as alpha value when you call GXPeekARGB. GX_READ_NONE will be used if you want to get alpha value from the EFB. If the EFB doesn't have alpha plane, the alpha value is undefined.
 */
typedef enum
{
    GX_READ_00,
    GX_READ_FF,
    GX_READ_NONE
} GXAlphaReadMode;

// Blending mode.
typedef enum
{
    GX_BM_NONE,
    GX_BM_BLEND,    // dst_pix_clr = src_pix_clr * src_factor + dst_pix_clr * dst_factor
    GX_BM_LOGIC,    // blended using logical bitwise operations
    GX_BM_SUBTRACT, // dst_pix_clr = dst_pix_clr - src_pix_clr [clamped to zero]
    GX_MAX_BLENDMODE
} GXBlendMode;

typedef enum
{
    GX_BL_ZERO,                       // 0.0
    GX_BL_ONE,                        // 1.0
    GX_BL_SRCCLR,                     // source color
    GX_BL_INVSRCCLR,                  // 1.0 - (source color)
    GX_BL_SRCALPHA,                   // source alpha
    GX_BL_INVSRCALPHA,                // 1.0 - (source alpha)
    GX_BL_DSTALPHA,                   // frame buffer alpha
    GX_BL_INVDSTALPHA,                // 1.0 - (frame buffer alpha)
    GX_BL_DSTCLR = GX_BL_SRCCLR,      // frame buffer color
    GX_BL_INVDSTCLR = GX_BL_INVSRCCLR // 1.0 - (frame buffer color)
} GXBlendFactor;

typedef enum
{
    GX_LO_CLEAR,   // dst = 0
    GX_LO_AND,     // dst = src & dst
    GX_LO_REVAND,  // dst = src & ~dst
    GX_LO_COPY,    // dst = src
    GX_LO_INVAND,  // dst = ~src & dst
    GX_LO_NOOP,    // dst = dst
    GX_LO_XOR,     // dst = src ^ dst
    GX_LO_OR,      // dst = src | dst
    GX_LO_NOR,     // dst = ~(src | dst)
    GX_LO_EQUIV,   // dst = ~(src ^ dst)
    GX_LO_INV,     // dst = ~dst
    GX_LO_REVOR,   // dst = src | ~dst
    GX_LO_INVCOPY, // dst = ~src
    GX_LO_INVOR,   // dst = ~src | dest
    GX_LO_NAND,    // dst = ~(src & dst)
    GX_LO_SET      // dst = 1
} GXLogicOp;

// From GXInit.c

#define PE_POKE_ZMODE_ID 0
#define PE_POKE_CMODE0_ID 1
#define PE_POKE_CMODE1_ID 2
#define PE_POKE_AMODE0_ID 3
#define PE_POKE_AMODE1_ID 4

#define PI_MEMSP_EFB 0x08000000

#define INSERT_FIELD(reg, value, nbits, shift) \
    (reg) = ((u32)(reg) & ~(((1 << (nbits)) - 1) << (shift))) | ((u32)(value) << (shift));

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
