#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
#include "lb/forward.h"

#include "lbcollision.h"

#include "lb_00B0.h"
#include "lbaudio_ax.h"
#include "lbvector.h"

#include "lb/types.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/particle.h>
#include <MetroTRK/intrinsics.h>

/* 006E58 */ static bool lbColl_80006E58(Vec3* arg0, Vec3* arg1, Vec3* arg2,
                                         Vec3* arg3, Vec3* arg4, Vec3* arg5,
                                         MtxPtr arg6, Vec3* arg7, float* arg8,
                                         float scl, float arg10, float arg11);

// .sdata
extern char lbColl_804D3700[8];
extern char lbColl_804D3708[8];
extern int lbColl_804D36D4;
extern int lbColl_804D36D8;

// .sdata2
float const lbColl_804D79F0 = 1e-5;
float const lbColl_804D79F4 = -1e-5;
float const lbColl_804D79F8 = 0;
f64 const lbColl_804D7A00 = 1;
float const lbColl_804D7A08 = 1;
f64 const lbColl_804D7A10 = 0;
f64 const lbColl_804D7A18 = 0.5;
f64 const lbColl_804D7A20 = 3.0;
float const lbColl_804D7A28 = 2;
float const lbColl_804D7A2C = 4;
float const lbColl_804D7A30 = M_PI;
float const lbColl_804D7A34 = 20;
float const lbColl_804D7A38 = 3;
float const lbColl_804D7A3C = 0.5;
float const lbColl_804D7A40 = 5;

// .data
int lbColl_803B9880[] = {
    0x00083D60, 0x00083D60, 0x00083D60, 0x0000005B, 0x0000005A, 0x00000059,
    0x00000058, 0x00000057, 0x00000056, 0x0000006F, 0x00000070, 0x00000071,
    0x00000054, 0x00000054, 0x00000054, 0x0000005A, 0x00000059, 0x000000DF,
    0x000000E1, 0x000000E1, 0x000000E1, 0x00000062, 0x00000063, 0x00000064,
    0x00000065, 0x00000066, 0x00000067, 0x0004461B, 0x0004461B, 0x0004461B,
    0x000000F1, 0x000000F1, 0x000000F1, 0x0000005E, 0x0000005D, 0x0000005C,
    0x00035BAF, 0x00035BB2, 0x00035BB5, 0x00083D60, 0x00083D60, 0x0000020D,
};
extern struct unk {
    u8* pad;
    GXColor* pad_x;
} lbColl_803B9928[];

// .text

int lbColl_80005BB0(HitCapsule* arg0, int arg1)
{
    u32 temp_r0;
    u32 temp_r6;

    temp_r0 = arg0->sfx_kind;
    if (temp_r0 == 0xD) {
        temp_r6 = arg0->sfx_severity;
        if (temp_r6 == 2) {
            return lbAudioAx_80024184(
                *(lbColl_803B9880 + (temp_r0 * 3) + (temp_r6)), 127, 64, arg1);
        }
    }

    return lbAudioAx_80024184(
        *(lbColl_803B9880 + (temp_r0 * 3) + (arg0->sfx_severity)), 127, 64,
        -1);
}

void vector_sub(Vec3* a, Vec3* b, Vec3* result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}

static inline bool between(float x, float lo, float hi)
{
    if (x < hi && x > lo) {
        return true;
    } else {
        return false;
    }
}

static inline bool nearzero(float x)
{
    if (x < 1e-5F && x > -1e-5F) {
        return true;
    } else {
        return false;
    }
}

bool lbColl_80005C44(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2, Vec3* arg3, float arg8,
                    float arg9)
{
    float temp_f2;
    float tmp_x;
    float scale;
    Vec3 d1;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 d2;
    float d1_dot_d1;
    float d1_dot_d2;

    temp_f2 = arg8 + arg9;
    sp38 = *arg0;
    sp2C = *arg2;

    tmp_x = arg1->x;

    if (sp38.x > arg1->x) {
        if (sp38.x  + temp_f2 < sp2C.x) return 0;
        if (arg1->x - temp_f2 > sp2C.x) return 0;
    } else {
        if (sp38.x  - temp_f2 > sp2C.x) return 0;
        if (arg1->x + temp_f2 < sp2C.x) return 0;
    }
    if (sp38.y > arg1->y) {
        if (sp38.y  + temp_f2 < sp2C.y) return 0;
        if (arg1->y - temp_f2 > sp2C.y) return 0;
    } else {
        if (sp38.y  - temp_f2 > sp2C.y) return 0;
        if (arg1->y + temp_f2 < sp2C.y) return 0;
    }
    if (sp38.z > arg1->z) {
        if (sp38.z  + temp_f2 < sp2C.z) return 0;
        if (arg1->z - temp_f2 > sp2C.z) return 0;
    } else {
        if (sp38.z  - temp_f2 > sp2C.z) return 0;
        if (arg1->z + temp_f2 < sp2C.z) return 0;
    }

    d1.x = arg1->x - sp38.x;
    d1.y = arg1->y - sp38.y;
    d1.z = arg1->z - sp38.z;

    d2.x = sp38.x - sp2C.x;
    d2.y = sp38.y - sp2C.y;
    d2.z = sp38.z - sp2C.z;

    d1_dot_d1 = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
    d1_dot_d2 = d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;

    if (between(d1_dot_d1, -1e-5, 1e-5)) {
        scale = 0.0;
    } else {
        scale = -d1_dot_d2 / d1_dot_d1;
        if (scale > 1.0) {
            scale = 1.0;
        } else if (scale < 0.0) {
            scale = 0.0;
        }
    }

    arg3->x = d1.x * scale + sp38.x;
    arg3->y = d1.y * scale + sp38.y;
    arg3->z = d1.z * scale + sp38.z;

    d2.x = arg3->x - sp2C.x;
    d2.y = arg3->y - sp2C.y;
    d2.z = arg3->z - sp2C.z;

    if (tmp_x * tmp_x < d2.x * d2.x + d2.y * d2.y + d2.z * d2.z) {
        return false;
    } else {
        return true;
    }
}

float lbColl_80005EBC(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2, float* arg3)
{
    Vec3 sp50;
    Vec3 d1;
    Vec3 sp38;
    Vec3 d2;
    float scale;
    float d1_dot_d1;
    float d1_dot_d2;
    float x;
    float y;
    float z;

    sp50 = *arg0;
    d1.x = arg1->x - arg0->x;
    d1.y = arg1->y - arg0->y;
    d1.z = arg1->z - arg0->z;

    sp38 = *arg2;
    d2.x = sp50.x - sp38.x;
    d2.y = sp50.y - sp38.y;
    d2.z = sp50.z - sp38.z;

    d1_dot_d1 = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
    d1_dot_d2 = d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;

    scale = -d1_dot_d2 / d1_dot_d1;
    if (scale > lbColl_804D7A00) {
        scale = lbColl_804D7A08;
    } else if (scale < lbColl_804D7A10) {
        scale = lbColl_804D79F8;
    }

    x = d1.x * scale + sp50.x - arg2->x;
    y = d1.y * scale + sp50.y - arg2->y;
    z = d1.z * scale + sp50.z - arg2->z;

    *arg3 = scale;
    return x * x + y * y + z * z;
}

float lbColl_80005FC0(Vec3* arg0, Vec3* arg1, Vec3* arg2, float* arg3)
{
    Vec3 sp50;
    Vec3 d1;
    Vec3 sp38;
    Vec3 d2;
    float scale;
    float d1_dot_d1;
    float d1_dot_d2;
    float x;
    float y;
    float z;

    sp50 = *arg0;
    d1.x = arg1->x - arg0->x;
    d1.y = arg1->y - arg0->y;

    sp38 = *arg2;
    d2.x = sp50.x - sp38.x;
    d2.y = sp50.y - sp38.y;

    d1_dot_d1 = d1.x * d1.x + d1.y * d1.y;
    d1_dot_d2 = d1.x * d2.x + d1.y * d2.y;

    scale = -d1_dot_d2 / d1_dot_d1;
    if (scale > lbColl_804D7A00) {
        scale = lbColl_804D7A08;
    } else if (scale < lbColl_804D7A10) {
        scale = lbColl_804D79F8;
    }

    x = d1.x * scale + sp50.x - arg2->x;
    y = d1.y * scale + sp50.y - arg2->y;

    *arg3 = scale;
    return x * x + y * y;
}

inline bool end(Vec3* a, Vec3* b, float unk_sum)
{
    float y = a->y - b->y;
    float x = a->x - b->x;
    float z = a->z - b->z;

    if (unk_sum * unk_sum < z * z + (x * x + y * y)) {
        return false;
    }

    return true;
}

