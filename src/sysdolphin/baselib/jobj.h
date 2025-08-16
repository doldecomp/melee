#ifndef _jobj_h_
#define _jobj_h_

#include <platform.h>

#include "baselib/class.h"
#include "baselib/debug.h"

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/list.h"
#include "baselib/object.h"
#include "baselib/pobj.h"

#include <dolphin/mtx.h>

struct HSD_JObj;

#define JOBJ_PTCL_ACTIVE 0x7FFFFFFF
#define JOBJ_PTCL_OFFSET_MASK 0xFFFFFF
#define JOBJ_PTCL_OFFSET_SHIFT 6
#define JOBJ_PTCL_BANK_MASK 0x3F

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

#define JOBJ_BILLBOARD_FIELD 0xE00
#define JOBJ_BILLBOARD 0x200
#define JOBJ_VBILLBOARD 0x400
#define JOBJ_HBILLBOARD 0x600
#define JOBJ_RBILLBOARD 0x800
#define JOBJ_PBILLBOARD 0x2000

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
#define JOBJ_SPLINE (1 << 14)
#define JOBJ_FLIP_IK (1 << 15)
#define JOBJ_SPECULAR (1 << 16)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_UNK_B18 (1 << 18)
#define JOBJ_UNK_B19 (1 << 19)
#define JOBJ_UNK_B20 (1 << 20)
#define JOBJ_NULL_OBJ (0 << 21)
#define JOBJ_JOINT1 (1 << 21)
#define JOBJ_JOINT2 (2 << 21)
#define JOBJ_JOINT (3 << 21)
#define JOBJ_EFFECTOR (3 << 21)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_PARENT (1 << 24)
#define JOBJ_MTX_INDEP_SRT (1 << 25)
#define JOBJ_UNK_B26 (1 << 26)
#define JOBJ_UNK_B27 (1 << 27)
#define JOBJ_ROOT_OPA (1 << 28)
#define JOBJ_ROOT_XLU (1 << 29)
#define JOBJ_ROOT_TEXEDGE (1 << 30)

#define JOBJ_ROOT_MASK (JOBJ_ROOT_OPA | JOBJ_ROOT_TEXEDGE | JOBJ_ROOT_XLU)

#define union_type_ptcl(o) ((o)->flags & JOBJ_PTCL ? true : false)
#define union_type_spline(o) ((o)->flags & JOBJ_SPLINE ? true : false)
#define union_type_dobj(o)                                                    \
    ((o)->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? false : true)

#define HSD_JOBJ_INFO(i) ((HSD_JObjInfo*) (i))
#define HSD_JOBJ_METHOD(o) HSD_JOBJ_INFO((o)->object.parent.class_info)

struct HSD_JObj {
    /* +0 */ HSD_Obj object;
    /* +8 */ HSD_JObj* next;
    /* +C */ HSD_JObj* parent;
    /* +10 */ HSD_JObj* child;
    /* +14 */ u32 flags;
    /* +18 */ union {
        HSD_SList* ptcl;
        struct HSD_DObj* dobj;
        HSD_Spline* spline;
    } u;
    /* +1C */ Quaternion rotate;
    /* +2C */ Vec3 scale;
    /* +38 */ Vec3 translate;
    /* +44 */ Mtx mtx;
    /* +74 */ Vec3* scl;
    /* +78 */ MtxPtr envelopemtx;
    /* +7C */ HSD_AObj* aobj;
    /* +80 */ HSD_RObj* robj;
    /* +84 */ u32 id;
};
STATIC_ASSERT(sizeof(struct HSD_JObj) == 0x88);

