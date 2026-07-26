#include "psdisp.h"

#include "baselib/cobj.h"
#include "baselib/fog.h"

#include "baselib/forward.h"

#include "baselib/lobj.h"
#include "baselib/mtx.h"
#include "baselib/psdisptev.h"
#include "baselib/psstructs.h"
#include "baselib/state.h"
#include "baselib/util.h"

#include <math_ppc.h>
#include <string.h>

extern float __fabsf(float);
#define fabsf __fabsf
#include <dolphin/gx.h>

typedef struct {
    u8 x0_pad[0x40];
    u8 texture_coords[0x20];
} psdisp_StaticData;

typedef struct {
    u8 sort_frame[0x10];
    char blend_mode_report[0x24];
    char filename[9];
    u8 x3D_pad[3];
} psdisp_ReportData;

typedef struct {
    HSD_Particle* head;
    HSD_Particle* tail;
} psdisp_ParticleSortBucket;

typedef struct {
    f32 type;
    f32 x_scale;
    f32 x_offset;
    f32 y_scale;
    f32 y_offset;
    f32 z_scale;
    f32 z_offset;
} psdisp_Projection;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} psdisp_ProjectionRow;

typedef struct {
    Mtx mtx;
} psdisp_Mtx;

typedef Vec3 Point3d;

typedef struct {
    Mtx view_mtx;
    Mtx inverse_view_mtx;
    psdisp_Projection projection;
    psdisp_ProjectionRow projected_x;
    psdisp_ProjectionRow projected_y;
    u8 x9C_pad[0x10];
    HSD_Particle* particle_list[17];
} psdisp_Cache;

STATIC_ASSERT(sizeof(psdisp_ParticleSortBucket) == 8);
STATIC_ASSERT(sizeof(psdisp_StaticData) == 0x60);
STATIC_ASSERT(sizeof(psdisp_ReportData) == 0x40);
STATIC_ASSERT(sizeof(psdisp_Cache) == 0xF0);
STATIC_ASSERT(offsetof(psdisp_Cache, particle_list) == 0xAC);

/* 39F89C */ static void calcTornadoLastPos(HSD_Particle*, f32*, f32*, f32*);
/* 39FA28 */ static void getColorPrimEnv(HSD_Particle*, GXColor*, GXColor*);
/* 39FB74 */ static void getColorMatAmb(HSD_Particle*, GXColor*, GXColor*);
/* 3B9628 */ extern psdisp_Mtx HSD_PSDisp_803B9628;
/* 40C300 */ extern psdisp_StaticData HSD_PSDisp_8040C300;
/* 40C360 */ extern psdisp_ReportData HSD_PSDisp_8040C360;
/* 4D6380 */ extern u8 HSD_PSDisp_804D6380[2];
/* 4D6384 */ extern u8 HSD_PSDisp_804D6384[2];
/* 4D0908 */ extern HSD_Particle* hsd_804D0908[146];
/* 4D0B50 */ extern void* psTexGroupArray_804D0B50;
/* 4D0C54 */ extern void* psNumCmdList_804D0C54;
/* 4D0FC0 */ extern psdisp_Cache HSD_PSDisp_804D0FC0;
/* 4D7908 */ extern HSD_Fog* HSD_PSDisp_804D7908;
/* 4D790C */ extern s32 HSD_PSDisp_804D790C;
/* 4D7910 */ extern s32 HSD_PSDisp_804D7910;
/* 4D7914 */ extern f32 HSD_PSDisp_804D7914;
/* 4D7918 */ extern f32 HSD_PSDisp_804D7918;
/* 4D791C */ extern f32 HSD_PSDisp_804D791C;
/* 4D7920 */ extern f32 HSD_PSDisp_804D7920;
/* 4D7924 */ extern f32 HSD_PSDisp_804D7924;
/* 4D7928 */ extern f32 HSD_PSDisp_804D7928;
/* 4D792C */ extern s32 HSD_PSDisp_804D792C;
/* 4D7930 */ extern s32 HSD_PSDisp_804D7930;
/* 4D7934 */ extern GXColor HSD_PSDisp_804D7934;
/* 4D7938 */ extern GXColor HSD_PSDisp_804D7938;
/* 4D793C */ extern GXColor HSD_PSDisp_804D793C;
/* 4D7940 */ extern GXColor HSD_PSDisp_804D7940;
/* 4D7944 */ extern GXColor HSD_PSDisp_804D7944;
/* 4D7948 */ extern s32 HSD_PSDisp_804D7948;

void setVtxDesc(s32 fmt)
{
    GXClearVtxDesc();
    switch (fmt) {
    case 0:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        return;
    case 1:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        return;
    case 2:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
        return;
    case 3:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        return;
    case 4:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        return;
    case 5:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        return;
    }
}

static void calcTornadoLastPos(HSD_Particle* pp, f32* x, f32* y, f32* z)
{
    f32 radius;
    f32 px, py, pz;
    f32 sina, sinb, cosa, cosb;
    f32 vx0, vz0;
    HSD_Generator* gp;

    gp = pp->gen;
    /// @bug The following should be accessing pp not gp
    if (gp == NULL) {
        *x = gp->pos.x;
        *y = gp->pos.y;
        *z = gp->pos.z;
        return;
    }

    sina = sinf(pp->grav);
    sinb = sinf(pp->fric);
    cosa = cosf(pp->grav);
    cosb = cosf(pp->fric);

    vz0 = pp->vel.z - gp->aux.tornado.vel;
    vx0 = pp->vel.x - gp->grav;

    radius = ABS(gp->radius);
    radius += vz0 * tanf(ABS(gp->angle));
    radius *= pp->vel.y;
    px = radius * cosf(vx0);
    py = radius * sinf(vx0);
    pz = vz0;

    *x = px * cosb + pz * sinb + gp->pos.x;
    *y = -px * sina * sinb + py * cosa + pz * sina * cosb + gp->pos.y;
    *z = -px * cosa * sinb - py * sina + pz * cosa * cosb + gp->pos.z;
}

static void getColorPrimEnv(HSD_Particle* pp, GXColor* primCol,
                            GXColor* envCol)
{
    if (pp->primColCount) {
        int scale = 65536 * pp->primColRemain / pp->primColCount;
        primCol->r = ((pp->primColTarget.r << 16) +
                      (pp->primCol.r - pp->primColTarget.r) * scale) >>
                     16;
        primCol->g = ((pp->primColTarget.g << 16) +
                      (pp->primCol.g - pp->primColTarget.g) * scale) >>
                     16;
        primCol->b = ((pp->primColTarget.b << 16) +
                      (pp->primCol.b - pp->primColTarget.b) * scale) >>
                     16;
        primCol->a = ((pp->primColTarget.a << 16) +
                      (pp->primCol.a - pp->primColTarget.a) * scale) >>
                     16;
    } else {
        *primCol = pp->primCol;
    }
    if (pp->envColCount) {
        int scale = 65536 * pp->envColRemain / pp->envColCount;
        envCol->r = ((pp->envColTarget.r << 16) +
                     (pp->envCol.r - pp->envColTarget.r) * scale) >>
                    16;
        envCol->g = ((pp->envColTarget.g << 16) +
                     (pp->envCol.g - pp->envColTarget.g) * scale) >>
                    16;
        envCol->b = ((pp->envColTarget.b << 16) +
                     (pp->envCol.b - pp->envColTarget.b) * scale) >>
                    16;
        envCol->a = ((pp->envColTarget.a << 16) +
                     (pp->envCol.a - pp->envColTarget.a) * scale) >>
                    16;
    } else {
        *envCol = pp->envCol;
    }
}

static void getColorMatAmb(HSD_Particle* pp, GXColor* matCol, GXColor* ambCol)
{
    if (pp->matColCount) {
        int scale = 65536 * pp->matColRemain / pp->matColCount;
        matCol->r = matCol->g = matCol->b =
            ((pp->matRGBTarget << 16) +
             (pp->matRGB - pp->matRGBTarget) * scale) >>
            16;
        matCol->a =
            ((pp->matATarget << 16) + (pp->matA - pp->matATarget) * scale) >>
            16;
    } else {
        matCol->r = matCol->g = matCol->b = pp->matRGB;
        matCol->a = pp->matA;
    }
    if (pp->ambColCount) {
        int scale = 65536 * pp->ambColRemain / pp->ambColCount;
        ambCol->r = ambCol->g = ambCol->b =
            ((pp->ambRGBTarget << 16) +
             (pp->ambRGB - pp->ambRGBTarget) * scale) >>
            16;
        ambCol->a =
            ((pp->ambATarget << 16) + (pp->ambA - pp->ambATarget) * scale) >>
            16;
    } else {
        ambCol->r = ambCol->g = ambCol->b = pp->ambRGB;
        ambCol->a = pp->ambA;
    }
}
static inline void getClrTrail(HSD_Particle* pp, GXColor* color)
{
    GXColor env_color;

    if (pp->kind & PrimEnv) {
        color->r = 0xFF;
        color->g = 0xFF;
        color->b = 0xFF;
        color->a = 0xFF;
    } else {
        getColorPrimEnv(pp, color, &env_color);
    }
}

static inline void psSetColor(GXColor* color, u8 value)
{
    color->r = value;
    color->g = value;
    color->b = value;
    color->a = value;
}

