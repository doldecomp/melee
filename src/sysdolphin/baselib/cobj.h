#ifndef _cobj_h_
#define _cobj_h_

#include <placeholder.h>
#include <dolphin/mtx/types.h>
#include <baselib/aobj.h>
#include <baselib/object.h>
#include <baselib/wobj.h>

#define PROJ_PERSPECTIVE 1
#define PROJ_FRUSTUM 2
#define PROJ_ORTHO 3

struct HSD_CObj {
    HSD_Obj parent;
    u32 flags; // 0x08
    struct Viewport {
        f32 left;   // 0x0C
        f32 right;  // 0x10
        f32 top;    // 0x14
        f32 bottom; // 0x18
    } viewport;
    struct Scissor {
        u16 left;   // 0x1C
        u16 right;  // 0x1E
        u16 top;    // 0x20
        u16 bottom; // 0x22
    } scissor;
    HSD_WObj* eyepos;   // 0x24
    HSD_WObj* interest; // 0x28
    union {
        f32 roll; // 0x2C
        Vec3 up;  // 0x2C - 0x34
    } u;
    f32 near; // 0x38
    f32 far;  // 0x3C
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
    u8 projection_type; // 0x50
    Mtx view_mtx;       // 0x54
    HSD_AObj* aobj;     // 0x84
    Mtx* proj_mtx;      // 0x88
};

struct HSD_CObjDesc {
    char* class_name;    // 0x00
    u16 flags;           // 0x04
    u16 projection_type; // 0x06
    struct {
        u16 left;   // 0x08
        u16 right;  // 0x0C
        u16 top;    // 0x10
        u16 bottom; // 0x14
    } viewport;
    struct {
        u16 left;   // 0x10
        u16 right;  // 0x12
        u16 top;    // 0x14
        u16 bottom; // 0x16
    } scissor;
    HSD_WObjDesc* eye_desc;      // 0x18
    HSD_WObjDesc* interest_desc; // 0x1C
    f32 roll;                    // 0x20
    Vec3* vector;                // 0x24
    f32 near;                    // 0x28
    f32 far;                     // 0x2C
    union {
        struct {
            f32 fov;
            f32 aspect;
        } perspective;

        /*
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
        */
    } projection_param;
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

void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha,
                         s32 enable_depth);
void HSD_CObjRemoveAnim(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj);
void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3*);
void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3*);
bool HSD_CObjSetCurrent(HSD_CObj*);
void HSD_CObjEndCurrent(void);
void HSD_CObjSetViewportfx4(HSD_CObj*, f32, f32, f32, f32);
void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* cam_pos);
int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye);
void HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up);
void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest);
HSD_CObj* HSD_CObjAlloc(void);

void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags);
void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim);
void HSD_CObjAnim(HSD_CObj* cobj);
void HSD_CObjReqAnim(HSD_CObj* cobj, f32 startframe);
GXProjectionType makeProjectionMtx(HSD_CObj* cobj, Mtx mtx);
int setupNormalCamera(HSD_CObj* cobj);
int setupTopHalfCamera(HSD_CObj* cobj);
int setupBottomHalfCamera(HSD_CObj* cobj);
void HSD_CObjSetupViewingMtx(HSD_CObj* cobj);
f32 HSD_CObjGetEyeDistance(HSD_CObj* cobj);
void HSD_CObjSetUpVector(UNK_PARAMS);
void HSD_CObjGetLeftVector(UNK_PARAMS);
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
void HSD_CObjGetScissor(HSD_CObj* cobj, struct Scissor*);
void HSD_CObjSetScissor(HSD_CObj* cobj, struct Scissor*);
void HSD_CObjSetScissorx4(HSD_CObj*, u16 left, u16 right, u16 top, u16 bottom);
void HSD_CObjGetViewportf(HSD_CObj* cobj, struct Viewport*);
void HSD_CObjSetViewport(HSD_CObj* cobj, s16* viewport);
void HSD_CObjSetViewportf(HSD_CObj* cobj, struct Viewport*);
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

#endif
