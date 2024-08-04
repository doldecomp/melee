#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

// GXLightObj private data
struct __GXLightObjInt_struct {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
};

void GXInitLightAttn(GXLightObj *lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x62, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x63, "GXInitLightAttn");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightAttnA(GXLightObj *lt_obj, f32 a0, f32 a1, f32 a2)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x70, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x71, "GXInitLightAttnA");
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXGetLightAttnA(GXLightObj *lt_obj, f32 *a0, f32 *a1, f32 *a2)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x7A, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x7B, "GXGetLightAttnA");
    *a0 = obj->a[0];
    *a1 = obj->a[1];
    *a2 = obj->a[2];
}

void GXInitLightAttnK(GXLightObj *lt_obj, f32 k0, f32 k1, f32 k2)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x84, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x85, "GXInitLightAttnK");
    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXGetLightAttnK(GXLightObj *lt_obj, f32 *k0, f32 *k1, f32 *k2)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x8E, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x8F, "GXGetLightAttnK");
    *k0 = obj->k[0];
    *k1 = obj->k[1];
    *k2 = obj->k[2];
}

void GXInitLightSpot(GXLightObj *lt_obj, f32 cutoff, GXSpotFn spot_func)
{
    float a0, a1, a2;
    float r;
    float d;
    float cr;
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0xA7, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0xA9, "GXInitLightSpot");

    if (cutoff <= 0.0f || cutoff > 90.0f)
        spot_func = GX_SP_OFF;

    r = (3.1415927f * cutoff) / 180.0f;
    cr = cosf(r);
    switch (spot_func) {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a0 = -cr / (1.0f - cr);
        a1 = 1.0f / (1.0f - cr);
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a0 = 0.0f;
        a1 = -cr / (1.0f - cr);
        a2 = 1.0f / (1.0f - cr);
        break;
    case GX_SP_SHARP:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = (cr * (cr - 2.0f)) / d;
        a1 = 2.0f / d;
        a2 = -1.0f / d;
        break;
    case GX_SP_RING1:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = (-4.0f * cr) / d;
        a1 = (4.0f * (1.0f + cr)) / d;
        a2 = -4.0f / d;
        break;
    case GX_SP_RING2:
        d = (1.0f - cr) * (1.0f - cr);
        a0 = 1.0f - ((2.0f * cr * cr) / d);
        a1 = (4.0f * cr) / d;
        a2 = -2.0f / d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}

void GXInitLightDistAttn(GXLightObj *lt_obj, f32 ref_dist, f32 ref_br, GXDistAttnFn dist_func)
{
    f32 k0, k1, k2;
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0xF2, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0xF4, "GXInitLightDistAttn");

    if (ref_dist < 0.0f)
        dist_func = GX_DA_OFF;
    if (ref_br <= 0.0f || ref_br >= 1.0f)
        dist_func = GX_DA_OFF;

    switch (dist_func) {
    case GX_DA_GENTLE:
        k0 = 1.0f;
        k1 = (1.0f - ref_br) / (ref_br * ref_dist);
        k2 = 0.0f;
        break;
    case GX_DA_MEDIUM:
        k0 = 1.0f;
        k1 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist);
        k2 = (0.5f * (1.0f - ref_br)) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_STEEP:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = (1.0f - ref_br) / (ref_br * ref_dist * ref_dist);
        break;
    case GX_DA_OFF:
    default:
        k0 = 1.0f;
        k1 = 0.0f;
        k2 = 0.0f;
        break;
    }

    obj->k[0] = k0;
    obj->k[1] = k1;
    obj->k[2] = k2;
}

void GXInitLightPos(GXLightObj *lt_obj, f32 x, f32 y, f32 z)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x129, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x12B, "GXInitLightPos");

    obj->lpos[0] = x;
    obj->lpos[1] = y;
    obj->lpos[2] = z;
}

void GXGetLightPos(GXLightObj *lt_obj, f32 *x, f32 *y, f32 *z)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x134, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x136, "GXGetLightPos");

    *x = obj->lpos[0];
    *y = obj->lpos[1];
    *z = obj->lpos[2];
}

void GXInitLightDir(GXLightObj *lt_obj, f32 nx, f32 ny, f32 nz)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x149, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;

    obj->ldir[0] = -nx;
    obj->ldir[1] = -ny;
    obj->ldir[2] = -nz;
}

void GXGetLightDir(GXLightObj *lt_obj, f32 *nx, f32 *ny, f32 *nz)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x155, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;

    *nx = -obj->ldir[0];
    *ny = -obj->ldir[1];
    *nz = -obj->ldir[2];
}