struct HSD_Joint {
    /* +0 */ char* class_name;
    /* +4 */ u32 flags;
    /* +8 */ HSD_Joint* child;
    /* +C */ HSD_Joint* next;
    /* +10 */ union {
        HSD_DObjDesc* dobjdesc;
        HSD_Spline* spline;
        HSD_SList* ptcl;
    } u;
    /* +14 */ Vec3 rotation;
    /* +20 */ Vec3 scale;
    /* +2C */ Vec3 position;
    /* +38 */ MtxPtr mtx;
    /* +3C */ HSD_RObjDesc* robjdesc;
};

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
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void HSD_JObjUnref(HSD_JObj* jobj);
HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj);
void HSD_JObjRemoveAll(HSD_JObj*);
struct HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void HSD_JObjAddAnimAll(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*,
                        HSD_ShapeAnimJoint*);
void HSD_JObjAnimAll(HSD_JObj*);
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
void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj);
void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj);

static inline HSD_JObj* HSD_JObjGetChild(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->child;
    }
}

static inline HSD_JObj* HSD_JObjGetNext(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->next;
    }
}

static inline HSD_JObj* HSD_JObjGetParent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->parent;
    }
}

static inline HSD_RObj* HSD_JObjGetRObj(HSD_JObj* jobj)
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

