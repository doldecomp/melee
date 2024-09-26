#include "lb_00F9.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 011B74 */ static void lb_80011B74(HSD_DObj* dobj, u32 flags);
/* 013BB0 */ bool lb_80013BB0(void);

/* 4D63B4 */ static enum_t lb_804D63B4;

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

/// #lb_8000FA94

/// #lb_8000FCDC

/// #lb_8000FD18

/// #lb_8000FD48

/// #lb_800100B0

/// #lb_800101C8

/// #lb_800103B8

/// #lb_800103D8

/// #lb_8001044C

/// #lb_800115F4

/// #lb_80011710

/// #lb_800117F4

/// #lb_800119DC

/// #lb_80011A50

enum_t lb_80011ABC(void)
{
    return lb_804D63B4;
}

/// #lb_80011AC4

/// #lb_80011B74

/// #lb_80011C18

/**
 * @note: The number of HSD_JObjs that get passed into arg1 is the number of
 * variable arguments passed until -1 is passed.
 */
/// #lb_80011E24

/// #lb_8001204C

/// #lb_800121FC

/// #lb_800122C8

/// #lb_800122F0

/// #lb_8001271C

/// #lb_8001285C

/// #lb_80012994

/// #fn_80013614

/// #fn_800138AC

void lb_800138CC(HSD_GObj* gobj, int arg1)
{
    UNK_T data = HSD_GObjGetUserData(gobj);
    M2C_FIELD(data, int*, 0x18) = arg1;
}

/// #lb_800138D8

/// #lb_800138EC

/// #lb_80013B14

bool lb_80013BB0(void)
{
    return true;
}

/// #lb_80013BB8

/// #lb_80013BE4

/// #lb_80013C18

/// #lb_80013D68

/// #lb_80013E3C

/// #lb_80013F78

/// #lb_80013FF0

/// #lb_80014014

/// #lb_800140F8

/// #lb_80014234

/// #lb_80014258

/// #lb_80014498

/// #lb_800144C8

/// #lb_80014534

/// #lb_80014574

/// #lb_800145C0

/// #lb_800145F4

/// #lb_80014638

/// #lb_80014770

/// #lb_800149E0
