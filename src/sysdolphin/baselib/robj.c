/**
 * @file robj.c
 * @brief Reference/Constraint Object (RObj) subsystem for SysDolphin
 * @details Implements constraint objects and effectors used for Inverse Kinematics (IK).
 * Defines bone chain endpoints, angular limits, and position targets that the JObj IK solver 
 * uses to procedurally position limbs. Supports bytecode evaluation for complex constraints.
 */
#include "robj.h"

#include <math.h>
#include <string.h>

#include "aobj.h"
#include "bytecode.h"
#include "class.h"
#include "debug.h"
#include "fobj.h"
#include "id.h"
#include "jobj.h"
#include "list.h"
#include "memory.h"
#include "mtx.h"
#include "object.h"
#include "util.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>

HSD_ObjAllocData robj_alloc_data;   // robj_alloc_data
HSD_ObjAllocData rvalue_alloc_data; // rvalue_alloc_data

static float* arg_buf;
static u32 arg_buf_size;

/**
 * @brief Initializes/Allocates operations for HSD_RObjInitAllocData
 */
void HSD_RObjInitAllocData(void)
{
    HSD_ObjAllocInit(&robj_alloc_data, sizeof(HSD_RObj), 4);
    HSD_ObjAllocInit(&rvalue_alloc_data, sizeof(HSD_Rvalue), 4);
}

HSD_ObjAllocData* HSD_RObjGetAllocData(void)
{
    return &robj_alloc_data;
}

HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void)
{
    return &rvalue_alloc_data;
}

/**
 * @brief Sets operations for HSD_RObjSetFlags
 * @param robj
 * @param flags
 */
void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags)
{
    if (robj != NULL) {
        robj->flags |= flags;
    }
}

HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype)
{
    bool has_type;
    HSD_RObj* curr;

    if (robj == NULL) {
        return NULL;
    }

    for (curr = robj; curr != NULL; curr = curr->next) {
        if (curr->flags & 0x80000000) {
            has_type = true;
        } else {
            has_type = false;
        }

        if (has_type) {
            if ((curr->flags & ROBJ_TYPE_MASK) == type &&
                (!subtype || subtype == (curr->flags & 0xFFFFFFF)))
            {
                return curr;
            }
        }
    }

    return NULL;
}

/**
 * @brief Handles operations for RObjUpdateFunc
 * @param obj
 * @param type
 * @param val
 * @return static void
 */
static void RObjUpdateFunc(void* robj_ptr, enum_t anim_type, HSD_ObjData* val)
{
    HSD_RObj* robj;

    if (obj == NULL) {
        return;
    }

    if (type != TYPE_ROBJ) {
        return;
    }

    robj = (HSD_RObj*) obj;
    if (val->fv >= 0.5) {
        robj->flags = robj->flags | 0x80000000;
        return;
    }
    robj->flags = robj->flags & 0x7fffffff;
}

/**
 * @brief Processes animation for operations for HSD_RObjAnim
 * @param robj
 */
void HSD_RObjAnim(HSD_RObj* robj)
{
    if (robj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(robj->aobj, robj, RObjUpdateFunc);
}

/**
 * @brief Processes animation for operations for HSD_RObjAnimAll
 * @param robj
 */
void HSD_RObjAnimAll(HSD_RObj* robj)
{
    HSD_RObj* curr;

    if (robj == NULL) {
        return;
    }

    for (curr = robj; curr != NULL; curr = curr->next) {
        HSD_RObjAnim(curr);
    }
}

/**
 * @brief Removes/Frees operations for HSD_RObjRemoveAnimByFlags
 * @param robj
 * @param flags
 */
void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    if (robj->aobj != NULL && (flags & 0x80) != 0) {
        HSD_AObjRemove(robj->aobj);
        robj->aobj = NULL;
    }
}