int lbColl_80006094(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, Vec3* arg4,
                    Vec3* arg5, float arg6, float arg7)
{
    {
        Vec3 vec4;
        float sp30;
        float sp34;
        float sp38;
        Vec3 arg4_offset;
        Vec3 arg5_offset;
        float sp3C;
        float temp_f1;
        float unk_sum = arg6 + arg7;
        vec4.x = arg0->x;
        vec4.y = arg0->y;
        vec4.z = arg0->z;

        sp30 = vec4.z;
        sp34 = arg2->x;
        sp38 = arg2->y;

        arg4_offset.x = vec4.x;
        arg4_offset.y = vec4.y;
        arg4_offset.z = vec4.z;

        {
            float temp_r0_2 = arg2->z;
            sp3C = temp_r0_2;

            arg5_offset.x = sp34;
            arg5_offset.y = sp38;
            arg5_offset.z = temp_r0_2;
        }

        {
            float arg1_x = arg1->x;
            if (arg4_offset.x > arg1_x) {
                if (!testPlusX(&arg4_offset, &arg5_offset, arg3, unk_sum)) {
                    return false;
                }

                if (!testMinusX(&arg4_offset, &arg5_offset, arg3, unk_sum)) {
                    return false;
                }

                goto block_13;
            }
            {
                if (!testMinusX(&arg4_offset, &arg5_offset, arg3, unk_sum)) {
                    return false;
                }
            }
            {
                float x = arg1_x + unk_sum;
                if (x < arg5_offset.x && x < arg3->x) {
                    return false;
                }
            }

        block_13: {
            temp_f1 = arg1->y;
            if (arg4_offset.y > temp_f1) {
                {
                    float temp_f3;
                    temp_f3 = arg4_offset.y + unk_sum;

                    if (temp_f3 < arg5_offset.y && temp_f3 < arg3->y) {
                        return false;
                    }
                }

                {
                    float temp_f3_2 = temp_f1 - unk_sum;

                    if (temp_f3_2 > arg5_offset.y && temp_f3_2 > arg3->y) {
                        return false;
                    }
                }

                goto block_26;
            }

            {
                float y = arg4_offset.y - unk_sum;
                if (y > arg5_offset.y && y > arg3->y) {
                    return false;
                }
            }

            {
                float y = temp_f1 + unk_sum;
                if (y < arg5_offset.y && y < arg3->y) {
                    return false;
                }
            }
        }
        block_26: {
            float temp_f2_5 = arg1->z;
            if (arg4_offset.z > temp_f2_5) {
                {
                    float temp_f4;
                    temp_f4 = arg4_offset.z + unk_sum;
                    if ((temp_f4 < arg5_offset.z) && (temp_f4 < arg3->z)) {
                        return false;
                    }
                }
                {
                    float temp_f4_2;
                    temp_f4_2 = temp_f2_5 - unk_sum;
                    if ((temp_f4_2 > arg5_offset.z) && (temp_f4_2 > arg3->z)) {
                        return false;
                    }
                }
                goto block_39;
            }
            {
                float temp_f4_3;
                temp_f4_3 = arg4_offset.z - unk_sum;
                if ((temp_f4_3 > arg5_offset.z) && (temp_f4_3 > arg3->z)) {
                    return false;
                }
            }
            {
                float temp_f4_4;
                temp_f4_4 = temp_f2_5 + unk_sum;
                if ((temp_f4_4 < arg5_offset.z) && (temp_f4_4 < arg3->z)) {
                    return false;
                }
            }
        block_39: {
            float arg4_scl;

            float temp_f25 = temp_f1 - arg4_offset.y;
            float temp_f5 = arg3->y;
            float temp_f24 = temp_f2_5 - arg4_offset.z;
            float temp_f22 = temp_f5 - arg5_offset.y;
            float temp_f13 = arg4_offset.y - arg5_offset.y;
            float temp_f4_5 = arg3->x;
            float temp_f26 = arg1_x - arg4_offset.x;
            float temp_f23 = temp_f4_5 - arg5_offset.x;
            float temp_f6 = arg3->z;
            float arg5_offset_base = temp_f6 - arg5_offset.z;
            float temp_f8 = temp_f24 * arg5_offset_base + temp_f26 * temp_f23 +
                            temp_f25 * temp_f22;
            float temp_f7 = arg5_offset_base * arg5_offset_base +
                            temp_f23 * temp_f23 + temp_f22 * temp_f22;
            float temp_f19 = arg4_offset.x - arg5_offset.x;
            float temp_f3_5 = (temp_f24 * temp_f24) +
                              ((temp_f26 * temp_f26) + (temp_f25 * temp_f25));
            float temp_f13_2 = arg4_offset.z - arg5_offset.z;
            float temp_f12 = arg5_offset_base * temp_f13_2 +
                             temp_f23 * temp_f19 + temp_f22 * temp_f13;
            float temp_f11 = (temp_f24 * temp_f13_2) + temp_f26 * temp_f19 +
                             temp_f25 * temp_f13;
            float temp_f10 = temp_f3_5 * temp_f7 - temp_f8 * temp_f8;

            {
                float arg5_scl;
                if (approximatelyZero(temp_f7)) {
                    if (approximatelyZero(temp_f3_5)) {
                        arg4_scl = 0.0f;
                        arg5_scl = 0.0f;
                    } else {
                        arg5_scl = 0.0f;
                        {
                            float temp_f1_2 = -temp_f11 / temp_f3_5;
                            arg4_scl = temp_f1_2;

                            if (temp_f1_2 > (float) 1.0) {
                                arg4_scl = 1.0f;
                            } else if (arg4_scl < (float) 0.0) {
                                arg4_scl = 0.0f;
                            }
                        }
                    }
                } else {
                    if (approximatelyZero(temp_f10)) {
                        float temp_f9 = (0.5 * temp_f22 + arg5_offset.y);
                        float temp_f7_2 = (0.5 * temp_f23 + arg5_offset.x);
                        float temp_f10_2 = arg4_offset.y - temp_f9;
                        float temp_f11_2 = temp_f1 - temp_f9;
                        float temp_f8_2 =
                            0.5 * arg5_offset_base + arg5_offset.z;
                        float temp_f3_6 = arg4_offset.x - temp_f7_2;
                        float temp_f9_2 = arg1_x - temp_f7_2;
                        float arg4_offset_z = arg4_offset.z - temp_f8_2;
                        float temp_f2_6 = temp_f2_5 - temp_f8_2;

                        // lhs and rhs each the same inline
                        if ((arg4_offset_z * arg4_offset_z +
                             ((temp_f3_6 * temp_f3_6) +
                              (temp_f10_2 * temp_f10_2))) <
                            ((temp_f2_6 * temp_f2_6) +
                             ((temp_f9_2 * temp_f9_2) +
                              (temp_f11_2 * temp_f11_2))))
                        {
                            Vec3 vec2;
                            float sp90;
                            float sp8C;
                            float sp88;
                            float temp_f7_4;
                            float temp_f8_3;
                            float temp_f9_3;
                            vec2.x = sp34;
                            vec2.y = sp38;
                            vec2.z = sp3C;
                            temp_f7_4 = temp_f4_5 - arg2->x;
                            temp_f8_3 = temp_f5 - arg2->y;
                            sp88 = vec4.x;
                            temp_f9_3 = temp_f6 - arg2->z;
                            sp8C = vec4.y;
                            sp90 = sp30;
                            arg4_scl = 0.0f;
                            {
                                float var_f2 =
                                    -((temp_f9_3 * (vec2.z - sp90)) +
                                      ((temp_f7_4 * (vec2.x - sp88)) +
                                       (temp_f8_3 * (vec2.y - sp8C)))) /
                                    ((temp_f9_3 * temp_f9_3) +
                                     ((temp_f7_4 * temp_f7_4) +
                                      (temp_f8_3 * temp_f8_3)));
                                if (var_f2 > (float) 1.0) {
                                    var_f2 = 1.0f;
                                } else if (var_f2 < (float) 0.0) {
                                    var_f2 = 0.0f;
                                }
                                arg5_scl = var_f2;
                            }
                        } else {
                            float sp58;
                            float sp60;
                            float sp48;
                            float sp5C;
                            float sp44;
                            float sp40;
                            float temp_f10_3;
                            float temp_f11_3;
                            float temp_f9_4;
                            sp40 = sp34;
                            sp44 = sp38;
                            sp48 = sp3C;
                            arg4_scl = 1.0f;
                            temp_f9_4 = temp_f4_5 - arg2->x;
                            temp_f10_3 = temp_f5 - arg2->y;
                            sp58 = arg1->x;
                            temp_f11_3 = temp_f6 - arg2->z;
                            sp5C = arg1->y;
                            sp60 = arg1->z;
                            {
                                float var_f2_2 =
                                    -temp_f11_3 * (sp48 - sp60) +
                                    temp_f9_4 * sp40 - sp58 +
                                    temp_f10_3 * sp44 -
                                    sp5C / (temp_f11_3 * temp_f11_3) +
                                    temp_f9_4 * temp_f9_4 +
                                    temp_f10_3 * temp_f10_3;

                                if (var_f2_2 > (float) 1.0) {
                                    var_f2_2 = 1.0f;
                                } else if (var_f2_2 < (float) 0.0) {
                                    var_f2_2 = 0.0f;
                                }

                                arg5_scl = var_f2_2;
                            }
                        }
                    } else {
                        float temp_f1_3 =
                            temp_f8 * temp_f12 - temp_f7 * temp_f11 / temp_f10;
                        arg5_scl =
                            ((temp_f3_5 * temp_f12) - (temp_f8 * temp_f11)) /
                            temp_f10;
                        arg4_scl = temp_f1_3;
                        if (temp_f1_3 > (float) 1.0 ||
                            arg4_scl < (float) 0.0 || arg5_scl > (float) 1.0 ||
                            arg5_scl < (float) 0.0)
                        {
                            float var_f18;
                            float var_f19;
                            float var_f1;
                            float spA4;

                            if (arg4_scl < (float) 0.0) {
                                var_f19 = 0.0f;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg0, &spA4);
                            } else {
                                var_f19 = 1.0f;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg1, &spA4);
                            }

                            {
                                float spA0;
                                if (arg5_scl < (float) 0.0) {
                                    arg5_scl = 0.0f;
                                    var_f1 = lbColl_80005EBC(arg0, arg1, arg2,
                                                             &spA0);
                                } else {
                                    arg5_scl = 1.0f;
                                    var_f1 = lbColl_80005EBC(arg0, arg1, arg3,
                                                             &spA0);
                                }

                                if (var_f18 < var_f1) {
                                    arg4_scl = var_f19;
                                    arg5_scl = spA4;
                                } else {
                                    arg4_scl = spA0;
                                }
                            }
                        }
                    }
                }

                arg4->x = temp_f26 * arg4_scl + arg4_offset.x;
                arg4->y = temp_f25 * arg4_scl + arg4_offset.y;
                arg4->z = temp_f24 * arg4_scl + arg4_offset.z;

                arg5->x = temp_f23 * arg5_scl + arg5_offset.x;
                arg5->y = temp_f22 * arg5_scl + arg5_offset.y;
                arg5->z = arg5_offset_base * arg5_scl + arg5_offset.z;
            }
        }
            return end(arg4, arg5, unk_sum);
        }
        }
    }
}

