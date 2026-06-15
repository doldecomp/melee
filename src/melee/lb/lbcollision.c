#include "lbcollision.h"

#include "lb_00B0.h"
#include "lbaudio_ax.h"
#include "lbvector.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/types.h"

#include "lb/forward.h"

#include "lb/types.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/particle.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/math_ppc.h>

/* 006E58 */ static bool
lbColl_80006E58(Vec3* hit_start, Vec3* hit_end, Vec3* hurt_start,
                Vec3* hurt_end, Vec3* hit_closest, Vec3* hurt_closest,
                MtxPtr hurt_mtx, Vec3* out_contact_pos, float* out_overlap,
                float hit_radius, float hurt_radius, float broadphase_scale);

/// .sdata
static GXColor lbColl_804D36C4 = { 0, 0xFF, 0xFF, 0x80 };
static GXColor lbColl_804D36C8 = { 0, 0x80, 0x80, 0x80 };
static GXColor lbColl_804D36D4 = { 0, 0x80, 0xFF, 0x80 };
static GXColor lbColl_804D36D8 = { 0, 0x40, 0x80, 0x80 };

/// .sdata2
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

/// .data
int lbColl_803B9880[] = {
    0x00083D60, 0x00083D60, 0x00083D60, 0x0000005B, 0x0000005A, 0x00000059,
    0x00000058, 0x00000057, 0x00000056, 0x0000006F, 0x00000070, 0x00000071,
    0x00000054, 0x00000054, 0x00000054, 0x0000005A, 0x00000059, 0x000000DF,
    0x000000E1, 0x000000E1, 0x000000E1, 0x00000062, 0x00000063, 0x00000064,
    0x00000065, 0x00000066, 0x00000067, 0x0004461B, 0x0004461B, 0x0004461B,
    0x000000F1, 0x000000F1, 0x000000F1, 0x0000005E, 0x0000005D, 0x0000005C,
    0x00035BAF, 0x00035BB2, 0x00035BB5, 0x00083D60, 0x00083D60, 0x0000020D,
};

extern GXColor lbColl_804D36AC;
extern GXColor lbColl_804D36B0;
extern GXColor lbColl_804D36B4;
extern GXColor lbColl_804D36B8;
extern GXColor lbColl_804D36BC;
extern GXColor lbColl_804D36C0;

struct unk {
    GXColor* pad;
    GXColor* pad_x;
} lbColl_803B9928[] = {
    &lbColl_804D36AC, &lbColl_804D36B0, &lbColl_804D36B4,
    &lbColl_804D36B8, &lbColl_804D36BC, &lbColl_804D36C0,
};

u8 lbColl_803B9940[0x1A0] = { 0 };
u8 lbColl_803B9AE0[0x1A0] = { 0 };
u8 lbColl_803B9C80[0x120] = { 0 };
u8 lbl_803B9DA0[0x80] = { 0 };
u8 lbl_803B9E20[0xA0] = { 0 };
u8 lbColl_803B9EC0[0x60] = { 0 };
u8 lbColl_803B9F20[0xA0] = { 0 };

/// .text

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

static inline void vector_sub(Vec3* a, Vec3* b, Vec3* result)
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

bool lbColl_80005C44(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2,
                     Vec3* arg3, float arg8, float arg9)
{
    float temp_f2;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 d1;
    float d2_x, d2_y, d2_z;

    temp_f2 = arg8 + arg9;
    sp38 = *arg0;
    sp2C = *arg2;

    if (sp38.x > arg1->x) {
        if (sp38.x + temp_f2 < sp2C.x) {
            return 0;
        }
        if (arg1->x - temp_f2 > sp2C.x) {
            return 0;
        }
    } else {
        if (sp38.x - temp_f2 > sp2C.x) {
            return 0;
        }
        if (arg1->x + temp_f2 < sp2C.x) {
            return 0;
        }
    }
    if (sp38.y > arg1->y) {
        if (sp38.y + temp_f2 < sp2C.y) {
            return 0;
        }
        if (arg1->y - temp_f2 > sp2C.y) {
            return 0;
        }
    } else {
        if (sp38.y - temp_f2 > sp2C.y) {
            return 0;
        }
        if (arg1->y + temp_f2 < sp2C.y) {
            return 0;
        }
    }
    if (sp38.z > arg1->z) {
        if (sp38.z + temp_f2 < sp2C.z) {
            return 0;
        }
        if (arg1->z - temp_f2 > sp2C.z) {
            return 0;
        }
    } else {
        if (sp38.z - temp_f2 > sp2C.z) {
            return 0;
        }
        if (arg1->z + temp_f2 < sp2C.z) {
            return 0;
        }
    }

    d1.x = arg1->x - sp38.x;
    d1.y = arg1->y - sp38.y;
    d1.z = arg1->z - sp38.z;

    d2_x = sp38.x - sp2C.x;
    d2_y = sp38.y - sp2C.y;
    d2_z = sp38.z - sp2C.z;

    {
        float d1_dot_d1 = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
        float d1_dot_d2 = d1.x * d2_x + d1.y * d2_y + d1.z * d2_z;
        float scale;

        if (nearzero(d1_dot_d1)) {
            scale = 0.0f;
        } else {
            scale = -d1_dot_d2 / d1_dot_d1;
            if (scale > 1.0) {
                scale = 1.0f;
            } else if (scale < 0.0) {
                scale = 0.0f;
            }
        }

        arg3->x = d1.x * scale + sp38.x;
        arg3->y = d1.y * scale + sp38.y;
        arg3->z = d1.z * scale + sp38.z;
    }

    d2_x = arg3->x - sp2C.x;
    d2_y = arg3->y - sp2C.y;
    d2_z = arg3->z - sp2C.z;

    if (SQ(temp_f2) < SQ(d2_x) + SQ(d2_y) + SQ(d2_z)) {
        return false;
    } else {
        return true;
    }
}

float lbColl_80005EBC(const Vec3* arg0, const Vec3* arg1, const Vec3* arg2,
                      float* arg3)
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

