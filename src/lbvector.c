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

// PSVECCrossProduct
void func_80342E58(/*VecPtr a, VecPtr b, VecPtr c*/);

float func_8000D5BC(float a);

#pragma fp_contract on

Vec *func_8000D530(Vec *a, Vec *b, Vec *c)
{
    float foo;

    func_80342E58(a, b /*, c*/);  // TODO: Doesn't match if I pass c in
    foo = func_8000D5BC(c->x * c->x + c->y * c->y + c->z * c->z);
    if (lbl_804D7AA8 /*0.0f*/ != foo)
    {
        float recip = /*1.0f*/ lbl_804D7AC0 / foo;
        c->x *= recip;
        c->y *= recip;
        c->z *= recip;
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
//#if 1

float func_8000D620(float *a, float *b)
{
    float foo = sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]) * sqrtf(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
    if (foo > lbl_804D7AC4)
    {
        // register swap here - can't match
        float f1 = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
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

#ifdef NONMATCHING
float func_8000D790(float *a, float *b)
{
    float foo = sqrtf_(a[0] * a[0] + a[1] * a[1]) * sqrtf_(b[0] * b[0] + b[1] * b[1]);
//#define lbl_804D7AA8 0.0f
    if (lbl_804D7AA8 != foo)
    {
        float f1 = (a[0] * b[0] + a[1] * b[1]);
        f1 = f1 / foo;
//#define lbl_804D7AC0 1.0f
//#define lbl_804D7AC8 2.0f
        if (f1 > lbl_804D7AC0)
            f1 = lbl_804D7AC0;
        if (f1 < lbl_804D7AC8)
            f1 = lbl_804D7AC8;
        return func_80022D1C(f1);
    } else
    //lbl_8000D8E4
    return lbl_804D7AA8;
}
#else
asm float func_8000D790(float *a, float *b)
{
    nofralloc
/* 8000D790 0000A370  7C 08 02 A6 */	mflr r0
/* 8000D794 0000A374  90 01 00 04 */	stw r0, 4(r1)
/* 8000D798 0000A378  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8000D79C 0000A37C  C0 23 00 00 */	lfs f1, 0(r3)
/* 8000D7A0 0000A380  C0 03 00 04 */	lfs f0, 4(r3)
/* 8000D7A4 0000A384  EC 41 00 72 */	fmuls f2, f1, f1
/* 8000D7A8 0000A388  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D7AC 0000A38C  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000D7B0 0000A390  EC 02 00 2A */	fadds f0, f2, f0
/* 8000D7B4 0000A394  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000D7B8 0000A398  40 81 00 60 */	ble lbl_8000D818
/* 8000D7BC 0000A39C  FC 40 00 34 */	frsqrte f2, f0
/* 8000D7C0 0000A3A0  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000D7C4 0000A3A4  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000D7C8 0000A3A8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D7CC 0000A3AC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D7D0 0000A3B0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D7D4 0000A3B4  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D7D8 0000A3B8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D7DC 0000A3BC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D7E0 0000A3C0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D7E4 0000A3C4  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D7E8 0000A3C8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D7EC 0000A3CC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D7F0 0000A3D0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D7F4 0000A3D4  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D7F8 0000A3D8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D7FC 0000A3DC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D800 0000A3E0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000D804 0000A3E4  FC 22 00 72 */	fmul f1, f2, f1
/* 8000D808 0000A3E8  FC 00 00 72 */	fmul f0, f0, f1
/* 8000D80C 0000A3EC  FC 00 00 18 */	frsp f0, f0
/* 8000D810 0000A3F0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8000D814 0000A3F4  C0 01 00 1C */	lfs f0, 0x1c(r1)
lbl_8000D818:
/* 8000D818 0000A3F8  C0 24 00 00 */	lfs f1, 0(r4)
/* 8000D81C 0000A3FC  C0 44 00 04 */	lfs f2, 4(r4)
/* 8000D820 0000A400  EC 61 00 72 */	fmuls f3, f1, f1
/* 8000D824 0000A404  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D828 0000A408  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8000D82C 0000A40C  EC A3 10 2A */	fadds f5, f3, f2
/* 8000D830 0000A410  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 8000D834 0000A414  40 81 00 60 */	ble lbl_8000D894
/* 8000D838 0000A418  FC 40 28 34 */	frsqrte f2, f5
/* 8000D83C 0000A41C  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000D840 0000A420  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000D844 0000A424  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D848 0000A428  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D84C 0000A42C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D850 0000A430  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D854 0000A434  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D858 0000A438  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D85C 0000A43C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D860 0000A440  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D864 0000A444  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D868 0000A448  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D86C 0000A44C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D870 0000A450  FC 42 00 72 */	fmul f2, f2, f1
/* 8000D874 0000A454  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000D878 0000A458  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000D87C 0000A45C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000D880 0000A460  FC 22 00 72 */	fmul f1, f2, f1
/* 8000D884 0000A464  FC 25 00 72 */	fmul f1, f5, f1
/* 8000D888 0000A468  FC 20 08 18 */	frsp f1, f1
/* 8000D88C 0000A46C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 8000D890 0000A470  C0 A1 00 18 */	lfs f5, 0x18(r1)
lbl_8000D894:
/* 8000D894 0000A474  EC 80 01 72 */	fmuls f4, f0, f5
/* 8000D898 0000A478  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D89C 0000A47C  FC 04 08 00 */	fcmpu cr0, f4, f1
/* 8000D8A0 0000A480  41 82 00 44 */	beq lbl_8000D8E4
/* 8000D8A4 0000A484  C0 23 00 04 */	lfs f1, 4(r3)
/* 8000D8A8 0000A488  C0 04 00 04 */	lfs f0, 4(r4)
/* 8000D8AC 0000A48C  C0 63 00 00 */	lfs f3, 0(r3)
/* 8000D8B0 0000A490  EC 21 00 32 */	fmuls f1, f1, f0
/* 8000D8B4 0000A494  C0 44 00 00 */	lfs f2, 0(r4)
/* 8000D8B8 0000A498  C0 02 80 E0 */	lfs f0, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000D8BC 0000A49C  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 8000D8C0 0000A4A0  EC 21 20 24 */	fdivs f1, f1, f4
/* 8000D8C4 0000A4A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D8C8 0000A4A8  40 81 00 08 */	ble lbl_8000D8D0
/* 8000D8CC 0000A4AC  FC 20 00 90 */	fmr f1, f0
lbl_8000D8D0:
/* 8000D8D0 0000A4B0  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000D8D4 0000A4B4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000D8D8 0000A4B8  40 80 00 08 */	bge lbl_8000D8E0
/* 8000D8DC 0000A4BC  FC 20 00 90 */	fmr f1, f0
lbl_8000D8E0:
/* 8000D8E0 0000A4C0  48 01 54 3D */	bl func_80022D1C
lbl_8000D8E4:
/* 8000D8E4 0000A4C4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000D8E8 0000A4C8  38 21 00 20 */	addi r1, r1, 0x20
/* 8000D8EC 0000A4CC  7C 08 03 A6 */	mtlr r0
/* 8000D8F0 0000A4D0  4E 80 00 20 */	blr 
}
#endif

/*
float func_8000D790(float *a, float *b)
{
    float foo = sqrtf_(a[0] * a[0] + a[1] * a[1]) * sqrtf_(b[0] * b[0] + b[1] * b[1]);
    if (lbl_804D7AA8 != foo)
    {
        float f1 = (a[0] * b[0] + a[1] * b[1]);
        f1 = f1 / foo;
#define lbl_804D7AC0 1.0f
#define lbl_804D7AC8 2.0f
        if (f1 > lbl_804D7AC0)
            f1 = lbl_804D7AC0;
        if (f1 < lbl_804D7AC8)
            f1 = lbl_804D7AC8;
        return func_80022D1C(f1);
    }
    //lbl_8000D8E4
    return lbl_804D7AA8;
}
*/


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

asm func_8000D8F4(float *a, float *b, float c)
{
    nofralloc
/* 8000D8F4 0000A4D4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8000D8F8 0000A4D8  C0 84 00 04 */	lfs f4, 4(r4)
/* 8000D8FC 0000A4DC  C0 04 00 08 */	lfs f0, 8(r4)
/* 8000D900 0000A4E0  EC A4 01 32 */	fmuls f5, f4, f4
/* 8000D904 0000A4E4  C0 82 80 C8 */	lfs f4, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000D908 0000A4E8  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000D90C 0000A4EC  EC 05 00 2A */	fadds f0, f5, f0
/* 8000D910 0000A4F0  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 8000D914 0000A4F4  40 81 00 50 */	ble lbl_8000D964
/* 8000D918 0000A4F8  FC A0 00 34 */	frsqrte f5, f0
/* 8000D91C 0000A4FC  C8 E2 80 D0 */	lfd f7, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000D920 0000A500  C8 C2 80 D8 */	lfd f6, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000D924 0000A504  FC 85 01 72 */	fmul f4, f5, f5
/* 8000D928 0000A508  FC A7 01 72 */	fmul f5, f7, f5
/* 8000D92C 0000A50C  FC 80 31 3C */	fnmsub f4, f0, f4, f6
/* 8000D930 0000A510  FC A5 01 32 */	fmul f5, f5, f4
/* 8000D934 0000A514  FC 85 01 72 */	fmul f4, f5, f5
/* 8000D938 0000A518  FC A7 01 72 */	fmul f5, f7, f5
/* 8000D93C 0000A51C  FC 80 31 3C */	fnmsub f4, f0, f4, f6
/* 8000D940 0000A520  FC A5 01 32 */	fmul f5, f5, f4
/* 8000D944 0000A524  FC 85 01 72 */	fmul f4, f5, f5
/* 8000D948 0000A528  FC A7 01 72 */	fmul f5, f7, f5
/* 8000D94C 0000A52C  FC 80 31 3C */	fnmsub f4, f0, f4, f6
/* 8000D950 0000A530  FC 85 01 32 */	fmul f4, f5, f4
/* 8000D954 0000A534  FC 00 01 32 */	fmul f0, f0, f4
/* 8000D958 0000A538  FC 00 00 18 */	frsp f0, f0
/* 8000D95C 0000A53C  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8000D960 0000A540  C0 01 00 14 */	lfs f0, 0x14(r1)
lbl_8000D964:
/* 8000D964 0000A544  C8 82 80 F0 */	lfd f4, lbl_804D7AD0-_SDA2_BASE_(r2)
/* 8000D968 0000A548  FD 00 08 90 */	fmr f8, f1
/* 8000D96C 0000A54C  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000D970 0000A550  40 81 00 14 */	ble lbl_8000D984
/* 8000D974 0000A554  C8 82 80 F8 */	lfd f4, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000D978 0000A558  FD 08 20 28 */	fsub f8, f8, f4
/* 8000D97C 0000A55C  FD 00 40 18 */	frsp f8, f8
/* 8000D980 0000A560  48 00 00 1C */	b lbl_8000D99C
lbl_8000D984:
/* 8000D984 0000A564  C8 82 81 00 */	lfd f4, lbl_804D7AE0-_SDA2_BASE_(r2)
/* 8000D988 0000A568  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000D98C 0000A56C  40 80 00 10 */	bge lbl_8000D99C
/* 8000D990 0000A570  C8 82 80 F8 */	lfd f4, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000D994 0000A574  FD 08 20 2A */	fadd f8, f8, f4
/* 8000D998 0000A578  FD 00 40 18 */	frsp f8, f8
lbl_8000D99C:
/* 8000D99C 0000A57C  C0 82 81 10 */	lfs f4, lbl_804D7AF0-_SDA2_BASE_(r2)
/* 8000D9A0 0000A580  C0 A2 81 0C */	lfs f5, lbl_804D7AEC-_SDA2_BASE_(r2)
/* 8000D9A4 0000A584  EC E4 02 32 */	fmuls f7, f4, f8
/* 8000D9A8 0000A588  C8 82 81 18 */	lfd f4, lbl_804D7AF8-_SDA2_BASE_(r2)
/* 8000D9AC 0000A58C  EC A5 02 32 */	fmuls f5, f5, f8
/* 8000D9B0 0000A590  C0 C2 81 08 */	lfs f6, lbl_804D7AE8-_SDA2_BASE_(r2)
/* 8000D9B4 0000A594  FD 21 20 2A */	fadd f9, f1, f4  
/* 8000D9B8 0000A598  EC E7 02 32 */	fmuls f7, f7, f8
/* 8000D9BC 0000A59C  C8 22 80 F0 */	lfd f1, lbl_804D7AD0-_SDA2_BASE_(r2)
/* 8000D9C0 0000A5A0  EC 85 02 32 */	fmuls f4, f5, f8  
/* 8000D9C4 0000A5A4  FD 20 48 18 */	frsp f9, f9
/* 8000D9C8 0000A5A8  EC A8 01 F2 */	fmuls f5, f8, f7   
/* 8000D9CC 0000A5AC  EC 88 01 32 */	fmuls f4, f8, f4  
/* 8000D9D0 0000A5B0  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000D9D4 0000A5B4  EC A8 01 72 */	fmuls f5, f8, f5   
/* 8000D9D8 0000A5B8  EC 26 22 38 */	fmsubs f1, f6, f8, f4  
/* 8000D9DC 0000A5BC  ED 08 09 7A */	fmadds f8, f8, f5, f1
/* 8000D9E0 0000A5C0  40 81 00 14 */	ble lbl_8000D9F4
/* 8000D9E4 0000A5C4  C8 22 80 F8 */	lfd f1, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000D9E8 0000A5C8  FD 29 08 28 */	fsub f9, f9, f1
/* 8000D9EC 0000A5CC  FD 20 48 18 */	frsp f9, f9
/* 8000D9F0 0000A5D0  48 00 00 1C */	b lbl_8000DA0C
lbl_8000D9F4:
/* 8000D9F4 0000A5D4  C8 22 81 00 */	lfd f1, lbl_804D7AE0-_SDA2_BASE_(r2)
/* 8000D9F8 0000A5D8  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000D9FC 0000A5DC  40 80 00 10 */	bge lbl_8000DA0C
/* 8000DA00 0000A5E0  C8 22 80 F8 */	lfd f1, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000DA04 0000A5E4  FD 29 08 2A */	fadd f9, f9, f1
/* 8000DA08 0000A5E8  FD 20 48 18 */	frsp f9, f9
lbl_8000DA0C:
/* 8000DA0C 0000A5EC  C0 22 81 10 */	lfs f1, lbl_804D7AF0-_SDA2_BASE_(r2)
/* 8000DA10 0000A5F0  C0 82 81 0C */	lfs f4, lbl_804D7AEC-_SDA2_BASE_(r2)
/* 8000DA14 0000A5F4  EC C1 02 72 */	fmuls f6, f1, f9
/* 8000DA18 0000A5F8  C0 22 80 E4 */	lfs f1, lbl_804D7AC4-_SDA2_BASE_(r2)
/* 8000DA1C 0000A5FC  EC 84 02 72 */	fmuls f4, f4, f9
/* 8000DA20 0000A600  C0 A2 81 08 */	lfs f5, lbl_804D7AE8-_SDA2_BASE_(r2)
/* 8000DA24 0000A604  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000DA28 0000A608  EC C6 02 72 */	fmuls f6, f6, f9
/* 8000DA2C 0000A60C  EC 24 02 72 */	fmuls f1, f4, f9
/* 8000DA30 0000A610  EC 89 01 B2 */	fmuls f4, f9, f6
/* 8000DA34 0000A614  EC 29 00 72 */	fmuls f1, f9, f1
/* 8000DA38 0000A618  EC 89 01 32 */	fmuls f4, f9, f4
/* 8000DA3C 0000A61C  EC 25 0A 78 */	fmsubs f1, f5, f9, f1
/* 8000DA40 0000A620  ED 29 09 3A */	fmadds f9, f9, f4, f1
/* 8000DA44 0000A624  40 81 00 34 */	ble lbl_8000DA78
/* 8000DA48 0000A628  C0 44 00 08 */	lfs f2, 8(r4)
/* 8000DA4C 0000A62C  C0 24 00 04 */	lfs f1, 4(r4)
/* 8000DA50 0000A630  EC 42 00 24 */	fdivs f2, f2, f0
/* 8000DA54 0000A634  C0 A3 00 08 */	lfs f5, 8(r3)
/* 8000DA58 0000A638  C0 C3 00 04 */	lfs f6, 4(r3)
/* 8000DA5C 0000A63C  C1 63 00 00 */	lfs f11, 0(r3)
/* 8000DA60 0000A640  EC 61 00 24 */	fdivs f3, f1, f0
/* 8000DA64 0000A644  EC 85 00 F2 */	fmuls f4, f5, f3
/* 8000DA68 0000A648  EC 25 00 B2 */	fmuls f1, f5, f2
/* 8000DA6C 0000A64C  ED 86 20 B8 */	fmsubs f12, f6, f2, f4
/* 8000DA70 0000A650  EC A6 08 FA */	fmadds f5, f6, f3, f1
/* 8000DA74 0000A654  48 00 00 10 */	b lbl_8000DA84
lbl_8000DA78:
/* 8000DA78 0000A658  C1 63 00 00 */	lfs f11, 0(r3)
/* 8000DA7C 0000A65C  C1 83 00 04 */	lfs f12, 4(r3)
/* 8000DA80 0000A660  C0 A3 00 08 */	lfs f5, 8(r3)
lbl_8000DA84:
/* 8000DA84 0000A664  C1 44 00 00 */	lfs f10, 0(r4)
/* 8000DA88 0000A668  EC 85 00 32 */	fmuls f4, f5, f0
/* 8000DA8C 0000A66C  C0 22 80 E4 */	lfs f1, lbl_804D7AC4-_SDA2_BASE_(r2)
/* 8000DA90 0000A670  EC EC 02 32 */	fmuls f7, f12, f8
/* 8000DA94 0000A674  EC A5 02 B2 */	fmuls f5, f5, f10
/* 8000DA98 0000A678  EC 8B 22 BA */	fmadds f4, f11, f10, f4
/* 8000DA9C 0000A67C  EC CC 02 72 */	fmuls f6, f12, f9
/* 8000DAA0 0000A680  ED 6B 28 38 */	fmsubs f11, f11, f0, f5
/* 8000DAA4 0000A684  EC A4 02 B2 */	fmuls f5, f4, f10
/* 8000DAA8 0000A688  EC 84 00 32 */	fmuls f4, f4, f0
/* 8000DAAC 0000A68C  EC EB 3A 78 */	fmsubs f7, f11, f9, f7
/* 8000DAB0 0000A690  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000DAB4 0000A694  EC CB 32 3A */	fmadds f6, f11, f8, f6
/* 8000DAB8 0000A698  FC 20 38 50 */	fneg f1, f7
/* 8000DABC 0000A69C  EC 07 28 3A */	fmadds f0, f7, f0, f5
/* 8000DAC0 0000A6A0  EC A1 22 BA */	fmadds f5, f1, f10, f4
/* 8000DAC4 0000A6A4  40 81 00 28 */	ble lbl_8000DAEC
/* 8000DAC8 0000A6A8  EC 85 00 F2 */	fmuls f4, f5, f3
/* 8000DACC 0000A6AC  D0 03 00 00 */	stfs f0, 0(r3)
/* 8000DAD0 0000A6B0  FC 20 30 50 */	fneg f1, f6
/* 8000DAD4 0000A6B4  EC 05 00 B2 */	fmuls f0, f5, f2
/* 8000DAD8 0000A6B8  EC 46 20 BA */	fmadds f2, f6, f2, f4
/* 8000DADC 0000A6BC  EC 01 00 FA */	fmadds f0, f1, f3, f0
/* 8000DAE0 0000A6C0  D0 43 00 04 */	stfs f2, 4(r3)
/* 8000DAE4 0000A6C4  D0 03 00 08 */	stfs f0, 8(r3)
/* 8000DAE8 0000A6C8  48 00 00 10 */	b lbl_8000DAF8
lbl_8000DAEC:
/* 8000DAEC 0000A6CC  D0 03 00 00 */	stfs f0, 0(r3)
/* 8000DAF0 0000A6D0  D0 C3 00 04 */	stfs f6, 4(r3)
/* 8000DAF4 0000A6D4  D0 A3 00 08 */	stfs f5, 8(r3)
lbl_8000DAF8:
/* 8000DAF8 0000A6D8  38 21 00 28 */	addi r1, r1, 0x28
/* 8000DAFC 0000A6DC  4E 80 00 20 */	blr 
}

asm func_8000DB00(Vec *a /*r3*/, int b /*r4*/, float c /*f1*/)
{
    nofralloc
/* 8000DB00 0000A6E0  C8 82 80 F0 */	lfd f4, lbl_804D7AD0-_SDA2_BASE_(r2)
/* 8000DB04 0000A6E4  FD 00 08 90 */	fmr f8, f1
/* 8000DB08 0000A6E8  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000DB0C 0000A6EC  40 81 00 14 */	ble lbl_8000DB20
/* 8000DB10 0000A6F0  C8 82 80 F8 */	lfd f4, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000DB14 0000A6F4  FD 08 20 28 */	fsub f8, f8, f4
/* 8000DB18 0000A6F8  FD 00 40 18 */	frsp f8, f8
/* 8000DB1C 0000A6FC  48 00 00 1C */	b lbl_8000DB38
lbl_8000DB20:
/* 8000DB20 0000A700  C8 82 81 00 */	lfd f4, lbl_804D7AE0-_SDA2_BASE_(r2)
/* 8000DB24 0000A704  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000DB28 0000A708  40 80 00 10 */	bge lbl_8000DB38
/* 8000DB2C 0000A70C  C8 82 80 F8 */	lfd f4, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000DB30 0000A710  FD 08 20 2A */	fadd f8, f8, f4
/* 8000DB34 0000A714  FD 00 40 18 */	frsp f8, f8
lbl_8000DB38:
/* 8000DB38 0000A718  C0 82 81 10 */	lfs f4, lbl_804D7AF0-_SDA2_BASE_(r2)
/* 8000DB3C 0000A71C  C0 A2 81 0C */	lfs f5, lbl_804D7AEC-_SDA2_BASE_(r2)
/* 8000DB40 0000A720  EC E4 02 32 */	fmuls f7, f4, f8
/* 8000DB44 0000A724  C8 82 81 18 */	lfd f4, lbl_804D7AF8-_SDA2_BASE_(r2)
/* 8000DB48 0000A728  EC A5 02 32 */	fmuls f5, f5, f8
/* 8000DB4C 0000A72C  C0 C2 81 08 */	lfs f6, lbl_804D7AE8-_SDA2_BASE_(r2)
/* 8000DB50 0000A730  FD 21 20 2A */	fadd f9, f1, f4
/* 8000DB54 0000A734  EC E7 02 32 */	fmuls f7, f7, f8
/* 8000DB58 0000A738  C8 22 80 F0 */	lfd f1, lbl_804D7AD0-_SDA2_BASE_(r2)
/* 8000DB5C 0000A73C  EC 85 02 32 */	fmuls f4, f5, f8
/* 8000DB60 0000A740  FD 20 48 18 */	frsp f9, f9
/* 8000DB64 0000A744  EC A8 01 F2 */	fmuls f5, f8, f7
/* 8000DB68 0000A748  EC 88 01 32 */	fmuls f4, f8, f4
/* 8000DB6C 0000A74C  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000DB70 0000A750  EC A8 01 72 */	fmuls f5, f8, f5
/* 8000DB74 0000A754  EC 26 22 38 */	fmsubs f1, f6, f8, f4
/* 8000DB78 0000A758  EC C8 09 7A */	fmadds f6, f8, f5, f1
/* 8000DB7C 0000A75C  40 81 00 14 */	ble lbl_8000DB90
/* 8000DB80 0000A760  C8 22 80 F8 */	lfd f1, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000DB84 0000A764  FD 29 08 28 */	fsub f9, f9, f1
/* 8000DB88 0000A768  FD 20 48 18 */	frsp f9, f9
/* 8000DB8C 0000A76C  48 00 00 1C */	b lbl_8000DBA8
lbl_8000DB90:
/* 8000DB90 0000A770  C8 22 81 00 */	lfd f1, lbl_804D7AE0-_SDA2_BASE_(r2)
/* 8000DB94 0000A774  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000DB98 0000A778  40 80 00 10 */	bge lbl_8000DBA8
/* 8000DB9C 0000A77C  C8 22 80 F8 */	lfd f1, lbl_804D7AD8-_SDA2_BASE_(r2)
/* 8000DBA0 0000A780  FD 29 08 2A */	fadd f9, f9, f1
/* 8000DBA4 0000A784  FD 20 48 18 */	frsp f9, f9
lbl_8000DBA8:
/* 8000DBA8 0000A788  C0 82 81 10 */	lfs f4, lbl_804D7AF0-_SDA2_BASE_(r2)
/* 8000DBAC 0000A78C  2C 04 00 03 */	cmpwi r4, 3
/* 8000DBB0 0000A790  C0 22 81 0C */	lfs f1, lbl_804D7AEC-_SDA2_BASE_(r2)
/* 8000DBB4 0000A794  EC A4 02 72 */	fmuls f5, f4, f9
/* 8000DBB8 0000A798  C0 82 81 08 */	lfs f4, lbl_804D7AE8-_SDA2_BASE_(r2)
/* 8000DBBC 0000A79C  EC 21 02 72 */	fmuls f1, f1, f9
/* 8000DBC0 0000A7A0  EC A5 02 72 */	fmuls f5, f5, f9
/* 8000DBC4 0000A7A4  EC 21 02 72 */	fmuls f1, f1, f9
/* 8000DBC8 0000A7A8  EC A9 01 72 */	fmuls f5, f9, f5
/* 8000DBCC 0000A7AC  EC 29 00 72 */	fmuls f1, f9, f1
/* 8000DBD0 0000A7B0  EC A9 01 72 */	fmuls f5, f9, f5
/* 8000DBD4 0000A7B4  EC 24 0A 78 */	fmsubs f1, f4, f9, f1
/* 8000DBD8 0000A7B8  EC 89 09 7A */	fmadds f4, f9, f5, f1
/* 8000DBDC 0000A7BC  41 82 00 80 */	beq lbl_8000DC5C
/* 8000DBE0 0000A7C0  40 80 00 14 */	bge lbl_8000DBF4
/* 8000DBE4 0000A7C4  2C 04 00 01 */	cmpwi r4, 1
/* 8000DBE8 0000A7C8  41 82 00 18 */	beq lbl_8000DC00
/* 8000DBEC 0000A7CC  40 80 00 34 */	bge lbl_8000DC20
/* 8000DBF0 0000A7D0  48 00 00 6C */	b lbl_8000DC5C
lbl_8000DBF4:
/* 8000DBF4 0000A7D4  2C 04 00 05 */	cmpwi r4, 5
/* 8000DBF8 0000A7D8  40 80 00 64 */	bge lbl_8000DC5C
/* 8000DBFC 0000A7DC  48 00 00 44 */	b lbl_8000DC40
lbl_8000DC00:
/* 8000DC00 0000A7E0  C0 23 00 08 */	lfs f1, 8(r3)
/* 8000DC04 0000A7E4  C0 63 00 04 */	lfs f3, 4(r3)
/* 8000DC08 0000A7E8  EC 41 01 B2 */	fmuls f2, f1, f6
/* 8000DC0C 0000A7EC  C0 03 00 00 */	lfs f0, 0(r3)
/* 8000DC10 0000A7F0  EC 21 01 32 */	fmuls f1, f1, f4
/* 8000DC14 0000A7F4  EC 43 11 38 */	fmsubs f2, f3, f4, f2
/* 8000DC18 0000A7F8  EC 63 09 BA */	fmadds f3, f3, f6, f1
/* 8000DC1C 0000A7FC  48 00 00 40 */	b lbl_8000DC5C
lbl_8000DC20:
/* 8000DC20 0000A800  C0 A3 00 00 */	lfs f5, 0(r3)
/* 8000DC24 0000A804  C0 63 00 08 */	lfs f3, 8(r3)
/* 8000DC28 0000A808  EC 05 01 B2 */	fmuls f0, f5, f6
/* 8000DC2C 0000A80C  C0 43 00 04 */	lfs f2, 4(r3)
/* 8000DC30 0000A810  EC 23 01 B2 */	fmuls f1, f3, f6
/* 8000DC34 0000A814  EC 63 01 38 */	fmsubs f3, f3, f4, f0
/* 8000DC38 0000A818  EC 05 09 3A */	fmadds f0, f5, f4, f1
/* 8000DC3C 0000A81C  48 00 00 20 */	b lbl_8000DC5C
lbl_8000DC40:
/* 8000DC40 0000A820  C0 23 00 04 */	lfs f1, 4(r3)
/* 8000DC44 0000A824  C0 43 00 00 */	lfs f2, 0(r3)
/* 8000DC48 0000A828  EC 01 01 B2 */	fmuls f0, f1, f6
/* 8000DC4C 0000A82C  C0 63 00 08 */	lfs f3, 8(r3)
/* 8000DC50 0000A830  EC 21 01 32 */	fmuls f1, f1, f4
/* 8000DC54 0000A834  EC 02 01 38 */	fmsubs f0, f2, f4, f0
/* 8000DC58 0000A838  EC 42 09 BA */	fmadds f2, f2, f6, f1
lbl_8000DC5C:
/* 8000DC5C 0000A83C  D0 03 00 00 */	stfs f0, 0(r3)
/* 8000DC60 0000A840  D0 43 00 04 */	stfs f2, 4(r3)
/* 8000DC64 0000A844  D0 63 00 08 */	stfs f3, 8(r3)
/* 8000DC68 0000A848  4E 80 00 20 */	blr 
}

extern const float lbl_804D7B04;

void func_8000DC6C(float *a, float *b)
{
    float f2 = lbl_804D7B04 * (b[0] * a[0] + b[1] * a[1]);
    a[0] += b[0] * f2;
    a[1] += b[1] * f2;
}

// Stack allocation doesn't match
#ifdef NONMATCHING
float func_8000DCA8(float *a, float *b)
{
    float foo = sqrtf(a[0] * a[0] + a[1] * a[1]) * sqrtf(b[0] * b[0] + b[1] * b[1]);
    return (a[0] * b[0] + a[1] * b[1]) / foo;
}
#else
asm float func_8000DCA8(float *a, float *b)
{
    nofralloc
/* 8000DCA8 0000A888  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000DCAC 0000A88C  C0 23 00 00 */	lfs f1, 0(r3)
/* 8000DCB0 0000A890  C0 03 00 04 */	lfs f0, 4(r3)
/* 8000DCB4 0000A894  EC 41 00 72 */	fmuls f2, f1, f1
/* 8000DCB8 0000A898  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000DCBC 0000A89C  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000DCC0 0000A8A0  EC 02 00 2A */	fadds f0, f2, f0
/* 8000DCC4 0000A8A4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000DCC8 0000A8A8  40 81 00 50 */	ble lbl_8000DD18
/* 8000DCCC 0000A8AC  FC 40 00 34 */	frsqrte f2, f0
/* 8000DCD0 0000A8B0  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000DCD4 0000A8B4  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000DCD8 0000A8B8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DCDC 0000A8BC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DCE0 0000A8C0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000DCE4 0000A8C4  FC 42 00 72 */	fmul f2, f2, f1
/* 8000DCE8 0000A8C8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DCEC 0000A8CC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DCF0 0000A8D0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000DCF4 0000A8D4  FC 42 00 72 */	fmul f2, f2, f1
/* 8000DCF8 0000A8D8  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DCFC 0000A8DC  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DD00 0000A8E0  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 8000DD04 0000A8E4  FC 22 00 72 */	fmul f1, f2, f1
/* 8000DD08 0000A8E8  FC 00 00 72 */	fmul f0, f0, f1
/* 8000DD0C 0000A8EC  FC 00 00 18 */	frsp f0, f0
/* 8000DD10 0000A8F0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8000DD14 0000A8F4  C0 01 00 14 */	lfs f0, 0x14(r1)
lbl_8000DD18:
/* 8000DD18 0000A8F8  C0 24 00 00 */	lfs f1, 0(r4)
/* 8000DD1C 0000A8FC  C0 44 00 04 */	lfs f2, 4(r4)
/* 8000DD20 0000A900  EC 61 00 72 */	fmuls f3, f1, f1
/* 8000DD24 0000A904  C0 22 80 C8 */	lfs f1, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000DD28 0000A908  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8000DD2C 0000A90C  EC A3 10 2A */	fadds f5, f3, f2
/* 8000DD30 0000A910  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 8000DD34 0000A914  40 81 00 50 */	ble lbl_8000DD84
/* 8000DD38 0000A918  FC 40 28 34 */	frsqrte f2, f5
/* 8000DD3C 0000A91C  C8 82 80 D0 */	lfd f4, lbl_804D7AB0-_SDA2_BASE_(r2)
/* 8000DD40 0000A920  C8 62 80 D8 */	lfd f3, lbl_804D7AB8-_SDA2_BASE_(r2)
/* 8000DD44 0000A924  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DD48 0000A928  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DD4C 0000A92C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000DD50 0000A930  FC 42 00 72 */	fmul f2, f2, f1
/* 8000DD54 0000A934  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DD58 0000A938  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DD5C 0000A93C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000DD60 0000A940  FC 42 00 72 */	fmul f2, f2, f1
/* 8000DD64 0000A944  FC 22 00 B2 */	fmul f1, f2, f2
/* 8000DD68 0000A948  FC 44 00 B2 */	fmul f2, f4, f2
/* 8000DD6C 0000A94C  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 8000DD70 0000A950  FC 22 00 72 */	fmul f1, f2, f1
/* 8000DD74 0000A954  FC 25 00 72 */	fmul f1, f5, f1
/* 8000DD78 0000A958  FC 20 08 18 */	frsp f1, f1
/* 8000DD7C 0000A95C  D0 21 00 10 */	stfs f1, 0x10(r1)
/* 8000DD80 0000A960  C0 A1 00 10 */	lfs f5, 0x10(r1)
lbl_8000DD84:
/* 8000DD84 0000A964  C0 43 00 04 */	lfs f2, 4(r3)
/* 8000DD88 0000A968  EC 00 01 72 */	fmuls f0, f0, f5
/* 8000DD8C 0000A96C  C0 24 00 04 */	lfs f1, 4(r4)
/* 8000DD90 0000A970  C0 63 00 00 */	lfs f3, 0(r3)
/* 8000DD94 0000A974  EC 22 00 72 */	fmuls f1, f2, f1
/* 8000DD98 0000A978  C0 44 00 00 */	lfs f2, 0(r4)
/* 8000DD9C 0000A97C  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 8000DDA0 0000A980  EC 21 00 24 */	fdivs f1, f1, f0
/* 8000DDA4 0000A984  38 21 00 18 */	addi r1, r1, 0x18
/* 8000DDA8 0000A988  4E 80 00 20 */	blr 
}
#endif

float *func_8000DDAC(float *a, float *b, float *c, float d)
{
    c[0] = b[0] - a[0];
    c[1] = b[1] - a[1];
    c[2] = b[2] - a[2];

    c[0] *= d;
    c[1] *= d;
    c[2] *= d;

    c[0] += a[0];
    c[1] += a[1];
    c[2] += a[2];  

    return c;  
}

extern const float lbl_804D7B00;
extern const float lbl_804D7B08;
extern const float lbl_804D7B0C;

// Matches if literals are used
#ifdef NONMATCHING
float *func_8000DE38(float *a, float *b, float c)
{
    float f2;
    float f0;

    if (c > lbl_804D7AC0)
        c = lbl_804D7AC0;
    else if (c < lbl_804D7AA8)
        c = lbl_804D7AA8;

    f2 = a[0] * lbl_804D7B00 - a[3] * lbl_804D7B08 + a[6] * lbl_804D7B00;
    f0 = a[0] * lbl_804D7B0C + a[3] * lbl_804D7B08 - a[6];
    b[0] = f2 * c * c + f0 * c + a[0];

    f2 = a[1] * lbl_804D7B00 - a[4] * lbl_804D7B08 + a[7] * lbl_804D7B00;
    f0 = a[1] * lbl_804D7B0C + a[4] * lbl_804D7B08 - a[7];
    b[1] = f2 * c * c + f0 * c + a[1];

    f2 = a[2] * lbl_804D7B00 - a[5] * lbl_804D7B08 + a[8] * lbl_804D7B00;
    f0 = a[2] * lbl_804D7B0C + a[5] * lbl_804D7B08 - a[8];
    b[2] = f2 * c * c + f0 * c + a[2];

    return b;
}
#else
asm float *func_8000DE38(float *a, float *b, float c)
{
    nofralloc
/* 8000DE38 0000AA18  C0 02 80 E0 */	lfs f0, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000DE3C 0000AA1C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000DE40 0000AA20  40 81 00 0C */	ble lbl_8000DE4C
/* 8000DE44 0000AA24  FC 20 00 90 */	fmr f1, f0
/* 8000DE48 0000AA28  48 00 00 14 */	b lbl_8000DE5C
lbl_8000DE4C:
/* 8000DE4C 0000AA2C  C0 02 80 C8 */	lfs f0, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000DE50 0000AA30  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000DE54 0000AA34  40 80 00 08 */	bge lbl_8000DE5C
/* 8000DE58 0000AA38  FC 20 00 90 */	fmr f1, f0
lbl_8000DE5C:
/* 8000DE5C 0000AA3C  C0 82 81 28 */	lfs f4, lbl_804D7B08-_SDA2_BASE_(r2)
/* 8000DE60 0000AA40  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 8000DE64 0000AA44  C0 A2 81 20 */	lfs f5, lbl_804D7B00-_SDA2_BASE_(r2)
/* 8000DE68 0000AA48  EC 04 00 32 */	fmuls f0, f4, f0
/* 8000DE6C 0000AA4C  C0 C3 00 00 */	lfs f6, 0(r3)
/* 8000DE70 0000AA50  C0 62 81 2C */	lfs f3, lbl_804D7B0C-_SDA2_BASE_(r2)
/* 8000DE74 0000AA54  C0 E3 00 18 */	lfs f7, 0x18(r3)
/* 8000DE78 0000AA58  EC 45 01 B8 */	fmsubs f2, f5, f6, f0
/* 8000DE7C 0000AA5C  EC 03 01 BA */	fmadds f0, f3, f6, f0
/* 8000DE80 0000AA60  EC 45 11 FA */	fmadds f2, f5, f7, f2
/* 8000DE84 0000AA64  EC 00 38 28 */	fsubs f0, f0, f7
/* 8000DE88 0000AA68  EC 42 00 72 */	fmuls f2, f2, f1
/* 8000DE8C 0000AA6C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000DE90 0000AA70  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8000DE94 0000AA74  EC 06 00 2A */	fadds f0, f6, f0
/* 8000DE98 0000AA78  D0 04 00 00 */	stfs f0, 0(r4)
/* 8000DE9C 0000AA7C  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 8000DEA0 0000AA80  C0 C3 00 04 */	lfs f6, 4(r3)
/* 8000DEA4 0000AA84  EC 04 00 32 */	fmuls f0, f4, f0
/* 8000DEA8 0000AA88  C0 E3 00 1C */	lfs f7, 0x1c(r3)
/* 8000DEAC 0000AA8C  EC 45 01 B8 */	fmsubs f2, f5, f6, f0
/* 8000DEB0 0000AA90  EC 03 01 BA */	fmadds f0, f3, f6, f0
/* 8000DEB4 0000AA94  EC 45 11 FA */	fmadds f2, f5, f7, f2
/* 8000DEB8 0000AA98  EC 00 38 28 */	fsubs f0, f0, f7
/* 8000DEBC 0000AA9C  EC 42 00 72 */	fmuls f2, f2, f1
/* 8000DEC0 0000AAA0  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000DEC4 0000AAA4  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8000DEC8 0000AAA8  EC 06 00 2A */	fadds f0, f6, f0
/* 8000DECC 0000AAAC  D0 04 00 04 */	stfs f0, 4(r4)
/* 8000DED0 0000AAB0  C0 03 00 14 */	lfs f0, 0x14(r3)
/* 8000DED4 0000AAB4  C0 C3 00 08 */	lfs f6, 8(r3)
/* 8000DED8 0000AAB8  EC 04 00 32 */	fmuls f0, f4, f0
/* 8000DEDC 0000AABC  C0 83 00 20 */	lfs f4, 0x20(r3)
/* 8000DEE0 0000AAC0  7C 83 23 78 */	mr r3, r4
/* 8000DEE4 0000AAC4  EC 45 01 B8 */	fmsubs f2, f5, f6, f0
/* 8000DEE8 0000AAC8  EC 03 01 BA */	fmadds f0, f3, f6, f0
/* 8000DEEC 0000AACC  EC 45 11 3A */	fmadds f2, f5, f4, f2
/* 8000DEF0 0000AAD0  EC 00 20 28 */	fsubs f0, f0, f4
/* 8000DEF4 0000AAD4  EC 42 00 72 */	fmuls f2, f2, f1
/* 8000DEF8 0000AAD8  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000DEFC 0000AADC  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8000DF00 0000AAE0  EC 06 00 2A */	fadds f0, f6, f0
/* 8000DF04 0000AAE4  D0 04 00 08 */	stfs f0, 8(r4)
/* 8000DF08 0000AAE8  4E 80 00 20 */	blr 
}
#endif

extern const float lbl_804D7B10;
extern const float lbl_804D7B14;

extern float func_80022C30(float, float);
extern float func_80022DBC(float);

/*
#define lbl_804D7AC8 1.2f
#define lbl_804D7AC0 2.3f
#define lbl_804D7B10 3.4f
#define lbl_804D7B14 4.5f
#define lbl_804D7AA8 5.6f
*/

// Prologue is completely different.
#ifdef NONMATCHING
Vec *func_8000DF0C(Vec *a, Vec *b, Vec *c, Vec *d)
{
    if (lbl_804D7AC8 == c->z || lbl_804D7AC0 == c->z)
    {
        if (c->z == lbl_804D7AC8)
        {
            a->y = lbl_804D7B10;
            a->x = func_80022C30(d->x, d->y);
        }
        else
        {
            a->y = lbl_804D7B14;
            a->x = func_80022C30(-d->x, d->y);
        }
        //lbl_8000DF98
        a->z = lbl_804D7AA8;
    }
    //lbl_8000DFA4
    else
    {
        a->y = func_80022DBC(-c->z);
        a->x = func_80022C30(d->z, b->z);
        a->z = func_80022C30(c->y, c->x);
    }
    //lbl_8000DFD0
    return a;
}
/*
float *func_8000DF0C(float *a, float *b, float *c, float *d)
{
    if (lbl_804D7AC8 == c[2] || lbl_804D7AC0 == c[2])
    {
        if (c[2] == lbl_804D7AC8)
        {
            a[1] = lbl_804D7B10;
            a[0] = func_80022C30(d[0], d[1]);
        }
        else
        {
            a[1] = lbl_804D7B14;
            a[0] = func_80022C30(-d[0], d[1]);
        }
        //lbl_8000DF98
        a[2] = lbl_804D7AA8;
    }
    //lbl_8000DFA4
    else
    {
        a[1] = func_80022DBC(-c[2]);
        a[0] = func_80022C30(d[2], b[2]);
        a[2] = func_80022C30(c[1], c[0]);
    }
    //lbl_8000DFD0
    return a;
}
*/
#else
asm float *func_8000DF0C(float *a, float *b, float *c, float *d)
{
    nofralloc
/* 8000DF0C 0000AAEC  7C 08 02 A6 */	mflr r0
/* 8000DF10 0000AAF0  90 01 00 04 */	stw r0, 4(r1)
/* 8000DF14 0000AAF4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8000DF18 0000AAF8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8000DF1C 0000AAFC  7C DF 33 78 */	mr r31, r6
/* 8000DF20 0000AB00  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8000DF24 0000AB04  7C BE 2B 78 */	mr r30, r5
/* 8000DF28 0000AB08  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8000DF2C 0000AB0C  3B A4 00 00 */	addi r29, r4, 0
/* 8000DF30 0000AB10  93 81 00 18 */	stw r28, 0x18(r1)
/* 8000DF34 0000AB14  3B 83 00 00 */	addi r28, r3, 0
/* 8000DF38 0000AB18  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000DF3C 0000AB1C  C0 25 00 08 */	lfs f1, 8(r5)
/* 8000DF40 0000AB20  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000DF44 0000AB24  41 82 00 10 */	beq lbl_8000DF54
/* 8000DF48 0000AB28  C0 02 80 E0 */	lfs f0, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000DF4C 0000AB2C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000DF50 0000AB30  40 82 00 54 */	bne lbl_8000DFA4
lbl_8000DF54:
/* 8000DF54 0000AB34  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000DF58 0000AB38  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000DF5C 0000AB3C  40 82 00 20 */	bne lbl_8000DF7C
/* 8000DF60 0000AB40  C0 02 81 30 */	lfs f0, lbl_804D7B10-_SDA2_BASE_(r2)
/* 8000DF64 0000AB44  D0 1C 00 04 */	stfs f0, 4(r28)
/* 8000DF68 0000AB48  C0 3F 00 00 */	lfs f1, 0(r31)
/* 8000DF6C 0000AB4C  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8000DF70 0000AB50  48 01 4C C1 */	bl func_80022C30
/* 8000DF74 0000AB54  D0 3C 00 00 */	stfs f1, 0(r28)
/* 8000DF78 0000AB58  48 00 00 20 */	b lbl_8000DF98
lbl_8000DF7C:
/* 8000DF7C 0000AB5C  C0 02 81 34 */	lfs f0, lbl_804D7B14-_SDA2_BASE_(r2)
/* 8000DF80 0000AB60  D0 1C 00 04 */	stfs f0, 4(r28)
/* 8000DF84 0000AB64  C0 1F 00 00 */	lfs f0, 0(r31)
/* 8000DF88 0000AB68  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8000DF8C 0000AB6C  FC 20 00 50 */	fneg f1, f0
/* 8000DF90 0000AB70  48 01 4C A1 */	bl func_80022C30
/* 8000DF94 0000AB74  D0 3C 00 00 */	stfs f1, 0(r28)
lbl_8000DF98:
/* 8000DF98 0000AB78  C0 02 80 C8 */	lfs f0, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000DF9C 0000AB7C  D0 1C 00 08 */	stfs f0, 8(r28)
/* 8000DFA0 0000AB80  48 00 00 30 */	b lbl_8000DFD0
lbl_8000DFA4:
/* 8000DFA4 0000AB84  FC 20 08 50 */	fneg f1, f1
/* 8000DFA8 0000AB88  48 01 4E 15 */	bl func_80022DBC
/* 8000DFAC 0000AB8C  D0 3C 00 04 */	stfs f1, 4(r28)
/* 8000DFB0 0000AB90  C0 3F 00 08 */	lfs f1, 8(r31)
/* 8000DFB4 0000AB94  C0 5D 00 08 */	lfs f2, 8(r29)
/* 8000DFB8 0000AB98  48 01 4C 79 */	bl func_80022C30
/* 8000DFBC 0000AB9C  D0 3C 00 00 */	stfs f1, 0(r28)
/* 8000DFC0 0000ABA0  C0 3E 00 04 */	lfs f1, 4(r30)
/* 8000DFC4 0000ABA4  C0 5E 00 00 */	lfs f2, 0(r30)
/* 8000DFC8 0000ABA8  48 01 4C 69 */	bl func_80022C30
/* 8000DFCC 0000ABAC  D0 3C 00 08 */	stfs f1, 8(r28)
lbl_8000DFD0:
/* 8000DFD0 0000ABB0  7F 83 E3 78 */	mr r3, r28
/* 8000DFD4 0000ABB4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000DFD8 0000ABB8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8000DFDC 0000ABBC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8000DFE0 0000ABC0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8000DFE4 0000ABC4  83 81 00 18 */	lwz r28, 0x18(r1)
/* 8000DFE8 0000ABC8  38 21 00 28 */	addi r1, r1, 0x28
/* 8000DFEC 0000ABCC  7C 08 03 A6 */	mtlr r0
/* 8000DFF0 0000ABD0  4E 80 00 20 */	blr 
}
#endif

/*
#define lbl_804D7AC8 1.2f
#define lbl_804D7AC0 2.3f
#define lbl_804D7B10 3.4f
#define lbl_804D7B14 4.5f
#define lbl_804D7AA8 5.6f
*/

// Prologue differences... again
#ifdef NONMATCHING
Vec *func_8000DFF4(Vec *a, Vec *b, Vec *c)
{
    Vec sp18;
    float foo;

    func_80342E58(c, b, &sp18);
    foo = func_8000D5BC(sp18.x * sp18.x + sp18.y * sp18.y + sp18.z * sp18.z);
    if (foo != lbl_804D7AA8)
    {
        float bar = lbl_804D7AC0 / foo;
        sp18.x *= bar;
        sp18.y *= bar;
        sp18.z *= bar;
    }
    // possible inlined call to func_8000DF0C?
    //lbl_8000E080
    if (sp18.z == lbl_804D7AC8 || sp18.z == lbl_804D7AC0)
    {
        if (sp18.z == lbl_804D7AC8)
        {
            a->y = lbl_804D7B10;
            a->x = func_80022C30(c->x, c->y);
        }
        else
        {
            a->y = lbl_804D7B14;
            a->x = func_80022C30(-c->x, c->y);
        }
        a->z = lbl_804D7AA8;
    }
    //lbl_8000E0EC
    else
    {
        a->y = func_80022DBC(-sp18.z);
        a->x = func_80022C30(c->z, b->z);
        a->z = func_80022C30(sp18.y, sp18.x);
    }
    return a;
}
#else
asm Vec *func_8000DFF4(Vec *a, Vec *b, Vec *c)
{
    nofralloc
/* 8000DFF4 0000ABD4  7C 08 02 A6 */	mflr r0
/* 8000DFF8 0000ABD8  90 01 00 04 */	stw r0, 4(r1)
/* 8000DFFC 0000ABDC  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8000E000 0000ABE0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8000E004 0000ABE4  3B E5 00 00 */	addi r31, r5, 0
/* 8000E008 0000ABE8  38 A1 00 18 */	addi r5, r1, 0x18
/* 8000E00C 0000ABEC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8000E010 0000ABF0  3B C4 00 00 */	addi r30, r4, 0
/* 8000E014 0000ABF4  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8000E018 0000ABF8  3B A3 00 00 */	addi r29, r3, 0
/* 8000E01C 0000ABFC  38 7F 00 00 */	addi r3, r31, 0
/* 8000E020 0000AC00  48 33 4E 39 */	bl func_80342E58
/* 8000E024 0000AC04  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 8000E028 0000AC08  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8000E02C 0000AC0C  EC 21 00 72 */	fmuls f1, f1, f1
/* 8000E030 0000AC10  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 8000E034 0000AC14  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000E038 0000AC18  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8000E03C 0000AC1C  EC 01 00 2A */	fadds f0, f1, f0
/* 8000E040 0000AC20  EC 22 00 2A */	fadds f1, f2, f0
/* 8000E044 0000AC24  4B FF F5 79 */	bl func_8000D5BC
/* 8000E048 0000AC28  C0 02 80 C8 */	lfs f0, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000E04C 0000AC2C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000E050 0000AC30  41 82 00 30 */	beq lbl_8000E080
/* 8000E054 0000AC34  C0 42 80 E0 */	lfs f2, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000E058 0000AC38  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 8000E05C 0000AC3C  EC 22 08 24 */	fdivs f1, f2, f1
/* 8000E060 0000AC40  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000E064 0000AC44  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8000E068 0000AC48  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8000E06C 0000AC4C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000E070 0000AC50  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8000E074 0000AC54  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 8000E078 0000AC58  EC 00 00 72 */	fmuls f0, f0, f1
/* 8000E07C 0000AC5C  D0 01 00 20 */	stfs f0, 0x20(r1)
lbl_8000E080:
/* 8000E080 0000AC60  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000E084 0000AC64  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 8000E088 0000AC68  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000E08C 0000AC6C  41 82 00 10 */	beq lbl_8000E09C
/* 8000E090 0000AC70  C0 02 80 E0 */	lfs f0, lbl_804D7AC0-_SDA2_BASE_(r2)
/* 8000E094 0000AC74  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000E098 0000AC78  40 82 00 54 */	bne lbl_8000E0EC
lbl_8000E09C:
/* 8000E09C 0000AC7C  C0 02 80 E8 */	lfs f0, lbl_804D7AC8-_SDA2_BASE_(r2)
/* 8000E0A0 0000AC80  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8000E0A4 0000AC84  40 82 00 20 */	bne lbl_8000E0C4
/* 8000E0A8 0000AC88  C0 02 81 30 */	lfs f0, lbl_804D7B10-_SDA2_BASE_(r2)
/* 8000E0AC 0000AC8C  D0 1D 00 04 */	stfs f0, 4(r29)
/* 8000E0B0 0000AC90  C0 3F 00 00 */	lfs f1, 0(r31)
/* 8000E0B4 0000AC94  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8000E0B8 0000AC98  48 01 4B 79 */	bl func_80022C30
/* 8000E0BC 0000AC9C  D0 3D 00 00 */	stfs f1, 0(r29)
/* 8000E0C0 0000ACA0  48 00 00 20 */	b lbl_8000E0E0
lbl_8000E0C4:
/* 8000E0C4 0000ACA4  C0 02 81 34 */	lfs f0, lbl_804D7B14-_SDA2_BASE_(r2)
/* 8000E0C8 0000ACA8  D0 1D 00 04 */	stfs f0, 4(r29)
/* 8000E0CC 0000ACAC  C0 1F 00 00 */	lfs f0, 0(r31)
/* 8000E0D0 0000ACB0  C0 5F 00 04 */	lfs f2, 4(r31)
/* 8000E0D4 0000ACB4  FC 20 00 50 */	fneg f1, f0
/* 8000E0D8 0000ACB8  48 01 4B 59 */	bl func_80022C30
/* 8000E0DC 0000ACBC  D0 3D 00 00 */	stfs f1, 0(r29)
lbl_8000E0E0:
/* 8000E0E0 0000ACC0  C0 02 80 C8 */	lfs f0, lbl_804D7AA8-_SDA2_BASE_(r2)
/* 8000E0E4 0000ACC4  D0 1D 00 08 */	stfs f0, 8(r29)
/* 8000E0E8 0000ACC8  48 00 00 30 */	b lbl_8000E118
lbl_8000E0EC:
/* 8000E0EC 0000ACCC  FC 20 08 50 */	fneg f1, f1
/* 8000E0F0 0000ACD0  48 01 4C CD */	bl func_80022DBC
/* 8000E0F4 0000ACD4  D0 3D 00 04 */	stfs f1, 4(r29)
/* 8000E0F8 0000ACD8  C0 3F 00 08 */	lfs f1, 8(r31)
/* 8000E0FC 0000ACDC  C0 5E 00 08 */	lfs f2, 8(r30)
/* 8000E100 0000ACE0  48 01 4B 31 */	bl func_80022C30
/* 8000E104 0000ACE4  D0 3D 00 00 */	stfs f1, 0(r29)
/* 8000E108 0000ACE8  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8000E10C 0000ACEC  C0 41 00 18 */	lfs f2, 0x18(r1)
/* 8000E110 0000ACF0  48 01 4B 21 */	bl func_80022C30
/* 8000E114 0000ACF4  D0 3D 00 08 */	stfs f1, 8(r29)
lbl_8000E118:
/* 8000E118 0000ACF8  7F A3 EB 78 */	mr r3, r29
/* 8000E11C 0000ACFC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8000E120 0000AD00  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8000E124 0000AD04  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8000E128 0000AD08  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8000E12C 0000AD0C  38 21 00 38 */	addi r1, r1, 0x38
/* 8000E130 0000AD10  7C 08 03 A6 */	mtlr r0
/* 8000E134 0000AD14  4E 80 00 20 */	blr 
}
#endif

#ifdef NONMATCHING
Vec *func_8000E138(Vec *a, Vec *b)
{
    func_8000DB00(a, 1, b->x);
    func_8000DB00(a, 2, b->y);
    func_8000DB00(a, 4, b->z);
    return a;
}
#else
asm Vec *func_8000E138(Vec *a, Vec *b)
{
    nofralloc
/* 8000E138 0000AD18  7C 08 02 A6 */	mflr r0
/* 8000E13C 0000AD1C  90 01 00 04 */	stw r0, 4(r1)
/* 8000E140 0000AD20  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8000E144 0000AD24  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8000E148 0000AD28  3B E4 00 00 */	addi r31, r4, 0
/* 8000E14C 0000AD2C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8000E150 0000AD30  3B C3 00 00 */	addi r30, r3, 0
/* 8000E154 0000AD34  C0 24 00 00 */	lfs f1, 0(r4)
/* 8000E158 0000AD38  38 80 00 01 */	li r4, 1
/* 8000E15C 0000AD3C  4B FF F9 A5 */	bl func_8000DB00
/* 8000E160 0000AD40  C0 3F 00 04 */	lfs f1, 4(r31)
/* 8000E164 0000AD44  38 7E 00 00 */	addi r3, r30, 0
/* 8000E168 0000AD48  38 80 00 02 */	li r4, 2
/* 8000E16C 0000AD4C  4B FF F9 95 */	bl func_8000DB00
/* 8000E170 0000AD50  C0 3F 00 08 */	lfs f1, 8(r31)
/* 8000E174 0000AD54  38 7E 00 00 */	addi r3, r30, 0
/* 8000E178 0000AD58  38 80 00 04 */	li r4, 4
/* 8000E17C 0000AD5C  4B FF F9 85 */	bl func_8000DB00
/* 8000E180 0000AD60  7F C3 F3 78 */	mr r3, r30
/* 8000E184 0000AD64  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8000E188 0000AD68  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8000E18C 0000AD6C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8000E190 0000AD70  38 21 00 18 */	addi r1, r1, 0x18
/* 8000E194 0000AD74  7C 08 03 A6 */	mtlr r0
/* 8000E198 0000AD78  4E 80 00 20 */	blr 
}
#endif
