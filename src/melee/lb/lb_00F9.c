#include "lb_00F9.static.h"

#include "lb/types.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/cobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <melee/sc/types.h>

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

UNK_T lb_804D63A0;
UNK_T lb_804D63A8;

void lb_8000FCDC(void)
{
    lb_804D63A0 = HSD_MemAlloc(0xBE00);
    lb_804D63A8 = HSD_MemAlloc(0x1C0);
    lb_8000FA94();
}

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

HSD_LObj* lb_80011AC4(LightList** list)
{
    HSD_LObj* prev;
    HSD_LObj* curr;
    HSD_LObj* first;
    HSD_LightAnim** temp_r4;

    prev = NULL;
    while (*list != NULL) {
        curr = HSD_LObjLoadDesc((*list)->desc);
        temp_r4 = (*list)->anims;
        if (temp_r4 != NULL) {
            HSD_LObjAddAnimAll(curr, temp_r4[0]);
        }
        if (prev != NULL) {
            if (prev == NULL) {
                __assert("lobj.h", 0x136, "lobj");
            }
            prev->next = curr;
        } else {
            first = curr;
        }
        prev = curr;
        list++;
    }
    return first;
}

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
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x18 = arg1;
}

void lb_800138D8(HSD_GObj* gobj, s8 arg1)
{
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x12 = 1;
    data->x11 = arg1;
}

/// #lb_800138EC

HSD_CObj* lb_80013B14(HSD_CameraDescPerspective* desc)
{
    HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc* ) desc);
    Scissor scissor;

    if (HSD_CObjGetProjectionType(cobj) == 1 &&
        HSD_CObjGetAspect(cobj) == 1.18F) {
        HSD_CObjSetAspect(cobj, 1.2173333F);
    }
    HSD_CObjGetScissor(cobj, &scissor);
    if (scissor.right > 0x280) {
        scissor.right = 0x280;
    }
    if (scissor.bottom > 0x1E0) {
        scissor.bottom = 0x1E0;
    }
    HSD_CObjSetScissor(cobj, &scissor);
    return cobj;
}

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