static inline void psSetupVtxFormat(GXVtxFmt format, bool has_color,
                                    bool has_texture, GXCompType texture_type)
{
    GXSetVtxAttrFmt(format, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
    if (has_color) {
        GXSetVtxAttrFmt(format, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0U);
    }
    if (has_texture) {
        GXSetVtxAttrFmt(format, GX_VA_TEX0, GX_TEX_ST, texture_type, 0U);
    }
}

static inline void setupChanCtrl(HSD_Particle* pp)
{
    u32 chan_state = pp->kind & (DispLighting | Trail);

    if ((u32) HSD_PSDisp_804D7930 != chan_state) {
        HSD_PSDisp_804D7930 = chan_state;
        GXSetNumChans(1);
        switch (chan_state) {
        default:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        case DispLighting:
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE,
                          HSD_LObjGetLightMaskAttnFunc() ? GX_AF_SPOT
                                                         : GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        case DispLighting | Trail:
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE,
                          HSD_LObjGetLightMaskAttnFunc() ? GX_AF_SPOT
                                                         : GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        case Trail:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0,
                          GX_DF_NONE, GX_AF_NONE);
            break;
        }
    }
}

static inline void setupChanReg(HSD_Particle* pp)
{
    GXColor mat_color;
    GXColor amb_color;
    GXColor prim_color;
    HSD_LObj* lobj;

    if (pp->kind & DispLighting) {
        getColorMatAmb(pp, &mat_color, &amb_color);
        if (pp->kind & PrimEnv) {
            prim_color.r = 0xFF;
            prim_color.g = 0xFF;
            prim_color.b = 0xFF;
        } else {
            getColorPrimEnv(pp, &prim_color, &mat_color);
            amb_color.r = (u8) ((amb_color.r * prim_color.r) >> 8);
            amb_color.g = (u8) ((amb_color.g * prim_color.g) >> 8);
            amb_color.b = (u8) ((amb_color.b * prim_color.b) >> 8);
        }
        if (prim_color.r != HSD_PSDisp_804D7934.r ||
            prim_color.g != HSD_PSDisp_804D7934.g ||
            prim_color.b != HSD_PSDisp_804D7934.b)
        {
            HSD_PSDisp_804D7934 = prim_color;
            GXSetChanMatColor(GX_COLOR0, HSD_PSDisp_804D7934);
        }
        lobj = HSD_LObjGetActiveByID(GX_MAX_LIGHT);
        if (lobj != NULL) {
            HSD_MulColor(&amb_color, &lobj->color, &amb_color);
        } else {
            amb_color.r = 0;
            amb_color.g = 0;
            amb_color.b = 0;
        }
        if (amb_color.r != HSD_PSDisp_804D7938.r ||
            amb_color.g != HSD_PSDisp_804D7938.g ||
            amb_color.b != HSD_PSDisp_804D7938.b)
        {
            HSD_PSDisp_804D7938 = amb_color;
            GXSetChanAmbColor(GX_COLOR0, HSD_PSDisp_804D7938);
        }
    }
}

static inline void setupTevReg(HSD_Particle* pp)
{
    GXColor prim_color;
    GXColor env_color;
    GXColor mat_color;
    GXColor amb_color;

    getColorPrimEnv(pp, &prim_color, &env_color);
    if ((pp->kind & PrimEnv) ||
        (!(pp->kind & DispLighting) && !(pp->kind & Trail)))
    {
        if (HSD_PSDisp_804D793C.r != prim_color.r ||
            HSD_PSDisp_804D793C.g != prim_color.g ||
            HSD_PSDisp_804D793C.b != prim_color.b ||
            HSD_PSDisp_804D793C.a != prim_color.a)
        {
            HSD_PSDisp_804D793C = prim_color;
            GXSetTevColor(GX_TEVREG0, HSD_PSDisp_804D793C);
        }
        if (pp->kind & PrimEnv) {
            if (HSD_PSDisp_804D7940.r != env_color.r ||
                HSD_PSDisp_804D7940.g != env_color.g ||
                HSD_PSDisp_804D7940.b != env_color.b ||
                HSD_PSDisp_804D7940.a != env_color.a)
            {
                HSD_PSDisp_804D7940 = env_color;
                GXSetTevColor(GX_TEVREG1, HSD_PSDisp_804D7940);
            }
        } else if (HSD_PSDisp_804D7940.r != 0 || HSD_PSDisp_804D7940.g != 0 ||
                   HSD_PSDisp_804D7940.b != 0 || HSD_PSDisp_804D7940.a != 0)
        {
            HSD_PSDisp_804D7940.r = 0;
            HSD_PSDisp_804D7940.g = 0;
            HSD_PSDisp_804D7940.b = 0;
            HSD_PSDisp_804D7940.a = 0;
            GXSetTevColor(GX_TEVREG1, HSD_PSDisp_804D7940);
        }
    }
    if (pp->kind & DispLighting) {
        getColorMatAmb(pp, &mat_color, &amb_color);
        if (pp->kind & PrimEnv) {
            if (HSD_PSDisp_804D7944.r != mat_color.r ||
                HSD_PSDisp_804D7944.g != mat_color.g ||
                HSD_PSDisp_804D7944.b != mat_color.b ||
                HSD_PSDisp_804D7944.a != mat_color.a)
            {
                HSD_PSDisp_804D7944 = mat_color;
                GXSetTevColor(GX_TEVREG2, HSD_PSDisp_804D7944);
            }
        } else {
            mat_color.a = (u8) ((mat_color.a * prim_color.a) >> 8);
            if (HSD_PSDisp_804D7944.r != mat_color.r ||
                HSD_PSDisp_804D7944.g != mat_color.g ||
                HSD_PSDisp_804D7944.b != mat_color.b ||
                HSD_PSDisp_804D7944.a != mat_color.a)
            {
                HSD_PSDisp_804D7944 = mat_color;
                GXSetTevColor(GX_TEVREG2, HSD_PSDisp_804D7944);
            }
        }
    }
}

static inline void psSetupParticleColors(HSD_Particle* pp)
{
    setupChanReg(pp);
    setupTevReg(pp);
}

static inline void psSetupParticleRenderState(HSD_Particle* pp)
{
    psSetupTev((u32*) pp);
    setupChanCtrl(pp);
    psSetupParticleColors(pp);
}

HSD_Particle* particleSort(s32 arg0, u8 arg1, HSD_Particle** arg2,
                           HSD_Particle** arg3)
{
    psdisp_ParticleSortBucket buckets[16];
    HSD_Particle** new_var;
    HSD_Particle* var_r28;
    HSD_Particle* var_r3;
    HSD_Particle* var_r4;
    HSD_Particle* var_r5;
    HSD_Particle* var_r7;
    HSD_Particle** temp_r29;
    HSD_Particle** var_r6_2;
    HSD_Particle** var_r7_2;
    psdisp_Cache* cache;
    s32 i;
    u32 temp_r3;
    u32 temp_r3_2;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r6;
    u8* temp_r9;

    temp_r9 = &HSD_PSDisp_8040C360.sort_frame[arg0];
    temp_r29 = (new_var = &hsd_804D0908[arg0]);
    cache = &HSD_PSDisp_804D0FC0;
    var_r28 = *temp_r29;
    if (*temp_r9 == arg1) {
        *arg2 = var_r28;
        *arg3 = cache->particle_list[arg0];
        return var_r28;
    }

    *temp_r9 = arg1;
    if (var_r28 == NULL) {
        cache->particle_list[arg0] = NULL;
        *arg2 = NULL;
        *arg3 = NULL;
        return NULL;
    }

    memset(buckets, 0, sizeof(buckets));
    temp_r3 = var_r28->kind;
    if (temp_r3 & 8) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }
    temp_r4 = ((temp_r3 >> 0x19) & 7) + (var_r0 * 8);
    buckets[temp_r4].head = var_r28;
    var_r6 = temp_r4;
    var_r7 = var_r28->next;

    while (var_r7 != NULL) {
        if ((var_r28->kind ^ var_r7->kind) & 0x0E000008) {
            buckets[var_r6].tail = var_r28;
            temp_r3_2 = var_r7->kind;
            if (temp_r3_2 & 8) {
                var_r0_2 = 0;
            } else {
                var_r0_2 = 1;
            }
            var_r6 = ((temp_r3_2 >> 0x19) & 7) + (var_r0_2 * 8);
            if (buckets[var_r6].head == NULL) {
                buckets[var_r6].head = var_r7;
            } else {
                buckets[var_r6].tail->next = var_r7;
            }
        }
        var_r28 = var_r7;
        var_r7 = var_r7->next;
    }
    buckets[var_r6].tail = var_r28;

    var_r6_2 = NULL;
    var_r4 = NULL;
    var_r7_2 = NULL;
    var_r5 = NULL;

    for (i = 0; i < 8; i++) {
        if (buckets[i].head != NULL) {
            if (var_r4 == NULL) {
                var_r4 = buckets[i].head;
            } else {
                *var_r6_2 = buckets[i].head;
            }
            var_r6_2 = &buckets[i].tail->next;
        }
    }

    for (i = 8; i < 16; i++) {
        if (buckets[i].head != NULL) {
            if (var_r5 == NULL) {
                var_r5 = buckets[i].head;
            } else {
                *var_r7_2 = buckets[i].head;
            }
            var_r7_2 = &buckets[i].tail->next;
        }
    }

    var_r3 = NULL;
    if (var_r6_2 != NULL) {
        var_r3 = var_r4;
        *var_r6_2 = var_r5;
    }
    if (var_r7_2 != NULL) {
        if (var_r3 == NULL) {
            var_r3 = var_r5;
        }
        *var_r7_2 = NULL;
    }

    *temp_r29 = var_r3;
    cache->particle_list[arg0] = var_r5;
    *arg2 = var_r3;
    *arg3 = var_r5;
    return var_r3;
}

