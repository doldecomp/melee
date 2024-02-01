#include <dolphin/gx/forward.h>

#include "cobj.h"

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "initialize.h"
#include "mtx.h"
#include "video.h"
#include "wobj.h"

#include <math.h>
#include <placeholder.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/vi/vi.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/trigf.h>

static HSD_ClassInfo* default_class;
static HSD_CObj* current;

#define DegToRad(a) ((a) * 0.01745329252F)

static int CObjInit(HSD_Class* o);
static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* cobjdesc);
static void CObjInfoInit(void);
static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
static void CObjRelease(HSD_Class* o);
static void CObjAmnesia(HSD_ClassInfo* info);

void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha,
                         s32 enable_depth)
{
    float m_val, z_val, left_res, right_res, top_res, bottom_res;

    if (cobj == NULL ||
        enable_color == 0 && enable_alpha == 0 && enable_depth == 0)
    {
        return;
    }

    z_val = (0.5 * (HSD_CObjGetNear(cobj) + HSD_CObjGetFar(cobj)));

    switch (HSD_CObjGetProjectionType(cobj)) {
    case PROJ_PERSPECTIVE:
        top_res =
            (z_val *
             tanf(0.5F * DegToRad(cobj->projection_param.perspective.fov)));
        bottom_res = -top_res;
        right_res = top_res * cobj->projection_param.perspective.aspect;
        left_res = -right_res;
        break;
    case PROJ_FRUSTUM:
        m_val = z_val / HSD_CObjGetNear(cobj);
        right_res = m_val * cobj->projection_param.frustum.right;
        left_res = m_val * cobj->projection_param.frustum.left;
        top_res = m_val * cobj->projection_param.frustum.top;
        bottom_res = m_val * cobj->projection_param.frustum.bottom;
        break;
    case PROJ_ORTHO:
        right_res = cobj->projection_param.ortho.right;
        left_res = cobj->projection_param.ortho.left;
        top_res = cobj->projection_param.ortho.top;
        bottom_res = cobj->projection_param.ortho.bottom;
        break;
    }

    HSD_EraseRect(top_res, bottom_res, left_res, right_res, -z_val,
                  enable_color, enable_alpha, enable_depth);
}

void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags)
{
    HSD_WObj* wobj;

    if (cobj == NULL) {
        return;
    }

    HSD_AObjRemove(cobj->aobj);
    cobj->aobj = NULL;
    wobj = HSD_CObjGetEyePositionWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
    wobj = HSD_CObjGetInterestWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
}

void HSD_CObjRemoveAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_CObjRemoveAnimByFlags(cobj, 0x7FF);
}

void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim)
{
    if (cobj == NULL) {
        return;
    }

    if (canim == NULL) {
        return;
    }

    if (cobj->aobj != NULL) {
        HSD_AObjRemove(cobj->aobj);
    }
    cobj->aobj = HSD_AObjLoadDesc(canim->aobjdesc);
    HSD_WObjAddAnim(HSD_CObjGetEyePositionWObj(cobj), canim->eye_anim);
    HSD_WObjAddAnim(HSD_CObjGetInterestWObj(cobj), canim->interest_anim);
}

HSD_CObjInfo hsdCObj = { CObjInfoInit };

typedef struct _HSD_FObjData {
    float fv;
    s32 iv;
    Vec3 p;
} FObjData;

static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_CObj* cobj = obj;
    Vec3 vec;

    if (cobj == NULL) {
        return;
    }

    switch (type) {
    case 1:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 2:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.y = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 3:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.z = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 5:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 6:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 7:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 9:
        HSD_CObjSetRoll(cobj, val->fv);
        break;
    case 10:
        HSD_CObjSetFov(cobj, val->fv);
        break;
    case 11:
        HSD_CObjSetNear(cobj, val->fv);
        break;
    case 12:
        HSD_CObjSetFar(cobj, val->fv);
        break;
    }
}

void HSD_CObjAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(cobj->aobj, cobj, CObjUpdateFunc);
    HSD_WObjInterpretAnim(cobj->eyepos);
    HSD_WObjInterpretAnim(cobj->interest);
}

