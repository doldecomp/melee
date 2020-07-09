#ifndef _aobj_h_
#define _aobj_h_

#include "global.h"

#include "object.h"
#include "objalloc.h"

#include "fobj.h"
#include "list.h"

#define AOBJ_REWINDED (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE (1 << 28)
#define AOBJ_LOOP (1 << 29)
#define AOBJ_NO_ANIM (1 << 30)

typedef struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
    f32 framerate;
    struct _HSD_FObj* fobj;
    struct _HSD_Obj* hsd_obj;
} HSD_AObj;

typedef struct _HSD_AObjDesc {
    u32 flags;
    f32 end_frame;
    struct _HSD_FObjDesc* fobjdesc;
    u32 obj_id;
} HSD_AObjDesc;

typedef struct _HSD_AnimJoint {
    struct _HSD_AnimJoint* child;
    struct _HSD_AnimJoint* next;
    struct _HSD_AObjDesc* aobjdesc;
    struct _HSD_RObjAnimJoint* robj_anim;
    u32 flags;
} HSD_AnimJoint;

void HSD_AObjInitAllocData(void);
HSD_ObjAllocData* HSD_AObjGetAllocData(void);
u32 HSD_AObjGetFlags(HSD_AObj* aobj);
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags);
void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj);
void HSD_AObjInitEndCallBack(void);
void HSD_AObjInvokeCallBacks(void);
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame);

#endif
