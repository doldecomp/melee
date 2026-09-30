/**
 * @file jobj.c
 * @brief Joint Object (JObj) skeletal transform hierarchy implementation.
 * @details Implements the core scene graph node operations for SysDolphin:
 * - Hierarchy Construction & Management: Loading joint trees from serialized DAT
 *   descriptors (#HSD_JObjLoadJoint), parent/child/sibling linking, and reference resolution.
 * - Transform & Matrix Evaluation: Local SRT matrix calculation with billboard support
 *   (#HSD_JObjMakeMatrix) and recursive world matrix accumulation (#HSD_JObjSetupMatrixSub).
 * - Animation Playback: Binding bone, material, and shape animation tracks (AObj),
 *   frame requests, and per-frame track evaluation (#HSD_JObjAnimAll, #JObjUpdateFunc).
 * - Display & Rendering: Traversal and rendering of attached Display Objects (DObj)
 *   respecting visibility and transparency flags (#HSD_JObjDispAll).
 * - Inverse Kinematics (IK): Two-bone analytical IK solvers (#resolveIKJoint1, #resolveIKJoint2)
 *   for character limb positioning with angular limits and bend inversion.
 *
 * Module prefix: HSD_JObj / JObj
 */

#include "jobj.h"

#include <math.h>
#include <string.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "displayfunc.h"
#include "dobj.h"
#include "fobj.h"
#include "id.h"
#include "mobj.h"
#include "mtx.h"
#include "pobj.h"
#include "robj.h"
#include "spline.h"
#include <dolphin/mtx.h>

void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };

static HSD_ClassInfo* default_class;
static HSD_SList* ufc_callbacks;
static void (*dptcl_callback)(int, int lo, int hi, HSD_JObj* jobj);
static void (*jsound_callback)(s32);
static void (*ptcltgt_callback)(HSD_JObj*, s32);
static HSD_JObj* current_jobj;

/**
 * @brief Verifies dependencies and reference validity on a joint.
 * @param jobj Pointer to HSD_JObj
 */
void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }

    switch (HSD_JObjMtxIsDirty(jobj)) {
    case false:
        if ((jobj->flags & JOBJ_USER_DEF_MTX)) {
            if (!(jobj->flags & JOBJ_MTX_INDEP_PARENT) &&
                jobj->parent != NULL && HSD_JObjMtxIsDirty(jobj->parent))
            {
                jobj->flags |= JOBJ_MTX_DIRTY;
            }
        } else if ((jobj->parent != NULL &&
                    (jobj->parent->flags & JOBJ_MTX_DIRTY)) ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT1 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR ||
                   jobj->robj != NULL)
        {
            jobj->flags |= JOBJ_MTX_DIRTY;
        }
        break;
    }
}

/**
 * @brief Internal helper copying translation, scale, and rotation from descriptor.
 * @param jobj Target HSD_JObj
 * @param joint Source HSD_Joint descriptor
 */
void JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

/**
 * @brief Resets a joint's rotation, scale, and translation (RST) to descriptor defaults.
 * @details Marks matrix dirty if any transform parameter differs from current state.
 * @param jobj Target HSD_JObj
 * @param joint Source HSD_Joint descriptor
 */
void HSD_JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    JObjResetRST(jobj, joint);
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child_jobj = jobj->child;
        HSD_Joint* child_joint = joint->child;
        while (child_jobj != NULL) {
            HSD_JObjResetRST(child_jobj, child_joint);
            child_jobj = child_jobj->next;
            child_joint = child_joint != NULL ? child_joint->next : NULL;
        }
    }
}

/**
 * @brief Recursive helper traversing joint tree depth-first with depth tracking.
 * @param jobj Current HSD_JObj node
 * @param cb Callback function invoked per joint
 * @param cb_args User arguments passed to callback
 * @param depth Current depth in the hierarchy
 */
void HSD_JObjWalkTree0(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                       f32** cb_args)
{
    u32 type;

    if (jobj == NULL) {
        return;
    }
    HSD_ASSERT(0xAE, jobj->parent);
    type = jobj->parent->child == jobj ? 1 : 2;
    if (cb != NULL) {
        cb(jobj, cb_args, type);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, cb_args);
            child = child->next;
        }
    }
}

/**
 * @brief Traverses the joint tree depth-first, invoking a user callback on each joint.
 * @param jobj Root of the joint tree
 * @param cb Callback function invoked per joint
 * @param cb_args User arguments passed to callback
 */
void HSD_JObjWalkTree(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                      f32** cb_args)
{
    if (jobj == NULL) {
        return;
    }
    if (cb != NULL) {
        cb(jobj, cb_args, 0);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, cb_args);
            child = child->next;
        }
    }
}

/**
 * @brief Checks if a joint has a non-uniform scale vector differing from (1, 1, 1).
 * @param jobj Pointer to HSD_JObj
 * @return True if scl exists and is non-unit
 */
static inline bool has_scl(HSD_JObj* jobj)
{
    bool result = false;
    if (jobj != NULL && jobj->scl != NULL) {
        result = true;
    }
    return result;
}

/**
 * @brief Computes local 3x4 transform matrix from scale, rotation, and translation.
 * @details Handles Euler angles, Quaternions (JOBJ_USE_QUATERNION), and billboard modes
 * (spherical, vertical, horizontal, rotational) by extracting camera viewing axes.
 * @param jobj Pointer to HSD_JObj
 */
void HSD_JObjMakeMatrix(HSD_JObj* jobj)
{
    Vec3* scl;

    HSD_JObjSetupMatrix(jobj->parent);
    if (jobj->flags & 8) {
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            if (jobj->scl == NULL) {
                jobj->scl = HSD_VecAlloc();
            }
            *jobj->scl = *jobj->parent->scl;
        } else {
            if (jobj->scl != NULL) {
                HSD_VecFree(jobj->scl);
                jobj->scl = NULL;
            }
        }
    } else {
        if (jobj->scl == NULL) {
            jobj->scl = HSD_VecAlloc();
        }
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            jobj->scl->x = jobj->scale.x * jobj->parent->scl->x;
            jobj->scl->y = jobj->scale.y * jobj->parent->scl->y;
            jobj->scl->z = jobj->scale.z * jobj->parent->scl->z;
        } else {
            *jobj->scl = jobj->scale;
        }
    }
    if (jobj->flags & 0x20000) {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRTQuat(jobj->mtx, &jobj->scale, &jobj->rotate,
                       &jobj->translate, scl);
    } else {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRT(jobj->mtx, &jobj->scale, (Vec3*) &jobj->rotate,
                   &jobj->translate, scl);
    }
    if (jobj->parent != NULL) {
        PSMTXConcat(jobj->parent->mtx, jobj->mtx, jobj->mtx);
    }
    if (jobj->aobj != NULL && jobj->aobj->hsd_obj != NULL) {
        Vec3 vec;
        HSD_JObj* aobj_jobj = (HSD_JObj*) jobj->aobj->hsd_obj;
        HSD_JObjSetupMatrix((HSD_JObj*) jobj->aobj->hsd_obj);
        MTXMultVec(aobj_jobj->mtx, &jobj->translate, &vec);
        jobj->mtx[0][3] = vec.x;
        jobj->mtx[1][3] = vec.y;
        jobj->mtx[2][3] = vec.z;
    }
}

