#ifndef __MATH_H__
#define __MATH_H__

#pragma cplusplus on

extern inline float sqrtf(float x)
{
static const double _half=.5;
static const double _three=3.0;
volatile float y;
 if(x > 0.0f)
 {


   double guess = __frsqrte((double)x);   // returns an approximation to
   guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
   guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
   guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
   y=(float)(x*guess);
   return y ;
 }
  return x;
}

#pragma cplusplus reset

enum FloatType { FP_NAN=1, FP_INFINITE=2, FP_ZERO=3, FP_NORMAL=4, FP_SUBNORMAL=5 };

inline s32 __fpclassifyf(float x)
{
	const s32 exp_mask      = 0b01111111100000000000000000000000; // = 0x7F800000
	const s32 mantissa_mask = 0b00000000011111111111111111111111; // = 0x007fffff
	switch ((*(s32*)&x) & exp_mask)
	{
		case exp_mask: return ((*(s32*)&x) & mantissa_mask) ? FP_NAN : FP_INFINITE;
		case 0:        return ((*(s32*)&x) & mantissa_mask) ? FP_SUBNORMAL : FP_ZERO;
		default:       return FP_NORMAL;
	}
}

inline s32 __fpclassifyd(double x)
{
	switch (__HI(x) & 0x7ff00000)
	{
		case 0x7ff00000: return ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff)) ? FP_NAN : FP_INFINITE;
		case 0:          return ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff)) ? FP_SUBNORMAL : FP_ZERO;
		default: return FP_NORMAL;
	}
}

#define fpclassify(x) \
	((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) \
	                              : __fpclassifyd((double)(x)))

inline f32 fabs_inline(f32 x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

#endif