void HSD_CObjReqAnim(HSD_CObj* cobj, float startframe)
{
    if (cobj == NULL) {
        return;
    }

    if (cobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(cobj->aobj, startframe);
    HSD_WObjReqAnim(cobj->eyepos, startframe);
    HSD_WObjReqAnim(cobj->interest, startframe);
}

GXProjectionType makeProjectionMtx(HSD_CObj* cobj, Mtx mtx)
{
    GXProjectionType projection_type;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        projection_type = GX_PERSPECTIVE;
        C_MTXPerspective(mtx, cobj->projection_param.perspective.fov,
                         cobj->projection_param.perspective.aspect, cobj->near,
                         cobj->far);
        break;
    case PROJ_FRUSTUM:
        projection_type = GX_PERSPECTIVE;
        C_MTXFrustum(mtx, cobj->projection_param.perspective.fov,
                     cobj->projection_param.perspective.aspect,
                     cobj->projection_param.frustum.left,
                     cobj->projection_param.frustum.right, cobj->near,
                     cobj->far);
        break;
    case PROJ_ORTHO:
        projection_type = GX_ORTHOGRAPHIC;
        C_MTXOrtho(mtx, cobj->projection_param.perspective.fov,
                   cobj->projection_param.perspective.aspect,
                   cobj->projection_param.frustum.left,
                   cobj->projection_param.frustum.right, cobj->near,
                   cobj->far);
        break;
    }
    return projection_type;
}

static const float HSD_CObj_804DE478 = 0.0F;
static const float HSD_CObj_804DE47C = 1.0F;

static bool setupOffscreenCamera(HSD_CObj* cobj)
{
    Mtx44 mtx;

    GXSetViewport(cobj->viewport.left, cobj->viewport.top,
                  cobj->viewport.right - cobj->viewport.left,
                  cobj->viewport.bottom - cobj->viewport.top, 0.0f, 1.0f);
    GXSetScissor(cobj->scissor.left, cobj->scissor.top,
                 cobj->scissor.right - cobj->scissor.left,
                 cobj->scissor.bottom - cobj->scissor.top);
    GXSetProjection(mtx, makeProjectionMtx(cobj, mtx));
    return true;
}

int setupNormalCamera(HSD_CObj* cobj)
{
    int unused[4];

    GXProjectionType projection_type;
    Mtx p;

    f32 x_scale;
    f32 y_scale;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    x_scale = (f32) rmode->fbWidth / (f32) rmode->viWidth;
    y_scale = (f32) rmode->efbHeight / (f32) rmode->viHeight;

    left = cobj->viewport.left * x_scale;
    right = cobj->viewport.right * x_scale;
    top = cobj->viewport.top * y_scale;
    bottom = cobj->viewport.bottom * y_scale;

    width = right - left;
    height = bottom - top;

    if (rmode->field_rendering) {
        GXSetViewportJitter(left, top, width, height, 0.0f, 1.0f,
                            VIGetNextField());
    } else {
        GXSetViewport(left, top, width, height, 0.0f, 1.0f);
    }

    left = cobj->scissor.left * x_scale;
    right = cobj->scissor.right * x_scale;
    top = cobj->scissor.top * y_scale;
    bottom = cobj->scissor.bottom * y_scale;
    width = right - left;
    height = bottom - top;
    GXSetScissor((u32) left, (u32) top, (u32) width, (u32) height);

    projection_type = makeProjectionMtx(cobj, p);
    GXSetProjection(p, projection_type);

    return 1;
}

