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
extern float func_8000D5BC(float, float);

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
    // NONMATCHING: epilogue
    return a;
}

Vec *func_8000DFF4(Vec *a, Vec *b, Vec *c)
{
    Vec sp18;

    PSVECCrossProduct(c, b, &sp18);
    func_8000D2EC(&sp18);
    func_8000DF0C(a, b, &sp18, c);
    // NONMATCHING: epilogue
    return a;
}

Vec *func_8000E138(Vec *a, Vec *b)
{
    func_8000DB00(a, 1, b->x);
    func_8000DB00(a, 2, b->y);
    func_8000DB00(a, 4, b->z);
    // NONMATCHING: epilogue
    return a;
}

float func_8000E19C(float n)
{
    return sqrtf_accurate(n);
}
/*
//((condition) ? ((void) 0) : __assertion_failed(#condition,__FILE__, __LINE__))
#define myassert(condition, line) ((condition) ? ((void) 0) : __assert(#condition,__FILE__, line))

float func_8000E210(struct Struct8000E210 *a, Vec *pos3d)
{
    //((b) ? ((void)0) : __assert("lbvector.c", 0x2A4, "pos3d"));
    //((pos3d->x>-50000.0F&&pos3d->x<50000.0F) ? ((void)0) : __
    myassert(pos3d, 0x2A4);
    myassert(pos3d->x>-50000.0F&&pos3d->x<50000.0F);
    myassert(pos3d->y>-50000.0F&&pos3d->y<50000.0F);
    myassert(pos3d->z>-50000.0F&&pos3d->z<50000.0F);
    
}
*/

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
