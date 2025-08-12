#ifndef RUNTIME_RUNTIME_H
#define RUNTIME_RUNTIME_H

#include <placeholder.h>
#include <platform.h>

ASM void __div2u(void);
ASM void __div2i(void);
ASM void __mod2u(void);
ASM void __mod2i(void);
ASM void __shl2i(void);
ASM void __shr2u(void);
ASM void __shr2i(void);
ASM void __cvt_sll_dbl(void);
ASM void __cvt_ull_dbl(void);
ASM void __cvt_sll_flt(void);
ASM void __cvt_ull_flt(void);
ASM u64 __cvt_dbl_usll(double);
ASM void __cvt_dbl_ull(void);
ASM unsigned long __cvt_fp2unsigned(register double d);

#endif
