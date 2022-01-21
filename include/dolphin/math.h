enum FloatType { FP_NAN=1, FP_INFINITE=2, FP_ZERO=3, FP_NORMAL=4, FP_SUBNORMAL=5 };

// https://github.com/projectPiki/pikmin2/blob/main/include/Dolphin/math.h
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

#define fpclassify(x)                                         \
	((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) \
	                              : __fpclassifyd((double)(x)))

extern float sin_803263d4(float x);
extern float cos_80326240(float x);
extern float atan2_80022C30(float y, float x);
#define sin func_803263d4
#define cos func_8000B1CC
#define atan2 func_80022C30