static inline HSD_Particle* psDispSubPoint(HSD_Particle* pp)
{
    Vec3 buf[16];
    Vec3* p;
    HSD_Particle* last;
    HSD_Particle* q;
    s32 count;
    s32 i;
    f32 fw;
    s32 w;

    psSetCurrentMtx(0);
    fw = (pp->size > 42.5f) ? 255.0f : 6.0f * pp->size;
    w = (s32) fw;
    if (HSD_PSDisp_804D790C != (s32) (u8) w) {
        HSD_PSDisp_804D790C = (u8) w;
        GXSetPointSize((u8) w, GX_TO_ONE);
    }
    last = pp;
    p = buf;
    p->x = pp->pos.x;
    p->y = pp->pos.y;
    p->z = pp->pos.z;
    p++;
    count = 1;
    q = pp->next;
    while (q != NULL) {
        if (q->size == pp->size && q->appsrt == NULL &&
            !((q->kind ^ pp->kind) & 0xC0100400) && q->primColCount == 0 &&
            q->primCol.r == pp->primCol.r && q->primCol.g == pp->primCol.g &&
            q->primCol.b == pp->primCol.b && q->primCol.a == pp->primCol.a &&
            !(q->kind & DispPoint) &&
            (!(pp->kind & DispLighting) ||
             (q->matColCount == 0 && q->ambColCount == 0 &&
              q->matRGB == pp->matRGB && q->matA == pp->matA &&
              q->ambRGB == pp->ambRGB && q->ambA == pp->ambA)))
        {
            count++;
            p->x = q->pos.x;
            p->y = q->pos.y;
            p->z = q->pos.z;
            p++;
            if (count == 16) {
                if (pp->kind & DispTexture) {
                    setVtxDesc(0);
                    GXBegin(GX_POINTS, GX_VTXFMT0, 16U);
                } else {
                    setVtxDesc(1);
                    GXBegin(GX_POINTS, GX_VTXFMT1, 16U);
                }
                for (p = buf, i = count; i != 0; i--) {
                    f32 z = p->z;
                    f32 y = p->y;
                    f32 x = p->x;
                    p++;
                    GXWGFifo.f32 = x;
                    GXWGFifo.f32 = y;
                    GXWGFifo.f32 = z;
                    if (pp->kind & DispTexture) {
                        GXWGFifo.f32 = 1;
                    }
                }
                p = buf;
                count = 0;
            }
            last = q;
            q = q->next;
        } else {
            break;
        }
    }
    if (count != 0) {
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_POINTS, GX_VTXFMT0, (u16) count);
        } else {
            setVtxDesc(1);
            GXBegin(GX_POINTS, GX_VTXFMT1, (u16) count);
        }
        for (p = buf, i = count; i != 0; i--) {
            f32 z = p->z;
            f32 y = p->y;
            f32 x = p->x;
            p++;
            GXWGFifo.f32 = x;
            GXWGFifo.f32 = y;
            GXWGFifo.f32 = z;
            if (pp->kind & DispTexture) {
                GXWGFifo.f32 = 1;
            }
        }
    }
    return last;
}

static inline HSD_Particle* psDispSubPointTrail(HSD_Particle* pp)
{
    struct {
        Vec3 cur;
        Vec3 prev;
    } vbuf[16];
    struct {
        GXColor c0;
        GXColor c1;
    } cbuf[16];
    GXColor env;
    HSD_Particle* last;
    HSD_Particle* q;
    s32 count;
    s32 i;
    f32 fw;
    s32 w;

    psSetCurrentMtx(0);
    fw = (pp->size > 42.5f) ? 255.0f : 6.0f * pp->size;
    w = (s32) fw;
    if (HSD_PSDisp_804D7910 != (s32) (u8) w) {
        HSD_PSDisp_804D7910 = (u8) w;
        GXSetLineWidth((u8) w, GX_TO_ONE);
    }
    last = pp;
    vbuf[0].cur = pp->pos;
    if (pp->kind & Tornado) {
        calcTornadoLastPos(pp, &vbuf[0].prev.x, &vbuf[0].prev.y,
                           &vbuf[0].prev.z);
    } else {
        vbuf[0].prev.x = pp->pos.x - pp->vel.x;
        vbuf[0].prev.y = pp->pos.y - pp->vel.y;
        vbuf[0].prev.z = pp->pos.z - pp->vel.z;
    }
    getClrTrail(pp, &cbuf[0].c0);
    count = 1;
    cbuf[0].c1 = cbuf[0].c0;
    cbuf[0].c1.a = (u8) ((f32) cbuf[0].c1.a * pp->trail);
    q = pp->next;
    while (q != NULL) {
        if (q->size == pp->size && q->appsrt == NULL &&
            !((q->kind ^ pp->kind) & 0xC0100400) && !(q->kind & DispPoint))
        {
            vbuf[count].cur.x = q->pos.x;
            vbuf[count].cur.y = q->pos.y;
            vbuf[count].cur.z = q->pos.z;
            if (q->kind & Tornado) {
                calcTornadoLastPos(q, &vbuf[count].prev.x, &vbuf[count].prev.y,
                                   &vbuf[count].prev.z);
            } else {
                vbuf[count].prev.x = q->pos.x - q->vel.x;
                vbuf[count].prev.y = q->pos.y - q->vel.y;
                vbuf[count].prev.z = q->pos.z - q->vel.z;
            }
            getClrTrail(q, &cbuf[count].c0);
            count++;
            cbuf[count - 1].c1 = cbuf[count - 1].c0;
            cbuf[count - 1].c1.a =
                (u8) ((f32) cbuf[count - 1].c1.a * q->trail);
            if (count == 16) {
                if (pp->kind & DispTexture) {
                    setVtxDesc(2);
                    GXBegin(GX_LINES, GX_VTXFMT2, 0x20U);
                } else {
                    setVtxDesc(3);
                    GXBegin(GX_LINES, GX_VTXFMT3, 0x20U);
                }
                for (i = 0; i < count; i++) {
                    GXWGFifo.f32 = vbuf[i].prev.x;
                    GXWGFifo.f32 = vbuf[i].prev.y;
                    GXWGFifo.f32 = vbuf[i].prev.z;
                    GXWGFifo.u8 = cbuf[i].c1.r;
                    GXWGFifo.u8 = cbuf[i].c1.g;
                    GXWGFifo.u8 = cbuf[i].c1.b;
                    GXWGFifo.u8 = cbuf[i].c1.a;
                    if (pp->kind & DispTexture) {
                        GXWGFifo.f32 = 0;
                    }
                    GXWGFifo.f32 = vbuf[i].cur.x;
                    GXWGFifo.f32 = vbuf[i].cur.y;
                    GXWGFifo.f32 = vbuf[i].cur.z;
                    GXWGFifo.u8 = cbuf[i].c0.r;
                    GXWGFifo.u8 = cbuf[i].c0.g;
                    GXWGFifo.u8 = cbuf[i].c0.b;
                    GXWGFifo.u8 = cbuf[i].c0.a;
                    if (pp->kind & DispTexture) {
                        GXWGFifo.f32 = 1;
                    }
                }
                count = 0;
            }
            last = q;
            q = q->next;
        } else {
            break;
        }
    }
    if (count != 0) {
        if (pp->kind & DispTexture) {
            setVtxDesc(2);
            GXBegin(GX_LINES, GX_VTXFMT2, (count * 2) & 0xFFFE);
        } else {
            setVtxDesc(3);
            GXBegin(GX_LINES, GX_VTXFMT3, (count * 2) & 0xFFFE);
        }
        for (i = 0; i < count; i++) {
            GXWGFifo.f32 = vbuf[i].prev.x;
            GXWGFifo.f32 = vbuf[i].prev.y;
            GXWGFifo.f32 = vbuf[i].prev.z;
            GXWGFifo.u8 = cbuf[i].c1.r;
            GXWGFifo.u8 = cbuf[i].c1.g;
            GXWGFifo.u8 = cbuf[i].c1.b;
            GXWGFifo.u8 = cbuf[i].c1.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.f32 = 0;
            }
            GXWGFifo.f32 = vbuf[i].cur.x;
            GXWGFifo.f32 = vbuf[i].cur.y;
            GXWGFifo.f32 = vbuf[i].cur.z;
            GXWGFifo.u8 = cbuf[i].c0.r;
            GXWGFifo.u8 = cbuf[i].c0.g;
            GXWGFifo.u8 = cbuf[i].c0.b;
            GXWGFifo.u8 = cbuf[i].c0.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.f32 = 1;
            }
        }
    }
    return last;
}

static inline void setBlendMode(int blend_mode)
{
    if (HSD_PSDisp_804D792C != blend_mode) {
        HSD_PSDisp_804D792C = blend_mode;
        switch (blend_mode) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
            break;
        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE,
                           GX_LO_CLEAR);
            break;
        default:
            OSReport("Particle:setBlendMode:Unknown mode\n");
            break;
        }
    }
}

static inline void psSetCurrentMtx(GXPosNrmMtx idx)
{
    if (HSD_PSDisp_804D7948 != idx) {
        HSD_PSDisp_804D7948 = idx;
        GXSetCurrentMtx(idx);
    }
}

