#include "sysdolphin/baselib/jobj.h"

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
