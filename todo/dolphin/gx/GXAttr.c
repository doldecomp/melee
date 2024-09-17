#include <platform.h>
#include <placeholder.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXTransform.h>

// https://decomp.me/scratch/d4i4k // 95 (98.90%)
/// #__GXXfVtxSpecs

/**
 * Sets the type of a single attribute (@p attr) in the current vertex
 * descriptor.
 *
 * The current vertex descriptor defines which attributes are present in a
 * vertex and how each attribute is referenced. It is used by the Graphics
 * Processor (GP) to interpret the graphics command stream produced by the GX
 * API. In particular, the current vertex descriptor is used to parse the
 * vertex data that is present in the command stream.
 *
 * @param attr The name of the attribute. Enabled attribute data must be sent
 *             in ascending order.
 * @param type The reference type of the attribute. Accepted values are
 *             #GX_NONE, #GX_DIRECT, #GX_INDEX8, and #GX_INDEX16.
 */
void GXSetVtxDesc(GXAttr attr, s32 type)
{
    switch (attr) {
    case GX_VA_PNMTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 0);
        break;
    case GX_VA_TEX0MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 1);
        break;
    case GX_VA_TEX1MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 2);
        break;
    case GX_VA_TEX2MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 3);
        break;
    case GX_VA_TEX3MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 4);
        break;
    case GX_VA_TEX4MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 5);
        break;
    case GX_VA_TEX5MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 6);
        break;
    case GX_VA_TEX6MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 7);
        break;
    case GX_VA_TEX7MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 8);
        break;
    case GX_VA_POS:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 9);
        break;
    case GX_VA_NRM:
        if (type != 0) {
            __GXContexts.main->x41C = 1;
            __GXContexts.main->x41D = 0;
            __GXContexts.main->x418 = type;
        } else {
            __GXContexts.main->x41C = 0;
        }
        break;
    case GX_VA_NBT:
        if (type != 0) {
            __GXContexts.main->x41D = 1;
            __GXContexts.main->x41C = 0;
            __GXContexts.main->x418 = type;
        } else {
            __GXContexts.main->x41D = 0;
        }
        break;
    case GX_VA_CLR0:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 13);
        break;
    case GX_VA_CLR1:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 15);
        break;
    case GX_VA_TEX0:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 0);
        break;
    case GX_VA_TEX1:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 2);
        break;
    case GX_VA_TEX2:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 4);
        break;
    case GX_VA_TEX3:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 6);
        break;
    case GX_VA_TEX4:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 8);
        break;
    case GX_VA_TEX5:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 10);
        break;
    case GX_VA_TEX6:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 12);
        break;
    case GX_VA_TEX7:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 14);
        break;
    }
    if (__GXContexts.main->x41C || __GXContexts.main->x41D) {
        INSERT_FIELD(__GXContexts.main->x14, __GXContexts.main->x418, 2, 11);
    } else {
        INSERT_FIELD(__GXContexts.main->x14, 0, 2, 11);
    }
    __GXContexts.main->x4F0_flags |= 8;
}

// https://decomp.me/scratch/NAwYO // 4529 (49.68%)
/// #__GXSetVCD

void GXClearVtxDesc(void)
{
    GXContext* temp_r3;
    GXContext* temp_r3_2;
    __GXContexts.main->x14 = 0;
    temp_r3 = __GXContexts.main;
    temp_r3->x14 = (temp_r3->x14 & 0xFFFFF9FF) | 0x200;
    __GXContexts.main->x18 = 0;
    __GXContexts.main->x41C = GX_FALSE;
    __GXContexts.main->x41D = GX_FALSE;
    temp_r3_2 = __GXContexts.main;
    temp_r3_2->x4F0_flags |= 8;
}

