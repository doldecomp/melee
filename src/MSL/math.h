#ifndef MSL_MATH_H
#define MSL_MATH_H

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

double frexp(double x, int* exponent);
double fabsf__Ff(double);
void __sinit_trigf_c();
void func_803265A8();

#endif
