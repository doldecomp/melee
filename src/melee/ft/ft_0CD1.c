#include "ft_0CD1.h"

#include "fighter.h"
#include "ftswing.h"

#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftCo_800CD140(Fighter_GObj* gobj, int arg1, int arg2, int arg3,
                   float arg4)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    Fighter_ChangeMotionState(gobj, arg1, arg2, 0.0f, arg4, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.swing.x0 = 1;
    fp->mv.co.swing.x4 = arg3;
    ftCommon_8007E79C(gobj, 1);
}

void ftCo_800CD1BC(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ftCo_800CD204(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int y;
    if ((fp->input.held_inputs & HSD_PAD_A) == 0) {
        fp->mv.co.swing.x0 = 0;
    }
    if (fp->throw_flags_b3) {
        fp->throw_flags_b3 = 0;
        y = 1;
    } else {
        y = 0;
    }
    if (y && fp->mv.co.swing.x0 != 0) {
        ftCo_Attack_800CCF58(gobj, 3);
    }
}

void ftCo_800CD278(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.swing.x4 != 4) {
        ft_80084FA8(gobj);
    } else {
        ft_80085030(gobj, p_ftCommonData->x420 * fp->co_attrs.gr_friction,
                    fp->facing_dir);
    }
}

void ftCo_800CD2C4(Fighter_GObj* gobj, void (*cb)(Fighter_GObj*))
{
    if (ft_800827A0(gobj) == 0) {
        cb(gobj);
        ftCo_Fall_Enter(gobj);
    }
}

void ft_800CD31C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        ftCommon_8007E7E4(gobj, 1);
    }
}