/**
 * Sets the attribute format (@p attr) for a single attribute in the Vertex
 * Attribute Format Table (VAT).
 *
 * Each attribute format describes the data type, number of elements
 * (@p count), and fixed point format (@p frac), if required. The are eight
 * vertex formats available in the VAT. The vertex format describes the format
 * of all attributes in a vertex. The application can pre-program all eight
 * vertex formats, and then select one of them during the actual drawing of
 * geometry (see #GXBegin). Note that all vertices used to draw a particular
 * graphics primitive will have the same format. The vertex format set using
 * #GXSetVtxAttrFmt, along with the current vertex descriptor set using
 * #GXSetVtxDesc, completely define the vertex data format.
 *
 * The vertex format allows data to be sent to the graphics processor in its
 * most quantized format. The graphics hardware will inverse-quantize the
 * data (into floating point format) before it is used. The vertex attribute
 * format is used to communicate the data quantization format to the hardware.
 *
 * Note that #GX_VA_NRM and #GX_VA_NBT attributes share the same type. Also,
 * the @p frac for these attributes is fixed according to the type. The
 * component count (@p count) for #GX_VA_NRM must be set to #GX_NRM_XYZ. The
 * component count for #GX_VA_NBT must be set to #GX_NRM_NBT (see exception for
 * HW2 below).
 *
 * Note also that a HW1 bug means that for a component type of #u8 or #s8, the
 * fixed-point fraction is ignored and assumed to be zero.
 *
 * @param vtxfmt The vertex format number.
 * @param attr   The attribute name.
 * @param count  May be one of several different enumerations, depending
 *               on the attribute name; one of #GXCompCnt, #GXPosCompCnt,
 *               #GXNrmCompCnt, #GXClrCompCnt, or #GXTexCompCnt. Ultimately
 *               aids in determining the number of dimensions for this
 *               attribute. For example, 4 for an RGBA color, or 3 for
 *               vertex position data.
 * @param type   May be one of several different enumerations, depending
 *               on the attribute name. Specifies the data format for
 *               a single value in a dimension, such as #u8, #s16, or #f32.
 * @param frac   Specifies the number of fractional bits in a fixed point
 *               number, where <tt>0 <= frac <= 31</tt>. @p frac is ignored for
 *               floating-point types and color types.
 * @see          GXBegin
 * @see          GXSetVtxAttrFmt
 * @see          GXSetVtxDesc
 */
