#ifndef SYSDOLPHIN_BASELIB_DOBJ_H
#define SYSDOLPHIN_BASELIB_DOBJ_H

#include <platform.h>

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/class.h"
#include "baselib/fobj.h"
#include "baselib/mobj.h"

#include <dolphin/mtx.h>

#define DOBJ_HIDDEN 0x1

struct HSD_DObj {
    HSD_Class parent;
    HSD_DObj* next; // 0x04
    HSD_MObj* mobj; // 0x08
    HSD_PObj* pobj; // 0x0C
    HSD_AObj* aobj; // 0x10
    u32 flags;      // 0x14
};

struct HSD_DObjDesc {
    char* class_name;
    HSD_DObjDesc* next;
    HSD_MObjDesc* mobjdesc;
    HSD_PObjDesc* pobjdesc;
};

struct HSD_DObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode); // 0x3C
    int (*load)(HSD_DObj* dobj, HSD_DObjDesc* desc);                  // 0x40
};

struct HSD_ShapeAnimDObj {
    HSD_ShapeAnimDObj* next;
    HSD_ShapeAnim* shapeanim;
};

#define HSD_DOBJ(o) ((HSD_DObj*) (o))
#define HSD_DOBJ_INFO(i) ((HSD_DObjInfo*) (i))
#define HSD_DOBJ_METHOD(o) HSD_DOBJ_INFO(HSD_CLASS_METHOD(o))

void HSD_DObjSetCurrent(HSD_DObj* dobj);
u32 HSD_DObjGetFlags(HSD_DObj* dobj);
void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask);
void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags);
void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim,
                     HSD_ShapeAnimDObj* sh_anim);
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                        HSD_ShapeAnimDObj* shapeanimdobj);
void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);
void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe);
void HSD_DObjAnim(HSD_DObj* dobj);
void HSD_DObjAnimAll(HSD_DObj* dobj);
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc);
void HSD_DObjRemoveAll(HSD_DObj* dobj);
HSD_DObj* HSD_DObjAlloc(void);
void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjDisp(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

void HSD_DObjRemove(HSD_DObj* dobj);
void HSD_DObjSetDefaultClass(HSD_ClassInfo* info);
void forceStringAllocation(HSD_DObj* dobj, HSD_MObj* mobj);

#endif
