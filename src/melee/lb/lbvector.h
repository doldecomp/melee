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

float lbvecttor_angle(Vec *a, Vec *b);
float lbvector_angle_xy(Vec *a, Vec *b);

static float sin(float angle);
static float cos(float angle);

void lbvector_rotate_about_unit_axis(Vec *v, Vec *axis, float angle);
void lbvector_rotate(Vec *v, int axis, float angle);

float dummy(void);
void lbvector_mirror(Vec *a, Vec *b);
float lbvector_cos_angle(Vec *a, Vec *b);
Vec *lbvector_lerp(Vec *a, Vec *b, Vec *result, float scale);
Vec *func_8000DE38(Mtx m, Vec *v, float c);

extern float func_80022DBC(float);
extern float func_80022C30(float, float);

Vec *lbvector_euler_angles_from_onb(Vec *result_angles, Vec *a, Vec *b, Vec *c);
Vec *lbvector_euler_angles_from_implicit_onb(Vec *result_angles, Vec *a, Vec *c);
Vec *lbvector_apply_euler_rotation(Vec *v, Vec *angles);
float lbvector_sqrtf_accurate(float x);

extern MtxPtr func_80369688(HSD_CObj *);

Vec *lbvector_project_world_to_screen_coord(HSD_CObj *cobj, const Point3d *pos3d, Point3d *screenCoords, int d);
void lbvector_create_euler_matrix(Mtx m, Vec *angles);
float lbvector_some_camera_vector_computation(Vec *a, Vec *b, Vec *c, Vec *d);


#endif
