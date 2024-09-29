#include <platform.h>

#include <dolphin/mtx/forward.h>

#include "ftCo_HammerWalk.h"

#include "ftCo_0C60.h"
#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftchangeparam.h"
#include "ft/ftwalkcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"

/* 0C5614 */ static void ftCo_800C5614(ftCo_GObj* gobj);

bool ftCo_800C55CC(ftCo_GObj* gobj)
{
    if (ftWalkCommon_800DFC70(gobj)) {
        ftCo_800C5614(gobj);
        return true;
    }
    return false;
}

void ftCo_800C5614(ftCo_GObj* gobj)
{
    /// @todo Cannot move below @c fp, which suggests an inline
    u32 flags;
    Fighter* fp = GET_FIGHTER(gobj);
    {
        float accel_mul = 1;
        if (fp->x34_scale.y != 1) {
            accel_mul = ftCo_CalcYScaledKnockback(
                &Fighter_804D6524[0], 1, fp->x34_scale.y, Fighter_804D6524[3]);
        }
        fp->mv.co.walk.accel_mul = accel_mul;
        fp->mv.co.walk.x0 = fp->gr_vel;
    }
    {
        flags = ftCo_800C54C4(fp);
        Fighter_ChangeMotionState(gobj, ftCo_MS_HammerWalk, flags,
                                  ftCo_800C548C(fp), 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
        ftCo_800C4E94(fp);
    }
}

void ftCo_HammerWalk_Anim(ftCo_GObj* gobj)
{
    ftCo_800C4F64(gobj);
}

void ftCo_HammerWalk_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_800C5A50(gobj));
    RETURN_IF(ftCo_800C60C8(gobj));
    RETURN_IF(ftCo_800C4E4C(gobj));
}

void ftCo_HammerWalk_Phys(ftCo_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftCo_HammerWalk_Coll(ftCo_GObj* gobj)
{
    ftCo_HammerWait_Coll(gobj);
}
