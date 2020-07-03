extern inline float sqrtf(float x)
{
// HACK: allow overriding definitions as extern
#ifdef _half
extern const double _half;
extern const double _three;
#else
static const double _half=.5;
static const double _three=3.0;
#endif

volatile float y;
// HACK: allow overriding zero constant as extern
#ifdef ZERO_CONSTANT_EXTERN
 if(x > ZERO_CONSTANT_EXTERN)
#else
 if(x > 0.0f)
#endif
 {
   double guess = __frsqrte((double)x);   // returns an approximation to   
    guess = _half*guess*(__fnmsub(x, guess*guess, _three));  // now have 12 sig bits
    guess = _half*guess*(__fnmsub(x, guess*guess, _three));  // now have 24 sig bits
    guess = _half*guess*(__fnmsub(x, guess*guess, _three));  // now have 32 sig bits
   y=(float)(x*guess);
   return y ;
 }
  return x ;
}   