static inline void psDispSubMakePolygon(HSD_Particle* pp, u8* texform, float x,
                                        float y, float z, float ppvx,
                                        float ppvy, float ppvz, float x0,
                                        float y0, float z0, float x1, float y1,
                                        float z1)
{
    Vec3 pos;
    Vec3 prev;
    Vec3 right;
    Vec3 up;
    u8 tex_base = (pp->kind >> 16) & 0xC;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    right.x = x0;
    right.y = y0;
    right.z = z0;
    up.x = x1;
    up.y = y1;
    up.z = z1;

    psSetCurrentMtx(0);
    if (pp->kind & Trail) {
        GXColor color;

        if (pp->kind & Tornado) {
            calcTornadoLastPos(pp, &prev.x, &prev.y, &prev.z);
        } else {
            prev.x = x - ppvx;
            prev.y = y - ppvy;
            prev.z = z - ppvz;
        }
        getClrTrail(pp, &color);
        if (texform == NULL) {
            if (pp->kind & DispTexture) {
                setVtxDesc(2);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4);
            } else {
                setVtxDesc(3);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4);
            }
            GXWGFifo.f32 = prev.x - right.x;
            GXWGFifo.f32 = prev.y - right.y;
            GXWGFifo.f32 = prev.z - right.z;
            GXWGFifo.u8 = color.r;
            GXWGFifo.u8 = color.g;
            GXWGFifo.u8 = color.b;
            GXWGFifo.u8 = (u8) ((f32) color.a * pp->trail);
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base;
            }
            GXWGFifo.f32 = pos.x - up.x;
            GXWGFifo.f32 = pos.y - up.y;
            GXWGFifo.f32 = pos.z - up.z;
            GXWGFifo.u8 = color.r;
            GXWGFifo.u8 = color.g;
            GXWGFifo.u8 = color.b;
            GXWGFifo.u8 = color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 1;
            }
            GXWGFifo.f32 = pos.x + right.x;
            GXWGFifo.f32 = pos.y + right.y;
            GXWGFifo.f32 = pos.z + right.z;
            GXWGFifo.u8 = color.r;
            GXWGFifo.u8 = color.g;
            GXWGFifo.u8 = color.b;
            GXWGFifo.u8 = color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 2;
            }
            GXWGFifo.f32 = prev.x + up.x;
            GXWGFifo.f32 = prev.y + up.y;
            GXWGFifo.f32 = prev.z + up.z;
            GXWGFifo.u8 = color.r;
            GXWGFifo.u8 = color.g;
            GXWGFifo.u8 = color.b;
            GXWGFifo.u8 = (u8) ((f32) color.a * pp->trail);
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 3;
            }
        } else {
            f32 trail_alpha = 255.0f * (1.0f - pp->trail);
            f32 up_len = sqrtf(up.x * up.x + up.y * up.y + up.z * up.z);

            if (up_len != 0.0f) {
                f32 dx = pos.x - prev.x;
                f32 dy = pos.y - prev.y;
                f32 dz = pos.z - prev.z;
                f32 segment_len = sqrtf(dx * dx + dy * dy + dz * dz);
                f32 ratio = segment_len / up_len;
                u8* it = texform;
                u32 primitive_count = *(u32*) it;

                it += sizeof(u32);
                while (primitive_count-- != 0) {
                    GXPrimitive primitive = it[0];
                    u8 count = it[1];
                    u8 vertex_count = count;

                    it += 4;
                    if (pp->kind & DispTexture) {
                        setVtxDesc(5);
                        GXBegin(primitive, GX_VTXFMT5, count);
                    } else {
                        setVtxDesc(3);
                        GXBegin(primitive, GX_VTXFMT3, count);
                    }
                    while (vertex_count-- != 0) {
                        f32 s = *(f32*) &it[0];
                        f32 sx = 2.0f * (s - 0.5f);
                        f32 t;
                        f32 tx;
                        s32 alpha;

                        if (pp->kind & TexFlipS) {
                            s = 1.0f - s;
                        }
                        t = *(f32*) &it[4];
                        it += 8;
                        alpha = (s32) (255.0f - t * trail_alpha);
                        if (alpha < 0) {
                            alpha = 0;
                        }
                        if (alpha > 0xFF) {
                            alpha = 0xFF;
                        }
                        tx = 2.0f * (t - 0.5f);
                        if (pp->kind & TexFlipT) {
                            t = 1.0f - t;
                        }
                        GXWGFifo.f32 =
                            up.x * ratio * tx + (right.x * sx + pos.x);
                        GXWGFifo.f32 =
                            up.y * ratio * tx + (right.y * sx + pos.y);
                        GXWGFifo.f32 =
                            up.z * ratio * tx + (right.z * sx + pos.z);
                        GXWGFifo.u8 = color.r;
                        GXWGFifo.u8 = color.g;
                        GXWGFifo.u8 = color.b;
                        GXWGFifo.u8 = alpha;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.f32 = s;
                            GXWGFifo.f32 = t;
                        }
                    }
                }
            }
        }
    } else if (texform == NULL) {
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        } else {
            setVtxDesc(1);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4);
        }
        GXWGFifo.f32 = pos.x - right.x;
        GXWGFifo.f32 = pos.y - right.y;
        GXWGFifo.f32 = pos.z - right.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base;
        }
        GXWGFifo.f32 = pos.x - up.x;
        GXWGFifo.f32 = pos.y - up.y;
        GXWGFifo.f32 = pos.z - up.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 1;
        }
        GXWGFifo.f32 = pos.x + right.x;
        GXWGFifo.f32 = pos.y + right.y;
        GXWGFifo.f32 = pos.z + right.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 2;
        }
        GXWGFifo.f32 = pos.x + up.x;
        GXWGFifo.f32 = pos.y + up.y;
        GXWGFifo.f32 = pos.z + up.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 3;
        }
    } else {
        u8* it = texform;
        u32 primitive_count = *(u32*) it;

        it += sizeof(u32);
        while (primitive_count-- != 0) {
            GXPrimitive primitive = it[0];
            u8 count = it[1];
            u8 vertex_count = count;

            it += 4;
            if (pp->kind & DispTexture) {
                setVtxDesc(4);
                GXBegin(primitive, GX_VTXFMT4, count);
            } else {
                setVtxDesc(1);
                GXBegin(primitive, GX_VTXFMT1, count);
            }
            while (vertex_count-- != 0) {
                f32 s = *(f32*) &it[0];
                f32 t = *(f32*) &it[4];
                f32 sx;
                f32 tx;

                it += 8;
                if (pp->kind & TexFlipS) {
                    s = 1.0f - s;
                }
                if (pp->kind & TexFlipT) {
                    t = 1.0f - t;
                }
                sx = 2.0f * (s - 0.5f);
                tx = 2.0f * (t - 0.5f);
                GXWGFifo.f32 = pos.x + right.x * sx + up.x * tx;
                GXWGFifo.f32 = pos.y + right.y * sx + up.y * tx;
                GXWGFifo.f32 = pos.z + right.z * sx + up.z * tx;
                if (pp->kind & DispTexture) {
                    GXWGFifo.f32 = s;
                    GXWGFifo.f32 = t;
                }
            }
        }
    }
}

static inline void psDispSub(HSD_Particle* pp, u8* texform)
{
    psdisp_Cache* cache = &HSD_PSDisp_804D0FC0;
    Vec3 right;
    Vec3 up;
    f32 angle;
    Mtx mtx;

    if (texform != NULL) {
        right.x = cache->inverse_view_mtx[0][0] * pp->size;
        right.y = cache->inverse_view_mtx[1][0] * pp->size;
        right.z = cache->inverse_view_mtx[2][0] * pp->size;
        up.x = -cache->inverse_view_mtx[0][1] * pp->size;
        up.y = -cache->inverse_view_mtx[1][1] * pp->size;
        up.z = -cache->inverse_view_mtx[2][1] * pp->size;
    } else {
        right.x = HSD_PSDisp_804D7914 * pp->size;
        right.y = HSD_PSDisp_804D791C * pp->size;
        right.z = HSD_PSDisp_804D7924 * pp->size;
        up.x = HSD_PSDisp_804D7918 * pp->size;
        up.y = HSD_PSDisp_804D7920 * pp->size;
        up.z = HSD_PSDisp_804D7928 * pp->size;
    }
    if ((pp->kind & Trail) || (pp->kind & DirVec)) {
        f32 x = 0.0f;
        f32 y = 0.0f;

        if (cache->projection.type == 0.0f) {
            Vec3 prev;
            f32 w0;

            if (pp->kind & Tornado) {
                calcTornadoLastPos(pp, &prev.x, &prev.y, &prev.z);
            } else {
                prev.x = pp->pos.x - pp->vel.x;
                prev.y = pp->pos.y - pp->vel.y;
                prev.z = pp->pos.z - pp->vel.z;
            }
            w0 = cache->view_mtx[2][3] + (cache->view_mtx[2][2] * pp->pos.z +
                                          (cache->view_mtx[2][0] * pp->pos.x +
                                           cache->view_mtx[2][1] * pp->pos.y));
            if (cache->projection.type != w0) {
                f32 w0inv = 1.0f / w0;
                f32 w1 =
                    cache->view_mtx[2][3] + (cache->view_mtx[2][2] * prev.z +
                                             (cache->view_mtx[2][0] * prev.x +
                                              cache->view_mtx[2][1] * prev.y));

                if (cache->projection.type != w1) {
                    f32 w1inv = 1.0f / w1;
                    f64 cur_y = (f64) (cache->projected_x.y * pp->pos.y);
                    f64 prev_xy = (f64) (cache->projected_x.x * prev.x +
                                         cache->projected_x.y * prev.y);

                    x = w0inv * (cache->projected_x.w +
                                 (cache->projected_x.z * pp->pos.z +
                                  (cache->projected_x.x * pp->pos.x +
                                   (f32) cur_y))) -
                        w1inv *
                            (cache->projected_x.w +
                             (cache->projected_x.z * prev.z + (f32) prev_xy));
                    y = w0inv * (cache->projected_y.w +
                                 (cache->projected_y.z * pp->pos.z +
                                  (cache->projected_y.x * pp->pos.x +
                                   cache->projected_y.y * pp->pos.y))) -
                        w1inv * (cache->projected_y.w +
                                 (cache->projected_y.z * prev.z +
                                  (cache->projected_y.x * prev.x +
                                   cache->projected_y.y * prev.y)));
                }
            }
        } else if (pp->kind & Tornado) {
            Vec3 prev;
            f32 dx;
            f32 dy;
            f32 dz;

            calcTornadoLastPos(pp, &prev.x, &prev.y, &prev.z);
            dx = pp->pos.x - prev.x;
            dy = pp->pos.y - prev.y;
            dz = pp->pos.z - prev.z;
            x = cache->projected_x.z * dz +
                (cache->projected_x.x * dx + cache->projected_x.y * dy);
            y = cache->projected_y.z * dz +
                (cache->projected_y.x * dx + cache->projected_y.y * dy);
        } else {
            x = cache->projected_x.z * pp->vel.z +
                (cache->projected_x.x * pp->vel.x +
                 cache->projected_x.y * pp->vel.y);
            y = cache->projected_y.z * pp->vel.z +
                (cache->projected_y.x * pp->vel.x +
                 cache->projected_y.y * pp->vel.y);
        }
        if (fabsf(y) < 0.00001f) {
            angle = (x >= 0.0f) ? 1.5707964f : -1.5707964f;
        } else {
            angle = atan2f(x, y);
        }
        if (pp->kind & DirVec) {
            angle += pp->rotate;
        }
    } else {
        angle = pp->rotate;
    }
    if (fabsf(angle) > 0.01f) {
        Vec3 axis;
        f32 t1;
        f32 t2;
        f32 t3;
        f32 t4;

        axis.x = right.y * up.z - right.z * up.y;
        axis.y = right.z * up.x - right.x * up.z;
        axis.z = right.x * up.y - right.y * up.x;
        PSMTXRotAxisRad(mtx, &axis, angle);
        t1 = mtx[1][0] * right.x + mtx[1][1] * right.y;
        t2 = mtx[1][0] * up.x + mtx[1][1] * up.y;
        t3 = mtx[2][0] * right.x + mtx[2][1] * right.y;
        t4 = mtx[2][0] * up.x + mtx[2][1] * up.y;
        right.x =
            mtx[0][2] * right.z + (mtx[0][0] * right.x + mtx[0][1] * right.y);
        right.y = mtx[1][2] * right.z + t1;
        right.z = mtx[2][2] * right.z + t3;
        up.x = mtx[0][2] * up.z + (mtx[0][0] * up.x + mtx[0][1] * up.y);
        up.y = mtx[1][2] * up.z + t2;
        up.z = mtx[2][2] * up.z + t4;
    }
    psDispSubMakePolygon(pp, texform, pp->pos.x, pp->pos.y, pp->pos.z,
                         pp->vel.x, pp->vel.y, pp->vel.z, right.x, right.y,
                         right.z, up.x, up.y, up.z);
}

