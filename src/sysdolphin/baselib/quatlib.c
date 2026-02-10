#include "quatlib.h"

#include <placeholder.h>

#include <MSL/math.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

/// @todo Currently 95.55% match - stack frame 8 bytes too large (80 vs 72)
s32 MatToQuat(Mtx m, Quaternion* q)
{
    int nxt[] = { 1, 2, 0 };
    f32 lenCol[3];
    f32 q3[3];
    f32 tr;
    f32 s;
    f32 sc0;
    f32 sc1;
    f32 sc2;
    int i;
    int j;
    int k;

    lenCol[0] = sqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0] +
                       m[2][0] * m[2][0]);
    lenCol[1] = sqrtf(m[0][1] * m[0][1] + m[1][1] * m[1][1] +
                       m[2][1] * m[2][1]);
    lenCol[2] = sqrtf(m[0][2] * m[0][2] + m[1][2] * m[1][2] +
                       m[2][2] * m[2][2]);

    sc0 = m[0][0] / lenCol[0];
    sc1 = m[1][1] / lenCol[1];
    sc2 = m[2][2] / lenCol[2];

    tr = sc0 + sc1 + sc2;

    if (tr > 0.0F) {
        s = sqrtf(1.0F + tr);
        q->w = 0.5F * s;
        sc0 = 0.5F / s;
        q->x = sc0 * ((m[2][1] / lenCol[1]) - (m[1][2] / lenCol[2]));
        q->y = sc0 * ((m[0][2] / lenCol[2]) - (m[2][0] / lenCol[0]));
        q->z = sc0 * ((m[1][0] / lenCol[0]) - (m[0][1] / lenCol[1]));
    } else {
        i = 0;
        if (sc1 > sc0) {
            i = 1;
        }
        if (sc2 > m[i][i] / lenCol[i]) {
            i = 2;
        }
        j = nxt[i];
        k = nxt[j];

        s = sqrtf(1.0F + ((m[i][i] / lenCol[i]) - (m[j][j] / lenCol[j])) -
                  (m[k][k] / lenCol[k]));
        sc0 = 0.5F / s;
        q3[i] = 0.5F * s;
        q->w = sc0 * ((m[k][j] / lenCol[j]) -
                       (m[j][k] / lenCol[k]));
        q3[j] = sc0 * ((m[j][i] / lenCol[i]) +
                        (m[i][j] / lenCol[j]));
        q3[k] = sc0 * ((m[k][i] / lenCol[i]) +
                        (m[i][k] / lenCol[k]));
        q->x = q3[0];
        q->y = q3[1];
        q->z = q3[2];
    }

    return 0;
}

s32 HSD_QuatLib_8037EB28(Mtx m, Vec3* euler)
{
    f32 len;

    len = sqrtf(m[0][0] * m[0][0] + m[1][0] * m[1][0]);
    if (len > 1e-05) {
        euler->x = atan2f(m[2][1], m[2][2]);
        euler->y = atan2f(-m[2][0], len);
        euler->z = atan2f(m[1][0], m[0][0]);
    } else {
        euler->x = atan2f(-m[1][2], m[1][1]);
        euler->y = atan2f(-m[2][0], len);
        euler->z = 0.0F;
    }

    return 0;
}

/// @todo Currently 87.16% match - temp register allocation (f3/f5, f4/f6
/// swapped) likely due to mwcc scheduler behavior
s32 HSD_QuatLib_8037EC4C(Quaternion* p, Quaternion* q, Quaternion* out)
{
    f32 py;
    f32 qx;
    f32 qy;
    f32 px;
    f32 qz;
    f32 pw;
    f32 pz;
    f32 qw;

    pw = p->w;
    qy = q->y;
    qx = q->x;
    py = p->y;
    pz = p->z;
    px = p->x;
    qz = q->z;
    qw = q->w;

    out->x = qw * px + pw * qx + (py * qz - qy * pz);
    out->y = qw * py + pw * qy + (qx * pz - px * qz);
    out->z = qw * pz + pw * qz + (px * qy - qx * py);
    out->w = pw * qw - (pz * qz + (px * qx + py * qy));

    PAD_STACK(24);
    return 0;
}

s32 HSD_QuatLib_8037ECE0(Vec3* axis, Quaternion* q, f32 angle)
{
    f32 len;
    f32 half_angle;
    f32 inv_len;
    f32 s;

    len = sqrtf(axis->x * axis->x + axis->y * axis->y + axis->z * axis->z);
    if (__fabsf(len) < 1.1754944E-38F) {
        return -1;
    }
    inv_len = 1.0F / len;
    half_angle = 0.5F * angle;
    q->w = cosf(half_angle);
    s = sinf(half_angle);
    q->x = s * (inv_len * axis->x);
    q->y = s * (inv_len * axis->y);
    q->z = s * (inv_len * axis->z);

    return 0;
}

s32 EulerToQuat(Vec3* euler, Quaternion* q)
{
    f32 cx;
    f32 cy;
    f32 cz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 cc;
    f32 ss;

    cx = cosf(0.5F * euler->x);
    cy = cosf(0.5F * euler->y);
    cz = cosf(0.5F * euler->z);
    sx = sinf(0.5F * euler->x);
    sy = sinf(0.5F * euler->y);
    sz = sinf(0.5F * euler->z);

    ss = sy * sz;
    cc = cy * cz;
    q->w = cx * cc + sx * ss;
    q->x = sx * cc - cx * ss;
    q->y = cz * (cx * sy) + sz * (sx * cy);
    q->z = sz * (cx * cy) - cz * (sx * sy);

    return 0;
}

s32 HSD_QuatLib_8037EF28(Quaternion* p, Quaternion* q, Quaternion* out,
                         f32 t)
{
    f32 cosom;
    f32 t2;
    f32 theta;
    f32 sinom;
    f32 sp;
    f32 sq;

    cosom = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;

    if ((1.0F + cosom) > 1e-10F) {
        if ((1.0F - cosom) > 1e-10F) {
            theta = acosf(cosom);
            sinom = sinf(theta);
            sp = sinf((1.0F - t) * theta) / sinom;
            sq = sinf(t * theta) / sinom;
        } else {
            sq = t;
            sp = (f32) (1.0 - (f64) t);
        }
        out->x = sp * p->x + sq * q->x;
        out->y = sp * p->y + sq * q->y;
        out->z = sp * p->z + sq * q->z;
        out->w = sp * p->w + sq * q->w;
    } else {
        out->x = -p->y;
        out->y = p->x;
        out->z = -p->w;
        out->w = p->z;

        if (t < 0.5F) {
            t2 = 2.0F * t;
            sp = sinf((f32) (M_PI_2 * (1.0F - t2)));
            sq = sinf((f32) (M_PI_2 * t2));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        } else {
            t -= 0.5F;
            t2 = 2.0F * t;
            sp = sinf((f32) (M_PI_2 * (1.0F - t2)));
            sq = sinf((f32) (M_PI_2 * t2));
            out->x = sp * p->x + sq * q->x;
            out->y = sp * p->y + sq * q->y;
            out->z = sp * p->z + sq * q->z;
            out->w = sp * p->w + sq * q->w;
        }
    }

    return 0;
}