int setupTopHalfCamera(HSD_CObj* cobj)
{
    int unused[3];
    GXProjectionType projection_type;
    Mtx p;

    f32 h_scale;
    f32 t;
    f32 b;
    f32 w;

    f32 top;
    f32 bottom;
    f32 left;
    f32 right;

    f32 width;
    f32 height;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    if (cobj->viewport.top >= rmode->efbHeight) {
        return 0;
    }
    left = cobj->viewport.left;
    right = cobj->viewport.right;
    top = cobj->viewport.top;
    bottom = bottom = cobj->viewport.bottom;
    bottom = bottom < rmode->efbHeight ? bottom : rmode->efbHeight;
    width = right - left;
    height = bottom - top;
    GXSetScissor((u32) left, (u32) top, (u32) width, (u32) height);
    top = cobj->viewport.top;
    bottom = cobj->viewport.bottom;
    left = cobj->viewport.left;
    right = cobj->viewport.right;
    height = (bottom < rmode->efbHeight ? bottom : rmode->efbHeight) - top;
    h_scale = height / (bottom - top);
    width = right - left;

    GXSetViewport(left, top, width, height, 0.0f, 1.0f);

    {
        int unused_2[1];

        switch (cobj->projection_type) {
        case PROJ_PERSPECTIVE:
            projection_type = GX_PERSPECTIVE;
            t = cobj->near *
                tanf(0.01745329238474369 *
                     (0.5 * cobj->projection_param.perspective.fov));
            w = t * cobj->projection_param.perspective.aspect;
            b = t * -(2.0f * h_scale - 1.0f);
            C_MTXFrustum(p, t, b, -w, w, cobj->near, cobj->far);
            break;
        case PROJ_FRUSTUM:
            projection_type = GX_PERSPECTIVE;
            C_MTXFrustum(
                p, cobj->projection_param.perspective.fov,
                -(h_scale * (cobj->projection_param.perspective.fov -
                             cobj->projection_param.perspective.aspect) -
                  cobj->projection_param.perspective.fov),
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        case PROJ_ORTHO:
            projection_type = GX_ORTHOGRAPHIC;
            C_MTXOrtho(
                p, cobj->projection_param.perspective.fov,
                -(h_scale * (cobj->projection_param.perspective.fov -
                             cobj->projection_param.perspective.aspect) -
                  cobj->projection_param.perspective.fov),
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        }
    }

    GXSetProjection(p, projection_type);

    return 1;
}

int setupBottomHalfCamera(HSD_CObj* cobj)
{
#ifdef MUST_MATCH
    int unused[4];
#endif

    GXProjectionType projection_type;
    Mtx p;

    f32 top, abs_top, margin, bottom, left, right, width, height, h_scale, t,
        b, w, h;
    u32 screen_top;

    GXRenderModeObj* rmode = HSD_VIGetRenderMode();

    screen_top = rmode->efbHeight - 8;

    if (cobj->viewport.bottom < screen_top) {
        return 0;
    }

    left = cobj->scissor.left;
    right = cobj->scissor.right;
    top = (cobj->scissor.top > screen_top ? cobj->scissor.top : screen_top) -
          screen_top;
    bottom = cobj->scissor.bottom - screen_top;
    width = right - left;
    height = bottom - top;
    GXSetScissor((u32) left, (u32) top, (u32) width, (u32) height);

    top = cobj->viewport.top;
    left = cobj->viewport.left;
    right = cobj->viewport.right;

    if (top > screen_top) {
        abs_top = top;
    } else {
        abs_top = screen_top;
    }
    bottom = cobj->viewport.bottom;
    width = right - left;
    height = bottom - top;

    margin = abs_top - screen_top;
    h = bottom - screen_top - abs_top;
    h_scale = h / (height - margin);

    GXSetViewport(left, abs_top, width, h, 0.0f, 1.0f);

    {
        switch (cobj->projection_type) {
        case PROJ_PERSPECTIVE:
            projection_type = GX_PERSPECTIVE;
            b = cobj->near *
                tanf(0.01745329238474369 *
                     (0.5 * cobj->projection_param.perspective.fov));
            w = b * cobj->projection_param.perspective.aspect;
            t = b * (2.0f * h_scale + 1.0f);
            C_MTXFrustum(p, t, -b, -w, w, cobj->near, cobj->far);
            break;
        case PROJ_FRUSTUM:
            projection_type = GX_PERSPECTIVE;
            C_MTXFrustum(
                p,
                (h_scale * (cobj->projection_param.perspective.fov -
                            cobj->projection_param.perspective.aspect) +
                 cobj->projection_param.perspective.aspect),
                cobj->projection_param.perspective.aspect,
                cobj->projection_param.frustum.left,
                cobj->projection_param.frustum.right, cobj->near, cobj->far);
            break;
        case PROJ_ORTHO:
            projection_type = GX_ORTHOGRAPHIC;
            C_MTXOrtho(p,
                       (h_scale * (cobj->projection_param.perspective.fov -
                                   cobj->projection_param.perspective.aspect) +
                        cobj->projection_param.perspective.aspect),
                       cobj->projection_param.perspective.aspect,
                       cobj->projection_param.frustum.left,
                       cobj->projection_param.frustum.right, cobj->near,
                       cobj->far);
            break;
        }
    }

    GXSetProjection(p, projection_type);

    return 1;
}

inline void HSD_WObjClearFlags(HSD_WObj* wobj, u32 flags)
{
    wobj->flags &= ~flags;
}

void HSD_CObjSetupViewingMtx(HSD_CObj* cobj)
{
    Vec3 eyepos;
    Vec3 up_vec;
    Vec3 interest;

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
}

static char HSD_CObj_804D5D40[7] = "cobj.c";
static char HSD_CObj_80406294[] = "unkown type of render pass.\n";

static void setNewProjection(HSD_CObj* cobj, Mtx44 mtx)
{
    GXSetProjection(mtx, makeProjectionMtx(cobj, mtx));
}

bool HSD_CObjSetCurrent(HSD_CObj* cobj)
{
    HSD_RenderPass render_pass;
    bool result;

    if (cobj == NULL) {
        return false;
    }
    render_pass = HSD_GetCurrentRenderPass();
    _HSD_ZListClear();
    current = cobj;
    switch (render_pass) {
    case HSD_RP_OFFSCREEN:
        result = setupOffscreenCamera(cobj);
        break;
    case HSD_RP_SCREEN:
        result = setupNormalCamera(cobj);
        break;
    case HSD_RP_TOPHALF:
        result = setupTopHalfCamera(cobj);
        break;
    case HSD_RP_BOTTOMHALF:
        result = setupBottomHalfCamera(cobj);
        break;
    default:
        HSD_Panic(HSD_CObj_804D5D40,
                  //"cobj.c",
                  0x270, HSD_CObj_80406294);
        //"unkown type of render pass.\n");
        return false;
    }
    if (!result) {
        return false;
    } else {
        HSD_CObjSetupViewingMtx(cobj);
        return true;
    }
}

void HSD_CObjEndCurrent(void)
{
    _HSD_ZListSort();
    _HSD_ZListDisp();
}

#define HSD_ASSERT3(line, msg, cond)                                          \
    ((cond) ? (void) 0 : __assert(HSD_CObj_804D5D40, line, msg))

#define HSD_ASSERT4(line, cond)                                               \
    ((cond) ? (void) 0 : __assert(HSD_CObj_804D5D40, line, #cond))

char HSD_CObj_804D5D48[8] = "cobj";

HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    HSD_ASSERT3(0x295, HSD_CObj_804D5D48, cobj);
    return cobj->interest;
}

HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    HSD_ASSERT3(0x2AD, HSD_CObj_804D5D48, cobj);
    return cobj->eyepos;
}

void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT3(0x2C5, HSD_CObj_804D5D48, cobj);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT3(0x2D1, HSD_CObj_804D5D48, cobj);
    HSD_WObjSetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT3(0x2DD, HSD_CObj_804D5D48, cobj);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT3(0x2E9, HSD_CObj_804D5D48, cobj);
    HSD_WObjSetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

static inline float fabsf(float x)
{
    *(u32*) &x &= 0x7FFFFFFF;
    return x;
}

#define FLT_MIN 2.848094538889218e-306f

static inline int _vec_normalize_check(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (fabsf(src->x) <= FLT_MIN && fabsf(src->y) <= FLT_MIN &&
        fabsf(src->z) <= FLT_MIN)
    {
        return -1;
    } else {
        PSVECNormalize(src, dst);
        return 0;
    }
}

int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye)
{
    Vec3 sp48;
    Vec3 sp3C;

    if (cobj != NULL && cobj->eyepos != NULL && cobj->interest != NULL &&
        eye != NULL)
    {
        HSD_CObjGetEyePosition(cobj, &sp48);
        HSD_CObjGetInterest(cobj, &sp3C);
        PSVECSubtract(&sp3C, &sp48, eye);
        if (_vec_normalize_check(eye, eye) == 0) {
            return 0;
        }
    }
    if (eye != NULL) {
        eye->y = eye->x = 0.0f;
        eye->z = -1.0f;
    }
    return -1;
}

float HSD_CObjGetEyeDistance(HSD_CObj* cobj)
{
    Vec3 position;
    Vec3 interest;
    Vec3 look_vector;

    if (cobj == NULL) {
        return 0.0f;
    }
    HSD_ASSERT4(0x327, cobj->eyepos);
    HSD_ASSERT4(0x328, cobj->interest);
    HSD_CObjGetEyePosition(cobj, &position);
    HSD_CObjGetInterest(cobj, &interest);
    PSVECSubtract(&interest, &position, &look_vector);
    return PSVECMag(&look_vector);
}

#ifndef BUGFIX
#pragma push
#pragma force_active on
static float unused1[] = {
    0.0F, 0.0F, 0.0F,

    0.0F, 1.0F, 0.0F,

    0.0F, 1.0F, 0.0F,
};

static char unused2[] = "hsdIsDescendantOf(info, &hsdCObj)";
#pragma pop
#endif

int vec_normalize_check(Vec3* src, Vec3* dst)
{
    return _vec_normalize_check(src, dst);
}

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll);

