#include "psdisp.h"

#include "baselib/forward.h"

#include "baselib/cobj.h"
#include "baselib/fog.h"
#include "baselib/lobj.h"
#include "baselib/mtx.h"
#include "baselib/psdisptev.h"
#include "baselib/psstructs.h"
#include "baselib/state.h"
#include "baselib/util.h"

#include <libc/math.h>
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

typedef Vec3 Point3d;

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
/* 4D0B50 */ extern void* psTexGroupArray_804D0B50;
/* 4D0C54 */ extern void* psNumCmdList_804D0C54;
/* 4D0FC0 */ extern psdisp_ParticleSortCache HSD_PSDisp_804D0FC0;
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

void psDispParticles(s32 arg0, u32 arg1)
{
    s32 sp8BC;
    s32 sp8B8;
    f64 sp8B0;
    f64 sp8A8;
    f64 sp8A0;
    f64 sp898;
    f64 sp890;
    f64 sp888;
    f64 sp880;
    f64 sp878;
    f64 sp870;
    f64 sp868;
    f64 sp860;
    f64 sp858;
    f64 sp850;
    f64 sp848;
    f64 sp840;
    f64 sp838;
    f64 sp830;
    f64 sp828;
    f64 sp820;
    f64 sp818;
    f32 sp814;
    f32 sp810;
    f32 sp80C;
    f32 sp808;
    f32 sp804;
    f32 sp800;
    f32 sp7FC;
    f32 sp7F8;
    void* sp7F4;
    void* sp7F0;
    s32 sp7EC;
    s32 sp7E8;
    s32* sp7E4;
    s32* sp7E0;
    s32* sp7DC;
    s32* sp7D8;
    s32* sp7D4;
    s32* sp7D0;
    s32* sp7CC;
    s32* sp7C8;
    s32* sp7C4;
    s32* sp7C0;
    s32* sp7BC;
    s32* sp7B8;
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
    u32 sp78C;
    GXTlutFmt sp788;
    GXTexObj sp764;
    HSD_Particle* sp760;
    HSD_Particle* sp75C;
    s32 sp758;
    s32 sp754;
    s32 sp750;
    s32 sp74C;
    s32 sp748;
    s32 sp744;
    s32 sp740;
    s32 sp73C;
    s32 sp738;
    s32 sp734;
    s32 sp730;
    s32 sp72C;
    GXTlutObj sp71C;
    f32 sp700;
    s32 sp6E0;
    s32 sp6DC;
    s32 sp6D8;
    s32 sp6D4;
    s32 sp6D0;
    s32 sp6CC;
    s32 sp6C8;
    u8 sp6C4;
    u8 sp6C2;
    u8 sp6C1;
    u8 sp6C0;
    u8 sp6BE;
    u8 sp6BD;
    u8 sp6BC;
    s32 sp6B8;
    s32 sp6B4;
    s32 sp6B0;
    s32 sp6AC;
    s32 sp6A8;
    u8 sp6A4;
    u8 sp6A3;
    u8 sp6A0;
    u8 sp69C;
    u8 sp698;
    u8 sp697;
    u8 sp696;
    u8 sp695;
    u8 sp694;
    f32 sp690;
    f32 sp68C;
    f32 sp688;
    Point3d sp67C;
    f32 sp678;
    f32 sp668;
    f32 sp644;
    f32 sp640;
    f32 sp63C;
    f32 sp638;
    f32 sp634;
    f32 sp630;
    s32 sp5B4;
    s8 sp5B3;
    s8 sp5B2;
    s8 sp5B1;
    u8 sp5B0;
    f32 sp438;
    f32 sp434;
    f32 sp430;
    f32 sp374;
    f32 sp370;
    f32 sp36C;
    u8 sp36B;
    u8 sp36A;
    u8 sp369;
    u8 sp368;
    f32 sp358;
    f32 sp354;
    f32 sp350;
    f32 sp34C;
    f32 sp348;
    f32 sp344;
    f32 sp310;
    f32 sp30C;
    f32 sp308;
    Point3d sp2FC;
    f32 sp2EC;
    f32 sp2E8;
    f32 sp2E4;
    f32 sp2E0;
    f32 sp2DC;
    f32 sp2D8;
    f32 sp2D4;
    f32 sp2D0;
    f32 sp2BC;
    f32 sp2B8;
    f32 sp2B4;
    u8 sp2B3;
    u8 sp2B2;
    u8 sp2B1;
    u8 sp2B0;
    f32 sp294;
    f32 sp290;
    f32 sp28C;
    f32 sp258;
    f32 sp254;
    f32 sp250;
    f32 sp24C;
    f32 sp248;
    f32 sp244;
    f32 sp240;
    f32 sp23C;
    u8 sp238;
    u8 sp208;
    u8 sp204;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    f32 sp1CC;
    u8 sp1C8;
    f32 sp184;
    f32 sp180;
    f32 sp110;
    f32 sp10C;
    u8 sp108;
    f32 spD4;
    f32 spD0;
    u32 prev_kind;
    s32 var_r16;
    s32 var_r15;
    HSD_Particle* pp;
    f32* cache;

    var_r16 = 0;
    var_r15 = 0;
    sp798 = arg1;
    sp794 = arg0;
    sp7A5 = 0;
    sp7A4 = 0xFF;
    sp7A0 = 1;
    prev_kind = 0;
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
    sp7B8 = &sp6B8;
    sp7BC = &sp6B4;
    sp7C0 = &sp6B0;
    sp7C4 = &sp6AC;
    sp7C8 = &sp6A8;
    sp7CC = &sp6CC;
    sp7D0 = &sp6C8;
    sp7D4 = &sp6D0;
    sp7D8 = &sp6D4;
    sp7DC = &sp6D8;
    sp7E0 = &sp6DC;
    sp7E4 = &sp6E0;
    sp8B0 = 0.0;
    sp8A8 = 4503599627370496.0;
    sp8A0 = 0.01;
    sp898 = 0.00001;
    sp878 = 1.0;
    sp828 = 6.0;
    sp820 = 42.5;
    sp818 = 0.000001;
    sp7A8 = (u32) -1;
    sp7AC = (u32) -1;
    sp79C = NULL;
    sp7B0 = NULL;
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
                GXColor prim_color;
                GXColor env_color;
                GXColor mat_color;
                GXColor amb_color;
                GXColor draw_color;
                GXColor tail_color;
                HSD_LObj* lobj;
                HSD_psAppSRT* appsrt;
                void* image;
                void* tlut;
                u32 blend_mode;
                u8 alpha0;
                u8 alpha1;
                Vec3 last_pos;
                Vec3 cur_pos;
                Vec3 prev_pos;
                Vec3 view_cur;
                Vec3 view_prev;
                Vec3 right;
                Vec3 up;
                Vec3 scale;
                Mtx temp_mtx;
                Mtx draw_mtx;
                f32 ax;
                f32 ay;
                f32 bx;
                f32 by;
                f32 angle;
                u8 tex_base;
                u32 chan_state;
                u32 wrap_bits;
                GXTexWrapMode wrap_s;
                GXTexWrapMode wrap_t;

                if ((sp798 == 1) && !(pp->kind & TexEdge)) {
                    prev_kind = pp->kind;
                    pp = pp->next;
                    continue;
                }
                if (pp->size < (f32) sp818) {
                    prev_kind = pp->kind;
                    pp = pp->next;
                    continue;
                }
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
                    HSD_PSDisp_804D7934.r = 0xFF;
                    HSD_PSDisp_804D7934.g = 0xFF;
                    HSD_PSDisp_804D7934.b = 0xFF;
                    HSD_PSDisp_804D7934.a = 0xFF;
                    HSD_PSDisp_804D7938.r = 0xFF;
                    HSD_PSDisp_804D7938.g = 0xFF;
                    HSD_PSDisp_804D7938.b = 0xFF;
                    HSD_PSDisp_804D7938.a = 0xFF;
                    sp6E0 = *(s32*) &HSD_PSDisp_804D7934;
                    GXSetChanMatColor(GX_COLOR0A0, *(GXColor*) sp7E4);
                    sp6DC = *(s32*) &HSD_PSDisp_804D7938;
                    GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*) sp7E0);
                    psSetupTevInvalidState();
                    psSetupTevCommon();
                    HSD_PSDisp_804D793C.r = 0xFF;
                    HSD_PSDisp_804D793C.g = 0xFF;
                    HSD_PSDisp_804D793C.b = 0xFF;
                    HSD_PSDisp_804D793C.a = 0xFF;
                    HSD_PSDisp_804D7940.r = 0;
                    HSD_PSDisp_804D7940.g = 0;
                    HSD_PSDisp_804D7940.b = 0;
                    HSD_PSDisp_804D7940.a = 0;
                    HSD_PSDisp_804D7944.r = 0xFF;
                    HSD_PSDisp_804D7944.g = 0xFF;
                    HSD_PSDisp_804D7944.b = 0xFF;
                    HSD_PSDisp_804D7944.a = 0xFF;
                    sp6D8 = *(s32*) &HSD_PSDisp_804D793C;
                    GXSetTevColor(GX_TEVREG0, *(GXColor*) sp7DC);
                    sp6D4 = *(s32*) &HSD_PSDisp_804D7940;
                    GXSetTevColor(GX_TEVREG1, *(GXColor*) sp7D8);
                    sp6D0 = *(s32*) &HSD_PSDisp_804D7944;
                    GXSetTevColor(GX_TEVREG2, *(GXColor*) sp7D4);
                    HSD_PSDisp_804D792C = -1;
                    GXSetZCompLoc(GX_FALSE);
                    cache = (f32*) &HSD_PSDisp_804D0FC0;
                    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), (MtxPtr) cache);
                    PSMTXInverse((MtxPtr) cache, (MtxPtr) (cache + 0xC));
                    GXGetProjectionv(&cache[0x18]);
                    if (cache[0x18] == (f32) sp8B0) {
                        cache[0x1F] = cache[0x19] * cache[0] + cache[0x1A] * cache[8];
                        cache[0x20] = cache[0x19] * cache[1] + cache[0x1A] * cache[9];
                        cache[0x21] = cache[0x19] * cache[2] + cache[0x1A] * cache[10];
                        cache[0x22] = cache[0x19] * cache[3] + cache[0x1A] * cache[11];
                        cache[0x23] = cache[0x1B] * cache[4] + cache[0x1C] * cache[8];
                        cache[0x24] = cache[0x1B] * cache[5] + cache[0x1C] * cache[9];
                        cache[0x25] = cache[0x1B] * cache[6] + cache[0x1C] * cache[10];
                        cache[0x26] = cache[0x1B] * cache[7] + cache[0x1C] * cache[11];
                    } else {
                        cache[0x1F] = cache[0x19] * cache[0] + cache[0x1A];
                        cache[0x20] = cache[0x19] * cache[1] + cache[0x1A];
                        cache[0x21] = cache[0x19] * cache[2] + cache[0x1A];
                        cache[0x22] = cache[0x19] * cache[3] + cache[0x1A];
                        cache[0x23] = cache[0x1B] * cache[4] + cache[0x1C];
                        cache[0x24] = cache[0x1B] * cache[5] + cache[0x1C];
                        cache[0x25] = cache[0x1B] * cache[6] + cache[0x1C];
                        cache[0x26] = cache[0x1B] * cache[7] + cache[0x1C];
                    }
                    HSD_PSDisp_804D7914 = cache[0xC] + cache[0xD];
                    HSD_PSDisp_804D7918 = cache[0xC] - cache[0xD];
                    HSD_PSDisp_804D791C = cache[0x10] + cache[0x11];
                    HSD_PSDisp_804D7920 = cache[0x10] - cache[0x11];
                    HSD_PSDisp_804D7924 = cache[0x14] + cache[0x15];
                    HSD_PSDisp_804D7928 = cache[0x14] - cache[0x15];
                    GXLoadPosMtxImm((MtxPtr) cache, 0);
                    sp72C = HSD_PSDisp_803B9628[0];
                    sp730 = HSD_PSDisp_803B9628[1];
                    sp734 = HSD_PSDisp_803B9628[2];
                    sp738 = HSD_PSDisp_803B9628[3];
                    sp73C = HSD_PSDisp_803B9628[4];
                    sp740 = HSD_PSDisp_803B9628[5];
                    sp744 = HSD_PSDisp_803B9628[6];
                    sp748 = HSD_PSDisp_803B9628[7];
                    sp74C = HSD_PSDisp_803B9628[8];
                    sp750 = HSD_PSDisp_803B9628[9];
                    sp754 = HSD_PSDisp_803B9628[10];
                    sp758 = HSD_PSDisp_803B9628[11];
                    GXLoadPosMtxImm((MtxPtr) &sp72C, 3);
                    HSD_PSDisp_804D7948 = 3;
                    if (HSD_PSDisp_804D7948 != 0) {
                        HSD_PSDisp_804D7948 = 0;
                        GXSetCurrentMtx(0);
                    }
                    GXEnableTexOffsets(GX_TEXCOORD0, GX_TRUE, GX_TRUE);
                    GXSetCullMode(GX_CULL_BACK);
                    GXSetArray(GX_VA_TEX0, (void*) ((char*) &HSD_PSDisp_8040C300 + 0x40), 2U);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT2, GX_VA_TEX0, GX_TEX_ST, GX_RGB565, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT4, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0U);
                    GXSetVtxAttrFmt(GX_VTXFMT5, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0U);
                    sp7A0 = 0;
                }

                blend_mode = (pp->kind >> 0x16U) & 3;
                if (HSD_PSDisp_804D792C != (s32) blend_mode) {
                    HSD_PSDisp_804D792C = blend_mode;
                    switch (blend_mode) {
                    case 0:
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                        break;
                    case 1:
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
                        break;
                    default:
                        OSReport((char*) &HSD_PSDisp_8040C300 + 0x70);
                        break;
                    }
                }

                if (pp->aCmpCount != 0) {
                    s32 scale = (65536 * pp->aCmpRemain) / pp->aCmpCount;
                    alpha0 = ((pp->aCmpParam1Target << 16) + scale * (pp->aCmpParam1 - pp->aCmpParam1Target)) >> 16;
                    alpha1 = ((pp->aCmpParam2Target << 16) + scale * (pp->aCmpParam2 - pp->aCmpParam2Target)) >> 16;
                } else {
                    alpha0 = pp->aCmpParam1;
                    alpha1 = pp->aCmpParam2;
                }
                if ((var_r16 != pp->aCmpMode) || (sp7A5 != alpha0) || (sp7A4 != alpha1)) {
                    sp7A5 = alpha0;
                    var_r16 = pp->aCmpMode;
                    sp7A4 = alpha1;
                    GXSetAlphaCompare((pp->aCmpMode >> 3) & 7, sp7A5, (pp->aCmpMode >> 6) & 3, pp->aCmpMode & 7, sp7A4);
                }

                psSetupTev((u32*) pp);
                chan_state = pp->kind & 0x80100000;
                if ((u32) HSD_PSDisp_804D7930 != chan_state) {
                    GXAttnFn attn_fn = HSD_LObjGetLightMaskAttnFunc() != 0 ? GX_AF_SPOT : GX_AF_NONE;
                    HSD_PSDisp_804D7930 = chan_state;
                    GXSetNumChans(1U);
                    switch (chan_state) {
                    case 0:
                    case DispLighting:
                        GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE, attn_fn);
                        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0U, GX_DF_NONE, GX_AF_NONE);
                        break;
                    case Trail:
                        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0U, GX_DF_NONE, GX_AF_NONE);
                        break;
                    case DispLighting | Trail:
                        GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, HSD_LObjGetLightMaskDiffuse(), GX_DF_NONE, attn_fn);
                        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0U, GX_DF_NONE, GX_AF_NONE);
                        break;
                    default:
                        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0U, GX_DF_NONE, GX_AF_NONE);
                        break;
                    }
                }

                if (pp->kind & DispLighting) {
                    getColorMatAmb(pp, &mat_color, &amb_color);
                    if (pp->kind & PrimEnv) {
                        prim_color.r = 0xFF;
                        prim_color.g = 0xFF;
                        prim_color.b = 0xFF;
                        prim_color.a = 0xFF;
                    } else {
                        getColorPrimEnv(pp, &prim_color, &env_color);
                        amb_color.r = (u8) (((u32) amb_color.r * prim_color.r) >> 8);
                        amb_color.g = (u8) (((u32) amb_color.g * prim_color.g) >> 8);
                        amb_color.b = (u8) (((u32) amb_color.b * prim_color.b) >> 8);
                    }
                    if ((prim_color.r != HSD_PSDisp_804D7934.r) || (prim_color.g != HSD_PSDisp_804D7934.g) || (prim_color.b != HSD_PSDisp_804D7934.b)) {
                        HSD_PSDisp_804D7934.r = prim_color.r;
                        HSD_PSDisp_804D7934.g = prim_color.g;
                        HSD_PSDisp_804D7934.b = prim_color.b;
                        sp6C8 = *(s32*) &HSD_PSDisp_804D7934;
                        GXSetChanMatColor(GX_COLOR0, *(GXColor*) sp7D0);
                    }
                    lobj = HSD_LObjGetActiveByID(GX_MAX_LIGHT);
                    if (lobj != NULL) {
                        HSD_MulColor(&amb_color, &lobj->color, &amb_color);
                    } else {
                        amb_color.r = 0;
                        amb_color.g = 0;
                        amb_color.b = 0;
                    }
                    if ((amb_color.r != HSD_PSDisp_804D7938.r) || (amb_color.g != HSD_PSDisp_804D7938.g) || (amb_color.b != HSD_PSDisp_804D7938.b)) {
                        HSD_PSDisp_804D7938.r = amb_color.r;
                        HSD_PSDisp_804D7938.g = amb_color.g;
                        HSD_PSDisp_804D7938.b = amb_color.b;
                        sp6CC = *(s32*) &HSD_PSDisp_804D7938;
                        GXSetChanAmbColor(GX_COLOR0, *(GXColor*) sp7CC);
                    }
                }

                getColorPrimEnv(pp, &prim_color, &env_color);
                if ((pp->kind & PrimEnv) || (!(pp->kind & DispLighting) && !(pp->kind & Trail))) {
                    if ((HSD_PSDisp_804D793C.r != prim_color.r) || (HSD_PSDisp_804D793C.g != prim_color.g) || (HSD_PSDisp_804D793C.b != prim_color.b) || (HSD_PSDisp_804D793C.a != prim_color.a)) {
                        HSD_PSDisp_804D793C = prim_color;
                        sp6A8 = *(s32*) &HSD_PSDisp_804D793C;
                        GXSetTevColor(GX_TEVREG0, *(GXColor*) sp7C8);
                    }
                    if (pp->kind & PrimEnv) {
                        if ((HSD_PSDisp_804D7940.r != env_color.r) || (HSD_PSDisp_804D7940.g != env_color.g) || (HSD_PSDisp_804D7940.b != env_color.b) || (HSD_PSDisp_804D7940.a != env_color.a)) {
                            HSD_PSDisp_804D7940 = env_color;
                            sp6AC = *(s32*) &HSD_PSDisp_804D7940;
                            GXSetTevColor(GX_TEVREG1, *(GXColor*) sp7C4);
                        }
                    } else if ((HSD_PSDisp_804D7940.r != 0) || (HSD_PSDisp_804D7940.g != 0) || (HSD_PSDisp_804D7940.b != 0) || (HSD_PSDisp_804D7940.a != 0)) {
                        HSD_PSDisp_804D7940.r = 0;
                        HSD_PSDisp_804D7940.g = 0;
                        HSD_PSDisp_804D7940.b = 0;
                        HSD_PSDisp_804D7940.a = 0;
                        sp6B0 = *(s32*) &HSD_PSDisp_804D7940;
                        GXSetTevColor(GX_TEVREG1, *(GXColor*) sp7C0);
                    }
                }
                if (pp->kind & DispLighting) {
                    getColorMatAmb(pp, &mat_color, &amb_color);
                    if (!(pp->kind & PrimEnv)) {
                        mat_color.a = (u8) (((u32) mat_color.a * prim_color.a) >> 8);
                    }
                    if ((HSD_PSDisp_804D7944.r != mat_color.r) || (HSD_PSDisp_804D7944.g != mat_color.g) || (HSD_PSDisp_804D7944.b != mat_color.b) || (HSD_PSDisp_804D7944.a != mat_color.a)) {
                        HSD_PSDisp_804D7944 = mat_color;
                        sp6B8 = *(s32*) &HSD_PSDisp_804D7944;
                        GXSetTevColor(GX_TEVREG2, *(GXColor*) sp7B8);
                    }
                }

                if (sp7AC != (pp->kind & TexEdge)) {
                    sp7AC = pp->kind & TexEdge;
                    GXSetZMode(GX_TRUE, GX_LEQUAL, (sp7AC != 0) ? GX_TRUE : GX_FALSE);
                }
                if (((pp->kind ^ prev_kind) & DispFog) != 0) {
                    HSD_FogSet((pp->kind & DispFog) ? HSD_PSDisp_804D7908 : NULL);
                }

                if (sp7F0 != NULL) {
                    HSD_PSFormGroup*** form_array = (HSD_PSFormGroup***) sp7F0;
                    HSD_PSFormGroup** bank_entry = form_array[pp->bank];
                    if (bank_entry != NULL) {
                        form_group = bank_entry[pp->texGroup];
                        if ((form_group != NULL) && (pp->poseNum < form_group->num)) {
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
                        PSMTXScale(temp_mtx, (pp->kind & MirrorS) ? 2.0f : 1.0f, (pp->kind & MirrorT) ? 2.0f : 1.0f, 1.0f);
                        if (pp->kind & MirrorT) {
                            sp700 = 1.0f;
                            temp_mtx[1][3] = sp700;
                        }
                        GXLoadTexMtxImm(temp_mtx, GX_TEXMTX0, GX_MTX2x4);
                        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                    }
                    if (sp7F4 != NULL) {
                        HSD_PSTexGroup*** tex_array = (HSD_PSTexGroup***) sp7F4;
                        HSD_PSTexGroup** bank_tex = tex_array[pp->bank];
                        if (bank_tex != NULL) {
                            tex_group = bank_tex[pp->texGroup];
                        }
                    }
                    if (tex_group != NULL) {
                        image = tex_group->texTable[pp->poseNum];
                        if ((tex_group->fmt == GX_TF_C4) || (tex_group->fmt == GX_TF_C8)) {
                            void** palettes = (void**) &tex_group->texTable[tex_group->num];
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
                                    GXInitTlutObj(&sp71C, tlut, sp788, sp790);
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
                            GXInitTexObjCI(&sp764, image, tex_group->width, tex_group->height, tex_group->fmt, wrap_s, wrap_t, GX_FALSE, GX_TLUT0);
                            break;
                        case GX_TF_I4:
                        case GX_TF_I8:
                        case GX_TF_IA4:
                        case GX_TF_IA8:
                        case GX_TF_RGB565:
                        case GX_TF_RGB5A3:
                        case GX_TF_RGBA8:
                        case GX_TF_CMPR:
                            GXInitTexObj(&sp764, image, tex_group->width, tex_group->height, tex_group->fmt, wrap_s, wrap_t, GX_FALSE);
                            break;
                        default:
                            __assert((char*) &HSD_PSDisp_8040C300 + 0x94, 0x8AAU, "0");
                            break;
                        }
                        var_r15 = pp->kind & TexInterpNear;
                        GXInitTexObjLOD(&sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR, (var_r15 != 0) ? GX_NEAR : GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                        GXLoadTexObj(&sp764, GX_TEXMAP0);
                    }
                    if ((pp->kind & TexInterpNear) != (u32) var_r15) {
                        var_r15 = pp->kind & TexInterpNear;
                        GXInitTexObjLOD(&sp764, (var_r15 != 0) ? GX_NEAR : GX_LINEAR, (var_r15 != 0) ? GX_NEAR : GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                        GXLoadTexObj(&sp764, GX_TEXMAP0);
                    }
                }

                if (pp->kind & Tornado) {
                    calcTornadoLastPos(pp, &last_pos.x, &last_pos.y, &last_pos.z);
                } else {
                    last_pos.x = pp->pos.x - pp->vel.x;
                    last_pos.y = pp->pos.y - pp->vel.y;
                    last_pos.z = pp->pos.z - pp->vel.z;
                }

                tex_base = (pp->kind >> 16) & 0xC;
                if (pp->kind & DispPoint) {
                    draw_color = prim_color;
                    if (pp->kind & PrimEnv) {
                        draw_color.r = 0xFF;
                        draw_color.g = 0xFF;
                        draw_color.b = 0xFF;
                        draw_color.a = 0xFF;
                    }
                    tail_color = draw_color;
                    cur_pos = pp->pos;
                    prev_pos = last_pos;
                    appsrt = pp->appsrt;
                    if (appsrt != NULL) {
                        cache = (f32*) &HSD_PSDisp_804D0FC0;
                        if (appsrt->frameNum != HSD_PSDisp_804D6380[0]) {
                            if (appsrt->status != 2) {
                                HSD_MtxSRT(appsrt->mmtx, &appsrt->scale, (Point3d*) &appsrt->rot, &appsrt->translate, NULL);
                            }
                            if (appsrt->status == 1) {
                                appsrt->status = 2;
                            }
                            PSMTXConcat((MtxPtr) cache, appsrt->mmtx, (MtxPtr) &appsrt->ssx);
                            ax = appsrt->ssx * appsrt->ssx + appsrt->x74 * appsrt->x74 + appsrt->x84 * appsrt->x84;
                            if (ax > (f32) sp8B0) {
                                double e = __frsqrte((double) ax);
                                e = 0.5 * e * (3.0 - (double) ax * e * e);
                                e = 0.5 * e * (3.0 - (double) ax * e * e);
                                e = 0.5 * e * (3.0 - (double) ax * e * e);
                                ax = (f32) ((double) ax * e);
                            }
                            appsrt->x94 = ax;
                            ay = appsrt->ssy * appsrt->ssy + appsrt->x78 * appsrt->x78 + appsrt->x88 * appsrt->x88;
                            if (ay > (f32) sp8B0) {
                                double e = __frsqrte((double) ay);
                                e = 0.5 * e * (3.0 - (double) ay * e * e);
                                e = 0.5 * e * (3.0 - (double) ay * e * e);
                                e = 0.5 * e * (3.0 - (double) ay * e * e);
                                ay = (f32) ((double) ay * e);
                            }
                            appsrt->x98 = ay;
                            if (appsrt->xA2 != 0) {
                                PSMTXIdentity(temp_mtx);
                                temp_mtx[0][3] = appsrt->translate.x;
                                temp_mtx[1][3] = appsrt->translate.y;
                                temp_mtx[2][3] = appsrt->translate.z;
                                PSMTXConcat((MtxPtr) cache, temp_mtx, temp_mtx);
                                HSD_MtxGetScale(temp_mtx, &scale);
                                PSMTXScale((MtxPtr) &appsrt->ssx, scale.x, scale.y, scale.z);
                                appsrt->x70 = temp_mtx[0][3];
                                appsrt->x80 = temp_mtx[1][3];
                                appsrt->x90 = temp_mtx[2][3];
                            }
                            appsrt->frameNum = HSD_PSDisp_804D6380[0];
                        }
                        if (HSD_PSDisp_804D7948 != 3) {
                            HSD_PSDisp_804D7948 = 3;
                            GXSetCurrentMtx(3U);
                        }
                        draw_mtx[0][0] = appsrt->ssx;
                        draw_mtx[0][1] = appsrt->ssy;
                        draw_mtx[0][2] = appsrt->x6C;
                        draw_mtx[0][3] = appsrt->x70;
                        draw_mtx[1][0] = appsrt->x74;
                        draw_mtx[1][1] = appsrt->x78;
                        draw_mtx[1][2] = appsrt->x7C;
                        draw_mtx[1][3] = appsrt->x80;
                        draw_mtx[2][0] = appsrt->x84;
                        draw_mtx[2][1] = appsrt->x88;
                        draw_mtx[2][2] = appsrt->x8C;
                        draw_mtx[2][3] = appsrt->x90;
                        cur_pos.x = draw_mtx[0][0] * pp->pos.x + draw_mtx[0][1] * pp->pos.y + draw_mtx[0][2] * pp->pos.z + draw_mtx[0][3];
                        cur_pos.y = draw_mtx[1][0] * pp->pos.x + draw_mtx[1][1] * pp->pos.y + draw_mtx[1][2] * pp->pos.z + draw_mtx[1][3];
                        cur_pos.z = draw_mtx[2][0] * pp->pos.x + draw_mtx[2][1] * pp->pos.y + draw_mtx[2][2] * pp->pos.z + draw_mtx[2][3];
                        prev_pos.x = draw_mtx[0][0] * last_pos.x + draw_mtx[0][1] * last_pos.y + draw_mtx[0][2] * last_pos.z + draw_mtx[0][3];
                        prev_pos.y = draw_mtx[1][0] * last_pos.x + draw_mtx[1][1] * last_pos.y + draw_mtx[1][2] * last_pos.z + draw_mtx[1][3];
                        prev_pos.z = draw_mtx[2][0] * last_pos.x + draw_mtx[2][1] * last_pos.y + draw_mtx[2][2] * last_pos.z + draw_mtx[2][3];
                    } else if (HSD_PSDisp_804D7948 != 0) {
                        HSD_PSDisp_804D7948 = 0;
                        GXSetCurrentMtx(0U);
                    }
                    ax = (pp->size > (f32) sp820) ? 255.0f : (f32) sp828 * pp->size;
                    if (pp->kind & Trail) {
                        tail_color.a = (u8) ((f32) tail_color.a * pp->trail);
                        if (HSD_PSDisp_804D7910 != (s32) (u8) (s32) ax) {
                            HSD_PSDisp_804D7910 = (u8) (s32) ax;
                            GXSetLineWidth((u8) HSD_PSDisp_804D7910, GX_TO_ONE);
                        }
                        if (pp->kind & DispTexture) {
                            setVtxDesc(2);
                            GXBegin(GX_LINES, GX_VTXFMT2, 2U);
                        } else {
                            setVtxDesc(3);
                            GXBegin(GX_LINES, GX_VTXFMT3, 2U);
                        }
                        GXWGFifo.f32 = prev_pos.x;
                        GXWGFifo.f32 = prev_pos.y;
                        GXWGFifo.f32 = prev_pos.z;
                        GXWGFifo.u8 = tail_color.r;
                        GXWGFifo.u8 = tail_color.g;
                        GXWGFifo.u8 = tail_color.b;
                        GXWGFifo.u8 = tail_color.a;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 0;
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
                            GXBegin(GX_POINTS, GX_VTXFMT0, 1U);
                        } else {
                            setVtxDesc(1);
                            GXBegin(GX_POINTS, GX_VTXFMT1, 1U);
                        }
                        GXWGFifo.f32 = cur_pos.x;
                        GXWGFifo.f32 = cur_pos.y;
                        GXWGFifo.f32 = cur_pos.z;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 1;
                        }
                    }
                } else if (pp->appsrt != NULL) {
                    appsrt = pp->appsrt;
                    cache = (f32*) &HSD_PSDisp_804D0FC0;
                    if (appsrt->frameNum != HSD_PSDisp_804D6380[0]) {
                        if (appsrt->status != 2) {
                            HSD_MtxSRT(appsrt->mmtx, &appsrt->scale, (Point3d*) &appsrt->rot, &appsrt->translate, NULL);
                        }
                        if (appsrt->status == 1) {
                            appsrt->status = 2;
                        }
                        PSMTXConcat((MtxPtr) cache, appsrt->mmtx, (MtxPtr) &appsrt->ssx);
                        ax = appsrt->ssx * appsrt->ssx + appsrt->x74 * appsrt->x74 + appsrt->x84 * appsrt->x84;
                        if (ax > (f32) sp8B0) {
                            double e = __frsqrte((double) ax);
                            e = 0.5 * e * (3.0 - (double) ax * e * e);
                            e = 0.5 * e * (3.0 - (double) ax * e * e);
                            e = 0.5 * e * (3.0 - (double) ax * e * e);
                            ax = (f32) ((double) ax * e);
                        }
                        appsrt->x94 = ax;
                        ay = appsrt->ssy * appsrt->ssy + appsrt->x78 * appsrt->x78 + appsrt->x88 * appsrt->x88;
                        if (ay > (f32) sp8B0) {
                            double e = __frsqrte((double) ay);
                            e = 0.5 * e * (3.0 - (double) ay * e * e);
                            e = 0.5 * e * (3.0 - (double) ay * e * e);
                            e = 0.5 * e * (3.0 - (double) ay * e * e);
                            ay = (f32) ((double) ay * e);
                        }
                        appsrt->x98 = ay;
                        if (appsrt->xA2 != 0) {
                            PSMTXIdentity(temp_mtx);
                            temp_mtx[0][3] = appsrt->translate.x;
                            temp_mtx[1][3] = appsrt->translate.y;
                            temp_mtx[2][3] = appsrt->translate.z;
                            PSMTXConcat((MtxPtr) cache, temp_mtx, temp_mtx);
                            HSD_MtxGetScale(temp_mtx, &scale);
                            PSMTXScale((MtxPtr) &appsrt->ssx, scale.x, scale.y, scale.z);
                            appsrt->x70 = temp_mtx[0][3];
                            appsrt->x80 = temp_mtx[1][3];
                            appsrt->x90 = temp_mtx[2][3];
                        }
                        appsrt->frameNum = HSD_PSDisp_804D6380[0];
                    }
                    if (HSD_PSDisp_804D7948 != 3) {
                        HSD_PSDisp_804D7948 = 3;
                        GXSetCurrentMtx(3U);
                    }
                    draw_mtx[0][0] = appsrt->ssx;
                    draw_mtx[0][1] = appsrt->ssy;
                    draw_mtx[0][2] = appsrt->x6C;
                    draw_mtx[0][3] = appsrt->x70;
                    draw_mtx[1][0] = appsrt->x74;
                    draw_mtx[1][1] = appsrt->x78;
                    draw_mtx[1][2] = appsrt->x7C;
                    draw_mtx[1][3] = appsrt->x80;
                    draw_mtx[2][0] = appsrt->x84;
                    draw_mtx[2][1] = appsrt->x88;
                    draw_mtx[2][2] = appsrt->x8C;
                    draw_mtx[2][3] = appsrt->x90;
                    cur_pos.x = draw_mtx[0][0] * pp->pos.x + draw_mtx[0][1] * pp->pos.y + draw_mtx[0][2] * pp->pos.z + draw_mtx[0][3];
                    cur_pos.y = draw_mtx[1][0] * pp->pos.x + draw_mtx[1][1] * pp->pos.y + draw_mtx[1][2] * pp->pos.z + draw_mtx[1][3];
                    cur_pos.z = draw_mtx[2][0] * pp->pos.x + draw_mtx[2][1] * pp->pos.y + draw_mtx[2][2] * pp->pos.z + draw_mtx[2][3];
                    prev_pos.x = draw_mtx[0][0] * last_pos.x + draw_mtx[0][1] * last_pos.y + draw_mtx[0][2] * last_pos.z + draw_mtx[0][3];
                    prev_pos.y = draw_mtx[1][0] * last_pos.x + draw_mtx[1][1] * last_pos.y + draw_mtx[1][2] * last_pos.z + draw_mtx[1][3];
                    prev_pos.z = draw_mtx[2][0] * last_pos.x + draw_mtx[2][1] * last_pos.y + draw_mtx[2][2] * last_pos.z + draw_mtx[2][3];
                    ax = appsrt->x94 * pp->size;
                    ay = 0.0f;
                    bx = 0.0f;
                    by = -appsrt->x98 * pp->size;
                    if (form == NULL) {
                        bx = ax;
                        ay = -by;
                    }
                    if (pp->kind & (Trail | DirVec)) {
                        f32 dx = cur_pos.x - prev_pos.x;
                        f32 dy = cur_pos.y - prev_pos.y;
                        if (fabsf(dx) < (f32) sp898) {
                            angle = (dy >= 0.0f) ? 1.5707964f : -1.5707964f;
                        } else {
                            angle = atan2f(dy, dx);
                        }
                        if (pp->kind & DirVec) {
                            angle += pp->rotate;
                        }
                    } else {
                        angle = pp->rotate;
                    }
                    if (fabsf(angle) > (f32) sp8A0) {
                        f32 c = cosf(angle);
                        f32 s = sinf(angle);
                        f32 old_ax = ax;
                        f32 old_ay = ay;
                        f32 old_bx = bx;
                        f32 old_by = by;
                        ax = c * old_ax - s * old_ay;
                        ay = s * old_ax + c * old_ay;
                        bx = c * old_bx - s * old_by;
                        by = s * old_bx + c * old_by;
                    }
                    if (pp->kind & Trail) {
                        draw_color = prim_color;
                        if (pp->kind & PrimEnv) {
                            draw_color.r = 0xFF;
                            draw_color.g = 0xFF;
                            draw_color.b = 0xFF;
                            draw_color.a = 0xFF;
                        }
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
                    } else if (form != NULL) {
                        u8* it = form;
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
                                GXWGFifo.f32 = cur_pos.x + ax * (2.0f * (s - 0.5f)) + bx * (2.0f * (t - 0.5f));
                                GXWGFifo.f32 = cur_pos.y + ay * (2.0f * (s - 0.5f)) + by * (2.0f * (t - 0.5f));
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
                } else {
                    cache = (f32*) &HSD_PSDisp_804D0FC0;
                    right.x = cache[0xC] * pp->size;
                    right.y = cache[0x10] * pp->size;
                    right.z = cache[0x14] * pp->size;
                    up.x = -cache[0xD] * pp->size;
                    up.y = -cache[0x11] * pp->size;
                    up.z = -cache[0x15] * pp->size;
                    cur_pos = pp->pos;
                    prev_pos = last_pos;
                    if (HSD_PSDisp_804D7948 != 0) {
                        HSD_PSDisp_804D7948 = 0;
                        GXSetCurrentMtx(0U);
                    }
                    if (pp->kind & (Trail | DirVec)) {
                        view_cur.x = cache[0] * cur_pos.x + cache[1] * cur_pos.y + cache[2] * cur_pos.z + cache[3];
                        view_cur.y = cache[4] * cur_pos.x + cache[5] * cur_pos.y + cache[6] * cur_pos.z + cache[7];
                        view_cur.z = cache[8] * cur_pos.x + cache[9] * cur_pos.y + cache[10] * cur_pos.z + cache[11];
                        view_prev.x = cache[0] * prev_pos.x + cache[1] * prev_pos.y + cache[2] * prev_pos.z + cache[3];
                        view_prev.y = cache[4] * prev_pos.x + cache[5] * prev_pos.y + cache[6] * prev_pos.z + cache[7];
                        view_prev.z = cache[8] * prev_pos.x + cache[9] * prev_pos.y + cache[10] * prev_pos.z + cache[11];
                        if (fabsf(view_cur.x - view_prev.x) < (f32) sp898) {
                            angle = ((view_cur.y - view_prev.y) >= 0.0f) ? 1.5707964f : -1.5707964f;
                        } else {
                            angle = atan2f(view_cur.y - view_prev.y, view_cur.x - view_prev.x);
                        }
                        if (pp->kind & DirVec) {
                            angle += pp->rotate;
                        }
                    } else {
                        angle = pp->rotate;
                    }
                    if (fabsf(angle) > (f32) sp8A0) {
                        f32 c = cosf(angle);
                        f32 s = sinf(angle);
                        Vec3 old_right = right;
                        Vec3 old_up = up;
                        right.x = c * old_right.x - s * old_up.x;
                        right.y = c * old_right.y - s * old_up.y;
                        right.z = c * old_right.z - s * old_up.z;
                        up.x = s * old_right.x + c * old_up.x;
                        up.y = s * old_right.y + c * old_up.y;
                        up.z = s * old_right.z + c * old_up.z;
                    }
                    if (pp->kind & Trail) {
                        draw_color = prim_color;
                        if (pp->kind & PrimEnv) {
                            draw_color.r = 0xFF;
                            draw_color.g = 0xFF;
                            draw_color.b = 0xFF;
                            draw_color.a = 0xFF;
                        }
                        tail_color = draw_color;
                        tail_color.a = (u8) ((f32) tail_color.a * pp->trail);
                        if (pp->kind & DispTexture) {
                            setVtxDesc(2);
                            GXBegin(GX_QUADS, GX_VTXFMT2, 4U);
                        } else {
                            setVtxDesc(3);
                            GXBegin(GX_QUADS, GX_VTXFMT3, 4U);
                        }
                        GXWGFifo.f32 = prev_pos.x - right.x - up.x;
                        GXWGFifo.f32 = prev_pos.y - right.y - up.y;
                        GXWGFifo.f32 = prev_pos.z - right.z - up.z;
                        GXWGFifo.u8 = tail_color.r;
                        GXWGFifo.u8 = tail_color.g;
                        GXWGFifo.u8 = tail_color.b;
                        GXWGFifo.u8 = tail_color.a;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 0;
                        }
                        GXWGFifo.f32 = cur_pos.x - right.x + up.x;
                        GXWGFifo.f32 = cur_pos.y - right.y + up.y;
                        GXWGFifo.f32 = cur_pos.z - right.z + up.z;
                        GXWGFifo.u8 = draw_color.r;
                        GXWGFifo.u8 = draw_color.g;
                        GXWGFifo.u8 = draw_color.b;
                        GXWGFifo.u8 = draw_color.a;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 1;
                        }
                        GXWGFifo.f32 = cur_pos.x + right.x + up.x;
                        GXWGFifo.f32 = cur_pos.y + right.y + up.y;
                        GXWGFifo.f32 = cur_pos.z + right.z + up.z;
                        GXWGFifo.u8 = draw_color.r;
                        GXWGFifo.u8 = draw_color.g;
                        GXWGFifo.u8 = draw_color.b;
                        GXWGFifo.u8 = draw_color.a;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 2;
                        }
                        GXWGFifo.f32 = prev_pos.x + right.x - up.x;
                        GXWGFifo.f32 = prev_pos.y + right.y - up.y;
                        GXWGFifo.f32 = prev_pos.z + right.z - up.z;
                        GXWGFifo.u8 = tail_color.r;
                        GXWGFifo.u8 = tail_color.g;
                        GXWGFifo.u8 = tail_color.b;
                        GXWGFifo.u8 = tail_color.a;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 3;
                        }
                    } else if (form != NULL) {
                        u8* it = form;
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
                                GXWGFifo.f32 = cur_pos.x + right.x * sx + up.x * tx;
                                GXWGFifo.f32 = cur_pos.y + right.y * sx + up.y * tx;
                                GXWGFifo.f32 = cur_pos.z + right.z * sx + up.z * tx;
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
                        GXWGFifo.f32 = cur_pos.x - right.x - up.x;
                        GXWGFifo.f32 = cur_pos.y - right.y - up.y;
                        GXWGFifo.f32 = cur_pos.z - right.z - up.z;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 0;
                        }
                        GXWGFifo.f32 = cur_pos.x - right.x + up.x;
                        GXWGFifo.f32 = cur_pos.y - right.y + up.y;
                        GXWGFifo.f32 = cur_pos.z - right.z + up.z;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 1;
                        }
                        GXWGFifo.f32 = cur_pos.x + right.x + up.x;
                        GXWGFifo.f32 = cur_pos.y + right.y + up.y;
                        GXWGFifo.f32 = cur_pos.z + right.z + up.z;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 2;
                        }
                        GXWGFifo.f32 = cur_pos.x + right.x - up.x;
                        GXWGFifo.f32 = cur_pos.y + right.y - up.y;
                        GXWGFifo.f32 = cur_pos.z + right.z - up.z;
                        if (pp->kind & DispTexture) {
                            GXWGFifo.u8 = tex_base + 3;
                        }
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
