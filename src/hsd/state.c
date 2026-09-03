#include "state.h"

#include "lobj.h"
#include "mobj.h"
#include "pobj.h"
#include "tev.h"
#include "texp.h"
#include "util.h"

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>

static GXColor dark_matter = { 0x00, 0x00, 0x00, 0xFF };

static u8 state_line_width;
static int state_line_tex_offsets;
static u8 state_point_size;
static int HSD_State_804D75BC;
static int state_cull_mode;
static int state_blend_type;
static int state_src_factor;
static int state_dst_factor;
static int state_logic_op;
static u8 state_z_enable;
static int state_z_func;
static u8 state_z_update;
static int state_alpha_comp0;
static u8 state_alpha_ref0;
static int state_alpha_op;
static int state_alpha_comp1;
static u8 state_alpha_ref1;
static u8 state_color_update;
static u8 state_alpha_update;
static u8 state_enable_dst_alpha;
static u8 state_dst_alpha;
static u8 state_before_tex;
static u8 state_dither;

static struct {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    u8 alpha;
    f32 shininess;
} matstate;

HSD_Chan HSD_State_80405A38 = {
    /* next       = */ NULL,
    /* chan       = */ 1,
    /* flags      = */ 1,
    /* amb_color  = */ { 0 },
    /* mat_color  = */ { 0xFF, 0xFF, 0xFF, 0xFF },
    /* enable     = */ 1,
    /* amb_src    = */ 0,
    /* mat_src    = */ 0,
    /* light_mask = */ 0,
    /* diff_fn    = */ 2
};

HSD_Chan HSD_State_80405A38_30 = {
    /* next       = */ NULL,
    /* chan       = */ 4,
    /* flags      = */ 0,
    /* amb_color  = */ { 0 },
    /* mat_color  = */ { 0 },
    /* enable     = */ 0,
    /* amb_src    = */ 0,
    /* mat_src    = */ 1,
    /* light_mask = */ 0,
    /* diff_fn    = */ 2,
    /* attn_fn    = */ 2,
};

HSD_Chan HSD_State_80405A38_60 = {
    /* next       = */ NULL,
    /* chan       = */ 0,
    /* flags      = */ 0,
    /* amb_color  = */ { 0 },
    /* mat_color  = */ { 0xFF, 0xFF, 0xFF, 0xFF },
    /* enable     = */ 1,
    /* amb_src    = */ 0,
    /* mat_src    = */ 0,
    /* light_mask = */ 0,
    /* diff_fn    = */ 2,
    /* attn_fn    = */ 1,
};

HSD_Chan HSD_State_80405A38_90 = {
    /* next       = */ NULL,
    /* chan       = */ 2,
    /* flags      = */ 0,
    /* amb_color  = */ { 0x00, 0x00, 0x00, 0xFF },
    /* mat_color  = */ { 0x00, 0x00, 0x00, 0xFF },
    /* enable     = */ 1,
    /* amb_src    = */ 0,
    /* mat_src    = */ 0,
    /* light_mask = */ 0,
    /* diff_fn    = */ 2,
    /* attn_fn    = */ 1,
};

HSD_Chan HSD_State_80405A38_C0 = {
    /* next       = */ NULL,
    /* chan       = */ 2,
    /* flags      = */ 0,
    /* amb_color  = */ { 0 },
    /* mat_color  = */ { 0x00, 0x00, 0x00, 0xFF },
    /* enable     = */ 0,
    /* amb_src    = */ 0,
    /* mat_src    = */ 0,
    /* light_mask = */ 0,
    /* diff_fn    = */ 0,
    /* attn_fn    = */ 2,
};

HSD_Chan HSD_State_80405A38_F0 = {
    /* next       = */ NULL,
    /* chan       = */ 4,
    /* flags      = */ 0,
    /* amb_color  = */ { 0 },
    /* mat_color  = */ { 0xFF, 0xFF, 0xFF, 0xFF },
    /* enable     = */ 0,
    /* amb_src    = */ 0,
    /* mat_src    = */ 0,
    /* light_mask = */ 0,
    /* diff_fn    = */ 2,
    /* attn_fn    = */ 2,
};

struct {
    int mask;
    void (*func)(void);
} invalidate_funcs[] = {
    { HSD_STATE_PRIMITIVE, _HSD_StateInvalidatePrimitive },
    { HSD_STATE_VTX_ATTR, _HSD_StateInvalidateVtxAttr },
    { HSD_STATE_COLOR_CHANNEL, _HSD_StateInvalidateColorChannel },
    { HSD_STATE_TEV_STAGE, _HSD_StateInvalidateTevStage },
    { HSD_STATE_TEV_REGISTER, _HSD_StateInvalidateTevRegister },
    { HSD_STATE_TEX_COORD_GEN, _HSD_StateInvalidateTexCoordGen },
    { HSD_STATE_RENDER_MODE, _HSD_StateInvalidateRenderMode },
    { HSD_STATE_NONE }
};

