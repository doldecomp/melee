#include "ftMh_ThrownMasterHand.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftMasterHand/types.h"

void ftMh_CaptureWaitMasterHand_80155D1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b0 = 0;
    fp->facing_dir = -fp->facing_dir;
    ftCo_800DC750(gobj);
}

void ftMh_CaptureWaitMasterHand_Anim(HSD_GObj* gobj) {}

void ftMh_CaptureWaitMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_CaptureWaitMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_CaptureWaitMasterHand_Coll(HSD_GObj* gobj) {}

void ftMh_CaptureWaitMasterHand_80155D6C(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);

    fp->facing_dir = victim_fp->facing_dir;
    fp->mv.mh.unk4.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_ThrownMasterHand, 0, 0.0f, 1.0f,
                              0.0f, 0);
    fp->x221E_b0 = 0;
    fp->accessory1_cb = &ftCo_800DE508;
    ftCommon_8007E2F4(fp, 511);
    ftAnim_8006EBA4(gobj);
}

void ftMh_ThrownMasterHand_Anim(HSD_GObj* gobj) {}

void ftMh_ThrownMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_ThrownMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_ThrownMasterHand_Coll(HSD_GObj* gobj) {}
