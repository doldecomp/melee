#include "ansi_fp.h"

#include "math.h"

#define __HI(x) (((s32*) &x)[0])
#define __LO(x) (((s32*) &x)[1])

/// @todo: somehow make this work with math.h
inline int _fpclassify(double x)
{
    switch (__HI(x) & 0x7FF00000) {
    case 0x7FF00000: {
        if ((__HI(x) & 0x000FFFFF) || (__LO(x) & 0xFFFFFFFF)) {
            return FP_NAN;
        } else {
            return FP_INFINITE;
        }
        break;
    }
    case 0: {
        if ((__HI(x) & 0x000FFFFF) || (__LO(x) & 0xFFFFFFFF)) {
            return FP_SUBNORMAL;
        } else {
            return FP_ZERO;
        }
        break;
    }
    }
    return FP_NORMAL;
}

#define _isnormal(x) (_fpclassify(x) == FP_NORMAL)
#define _isnan(x) (_fpclassify(x) == FP_NAN)
#define _isinf(x) (_fpclassify(x) == FP_INFINITE)
#define _isfinite(x) (_fpclassify(x) > FP_INFINITE)

const double bit_values[] = {
    1e1, 1e2, 1e4, 1e8, 1e16, 1e32, 1e64, 1e128, 1e256,
};

const double digit_values[] = {
    1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8,
};

void __num2dec(const decform* f, double x, decimal* d)
{
    int sp30;
    int exp;
    unsigned char* p;
    int digits;
    int var_r4;
    double var_f1;
    int var_r11;
    int var_r12;
    int temp_r5;
    int var_r6;
    int var_r6_2;
    const double* var_r5;

    // fixes float ordering issue
    (void) 0.0;
    (void) 1.0;
    (void) 4503601774854144.0;

    digits = f->digits;
    if (digits > 16) {
        digits = 16;
    }

    d->sign = 0;
    d->exp = 0;
    d->sig.length = 1;

    if (x == 0.0) {
        d->sig.text[0] = '0';
        return;
    }

    if (!_isfinite(x)) {
        d->sig.text[0] = _isnan(x) ? 'N' : 'I';
        return;
    }

    d->sig.length = 0;
    if (x < 0.0) {
        x = -x;
        d->sign = 1;
    }

    frexp(x, &sp30);
    var_r4 = (sp30 * 301029) / 1000000; // log_10(2)
    exp = var_r4;
    var_r5 = bit_values;
    if (var_r4 < 0) {
        var_r4 = -var_r4;
        while (var_r4 != 0) {
            if (var_r4 & 1) {
                x *= *var_r5;
            }
            var_r4 >>= 1;
            var_r5++;
        }
    } else if (var_r4 > 0) {
        var_f1 = 1.0f;
        while (var_r4 != 0) {
            if (var_r4 & 1) {
                var_f1 *= *var_r5;
            }
            var_r4 >>= 1;
            var_r5++;
        }
        x /= var_f1;
    }

    while (x >= 1.0) {
        x *= 0.1;
        exp += 1;
    }

    while (x < 0.1) {
        x *= 10.0;
        exp -= 1;
    }

    p = d->sig.text;
    while (digits != 0) {
        var_r12 = digits;
        if (digits > 8) {
            var_r12 = 8;
        }
        d->sig.length += var_r12;
        digits -= var_r12;
        exp -= var_r12;
        p += var_r12;
        x *= digit_values[var_r12 - 1];
        var_r6 = (int) x;
        x = x - var_r6;

        var_r11 = var_r12 + 1;
        while (--var_r11 != 0) {
            *--p = '0' + (var_r6 % 10);
            var_r6 /= 10;
        }
        p += var_r12;
    }

    digits = f->digits;
    if (f->digits > 36) {
        digits = 36;
    }

    temp_r5 = digits - d->sig.length;
    if (temp_r5 > 0) {
        var_r6_2 = temp_r5 + 1;
        while (--var_r6_2 != 0) {
            *p++ = '0';
        }
        exp -= temp_r5;
        d->sig.length += temp_r5;
    }

    d->exp = exp;
}