/**
 * @brief Removes animation tracks matching specified flags from this joint's AObj.
 * @param jobj Target HSD_JObj
 * @param flags Animation track flag bitmask
 */
void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjRemove(jobj->aobj);
            jobj->aobj = NULL;
        }
        if (union_type_dobj(jobj)) {
            HSD_DObjRemoveAnimAllByFlags(jobj->u.dobj, flags);
        }
        HSD_RObjRemoveAnimAllByFlags(jobj->robj, flags);
    }
}

/**
 * @brief Recursively removes animation tracks matching flags across joint hierarchy.
 * @param jobj Root HSD_JObj
 * @param flags Animation track flag bitmask
 */
void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjRemoveAnimByFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjRemoveAnimAllByFlags(child, flags);
                child = child->next;
            }
        }
    }
}

/**
 * @brief Removes all animation tracks from this joint's AObj and attached DObjs.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjRemoveAnim(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimByFlags(jobj, 0x7FF);
}

/**
 * @brief Recursively removes all animation tracks across joint hierarchy.
 * @param jobj Root HSD_JObj
 */
void HSD_JObjRemoveAnimAll(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimAllByFlags(jobj, 0x7FF);
}

void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    bool has_dobj;
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjReqAnim(jobj->aobj, frame);
        }
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = false;
        } else {
            has_dobj = true;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->u.dobj, frame, flags);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, frame, flags);
    }
}

/**
 * @brief Recursively sets animation frame on tracks matching flags across hierarchy.
 * @param jobj Root HSD_JObj
 * @param flags Animation track flag bitmask
 * @param frame Animation frame time
 */
void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    if (jobj != NULL) {
        HSD_JObjReqAnimByFlags(jobj, flags, frame);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjReqAnimAllByFlags(child, flags, frame);
                child = child->next;
            }
        }
    }
}

/**
 * @brief Recursively sets animation frame on all tracks across hierarchy.
 * @param jobj Root HSD_JObj
 * @param frame Animation frame time
 */
void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 0x7FF, frame);
}

/**
 * @brief Sets animation frame on all tracks for this joint.
 * @param jobj Target HSD_JObj
 * @param frame Animation frame time
 */
void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame);
}

/**
 * @brief Sorts animation tracks attached to an AObj into canonical evaluation order.
 * @param aobj Pointer to HSD_AObj
 */
void JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == NULL || aobj->fobj == NULL) {
        return;
    }
    for (fobj_ptr = &aobj->fobj; *fobj_ptr != NULL; fobj_ptr = &fobj->next) {
        fobj = *fobj_ptr;
        if (fobj->obj_type == TYPE_JOBJ) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
    }
}

/**
 * @brief Attaches bone, material, and shape animations to this joint and its DObjs.
 * @param jobj Target HSD_JObj
 * @param an_joint Bone transform animation joint
 * @param mat_joint Material animation joint
 * @param sh_joint Shape/morph animation joint
 */
void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* an_joint,
                     HSD_MatAnimJoint* mat_joint, HSD_ShapeAnimJoint* sh_joint)
{
    if (jobj != NULL) {
        if (an_joint != NULL) {
            if (jobj->aobj != NULL) {
                HSD_AObjRemove(jobj->aobj);
            }
            jobj->aobj = HSD_AObjLoadDesc(an_joint->aobjdesc);
            JObjSortAnim(jobj->aobj);
            HSD_RObjAddAnimAll(jobj->robj, an_joint->robj_anim);
            if (an_joint->flags & 1) {
                HSD_JObjSetFlags(jobj, JOBJ_CLASSICAL_SCALE);
            } else {
                HSD_JObjClearFlags(jobj, JOBJ_CLASSICAL_SCALE);
            }
        }
        if (union_type_dobj(jobj)) {
            HSD_DObjAddAnimAll(
                jobj->u.dobj, mat_joint != NULL ? mat_joint->matanim : NULL,
                sh_joint != NULL ? sh_joint->shapeanimdobj : NULL);
        }
    }
}

/**
 * @brief Recursively attaches animation trees across entire joint hierarchy.
 * @param jobj Root HSD_JObj
 * @param an_joint Bone transform animation tree
 * @param mat_joint Material animation tree
 * @param sh_joint Shape animation tree
 */
void HSD_JObjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* ajoint,
                        HSD_MatAnimJoint* mjoint, HSD_ShapeAnimJoint* sjoint)
{
    HSD_JObj* jp;
    HSD_AnimJoint* aj;
    HSD_MatAnimJoint* mj;
    HSD_ShapeAnimJoint* sj;

    if (jobj != NULL) {
        HSD_JObjAddAnim(jobj, ajoint, mjoint, sjoint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            jp = jobj->child;
            aj = ajoint != NULL ? ajoint->child : NULL;
            mj = mjoint != NULL ? mjoint->child : NULL;
            sj = sjoint != NULL ? sjoint->child : NULL;
            while (jp != NULL) {
                HSD_JObjAddAnimAll(jp, aj, mj, sj);
                jp = jp->next;
                aj = aj != NULL ? aj->next : NULL;
                mj = mj != NULL ? mj->next : NULL;
                sj = sj != NULL ? sj->next : NULL;
            }
        }
    }
}

typedef void (*ufc_callback)(HSD_JObj*, u32, f32);

/**
 * @brief Core property animation evaluator dispatched by HSD_AObj.
 * @details Evaluates keyframe curves for translation, rotation, scale, node flags,
 * paths, and custom user float/byte tracks.
 * @param obj Pointer to animated object (HSD_JObj)
 * @param type Animation track type (HSD_A_J_*)
 * @param val Property value evaluated from curve
 */
void JObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_JObj* jobj = obj;
    ufc_callback cb;
    Vec3 p;
    HSD_JObj* jp;
    HSD_RObj* robj;
    Mtx mtx;

    if (jobj != NULL) {
        switch (type) {
        case HSD_A_J_PATH:
            if (val->fv < 0.0L) {
                val->fv = 0.0F;
            }
            if (1.0L < val->fv) {
                val->fv = 1.0F;
            }
            HSD_ASSERT(0x24B, jobj->aobj);
            jp = (HSD_JObj*) jobj->aobj->hsd_obj;
            HSD_ASSERT(0x24D, jp);
            HSD_ASSERT(0x24E, jp->u.spline);
            splArcLengthPoint(&p, jp->u.spline, val->fv);
            HSD_JObjSetTranslateX(jobj, p.x);
            HSD_JObjSetTranslateY(jobj, p.y);
            HSD_JObjSetTranslateZ(jobj, p.z);
            break;
        case HSD_A_J_ROTX:
            if (jobj->flags & JOBJ_JOINT1) {
                robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    robj->u.ik_hint.rotate_x = val->fv;
                }
            }
            HSD_JObjSetRotationX(jobj, val->fv);
            break;
        case HSD_A_J_ROTY:
            HSD_JObjSetRotationY(jobj, val->fv);
            break;
        case HSD_A_J_ROTZ:
            HSD_JObjSetRotationZ(jobj, val->fv);
            break;
        case HSD_A_J_TRAX:
            HSD_JObjSetTranslateX(jobj, val->fv);
            break;
        case HSD_A_J_TRAY:
            HSD_JObjSetTranslateY(jobj, val->fv);
            break;
        case HSD_A_J_TRAZ:
            HSD_JObjSetTranslateZ(jobj, val->fv);
            break;
        case HSD_A_J_SCAX:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleX(jobj, val->fv);
            break;
        case HSD_A_J_SCAY:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleY(jobj, val->fv);
            break;
        case HSD_A_J_SCAZ:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleZ(jobj, val->fv);
            break;
        case HSD_A_J_BRANCH:
            if (val->fv > 0.5) {
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_NODE:
            if (val->fv > 0.5) {
                HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_SETBYTE0:
        case HSD_A_J_SETBYTE1:
        case HSD_A_J_SETBYTE2:
        case HSD_A_J_SETBYTE3:
        case HSD_A_J_SETBYTE4:
        case HSD_A_J_SETBYTE5:
        case HSD_A_J_SETBYTE6:
        case HSD_A_J_SETBYTE7:
        case HSD_A_J_SETBYTE8:
        case HSD_A_J_SETBYTE9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->iv);
                callback_node = callback_node->next;
            }
            break;
        }
        case HSD_A_J_SETFLOAT0:
        case HSD_A_J_SETFLOAT1:
        case HSD_A_J_SETFLOAT2:
        case HSD_A_J_SETFLOAT3:
        case HSD_A_J_SETFLOAT4:
        case HSD_A_J_SETFLOAT5:
        case HSD_A_J_SETFLOAT6:
        case HSD_A_J_SETFLOAT7:
        case HSD_A_J_SETFLOAT8:
        case HSD_A_J_SETFLOAT9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->fv);
                callback_node = callback_node->next;
            }
            break;
        }
        case 0x28: {
            s32 iv = val->iv;
            s32 lo = iv & 0x3F;
            s32 hi = iv >> 6 & 0xFFFFFF;
            if (dptcl_callback != NULL) {
                dptcl_callback(0, lo, hi, jobj);
            }
        } break;
        case 0x29:
            if (jsound_callback != NULL) {
                jsound_callback(val->iv);
            }
            break;
        case 0x2A:
            if (ptcltgt_callback != NULL) {
                ptcltgt_callback(jobj, val->iv);
            }
            break;
        case 0x32:
            jobj->mtx[0][0] = val->p.x;
            jobj->mtx[1][0] = val->p.y;
            jobj->mtx[2][0] = val->p.z;
            break;
        case 0x33:
            jobj->mtx[0][1] = val->p.x;
            jobj->mtx[1][1] = val->p.y;
            jobj->mtx[2][1] = val->p.z;
            break;
        case 0x34:
            jobj->mtx[0][2] = val->p.x;
            jobj->mtx[1][2] = val->p.y;
            jobj->mtx[2][2] = val->p.z;
            break;
        case 0x35:
            jobj->mtx[0][3] = val->p.x;
            jobj->mtx[1][3] = val->p.y;
            jobj->mtx[2][3] = val->p.z;
            break;
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            if (jobj->parent != NULL) {
                HSD_MtxInverseConcat(jobj->parent->mtx, jobj->mtx, mtx);
            } else {
                PSMTXCopy(jobj->mtx, mtx);
            }
            if (type == 0x36U || type == 0x38U) {
                HSD_MtxGetTranslate(mtx, &jobj->translate);
            }
            if (type == 0x36 || type == 0x37) {
                HSD_MtxGetRotation(mtx, (Vec3*) &jobj->rotate);
            }
            if (type == 0x36U || type == 0x39U) {
                HSD_MtxGetScale(mtx, &jobj->scale);
            }
            break;
        }
    }
}

/**
 * @brief Advances animation tracks by delta frame for this joint and attached DObjs.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjAnim(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_JObjCheckDepend(jobj);
        HSD_AObjInterpretAnim(jobj->aobj, jobj, JObjUpdateFunc);
        HSD_RObjAnimAll(jobj->robj);
        if (union_type_dobj(jobj)) {
            HSD_DObjAnimAll(jobj->u.dobj);
        }
    }
}

/**
 * @brief Internal recursive helper advancing animation tracks across hierarchy.
 * @param jobj Current HSD_JObj
 */
void JObjAnimAll(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if (jobj != NULL) {
        HSD_JObjAnim(jobj);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            child = jobj->child;
            while (child != NULL) {
                JObjAnimAll(child);
                child = child->next;
            }
        }
    }
}

/**
 * @brief Advances animation tracks and updates transforms across entire joint hierarchy.
 * @param jobj Root HSD_JObj
 */
void HSD_JObjAnimAll(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_AObjInitEndCallBack();
        JObjAnimAll(jobj);
        HSD_AObjInvokeCallBacks();
    }
}

/**
 * @brief Traverses and renders the joint hierarchy using specified camera view matrix.
 * @details Evaluates visibility (JOBJ_HIDDEN), computes matrices, handles transparency
 * render modes (opaque, translucent, texedge), and dispatches attached DObjs.
 * @param jobj Root HSD_JObj to render
 * @param vmtx Camera view matrix
 * @param flags Render filter flags
 * @param rendermode Render pass mode
 */
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    MtxPtr new_var = vmtx;
    if (jobj != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            if (!(jobj->flags & JOBJ_HIDDEN)) {
                Mtx mtx;

                u8 _[8];

                HSD_CObj* cobj;
                HSD_JObjSetupMatrix(jobj);
                HSD_JObjSetupMatrix(jobj->child);
                PSMTXInverse(jobj->child->mtx, mtx);
                PSMTXConcat(jobj->mtx, mtx, mtx);
                cobj = HSD_CObjGetCurrent();
                HSD_ASSERT(0x355, cobj);
                PSMTXConcat(HSD_CObjGetViewingMtxPtrDirect(cobj), mtx, mtx);
                HSD_JObjDispAll(jobj->child, mtx, flags, rendermode);
            }
        } else {
            if (jobj->flags & (flags << 0x12)) {
                HSD_JObjDisp(jobj, new_var, flags, rendermode);
            }
            if (jobj->flags & (flags << 0x1C)) {
                HSD_JObj* child = jobj->child;
                while (child != NULL) {
                    HSD_JObjDispAll(child, new_var, flags, rendermode);
                    child = child->next;
                }
            }
        }
    }
}

/**
 * @brief Sets default class info structure for JObj allocations.
 * @param info Class info pointer
 */
