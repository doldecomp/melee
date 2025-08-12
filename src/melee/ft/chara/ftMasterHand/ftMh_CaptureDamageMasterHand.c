#include "ftMasterHand/ftMh_CaptureDamageMasterHand.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

void ftMh_CaptureDamageMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_Coll(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_80155C94(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitMasterHand, 0, 0, 1, 0,
                              0);
    fp->x221E_b0 = true;
    ftCommon_8007E2F4(fp, 511);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
}
