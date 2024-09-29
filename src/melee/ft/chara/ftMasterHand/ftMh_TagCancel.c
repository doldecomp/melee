#include <platform.h>

#include "ftCommon/forward.h"

#include "ftMh_TagCancel.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Lift.h"

void ftMh_MS_388_80155A58(HSD_GObj* gobj_1, HSD_GObj* gobj_2)
{
    Fighter* ft_1;
    Fighter* ft_2;

    u8 _[8];

    ft_1 = gobj_1->user_data;
    ft_2 = gobj_2->user_data;
    ftCommon_8007DB58(gobj_1);
    ftCo_8009750C(gobj_1);
    ftCo_800DD168(gobj_1);
    ft_1->x1A5C = gobj_2;
    ft_1->victim_gobj = gobj_2;
    ft_1->x221B_b5 = false;
    ft_1->x221B_b7 = false;
    ft_1->facing_dir = ft_2->facing_dir;
    ftCommon_8007DBCC(ft_1, 0, ftCo_800DA824(ft_2));
    ftCo_800DB368(ft_2, ft_1);
    ft_1->accessory1_cb = ftCo_800DB464;
    ftCommon_8007D5D4(ft_1);
    Fighter_ChangeMotionState(gobj_1, ftCo_MS_CaptureMasterHand, 0, 0, 1, 0,
                              0);
    ft_1->x221E_b0 = true;
    ft_1->x2220_flag.b3 = true;
    ftCommon_8007E2F4(ft_1, 511);
    ftAnim_8006EBA4(gobj_1);
    ftCommon_8007E2FC(gobj_1);
}
