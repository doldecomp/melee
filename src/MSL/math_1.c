#include <MetroTRK/intrinsics.h>
#include <MSL/math.h>

const double lbl_804DE190 = 1.8014398509481984e+16;

float fabsf__Ff(float param_1)
{
    return __fabsf(param_1);
}

double frexp(double x, int* exponent)
{
    int hx, ix, lx;
    hx = MSL_HI(x);
    ix = 0x7fffffff & hx;
    lx = MSL_LO(x);
    *exponent = 0;
    if (ix >= 0x7ff00000 || ((ix | lx) == 0)) {
        return x; /* 0,inf,nan */
    }
    if (ix < 0x00100000) { /* subnormal */
        x *= lbl_804DE190;
        hx = MSL_HI(x);
        ix = hx & 0x7fffffff;
        *exponent = -54;
    }
    *exponent += (ix >> 20) - 1022;
    hx = (hx & 0x800fffff) | 0x3fe00000;
    MSL_HI(x) = hx;
    return x;
}