bool lbColl_80006094(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, Vec3* arg4,
                    Vec3* arg5, float arg6, float arg7)
{
    {
        Vec3 vec4;
        Vec3 arg4_offset;
        Vec3 arg5_offset;
        float temp_f1;
        float unk_sum = arg6 + arg7;
        vec4 = *arg0;
        arg4_offset = vec4;
        {
            Vec3 arg2_copy;
            arg2_copy = *arg2;
            arg5_offset = arg2_copy;
        }

        {
            float arg1_x = arg1->x;
            if (arg4_offset.x > arg1_x) {
                {
                    float x = arg4_offset.x + unk_sum;
                    if (x < arg5_offset.x && x < arg3->x) {
                        return false;
                    }
                }

                {
                    float x = arg1_x - unk_sum;
                    if (x > arg5_offset.x && x > arg3->x) {
                        return false;
                    }
                }

                goto block_13;
            } else {
                {
                    float x = arg4_offset.x - unk_sum;
                    if (x > arg5_offset.x && x > arg3->x) {
                        return false;
                    }
                }

                {
                    float x = arg1_x + unk_sum;
                    if (x < arg5_offset.x && x < arg3->x) {
                        return false;
                    }
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

            float d1_y = arg1->y - arg4_offset.y;
            float arg3_y = arg3->y;
            float d1_z = arg1->z - arg4_offset.z;
            float d2_y = arg3_y - arg5_offset.y;
            float offset_delta_y = arg4_offset.y - arg5_offset.y;
            float arg3_x = arg3->x;
            float d1_x = arg1_x - arg4_offset.x;
            float d2_x = arg3_x - arg5_offset.x;
            float arg3_z = arg3->z;
            float d2_z = arg3_z - arg5_offset.z;
            float d1_dot_d2 = d1_z * d2_z + d1_x * d2_x +
                            d1_y * d2_y;
            float d2_z_sq = d2_z * d2_z;
            float d2_len_sq = d2_z_sq + d2_x * d2_x +
                              d2_y * d2_y;
            float offset_delta_x = arg4_offset.x - arg5_offset.x;
            float d1_len_sq = (d1_z * d1_z) +
                              ((d1_x * d1_x) + (d1_y * d1_y));
            float offset_delta_z = arg4_offset.z - arg5_offset.z;
            float d2_dot_offset_delta = d2_z * offset_delta_z +
                             d2_x * offset_delta_x + d2_y * offset_delta_y;
            float d1_dot_offset_delta = (d1_z * offset_delta_z) + d1_x * offset_delta_x +
                             d1_y * offset_delta_y;
            float denom = d1_len_sq * d2_len_sq - d1_dot_d2 * d1_dot_d2;

            {
                float arg5_scl;
                if (approximatelyZero(d2_len_sq)) {
                    if (approximatelyZero(d1_len_sq)) {
                        arg4_scl = 0.0f;
                        arg5_scl = 0.0f;
                    } else {
                        arg5_scl = 0.0f;
                        {
                            float scale = -d1_dot_offset_delta / d1_len_sq;
                            arg4_scl = scale;

                            if (scale > lbColl_804D7A00) {
                                arg4_scl = lbColl_804D7A08;
                            } else if (arg4_scl < lbColl_804D7A10) {
                                arg4_scl = lbColl_804D79F8;
                            }
                        }
                    }
                } else {
                    if (approximatelyZero(denom)) {
                        float mid_y =
                            (lbColl_804D7A18 * d2_y + arg5_offset.y);
                        float mid_x =
                            (lbColl_804D7A18 * d2_x + arg5_offset.x);
                        float arg4_mid_y = arg4_offset.y - mid_y;
                        float arg1_mid_y = arg1->y - mid_y;
                        float mid_z =
                            lbColl_804D7A18 * d2_z + arg5_offset.z;
                        float arg4_mid_x = arg4_offset.x - mid_x;
                        float arg1_mid_x = arg1_x - mid_x;
                        float arg4_offset_z = arg4_offset.z - mid_z;
                        float arg1_mid_z = arg1->z - mid_z;

                        // lhs and rhs each the same inline
                        if ((arg4_offset_z * arg4_offset_z +
                             ((arg4_mid_x * arg4_mid_x) +
                              (arg4_mid_y * arg4_mid_y))) <
                            ((arg1_mid_z * arg1_mid_z) +
                             ((arg1_mid_x * arg1_mid_x) +
                              (arg1_mid_y * arg1_mid_y))))
                        {
                            Vec3 c3;
                            float arg3_arg2_x;
                            float arg3_arg2_y;
                            c3 = arg5_offset;
                            arg3_arg2_x = arg3_x - arg2->x;
                            arg3_arg2_y = arg3_y - arg2->y;
                            {
                                Vec3 a2;
                                float dot;
                                float arg3_arg2_z;
                                float scale;
                                a2 = vec4;
                                arg3_arg2_z = arg3_z - arg2->z;
                                arg4_scl = 0.0f;
                                dot = (arg3_arg2_z * (c3.z - a2.z)) +
                                      ((arg3_arg2_x * (c3.x - a2.x)) +
                                       (arg3_arg2_y * (c3.y - a2.y)));
                                scale = -dot / ((arg3_arg2_z * arg3_arg2_z) +
                                                 ((arg3_arg2_x * arg3_arg2_x) +
                                                  (arg3_arg2_y * arg3_arg2_y)));
                                if (scale > lbColl_804D7A00) {
                                    scale = lbColl_804D7A08;
                                } else if (scale < lbColl_804D7A10) {
                                    scale = lbColl_804D79F8;
                                }
                                arg5_scl = scale;
                            }
                        } else {
                            Vec3 c2;
                            c2 = arg5_offset;
                            {
                                float arg3_arg2_x;
                                arg4_scl = 1.0f;
                                arg3_arg2_x = arg3_x - arg2->x;
                                {
                                    float arg3_arg2_y;
                                    float arg3_arg2_z;
                                    arg3_arg2_y = arg3_y - arg2->y;
                                    arg3_arg2_z = arg3_z - arg2->z;
                                    {
                                        Vec3 b0;

                                        b0 = *arg1;
                                        {
                                            float dot;
                                            float scale;
                                            float d2_from_arg2_len_sq;
                                            dot = (arg3_arg2_z * (c2.z - b0.z)) +
                                                  ((arg3_arg2_x * (c2.x - b0.x)) +
                                                   (arg3_arg2_y * (c2.y - b0.y)));
                                            d2_from_arg2_len_sq =
                                                (arg3_arg2_z * arg3_arg2_z) +
                                                ((arg3_arg2_x * arg3_arg2_x) +
                                                 (arg3_arg2_y * arg3_arg2_y));
                                            scale = -dot / d2_from_arg2_len_sq;

                                            if (scale > lbColl_804D7A00) {
                                                scale = lbColl_804D7A08;
                                            } else if (scale < lbColl_804D7A10) {
                                                scale = lbColl_804D79F8;
                                            }

                                            arg5_scl = scale;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        float temp_f1_3 =
                            ((d1_dot_d2 * d2_dot_offset_delta) - (d2_len_sq * d1_dot_offset_delta)) /
                            denom;
                        arg5_scl =
                            ((d1_len_sq * d2_dot_offset_delta) - (d1_dot_d2 * d1_dot_offset_delta)) /
                            denom;
                        arg4_scl = temp_f1_3;
                        if (temp_f1_3 > lbColl_804D7A00 ||
                            arg4_scl < lbColl_804D7A10 ||
                            arg5_scl > lbColl_804D7A00 ||
                            arg5_scl < lbColl_804D7A10)
                        {
                            float var_f18;
                            float var_f19;
                            float var_f1;
                            float spA4;

                            if (arg4_scl < lbColl_804D7A10) {
                                var_f19 = lbColl_804D79F8;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg0, &spA4);
                            } else {
                                var_f19 = lbColl_804D7A08;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg1, &spA4);
                            }

                            {
                                float spA0;
                                if (arg5_scl < lbColl_804D7A10) {
                                    arg5_scl = lbColl_804D79F8;
                                    var_f1 = lbColl_80005EBC(arg0, arg1, arg2,
                                                             &spA0);
                                } else {
                                    arg5_scl = lbColl_804D7A08;
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

                arg4->x = d1_x * arg4_scl + arg4_offset.x;
                arg4->y = d1_y * arg4_scl + arg4_offset.y;
                arg4->z = d1_z * arg4_scl + arg4_offset.z;

                arg5->x = d2_x * arg5_scl + arg5_offset.x;
                arg5->y = d2_y * arg5_scl + arg5_offset.y;
                arg5->z = d2_z * arg5_scl + arg5_offset.z;
            }
        }
            PAD_STACK(72);
            return end(arg4, arg5, unk_sum);
        }
        }
    }
}

bool lbColl_800067F8(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* e, Vec3* f,
                     float p, float q, float r)
{
    Vec3 a1;
    float sum_pq = p + q;

    Vec3 a0;
    PAD_STACK(72);

    a0 = *a;
    a1 = a0;
    {
        Vec3 c0;

        c0 = *c;

        {
            Vec3 c1;

            c1 = c0;
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
                            float out0;
                            float out1;
                            if (approximatelyZero(sqdist2_dc)) {
                                if (approximatelyZero(sqdist2_ba)) {
                                    scl_e = 0.0f;
                                    scl_f = 0.0f;
                                } else {
                                    float temp_f1_2;
                                    scl_f = 0.0f;
                                    temp_f1_2 = -dot2_diff_ba_ac / sqdist2_ba;
                                    scl_e = temp_f1_2;
                                    if (temp_f1_2 > lbColl_804D7A00) {
                                        scl_e = lbColl_804D7A08;
                                    } else if (scl_e < lbColl_804D7A10) {
                                        scl_e = lbColl_804D79F8;
                                    }
                                }
                            } else if (approximatelyZero(determinant)) {
                                float temp_f7_2 =
                                    lbColl_804D7A18 * diff_dc_y + c1.y;
                                float temp_f5_2 =
                                    lbColl_804D7A18 * diff_dc_x + c1.x;
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
                                        c3 = c0;
                                        diff_dc_x = d_x - c->x;
                                        temp_f8_2 = d_y - c->y;
                                        {
                                            {
                                                Vec3 a2;
                                                float diff_dc_z;
                                                float dot;
                                                a2 = a0;
                                                diff_dc_z = d->z - c->z;
                                                scl_e = 0.0f;
                                                dot =
                                                    diff_dc_z * (c3.z - a2.z) +
                                                    ((diff_dc_x *
                                                      (c3.x - a2.x)) +
                                                     (temp_f8_2 *
                                                      (c3.y - a2.y)));
                                                temp_scl_f =
                                                    -dot /
                                                    ((diff_dc_z * diff_dc_z) +
                                                     ((diff_dc_x * diff_dc_x) +
                                                      (temp_f8_2 *
                                                       temp_f8_2)));
                                            }
                                        }
                                        if (temp_scl_f > lbColl_804D7A00) {
                                            temp_scl_f = lbColl_804D7A08;
                                        } else if (temp_scl_f <
                                                   lbColl_804D7A10)
                                        {
                                            temp_scl_f = lbColl_804D79F8;
                                        }
                                        scl_f = temp_scl_f;
                                    } else {
                                        Vec3 c2;

                                        c2 = c0;
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

                                                    b0 = *b;
                                                    {
                                                        float dot;
                                                        float var_f2_2;
                                                        dot =
                                                            diff_dc_z1 *
                                                                (c2.z - b0.z) +
                                                            ((diff_dc_x1 *
                                                              (c2.x - b0.x)) +
                                                             (diff_dc_y1 *
                                                              (c2.y - b0.y)));
                                                        var_f2_2 =
                                                            -dot /
                                                            ((diff_dc_z1 *
                                                              diff_dc_z1) +
                                                             ((diff_dc_x1 *
                                                               diff_dc_x1) +
                                                              (diff_dc_y1 *
                                                               diff_dc_y1)));
                                                        if (var_f2_2 >
                                                            lbColl_804D7A00)
                                                        {
                                                            var_f2_2 =
                                                                lbColl_804D7A08;
                                                        } else if (
                                                            var_f2_2 <
                                                            lbColl_804D7A10)
                                                        {
                                                            var_f2_2 =
                                                                lbColl_804D79F8;
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
                                if ((temp_f1_3 > lbColl_804D7A00) ||
                                    (scl_e < lbColl_804D7A10) ||
                                    (scl_f > lbColl_804D7A00) ||
                                    (scl_f < lbColl_804D7A10))
                                {
                                    float result0;
                                    float temp_scl_e;
                                    {
                                        if (scl_e < lbColl_804D7A10) {
                                            temp_scl_e = lbColl_804D79F8;
                                            result0 = lbColl_80005FC0(c, d, a,
                                                                      &out0);
                                        } else {
                                            temp_scl_e = lbColl_804D7A08;
                                            result0 = lbColl_80005FC0(c, d, b,
                                                                      &out0);
                                        }
                                    }
                                    {
                                        float result1;
                                        if (scl_f < lbColl_804D7A10) {
                                            scl_f = lbColl_804D79F8;
                                            result1 = lbColl_80005FC0(a, b, c,
                                                                      &out1);
                                        } else {
                                            scl_f = lbColl_804D7A08;
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

/// @brief Tests a hit capsule segment against a hurt or shield capsule
/// segment.
/// @param[in] hit_start First endpoint of the hit capsule axis.
/// @param[in] hit_end Second endpoint of the hit capsule axis.
/// @param[in] hurt_start First endpoint of the hurt/shield capsule axis.
/// @param[in] hurt_end Second endpoint of the hurt/shield capsule axis.
/// @param[out] hit_closest Closest point on the hit capsule axis.
/// @param[out] hurt_closest Closest point on the hurt/shield capsule axis.
/// @param[in] hurt_mtx Matrix used to measure hurt radius along contact
/// normal.
/// @param[out] out_contact_pos Contact point on the hurt/shield surface.
/// @param[out] out_overlap Effective radius margin minus closest distance.
/// @param[in] hit_radius Hit capsule radius.
/// @param[in] hurt_radius Hurt/shield capsule radius.
/// @param[in] broadphase_scale Scale applied to hurt_radius for AABB
/// rejection.
/// @return true if the capsule axes overlap within their effective radii.
bool lbColl_80006E58(Vec3* hit_start, Vec3* hit_end, Vec3* hurt_start,
                     Vec3* hurt_end, Vec3* hit_closest, Vec3* hurt_closest,
                     MtxPtr hurt_mtx, Vec3* out_contact_pos,
                     float* out_overlap, float hit_radius, float hurt_radius,
                     float broadphase_scale)
{
    float hurt_len_sq;
    float closest_delta_x;
    float hit_start_mid_x;
    float local_delta_x;
    float hurt_mid_z;
    Vec3 hit_start_copy;
    Vec3 hurt_start_copy;
    Vec3 hit_delta;
    Mtx inv_hurt_mtx;
    float candidate_hit_param;
    float scaled_hurt_radius;
    float hurt_mid_x;
    float hurt_mid_y;
    float hurt_start_dot;
    float hit_end_mid_y;
    float closest_denom;
    float projected_hit_param;
    float local_dist_sq;
    float allowed_distance;
    float hurt_closest_x;
    float hurt_closest_y;
    float hurt_closest_z;
    float hit_start_mid_y;
    float hit_param_candidate;
    float closest_delta_y;
    float closest_dist_sq;
    float local_delta_y;
    float start_delta_x;
    float start_delta_y;
    float start_delta_z;
    float hurt_delta_x;
    float hit_start_max_x;
    float hit_end_min_x;
    float hit_start_min_x;
    float hit_end_max_x;
    float hit_start_mid_z;
    float closest_delta_z;
    float local_delta_z;
    float contact_lerp;
    float broadphase_radius;
    float hit_end_mid_z;
    float hit_start_max_y;
    float hit_end_min_y;
    float hit_start_min_y;
    float hit_end_max_y;
    float hit_end_min_z;
    float hit_end_max_z;
    float hit_start_dot;
    float hit_end_x;
    float hit_len_sq;
    float hit_end_mid_x;
    float hit_end_y;
    float hit_start_max_z;
    float hit_start_min_z;
    float hurt_end_x;
    float hit_end_z;
    float hurt_end_y;
    float hurt_end_z;
    float hit_param;
    float local_dist;
    float hurt_param;
    float hurt_param_from_hit_start;
    float hurt_param_from_hit_end;
    float closest_dist;
    float segment_dot;
    f64 local_rsqrt_estimate;
    f64 local_rsqrt_step1;
    f64 local_rsqrt_step2;
    f64 closest_rsqrt_estimate;
    f64 closest_rsqrt_step1;
    f64 closest_rsqrt_step2;
    s32 is_hurt_segment_degenerate;
    s32 is_hit_segment_degenerate;
    s32 is_parallel;
    s32 is_zero_distance;
    float hurt_delta_z;
    float hurt_delta_y;
    PAD_STACK(64);

    // Fast reject when the expanded hit segment AABB misses both hurt
    // endpoints.
    broadphase_radius = (hurt_radius * broadphase_scale) + hit_radius;
    hit_start_copy = *hit_start;
    hurt_start_copy = *hurt_start;
    hit_end_x = hit_end->x;
    if (hit_start_copy.x > hit_end_x) {
        hit_start_max_x = hit_start_copy.x + broadphase_radius;
        if ((hit_start_max_x < hurt_start_copy.x) &&
            (hit_start_max_x < hurt_end->x))
        {
            return 0;
        }
        hit_end_min_x = hit_end_x - broadphase_radius;
        if ((hit_end_min_x > hurt_start_copy.x) &&
            (hit_end_min_x > hurt_end->x))
        {
            return 0;
        }
        goto block_13;
    }
    hit_start_min_x = hit_start_copy.x - broadphase_radius;
    if ((hit_start_min_x > hurt_start_copy.x) &&
        (hit_start_min_x > hurt_end->x))
    {
        return 0;
    }
    hit_end_max_x = hit_end_x + broadphase_radius;
    if ((hit_end_max_x < hurt_start_copy.x) && (hit_end_max_x < hurt_end->x)) {
        return 0;
    }
block_13:
    if (hit_start_copy.y > (hit_end_y = hit_end->y)) {
        hit_start_max_y = hit_start_copy.y + broadphase_radius;
        if ((hit_start_max_y < hurt_start_copy.y) &&
            (hit_start_max_y < hurt_end->y))
        {
            return 0;
        }
        hit_end_min_y = hit_end_y - broadphase_radius;
        if ((hit_end_min_y > hurt_start_copy.y) &&
            (hit_end_min_y > hurt_end->y))
        {
            return 0;
        }
        goto block_26;
    }
    hit_start_min_y = hit_start_copy.y - broadphase_radius;
    if ((hit_start_min_y > hurt_start_copy.y) &&
        (hit_start_min_y > hurt_end->y))
    {
        return 0;
    }
    hit_end_max_y = hit_end_y + broadphase_radius;
    if ((hit_end_max_y < hurt_start_copy.y) && (hit_end_max_y < hurt_end->y)) {
        return 0;
    }
block_26:
    if (hit_start_copy.z > (hit_end_z = hit_end->z)) {
        hit_start_max_z = hit_start_copy.z + broadphase_radius;
        if ((hit_start_max_z < hurt_start_copy.z) &&
            (hit_start_max_z < hurt_end->z))
        {
            return 0;
        }
        hit_end_min_z = hit_end_z - broadphase_radius;
        if ((hit_end_min_z > hurt_start_copy.z) &&
            (hit_end_min_z > hurt_end->z))
        {
            return 0;
        }
        goto block_39;
    }
    hit_start_min_z = hit_start_copy.z - broadphase_radius;
    if ((hit_start_min_z > hurt_start_copy.z) &&
        (hit_start_min_z > hurt_end->z))
    {
        return 0;
    }
    hit_end_max_z = hit_end_z + broadphase_radius;
    if ((hit_end_max_z < hurt_start_copy.z) && (hit_end_max_z < hurt_end->z)) {
        return 0;
    }
block_39:
    // Solve closest points between the two segment axes.
    hit_delta.x = hit_end_x - hit_start_copy.x;
    hit_delta.y = hit_end->y - hit_start_copy.y;
    hit_delta.z = hit_end->z - hit_start_copy.z;
    hurt_end_y = hurt_end->y;
    start_delta_y = hit_start_copy.y - hurt_start_copy.y;
    hurt_delta_y = hurt_end_y - hurt_start_copy.y;
    hurt_end_x = hurt_end->x;
    hurt_delta_x = hurt_end_x - hurt_start_copy.x;
    segment_dot = hit_delta.y * hurt_delta_y;
    hurt_len_sq = hurt_delta_y * hurt_delta_y;
    hit_start_mid_x = hit_delta.x * hit_delta.x;
    hit_start_mid_y = hit_delta.y * hit_delta.y;
    hurt_end_z = hurt_end->z;
    start_delta_x = hit_start_copy.x - hurt_start_copy.x;
    hurt_delta_z = hurt_end_z - hurt_start_copy.z;
    segment_dot = (hit_delta.x * hurt_delta_x) + segment_dot;
    /* Cache 1.0 constant in a callee-save to avoid reloading it across the
     * several `hit_param = 1.0` / `hurt_param = 1.0` branches below. The
     * variable name is a borrow from the unused-after-broadphase-rejection
     * slot. */
    hit_start_min_z = lbColl_804D7A08;
    hurt_len_sq = (hurt_delta_x * hurt_delta_x) + hurt_len_sq;
    segment_dot = (hit_delta.z * hurt_delta_z) + segment_dot;
    hurt_len_sq = (hurt_delta_z * hurt_delta_z) + hurt_len_sq;
    hit_start_mid_z = hit_delta.z * hit_delta.z;
    start_delta_z = hit_start_copy.z - hurt_start_copy.z;
    hit_len_sq = hit_start_mid_x + hit_start_mid_y;
    hit_len_sq = hit_start_mid_z + hit_len_sq;
    hit_start_dot = hit_delta.y * start_delta_y;
    hit_start_dot = (hit_delta.x * start_delta_x) + hit_start_dot;
    hurt_start_dot =
        (hurt_delta_y * start_delta_y) + (hurt_delta_x * start_delta_x);
    hit_start_dot = (hit_delta.z * start_delta_z) + hit_start_dot;
    hurt_start_dot = (hurt_delta_z * start_delta_z) + hurt_start_dot;
    closest_denom = (hit_len_sq * hurt_len_sq) - (segment_dot * segment_dot);
    if ((hurt_len_sq < lbColl_804D79F0) && (hurt_len_sq > lbColl_804D79F4)) {
        is_hurt_segment_degenerate = 1;
    } else {
        is_hurt_segment_degenerate = 0;
    }
    if (is_hurt_segment_degenerate != 0) {
        if ((hit_len_sq < lbColl_804D79F0) && (hit_len_sq > lbColl_804D79F4)) {
            is_hit_segment_degenerate = 1;
        } else {
            is_hit_segment_degenerate = 0;
        }
        if (is_hit_segment_degenerate != 0) {
            hit_param = lbColl_804D79F8;
            hurt_param = hit_param;
        } else {
            hurt_param = lbColl_804D79F8;
            projected_hit_param = -hit_start_dot / hit_len_sq;
            hit_param = projected_hit_param;
            if (projected_hit_param > lbColl_804D7A00) {
                hit_param = hit_start_min_z;
            } else if (hit_param < lbColl_804D7A10) {
                hit_param = hurt_param;
            }
        }
    } else {
        if ((closest_denom < lbColl_804D79F0) &&
            (closest_denom > lbColl_804D79F4))
        {
            is_parallel = 1;
        } else {
            is_parallel = 0;
        }
        if (is_parallel != 0) {
            // For parallel axes, project the hit endpoint nearer the hurt
            // midpoint.
            hurt_mid_y = (float) ((lbColl_804D7A18 * (f64) hurt_delta_y) +
                                  (f64) hurt_start_copy.y);
            hurt_mid_x = (float) ((lbColl_804D7A18 * (f64) hurt_delta_x) +
                                  (f64) hurt_start_copy.x);
            hit_start_mid_y = hit_start_copy.y - hurt_mid_y;
            hurt_mid_z = (float) ((lbColl_804D7A18 * (f64) hurt_delta_z) +
                                  (f64) hurt_start_copy.z);
            hit_end_mid_y = hit_end->y - hurt_mid_y;
            hit_start_mid_x = hit_start_copy.x - hurt_mid_x;
            hit_end_mid_x = hit_end->x - hurt_mid_x;
            hit_start_mid_z = hit_start_copy.z - hurt_mid_z;
            hit_end_mid_z = hit_end->z - hurt_mid_z;
            if (((hit_start_mid_z * hit_start_mid_z) +
                 ((hit_start_mid_x * hit_start_mid_x) +
                  (hit_start_mid_y * hit_start_mid_y))) <
                ((hit_end_mid_z * hit_end_mid_z) +
                 ((hit_end_mid_x * hit_end_mid_x) +
                  (hit_end_mid_y * hit_end_mid_y))))
            {
                Vec3 a2;
                Vec3 d1;
                Vec3 c3;
                c3 = *hurt_start;
                hit_param = lbColl_804D79F8;
                d1.x = hurt_end_x - hurt_start->x;
                d1.y = hurt_end_y - hurt_start->y;
                d1.z = hurt_end_z - hurt_start->z;
                {
                    float dot;

                    a2 = *hit_start;
                    dot = (d1.z * (c3.z - a2.z)) +
                          ((d1.x * (c3.x - a2.x)) + (d1.y * (c3.y - a2.y)));
                    hit_end_mid_x = d1.x * d1.x;
                    hurt_param_from_hit_start =
                        -dot /
                        ((d1.z * d1.z) + (hit_end_mid_x + (d1.y * d1.y)));
                }
                if (hurt_param_from_hit_start > lbColl_804D7A00) {
                    hurt_param_from_hit_start = hit_start_min_z;
                } else if (hurt_param_from_hit_start < lbColl_804D7A10) {
                    hurt_param_from_hit_start = hit_param;
                }
                hurt_param = hurt_param_from_hit_start;
            } else {
                Vec3 b0;
                Vec3 d1;
                Vec3 c2;
                c2 = *hurt_start;
                hit_param = hit_start_min_z;
                d1.x = hurt_end_x - hurt_start->x;
                d1.y = hurt_end_y - hurt_start->y;
                d1.z = hurt_end_z - hurt_start->z;
                {
                    float dot;

                    b0 = *hit_end;
                    dot = (d1.z * (c2.z - b0.z)) +
                          ((d1.x * (c2.x - b0.x)) + (d1.y * (c2.y - b0.y)));
                    hurt_param_from_hit_end =
                        -dot /
                        ((d1.z * d1.z) + ((d1.x * d1.x) + (d1.y * d1.y)));
                }
                if (hurt_param_from_hit_end > lbColl_804D7A00) {
                    hurt_param_from_hit_end = hit_param;
                } else if (hurt_param_from_hit_end < lbColl_804D7A10) {
                    hurt_param_from_hit_end = lbColl_804D79F8;
                }
                hurt_param = hurt_param_from_hit_end;
            }
        } else {
            hit_param =
                (hit_param_candidate = ((segment_dot * hurt_start_dot) -
                                        (hurt_len_sq * hit_start_dot)) /
                                       closest_denom);
            hurt_param = ((hit_len_sq * hurt_start_dot) -
                          (segment_dot * hit_start_dot)) /
                         closest_denom;
            if ((hit_param_candidate > lbColl_804D7A00) ||
                (hit_param < lbColl_804D7A10) ||
                (hurt_param > lbColl_804D7A00) ||
                (hurt_param < lbColl_804D7A10))
            {
                float candidate_hurt_param;
                float hit_endpoint_dist_sq;
                float hit_endpoint_param;
                float hurt_endpoint_param;
                float hurt_endpoint_dist_sq;

                // If the unconstrained solution leaves either segment, compare
                // the nearest endpoint projection from each axis.
                if (hit_param < lbColl_804D7A10) {
                    hit_endpoint_param = lbColl_804D79F8;
                    hit_endpoint_dist_sq =
                        lbColl_80005EBC(hurt_start, hurt_end, hit_start,
                                        &candidate_hurt_param);
                } else {
                    hit_endpoint_param = hit_start_min_z;
                    hit_endpoint_dist_sq = lbColl_80005EBC(
                        hurt_start, hurt_end, hit_end, &candidate_hurt_param);
                }
                if (hurt_param < lbColl_804D7A10) {
                    hurt_endpoint_param = lbColl_804D79F8;
                    hurt_endpoint_dist_sq = lbColl_80005EBC(
                        hit_start, hit_end, hurt_start, &candidate_hit_param);
                } else {
                    hurt_endpoint_param = hit_start_min_z;
                    hurt_endpoint_dist_sq = lbColl_80005EBC(
                        hit_start, hit_end, hurt_end, &candidate_hit_param);
                }
                if (hit_endpoint_dist_sq < hurt_endpoint_dist_sq) {
                    hit_param = hit_endpoint_param;
                    hurt_param = candidate_hurt_param;
                } else {
                    hit_param = candidate_hit_param;
                    hurt_param = hurt_endpoint_param;
                }
            }
        }
    }
    hit_closest->x = (hit_delta.x * hit_param) + hit_start_copy.x;
    hit_closest->y = (hit_delta.y * hit_param) + hit_start_copy.y;
    hit_closest->z = (hit_delta.z * hit_param) + hit_start_copy.z;
    hurt_closest->x = (hurt_delta_x * hurt_param) + hurt_start_copy.x;
    hurt_closest->y = (hurt_delta_y * hurt_param) + hurt_start_copy.y;
    hurt_closest->z = (hurt_delta_z * hurt_param) + hurt_start_copy.z;
    closest_delta_y = hit_closest->y - hurt_closest->y;
    closest_delta_x = hit_closest->x - hurt_closest->x;
    closest_delta_z = hit_closest->z - hurt_closest->z;
    closest_dist_sq = (closest_delta_z * closest_delta_z) +
                      ((closest_delta_x * closest_delta_x) +
                       (closest_delta_y * closest_delta_y));
    if (closest_dist_sq > lbColl_804D79F8) {
        volatile float sp38;

        closest_rsqrt_estimate = __frsqrte(closest_dist_sq);
        closest_rsqrt_step1 =
            lbColl_804D7A18 * closest_rsqrt_estimate *
            -(((f64) closest_dist_sq *
               (closest_rsqrt_estimate * closest_rsqrt_estimate)) -
              lbColl_804D7A20);
        closest_rsqrt_step2 = lbColl_804D7A18 * closest_rsqrt_step1 *
                              -(((f64) closest_dist_sq *
                                 (closest_rsqrt_step1 * closest_rsqrt_step1)) -
                                lbColl_804D7A20);
        sp38 = (float) ((f64) closest_dist_sq *
                        (lbColl_804D7A18 * closest_rsqrt_step2 *
                         -(((f64) closest_dist_sq *
                            (closest_rsqrt_step2 * closest_rsqrt_step2)) -
                           lbColl_804D7A20)));
        closest_dist = sp38;
    } else {
        closest_dist = closest_dist_sq;
    }
    if ((closest_dist < lbColl_804D79F0) && (closest_dist > lbColl_804D79F4)) {
        is_zero_distance = 1;
    } else {
        is_zero_distance = 0;
    }
    if (is_zero_distance != 0) {
        *out_overlap = (hit_radius + hurt_radius) - closest_dist;
        *out_contact_pos = *hit_closest;
        return 1;
    }

    // Measure the hurt radius in the matrix's local space for scaled bones.
    HSD_MtxInverse(hurt_mtx, inv_hurt_mtx);
    PSMTXMultVec(inv_hurt_mtx, hit_closest, &hit_start_copy);
    PSMTXMultVec(inv_hurt_mtx, hurt_closest, &hit_delta);
    local_delta_y = hit_start_copy.y - hit_delta.y;
    local_delta_x = hit_start_copy.x - hit_delta.x;
    local_delta_z = hit_start_copy.z - hit_delta.z;
    local_dist_sq =
        (local_delta_z * local_delta_z) +
        ((local_delta_x * local_delta_x) + (local_delta_y * local_delta_y));
    if (local_dist_sq > lbColl_804D79F8) {
        volatile float sp34;

        local_rsqrt_estimate = __frsqrte(local_dist_sq);
        local_rsqrt_step1 = lbColl_804D7A18 * local_rsqrt_estimate *
                            -(((f64) local_dist_sq *
                               (local_rsqrt_estimate * local_rsqrt_estimate)) -
                              lbColl_804D7A20);
        local_rsqrt_step2 =
            lbColl_804D7A18 * local_rsqrt_step1 *
            -(((f64) local_dist_sq * (local_rsqrt_step1 * local_rsqrt_step1)) -
              lbColl_804D7A20);
        sp34 = (float) ((f64) local_dist_sq *
                        (lbColl_804D7A18 * local_rsqrt_step2 *
                         -(((f64) local_dist_sq *
                            (local_rsqrt_step2 * local_rsqrt_step2)) -
                           lbColl_804D7A20)));
        local_dist = sp34;
    } else {
        local_dist = local_dist_sq;
    }
    scaled_hurt_radius = (hurt_radius * closest_dist) / local_dist;
    contact_lerp = scaled_hurt_radius / closest_dist;
    allowed_distance = hit_radius + scaled_hurt_radius;
    hurt_closest_x = hurt_closest->x;
    *out_overlap = allowed_distance - closest_dist;
    out_contact_pos->x =
        (contact_lerp * (hit_closest->x - hurt_closest_x)) + hurt_closest_x;
    hurt_closest_y = hurt_closest->y;
    out_contact_pos->y =
        (contact_lerp * (hit_closest->y - hurt_closest_y)) + hurt_closest_y;
    hurt_closest_z = hurt_closest->z;
    out_contact_pos->z =
        (contact_lerp * (hit_closest->z - hurt_closest_z)) + hurt_closest_z;
    if (allowed_distance < closest_dist) {
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

        diff_ba.x = b->x - a->x;
        diff_ba.y = b->y - a->y;
        diff_ba.z = b->z - a->z;

        dot_diff_cb = diff_cb.x * diff_cb.x + diff_cb.y * diff_cb.y +
                      diff_cb.z * diff_cb.z;

        if (nearzero(dot_diff_cb)) {
            scl = 0.0f;
        } else {
            n0 = 2.0f * diff_cb.x * diff_ba.x + 2.0f * diff_cb.y * diff_ba.y +
                 2.0f * diff_cb.z * diff_ba.z;

            ba_dot = diff_ba.x * diff_ba.x + diff_ba.y * diff_ba.y +
                     diff_ba.z * diff_ba.z;

            n1 = n0 * n0 -
                 (4.0f * dot_diff_cb * -(offset_dist * offset_dist - ba_dot));

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

bool lbColl_80007B78(Mtx a, struct Fighter_x1614_t* b, float x, float y)
{
    /// @todo Eliminate casts.
    return lbColl_800067F8(&b->x14, &b->x8, (Vec3*) &a[1][1], (Vec3*) &a[0][2],
                           &b->x20, (Vec3*) &a[1][4], b->x0 * y, a[0][0] * x,
                           x);
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

    return lbColl_80006E58(&arg0->x58,            // hit_start
                           &arg0->x4C,            // hit_end
                           &shield_hit->pos,      // hurt_start
                           &shield_hit->pos,      // hurt_end
                           &sp74,                 // hit_closest
                           &sp68,                 // hurt_closest
                           var_r9,                // hurt_mtx
                           &arg0->hurt_coll_pos,  // out_contact_pos
                           &arg0->coll_distance,  // out_overlap
                           var_f1,                // hit_radius
                           shield_hit->size,      // hurt_radius
                           lbColl_804D7A34 * arg5 // broadphase_scale
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

bool lbColl_80008248(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2, f32 arg3,
                     f32 arg4, f32 arg5)
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
    return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos, &arg1->b_pos,
                           &sp70, &sp64, var_r9, &arg0->hurt_coll_pos,
                           &arg0->coll_distance, var_f1, arg1->scale,
                           3.0f * arg4);
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

extern GXColor lbColl_804D36CC;
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

void lbColl_80008DA4(GXColor* arg0, GXColor* arg1)
{
    GXColor sp10;
    GXBlendMode var_r3;
    u8 var_r5;

    sp10 = lbColl_804D7A50;
    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_DISABLE);
    GXSetFog(GX_FOG_NONE, 0.0F, 0.0F, 0.0F, 0.0F, sp10);
    if (arg0->a < 0xFF) {
        var_r3 = GX_BM_BLEND;
    } else {
        var_r3 = GX_BM_NONE;
    }
    GXSetBlendMode(var_r3, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    if (arg0->a < 0xFF) {
        var_r5 = 0;
    } else {
        var_r5 = 1;
    }
    GXSetZMode(1, GX_LEQUAL, var_r5);
    GXSetZCompLoc(0);
    GXSetNumTexGens(0);
    GXSetTevClampMode(0, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColor(GX_TEVREG0, *arg0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0,
                    GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ONE, GX_CA_A0, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetNumChans(1);
    sp10 = *arg1;
    GXSetChanAmbColor(GX_COLOR0A0, sp10);
    sp10.r = 0xFF;
    sp10.g = 0xFF;
    sp10.b = 0xFF;
    sp10.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, sp10);
    if (arg0->a < 0xFF) {
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_NONE,
                      GX_AF_NONE);
    } else {
        GXSetChanCtrl(GX_COLOR0A0, 1, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP,
                      GX_AF_NONE);
    }
}

static inline bool isSmall(float x)
{
    if (x < 0.00001F && x > -0.00001F) {
        return true;
    } else {
        return false;
    }
}

void lbColl_80008FC8(Vec3 arg0, Vec3 arg1, GXColor* arg2, GXColor* arg3,
                     f32 arg4)
{
    Mtx sp104;
    Mtx spD4;
    Mtx spA4;
    Mtx sp74;
    Mtx sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;

    f32 var_f31;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    lbColl_80008DA4(arg2, arg3);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp104);
    PSMTXScale(spA4, arg4, arg4, arg4);
    sp38.x = arg0.x - arg1.x;
    sp38.y = arg0.y - arg1.y;
    sp38.z = arg0.z - arg1.z;
    var_f31 = sqrtf(SQ(sp38.x) + SQ(sp38.y) + SQ(sp38.z));
    if (isSmall(var_f31) ||
        (isSmall(sp38.x) && isSmall(sp38.y) && isSmall(sp38.z)))
    {
        PSMTXIdentity(sp44);
        sp44[0][0] = -1.0F;
        sp44[1][0] = 0.0F;
        sp44[2][0] = 0.0F;
        sp44[0][1] = 0.0F;
        sp44[1][1] = 1.0F;
        sp44[2][1] = 0.0F;
        sp44[0][2] = 0.0F;
        sp44[1][2] = 0.0F;
        sp44[2][2] = -1.0F;
        PSMTXConcat(sp44, spA4, spD4);
    } else {
        PSMTXScale(sp74, var_f31, arg4, arg4);
        if (isSmall(sp38.x) && isSmall(sp38.y)) {
            sp2C.x = sp38.z;
            sp2C.y = 0.0f;
            sp2C.z = 0.0f;
        } else {
            sp2C.x = sp38.y;
            sp2C.y = -sp38.x;
            sp2C.z = 0.0f;
        }
        PSVECNormalize(&sp38, &sp38);
        PSVECNormalize(&sp2C, &sp2C);
        PSVECCrossProduct(&sp38, &sp2C, &sp20);
        PSMTXIdentity(sp44);
        sp44[0][0] = sp38.x;
        sp44[1][0] = sp38.y;
        sp44[2][0] = sp38.z;
        sp44[0][1] = sp2C.x;
        sp44[1][1] = sp2C.y;
        sp44[2][1] = sp2C.z;
        sp44[0][2] = sp20.x;
        sp44[1][2] = sp20.y;
        sp44[2][2] = sp20.z;
        PSMTXConcat(sp44, spA4, spD4);
        PSMTXConcat(sp44, sp74, sp74);
        sp44[0][0] = -sp38.x;
        sp44[1][0] = -sp38.y;
        sp44[2][0] = -sp38.z;
        sp44[0][1] = sp2C.x;
        sp44[1][1] = sp2C.y;
        sp44[2][1] = sp2C.z;
        sp44[0][2] = -sp20.x;
        sp44[1][2] = -sp20.y;
        sp44[2][2] = -sp20.z;
        PSMTXConcat(sp44, spA4, spA4);
    }
    PSMTXTrans(sp44, arg0.x, arg0.y, arg0.z);
    PSMTXConcat(sp44, spD4, spD4);
    PSMTXTrans(sp44, arg1.x, arg1.y, arg1.z);
    PSMTXConcat(sp44, spA4, spA4);
    PSMTXTrans(sp44, 0.5 * (arg0.x + arg1.x), 0.5 * (arg0.y + arg1.y),
               0.5 * (arg0.z + arg1.z));
    PSMTXConcat(sp44, sp74, sp74);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_803B9940, 6);
    GXSetArray(GX_VA_NRM, lbColl_803B9AE0, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp104, spD4, spD4);
    GXLoadPosMtxImm(spD4, 0);
    HSD_MtxInverse(spD4, spD4);
    PSMTXTranspose(spD4, spD4);
    GXLoadNrmMtxImm(spD4, 0);
    GXCallDisplayList(lbColl_803B9C80, 0x120);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_803B9940, 6);
    GXSetArray(GX_VA_NRM, lbColl_803B9AE0, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp104, spA4, spA4);
    GXLoadPosMtxImm(spA4, 0);
    HSD_MtxInverse(spA4, spA4);
    PSMTXTranspose(spA4, spA4);
    GXLoadNrmMtxImm(spA4, 0);
    GXCallDisplayList(lbColl_803B9C80, 0x120);
    if (!isSmall(var_f31)) {
        GXClearVtxDesc();
        GXSetArray(GX_VA_POS, lbl_803B9DA0, 6);
        GXSetArray(GX_VA_NRM, lbColl_803B9EC0, 6);
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 6);
        PSMTXConcat(sp104, sp74, sp74);
        GXLoadPosMtxImm(sp74, 0);
        HSD_MtxInverse(sp74, sp74);
        PSMTXTranspose(sp74, sp74);
        GXLoadNrmMtxImm(sp74, 0);
        GXCallDisplayList(lbColl_803B9F20, 0xA0);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

void lbColl_800096B4(MtxPtr arg0, Vec3 arg1, Vec3 arg2, GXColor* arg3,
                     GXColor* arg4, f32 arg5)
{
    Mtx sp108;
    Mtx spD8;
    Mtx spA8;
    Mtx sp78;
    Mtx sp48;
    Vec3 sp3C;
    Vec3 sp30;
    Vec3 sp24;
    f32 var_f31;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    lbColl_80008DA4(arg3, arg4);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp108);
    PSMTXScale(spA8, arg5, arg5, arg5);
    sp3C.x = arg1.x - arg2.x;
    sp3C.y = arg1.y - arg2.y;
    sp3C.z = arg1.z - arg2.z;
    var_f31 = sqrtf(SQ(sp3C.x) + SQ(sp3C.y) + SQ(sp3C.z));
    if (isSmall(var_f31) ||
        (isSmall(sp3C.x) && isSmall(sp3C.y) && isSmall(sp3C.z)))
    {
        PSMTXIdentity(sp48);
        sp48[0][0] = -1.0F;
        sp48[1][0] = 0.0F;
        sp48[2][0] = 0.0F;
        sp48[0][1] = 0.0F;
        sp48[1][1] = 1.0F;
        sp48[2][1] = 0.0F;
        sp48[0][2] = 0.0F;
        sp48[1][2] = 0.0F;
        sp48[2][2] = -1.0F;
        PSMTXConcat(sp48, spA8, spD8);
    } else {
        PSMTXScale(sp78, var_f31, arg5, arg5);
        if (isSmall(sp3C.x) && isSmall(sp3C.y)) {
            sp30.x = sp3C.z;
            sp30.y = 0.0F;
            sp30.z = 0.0F;
        } else {
            sp30.x = sp3C.y;
            sp30.y = -sp3C.x;
            sp30.z = 0.0F;
        }
        PSVECNormalize(&sp3C, &sp3C);
        PSVECNormalize(&sp30, &sp30);
        PSVECCrossProduct(&sp3C, &sp30, &sp24);
        PSMTXIdentity(sp48);
        sp48[0][0] = sp3C.x;
        sp48[1][0] = sp3C.y;
        sp48[2][0] = sp3C.z;
        sp48[0][1] = sp30.x;
        sp48[1][1] = sp30.y;
        sp48[2][1] = sp30.z;
        sp48[0][2] = sp24.x;
        sp48[1][2] = sp24.y;
        sp48[2][2] = sp24.z;
        PSMTXConcat(sp48, spA8, spD8);
        PSMTXConcat(sp48, sp78, sp78);
        sp48[0][0] = -sp3C.x;
        sp48[1][0] = -sp3C.y;
        sp48[2][0] = -sp3C.z;
        sp48[0][1] = sp30.x;
        sp48[1][1] = sp30.y;
        sp48[2][1] = sp30.z;
        sp48[0][2] = -sp24.x;
        sp48[1][2] = -sp24.y;
        sp48[2][2] = -sp24.z;
        PSMTXConcat(sp48, spA8, spA8);
    }
    PSMTXTrans(sp48, arg1.x, arg1.y, arg1.z);
    PSMTXConcat(sp48, spD8, spD8);
    PSMTXTrans(sp48, arg2.x, arg2.y, arg2.z);
    PSMTXConcat(sp48, spA8, spA8);
    PSMTXTrans(sp48, 0.5 * (arg1.x + arg2.x), 0.5 * (arg1.y + arg2.y),
               0.5 * (arg1.z + arg2.z));
    PSMTXConcat(sp48, sp78, sp78);
    PSMTXConcat(arg0, spD8, spD8);
    PSMTXConcat(arg0, spA8, spA8);
    PSMTXConcat(arg0, sp78, sp78);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_803B9940, 6);
    GXSetArray(GX_VA_NRM, lbColl_803B9AE0, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp108, spD8, spD8);
    GXLoadPosMtxImm(spD8, 0);
    HSD_MtxInverse(spD8, spD8);
    PSMTXTranspose(spD8, spD8);
    GXLoadNrmMtxImm(spD8, 0);
    GXCallDisplayList(lbColl_803B9C80, 0x120);
    GXClearVtxDesc();
    GXSetArray(GX_VA_POS, lbColl_803B9940, 6);
    GXSetArray(GX_VA_NRM, lbColl_803B9AE0, 6);
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 0xE);
    PSMTXConcat(sp108, spA8, spA8);
    GXLoadPosMtxImm(spA8, 0);
    HSD_MtxInverse(spA8, spA8);
    PSMTXTranspose(spA8, spA8);
    GXLoadNrmMtxImm(spA8, 0);
    GXCallDisplayList(lbColl_803B9C80, 0x120);
    if (!isSmall(var_f31)) {
        GXClearVtxDesc();
        GXSetArray(GX_VA_POS, lbl_803B9DA0, 6);
        GXSetArray(GX_VA_NRM, lbColl_803B9EC0, 6);
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA4, 0xE);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_TEX_S, GX_RGBA4, 6);
        PSMTXConcat(sp108, sp78, sp78);
        GXLoadPosMtxImm(sp78, 0);
        HSD_MtxInverse(sp78, sp78);
        PSMTXTranspose(sp78, sp78);
        GXLoadNrmMtxImm(sp78, 0);
        GXCallDisplayList(lbColl_803B9F20, 0xA0);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

void lbColl_80009DD4(Vec3* v0, Vec3* v1, GXColor* clr)
{
    Mtx viewMtx;
    float x1, x0, y0, z0, y1;
    u8 r, g, b, a;

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    PAD_STACK(32);
    lbColl_80008DA4(clr, clr);
    HSD_ClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetCurrentMtx(0);
    GXSetCullMode(GX_CULL_NONE);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), viewMtx);
    GXLoadPosMtxImm(viewMtx, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    z0 = v0->z;
    y0 = v0->y;
    x0 = v0->x;
    GXPosition3f32(x0, y0, z0);
    a = clr->a;
    b = clr->b;
    g = clr->g;
    r = clr->r;
    GXColor4u8(r, g, b, a);

    x1 = v1->x;
    GXPosition3f32(x1, y0, z0);
    GXColor4u8(r, g, b, a);

    y1 = v1->y;
    GXPosition3f32(x1, y1, z0);
    GXColor4u8(r, g, b, a);

    GXPosition3f32(x0, y1, z0);
    GXColor4u8(r, g, b, a);

    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
}

extern GXColor lbColl_804D36A0;
extern GXColor lbColl_804D36A4;
extern GXColor lbColl_804D36A8;
extern GXColor lbColl_804D36DC;

bool lbColl_80009F54(HitCapsule* hit, u32 arg1, float arg8)
{
    GXColor* var_r5;
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        switch (hit->element) {
        case HitElement_Catch:
            var_r5 = &lbColl_804D36A4;
            break;
        case HitElement_Inert:
            var_r5 = &lbColl_804D36DC;
            break;
        default:
            var_r5 = &lbColl_804D36A0;
            break;
        }

        if (var_r5->a == 0xFF) {
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
            lbColl_80008FC8(hit->x58, hit->x4C, var_r5, &lbColl_804D36A8,
                            var_f1);
            return 1;
        }
    }
    return 0;
}

extern GXColor lbColl_804D36E8;
extern GXColor lbColl_804D36EC;

static inline void lbColl_DrawHitResult(MtxPtr mtx, Vec3* a, Vec3* b,
                                        GXColor* c0, GXColor* c1, f32 size)
{
    Vec3 sp30;
    Vec3 sp24;
    Mtx sp3C;

    HSD_MtxInverse(mtx, sp3C);
    PSMTXMultVec(sp3C, a, &sp30);
    PSMTXMultVec(sp3C, b, &sp24);
    lbColl_800096B4(mtx, sp30, sp24, c0, c1, size);
}

bool lbColl_8000A044(HitCapsule* hit, u32 arg1, float arg8)
{
    float var_f1;
    u32 var_r0;

    if (hit->state != HitCapsule_Disabled && !hit->x43_b2) {
        if (lbColl_804D36E8.a == 0xFF) {
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
            lbColl_80008FC8(hit->x58, hit->x4C, &lbColl_804D36E8,
                            &lbColl_804D36EC, var_f1);
            return 1;
        }
    }
    return 0;
}

bool lbColl_8000A244(HurtCapsule* hurt, u32 arg1, Mtx arg2, float arg3)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;
    float temp_f31;
    MtxPtr var_r28;
    GXColor* temp_r31_2;
    u32 var_r0;
    GXColor* temp_r3;

    temp_r3 = lbColl_803B9928[hurt->state].pad;
    if (temp_r3->a == 0xFF) {
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
        lbColl_DrawHitResult(var_r28, &sp90, &sp84, temp_r3, temp_r31_2,
                             temp_f31);
        return true;
    }
    return false;
}

static GXColor lbColl_804D36F8 = { 0xFF, 0, 0, 0x80 };
static GXColor lbColl_804D36FC = { 0x80, 0, 0, 0x80 };

bool lbColl_8000A10C(struct lbColl_8000A10C_arg0_t* arg0, u32 arg1, f32 arg2)
{
    GXColor* c = &lbColl_804D36F8;
    u32 var_r0;
    if (c->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        lbColl_80008FC8(arg0->x14, arg0->x8, c, &lbColl_804D36FC,
                        arg0->x0 * arg2);
        return true;
    }
    return false;
}

static GXColor lbColl_804D36F0 = { 0xFF, 0xFF, 0, 0x80 };
static GXColor lbColl_804D36F4 = { 0x80, 0x80, 0, 0x80 };

bool lbColl_8000A1A8(struct Fighter_x1614_t* arg0, int arg1, f32 scale_y)
{
    u32 var_r0;

    if (lbColl_804D36F0.a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        lbColl_80008FC8(arg0->x14, arg0->x8, &lbColl_804D36F0,
                        &lbColl_804D36F4, arg0->x0 * scale_y);
        return true;
    }
    return false;
}

GXColor lbColl_804D36E0 = { 0 };
GXColor lbColl_804D36E4 = { 0x80, 0x40, 0x00, 0x80 };

bool lbColl_8000A460(Fighter_x1670_t* hurt, u32 arg1)
{
    u32 var_r0;

    GXColor* r31 = &lbColl_804D36E0;
    GXColor* r30 = &lbColl_804D36E4;

    if (r31->a == 0xFF) {
        var_r0 = 0;
    } else {
        var_r0 = 2;
    }
    if (var_r0 == arg1) {
        HSD_JObjSetupMatrix(hurt->jobj);
        lbColl_800096B4(HSD_JObjGetMtxPtr(hurt->jobj), hurt->v1, hurt->v1, r31,
                        r30, hurt->v2);
        return true;
    }
    return false;
}

bool lbColl_8000A584(HurtCapsule* hurt, u32 arg1, u32 arg2, Mtx arg3, f32 arg8)
{
    PAD_STACK(4);
    {
        Mtx spA0;
        Vec3 sp94;
        Vec3 sp88;
        f32 temp_f31;
        GXColor* temp_r31_2;
        u32 var_r0;
        u32 var_r4;
        GXColor* temp_r3;

        var_r4 = arg1;
        if (hurt->state == Intangible) {
            var_r4 = 2;
        }
        temp_r3 = lbColl_803B9928[var_r4].pad;
        if (temp_r3->a == 0xFF) {
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
                hurt = (HurtCapsule*) spA0;
            } else {
                hurt = (HurtCapsule*) HSD_JObjGetMtxPtr(hurt->bone);
            }
            lbColl_DrawHitResult((MtxPtr) hurt, &sp94, &sp88, temp_r3,
                                 temp_r31_2, temp_f31);
            return true;
        }
        return false;
    }
}

bool lbColl_8000A78C(HitResult* hit, u32 arg1, Mtx arg2, f32 pos_z)
{
    f32 temp_f31;
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;
    MtxPtr var_r31;
    u32 var_r0;

    if (lbColl_804D36C4.a == 0xFF) {
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
            hit->skip_update_pos = true;
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
        lbColl_DrawHitResult(var_r31, &sp90, &sp84, &lbColl_804D36C4,
                             &lbColl_804D36C8, temp_f31);
        return true;
    }
    return false;
}

bool lbColl_8000A95C(HitResult* hit, u32 arg1, Mtx arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;

    f32 temp_f31;
    MtxPtr var_r31;
    u32 var_r0;

    if (lbColl_804D36CC.a == 0xFF) {
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
        lbColl_DrawHitResult(var_r31, &sp90, &sp84, &lbColl_804D36CC,
                             &lbColl_804D36D0, temp_f31);
        return true;
    }
    return false;
}

bool lbColl_8000AB2C(HitResult* hit, u32 arg1, MtxPtr arg2, f32 pos_z)
{
    Mtx sp9C;
    Vec3 sp90;
    Vec3 sp84;

    f32 temp_f31;
    MtxPtr var_r31;
    u32 var_r0;

    if (lbColl_804D36D4.a == 0xFF) {
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
            hit->skip_update_pos = true;
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
        lbColl_DrawHitResult(var_r31, &sp90, &sp84, &lbColl_804D36D4,
                             &lbColl_804D36D8, temp_f31);
        return true;
    }
    return false;
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
