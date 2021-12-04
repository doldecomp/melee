#include <math.h>
#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/gx/GXTransform.h>

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
    float len = vec_len(vec);
    float inv;

    if (len == 0.0f)
        return 0.0f;
    inv = 1.0f / len;
    vec->x *= inv;
    vec->y *= inv;
    vec->z *= inv;
    return len;
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
    return c;
}

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

static float sin(float angle)
{
    if (angle > 3.1415926535897931)
        angle -= 6.2831853071795862;
    else if (angle < -3.1415926535897931)
        angle += 6.2831853071795862;
    return 0.9878619909286499f * angle - 0.15527099370956421f * angle * angle * angle + 0.0056429998949170113f * angle * angle * angle * angle * angle;
}

static float cos(float angle)
{
    angle += 1.5707963267948966;
    if (angle > 3.1415926535897931)
        angle -= 6.2831853071795862;
    else if (angle < -3.1415926535897931)
        angle += 6.2831853071795862;
    return 0.9878619909286499f * angle - 0.15527099370956421f * angle * angle * angle + 0.0056429998949170113f * angle * angle * angle * angle * angle;
}

void func_8000D8F4(Vec *a, Vec *b, float angle)
{
    float f0 = sqrtf(b->y * b->y + b->z * b->z);
    float s = sin(angle);
    float c = cos(angle);
    float f2;
    float f3;
    float x, y, z;
    float f11;
    float f4;
    float v3;
    float v4;

    if (f0 > 1.000000013351432e-10f)
    {
        f2 = b->z / f0;
        f3 = b->y / f0;

        x = a->x;
        y = a->y * f2 - a->z * f3;
        z = a->y * f3 + a->z * f2;
    }
    else
    {
        x = a->x;
        y = a->y;
        z = a->z;
    }

    f11 = x * f0  -  z * b->x;
    f4 = x * b->x  +  z * f0;

    v3 = f11 * c  -  y * s;
    v4 = f11 * s  +  y * c;

    x = v3 * f0  +  f4 * b->x;
    y = v4;
    z = -v3 * b->x  +  f4 * f0;

    if (f0 > 1.000000013351432e-10f)
    {
        a->x = x;
        a->y = y * f2 + z * f3;
        a->z = -y * f3 + z * f2;
    }
    else
    {
        a->x = x;
        a->y = y;
        a->z = z;
    }
}

void func_8000DB00(Vec *a, int b, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    float x;
    float y;
    float z;

    switch (b)
    {
    case 1:
        x = a->x;
        y = a->y * c - a->z * s;
        z = a->y * s + a->z * c;
        break;
    case 2:
        x = a->x * c + a->z * s;
        y = a->y;
        z = a->z * c - a->x * s;
        break;
    case 4:
        x = a->x * c - a->y * s;
        y = a->x * s + a->y * c;
        z = a->z;
        break;
    }
    a->x = x;
    a->y = y;
    a->z = z;
}

float dummy(void) { return 2.0f; } // needed here to force order of floats in .sdata2 section

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

extern float func_80022DBC(float);
extern float func_80022C30(float, float);
extern float sqrtf__Ff(float, float);

Vec *func_8000DF0C(Vec *a, Vec *b, Vec *c, Vec *d)
{
    if (c->z == -1.0f || c->z == 1.0f)
    {
        if (c->z == -1.0f)
        {
            a->y = 1.5707963705062866f;
            a->x = func_80022C30(d->x, d->y);
        }
        else
        {
            a->y = -1.5707963705062866f;
            a->x = func_80022C30(-d->x, d->y);
        }
        a->z = 0.0f;
    }
    else
    {
        a->y = func_80022DBC(-c->z);
        a->x = func_80022C30(d->z, b->z);
        a->z = func_80022C30(c->y, c->x);
    }
    return a;
}

Vec *func_8000DFF4(Vec *a, Vec *b, Vec *c)
{
    Vec sp18;

    PSVECCrossProduct(c, b, &sp18);
    func_8000D2EC(&sp18);
    func_8000DF0C(a, b, &sp18, c);
    return a;
}

Vec *func_8000E138(Vec *a, Vec *b)
{
    func_8000DB00(a, 1, b->x);
    func_8000DB00(a, 2, b->y);
    func_8000DB00(a, 4, b->z);
    return a;
}

float func_8000E19C(float n)
{
    return sqrtf_accurate(n);
}

struct Struct8000E210
{
    u8 filler0[0xC];
    float unkC;
    float unk10;
    float unk14;
    float unk18;
    u8 filler1C[0x38-0x1C];
    float unk38;
    float unk3C;
    float unk40;
    float unk44;
    float unk48;
    float unk4C;
};

