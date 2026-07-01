/**
 * @file lbbgflash.c
 * @brief Background flash effects for dramatic game events.
 *
 * Provides full-screen color overlay flashes triggered by various game events.
 * Called from game mode code (gmallstar.c, gmregclear.c, gm_1A7A.c, etc).
 */

#include "lbbgflash.h"

#include <placeholder.h>

#include "dolphin/gx/GXStruct.h"

#include "lb/forward.h"

#include "lb/lbspdisplay.h"

typedef struct BgFlashState {
    u8 active : 1;
    u8 mode : 7;
} BgFlashState;

typedef struct BgFlashData {
    /* 0x00 */ BgFlashState state;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ GXColor x4;
    /* 0x08 */ GXColor x8;
    /* 0x0C */ GXColor xC;
    /* 0x10 */ f32 x10[4];
    /* 0x20 */ f32 x20[4];
    /* 0x30 */ u8 x30;
    /* 0x31 */ u8 x31;
    /* 0x32 */ u8 x32;
    /* 0x33 */ u8 x33;
    /* 0x34 */ s32 x34;
    /* 0x38 */ s32 x38;
    /* 0x3C */ s32 x3C;
    /* 0x40 */ HSD_GObj* x40;
    /* 0x44 */ HSD_GObj* x44;
} BgFlashData;

extern BgFlashData lbl_80433658;

#include <dolphin/gx.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/objalloc.h>
#include <baselib/particle.h>
#include <baselib/quatlib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

/* 021C18 */ static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd,
                                     int arg2);

static GXColor lbl_804D3840 = { 0, 0, 0, 255 };
static GXColor lbl_804D3844 = { 0, 0, 0, 0 };
static GXColor lbl_804D3848 = { 255, 255, 255, 255 };
static GXColor lbl_804D384C = { 0, 0, 0, 0 };

extern HSD_CObjDesc lbl_803BB028;

