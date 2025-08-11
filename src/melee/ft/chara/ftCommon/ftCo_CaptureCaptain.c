#include <platform.h>

#include "ftCo_CaptureCaptain.h"

#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include <common_structs.h>

void ftCo_8009CA0C(Fighter_GObj* gobj, Fighter_GObj* vic_gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    Fighter* vic_fp = vic_gobj->user_data;
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->victim_gobj = fp->x1A5C = vic_gobj;
    fp->x221B_b5 = false;
    fp->facing_dir = -vic_fp->facing_dir;
    if (fp->ground_or_air == GA_Air) {
        ftCo_800DB368(vic_fp, fp);
        fp->x221B_b7 = false;
    } else {
        fp->x221B_b7 = true;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCaptain, Ft_MF_None, 0, 1,
                              0, fp->victim_gobj);
    if (!fp->x221B_b7) {
        fp->accessory1_cb = ftCo_800DB464;
    }
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureCaptain_Anim(Fighter_GObj* gobj) {}

void ftCo_CaptureCaptain_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureCaptain_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureCaptain_Coll(Fighter_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083B68(gobj);
    }
}