extern void __assert(const char *file, int line, const char *condition);
#define assert_line(condition, line) ((condition) ? ((void) 0) : __assert(__FILE__, line, #condition))

extern MtxPtr func_80369688(struct Struct8000E210 *);

float *func_8000E210(struct Struct8000E210 *a, Vec *pos3d, float *c, int d)
{
    u8 filler[16];
    Mtx projMtx;
    float sp90[7];
    float sp78[6];
    Mtx sp48;
    Vec sp3C;
    Vec sp30;
    Point3d sp24;
    Point3d sp18;
    MtxPtr r3;
    float f1;

    assert_line(pos3d, 676);
    assert_line(pos3d->x>-50000.0F&&pos3d->x<50000.0F, 677);
    assert_line(pos3d->y>-50000.0F&&pos3d->y<50000.0F, 678);
    assert_line(pos3d->z>-50000.0F&&pos3d->z<50000.0F, 679);

    sp3C = *pos3d;
    switch (func_8036A12C(a))
    {
    case 1:
        C_MTXPerspective(projMtx, a->unk40, a->unk44, a->unk38, a->unk3C);
        sp90[0] = 0.0f;
        sp90[1] = projMtx[0][0];
        sp90[2] = projMtx[0][2];
        sp90[3] = projMtx[1][1];
        sp90[4] = projMtx[1][2];
        sp90[5] = projMtx[2][2];
        sp90[6] = projMtx[2][3];
        break;
    case 3:
        C_MTXOrtho(&projMtx, a->unk40, a->unk44, a->unk48, a->unk4C, a->unk38, a->unk3C);
        sp90[0] = 1.0f;
        sp90[1] = projMtx[0][0];
        sp90[2] = projMtx[0][3];
        sp90[3] = projMtx[1][1];
        sp90[4] = projMtx[1][3];
        sp90[5] = projMtx[2][2];
        sp90[6] = projMtx[2][3];
        break;
    default:
        return NULL;
    }

    sp78[0] = a->unkC;
    sp78[1] = a->unk14;

    sp78[2] = a->unk10 - a->unkC;
    sp78[3] = a->unk18 - a->unk14;
    sp78[4] = 0.0f;
    sp78[5] = 1.0f;

    if (d != 0)
    {
        func_80368784(a, &sp24);
        func_80368E70(a, &sp30);
        func_803686AC(a, &sp18);
        C_MTXLookAt(sp48, &sp24, &sp30, &sp18);
        r3 = sp48;
    }
    else
        r3 = func_80369688(a);

    f1 = r3[2][0] * pos3d->x + r3[2][1] * pos3d->y + r3[2][2] * pos3d->z + r3[2][3];
    if (f1 > -0.0099999999f)
    {
        f1 = -f1 - 0.0099999999f;
        sp3C.x += r3[2][0] * f1;
        sp3C.y += r3[2][1] * f1;
        sp3C.z += r3[2][2] * f1;
    }

    GXProject(sp3C.x, sp3C.y, sp3C.z, r3, sp90, sp78, &c[0], &c[1], &c[2]);
    return c;
}

void func_8000E530(Mtx a, Vec *b)
{
    float f0 = sin(b->x);
    float f1 = cos(b->x);
    float f2 = sin(b->y);
    float f3 = cos(b->y);
    float f11 = sin(b->z);
    float f10 = cos(b->z);
    float f12 = f0 * f2;
    float f13 = f1 * f2;

    a[0][0] = f3 * f10;
    a[1][0] = f3 * f11;
    a[2][0] = -f2;
    a[0][1] = f10 * f12 - f1 * f11;
    a[1][1] = f11 * f12 + f1 * f10;
    a[2][1] = f0 * f3;
    a[0][2] = f10 * f13 + f0 * f11;
    a[1][2] = f11 * f13 - f0 * f10;
    a[2][2] = f1 * f3;
    a[0][3] = 0.0f;
    a[1][3] = 0.0f;
    a[2][3] = 0.0f;
}

float func_8000E838(Vec *a, Vec *b, Vec *c, Vec *d)
{
    Vec v1;
    Vec v2;
    float f3;
    int tooSmall;

    // also matches with these calls written out
    func_8000D4F8(b, a, &v1);
    f3 = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
    func_8000D4F8(c, a, &v2);
    if (f3 < 9.9999997473787516e-06f && f3 > -9.9999997473787516e-06f)
        tooSmall = 1;
    else
        tooSmall = 0;
    if (tooSmall)
    {
        *d = *a;
        return vec_len(&v2);
    }
    else
    {
        Vec v3;
        float f1 = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / f3;

        d->x = a->x + v1.x * f1;
        d->y = a->y + v1.y * f1;
        d->z = a->z + v1.z * f1;
        func_8000D4F8(c, d, &v3);
        return vec_len(&v3);
        
    }
}