extern const f64 HSD_CObj_804DE4B0;
extern const f64 HSD_CObj_804DE4B8;
extern const f64 HSD_CObj_804DE4C0;

int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{
    Vec3 eye;
    Vec3 v0;
    Vec3 v1;
    Mtx m;

    if (HSD_CObjGetEyeVector(cobj, &eye) != 0) {
        return 1;
    }

    if (1.0 - __fabs(eye.y) < 0.0001) {
        v0.x = sqrtf(eye.y * eye.y + eye.z * eye.z);
        v0.y = eye.y * (-eye.x / v0.x);
        v0.z = eye.z * (-eye.x / v0.x);
    } else {
        v0.y = sqrtf(eye.x * eye.x + eye.z * eye.z);
        v0.x = eye.x * (-eye.y / v0.y);
        v0.z = eye.z * (-eye.y / v0.y);
    }
    PSMTXRotAxisRad(m, &eye, -roll);
    PSMTXMultVecSR(m, &v0, &v1);
    PSVECNormalize(&v1, up);
    return 0;
}

void HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjGetLeftVector(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void HSD_CObjSetMtxDirty(HSD_CObj* cobj)
{
    cobj->flags |= (1 << 30) | (1 << 31);
}

bool HSD_CObjMtxIsDirty(HSD_CObj* cobj)
{
    return (cobj->flags & (1 << 30)) ||
           (cobj->eyepos != NULL && (cobj->eyepos->flags & 2)) ||
           (cobj->interest != NULL && (cobj->interest->flags & 2));
}

void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx)
{
    PSMTXCopy(HSD_CObjGetViewingMtxPtr(cobj), mtx);
}

MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj)
{
    if (cobj->flags & (1 << 31)) {
        if (cobj->proj_mtx == NULL) {
            cobj->proj_mtx = HSD_MtxAlloc();
        }
        PSMTXInverse(cobj->view_mtx, *cobj->proj_mtx);
        HSD_CObjClearFlags(cobj, (1 << 31));
    }
    return *cobj->proj_mtx;
}

#define SOLUTION 1
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj)
{
#if SOLUTION == 0
    HSD_CObjSetupViewingMtx(cobj);
#elif SOLUTION == 1
    Vec3 interest;
    Vec3 up_vec;
    Vec3 eyepos;
    u32 unused[6];

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
#endif
    HSD_CObjSetupViewingMtx(cobj);
    return HSD_CObjGetViewingMtxPtrDirect(cobj);
}
#undef SOLUTION

#define SOLUTION 1
MtxPtr HSD_CObjGetInvViewingMtxPtr(HSD_CObj* cobj)
{
#if SOLUTION == 0
    HSD_CObjGetViewingMtxPtr(cobj);
#elif SOLUTION == 1
    Vec3 interest;
    Vec3 up_vec;
    Vec3 eyepos;
    u32 unused[6];

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        HSD_CObjGetUpVector(cobj, &up_vec);
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
    return HSD_CObjGetInvViewingMtxPtrDirect(cobj);
#endif
}
#undef SOLUTION

