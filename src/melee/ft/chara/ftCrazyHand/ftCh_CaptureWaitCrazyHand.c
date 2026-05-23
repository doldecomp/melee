#include "ftCh_CaptureWaitCrazyHand.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_GrabUnk1_8015B778(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x152, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 511);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
}

void ftCh_GrabUnk1_8015B800(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->invisible = false;
    fp->facing_dir = -fp->facing_dir;
    ftCo_CaptureCut_Enter(gobj);
}

void ftCo_CaptureWaitCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureWaitCrazyHand_Coll(HSD_GObj* gobj) {}