/**
 * @brief Removes/Frees operations for HSD_RObjRemoveAnimAllByFlags
 * @param robj
 * @param flags
 */
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    for (; robj != NULL; robj = robj->next) {
        HSD_RObjRemoveAnimByFlags(robj, flags);
    }
}

/**
 * @brief Removes/Frees operations for HSD_RObjRemoveAnimAll
 * @param robj
 */
void HSD_RObjRemoveAnimAll(HSD_RObj* robj)
{
    HSD_RObjRemoveAnimAllByFlags(robj, 0x7FF);
}

/**
 * @brief Processes animation for operations for HSD_RObjReqAnimByFlags
 * @param robj
 * @param startframe
 * @param flags
 */
void HSD_RObjReqAnimByFlags(HSD_RObj* robj, f32 startframe, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    if (robj->aobj != NULL && (flags & 0x80) != 0) {
        HSD_AObjReqAnim(robj->aobj, startframe);
    }
}

/**
 * @brief Processes animation for operations for HSD_RObjReqAnimAllByFlags
 * @param robj
 * @param startframe
 * @param flags
 */
void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, f32 startframe, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    for (; robj != NULL; robj = robj->next) {
        HSD_RObjReqAnimByFlags(robj, startframe, flags);
    }
}

/**
 * @brief Processes animation for operations for HSD_RObjReqAnimAll
 * @param robj
 * @param startframe
 */
void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 startframe)
{
    HSD_RObjReqAnimAllByFlags(robj, startframe, 0x7FF);
}

/**
 * @brief Processes animation for operations for HSD_RObjAddAnim
 * @param robj
 * @param anim
 */
void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    if (robj == NULL || anim == NULL) {
        return;
    }

    if (robj->aobj != NULL) {
        HSD_AObjRemove(robj->aobj);
    }
    robj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
}

/**
 * @brief Processes animation for operations for HSD_RObjAddAnimAll
 * @param robj
 * @param anim
 */
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    HSD_RObj* i;
    HSD_RObjAnimJoint* j;

    if (robj == NULL || anim == NULL) {
        return;
    }

    for (i = robj, j = anim; i != NULL && j != NULL; i = i->next, j = j->next)
    {
        HSD_RObjAddAnim(i, j);
    }
}

/**
 * @brief Retrieves operations for HSD_RObjGetConstraintType
 * @param robj
 * @return static u32
 */
static u32 HSD_RObjGetConstraintType(HSD_RObj* robj)
{
    if (robj == NULL) {
        return 0;
    }

    return robj->flags & 0x0FFFFFFF;
}

/**
 * @brief Retrieves operations for HSD_RObjGetGlobalPosition
 * @param robj
 * @param type
 * @param p
 * @return int
 */
int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int type, Vec3* p)
{
    Vec3 v = { 0, 0, 0 };
    HSD_RObj* rp;
    int n = 0;

    if (robj == NULL) {
        return 0;
    }
    for (rp = robj; rp != NULL; rp = rp->next) {
        if (((rp->flags & ROBJ_TYPE_MASK) == REFTYPE_JOBJ ? 1 : 0) != 0) {
            if (((rp->flags & 0x80000000) ? 1 : 0) != 0 &&
                (unsigned) type == HSD_RObjGetConstraintType(rp))
            {
                HSD_ASSERT(498, rp->u.jobj);
                HSD_JObjSetupMatrix(rp->u.jobj);
                n += 1;
                v.x += rp->u.jobj->mtx[0][3];
                v.y += rp->u.jobj->mtx[1][3];
                v.z += rp->u.jobj->mtx[2][3];
            }
        }
    }
    if (n != 0) {
        f32 f = (f32) 1.0 / (f32) n;
        p->x = f * v.x;
        p->y = f * v.y;
        p->z = f * v.z;
    }
    return n;
}

/**
 * @brief Handles operations for set_dirup_matrix
 * @param dir_ptr
 * @param uv_ptr
 * @param scale_ptr
 * @param obj
 * @param update_func
 * @return static void
 */
