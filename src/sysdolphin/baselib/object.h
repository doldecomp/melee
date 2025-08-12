#ifndef _object_h_
#define _object_h_

#include <platform.h>

#include "baselib/class.h"
#include "baselib/debug.h"

#include "baselib/forward.h"

#define HSD_OBJ_NOREF ((u16) - 1)

#define HSD_OBJ(o) ((HSD_Obj*) o)
#define HSD_OBJECT_INFO(o) (o.parent.parent)
#define HSD_OBJECT_METHOD(o) (o->parent.parent.class_info)
#define HSD_OBJECT_PARENT_INFO(o) ((o)->parent.parent.head.parent)

typedef enum _HSD_Type {
    AOBJ_TYPE = 1,
    COBJ_TYPE,
    DOBJ_TYPE,
    FOBJ_TYPE,
    FOG_TYPE,
    JOBJ_TYPE,
    LOBJ_TYPE,
    MOBJ_TYPE,
    POBJ_TYPE,
    ROBJ_TYPE,
    TOBJ_TYPE,
    WOBJ_TYPE,
    RENDER_TYPE,
    CHAN_TYPE,
    TEVREG_TYPE,
    CBOBJ_TYPE,
    HSD_MAX_TYPE,
} HSD_Type;

#define MASK_OF(type) (1 << ((type) - 1))

typedef enum _HSD_TypeMask {
    AOBJ_MASK = MASK_OF(AOBJ_TYPE),
    COBJ_MASK = MASK_OF(COBJ_TYPE),
    DOBJ_MASK = MASK_OF(DOBJ_TYPE),
    FOBJ_MASK = MASK_OF(FOBJ_TYPE),
    FOG_MASK = MASK_OF(FOG_TYPE),
    JOBJ_MASK = MASK_OF(JOBJ_TYPE),
    LOBJ_MASK = MASK_OF(LOBJ_TYPE),
    MOBJ_MASK = MASK_OF(MOBJ_TYPE),
    POBJ_MASK = MASK_OF(POBJ_TYPE),
    ROBJ_MASK = MASK_OF(ROBJ_TYPE),
    TOBJ_MASK = MASK_OF(TOBJ_TYPE),
    WOBJ_MASK = MASK_OF(WOBJ_TYPE),
    RENDER_MASK = MASK_OF(RENDER_TYPE),
    CHAN_MASK = MASK_OF(CHAN_TYPE),
    TEVREG_MASK = MASK_OF(TEVREG_TYPE),
    CBOBJ_MASK = MASK_OF(CBOBJ_TYPE),
    ALL_TYPE_MASK = MASK_OF(HSD_MAX_TYPE) - 1,
} HSD_TypeMask;

struct HSD_Obj {
    struct _HSD_Class parent;
    u16 ref_count;
    u16 ref_count_individual;
};

typedef struct _HSD_ObjInfo {
    struct _HSD_ClassInfo parent;
} HSD_ObjInfo;

extern HSD_ClassInfo hsdObj;

void ObjInfoInit(void);

static inline bool ref_DEC(void* o)
{
    bool ret;
    if ((ret = (HSD_OBJ(o)->ref_count == HSD_OBJ_NOREF))) {
        return ret;
    }
    return HSD_OBJ(o)->ref_count-- == 0;
}

static inline void ref_INC(void* o)
{
    if (o != NULL) {
        HSD_OBJ(o)->ref_count++;
        HSD_ASSERT(93, HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF);
    }
}

static inline int ref_CNT(void* o)
{
    if (HSD_OBJ(o)->ref_count == HSD_OBJ_NOREF) {
        return -1;
    } else {
        return HSD_OBJ(o)->ref_count;
    }
}

static inline int iref_CNT(void* o)
{
    return HSD_OBJ(o)->ref_count_individual;
}

static inline bool iref_DEC(void* o)
{
    bool ret;
    if ((ret = (HSD_OBJ(o)->ref_count_individual == 0))) {
        return ret;
    }
    HSD_OBJ(o)->ref_count_individual -= 1;
    return HSD_OBJ(o)->ref_count_individual == 0;
}

static inline void iref_INC(void* o)
{
    HSD_OBJ(o)->ref_count_individual++;
    HSD_ASSERT(158, HSD_OBJ(o)->ref_count_individual != 0);
}

#endif
