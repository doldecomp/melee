#include <platform.h>

#include "ftCo_CaptureYoshi.h"

#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

void ftCo_800BBB8C(Fighter_GObj* gobj, Fighter_GObj* attacker_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* attacker_fp = GET_FIGHTER(attacker_gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = attacker_gobj;
    fp->victim_gobj = attacker_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = -attacker_fp->facing_dir;
    ftCo_800DB368(attacker_fp, fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureYoshi, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureYoshi_Anim(Fighter_GObj* gobj) {}

void ftCo_CaptureYoshi_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureYoshi_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureYoshi_Coll(Fighter_GObj* gobj) {}
