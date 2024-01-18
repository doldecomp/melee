#include "lb/lbrefract.h"

#include <math.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXMisc.h>
#include <baselib/__baselib.h>
#include <baselib/fog.h>
#include <baselib/lobj.h>
#include <baselib/mtx.h>
#include <baselib/psdisp.h>
#include <baselib/state.h>
#include <baselib/util.h>
#include <MSL/math.h>

typedef struct {
    u8 filename[9];
    u8 message[39];
    unk_t pointers[3];
    u32 bitfields[8];
} psdisp_UnknownType001;

typedef struct {
    unk_t pointers[4];
    u8 message[36];
    u8 filename[9];
} psdisp_UnknownType002;

/* 004D4528 */ extern s32 HSD_PSDisp_804D7948;
/* 004D4524 */ extern unk_t HSD_PSDisp_804D7944;
/* 004D4520 */ extern unk_t HSD_PSDisp_804D7940;
/* 004D451C */ extern unk_t HSD_PSDisp_804D793C;
/* 004D4518 */ extern unk_t HSD_PSDisp_804D7938;
/* 004D4514 */ extern unk_t HSD_PSDisp_804D7934;
/* 004D4510 */ extern s32 HSD_PSDisp_804D7930;
/* 004D450C */ extern s32 HSD_PSDisp_804D792C;
/* 004D4508 */ extern f32 HSD_PSDisp_804D7928;
/* 004D4504 */ extern f32 HSD_PSDisp_804D7924;
/* 004D4500 */ extern f32 HSD_PSDisp_804D7920;
/* 004D44FC */ extern f32 HSD_PSDisp_804D791C;
/* 004D44F8 */ extern f32 HSD_PSDisp_804D7918;
/* 004D44F4 */ extern f32 HSD_PSDisp_804D7914;
/* 004D44F0 */ extern s32 HSD_PSDisp_804D7910;
/* 004D44EC */ extern s32 HSD_PSDisp_804D790C;
/* 004D44E8 */ extern s32 HSD_PSDisp_804D7908;
/* 004D2F64 */ extern u8 HSD_PSDisp_804D6384[2];
/* 004D2F60 */ extern u8 HSD_PSDisp_804D6380[2];
/* 00408F40 */ extern psdisp_UnknownType002 HSD_PSDisp_8040C360;
/* 00408EE0 */ extern psdisp_UnknownType001 HSD_PSDisp_8040C300;
/* 003B6208 */ extern f32 HSD_PSDisp_803B9628[12];

#ifdef 0
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
#endif
