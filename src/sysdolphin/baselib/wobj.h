#ifndef SYSDOLPHIN_BASELIB_WOBJ_H
#define SYSDOLPHIN_BASELIB_WOBJ_H

#include <platform.h>
#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/class.h"
#include "baselib/object.h"

#include <dolphin/mtx/types.h>

struct HSD_WObj {
    HSD_Obj parent;
    u32 flags;
    Vec3 pos;
    HSD_AObj* aobj;
    HSD_RObj* robj;
};

struct HSD_WObjDesc {
    char* class_name;
    Vec3 pos;
    HSD_RObjDesc* robjdesc;
};

struct HSD_WObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_WObj* wobj, HSD_WObjDesc* desc);
};

struct HSD_WObjAnim {
    HSD_AObjDesc* aobjdesc;
    HSD_RObjAnimJoint* robjanim;
};

extern HSD_WObjInfo hsdWObj;

#define HSD_WOBJ_INFO(i) ((HSD_WObjInfo*) (i))
#define HSD_WOBJ_METHOD(o) HSD_WOBJ_INFO(HSD_OBJECT_METHOD(o))

static inline void HSD_WObjUnref(HSD_WObj* wobj)
{
    if (wobj == NULL) {
        return;
    }

    if (ref_DEC(wobj) != 0) {
        if (wobj != NULL) {
            HSD_OBJECT_METHOD(wobj)->release((HSD_Class*) wobj);
            HSD_OBJECT_METHOD(wobj)->destroy((HSD_Class*) wobj);
        }
    }
}

static inline void HSD_WObjClearFlags(HSD_WObj* wobj, u32 flags)
{
    wobj->flags &= ~flags;
}

void HSD_WObjRemoveAnim(HSD_WObj* wobj);
void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame);
void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim);
void HSD_WObjInterpretAnim(HSD_WObj* wobj);
void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc);
HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc);
void WObjSetupPosition(HSD_WObj* wobj);
void HSD_WObjSetPosition(HSD_WObj*, Vec3*);
void HSD_WObjSetPositionX(HSD_WObj*, f32);
void HSD_WObjSetPositionY(HSD_WObj*, f32);
void HSD_WObjSetPositionZ(HSD_WObj*, f32);
void HSD_WObjGetPosition(HSD_WObj*, Vec3*);
HSD_WObj* HSD_WObjAlloc(void);
void HSD_WObjSetDefaultClass(HSD_ClassInfo* info);

#endif
