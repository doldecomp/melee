#ifndef _wobj_h_
#define _wobj_h_

#include "global.h"

#include "object.h"
#include "aobj.h"

typedef struct _HSD_WObj {
    HSD_Obj parent;
    u32 flags;
    Vec pos;
    struct _HSD_AObj* aobj;
    struct _HSD_RObj* robj;
} HSD_WObj;

typedef struct _HSD_WObjDesc {
    char* class_name;
    Vec pos;
    struct _HSD_RObjDesc* robjdesc;
    struct _HSD_WObjDesc* next;
} HSD_WObjDesc;

typedef struct _HSD_WObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_WObj* wobj, HSD_WObjDesc* desc);
} HSD_WObjInfo;

typedef struct _HSD_WObjAnim {
    struct _HSD_AObjDesc* aobjdesc;
    struct _HSD_RObjAnimJoint* robjanim;
} HSD_WObjAnim;

void HSD_WObjRemoveAnim(HSD_WObj* wobj);
void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame);

#endif
