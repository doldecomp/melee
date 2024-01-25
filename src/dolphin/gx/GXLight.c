#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXLight.h>
#include <MSL/trigf.h>

void GXInitLightAttn(GXLightObj* light, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb,
                     f32 kc)
{
    light->aa = aa;
    light->ab = ab;
    light->ac = ac;
    light->ka = ka;
    light->kb = kb;
    light->kc = kc;
}

void GXInitLightSpot(GXLightObj* light, f32 angle, GXSpotFn fn)
{
    f32 rad, temp;
    f32 a, b, c;

    if (angle <= 0.0f || angle > 90.0f) {
        fn = GX_SP_OFF;
    }

    rad = cosf((3.1415927410125732f * angle) / 180.0f);

    switch (fn) {
    case GX_SP_FLAT:
        a = -1000.0f * rad;
        b = 1000.0f;
        c = 0.0f;
        break;
    case GX_SP_COS:
        c = 0.0f;
        a = -rad / (1.0f - rad);
        b = 1.0f / (1.0f - rad);
        break;
    case GX_SP_COS2:
        a = 0.0f;
        b = -rad / (1.0f - rad);
        c = 1.0f / (1.0f - rad);
        break;
    case GX_SP_SHARP:
        temp = 1.0f - rad;
        temp *= temp;
        b = 2.0f / temp;
        a = (rad * (rad - 2.0f)) / temp;
        c = -1.0f / temp;
        break;
    case GX_SP_RING1:
        temp = 1.0f - rad;
        temp *= temp;
        a = (-4.0f * rad) / temp;
        b = (4.0f * (1.0f + rad)) / temp;
        c = -4.0f / temp;
        break;
    case GX_SP_RING2:
        temp = 1.0f - rad;
        temp *= temp;
        a = 1.0f - ((2.0f * rad * rad) / temp);
        b = (4.0f * rad) / temp;
        c = -2.0f / temp;
        break;
    case GX_SP_OFF:
    default:
        b = 0.0f;
        a = 1.0f;
        c = 0.0f;
        break;
    }

    light->aa = a;
    light->ab = b;
    light->ac = c;
}

static void GXInitLightAttnK(GXLightObj* light, f32 ka, f32 kb, f32 kc)
{
    light->ka = ka;
    light->kb = kb;
    light->kc = kc;
}

void GXInitLightDistAttn(GXLightObj* light, f32 ref_distance,
                         f32 ref_brightness, GXDistAttnFn dist_fn)
{
    f32 ka, kb, kc;

    if (ref_distance < 0.0f) {
        dist_fn = GX_DA_OFF;
    }

    if (ref_brightness <= 0.0f || ref_brightness >= 1.0f) {
        dist_fn = GX_DA_OFF;
    }

    switch (dist_fn) {
    case GX_DA_GENTLE:
        ka = 1.0f;
        kb = (1.0f - ref_brightness) / (ref_brightness * ref_distance);
        kc = 0.0f;
        break;
    case GX_DA_MEDIUM:
        ka = 1.0f;
        kb =
            (0.5f * (1.0f - ref_brightness)) / (ref_brightness * ref_distance);
        kc = (0.5f * (1.0f - ref_brightness)) /
             (ref_brightness * ref_distance * ref_distance);
        break;
    case GX_DA_STEEP:
        ka = 1.0f;
        kb = 0.0f;
        kc = (1.0f - ref_brightness) /
             (ref_brightness * ref_distance * ref_distance);
        break;
    case GX_DA_OFF:
    default:
        ka = 1.0f;
        kb = 0.0f;
        kc = 0.0f;
        break;
    }

    GXInitLightAttnK(light, ka, kb, kc);
}

void GXInitLightPos(GXLightObj* light, f32 x, f32 y, f32 z)
{
    light->pos.x = x;
    light->pos.y = y;
    light->pos.z = z;
}

void GXInitLightDir(GXLightObj* light, f32 x, f32 y, f32 z)
{
    light->dir.x = -x;
    light->dir.y = -y;
    light->dir.z = -z;
}

