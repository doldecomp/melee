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

// HACK! dummies out the _SDA_BASE_ offsets in inline asm
#define _SDA2_BASE_(dummy) 0
#define _SDA_BASE_(dummy) 0

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

float func_8000D3B0(float *a)
{
    float var1 = sqrtf_(a[0] * a[0] + a[1] * a[1]);
    float foo;
    if (lbl_804D7AA8 == var1)
        return lbl_804D7AA8;
    foo = lbl_804D7AC0 / var1;
    a[0] *= foo;
    a[1] *= foo;
    return var1;
}

struct Vec3f
{
    float x;
    float y;
    float z;
};

typedef struct
{

    f32 x, y, z;

} Vec, *VecPtr, Point3d, *Point3dPtr;

float *func_8000D46C(float *a, const float *b)
{
    float f0 = ((volatile float *)b)[0];
    float f1 = ((volatile float *)a)[0];
    a[0] = f1 + f0;
    a[1] = a[1] + b[1];
    a[2] = a[2] + b[2];
    return a;
}

float *func_8000D4A0(float *a, float *b)
{
    float f0 = ((volatile float *)b)[0];
    float f1 = ((volatile float *)a)[0];
    a[0] = f1 + f0;
    a[1] += b[1];
    return a;
}

float *func_8000D4C4(float *a, float *b)
{
    float f0 = ((volatile float *)b)[0];
    float f1 = ((volatile float *)a)[0];
    a[0] = f1 - f0;
    a[1] -= b[1];
    a[2] -= b[2];
    return a;
}

float *func_8000D4F8(float *a, float *b, float *c)
{
    c[0] = a[0] - b[0];
    c[1] = a[1] - b[1];
    c[2] = a[2] - b[2];
    return c;
}

// uses ps instructions
void func_80342E58(float *a, float *b);

float func_8000D5BC(float a);