void HSD_SetupChannelMode(u32 arg0)
{
    HSD_LObj* temp_r3;
    HSD_LObj* temp_r3_2;
    f32 var_f0;
    int i;
    s32 var_r3;
    int max;

    if (arg0 & 8) {
        var_r3 = 2;
    } else {
        var_r3 = 1;
    }
    HSD_StateSetNumChans(var_r3);
    if (arg0 & 8) {
        HSD_State_80405A38.light_mask = HSD_LObjGetLightMaskSpecular();
        HSD_SetupChannel(&HSD_State_80405A38);
        i = 0;
        max = HSD_LObjGetNbActive();
        for (i = 0; i < max; i++) {
            temp_r3 = HSD_LObjGetActiveByIndex(i);
            if (temp_r3 != NULL) {
                var_f0 = arg0 & 8 ? matstate.shininess : temp_r3->shininess;
                HSD_LObjSetup(temp_r3, temp_r3->color, var_f0);
            }
        }
    }
    switch (arg0 & 7) {
    case 2:
        HSD_SetupChannel(&HSD_State_80405A38_30);
        break;
    case 4:
        temp_r3_2 = HSD_LObjGetActiveByID(0x100);
        if (temp_r3_2 != NULL && (temp_r3_2->flags & 4)) {
            HSD_MulColor(&matstate.ambient, &temp_r3_2->color,
                         &HSD_State_80405A38_60.amb_color);
        } else {
            HSD_State_80405A38_60.amb_color = dark_matter;
        }
        HSD_State_80405A38_60.light_mask = HSD_LObjGetLightMaskDiffuse();
        HSD_SetupChannel(&HSD_State_80405A38_60);
        HSD_State_80405A38_90.light_mask = HSD_LObjGetLightMaskAlpha();
        if (temp_r3_2 != NULL && (temp_r3_2->flags & 0x10)) {
            HSD_State_80405A38_90.amb_color.a = temp_r3_2->color.a;
            HSD_SetupChannel(&HSD_State_80405A38_90);
        } else if (HSD_State_80405A38_90.light_mask != 0) {
            HSD_State_80405A38_90.amb_color.a = 0;
            HSD_SetupChannel(&HSD_State_80405A38_90);
        } else {
            HSD_SetupChannel(&HSD_State_80405A38_C0);
        }
        break;
    case 3:
    default:
        HSD_SetupChannel(&HSD_State_80405A38_F0);
        break;
    }
}

void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe)
{
    u8 var_r3_2;
    int var_r3;

    if (pe != NULL) {
        HSD_StateSetColorUpdate(pe->flags & 1);
        HSD_StateSetAlphaUpdate(pe->flags & 2);
        HSD_StateSetDstAlpha(pe->flags & 4, pe->dst_alpha);
        HSD_StateSetBlendMode(pe->type, pe->src_factor, pe->dst_factor,
                              pe->logic_op);
        HSD_StateSetZMode(pe->flags & 0x10, pe->z_comp, pe->flags & 0x20);
        HSD_StateSetZCompLoc(pe->flags & 8);
        HSD_StateSetAlphaCompare(pe->alpha_comp0, pe->ref0, pe->alpha_op,
                                 pe->alpha_comp1, pe->ref1);
        HSD_StateSetDither(pe->flags & 0x40);
        return;
    }
    HSD_StateSetColorUpdate(1);
    HSD_StateSetAlphaUpdate(0);
    HSD_StateSetDstAlpha(0, 0U);
    if (flags & 0x40000000) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    HSD_StateSetBlendMode(var_r3, 4U, 5U, 0xFU);
    var_r3_2 = (flags & 0x20000000) ? GX_FALSE : GX_TRUE;
    HSD_StateSetZMode(1, (flags & 0x08000000) ? 7 : 3, var_r3_2);
    if (!(flags & 0x20000000) && (flags & 0x40000000)) {
        HSD_StateSetZCompLoc(0);
        HSD_StateSetAlphaCompare(4U, 0U, 0U, 4U, 0U);
    } else {
        HSD_StateSetZCompLoc(1);
        HSD_StateSetAlphaCompare(7U, 0U, 0U, 7U, 0U);
    }
    HSD_StateSetDither(0);
}

static void setupTevMode_last(void)
{
    if (!HSD_StateGetNumTevStages()) {
        HSD_TevDesc tevdesc;
        tevdesc.flags = 0;
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = 0xFF;
        tevdesc.map = GX_TEXMAP_NULL;
        tevdesc.color = GX_COLOR0A0;
        tevdesc.u.tevop.tevmode = GX_PASSCLR;
        HSD_SetupTevStage(&tevdesc);
    }
}

void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe)
{
    setupTevMode_last();
    HSD_SetupPEMode(rendermode, pe);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_SetupChannelMode(rendermode);
}