static void set_dirup_matrix(Vec3* dir_ptr, Vec3* uv_ptr, Vec3* scale_ptr,
                             void* robj_ptr, HSD_ObjUpdateFunc update_func)
{
    Vec3 z_vec;
    Vec3 v;
    f32 kz;
    f32 kdir;

    PSVECCrossProduct(dir_ptr, uv_ptr, &z_vec);
    kdir =
        sqrtf(1.0F / (1.00000001335e-10f + PSVECDotProduct(dir_ptr, dir_ptr)));
    PSVECScale(dir_ptr, dir_ptr, kdir);
    kz = sqrtf(1.0F / (1.00000001335e-10f + PSVECDotProduct(&z_vec, &z_vec)));
    PSVECScale(&z_vec, &z_vec, kz);
    PSVECCrossProduct(&z_vec, dir_ptr, uv_ptr);
    v.x = dir_ptr->x * scale_ptr->x;
    v.y = dir_ptr->y * scale_ptr->x;
    v.z = dir_ptr->z * scale_ptr->x;
    update_func(obj, 50, (HSD_ObjData*) &v);
    v.x = uv_ptr->x * scale_ptr->y;
    v.y = uv_ptr->y * scale_ptr->y;
    v.z = uv_ptr->z * scale_ptr->y;
    update_func(obj, 51, (HSD_ObjData*) &v);
    v.x = z_vec.x * scale_ptr->z;
    v.y = z_vec.y * scale_ptr->z;
    v.z = z_vec.z * scale_ptr->z;
    update_func(obj, 52, (HSD_ObjData*) &v);
    update_func(obj, 55, NULL);
}

/**
 * @brief Resolves constraint/IK references for operations for resolveCnsDirUp
 * @param robj
 * @param obj
 * @param update_func
 * @return static void
 */
static void resolveCnsDirUp(HSD_RObj* robj, void* robj_ptr,
                            HSD_ObjUpdateFunc update_func)
{
    Vec3 this_scale = { 1.0f, 1.0f, 1.0f };
    Vec3 up = { 0.0f, 1.0f, 0.0f };
    Vec3 this_pos;
    Vec3 dir;
    f32 k;

    if (HSD_RObjGetGlobalPosition(robj, 2, &this_pos) != 0) {
        dir.x = ((HSD_JObj*) robj_ptr)->mtx[0][3];
        dir.y = ((HSD_JObj*) robj_ptr)->mtx[1][3];
        dir.z = ((HSD_JObj*) robj_ptr)->mtx[2][3];
        PSVECSubtract(&this_pos, &dir, &this_pos);
        if (HSD_RObjGetGlobalPosition(robj, 3, &up) != 0) {
            PSVECSubtract(&up, &dir, &up);
        } else {
            k = 1.0f - PSVECDotProduct(&this_pos, &up);
            if (fabsf_bitwise(k) < 1.00000001335e-10f) {
                up.x = 0.0f;
                up.y = 0.0f;
                up.z = 1.0;
            }
        }

        if (((HSD_JObj*) robj_ptr)->scl != NULL) {
            this_scale = *((HSD_JObj*) robj_ptr)->scl;
        }
        set_dirup_matrix(&this_pos, &up, &this_scale, obj, update_func);
    }
}

static inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}

static int HSD_RObj_80406E74[3] = { 0x32, 0x33, 0x34 };

static inline HSD_RObj* inlined_HSD_RObjGetByType(HSD_RObj* robj, u32 type,
                                                  u32 subtype)
{
    bool has_type;
    HSD_RObj* curr;

    if (robj == NULL) {
        return NULL;
    }

    for (curr = robj; curr != NULL; curr = curr->next) {
        if (curr->flags & 0x80000000) {
            has_type = true;
        } else {
            has_type = false;
        }

        if (has_type) {
            if ((curr->flags & ROBJ_TYPE_MASK) == type &&
                (!subtype || subtype == (curr->flags & 0xFFFFFFF)))
            {
                return curr;
            }
        }
    }

    return NULL;
}

