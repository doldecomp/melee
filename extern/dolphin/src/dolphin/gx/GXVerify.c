#if DEBUG

#include <dolphin/gx.h>

#include "__gx.h"

static struct __GXVerifyData __gxVerifData;
struct __GXVerifyData * __gxVerif = &__gxVerifData;

char *__gxvWarnings[113] = {
    "Invalid Vertex Format. Normal count must be set to GX_NRM_NBT",
    "Texture size %ld not initialized.",
    "Left edge of scissor rectangle is less than %d.",
    "Top edge of scissor rectangle is less than %d.",
    "Right edge of scissor rectangle is greater than %d in %s mode.",
    "Bottom edge of scissor rectangle is greater than %d in %s mode.",
    "%s value for subsample %d in pixel %ld is not 6 when single-sampling.",
    "Bump command for stage %ld is not set.",
    "Invalid indirect data request in TEV stage %ld",
    "Indirect matrix %ld requested in stage %d not set.",
    "Requested indirect textures never initialized.",
    "Indirect texture coordinate scales %d and %d not set.",
    "Invalid tex coordinate specified for BUMP stage %d.",
    "Accumulation is on in BUMP stage 0.",
    "Bump alpha is enabled in BUMP stage 0.",
    "Indirect vs. direct mask byte never set.",
    "Texture reference never written for TEV stage %ld.",
    "Invalid tex coordinate specified for TEV stage %ld.",
    "Texture %ld is used as both indirect and direct.",
    "Texture %ld not configured.",
    "Base pointer for cached texture %ld is never set.",
    "TLUT for indexed texture %ld never set up.",
    "%s is not a power of two for mipmapped  texture %ld.",
    "%s is not clamp-to-edge for non-power-of-2 width in texture %ld",
    "Minification filter for texture %ld is not compatible with color index texture format.",
    "Minimum LOD is greater than maximum LOD in texture %ld.",
    "Maximum LOD is greater than image's maximum LOD for texture %ld.",
    "LOD clamp and diag LOD both set for texture %ld.",
    "Texture %ld does not meet requirements for anisotropic mipmapping.",
    "Filters are not linear for field prediction in texture %ld.",
    "Incomplete mpeg configuration for texture %ld.",
    "Rounding color indexed texture %ld.",
    "Environment for TEV stage %ld not fully set up.",
    "Invalid color channel selected in TEV stage %ld.",
    "%s selects null texture in TEV color stage %ld.",
    "%s selects null texture in TEV alpha stage %ld.",
    "Color arg %s in TEV stage %ld accesses %s register %ld, which may be dirty.",
    "Alpha arg %s in TEV stage %ld accesses alpha register %ld, which may be dirty.",
    "Color arg %s in TEV stage %ld accesses %s register %ld, which was last clamped linear high. Possible wrap-around effect.",
    "Alpha arg C in TEV stage %ld accesses alpha register %ld, which was last clamped linear high. Possible wrap-around effect.",
    "Z texturing enabled, but no Z offset specified.",
    "Z texturing enabled, but no texture specified for final TEV stage.",
    "Final stage doesn't write color to TEV register 0.",
    "Final stage doesn't write alpha to TEV register 0.",
    "Final color stage has linear high clamping possible color wrap-around effect.",
    "Final alpha stage has linear high clamping possible alpha wrap-around effect.",
    "Z buffering is before texture, but alpha function is an alpha function.",
    "PE blend and logicop are both on.",
    "Selected pixel format does not support dithering.",
    "Multisample enabled but pixel type is not RGB565",
    "Pixel type is RGB565 but multisample is not enabled",
    "Multisample locations for pixel %ld are not ordered correctly for antialias filter.",
    "Invalid texgen_type %d for texture %d",
    "Register address 0x%04x uninitialized (%s)",
    "Register address 0x%04x initialized (%s), probably should not be",
    "Invalid combination of %d output colors and %d color texgen textures",
    "Invalid number of output colors, %d",
    "Vertex packet does not contain geometry values",
    "XF is not expecting host colors but cp is sending some",
    "XF is expecting a host color but cp is not sending one",
    "XF is expecting a single host color but cp is sending two",
    "XF is expecting two host colors but cp is not sending first color",
    "XF is expecting two host colors but cp is not sending second color",
    "Invalid value (%d) for INVERTEXSPEC_REG.host_colors",
    "XF is not expecting host normals but cp is sending them",
    "XF is not expecting host normals, binormals and tangents but cp is sending them",
    "XF is expecting host normals but cp is not sending them",
    "XF is expecting host normals but cp is sending normals, binormals, and tangents",
    "XF is expecting host normals, binormals and tangents but cp is only sending normals",
    "XF is expecting host normals, binormals and tangents but cp is not sending them",
    "Invalid value (%d) for INVERTEXSPEC_REG.host_normal",
    "XF expecting %d host textures but CP is only sending %d",
    "Regular texture %d specifying source row of geometry, but this is not getting sent by the CP",
    "Regular texture %d specifying source row of normals, but this is not getting sent by the CP",
    "Regular texture %d specifying source row of colors, but color0 is not getting sent by the CP",
    "Regular texture %d specifying source row of colors, but color1 is not getting sent by the CP",
    "Regular texture %d specifying source row of binormal or tangent, but these are not getting sent by the CP",
    "Regular texture %d specifying source row of texture %d, but this is not getting sent by the CP",
    "Regular texture %d is specifying an invalid source row of %d",
    "Texture texgen types are out of order. Must be defined as regular if any, then bumpmap if any, then color if any",
    "Bumpmap textures are defined, which requires the binormals and tangents to be transformed by a normal matrix, but MATRIXINDEX0_REG.geom is set to an invalid value (%d)",
    "Bumpmap %d (texture %d) is referencing texture %d as a source texture, which is not of texgen type regular",
    "Bumpmap %d (texture %d) using light source %d, but light's %c position is not defined",
    "Texture %d is defined as texgen type Bumpmap, but cp is not sending binormals and tangents",
    "Invalid regular texture number (%d)",
    "Regular texture %d specifying a source row of %d which only has 2 elements, but an input form of ABC1",
    "Output XF colors or color textures enabled, but register address 0x%04x uninitialized (%s)",
    "Output XF colors or color textures enabled, COLOR%dCNTRL_REG.material_src == REGISTER, but Material %d register (0x%04x) is not initialized",
    "Output XF colors or color textures enabled, COLOR%dCNTRL_REG.ambient_src == REGISTER, but Ambient %d register (0x%04x) is not initialized",
    "%sCNTRL_REG.attenselect == SPECULAR but %sCNTRL_REG.diffuseatten != NL_ONE",
    "Color %d lighting requires a normal, but cp is not sending it",
    "Color %d lighting requires the normal to be transformed by a normal matrix, but MATRIXINDEX0_REG.geom is set to an invalid value (%d)",
    "%s has a value of %sinfinity (%08x), which is probably not intended",
    "%s has a value of NaN (%08x), which is probably not intended",
    "%s has a value of (%f 0x%08x), which might be unintentionally small",
    "%s has a value of (%f 0x%08x), which might be unintentionally large",
    "%d regular textures active, but MatrixIndex1 register (0x%04x) uninitialized",
    "gen_mode register not initialized",
    "Number of XF output textures does not match what downstream units are expecting",
    "Number of XF output colors does not match what downstream units are expecting",
    "Number of all texgens (%d) > max allowed %d",
    "Number of regular type texgens (%d) > max allowed %d",
    "Number of bumpmap type texgens (%d) > max allowed %d",
    "Number of color texgens (%d) > max allowed %d",
    "First color texgen is not referencing COLOR0",
    "Color texgen from COLOR%d is used more than once",
    "Bumpmap textures are defined, which requires the normal matrix values pointed to by MATRIXINDEX0_REG.geom (%d) to be loaded, however...",
    "Texture %d is a regular texture, which requires that the matrix values pointed to by MATRIXINDEX0_REG.tex%d (%d) must be loaded, however...",
    "Light %d is being referenced, however...",
    "Color %d lighting requires the normal matrix values pointed to by MATRIXINDEX0_REG.geom (%d) to be loaded, however...",
    "MatrixIndex0.Geometry matrix values must be loaded, however...",
    "Address 0x%04x is uninitialized",
    "Register (0x%04x) (%s) is not initialized"
};

