#ifndef _wobj_h_
#define _wobj_h_

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/object.h>

typedef struct _HSD_WObj {
    HSD_Obj parent;
    u32 flags;
    Vec3 pos;
    HSD_AObj* aobj;
    HSD_RObj* robj;
} HSD_WObj;

typedef struct _HSD_WObjDesc {
    char* class_name;
    Vec3 pos;
    struct _HSD_RObjDesc* robjdesc;
    struct _HSD_WObjDesc* next;
} HSD_WObjDesc;

typedef struct _HSD_WObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_WObj* wobj, HSD_WObjDesc* desc);
} HSD_WObjInfo;

typedef struct _HSD_WObjAnim {
    HSD_AObjDesc* aobjdesc;
    struct _HSD_RObjAnimJoint* robjanim;
} HSD_WObjAnim;

extern HSD_WObjInfo hsdWObj;

#define HSD_WOBJ_INFO(i) ((HSD_WObjInfo*) (i))
#define HSD_WOBJ_METHOD(o) HSD_WOBJ_INFO(HSD_OBJECT_METHOD(o))

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
void HSD_WObjSetDefaultClass(HSD_ClassInfo* info);

#endif