static inline void psUpdateAppSRT(HSD_Particle* pp, psdisp_Cache* cache)
{
    Vec3 scale;
    Mtx temp_mtx;
    f32 scale_x;
    f32 scale_y;

    if (pp->appsrt->frameNum != HSD_PSDisp_804D6380[0]) {
        if (pp->appsrt->status != 2) {
            HSD_MtxSRT(pp->appsrt->mmtx, &pp->appsrt->scale,
                       (Point3d*) &pp->appsrt->rot, &pp->appsrt->translate,
                       NULL);
        }
        if (pp->appsrt->status == 1) {
            pp->appsrt->status = 2;
        }
        PSMTXConcat(cache->view_mtx, pp->appsrt->mmtx,
                    (MtxPtr) &pp->appsrt->ssx);
        scale_x = pp->appsrt->ssx * pp->appsrt->ssx +
                  pp->appsrt->x74 * pp->appsrt->x74 +
                  pp->appsrt->x84 * pp->appsrt->x84;
        scale_x = sqrtf(scale_x);
        pp->appsrt->x94 = scale_x;
        scale_y = pp->appsrt->ssy * pp->appsrt->ssy +
                  pp->appsrt->x78 * pp->appsrt->x78 +
                  pp->appsrt->x88 * pp->appsrt->x88;
        scale_y = sqrtf(scale_y);
        pp->appsrt->x98 = scale_y;
        if (pp->appsrt->xA2 != 0) {
            PSMTXIdentity(temp_mtx);
            temp_mtx[0][3] = pp->appsrt->translate.x;
            temp_mtx[1][3] = pp->appsrt->translate.y;
            temp_mtx[2][3] = pp->appsrt->translate.z;
            PSMTXConcat(cache->view_mtx, temp_mtx, temp_mtx);
            HSD_MtxGetScale(temp_mtx, &scale);
            PSMTXScale((MtxPtr) &pp->appsrt->ssx, scale.x, scale.y, scale.z);
            pp->appsrt->x70 = temp_mtx[0][3];
            pp->appsrt->x80 = temp_mtx[1][3];
            pp->appsrt->x90 = temp_mtx[2][3];
        }
        pp->appsrt->frameNum = HSD_PSDisp_804D6380[0];
    }
}

static inline void psGetAppSRTPositions(HSD_Particle* pp, Mtx draw_mtx,
                                        Vec3* cur_pos, Vec3* prev_pos)
{
    Vec3 last_pos;

    cur_pos->x = draw_mtx[0][0] * pp->pos.x + draw_mtx[0][1] * pp->pos.y +
                 draw_mtx[0][2] * pp->pos.z + draw_mtx[0][3];
    cur_pos->y = draw_mtx[1][0] * pp->pos.x + draw_mtx[1][1] * pp->pos.y +
                 draw_mtx[1][2] * pp->pos.z + draw_mtx[1][3];
    cur_pos->z = draw_mtx[2][0] * pp->pos.x + draw_mtx[2][1] * pp->pos.y +
                 draw_mtx[2][2] * pp->pos.z + draw_mtx[2][3];
    if (pp->kind & Tornado) {
        calcTornadoLastPos(pp, &last_pos.x, &last_pos.y, &last_pos.z);
    } else {
        last_pos.x = pp->pos.x - pp->vel.x;
        last_pos.y = pp->pos.y - pp->vel.y;
        last_pos.z = pp->pos.z - pp->vel.z;
    }
    prev_pos->x = draw_mtx[0][0] * last_pos.x + draw_mtx[0][1] * last_pos.y +
                  draw_mtx[0][2] * last_pos.z + draw_mtx[0][3];
    prev_pos->y = draw_mtx[1][0] * last_pos.x + draw_mtx[1][1] * last_pos.y +
                  draw_mtx[1][2] * last_pos.z + draw_mtx[1][3];
    prev_pos->z = draw_mtx[2][0] * last_pos.x + draw_mtx[2][1] * last_pos.y +
                  draw_mtx[2][2] * last_pos.z + draw_mtx[2][3];
}

static inline void psDispSubAPPSRTPoint(HSD_Particle* pp, psdisp_Cache* cache)
{
    GXColor draw_color;
    GXColor tail_color;
    Vec3 cur_pos;
    Vec3 prev_pos;
    Mtx draw_mtx;
    f32 ax;
    f32 ay;
    u8 tex_base = (pp->kind >> 16) & 0xC;

    psSetCurrentMtx(3);
    psUpdateAppSRT(pp, cache);

    draw_mtx[0][0] = pp->appsrt->ssx;
    draw_mtx[0][1] = pp->appsrt->ssy;
    draw_mtx[0][2] = pp->appsrt->x6C;
    draw_mtx[0][3] = pp->appsrt->x70;
    draw_mtx[1][0] = pp->appsrt->x74;
    draw_mtx[1][1] = pp->appsrt->x78;
    draw_mtx[1][2] = pp->appsrt->x7C;
    draw_mtx[1][3] = pp->appsrt->x80;
    draw_mtx[2][0] = pp->appsrt->x84;
    draw_mtx[2][1] = pp->appsrt->x88;
    draw_mtx[2][2] = pp->appsrt->x8C;
    draw_mtx[2][3] = pp->appsrt->x90;
    psGetAppSRTPositions(pp, draw_mtx, &cur_pos, &prev_pos);

    ax = pp->size > 42.5f ? 255.0f : 6.0f * pp->size;
    if (pp->kind & Trail) {
        if (HSD_PSDisp_804D7910 != (s32) (u8) (s32) ax) {
            HSD_PSDisp_804D7910 = (u8) (s32) ax;
            GXSetLineWidth((u8) HSD_PSDisp_804D7910, GX_TO_ONE);
        }
        getClrTrail(pp, &draw_color);
        tail_color = draw_color;
        tail_color.a = (u8) ((f32) tail_color.a * pp->trail);
        if (pp->kind & DispTexture) {
            setVtxDesc(2);
            GXBegin(GX_LINES, GX_VTXFMT2, 2);
        } else {
            setVtxDesc(3);
            GXBegin(GX_LINES, GX_VTXFMT3, 2);
        }
        GXWGFifo.f32 = prev_pos.x;
        GXWGFifo.f32 = prev_pos.y;
        GXWGFifo.f32 = prev_pos.z;
        GXWGFifo.u8 = tail_color.r;
        GXWGFifo.u8 = tail_color.g;
        GXWGFifo.u8 = tail_color.b;
        GXWGFifo.u8 = tail_color.a;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base;
        }
        GXWGFifo.f32 = cur_pos.x;
        GXWGFifo.f32 = cur_pos.y;
        GXWGFifo.f32 = cur_pos.z;
        GXWGFifo.u8 = draw_color.r;
        GXWGFifo.u8 = draw_color.g;
        GXWGFifo.u8 = draw_color.b;
        GXWGFifo.u8 = draw_color.a;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 1;
        }
    } else {
        if (HSD_PSDisp_804D790C != (s32) (u8) (s32) ax) {
            HSD_PSDisp_804D790C = (u8) (s32) ax;
            GXSetPointSize((u8) HSD_PSDisp_804D790C, GX_TO_ONE);
        }
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_POINTS, GX_VTXFMT0, 1);
        } else {
            setVtxDesc(1);
            GXBegin(GX_POINTS, GX_VTXFMT1, 1);
        }
        GXWGFifo.f32 = cur_pos.x;
        GXWGFifo.f32 = cur_pos.y;
        GXWGFifo.f32 = cur_pos.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 1;
        }
    }
}

