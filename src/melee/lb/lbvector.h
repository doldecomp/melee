#ifndef _lbvector_h_
#define _lbvector_h_

#include <dolphin/mtx/mtxtypes.h>
#include <dolphin/gx/GXTransform.h>

#include "sysdolphin/baselib/cobj.h"

extern inline float sqrtf_accurate(float x);

static float lbvector_len(Vec *vec);
static float lbvector_len_xy(Vec *vec);

float lbvector_normalize(Vec *vec);
float lbvector_normalize_xy(Vec *a);
Vec *lbvector_add(Vec *a, Vec *b);
Vec *lbvector_add_xy(Vec *a, Vec *b);
Vec *lbvector_sub(Vec *a, Vec *b);
Vec *lbvector_diff(Vec *a, Vec *b, Vec *result);
Vec *lbvector_crossprod_normalized(Vec *a, Vec *b, Vec *c);

extern float func_80022D1C(float);

float func_8000D620(Vec *a, Vec *b);
float func_8000D790(Vec *a, Vec *b);

static float sin(float angle);
static float cos(float angle);

void func_8000D8F4(Vec *a, Vec *b, float angle);
void lbvector_rotate(Vec *v, int axis, float angle);

float dummy(void);
void func_8000DC6C(Vec *a, Vec *b);
float func_8000DCA8(Vec *a, Vec *b);
Vec *func_8000DDAC(Vec *a, Vec *b, Vec *result, float scale);
Vec *func_8000DE38(Mtx m, Vec *v, float c);

extern float func_80022DBC(float);
extern float func_80022C30(float, float);

Vec *func_8000DF0C(Vec *a, Vec *b, Vec *c, Vec *d);
Vec *func_8000DFF4(Vec *a, Vec *b, Vec *c);
Vec *func_8000E138(Vec *v, Vec *rot);
float func_8000E19C(float n);

extern MtxPtr func_80369688(HSD_CObj *);

Vec *func_8000E210(HSD_CObj *cobj, const Point3d *pos3d, Point3d *screenCoords, int d);
void func_8000E530(Mtx m, Vec *v);
float func_8000E838(Vec *a, Vec *b, Vec *c, Vec *d);


#endif
