#include <platform.h>

#include "ftCommon/forward.h"

#include "ftMh_CaptureMasterHand.h"

#include "ftMh_BackDisappear.h"
#include "ftMh_CaptureDamageMasterHand.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

void ftMh_CaptureMasterHand_Anim(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_Coll(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_80155B80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageMasterHand, 0, 0, 1,
                              0, 0);
    fp->x221E_b0 = true;
    fp->x2220_b3 = true;
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 511);
    fp->x2220_b3 = true;
    ftAnim_8006EBA4(gobj);
}

void ftMh_CaptureDamageMasterHand_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DC08(fp, p_ftCommonData->x3A8);
    if (fp->grab_timer <= 0) {
        ftMh_CaptureDamageMasterHand_80155C94(gobj);
        ftMh_MS_381_8015483C(fp->victim_gobj);
    }
}
