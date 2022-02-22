#include "sysdolphin/baselib/wobj.h"

#include "sysdolphin/baselib/robj.h"

void WObjInfoInit(void);

HSD_WObjInfo hsdWObj = { WObjInfoInit };

void HSD_WObjRemoveAnim(HSD_WObj* wobj)
{
    if (wobj != NULL) {
        HSD_AObjRemove(wobj->aobj);
        wobj->aobj = NULL;
        HSD_RObjRemoveAnimAll(wobj->robj);
    }
}

void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame)
{
    if (wobj != NULL) {
        HSD_AObjReqAnim(wobj->aobj, frame);
        HSD_RObjReqAnimAll(wobj->robj, frame);
    }
}

void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim)
{
    if (wobj != NULL && anim != NULL) {
        if (wobj->aobj != NULL) {
            HSD_AObjRemove(wobj->aobj);
        }
        wobj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
        HSD_RObjAddAnimAll(wobj->robj, anim->robjanim);
    }
}

/*static*/ void WObjUpdateFunc(void* obj, u32 type, f32* fval)
{
    HSD_WObj* wobj;
    Vec p;
    HSD_JObj* jp;

    wobj = obj;
    if (wobj != NULL) {
        switch (type) {
        case 4: {
            if (*fval < 0.0) {
                *fval = 0.0;
            }
            if (1.0 < *fval) {
                *fval = 1.0;
            }

            if (wobj->aobj == NULL) {
                __assert("wobj.c", 148, "wobj->aobj");
            }

            jp = (HSD_JObj*)wobj->aobj->hsd_obj;
            if (jp == NULL) {
                __assert("wobj.c", 150, "jp");
            }

            if (jp->u.spline == NULL) {
                __assert("wobj.c", 151, "jobj->u.spline");
            }

            splArcLengthPoint(&p, jp->u.spline, *fval);
            HSD_WObjSetPosition(wobj, &p);
            wobj->flags |= 1;
        } break;

        case 5:
            HSD_WObjSetPositionX(wobj, *fval);
            break;

        case 6:
            HSD_WObjSetPositionY(wobj, *fval);
            break;

        case 7:
            HSD_WObjSetPositionZ(wobj, *fval);
            break;
        }
    }
}