void HSD_CObjSetRoll(HSD_CObj* cobj, float arg1)
{
    NOT_IMPLEMENTED;
}

float HSD_CObjGetFov(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return 0.0f;
    }
    return cobj->projection_param.perspective.fov;
}

void HSD_CObjSetFov(HSD_CObj* cobj, float fov)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.fov = fov;
}

float HSD_CObjGetAspect(HSD_CObj* cobj)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return 0.0f;
    }
    return cobj->projection_param.perspective.aspect;
}

void HSD_CObjSetAspect(HSD_CObj* cobj, float aspect)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    cobj->projection_param.perspective.aspect = aspect;
}

float HSD_CObjGetTop(HSD_CObj* cobj)
{
    float result;

    if (cobj == NULL) {
        return 0.0f;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        result =
            cobj->near * tanf(0.5F * (0.01745329252F *
                                      cobj->projection_param.perspective.fov));
        break;
    case PROJ_FRUSTUM:
        result = cobj->projection_param.perspective.fov;
        break;
    case PROJ_ORTHO:
        result = cobj->projection_param.perspective.fov;
        break;
    default:
        result = 0.0f;
        break;
    }
    return result;
}

void HSD_CObjSetTop(HSD_CObj* cobj, float top)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.top = top;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.top = top;
        break;
    }
}

float HSD_CObjGetBottom(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return -cobj->near *
               tanf(0.5F *
                    (0.01745329252F * cobj->projection_param.perspective.fov));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.bottom;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.bottom;
    default:
        return 0.0f;
    }
}

void HSD_CObjSetBottom(HSD_CObj* cobj, float bottom)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.bottom = bottom;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.bottom = bottom;
        break;
    }
}

float HSD_CObjGetLeft(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return cobj->projection_param.perspective.aspect *
               (-cobj->near *
                tanf(0.5F * (0.01745329252F *
                             cobj->projection_param.perspective.fov)));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.left;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.left;
    default:
        return 0.0f;
    }
}

void HSD_CObjSetLeft(HSD_CObj* cobj, float left)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.left = left;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.left = left;
        break;
    }
}

float HSD_CObjGetRight(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        return cobj->projection_param.perspective.aspect *
               (cobj->near *
                tanf(0.5F * (0.01745329252F *
                             cobj->projection_param.perspective.fov)));
    case PROJ_FRUSTUM:
        return cobj->projection_param.frustum.right;
    case PROJ_ORTHO:
        return cobj->projection_param.ortho.right;
    default:
        return 0.0f;
    }
}

void HSD_CObjSetRight(HSD_CObj* cobj, float right)
{
    if (cobj == NULL) {
        return;
    }
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        break;
    case PROJ_FRUSTUM:
        cobj->projection_param.frustum.right = right;
        break;
    case PROJ_ORTHO:
        cobj->projection_param.ortho.right = right;
        break;
    }
}

float HSD_CObjGetNear(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->near;
}

void HSD_CObjSetNear(HSD_CObj* cobj, float near)
{
    if (cobj != NULL) {
        cobj->near = near;
    }
}

float HSD_CObjGetFar(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->far;
}

void HSD_CObjSetFar(HSD_CObj* cobj, float far)
{
    if (cobj != NULL) {
        cobj->far = far;
    }
}

void HSD_CObjGetScissor(HSD_CObj* cobj, Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    *scissor = cobj->scissor;
}

void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor = *scissor;
}