void GXSetVtxAttrFmt(size_t vtxfmt, GXAttr attr, enum_t count, GXCompType type,
                     u8 frac)
{
    s32* temp_r4 = &__GXContexts.main->x1C_data[vtxfmt];
    s32* temp_r8 = &__GXContexts.main->x3C_data[vtxfmt];
    s32* temp_r9 = &__GXContexts.main->x5C_data[vtxfmt];

    switch (attr) {
    case GX_VA_POS:
        INSERT_FIELD(*temp_r4, count, 1, 0);
        INSERT_FIELD(*temp_r4, type, 3, 1);
        INSERT_FIELD(*temp_r4, frac, 5, 4);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        INSERT_FIELD(*temp_r4, type, 3, 10);
        if (count == 2) {
            INSERT_FIELD(*temp_r4, 1, 1, 9);
            INSERT_FIELD(*temp_r4, 1, 1, 31);
        } else {
            INSERT_FIELD(*temp_r4, count, 1, 9);
            INSERT_FIELD(*temp_r4, 0, 1, 31);
        }
        break;
    case GX_VA_CLR0:
        INSERT_FIELD(*temp_r4, count, 1, 13);
        INSERT_FIELD(*temp_r4, type, 3, 14);
        break;
    case GX_VA_CLR1:
        INSERT_FIELD(*temp_r4, count, 1, 17);
        INSERT_FIELD(*temp_r4, type, 3, 18);
        break;
    case GX_VA_TEX0:
        INSERT_FIELD(*temp_r4, count, 1, 21);
        INSERT_FIELD(*temp_r4, type, 3, 22);
        INSERT_FIELD(*temp_r4, frac, 5, 25);
        break;
    case GX_VA_TEX1:
        INSERT_FIELD(*temp_r8, count, 1, 0);
        INSERT_FIELD(*temp_r8, type, 3, 1);
        INSERT_FIELD(*temp_r8, frac, 5, 4);
        break;
    case GX_VA_TEX2:
        INSERT_FIELD(*temp_r8, count, 1, 9);
        INSERT_FIELD(*temp_r8, type, 3, 10);
        INSERT_FIELD(*temp_r8, frac, 5, 13);
        break;
    case GX_VA_TEX3:
        INSERT_FIELD(*temp_r8, count, 1, 18);
        INSERT_FIELD(*temp_r8, type, 3, 19);
        INSERT_FIELD(*temp_r8, frac, 5, 22);
        break;
    case GX_VA_TEX4:
        INSERT_FIELD(*temp_r8, count, 1, 27);
        INSERT_FIELD(*temp_r8, type, 3, 28);
        INSERT_FIELD(*temp_r9, frac, 5, 0);
        break;
    case GX_VA_TEX5:
        INSERT_FIELD(*temp_r9, count, 1, 5);
        INSERT_FIELD(*temp_r9, type, 3, 6);
        INSERT_FIELD(*temp_r9, frac, 5, 9);
        break;
    case GX_VA_TEX6:
        INSERT_FIELD(*temp_r9, count, 1, 14);
        INSERT_FIELD(*temp_r9, type, 3, 15);
        INSERT_FIELD(*temp_r9, frac, 5, 18);
        break;
    case GX_VA_TEX7:
        INSERT_FIELD(*temp_r9, count, 1, 23);
        INSERT_FIELD(*temp_r9, type, 3, 24);
        INSERT_FIELD(*temp_r9, frac, 5, 27);
        break;
    }
    __GXContexts.main->x4F0_flags |= 0x10;
    __GXContexts.main->x4EE |= (u8) (1 << (u8) vtxfmt);
}

void __GXSetVAT(void)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        if (__GXContexts.main->x4EE & (1 << (u32) i)) {
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x70;
            WGPIPE.u32 = __GXContexts.main->x1C_data[i];
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x80;
            WGPIPE.u32 = __GXContexts.main->x3C_data[i];
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x90;
            WGPIPE.u32 = __GXContexts.main->x5C_data[i];
        }
    }
    __GXContexts.main->x4EE = 0;
}

/**
 * Sets the array base pointer and stride for a single attribute.
 *
 * The array base and stride are used to compute the address of indexed
 * attribute data using the equation:
 *
 * @code{c}
 *      attr_addr = base_ptr + attr_idx * stride
 * @endcode
 *
 * When drawing a graphics primitive that has been enabled to use indexed
 * attributes (see #GXSetVtxDesc), @p attr_idx is supplied in the vertex data.
 * The format and size of the data in the array must also be described
 * using #GXSetVtxAttrFmt.
 *
 * You can also index other data, such as matrices (see #GXLoadPosMtxIndx,
 * #GXLoadNrmMtxIndx3x3, and #GXLoadTexMtxIndx), and light objects (see
 * #GXLoadLightObjIndx). In the case of matrices and light objects, the
 * size and format of the data to be loaded is implied by the function call.
 *
 * There is a base pointer, @p base_ptr, for each type of attribute as well as
 * for light data and matrices. Each attribute can be stored in its own
 * array for maximum data compression (i.e., removal of redundant attribute
 * data). The stride is in byte units and is the distance between
 * attributes in the array.
 *
 * Indexed data is loaded into a vertex cache in the graphics processor.
 * The vertex cache fetches 32 bytes of data for each cache miss; therefore,
 * there is a small performance benefit to aligning attribute arrays to
 * 32 bytes, and possibly for arranging vertex data so that it doesn't span
 * 32-byte boundaries. Conveniently enough, #OSAlloc returns 32-byte aligned
 * pointers. For static data arrays, you can use the #ATTRIBUTE_ALIGN macro
 * (specific to the MetroWerks compiler) to align the @p base_ptr to 32 bytes,
 * as in:
 *
 * @code{c}
 *      u32 mydata[] ATTRIBUTE_ALIGN(32) = {
 *          // initialize data
 *      };
 * @endcode
 *
 * @param attr      The attribute array name.
 * @param base_ptr  Pointer to first element in attribute data array.
 * @param stride    Stride in bytes between attribute data elements.
 */