void fn_8001FC08(void)
{
    // TODO: Un-unroll this somehow?
    // When I try it just stays a loop in the asm
    BgFlashData* data = &lbl_80433658;
    f32 val;
    f32 cur_val;
    f32* cur;
    u8 target;

    if (data->x20[0] > 0.0f) {
        target = data->x8.r;
        cur_val = *(cur = &data->x10[0]);
        val = cur_val + data->x20[0];
        if (val < (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        target = data->x8.r;
        cur_val = *(cur = &data->x10[0]);
        val = cur_val + data->x20[0];
        if (val > (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[1] > 0.0f) {
        target = data->x8.g;
        cur_val = *(cur = &data->x10[1]);
        val = cur_val + data->x20[1];
        if (val < (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        target = data->x8.g;
        cur_val = *(cur = &data->x10[1]);
        val = cur_val + data->x20[1];
        if (val > (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[2] > 0.0f) {
        target = data->x8.b;
        cur_val = *(cur = &data->x10[2]);
        val = cur_val + data->x20[2];
        if (val < (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        target = data->x8.b;
        cur_val = *(cur = &data->x10[2]);
        val = cur_val + data->x20[2];
        if (val > (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }

    if (data->x20[3] > 0.0f) {
        target = data->x8.a;
        cur_val = *(cur = &data->x10[3]);
        val = cur_val + data->x20[3];
        if (val < (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    } else {
        target = data->x8.a;
        cur_val = *(cur = &data->x10[3]);
        val = cur_val + data->x20[3];
        if (val > (f32) target) {
            *cur = val;
        } else {
            *cur = (f32) target;
        }
    }
}

void fn_8001FEC4(HSD_GObj* gobj, s32 code)
{
    BgFlashData* data = &lbl_80433658;
    s32 mode;
    s32 y;
    PAD_STACK(8);

    if (data->state.active) {
        return;
    }

    hsd_80391A04(1.0f, 1.0f, 1);
    mode = data->state.mode;

    if (mode == 5 || mode >= 5 || mode < 3) {
        u8 r;
        u8 g;
        u8 b;
        u8 a;

        a = data->xC.a;
        b = data->xC.b;
        g = data->xC.g;
        r = data->xC.r;

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(0.0f, 0.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(640.0f, 0.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(640.0f, -480.0f);
        GXColor4u8(r, g, b, a);
        GXPosition2f32(0.0f, -480.0f);
        GXColor4u8(r, g, b, a);
        return;
    }

    if (data->x33 != 0) {
        if ((u32) mode == 3U) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition2f32(0.0f, 0.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(640.0f, 0.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(640.0f, -480.0f);
            GXColor4u8(0, 0, 0, 0xFF);
            GXPosition2f32(0.0f, -480.0f);
            GXColor4u8(0, 0, 0, 0xFF);
        }
        return;
    }

    switch ((s32) data->x30) {
    case 0:
        if ((u32) mode == 3U) {
            y = 0;
            while (y <= (s32) data->x38) {
                if (y == (s32) data->x38) {
                    s32 width;
                    u8 strip_h;
                    s32 neg_y;
                    s32 neg_yh;

                    strip_h = data->x32;
                    width = data->x34;
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y;
                    neg_yh = -(y + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) width, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) width, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                } else {
                    u8 strip_h = data->x32;
                    s32 neg_y;
                    s32 neg_yh;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y;
                    neg_yh = -(y + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                }
                y += data->x32;
            }
        } else {
            s32* pY;
            s32 y2;

            for (pY = &data->x38, y2 = data->x38; y2 <= 0x1E0; y2 += data->x32)
            {
                if (y2 == *pY) {
                    s32 x34;
                    u8 strip_h;
                    s32 right;
                    s32 neg_y;
                    s32 xr;
                    s32 neg_yh;

                    x34 = data->x34;
                    strip_h = data->x32;
                    right = 0x280;
                    right -= x34;
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y2;
                    xr = right + x34;
                    neg_yh = -(y2 + strip_h);
                    GXPosition2f32((f32) x34, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) xr, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) xr, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32((f32) x34, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                } else {
                    s32 neg_y;
                    u8 strip_h = data->x32;
                    s32 neg_yh;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    neg_y = -y2;
                    neg_yh = -(y2 + strip_h);
                    GXPosition2f32(0.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_y);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(640.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                    GXPosition2f32(0.0f, (f32) neg_yh);
                    GXColor4u8(0, 0, 0, 0xFF);
                }
            }
        }
        break;
    }
}

void fn_800204C8(void)
{
    f64 temp;
    BgFlashData* data = &lbl_80433658;
    s32 mode = data->state.mode;

    if (mode == 5) {
        return;
    }
    if (mode >= 5) {
        return;
    }
    if (mode >= 3) {
        goto case_3_4;
    }
    switch (mode) {
    case 0:
    case 1:
    case 2:
        goto case_0_1_2;
    }
    return;

case_0_1_2:
    fn_8001FC08();
    data->xC.r = data->x10[0];
    data->xC.g = data->x10[1];
    data->xC.b = data->x10[2];
    data->xC.a = data->x10[3];
    return;

case_3_4:
    switch ((s32) data->x30) {
    case 0: {
        s32* pX;
        s32* pY;
        s32 i;

        pY = &data->x38;
        pX = &data->x34;

        for (i = 0; i < data->x3C; i++) {
            if (*pX < 0x280) {
                *pX = *pX + data->x31;
            } else if (*pY < 0x1E0) {
                *pY = *pY + data->x32;
                *pX = 0;
            } else {
                data->x33 = 1;
                return;
            }
        }
        break;
    }
    }
}

/// @brief Trigger background flash.
/// @param duration Flash duration in frames (minimum 1).
void lbBgFlash_800205F0(s32 duration)
{
    if (duration < 1) {
        duration = 1;
    }
    lbBgFlash_800206D4(&lbl_804D3848, &lbl_804D3840, duration);
    lbl_80433658.state.mode = 0;
}

/// @brief Trigger background flash.
/// @param count Flash duration in frames (minimum 1).
void lbBgFlash_8002063C(int count)
{
    if (count < 1) {
        count = 1;
    }
    lbBgFlash_800206D4(&lbl_804D3844, &lbl_804D3840, count);
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_80020688(int count)
{
    if (count < 1) {
        count = 1;
    }
    lbBgFlash_800206D4(&lbl_804D384C, &lbl_804D3848, count);
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_800206D4(GXColor* col1, GXColor* col2, int arg2)
{
    BgFlashData* data = &lbl_80433658;
    int count = arg2;

    if (count < 1) {
        count = 1;
    }

    data->state.active = 0;
    data->state.mode = 2;
    data->x4 = *col1;
    data->xC = data->x4;
    data->x8 = *col2;
    data->x10[0] = (f32) col1->r;
    data->x10[1] = (f32) col1->g;
    data->x10[2] = (f32) col1->b;
    data->x10[3] = (f32) col1->a;
    data->x20[0] = (f32) (col2->r - col1->r) / (f32) count;
    data->x20[1] = (f32) (col2->g - col1->g) / (f32) count;
    data->x20[2] = (f32) (col2->b - col1->b) / (f32) count;
    data->x20[3] = (f32) (col2->a - col1->a) / (f32) count;
}

void lbBgFlash_InitState(GXColor* color)
{
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    lbl_80433658.xC = *color;
}
void fn_800208B0(u8 arg0)
{
    BgFlashData* data = &lbl_80433658;
    lbl_80433658.state.active = 0;
    if ((data && data) && data) {
    }
    lbl_80433658.state.mode = 5;
    data->xC.b = 0;
    data->xC.g = 0;
    data->xC.r = 0;
    data->xC.a = arg0;
}
void lbBgFlash_800208EC(int arg0)
{
    BgFlashData* flash = &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;

    HSD_CObj* temp1;
    HSD_CObj* temp2;
    u8 temp3;

    lbl_80433658.x44 = GObj_Create(0x14, 0x16, 0);

    temp2 = (temp1 = HSD_CObjLoadDesc(&lbl_803BB028));
    temp3 = HSD_GObj_804D784B;
    gobj1_slot = &flash->x44;
    HSD_GObjObject_80390A70(*gobj1_slot, temp3 & 0xFFFFFFFF, temp2);

    if ((gobj1_slot && gobj1_slot) && gobj1_slot) {
    }

    GObj_SetupGXLinkMax(*gobj1_slot, HSD_GObj_803910D8, (u8) (arg0 & 0xFFFFu));
    (*gobj1_slot)->gxlink_prios = 0x10000;
    flash->x40 = GObj_Create(0x15, 0x16, 2);

    gobj2_slot = &flash->x40;
    GObj_SetupGXLink(*gobj2_slot, (GObj_RenderFunc) fn_8001FEC4, 0x10,
                     (u8) arg0);
    HSD_GObj_SetupProc(*gobj2_slot, (HSD_GObjEvent) fn_800204C8, 0);

    lbl_80433658.state.active = 1;
    lbl_80433658.state.mode = 0;
}

void lbBgFlash_800209F4(void)
{
    BgFlashData* flash = &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;
    HSD_GObj* temp;

    PAD_STACK(0x8);

    // This is flash->x44
    lbl_80433658.x44 = GObj_Create(0x14, 0x16, 0);
    gobj1_slot = &flash->x44;
    HSD_GObjObject_80390A70(*gobj1_slot,
                            HSD_GObj_804D784B & 0xFFFFFFFFFFFFFFFF,
                            HSD_CObjLoadDesc(&lbl_803BB028));
    GObj_SetupGXLinkMax(*gobj1_slot, HSD_GObj_803910D8, 0xa);
    (*gobj1_slot)->gxlink_prios = 0x10000;

    if ((!HSD_GObj_804D784B) && (!HSD_GObj_804D784B)) {
    }
    // This is flash->x40
    lbl_80433658.x40 = GObj_Create(0x15, 0x16, 2);
    gobj2_slot = &flash->x40;
    GObj_SetupGXLink(*gobj2_slot, (GObj_RenderFunc) fn_8001FEC4, 0x10, 0xa);
    temp = *gobj2_slot;
    HSD_GObj_SetupProc(temp, (HSD_GObjEvent) fn_800204C8, 0);
    lbl_80433658.state.active = 1;
    lbl_80433658.state.mode = 0;
}

static inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

#pragma inline_depth(1)
void fn_80020AEC(HSD_JObj* jobj, Mtx out)
{
    MtxPtr out_mtx = out;
    HSD_JObj* parent;
    HSD_JObj* cur;
    s32 i;
    Mtx tmp;
    Vec3 col;
    volatile f32 scale_mag;
    u8 _[4];

    if (jobj == NULL) {
        parent = NULL;
    } else {
        parent = jobj->parent;
    }

    {
        MtxPtr jobj_mtx = HSD_JObjGetMtxPtr(jobj);
        HSD_JObjGetMtxPtr(parent);
        HSD_MtxInverseConcat(parent->mtx, jobj_mtx, out_mtx);
    }

    for (i = 0; i < 3; i++) {
        f32 mag;
        f32 scale_sq;
        f32 factor;

        col.x = out_mtx[0][i];
        col.y = out_mtx[1][i];
        col.z = out_mtx[2][i];

        mag = PSVECMag(&col);
        if (mag > 1e-10f) {
            mag = 1.0f / mag;
        }

        {
            f32 sx;
            f32 sy;
            f32 sz;
            sy = jobj->mtx[1][i];
            sx = jobj->mtx[0][i];
            sz = jobj->mtx[2][i];
            sy *= sy;
            sx *= sx;
            sz *= sz;
            scale_sq = sy + sx;
            scale_sq = sz + scale_sq;
        }

        if (scale_sq > 0.0f) {
            f64 e = __frsqrte(scale_sq);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            scale_mag = (f32) ((f64) scale_sq * e);
            scale_sq = scale_mag;
        }

        factor = mag * scale_sq;
        col.x *= factor;
        col.y *= factor;
        col.z *= factor;
        out_mtx[0][i] = col.x;
        out_mtx[1][i] = col.y;
        out_mtx[2][i] = col.z;
    }

    cur = jobj_parent(jobj);
    while (cur != NULL) {
        if (jobj_parent(cur) != NULL) {
            HSD_JObj* grandpar;
            if (cur == NULL) {
                grandpar = NULL;
            } else {
                grandpar = cur->parent;
            }
            HSD_MtxInverseConcat(HSD_JObjGetMtxPtr(grandpar),
                                 HSD_JObjGetMtxPtr(cur), tmp);
        } else {
            PSMTXCopy(HSD_JObjGetMtxPtr(cur), tmp);
        }

        for (i = 0; i < 3; i++) {
            f32 mag;

            col.x = tmp[0][i];
            col.y = tmp[1][i];
            col.z = tmp[2][i];

            mag = PSVECMag(&col);
            if (mag > 0.00001f) {
                mag = 1.0f / mag;
            }

            col.x *= mag;
            col.y *= mag;
            col.z *= mag;
            tmp[0][i] = col.x;
            tmp[1][i] = col.y;
            tmp[2][i] = col.z;
        }

        PSMTXConcat(tmp, out_mtx, out_mtx);
        cur = jobj_parent(cur);
    }
}
#pragma inline_depth(8)
void lbBgFlash_80020E38(HSD_JObj* jobj, Vec3* dir, f32 max_angle,
                        f32 min_angle, f32 unused)
{
    f32 dz2;
    u8 _1[16];
    Mtx quatMtx;
    Mtx rotMtx;
    Mtx resultMtx;
    volatile f32 tmp;
    f32 z_col_z;
    f32 angle;
    f32 z_col_y;
    f32 z_col_x;
    f32 mag_sq;
    f32 dx2 = dir->x * dir->x;
    f32 dy2 = dir->y * dir->y;
    dz2 = dir->z * dir->z;
    (void) dz2;
    if (dx2 + dy2 + dz2 == 0.0f) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    z_col_y = jobj->mtx[1][2];
    z_col_x = jobj->mtx[0][2];
    z_col_z = jobj->mtx[2][2];
    z_col_x = SQ(z_col_x) + SQ(z_col_y); mag_sq = z_col_x;
    mag_sq = SQ(z_col_z) + mag_sq;
    if (mag_sq > 0.0f) {
        f64 e = __frsqrte(mag_sq);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        tmp = (f32) ((f64) mag_sq * e);
        mag_sq = tmp;
    }

    if (mag_sq != 0.0f) {
        {
            f32 z_div_mag = z_col_z / mag_sq;
            angle = atan2f(-dir->x * z_div_mag, dir->y);
        }

        if (angle > max_angle) {
            angle = max_angle;
        }
        if (angle < -min_angle) {
            angle = -min_angle;
        }

        if (!(jobj->flags & JOBJ_USE_QUATERNION)) {
            HSD_JObjSetRotationZ(jobj, angle + HSD_JObjGetRotationZ(jobj));
        } else {
            PSMTXQuat(quatMtx, &jobj->rotate);
            MTXRotRad(rotMtx, 'z', angle);
            PSMTXConcat(quatMtx, rotMtx, resultMtx);
            MatToQuat(resultMtx, &jobj->rotate);
            HSD_JObjSetMtxDirty(jobj);
        }

        HSD_JObjSetupMatrix(jobj);
    }
}

void fn_8002113C(HSD_JObj* jobj, Vec3* axis, f32 angle)
{
    Mtx tmpMtx;
    Mtx rotMtx;
    Mtx result;
    Vec3 rot;
    Quaternion rot2;
    Vec3 localAxis;
    Mtx mtx;

    PAD_STACK(0x10);

    HSD_JObjSetupMatrix(jobj);
    fn_80020AEC(jobj, mtx);
    PSMTXTranspose(mtx, mtx);
    PSMTXMultVec(mtx, (Vec*) axis, (Vec*) &localAxis);
    PSMTXRotAxisRad(rotMtx, (Vec*) &localAxis, -angle);

    if (!(jobj->flags & JOBJ_USE_QUATERNION)) {
        HSD_JObjGetRotation(jobj, (Quaternion*) &rot);
        HSD_MkRotationMtx(tmpMtx, &rot);
        PSMTXConcat(tmpMtx, rotMtx, result);
        HSD_QuatLib_8037EB28(result, &rot);
        HSD_JObjSetRotation(jobj, (Quaternion*) &rot);
    } else {
        HSD_JObjGetRotation(jobj, &rot2);
        HSD_MtxQuat(tmpMtx, &rot2);
        PSMTXConcat(tmpMtx, rotMtx, result);
        MatToQuat(result, &rot2);
        HSD_JObjSetRotation(jobj, &rot2);
    }
}

typedef struct IKChainData {
    /* 0x00 */ HSD_JObj* jobj0;
    /* 0x04 */ HSD_JObj* jobj1;
    /* 0x08 */ u8 pad_08[4];
    /* 0x0C */ Vec3 pos0;
    /* 0x18 */ Vec3 pos1;
    /* 0x24 */ Vec3 pos2;
    /* 0x30 */ Vec3 pos3;
    /* 0x3C */ Vec3 pos4;
    /* 0x48 */ f32 len0;
    /* 0x4C */ f32 len1;
} IKChainData;

void lbBgFlash_80021410(void* arg0)
{
    IKChainData* data = arg0;
    u8 pad_hi[32];
    Vec3 axis;
    u8 pad_mid[16];
    Vec3 diff_pos0_pos1;
    Vec3 pos1_from_pos0;
    Vec3 temp_delta;
    volatile f32 sin_mag;
    volatile f32 len_ab_mag;
    volatile f32 len_bc_mag;
    volatile f32 len_ac_mag;
    f32 dot;
    f32 sin_val;
    f32 len_ab;
    f32 len_bc;
    f32 len_ac;
    f32 angle1;
    f32 angle2;
    f32 sum_len;
    f32 sum_pow;
    f32 len_pow;
    f32 c2;
    f32 a2;
    f32 b2;
    f32 two_a;
    f32 cos1;
    f32 cos2;
    f32 acos1;
    f32 acos2;
    f64 rem;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3* pDiff;
    PAD_STACK(16);

    HSD_JObjSetupMatrix(data->jobj1);

    axis.x = data->jobj1->mtx[0][2];
    axis.y = data->jobj1->mtx[1][2];
    axis.z = data->jobj1->mtx[2][2];
    lbVector_Normalize(&axis);

    {
        f32 nx = axis.x;
        f32 nz = axis.z;
        f32 ny = axis.y;
        f32 dot;
        f32 d;
        f32 x = data->pos4.x;

        dot = -((nz * data->pos1.z) +
                ((nx * data->pos1.x) + (ny * data->pos1.y)));

        d = -(dot + ((data->pos4.z * nz) + ((x * nx) + (data->pos4.y * ny))));
        data->pos4.x = (d * nx) + x;
        data->pos4.y = (d * ny) + data->pos4.y;
        data->pos4.z = (d * nz) + data->pos4.z;

        {
            f32 x = data->pos0.x;
            d = -(dot +
                  ((data->pos0.z * nz) + ((x * nx) + (data->pos0.y * ny))));
            data->pos0.x = (d * nx) + x;
        }
        data->pos0.y = (d * ny) + data->pos0.y;
        data->pos0.z = (d * nz) + data->pos0.z;

        {
            f32 x = data->pos1.x;
            d = -(dot +
                  ((data->pos1.z * nz) + ((x * nx) + (data->pos1.y * ny))));
            data->pos1.x = (d * nx) + x;
        }
        data->pos1.y = (d * ny) + data->pos1.y;
        data->pos1.z = (d * nz) + data->pos1.z;
    }

    pDiff = lbVector_Diff(&data->pos0, &data->pos1, &diff_pos0_pos1);
    dot = (axis.z * pDiff->z) + ((axis.x * pDiff->x) + (axis.y * pDiff->y));
    if ((sin_val = 1.0f - (dot * dot)) > 0.0f) {
        f64 e = __frsqrte(sin_val);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        sin_mag = (f32) ((f64) sin_val * e);
        sin_val = sin_mag;
    }
    data->len0 = data->len0 * sin_val;

    lbVector_Diff(&data->pos4, &data->pos0, &temp_delta);
    lbVector_Diff(&data->pos1, &data->pos0, &pos1_from_pos0);
    angle1 = lbVector_Angle(&temp_delta, &pos1_from_pos0);

    lbVector_Diff(&data->pos2, &data->pos1, &temp_delta);
    angle2 = (f32) (3.141592653589793 -
                    lbVector_Angle(&temp_delta, &pos1_from_pos0));

    dx = data->pos0.x - data->pos4.x;
    dz = data->pos0.z;
    dz -= data->pos4.z;
    dy = data->pos0.y - data->pos4.y;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    if ((len_ab = dz + (dx + dy)) > 0.0f) {
        f64 e = __frsqrte(len_ab);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        len_ab_mag = (f32) ((f64) len_ab * e);
        len_ab = len_ab_mag;
    }

    dx = data->pos0.x - data->pos1.x;
    dz = data->pos0.z;
    dz -= data->pos1.z;
    dy = data->pos0.y - data->pos1.y;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    if ((len_bc = dz + (dx + dy)) > 0.0f) {
        f64 e = __frsqrte(len_bc);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        len_bc_mag = (f32) ((f64) len_bc * e);
        len_bc = len_bc_mag;
    }
    data->len0 = len_bc;

    dx = data->pos1.x - data->pos3.x;
    dz = data->pos1.z;
    dz -= data->pos3.z;
    dy = data->pos1.y - data->pos3.y;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    if ((len_ac = dz + (dx + dy)) > 0.0f) {
        f64 e = __frsqrte(len_ac);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        len_ac_mag = (f32) ((f64) len_ac * e);
        len_ac = len_ac_mag;
    }
    data->len1 = len_ac;

    len_bc = data->len0;
    len_ac = data->len1;

    sum_len = (10.0f * (len_bc + len_ac)) / 11.0f;
    sum_pow = sum_len * sum_len;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    sum_pow = sum_len * sum_pow;
    len_pow = len_ab * len_ab;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    len_pow = len_ab * len_pow;
    if (len_ab > sum_len) {
        len_ab =
            ((11.0f * sum_len) / 10.0f) + (-(sum_pow) / (10.0f * len_pow));
    }

    a2 = len_bc * len_bc;
    b2 = len_ab * len_ab;
    two_a = 2.0f * len_bc;
    c2 = len_ac * len_ac;

    cos1 = ((a2 + b2) - c2) / (two_a * len_ab);
    cos2 = ((a2 + c2) - b2) / (two_a * len_ac);

    if (cos1 > 1.0f) {
        cos1 = 1.0f;
    } else if (cos1 < -1.0f) {
        cos1 = -1.0f;
    }

    if (cos2 > 1.0f) {
        cos2 = 1.0f;
    } else if (cos2 < -1.0f) {
        cos2 = -1.0f;
    }

    acos1 = acosf(cos1);
    acos2 = acosf(cos2);
    rem = 3.141592653589793 - (f64) acos2;
    if (rem < 0.1745329201221466) {
        acos2 =
            (f32) (2.9670597334676465 +
                   (f64) (f32) ((f64) (f32) (fabs(rem) / 0.1745329201221466) *
                                ((f64) acos2 - 2.9670597334676465)));
    }

    acos1 -= angle1;
    acos2 -= angle2;
    fn_8002113C(data->jobj0, &axis, acos1);
    fn_8002113C(data->jobj1, &axis, acos2);
}

extern HSD_ObjAllocData lbl_804336A0;

void fn_800219E4(void* arg0)
{
    HSD_ObjFree(&lbl_804336A0, arg0);
}

f32 lbl_804D63D8;

typedef struct {
    char pad[0x2C];
    void* x2C;
} BgFlashGlobal;

extern BgFlashGlobal* lbl_804D63E0;
extern struct Fighter_804D653C_t* lbl_804D63DC;

void lbBgFlash_80021A10(f32 arg8)
{
    lbl_804D63D8 = arg8;
}

void lbBgFlash_80021A18(int arg0)
{
    HSD_GObj* gobj;
    u8* user_data;

    HSD_ObjAllocInit(&lbl_804336A0, 0x84, 4);
    gobj = GObj_Create(0xE, 0xE, 0);
    if (gobj != NULL) {
        user_data = HSD_ObjAlloc(&lbl_804336A0);
        if (user_data != NULL) {
            GObj_InitUserData(gobj, 0xE, fn_800219E4, user_data);
            lbl_804D63E0 = (BgFlashGlobal*) gobj;
            lbl_804D63D8 = 1.0f;
            *user_data = (u8) arg0;
            lbArchive_LoadSymbols("LbBf.dat", &lbl_804D63DC,
                                  "lbBgFlashColAnimData", NULL);
            lbBgFlash_800208EC(6);
            fn_80021C1C();
            HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80021B04, 1);
            return;
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

typedef struct BgFlashUserData {
    u8 x0;
    u8 pad_01[3];
    ColorOverlay x4;
} BgFlashUserData;

#pragma dont_inline on

void fn_80021B04(HSD_GObj* gobj)
{
    BgFlashUserData* data = gobj->user_data;
    int was_active = data->x4.x7C_color_enable;
    GXColor color;
    f32 scale;

    PAD_STACK(4);

    fn_80021C80(gobj);
    if (data->x4.x7C_color_enable) {
        u8* bytes = (u8*) &color;
        scale = lbl_804D63D8;
        bytes[0] = (u8) ((f32) data->x4.x2C_hex.r * scale);
        // This is bytes[1] to bytes[3]
        ((u8*) (&color))[1] = (u8) (((f32) data->x4.x2C_hex.g) * scale);
        ((u8*) (&color))[2] = (u8) (((f32) data->x4.x2C_hex.b) * scale);
        ((u8*) (&color))[3] = (data->x4.x2C_hex.a * data->x0) / 255;
        lbBgFlash_InitState(&color);
        return;
    }
    if (was_active) {
        fn_800208B0(0);
    }
}

#pragma dont_inline reset

static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd, int arg2) {}

void fn_80021C1C(void)
{
    HSD_GObj* gobj = (HSD_GObj*) lbl_804D63E0;
    u8* user_data = gobj->user_data;
    lb_80014498((ColorOverlay*) (user_data + 4));
}

void lbBgFlash_80021C48(u32 arg0, u32 arg1)
{
    struct {
        u8 unk0[4];
        ColorOverlay x4;
    }* data = lbl_804D63E0->x2C;
    lb_800144C8(&data->x4, lbl_804D63DC, arg0, arg1);
}

void fn_80021C80(HSD_GObj* gobj)
{
    struct {
        u8 unk0[4];
        ColorOverlay x4;
    }* user_data = gobj->user_data;

    while (lb_80014258(gobj, &user_data->x4, fn_80021C18)) {
        lb_80014498(&user_data->x4);
    }
}