bool lbColl_800067F8(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* e, Vec3* f,
                     float p, float q, float r)
{
    float sum_pq = p + q;

    float a_z;
    Vec3 a0;
    Vec3 a1;

    a0.x = a->x;
    a0.y = a->y;
    a0.z = a_z = a->z;
    a1.x = a0.x;
    a1.y = a0.y;
    a1.z = a_z;
    {
        Vec3 c0;
        float temp_r0_2;

        c0.x = c->x;
        c0.y = c->y;
        c0.z = temp_r0_2 = c->z;

        {
            Vec3 c1;

            c1.x = c0.x;
            c1.y = c0.y;
            c1.z = temp_r0_2;
            {
                float b_x = b->x;
                if (a1.x > b_x) {
                    {
                        float x = a1.x + sum_pq;
                        if (x < c1.x && x < d->x) {
                            return false;
                        }
                    }

                    {
                        float x = b_x - sum_pq;
                        if ((x > c1.x) && (x > d->x)) {
                            return false;
                        }
                    }

                } else {
                    {
                        float x = a1.x - sum_pq;
                        if (x > c1.x && x > d->x) {
                            return false;
                        }
                    }

                    {
                        float temp_f2_4 = b_x + sum_pq;
                        if (temp_f2_4 < c1.x && temp_f2_4 < d->x) {
                            return false;
                        }
                    }
                }

                {
                    float b_y = b->y;
                    if (a1.y > b_y) {
                        {
                            float y;
                            y = a1.y + sum_pq;
                            if (y < c1.y && y < d->y) {
                                return false;
                            }
                        }
                        {
                            float y = b_y - sum_pq;
                            if (y > c1.y && y > d->y) {
                                return false;
                            }
                        }

                    } else {
                        {
                            float y = a1.y - sum_pq;
                            if (y > c1.y && y > d->y) {
                                return false;
                            }
                        }
                        {
                            float y = b_y + sum_pq;
                            if (y < c1.y && y < d->y) {
                                return false;
                            }
                        }
                    }

                    {
                        float diff_ba_y = b_y - a1.y;
                        float d_y = d->y;
                        float diff_ac_y = a1.y - c1.y;
                        float diff_dc_y = d_y - c1.y;
                        float diff_ba_x = b_x - a1.x;
                        float d_x = d->x;
                        float diff_dc_x = d_x - c1.x;

                        float dot2_diff_ba_dc =
                            diff_ba_x * diff_dc_x + diff_ba_y * diff_dc_y;

                        float sqdist2_dc =
                            diff_dc_x * diff_dc_x + diff_dc_y * diff_dc_y;
                        float sqdist2_ba =
                            diff_ba_x * diff_ba_x + diff_ba_y * diff_ba_y;
                        float diff_ac_x = a1.x - c1.x;

                        float dot2_diff_dc_ac =
                            diff_dc_x * diff_ac_x + diff_dc_y * diff_ac_y;

                        float dot2_diff_ba_ac =
                            diff_ba_x * diff_ac_x + diff_ba_y * diff_ac_y;

                        float determinant = sqdist2_ba * sqdist2_dc -
                                            dot2_diff_ba_dc * dot2_diff_ba_dc;

                        {
                            float scl_e;
                            float scl_f;
                            if (approximatelyZero(sqdist2_dc)) {
                                if (approximatelyZero(sqdist2_ba)) {
                                    scl_e = 0.0f;
                                    scl_f = 0.0f;
                                } else {
                                    float temp_f1_2;
                                    scl_f = 0.0f;
                                    temp_f1_2 = -dot2_diff_ba_ac / sqdist2_ba;
                                    scl_e = temp_f1_2;
                                    if (temp_f1_2 > (float) 1.0) {
                                        scl_e = 1.0f;
                                    } else if (scl_e < (float) 0.0) {
                                        scl_e = 0.0f;
                                    }
                                }
                            } else if (approximatelyZero(determinant)) {
                                float temp_f7_2 = 0.5 * diff_dc_y + c1.y;
                                float temp_f5_2 = 0.5 * diff_dc_x + c1.x;
                                float temp_f6_2 = a1.y - temp_f7_2;
                                float temp_f7_3 = b_y - temp_f7_2;
                                {
                                    float temp_scl_f;
                                    float f4 = a1.x - temp_f5_2;
                                    float temp_f5_3 = b_x - temp_f5_2;
                                    if ((f4 * f4 + temp_f6_2 * temp_f6_2) <
                                        (temp_f5_3 * temp_f5_3 +
                                         temp_f7_3 * temp_f7_3))
                                    {
                                        float diff_dc_x;
                                        float temp_f8_2;
                                        Vec3 c3;
                                        c3.x = c0.x;
                                        c3.y = c0.y;
                                        c3.z = c0.z;
                                        diff_dc_x = d_x - c->x;
                                        temp_f8_2 = d_y - c->y;
                                        {
                                            {
                                                Vec3 a2;
                                                float diff_dc_z;
                                                a2.x = a0.x;
                                                diff_dc_z = d->z - c->z;
                                                a2.y = a0.y;
                                                a2.z = a0.z;
                                                scl_e = 0.0f;
                                                temp_scl_f =
                                                    -(diff_dc_z *
                                                      (c3.z - a2.z)) +
                                                    ((diff_dc_x *
                                                      (c3.x - a2.x)) +
                                                     (temp_f8_2 *
                                                      (c3.y - a2.y))) /
                                                        ((diff_dc_z *
                                                          diff_dc_z) +
                                                         ((diff_dc_x *
                                                           diff_dc_x) +
                                                          (temp_f8_2 *
                                                           temp_f8_2)));
                                            }
                                        }
                                        if (temp_scl_f > (float) 1.0) {
                                            temp_scl_f = 1.0f;
                                        } else if (temp_scl_f < (float) 0.0) {
                                            temp_scl_f = 0.0f;
                                        }
                                        scl_f = temp_scl_f;
                                    } else {
                                        Vec3 c2;

                                        c2.x = c0.x;
                                        c2.y = c0.y;
                                        c2.z = c0.z;
                                        {
                                            float diff_dc_x1;
                                            scl_e = 1.0f;
                                            diff_dc_x1 = d_x - c->x;
                                            {
                                                float diff_dc_y1;
                                                float diff_dc_z1;
                                                diff_dc_y1 = d_y - c->y;
                                                diff_dc_z1 = d->z - c->z;
                                                {
                                                    Vec3 b0;

                                                    b0.x = b->x;
                                                    b0.y = b->y;
                                                    b0.z = b->z;
                                                    {
                                                        float var_f2_2 =
                                                            -(diff_dc_z1 *
                                                                  (c2.z -
                                                                   b0.z) +
                                                              ((diff_dc_x1 *
                                                                (c2.x -
                                                                 b0.x)) +
                                                               (diff_dc_y1 *
                                                                (c2.y -
                                                                 b0.y)))) /
                                                            ((diff_dc_z1 *
                                                              diff_dc_z1) +
                                                             ((diff_dc_x1 *
                                                               diff_dc_x1) +
                                                              (diff_dc_y1 *
                                                               diff_dc_y1)));
                                                        if (var_f2_2 >
                                                            (float) 1.0)
                                                        {
                                                            var_f2_2 = 1.0f;
                                                        } else if (var_f2_2 <
                                                                   (float) 0.0)
                                                        {
                                                            var_f2_2 = 0.0f;
                                                        }
                                                        scl_f = var_f2_2;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                float temp_f1_3 =
                                    ((dot2_diff_ba_dc * dot2_diff_dc_ac) -
                                     (sqdist2_dc * dot2_diff_ba_ac)) /
                                    determinant;
                                scl_f = ((sqdist2_ba * dot2_diff_dc_ac) -
                                         (dot2_diff_ba_dc * dot2_diff_ba_ac)) /
                                        determinant;
                                scl_e = temp_f1_3;
                                if ((temp_f1_3 > (float) 1.0) ||
                                    (scl_e < (float) 0.0) ||
                                    (scl_f > (float) 1.0) ||
                                    (scl_f < (float) 0.0))
                                {
                                    float out0;
                                    float temp_scl_e;
                                    float result0;
                                    {
                                        if (scl_e < (float) 0.0) {
                                            temp_scl_e = 0.0f;
                                            result0 = lbColl_80005FC0(c, d, a,
                                                                      &out0);
                                        } else {
                                            temp_scl_e = 1.0f;
                                            result0 = lbColl_80005FC0(c, d, b,
                                                                      &out0);
                                        }
                                    }
                                    {
                                        float result1;
                                        float out1;
                                        if (scl_f < (float) 0.0) {
                                            scl_f = 0.0f;
                                            result1 = lbColl_80005FC0(a, b, c,
                                                                      &out1);
                                        } else {
                                            scl_f = 1.0f;
                                            result1 = lbColl_80005FC0(a, b, d,
                                                                      &out1);
                                        }

                                        if (result0 < result1) {
                                            scl_e = temp_scl_e;
                                            scl_f = out0;
                                        } else {
                                            scl_e = out1;
                                        }
                                    }
                                }
                            }

                            e->x = diff_ba_x * scl_e + a1.x;
                            e->y = diff_ba_y * scl_e + a1.y;
                            e->z = 0.0f;

                            f->x = diff_dc_x * scl_f + c1.x;
                            f->y = diff_dc_y * scl_f + c1.y;
                            f->z = 0.0f;
                        }
                    }
                }
            }
        }
    }
    {
        float diff_ef_y;
        float diff_ef_x;
        diff_ef_y = e->y - f->y;
        diff_ef_x = e->x - f->x;
        if (sum_pq * sum_pq < diff_ef_x * diff_ef_x + (diff_ef_y * diff_ef_y))
        {
            return false;
        }
        return true;
    }
}

bool lbColl_80006E58(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3,
                     Vec3* arg4, Vec3* arg5, MtxPtr arg6, Vec3* arg7,
                     float* arg8, float scl, float arg10, float arg11)
{
    float sp124;
    float sp120;
    float sp11C;
    float sp118;
    float sp114;
    float sp110;
    float sp10C;
    float sp108;
    float sp104;
    float spD0;
    float spCC;
    float sp8C;
    float sp88;
    float sp84;
    float sp74;
    float sp70;
    float sp6C;
    float sp5C;
    float sp58;
    float sp54;
    float sp44;
    float sp40;
    float sp3C;
    float sp38;
    float sp34;
    float temp_f0;
    float temp_f10;
    float temp_f10_2;
    float temp_f10_3;
    float temp_f10_4;
    float temp_f11;
    float temp_f11_2;
    float temp_f11_3;
    float temp_f11_4;
    float temp_f11_5;
    float temp_f12;
    float temp_f1;
    float temp_f1_10;
    float temp_f1_14;
    float temp_f1_15;
    float temp_f1_16;
    float temp_f1_17;
    float temp_f1_2;
    float temp_f1_3;
    float temp_f1_4;
    float temp_f1_5;
    float temp_f1_9;
    float temp_f20;
    float temp_f21;
    float temp_f21_2;
    float temp_f25;
    float temp_f26;
    float temp_f27;
    float temp_f2;
    float temp_f2_2;
    float temp_f2_3;
    float temp_f2_4;
    float temp_f2_5;
    float temp_f2_6;
    float temp_f2_7;
    float temp_f2_8;
    float temp_f3;
    float temp_f3_2;
    float temp_f3_3;
    float temp_f4;
    float temp_f4_10;
    float temp_f4_2;
    float temp_f4_3;
    float temp_f4_4;
    float temp_f4_5;
    float temp_f4_6;
    float temp_f4_7;
    float temp_f4_8;
    float temp_f4_9;
    float temp_f5;
    float temp_f5_2;
    float temp_f5_3;
    float temp_f6;
    float temp_f6_2;
    float temp_f6_3;
    float temp_f6_4;
    float temp_f7;
    float temp_f7_2;
    float temp_f8;
    float temp_f9;
    float temp_f9_2;
    float temp_f9_3;
    float temp_f9_4;
    float var_f0;
    float var_f1;
    float var_f1_2;
    float var_f20;
    float var_f21;
    float var_f22;
    float var_f24;
    float var_f2;
    float var_f2_2;
    float var_f30;
    f64 temp_f1_11;
    f64 temp_f1_12;
    f64 temp_f1_13;
    f64 temp_f1_6;
    f64 temp_f1_7;
    f64 temp_f1_8;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;

    temp_f3 = (arg10 * arg11) + scl;
    sp11C = arg0->x;
    sp120 = arg0->y;
    sp124 = arg0->z;
    sp110 = arg2->x;
    sp114 = arg2->y;
    sp118 = arg2->z;
    temp_f5 = arg1->x;
    if (sp11C > temp_f5) {
        temp_f2 = sp11C + temp_f3;
        if ((temp_f2 < sp110) && (temp_f2 < arg3->x)) {
            return 0;
        }
        temp_f2_2 = temp_f5 - temp_f3;
        if ((temp_f2_2 > sp110) && (temp_f2_2 > arg3->x)) {
            return 0;
        }
        goto block_13;
    }
    temp_f2_3 = sp11C - temp_f3;
    if ((temp_f2_3 > sp110) && (temp_f2_3 > arg3->x)) {
        return 0;
    }
    temp_f2_4 = temp_f5 + temp_f3;
    if ((temp_f2_4 < sp110) && (temp_f2_4 < arg3->x)) {
        return 0;
    }
block_13:
    temp_f6 = arg1->y;
    if (sp120 > temp_f6) {
        temp_f4 = sp120 + temp_f3;
        if ((temp_f4 < sp114) && (temp_f4 < arg3->y)) {
            return 0;
        }
        temp_f4_2 = temp_f6 - temp_f3;
        if ((temp_f4_2 > sp114) && (temp_f4_2 > arg3->y)) {
            return 0;
        }
        goto block_26;
    }
    temp_f4_3 = sp120 - temp_f3;
    if ((temp_f4_3 > sp114) && (temp_f4_3 > arg3->y)) {
        return 0;
    }
    temp_f4_4 = temp_f6 + temp_f3;
    if ((temp_f4_4 < sp114) && (temp_f4_4 < arg3->y)) {
        return 0;
    }
block_26:
    temp_f7 = arg1->z;
    if (sp124 > temp_f7) {
        temp_f6_2 = sp124 + temp_f3;
        if ((temp_f6_2 < sp118) && (temp_f6_2 < arg3->z)) {
            return 0;
        }
        temp_f4_5 = temp_f7 - temp_f3;
        if ((temp_f4_5 > sp118) && (temp_f4_5 > arg3->z)) {
            return 0;
        }
        goto block_39;
    }
    temp_f6_3 = sp124 - temp_f3;
    if ((temp_f6_3 > sp118) && (temp_f6_3 > arg3->z)) {
        return 0;
    }
    temp_f4_6 = temp_f7 + temp_f3;
    if ((temp_f4_6 < sp118) && (temp_f4_6 < arg3->z)) {
        return 0;
    }
block_39:
    temp_f3_2 = temp_f5 - sp11C;
    sp104 = temp_f3_2;
    sp108 = arg1->y - sp120;
    sp10C = arg1->z - sp124;
    temp_f7_2 = arg3->y;
    temp_f21 = sp120 - sp114;
    temp_f26 = temp_f7_2 - sp114;
    temp_f6_4 = arg3->x;
    temp_f27 = temp_f6_4 - sp110;
    temp_f8 = arg3->z;
    temp_f20 = sp11C - sp110;
    temp_f25 = temp_f8 - sp118;
    temp_f10 =
        (sp10C * temp_f25) + ((temp_f3_2 * temp_f27) + (sp108 * temp_f26));
    temp_f9 = (temp_f25 * temp_f25) +
              ((temp_f27 * temp_f27) + (temp_f26 * temp_f26));
    temp_f21_2 = sp124 - sp118;
    temp_f5_2 = (sp10C * sp10C) + ((temp_f3_2 * temp_f3_2) + (sp108 * sp108));
    temp_f4_7 =
        (sp10C * temp_f21_2) + ((temp_f3_2 * temp_f20) + (sp108 * temp_f21));
    temp_f11 = (temp_f25 * temp_f21_2) +
               ((temp_f27 * temp_f20) + (temp_f26 * temp_f21));
    temp_f12 = (temp_f5_2 * temp_f9) - (temp_f10 * temp_f10);
    if ((temp_f9 < lbColl_804D79F0) && (temp_f9 > lbColl_804D79F4)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        if ((temp_f5_2 < lbColl_804D79F0) && (temp_f5_2 > lbColl_804D79F4)) {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            var_f0 = lbColl_804D79F8;
            var_f24 = var_f0;
        } else {
            var_f24 = lbColl_804D79F8;
            temp_f1 = -temp_f4_7 / temp_f5_2;
            var_f0 = temp_f1;
            if (temp_f1 > (float) lbColl_804D7A00) {
                var_f0 = lbColl_804D7A08;
            } else if (var_f0 < (float) lbColl_804D7A10) {
                var_f0 = var_f24;
            }
        }
    } else {
        if ((temp_f12 < lbColl_804D79F0) && (temp_f12 > lbColl_804D79F4)) {
            var_r0_3 = 1;
        } else {
            var_r0_3 = 0;
        }
        if (var_r0_3 != 0) {
            temp_f11_2 =
                (float) ((lbColl_804D7A18 * (f64) temp_f26) + (f64) sp114);
            temp_f10_2 =
                (float) ((lbColl_804D7A18 * (f64) temp_f27) + (f64) sp110);
            temp_f1_2 = sp120 - temp_f11_2;
            temp_f9_2 =
                (float) ((lbColl_804D7A18 * (f64) temp_f25) + (f64) sp118);
            temp_f11_3 = arg1->y - temp_f11_2;
            temp_f4_8 = sp11C - temp_f10_2;
            temp_f5_3 = arg1->x - temp_f10_2;
            temp_f2_5 = sp124 - temp_f9_2;
            temp_f3_3 = arg1->z - temp_f9_2;
            if (((temp_f2_5 * temp_f2_5) +
                 ((temp_f4_8 * temp_f4_8) + (temp_f1_2 * temp_f1_2))) <
                ((temp_f3_3 * temp_f3_3) +
                 ((temp_f5_3 * temp_f5_3) + (temp_f11_3 * temp_f11_3))))
            {
                sp6C = arg2->x;
                var_f0 = lbColl_804D79F8;
                sp70 = arg2->y;
                sp74 = arg2->z;
                temp_f9_3 = temp_f6_4 - arg2->x;
                temp_f10_3 = temp_f7_2 - arg2->y;
                temp_f11_4 = temp_f8 - arg2->z;
                sp84 = arg0->x;
                sp88 = arg0->y;
                sp8C = arg0->z;
                var_f2 =
                    -((temp_f11_4 * (sp74 - sp8C)) +
                      ((temp_f9_3 * (sp6C - sp84)) +
                       (temp_f10_3 * (sp70 - sp88)))) /
                    ((temp_f11_4 * temp_f11_4) +
                     ((temp_f9_3 * temp_f9_3) + (temp_f10_3 * temp_f10_3)));
                if (var_f2 > (float) lbColl_804D7A00) {
                    var_f2 = lbColl_804D7A08;
                } else if (var_f2 < (float) lbColl_804D7A10) {
                    var_f2 = var_f0;
                }
                var_f24 = var_f2;
            } else {
                sp3C = arg2->x;
                var_f0 = lbColl_804D7A08;
                sp40 = arg2->y;
                sp44 = arg2->z;
                temp_f9_4 = temp_f6_4 - arg2->x;
                temp_f10_4 = temp_f7_2 - arg2->y;
                temp_f11_5 = temp_f8 - arg2->z;
                sp54 = arg1->x;
                sp58 = arg1->y;
                sp5C = arg1->z;
                var_f2_2 =
                    -((temp_f11_5 * (sp44 - sp5C)) +
                      ((temp_f9_4 * (sp3C - sp54)) +
                       (temp_f10_4 * (sp40 - sp58)))) /
                    ((temp_f11_5 * temp_f11_5) +
                     ((temp_f9_4 * temp_f9_4) + (temp_f10_4 * temp_f10_4)));
                if (var_f2_2 > (float) lbColl_804D7A00) {
                    var_f2_2 = var_f0;
                } else if (var_f2_2 < (float) lbColl_804D7A10) {
                    var_f2_2 = lbColl_804D79F8;
                }
                var_f24 = var_f2_2;
            }
        } else {
            temp_f1_3 =
                ((temp_f10 * temp_f11) - (temp_f9 * temp_f4_7)) / temp_f12;
            var_f24 =
                ((temp_f5_2 * temp_f11) - (temp_f10 * temp_f4_7)) / temp_f12;
            var_f0 = temp_f1_3;
            if ((temp_f1_3 > (float) lbColl_804D7A00) ||
                (var_f0 < (float) lbColl_804D7A10) ||
                (var_f24 > (float) lbColl_804D7A00) ||
                (var_f24 < (float) lbColl_804D7A10))
            {
                if (var_f0 < (float) lbColl_804D7A10) {
                    var_f21 = lbColl_804D79F8;
                    var_f20 = lbColl_80005EBC(arg2, arg3, arg0, &spD0);
                } else {
                    var_f21 = lbColl_804D7A08;
                    var_f20 = lbColl_80005EBC(arg2, arg3, arg1, &spD0);
                }
                if (var_f24 < (float) lbColl_804D7A10) {
                    var_f22 = lbColl_804D79F8;
                    var_f1 = lbColl_80005EBC(arg0, arg1, arg2, &spCC);
                } else {
                    var_f22 = lbColl_804D7A08;
                    var_f1 = lbColl_80005EBC(arg0, arg1, arg3, &spCC);
                }
                if (var_f20 < var_f1) {
                    var_f0 = var_f21;
                    var_f24 = spD0;
                } else {
                    var_f0 = spCC;
                    var_f24 = var_f22;
                }
            }
        }
    }
    arg4->x = (sp104 * var_f0) + sp11C;
    arg4->y = (sp108 * var_f0) + sp120;
    arg4->z = (sp10C * var_f0) + sp124;
    arg5->x = (temp_f27 * var_f24) + sp110;
    arg5->y = (temp_f26 * var_f24) + sp114;
    arg5->z = (temp_f25 * var_f24) + sp118;
    temp_f1_4 = arg4->y - arg5->y;
    temp_f4_9 = arg4->x - arg5->x;
    temp_f2_6 = arg4->z - arg5->z;
    temp_f1_5 = (temp_f2_6 * temp_f2_6) +
                ((temp_f4_9 * temp_f4_9) + (temp_f1_4 * temp_f1_4));
    if (temp_f1_5 > lbColl_804D79F8) {
        temp_f1_6 = __frsqrte(temp_f1_5);
        temp_f1_7 =
            lbColl_804D7A18 * temp_f1_6 *
            -(((f64) temp_f1_5 * (temp_f1_6 * temp_f1_6)) - lbColl_804D7A20);
        temp_f1_8 =
            lbColl_804D7A18 * temp_f1_7 *
            -(((f64) temp_f1_5 * (temp_f1_7 * temp_f1_7)) - lbColl_804D7A20);
        sp38 = (float) ((f64) temp_f1_5 *
                        (lbColl_804D7A18 * temp_f1_8 *
                         -(((f64) temp_f1_5 * (temp_f1_8 * temp_f1_8)) -
                           lbColl_804D7A20)));
        var_f30 = sp38;
    } else {
        var_f30 = temp_f1_5;
    }
    if ((var_f30 < lbColl_804D79F0) && (var_f30 > lbColl_804D79F4)) {
        var_r0_4 = 1;
    } else {
        var_r0_4 = 0;
    }
    if (var_r0_4 != 0) {
        arg2->x = (scl + arg10) - var_f30;
        arg7->x = arg4->x;
        arg7->y = arg4->y;
        arg7->z = arg4->z;
        return 1;
    }
    // HSD_MtxInverse(arg6, (float(*)[4]) & sp9C[0]);
    // PSMTXMultVec((float(*)[4]) & sp9C[0], arg4, (Vec3*) &sp11C);
    // PSMTXMultVec((float(*)[4]) & sp9C[0], arg5, (Vec3*) &sp104);
    temp_f1_9 = sp120 - sp108;
    temp_f4_10 = sp11C - sp104;
    temp_f2_7 = sp124 - sp10C;
    temp_f1_10 = (temp_f2_7 * temp_f2_7) +
                 ((temp_f4_10 * temp_f4_10) + (temp_f1_9 * temp_f1_9));
    if (temp_f1_10 > lbColl_804D79F8) {
        temp_f1_11 = __frsqrte(temp_f1_10);
        temp_f1_12 = lbColl_804D7A18 * temp_f1_11 *
                     -(((f64) temp_f1_10 * (temp_f1_11 * temp_f1_11)) -
                       lbColl_804D7A20);
        temp_f1_13 = lbColl_804D7A18 * temp_f1_12 *
                     -(((f64) temp_f1_10 * (temp_f1_12 * temp_f1_12)) -
                       lbColl_804D7A20);
        sp34 = (float) ((f64) temp_f1_10 *
                        (lbColl_804D7A18 * temp_f1_13 *
                         -(((f64) temp_f1_10 * (temp_f1_13 * temp_f1_13)) -
                           lbColl_804D7A20)));
        var_f1_2 = sp34;
    } else {
        var_f1_2 = temp_f1_10;
    }
    temp_f0 = (arg10 * var_f30) / var_f1_2;
    temp_f2_8 = temp_f0 / var_f30;
    temp_f1_14 = scl + temp_f0;
    arg2->x = temp_f1_14 - var_f30;
    temp_f1_15 = arg5->x;
    arg7->x = (temp_f2_8 * (arg4->x - temp_f1_15)) + temp_f1_15;
    temp_f1_16 = arg5->y;
    arg7->y = (temp_f2_8 * (arg4->y - temp_f1_16)) + temp_f1_16;
    temp_f1_17 = arg5->z;
    arg7->z = (temp_f2_8 * (arg4->z - temp_f1_17)) + temp_f1_17;
    if (temp_f1_14 < var_f30) {
        return 0;
    }
    return 1;
}

inline float sqrDistance(Vec3* a, Vec3* b)
{
    float x = a->x - b->x;
    float y = a->y - b->y;
    float z = a->z - b->z;
    return x * x + y * y + z * z;
}

void lbColl_800077A0(Vec3* a, MtxPtr arg1, Vec3* b, Vec3* c, Vec3* d, Vec3* e,
                     float* angle, float x, float dist_offset)
{
    float dot_diff_cb;
    float offset_dist;
    float scl;
    float n0;
    float ba_dot;
    float dist;
    Vec3 diff_cb;
    float n1;
    Vec3 diff_ba;
    Vec3 normalize_e;
    Vec3 normal_x;
    Vec3 multi_mtx;

    diff_cb.x = c->x - b->x;
    diff_cb.y = c->y - b->y;
    diff_cb.z = c->z - b->z;

    if (diff_cb.x || diff_cb.y || diff_cb.z) {

        normal_x.x = x;
        normal_x.y = 0.0f;
        normal_x.z = 0.0f;
        PSMTXMultVec(arg1, &normal_x, &normal_x);

        multi_mtx.x = 0.0f;
        multi_mtx.y = 0.0f;
        multi_mtx.z = 0.0f;
        PSMTXMultVec(arg1, &multi_mtx, &multi_mtx);

        dist = sqrDistance(&normal_x, &multi_mtx);
        dist = sqrtf(dist);

        offset_dist = dist + dist_offset;

        dot_diff_cb = diff_cb.x * diff_cb.x
                    + diff_cb.y * diff_cb.y
                    + diff_cb.z * diff_cb.z;

        diff_ba.x = b->x - a->x;
        diff_ba.y = b->y - a->y;
        diff_ba.z = b->z - a->z;

        if (nearzero(dot_diff_cb)) {
            scl = 0.0f;
        } else {
            n0 = 2.0f * diff_cb.x * diff_ba.x
               + 2.0f * diff_cb.y * diff_ba.y
               + 2.0f * diff_cb.z * diff_ba.z;

            ba_dot = diff_ba.x * diff_ba.x
                   + diff_ba.y * diff_ba.y
                   + diff_ba.z * diff_ba.z;

            n1 = n0 * n0 - (4.0f * dot_diff_cb *
                            -(offset_dist * offset_dist - ba_dot));

            if (n1 < 0.0f) {
                n1 = 0.0f;
            }

            scl = (-n0 - sqrtf(n1)) / (2.0f * dot_diff_cb);
        }

        normalize_e.x = scl * diff_cb.x + b->x - a->x;
        normalize_e.y = scl * diff_cb.y + b->y - a->y;
        normalize_e.z = scl * diff_cb.z + b->z - a->z;

        PSVECNormalize(&normalize_e, e);

        *angle = lbVector_AngleXY(e, &diff_cb);
        d->x = dist * e->x + a->x;
        d->y = dist * e->y + a->y;
        d->z = dist * e->z + a->z;
    } else {
        *angle = M_PI;
        e->z = 0.0f;
        e->y = 0.0f;
        e->x = 0.0f;
    }
}

bool lbColl_80007AFC(HitCapsule* a, HitCapsule* b, float x, float y)
{
    float a_val, b_val;

    if (a->x43_b1) {
        a_val = a->scale;
    } else {
        a_val = a->scale * x;
    }

    if (b->x43_b1) {
        b_val = b->scale;
    } else {
        b_val = b->scale * y;
    }

    return lbColl_80006094(&b->x58, &b->x4C, &a->x58, &a->x4C,
                           &b->hurt_coll_pos, &a->hurt_coll_pos, b_val, a_val);
}

void lbColl_80007B78(Mtx a, Mtx b, float x, float y)
{
    /// @todo Eliminate casts.
    lbColl_800067F8((Vec3*) &b[1][1], (Vec3*) &b[0][2], (Vec3*) &a[1][1],
                    (Vec3*) &a[0][2], (Vec3*) &b[1][4], (Vec3*) &a[1][4],
                    b[0][0] * y, a[0][0] * x, x);
}

bool lbColl_80007BCC(HitCapsule* arg0, HitResult* shield_hit, void* arg2,
                     s32 arg3, float arg4, float arg5, float arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    MtxPtr var_r9;
    float var_f1;
    Mtx sp38;

    if (!shield_hit->skip_update_pos) {
        lb_8000B1CC(shield_hit->bone, &shield_hit->offset, &shield_hit->pos);
        if (arg2 != NULL) {
            shield_hit->pos.z = arg6;
        }
        shield_hit->skip_update_pos = 1;
    }
    if (arg3 != 0) {
        arg0->hurt_coll_pos = shield_hit->pos;
        arg0->coll_distance = lbColl_804D79F8;
        return 1;
    }
    if (arg2 != NULL) {
        PSMTXConcat(arg2, HSD_JObjGetMtxPtr(shield_hit->bone), sp38);
    }
    if (arg2 != NULL) {
        var_r9 = sp38;
    } else {
        var_r9 = HSD_JObjGetMtxPtr(shield_hit->bone);
    }
    if (arg0->x43_b1) {
        var_f1 = arg0->scale;
    } else {
        var_f1 = arg0->scale * arg4;
    }

    return lbColl_80006E58(&arg0->x58,            // arg0
                           &arg0->x4C,            // arg1
                           &shield_hit->pos,      // arg2
                           &shield_hit->pos,      // arg3
                           &sp74,                 // arg4
                           &sp68,                 // arg5
                           var_r9,                // arg6
                           &arg0->hurt_coll_pos,  // arg7
                           &arg0->coll_distance,  // arg8
                           var_f1,                // arg9
                           shield_hit->size,      // arg10
                           lbColl_804D7A34 * arg5 // arg11
    );
}

void lbColl_80007DD8(HitCapsule* capsule, HitResult* hit, Mtx hit_transform,
                     Vec3* /*out*/ arg3, float* angle, float scale)
{
    float dist_offset;
    Vec3 unused_result;
    Mtx transformed_hit;

    if (hit_transform != NULL) {
        PSMTXConcat(hit_transform, HSD_JObjGetMtxPtr(hit->bone),
                    transformed_hit);
    }
    if (capsule->x43_b1) {
        dist_offset = capsule->scale;
    } else {
        dist_offset = capsule->scale * scale;
    }
    lbColl_800077A0(&hit->pos,
                    hit_transform != NULL ? transformed_hit
                                          : HSD_JObjGetMtxPtr(hit->bone),
                    &capsule->x58, &capsule->x4C, &unused_result, arg3, angle,
                    hit->size, dist_offset);
}

bool lbColl_80007ECC(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2,
                     float hit_scl_y, float hurt_scl_y, float hurt_pos_z)
{
    Vec3 sp70;
    Vec3 sp64;
    Mtx sp34;
    float var_f1;
    MtxPtr var_r9;

    if (arg1->state == HurtCapsule_Enabled) {
        if (!arg1->skip_update_pos) {
            lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = hurt_pos_z;
                arg1->a_pos.z = hurt_pos_z;
            }
            arg1->skip_update_pos = 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp34);
        }
        if (arg2 != NULL) {
            var_r9 = sp34;
        } else {
            var_r9 = HSD_JObjGetMtxPtr(arg1->bone);
        }
        if (arg0->x43_b1) {
            var_f1 = arg0->scale;
        } else {
            var_f1 = arg0->scale * hit_scl_y;
        }
        return lbColl_80006E58(
            &arg0->x58, &arg0->x4C, &arg1->a_pos, &arg1->b_pos, &sp70, &sp64,
            var_r9, &arg0->hurt_coll_pos, &arg0->coll_distance, var_f1,
            arg1->scale, lbColl_804D7A38 * hurt_scl_y);
    }
    return 0;
}

bool lbColl_8000805C(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2, s32 arg3,
                     float arg4, float arg5, float arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    Mtx sp38;
    MtxPtr var_r9;
    float var_f1;

    if (arg1->state != Intangible) {
        if (!arg1->skip_update_pos) {
            lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = arg6;
                arg1->a_pos.z = arg6;
            }
            arg1->skip_update_pos = 1;
        }
        if (arg3 != 0) {
            arg0->hurt_coll_pos.x = 0.5F * (arg1->a_pos.x + arg1->b_pos.x);
            arg0->hurt_coll_pos.y = 0.5F * (arg1->a_pos.y + arg1->b_pos.y);
            arg0->hurt_coll_pos.z = 0.5F * (arg1->a_pos.z + arg1->b_pos.z);
            arg0->coll_distance = 5.0f;
            return 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp38);
        }
        if (arg2 != NULL) {
            var_r9 = sp38;
        } else {
            var_r9 = HSD_JObjGetMtxPtr(arg1->bone);
        }
        if (arg0->x43_b1) {
            var_f1 = arg0->scale;
        } else {
            var_f1 = arg0->scale * arg4;
        }

        return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos,
                               &arg1->b_pos, &sp74, &sp68, var_r9,
                               &arg0->hurt_coll_pos, &arg0->coll_distance,
                               var_f1, arg1->scale, lbColl_804D7A38 * arg5);
    }
    return 0;
}

inline void checkPos(HurtCapsule* hurt, Mtx mtx, float arg5)
{
    if (!hurt->skip_update_pos) {
        lb_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
        lb_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);

        if (mtx != NULL) {
            hurt->b_pos.z = arg5;
            hurt->a_pos.z = arg5;
        }

        hurt->skip_update_pos = true;
    }
}