/**
 * @brief Resolves constraint/IK references for operations for resolveCnsOrientation
 * @param robj
 * @param obj
 * @param (update_func)(void
 * @param int
 * @param HSD_ObjData)
 * @return static void
 */
static void resolveCnsOrientation(HSD_RObj* robj, void* robj_ptr,
                                  void (*update_func)(void*, int,
                                                      HSD_ObjData*))
{
    Mtx mtx0;
    float sval;
    u8 _[4];
    Vec3 v;
    Mtx mtx1;
    HSD_JObj* jobj;
    int i;

    HSD_ASSERT(0x276, obj);

    robj = inlined_HSD_RObjGetByType(robj, 0x10000000, 4);
    if (robj == NULL) {
        return;
    }
    if (!(HSD_JObjGetFlags(robj->u.jobj) & 8) ||
        jobj_parent(robj->u.jobj) == NULL)
    {
        PSMTXCopy(HSD_JObjGetMtxPtr(robj->u.jobj), mtx0);
        jobj = obj;

        for (i = 0; i < 3; i++) {
            HSD_MtxColVec(mtx0, i, &v);
            sval = VECMag(&v);
            if (sval > 1e-10F) {
                sval = 1.0F / sval;
            }
            sval *= HSD_MtxColMag(jobj->mtx, i);
            v.x *= sval;
            v.y *= sval;
            v.z *= sval;
            update_func(obj, HSD_RObj_80406E74[i], (HSD_ObjData*) &v);
        }
    } else {
        HSD_MtxInverseConcat(HSD_JObjGetMtxPtr(jobj_parent(robj->u.jobj)),
                             HSD_JObjGetMtxPtr(robj->u.jobj), mtx1);
        jobj = obj;

        for (i = 0; i < 3; i++) {
            v.x = mtx1[0][i];
            v.y = mtx1[1][i];
            v.z = mtx1[2][i];
            sval = VECMag(&v);
            if (sval > 1e-10F) {
                sval = 1.0F / sval;
            }
            sval *= HSD_MtxColMag(jobj->mtx, i);
            v.x *= sval;
            v.y *= sval;
            v.z *= sval;
            mtx1[0][i] = v.x;
            mtx1[1][i] = v.y;
            mtx1[2][i] = v.z;
        }

        jobj = jobj_parent(robj->u.jobj);
        while (jobj != NULL) {
            if (jobj_parent(jobj) != NULL) {
                HSD_MtxInverseConcat(HSD_JObjGetMtxPtr(jobj_parent(jobj)),
                                     HSD_JObjGetMtxPtr(jobj), mtx0);
            } else {
                PSMTXCopy(HSD_JObjGetMtxPtr(jobj), mtx0);
            }

            for (i = 0; i < 3; i++) {
                v.x = mtx0[0][i];
                v.y = mtx0[1][i];
                v.z = mtx0[2][i];
                sval = VECMag(&v);
                if (sval > 1e-10F) {
                    sval = 1.0F / sval;
                }
                v.x *= sval;
                v.y *= sval;
                v.z *= sval;
                mtx0[0][i] = v.x;
                mtx0[1][i] = v.y;
                mtx0[2][i] = v.z;
            }
            PSMTXConcat(mtx0, mtx1, mtx1);
            jobj = jobj_parent(jobj);
        }

        for (i = 0; i < 3; i++) {
            v.x = mtx1[0][i];
            v.y = mtx1[1][i];
            v.z = mtx1[2][i];
            update_func(obj, HSD_RObj_80406E74[i], (HSD_ObjData*) &v);
        }
    }
    update_func(obj, 0x37, NULL);
}

/**
 * @brief Resolves constraint/IK references for operations for resolveLimits
 * @param robj
 * @param obj
 * @param update_func
 * @return static void
 */
