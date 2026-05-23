#include "ftCh_CaptureCrazyHand.h"

#include "ftCh_Init.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_Attack100.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void fn_8015B548(HSD_GObj* gobj, HSD_GObj* gobj2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2 = GET_FIGHTER(gobj2);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = gobj2;
    fp->victim_gobj = gobj2;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = fp2->facing_dir;
    ftCommon_InitGrab(fp, 0, ftCo_800DA824(fp2));
    ftCo_800DB368(fp2, fp);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x150, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureCrazyHand_Coll(HSD_GObj* gobj) {}
