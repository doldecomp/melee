#ifndef _wobj_h_
#define _wobj_h_

#include <global.h>

#include "sysdolphin/baselib/object.h"
#include "sysdolphin/baselib/aobj.h"

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

extern HSD_WObjInfo hsdWObj;

#define HSD_WOBJ_INFO(i) ((HSD_WObjInfo*)(i))
#define HSD_WOBJ_METHOD(o) HSD_WOBJ_INFO(HSD_OBJECT_METHOD(o))

void HSD_WObjRemoveAnim(HSD_WObj* wobj);
void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame);
void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim);
void HSD_WObjInterpretAnim(HSD_WObj* wobj);
void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc);
HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc);
void WObjSetupPosition(HSD_WObj* wobj);
void HSD_WObjSetPosition(HSD_WObj*, Vec*);
void HSD_WObjSetPositionX(HSD_WObj*, f32);
void HSD_WObjSetPositionY(HSD_WObj*, f32);
void HSD_WObjSetPositionZ(HSD_WObj*, f32);
void HSD_WObjGetPosition(HSD_WObj*, Vec*);
HSD_WObj* HSD_WObjAlloc();

#endif
