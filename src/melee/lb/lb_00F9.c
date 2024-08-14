#include "lb_00F9.h"

#include <baselib/jobj.h>

/* 011B74 */ static void lb_80011B74(HSD_DObj* dobj, u32 flags);

static inline bool checkJObjFlags(HSD_JObj* jobj)
{
    return jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? false : true;
}

void lb_8000F9F8(HSD_JObj* jobj)
{
    if (HSD_JObjGetChild(jobj) != NULL) {
        lb_80011C18(HSD_JObjGetChild(jobj), JOBJ_UNK_B26);
    }
    if (checkJObjFlags(jobj) && HSD_JObjGetDObj(jobj) != NULL) {
        lb_80011B74(HSD_JObjGetDObj(jobj), JOBJ_UNK_B26);
    }
}

/*
@note: The number of HSD_JObjs that get passed into arg1 is the number of
variable arguments passed until -1 is passed. lb_80011E24
*/
