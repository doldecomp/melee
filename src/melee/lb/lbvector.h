#ifndef _lbvector_h_
#define _lbvector_h_

#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/gx/GXTransform.h>

#include "sysdolphin/baselib/cobj.h"

extern inline float sqrtf_accurate(float x);

static float lbvector_Len(Vec *vec);
static float lbvector_Len_xy(Vec *vec);

float lbvector_Normalize(Vec *vec);
float lbvector_NormalizeXY(Vec *a);
Vec *lbvector_Add(Vec *a, Vec *b);
Vec *lbvector_Add_xy(Vec *a, Vec *b);
Vec *lbvector_Sub(Vec *a, Vec *b);
Vec *lbvector_Diff(Vec *a, Vec *b, Vec *result);
Vec *lbvector_CrossprodNormalized(Vec *a, Vec *b, Vec *result);

extern float func_80022D1C(float);

float lbvector_Angle(Vec *a, Vec *b);
float lbvector_AngleXY(Vec *a, Vec *b);

static float sin(float angle);
static float cos(float angle);

void lbvector_RotateAboutUnitAxis(Vec *v, Vec *axis, float angle);
void lbvector_Rotate(Vec *v, int axis, float angle);

float dummy(void);
void lbvector_Mirror(Vec *a, Vec *b);
float lbvector_CosAngle(Vec *a, Vec *b);
Vec *lbvector_Lerp(Vec *a, Vec *b, Vec *result, float f);
Vec *func_8000DE38(Mtx m, Vec *v, float c);

extern float func_80022DBC(float);
extern float func_80022C30(float, float);

Vec *lbvector_EulerAnglesFromONB(Vec *result_angles, Vec *a, Vec *b, Vec *c);
Vec *lbvector_EulerAnglesFromPartialONB(Vec *result_angles, Vec *a, Vec *c);
Vec *lbvector_ApplyEulerRotation(Vec *v, Vec *angles);
float lbvector_sqrtf_accurate(float x);

extern MtxPtr func_80369688(HSD_CObj *);

Vec *lbvector_WorldToScreen(HSD_CObj *cobj, const Point3d *pos3d, Point3d *screenCoords, int d);
void lbvector_CreateEulerMatrix(Mtx m, Vec *angles);
float lbvector_8000E838(Vec *a, Vec *b, Vec *c, Vec *d);


#endif