static void resolveLimits(HSD_RObj* robj, void* robj_ptr,
                          HSD_ObjUpdateFunc update_func)
{
    HSD_JObj* jobj = (HSD_JObj*) robj_ptr;
    HSD_RObj* rp;
    bool update_mtx = false;

    HSD_ASSERT(0x2E1, jobj);

    rp = robj;
    while (rp != NULL) {
        if (RObjHasLimitReftype(rp)) {
            break;
        }
        rp = rp->next;
    }

    if (rp != NULL) {
        for (rp = robj; rp != NULL; rp = rp->next) {
            if (RObjHasLimitReftype(rp)) {
                switch (rp->flags & 0xFFFFFFF) {
                default:
                    continue;
                case 1:
                    if (jobj->rotate.x < rp->u.limit) {
                        jobj->rotate.x = rp->u.limit;
                    }
                    break;

                case 2:
                    if (jobj->rotate.x > rp->u.limit) {
                        jobj->rotate.x = rp->u.limit;
                    }
                    break;

                case 3:
                    if (jobj->rotate.y < rp->u.limit) {
                        jobj->rotate.y = rp->u.limit;
                    }
                    break;

                case 4:
                    if (jobj->rotate.y > rp->u.limit) {
                        jobj->rotate.y = rp->u.limit;
                    }
                    break;

                case 5:
                    if (jobj->rotate.z < rp->u.limit) {
                        jobj->rotate.z = rp->u.limit;
                    }
                    break;

                case 6:
                    if (jobj->rotate.z > rp->u.limit) {
                        jobj->rotate.z = rp->u.limit;
                    }
                    break;

                case 7:
                    if (jobj->translate.x < rp->u.limit) {
                        jobj->translate.x = rp->u.limit;
                    }
                    break;

                case 8:
                    if (jobj->translate.x > rp->u.limit) {
                        jobj->translate.x = rp->u.limit;
                    }
                    break;

                case 9:
                    if (jobj->translate.y < rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 10:
                    if (jobj->translate.y > rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 11:
                    if (jobj->translate.y < rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 12:
                    if (jobj->translate.y > rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;
                }
                update_mtx = true;
            }
        }
        if (update_mtx) {
            HSD_JObjMakeMatrix(jobj);
        }
    }
}

/**
 * @brief Evaluates constraint expression/bytecode for operations for expEvaluate
 * @param exp
 * @param type
 * @param obj
 * @param robj
 * @param obj
 * @param update_func
 * @return static void
 */
static void expEvaluate(HSD_Exp* exp, u32 eval_type, void* robj_ptr,
                        HSD_ObjUpdateFunc update_func);

void HSD_RObjUpdateAll(HSD_RObj* robj, void* robj_ptr,
                       HSD_ObjUpdateFunc update_func)
{
    HSD_RObj* rp;
    Vec3 vec;

    if (robj != NULL) {
        if (HSD_RObjGetGlobalPosition(robj, 1, &vec) != 0) {
            update_func(obj, 0x35, (HSD_ObjData*) &vec);
            update_func(obj, 0x38, NULL);
        }
        resolveCnsDirUp(robj, obj, update_func);
        resolveCnsOrientation(robj, obj, update_func);
        resolveLimits(robj, obj, update_func);

        for (rp = robj; rp != NULL; rp = rp->next) {
            if (RObjHasFlags(rp) && RObjHasFlags2(rp)) {
                expEvaluate(&rp->u.exp, rp->flags & 0xFFFFFFF, obj,
                            update_func);
            }
        }
    }
}

/**
 * @brief Resolves constraint/IK references for operations for HSD_RObjResolveRefs
 * @param robj
 * @param desc
 */
void HSD_RObjResolveRefs(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    if (robj != NULL && desc != NULL) {
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(robj->u.jobj);
            robj->u.jobj = HSD_IDGetData((HSD_IDKey) desc->u.joint, NULL);
            HSD_ASSERT(883, robj->u.jobj);
            HSD_JObjRefThis(robj->u.jobj);
            break;
        case 0x0:
            HSD_RvalueResolveRefsAll(robj->u.exp.rvalue, desc->u.exp->rvalue);
            break;
        }
    }
}

/**
 * @brief Resolves constraint/IK references for operations for HSD_RObjResolveRefsAll
 * @param robj
 * @param desc
 */
void HSD_RObjResolveRefsAll(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    for (; robj != NULL && desc != NULL; robj = robj->next, desc = desc->next)
    {
        HSD_RObjResolveRefs(robj, desc);
    }
}

/**
 * @brief Handles operations for bcexpLoadDesc
 * @param exp
 * @param exp
 * @param robjdesc
 * @return static void
 */
static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc);
static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc);

HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc* robjdesc)
{
    HSD_RObj* robj;

    if (robjdesc != NULL) {
        robj = HSD_RObjAlloc();
        robj->next = HSD_RObjLoadDesc(robjdesc->next);
        robj->flags = robjdesc->flags;
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            break;
        case REFTYPE_LIMIT: {
            switch (robj->flags & 0xFFFFFFF) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                robj->u.limit = 0.017453292f * robjdesc->u.limit;
                break;
            default:
                robj->u.limit = robjdesc->u.limit;
                break;
            }
        } break;
        case REFTYPE_EXP:
            expLoadDesc(&robj->u.exp, robjdesc->u.exp);
            break;
        case REFTYPE_BYTECODE:
            bcexpLoadDesc(&robj->u.exp, robjdesc->u.bcexp);
            robj->flags &= ~ROBJ_TYPE_MASK;
            break;
        case REFTYPE_IKHINT:
            robj->u.ik_hint.bone_length = robjdesc->u.ik_hint->bone_length;
            robj->u.ik_hint.rotate_x = robjdesc->u.ik_hint->rotate_x;
            break;
        default:
            HSD_Panic(__FILE__, 0x3C0, "unexpected type of robj.\n");
            break;
        }
        return robj;
    }
    return NULL;
}

