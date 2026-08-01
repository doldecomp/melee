#include "lb_E9F0.h"

#include <placeholder.h>

#include <sysdolphin/baselib/spline.h>

/**
 * @todo Emitted only to lay out the .sdata2 literal pool in retail order,
 * which follows per-type tangent helpers defined above #lbShadow_8000E9F0.
 */
static void sdata2_order(void)
{
    (void) -3.0f;
    (void) 4.0f;
    (void) 1.0f;
    (void) 3.0f;
    (void) 2.0f;
    (void) 0.5f;
    (void) 0.0f;
    (void) S32_TO_F32;
}

/// @todo Case 1 emits its @c fnmsubs after the @c t2 multiply.
void lbShadow_8000E9F0(Vec3* p, HSD_Spline* spline, f32 u)
{
    Vec3* cp;
    s16 idx;
    f32 t;
    f32 orig_u;

    PAD_STACK(8);

    if (u < 0.0F || u > 1.0F) {
        return;
    }

    orig_u = u;
    u *= spline->numcv - 1;
    idx = (s16) u;
    t = u - (f32) idx;

    switch (spline->type) {
    case 0:
        if (orig_u == 1.0F) {
            idx -= 1;
        }
        cp = &spline->cv[idx];
        p->x = cp[1].x - cp[0].x;
        p->y = cp[1].y - cp[0].y;
        p->z = cp[1].z - cp[0].z;
        return;
    case 1: {
        f32 t2, u_1, bez1, bez0, bez2;
        cp = &spline->cv[idx * 3];
        t2 = 3.0F * (t * t);
        bez1 = 1.0F - (4.0F * t);
        u_1 = t - 1.0F;
        bez0 = -3.0F * u_1 * u_1;
        bez1 = 3.0F * (bez1 + t2);
        bez2 = 3.0F * ((2.0F * t) - t2);
        p->x = (cp[3].x * t2) +
               ((cp[2].x * bez2) + ((cp[0].x * bez0) + (cp[1].x * bez1)));
        p->y = (cp[3].y * t2) +
               ((cp[2].y * bez2) + ((cp[0].y * bez0) + (cp[1].y * bez1)));
        p->z = (cp[3].z * t2) +
               ((cp[2].z * bez2) + ((cp[0].z * bez0) + (cp[1].z * bez1)));
        return;
    }
    case 2: {
        f32 b3, b2, b1, b0, half, u_1, u2;
        cp = &spline->cv[idx];
        u2 = t * t;
        u_1 = 1.0F - t;
        half = 0.5F;
        {
            f32 b0_tmp = u_1 * (-half * u_1);
            b0 = b0_tmp;
        }
        b1 = half * ((3.0F * u2) - (4.0F * t));
        b2 = half * (1.0F + ((-3.0F * u2) + (2.0F * t)));
        b3 = half * u2;
        p->x = (cp[3].x * b3) +
               ((cp[2].x * b2) + ((cp[0].x * b0) + (cp[1].x * b1)));
        p->y = (cp[3].y * b3) +
               ((cp[2].y * b2) + ((cp[0].y * b0) + (cp[1].y * b1)));
        p->z = (cp[3].z * b3) +
               ((cp[2].z * b2) + ((cp[0].z * b0) + (cp[1].z * b1)));
        return;
    }
    case 3: {
        f32 u2 = t * t;
        f32 tension = spline->tension;
        f32 car1, car0, car3, car2;
        cp = &spline->cv[idx];
        car0 = tension * (((-3.0F * u2) + (4.0F * t)) - 1.0F);
        car1 = (3.0F * (2.0F - tension) * u2) + (2.0F * (tension - 3.0F) * t);
        car2 = tension + ((3.0F * (tension - 2.0F) * u2) +
                          (2.0F * -((2.0F * tension) - 3.0F) * t));
        car3 = tension * ((3.0F * u2) - (2.0F * t));
        p->x = (cp[3].x * car3) +
               ((cp[2].x * car2) + ((cp[0].x * car0) + (cp[1].x * car1)));
        p->y = (cp[3].y * car3) +
               ((cp[2].y * car2) + ((cp[0].y * car0) + (cp[1].y * car1)));
        p->z = (cp[3].z * car3) +
               ((cp[2].z * car2) + ((cp[0].z * car0) + (cp[1].z * car1)));
        break;
    }
    }
}
