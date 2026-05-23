#include "ftCh_CaptureWaitCrazyHand.h"

#include "ftCh_Init.h"

#include "math.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ft/chara/ftCommon/ftCo_Attack100.h"
#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D4D.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "pl/player.h"

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

