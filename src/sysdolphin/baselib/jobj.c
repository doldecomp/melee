#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/mtx.h"

void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };

void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }

    switch (HSD_JObjMtxIsDirty(jobj)) {
        case FALSE:
            if ((jobj->flags & USER_DEF_MTX)){
                if ((jobj->flags & MTX_INDEP_PARENT) == 0 && jobj->parent != NULL && HSD_JObjMtxIsDirty(jobj->parent)){
                    jobj->flags |= MTX_DIRTY;
                }
            }
            else if (jobj->parent != NULL && (jobj->parent->flags & MTX_DIRTY) != 0
                || (jobj->flags & EFFECTOR) == JOINT1
                || (jobj->flags & EFFECTOR) == JOINT2
                || (jobj->flags & EFFECTOR) == EFFECTOR
                || jobj->robj != NULL) {
                    jobj->flags |= MTX_DIRTY;
            }
        break;
    }
}

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
    if (!(jobj->flags & MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void HSD_JObjResetRST(HSD_JObj* jobj, HSD_Joint* joint)
{
    if (jobj == NULL || joint == NULL) {
        return;
    }
    JObjResetRST(jobj, joint);
    if (!(jobj->flags & 0x1000)) {
        HSD_JObj* child_jobj = jobj->child;
        HSD_Joint* child_joint = joint->child;
        while (child_jobj != NULL) {
            HSD_JObjResetRST(child_jobj, child_joint);
            child_jobj = child_jobj->next;
            child_joint = child_joint != NULL ? child_joint->next : NULL;
        }
    }
}

extern char lbl_804D5DB0[8];
void func_8036EFAC(HSD_JObj* jobj, void (*cb)(HSD_JObj*, void*, u32), void* args)
{
    u32 type;

    if (jobj == NULL) {
        return;
    }
    if (jobj->parent == NULL) {
        __assert(lbl_804D5DB0, 0xAE, "jobj->parent");
    }
    type = jobj->parent->child == jobj ? 1 : 2;
    if (cb != NULL) {
        cb(jobj, args, type);
    }
    if (!(jobj->flags & 0x1000)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            func_8036EFAC(child, cb, args);
            child = child->next;
        }
    }
}

void func_8036F0F0(HSD_JObj* jobj, void (*cb)(HSD_JObj*, void*, u32), void* args)
{
    if (jobj == NULL) {
        return;
    }
    if (cb != NULL) {
        cb(jobj, args, 0);
    }
    if (!(jobj->flags & 0x1000)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            func_8036EFAC(child, cb, args);
            child = child->next;
        }
    }
}

inline BOOL has_scl(HSD_JObj* jobj)
{
    BOOL result = FALSE;
    if (jobj != NULL && jobj->scl != NULL)
        result = TRUE;
    return result;
}

void HSD_JObjMakeMatrix(HSD_JObj* jobj)
{
    Vec* scl;

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
        HSD_MtxSRTQuat(jobj->mtx, &jobj->scale, &jobj->rotate, &jobj->translate, scl);
    } else {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRT(jobj->mtx, &jobj->scale, (Vec*) &jobj->rotate, &jobj->translate, scl);
    }
    if (jobj->parent != NULL) {
        PSMTXConcat(jobj->parent->mtx, jobj->mtx, jobj->mtx);
    }
    if (jobj->aobj != NULL && jobj->aobj->hsd_obj != NULL) {
        Vec vec;
        HSD_JObj* aobj_jobj = (HSD_JObj*) jobj->aobj->hsd_obj;
        HSD_JObjSetupMatrix((HSD_JObj*) jobj->aobj->hsd_obj);
        PSMTXMUltiVec(aobj_jobj->mtx, &jobj->translate, &vec);
        jobj->mtx[0][3] = vec.x;
        jobj->mtx[1][3] = vec.y;
        jobj->mtx[2][3] = vec.z;
    }
}

void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags)
{
    BOOL has_dobj;
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjRemove(jobj->aobj);
            jobj->aobj = NULL;
        }
        if (jobj->flags & 0x4020) {
            has_dobj = FALSE;
        } else {
            has_dobj = TRUE;
        }
        if (has_dobj) {
            HSD_DObjRemoveAnimAllByFlags(jobj->u.dobj, flags);
        }
        HSD_RObjRemoveAnimAllByFlags(jobj->robj, flags);
    }
}

void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 arg1)
{
    if (jobj != NULL) {
        HSD_JObjRemoveAnimByFlags(jobj, arg1);
        if (!(jobj->flags & 0x1000)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjRemoveAnimAllByFlags(child, arg1);
                child = child->next;
            }
        }
    }
}

void HSD_JObjRemoveAnim(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimByFlags(jobj, 0x7FF);
}

void HSD_JObjRemoveAnimAll(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimAllByFlags(jobj, 0x7FF);
}

void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    BOOL has_dobj;
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjReqAnim(jobj->aobj, frame);
        }
        if (jobj->flags & 0x4020) {
            has_dobj = FALSE;
        } else {
            has_dobj = TRUE;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->u.dobj, frame, flags);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, flags, frame);
    }
}

void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    if (jobj != NULL) {
        HSD_JObjReqAnimByFlags(jobj, flags, frame);
        if (!(jobj->flags & 0x1000)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjReqAnimAllByFlags(child, flags, frame);
                child = child->next;
            }
        }
    }
}

void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 0x7FF, frame);
}

void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame);
}

void JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == NULL || aobj->fobj == NULL) {
        return;
    }
    fobj_ptr = &aobj->fobj;
    while ((fobj = *fobj_ptr) != NULL) {
        if (fobj->obj_type == 0xC) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
        fobj_ptr = &fobj->next;
    }
}