void GXSetArray(GXAttr attr, s32 base_ptr, u8 stride)
{
    s32 idx;
    s32 temp_r6;
    s32 var_r3;

    var_r3 = attr;
    if (var_r3 == GX_VA_NBT) {
        var_r3 = GX_VA_NRM;
    }
    temp_r6 = var_r3 - 9;

    WGPIPE.u8 = GX_LOAD_CP_REG;
    WGPIPE.u8 = temp_r6 | 0xA0;
    WGPIPE.u32 = base_ptr & 0x3FFFFFFF;
    idx = temp_r6 - 0xC;
    if (idx >= 0 && idx < 4) {
        __GXContexts.main->x88_data[idx] = base_ptr & 0x3FFFFFFF;
    }
    WGPIPE.u8 = GX_LOAD_CP_REG;
    WGPIPE.u8 = (s8) (temp_r6 | 0xB0);
    WGPIPE.u32 = stride;
    idx = temp_r6 - 0xC;
    if (idx >= 0 && idx < 4) {
        __GXContexts.main->x98_data[idx] = stride;
    }
}

/**
 * Called by #GXInit and invalidates the vertex cache tags.
 *
 * This function should be used whenever you relocate or modify data that
 * is read by, or may be cached by, the vertex cache. The invalidate is
 * very fast, taking only two Graphics Processor (GP) clock cycles to complete.
 *
 * The vertex cache is used to cache indexed attribute data. Any attribute
 * that is set to #GX_INDEX8 or #GX_INDEX16 in the current vertex descriptor
 * (see #GXSetVtxDesc) is indexed. Direct data bypasses the vertex cache.
 * Direct data is any attribute that is set to #GX_DIRECT in the current
 * vertex descriptor.
 *
 * @see GXInit
 * @see GXSetVtxDesc
 */
void GXInvalidateVtxCache(void)
{
    WGPIPE.u8 = GX_CMD_INVL_VC;
}

