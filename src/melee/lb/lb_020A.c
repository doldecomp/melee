/**
 * @file lb_020A.c
 * @brief Skeletal transform and two-joint IK utilities.
 *
 * Accumulates a joint's world transform by walking its parents, applies
 * rotations about an arbitrary axis, and solves the two-bone IK chain used to
 * plant a fighter's legs on the ground.
 */

#include "lb_020A.h"

#include <placeholder.h>

#include "ft/types.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/quatlib.h>
#include <melee/lb/lbvector.h>

static inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

#ifdef MUST_MATCH
#pragma inline_depth(1)
#endif
void fn_80020AEC(HSD_JObj* jobj, Mtx out)
{
    HSD_JObj* cur;
    s32 i;
    Mtx tmp;
    Vec3 col;
    volatile f32 scale_mag;
    u8 _[4];

    HSD_MtxInverseConcat(HSD_JObjGetMtxPtr(jobj_parent(jobj)),
                         HSD_JObjGetMtxPtr(jobj), out);

    for (i = 0; i < 3; i++) {
        f32 mag;
        f32 scale_sq;
        f32 factor;

        col.x = out[0][i];
        col.y = out[1][i];
        col.z = out[2][i];

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
        out[0][i] = col.x;
        out[1][i] = col.y;
        out[2][i] = col.z;
    }

    cur = jobj_parent(jobj);
    while (cur != NULL) {
        if (jobj_parent(cur) != NULL) {
            HSD_MtxInverseConcat(HSD_JObjGetMtxPtr(jobj_parent(cur)),
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

        PSMTXConcat(tmp, out, out);
        cur = jobj_parent(cur);
    }
}
#ifdef MUST_MATCH
#pragma inline_depth(8)
#endif
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
    z_col_x = SQ(z_col_x) + SQ(z_col_y);
    mag_sq = z_col_x;
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

static inline f32 calc_acos(f32 value)
{
    return acosf(value);
}

static inline f32 sqrtf_store(f32 x, volatile f32* y)
{
    if (x > 0.0f) {
        f64 guess = __frsqrte((f64) x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = (f32) (x * guess);
        return *y;
    }
    return x;
}

void lbBgFlash_80021410(IKState* data)
{
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
    f32 ten;
    f32 eleven;
    f32 acos1;
    f32 acos2;
    f64 rem;
    f32 dx;
    f32 dz;
    f32 dy;
    f64 pi;
    Vec3* pDiff;
    PAD_STACK(8);

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
                ((nx * data->pos1.x) + (data->pos1.y * ny)));

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
    sin_val = sqrtf_store(1.0f - (dot * dot), &sin_mag);
    data->len0 = data->len0 * sin_val;

    lbVector_Diff(&data->pos4, &data->pos0, &temp_delta);
    lbVector_Diff(&data->pos1, &data->pos0, &pos1_from_pos0);
    angle1 = lbVector_Angle(&temp_delta, &pos1_from_pos0);

    lbVector_Diff(&data->pos2, &data->pos1, &temp_delta);
    angle2 = (f32) ((pi = 3.141592653589793) -
                    lbVector_Angle(&temp_delta, &pos1_from_pos0));

    dx = data->pos0.x - data->pos4.x;
    dz = data->pos0.z;
    dz -= data->pos4.z;
    {
        f32 y = data->pos0.y - data->pos4.y;
        dy = y;
    }
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_ab = sqrtf_store(dz + (dx + dy), &len_ab_mag);

    dx = data->pos0.x - data->pos1.x;
    dz = data->pos0.z;
    dz -= data->pos1.z;
    dy = data->pos0.y - data->pos1.y;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_bc = sqrtf_store(dz + (dx + dy), &len_bc_mag);
    data->len0 = len_bc;

    dx = data->pos1.x - data->pos3.x;
    dz = data->pos1.z;
    dz -= data->pos3.z;
    dy = data->pos1.y - data->pos3.y;
    dx *= dx;
    dy *= dy;
    dz *= dz;
    len_ac = sqrtf_store(dz + (dx + dy), &len_ac_mag);
    data->len1 = len_ac;

    sum_len = ((ten = 10.0f) * ((len_bc = data->len0) + (len_ac = data->len1))) /
              (eleven = 11.0f);
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
        len_ab = ((eleven * sum_len) / ten) + (-sum_pow / (ten * len_pow));
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

    acos1 = calc_acos(cos1);
    acos2 = calc_acos(cos2);
    rem = 3.141592653589793 - (f64) acos2;
    if (rem < 0.1745329201221466) {
        f32 ratio = (f32) (fabs(rem) / 0.1745329201221466);
        acos2 = (f32) (2.9670597334676465 +
                       (f64) (f32) ((f64) ratio *
                                    ((f64) acos2 - 2.9670597334676465)));
    }

    acos1 -= angle1;
    acos2 -= angle2;
    fn_8002113C(data->jobj0, &axis, acos1);
    fn_8002113C(data->jobj1, &axis, acos2);
}
