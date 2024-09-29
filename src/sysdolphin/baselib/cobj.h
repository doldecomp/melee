#ifndef _cobj_h_
#define _cobj_h_

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/object.h"

#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx/types.h>

#define PROJ_PERSPECTIVE 1
#define PROJ_FRUSTUM 2
#define PROJ_ORTHO 3

typedef struct _Scissor {
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;
} Scissor;

typedef struct _HSD_RectS16 {
    s16 xmin;
    s16 xmax;
    s16 ymin;
    s16 ymax;
} HSD_RectS16;

typedef struct _HSD_RectF32 {
    f32 xmin;
    f32 xmax;
    f32 ymin;
    f32 ymax;
} HSD_RectF32;

struct HSD_CObj {
    /*  +0 */ HSD_Obj parent;
    /*  +8 */ u32 flags;
    /*  +C */ HSD_RectF32 viewport;
    /* +1C */ Scissor scissor;
    /* +24 */ HSD_WObj* eyepos;
    /* +28 */ HSD_WObj* interest;
    union {
        /* +2C */ f32 roll;
        /* +2C */ Vec3 up;
    } u;
    /* +38 */ f32 near;
    /* +3C */ f32 far;
    union {
        struct {
            f32 fov;
            f32 aspect;
        } perspective;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustum;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
    /* +50 */ u8 projection_type;
    /* +54 */ Mtx view_mtx;
    /* +84 */ HSD_AObj* aobj;
    /* +88 */ Mtx* proj_mtx;
};

struct HSD_CameraDescCommon {
    char* class_name;    // 0x00
    u16 flags;           // 0x04
    u16 projection_type; // 0x06
    HSD_RectS16 viewport;
    Scissor scissor;
    HSD_WObjDesc* eyepos;   // 0x18
    HSD_WObjDesc* interest; // 0x1C
    f32 roll;               // 0x20
    Vec3* up_vector;        // 0x24
    f32 nnear;              // 0x28
    f32 ffar;               // 0x2C
};

struct HSD_CameraDescFrustum {
    char* class_name;    // 0x00
    u16 flags;           // 0x04
    u16 projection_type; // 0x06
    HSD_RectS16 viewport;
    Scissor scissor;
    HSD_WObjDesc* eyepos;   // 0x18
    HSD_WObjDesc* interest; // 0x1C
    f32 roll;               // 0x20
    Vec3* up_vector;        // 0x24
    f32 nnear;              // 0x28
    f32 ffar;               // 0x2C
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
};

struct HSD_CameraDescPerspective {
    char* class_name;    // 0x00
    u16 flags;           // 0x04
    u16 projection_type; // 0x06
    HSD_RectS16 viewport;
    Scissor scissor;
    HSD_WObjDesc* eyepos;   // 0x18
    HSD_WObjDesc* interest; // 0x1C
    f32 roll;               // 0x20
    Vec3* up_vector;        // 0x24
    f32 nnear;              // 0x28
    f32 ffar;               // 0x2C
    f32 fov;
    f32 aspect;
};

union HSD_CObjDesc {
    char* class_name;
    HSD_CameraDescCommon common;
    HSD_CameraDescFrustum frustum;
    HSD_CameraDescFrustum ortho;
    HSD_CameraDescPerspective perspective;
};

struct HSD_CObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_CObj* cobj, HSD_CObjDesc* desc);
};

struct HSD_CameraAnim {
    HSD_AObjDesc* aobjdesc;
    HSD_WObjAnim* eye_anim;
    HSD_WObjAnim* interest_anim;
};

typedef struct _cobj_Unk1 cobj_Unk1;

#define HSD_COBJ(o) ((HSD_CObj*) (o))
#define HSD_COBJ_INFO(i) ((HSD_CObjInfo*) (i))
#define HSD_COBJ_METHOD(o) HSD_COBJ_INFO(HSD_OBJECT_METHOD(o))

void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha,
                         s32 enable_depth);
