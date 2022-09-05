#ifndef _aobj_h_
#define _aobj_h_

#include <dolphin/types.h>

#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/objalloc.h>

#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/list.h>

#define AOBJ_REWINDED (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE (1 << 28)
#define AOBJ_LOOP (1 << 29)
#define AOBJ_NO_ANIM (1 << 30)

typedef enum _AObj_Arg_Type
{
    AOBJ_ARG_A,
    AOBJ_ARG_AF,
    AOBJ_ARG_AV,
    AOBJ_ARG_AU,
    AOBJ_ARG_AO,
    AOBJ_ARG_AOF,
    AOBJ_ARG_AOV,
    AOBJ_ARG_AOU,
    AOBJ_ARG_AOT,
    AOBJ_ARG_AOTF,
    AOBJ_ARG_AOTV,
    AOBJ_ARG_AOTU,
} AObj_Arg_Type;

typedef union _callbackArg {
    f32 f;
    u32 d;
    void* v;
} callbackArg;

typedef struct _HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
    f32 framerate;
    HSD_FObj* fobj;
    struct _HSD_Obj* hsd_obj;
} HSD_AObj;

typedef struct _HSD_AObjDesc {
    u32 flags;
    f32 end_frame;
    HSD_FObjDesc* fobjdesc;
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
void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, void (*func)());
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj, void (*update_func)());
float fmod(float x, float y);
HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc);
void HSD_AObjRemove(HSD_AObj* aobj);
HSD_AObj* HSD_AObjAlloc(void);
void HSD_AObjFree(HSD_AObj* aobj);
void callbackForeachFunc(HSD_AObj *aobj, void *obj, HSD_Type type, void (*func)(), AObj_Arg_Type arg_type, callbackArg *arg);
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);
void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame);
void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame);
void HSD_AObjSetCurrentFrame(HSD_AObj* aobj, f32 frame);
void _HSD_AObjForgetMemory(void);

inline f32 HSD_AObjGetEndFrame(HSD_AObj* aobj) {
    if (!aobj) {
        __assert("aobj.h", 0xAAU, "aobj");
    }
    return aobj->end_frame;
}

#endif
