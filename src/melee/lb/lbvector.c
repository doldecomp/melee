#include <math.h>
#include <dolphin/mtx/mtxtypes.h>

// exactly the same as the one from math.h, but with one extra iteration
extern inline float sqrtf_accurate(float x)
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
   guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
   y=(float)(x*guess);
   return y ;
 }
  return x ;
}

static float vec_len(Vec *vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

static float vec_len2(Vec *vec)
{
    return sqrtf_accurate(vec->x * vec->x + vec->y * vec->y);
}

float func_8000D2EC(Vec *vec)
{
    float var1 = vec_len(vec);
    float var2;

    if (var1 == 0.0f)
        return 0.0f;
    var2 = 1.0f / var1;
    vec->x *= var2;
    vec->y *= var2;
    vec->z *= var2;
    return var1;
}

float func_8000D3B0(Vec *a)
{
    float var1 = sqrtf_accurate(a->x * a->x + a->y * a->y);
    float var2;

    if (var1 == 0.0f)
        return 0.0f;
    var2 = 1.0f / var1;
    a->x *= var2;
    a->y *= var2;
    return var1;
}

Vec *func_8000D46C(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
    return a;
}

Vec *func_8000D4A0(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    return a;
}

Vec *func_8000D4C4(Vec *a, Vec *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
    return a;
}

Vec *func_8000D4F8(Vec *a, Vec *b, Vec *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

Vec *func_8000D530(Vec *a, Vec *b, Vec *c)
{
    PSVECCrossProduct(a, b, c);
    func_8000D2EC(c);
    // NONMATCHING: epilogue scheduling issue
    return c;
}

// non-inlined sqrtf here

extern float func_80022D1C(float);

float func_8000D620(Vec *a, Vec *b)
{
    float f5 = vec_len(a) * vec_len(b);

    if (f5 > 1.000000013351432e-10f)
    {
        float f1 = (a->x * b->x + a->y * b->y + a->z * b->z) / f5;
        if (f1 > 1.0f)
            f1 = 1.0f;
        if (f1 < -1.0f)
            f1 = -1.0f;
        return func_80022D1C(f1);
    }
    return 0.0f;
}

float func_8000D790(Vec *a, Vec *b)
{
    float f4 = vec_len2(a) * vec_len2(b);
    float f1 = 0.0f;

    if (f4 != f1)
    {
        f1 = (a->x * b->x + a->y * b->y) / f4;
        if (f1 > 1.0f)
            f1 = 1.0f;
        if (f1 < -1.0f)
            f1 = -1.0f;
        return func_80022D1C(f1);
    }
    return 0.0f;
}

static float func_8000D8F4_inline(float f8)
{
    return 0.0056429998949170113f * f8 * f8 * f8 * f8 * f8 + (0.9878619909286499f * f8 - 0.15527099370956421f * f8 * f8 * f8);
}

static float test(float f8)
{
    if (f8 > 3.1415926535897931)
        f8 -= 6.2831853071795862;
    else if (f8 < -3.1415926535897931)
        f8 += 6.2831853071795862;
    return func_8000D8F4_inline(f8);
}

// TODO: fix register swaps
#ifdef NONMATCHING
void func_8000D8F4(Vec *a, Vec *b, float c)
{
    //float f12;
    //float f11;
    float f11;
    float f9;
    float f8;
    float f0 = sqrtf(b->y * b->y + b->z * b->z);
    float f7;
    //float f6;
    //float f5_;
    float f4;
    float f2;
    float f3;
    float f1;

    float f10;
    float f12;
    float f5;

    float f0_;
    float f6;
    float f5_;

    /*
    f8 = c;
    if (f8 > 3.1415926535897931)
        f8 -= 6.2831853071795862;
    else if (f8 < -3.1415926535897931)
        f8 += 6.2831853071795862;
    //lbl_8000D99C
    //f8 = 0.0056429998949170113f * f8 * f8 * f8 * f8 * f8 + (0.9878619909286499f * f8 - 0.15527099370956421f * f8 * f8 * f8);
    f8 = test(f8);
    */
    f8 = test(c);

    /*
    f9 = c + 1.5707963267948966;
    if (f9 > 3.1415926535897931)
        f9 -= 6.2831853071795862;
    else if (f9 < -3.1415926535897931)
        f9 += 6.2831853071795862;
    //lbl_8000DA0C
    //f9 = 0.0056429998949170113f * f9 * f9 * f9 * f9 * f9 + (0.9878619909286499f * f9 - 0.15527099370956421f * f9 * f9 * f9);
    f9 = test(f9);
    */
    f9 = test(c + 1.5707963267948966);

    if (f0 > 1.000000013351432e-10f)
    {
        f2 = b->z / f0;
        f3 = b->y / f0;

        f11 = a->x;
        f12 = a->y * f2 - a->z * f3;
        f5 = a->y * f3 + a->z * f2;
    }
    else
    {
        f11 = a->x;
        f12 = a->y;
        f5 = a->z;
    }
    //f10 = b->x;
    //f4 = f5 * f0;
    //f7 = f12 * f8;
    f4 = f11 * b->x  +  f5 * f0;
    //f5 = f5 * f10;
    //f6 = f12 * f9;
    f11 = f11 * f0  -  f5 * b->x;
    //f5 = f4 * f10;
    //f4 = f4 * f0;
    f7 = f11 * f9  -  f12 * f8;
    //fcmpo cr0, f0, f1
    f6 = f11 * f8  +  f12 * f9;
    f0_ = f7 * f0  +  f4 * b->x;
    f5_ = -f7 * b->x  +  f4 * f0;
    if (f0 > 1.000000013351432e-10f)
    {
        a->x = f0_;
        a->y = f6 * f2 + f5_ * f3;
        a->z = -f6 * f3 + f5_ * f2;
    }
    else
    {
        a->x = f0_;
        a->y = f6;
        a->z = f5_;
    }
}
#else
extern const float lbl_804D7AA8;
extern const double lbl_804D7AB0;
extern const double lbl_804D7AB8;
extern const float lbl_804D7AC4;
extern const double lbl_804D7AD0;
extern const double lbl_804D7AD8;
extern const double lbl_804D7AE0;
extern const float lbl_804D7AE8;
extern const float lbl_804D7AEC;
extern const float lbl_804D7AF0;
extern const double lbl_804D7AF8;
asm void func_8000D8F4(Vec *a, Vec *b, float c)
{
    nofralloc
/* 8000D8F4 0000A4D4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8000D8F8 0000A4D8  C0 84 00 04 */	lfs f4, 4(r4)
/* 8000D8FC 0000A4DC  C0 04 00 08 */	lfs f0, 8(r4)
/* 8000D900 0000A4E0  EC A4 01 32 */	fmuls f5, f4, f4
/* 8000D904 0000A4E4  C0 82 80 C8 */	lfs f4, lbl_804D7AA8 //@sda21(r2)
/* 8000D908 0000A4E8  EC 00 00 32 */	fmuls f0, f0, f0
/* 8000D90C 0000A4EC  EC 05 00 2A */	fadds f0, f5, f0
/* 8000D910 0000A4F0  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 8000D914 0000A4F4  40 81 00 50 */	ble lbl_8000D964
/* 8000D918 0000A4F8  FC A0 00 34 */	frsqrte f5, f0
/* 8000D91C 0000A4FC  C8 E2 80 D0 */	lfd f7, lbl_804D7AB0 //@sda21(r2)
/* 8000D920 0000A500  C8 C2 80 D8 */	lfd f6, lbl_804D7AB8 //@sda21(r2)
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
/* 8000D964 0000A544  C8 82 80 F0 */	lfd f4, lbl_804D7AD0 //@sda21(r2)
/* 8000D968 0000A548  FD 00 08 90 */	fmr f8, f1
/* 8000D96C 0000A54C  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000D970 0000A550  40 81 00 14 */	ble lbl_8000D984
/* 8000D974 0000A554  C8 82 80 F8 */	lfd f4, lbl_804D7AD8 //@sda21(r2)
/* 8000D978 0000A558  FD 08 20 28 */	fsub f8, f8, f4
/* 8000D97C 0000A55C  FD 00 40 18 */	frsp f8, f8
/* 8000D980 0000A560  48 00 00 1C */	b lbl_8000D99C
lbl_8000D984:
/* 8000D984 0000A564  C8 82 81 00 */	lfd f4, lbl_804D7AE0 //@sda21(r2)
/* 8000D988 0000A568  FC 01 20 40 */	fcmpo cr0, f1, f4
/* 8000D98C 0000A56C  40 80 00 10 */	bge lbl_8000D99C
/* 8000D990 0000A570  C8 82 80 F8 */	lfd f4, lbl_804D7AD8 //@sda21(r2)
/* 8000D994 0000A574  FD 08 20 2A */	fadd f8, f8, f4
/* 8000D998 0000A578  FD 00 40 18 */	frsp f8, f8
lbl_8000D99C:
/* 8000D99C 0000A57C  C0 82 81 10 */	lfs f4, lbl_804D7AF0 //@sda21(r2)
/* 8000D9A0 0000A580  C0 A2 81 0C */	lfs f5, lbl_804D7AEC //@sda21(r2)
/* 8000D9A4 0000A584  EC E4 02 32 */	fmuls f7, f4, f8
/* 8000D9A8 0000A588  C8 82 81 18 */	lfd f4, lbl_804D7AF8 //@sda21(r2)
/* 8000D9AC 0000A58C  EC A5 02 32 */	fmuls f5, f5, f8
/* 8000D9B0 0000A590  C0 C2 81 08 */	lfs f6, lbl_804D7AE8 //@sda21(r2)
/* 8000D9B4 0000A594  FD 21 20 2A */	fadd f9, f1, f4
/* 8000D9B8 0000A598  EC E7 02 32 */	fmuls f7, f7, f8
/* 8000D9BC 0000A59C  C8 22 80 F0 */	lfd f1, lbl_804D7AD0 //@sda21(r2)
/* 8000D9C0 0000A5A0  EC 85 02 32 */	fmuls f4, f5, f8
/* 8000D9C4 0000A5A4  FD 20 48 18 */	frsp f9, f9
/* 8000D9C8 0000A5A8  EC A8 01 F2 */	fmuls f5, f8, f7
/* 8000D9CC 0000A5AC  EC 88 01 32 */	fmuls f4, f8, f4
/* 8000D9D0 0000A5B0  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000D9D4 0000A5B4  EC A8 01 72 */	fmuls f5, f8, f5
/* 8000D9D8 0000A5B8  EC 26 22 38 */	fmsubs f1, f6, f8, f4
/* 8000D9DC 0000A5BC  ED 08 09 7A */	fmadds f8, f8, f5, f1
/* 8000D9E0 0000A5C0  40 81 00 14 */	ble lbl_8000D9F4
/* 8000D9E4 0000A5C4  C8 22 80 F8 */	lfd f1, lbl_804D7AD8 //@sda21(r2)
/* 8000D9E8 0000A5C8  FD 29 08 28 */	fsub f9, f9, f1
/* 8000D9EC 0000A5CC  FD 20 48 18 */	frsp f9, f9
/* 8000D9F0 0000A5D0  48 00 00 1C */	b lbl_8000DA0C
lbl_8000D9F4:
/* 8000D9F4 0000A5D4  C8 22 81 00 */	lfd f1, lbl_804D7AE0 //@sda21(r2)
/* 8000D9F8 0000A5D8  FC 09 08 40 */	fcmpo cr0, f9, f1
/* 8000D9FC 0000A5DC  40 80 00 10 */	bge lbl_8000DA0C
/* 8000DA00 0000A5E0  C8 22 80 F8 */	lfd f1, lbl_804D7AD8 //@sda21(r2)
/* 8000DA04 0000A5E4  FD 29 08 2A */	fadd f9, f9, f1
/* 8000DA08 0000A5E8  FD 20 48 18 */	frsp f9, f9
lbl_8000DA0C:
/* 8000DA0C 0000A5EC  C0 22 81 10 */	lfs f1, lbl_804D7AF0 //@sda21(r2)
/* 8000DA10 0000A5F0  C0 82 81 0C */	lfs f4, lbl_804D7AEC //@sda21(r2)
/* 8000DA14 0000A5F4  EC C1 02 72 */	fmuls f6, f1, f9
/* 8000DA18 0000A5F8  C0 22 80 E4 */	lfs f1, lbl_804D7AC4 //@sda21(r2)
/* 8000DA1C 0000A5FC  EC 84 02 72 */	fmuls f4, f4, f9
/* 8000DA20 0000A600  C0 A2 81 08 */	lfs f5, lbl_804D7AE8 //@sda21(r2)
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
/* 8000DA50 0000A630  EC 42 00 24 */	fdivs f2, f2, f0  // b->z/ f0
/* 8000DA54 0000A634  C0 A3 00 08 */	lfs f5, 8(r3)
/* 8000DA58 0000A638  C0 C3 00 04 */	lfs f6, 4(r3)
/* 8000DA5C 0000A63C  C1 63 00 00 */	lfs f11, 0(r3)
/* 8000DA60 0000A640  EC 61 00 24 */	fdivs f3, f1, f0  // b->y / f0
/* 8000DA64 0000A644  EC 85 00 F2 */	fmuls f4, f5, f3  // a->z * (b->y / f0)
/* 8000DA68 0000A648  EC 25 00 B2 */	fmuls f1, f5, f2  // a->z * (b->z / f0)
/* 8000DA6C 0000A64C  ED 86 20 B8 */	fmsubs f12, f6, f2, f4  // a->y * (b->z / f0) - a->z * (b->y / f0)
/* 8000DA70 0000A650  EC A6 08 FA */	fmadds f5, f6, f3, f1  // a->y * (b->y / f0) + a->z * (b->z / f0);
/* 8000DA74 0000A654  48 00 00 10 */	b lbl_8000DA84
lbl_8000DA78:
/* 8000DA78 0000A658  C1 63 00 00 */	lfs f11, 0(r3)
/* 8000DA7C 0000A65C  C1 83 00 04 */	lfs f12, 4(r3)
/* 8000DA80 0000A660  C0 A3 00 08 */	lfs f5, 8(r3)
lbl_8000DA84:
/* 8000DA84 0000A664  C1 44 00 00 */	lfs f10, 0(r4)
/* 8000DA88 0000A668  EC 85 00 32 */	fmuls f4, f5, f0
/* 8000DA8C 0000A66C  C0 22 80 E4 */	lfs f1, lbl_804D7AC4 //@sda21(r2)
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
#pragma peephole on
#endif

void func_8000DB00(Vec *a, int b, float c)
{
    //float f8;
    //float f9;
    float f6;
    float f4;
    float x;
    float y;
    float z;

    f6 = test(c);
    f4 = test(c + 1.5707963267948966);

    switch (b)
    {
    case 1:
        x = a->x;
        y = a->y * f4 - a->z * f6;
        z = a->y * f6 + a->z * f4;
        break;
    case 2:
        x = a->x * f4 + a->z * f6;
        y = a->y;
        z = a->z * f4 - a->x * f6;
        break;
    case 4:
        x = a->x * f4 - a->y * f6;
        y = a->x * f6 + a->y * f4;
        z = a->z;
        break;
    }
    a->x = x;
    a->y = y;
    a->z = z;
}

void func_8000DC6C(Vec *a, Vec *b)
{
    float f2 = (b->x * a->x + b->y * a->y) * -2.0f;

    a->x += b->x * f2;
    a->y += b->y * f2;
}

float func_8000DCA8(Vec *a, Vec *b)
{
    return (a->x*b->x + a->y*b->y)
         / (sqrtf(a->x*a->x + a->y*a->y) * sqrtf(b->x*b->x + b->y*b->y));
}

Vec *func_8000DDAC(Vec *a, Vec *b, Vec *c, float d)
{
    func_8000D4F8(b, a, c);
    c->x *= d;
    c->y *= d;
    c->z *= d;
    func_8000D46C(c, a);
    return c;
}

Vec *func_8000DE38(Mtx a, Vec *b, float c)
{
    float var1;
    float var2;

    if (c > 1.0f)
        c = 1.0f;
    else if (c < 0.0f)
        c = 0.0f;

    var1 = a[0][0] *  2.0f - a[0][3] * 4.0f + a[1][2] * 2.0f;
    var2 = a[0][0] * -3.0f + a[0][3] * 4.0f - a[1][2];
    b->x = a[0][0] + (var1*c*c + var2*c);

    var1 = a[0][1] *  2.0f - a[1][0] * 4.0f + a[1][3] * 2.0f;
    var2 = a[0][1] * -3.0f + a[1][0] * 4.0f - a[1][3];
    b->y = a[0][1] + (var1*c*c + var2*c);

    var1 = a[0][2] *  2.0f - a[1][1] * 4.0f + a[2][0] * 2.0f;
    var2 = a[0][2] * -3.0f + a[1][1] * 4.0f - a[2][0];
    b->z = a[0][2] + (var1*c*c + var2*c);

    return b;
}

const float lbl_804D7AA8 = 0.0f;
const double lbl_804D7AB0 = 0.5;
const double lbl_804D7AB8 = 3.0;
const float lbl_804D7AC0 = 1.0f;
const float lbl_804D7AC4 = 1.000000013351432e-10f;
const float lbl_804D7AC8 = -1.0f;
const double lbl_804D7AD0 = 3.1415926535897931;
const double lbl_804D7AD8 = 6.2831853071795862;
const double lbl_804D7AE0 = -3.1415926535897931;
const float lbl_804D7AE8 = 0.9878619909286499f;
const float lbl_804D7AEC = 0.15527099370956421f;
const float lbl_804D7AF0 = 0.0056429998949170113f;
const double lbl_804D7AF8 = 1.5707963267948966;
const float lbl_804D7B00 = 2.0f;
const float lbl_804D7B04 = -2.0f;
const float lbl_804D7B08 = 4.0f;
const float lbl_804D7B0C = -3.0f;
const float lbl_804D7B10 = 1.5707963705062866f;
const float lbl_804D7B14 = -1.5707963705062866f;
const float lbl_804D7B18 = -50000.0f;
const float lbl_804D7B1C = 50000.0f;
const float lbl_804D7B20 = -0.0099999997764825821f;
const float lbl_804D7B24 = 0.0099999997764825821f;
const float lbl_804D7B28 = 9.9999997473787516e-06f;
const float lbl_804D7B2C = -9.9999997473787516e-06f;
