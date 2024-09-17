#include <placeholder.h>

#include "dolphin/gx/forward.h"

#include <dolphin/gx/__GXBump.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXTexture.h>

static Vec2 const GXTexture_804DE268 = { 16.0F, 0.0F };
static f64 const GXTexture_804DE270 = 4503599627370496.0L;
static f32 const GXTexture_804DE278 = -4.0F;
static f32 const GXTexture_804DE27C = 4.0F;
static f32 const GXTexture_804DE280 = 3.990000009536743F;
static f32 const GXTexture_804DE284 = 32.0F;
static f32 const GXTexture_804DE288 = 0.0F;
static f32 const GXTexture_804DE28C = 10.0F;

typedef struct {
    u32 x0;
    u32 x4;
} GXTexture_Unk0;

static GXTexture_Unk0 GXTexMode0Ids = { 0x80818283, 0xA0A1A2A3 };
static GXTexture_Unk0 GXTexMode1Ids = { 0x84858687, 0xA4A5A6A7 };
static GXTexture_Unk0 GXTexImage0Ids = { 0x88898A8B, 0xA8A9AAAB };
static GXTexture_Unk0 GXTexImage1Ids = { 0x8C8D8E8F, 0xACADAEAF };
static GXTexture_Unk0 GXTexImage2Ids = { 0x90919293, 0xB0B1B2B3 };
static GXTexture_Unk0 GXTexImage3Ids = { 0x94959697, 0xB4B5B6B7 };
static GXTexture_Unk0 GXTexTlutIds = { 0x98999A9B, 0xB8B9BABB };
static GXTexture_Unk0 GX2HWFiltConv = { 0x00040105, 0x02060000 };

s32 GXGetTexBufferSize(u16 arg0, u16 arg1, u32 arg2, u8 arg3, u8 arg4)
{
    NOT_IMPLEMENTED;
}

void __GetImageTileCount(u32 arg0, s16 arg1, s16 arg2, s32* arg3, s32* arg4,
                         s32* arg5)
{
    NOT_IMPLEMENTED;
}

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                  GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
                  GXBool mipmap)
{
    NOT_IMPLEMENTED;
}

void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                    GXCITexFmt format, GXTexWrapMode wrap_s,
                    GXTexWrapMode wrap_t, GXBool mipmap, u32 tlut_name)
{
    NOT_IMPLEMENTED;
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
                     f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
                     GXBool do_edge_lod, GXAnisotropy max_aniso)
{
    NOT_IMPLEMENTED;
}

s32 GXGetTexObjWidth(GXTexObj* tex_obj)
{
    return (tex_obj->dimensions & 0x3FF) + 1;
}

s32 GXGetTexObjHeight(GXTexObj* tex_obj)
{
    return (tex_obj->dimensions >> 10 & 0x3FF) + 1;
}

GXTexFmt GXGetTexObjFmt(GXTexObj* tex_obj)
{
    return tex_obj->tex_fmt;
}

void GXLoadTexObjPreLoaded(const GXTexObj* arg0, UNK_T arg1, GXTexMapID arg2)
{
    NOT_IMPLEMENTED;
}

void GXLoadTexObj(const GXTexObj* arg0, GXTexMapID arg1)
{
    GXLoadTexObjPreLoaded(arg0, __GXContexts.main->callbacks[0x98](), arg1);
}

void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt,
                   u16 n_entries)
{
    NOT_IMPLEMENTED;
}

void GXLoadTlut(GXTlutObj* arg0, s32 arg1)
{
    NOT_IMPLEMENTED;
}

void GXInitTexCacheRegion(UNK_T arg0, s8 arg1, u32 arg2, s32 arg3, u32 arg4,
                          s32 arg5, s32 arg6)
{
    NOT_IMPLEMENTED;
}

void GXInitTlutRegion(s32* arg0, s32 arg1, s32 arg2)
{
    *arg0 = 0;
    INSERT_FIELD(*arg0, (arg1 + 0xFFF80000) >> 9, 10, 0);
    INSERT_FIELD(*arg0, arg2, 11, 10);
    INSERT_FIELD(*arg0, 0x65, 8, 24);
}

void GXInvalidateTexAll(void)
{
    __GXFlushTextureState();
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x66001000;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x66001100;
    __GXFlushTextureState();
}

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback arg0)
{
    GXContext* main = __GXContexts.main;
    GXTexRegionCallback result = main->tex_region_cb;
    main->tex_region_cb = arg0;
    return result;
}

GXTexRegionCallback GXSetTlutRegionCallback(GXTexRegionCallback arg0)
{
    GXContext* main = __GXContexts.main;
    GXTexRegionCallback result = main->tlut_region_cb;
    main->tlut_region_cb = arg0;
    return result;
}

void __SetSURegs(s32 arg0, s32 arg1)
{
    NOT_IMPLEMENTED;
}

void __GXSetSUTexSize(void)
{
    NOT_IMPLEMENTED;
}

void __GXSetTmemConfig(s32 arg0)
{
    NOT_IMPLEMENTED;
}
