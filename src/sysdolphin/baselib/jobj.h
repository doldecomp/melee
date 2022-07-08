#ifndef _jobj_h_
#define _jobj_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/object.h"
#include "sysdolphin/baselib/list.h"

#include "sysdolphin/baselib/aobj.h"
/*#include "dobj.h"
#include "mobj.h"
#include "robj.h"*/

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

#define SKELETON (1 << 0)
#define SKELETON_ROOT (1 << 1)
#define ENVELOPE_MODEL (1 << 2)
#define CLASSICAL_SCALE (1 << 3)
#define HIDDEN (1 << 4)
#define PTCL (1 << 5)
#define MTX_DIRTY (1 << 6)
#define LIGHTING (1 << 7)
#define TEXGEN (1 << 8)
#define INSTANCE (1 << 12)
#define PBILLBOARD (1 << 13)
#define SPLINE (1 << 14)
#define FLIP_IK (1 << 15)
#define SPECULAR (1 << 16)
#define USE_QUATERNION (1 << 17)
#define NULL_OBJ (0 << 21)
#define JOINT1 (1 << 21)
#define JOINT2 (2 << 21)
#define EFFECTOR (3 << 21)
#define USER_DEF_MTX (1 << 23)
#define MTX_INDEP_PARENT (1 << 24)
#define MTX_INDEP_SRT (1 << 25)
#define ROOT_OPA (1 << 28)
#define ROOT_XLU (1 << 29)
#define ROOT_TEXEDGE (1 << 30)

#define JOBJ_INSTANCE(o) ((o->flags & INSTANCE) == 0)
#define JOBJ_USE_QUATERNION(o) ((o->flags & USE_QUATERNION))
#define union_type_dobj(o) ((o->flags & 0x4020) == 0)
#define union_type_ptcl(o) ((o->flags & PTCL) != 0)

typedef u32 HSD_TrspMask;

typedef struct _HSD_JObj {
    HSD_Obj object;
    struct _HSD_JObj* next;
    struct _HSD_JObj* parent;
    struct _HSD_JObj* child;
    u32 flags;
    union {
        HSD_SList* ptcl;
        struct _HSD_DObj* dobj;
        struct _HSD_Spline* spline;
    } u;
    Quaternion rotate;
    Vec scale;
    Vec translate;
    Mtx mtx;
    Vec* scl;
    MtxPtr envelopemtx;
    struct _HSD_AObj* aobj;
    struct _HSD_RObj* robj;
    u32 id;
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
    Vec rotation;
    Vec scale;
    Vec position;
    MtxPtr mtx;
    struct _HSD_RObjDesc* robjdesc;
} HSD_Joint;

typedef struct _HSD_JObjInfo {
    HSD_ObjInfo parent;
    s32 (*load)(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* jobj_2);
    void (*make_mtx)(HSD_JObj* jobj);
    void (*make_pmtx)(HSD_JObj* jobj, Mtx mtx, Mtx rmtx);
    void (*disp)(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx, HSD_TrspMask trsp_mask, u32 rendermode);
    void (*release_child)(HSD_JObj* jobj);
} HSD_JObjInfo;

extern HSD_JObjInfo hsdJObj;

void HSD_JObjCheckDependAll(HSD_JObj* jobj);
u32 HSD_JObjGetFlags(HSD_JObj* jobj);
void HSD_JObjReqAnimAll(HSD_JObj*, f32);
void HSD_JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint);
void HSD_JObjReqAnimAll(HSD_JObj*, f32);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);

#pragma push
#pragma always_inline on
inline struct _HSD_RObj* HSD_JObjGetRObj(HSD_JObj* jobj)
{
    assert_line(405, jobj);
    return jobj->robj;
}

inline BOOL HSD_JObjMtxIsDirty(HSD_JObj* jobj)
{
    BOOL result;
    assert_line(564, jobj);
    result = FALSE;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = TRUE;
    }
    return result;
}

inline void HSD_JObjSetupMatrix(HSD_JObj* jobj)
{
    if (jobj != NULL && HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj) 
{
    if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

inline void HSD_JObjGetRotation(HSD_JObj* jobj, Quaternion *quat)
{
    assert_line(699, jobj);
    *quat = jobj->rotate;
}

inline void HSD_JObjSetScale(HSD_JObj* jobj, Vec* scale)
{
    assert_line(760, jobj);
    assert_line(761, scale);
    jobj->scale = *scale;
    if (!(jobj->flags & 0x2000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

inline void HSD_JObjGetScale(HSD_JObj* jobj, Vec *scale)
{
    assert_line(823, jobj);
    *scale = jobj->scale;
}

inline void HSD_JObjSetTranslate(HSD_JObj* jobj, Vec* translate)
{
    assert_line(916, jobj);
    assert_line(917, translate);
    jobj->translate = *translate;
    if (!(jobj->flags & 0x2000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

inline void HSD_JObjGetTranslation(HSD_JObj* jobj, Vec *translate)
{
    assert_line(979, jobj);
    assert_line(980, translate);
    *translate = jobj->translate;
}

inline f32 HSD_JObjGetTranslationX(HSD_JObj* jobj)
{
    assert_line(993, jobj);
    return jobj->translate.x;
}

inline f32 HSD_JObjGetTranslationY(HSD_JObj* jobj)
{
    assert_line(1006, jobj);
    return jobj->translate.y;
}

inline void HSD_JObjGetMtx(HSD_JObj* jobj)
{
    assert_line(1144, jobj);
    HSD_JObjUnkMtxPtr(jobj);
}

inline void HSD_JObjCopyMtx(HSD_JObj* jobj, Mtx mtx)
{
    assert_line(1170, jobj);
    assert_line(1171, mtx);
    PSMTXCopy(mtx, jobj->mtx); 
}

#pragma pop

#endif