static inline void psGetPerspectiveAppSRTDirection(HSD_Particle* pp,
                                                   psdisp_Cache* cache,
                                                   Mtx draw_mtx, f32* dir_x,
                                                   f32* dir_y)
{
    Vec3 prev;
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    f32 x74;
    f32 x78;
    f32 x7C;
    f32 x80;
    f64 d830;
    f64 d840;
    f64 d850;
    f64 d860;
    f64 d870;
    f32 w0;
    f32 f16;
    f32 s808;
    f32 s804;
    f32 f20;
    f32 f12;
    f32 f8;
    f32 f11;
    f32 f13;

    if (pp->kind & Tornado) {
        calcTornadoLastPos(pp, &prev.x, &prev.y, &prev.z);
    } else {
        prev.x = pp->pos.x - pp->vel.x;
        prev.y = pp->pos.y - pp->vel.y;
        prev.z = pp->pos.z - pp->vel.z;
    }
    x84 = draw_mtx[2][0];
    x88 = draw_mtx[2][1];
    x8C = draw_mtx[2][2];
    x90 = draw_mtx[2][3];
    x74 = draw_mtx[1][0];
    x78 = draw_mtx[1][1];
    x7C = draw_mtx[1][2];
    x80 = draw_mtx[1][3];
    d830 = (f64) (cache->projection.x_offset * x90);
    d840 = (f64) (cache->projection.y_offset * x84);
    d850 = (f64) (cache->projection.y_offset * x88);
    d860 = (f64) (cache->projection.y_offset * x8C);
    d870 = (f64) (cache->projection.y_offset * x90);
    w0 = x90 + (x8C * pp->pos.z + (x84 * pp->pos.x + x88 * pp->pos.y));
    f16 = cache->projection.x_scale * draw_mtx[0][2] +
          cache->projection.x_offset * x8C;
    s808 = cache->projection.x_scale * draw_mtx[0][0] +
           cache->projection.x_offset * x84;
    s804 = cache->projection.x_scale * draw_mtx[0][1] +
           cache->projection.x_offset * x88;
    f20 = cache->projection.x_scale * draw_mtx[0][3] + (f32) d830;
    f12 = cache->projection.y_scale * x74 + (f32) d840;
    f8 = cache->projection.y_scale * x78 + (f32) d850;
    f11 = cache->projection.y_scale * x7C + (f32) d860;
    f13 = cache->projection.y_scale * x80 + (f32) d870;
    if (cache->projection.type != w0) {
        f32 w0inv = 1.0f / w0;
        f32 w1 = x90 + (x8C * prev.z + (x84 * prev.x + x88 * prev.y));
        if (cache->projection.type != w1) {
            f32 w1inv = 1.0f / w1;
            *dir_x =
                w0inv * (f20 + (f16 * pp->pos.z +
                                (s808 * pp->pos.x + s804 * pp->pos.y))) -
                w1inv *
                    (f20 + (f16 * prev.z + (s808 * prev.x + s804 * prev.y)));
            *dir_y =
                w0inv * (f13 + (f11 * pp->pos.z +
                                (f12 * pp->pos.x + f8 * pp->pos.y))) -
                w1inv * (f13 + (f11 * prev.z + (f12 * prev.x + f8 * prev.y)));
        }
    }
}

static inline void psScaleAppSRTAxes(HSD_Particle* pp, Mtx mtx)
{
    mtx[0][0] *= pp->size;
    mtx[1][0] *= pp->size;
    mtx[2][0] *= pp->size;
    mtx[0][1] *= pp->size;
    mtx[1][1] *= pp->size;
    mtx[2][1] *= pp->size;
    mtx[0][2] *= pp->size;
    mtx[1][2] *= pp->size;
    mtx[2][2] *= pp->size;
}

static inline void psDispSubAppSRT(HSD_Particle* pp, u8* texform,
                                   psdisp_Cache* cache)
{
    GXColor draw_color;
    GXColor tail_color;
    Vec3 cur_pos;
    Vec3 prev_pos;
    Mtx draw_mtx;
    f32 ax;
    f32 ay;
    f32 bx;
    f32 by;
    f32 angle;
    u8 tex_base = (pp->kind >> 16) & 0xC;

    psUpdateAppSRT(pp, cache);
    PSMTXCopy((MtxPtr) &pp->appsrt->ssx, draw_mtx);
    psGetAppSRTPositions(pp, draw_mtx, &cur_pos, &prev_pos);
    psScaleAppSRTAxes(pp, draw_mtx);
    ax = pp->appsrt->x94 * pp->size;
    ay = 0.0f;
    bx = 0.0f;
    by = -pp->appsrt->x98 * pp->size;
    if (texform == NULL) {
        bx = ax;
        ay = -by;
    }
    if ((pp->kind & Trail) || (pp->kind & DirVec)) {
        f32 vf1 = 0.0f;
        f32 vf2 = 0.0f;
        if (0.0f == cache->projection.type) {
            psGetPerspectiveAppSRTDirection(pp, cache, draw_mtx, &vf1, &vf2);
        } else {
            f32 s800 = cache->projection.x_scale * draw_mtx[0][0] +
                       cache->projection.x_offset;
            f32 s7FC = cache->projection.x_scale * draw_mtx[0][1] +
                       cache->projection.x_offset;
            f32 s7F8 = cache->projection.x_scale * draw_mtx[0][2] +
                       cache->projection.x_offset;
            f32 f17 = cache->projection.y_scale * draw_mtx[1][0] +
                      cache->projection.y_offset;
            f32 f18 = cache->projection.y_scale * draw_mtx[1][1] +
                      cache->projection.y_offset;
            f32 f20 = cache->projection.y_scale * draw_mtx[1][2] +
                      cache->projection.y_offset;
            if (pp->kind & Tornado) {
                Vec3 t;
                calcTornadoLastPos(pp, &t.x, &t.y, &t.z);
                {
                    f32 dy = pp->pos.y - t.y;
                    f32 dx = pp->pos.x - t.x;
                    f32 dz = pp->pos.z - t.z;
                    vf1 = s7F8 * dz + (s800 * dx + s7FC * dy);
                    vf2 = f20 * dz + (f17 * dx + f18 * dy);
                }
            } else {
                f32 vy = pp->vel.y;
                f32 vx = pp->vel.x;
                f32 vz = pp->vel.z;
                vf1 = s7F8 * vz + (s800 * vx + s7FC * vy);
                vf2 = f20 * vz + (f17 * vx + f18 * vy);
            }
        }
        if (fabsf(vf2) < 0.00001f) {
            angle = (-vf1 >= 0.0) ? 1.5707964f : -1.5707964f;
        } else {
            angle = atan2f(-vf1, vf2);
        }
        if (pp->kind & DirVec) {
            angle += pp->rotate;
        }
    } else {
        angle = pp->rotate;
    }
    if (fabsf(angle) > 0.01f) {
        f32 c = cosf(angle);
        f32 s = sinf(angle);
        f32 old_ax = ax;
        f32 old_bx = bx;
        ax = c * ax - s * ay;
        ay = s * old_ax + c * ay;
        bx = c * bx - s * by;
        by = s * old_bx + c * by;
    }
    psSetCurrentMtx(3);
    if (pp->kind & Trail) {
        getClrTrail(pp, &draw_color);
        if (texform == NULL) {
            tail_color = draw_color;
            tail_color.a = (u8) ((f32) tail_color.a * pp->trail);
            if (pp->kind & DispTexture) {
                setVtxDesc(2);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4U);
            } else {
                setVtxDesc(3);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4U);
            }
            GXWGFifo.f32 = prev_pos.x - ax;
            GXWGFifo.f32 = prev_pos.y - ay;
            GXWGFifo.f32 = prev_pos.z;
            GXWGFifo.u8 = tail_color.r;
            GXWGFifo.u8 = tail_color.g;
            GXWGFifo.u8 = tail_color.b;
            GXWGFifo.u8 = tail_color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 0;
            }
            GXWGFifo.f32 = cur_pos.x - bx;
            GXWGFifo.f32 = cur_pos.y - by;
            GXWGFifo.f32 = cur_pos.z;
            GXWGFifo.u8 = draw_color.r;
            GXWGFifo.u8 = draw_color.g;
            GXWGFifo.u8 = draw_color.b;
            GXWGFifo.u8 = draw_color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 1;
            }
            GXWGFifo.f32 = cur_pos.x + ax;
            GXWGFifo.f32 = cur_pos.y + ay;
            GXWGFifo.f32 = cur_pos.z;
            GXWGFifo.u8 = draw_color.r;
            GXWGFifo.u8 = draw_color.g;
            GXWGFifo.u8 = draw_color.b;
            GXWGFifo.u8 = draw_color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 2;
            }
            GXWGFifo.f32 = prev_pos.x + bx;
            GXWGFifo.f32 = prev_pos.y + by;
            GXWGFifo.f32 = prev_pos.z;
            GXWGFifo.u8 = tail_color.r;
            GXWGFifo.u8 = tail_color.g;
            GXWGFifo.u8 = tail_color.b;
            GXWGFifo.u8 = tail_color.a;
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = tex_base + 3;
            }
        } else {
            f32 trail_alpha = 255.0f * (1.0f - pp->trail);
            f32 axis_len = sqrtf(bx * bx + by * by);

            if (axis_len != 0.0f) {
                f32 dx = cur_pos.x - prev_pos.x;
                f32 dy = cur_pos.y - prev_pos.y;
                f32 dz = cur_pos.z - prev_pos.z;
                f32 segment_len = sqrtf(dx * dx + dy * dy + dz * dz);
                f32 ratio = segment_len / axis_len;
                u8* it = texform;
                u32 primitive_count = *(u32*) it;

                bx *= ratio;
                by *= ratio;
                it += sizeof(u32);
                while (primitive_count-- != 0) {
                    GXPrimitive primitive = it[0];
                    u8 count = it[1];
                    u8 vertex_count = count;

                    it += 4;
                    if (pp->kind & DispTexture) {
                        setVtxDesc(5);
                        GXBegin(primitive, GX_VTXFMT5, count);
                    } else {
                        setVtxDesc(3);
                        GXBegin(primitive, GX_VTXFMT3, count);
                    }
                    while (vertex_count-- != 0) {
                        f32 s = *(f32*) &it[0];
                        f32 sx = 2.0f * (s - 0.5f);
                        f32 t;
                        f32 tx;
                        s32 alpha;

                        if (pp->kind & TexFlipS) {
                            s = 1.0f - s;
                        }
                        t = *(f32*) &it[4];
                        it += 8;
                        alpha = (s32) (255.0f - t * trail_alpha);
                        if (alpha < 0) {
                            alpha = 0;
                        }
                        if (alpha > 0xFF) {
                            alpha = 0xFF;
                        }
                        tx = 2.0f * (t - 0.5f);
                        if (pp->kind & TexFlipT) {
                            t = 1.0f - t;
                        }
                        GXWGFifo.f32 = cur_pos.x + ax * sx + bx * tx;
                        GXWGFifo.f32 = cur_pos.y + ay * sx + by * tx;
                        GXWGFifo.f32 = cur_pos.z;
                        GXWGFifo.u8 = draw_color.r;
                        GXWGFifo.u8 = draw_color.g;
                        GXWGFifo.u8 = draw_color.b;
                        GXWGFifo.u8 = alpha;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.f32 = s;
                            GXWGFifo.f32 = t;
                        }
                    }
                }
            }
        }
    } else if (texform != NULL) {
        u8* it = texform;
        u32 primitive_count = *(u32*) it;
        it += sizeof(u32);
        while (primitive_count-- != 0) {
            GXPrimitive prim = it[0];
            u8 count = it[1];
            u8 vtx_count = count;
            it += 4;
            if (pp->kind & DispTexture) {
                setVtxDesc(4);
                GXBegin(prim, GX_VTXFMT4, count);
            } else {
                setVtxDesc(1);
                GXBegin(prim, GX_VTXFMT1, count);
            }
            while (vtx_count-- != 0) {
                f32 s = *(f32*) &it[0];
                f32 t = *(f32*) &it[4];
                it += 8;
                if (pp->kind & TexFlipS) {
                    s = 1.0f - s;
                }
                if (pp->kind & TexFlipT) {
                    t = 1.0f - t;
                }
                GXWGFifo.f32 = cur_pos.x + ax * (2.0f * (s - 0.5f)) +
                               bx * (2.0f * (t - 0.5f));
                GXWGFifo.f32 = cur_pos.y + ay * (2.0f * (s - 0.5f)) +
                               by * (2.0f * (t - 0.5f));
                GXWGFifo.f32 = cur_pos.z;
                if (pp->kind & DispTexture) {
                    GXWGFifo.f32 = s;
                    GXWGFifo.f32 = t;
                }
            }
        }
    } else {
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
        } else {
            setVtxDesc(1);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4U);
        }
        GXWGFifo.f32 = cur_pos.x - ax;
        GXWGFifo.f32 = cur_pos.y - ay;
        GXWGFifo.f32 = cur_pos.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 0;
        }
        GXWGFifo.f32 = cur_pos.x - bx;
        GXWGFifo.f32 = cur_pos.y - by;
        GXWGFifo.f32 = cur_pos.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 1;
        }
        GXWGFifo.f32 = cur_pos.x + ax;
        GXWGFifo.f32 = cur_pos.y + ay;
        GXWGFifo.f32 = cur_pos.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 2;
        }
        GXWGFifo.f32 = cur_pos.x + bx;
        GXWGFifo.f32 = cur_pos.y + by;
        GXWGFifo.f32 = cur_pos.z;
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = tex_base + 3;
        }
    }
}

