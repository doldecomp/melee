#include "lbvector.h"
#include <math.h>

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
        return y;
    }
    return x;
}

static float lbvector_Len(Vec *vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

static float lbvector_Len_xy(Vec *vec)
{
    return sqrtf_accurate(vec->x * vec->x + vec->y * vec->y);
}

float lbvector_Normalize(Vec *vec)
{
    float len = lbvector_Len(vec);
    float inv;

    if (len == 0.0f)
        return 0.0f;
    inv = 1.0f / len;
    vec->x *= inv;
    vec->y *= inv;
    vec->z *= inv;
    return len;
}

float lbvector_NormalizeXY(Vec *a)
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

Vec *lbvector_Add(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
    return a;
}

Vec *lbvector_Add_xy(Vec *a, Vec *b)
{
    a->x += b->x;
    a->y += b->y;
    return a;
}

Vec *lbvector_Sub(Vec *a, Vec *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
    return a;
}

Vec *lbvector_Diff(Vec *a, Vec *b, Vec *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
    return result;
}

Vec *lbvector_CrossprodNormalized(Vec *a, Vec *b, Vec *result)
{
    PSVECCrossProduct(a, b, result);
    lbvector_Normalize(result);
    return result;
}

extern float func_80022D1C(float); // acos

// 8000D620 - returns the angle between a and b
float lbvector_Angle(Vec *a, Vec *b)
{
    float lena_lenb = lbvector_Len(a) * lbvector_Len(b);

    if (lena_lenb > 0.0000000001f)
    {
        float cosine = (a->x * b->x + a->y * b->y + a->z * b->z) / lena_lenb;
        if (cosine > 1.0f)
            cosine = 1.0f;
        if (cosine < -1.0f)
            cosine = -1.0f;

        return func_80022D1C(cosine); // acos
    }
    return 0.0f;
}

// 8000D790 - returns the angle between a and b
float lbvector_AngleXY(Vec* a, Vec* b)
{
    float lena_lenb = lbvector_Len_xy(a) * lbvector_Len_xy(b);

    if (lena_lenb)
    {
        float cosine = (a->x * b->x + a->y * b->y) / lena_lenb;
        if (cosine > 1.0f)
            cosine = 1.0f;
        if (cosine < -1.0f)
            cosine = -1.0f;
        return func_80022D1C(cosine); // acos
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

// 8000D8F4
// Rotates v by angle about the given axis. The axis must have unit length, the angle is in radians.
// Rotation is oriented such that rotating (1,0,0) about the (0,0,1) axis results in (0,1,0).
void lbvector_RotateAboutUnitAxis(Vec *v, Vec *axis, float angle)
{
    // The implementation is unnecessarily complex. the idea is to reduce the problem to the
    // case where the rotation axis is pointing along the z-axis by using two initial rotations,
    // then the new v is rotated about the z-axis by angle, and finally the first two rotations
    // are reversed.

    float len_axis_yz = sqrtf(axis->y * axis->y + axis->z * axis->z);
    float s = sin(angle);
    float c = cos(angle);
    float unit_axis_yz_y;
    float unit_axis_yz_z;
    float x, y, z;
    float x2, z2;
    float x3, y3;

    // rotation (1) about the x-axis: rotate everything such that the rotation axis lies in the xz-plane.
    // new v is then (x,y,z), new rotation axis is (b.x, 0, len_axis_yz)
    if (len_axis_yz > 0.0000000001f)
    {
        unit_axis_yz_y = axis->z / len_axis_yz;
        unit_axis_yz_z = axis->y / len_axis_yz;

        x = v->x;
        y = v->y * unit_axis_yz_y - v->z * unit_axis_yz_z;
        z = v->y * unit_axis_yz_z + v->z * unit_axis_yz_y;
    }
    else
    {
        x = v->x;
        y = v->y;
        z = v->z;
    }

    // rotation (2) about the y-axis: rotate everything such that the rotation axis aligns with the z-axis
    // new v is then (x2,y2,z2)
    x2 = x * len_axis_yz  -  z * axis->x;
    // y2 = y
    z2 = x * axis->x  +  z * len_axis_yz;

    // rotate by 'angle' about the z axis, which now aligns with the rotation axis
    x3 = x2 * c  -  y * s; // remember that y2=y
    y3 = x2 * s  +  y * c;
    // z3 = z2

    // opposite of rotation (2). We overwrite (x,y,z) with the resulting new v.
    x = x3 * len_axis_yz  +  z2 * axis->x; // remember that z3=z2
    y = y3;
    z = -x3 * axis->x  +  z2 * len_axis_yz;

    // opposite of rotation (1)
    if (len_axis_yz > 0.0000000001f)
    {
        v->x = x;
        v->y = y * unit_axis_yz_y + z * unit_axis_yz_z;
        v->z = -y * unit_axis_yz_z + z * unit_axis_yz_y;
    }
    else
    {
        v->x = x;
        v->y = y;
        v->z = z;
    }
}

void lbvector_Rotate(Vec *v, int axis, float angle)
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

// 8000DC6C - compute a -= 2*<a,b>*b. When b has unit length, this mirrors a at the plane that is perpendicular to b and contains the origin.
void lbvector_Mirror(Vec *a, Vec *unit_mirror_axis)
{
    float f = (unit_mirror_axis->x * a->x + unit_mirror_axis->y * a->y) * -2.0f;

    a->x += unit_mirror_axis->x * f;
    a->y += unit_mirror_axis->y * f;
}

// 8000DCA8 - returns <a/|a|, b/|b|>, which is the cosine of the angle between a and b.
float lbvector_CosAngle(Vec *a, Vec *b)
{
    return (a->x*b->x + a->y*b->y)
         / (sqrtf(a->x*a->x + a->y*a->y) * sqrtf(b->x*b->x + b->y*b->y));
}


// 8000DDAC - linearly interpolates between a and b as f goes from 0 to 1, returns a + f*(b-a).
// The numerical error can be large for f=1 when b is small compared to a.
Vec *lbvector_Lerp(Vec *a, Vec *b, Vec *result, float f)
{
    lbvector_Diff(b, a, result);
    result->x *= f;
    result->y *= f;
    result->z *= f;
    lbvector_Add(result, a);
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

extern float func_80022DBC(float); // asin
extern float func_80022C30(float, float); // atan2


// 8000DF0C - computes euler angles phi_x,phi_y,phi_z that rotate the standard basis (e1,e2,e3) onto the orthonormal basis (b,c,a)
// with 3 rotations about the x,y,z axes in that order.
Vec *lbvector_EulerAnglesFromONB(Vec *result_angles, Vec *a, Vec *b, Vec *c)
{
    if (b->z == -1.0f || b->z == 1.0f)
    {
        if (b->z == -1.0f)
        {
            result_angles->y = 1.5707963705062866f; // pi/2
            result_angles->x = func_80022C30(c->x, c->y); // atan2
        }
        else
        {
            result_angles->y = -1.5707963705062866f; // -pi/2
            result_angles->x = func_80022C30(-c->x, c->y); // atan2
        }
        result_angles->z = 0.0f;
    }
    else
    {
        result_angles->y = func_80022DBC(-b->z); // asin
        result_angles->x = func_80022C30(c->z, a->z); // atan2
        result_angles->z = func_80022C30(b->y, b->x); // atan2
    }
    return result_angles;
}

// 8000DFF4 - returns lbvector_EulerAnglesFromONB(result_angles, a, c cross a, c).
// When rotating about the x,y,z angles about the euler angles returned from that function
// in that order, the standard basis (e1,e2,e3) is rotated onto (c cross a,c,a).
Vec *lbvector_EulerAnglesFromPartialONB(Vec *result_angles, Vec *a, Vec *c)
{
    Vec b;

    PSVECCrossProduct(c, a, &b);
    lbvector_Normalize(&b);
    lbvector_EulerAnglesFromONB(result_angles, a, &b, c);
    return result_angles;
}

// 8000E138
Vec *lbvector_ApplyEulerRotation(Vec *v, Vec *angles)
{
    lbvector_Rotate(v, 1, angles->x); // rotate about x-axis
    lbvector_Rotate(v, 2, angles->y); // rotate about y-axis
    lbvector_Rotate(v, 4, angles->z); // rotate about z-axis
    return v;
}

// 8000E19C
float lbvector_sqrtf_accurate(float x)
{
    return sqrtf_accurate(x);
}

#define assert_line(condition, line) ((condition) ? ((void) 0) : __assert(__FILE__, line, #condition))

extern MtxPtr func_80369688(HSD_CObj *);


// 8000E210
Vec *lbvector_WorldToScreen(HSD_CObj *cobj, const Point3d *pos3d, Point3d *screenCoords, int d)
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
    switch (HSD_CObjGetProjectionType(cobj))
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
        func_80368784(cobj, &camPos); // HSD_CObjGetEyePosition
        func_80368E70(cobj, &upVec);  // HSD_CObjGetUpVector
        func_803686AC(cobj, &target); // HSD_CObjGetInterest
        C_MTXLookAt(m, &camPos, &upVec, &target);
        mvMtx = m;
    }
    else
        mvMtx = func_80369688(cobj); // HSD_CObjSetupViewingMtx

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

// 8000E530 - Sets m to the 3x3 euler matrix that rotates about the x,y,z axes
// with angles angles.x, angles.y, angles.z in that order, that means
// m = rotation_matrix_z(angles.z) * rotation_matrix_y(angles.y) * rotation_matrix_x(angles.x)
// Column 4 of m is then set to (0,0,0) because there is no translational component.
void lbvector_CreateEulerMatrix(Mtx m, Vec *angles)
{
    float sx = sin(angles->x);
    float cx = cos(angles->x);
    float sy = sin(angles->y);
    float cy = cos(angles->y);
    float sz = sin(angles->z);
    float cz = cos(angles->z);

    float sxsy = sx * sy;
    float cxsy = cx * sy;

	// column 1
    m[0][0] = cy * cz;
    m[1][0] = cy * sz;
    m[2][0] = -sy;

	// column 2
    m[0][1] = cz * sxsy - cx * sz;
    m[1][1] = sz * sxsy + cx * cz;
    m[2][1] = sx * cy;

	// column 3
    m[0][2] = cz * cxsy + sx * sz;
    m[1][2] = sz * cxsy - sx * cz;
    m[2][2] = cx * cy;

	// column 4 - no translational component
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}


// 8000E838 - This function seems to have a very specific use case and is only used once
// in Camera_CheckToStopDrawingHighPoly(80030cfc), here's what it does:
// Let u = b-a, then compute the intersection of the line through a with direction u
// with the plane that contains c and is perpendicular to u. Write the result to d.
// If u is numerically too small, set d=a instead. Return the length of c-d.
float lbvector_8000E838(Vec *a, Vec *b, Vec *c, Vec *d)
{
    Vec b_a;
    Vec c_a;
    float sqrlen_b_a;
    int tooSmall;

    lbvector_Diff(b, a, &b_a);
    sqrlen_b_a = b_a.x * b_a.x + b_a.y * b_a.y + b_a.z * b_a.z;
    lbvector_Diff(c, a, &c_a);
    if (sqrlen_b_a < 9.9999997473787516e-06f && sqrlen_b_a > -9.9999997473787516e-06f)
        tooSmall = 1;
    else
        tooSmall = 0;
    if (tooSmall)
    {
        *d = *a;
        return lbvector_Len(&c_a);
    }
    else
    {
        Vec v3;
        float f1 = (b_a.x * c_a.x + b_a.y * c_a.y + b_a.z * c_a.z) / sqrlen_b_a;

        d->x = a->x + b_a.x * f1;
        d->y = a->y + b_a.y * f1;
        d->z = a->z + b_a.z * f1;
        lbvector_Diff(c, d, &v3);
        return lbvector_Len(&v3);
        
    }
}