void GXInitSpecularDir(GXLightObj *lt_obj, f32 nx, f32 ny, f32 nz)
{
    float mag;
    float vx;
    float vy;
    float vz;
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x16F, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x170, "GXInitSpecularDir");

    vx = -nx;
    vy = -ny;
    vz = -nz + 1.0f;
    mag = 1.0f / sqrtf((vx * vx) + (vy * vy) + (vz * vz));
    obj->ldir[0] = vx * mag;
    obj->ldir[1] = vy * mag;
    obj->ldir[2] = vz * mag;
    obj->lpos[0] = -nx * 1048576.0f;
    obj->lpos[1] = -ny * 1048576.0f;
    obj->lpos[2] = -nz * 1048576.0f;
}

void GXInitSpecularDirHA(GXLightObj *lt_obj, f32 nx, f32 ny, f32 nz, f32 hx, f32 hy, f32 hz)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x18E, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x18F, "GXInitSpecularHA");

    obj->ldir[0] = hx;
    obj->ldir[1] = hy;
    obj->ldir[2] = hz;
    obj->lpos[0] = -nx * 1048576.0f;
    obj->lpos[1] = -ny * 1048576.0f;
    obj->lpos[2] = -nz * 1048576.0f;
}

void GXInitLightColor(GXLightObj *lt_obj, GXColor color)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x1A8, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x1A9, "GXInitLightColor");

    obj->Color = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

void GXGetLightColor(GXLightObj *lt_obj, GXColor *color)
{
    struct __GXLightObjInt_struct *obj;

    ASSERTMSGLINE(0x1B2, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x1B3, "GXGetLightColor");

    color->r = (obj->Color >> 24) & 0xFF;
    color->g = (obj->Color >> 16) & 0xFF;
    color->b = (obj->Color >> 8) & 0xFF;
    color->a = obj->Color & 0xFF;
}

#if DEBUG
#define WRITE_SOME_LIGHT_REG1(val, addr) \
do {  \
    u32 xfData = val; \
    GX_WRITE_U32(val); \
    VERIF_MTXLIGHT(addr, xfData); \
} while (0)

#define WRITE_SOME_LIGHT_REG2(val, addr) \
do {  \
    f32 xfData = val; \
    GX_WRITE_F32(val); \
    VERIF_MTXLIGHT(addr, *(u32 *)&xfData); \
} while (0)
#else
#define WRITE_SOME_LIGHT_REG1(val, addr) GX_WRITE_U32(val)
#define WRITE_SOME_LIGHT_REG2(val, addr) GX_WRITE_F32(val)
#endif

void GXLoadLightObjImm(GXLightObj *lt_obj, GXLightID light)
{
    unsigned long addr;
    unsigned long idx;
    struct __GXLightObjInt_struct * obj;

    ASSERTMSGLINE(0x1C9, lt_obj != NULL, "Light Object Pointer is null");
    obj = (struct __GXLightObjInt_struct *)lt_obj;
    CHECK_GXBEGIN(0x1CA, "GXLoadLightObjImm");

    switch (light) {
    case GX_LIGHT0: idx = 0; break;
    case GX_LIGHT1: idx = 1; break;
    case GX_LIGHT2: idx = 2; break;
    case GX_LIGHT3: idx = 3; break;
    case GX_LIGHT4: idx = 4; break;
    case GX_LIGHT5: idx = 5; break;
    case GX_LIGHT6: idx = 6; break;
    case GX_LIGHT7: idx = 7; break;
    default:
        idx = 0;
        ASSERTMSGLINE(0x1DA, 0, "GXLoadLightStateImm: Invalid Light Id");
        break;
    }

    addr = idx * 0x10 + 0x600;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(addr | 0xF0000);

    WRITE_SOME_LIGHT_REG1(0, addr);
    WRITE_SOME_LIGHT_REG1(0, addr + 1);
    WRITE_SOME_LIGHT_REG1(0, addr + 2);
    WRITE_SOME_LIGHT_REG1(obj->Color, addr + 3);
    WRITE_SOME_LIGHT_REG2(obj->a[0], addr + 4);
    WRITE_SOME_LIGHT_REG2(obj->a[1], addr + 5);
    WRITE_SOME_LIGHT_REG2(obj->a[2], addr + 6);
    WRITE_SOME_LIGHT_REG2(obj->k[0], addr + 7);
    WRITE_SOME_LIGHT_REG2(obj->k[1], addr + 8);
    WRITE_SOME_LIGHT_REG2(obj->k[2], addr + 9);
    WRITE_SOME_LIGHT_REG2(obj->lpos[0], addr + 10);
    WRITE_SOME_LIGHT_REG2(obj->lpos[1], addr + 11);
    WRITE_SOME_LIGHT_REG2(obj->lpos[2], addr + 12);
    WRITE_SOME_LIGHT_REG2(obj->ldir[0], addr + 13);
    WRITE_SOME_LIGHT_REG2(obj->ldir[1], addr + 14);
    WRITE_SOME_LIGHT_REG2(obj->ldir[2], addr + 15);

    gx->bpSent = 0;
}