void HSD_JObjSetDefaultClass(HSD_ClassInfo* info)
{
    if (info != NULL) {
        HSD_ASSERT(0x3A5, hsdIsDescendantOf(info, &hsdJObj));
    }
    default_class = info;
}

/**
 * @brief Allocates and initializes a single HSD_JObj from a joint descriptor.
 * @param joint Source HSD_Joint descriptor
 * @param parent Parent HSD_JObj
 * @return Newly allocated HSD_JObj
 */
static inline HSD_JObj* JObjLoadJointSub(HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_JObj* jobj;
    HSD_ClassInfo* info;
    if (joint == NULL) {
        return NULL;
    }
    if (joint->class_name == NULL ||
        !(info = hsdSearchClassInfo(joint->class_name)))
    {
        jobj = HSD_JObjAlloc();
    } else {
        jobj = hsdNew(info);
        HSD_ASSERT(972, jobj);
    }
    HSD_JOBJ_METHOD(jobj)->load(jobj, joint, parent);
    return jobj;
}

/**
 * @brief Recursively instantiates child and sibling joint hierarchies from descriptors.
 * @param jobj Current HSD_JObj
 * @param joint Current HSD_Joint descriptor
 * @param parent Parent HSD_JObj
 * @return 0 on success
 */
s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    if (!(joint->flags & JOBJ_INSTANCE)) {
        jobj->child = JObjLoadJointSub(joint->child, jobj);
    }
    jobj->next = JObjLoadJointSub(joint->next, parent);
    jobj->parent = parent;
    jobj->flags |= joint->flags;
    if (union_type_spline(jobj)) {
        jobj->u.spline = joint->u.spline;
    } else if (union_type_ptcl(jobj)) {
        HSD_SList* slist;
        jobj->u.ptcl = joint->u.ptcl;
        slist = joint->u.ptcl;
        while (slist != NULL) {
            *(u32*) &slist->data |= 0x80000000;
            slist = slist->next;
        }
    } else {
        jobj->u.dobj = HSD_DObjLoadDesc(joint->u.dobjdesc);
    }
    jobj->robj = HSD_RObjLoadDesc(joint->robjdesc);
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    PSMTXIdentity(jobj->mtx);
    jobj->scl = NULL;
    if (joint->mtx != NULL) {
        jobj->envelopemtx = HSD_MtxAlloc();
        memcpy(jobj->envelopemtx, joint->mtx, sizeof(Mtx));
    }
    HSD_IDInsertToTable(NULL, (HSD_IDKey) joint, jobj);
    jobj->id = (HSD_IDKey) joint;
    return 0;
}

/**
 * @brief Master entry point loading a complete joint hierarchy from a DAT file descriptor.
 * @param joint Pointer to root HSD_Joint descriptor
 * @return Pointer to constructed root HSD_JObj
 */
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* arg0)
{
    HSD_JObj* jobj = JObjLoadJointSub(arg0, 0);
    HSD_JObjResolveRefsAll(jobj, arg0);
    return jobj;
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused1[] = "jobj_root";
static char unused2[] = "jobj_root == NULL";
#pragma pop
#endif

/**
 * @brief Resolves DObj, particle, and bone references for a single joint.
 * @param jobj Target HSD_JObj
 * @param joint Source HSD_Joint descriptor
 */
void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    if (jobj == NULL || joint == NULL) {
        return;
    }

    HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
    if (!!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObjUnref(jobj->child);
        jobj->child =
            HSD_IDGetDataFromTable(NULL, (HSD_IDKey) joint->child, NULL);
        HSD_ASSERT(1108, jobj->child);
        HSD_JObjRef(jobj->child);
    }
    if (union_type_dobj(jobj)) {
        HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
    }
}

/**
 * @brief Recursively resolves envelope skinning references across joint tree.
 * @param jobj Root HSD_JObj
 * @param joint Root HSD_Joint descriptor
 */
void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    while (jobj != NULL && joint != NULL) {
        HSD_JObjResolveRefs(jobj, joint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObjResolveRefsAll(jobj->child, joint->child);
        }
        jobj = jobj->next;
        joint = joint->next;
    }
}

/**
 * @brief Decrements reference count on a joint, freeing it when reaching 0.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjUnref(HSD_JObj* jobj)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) - 1 < 0) {
            hsdDelete(jobj);
        } else {
            iref_INC(jobj);
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                hsdDelete(jobj);
            }
        }
    }
}

/**
 * @brief Decrements internal reference count on a joint.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjUnrefThis(HSD_JObj* jobj)
{
    if (jobj != NULL && iref_DEC(jobj) && ref_CNT(jobj) < 0) {
        hsdDelete(jobj);
    }
}

HSD_JObj* HSD_JObjGetPrev(HSD_JObj*);

/**
 * @brief Unlinks and removes a single joint from its parent and sibling chain.
 * @param jobj Target HSD_JObj to remove
 * @return Next sibling joint, or NULL
 */
HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj)
{
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* prev;

    if (jobj == NULL) {
        return 0;
    }
    child = jobj->child;
    if (child != NULL) {
        HSD_ASSERT(1216, child->next == NULL);
    }

    next = child != NULL ? child : jobj->next;

    prev = HSD_JObjGetPrev(jobj);
    if (prev != NULL) {
        prev->next = next;
    } else if (jobj->parent != NULL) {
        jobj->parent->child = next;
    }
    if (next != NULL && next == child) {
        next->next = jobj->next;
        next->parent = jobj->parent;
    }
    jobj->parent = NULL;
    jobj->child = NULL;
    jobj->next = NULL;
    HSD_JObjUnref(jobj);
    return child;
}

/**
 * @brief Recursively unlinks and removes a joint and all its descendants.
 * @param jobj Root HSD_JObj
 */
void HSD_JObjRemoveAll(HSD_JObj* jobj)
{
    HSD_JObj* prev;
    HSD_JObj* next;

    if (jobj == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        prev = HSD_JObjGetPrev(jobj);
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            jobj->parent->child = NULL;
        }
    }
    while (jobj != NULL) {
        next = jobj->next;
        jobj->parent = NULL;
        jobj->next = NULL;
        HSD_JObjUnref(jobj);
        jobj = next;
    }
}

/**
 * @brief Recalculates transparency render flags (opaque, transparent, texedge) from children.
 * @param jobj Target HSD_JObj
 */
void RecalcParentTrspBits(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        HSD_JObj* child = jobj->child;
        u32 flags = ~JOBJ_ROOT_MASK;
        while (child != NULL) {
            flags |= (child->flags | child->flags << 10) & JOBJ_ROOT_MASK;
            child = child->next;
        }
        if (!(jobj->flags & ~flags)) {
            break;
        }
        jobj->flags &= flags;
        jobj = jobj->next;
    }
}

/**
 * @brief Propagates transparency flags upward through the parent chain.
 * @param jobj Target HSD_JObj
 */