void HSD_SetupRenderMode(u32 rendermode)
{
    HSD_SetupRenderModeWithCustomPE(rendermode, NULL);
}

void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          f32 alpha)
{
    matstate.ambient = ambient;
    matstate.diffuse = diffuse;
    matstate.specular = specular;
    matstate.alpha = 255.0 * alpha;
}

void HSD_SetMaterialShininess(f32 shininess)
{
    matstate.shininess = shininess;
}

void HSD_StateSetLineWidth(u8 arg0, int arg1)
{
    if (state_line_width != arg0 || state_line_tex_offsets != arg1) {
        GXSetLineWidth(arg0, arg1);
        state_line_width = arg0;
        state_line_tex_offsets = arg1;
    }
}

void HSD_StateSetCullMode(int mode)
{
    if (state_cull_mode != mode) {
        GXSetCullMode(mode);
        state_cull_mode = mode;
    }
}

void HSD_StateSetBlendMode(int type, int src_factor, int dst_factor, int op)
{
    if (state_blend_type != type || state_src_factor != src_factor ||
        state_dst_factor != dst_factor || state_logic_op != op)
    {
        GXSetBlendMode(type, src_factor, dst_factor, op);
        state_blend_type = type;
        state_src_factor = src_factor;
        state_dst_factor = dst_factor;
        state_logic_op = op;
    }
}

void HSD_StateSetZMode(int arg0, int arg1, int arg2)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    arg2 = arg2 ? GX_TRUE : GX_FALSE;

    if (state_z_enable != arg0 || state_z_func != arg1 ||
        state_z_update != arg2)
    {
        GXSetZMode(arg0, arg1, arg2);
        state_z_enable = arg0;
        state_z_func = arg1;
        state_z_update = arg2;
    }
}

void HSD_StateSetPointSize(u8 arg0, int arg1)
{
    if (state_point_size != arg0 || HSD_State_804D75BC != arg1) {
        GXSetPointSize(arg0, arg1);
        state_point_size = arg0;
        HSD_State_804D75BC = arg1;
    }
}

void HSD_StateSetAlphaCompare(int arg0, u8 arg1, int arg2, int arg3, u8 arg4)
{
    if (state_alpha_comp0 != arg0 || state_alpha_ref0 != arg1 ||
        state_alpha_op != arg2 || state_alpha_comp1 != arg3 ||
        state_alpha_ref1 != arg4)
    {
        GXSetAlphaCompare(arg0, arg1, arg2, arg3, arg4);
        state_alpha_comp0 = arg0;
        state_alpha_ref0 = arg1;
        state_alpha_op = arg2;
        state_alpha_comp1 = arg3;
        state_alpha_ref1 = arg4;
    }
}

void HSD_StateSetColorUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_color_update != arg0) {
        GXSetColorUpdate(arg0);
        state_color_update = arg0;
    }
}

void HSD_StateSetAlphaUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_alpha_update != arg0) {
        GXSetAlphaUpdate(arg0);
        state_alpha_update = arg0;
    }
}

void HSD_StateSetDstAlpha(int arg0, u8 arg1)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_enable_dst_alpha != arg0 || state_dst_alpha != arg1) {
        GXSetDstAlpha(arg0, arg1);
        state_enable_dst_alpha = arg0;
        state_dst_alpha = arg1;
    }
}

void HSD_StateSetZCompLoc(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_before_tex != arg0) {
        GXSetZCompLoc(arg0);
        state_before_tex = (u8) arg0;
    }
}

void HSD_StateSetDither(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_dither != arg0) {
        GXSetDither(arg0);
        state_dither = arg0;
    }
}

void _HSD_StateInvalidatePrimitive(void)
{
    state_line_width = 0;
    state_point_size = 0;
    state_cull_mode = -1;
}

void _HSD_StateInvalidateVtxAttr(void)
{
    HSD_ClearVtxDesc();
}

void _HSD_StateInvalidateRenderMode(void)
{
    state_blend_type = -1;
    state_src_factor = -1;
    state_dst_factor = -1;
    state_logic_op = -1;
    state_z_enable = -1;
    state_z_func = -1;
    state_z_update = -1;
    state_alpha_comp0 = -1;
    state_alpha_ref0 = 0;
    state_alpha_op = -1;
    state_alpha_comp1 = -1;
    state_alpha_ref1 = 0;
    state_color_update = -1;
    state_alpha_update = -1;
    state_enable_dst_alpha = -1;
    state_dst_alpha = 0;
    state_before_tex = -1;
    state_dither = -1;
}

void HSD_StateInvalidate(int mask)
{
    int i;
    for (i = 0; invalidate_funcs[i].mask != HSD_STATE_NONE; i++) {
        if (mask & invalidate_funcs[i].mask) {
            invalidate_funcs[i].func();
        }
    }
}
