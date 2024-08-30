#ifndef SYSDOLPHIN_BASELIB_S
#define SYSDOLPHIN_BASELIB_S

#include <platform.h>
#include "baselib/forward.h"

#include <dolphin/gx/types.h>

#define HSD_STATE_ALL -1
#define HSD_STATE_NONE 0
#define HSD_STATE_PRIMITIVE 0x1
#define HSD_STATE_VTX_ATTR 0x2
#define HSD_STATE_COLOR_CHANNEL 0x4
#define HSD_STATE_TEV_STAGE 0x8
#define HSD_STATE_TEV_REGISTER 0x10
#define HSD_STATE_TEX_COORD_GEN 0x20
#define HSD_STATE_RENDER_MODE 0x40

typedef struct HSD_Chan {
    struct HSD_Chan* next;
    GXChannelID chan;
    u32 flags;
    GXColor amb_color;
    GXColor mat_color;
    u8 enable;
    GXColorSrc amb_src;
    GXColorSrc mat_src;
    GXLightID light_mask;
    GXDiffuseFn diff_fn;
    GXAttnFn attn_fn;
    HSD_AObj* aobj;
} HSD_Chan;

void HSD_SetupChannelMode(u32 arg0);
void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe);
void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe);
void HSD_SetupRenderMode(u32);
void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          f32 alpha);
void HSD_SetMaterialShininess(f32 shininess);
void HSD_StateSetLineWidth(u8 width, int tex_offsets);
void HSD_StateSetCullMode(int mode);
void HSD_StateSetBlendMode(int type, int src_factor, int dst_factor, int op);
void HSD_StateSetZMode(int, int, int);
void HSD_StateSetPointSize(u8, int);
void HSD_StateSetAlphaCompare(int, u8, int, int, u8);
void HSD_StateSetColorUpdate(int);
void HSD_StateSetAlphaUpdate(int);
void HSD_StateSetDstAlpha(int, u8);
void HSD_StateSetZCompLoc(int);
void HSD_StateSetDither(int);
void _HSD_StateInvalidatePrimitive(void);
void _HSD_StateInvalidateVtxAttr(void);
void _HSD_StateInvalidateRenderMode(void);
void HSD_StateInvalidate(int mask);

#endif