static void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child)
{
    u32 flags = (child->flags | (child->flags << 10)) & JOBJ_ROOT_MASK;
    while (jobj != NULL) {
        if (!(flags & ~jobj->flags)) {
            break;
        }
        jobj->flags |= flags;
        jobj = jobj->parent;
    }
}

/**
 * @brief Attaches a child joint to a parent joint.
 * @param jobj Parent HSD_JObj
 * @param child Child HSD_JObj to attach
 */
void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child)
{
    HSD_JObj* last;

    if (jobj == NULL || child == NULL) {
        return;
    }
    HSD_ASSERTREPORT(1350, child->parent == NULL,
                     "child should be a orphan.\n");
    HSD_ASSERTREPORT(1351, child->next == NULL,
                     "child should not have siblings");
    if (jobj->child == NULL) {
        jobj->child = child;
    } else {
        HSD_ASSERT(1357, !(jobj->flags & JOBJ_INSTANCE));
        last = jobj->child;
        while (last->next != NULL) {
            HSD_ASSERT(1360, last != child);
            last = last->next;
        }
        last->next = child;
    }
    child->parent = jobj;
    UpdateParentTrspBits(jobj, child);
}

/**
 * @brief Moves a joint from its current parent to a new parent in the hierarchy.
 * @param jobj Joint to reparent
 * @param parent New parent HSD_JObj
 * @return The reparented joint
 */
HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent)
{
    HSD_JObj* next;

    if (jobj == NULL) {
        return NULL;
    }
    next = jobj->next;
    if (jobj->parent != NULL) {
        if (jobj->parent->child == jobj) {
            jobj->parent->child = next;
        } else {
            HSD_JObj* prev = HSD_JObjGetPrev(jobj);
            HSD_ASSERT(0x56F, prev);
            prev->next = next;
        }
        RecalcParentTrspBits(jobj->parent);
        jobj->parent = NULL;
    }
    jobj->next = NULL;
    HSD_JObjAddChild(parent, jobj);
    return next;
}

/**
 * @brief Appends a sibling joint to the current joint's next chain.
 * @param jobj Current HSD_JObj
 * @param next Sibling HSD_JObj to append
 */
void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next)
{
    HSD_JObj* cur;

    if (jobj == NULL || next == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        cur = jobj->parent->child;
        jobj->parent->child = NULL;
        jobj->flags &= ~JOBJ_ROOT_MASK;
    } else {
        cur = jobj;
    }
    HSD_JObjReparent(next, jobj->parent);
    if (next->child != NULL) {
        HSD_JObj* child = next->child;
        while (child->next != NULL) {
            child = child->next;
        }
        child->next = cur;
    } else {
        next->child = cur;
    }
    while (cur != NULL) {
        cur->parent = next;
        UpdateParentTrspBits(next, cur);
        cur = cur->next;
    }
}

/**
 * @brief Finds the preceding sibling in the joint linked list.
 * @param jobj Current HSD_JObj
 * @return Preceding sibling HSD_JObj, or NULL if first
 */
HSD_JObj* HSD_JObjGetPrev(HSD_JObj* jobj)
{
    HSD_JObj* cur;

    if (jobj == NULL || jobj->parent == NULL) {
        return NULL;
    }
    if (jobj == jobj->parent->child) {
        return NULL;
    }
    cur = jobj->parent->child;
    while (cur != NULL) {
        if (cur->next == jobj) {
            return cur;
        }
        cur = cur->next;
    }
    HSD_Panic(__FILE__, 1516,
              "can not find specified jobj. maybe jobj tree is broken.\n");
    return NULL;
}

/**
 * @brief Returns the head of the attached display object (DObj) linked list.
 * @param jobj Pointer to HSD_JObj
 * @return Attached HSD_DObj pointer, or NULL
 */
HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj)
{
    if (jobj == NULL || !union_type_dobj(jobj)) {
        return NULL;
    }
    return jobj->u.dobj;
}

/**
 * @brief Appends a display object (DObj) mesh to this joint.
 * @param jobj Target HSD_JObj
 * @param dobj HSD_DObj to attach
 */
void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj == NULL || dobj == NULL || !union_type_dobj(jobj)) {
        return;
    }
    dobj->next = jobj->u.dobj;
    jobj->u.dobj = dobj;
}

/**
 * @brief Internal helper chaining render objects (RObj).
 * @param robj Current HSD_RObj
 * @param next Next HSD_RObj
 * @return The chained RObj
 */
static inline HSD_RObj* robj_set_next(HSD_RObj* robj, HSD_RObj* next)
{
    if (robj == NULL) {
        return next;
    }
    robj->next = next;
    return robj;
}

/**
 * @brief Prepends a render object constraint (RObj) to this joint.
 * @param jobj Target HSD_JObj
 * @param robj HSD_RObj constraint to prepend
 */
void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    jobj->robj = robj_set_next(robj, jobj->robj);
}

/**
 * @brief Removes and deletes an RObj constraint from this joint.
 * @param jobj Target HSD_JObj
 * @param robj HSD_RObj constraint to delete
 */
void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    if (robj != NULL) {
        HSD_RObj** cur_ptr = &jobj->robj;
        HSD_RObj* cur;
        while (*cur_ptr != NULL) {
            cur = *cur_ptr;
            if (cur == robj) {
                *cur_ptr = cur->next;
                robj->next = NULL;
                return;
            }
            cur_ptr = &cur->next;
        }
    }
}

/**
 * @brief Retrieves active JOBJ_* flags from a joint.
 * @param jobj Pointer to HSD_JObj
 * @return Bitmask of JOBJ_* flags
 */
u32 HSD_JObjGetFlags(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        return jobj->flags;
    }
    return 0;
}

/**
 * @brief Sets specific JOBJ_* flag bits on a joint.
 * @param jobj Target HSD_JObj
 * @param flags Bitmask of flags to set
 */
void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ flags) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags |= flags;
    }
}

/**
 * @brief Recursively sets JOBJ_* flag bits across joint hierarchy.
 * @param jobj Root HSD_JObj
 * @param flags Bitmask of flags to set
 */
void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjSetFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjSetFlagsAll(i, flags);
            }
        }
    }
}

/**
 * @brief Clears specific JOBJ_* flag bits on a joint.
 * @param jobj Target HSD_JObj
 * @param flags Bitmask of flags to clear
 */
void HSD_JObjClearFlags(HSD_JObj* jobj, u32 arg1)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ arg1) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags &= ~arg1;
    }
}

/**
 * @brief Recursively clears JOBJ_* flag bits across joint hierarchy.
 * @param jobj Root HSD_JObj
 * @param flags Bitmask of flags to clear
 */
void HSD_JObjClearFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjClearFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjClearFlagsAll(i, flags);
            }
        }
    }
}

/**
 * @brief Allocates a new blank HSD_JObj from class memory pool.
 * @return Newly allocated HSD_JObj pointer
 */
HSD_JObj* HSD_JObjAlloc(void)
{
    HSD_JObj* jobj =
        hsdNew(default_class != NULL ? default_class : &hsdJObj.parent.parent);
    HSD_ASSERT(2003, jobj);
    return jobj;
}

