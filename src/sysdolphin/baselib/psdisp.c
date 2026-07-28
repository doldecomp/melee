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
#include <dolphin/gx.h>

typedef struct {
    HSD_Particle* head;
    HSD_Particle* tail;
} psdisp_ParticleSortBucket;

typedef struct {
    GXTlutFmt fmt;
    u32 tlut_name;
    u16 n_entries;
} psdisp_Tlut;

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
    Mtx mtx;
} psdisp_Mtx;

typedef struct {
    Mtx view_mtx;
    Mtx inverse_view_mtx;
    psdisp_Projection projection;
    Vec4 projected_x;
    Vec4 projected_y;
    u8 x9C_pad[0x10];
    HSD_Particle* particle_list[17];
} psdisp_Cache;

/* 39F89C */ static void calcTornadoLastPos(HSD_Particle*, f32*, f32*, f32*);
/* 39FA28 */ static void getColorPrimEnv(HSD_Particle*, GXColor*, GXColor*);
/* 39FB74 */ static void getColorMatAmb(HSD_Particle*, GXColor*, GXColor*);

/* 3B9628 */ static const psdisp_Mtx HSD_PSDisp_803B9628 = {
    { { 1.0F, 0.0F, 0.0F, 0.0F },
      { 0.0F, 1.0F, 0.0F, 0.0F },
      { 0.0F, 0.0F, 1.0F, 0.0F } },
};
/** @remarks Orphaned #ref_INC assertion literals: no caller survives in this
 * unit, but GNT4 emits the live #psSetBillboardCamera body in its generator
 * unit with the same `__assert` strings. */
/* 40C300 */ static char HSD_PSDisp_8040C300[] = "object.h";
/* 40C30C */ static char HSD_PSDisp_8040C30C[] =
    "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF";
/* 40C334 */ static u8 HSD_PSDisp_8040C334[0xC] = { 0 };
/* 40C340 */ static u8 HSD_PSDisp_8040C340[0x20] = {
    0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0,
};
/* 40C360 */ static u8 HSD_PSDisp_8040C360[0x10] = { 0 };
/* 4D6380 */ static u8 HSD_PSDisp_804D6380 = 0x7B;
/* 4D0908 */ extern HSD_Particle* hsd_804D0908[146];
/* 4D0B50 */ extern HSD_PSTexGroup** psTexGroupArray[65];
/* 4D0C54 */ extern HSD_PSFormGroup** psNumCmdList[65];
/* 4D0FC0 */ static psdisp_Cache HSD_PSDisp_804D0FC0;
/* 4D7908 */ static HSD_Fog* HSD_PSDisp_804D7908;
/* 4D790C */ static s32 HSD_PSDisp_804D790C;
/* 4D7910 */ static s32 HSD_PSDisp_804D7910;
/* 4D7914 */ static f32 HSD_PSDisp_804D7914;
/* 4D7918 */ static f32 HSD_PSDisp_804D7918;
/* 4D791C */ static f32 HSD_PSDisp_804D791C;
/* 4D7920 */ static f32 HSD_PSDisp_804D7920;
/* 4D7924 */ static f32 HSD_PSDisp_804D7924;
/* 4D7928 */ static f32 HSD_PSDisp_804D7928;
/* 4D792C */ static s32 HSD_PSDisp_804D792C;
/* 4D7930 */ static s32 HSD_PSDisp_804D7930;
/* 4D7934 */ static GXColor HSD_PSDisp_804D7934;
/* 4D7938 */ static GXColor HSD_PSDisp_804D7938;
/* 4D793C */ static GXColor HSD_PSDisp_804D793C;
/* 4D7940 */ static GXColor HSD_PSDisp_804D7940;
/* 4D7944 */ static GXColor HSD_PSDisp_804D7944;
/* 4D7948 */ static s32 HSD_PSDisp_804D7948[2];

STATIC_ASSERT(sizeof(HSD_PSDisp_8040C340) == 0x20);
STATIC_ASSERT(sizeof(HSD_PSDisp_8040C360) == 0x10);
STATIC_ASSERT(sizeof(HSD_PSDisp_804D0FC0) == 0xF0);
STATIC_ASSERT(sizeof(HSD_PSDisp_804D0FC0) -
                  sizeof(HSD_PSDisp_804D0FC0.particle_list) ==
              0xAC);

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

#pragma push
#pragma dont_inline on
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
#pragma pop

