#include "psdisp.h"

#include <math.h>
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

/* 39F89C */ static void calcTornadoLastPos(HSD_Particle*, f32*, f32*, f32*);
/* 39FA28 */ static void getColorPrimEnv(HSD_Particle*, GXColor*, GXColor*);
/* 39FB74 */ static void getColorMatAmb(HSD_Particle*, GXColor*, GXColor*);
/* 3B9628 */ extern f32 HSD_PSDisp_803B9628[12];
/* 40C300 */ extern psdisp_UnknownType001 HSD_PSDisp_8040C300;
/* 40C360 */ extern psdisp_UnknownType002 HSD_PSDisp_8040C360;
/* 4D6380 */ extern u8 HSD_PSDisp_804D6380[2];
/* 4D6384 */ extern u8 HSD_PSDisp_804D6384[2];
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
        *x = gp->x;
        *y = gp->y;
        *z = gp->z;
        return;
    }

    sina = sinf(pp->grav);
    sinb = sinf(pp->fric);
    cosa = cosf(pp->grav);
    cosb = cosf(pp->fric);

    vz0 = pp->vz - gp->aux.tornado.vel;
    vx0 = pp->vx - gp->grav;

    radius = ABS(gp->radius);
    radius += vz0 * tanf(ABS(gp->angle));
    radius *= pp->vy;
    px = radius * cosf(vx0);
    py = radius * sinf(vx0);
    pz = vz0;

    *x = px * cosb + pz * sinb + gp->x;
    *y = -px * sina * sinb + py * cosa + pz * sina * cosb + gp->y;
    *z = -px * cosa * sinb - py * sina + pz * cosa * cosb + gp->z;
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
