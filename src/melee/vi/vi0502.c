#include <baselib/forward.h>

#include "vi0502.h"

#include "baselib/gobj.h"
#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "vi/vi.h"

#include <dolphin/gx/types.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/wobj.h>

void vi_8031E304(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi0502_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (190.0f == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(14, 0);
        lbAudioAx_800237A8(430009, 0x7F, 0x40);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}
