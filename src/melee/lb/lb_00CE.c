#include "lb/lb_00CE.h"

#include <platform.h>

#include "MSL/math_ppc.h"

#include <baselib/forward.h>

#include <math.h>
#include <trigf.h>

f32 expf(f32 arg8)
{
    f32 temp_f5;
    f32 var_f1;
    f32 var_f3;
    f32 var_f4;
    f32 var_f6;
    s32 temp_r3;
    s32 var_r4;
    s32 var_r5;

    var_f1 = arg8;
    var_r5 = 2;
    var_f6 = 1.0f;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
        var_r4 = 1;
    } else {
        var_r4 = 0;
    }
    var_f4 = var_f1;
    var_f3 = 1.0f + var_f1;
    do {
        temp_r3 = var_r5;
        var_f4 *= var_f1;
        temp_f5 = var_f3;
        var_r5 += 1;
        var_f6 *= (f32) temp_r3;
        var_f3 += var_f4 / var_f6;
    } while (var_f3 != temp_f5);
    if (var_r4 != 0) {
        var_f3 = 1.0f / var_f3;
    }
    return var_f3;
}

f32 powf(f32 arg0, f32 arg1)
{
    f32 temp_f1;
    f32 temp_f5;
    f32 var_f4;
    f32 var_f6;
    s32 var_r4;

    if (arg0 == 0.0f) {
        return 0.0f;
    }
    var_r4 = 1;
    var_f6 = (arg0 - 1.0f) / (1.0f + arg0);
    var_f4 = var_f6;
    temp_f5 = var_f6 * var_f6;
    do {
        var_r4 += 2;
        var_f6 *= temp_f5;
        temp_f1 = var_f4;
        var_f4 += var_f6 / (f32) var_r4;
    } while (var_f4 != temp_f1);
    return expf(arg1 * (2.0f * var_f4));
}

s32 powi(s32 arg0, s32 arg1)
{
    s32 temp_r5;
    s32 var_ctr_2;
    s32 var_r6;
    s32 var_r7;
    u32 var_ctr;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 >= 0) {
        var_r6 = 0;
        var_r7 = 1;
        if (arg1 > 0) {
            temp_r5 = arg1 - 8;
            if (arg1 > 8) {
                var_ctr = (u32) (temp_r5 + 7) >> 3U;
                if (temp_r5 > 0) {
                    do {
                        var_r7 = var_r7 * arg0 * arg0 * arg0 * arg0 * arg0 *
                                 arg0 * arg0 * arg0;
                        var_r6 += 8;
                        var_ctr -= 1;
                    } while (var_ctr != 0);
                }
            }
            var_ctr_2 = arg1 - var_r6;
            if (var_r6 < arg1) {
                do {
                    var_r7 *= arg0;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
            }
        }
        return var_r7;
    }
    return 0;
}

f32 lb_8000D008(f32 point_y_in, f32 point_x)
{
    f32 var_f2;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r31;

    f32 point_y = point_y_in;
    if ((point_x < 0.00001f) && (point_x > -0.00001f)) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        if ((point_y < 0.00001f) && (point_y > -0.00001f)) {
            var_r0_3 = 1;
        } else {
            var_r0_3 = 0;
        }
        if (var_r0_3 != 0) {
            return 0.0f;
        }
        if (point_y < 0.0f) {
            var_r0 = -1;
        } else {
            var_r0 = 1;
        }
        return (f32) ((M_PI / 2) * (f64) var_r0);
    }
    if (point_x > 0.0f) {
        return atanf(point_y / point_x);
    }
    if (point_x < 0.0f) {
        var_f2 = point_y / point_x;
        if (var_f2 < 0.0f) {
            var_f2 = -var_f2;
        }
        if (point_y < 0.0f) {
            var_r31 = -1;
        } else {
            var_r31 = 1;
        }
        point_y = (f32) ((f64) var_r31 * (M_PI - atanf(var_f2)));
    }
    return point_y;
}

s32 lb_8000D148(f32 point0_x, f32 point0_y, f32 point1_x, f32 point1_y,
                f32 point2_x, f32 point2_y, f32 threshold)
{
    f32 dist_01;
    f32 var_f0;
    {
        f32 diff_01_y = point0_y - point1_y;
        f32 diff_01_x = point1_x - point0_x;
        f32 dist_squared_01 =
            (diff_01_x * diff_01_x) + (diff_01_y * diff_01_y);
        if (dist_squared_01 < 0.00001f) {
            return 0;
        }
        dist_01 = sqrtf(dist_squared_01);

        var_f0 = ((point0_x * point1_y) - (point0_y * point1_x)) +
                 ((diff_01_x * point2_x) + (diff_01_y * point2_y));
        if (var_f0 < 0.0f) {
            var_f0 = -var_f0;
        }
    }

    if ((var_f0 / dist_01) <= threshold) {
        f32 diff_02_x = point0_x - point2_x;
        f32 diff_02_y = point0_y - point2_y;
        f32 diff_12_x = point1_x - point2_x;
        f32 diff_12_y = point1_y - point2_y;
        f32 threshold_squared = threshold * threshold;
        f32 dist_squared_02 =
            (diff_02_x * diff_02_x) + (diff_02_y * diff_02_y);
        f32 dist_squared_12 =
            (diff_12_x * diff_12_x) + (diff_12_y * diff_12_y);
        if (dist_squared_02 < threshold_squared) {
            if (dist_squared_12 > threshold_squared) {
                return 1;
            }
            if (dist_squared_12 < threshold_squared) {
                return 0;
            }
            return 1;
        }
        if (dist_squared_02 > threshold_squared) {
            if (dist_squared_12 > threshold_squared) {
                // If an axis of point0 and point1 are on opposite sides of
                // point2, return true.
                if (((point0_x > point2_x) && (point1_x < point2_x)) ||
                    ((point0_x < point2_x) && (point1_x > point2_x)) ||
                    ((point0_y > point2_y) && (point1_y < point2_y)) ||
                    ((point0_y < point2_y) && (point1_y > point2_y)))
                {
                    return 1;
                }
                return 0;
            }
            if (dist_squared_12 < threshold_squared) {
                return 1;
            }
            return 1;
        }
        return 1;
    }
    return 0;
}
