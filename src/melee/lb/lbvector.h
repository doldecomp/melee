#ifndef _lbvector_h_
#define _lbvector_h_

#include <dolphin/gx/GXTransform.h>
#include <dolphin/mtx/types.h>
#include <melee/lb/lbrefract.h>

#include <sysdolphin/baselib/cobj.h>

extern inline float sqrtf_accurate(float x);

static float lbvector_Len(Vec3* vec);
static float lbvector_Len_xy(Vec3* vec);

float lbvector_Normalize(Vec3* vec);
float lbvector_NormalizeXY(Vec3* a);
Vec3* lbvector_Add(Vec3* a, Vec3* b);
Vec3* lbvector_Add_xy(Vec3* a, Vec3* b);
Vec3* lbvector_Sub(Vec3* a, Vec3* b);
Vec3* lbvector_Diff(Vec3* a, Vec3* b, Vec3* result);
Vec3* lbvector_CrossprodNormalized(Vec3* a, Vec3* b, Vec3* result);

float lbvector_Angle(Vec3* a, Vec3* b);
float lbvector_AngleXY(Vec3* a, Vec3* b);

static float sin(float angle);
static float cos(float angle);

void lbvector_RotateAboutUnitAxis(Vec3* v, Vec3* axis, float angle);
void lbvector_Rotate(Vec3* v, int axis, float angle);

float dummy(void);
void lbvector_Mirror(Vec3* a, Vec3* b);
float lbvector_CosAngle(Vec3* a, Vec3* b);
Vec3* lbvector_Lerp(Vec3* a, Vec3* b, Vec3* result, float f);
Vec3* func_8000DE38(Mtx m, Vec3* v, float c);

Vec3* lbvector_EulerAnglesFromONB(Vec3* result_angles, Vec3* a, Vec3* b,
                                  Vec3* c);
Vec3* lbvector_EulerAnglesFromPartialONB(Vec3* result_angles, Vec3* a, Vec3* c);
Vec3* lbvector_ApplyEulerRotation(Vec3* v, Vec3* angles);
float lbvector_sqrtf_accurate(float x);

extern MtxPtr func_80369688(HSD_CObj*);

Vec3* lbvector_WorldToScreen(HSD_CObj* cobj, const Vec3* pos3d,
                             Vec3* screenCoords, int d);
void lbvector_CreateEulerMatrix(Mtx m, Vec3* angles);
float lbvector_8000E838(Vec3* a, Vec3* b, Vec3* c, Vec3* d);

#endif
