#include <math.h>
#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/gx/GXTransform.h>

#include "sysdolphin/baselib/cobj.h"

#define PI 3.1415926535897931

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
   guess = _half*guess*(_three - guess*guess*x);  // extra iteration
   y=(float)(x*guess);
   return y ;
 }
  return x ;
}

static float lbvector_len(Vec *vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

static float lbvector_len_xy(Vec *vec)
{
    return sqrtf_accurate(vec->x * vec->x + vec->y * vec->y);
}

float lbvector_normalize(Vec *vec)
{
    float len = lbvector_len(vec);
    float inv;

    if (len == 0.0f)
        return 0.0f;
    inv = 1.0f / len;
    vec->x *= inv;
    vec->y *= inv;
    vec->z *= inv;
    return len;
}

float lbvector_normalize_xy(Vec *a)
{
    float len = sqrtf_accurate(a->x * a->x + a->y * a->y);
    float inv;

    if (len == 0.0f)
        return 0.0f;
    inv = 1.0f / len;
    a->x *= inv;
    a->y *= inv;
    return len;
}

Vec *lbvector_add(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
    return a;
}

Vec *lbvector_add_xy(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    return a;
}

Vec *lbvector_sub(Vec *a, Vec *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
    return a;
}

Vec *lbvector_diff(Vec *a, Vec *b, Vec *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

Vec *lbvector_crossprod_normalized(Vec *a, Vec *b, Vec *c)
{
    PSVECCrossProduct(a, b, c);
    lbvector_normalize(c);
    return c;
}

extern float func_80022D1C(float);

float func_8000D620(Vec *a, Vec *b)
{
    float f5 = lbvector_len(a) * lbvector_len(b);

    if (f5 > 0.0000000001f)
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
    float f4 = lbvector_len_xy(a) * lbvector_len_xy(b);
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

// Taylor series approximations of sin and cos

static float sin(float angle)
{
    if (angle > PI)
        angle -= 2.0 * PI;
    else if (angle < -PI)
        angle += 2.0 * PI;
    return 0.9878619909286499f * angle - 0.15527099370956421f * angle * angle * angle + 0.0056429998949170113f * angle * angle * angle * angle * angle;
}

static float cos(float angle)
{
    angle += PI / 2.0;
    if (angle > PI)
        angle -= 2.0 * PI;
    else if (angle < -PI)
        angle += 2.0 * PI;
    return 0.9878619909286499f * angle - 0.15527099370956421f * angle * angle * angle + 0.0056429998949170113f * angle * angle * angle * angle * angle;
}

void func_8000D8F4(Vec *a, Vec *b, float angle)
{
    float f0 = sqrtf(b->y * b->y + b->z * b->z);
    float s = sin(angle);
    float c = cos(angle);
    float var5;
    float var6;
    float x, y, z;
    float var1;
    float var2;
    float var3;
    float var4;

    if (f0 > 0.0000000001f)
    {
        var5 = b->z / f0;
        var6 = b->y / f0;

        x = a->x;
        y = a->y * var5 - a->z * var6;
        z = a->y * var6 + a->z * var5;
    }
    else
    {
        x = a->x;
        y = a->y;
        z = a->z;
    }

    var1 = x * f0  -  z * b->x;
    var2 = x * b->x  +  z * f0;

    var3 = var1 * c  -  y * s;
    var4 = var1 * s  +  y * c;

    x = var3 * f0  +  var2 * b->x;
    y = var4;
    z = -var3 * b->x  +  var2 * f0;

    if (f0 > 0.0000000001f)
    {
        a->x = x;
        a->y = y * var5 + z * var6;
        a->z = -y * var6 + z * var5;
    }
    else
    {
        a->x = x;
        a->y = y;
        a->z = z;
    }
}

void lbvector_rotate(Vec *v, int axis, float angle)
{
    float s = sin(angle);
    float c = cos(angle);
    float x;
    float y;
    float z;

    switch (axis)
    {
    case 1:  // rotate about x axis
        x = v->x;
        y = v->y * c - v->z * s;
        z = v->y * s + v->z * c;
        break;
    case 2:  // rotate about y axis
        x = v->x * c + v->z * s;
        y = v->y;
        z = v->z * c - v->x * s;
        break;
    case 4:  // rotate about z axis
        x = v->x * c - v->y * s;
        y = v->x * s + v->y * c;
        z = v->z;
        break;
    }
    v->x = x;
    v->y = y;
    v->z = z;
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

Vec *func_8000DDAC(Vec *a, Vec *b, Vec *result, float scale)
{
    lbvector_diff(b, a, result);
    result->x *= scale;
    result->y *= scale;
    result->z *= scale;
    lbvector_add(result, a);
    return result;
}

Vec *func_8000DE38(Mtx m, Vec *v, float c)
{
    float var1;
    float var2;

    if (c > 1.0f)
        c = 1.0f;
    else if (c < 0.0f)
        c = 0.0f;

    var1 = m[0][0] *  2.0f - m[0][3] * 4.0f + m[1][2] * 2.0f;
    var2 = m[0][0] * -3.0f + m[0][3] * 4.0f - m[1][2];
    v->x = m[0][0] + (var1*c*c + var2*c);

    var1 = m[0][1] *  2.0f - m[1][0] * 4.0f + m[1][3] * 2.0f;
    var2 = m[0][1] * -3.0f + m[1][0] * 4.0f - m[1][3];
    v->y = m[0][1] + (var1*c*c + var2*c);

    var1 = m[0][2] *  2.0f - m[1][1] * 4.0f + m[2][0] * 2.0f;
    var2 = m[0][2] * -3.0f + m[1][1] * 4.0f - m[2][0];
    v->z = m[0][2] + (var1*c*c + var2*c);

    return v;
}

extern float func_80022DBC(float);
extern float func_80022C30(float, float);

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
    lbvector_normalize(&sp18);
    func_8000DF0C(a, b, &sp18, c);
    return a;
}

Vec *func_8000E138(Vec *v, Vec *rot)
{
    lbvector_rotate(v, 1, rot->x);
    lbvector_rotate(v, 2, rot->y);
    lbvector_rotate(v, 4, rot->z);
    return v;
}

float func_8000E19C(float n)
{
    return sqrtf_accurate(n);
}

#define assert_line(condition, line) ((condition) ? ((void) 0) : __assert(__FILE__, line, #condition))

extern MtxPtr func_80369688(HSD_CObj *);

Vec *func_8000E210(HSD_CObj *cobj, const Point3d *pos3d, Point3d *screenCoords, int d)
{
    u8 filler[16];
    Mtx projMtx;
    float projection[7];  // projection params
    float viewport[6];  // viewport params
    Mtx m;
    Point3d point;
    Vec upVec;
    Point3d camPos;
    Point3d target;
    MtxPtr mvMtx;  // modelview matrix
    float f1;

    assert_line(pos3d, 676);
    assert_line(pos3d->x>-50000.0F&&pos3d->x<50000.0F, 677);
    assert_line(pos3d->y>-50000.0F&&pos3d->y<50000.0F, 678);
    assert_line(pos3d->z>-50000.0F&&pos3d->z<50000.0F, 679);

    point = *pos3d;
    switch (func_8036A12C(cobj))
    {
    case PROJ_PERSPECTIVE:
        C_MTXPerspective(projMtx, cobj->projection_param.perspective.fov, cobj->projection_param.perspective.aspect, cobj->near, cobj->far);
        projection[0] = 0.0f;
        projection[1] = projMtx[0][0];
        projection[2] = projMtx[0][2];
        projection[3] = projMtx[1][1];
        projection[4] = projMtx[1][2];
        projection[5] = projMtx[2][2];
        projection[6] = projMtx[2][3];
        break;
    case PROJ_ORTHO:
        C_MTXOrtho(&projMtx, cobj->projection_param.ortho.top, cobj->projection_param.ortho.bottom, cobj->projection_param.ortho.left, cobj->projection_param.ortho.right, cobj->near, cobj->far);
        projection[0] = 1.0f;
        projection[1] = projMtx[0][0];
        projection[2] = projMtx[0][3];
        projection[3] = projMtx[1][1];
        projection[4] = projMtx[1][3];
        projection[5] = projMtx[2][2];
        projection[6] = projMtx[2][3];
        break;
    default:
        return NULL;
    }

    viewport[0] = cobj->viewport_left;  // x origin
    viewport[1] = cobj->viewport_top;  // y origin
    viewport[2] = cobj->viewport_right - cobj->viewport_left;  // width
    viewport[3] = cobj->viewport_bottom - cobj->viewport_top;  // height
    viewport[4] = 0.0f;  // near z
    viewport[5] = 1.0f;  // far z

    if (d != 0)
    {
        func_80368784(cobj, &camPos);
        func_80368E70(cobj, &upVec);
        func_803686AC(cobj, &target);
        C_MTXLookAt(m, &camPos, &upVec, &target);
        mvMtx = m;
    }
    else
        mvMtx = func_80369688(cobj);

    f1 = mvMtx[2][0] * pos3d->x
       + mvMtx[2][1] * pos3d->y
       + mvMtx[2][2] * pos3d->z
       + mvMtx[2][3];
    if (f1 > -0.01f)
    {
        f1 = -f1 - 0.01f;
        point.x += mvMtx[2][0] * f1;
        point.y += mvMtx[2][1] * f1;
        point.z += mvMtx[2][2] * f1;
    }

    GXProject(
        point.x, point.y, point.z,
        mvMtx,
        projection, viewport,
        &screenCoords->x, &screenCoords->y, &screenCoords->z);
    return screenCoords;
}

void func_8000E530(Mtx m, Vec *v)
{
    float sx = sin(v->x);
    float cx = cos(v->x);
    float sy = sin(v->y);
    float cy = cos(v->y);
    float sz = sin(v->z);
    float cz = cos(v->z);

    float sxsy = sx * sy;
    float cxsy = cx * sy;

    m[0][0] = cy * cz;
    m[1][0] = cy * sz;
    m[2][0] = -sy;

    m[0][1] = cz * sxsy - cx * sz;
    m[1][1] = sz * sxsy + cx * cz;
    m[2][1] = sx * cy;

    m[0][2] = cz * cxsy + sx * sz;
    m[1][2] = sz * cxsy - sx * cz;
    m[2][2] = cx * cy;

    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}

float func_8000E838(Vec *a, Vec *b, Vec *c, Vec *d)
{
    Vec v1;
    Vec v2;
    float f3;
    int tooSmall;

    lbvector_diff(b, a, &v1);
    f3 = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
    lbvector_diff(c, a, &v2);
    if (f3 < 9.9999997473787516e-06f && f3 > -9.9999997473787516e-06f)
        tooSmall = 1;
    else
        tooSmall = 0;
    if (tooSmall)
    {
        *d = *a;
        return lbvector_len(&v2);
    }
    else
    {
        Vec v3;
        float f1 = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / f3;

        d->x = a->x + v1.x * f1;
        d->y = a->y + v1.y * f1;
        d->z = a->z + v1.z * f1;
        lbvector_diff(c, d, &v3);
        return lbvector_len(&v3);
        
    }
}