void GXInitLightColor(GXLightObj* light, GXColor color)
{
    *(u32*) &light->color =
        (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

void GXLoadLightObjImm(GXLightObj* light, GXLightID light_id)
{
    u32 ordinal_id;

    switch (light_id) {
    case GX_LIGHT0:
        ordinal_id = 0;
        break;
    case GX_LIGHT1:
        ordinal_id = 1;
        break;
    case GX_LIGHT2:
        ordinal_id = 2;
        break;
    case GX_LIGHT3:
        ordinal_id = 3;
        break;
    case GX_LIGHT4:
        ordinal_id = 4;
        break;
    case GX_LIGHT5:
        ordinal_id = 5;
        break;
    case GX_LIGHT6:
        ordinal_id = 6;
        break;
    case GX_LIGHT7:
        ordinal_id = 7;
        break;
    default:
        ordinal_id = 0;
        break;
    }

    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = ((ordinal_id << 4) + 0x600) | 0xF0000;
    WGPIPE.u32 = 0;
    WGPIPE.u32 = 0;
    WGPIPE.u32 = 0;
    GX_WRITE_U32(light->color);
    GX_WRITE_F32(light->aa);
    GX_WRITE_F32(light->ab);
    GX_WRITE_F32(light->ac);
    GX_WRITE_F32(light->ka);
    GX_WRITE_F32(light->kb);
    GX_WRITE_F32(light->kc);
    GX_WRITE_F32(light->pos.x);
    GX_WRITE_F32(light->pos.y);
    GX_WRITE_F32(light->pos.z);
    GX_WRITE_F32(light->dir.x);
    GX_WRITE_F32(light->dir.y);
    GX_WRITE_F32(light->dir.z);

    set_x2(GX_TRUE);
}

void GXSetChanAmbColor(GXChannelID chan, GXColor* color)
{
    s32 idx;
    u32 val;

    switch (chan) {
    case GX_COLOR0:
        idx = 0;
        val = __GXContexts.main->ambColors[idx] & 0xFF;
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_COLOR1:
        idx = 1;
        val = __GXContexts.main->ambColors[idx] & 0xFF;
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_ALPHA0:
        idx = 0;
        val = __GXContexts.main->ambColors[idx];
        INSERT_FIELD(val, color->a, 8, 0);
        break;
    case GX_ALPHA1:
        idx = 1;
        val = __GXContexts.main->ambColors[idx];
        INSERT_FIELD(val, color->a, 8, 0);
        break;
    case GX_COLOR0A0:
        idx = 0;
        val = 0;
        INSERT_FIELD(val, color->a, 8, 0);
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_COLOR1A1:
        idx = 1;
        val = 0;
        INSERT_FIELD(val, color->a, 8, 0);
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    default:
        return;
    }
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = idx + 0x100A;
    WGPIPE.u32 = val;
    set_x2(GX_TRUE);
    __GXContexts.main->ambColors[idx] = val;
}

void GXSetChanMatColor(GXChannelID id, GXColor* color)
{
    s32 idx;
    u32 val;

    switch (id) {
    case GX_COLOR0:
        idx = 0;
        val = __GXContexts.main->matColors[idx] & 0xFF;
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_COLOR1:
        idx = 1;
        val = __GXContexts.main->matColors[idx] & 0xFF;
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_ALPHA0:
        idx = 0;
        val = __GXContexts.main->matColors[idx];
        INSERT_FIELD(val, color->a, 8, 0);
        break;
    case GX_ALPHA1:
        idx = 1;
        val = __GXContexts.main->matColors[idx];
        INSERT_FIELD(val, color->a, 8, 0);
        break;
    case GX_COLOR0A0:
        idx = 0;
        val = 0;
        INSERT_FIELD(val, color->a, 8, 0);
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    case GX_COLOR1A1:
        idx = 1;
        val = 0;
        INSERT_FIELD(val, color->a, 8, 0);
        INSERT_FIELD(val, color->b, 8, 8);
        INSERT_FIELD(val, color->g, 8, 16);
        INSERT_FIELD(val, color->r, 8, 24);
        break;
    default:
        return;
    }
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = idx + 0x100C;
    WGPIPE.u32 = val;
    set_x2(GX_TRUE);
    __GXContexts.main->matColors[idx] = val;
}

void GXSetNumChans(u8 num_chans)
{
    INSERT_FIELD(__GXContexts.main->x204, num_chans, 3, 4);
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x1009;
    WGPIPE.u32 = num_chans;
    __GXContexts.main->x4F0_flags |= 4;
}

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src,
                   GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn,
                   GXAttnFn attn_fn)
{
    u32 reg;
    int r26;

    if (chan == 4) {
        r26 = 0;
    } else if (chan == 5) {
        r26 = 1;
    } else {
        r26 = chan;
    }

    reg = 0;
    INSERT_FIELD(reg, enable, 1, 1);
    INSERT_FIELD(reg, mat_src, 1, 0);
    INSERT_FIELD(reg, amb_src, 1, 6);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT0) != 0, 1, 2);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT1) != 0, 1, 3);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT2) != 0, 1, 4);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT3) != 0, 1, 5);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT4) != 0, 1, 11);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT5) != 0, 1, 12);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT6) != 0, 1, 13);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT7) != 0, 1, 14);
    INSERT_FIELD(reg, (attn_fn == 0) ? 0 : diff_fn, 2, 7);
    INSERT_FIELD(reg, (attn_fn != 2), 1, 9);
    INSERT_FIELD(reg, (attn_fn != 0), 1, 10);

    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x1000 + (r26 + 14);
    WGPIPE.u32 = reg;
    set_x2(GX_TRUE);
    if (chan == GX_COLOR0A0) {
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1000 + 16;
        WGPIPE.u32 = reg;
    } else if (chan == GX_COLOR1A1) {
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1000 + 17;
        WGPIPE.u32 = reg;
    }
}