float *func_8000D530(float *a, float *b, float *c)
{
    float foo;

    func_80342E58(a, b);
    foo = func_8000D5BC(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    if (lbl_804D7AA8 /*0.0f*/ != foo)
    {
        float recip = /*1.0f*/ lbl_804D7AC0 / foo;
        c[0] *= recip;
        c[1] *= recip;
        c[2] *= recip;
    }
    return c;
}

float func_8000D5BC(float a)
{
    return sqrtf(a);
}

extern const float lbl_804D7AC4;
extern const float lbl_804D7AC8;

extern float func_80022D1C(float);

#ifdef NONMATCHING
float func_8000D620(float *a, float *b)
{
    float foo = sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]) * sqrtf(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
    if (foo > lbl_804D7AC4)
    {
        // register swap here - can't match
        float f1 = __fmadds(a[2], b[2], __fmadds(a[0], b[0], a[1] * b[1]));
        f1 = f1 / foo;
        if (f1 > lbl_804D7AC0)
            f1 = lbl_804D7AC0;
        if (f1 < lbl_804D7AC8)
            f1 = lbl_804D7AC8;
        return func_80022D1C(f1);
    }
    //lbl_8000D77C
    return lbl_804D7AA8;
}
#else
asm float func_8000D620(float *a, float *b)
{
    nofralloc
/* 8000D620 0000A200  7C 08 02 A6 */	mflr r0
/* 8000D624 0000A204  90 01 00 04 */	stw r0, 4(r1)
/* 8000D628 0000A208  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8000D62C 0000A20C  C0 23 00 00 */	lfs f1, 0(r3)
/* 8000D630 0000A210  C0 03 00 04 */	lfs f0, 4(r3)
/* 8000D634 0000A214  EC 41 00 72 */	fmuls f2, f1, f1
/* 8000D638 0000A218  C0 63 00 08 */	lfs f3, 8(r3)
/* 8000D63C 0000A21C  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000D640 0000A220  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D644 0000A224  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8000D648 0000A228  EC 02 00 2A */	fadds f0, f2, f0
/* 8000D64C 0000A22C  EC 03 00 2A */	fadds f0, f3, f0
/* 8000D650 0000A230  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000D654 0000A234  40 81 00 50 */	ble lbl_8000D6A4
/* 8000D658 0000A238  FC 40 00 34 */	frsqrte f2, f0
/* 8000D65C 0000A23C  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000D660 0000A240  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000D664 0000A244  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D668 0000A248  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D66C 0000A24C  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D670 0000A250  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D674 0000A254  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D678 0000A258  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D67C 0000A25C  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D680 0000A260  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D684 0000A264  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D688 0000A268  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D68C 0000A26C  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D690 0000A270  FC 22 00 72 */	fmul f1, f2, f1
/* 8000D694 0000A274  FC 00 00 72 */	fmul f0, f0, f1
/* 8000D698 0000A278  FC 00 00 18 */	frsp f0, f0
/* 8000D69C 0000A27C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8000D6A0 0000A280  C0 01 00 1C */	lfs f0, 0x1c(r1)
lbl_8000D6A4:
/* 8000D6A4 0000A284  C0 44 00 00 */	lfs f2, 0(r4)
/* 8000D6A8 0000A288  C0 24 00 04 */	lfs f1, 4(r4)
/* 8000D6AC 0000A28C  EC 62 00 B2 */	fmuls f3, f2, f2
/* 8000D6B0 0000A290  C0 84 00 08 */	lfs f4, 8(r4)
/* 8000D6B4 0000A294  EC 41 00 72 */	fmuls f2, f1, f1
/* 8000D6B8 0000A298  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D6BC 0000A29C  EC 84 01 32 */	fmuls f4, f4, f4
/* 8000D6C0 0000A2A0  EC 43 10 2A */	fadds f2, f3, f2
/* 8000D6C4 0000A2A4  EC A4 10 2A */	fadds f5, f4, f2
/* 8000D6C8 0000A2A8  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 8000D6CC 0000A2AC  40 81 00 50 */	ble lbl_8000D71C
/* 8000D6D0 0000A2B0  FC 40 28 34 */	frsqrte f2, f5
/* 8000D6D4 0000A2B4  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000D6D8 0000A2B8  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000D6DC 0000A2BC  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D6E0 0000A2C0  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D6E4 0000A2C4  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D6E8 0000A2C8  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D6EC 0000A2CC  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D6F0 0000A2D0  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D6F4 0000A2D4  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D6F8 0000A2D8  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D6FC 0000A2DC  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D700 0000A2E0  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D704 0000A2E4  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D708 0000A2E8  FC 22 00 72 */	fmul f1, f2, f1
/* 8000D70C 0000A2EC  FC 25 00 72 */	fmul f1, f5, f1
/* 8000D710 0000A2F0  FC 20 08 18 */	frsp f1, f1
/* 8000D714 0000A2F4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8000D718 0000A2F8  C0 A1 00 18 */	lfs f5, 0x18(r1)
lbl_8000D71C:
/* 8000D71C 0000A2FC  EC A0 01 72 */	fmuls f5, f0, f5
/* 8000D720 0000A300  C0 02 80 E4 */	lfs f0, lbl_804D7AC4-_SDA2_BASE_(r2)
/* 8000D724 0000A304  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8000D728 0000A308  40 81 00 54 */	ble lbl_8000D77C
/* 8000D72C 0000A30C  C0 23 00 04 */	lfs f1, 4(r3)
/* 8000D730 0000A310  C0 04 00 04 */	lfs f0, 4(r4)
/* 8000D734 0000A314  C0 43 00 00 */	lfs f2, 0(r3)
/* 8000D738 0000A318  EC 01 00 32 */	fmuls f0, f1, f0
/* 8000D73C 0000A31C  C0 24 00 00 */	lfs f1, 0(r4)
/* 8000D740 0000A320  C0 83 00 08 */	lfs f4, 8(r3)
/* 8000D744 0000A324  C0 64 00 08 */	lfs f3, 8(r4)
/* 8000D748 0000A328  EC 22 00 7A */	fmadds f1, f2, f1, f0
/* 8000D74C 0000A32C  C0 02 80 E0 */	lfs f0, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000D750 0000A330  EC 24 08 FA */	fmadds f1, f4, f3, f1
/* 8000D754 0000A334  EC 21 28 24 */	fdivs f1, f1, f5
/* 8000D758 0000A338  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D75C 0000A33C  40 81 00 08 */	ble lbl_8000D764
/* 8000D760 0000A340  FC 20 00 90 */	fmr f1, f0
lbl_8000D764:
/* 8000D764 0000A344  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000D768 0000A348  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D76C 0000A34C  40 80 00 08 */	bge lbl_8000D774
/* 8000D770 0000A350  FC 20 00 90 */	fmr f1, f0
lbl_8000D774:
/* 8000D774 0000A354  48 01 55 A9 */	bl func_80022D1C
/* 8000D778 0000A358  48 00 00 08 */	b lbl_8000D780
lbl_8000D77C:
/* 8000D77C 0000A35C  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
lbl_8000D780:
/* 8000D780 0000A360  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000D784 0000A364  38 21 00 20 */	addi r1, r1, 0x20
/* 8000D788 0000A368  7C 08 03 A6 */	mtlr r0
/* 8000D78C 0000A36C  4E 80 00 20 */	blr 
}
#endif

extern const double lbl_804D7AD0;
extern const double lbl_804D7AD8;
extern const double lbl_804D7AE0;
extern const float lbl_804D7AF0;
extern const double lbl_804D7AF8;
extern const float lbl_804D7AEC;
extern const float lbl_804D7AE8;

// fuck this...
/*
func_8000D8F4(float *a, float *b, float c)
{
    float foo = sqrtf(b[1] * b[1] + b[2] * b[2]);
    //lbl_8000D964
    float f8 = c;
    float f9;

    if (c > lbl_804D7AD0)
        f8 -= lbl_804D7AD8;
    else if (c < lbl_804D7AE0);
        f8 += lbl_804D7AD8;

    f8 = 
    f9 = c + lbl_804D7AF0;
    if (f9 > c)
        
}
*/