void GXSetTexCoordGen2(GXTexCoordID arg0, GXTexGenType arg1, GXTexGenSrc arg2,
                       u32 arg3, GXBool arg4, u32 arg5)
{
    s32 var_r0;
    s32 var_r10;
    s32 var_r11;
    s32 var_r12;

    var_r11 = 0;
    var_r12 = 0;
    var_r10 = 5;
    switch (arg2) {
    case GX_TG_POS:
        var_r10 = 0;
        var_r12 = 1;
        break;
    case GX_TG_NRM:
        var_r10 = 1;
        var_r12 = 1;
        break;
    case GX_TG_BINRM:
        var_r10 = 3;
        var_r12 = 1;
        break;
    case GX_TG_TANGENT:
        var_r10 = 4;
        var_r12 = 1;
        break;
    case GX_TG_COLOR0:
        var_r10 = 2;
        break;
    case GX_TG_COLOR1:
        var_r10 = 2;
        break;
    case GX_TG_TEX0:
        var_r10 = 5;
        break;
    case GX_TG_TEX1:
        var_r10 = 6;
        break;
    case GX_TG_TEX2:
        var_r10 = 7;
        break;
    case GX_TG_TEX3:
        var_r10 = 8;
        break;
    case GX_TG_TEX4:
        var_r10 = 9;
        break;
    case GX_TG_TEX5:
        var_r10 = 0xA;
        break;
    case GX_TG_TEX6:
        var_r10 = 0xB;
        break;
    case GX_TG_TEX7:
        var_r10 = 0xC;
        break;
    }
    switch (arg1) {
    case GX_TG_MTX2x4:
        var_r11 = var_r12 * 4;
        INSERT_FIELD(var_r11, var_r10 << 3, 8, 4);
        break;
    case GX_TG_MTX3x4:
        var_r11 = var_r12 * 4 | 2;
        INSERT_FIELD(var_r11, var_r10 << 3, 8, 4);
        break;
    case GX_TG_BUMP0:
    case GX_TG_BUMP1:
    case GX_TG_BUMP2:
    case GX_TG_BUMP3:
    case GX_TG_BUMP4:
    case GX_TG_BUMP5:
    case GX_TG_BUMP6:
    case GX_TG_BUMP7:
        var_r11 = var_r12 * 4;
        INSERT_FIELD(var_r11, 1, 3, 4);
        INSERT_FIELD(var_r11, var_r10, 5, 7);
        INSERT_FIELD(var_r11, arg2 - 12, 3, 12);
        INSERT_FIELD(var_r11, arg1 - 2, 3, 15);
        break;
    case GX_TG_SRTG:
        var_r11 = var_r12 * 4;
        if (arg2 == 0x13) {
            INSERT_FIELD(var_r11, 2, 3, 4);
        } else {
            INSERT_FIELD(var_r11, 3, 3, 4);
        }
        INSERT_FIELD(var_r11, 2, 5, 7);
        break;
    }
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = arg0 + 0x1040;
    WGPIPE.u32 = var_r11;
    WGPIPE.u8 = GX_LOAD_XF_REG;
    arg5 -= 0x40;
    INSERT_FIELD(arg5, arg4, 1, 8);
    WGPIPE.u32 = arg0 + 0x1050;
    WGPIPE.u32 = arg5;
    switch (arg0) {
    case GX_TEXCOORD0:
        INSERT_FIELD(__GXContexts.main->x80, arg3, 6, 6);
        break;
    case GX_TEXCOORD1:
        INSERT_FIELD(__GXContexts.main->x80, arg3, 6, 12);
        break;
    case GX_TEXCOORD2:
        INSERT_FIELD(__GXContexts.main->x80, arg3, 6, 18);
        break;
    case GX_TEXCOORD3:
        INSERT_FIELD(__GXContexts.main->x80, arg3, 6, 24);
        break;
    case GX_TEXCOORD4:
        INSERT_FIELD(__GXContexts.main->x84, arg3, 6, 0);
        break;
    case GX_TEXCOORD5:
        INSERT_FIELD(__GXContexts.main->x84, arg3, 6, 6);
        break;
    case GX_TEXCOORD6:
        INSERT_FIELD(__GXContexts.main->x84, arg3, 6, 12);
        break;
    default:
        INSERT_FIELD(__GXContexts.main->x84, arg3, 6, 18);
        break;
    }
    __GXSetMatrixIndex(arg0 + 1);
}

/**
 * Sets the number of texture coordinates that are generated and available for
 * use in the Texture Environment (TEV) stages.
 *
 * Texture coordinates are generated from input data as described by
 * #GXSetTexCoordGen2. The generated texture coordinates are linked to specific
 * textures and specific Texture Environment (TEV) stages using #GXSetTevOrder.
 *
 * A consecutive number of texture coordinates may be generated, starting
 * at #GX_TEXCOORD0. A maximum of 8 texture coordinates may be generated.
 * If @p num is set to 0, no texture coordinates will be generated. In
 * this case, at least one color channel must be output, see #GXSetNumChans.
 *
 * @param num Number of texture coordinates to generate. Minimum value is 0,
 *            maximum value is 8.
 * @see       GXSetNumChans
 */
void GXSetNumTexGens(u8 num)
{
    INSERT_FIELD(__GXContexts.main->x204, num, 4, 0);
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x103F;
    WGPIPE.u32 = num;
    __GXContexts.main->x4F0_flags |= 4;
}