static inline void psComposeProjectionRow(psdisp_ProjectionRow* dst,
                                          const f32* row, const f32* view_w,
                                          f32 scale, f32 offset,
                                          bool perspective)
{
    if (perspective) {
        dst->x = scale * row[0] + offset * view_w[0];
        dst->y = scale * row[1] + offset * view_w[1];
        dst->z = scale * row[2] + offset * view_w[2];
        dst->w = scale * row[3] + offset * view_w[3];
    } else {
        dst->x = scale * row[0] + offset;
        dst->y = scale * row[1] + offset;
        dst->z = scale * row[2] + offset;
        dst->w = scale * row[3] + offset;
    }
}

static inline void psUpdateBillboardAxes(const Mtx inv_view)
{
    f32 right_x = inv_view[0][0];
    f32 up_x = inv_view[0][1];
    f32 right_y = inv_view[1][0];
    f32 up_y = inv_view[1][1];
    f32 right_z = inv_view[2][0];
    f32 up_z = inv_view[2][1];

    HSD_PSDisp_804D7914 = right_x + up_x;
    HSD_PSDisp_804D7918 = right_x - up_x;
    HSD_PSDisp_804D791C = right_y + up_y;
    HSD_PSDisp_804D7920 = right_y - up_y;
    HSD_PSDisp_804D7924 = right_z + up_z;
    HSD_PSDisp_804D7928 = right_z - up_z;
}

static inline void psUpdateProjectionCache(psdisp_Cache* cache,
                                           f32 perspective)
{
    GXGetProjectionv((f32*) &cache->projection);
    if (cache->projection.type == perspective) {
        psComposeProjectionRow(&cache->projected_x, cache->view_mtx[0],
                               cache->view_mtx[2], cache->projection.x_scale,
                               cache->projection.x_offset, true);
        psComposeProjectionRow(&cache->projected_y, cache->view_mtx[1],
                               cache->view_mtx[2], cache->projection.y_scale,
                               cache->projection.y_offset, true);
    } else {
        psComposeProjectionRow(&cache->projected_x, cache->view_mtx[0],
                               cache->view_mtx[2], cache->projection.x_scale,
                               cache->projection.x_offset, false);
        psComposeProjectionRow(&cache->projected_y, cache->view_mtx[1],
                               cache->view_mtx[2], cache->projection.y_scale,
                               cache->projection.y_offset, false);
    }
    psUpdateBillboardAxes(cache->inverse_view_mtx);
}