void GXLoadLightObjIndx(u32 lt_obj_indx, GXLightID light)
{
    unsigned long reg;
    unsigned long addr;
    unsigned long idx;

    CHECK_GXBEGIN(0x209, "GXLoadLightObjIndx");

    switch (light) {
    case GX_LIGHT0: idx = 0; break;
    case GX_LIGHT1: idx = 1; break;
    case GX_LIGHT2: idx = 2; break;
    case GX_LIGHT3: idx = 3; break;
    case GX_LIGHT4: idx = 4; break;
    case GX_LIGHT5: idx = 5; break;
    case GX_LIGHT6: idx = 6; break;
    case GX_LIGHT7: idx = 7; break;
    default:
        idx = 0;
        ASSERTMSGLINE(0x216, 0, "GXLoadLightObjIndx: Invalid Light Id");
        break;
    }

    addr = idx * 0x10 + 0x600;
    reg = 0;
    SET_REG_FIELD(0x21C, reg, 12, 0, addr);
    SET_REG_FIELD(0x21D, reg, 4, 12, 0xF);
    SET_REG_FIELD(0x21E, reg, 16, 16, lt_obj_indx);
    GX_WRITE_U8(0x38);
    GX_WRITE_U32(reg);
#if DEBUG
    __GXShadowIndexState(7, reg);
#endif
    gx->bpSent = 0;
}

void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color)
{
    u32 reg = 0;
    u32 colIdx;
    u32 alpha;

    CHECK_GXBEGIN(0x239, "GXSetChanAmbColor");

    switch (chan) {
    case GX_COLOR0:
        alpha = gx->ambColor[0] & 0xFF;
        SET_REG_FIELD(0x23E, reg, 8, 0, alpha);
        SET_REG_FIELD(0x23F, reg, 8, 8, amb_color.b);
        SET_REG_FIELD(0x240, reg, 8, 16, amb_color.g);
        SET_REG_FIELD(0x241, reg, 8, 24, amb_color.r);
        colIdx = 0;
        break;
    case GX_COLOR1:
        alpha = gx->ambColor[1] & 0xFF;
        SET_REG_FIELD(0x247, reg, 8, 0, alpha);
        SET_REG_FIELD(0x248, reg, 8, 8, amb_color.b);
        SET_REG_FIELD(0x249, reg, 8, 16, amb_color.g);
        SET_REG_FIELD(0x24A, reg, 8, 24, amb_color.r);
        colIdx = 1;
        break;
    case GX_ALPHA0:
        reg = gx->ambColor[0];
        SET_REG_FIELD(0x250, reg, 8, 0, amb_color.a);
        colIdx = 0;
        break;
    case GX_ALPHA1:
        reg = gx->ambColor[1];
        SET_REG_FIELD(0x256, reg, 8, 0, amb_color.a);
        colIdx = 1;
        break;
    case GX_COLOR0A0:
        SET_REG_FIELD(0x25B, reg, 8, 0, amb_color.a);
        SET_REG_FIELD(0x25C, reg, 8, 8, amb_color.b);
        SET_REG_FIELD(0x25D, reg, 8, 16, amb_color.g);
        SET_REG_FIELD(0x25E, reg, 8, 24, amb_color.r);
        colIdx = 0;
        break;
    case GX_COLOR1A1:
        SET_REG_FIELD(0x263, reg, 8, 0, amb_color.a);
        SET_REG_FIELD(0x264, reg, 8, 8, amb_color.b);
        SET_REG_FIELD(0x265, reg, 8, 16, amb_color.g);
        SET_REG_FIELD(0x266, reg, 8, 24, amb_color.r);
        colIdx = 1;
        break;
    default:
        ASSERTMSGLINE(0x26B, 0, "GXSetChanAmbColor: Invalid Channel Id");
        return;
    }

    GX_WRITE_XF_REG(colIdx + 10, reg);
    gx->bpSent = 0;
    gx->ambColor[colIdx] = reg;
}

