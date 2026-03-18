/**
 * @file lbbgflash.c
 * @brief Background flash effects for dramatic game events.
 *
 * Provides full-screen color overlay flashes triggered by various game events.
 * Called from game mode code (gmallstar.c, gmregclear.c, gm_1A4C.c, etc).
 */

#include "lbbgflash.h"

#include <placeholder.h>

#include "lb/forward.h"

#include "lb/lb_00F9.h"

typedef struct BgFlashState {
    u8 active : 1;
    u8 mode : 7;
} BgFlashState;

typedef struct BgFlashData {
    BgFlashState state;
    u8 pad[3];
    int x4;
    int x8;
    int xC;
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
#include <MSL/trigf.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>

/* 021A10 */ static void lbBgFlash_80021A10(f32 arg8);
/* 021C18 */ static void fn_80021C18(HSD_GObj* gobj, CommandInfo* cmd,
                                     int arg2);
/// @brief Initialize background flash state.
/* 02087C */ void lbBgFlash_InitState(int* duration);

extern s32 lbl_804D3840;
extern s32 lbl_804D3844;
extern s32 lbl_804D3848;
extern s32 lbl_804D384C;

typedef struct BgFlashData2 {
    u8 state;
    u8 pad1[3];
    int x4;
    int x8;
    u8 xC;
    u8 xD;
    u8 xE;
    u8 xF;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    u8 x30;
    u8 x31;
    u8 x32;
    u8 x33;
    s32 x34;
    s32 x38;
    s32 x3C;
    HSD_GObj* x40;
    HSD_GObj* x44;
} BgFlashData2;

extern HSD_CObjDesc lbl_803BB028;

void fn_8001FC08(void)
{
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    u8* end = (u8*) &data->x8;
    f32 val;

    if (data->x20 > 0.0f) {
        val = data->x10 + data->x20;
        if (val < (f32) end[0]) {
            data->x10 = val;
        } else {
            data->x10 = (f32) end[0];
        }
    } else {
        val = data->x10 + data->x20;
        if (val > (f32) end[0]) {
            data->x10 = val;
        } else {
            data->x10 = (f32) end[0];
        }
    }

    if (data->x24 > 0.0f) {
        val = data->x14 + data->x24;
        if (val < (f32) end[1]) {
            data->x14 = val;
        } else {
            data->x14 = (f32) end[1];
        }
    } else {
        val = data->x14 + data->x24;
        if (val > (f32) end[1]) {
            data->x14 = val;
        } else {
            data->x14 = (f32) end[1];
        }
    }

    if (data->x28 > 0.0f) {
        val = data->x18 + data->x28;
        if (val < (f32) end[2]) {
            data->x18 = val;
        } else {
            data->x18 = (f32) end[2];
        }
    } else {
        val = data->x18 + data->x28;
        if (val > (f32) end[2]) {
            data->x18 = val;
        } else {
            data->x18 = (f32) end[2];
        }
    }

    if (data->x2C > 0.0f) {
        val = data->x1C + data->x2C;
        if (val < (f32) end[3]) {
            data->x1C = val;
        } else {
            data->x1C = (f32) end[3];
        }
    } else {
        val = data->x1C + data->x2C;
        if (val > (f32) end[3]) {
            data->x1C = val;
        } else {
            data->x1C = (f32) end[3];
        }
    }
}

/// #fn_8001FEC4
void fn_8001FEC4(HSD_GObj* gobj, s32 code)
{
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    s32 mode;
    s32 y;

    PAD_STACK(8);

    if ((data->state >> 7) & 1) {
        return;
    }

    hsd_80391A04(1.0f, 1.0f, 1);
    mode = data->state & 0x7F;

    if (mode == 5 || mode >= 5 || mode < 3) {
        u8 a = data->xF;
        u8 b = data->xE;
        u8 g = data->xD;
        u8 r = data->xC;

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

    if (data->x30 != 0) {
        return;
    }

    if ((u32) mode == 3U) {
        y = 0;
        while (y <= (s32) data->x38) {
            if (y == (s32) data->x38) {
                u8 strip_h = data->x32;
                s32 width = data->x34;
                s32 neg_y;
                s32 neg_yh;

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
        y = data->x38;
        while (y <= 0x1E0) {
            if (y == (s32) data->x38) {
                s32 x34 = data->x34;
                u8 strip_h = data->x32;
                s32 right = 0x280 - x34;
                s32 neg_y;
                s32 xr = x34 + right;
                s32 neg_yh;

                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                neg_y = -y;
                neg_yh = -(y + strip_h);
                GXPosition2f32((f32) x34, (f32) neg_y);
                GXColor4u8(0, 0, 0, 0xFF);
                GXPosition2f32((f32) xr, (f32) neg_y);
                GXColor4u8(0, 0, 0, 0xFF);
                GXPosition2f32((f32) xr, (f32) neg_yh);
                GXColor4u8(0, 0, 0, 0xFF);
                GXPosition2f32((f32) x34, (f32) neg_yh);
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
    }
}

void fn_800204C8(void)
{
    f64 temp;
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    s32 mode = data->state & 0x7F;

    if (mode == 5) {
        return;
    }
    if (mode >= 5) {
        return;
    }
    if (mode >= 3) {
        goto case_3_4;
    }
    if (mode >= 0) {
        goto case_0_1_2;
    }
    return;

case_0_1_2:
    fn_8001FC08();
    data->xC = (s32) data->x10;
    data->xD = (s32) data->x14;
    data->xE = (s32) data->x18;
    data->xF = (s32) data->x1C;
    return;

case_3_4:
    if ((s32) data->x30 == 0) {
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

void lbBgFlash_800206D4(void* arg0, s32* arg1, int arg2)
{
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    BgFlashState* state = (BgFlashState*) data;
    u8* src = (u8*) arg0;
    u8* dst = (u8*) arg1;
    int count = arg2;

    if (count < 1) {
        count = 1;
    }

    state->active = 0;
    state->mode = 2;
    data->x4 = *(s32*) arg0;
    *(s32*) &data->xC = data->x4;
    data->x8 = *arg1;
    data->x10 = (f32) src[0];
    data->x14 = (f32) src[1];
    data->x18 = (f32) src[2];
    data->x1C = (f32) src[3];
    data->x20 = (f32) (dst[0] - src[0]) / (f32) count;
    data->x24 = (f32) (dst[1] - src[1]) / (f32) count;
    data->x28 = (f32) (dst[2] - src[2]) / (f32) count;
    data->x2C = (f32) (dst[3] - src[3]) / (f32) count;
}

void lbBgFlash_InitState(int* duration)
{
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    lbl_80433658.xC = *duration;
}
void fn_800208B0(u8 arg0)
{
    BgFlashData2* data = (BgFlashData2*) &lbl_80433658;
    lbl_80433658.state.active = 0;
    lbl_80433658.state.mode = 5;
    data->xE = 0;
    data->xD = 0;
    data->xC = 0;
    data->xF = arg0;
}
#pragma push
#pragma dont_inline on
void lbBgFlash_800208EC(int arg0)
{
    BgFlashData2* flash = (BgFlashData2*) &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;

    HSD_CObj* temp1;
    HSD_CObj* temp2;
    u8 temp3;

    ((BgFlashData2*) (&lbl_80433658))->x44 = GObj_Create(0x14, 0x16, 0);

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
#pragma pop

void lbBgFlash_800209F4(void)
{
    BgFlashData2* flash = (BgFlashData2*) &lbl_80433658;
    HSD_GObj** gobj1_slot;
    HSD_GObj** gobj2_slot;
    HSD_GObj* temp;

    PAD_STACK(0x8);

    // This is flash->x44
    ((BgFlashData2*) (&lbl_80433658))->x44 = GObj_Create(0x14, 0x16, 0);
    gobj1_slot = &flash->x44;
    HSD_GObjObject_80390A70(*gobj1_slot,
                            HSD_GObj_804D784B & 0xFFFFFFFFFFFFFFFF,
                            HSD_CObjLoadDesc(&lbl_803BB028));
    GObj_SetupGXLinkMax(*gobj1_slot, HSD_GObj_803910D8, 0xa);
    (*gobj1_slot)->gxlink_prios = 0x10000;

    if ((!HSD_GObj_804D784B) && (!HSD_GObj_804D784B)) {
    }
    // This is flash->x40
    ((BgFlashData2*) (&lbl_80433658))->x40 = GObj_Create(0x15, 0x16, 2);
    gobj2_slot = &flash->x40;
    GObj_SetupGXLink(*gobj2_slot, (GObj_RenderFunc) fn_8001FEC4, 0x10, 0xa);
    temp = *gobj2_slot;
    HSD_GObj_SetupProc(temp, (HSD_GObjEvent) fn_800204C8, 0);
    lbl_80433658.state.active = 1;
    lbl_80433658.state.mode = 0;
}

/// #fn_80020AEC

#pragma inline_depth(1)
void fn_80020AEC(HSD_JObj* jobj, Mtx out)
{
    HSD_JObj* parent;
    HSD_JObj* cur;
    s32 i;

    parent = jobj ? jobj->parent : NULL;

    {
        MtxPtr jobj_mtx = HSD_JObjGetMtxPtr(jobj);
        HSD_JObjGetMtxPtr(parent);
        HSD_MtxInverseConcat(parent->mtx, jobj_mtx, out);
    }

    for (i = 0; i < 3; i++) {
        Vec3 col;
        f32 mag;
        f32 scale_sq;
        f32 sp28;
        f32 factor;

        col.x = out[0][i];
        col.y = out[1][i];
        col.z = out[2][i];

        mag = PSVECMag(&col);
        if (mag > 1e-10f) {
            mag = 1.0f / mag;
        }

        {
            f32 sy = jobj->mtx[1][i];
            f32 sx = jobj->mtx[0][i];
            f32 sz = jobj->mtx[2][i];
            scale_sq = sz * sz + sy * sy + sx * sx;
        }

        if (scale_sq > 0.0f) {
            f64 e = __frsqrte(scale_sq);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            e = 0.5 * e * -(((f64) scale_sq * (e * e)) - 3.0);
            sp28 = (f32) ((f64) scale_sq * e);
            scale_sq = sp28;
        }

        factor = mag * scale_sq;
        col.x *= factor;
        col.y *= factor;
        col.z *= factor;
        out[0][i] = col.x;
        out[1][i] = col.y;
        out[2][i] = col.z;
    }

    cur = jobj ? jobj->parent : NULL;
    while (cur != NULL) {
        HSD_JObj* grandpar;
        Mtx tmp;

        grandpar = cur ? cur->parent : NULL;

        if (grandpar != NULL) {
            HSD_JObjGetMtxPtr(cur);
            HSD_JObjGetMtxPtr(grandpar);
            HSD_MtxInverseConcat(grandpar->mtx, cur->mtx, tmp);
        } else {
            HSD_JObjGetMtxPtr(cur);
            PSMTXCopy(cur->mtx, tmp);
        }

        for (i = 0; i < 3; i++) {
            Vec3 col;
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

        PSMTXConcat(tmp, out, out);
        cur = cur ? cur->parent : NULL;
    }
}
#pragma inline_depth(8)
void lbBgFlash_80020E38(HSD_JObj* jobj, Vec3* dir, f32 max_angle,
                        f32 min_angle)
{
    f32 dx = dir->x;
    f32 dy = dir->y;
    f32 dz = dir->z;
    f32 mag_sq;
    f32 len;
    f32 angle;
    f32 z_col_z;
    f32 z_col_x;

    PAD_STACK(24);

    if ((dz * dz) + ((dx * dx) + (dy * dy)) == 0.0f) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    z_col_x = jobj->mtx[0][2];
    z_col_z = jobj->mtx[2][2];
    mag_sq = (jobj->mtx[2][2] * jobj->mtx[2][2]) +
             ((jobj->mtx[0][2] * jobj->mtx[0][2]) +
              (jobj->mtx[1][2] * jobj->mtx[1][2]));

    if (mag_sq > 0.0f) {
        f64 e = __frsqrte(mag_sq);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) mag_sq * (e * e)) - 3.0);
        len = (f32) ((f64) mag_sq * e);
    } else {
        len = mag_sq;
    }

    if (len == 0.0f) {
        return;
    }

    angle = atan2f(-dir->x * (z_col_z / len), dir->y);

    if (angle > max_angle) {
        angle = max_angle;
    }
    if (angle < -min_angle) {
        angle = -min_angle;
    }

    if (!(jobj->flags & JOBJ_USE_QUATERNION)) {
        f32 z = angle + HSD_JObjGetRotationZ(jobj);
        HSD_JObjSetRotationZ(jobj, z);
    } else {
        Mtx quatMtx;
        Mtx rotMtx;
        Mtx resultMtx;
        PSMTXQuat(quatMtx, &jobj->rotate);
        MTXRotRad(rotMtx, 'z', angle);
        PSMTXConcat(quatMtx, rotMtx, resultMtx);
        MatToQuat(resultMtx, &jobj->rotate);
        HSD_JObjSetMtxDirty(jobj);
    }

    HSD_JObjSetupMatrix(jobj);
}

void fn_8002113C(HSD_JObj* jobj, Vec3* axis, f32 angle)
{
    Mtx mtx;
    Mtx rotMtx;
    Mtx tmpMtx;
    Mtx result;
    Vec3 localAxis;
    Quaternion rot;
    Quaternion rot2;

    PAD_STACK(16);

    HSD_JObjSetupMatrix(jobj);
    fn_80020AEC(jobj, mtx);
    PSMTXTranspose(mtx, mtx);
    PSMTXMultVec(mtx, (Vec*) axis, (Vec*) &localAxis);
    PSMTXRotAxisRad(rotMtx, (Vec*) &localAxis, -angle);

    if (!(jobj->flags & JOBJ_USE_QUATERNION)) {
        HSD_JObjGetRotation(jobj, &rot);
        HSD_MkRotationMtx(tmpMtx, (Vec3*) &rot);
        PSMTXConcat(tmpMtx, rotMtx, result);
        HSD_QuatLib_8037EB28(result, (Vec3*) &rot);
        HSD_JObjSetRotation(jobj, &rot);
    } else {
        HSD_JObjGetRotation(jobj, &rot2);
        HSD_MtxQuat(tmpMtx, &rot2);
        PSMTXConcat(tmpMtx, rotMtx, result);
        MatToQuat(result, &rot2);
        HSD_JObjSetRotation(jobj, &rot2);
    }
}

/// #lbBgFlash_80021410

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
    Vec3 axis;
    Vec3 sp2C;
    Vec3 sp38;
    Vec3 sp44;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 dot;
    f32 d;
    f32 sin_val;
    f32 len_ab;
    f32 len_bc;
    f32 len_ac;
    f32 angle1;
    f32 angle2;
    f32 sum_len;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 two_a;
    f32 cos1;
    f32 cos2;
    f32 acos1;
    f32 acos2;
    f32 rem;
    f32 dx;
    f32 dy;
    f32 dz;
    HSD_JObj* jobj;
    Vec3* pDiff;
    PAD_STACK(64);

    jobj = data->jobj1;
    HSD_JObjSetupMatrix(jobj);

    axis.x = data->jobj1->mtx[0][2];
    axis.y = data->jobj1->mtx[1][2];
    axis.z = data->jobj1->mtx[2][2];
    lbVector_Normalize(&axis);

    nx = axis.x;
    ny = axis.y;
    nz = axis.z;

    dot = -((nz * data->pos1.z) +
            ((nx * data->pos1.x) + (ny * data->pos1.y)));

    d = -(dot + ((data->pos4.z * nz) +
                 ((data->pos4.x * nx) + (data->pos4.y * ny))));
    data->pos4.x = (d * nx) + data->pos4.x;
    data->pos4.y = (d * ny) + data->pos4.y;
    data->pos4.z = (d * nz) + data->pos4.z;

    d = -(dot + ((data->pos0.z * nz) +
                 ((data->pos0.x * nx) + (data->pos0.y * ny))));
    data->pos0.x = (d * nx) + data->pos0.x;
    data->pos0.y = (d * ny) + data->pos0.y;
    data->pos0.z = (d * nz) + data->pos0.z;

    d = -(dot + ((data->pos1.z * nz) +
                 ((data->pos1.x * nx) + (data->pos1.y * ny))));
    data->pos1.x = (d * nx) + data->pos1.x;
    data->pos1.y = (d * ny) + data->pos1.y;
    data->pos1.z = (d * nz) + data->pos1.z;

    pDiff = lbVector_Diff(&data->pos0, &data->pos1, &sp44);
    dot = (nz * pDiff->z) + ((nx * pDiff->x) + (ny * pDiff->y));
    sin_val = -((dot * dot) - 1.0f);
    if (sin_val > 0.0f) {
        f64 e = __frsqrte(sin_val);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) sin_val * (e * e)) - 3.0);
        sp28 = (f32) ((f64) sin_val * e);
        sin_val = sp28;
    }
    data->len0 = data->len0 * sin_val;

    lbVector_Diff(&data->pos4, &data->pos0, &sp2C);
    lbVector_Diff(&data->pos1, &data->pos0, &sp38);
    angle1 = lbVector_Angle(&sp2C, &sp38);

    lbVector_Diff(&data->pos2, &data->pos1, &sp2C);
    angle2 = (f32) (3.141592653589793 - lbVector_Angle(&sp2C, &sp38));

    dx = data->pos0.x - data->pos4.x;
    dy = data->pos0.y - data->pos4.y;
    dz = data->pos0.z - data->pos4.z;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_ab = dz + (dx + dy);
    if (len_ab > 0.0f) {
        f64 e = __frsqrte(len_ab);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ab * (e * e)) - 3.0);
        sp24 = (f32) ((f64) len_ab * e);
        len_ab = sp24;
    }

    dx = data->pos0.x - data->pos1.x;
    dy = data->pos0.y - data->pos1.y;
    dz = data->pos0.z - data->pos1.z;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_bc = dz + (dx + dy);
    if (len_bc > 0.0f) {
        f64 e = __frsqrte(len_bc);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_bc * (e * e)) - 3.0);
        sp20 = (f32) ((f64) len_bc * e);
        len_bc = sp20;
    }
    data->len0 = len_bc;

    dx = data->pos1.x - data->pos3.x;
    dy = data->pos1.y - data->pos3.y;
    dz = data->pos1.z - data->pos3.z;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_ac = dz + (dx + dy);
    if (len_ac > 0.0f) {
        f64 e = __frsqrte(len_ac);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        e = 0.5 * e * -(((f64) len_ac * (e * e)) - 3.0);
        sp1C = (f32) ((f64) len_ac * e);
        len_ac = sp1C;
    }
    data->len1 = len_ac;

    len_bc = data->len0;
    len_ac = data->len1;

    a2 = len_bc * len_bc;
    b2 = len_ab * len_ab;
    two_a = 2.0f * len_bc;
    c2 = len_ac * len_ac;

    sum_len = (10.0f * (len_bc + len_ac)) / 11.0f;
    if (len_ab > sum_len) {
        len_ab = ((11.0f * sum_len) / 10.0f) +
                 (-(sum_len * (sum_len * (sum_len * (sum_len *
                   (sum_len * (sum_len * (sum_len * (sum_len *
                   (sum_len * (sum_len * sum_len)))))))))) /
                  (10.0f * (len_ab * (len_ab * (len_ab * (len_ab *
                   (len_ab * (len_ab * (len_ab * (len_ab *
                   (len_ab * len_ab)))))))))));
    }

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
    rem = (f32) (3.141592653589793 - (f64) acos2);
    if (rem < 0.1745329201221466f) {
        acos2 = (f32) (2.9670597334676465 +
                (f64) (f32) ((f64) (f32) (fabs((f64) rem) /
                0.1745329201221466) *
                ((f64) acos2 - 2.9670597334676465)));
    }

    fn_8002113C(data->jobj0, &axis, acos1 - angle1);
    fn_8002113C(data->jobj1, &axis, acos2 - angle2);
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

static void lbBgFlash_80021A10(f32 arg8)
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
    int color;
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
