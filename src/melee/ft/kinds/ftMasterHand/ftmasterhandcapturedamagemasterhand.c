#include "ftmasterhandcapturedamagemasterhand.h"

#include <melee/ft/kinds/ftCommon/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftMh_CaptureDamageMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_Coll(HSD_GObj* gobj) {}

void ftMh_CaptureDamageMasterHand_80155C94(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitMasterHand, 0, 0, 1, 0,
                              0);
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 511);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
}