void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top,
                          u16 bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->scissor.left = left;
    cobj->scissor.right = right;
    cobj->scissor.top = top;
    cobj->scissor.bottom = bottom;
}

void HSD_CObjGetViewportf(HSD_CObj* cobj, struct Viewport* viewport)
{
    if (cobj == NULL) {
        return;
    }
    *viewport = cobj->viewport;
}

extern const f64 HSD_CObj_804DE4C8;

// Uses s16 -> float cast literal
void HSD_CObjSetViewport(HSD_CObj* cobj, s16* viewport)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.left = viewport[0];
    cobj->viewport.right = viewport[1];
    cobj->viewport.top = viewport[2];
    cobj->viewport.bottom = viewport[3];
}

void HSD_CObjSetViewportf(HSD_CObj* cobj, struct Viewport* viewport)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport = *viewport;
}

void HSD_CObjSetViewportfx4(HSD_CObj* cobj, float left, float right, float top,
                            float bottom)
{
    if (cobj == NULL) {
        return;
    }
    cobj->viewport.left = left;
    cobj->viewport.right = right;
    cobj->viewport.top = top;
    cobj->viewport.bottom = bottom;
}

u32 HSD_CObjGetProjectionType(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 1;
    }
    return cobj->projection_type;
}

void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = proj_type;
}

void HSD_CObjSetPerspective(HSD_CObj* cobj, float fov, float aspect)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_PERSPECTIVE;
    cobj->projection_param.perspective.fov = fov;
    cobj->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetFrustum(HSD_CObj* cobj, float top, float bottom, float left,
                        float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_FRUSTUM;
    cobj->projection_param.frustum.top = top;
    cobj->projection_param.frustum.bottom = bottom;
    cobj->projection_param.frustum.left = left;
    cobj->projection_param.frustum.right = right;
}

void HSD_CObjSetOrtho(HSD_CObj* cobj, float top, float bottom, float left,
                      float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_ORTHO;
    cobj->projection_param.ortho.top = top;
    cobj->projection_param.ortho.bottom = bottom;
    cobj->projection_param.ortho.left = left;
    cobj->projection_param.ortho.right = right;
}

void HSD_CObjGetPerspective(HSD_CObj* cobj, float* top, float* bottom)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.perspective.fov;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.perspective.aspect;
    }
}

void HSD_CObjGetOrtho(HSD_CObj* cobj, float* top, float* bottom, float* left,
                      float* right)
{
    if (cobj == NULL || cobj->projection_type != PROJ_ORTHO) {
        return;
    }
    if (top != NULL) {
        *top = cobj->projection_param.ortho.top;
    }
    if (bottom != NULL) {
        *bottom = cobj->projection_param.ortho.bottom;
    }
    if (left != NULL) {
        *left = cobj->projection_param.ortho.left;
    }
    if (right != NULL) {
        *right = cobj->projection_param.ortho.right;
    }
}

u32 HSD_CObjGetFlags(HSD_CObj* cobj)
{
    return cobj->flags;
}

void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags |= flags;
}

void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags &= ~flags;
}

HSD_CObj* HSD_CObjGetCurrent(void)
{
    return current;
}

HSD_CObj* HSD_CObjAlloc(void)
{
    HSD_CObj* cobj = (HSD_CObj*) hsdNew(
        default_class ? default_class : &hsdCObj.parent.parent);
    HSD_ASSERT3(1954, HSD_CObj_804D5D48, cobj);
    return cobj;
}

static Vec3 HSD_CObj_8040631C = { 0, 1, 0 };
static char HSD_CObj_804D5D50[3] = "0";

