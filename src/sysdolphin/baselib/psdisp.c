#include "psdisp.h"

#include "baselib/forward.h"

#include "baselib/psstructs.h"

#include <math.h>
#include <string.h>
#include <dolphin/gx.h>

typedef struct {
    u8 filename[9];
    u8 message[39];
    UNK_T pointers[3];
    u32 bitfields[8];
} psdisp_UnknownType001;

typedef struct {
    UNK_T pointers[4];
    u8 message[36];
    u8 filename[9];
} psdisp_UnknownType002;

typedef struct {
    HSD_Particle* head;
    HSD_Particle* tail;
} psdisp_ParticleSortBucket;

typedef struct {
    u8 x0_pad[0xAC];
    HSD_Particle* xAC[17];
} psdisp_ParticleSortCache;

STATIC_ASSERT(sizeof(psdisp_ParticleSortBucket) == 8);
STATIC_ASSERT(sizeof(psdisp_ParticleSortCache) == 0xF0);

/* 39F89C */ static void calcTornadoLastPos(HSD_Particle*, f32*, f32*, f32*);
/* 39FA28 */ static void getColorPrimEnv(HSD_Particle*, GXColor*, GXColor*);
/* 39FB74 */ static void getColorMatAmb(HSD_Particle*, GXColor*, GXColor*);
/* 3B9628 */ extern f32 HSD_PSDisp_803B9628[12];
/* 40C300 */ extern psdisp_UnknownType001 HSD_PSDisp_8040C300;
/* 40C360 */ extern psdisp_UnknownType002 HSD_PSDisp_8040C360;
/* 4D6380 */ extern u8 HSD_PSDisp_804D6380[2];
/* 4D6384 */ extern u8 HSD_PSDisp_804D6384[2];
/* 4D0908 */ extern HSD_Particle* hsd_804D0908[146];
/* 4D0FC0 */ extern psdisp_ParticleSortCache HSD_PSDisp_804D0FC0;
/* 4D7908 */ extern s32 HSD_PSDisp_804D7908;
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
/* 4D7934 */ extern UNK_T HSD_PSDisp_804D7934;
/* 4D7938 */ extern UNK_T HSD_PSDisp_804D7938;
/* 4D793C */ extern UNK_T HSD_PSDisp_804D793C;
/* 4D7940 */ extern UNK_T HSD_PSDisp_804D7940;
/* 4D7944 */ extern UNK_T HSD_PSDisp_804D7944;
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

HSD_Particle* particleSort(s32 arg0, u8 arg1, HSD_Particle** arg2,
                           HSD_Particle** arg3)
{
    psdisp_ParticleSortBucket buckets[16];
    HSD_Particle* var_r28;
    HSD_Particle* var_r3;
    HSD_Particle* var_r4;
    HSD_Particle* var_r5;
    HSD_Particle* var_r7;
    HSD_Particle** temp_r29;
    HSD_Particle** var_r6_2;
    HSD_Particle** var_r7_2;
    psdisp_ParticleSortBucket* temp_r3_4;
    psdisp_ParticleSortBucket* temp_r3_10;
    psdisp_ParticleSortCache* cache;
    u32 temp_r3;
    u32 temp_r3_2;
    s32 temp_r4;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r6;
    u8* temp_r9;

    temp_r9 = (u8*) &HSD_PSDisp_8040C360 + arg0;
    temp_r29 = &hsd_804D0908[arg0];
    cache = &HSD_PSDisp_804D0FC0;
    var_r28 = *temp_r29;
    if (*temp_r9 == arg1) {
        *arg2 = var_r28;
        *arg3 = cache->xAC[arg0];
        return var_r28;
    }

    *temp_r9 = arg1;
    if (var_r28 == NULL) {
        cache->xAC[arg0] = NULL;
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

    temp_r3_4 = buckets;
    if (temp_r3_4->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }
    if ((++temp_r3_4)->head != NULL) {
        if (var_r4 == NULL) {
            var_r4 = temp_r3_4->head;
        } else {
            *var_r6_2 = temp_r3_4->head;
        }
        var_r6_2 = &temp_r3_4->tail->next;
    }

    temp_r3_10 = &buckets[8];
    if (temp_r3_10->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
    }
    if ((++temp_r3_10)->head != NULL) {
        if (var_r5 == NULL) {
            var_r5 = temp_r3_10->head;
        } else {
            *var_r7_2 = temp_r3_10->head;
        }
        var_r7_2 = &temp_r3_10->tail->next;
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
    cache->xAC[arg0] = var_r5;
    *arg2 = var_r3;
    *arg3 = var_r5;
    return var_r3;
}
