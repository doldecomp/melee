#ifndef _jobj_h_
#define _jobj_h_

#include <Runtime/platform.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/pobj.h>

#define HSD_A_J_ROTX 1
#define HSD_A_J_ROTY 2
#define HSD_A_J_ROTZ 3
#define HSD_A_J_PATH 4
#define HSD_A_J_TRAX 5
#define HSD_A_J_TRAY 6
#define HSD_A_J_TRAZ 7
#define HSD_A_J_SCAX 8
#define HSD_A_J_SCAY 9
#define HSD_A_J_SCAZ 10
#define HSD_A_J_NODE 11
#define HSD_A_J_BRANCH 12

#define HSD_A_J_SETBYTE0 20
#define HSD_A_J_SETBYTE1 21
#define HSD_A_J_SETBYTE2 22
#define HSD_A_J_SETBYTE3 23
#define HSD_A_J_SETBYTE4 24
#define HSD_A_J_SETBYTE5 25
#define HSD_A_J_SETBYTE6 26
#define HSD_A_J_SETBYTE7 27
#define HSD_A_J_SETBYTE8 28
#define HSD_A_J_SETBYTE9 29

#define HSD_A_J_SETFLOAT0 30
#define HSD_A_J_SETFLOAT1 31
#define HSD_A_J_SETFLOAT2 32
#define HSD_A_J_SETFLOAT3 33
#define HSD_A_J_SETFLOAT4 34
#define HSD_A_J_SETFLOAT5 35
#define HSD_A_J_SETFLOAT6 36
#define HSD_A_J_SETFLOAT7 37
#define HSD_A_J_SETFLOAT8 38
#define HSD_A_J_SETFLOAT9 39

#define JOBJ_SKELETON (1 << 0)
#define JOBJ_SKELETON_ROOT (1 << 1)
#define JOBJ_ENVELOPE_MODEL (1 << 2)
#define JOBJ_CLASSICAL_SCALE (1 << 3)
#define JOBJ_HIDDEN (1 << 4)
#define JOBJ_PTCL (1 << 5)
#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_LIGHTING (1 << 7)
#define JOBJ_TEXGEN (1 << 8)
#define JOBJ_INSTANCE (1 << 12)
#define JOBJ_PBILLBOARD (1 << 13)
#define JOBJ_SPLINE (1 << 14)
#define JOBJ_FLIP_IK (1 << 15)
#define JOBJ_SPECULAR (1 << 16)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_NULL_OBJ (0 << 21)
#define JOBJ_JOINT1 (1 << 21)
#define JOBJ_JOINT2 (2 << 21)
#define JOBJ_EFFECTOR (3 << 21)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_PARENT (1 << 24)
#define JOBJ_MTX_INDEP_SRT (1 << 25)
#define JOBJ_ROOT_OPA (1 << 28)
#define JOBJ_ROOT_XLU (1 << 29)
#define JOBJ_ROOT_TEXEDGE (1 << 30)

#define JOBJ_ROOT_MASK (JOBJ_ROOT_OPA | JOBJ_ROOT_TEXEDGE | JOBJ_ROOT_XLU)

#define union_type_ptcl(o) ((o)->flags & JOBJ_PTCL ? true : false)
#define union_type_spline(o) ((o)->flags & JOBJ_SPLINE ? true : false)
#define union_type_dobj(o)                                                     \
    ((o)->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? false : true)

#define HSD_JOBJ_INFO(i) ((HSD_JObjInfo*) (i))
#define HSD_JOBJ_METHOD(o) HSD_JOBJ_INFO((o)->object.parent.class_info)

typedef u32 HSD_TrspMask;

typedef struct _HSD_JObj {
    /* 0x00 - 0x04 */ HSD_Obj object;
    /* 0x08 */ struct _HSD_JObj* next;
    /* 0x0C */ struct _HSD_JObj* parent;
    /* 0x10 */ struct _HSD_JObj* child;
    /* 0x14 */ u32 flags;
    /* 0x18 */ union {
        HSD_SList* ptcl;
        struct _HSD_DObj* dobj;
        struct _HSD_Spline* spline;
    } u;
    /* 0x1C */ Quaternion rotate;
    /* 0x2C */ Vec3 scale;
    /* 0x38 */ Vec3 translate;
    /* 0x44 */ Mtx mtx;
    /* 0x74 */ Vec3* scl;
    /* 0x78 */ MtxPtr envelopemtx;
    /* 0x7C */ struct _HSD_AObj* aobj;
    /* 0x80 */ struct _HSD_RObj* robj;
    /* 0x84 */ u32 id;
} HSD_JObj;

typedef struct _HSD_Joint {
    char* class_name;
    u32 flags;
    struct _HSD_Joint* child;
    struct _HSD_Joint* next;
    union {
        struct _HSD_DObjDesc* dobjdesc;
        struct _HSD_Spline* spline;
        struct _HSD_SList* ptcl;
    } u;
    Vec3 rotation;
    Vec3 scale;
    Vec3 position;
    MtxPtr mtx;
    struct _HSD_RObjDesc* robjdesc;
} HSD_Joint;

typedef struct _HSD_JObjInfo {
    HSD_ObjInfo parent;
    s32 (*load)(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* jobj_2);
    void (*make_mtx)(HSD_JObj* jobj);
    void (*make_pmtx)(HSD_JObj* jobj, Mtx mtx, Mtx rmtx);
    void (*disp)(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx, HSD_TrspMask trsp_mask,
                 u32 rendermode);
    void (*release_child)(HSD_JObj* jobj);
} HSD_JObjInfo;

