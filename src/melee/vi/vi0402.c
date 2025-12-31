#include "vi/vi0402.h"

#include <placeholder.h>

#include "gm/gm_unsplit.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "sc/types.h"
#include "vi/vi.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

extern SceneDesc* un_804D6F68;

void un_8031D6E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031D708(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    for (i = 0; un_804D6F68->models[i] != NULL; i++) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F68->models[i]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, un_804D6F68->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(gobj, un_8031D6E4, 0x17);
    }

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x10000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// #vi_8031D80C
void vi_8031D80C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;

    if (aobj->curr_frame == aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

/// #un_8031D858_OnEnter

void vi_8031D9C4_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031D9E4(int arg0, int arg1, int arg2)
{
    M2C_FIELD(&un_804D6F84, u8*, 0) = arg0;
    M2C_FIELD(&un_804D6F84, u8*, 1) = arg1;
    M2C_FIELD(&un_804D6F84, u8*, 3) = arg2;
}
