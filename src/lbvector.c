#include "global.h"

#define _half lbl_804D7AB0
#define _three lbl_804D7AB8
#define ZERO_CONSTANT_EXTERN lbl_804D7AA8
extern const float lbl_804D7AA8;  // 0.0f
#include "math.h"

extern const float lbl_804D7AC0;

extern const double lbl_804D7AB0;
extern const double lbl_804D7AB8;

//#define NONMATCHING

// matches except for location of variable y on stack in inlined sqrtf call
#ifdef NONMATCHING
float func_8000D2EC(float *a)
{
    float foo;

    float f4 = sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    if (lbl_804D7AA8 == f4 /*0.0f*/)
        return /*0.0f*/ lbl_804D7AA8;
    foo = /*1.0f*/ lbl_804D7AC0 / f4;
    a[0] *= foo;
    a[1] *= foo;
    a[2] *= foo;
    return f4;
}
#else
asm float func_8000D2EC(float *a)
{
    nofralloc
/* 8000D2EC 00009ECC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000D2F0 00009ED0  C0 23 00 00 */	lfs f1, 0(r3)    
/* 8000D2F4 00009ED4  C0 03 00 04 */	lfs f0, 4(r3)    
/* 8000D2F8 00009ED8  EC 41 00 72 */	fmuls f2, f1, f1   
/* 8000D2FC 00009EDC  C0 63 00 08 */	lfs f3, 8(r3)     
/* 8000D300 00009EE0  EC 20 00 32 */	fmuls f1, f0, f0   
/* 8000D304 00009EE4  C0 02 80 C8 */	lfs f0, lbl_804D7AA8
/* 8000D308 00009EE8  EC 63 00 F2 */	fmuls f3, f3, f3   
/* 8000D30C 00009EEC  EC 22 08 2A */	fadds f1, f2, f1
/* 8000D310 00009EF0  EC 83 08 2A */	fadds f4, f3, f1
/* 8000D314 00009EF4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8000D318 00009EF8  40 81 00 50 */	ble lbl_8000D368
/* 8000D31C 00009EFC  FC 20 20 34 */	frsqrte f1, f4    
/* 8000D320 00009F00  C8 62 80 D0 */	lfd f3, lbl_804D7AB0
/* 8000D324 00009F04  C8 42 80 D8 */	lfd f2, lbl_804D7AB8
/* 8000D328 00009F08  FC 01 00 72 */	fmul f0, f1, f1 
/* 8000D32C 00009F0C  FC 23 00 72 */	fmul f1, f3, f1
/* 8000D330 00009F10  FC 04 10 3C */	fnmsub f0, f4, f0, f2  
/* 8000D334 00009F14  FC 21 00 32 */	fmul f1, f1, f0
/* 8000D338 00009F18  FC 01 00 72 */	fmul f0, f1, f1
/* 8000D33C 00009F1C  FC 23 00 72 */	fmul f1, f3, f1
/* 8000D340 00009F20  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8000D344 00009F24  FC 21 00 32 */	fmul f1, f1, f0
/* 8000D348 00009F28  FC 01 00 72 */	fmul f0, f1, f1
/* 8000D34C 00009F2C  FC 23 00 72 */	fmul f1, f3, f1
/* 8000D350 00009F30  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8000D354 00009F34  FC 01 00 32 */	fmul f0, f1, f0
/* 8000D358 00009F38  FC 04 00 32 */	fmul f0, f4, f0
/* 8000D35C 00009F3C  FC 00 00 18 */	frsp f0, f0         
/* 8000D360 00009F40  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8000D364 00009F44  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8000D368:
/* 8000D368 00009F48  C0 22 80 C8 */	lfs f1, lbl_804D7AA8
/* 8000D36C 00009F4C  FC 01 20 00 */	fcmpu cr0, f1, f4
/* 8000D370 00009F50  40 82 00 08 */	bne lbl_8000D378
/* 8000D374 00009F54  48 00 00 34 */	b lbl_8000D3A8
lbl_8000D378:
/* 8000D378 00009F58  C0 42 80 E0 */	lfs f2, lbl_804D7AC0
/* 8000D37C 00009F5C  FC 20 20 90 */	fmr f1, f4
/* 8000D380 00009F60  C0 03 00 00 */	lfs f0, 0(r3)
/* 8000D384 00009F64  EC 42 20 24 */	fdivs f2, f2, f4  
/* 8000D388 00009F68  EC 00 00 B2 */	fmuls f0, f0, f2  
/* 8000D38C 00009F6C  D0 03 00 00 */	stfs f0, 0(r3)
/* 8000D390 00009F70  C0 03 00 04 */	lfs f0, 4(r3)
/* 8000D394 00009F74  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8000D398 00009F78  D0 03 00 04 */	stfs f0, 4(r3)
/* 8000D39C 00009F7C  C0 03 00 08 */	lfs f0, 8(r3)
/* 8000D3A0 00009F80  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8000D3A4 00009F84  D0 03 00 08 */	stfs f0, 8(r3)
lbl_8000D3A8:
/* 8000D3A8 00009F88  38 21 00 18 */	addi r1, r1, 0x18
/* 8000D3AC 00009F8C  4E 80 00 20 */	blr 
}
#endif