inline void HSD_JObjSetupMatrix(HSD_JObj* jobj)
{
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

// Why does this seem to be a define while the others are inline functions?
#define HSD_JObjSetMtxDirty(jobj)                                             \
    {                                                                         \
        if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {                      \
            HSD_JObjSetMtxDirtySub(jobj);                                     \
        }                                                                     \
    }

/// @todo See #lb_800117F4
static inline void HSD_JObjSetMtxDirtyInline(HSD_JObj* jobj)
{
    if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetRotation(HSD_JObj* jobj, Quaternion* rotate)
{
    HSD_ASSERT(618, jobj);
    HSD_ASSERT(619, rotate);
    jobj->rotate = *rotate;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj* jobj, f32 x)
{
    HSD_ASSERT(639, jobj);
    HSD_ASSERT(640, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(660, jobj);
    HSD_ASSERT(661, !(jobj->flags & JOBJ_USE_QUATERNION));
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(681, jobj);
    HSD_ASSERT(682, !(jobj->flags & JOBJ_USE_QUATERNION));
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

static inline f32 HSD_JObjGetRotationX(HSD_JObj* jobj)
{
    HSD_ASSERT(715, jobj);
    return jobj->rotate.x;
}

static inline f32 HSD_JObjGetRotationY(HSD_JObj* jobj)
{
    HSD_ASSERT(730, jobj);
    return jobj->rotate.y;
}

static inline f32 HSD_JObjGetRotationZ(HSD_JObj* jobj)
{
    HSD_ASSERT(745, jobj);
    return jobj->rotate.z;
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
    HSD_ASSERT(776, jobj);
    jobj->scale.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(791, jobj);
    jobj->scale.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(806, jobj);
    jobj->scale.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetScale(HSD_JObj* jobj, Vec3* scale)
{
    HSD_ASSERT(823, jobj);
    HSD_ASSERT(824, scale);
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
    HSD_ASSERT(932, jobj);
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    HSD_ASSERT(947, jobj);
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj* jobj, f32 z)
{
    HSD_ASSERT(962, jobj);
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

///@todo Likely fake but needed by vi0502 as there is a usage of
/// HSD_JObjGetTranslation that lacks the 2nd assert
static inline void HSD_JObjGetTranslation2(HSD_JObj* jobj, Vec3* translate)
{
    HSD_ASSERT(979, jobj);
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

static inline float HSD_JObjGetTranslationZ(HSD_JObj* jobj)
{
    HSD_ASSERT(1019, jobj);
    return jobj->translate.z;
}

static inline void HSD_JObjAddRotationX(HSD_JObj* jobj, float x)
{
    HSD_ASSERT(1029, jobj);
    jobj->rotate.x += x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddRotationY(HSD_JObj* jobj, float y)
{
    HSD_ASSERT(1041, jobj);
    jobj->rotate.y += y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddRotationZ(HSD_JObj* jobj, float z)
{
    HSD_ASSERT(1053, jobj);
    jobj->rotate.z += z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddScaleX(HSD_JObj* jobj, float x)
{
    // ((jobj) ? ((void) 0) : __assert("jobj.h", 1065, "jobj"));
    HSD_ASSERT(1065, jobj);
    jobj->scale.x += x;
    // if (!(jobj->flags & (1 << 25))) {
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        // { if (jobj != ((void*) 0) && !HSD_JObjMtxIsDirty(jobj)) {
        // HSD_JObjSetMtxDirtySub(jobj); } };
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddScaleY(HSD_JObj* jobj, float y)
{
    // ((jobj) ? ((void) 0) : __assert("jobj.h", 1077, "jobj"));
    HSD_ASSERT(1077, jobj);
    jobj->scale.y += y;
    // if (!(jobj->flags & (1 << 25))) {
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        // { if (jobj != ((void*) 0) && !HSD_JObjMtxIsDirty(jobj)) {
        // HSD_JObjSetMtxDirtySub(jobj); } };
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddScaleZ(HSD_JObj* jobj, float z)
{
    // ((jobj) ? ((void) 0) : __assert("jobj.h", 1089, "jobj"));
    HSD_ASSERT(1089, jobj);
    jobj->scale.z += z;
    // if (!(jobj->flags & (1 << 25))) {
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        // { if (jobj != ((void*) 0) && !HSD_JObjMtxIsDirty(jobj)) {
        // HSD_JObjSetMtxDirtySub(jobj); } };
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddTranslationX(HSD_JObj* jobj, float x)
{
    HSD_ASSERT(1102, jobj);
    jobj->translate.x += x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddTranslationY(HSD_JObj* jobj, float y)
{
    HSD_ASSERT(1114, jobj);
    jobj->translate.y += y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjAddTranslationZ(HSD_JObj* jobj, float z)
{
    HSD_ASSERT(1126, jobj);
    jobj->translate.z += z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline MtxPtr HSD_JObjGetMtxPtr(HSD_JObj* jobj)
{
    HSD_ASSERT(1144, jobj);
    HSD_JObjSetupMatrix(jobj);
    return jobj->mtx;
}

static inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx)
{
    HSD_ASSERT(1170, jobj);
    HSD_ASSERT(1171, mtx);
    PSMTXCopy(mtx, jobj->mtx);
}

static inline void HSD_JObjRef(HSD_JObj* jobj)
{
    ref_INC(jobj);
}

static inline void HSD_JObjRefThis(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        iref_INC(jobj);
    }
}

void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint);
void HSD_JObjUnrefThis(HSD_JObj* jobj);
void HSD_JObjRefThis(HSD_JObj* jobj);
void HSD_JObjMakeMatrix(HSD_JObj* jobj);
void RecalcParentTrspBits(HSD_JObj* jobj);
void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child);
HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent);
void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj);
HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff);
void resolveIKJoint1(HSD_JObj* jobj);
void resolveIKJoint2(HSD_JObj* jobj);
void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjSetDPtclCallback(DPCtlCallback cb);
int JObjInit(HSD_Class* o);
void JObjReleaseChild(HSD_JObj* jobj);
void JObjRelease(HSD_Class* o);
void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags);
void JObjAmnesia(HSD_ClassInfo* info);
void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame);
void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame);
void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame);
void JObjSortAnim(HSD_AObj* aobj);
void JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint);
void JObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);
void HSD_JObjAnim(HSD_JObj* jobj);
void JObjAnimAll(HSD_JObj* jobj);
s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent);

void HSD_JObjAddAnim(HSD_JObj*, HSD_AnimJoint* an_joint,
                     HSD_MatAnimJoint* mat_joint,
                     HSD_ShapeAnimJoint* sh_joint);
void HSD_JObjWalkTree0(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                       f32** cb_args);

#endif