inline void mtxConcat(HurtCapsule* hurt, Mtx mtx)
{
    Mtx sp34;
    if (mtx != NULL) {
        PSMTXConcat(mtx, HSD_JObjGetMtxPtr(hurt->bone), &sp34[0]);
    }
}

inline MtxPtr pickMtx(HurtCapsule* hurt, Mtx mtx)
{
    MtxPtr var_r9;
    Mtx sp34;
    if (mtx != NULL) {
        var_r9 = sp34;
    } else {
        var_r9 = HSD_JObjGetMtxPtr(hurt->bone);
    }
    return var_r9;
}

inline float getHit1C(HitCapsule* hit, float arg3)
{
    float var_f1;
    if (hit->x43_b1) {
        var_f1 = hit->scale;
    } else {
        var_f1 = hit->scale * arg3;
    }
    return var_f1;
}

bool lbColl_80008248(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2, f32 arg3, f32 arg4, f32 arg5)
{
    f32 var_f1;
    Vec3 sp70;
    Vec3 sp64;
    Mtx sp34;
    MtxPtr var_r9;

    if (!arg1->skip_update_pos) {
        lb_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
        lb_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
        if (arg2 != NULL) {
            arg1->b_pos.z = arg5;
            arg1->a_pos.z = arg5;
        }
        arg1->skip_update_pos = 1;
    }
    if (arg2 != NULL) {
        PSMTXConcat(arg2, HSD_JObjGetMtxPtr(arg1->bone), sp34);
    }
    if (arg2 != NULL) {
        var_r9 = sp34;
    } else {
        var_r9 = HSD_JObjGetMtxPtr(arg1->bone);
    }
    if (arg0->x43_b1) {
        var_f1 = arg0->scale;
    } else {
        var_f1 = arg0->scale * arg3;
    }
    return lbColl_80006E58(
            &arg0->x58, &arg0->x4C, &arg1->a_pos,
            &arg1->b_pos, &sp70, &sp64,
            var_r9, &arg0->hurt_coll_pos, &arg0->coll_distance,
            var_f1, arg1->scale, 3.0f * arg4);
}

