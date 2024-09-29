#include <platform.h>

#include "ftCommon/forward.h"

#include "ftCo_CaptureMewtwo.h"

#include "ftCo_Lift.h"
#include "ftCo_ThrownMewtwo.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

static inline void doEnter(ftCo_GObj* gobj, ftCo_GObj* victim_gobj,
                           FtMotionId msid, FtMotionId victim_msid)
{
    ftCo_Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = victim_gobj;
    fp->victim_gobj = victim_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = victim_fp->facing_dir;
    ftCo_800DB368(victim_fp, fp);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0,
                              fp->victim_gobj);
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
    ftCo_800BD0E8(gobj, victim_msid);
}

void ftCo_800BCF18(ftCo_GObj* gobj, ftCo_GObj* victim_gobj)
{
    doEnter(gobj, victim_gobj, ftCo_MS_CaptureMewtwo, ftCo_MS_ThrownMewtwo);
}

void ftCo_800BD000(ftCo_GObj* gobj, ftCo_GObj* victim_gobj)
{
    doEnter(gobj, victim_gobj, ftCo_MS_CaptureMewtwoAir,
            ftCo_MS_ThrownMewtwoAir);
}
