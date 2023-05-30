#include <platform.h>

#include "ftCo_CaptureCaptain.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_08A4.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

void ftCo_8009CA0C(ftCo_GObj* gobj, ftCo_GObj* vic_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_Fighter* vic_fp = vic_gobj->user_data;
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
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCaptain, 0U, 0, 1, 0,
                              fp->victim_gobj);
    if (!fp->x221B_b7) {
        fp->cb.x21B0_callback_Accessory1 = ftCo_800DB464;
    }
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_CaptureCaptain_Anim(ftCo_GObj* gobj) {}

void ftCo_CaptureCaptain_IASA(ftCo_GObj* gobj) {}

void ftCo_CaptureCaptain_Phys(ftCo_GObj* gobj) {}

void ftCo_CaptureCaptain_Coll(ftCo_GObj* gobj)
{
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083B68(gobj);
    }
}
