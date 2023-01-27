#ifndef MSL_MATH_H
#define MSL_MATH_H

#define __HI(x) *(int*) &x
#define __LO(x) *(1 + (int*) &x)

double frexp(double x, int* exponent);
double fabsf__Ff(double);
float tanf(float x);
float cos__Ff(float x);
float sin__Ff(float x);
float cosf(float x);
float sinf(float x);
void __sinit_trigf_c(void);
float logf(float);

#endif