/**
 * @brief Sets the thread-local current active HSD_JObj pointer.
 * @param jobj Pointer to HSD_JObj
 */
void HSD_JObjSetCurrent(HSD_JObj* jobj)
{
    HSD_JObjRef(jobj);
    HSD_JObjUnref(current_jobj);
    current_jobj = jobj;
}

/**
 * @brief Retrieves the thread-local current active HSD_JObj pointer.
 * @return Currently active HSD_JObj pointer
 */
HSD_JObj* HSD_JObjGetCurrent(void)
{
    return current_jobj;
}

static inline HSD_JObj* jobj_get_joint2(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

/**
 * @brief Finds the effector joint in an IK chain.
 * @param jobj Starting child joint
 * @return Effector HSD_JObj, or NULL
 */
static inline HSD_JObj* jobj_get_effector(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

/// Note: this must not be declared inline, so that
/// the "eff" assertion string data is placed before "robj".
/**
 * @brief Finds the effector joint in an IK chain and asserts its reference validity.
 * @param eff Starting child joint
 * @return Validated effector HSD_JObj, or NULL
 */
HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff)
{
    eff = jobj_get_effector(eff);
    HSD_ASSERT(2084, eff);
    if (HSD_RObjGetByType(eff->robj, REFTYPE_JOBJ, 1) != NULL) {
        return eff;
    } else {
        return NULL;
    }
}

extern const Vec3 HSD_JObj_803B94C4;

/// @todo Variables @c var_f27 and @c var_f28 are used uninitialized
///       whenever 'if' condition is false.
/**
 * @brief Analytical two-bone inverse kinematics solver for base joint (Joint1, e.g. shoulder/hip).
 * @details Solves orientation matrix for the upper limb joint given target effector position,
 * bone lengths, roll angle, and bend direction (JOBJ_FLIP_IK) using the Law of Cosines.
 * @param jobj Pointer to Joint1 HSD_JObj
 */
void resolveIKJoint1(HSD_JObj* jobj)
{
    HSD_JObj* robj_4;
    HSD_JObj* effector;
    HSD_JObj* joint2;
    Vec3* scl_ptr;
    f32 temp_f1_7;
    f32 temp_f1_8;
    f32 target_dist_sq;
    f32 bone1_len;
    f32 temp_f5;
    f32 temp_f5_2;
    Vec3 scale_vec = { 1.0F, 1.0F, 1.0F };
    f32 var_f1;
    f32 bone2_len;
    f32 var_f29_2;
    f32 var_f28;
    f32 var_f27;
    f32 roll_angle;
    f32 var_f4;
    f32 var_f4_2;
    Vec3 parent_pos;

    u8 _[4];

    f32 var_f4_3;
    f32 var_f4_4;
    f32 var_f5;
    s32 flip_ik;
    HSD_RObj* robj;
    Vec3 axis_x;
    Vec3 target_diff;
    Vec3 unit_normal;
    HSD_IKHint* new_var;
    Vec3 unit_pole;
    Vec3 target_dir;
    Vec3 pole_vec;
    Vec3 normal_vec;
    Mtx roll_mtx;

    flip_ik = 0;
    bone2_len = 0.0F;
    joint2 = jobj_get_joint2(jobj->child);
    parent_pos = HSD_JObj_803B94C4;
    scl_ptr = jobj->scl;
    var_f5 = 1e-8F;
    if (scl_ptr != NULL) {
        scale_vec = *scl_ptr;
    }
    robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x853, robj);
    new_var = &robj->u.ik_hint;
    roll_angle = new_var->rotate_x;
    bone1_len = new_var->bone_length * scale_vec.x;
    if (joint2 != NULL) {
        robj = HSD_RObjGetByType(joint2->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x85E, robj);
        bone2_len = robj->u.ik_hint.bone_length * joint2->scale.x * scale_vec.x;
        flip_ik = robj->flags & 4 ? 1 : 0;
        effector = jobj_get_effector_checked(joint2->child);
    } else {
        effector = jobj_get_effector_checked(jobj->child);
    }
    if (effector != NULL) {
        if ((HSD_RObjGetByType(jobj->robj, REFTYPE_JOBJ, 3) == NULL) &&
            (jobj != NULL))
        {
            if (jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, JObjUpdateFunc);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= 0xFFFFFFBF;
                }
            }
        }
        robj_4 = jobj->parent;
        if (robj_4 != NULL) {
            HSD_MtxGetTranslate(robj_4->mtx, &parent_pos);
        }
        HSD_RObjGetGlobalPosition(effector->robj, 1, &effector->translate);
        VECSubtract(&effector->translate, &parent_pos, &target_diff);
        target_dist_sq = VECDotProduct(&target_diff, &target_diff);

        if (target_dist_sq > var_f5) {
            target_dir = target_diff;
            if (HSD_RObjGetGlobalPosition(jobj->robj, 3, &pole_vec)) {
                VECSubtract(&pole_vec, &parent_pos, &pole_vec);
                if (roll_angle != 0.0F) {
                    PSMTXRotAxisRad(roll_mtx, &target_dir, roll_angle);
                    MTXMultVec(roll_mtx, &pole_vec, &pole_vec);
                }
                VECCrossProduct(&target_dir, &pole_vec, &normal_vec);
                VECCrossProduct(&normal_vec, &target_dir, &pole_vec);
            } else {
                normal_vec.x = jobj->mtx[0][2];
                normal_vec.y = jobj->mtx[1][2];
                normal_vec.z = jobj->mtx[2][2];
                VECCrossProduct(&normal_vec, &target_dir, &pole_vec);
                VECCrossProduct(&target_dir, &pole_vec, &normal_vec);
            }
            var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&normal_vec, &normal_vec)));
            VECScale(&normal_vec, &unit_normal, var_f4);
            var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&pole_vec, &pole_vec)));
            VECScale(&pole_vec, &unit_pole, var_f4_2);
            temp_f5 = bone1_len * bone1_len;
            var_f28 = bone2_len * bone2_len;
            temp_f1_7 = temp_f5 - var_f28;
            temp_f1_8 = 0.25F * (((2.0F * (temp_f5 + var_f28)) - target_dist_sq) -
                                 ((temp_f1_7 * temp_f1_7) / target_dist_sq));
            var_f27 = temp_f1_8;
            if (temp_f1_8 < 0.0F) {
                var_f27 = 0.0F;
            }
            temp_f5_2 = (temp_f5 - var_f27) / target_dist_sq;
            var_f4_3 = sqrtf(1.0F / (1e-10F + temp_f5_2));
            var_f1 = temp_f5_2 * var_f4_3;
            var_f5 = sqrtf(1.0F / (1e-10F + var_f27));
            var_f29_2 = var_f27 * var_f5;
        } else {
            var_f1 = 0.0F;
            var_f29_2 = bone1_len;
        }
        if (flip_ik != 0) {
            var_f29_2 = -var_f29_2;
        }
        if ((var_f28 - var_f27) < target_dist_sq) {
            VECScale(&target_diff, &axis_x, var_f1);
        } else {
            VECScale(&target_diff, &axis_x, -var_f1);
        }
        VECScale(&unit_pole, &pole_vec, var_f29_2);
        VECAdd(&axis_x, &pole_vec, &axis_x);
        var_f4_4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&axis_x, &axis_x)));
        VECScale(&axis_x, &axis_x, var_f4_4);
        jobj->mtx[0][0] = axis_x.x * scale_vec.x;
        jobj->mtx[1][0] = axis_x.y * scale_vec.x;
        jobj->mtx[2][0] = axis_x.z * scale_vec.x;
        VECCrossProduct(&unit_normal, &axis_x, &pole_vec);
        jobj->mtx[0][1] = pole_vec.x * scale_vec.y;
        jobj->mtx[1][1] = pole_vec.y * scale_vec.y;
        jobj->mtx[2][1] = pole_vec.z * scale_vec.y;
        jobj->mtx[0][2] = unit_normal.x * scale_vec.z;
        jobj->mtx[1][2] = unit_normal.y * scale_vec.z;
        jobj->mtx[2][2] = unit_normal.z * scale_vec.z;
        jobj->mtx[0][3] = parent_pos.x;
        jobj->mtx[1][3] = parent_pos.y;
        jobj->mtx[2][3] = parent_pos.z;
    }
}