extern HSD_JObjInfo hsdJObj;
typedef void (*HSD_JObjWalkTreeCallback)(HSD_JObj*, f32**, s32);
typedef void (*DPCtlCallback)(int, int lo, int hi, HSD_JObj* jobj);

void HSD_JObjSetDefaultClass(HSD_ClassInfo* info);

void HSD_JObjCheckDepend(HSD_JObj* jobj);
u32 HSD_JObjGetFlags(HSD_JObj* jobj);
void HSD_JObjReqAnimAll(HSD_JObj*, f32);
void HSD_JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint);
void HSD_JObjReqAnimAll(HSD_JObj*, f32);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void HSD_JObjUnref(HSD_JObj* jobj);
HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj);
void HSD_JObjRemoveAll(HSD_JObj*); // sysdolphin/baselib/jobj.s
struct _HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void HSD_JObjAddAnimAll(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*,
                        HSD_ShapeAnimJoint*);
void HSD_JObjAnimAll(HSD_JObj*); // asm/sysdolphin/baselib/jobj.s
void HSD_JObjSetFlags(HSD_JObj*, u32 flags);
void HSD_JObjSetFlagsAll(HSD_JObj*, u32 flags);
void HSD_JObjClearFlags(HSD_JObj*, u32 flags);
void HSD_JObjClearFlagsAll(HSD_JObj*, u32 flags);
HSD_JObj* HSD_JObjAlloc(void);
void HSD_JObjSetCurrent(HSD_JObj* jobj);
HSD_JObj* HSD_JObjGetCurrent(void);
void HSD_JObjResolveRefsAll(HSD_JObj*, HSD_Joint*);
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode);
void HSD_JObjRemoveAnim(HSD_JObj* jobj);
void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next);
void HSD_JObjRemoveAnimAll(HSD_JObj* jobj);
void HSD_JObjWalkTree(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                      f32** cb_args);
void HSD_JObjPrependRObj(HSD_JObj* jobj, struct _HSD_RObj* robj);
void HSD_JObjDeleteRObj(HSD_JObj* jobj, struct _HSD_RObj* robj);

static inline struct _HSD_RObj* HSD_JObjGetRObj(HSD_JObj* jobj)
{
    HSD_ASSERT(405, jobj);
    return jobj->robj;
}

static inline bool HSD_JObjMtxIsDirty(HSD_JObj* jobj)
{
    bool result;
    HSD_ASSERT(564, jobj);
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj)
{
    if (jobj != NULL && HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

// Why does this seem to be a define while the others are inline functions?
#define HSD_JObjSetMtxDirty(jobj)                                              \
    {                                                                          \
        if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {                       \
            HSD_JObjSetMtxDirtySub(jobj);                                      \
        }                                                                      \
    }

static inline void HSD_JObjSetRotation(HSD_JObj* jobj, Quaternion* quat)
{
    HSD_ASSERT(618, jobj);
    jobj->rotate = *quat;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(0x27F, jobj);
    HSD_ASSERT(0x280, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(0x294, jobj);
    HSD_ASSERT(0x295, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(0x2A9, jobj);
    HSD_ASSERT(0x2AA, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetRotation(HSD_JObj* jobj, Quaternion* quat)
{
    HSD_ASSERT(699, jobj);
    *quat = jobj->rotate;
}

static inline void HSD_JObjSetScale(HSD_JObj* jobj, Vec3* scale)
{
    HSD_ASSERT(760, jobj);
    HSD_ASSERT(761, scale);
    jobj->scale = *scale;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(0x308, jobj);
    jobj->scale.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(0x317, jobj);
    jobj->scale.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(0x326, jobj);
    jobj->scale.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, Vec3* scale)
{
    HSD_ASSERT(823, jobj);
    *scale = jobj->scale;
}

static inline f32 HSD_JObjGetScaleX(HSD_JObj* jobj)
{
    HSD_ASSERT(875, jobj);
    return jobj->scale.x;
}

static inline f32 HSD_JObjGetScaleY(HSD_JObj* jobj)
{
    HSD_ASSERT(888, jobj);
    return jobj->scale.y;
}

static inline f32 HSD_JObjGetScaleZ(HSD_JObj* jobj)
{
    HSD_ASSERT(901, jobj);
    return jobj->scale.z;
}

static inline void HSD_JObjSetTranslate(HSD_JObj* jobj, Vec3* translate)
{
    HSD_ASSERT(916, jobj);
    HSD_ASSERT(917, translate);
    jobj->translate = *translate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(0x3A4, jobj);
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(0x3B3, jobj);
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(0x3C2, jobj);
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetTranslation(HSD_JObj* jobj, Vec3* translate)
{
    HSD_ASSERT(979, jobj);
    HSD_ASSERT(980, translate);
    *translate = jobj->translate;
}

static inline f32 HSD_JObjGetTranslationX(HSD_JObj* jobj)
{
    HSD_ASSERT(993, jobj);
    return jobj->translate.x;
}

static inline f32 HSD_JObjGetTranslationY(HSD_JObj* jobj)
{
    HSD_ASSERT(1006, jobj);
    return jobj->translate.y;
}

/// @todo This is misplaced or something; @c jobj.h must not include @c
///       lbcollision.
void* HSD_JObjUnkMtxPtr(struct _HSD_JObj*);

static inline void HSD_JObjGetMtx(HSD_JObj* jobj)
{
    HSD_ASSERT(1144, jobj);
    HSD_JObjUnkMtxPtr(jobj);
}

static inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx)
{
    HSD_ASSERT(1170, jobj);
    HSD_ASSERT(1171, mtx);
    PSMTXCopy(mtx, jobj->mtx);
}

#endif
