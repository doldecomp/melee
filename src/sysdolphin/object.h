#ifndef _object_h_
#define _object_h_

#include "class.h"

#define HSD_OBJ_NOREF -1

#define HSD_OBJECT_INFO(o) (o.parent.parent)
#define HSD_OBJECT_METHOD(o) (o->parent.parent.class_info)
#define HSD_OBJECT_PARENT_INFO(o) ((o)->parent.parent.head.parent)

typedef struct _HSD_Obj {
    struct _HSD_Class parent;
    u16 ref_count;
    u16 ref_count_individual;
} HSD_Obj;

typedef struct _HSD_ObjInfo {
    struct _HSD_ClassInfo parent;
} HSD_ObjInfo;

#endif