void lbColl_800083C4(HurtCapsule* arg0)
{
    if (arg0->skip_update_pos) {
        return;
    }

    lb_8000B1CC(arg0->bone, &arg0->a_offset, &arg0->a_pos);
    lb_8000B1CC(arg0->bone, &arg0->b_offset, &arg0->b_pos);
    arg0->skip_update_pos = true;
}

void lbColl_80008428(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Disabled;
}

void lbColl_80008434(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Enabled;
}

void lbColl_80008440(HitCapsule* hit)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
        hit->victims_1[i].victim = NULL;
    }
    hit->x44 = 0;
    for (i = 0; i < ARRAY_SIZE(hit->victims_2); i++) {
        hit->victims_2[i].victim = NULL;
    }
    hit->x45 = 0;
}

void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst)
{
    HitVictim* sv1 = src->victims_1;
    HitVictim* dv1 = dst->victims_1;
    HitVictim* sv2 = src->victims_2;
    HitVictim* dv2 = dst->victims_2;
    size_t i;
    for (i = 0; i < ARRAY_SIZE(src->victims_1); i++) {
        dv1[i] = sv1[i];
        dv2[i] = sv2[i];
    }
    dst->x44 = src->x44;
    dst->x45 = src->x45;
}

bool lbColl_80008688(HitCapsule* capsule, int type, void* victim)
{
    int var_r0;
    int i;

    for (i = 0; i < ARRAY_SIZE(capsule->victims_1); i++) {
        if (capsule->victims_1[i].victim == victim) {
            switch (type) {
            case 2:
            case 4:
            case 5:
            case 7:
            case 8:
                capsule->victims_1[i].x4 = capsule->x40_b4;
            }
            return false;
        }
    }

    for (i = 0; i < ARRAY_SIZE(capsule->victims_1); i++) {
        if (capsule->victims_1[i].victim == NULL) {
            break;
        }
    }

    if (i == ARRAY_SIZE(capsule->victims_1)) {
        var_r0 = capsule->x44;
    } else {
        var_r0 = i;
    }

    capsule->victims_1[var_r0].victim = victim;

    switch (type) {
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
        capsule->victims_1[var_r0].x4 = capsule->x40_b4;
        break;
    default:
        capsule->victims_1[var_r0].x4 = 0;
        break;
    }

    if (i == ARRAY_SIZE(capsule->victims_1)) {
        capsule->x44 += 1;
        if (capsule->x44 >= 0xC) {
            capsule->x44 = 0;
        }
    }
    return true;
}