char __gxvDummyStr[256];

static void __GXVerifyGlobal(void)
{
}

static void __GXVerifyCP(GXVtxFmt fmt)
{
    u32 nrmCnt = GET_REG_FIELD(gx->vatA[fmt], 1, 9);
    
    if (__gxVerif->verifyLevel >= GX_WARN_SEVERE) {
        if (gx->hasNrms && nrmCnt != 0) {
            __gxVerif->cb(1, 0, __gxvWarnings[0]);
        }
        else if (gx->hasBiNrms && nrmCnt != 1 && nrmCnt != 2) {
            __gxVerif->cb(1, 0, __gxvWarnings[0]);
        }
    }
}

void __GXVerifyState(GXVtxFmt vtxfmt)
{
    if (__gxVerif->verifyLevel != GX_WARN_NONE) {
        __GXVerifyGlobal();
        __GXVerifyCP(vtxfmt);
        __GXVerifyXF();
        __GXVerifySU();
        __GXVerifyBUMP();
        __GXVerifyTEX();
        __GXVerifyTEV();
        __GXVerifyPE();
    }
}

void GXSetVerifyLevel(GXWarningLevel level)
{
    __gxVerif->verifyLevel = level;
}

GXVerifyCallback GXSetVerifyCallback(GXVerifyCallback cb)
{
    GXVerifyCallback old_cb = __gxVerif->cb;
    
    __gxVerif->cb = cb;
    return old_cb;
}

#endif  // DEBUG