void GXSetChanMatColor(GXChannelID chan, GXColor mat_color)
{
    u32 reg = 0;
    u32 alpha;
    u32 colIdx;

    CHECK_GXBEGIN(0x28A, "GXSetChanMatColor");

    switch (chan) {
    case GX_COLOR0:
        alpha = gx->matColor[0] & 0xFF;
        SET_REG_FIELD(0x28F, reg, 8, 0, alpha);
        SET_REG_FIELD(0x290, reg, 8, 8, mat_color.b);
        SET_REG_FIELD(0x291, reg, 8, 16, mat_color.g);
        SET_REG_FIELD(0x292, reg, 8, 24, mat_color.r);
        colIdx = 0;
        break;
    case GX_COLOR1:
        alpha = gx->matColor[1] & 0xFF;
        SET_REG_FIELD(0x298, reg, 8, 0, alpha);
        SET_REG_FIELD(0x299, reg, 8, 8, mat_color.b);
        SET_REG_FIELD(0x29A, reg, 8, 16, mat_color.g);
        SET_REG_FIELD(0x29B, reg, 8, 24, mat_color.r);
        colIdx = 1;
        break;
    case GX_ALPHA0:
        reg = gx->matColor[0];
        SET_REG_FIELD(0x2A1, reg, 8, 0, mat_color.a);
        colIdx = 0;
        break;
    case GX_ALPHA1:
        reg = gx->matColor[1];
        SET_REG_FIELD(0x2A7, reg, 8, 0, mat_color.a);
        colIdx = 1;
        break;
    case GX_COLOR0A0:
        SET_REG_FIELD(0x2AC, reg, 8, 0, mat_color.a);
        SET_REG_FIELD(0x2AD, reg, 8, 8, mat_color.b);
        SET_REG_FIELD(0x2AE, reg, 8, 16, mat_color.g);
        SET_REG_FIELD(0x2AF, reg, 8, 24, mat_color.r);
        colIdx = 0;
        break;
    case GX_COLOR1A1:
        SET_REG_FIELD(0x2B4, reg, 8, 0, mat_color.a);
        SET_REG_FIELD(0x2B5, reg, 8, 8, mat_color.b);
        SET_REG_FIELD(0x2B6, reg, 8, 16, mat_color.g);
        SET_REG_FIELD(0x2B7, reg, 8, 24, mat_color.r);
        colIdx = 1;
        break;
    default:
        ASSERTMSGLINE(0x2BC, 0, "GXSetChanMatColor: Invalid Channel Id");
        return;
    }

    GX_WRITE_XF_REG(colIdx + 12, reg);
    gx->bpSent = 0;
    gx->matColor[colIdx] = reg;
}

void GXSetNumChans(u8 nChans)
{
    CHECK_GXBEGIN(0x2D5, "GXSetNumChans");
    ASSERTMSGLINE(0x2D6, nChans <= 2, "GXSetNumChans: nChans > 2");

    SET_REG_FIELD(0x2D8, gx->genMode, 3, 4, nChans);
    GX_WRITE_XF_REG(9, nChans);
    gx->dirtyState |= 4;
}

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src,
    GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn)
{
    u32 reg; // r31
    u32 idx; // r26

    CHECK_GXBEGIN(0x2F8, "GXSetChanCtrl");

    ASSERTMSGLINE(0x2FB, chan >= 0 && chan <= 5, "GXSetChanCtrl: Invalid Channel Id");

    if (chan == 4)
        idx = 0;
    else if (chan == 5)
        idx = 1;
    else
        idx = chan;

    reg = 0;
    SET_REG_FIELD(0x302, reg, 1, 1, enable);
    SET_REG_FIELD(0x303, reg, 1, 0, mat_src);
    SET_REG_FIELD(0x304, reg, 1, 6, amb_src);
    SET_REG_FIELD(0x305, reg, 1, 2, (light_mask & GX_LIGHT0) != 0);
    SET_REG_FIELD(0x306, reg, 1, 3, (light_mask & GX_LIGHT1) != 0);
    SET_REG_FIELD(0x307, reg, 1, 4, (light_mask & GX_LIGHT2) != 0);
    SET_REG_FIELD(0x308, reg, 1, 5, (light_mask & GX_LIGHT3) != 0);
    SET_REG_FIELD(0x309, reg, 1, 11, (light_mask & GX_LIGHT4) != 0);
    SET_REG_FIELD(0x30A, reg, 1, 12, (light_mask & GX_LIGHT5) != 0);
    SET_REG_FIELD(0x30B, reg, 1, 13, (light_mask & GX_LIGHT6) != 0);
    SET_REG_FIELD(0x30C, reg, 1, 14, (light_mask & GX_LIGHT7) != 0);
    SET_REG_FIELD(0x30E, reg, 2, 7, (attn_fn == 0) ? 0 : diff_fn);
    SET_REG_FIELD(0x30F, reg, 1, 9, (attn_fn != 2));
    SET_REG_FIELD(0x310, reg, 1, 10, (attn_fn != 0));

    GX_WRITE_XF_REG(idx + 14, reg);
    gx->bpSent = 0;
    if (chan == GX_COLOR0A0) {
        GX_WRITE_XF_REG(16, reg);
    } else if (chan == GX_COLOR1A1) {
        GX_WRITE_XF_REG(17, reg);
    }
}