/**
 * @brief Removes/Frees operations for HSD_RObjRemove
 * @param robj
 */
void HSD_RObjRemove(HSD_RObj* robj)
{
    // s32 flags;

    if (robj != NULL) {
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(robj->u.jobj);
            break;
        case 0x0:
            HSD_RvalueRemoveAll(robj->u.exp.rvalue);
            break;
        }
        HSD_AObjRemove(robj->aobj);
        HSD_RObjFree(robj);
    }
}

/**
 * @brief Removes/Frees operations for HSD_RObjRemoveAll
 * @param robj
 */
void HSD_RObjRemoveAll(HSD_RObj* robj)
{
    HSD_RObj* next;

    for (; robj != NULL; robj = next) {
        next = robj->next;
        HSD_RObjRemove(robj);
    }
}

HSD_RObj* HSD_RObjAlloc(void)
{
    HSD_RObj* new = HSD_ObjAlloc(HSD_RObjGetAllocData());
    HSD_ASSERT(1032, new);
    memset(new, 0, sizeof(*new));
    return new;
}

/**
 * @brief Removes/Frees operations for HSD_RObjFree
 * @param robj
 */
void HSD_RObjFree(HSD_RObj* robj)
{
    HSD_ObjFree(HSD_RObjGetAllocData(), robj);
}

static char HSD_RObj_80406F14[] = "(ptr && nitems) || !ptr";

/**
 * @brief Evaluates constraint expression/bytecode for operations for expEvaluate
 * @param exp
 * @param type
 * @param obj
 * @param update_func
 * @return static void
 */
