float fabsf(float x);
double fabs(double x);
float sqrtf(float x);
double sqrt(double x);
#pragma intrinsic (fabsf)
#pragma intrinsic (fabs)
#pragma intrinsic (sqrtf)
#pragma intrinsic (sqrt)

float test(float a) {
    double r = (double)sqrtf(fabsf(a));
    return (float)sqrt(fabs(r));
}
