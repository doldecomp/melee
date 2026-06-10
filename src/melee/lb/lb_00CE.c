#include "lb/lb_00CE.h"

#include <platform.h>

#include <baselib/forward.h>

#include <math.h>
#include <trigf.h>

static void float_order(Vec3* temp, s32 in1)
{
    f64 tmp1 = 3.14159265358979323846 / 2;
    f64 tmp2 = 3.14159265358979323846;
    temp->y = tmp1;
    temp->y = tmp2;
    temp->y = 1.0f;
    temp->y = 2.0f;
    temp->y = temp->y * in1;
}
static void float_order2(Vec3* temp)
{
    temp->y = 0.0f;
}
inline float sqrtf(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}
static void float_order3(Vec3* temp, f32 in)
{
    temp->y = sqrtf(in);
    temp->y = 0.00001f;
    temp->y = -0.00001f;
}

f32 expf(f32 arg8)
{
    f32 var_f1;
    f32 var_f3;
    f32 var_f4;
    f32 temp_f5;
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
    f32 var_f4;
    f32 temp_f5;
    s32 var_r4;
    f32 var_f6;

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

s32 powi(s32 base, s32 exponent)
{
    s32 i;
    s32 result;

    if (base == 0) {
        return 0;
    }
    if (exponent < 0) {
        goto return_zero;
    }

    i = 0;
    result = 1;

    for (; i < exponent; i++) {
        result *= base;
    }

    return result;

return_zero:
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
        return (f32) ((3.14159265358979323846 / 2) * (f64) var_r0);
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
        point_y =
            (f32) ((f64) var_r31 * (3.14159265358979323846 - atanf(var_f2)));
    }
    return point_y;
}

s32 lb_8000D148(f32 point0_x, f32 point0_y, f32 point1_x, f32 point1_y,
                f32 point2_x, f32 point2_y, f32 threshold)
{
    f32 dist_01;
    f32 var_f0;
    {
        f32 diff_01_x = point1_x - point0_x;
        f32 diff_01_y = point0_y - point1_y;
        f32 cross = point0_y * point1_x;

        dist_01 = (diff_01_x * diff_01_x) + (diff_01_y * diff_01_y);
        cross = (point0_x * point1_y) - cross;
        if (dist_01 < 0.00001f) {
            return 0;
        }
        dist_01 = sqrtf(dist_01);

        var_f0 = cross + ((diff_01_x * point2_x) + (diff_01_y * point2_y));
        if (var_f0 < 0.0f) {
            var_f0 = -var_f0;
        }
    }

    if ((var_f0 / dist_01) <= threshold) {
        f32 threshold_squared;
        f32 dist_squared_02;
        f32 dist_squared_12;

        dist_squared_02 = (point0_x - point2_x) * (point0_x - point2_x) +
                          (point0_y - point2_y) * (point0_y - point2_y);
        threshold_squared = threshold * threshold;
        dist_squared_12 = (point1_x - point2_x) * (point1_x - point2_x) +
                          (point1_y - point2_y) * (point1_y - point2_y);
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