static void expEvaluate(HSD_Exp* exp, u32 eval_type, void* robj_ptr,
                        HSD_ObjUpdateFunc update_func)
{
    HSD_Rvalue* rvalue;
    HSD_JObj* jobj;
    Vec3 scale;
    float temp_f31;
    float* cur_arg;
    int cur_bit;
    Vec3 sp2C;
    u8 _[4]; ///< @todo should HSD_ObjData be 4 bytes larger?
    HSD_ObjData sp1C;
    HSD_RObj* robj = (HSD_RObj*) robj_ptr;

    if (exp->nb_args == -1) {
        u32 nb_args = 0;
        HSD_Rvalue* rvalue;
        for (rvalue = exp->rvalue; rvalue != NULL; rvalue = rvalue->next) {
            nb_args += HSD_GetNbBits(rvalue->flags);
        }
        exp->nb_args = nb_args;
    }
    if (arg_buf == NULL) {
        if (arg_buf_size == 0) {
            arg_buf_size = 100;
        }
        arg_buf = HSD_MemAlloc(arg_buf_size * sizeof(float));
    }
    if (arg_buf_size < exp->nb_args) {
        OSReport(
            "Number of argment of expression exceeds the argument buffer\n"
            "size. (requested num of arg %d, allocated %d)\n",
            exp->nb_args, arg_buf_size);
        HSD_Panic(__FILE__, 0x45E, "");
    }
    cur_arg = arg_buf;
    temp_f31 = 57.29578F;
    for (rvalue = exp->rvalue; rvalue != NULL; rvalue = rvalue->next) {
        jobj = rvalue->jobj;
        HSD_ASSERT(0x467, jobj);
        HSD_JObjSetupMatrix(rvalue->jobj);
        for (cur_bit = 1; cur_bit && cur_bit <= rvalue->flags; cur_bit <<= 1) {
            switch (rvalue->flags & cur_bit) {
            case 0x1:
                *cur_arg++ = temp_f31 * jobj->rotate.x;
                break;
            case 0x2:
                *cur_arg++ = temp_f31 * jobj->rotate.y;
                break;
            case 0x4:
                *cur_arg++ = temp_f31 * jobj->rotate.z;
                break;
            case 0x8:
                break;
            case 0x10:
                *cur_arg++ = jobj->translate.x;
                break;
            case 0x20:
                *cur_arg++ = jobj->translate.y;
                break;
            case 0x40:
                *cur_arg++ = jobj->translate.z;
                break;
            case 0x80:
                *cur_arg++ = jobj->scale.x;
                break;
            case 0x100:
                *cur_arg++ = jobj->scale.y;
                break;
            case 0x200:
                *cur_arg++ = jobj->scale.z;
                break;
            case 0x400:
            case 0x800:
                break;
            case 0x10000:
                HSD_MtxGetRotation(jobj->mtx, &sp2C);
                *cur_arg++ = temp_f31 * sp2C.x;
                break;
            case 0x20000:
                HSD_MtxGetRotation(jobj->mtx, &sp2C);
                *cur_arg++ = temp_f31 * sp2C.y;
                break;
            case 0x40000:
                HSD_MtxGetRotation(jobj->mtx, &sp2C);
                *cur_arg++ = temp_f31 * sp2C.z;
                break;
            case 0x100000:
                *cur_arg++ = jobj->mtx[0][3];
                break;
            case 0x200000:
                *cur_arg++ = jobj->mtx[1][3];
                break;
            case 0x400000:
                *cur_arg++ = jobj->mtx[2][3];
                break;
            case 0x800000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.x;
                break;
            case 0x1000000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.y;
                break;
            case 0x2000000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.z;
                break;
            }
        }
    }
    if (exp->is_bytecode) {
        sp1C.fv = HSD_ByteCodeEval(exp->expr.bytecode, arg_buf, exp->nb_args);
    } else {
        sp1C.fv = exp->expr.func(arg_buf);
    }
    if (type - 1 <= 2) {
        sp1C.fv = sp1C.fv * 0.017453292F;
    }
    update_func(obj, type, &sp1C);
}

static f32 dummy_func(void* unused)
{
    return 0.0f;
}

HSD_Rvalue* HSD_RvalueAlloc(void)
{
    HSD_Rvalue* rvalue = HSD_ObjAlloc(HSD_RvalueObjGetAllocData());
    HSD_ASSERT(1224, rvalue);
    memset(rvalue, 0, sizeof(HSD_Rvalue));
    return rvalue;
}

