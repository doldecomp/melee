#ifndef GALE01_00D2EC
#define GALE01_00D2EC

#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include <MetroTRK/intrinsics.h>

static float lbVector_Len(Vec3* vec);
static float lbVector_Len_xy(Vec3* vec);

float lbVector_Normalize(Vec3* vec);
float lbVector_NormalizeXY(Vec3* a);
Vec3* lbVector_Add(Vec3* a, Vec3* b);
Vec3* lbVector_Add_xy(Vec3* a, Vec3* b);
Vec3* lbVector_Sub(Vec3* a, Vec3* b);
Vec3* lbVector_Diff(Vec3* a, Vec3* b, Vec3* result);
Vec3* lbVector_CrossprodNormalized(Vec3* a, Vec3* b, Vec3* result);

float lbVector_Angle(Vec3* a, Vec3* b);
float lbVector_AngleXY(Vec3* a, Vec3* b);

static float sin(float angle);
static float cos(float angle);

void lbVector_RotateAboutUnitAxis(Vec3* v, Vec3* axis, float angle);
void lbVector_Rotate(Vec3* v, int axis, float angle);

float dummy(void);
void lbVector_Mirror(Vec3* a, Vec3* b);
float lbVector_CosAngle(Vec3* a, Vec3* b);
Vec3* lbVector_Lerp(Vec3* a, Vec3* b, Vec3* result, float f);
Vec3* lbVector_8000DE38(Mtx m, Vec3* v, float c);

Vec3* lbVector_EulerAnglesFromONB(Vec3* result_angles, Vec3* a, Vec3* b,
                                  Vec3* c);
Vec3* lbVector_EulerAnglesFromPartialONB(Vec3* result_angles, Vec3* a,
                                         Vec3* c);
Vec3* lbVector_ApplyEulerRotation(Vec3* v, Vec3* angles);
float lbVector_sqrtf_accurate(float x);

Vec3* lbVector_WorldToScreen(HSD_CObj* cobj, const Vec3* pos3d,
                             Vec3* screenCoords, int d);
void lbVector_CreateEulerMatrix(Mtx m, Vec3* angles);
float lbVector_8000E838(Vec3* a, Vec3* b, Vec3* c, Vec3* d);

/// @todo Doesn't belong here.
/// Exactly the same as the one from math.h, but with one extra iteration
static inline float sqrtf_accurate(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess =
            0.5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        guess = 0.5 * guess * (3.0 - guess * guess * x); // extra iteration
        y = (float) (x * guess);
        return y;
    }
    return x;
}

#endif