const Vec3 HSD_JObj_803B94C4 = { 0.0F, 0.0F, 0.0F };
const Vec3 HSD_JObj_803B94D0 = { 1.0F, 1.0F, 1.0F };

/**
 * @brief Analytical two-bone inverse kinematics solver for second joint (Joint2, e.g. elbow/knee).
 * @details Solves orientation matrix for the lower limb joint given target effector position,
 * clamping joint bend angle against angular limits defined in attached RObjs.
 * @param jobj Pointer to Joint2 HSD_JObj
 */
void resolveIKJoint2(HSD_JObj* jobj)
{
    Vec3 scale_vec;
    Vec3 joint2_pos;
    Vec3 parent_pos;
    Vec3 target_dir;
    Vec3 axis_y;
    Vec3 axis_z;
    Mtx rot_mtx;
    Vec3 parent_axis_x;
    Vec3 parent_axis_z;

    u8 _[4];

    HSD_JObj* effector;
    f32 temp_f1_4;
    f32 joint_angle;
    f32 var_f31;
    f32 var_f4;
    f32 var_f4_2;
    s32 angle_clamped;
    s32 flip_ik;
    HSD_RObj* min_limit_robj;
    HSD_RObj* max_limit_robj;
    HSD_RObj* robj;

    var_f31 = 1.0F;
    scale_vec = HSD_JObj_803B94D0;
    effector = jobj_get_effector_checked(jobj->child);
    if (effector == NULL || jobj->parent == NULL) {
        return;
    }
    if (jobj->scl != NULL) {
        scale_vec = *jobj->scl;
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        parent_pos.x = mtx[0][3];
        parent_pos.y = mtx[1][3];
        parent_pos.z = mtx[2][3];
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        target_dir.x = mtx[0][0];
        target_dir.y = mtx[1][0];
        target_dir.z = mtx[2][0];
    }
    var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&target_dir, &target_dir)));
    VECScale(&target_dir, &target_dir, var_f4);
    if (jobj->parent->scl != NULL) {
        var_f31 = jobj->parent->scl->x;
    }
    robj = HSD_RObjGetByType(jobj->parent->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x8FC, robj);
    VECScale(&target_dir, &target_dir, robj->u.ik_hint.bone_length * var_f31);
    VECAdd(&parent_pos, &target_dir, &joint2_pos);
    VECSubtract(&effector->translate, &joint2_pos, &target_dir);
    VECScale(&target_dir, &target_dir,
             sqrtf(1.0F / (1e-10F + VECDotProduct(&target_dir, &target_dir))));
    min_limit_robj = HSD_RObjGetByType(jobj->robj, 0x20000000, 5);
    max_limit_robj = HSD_RObjGetByType(jobj->robj, 0x20000000, 6);
    if ((min_limit_robj != NULL) || (max_limit_robj != NULL)) {
        angle_clamped = 0;
        robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x91E, robj);
        flip_ik = robj->flags & 4 ? 1 : 0;
        {
            MtxPtr mtx = jobj->parent->mtx;
            parent_axis_x.x = mtx[0][0];
            parent_axis_x.y = mtx[1][0];
            parent_axis_x.z = mtx[2][0];
        }
        VECNormalize(&parent_axis_x, &parent_axis_x);
        temp_f1_4 = VECDotProduct(&parent_axis_x, &target_dir);
        if (temp_f1_4 >= 1.0F) {
            joint_angle = 0.0F;
        } else if (temp_f1_4 <= -1.0F) {
            joint_angle = M_PI;
        } else {
            joint_angle = acosf(temp_f1_4);
        }
        if (flip_ik == 0) {
            joint_angle = -joint_angle;
        }
        if (min_limit_robj != NULL && joint_angle < min_limit_robj->u.limit) {
            joint_angle = min_limit_robj->u.limit;
            angle_clamped = 1;
        } else if (max_limit_robj != NULL) {
            if (max_limit_robj->u.limit < joint_angle) {
                joint_angle = max_limit_robj->u.limit;
                angle_clamped = 1;
            }
        }
        if (angle_clamped != 0) {
            {
                MtxPtr mtx = jobj->parent->mtx;
                parent_axis_z.x = mtx[0][2];
                parent_axis_z.y = mtx[1][2];
                parent_axis_z.z = mtx[2][2];
            }
            PSMTXRotAxisRad(rot_mtx, &parent_axis_z, joint_angle);
            MTXMultVec(rot_mtx, &parent_axis_x, &target_dir);
        }
    }
    {
        MtxPtr mtx = jobj->parent->mtx;
        axis_z.x = mtx[0][2];
        axis_z.y = mtx[1][2];
        axis_z.z = mtx[2][2];
    }
    VECCrossProduct(&axis_z, &target_dir, &axis_y);
    var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&axis_y, &axis_y)));
    VECScale(&axis_y, &axis_y, var_f4_2);
    VECCrossProduct(&target_dir, &axis_y, &axis_z);
    jobj->mtx[0][0] = target_dir.x * scale_vec.x;
    jobj->mtx[1][0] = target_dir.y * scale_vec.x;
    jobj->mtx[2][0] = target_dir.z * scale_vec.x;
    jobj->mtx[0][1] = axis_y.x * scale_vec.y;
    jobj->mtx[1][1] = axis_y.y * scale_vec.y;
    jobj->mtx[2][1] = axis_y.z * scale_vec.y;
    jobj->mtx[0][2] = axis_z.x * scale_vec.z;
    jobj->mtx[1][2] = axis_z.y * scale_vec.z;
    jobj->mtx[2][2] = axis_z.z * scale_vec.z;
    jobj->mtx[0][3] = joint2_pos.x;
    jobj->mtx[1][3] = joint2_pos.y;
    jobj->mtx[2][3] = joint2_pos.z;
}