/**
 * @brief Removes/Frees operations for HSD_RvalueRemove
 * @param rvalue
 */
void HSD_RvalueRemove(HSD_Rvalue* rvalue)
{
    if (rvalue != NULL) {
        HSD_JObjUnrefThis(rvalue->jobj);
        HSD_ObjFree(HSD_RvalueObjGetAllocData(), rvalue);
    }
}

/**
 * @brief Removes/Frees operations for HSD_RvalueRemoveAll
 * @param rvalue
 */
void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue)
{
    HSD_Rvalue* next;

    for (; rvalue != NULL; rvalue = next) {
        next = rvalue->next;
        HSD_RvalueRemove(rvalue);
    }
}

static HSD_Rvalue* loadRvalue(HSD_RvalueList* list)
{
    HSD_Rvalue* rp;
    HSD_SList rv;

    rv.next = NULL;
    rp = (HSD_Rvalue*) &rv;
    if (list == NULL) {
        return NULL;
    } else {
        for (; list->joint != NULL; list++) {
            rp->next = HSD_RvalueAlloc();
            rp->next->flags = list->flags;
            rp = rp->next;
        }
    }
    return (HSD_Rvalue*) rv.next;
}

/**
 * @brief Handles operations for expLoadDesc
 * @param exp
 * @param desc
 * @return static void
 */
static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != NULL) {
        if (desc->func != NULL) {
            exp->expr.func = desc->func;
        } else {
            exp->expr.func = dummy_func;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
    }
}

/**
 * @brief Handles operations for bcexpLoadDesc
 * @param exp
 * @param desc
 * @return static void
 */
static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != NULL) {
        if (desc->bytecode != NULL) {
            exp->expr.bytecode = desc->bytecode;
        } else {
            exp->expr.bytecode = NULL;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
        exp->is_bytecode = 1;
    }
}

/**
 * @brief Resolves constraint/IK references for operations for HSD_RvalueResolveRefs
 * @param rvalue
 * @param list
 */
void HSD_RvalueResolveRefs(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (rvalue != NULL && list != NULL) {
        HSD_JObjUnrefThis(rvalue->jobj);
        rvalue->jobj = HSD_IDGetData((HSD_IDKey) list->joint, NULL);
        HSD_ASSERT(1333, rvalue->jobj);
        HSD_JObjRefThis(rvalue->jobj);
    }
}

/**
 * @brief Resolves constraint/IK references for operations for HSD_RvalueResolveRefsAll
 * @param rvalue
 * @param list
 */
void HSD_RvalueResolveRefsAll(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (list == NULL) {
        return;
    }
    for (; rvalue != NULL && list->joint != NULL;
         rvalue = rvalue->next, list++)
    {
        HSD_RvalueResolveRefs(rvalue, list);
    }
}

/**
 * @brief Sets operations for HSD_RObjSetConstraintObj
 * @param robj
 * @param o
 */
void HSD_RObjSetConstraintObj(HSD_RObj* robj, void* o)
{
    bool isDesc;
    HSD_JObj* jobj = o;

    if (robj != NULL) {
        if (robj->u.jobj != NULL) {
            HSD_JObjUnrefThis(robj->u.jobj);
            robj->u.jobj = NULL;
        }

        if (isDesc = hsdObjIsDescendantOf(&((HSD_JObj*) o)->object,
                                          &hsdJObj.parent.parent),
            isDesc != 0)
        {
            robj->u.jobj = o;
            HSD_JObjRefThis(o);
        } else {
            OSReport("constraint only support jobj target.\n");
            HSD_ASSERT(1376, 0);
        }
    }
}

void _HSD_RObjForgetMemory(void* low, void* high)
{
    if (low <= (void*) arg_buf && (void*) arg_buf < high) {
        arg_buf = 0U;
        arg_buf_size = 0U;
    }
}