static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* desc)
{
    cobj->flags = desc->flags;
    CObjResetFlags(cobj, desc->flags);
    HSD_CObjSetViewport(cobj, &desc->viewport.left);
    HSD_CObjSetScissor(cobj, &desc->scissor);
    HSD_WObjInit(cobj->eyepos, desc->eye_desc);
    HSD_WObjInit(cobj->interest, desc->interest_desc);
    HSD_CObjSetNear(cobj, desc->near);
    HSD_CObjSetFar(cobj, desc->far);
    if (desc->flags & 1) {
        if (desc->vector != NULL) {
            HSD_CObjSetUpVector(cobj, desc->vector);
        } else {
            HSD_CObjSetUpVector(cobj, &HSD_CObj_8040631C);
        }
    } else {
        HSD_CObjSetRoll(cobj, desc->roll);
    }
    switch (desc->projection_type) {
    case PROJ_PERSPECTIVE:
        HSD_CObjSetPerspective(cobj, desc->projection_param.perspective.fov,
                               desc->projection_param.perspective.aspect);
        break;
    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, desc->projection_param.ortho.top,
                         desc->projection_param.ortho.bottom,
                         desc->projection_param.ortho.left,
                         desc->projection_param.ortho.right);
        break;
    case PROJ_FRUSTUM:
        HSD_CObjSetFrustum(cobj, desc->projection_param.frustum.top,
                           desc->projection_param.frustum.bottom,
                           desc->projection_param.frustum.left,
                           desc->projection_param.frustum.right);
        break;
    default:
        __assert(HSD_CObj_804D5D40, 0x7D0, HSD_CObj_804D5D50);
        break;
    }
    return 0;
}

void HSD_CObjInit(HSD_CObj* cobj, HSD_CObjDesc* desc)
{
    if (cobj == NULL || desc == NULL) {
        return;
    }
    CObjLoad(cobj, desc);
}

HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc)
{
    HSD_ClassInfo* info;
    HSD_CObj* cobj;

    if (desc != NULL) {
        if (desc->class_name == NULL ||
            (info = hsdSearchClassInfo(desc->class_name)) == NULL)
        {
            cobj = HSD_CObjAlloc();
        } else {
            cobj = hsdNew(info);
            HSD_ASSERT3(0x7F7, HSD_CObj_804D5D48, cobj);
        }
        HSD_COBJ_METHOD(cobj)->load(cobj, desc);
        return cobj;
    }
    return NULL;
}

static int CObjInit(HSD_Class* o)
{
    HSD_CObj* cobj;
    int status = HSD_OBJECT_PARENT_INFO(&hsdCObj)->init(o);
    if (status < 0) {
        return status;
    }
    cobj = (HSD_CObj*) o;
    if (cobj != NULL) {
        HSD_CObjSetMtxDirty(cobj);
    }
    cobj->eyepos = HSD_WObjAlloc();
    cobj->interest = HSD_WObjAlloc();
    return 0;
}

void CObjRelease(HSD_Class* o)
{
    HSD_WObj* eyepos;
    HSD_WObj* interest;
    HSD_CObj* cobj = (HSD_CObj*) o;

    HSD_AObjRemove(cobj->aobj);
    eyepos = HSD_CObjGetEyePositionWObj(cobj);
    if (eyepos != NULL) {
        if (ref_DEC(eyepos) && eyepos != NULL) {
            HSD_CLASS_METHOD(eyepos)->release((HSD_Class*) eyepos);
            HSD_CLASS_METHOD(eyepos)->destroy((HSD_Class*) eyepos);
        }
    }
    interest = HSD_CObjGetInterestWObj(cobj);
    if (interest != NULL) {
        if (ref_DEC(interest) && interest != NULL) {
            HSD_CLASS_METHOD(interest)->release((HSD_Class*) interest);
            HSD_CLASS_METHOD(interest)->destroy((HSD_Class*) interest);
        }
    }
    if (cobj->proj_mtx != NULL) {
        HSD_MtxFree(cobj->proj_mtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->release(o);
}

static void CObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdCObj)) {
        current = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->amnesia(info);
}

static void CObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdCObj), &hsdObj,
                     "sysdolphin_base_library", "hsd_cobj",
                     sizeof(HSD_CObjInfo), sizeof(HSD_CObj));

    HSD_CLASS_INFO(&hsdCObj)->init = CObjInit;
    HSD_CLASS_INFO(&hsdCObj)->release = CObjRelease;
    HSD_CLASS_INFO(&hsdCObj)->amnesia = CObjAmnesia;
    hsdCObj.load = CObjLoad;
}