bool lbColl_80008820(HitCapsule* capsule, int type, void* victim)
{
    int var_r0;
    int i;

    for (i = 0; i < ARRAY_SIZE(capsule->victims_2); i++) {
        if (capsule->victims_2[i].victim == victim) {
            switch (type) {
            case 2:
            case 5:
            case 7:
            case 8:
                capsule->victims_2[i].x4 = capsule->x40_b4;
            }
            return false;
        }
    }

    for (i = 0; i < ARRAY_SIZE(capsule->victims_2); i++) {
        if (capsule->victims_2[i].victim == NULL) {
            break;
        }
    }

    if (i == ARRAY_SIZE(capsule->victims_2)) {
        var_r0 = capsule->x45;
    } else {
        var_r0 = i;
    }

    capsule->victims_2[var_r0].victim = victim;

    switch (type) {
    case 2:
    case 5:
    case 7:
    case 8:
        capsule->victims_2[var_r0].x4 = capsule->x40_b4;
        break;
    default:
        capsule->victims_2[var_r0].x4 = 0;
        break;
    }

    if (i == ARRAY_SIZE(capsule->victims_2)) {
        capsule->x45 += 1;
        if (capsule->x45 >= ARRAY_SIZE(capsule->victims_2)) {
            capsule->x45 = 0;
        }
    }
    return true;
}