void HSD_CObjRemoveAnim(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj);
void HSD_CObjSetInterestWObj(HSD_CObj* cobj, HSD_WObj* interest);
HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj);
void HSD_CObjSetEyePositionWObj(HSD_CObj* cobj, HSD_WObj* eyepos);
void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3*);
void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3*);
bool HSD_CObjSetCurrent(HSD_CObj*);
void HSD_CObjEndCurrent(void);
void HSD_CObjSetViewportfx4(HSD_CObj*, f32, f32, f32, f32);
void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* cam_pos);
int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye);
int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up);
void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest);
HSD_CObj* HSD_CObjAlloc(void);

void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags);
void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim);
void HSD_CObjAnim(HSD_CObj* cobj);
void HSD_CObjReqAnim(HSD_CObj* cobj, f32 startframe);
GXProjectionType makeProjectionMtx(HSD_CObj* cobj, Mtx mtx);
void HSD_CObjSetupViewingMtx(HSD_CObj* cobj);
f32 HSD_CObjGetEyeDistance(HSD_CObj* cobj);
void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up);
int HSD_CObjGetLeftVector(HSD_CObj* cobj, Vec3* left);
void HSD_CObjSetMtxDirty(HSD_CObj* cobj);
bool HSD_CObjMtxIsDirty(HSD_CObj*);
void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx);
MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj);
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj);
MtxPtr HSD_CObjGetInvViewingMtxPtr(HSD_CObj* cobj);
void HSD_CObjSetRoll(HSD_CObj* cobj, f32);
f32 HSD_CObjGetFov(HSD_CObj* cobj);
void HSD_CObjSetFov(HSD_CObj*, f32);
f32 HSD_CObjGetAspect(HSD_CObj* cobj);
void HSD_CObjSetAspect(HSD_CObj* cobj, f32 aspect);
f32 HSD_CObjGetTop(HSD_CObj* cobj);
void HSD_CObjSetTop(HSD_CObj* cobj, f32 top);
f32 HSD_CObjGetBottom(HSD_CObj* cobj);
void HSD_CObjSetBottom(HSD_CObj* cobj, f32 bottom);
f32 HSD_CObjGetLeft(HSD_CObj* cobj);
void HSD_CObjSetLeft(HSD_CObj* cobj, f32 left);
f32 HSD_CObjGetRight(HSD_CObj* cobj);
void HSD_CObjSetRight(HSD_CObj* cobj, f32 right);
f32 HSD_CObjGetNear(HSD_CObj*);
void HSD_CObjSetNear(HSD_CObj* cobj, f32 near);
f32 HSD_CObjGetFar(HSD_CObj*);
void HSD_CObjSetFar(HSD_CObj* cobj, f32 far);
void HSD_CObjGetScissor(HSD_CObj* cobj, Scissor*);
void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor*);
void HSD_CObjSetScissorx4(HSD_CObj*, u16 left, u16 right, u16 top, u16 bottom);
void HSD_CObjGetViewportf(HSD_CObj* cobj, HSD_RectF32*);
void HSD_CObjSetViewport(HSD_CObj* cobj, HSD_RectS16* viewport);
void HSD_CObjSetViewportf(HSD_CObj* cobj, HSD_RectF32*);
u32 HSD_CObjGetProjectionType(HSD_CObj*);
void HSD_CObjSetProjectionType(HSD_CObj*, u32);
void HSD_CObjSetPerspective(HSD_CObj* cobj, f32 fov, f32 aspect);
void HSD_CObjSetFrustum(HSD_CObj*, f32 top, f32 bottom, f32 left, f32 right);
void HSD_CObjSetOrtho(HSD_CObj*, f32 top, f32 bottom, f32 left, f32 right);
void HSD_CObjGetPerspective(HSD_CObj* cobj, f32* top, f32* bottom);
void HSD_CObjGetOrtho(HSD_CObj*, f32* top, f32* bottom, f32* left, f32* right);
u32 HSD_CObjGetFlags(HSD_CObj* cobj);
void HSD_CObjSetFlags(HSD_CObj*, u32);
void HSD_CObjClearFlags(HSD_CObj*, u32);
HSD_CObj* HSD_CObjGetCurrent(void);
void HSD_CObjInit(HSD_CObj* cobj, HSD_CObjDesc* desc);
HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc);
void HSD_CObjSetDefaultClass(HSD_ClassInfo* info);

static inline MtxPtr HSD_CObjGetViewingMtxPtrDirect(HSD_CObj* cobj)
{
    return cobj->view_mtx;
}

#endif