/**
 * @brief Computes world transform matrix by combining parent transform with local transform.
 * @details Dispatches IK solvers for IK joint types, computes billboard orientations,
 * and handles classical scale and independent parent flags.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj)
{
    Vec3 effector_pos;
    Vec3 parent_pos;
    Vec3 bone_dir;
    HSD_JObj* parent;
    HSD_RObj* robj;
    f32 x_scale;

    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
    jobj->flags &= ~JOBJ_MTX_DIRTY;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX)) {
        switch (jobj->flags & JOBJ_JOINT) {
        case JOBJ_JOINT1:
            resolveIKJoint1(jobj);
            break;
        case JOBJ_JOINT2:
            resolveIKJoint2(jobj);
            break;
        case JOBJ_EFFECTOR:
            parent = jobj->parent;
            x_scale = 1.0F;
            if (parent != NULL) {
                robj = HSD_RObjGetByType(parent->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    parent_pos.x = parent->mtx[0][3];
                    parent_pos.y = parent->mtx[1][3];
                    parent_pos.z = parent->mtx[2][3];
                    bone_dir.x = parent->mtx[0][0];
                    bone_dir.y = parent->mtx[1][0];
                    bone_dir.z = parent->mtx[2][0];
                    VECScale(
                        &bone_dir, &bone_dir,
                        sqrtf(1.0F / (1e-10F + VECDotProduct(&bone_dir, &bone_dir))));
                    if (parent->scl != NULL) {
                        x_scale = parent->scl->x;
                    }
                    VECScale(&bone_dir, &bone_dir,
                             robj->u.ik_hint.bone_length * x_scale);
                    VECAdd(&parent_pos, &bone_dir, &effector_pos);
                    jobj->mtx[0][3] = effector_pos.x;
                    jobj->mtx[1][3] = effector_pos.y;
                    jobj->mtx[2][3] = effector_pos.z;
                }
            }
            break;
        default:
            if (jobj->robj != NULL && jobj != NULL && jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, JObjUpdateFunc);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= ~JOBJ_MTX_DIRTY;
                }
            }
            break;
        }
        jobj->flags &= ~JOBJ_MTX_DIRTY;
    }
}

/**
 * @brief Recursively marks a joint and all its descendants as having dirty matrices.
 * @param jobj Target HSD_JObj
 */
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj)
{
    jobj->flags |= 0x40;
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            if (!(child->flags & JOBJ_MTX_INDEP_PARENT)) {
                if (!HSD_JObjMtxIsDirty(child)) {
                    HSD_JObjSetMtxDirtySub(child);
                }
            }
            child = child->next;
        }
    }
}

/**
 * @brief Sets the dynamic particle render callback.
 * @param cb Callback function pointer
 */
void HSD_JObjSetDPtclCallback(DPCtlCallback cb)
{
    dptcl_callback = cb;
}

int JObjInit(HSD_Class* o)
{
    int status = HSD_OBJECT_PARENT_INFO(&hsdJObj)->init(o);
    if (status >= 0) {
        HSD_JObj* jobj = (HSD_JObj*) o;
        status = 0;
        jobj->flags = JOBJ_MTX_DIRTY;
        jobj->scale.x = 1.0F;
        jobj->scale.y = 1.0F;
        jobj->scale.z = 1.0F;
    }
    return status;
}

/**
 * @brief Recursively releases all child joints attached to this joint.
 * @param jobj Parent HSD_JObj
 */
void JObjReleaseChild(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if ((child = jobj->child) != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            HSD_JObjUnref(child);
        } else {
            child->parent = NULL;
            HSD_JObjRemoveAll(jobj->child);
        }
        jobj->child = NULL;
    }
    if (jobj->parent != NULL) {
        HSD_JObjReparent(jobj, NULL);
    }
    if (union_type_dobj(jobj)) {
        if (jobj->u.dobj != NULL) {
            HSD_DObjRemoveAll(jobj->u.dobj);
            jobj->u.dobj = NULL;
        }
    }
    if (jobj->robj != NULL) {
        HSD_RObjRemoveAll(jobj->robj);
        jobj->robj = NULL;
    }
    if (jobj->aobj != NULL) {
        HSD_AObjRemove(jobj->aobj);
        jobj->aobj = NULL;
    }
}

/**
 * @brief Class destructor releasing attached DObjs, AObjs, RObjs, matrices, and memory.
 * @param o Object instance to destroy
 */
void JObjRelease(HSD_Class* o)
{
    HSD_JObj* jobj = (HSD_JObj*) o;
    HSD_JOBJ_METHOD(jobj)->release_child(jobj);

    if (HSD_IDGetDataFromTable(NULL, jobj->id, NULL) == jobj) {
        HSD_IDKey id = jobj->id;
        HSD_IDRemoveByIDFromTable(NULL, id);
    }
    if (jobj->scl != NULL) {
        HSD_VecFree(jobj->scl);
    }
    if (jobj->envelopemtx != NULL) {
        HSD_MtxFree(jobj->envelopemtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->release(o);
}

/**
 * @brief Class memory teardown handler clearing class info references.
 * @param info Class info pointer
 */
void JObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdJObj)) {
        ufc_callbacks = NULL;
        current_jobj = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->amnesia(info);
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused3[] = "jobj[%d,%d]";
static char unused4[] = "SKELETON_ROOT ";
static char unused5[] = "SKELETON ";
static char unused6[] = "ENVELOPE_MODEL ";
static char unused7[] = "EFFECTOR ";
static char unused8[] = "  rot(L): ";
static char unused9[] = "  sca(L): ";
static char unused10[] = "  tra(L): ";
static char unused11[] = "  rot(G): ";
static char unused12[] = "  sca(G): ";
static char unused13[] = "  tra(G): ";
#pragma pop
#endif

/**
 * @brief Initializes and registers the HSD_JObj class structure and virtual methods.
 */
void JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdJObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_jobj",
                     sizeof(HSD_JObjInfo), sizeof(HSD_JObj));
    HSD_CLASS_INFO(&hsdJObj)->init = JObjInit;
    HSD_CLASS_INFO(&hsdJObj)->release = JObjRelease;
    HSD_CLASS_INFO(&hsdJObj)->amnesia = JObjAmnesia;
    HSD_JOBJ_INFO(&hsdJObj)->make_mtx = HSD_JObjMakeMatrix;
    HSD_JOBJ_INFO(&hsdJObj)->make_pmtx = HSD_JObjMakePositionMtx;
    HSD_JOBJ_INFO(&hsdJObj)->disp = HSD_JObjDispSub;
    HSD_JOBJ_INFO(&hsdJObj)->load = JObjLoad;
    HSD_JOBJ_INFO(&hsdJObj)->release_child = JObjReleaseChild;
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static u32 unused14[6] = { 0 };
#pragma pop
#endif