GXColor const lbColl_804D7A50 = { 0 };

extern u8 lbColl_804D36CC[4];
extern GXColor lbColl_804D36D0;

void lbColl_800089B8(HitCapsule* hit, UNK_T arg1)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
        if (hit->victims_1[i].victim == arg1) {
            hit->victims_1[i].victim = 0;
        }
    }
}

void lbColl_80008A5C(HitCapsule* hit)
{
    if (hit->state != HitCapsule_Disabled) {
        size_t i;
        for (i = 0; i < ARRAY_SIZE(hit->victims_1); i++) {
            if (hit->victims_1[i].victim != NULL) {
                u32 temp_r4 = hit->victims_1[i].x4;
                if (temp_r4 != 0) {
                    hit->victims_1[i].x4 = temp_r4 - 1;
                    if (hit->victims_1[i].x4 == 0) {
                        hit->victims_1[i].victim = NULL;
                    }
                }
            }
        }
        for (i = 0; i < ARRAY_SIZE(hit->victims_2); i++) {
            if (hit->victims_2[i].victim != 0) {
                u32 temp_r4 = hit->victims_2[i].x4;
                if (temp_r4 != 0) {
                    hit->victims_2[i].x4 = temp_r4 - 1;
                    if (hit->victims_2[i].x4 == 0) {
                        hit->victims_2[i].victim = NULL;
                    }
                }
            }
        }
    }
}

