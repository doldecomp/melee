#include "math_ppc.h"

double log2(double x)
{
    static const unsigned long f[2] = { 0x3ff71547, 0x652b82fe };
    return log(x) * *(double*) f;
}

#define _ln2 0.6931471805599453094172321

double exp2(double x)
{
    return (exp(x * _ln2));
}
