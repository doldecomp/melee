#include <MSL/math.h>
#include <math.h>

#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

#define __two_over_pi .636619772367581343075535053490057f
#define __four_over_pi 1.27323954473516268615107010698011f
#define __SQRT_FLT_EPSILON__ 3.4526698300e-04f

const int tmp_float[4]={0x3E800000,0x3Cbe6080,0x34372200,0x2da44152};
static float  __four_over_pi_m1[]={0x3E800000,0x3Cbe6080,
                                         0x34372200,0x2da44152}; 
extern const float __sincos_poly[];
extern const float __sincos_on_quadrant[];


#define __two_over_pi .636619772367581343075535053490057f // lbl_804DE198
#define __four_over_pi 1.27323954473516268615107010698011f // lbl_804DE19C
#define __SQRT_FLT_EPSILON__ 3.4526698300e-04f // lbl_804DE1A0

static float  __four_over_pi_m1[]={0x3E800000,0x3Cbe6080,
                                         0x34372200,0x2da44152}; // lbl_804DE198 - lbl_804DE1A8

extern const float __sincos_poly[]; // lbl_803B9378
extern const float __sincos_on_quadrant[]; // lbl_803B9358

extern float lbl_80400778[];
extern const float lbl_803B8F40[4] = { 0.25f, 0.023239374f, 0.00000017055572f, 1.867365e-11f };

float tanf(float x)
{
    // tan(x) == sin(x) / cos(x)
    return func_80326220(x) / func_80326200(x);
}

float cos__Ff(float x)
{
    return func_80326240(x);
}

float sin__Ff(float x)
{
    return func_803263D4(x);
}

float cosf(float x) {
    float z = __two_over_pi * x;

    //note we multiply n by 2 below because the polynomial we are using is for [o,pi/4]. n is the nearest multiple
    // of pi/2 not pi/4.
    //  frac_part is the remainder(mod(pi/4))
    // i.e. the actual arg that will be evaluated is frac_part*(pi/4)
    // note: since n is signed n<<1 may pad rightmost bit w/a one.
    int n = (__HI(x) & 0x80000000) ? (int)(z - .5f) : (int)(z + .5f);

    const float frac_part = ((((x - (float)(n * 2)) + __four_over_pi_m1[0] * x) + __four_over_pi_m1[1] * x) +
        __four_over_pi_m1[2] * x) + __four_over_pi_m1[3] * x
    /*) +
    													__four_over_pi_m1[4]*x  */
    ;

    float xsq;
    n &= 0x00000003;

    if (func_803261B4(frac_part) < __SQRT_FLT_EPSILON__) {
        n <<= 1; //index into __sincos_on_quadrant array
        return __sincos_on_quadrant[n + 1] - (__sincos_on_quadrant[n] * frac_part);
    }

    //use identity cos(x)=cos(n*pi/4 + frac_part)=cos(n*pi/4)cos(frac_part)- sin(n*pi/4)sin(frac_part)
    xsq = frac_part * frac_part;
    if (n & 0x00000001) // we are at a multiple of pi/2 thus cos(n*pi/4)= 0
    {
        n <<= 1; //index into __sincos_on_quadrant array 
        z = -((((__sincos_poly[1] * xsq + __sincos_poly[3]) * xsq + __sincos_poly[5]) * xsq + __sincos_poly[7]) * xsq + __sincos_poly[9]) * frac_part;
        return z * __sincos_on_quadrant[n];
    }

    n <<= 1; //index into __sincos_on_quadrant array
    // if here we are near a multiple of pi so sin(n*pi/4) =0

    z = (((__sincos_poly[0] * xsq + __sincos_poly[2]) * xsq + __sincos_poly[4]) * xsq + __sincos_poly[6]) * xsq + __sincos_poly[8];
    return z * __sincos_on_quadrant[n + 1]; // sin(frac_part)*cos(n*pi/4);  note: n*pi/4 is a multiple of pi/2(not pi)
}

float sinf(float x) {
    float z = __two_over_pi * x;
    //note we multiply n by 2 below because the polynomial we are using is for [o,pi/4]. n is the nearest multiple
    // of pi/2 not pi/4.
    //  frac_part is the remainder(mod(pi/4))
    // i.e. the actual arg that will be evaluated is frac_part*(pi/4)
    // note: since n is signed n<<1 may pad rightmost bit w/a one.
    int n = (__HI(x) & 0x80000000) ? (int)(z - .5f) : (int)(z + .5f);

    const float frac_part = ((((x - (float)(n * 2)) + __four_over_pi_m1[0] * x) + __four_over_pi_m1[1] * x) +
        __four_over_pi_m1[2] * x) + __four_over_pi_m1[3] * x
    /*) +
      	                                               __four_over_pi_m1[4]*x  */
    ;

    float xsq;

    //assumes 2's complement integer storage for negative numbers.
    n &= 0x00000003;

    if (func_803261B4(frac_part) < __SQRT_FLT_EPSILON__) {
        n <<= 1; //index into __sincos_on_quadrant array
        return __sincos_on_quadrant[n] + (__sincos_on_quadrant[n + 1] * frac_part * __sincos_poly[9]);
    }

    xsq = frac_part * frac_part;
    if (n & 0x00000001) // we are at a multiple of pi/2 thus cos(n*pi/4)= 0
    {

        n <<= 1; //index into __sincos_on_quadrant array
        z = (((__sincos_poly[0] * xsq + __sincos_poly[2]) * xsq + __sincos_poly[4]) * xsq + __sincos_poly[6]) * xsq +
            __sincos_poly[8];

        return z * __sincos_on_quadrant[n]; // sin(frac_part)*cos(n*pi/4);  note: n*pi/4 is a multiple of pi/2(not pi)
        //return z;// sin(frac_part)*cos(n*pi/4);  note: n*pi/4 is a multiple of pi/2(not pi)
    }

    // if here we are near a multiple of pi so sin(n*pi/4) =0
    n <<= 1; //index into __sincos_on_quadrant array

    z = ((((__sincos_poly[1] * xsq + __sincos_poly[3]) * xsq + __sincos_poly[5]) * xsq + __sincos_poly[7]) * xsq + __sincos_poly[9]) * frac_part;
    //return z;// sin(frac_part)*cos(n*pi/4);  note: n*pi/4 is a multiple of pi/2(not pi)

    return z * __sincos_on_quadrant[n + 1]; // sin(frac_part)*cos(n*pi/4);  note: n*pi/4 is a multiple of pi/2(not pi)
}

void func_80326578() {
    lbl_80400778[0] = lbl_803B8F40[0];
    lbl_80400778[1] = lbl_803B8F40[1];
    lbl_80400778[2] = lbl_803B8F40[2];
    lbl_80400778[3] = lbl_803B8F40[3];
}

void func_803265A8(void);