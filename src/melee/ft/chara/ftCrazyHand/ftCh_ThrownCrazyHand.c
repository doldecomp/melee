#include "ftCh_ThrownCrazyHand.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_GrabUnk1_8015B850(HSD_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    fp->facing_dir = victim_fp->facing_dir;
    fp->mv.ch.unk4.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x153, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->invisible = false;
    fp->accessory1_cb = ftCo_800DE508;
    ftCommon_8007E2F4(fp, 511);
    ftAnim_8006EBA4(gobj);
}

void ftCo_ThrownCrazyHand_Anim(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_IASA(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Phys(HSD_GObj* gobj) {}

void ftCo_ThrownCrazyHand_Coll(HSD_GObj* gobj) {}