#pragma push
#pragma inline_depth(3)
void psDispParticles(s32 arg0, u32 arg1)
{
    f64 sp8B0;
    f64 sp818;
    void* sp7F4;
    void* sp7F0;
    s32 sp7B4;
    void* sp7B0;
    u32 sp7AC;
    u32 sp7A8;
    u8 sp7A5;
    u8 sp7A4;
    s32 sp7A0;
    void* sp79C;
    u32 sp798;
    s32 sp794;
    u16 sp790;
    GXTlutFmt sp788;
    GXTexObj sp764;
    HSD_Particle* sp760;
    HSD_Particle* sp75C;
    psdisp_Mtx billboard_mtx;
    GXTlutObj sp71C;
    f32 sp700;
    GXColor sp6E0;
    GXColor sp6DC;
    GXColor sp6D8;
    GXColor sp6D4;
    GXColor sp6D0;
    u32 prev_kind;
    s32 var_r16;
    s32 var_r15;
    HSD_Particle* pp;
    psdisp_Cache* cache;
    /// @todo Recover this stack space from the original inline hierarchy.
    PAD_STACK(0x40);

    var_r16 = 0;
    var_r15 = 0;
    cache = &HSD_PSDisp_804D0FC0;
    sp798 = arg1;
    sp794 = arg0;
    sp7A5 = 0;
    sp7A4 = 0xFF;
    sp7A0 = 1;
    if (sp798 == 0) {
        if (HSD_PSDisp_804D6380[0] < 0xFFU) {
            HSD_PSDisp_804D6380[0] += 1;
            return;
        }
        HSD_PSDisp_804D6380[0] = 1;
        return;
    }
    sp7F4 = (void*) &psTexGroupArray_804D0B50;
    sp7F0 = (void*) &psNumCmdList_804D0C54;
    sp8B0 = 0.0;
    sp818 = 0.000001;
    sp7B4 = 0;
    do {
        if (sp794 & (1 << sp7B4)) {
            particleSort(sp7B4, HSD_PSDisp_804D6380[0], &sp760, &sp75C);
            if (sp798 == 1) {
                pp = sp760;
            } else {
                pp = sp75C;
            }
            while (pp != NULL) {
                HSD_PSTexGroup* tex_group = NULL;
                HSD_PSFormGroup* form_group = NULL;
                u8* form = NULL;
                void* image;
                void* tlut;
                u32 blend_mode;
                u8 alpha0;
                u8 alpha1;
                Mtx temp_mtx;
                u32 wrap_bits;
                GXTexWrapMode wrap_s;
                GXTexWrapMode wrap_t;

                if ((sp798 == 1) && !(pp->kind & TexEdge)) {
                    break;
                }
                if (pp->size >= (f32) sp818) {
                    if (sp7A0 != 0) {
                        sp79C = NULL;
                        HSD_PSDisp_804D790C = -1;
                        sp7B0 = NULL;
                        HSD_PSDisp_804D7910 = -1;
                        HSD_PSDisp_804D7930 = -1;
                        psSetupTevInvalidState();
                        sp7A8 = (u32) -1;
                        prev_kind &= 0xFEFFFFFF;
                        sp7AC = (u32) -1;
                        HSD_FogSet(NULL);
                        psSetColor(&HSD_PSDisp_804D7934, 0xFF);
                        psSetColor(&HSD_PSDisp_804D7938, 0xFF);
                        sp6E0 = HSD_PSDisp_804D7934;
                        GXSetChanMatColor(GX_COLOR0A0, sp6E0);
                        sp6DC = HSD_PSDisp_804D7938;
                        GXSetChanAmbColor(GX_COLOR0A0, sp6DC);
                        psSetupTevInvalidState();
                        psSetupTevCommon();
                        psSetColor(&HSD_PSDisp_804D793C, 0xFF);
                        psSetColor(&HSD_PSDisp_804D7940, 0);
                        psSetColor(&HSD_PSDisp_804D7944, 0xFF);
                        sp6D8 = HSD_PSDisp_804D793C;
                        GXSetTevColor(GX_TEVREG0, sp6D8);
                        sp6D4 = HSD_PSDisp_804D7940;
                        GXSetTevColor(GX_TEVREG1, sp6D4);
                        sp6D0 = HSD_PSDisp_804D7944;
                        GXSetTevColor(GX_TEVREG2, sp6D0);
                        HSD_PSDisp_804D792C = -1;
                        GXSetZCompLoc(GX_FALSE);
                        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(),
                                              cache->view_mtx);
                        PSMTXInverse(cache->view_mtx, cache->inverse_view_mtx);
                        psUpdateProjectionCache(cache, (f32) sp8B0);
                        GXLoadPosMtxImm(cache->view_mtx, 0);
                        billboard_mtx = HSD_PSDisp_803B9628;
                        GXLoadPosMtxImm(billboard_mtx.mtx, 3);
                        HSD_PSDisp_804D7948 = 3;
                        psSetCurrentMtx(0);
                        GXEnableTexOffsets(GX_TEXCOORD0, GX_TRUE, GX_TRUE);
                        GXSetCullMode(GX_CULL_BACK);
                        GXSetArray(GX_VA_TEX0,
                                   HSD_PSDisp_8040C300.texture_coords, 2U);
                        psSetupVtxFormat(GX_VTXFMT0, false, true, GX_RGB565);
                        psSetupVtxFormat(GX_VTXFMT1, false, false, GX_RGB565);
                        psSetupVtxFormat(GX_VTXFMT2, true, true, GX_RGB565);
                        psSetupVtxFormat(GX_VTXFMT3, true, false, GX_RGB565);
                        psSetupVtxFormat(GX_VTXFMT4, false, true, GX_RGBA6);
                        psSetupVtxFormat(GX_VTXFMT5, true, true, GX_RGBA6);
                        sp7A0 = 0;
                    }

                    blend_mode = (pp->kind >> 0x16U) & 3;
                    setBlendMode(blend_mode);

                    if (pp->aCmpCount != 0) {
                        s32 scale = (65536 * pp->aCmpRemain) / pp->aCmpCount;
                        alpha0 = ((pp->aCmpParam1Target << 16) +
                                  scale * (pp->aCmpParam1 -
                                           pp->aCmpParam1Target)) >>
                                 16;
                        alpha1 = ((pp->aCmpParam2Target << 16) +
                                  scale * (pp->aCmpParam2 -
                                           pp->aCmpParam2Target)) >>
                                 16;
                    } else {
                        alpha0 = pp->aCmpParam1;
                        alpha1 = pp->aCmpParam2;
                    }
                    if ((var_r16 != pp->aCmpMode) || (sp7A5 != alpha0) ||
                        (sp7A4 != alpha1))
                    {
                        sp7A5 = alpha0;
                        var_r16 = pp->aCmpMode;
                        sp7A4 = alpha1;
                        GXSetAlphaCompare((pp->aCmpMode >> 3) & 7, sp7A5,
                                          (pp->aCmpMode >> 6) & 3,
                                          pp->aCmpMode & 7, sp7A4);
                    }

                    psSetupParticleRenderState(pp);
                    if (sp7AC != (pp->kind & TexEdge)) {
                        sp7AC = pp->kind & TexEdge;
                        if (sp7AC != 0) {
                            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                        } else {
                            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                        }
                    }
                    if (((pp->kind ^ prev_kind) & DispFog) != 0) {
                        if (pp->kind & DispFog) {
                            HSD_FogSet(HSD_PSDisp_804D7908);
                        } else {
                            HSD_FogSet(NULL);
                        }
                    }

                    if (sp7F0 != NULL) {
                        HSD_PSFormGroup*** form_array =
                            (HSD_PSFormGroup***) sp7F0;
                        HSD_PSFormGroup** bank_entry = form_array[pp->bank];
                        if (bank_entry != NULL) {
                            form_group = bank_entry[pp->texGroup];
                            if ((form_group != NULL) &&
                                (pp->poseNum < form_group->num))
                            {
                                form = form_group->formTable[pp->poseNum];
                            }
                        }
                    }

                    if (pp->kind & DispTexture) {
                        image = NULL;
                        tlut = NULL;
                        if (pp->kind & MirrorS) {
                            wrap_s = GX_MIRROR;
                        } else {
                            wrap_s = GX_CLAMP;
                        }
                        if (pp->kind & MirrorT) {
                            wrap_t = GX_MIRROR;
                        } else {
                            wrap_t = GX_CLAMP;
                        }
                        wrap_bits = pp->kind & (MirrorS | MirrorT);
                        if (wrap_bits != sp7A8) {
                            sp7A8 = wrap_bits;
                            sp7B0 = NULL;
                            PSMTXScale(
                                temp_mtx, (pp->kind & MirrorS) ? 2.0f : 1.0f,
                                (pp->kind & MirrorT) ? 2.0f : 1.0f, 1.0f);
                            if (pp->kind & MirrorT) {
                                sp700 = 1.0f;
                                temp_mtx[1][3] = sp700;
                            }
                            GXLoadTexMtxImm(temp_mtx, GX_TEXMTX0, GX_MTX2x4);
                            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4,
                                              GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                              GX_PTIDENTITY);
                        }
                        if (sp7F4 != NULL) {
                            HSD_PSTexGroup*** tex_array =
                                (HSD_PSTexGroup***) sp7F4;
                            HSD_PSTexGroup** bank_tex = tex_array[pp->bank];
                            if (bank_tex != NULL) {
                                tex_group = bank_tex[pp->texGroup];
                            }
                        }
                        if (tex_group != NULL) {
                            image = tex_group->texTable[pp->poseNum];
                            if ((tex_group->fmt == GX_TF_C4) ||
                                (tex_group->fmt == GX_TF_C8))
                            {
                                void** palettes =
                                    (void**) &tex_group
                                        ->texTable[tex_group->num];
                                if (pp->palNum != 0xFF) {
                                    tlut = palettes[pp->palNum];
                                } else if (!(pp->kind & ComTLUT)) {
                                    tlut = palettes[pp->poseNum];
                                } else {
                                    tlut = palettes[0];
                                }
                                if (tlut != sp79C) {
                                    sp79C = tlut;
                                    if (tex_group->fmt == GX_TF_C4) {
                                        sp790 = 0x10;
                                    } else {
                                        sp790 = 0x100;
                                    }
                                    sp788 = tex_group->tlutfmt;
                                    if (tlut != NULL) {
                                        GXInitTlutObj(&sp71C, tlut, sp788,
                                                      sp790);
                                        GXLoadTlut(&sp71C, GX_TLUT0);
                                    }
                                    sp7B0 = NULL;
                                }
                            }
                        }
                        if ((image != sp7B0) && (image != NULL)) {
                            sp7B0 = image;
                            switch (tex_group->fmt) {
                            case GX_TF_C4:
                            case GX_TF_C8:
                                GXInitTexObjCI(&sp764, image, tex_group->width,
                                               tex_group->height,
                                               tex_group->fmt, wrap_s, wrap_t,
                                               GX_FALSE, GX_TLUT0);
                                break;
                            case GX_TF_I4:
                            case GX_TF_I8:
                            case GX_TF_IA4:
                            case GX_TF_IA8:
                            case GX_TF_RGB565:
                            case GX_TF_RGB5A3:
                            case GX_TF_RGBA8:
                            case GX_TF_CMPR:
                                GXInitTexObj(&sp764, image, tex_group->width,
                                             tex_group->height, tex_group->fmt,
                                             wrap_s, wrap_t, GX_FALSE);
                                break;
                            default:
                                HSD_ASSERT(0x8AA, 0);
                                break;
                            }
                            var_r15 = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR,
                                (var_r15 != 0) ? GX_NEAR : GX_LINEAR, 0.0f,
                                0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                            GXLoadTexObj(&sp764, GX_TEXMAP0);
                        }
                        if ((pp->kind & TexInterpNear) != (u32) var_r15) {
                            var_r15 = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR,
                                (var_r15 != 0) ? GX_NEAR : GX_LINEAR, 0.0f,
                                0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                            GXLoadTexObj(&sp764, GX_TEXMAP0);
                        }
                    }

                    if (pp->kind & DispPoint) {
                        if (pp->appsrt != NULL) {
                            psDispSubAPPSRTPoint(pp, cache);
                        } else {
                            if (pp->kind & Trail) {
                                pp = psDispSubPointTrail(pp);
                            } else {
                                pp = psDispSubPoint(pp);
                            }
                        }
                    } else if (pp->appsrt != NULL) {
                        psDispSubAppSRT(pp, form, cache);
                    } else {
                        psDispSub(pp, form);
                    }
                }

                prev_kind = pp->kind;
                pp = pp->next;
            }
        }
        sp7B4 += 1;
    } while (sp7B4 < 0x10);
    if (sp7A0 == 0) {
        HSD_StateInvalidate(-1);
    }
}
#pragma pop
