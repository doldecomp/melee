#ifndef _dobj_h_
#define _dobj_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/mobj.h>

typedef struct _HSD_DObj {
    HSD_Class parent;
    struct _HSD_DObj* next; //0x04
    struct _HSD_MObj* mobj; //0x08
    struct _HSD_PObj* pobj; //0x0C
    struct _HSD_AObj* aobj; //0x10
    u32 flags; //0x14
} HSD_DObj;

typedef struct _HSD_DObjDesc {
    char* class_name;
    struct _HSD_DObjDesc* next;
    struct _HSD_MObjDesc* mobjdesc;
    struct _HSD_PObjDesc* pobjdesc;
} HSD_DObjDesc;

typedef struct _HSD_DObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode); //0x3C
    int (*load)(HSD_DObj* dobj, HSD_DObjDesc* desc); //0x40
} HSD_DObjInfo;

typedef struct _HSD_ShapeAnimDObj {
    struct _HSD_ShapeAnimDObj* next;
    struct _HSD_ShapeAnim* shapeanim;
} HSD_ShapeAnimDObj;

#define HSD_DOBJ(o) ((HSD_DObj*)(o))
#define HSD_DOBJ_INFO(i) ((HSD_DObjInfo*)(i))
#define HSD_DOBJ_METHOD(o) HSD_DOBJ_INFO(HSD_CLASS_METHOD(o))

void HSD_DObjSetCurrent(HSD_DObj* dobj);
u32 HSD_DObjGetFlags(HSD_DObj* dobj);
void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask);
void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim, HSD_ShapeAnimDObj* sh_anim);
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim, HSD_ShapeAnimDObj* shapeanimdobj);
void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);
void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe);
void HSD_DObjAnim(HSD_DObj* dobj);
void HSD_DObjAnimAll(HSD_DObj* dobj);
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc) ;
void HSD_DObjRemoveAll(HSD_DObj* dobj);
HSD_DObj* HSD_DObjAlloc(void);
void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjDisp(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

#endif
