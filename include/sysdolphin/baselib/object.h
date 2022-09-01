#ifndef _object_h_
#define _object_h_

#include <sysdolphin/baselib/class.h>

#define HSD_OBJ_NOREF -1

#define HSD_OBJ(o) ((HSD_Obj*) o)
#define HSD_OBJECT_INFO(o) (o.parent.parent)
#define HSD_OBJECT_METHOD(o) (o->parent.parent.class_info)
#define HSD_OBJECT_PARENT_INFO(o) ((o)->parent.parent.head.parent)

typedef enum _HSD_Type {
    AOBJ_TYPE = 1,
    COBJ_TYPE = 2,
    DOBJ_TYPE = 3,
    FOBJ_TYPE = 4,
    FOG_TYPE = 5,
    JOBJ_TYPE = 6,
    LOBJ_TYPE = 7,
    MOBJ_TYPE = 8,
    POBJ_TYPE = 9,
    ROBJ_TYPE = 10,
    TOBJ_TYPE = 11,
    WOBJ_TYPE = 12,
    RENDER_TYPE = 13,
    CHAN_TYPE = 14,
    TEVREG_TYPE = 15,
    CBOBJ_TYPE = 16,
    HSD_MAX_TYPE,
} HSD_Type;

typedef struct _HSD_Obj {
    struct _HSD_Class parent;
    u16 ref_count;
    u16 ref_count_individual;
} HSD_Obj;

typedef struct _HSD_ObjInfo {
    struct _HSD_ClassInfo parent;
} HSD_ObjInfo;

extern HSD_ClassInfo hsdObj;

void ObjInfoInit(void);

#endif