void lbColl_80008D30(HitCapsule* arg0, lbColl_80008D30_arg1* arg1)
{
    arg0->state = arg1->state;
    arg0->damage = arg1->damage;
    arg0->kb_angle = arg1->kb_angle;
    arg0->x24 = arg1->unkC;
    arg0->x28 = arg1->unk10;
    arg0->x2C = arg1->unk14;
    arg0->element = arg1->element;
    arg0->sfx_severity = arg1->sfx_severity;
    arg0->sfx_kind = arg1->sfx_kind;
    arg0->unk_count = arg1->damage;
}

extern u8 lbColl_804D36A0[4];
extern u8 lbColl_804D36A4[4];
extern u8 lbColl_804D36A8[4];
extern u8 lbColl_804D36DC[4];

bool lbColl_80009F54(HitCapsule* hit, u32 arg1, float arg8)
{
    u8* var_r5;
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        switch (hit->element) {
        case HitElement_Catch:
            var_r5 = lbColl_804D36A4;
            break;
        case HitElement_Inert:
            var_r5 = lbColl_804D36DC;
            break;
        default:
            var_r5 = lbColl_804D36A0;
            break;
        }

        if (var_r5[3] == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg1) {
            if (hit->x43_b1) {
                var_f1 = hit->scale;
            } else {
                var_f1 = hit->scale * arg8;
            }
            lbColl_80008FC8(hit->x58, hit->x4C, var_r5, lbColl_804D36A8,
                            var_f1);
            return 1;
        }
    }
    return 0;
}

extern u8 lbColl_804D36E8[4];
extern u8 lbColl_804D36EC[4];

bool lbColl_8000A044(HitCapsule* hit, u32 arg1, float arg8)
{
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        if (lbColl_804D36E8[3] == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg1) {
            if (hit->x43_b1) {
                var_f1 = hit->scale;
            } else {
                var_f1 = hit->scale * arg8;
            }
            lbColl_80008FC8(hit->x58, hit->x4C, lbColl_804D36E8,
                            lbColl_804D36EC, var_f1);
            return 1;
        }
    }
    return 0;
}

bool lbColl_8000A584(HurtCapsule* hurt, u32 arg1, u32 arg2, Mtx arg3, f32 arg8)
{
    PAD_STACK(4);
    {
        Mtx spA0;
        Vec3 sp94;
        Vec3 sp88;
        Mtx sp40;
        Vec3 sp34;
        Vec3 sp28;
        f32 temp_f31;
        GXColor* temp_r31_2;
        MtxPtr var_r28;
        u32 var_r0;
        u32 var_r4;
        u8* temp_r3;

        var_r4 = arg1;
        if (hurt->state == Intangible) {
            var_r4 = 2;
        }
        temp_r3 = lbColl_803B9928[var_r4].pad;
        if (temp_r3[3] == 0xFF) {
            var_r0 = 0;
        } else {
            var_r0 = 2;
        }
        if (var_r0 == arg2) {
            if (!hurt->skip_update_pos) {
                lb_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
                lb_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);
                if (arg3 != NULL) {
                    hurt->b_pos.z = arg8;
                    hurt->a_pos.z = arg8;
                }
                hurt->skip_update_pos = 1;
            }
            if (arg3 != NULL) {
                PSMTXConcat(arg3, HSD_JObjGetMtxPtr(hurt->bone), spA0);
            }
            temp_f31 = hurt->scale;
            temp_r31_2 = lbColl_803B9928[var_r4].pad_x;
            sp88 = hurt->b_pos;
            sp94 = hurt->a_pos;
            if (arg3 != NULL) {
                var_r28 = spA0;
            } else {
                var_r28 = HSD_JObjGetMtxPtr(hurt->bone);
            }
            HSD_MtxInverse(var_r28, sp40);
            PSMTXMultVec(sp40, &sp94, &sp28);
            PSMTXMultVec(sp40, &sp88, &sp34);
            lbColl_800096B4(var_r28, sp28, sp34, temp_r3, temp_r31_2,
                            temp_f31);
            return 1;
        }
        return 0;
    }
}

u8 lbColl_804D36E0[4] = { 0 };
GXColor lbColl_804D36E4 = { 0x80, 0x40, 0x00, 0x80 };
extern char lbColl_804D3700[8];
extern char lbColl_804D3708[8];

bool lbColl_8000A460(Foo* hurt, u32 arg1)
{
    u32 var_r0;

    u8* r31 = lbColl_804D36E0;
    GXColor* r30 = &lbColl_804D36E4;

    if (r31[3] == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        HSD_JObjSetupMatrix(hurt->jobj);
        lbColl_800096B4(HSD_JObjGetMtxPtr(hurt->jobj), hurt->v1, hurt->v1, r31,
                        r30, hurt->v2);
        return 1;
    }
    return 0;
}

bool lbColl_8000A244(HurtCapsule* hurt, u32 arg1, Mtx arg2, float arg3)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;
    Vec3 sp78;
    Vec3 sp6C;
    Mtx sp3C;
    float temp_f31;
    MtxPtr var_r28;
    GXColor* temp_r31_2;
    u32 var_r0;
    u8* temp_r3;

    temp_r3 = lbColl_803B9928[hurt->state].pad;
    if (temp_r3[3] == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        if (!hurt->skip_update_pos) {
            lb_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
            lb_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);
            if (arg2 != NULL) {
                hurt->b_pos.z = arg3;
                hurt->a_pos.z = arg3;
            }
            hurt->skip_update_pos = 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(hurt->bone), sp9C);
        }
        temp_f31 = hurt->scale;
        temp_r31_2 = lbColl_803B9928[hurt->state].pad_x;
        sp84 = hurt->b_pos;
        sp90 = hurt->a_pos;
        if (arg2 != NULL) {
            var_r28 = sp9C;
        } else {
            var_r28 = HSD_JObjGetMtxPtr(hurt->bone);
        }
        HSD_MtxInverse(var_r28, sp3C);
        PSMTXMultVec(sp3C, &sp90, &sp6C);
        PSMTXMultVec(sp3C, &sp84, &sp78);
        lbColl_800096B4(var_r28, sp6C, sp78, temp_r3, temp_r31_2,
                        temp_f31);
        return 1;
    }
    return 0;
}

bool lbColl_8000A95C(HitResult* hit, u32 arg1, Mtx arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;
    Mtx sp3C;
    Vec3 sp30;
    Vec3 sp24;
    f32 temp_f31;
    MtxPtr var_r31;
    u32 var_r0;

    if (lbColl_804D36CC[3] == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        if (!hit->skip_update_pos) {
            lb_8000B1CC(hit->bone, &hit->offset, &hit->pos);
            if (arg2 != NULL) {
                hit->pos.z = pos_z;
            }
            hit->skip_update_pos = 1;
        }
        if (arg2 != NULL) {
            PSMTXConcat(arg2, HSD_JObjGetMtxPtr(hit->bone), sp9C);
        }
        temp_f31 = hit->size;
        sp84 = hit->pos;
        sp90 = hit->pos;
        if (arg2 != NULL) {
            var_r31 = sp9C;
        } else {
            var_r31 = HSD_JObjGetMtxPtr(hit->bone);
        }
        HSD_MtxInverse(var_r31, sp3C);
        PSMTXMultVec(sp3C, &sp90, &sp24);
        PSMTXMultVec(sp3C, &sp84, &sp30);
        lbColl_800096B4(var_r31, sp24, sp30, lbColl_804D36CC, &lbColl_804D36D0,
                        temp_f31);
        return 1;
    }
    return 0;
}

bool lbColl_8000ACFC(UNK_T victim, HitCapsule* hitbox)
{
    HitVictim* victims = hitbox->victims_1;
    size_t const count = ARRAY_SIZE(hitbox->victims_1);
    size_t i;

    for (i = 0; i < count; i++) {
        if (victims[i].victim == victim) {
            break;
        }
    }

    return i == count ? false : true;
}