static inline void getClrTrail(HSD_Particle* pp, GXColor* color)
{
    GXColor env_color;

    switch (pp->kind & (DispLighting | PrimEnv)) {
    case 0:
    case DispLighting:
        getColorPrimEnv(pp, color, &env_color);
        break;
    case PrimEnv:
    case DispLighting | PrimEnv:
        color->r = color->g = color->b = color->a = 0xFF;
        break;
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

    if (chan_state != (u32) HSD_PSDisp_804D7930) {
        HSD_PSDisp_804D7930 = chan_state;
        GXSetNumChans(1);
        switch (HSD_PSDisp_804D7930) {
        case Trail:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0,
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
        default:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0,
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
            HSD_PSDisp_804D7940.r = HSD_PSDisp_804D7940.g =
                HSD_PSDisp_804D7940.b = HSD_PSDisp_804D7940.a = 0;
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

    STATIC_ASSERT(sizeof(buckets[0]) == 8);

    temp_r9 = &HSD_PSDisp_8040C360[arg0];
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
    fw = (pp->size > 42.5) ? 255.0f : 6.0f * pp->size;
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
                p = buf;
                if (pp->kind & DispTexture) {
                    setVtxDesc(0);
                    GXBegin(GX_POINTS, GX_VTXFMT0, 16U);
                } else {
                    setVtxDesc(1);
                    GXBegin(GX_POINTS, GX_VTXFMT1, 16U);
                }
                for (i = count; i != 0; i--) {
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
                GXWGFifo.u8 = 1;
            }
        }
    }
    return last;
}

static inline HSD_Particle* psDispSubPointTrail(HSD_Particle* pp)
{
    Vec3 vbuf[32];
    GXColor cbuf[32];
    Vec3* p;
    GXColor* c;
    HSD_Particle* last;
    HSD_Particle* q;
    s32 count;
    s32 i;
    f32 fw;
    s32 w;

    psSetCurrentMtx(0);
    fw = (pp->size > 42.5) ? 255.0f : 6.0f * pp->size;
    w = (s32) fw;
    if (HSD_PSDisp_804D7910 != (s32) (u8) w) {
        HSD_PSDisp_804D7910 = (u8) w;
        GXSetLineWidth((u8) w, GX_TO_ONE);
    }
    last = pp;
    p = vbuf;
    c = cbuf;
    p->x = pp->pos.x;
    p->y = pp->pos.y;
    p->z = pp->pos.z;
    p++;
    if (pp->kind & Tornado) {
        f32 x, y, z;
        calcTornadoLastPos(pp, &x, &y, &z);
        p->x = x;
        p->y = y;
        p->z = z;
    } else {
        p->x = pp->pos.x - pp->vel.x;
        p->y = pp->pos.y - pp->vel.y;
        p->z = pp->pos.z - pp->vel.z;
    }
    p++;
    getClrTrail(pp, c);
    c[1] = c[0];
    count = 1;
    c[1].a = (u8) ((f32) c[1].a * pp->trail);
    c += 2;
    q = pp->next;
    while (q != NULL) {
        if (q->size == pp->size && q->appsrt == NULL &&
            !((q->kind ^ pp->kind) & 0xC0100400) && !(q->kind & DispPoint))
        {
            p->x = q->pos.x;
            p->y = q->pos.y;
            p->z = q->pos.z;
            p++;
            if (q->kind & Tornado) {
                f32 x, y, z;
                calcTornadoLastPos(q, &x, &y, &z);
                p->x = x;
                p->y = y;
                p->z = z;
            } else {
                p->x = q->pos.x - q->vel.x;
                p->y = q->pos.y - q->vel.y;
                p->z = q->pos.z - q->vel.z;
            }
            p++;
            getClrTrail(q, c);
            c[1] = c[0];
            count++;
            c[1].a = (u8) ((f32) c[1].a * q->trail);
            c += 2;
            if (count == 16) {
                p = vbuf;
                c = cbuf;
                if (pp->kind & DispTexture) {
                    setVtxDesc(2);
                    GXBegin(GX_LINES, GX_VTXFMT2, 0x20U);
                } else {
                    setVtxDesc(3);
                    GXBegin(GX_LINES, GX_VTXFMT3, 0x20U);
                }
                for (i = count; i != 0; i--) {
                    {
                        f32 z = p[1].z;
                        f32 y = p[1].y;
                        f32 x = p[1].x;
                        GXWGFifo.f32 = x;
                        GXWGFifo.f32 = y;
                        GXWGFifo.f32 = z;
                    }
                    {
                        u8 a = c[1].a;
                        u8 b = c[1].b;
                        u8 g = c[1].g;
                        u8 r = c[1].r;
                        GXWGFifo.u8 = r;
                        GXWGFifo.u8 = g;
                        GXWGFifo.u8 = b;
                        GXWGFifo.u8 = a;
                    }
                    if (pp->kind & DispTexture) {
                        GXWGFifo.u8 = 0;
                    }
                    {
                        f32 z = p[0].z;
                        f32 y = p[0].y;
                        f32 x = p[0].x;
                        GXWGFifo.f32 = x;
                        GXWGFifo.f32 = y;
                        GXWGFifo.f32 = z;
                    }
                    {
                        u8 a = c[0].a;
                        u8 b = c[0].b;
                        u8 g = c[0].g;
                        u8 r = c[0].r;
                        GXWGFifo.u8 = r;
                        GXWGFifo.u8 = g;
                        GXWGFifo.u8 = b;
                        GXWGFifo.u8 = a;
                    }
                    if (pp->kind & DispTexture) {
                        GXWGFifo.u8 = 1;
                    }
                    p += 2;
                    c += 2;
                }
                p = vbuf;
                c = cbuf;
                count = 0;
            }
            last = q;
            q = q->next;
        } else {
            break;
        }
    }
    if (count != 0) {
        p = vbuf;
        c = cbuf;
        if (pp->kind & DispTexture) {
            setVtxDesc(2);
            GXBegin(GX_LINES, GX_VTXFMT2, count * 2);
        } else {
            setVtxDesc(3);
            GXBegin(GX_LINES, GX_VTXFMT3, count * 2);
        }
        for (i = count; i != 0; i--) {
            {
                f32 z = p[1].z;
                f32 y = p[1].y;
                f32 x = p[1].x;
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            {
                u8 a = c[1].a;
                u8 b = c[1].b;
                u8 g = c[1].g;
                u8 r = c[1].r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = 0;
            }
            {
                f32 z = p[0].z;
                f32 y = p[0].y;
                f32 x = p[0].x;
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            {
                u8 a = c[0].a;
                u8 b = c[0].b;
                u8 g = c[0].g;
                u8 r = c[0].r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = 1;
            }
            p += 2;
            c += 2;
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
    if (HSD_PSDisp_804D7948[0] != idx) {
        HSD_PSDisp_804D7948[0] = idx;
        GXSetCurrentMtx(idx);
    }
}

static inline void psDispSubMakePolygon(HSD_Particle* pp, u8* texform, f32 x,
                                        f32 y, f32 z, f32 ppvx, f32 ppvy,
                                        f32 ppvz, f32 x0, f32 y0, f32 z0,
                                        f32 x1, f32 y1, f32 z1)
{
    f32 prev_x;
    f32 prev_y;
    f32 prev_z;
    u8* it = texform;

    psSetCurrentMtx(0);
    if (pp->kind & Trail) {
        GXColor color;

        if (pp->kind & Tornado) {
            calcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
        } else {
            prev_x = x - pp->vel.x;
            prev_y = y - pp->vel.y;
            prev_z = z - pp->vel.z;
        }
        getClrTrail(pp, &color);
        if (it == NULL) {
            if (pp->kind & DispTexture) {
                setVtxDesc(2);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4);
            } else {
                setVtxDesc(3);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4);
            }
            {
                f32 vx = prev_x - x0;
                f32 vy = prev_y - y0;
                f32 vz = prev_z - z0;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = vz;
            }
            {
                u8 a = color.a;
                u8 b = color.b;
                u8 g = color.g;
                u8 r = color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = (u8) ((f32) a * pp->trail);
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = (pp->kind >> 16) & 0xC;
            }
            {
                f32 vx = x - x1;
                f32 vy = y - y1;
                f32 vz = z - z1;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = vz;
            }
            {
                u8 a = color.a;
                u8 b = color.b;
                u8 g = color.g;
                u8 r = color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 1;
            }
            {
                f32 vx = x + x0;
                f32 vy = y + y0;
                f32 vz = z + z0;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = vz;
            }
            {
                u8 a = color.a;
                u8 b = color.b;
                u8 g = color.g;
                u8 r = color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 2;
            }
            {
                f32 vx = prev_x + x1;
                f32 vy = prev_y + y1;
                f32 vz = prev_z + z1;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = vz;
            }
            {
                u8 a = color.a;
                u8 b = color.b;
                u8 g = color.g;
                u8 r = color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = (u8) ((f32) a * pp->trail);
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 3;
            }
        } else {
            f32 trail_alpha = 255.0f * (1.0f - pp->trail);
            f32 up_len = sqrtf(x1 * x1 + y1 * y1 + z1 * z1);

            if (up_len != 0.0f) {
                f32 dx = x - prev_x;
                f32 dy = y - prev_y;
                f32 dz = z - prev_z;
                f32 xl = dx * dx;
                f32 yl = dy * dy;
                f32 zl = dz * dz;
                f32 segment_len = sqrtf(zl + (xl + yl));
                f32 ratio = segment_len / up_len;
                u32 primitive_count = *(u32*) it;

                it += sizeof(u32);
                x1 *= ratio;
                y1 *= ratio;
                z1 *= ratio;
                for (; primitive_count != 0; primitive_count--) {
                    GXPrimitive primitive = it[0];
                    u8 count = it[1];
                    s32 i;
                    u8 b;
                    u8 g;
                    u8 r;

                    it += 4;
                    if (pp->kind & DispTexture) {
                        setVtxDesc(5);
                        GXBegin(primitive, GX_VTXFMT5, count);
                    } else {
                        setVtxDesc(3);
                        GXBegin(primitive, GX_VTXFMT3, count);
                    }
                    b = color.b;
                    g = color.g;
                    r = color.r;
                    for (i = count; i > 0; i--) {
                        f32 s = *(f32*) &it[0];
                        f32 sx = 2.0f * (s - 0.5f);
                        f32 t;
                        f32 tx;
                        s32 converted_alpha;
                        s32 alpha;

                        if (pp->kind & TexFlipS) {
                            s = 1.0f - s;
                        }
                        t = *(f32*) &it[4];
                        it += 8;
                        converted_alpha = (s32) (255.0f - t * trail_alpha);
                        alpha = (s32) (255.0f - t * trail_alpha);
                        if (converted_alpha < 0) {
                            alpha = 0;
                        }
                        if (alpha > 0xFF) {
                            alpha = 0xFF;
                        }
                        tx = 2.0f * (t - 0.5f);
                        if (pp->kind & TexFlipT) {
                            t = 1.0f - t;
                        }
                        GXWGFifo.f32 = x1 * tx + (x0 * sx + x);
                        GXWGFifo.f32 = y1 * tx + (y0 * sx + y);
                        GXWGFifo.f32 = z1 * tx + (z0 * sx + z);
                        GXWGFifo.u8 = r;
                        GXWGFifo.u8 = g;
                        GXWGFifo.u8 = b;
                        GXWGFifo.u8 = alpha;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.f32 = s;
                            GXWGFifo.f32 = t;
                        }
                    }
                }
            }
        }
    } else if (it == NULL) {
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        } else {
            setVtxDesc(1);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4);
        }
        {
            f32 vx = x - x0;
            f32 vy = y - y0;
            f32 vz = z - z0;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = vz;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = 0;
        }
        {
            f32 vx = x - x1;
            f32 vy = y - y1;
            f32 vz = z - z1;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = vz;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 1;
        }
        {
            f32 vx = x + x0;
            f32 vy = y + y0;
            f32 vz = z + z0;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = vz;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 2;
        }
        {
            f32 vx = x + x1;
            f32 vy = y + y1;
            f32 vz = z + z1;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = vz;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 3;
        }
    } else {
        u32 primitive_count = *(u32*) it;
        it += sizeof(u32);
        for (; primitive_count != 0; primitive_count--) {
            GXPrimitive primitive = it[0];
            u8 count = it[1];
            s32 i;

            it += 4;
            if (pp->kind & DispTexture) {
                setVtxDesc(4);
                GXBegin(primitive, GX_VTXFMT4, count);
            } else {
                setVtxDesc(1);
                GXBegin(primitive, GX_VTXFMT1, count);
            }
            for (i = count; i > 0; i--) {
                f32 s = *(f32*) &it[0];
                f32 sx = 2.0f * (s - 0.5f);
                f32 t;
                f32 tx;

                if (pp->kind & TexFlipS) {
                    s = 1.0f - s;
                }
                t = *(f32*) &it[4];
                it += 8;
                tx = 2.0f * (t - 0.5f);
                if (pp->kind & TexFlipT) {
                    t = 1.0f - t;
                }
                GXWGFifo.f32 = x + x0 * sx + x1 * tx;
                GXWGFifo.f32 = y + y0 * sx + y1 * tx;
                GXWGFifo.f32 = z + z0 * sx + z1 * tx;
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
    f32 abs_angle;
    psdisp_Cache* cache = &HSD_PSDisp_804D0FC0;
    f32 right_x;
    f32 right_y;
    f32 right_z;
    f32 up_x;
    f32 up_y;
    f32 up_z;
    f32 angle;
    f32 x;
    f32 y;
    f32 z;
    Mtx mtx;

    x = pp->pos.x;
    y = pp->pos.y;
    z = pp->pos.z;
    if (texform != NULL) {
        right_x = cache->inverse_view_mtx[0][0] * pp->size;
        right_y = cache->inverse_view_mtx[1][0] * pp->size;
        right_z = cache->inverse_view_mtx[2][0] * pp->size;
        up_x = -cache->inverse_view_mtx[0][1] * pp->size;
        up_y = -cache->inverse_view_mtx[1][1] * pp->size;
        up_z = -cache->inverse_view_mtx[2][1] * pp->size;
    } else {
        right_x = HSD_PSDisp_804D7914 * pp->size;
        up_x = HSD_PSDisp_804D7918 * pp->size;
        right_y = HSD_PSDisp_804D791C * pp->size;
        up_y = HSD_PSDisp_804D7920 * pp->size;
        right_z = HSD_PSDisp_804D7924 * pp->size;
        up_z = HSD_PSDisp_804D7928 * pp->size;
    }
    if ((pp->kind & Trail) || (pp->kind & DirVec)) {
        f32 x;
        f32 y;

        if (0.0f == cache->projection.type) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 w0;
            f32 w0inv;
            f32 w1;
            f32 w1inv;
            f32 cur_y;
            f32 prev_xy;

            if (pp->kind & Tornado) {
                calcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            } else {
                prev_x = pp->pos.x - pp->vel.x;
                prev_y = pp->pos.y - pp->vel.y;
                prev_z = pp->pos.z - pp->vel.z;
            }
            w0 = cache->view_mtx[2][3] + (cache->view_mtx[2][2] * pp->pos.z +
                                          (cache->view_mtx[2][0] * pp->pos.x +
                                           cache->view_mtx[2][1] * pp->pos.y));
            if (0.0f == w0) {
                return;
            }
            w0inv = -1.0f / w0;
            w1 = cache->view_mtx[2][3] + (cache->view_mtx[2][2] * prev_z +
                                          (cache->view_mtx[2][0] * prev_x +
                                           cache->view_mtx[2][1] * prev_y));
            if (0.0f == w1) {
                return;
            }
            w1inv = -1.0f / w1;
            cur_y = cache->projected_x.y * pp->pos.y;
            prev_xy =
                cache->projected_x.x * prev_x + cache->projected_x.y * prev_y;
            x = w0inv * (cache->projected_x.w +
                         (cache->projected_x.z * pp->pos.z +
                          (cache->projected_x.x * pp->pos.x + cur_y))) -
                w1inv * (cache->projected_x.w +
                         (cache->projected_x.z * prev_z + prev_xy));
            y = w0inv * (cache->projected_y.w +
                         (cache->projected_y.z * pp->pos.z +
                          (cache->projected_y.x * pp->pos.x +
                           cache->projected_y.y * pp->pos.y))) -
                w1inv *
                    (cache->projected_y.w + (cache->projected_y.z * prev_z +
                                             (cache->projected_y.x * prev_x +
                                              cache->projected_y.y * prev_y)));
        } else if (pp->kind & Tornado) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 dx;
            f32 dy;
            f32 dz;

            calcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            dx = pp->pos.x - prev_x;
            dy = pp->pos.y - prev_y;
            dz = pp->pos.z - prev_z;
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
        {
            f32 abs_y = y;
            *(s32*) &abs_y &= 0x7FFFFFFF;
            if (abs_y < 1.17549435e-38f) {
                angle = (x >= 0.0f) ? 1.5707964f : -1.5707964f;
            } else {
                angle = atan2f(x, y);
            }
        }
        if (pp->kind & DirVec) {
            angle += pp->rotate;
        }
    } else {
        angle = pp->rotate;
    }
    abs_angle = angle;
    *(s32*) &abs_angle &= 0x7FFFFFFF;
    if (abs_angle > 0.01) {
        Vec3 axis;

        f32 t1;
        f32 t2;
        f32 t3;
        f32 t4;
        f32 rx = right_x;
        f32 ry = right_y;
        f32 rz = right_z;
        f32 ux = up_x;
        f32 uz = up_z;

        axis.x = ry * uz - rz * up_y;
        axis.y = rz * ux - rx * uz;
        axis.z = rx * up_y - ry * ux;
        PSMTXRotAxisRad(mtx, &axis, angle);
        t1 = mtx[1][0] * rx + mtx[1][1] * ry;
        t2 = mtx[1][0] * ux + mtx[1][1] * up_y;
        t3 = mtx[2][0] * rx + mtx[2][1] * ry;
        t4 = mtx[2][0] * ux + mtx[2][1] * up_y;
        right_x = mtx[0][2] * rz + (mtx[0][0] * rx + mtx[0][1] * ry);
        right_y = mtx[1][2] * rz + t1;
        right_z = mtx[2][2] * rz + t3;
        up_x = mtx[0][2] * uz + (mtx[0][0] * ux + mtx[0][1] * up_y);
        up_y = mtx[1][2] * uz + t2;
        up_z = mtx[2][2] * uz + t4;
    }
    psDispSubMakePolygon(pp, texform, x, y, z, pp->vel.x, pp->vel.y, pp->vel.z,
                         right_x, right_y, right_z, up_x, up_y, up_z);
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

static inline void psDispSubAPPSRTPoint(HSD_Particle* pp)
{
    GXColor draw_color;
    Vec3 cur_pos;
    Vec3 prev_pos;
    f32 ax;
    s32 w;

    psSetCurrentMtx(3);
    if (pp->appsrt != NULL) {
        if (pp->appsrt->frameNum != HSD_PSDisp_804D6380) {
            f32 scale_x;
            f32 scale_y;

            if (pp->appsrt->status != 2) {
                HSD_psAppSRT* appsrt = pp->appsrt;
                Vec3* translate = &appsrt->translate;
                Vec3* rotate = (Vec3*) &appsrt->rot;
                Vec3* scale = &appsrt->scale;
                MtxPtr mmtx = appsrt->mmtx;

                HSD_MtxSRT(mmtx, scale, rotate, translate, NULL);
            }
            if (pp->appsrt->status == 1) {
                pp->appsrt->status = 2;
            }
            PSMTXConcat(HSD_PSDisp_804D0FC0.view_mtx, pp->appsrt->mmtx,
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
                Mtx temp_mtx;
                Vec3 scale;

                PSMTXIdentity(temp_mtx);
                temp_mtx[0][3] = pp->appsrt->translate.x;
                temp_mtx[1][3] = pp->appsrt->translate.y;
                temp_mtx[2][3] = pp->appsrt->translate.z;
                PSMTXConcat(HSD_PSDisp_804D0FC0.view_mtx, temp_mtx, temp_mtx);
                HSD_MtxGetScale(temp_mtx, &scale);
                PSMTXScale((MtxPtr) &pp->appsrt->ssx, scale.x, scale.y,
                           scale.z);
                pp->appsrt->x70 = temp_mtx[0][3];
                pp->appsrt->x80 = temp_mtx[1][3];
                pp->appsrt->x90 = temp_mtx[2][3];
            }
        }
        pp->appsrt->frameNum = HSD_PSDisp_804D6380;
    }
    {
        HSD_psAppSRT* appsrt = pp->appsrt;
        f32 pos_y = pp->pos.y;

        cur_pos.x = appsrt->ssy * pos_y;
        cur_pos.y = appsrt->x78 * pos_y;
        cur_pos.z = appsrt->x88 * pos_y;
        cur_pos.y = appsrt->x74 * pp->pos.x + cur_pos.y;
        cur_pos.x = appsrt->ssx * pp->pos.x + cur_pos.x;
        cur_pos.z = appsrt->x84 * pp->pos.x + cur_pos.z;
        cur_pos.x = appsrt->x6C * pp->pos.z + cur_pos.x;
        cur_pos.y = appsrt->x7C * pp->pos.z + cur_pos.y;
        cur_pos.z = appsrt->x8C * pp->pos.z + cur_pos.z;
        cur_pos.x = appsrt->x70 + cur_pos.x;
        cur_pos.y = appsrt->x80 + cur_pos.y;
        cur_pos.z = appsrt->x90 + cur_pos.z;
    }
    if (pp->kind & Tornado) {
        f32 x;
        f32 y;
        f32 z;

        calcTornadoLastPos(pp, &x, &y, &z);
        prev_pos.x =
            pp->appsrt->x70 + (pp->appsrt->x6C * z +
                               (pp->appsrt->ssx * x + pp->appsrt->ssy * y));
        prev_pos.y =
            pp->appsrt->x80 + (pp->appsrt->x7C * z +
                               (pp->appsrt->x74 * x + pp->appsrt->x78 * y));
        prev_pos.z =
            pp->appsrt->x90 + (pp->appsrt->x8C * z +
                               (pp->appsrt->x84 * x + pp->appsrt->x88 * y));
    } else {
        f32 dx = pp->pos.x - pp->vel.x;
        f32 dy = pp->pos.y - pp->vel.y;
        f32 dz = pp->pos.z - pp->vel.z;
        prev_pos.x =
            pp->appsrt->x70 + (pp->appsrt->x6C * dz +
                               (pp->appsrt->ssx * dx + pp->appsrt->ssy * dy));
        prev_pos.y =
            pp->appsrt->x80 + (pp->appsrt->x7C * dz +
                               (pp->appsrt->x74 * dx + pp->appsrt->x78 * dy));
        prev_pos.z =
            pp->appsrt->x90 + (pp->appsrt->x8C * dz +
                               (pp->appsrt->x84 * dx + pp->appsrt->x88 * dy));
    }

    ax = pp->size > 42.5 ? 255.0f : 6.0f * pp->size;
    w = (s32) ax;
    if (pp->kind & Trail) {
        if (HSD_PSDisp_804D7910 != (s32) (u8) w) {
            HSD_PSDisp_804D7910 = (u8) w;
            GXSetLineWidth((u8) w, GX_TO_ONE);
        }
        getClrTrail(pp, &draw_color);
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
        {
            u8 a = draw_color.a;
            u8 b = draw_color.b;
            u8 g = draw_color.g;
            u8 r = draw_color.r;
            GXWGFifo.u8 = r;
            GXWGFifo.u8 = g;
            GXWGFifo.u8 = b;
            GXWGFifo.u8 = (u8) ((f32) a * pp->trail);
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = (pp->kind >> 16) & 0xC;
        }
        GXWGFifo.f32 = cur_pos.x;
        GXWGFifo.f32 = cur_pos.y;
        GXWGFifo.f32 = cur_pos.z;
        {
            u8 a = draw_color.a;
            u8 b = draw_color.b;
            u8 g = draw_color.g;
            u8 r = draw_color.r;
            GXWGFifo.u8 = r;
            GXWGFifo.u8 = g;
            GXWGFifo.u8 = b;
            GXWGFifo.u8 = a;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = 1;
        }
    } else {
        if (HSD_PSDisp_804D790C != (s32) (u8) w) {
            HSD_PSDisp_804D790C = (u8) w;
            GXSetPointSize((u8) w, GX_TO_ONE);
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
            GXWGFifo.u8 = 1;
        }
    }
}

static inline void psDispSubAppSRT(HSD_Particle* pp, u8* texform)
{
    GXColor draw_color;
    Vec3 cur_pos;
    Vec3 prev_pos;
    f32 ax;
    f32 ay;
    f32 bx;
    f32 by;
    f32 y_extent;
    f32 angle;
    f32 abs_angle;
    u8* it = texform;

    if (pp->appsrt->frameNum != HSD_PSDisp_804D6380) {
        f32 scale_x;
        f32 scale_y;

        if (pp->appsrt->status != 2) {
            HSD_psAppSRT* appsrt = pp->appsrt;
            Vec3* translate = &appsrt->translate;
            Vec3* rotate = (Vec3*) &appsrt->rot;
            Vec3* scale = &appsrt->scale;
            MtxPtr mmtx = appsrt->mmtx;

            HSD_MtxSRT(mmtx, scale, rotate, translate, NULL);
        }
        if (pp->appsrt->status == 1) {
            pp->appsrt->status = 2;
        }
        PSMTXConcat(HSD_PSDisp_804D0FC0.view_mtx, pp->appsrt->mmtx,
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
            Mtx temp_mtx;
            Vec3 scale;

            PSMTXIdentity(temp_mtx);
            temp_mtx[0][3] = pp->appsrt->translate.x;
            temp_mtx[1][3] = pp->appsrt->translate.y;
            temp_mtx[2][3] = pp->appsrt->translate.z;
            PSMTXConcat(HSD_PSDisp_804D0FC0.view_mtx, temp_mtx, temp_mtx);
            HSD_MtxGetScale(temp_mtx, &scale);
            PSMTXScale((MtxPtr) &pp->appsrt->ssx, scale.x, scale.y, scale.z);
            pp->appsrt->x70 = temp_mtx[0][3];
            pp->appsrt->x80 = temp_mtx[1][3];
            pp->appsrt->x90 = temp_mtx[2][3];
        }
        pp->appsrt->frameNum = HSD_PSDisp_804D6380;
    }
    {
        Mtx draw_mtx;

        PSMTXCopy((MtxPtr) &pp->appsrt->ssx, draw_mtx);
        cur_pos.z =
            draw_mtx[2][3] +
            (draw_mtx[2][2] * pp->pos.z +
             (draw_mtx[2][0] * pp->pos.x + draw_mtx[2][1] * pp->pos.y));
        cur_pos.y =
            draw_mtx[1][3] +
            (draw_mtx[1][2] * pp->pos.z +
             (draw_mtx[1][0] * pp->pos.x + draw_mtx[1][1] * pp->pos.y));
        cur_pos.x =
            draw_mtx[0][3] +
            (draw_mtx[0][2] * pp->pos.z +
             (draw_mtx[0][0] * pp->pos.x + draw_mtx[0][1] * pp->pos.y));
        if (pp->kind & Tornado) {
            f32 x;
            f32 y;
            f32 z;

            calcTornadoLastPos(pp, &x, &y, &z);
            prev_pos.x =
                draw_mtx[0][3] + (draw_mtx[0][2] * z +
                                  (draw_mtx[0][0] * x + draw_mtx[0][1] * y));
            prev_pos.y =
                draw_mtx[1][3] + (draw_mtx[1][2] * z +
                                  (draw_mtx[1][0] * x + draw_mtx[1][1] * y));
            prev_pos.z =
                draw_mtx[2][3] + (draw_mtx[2][2] * z +
                                  (draw_mtx[2][0] * x + draw_mtx[2][1] * y));
        } else {
            f32 dx = pp->pos.x - pp->vel.x;
            f32 dy = pp->pos.y - pp->vel.y;
            f32 dz = pp->pos.z - pp->vel.z;
            prev_pos.x =
                draw_mtx[0][3] + (draw_mtx[0][2] * dz +
                                  (draw_mtx[0][0] * dx + draw_mtx[0][1] * dy));
            prev_pos.y =
                draw_mtx[1][3] + (draw_mtx[1][2] * dz +
                                  (draw_mtx[1][0] * dx + draw_mtx[1][1] * dy));
            prev_pos.z =
                draw_mtx[2][3] + (draw_mtx[2][2] * dz +
                                  (draw_mtx[2][0] * dx + draw_mtx[2][1] * dy));
        }
        psScaleAppSRTAxes(pp, draw_mtx);
    }
    ax = pp->appsrt->x94 * pp->size;
    y_extent = pp->appsrt->x98 * pp->size;
    if (it == NULL) {
        ay = y_extent;
        by = -ay;
        bx = ax;
    } else {
        ay = 0.0f;
        by = -y_extent;
        bx = 0.0f;
    }
    if ((pp->kind & Trail) || (pp->kind & DirVec)) {
        f32 vf1;
        f32 vf2;
        if (0.0f == HSD_PSDisp_804D0FC0.projection.type) {
            f32 prev_x;
            f32 prev_y;
            f32 prev_z;
            f32 w0;
            f32 w1;
            f32 w0inv;
            f32 w1inv;
            f32 f16;
            f32 f20;
            f32 f11;
            f32 f8;
            f32 f12;
            f32 f13;
            f32 s808;
            f32 s804;

            if (pp->kind & Tornado) {
                calcTornadoLastPos(pp, &prev_x, &prev_y, &prev_z);
            } else {
                prev_x = pp->pos.x - pp->vel.x;
                prev_y = pp->pos.y - pp->vel.y;
                prev_z = pp->pos.z - pp->vel.z;
            }
            w0 = pp->appsrt->x90 +
                 (pp->appsrt->x8C * pp->pos.z +
                  (pp->appsrt->x84 * pp->pos.x + pp->appsrt->x88 * pp->pos.y));
            f16 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->x6C +
                  HSD_PSDisp_804D0FC0.projection.x_offset * pp->appsrt->x8C;
            s808 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->ssx +
                   HSD_PSDisp_804D0FC0.projection.x_offset * pp->appsrt->x84;
            s804 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->ssy +
                   HSD_PSDisp_804D0FC0.projection.x_offset * pp->appsrt->x88;
            f20 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->x70 +
                  HSD_PSDisp_804D0FC0.projection.x_offset * pp->appsrt->x90;
            f12 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x74 +
                  HSD_PSDisp_804D0FC0.projection.y_offset * pp->appsrt->x84;
            f8 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x78 +
                 HSD_PSDisp_804D0FC0.projection.y_offset * pp->appsrt->x88;
            f11 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x7C +
                  HSD_PSDisp_804D0FC0.projection.y_offset * pp->appsrt->x8C;
            f13 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x80 +
                  HSD_PSDisp_804D0FC0.projection.y_offset * pp->appsrt->x90;
            if (0.0f == w0) {
                return;
            }
            w0inv = -1.0f / w0;
            w1 = pp->appsrt->x90 +
                 (pp->appsrt->x8C * prev_z +
                  (pp->appsrt->x84 * prev_x + pp->appsrt->x88 * prev_y));
            if (0.0f == w1) {
                return;
            }
            w1inv = -1.0f / w1;
            vf1 = w0inv * (f20 + (f16 * pp->pos.z +
                                  (s808 * pp->pos.x + s804 * pp->pos.y))) -
                  w1inv *
                      (f20 + (f16 * prev_z + (s808 * prev_x + s804 * prev_y)));
            vf2 =
                w0inv * (f13 + (f11 * pp->pos.z +
                                (f12 * pp->pos.x + f8 * pp->pos.y))) -
                w1inv * (f13 + (f11 * prev_z + (f12 * prev_x + f8 * prev_y)));
        } else {
            f32 f17;
            f32 f18;
            f32 f20;
            f32 s800;
            f32 s7FC;
            f32 s7F8;

            s800 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->ssx +
                   HSD_PSDisp_804D0FC0.projection.x_offset;
            s7FC = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->ssy +
                   HSD_PSDisp_804D0FC0.projection.x_offset;
            s7F8 = HSD_PSDisp_804D0FC0.projection.x_scale * pp->appsrt->x6C +
                   HSD_PSDisp_804D0FC0.projection.x_offset;
            f17 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x74 +
                  HSD_PSDisp_804D0FC0.projection.y_offset;
            f18 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x78 +
                  HSD_PSDisp_804D0FC0.projection.y_offset;
            f20 = HSD_PSDisp_804D0FC0.projection.y_scale * pp->appsrt->x7C +
                  HSD_PSDisp_804D0FC0.projection.y_offset;
            if (pp->kind & Tornado) {
                f32 tx;
                f32 ty;
                f32 tz;
                calcTornadoLastPos(pp, &tx, &ty, &tz);
                {
                    f32 dy = pp->pos.y - ty;
                    f32 dx = pp->pos.x - tx;
                    f32 dz = pp->pos.z - tz;
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
        {
            f32 abs_v = vf2;
            *(s32*) &abs_v &= 0x7FFFFFFF;
            if (abs_v < 1.17549435e-38f) {
                angle = (-vf1 >= 0.0f) ? 1.5707964f : -1.5707964f;
            } else {
                angle = atan2f(-vf1, vf2);
            }
        }
        if (pp->kind & DirVec) {
            angle += pp->rotate;
        }
    } else {
        angle = pp->rotate;
    }
    abs_angle = angle;
    *(s32*) &abs_angle &= 0x7FFFFFFF;
    if (abs_angle > 0.01) {
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
        if (it == NULL) {
            if (pp->kind & DispTexture) {
                setVtxDesc(2);
                GXBegin(GX_QUADS, GX_VTXFMT2, 4U);
            } else {
                setVtxDesc(3);
                GXBegin(GX_QUADS, GX_VTXFMT3, 4U);
            }
            {
                f32 vx = -ax + prev_pos.x;
                f32 vy = -ay + prev_pos.y;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = prev_pos.z;
            }
            {
                u8 a = draw_color.a;
                u8 b = draw_color.b;
                u8 g = draw_color.g;
                u8 r = draw_color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = (u8) ((f32) a * pp->trail);
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = (pp->kind >> 16) & 0xC;
            }
            {
                f32 vx = -bx + cur_pos.x;
                f32 vy = -by + cur_pos.y;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = cur_pos.z;
            }
            {
                u8 a = draw_color.a;
                u8 b = draw_color.b;
                u8 g = draw_color.g;
                u8 r = draw_color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 1;
            }
            {
                f32 vx = ax + cur_pos.x;
                f32 vy = ay + cur_pos.y;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = cur_pos.z;
            }
            {
                u8 a = draw_color.a;
                u8 b = draw_color.b;
                u8 g = draw_color.g;
                u8 r = draw_color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = a;
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 2;
            }
            {
                f32 vx = bx + prev_pos.x;
                f32 vy = by + prev_pos.y;
                GXWGFifo.f32 = vx;
                GXWGFifo.f32 = vy;
                GXWGFifo.f32 = prev_pos.z;
            }
            {
                u8 a = draw_color.a;
                u8 b = draw_color.b;
                u8 g = draw_color.g;
                u8 r = draw_color.r;
                GXWGFifo.u8 = r;
                GXWGFifo.u8 = g;
                GXWGFifo.u8 = b;
                GXWGFifo.u8 = (u8) ((f32) a * pp->trail);
            }
            if (pp->kind & DispTexture) {
                GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 3;
            }
        } else {
            f32 trail_alpha = 255.0f * (1.0f - pp->trail);
            f32 axis_len = sqrtf(bx * bx + by * by);

            if (axis_len != 0.0f) {
                f32 dx = cur_pos.x - prev_pos.x;
                f32 dy = cur_pos.y - prev_pos.y;
                f32 dz = cur_pos.z - prev_pos.z;
                f32 xl = dx * dx;
                f32 yl = dy * dy;
                f32 zl = dz * dz;
                f32 segment_len = sqrtf(zl + (xl + yl));
                f32 ratio = segment_len / axis_len;
                u32 primitive_count = *(u32*) it;

                bx *= ratio;
                by *= ratio;
                it += sizeof(u32);
                for (; primitive_count != 0; primitive_count--) {
                    GXPrimitive primitive = it[0];
                    u8 count = it[1];
                    s32 i;
                    u8 b;
                    u8 g;
                    u8 r;

                    it += 4;
                    if (pp->kind & DispTexture) {
                        setVtxDesc(5);
                        GXBegin(primitive, GX_VTXFMT5, count);
                    } else {
                        setVtxDesc(3);
                        GXBegin(primitive, GX_VTXFMT3, count);
                    }
                    b = draw_color.b;
                    g = draw_color.g;
                    r = draw_color.r;
                    for (i = count; i > 0; i--) {
                        f32 s = *(f32*) &it[0];
                        f32 sx = 2.0f * (s - 0.5f);
                        f32 t;
                        f32 tx;
                        s32 converted_alpha;
                        s32 alpha;

                        if (pp->kind & TexFlipS) {
                            s = 1.0f - s;
                        }
                        t = *(f32*) &it[4];
                        it += 8;
                        converted_alpha = (s32) (255.0f - t * trail_alpha);
                        alpha = (s32) (255.0f - t * trail_alpha);
                        if (converted_alpha < 0) {
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
                        GXWGFifo.u8 = r;
                        GXWGFifo.u8 = g;
                        GXWGFifo.u8 = b;
                        GXWGFifo.u8 = alpha;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.f32 = s;
                            GXWGFifo.f32 = t;
                        }
                    }
                }
            }
        }
    } else if (it == NULL) {
        if (pp->kind & DispTexture) {
            setVtxDesc(0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
        } else {
            setVtxDesc(1);
            GXBegin(GX_QUADS, GX_VTXFMT1, 4U);
        }
        {
            f32 vx = -ax + cur_pos.x;
            f32 vy = -ay + cur_pos.y;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = cur_pos.z;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = (pp->kind >> 16) & 0xC;
        }
        {
            f32 vx = -bx + cur_pos.x;
            f32 vy = -by + cur_pos.y;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = cur_pos.z;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 1;
        }
        {
            f32 vx = ax + cur_pos.x;
            f32 vy = ay + cur_pos.y;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = cur_pos.z;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 2;
        }
        {
            f32 vx = bx + cur_pos.x;
            f32 vy = by + cur_pos.y;
            GXWGFifo.f32 = vx;
            GXWGFifo.f32 = vy;
            GXWGFifo.f32 = cur_pos.z;
        }
        if (pp->kind & DispTexture) {
            GXWGFifo.u8 = ((pp->kind >> 16) & 0xC) + 3;
        }
    } else {
        u32 primitive_count = *(u32*) it;

        it += sizeof(u32);
        for (; primitive_count != 0; primitive_count--) {
            GXPrimitive prim = it[0];
            u8 count = it[1];
            s32 i;
            it += 4;
            if (pp->kind & DispTexture) {
                setVtxDesc(4);
                GXBegin(prim, GX_VTXFMT4, count);
            } else {
                setVtxDesc(1);
                GXBegin(prim, GX_VTXFMT1, count);
            }
            for (i = count; i > 0; i--) {
                f32 s = *(f32*) &it[0];
                f32 sx = 2.0f * (s - 0.5f);
                f32 t;
                f32 tx;

                if (pp->kind & TexFlipS) {
                    s = 1.0f - s;
                }
                t = *(f32*) &it[4];
                it += 8;
                tx = 2.0f * (t - 0.5f);
                if (pp->kind & TexFlipT) {
                    t = 1.0f - t;
                }
                GXWGFifo.f32 = cur_pos.x + ax * sx + bx * tx;
                GXWGFifo.f32 = cur_pos.y + ay * sx + by * tx;
                GXWGFifo.f32 = cur_pos.z;
                if (pp->kind & DispTexture) {
                    GXWGFifo.f32 = s;
                    GXWGFifo.f32 = t;
                }
            }
        }
    }
}

static inline void psUpdateBillboardAxes(const Mtx inv_view)
{
    f32 right;
    f32 up;

    right = inv_view[0][0];
    up = inv_view[0][1];
    HSD_PSDisp_804D7914 = right + up;
    HSD_PSDisp_804D7918 = right - up;
    right = inv_view[1][0];
    up = inv_view[1][1];
    HSD_PSDisp_804D791C = right + up;
    HSD_PSDisp_804D7920 = right - up;
    right = inv_view[2][0];
    up = inv_view[2][1];
    HSD_PSDisp_804D7924 = right + up;
    HSD_PSDisp_804D7928 = right - up;
}

static inline void psUpdateProjectionCache(psdisp_Cache* cache,
                                           f32 perspective)
{
    GXGetProjectionv((f32*) &cache->projection);
    if (perspective == cache->projection.type) {
        f32 w0 = cache->view_mtx[2][0];
        f32 x_scale = cache->projection.x_scale;
        f32 x_offset = cache->projection.x_offset;
        f32 w1;
        f32 w2;
        f32 w3;
        f32 y_scale;
        f32 y_offset;
        f32 product;
        f32 y0;
        f32 y1;
        f32 y2;
        f32 y3;

        product = x_offset * w0;
        cache->projected_x.x = x_scale * cache->view_mtx[0][0] + product;
        w1 = cache->view_mtx[2][1];
        product = x_offset * w1;
        cache->projected_x.y = x_scale * cache->view_mtx[0][1] + product;
        w2 = cache->view_mtx[2][2];
        product = x_offset * w2;
        cache->projected_x.z = x_scale * cache->view_mtx[0][2] + product;
        w3 = cache->view_mtx[2][3];
        product = x_offset * w3;
        cache->projected_x.w = x_scale * cache->view_mtx[0][3] + product;
        y_scale = cache->projection.y_scale;
        y_offset = cache->projection.y_offset;
        y0 = y_offset * w0;
        y1 = y_offset * w1;
        y2 = y_offset * w2;
        y3 = y_offset * w3;
        cache->projected_y.x = y_scale * cache->view_mtx[1][0] + y0;
        cache->projected_y.y = y_scale * cache->view_mtx[1][1] + y1;
        cache->projected_y.z = y_scale * cache->view_mtx[1][2] + y2;
        cache->projected_y.w = y_scale * cache->view_mtx[1][3] + y3;
    } else {
        f32 x_offset = cache->projection.x_offset;
        f32 x_scale = cache->projection.x_scale;
        f32 y_offset;
        f32 y_scale;

        cache->projected_x.x = x_scale * cache->view_mtx[0][0] + x_offset;
        cache->projected_x.y = x_scale * cache->view_mtx[0][1] + x_offset;
        cache->projected_x.z = x_scale * cache->view_mtx[0][2] + x_offset;
        cache->projected_x.w = x_scale * cache->view_mtx[0][3] + x_offset;
        y_offset = cache->projection.y_offset;
        y_scale = cache->projection.y_scale;
        cache->projected_y.x = y_scale * cache->view_mtx[1][0] + y_offset;
        cache->projected_y.y = y_scale * cache->view_mtx[1][1] + y_offset;
        cache->projected_y.z = y_scale * cache->view_mtx[1][2] + y_offset;
        cache->projected_y.w = y_scale * cache->view_mtx[1][3] + y_offset;
    }
    psUpdateBillboardAxes(cache->inverse_view_mtx);
}

#pragma push
#pragma inline_depth(3)
void psDispParticles(s32 arg0, u32 arg1)
{
    s32 var_r16;
    s32 var_r15;
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
    psdisp_Tlut tlut_obj;
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
    HSD_Particle* pp;
    psdisp_Cache* cache;
    /// @todo Recover this stack space from the original inline hierarchy.
    PAD_STACK(0x7C);

    var_r16 = 0;
    var_r15 = 0;
    cache = &HSD_PSDisp_804D0FC0;
    sp7A5 = 0;
    sp7A4 = 0xFF;
    sp7A0 = 1;
    if (arg1 == 0) {
        if (HSD_PSDisp_804D6380 < 0xFFU) {
            HSD_PSDisp_804D6380 += 1;
            return;
        }
        HSD_PSDisp_804D6380 = 1;
        return;
    }
    sp7F4 = psTexGroupArray;
    sp7F0 = psNumCmdList;
    sp7B4 = 0;
    do {
        if (arg0 & (1 << sp7B4)) {
            particleSort(sp7B4, HSD_PSDisp_804D6380, &sp760, &sp75C);
            if (arg1 == 1) {
                pp = sp760;
            } else {
                pp = sp75C;
            }
            while (pp != NULL) {
                HSD_PSTexGroup* tex_group = NULL;
                HSD_PSFormGroup* form_group = NULL;
                HSD_PSFormGroup** form_bank;
                u8* form = NULL;
                void* image;
                void* tlut;
                u32 blend_mode;
                u8 alpha0;
                u8 alpha1;
                Mtx temp_mtx;
                GXTexWrapMode wrap_s;
                GXTexWrapMode wrap_t;
                f32 scale_s;
                f32 scale_t;
                GXTexFmt fmt;
                u8** tex_table;
                u32 width;
                u32 height;

                if ((arg1 == 1) && !(pp->kind & TexEdge)) {
                    break;
                }
                if (!(pp->size < 1.1920928955078125e-07f)) {
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
                                              HSD_PSDisp_804D0FC0.view_mtx);
                        PSMTXInverse(HSD_PSDisp_804D0FC0.view_mtx,
                                     HSD_PSDisp_804D0FC0.inverse_view_mtx);
                        psUpdateProjectionCache(cache, 0.0f);
                        GXLoadPosMtxImm(HSD_PSDisp_804D0FC0.view_mtx, 0);
                        billboard_mtx = HSD_PSDisp_803B9628;
                        GXLoadPosMtxImm(billboard_mtx.mtx, 3);
                        HSD_PSDisp_804D7948[0] = 3;
                        psSetCurrentMtx(0);
                        GXEnableTexOffsets(GX_TEXCOORD0, GX_TRUE, GX_TRUE);
                        GXSetCullMode(GX_CULL_BACK);
                        GXSetArray(GX_VA_TEX0, HSD_PSDisp_8040C340, 2U);
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
                        GXSetAlphaCompare((var_r16 >> 3) & 7, sp7A5,
                                          (var_r16 >> 6) & 3, var_r16 & 7,
                                          sp7A4);
                    }

                    psSetupTev((u32*) pp);
                    setupChanCtrl(pp);
                    setupChanReg(pp);
                    setupTevReg(pp);
                    if ((pp->kind & TexEdge) != sp7AC) {
                        sp7AC = pp->kind & TexEdge;
                        if ((s32) sp7AC != 0) {
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

                    {
                        HSD_PSFormGroup*** form_banks = sp7F0;
                        form_banks += pp->bank;
                        form_bank = *form_banks;
                    }
                    if (form_bank != NULL &&
                        (form_group = form_bank[pp->texGroup]) != NULL &&
                        form_group->formTable != NULL)
                    {
                        form = form_group->formTable[pp->poseNum];
                    } else {
                        form = NULL;
                    }

                    if (pp->kind & DispTexture) {
                        if (pp->kind & MirrorS) {
                            scale_s = 2.0f;
                            wrap_s = GX_MIRROR;
                        } else {
                            scale_s = 1.0f;
                            wrap_s = GX_CLAMP;
                        }
                        if (pp->kind & MirrorT) {
                            scale_t = 2.0f;
                            wrap_t = GX_MIRROR;
                        } else {
                            scale_t = 1.0f;
                            wrap_t = GX_CLAMP;
                        }
                        if ((pp->kind & (MirrorS | MirrorT)) != sp7A8) {
                            sp7A8 = pp->kind & (MirrorS | MirrorT);
                            sp7B0 = NULL;
                            PSMTXScale(temp_mtx, scale_s, scale_t, 1.0f);
                            if (pp->kind & MirrorT) {
                                sp700 = 1.0f;
                                temp_mtx[1][3] = sp700;
                            }
                            GXLoadTexMtxImm(temp_mtx, GX_TEXMTX0, GX_MTX2x4);
                            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4,
                                              GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                              GX_PTIDENTITY);
                        }
                        {
                            HSD_PSTexGroup*** tex_banks = sp7F4;
                            tex_banks += pp->bank;
                            tex_group = (*tex_banks)[pp->texGroup];
                        }
                        if (tex_group != NULL) {
                            fmt = tex_group->fmt;
                            tex_table = tex_group->texTable;
                            width = tex_group->width;
                            height = tex_group->height;
                        } else {
                            fmt = 0;
                            height = 0;
                            width = 0;
                            tex_table = NULL;
                        }
                        if (tex_table != NULL) {
                            image = tex_table[pp->poseNum];
                        } else {
                            image = NULL;
                        }
                        if ((fmt == GX_TF_C4) || (fmt == GX_TF_C8)) {
                            if (tex_table != NULL) {
                                void** palettes =
                                    (void**) &tex_table[tex_group->num];
                                if (palettes != NULL) {
                                    if (pp->palNum != 0xFF) {
                                        tlut = palettes[pp->palNum];
                                    } else if (!(pp->kind & ComTLUT)) {
                                        tlut = palettes[pp->poseNum];
                                    } else {
                                        tlut = palettes[0];
                                    }
                                    if (tlut != sp79C) {
                                        tlut_obj.fmt = (GXTlutFmt) (u8)
                                                           tex_group->tlutfmt;
                                        tlut_obj.tlut_name = GX_TLUT0;
                                        tlut_obj.n_entries =
                                            (fmt == GX_TF_C4) ? 0x10 : 0x100;
                                        GXInitTlutObj(&sp71C, tlut,
                                                      tlut_obj.fmt,
                                                      tlut_obj.n_entries);
                                        GXLoadTlut(&sp71C, tlut_obj.tlut_name);
                                        sp7B0 = NULL;
                                    }
                                }
                            }
                        }
                        if ((sp7B0 != image) && (image != NULL)) {
                            sp7B0 = image;
                            switch (fmt) {
                            case GX_TF_C4:
                            case GX_TF_C8:
                                GXInitTexObjCI(&sp764, image, width, height,
                                               fmt, wrap_s, wrap_t, GX_FALSE,
                                               GX_TLUT0);
                                break;
                            case GX_TF_I4:
                            case GX_TF_I8:
                            case GX_TF_IA4:
                            case GX_TF_IA8:
                            case GX_TF_RGB565:
                            case GX_TF_RGB5A3:
                            case GX_TF_RGBA8:
                            case GX_TF_CMPR:
                                GXInitTexObj(&sp764, image, width, height, fmt,
                                             wrap_s, wrap_t, GX_FALSE);
                                break;
                            default:
                                HSD_ASSERT(0x8AA, 0);
                                break;
                            }
                            var_r15 = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR,
                                (pp->kind & TexInterpNear) ? GX_NEAR
                                                           : GX_LINEAR,
                                0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                            GXLoadTexObj(&sp764, GX_TEXMAP0);
                        }
                        if ((u32) var_r15 != (pp->kind & TexInterpNear)) {
                            var_r15 = pp->kind & TexInterpNear;
                            GXInitTexObjLOD(
                                &sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR,
                                (s32) (pp->kind & TexInterpNear) != 0
                                    ? GX_NEAR
                                    : GX_LINEAR,
                                0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE,
                                GX_ANISO_1);
                            GXLoadTexObj(&sp764, GX_TEXMAP0);
                        }
                    }

                    if (pp->kind & DispPoint) {
                        if (pp->appsrt != NULL) {
                            psDispSubAPPSRTPoint(pp);
                        } else {
                            if (pp->kind & Trail) {
                                pp = psDispSubPointTrail(pp);
                            } else {
                                pp = psDispSubPoint(pp);
                            }
                        }
                    } else if (pp->appsrt != NULL) {
                        psDispSubAppSRT(pp, form);
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
