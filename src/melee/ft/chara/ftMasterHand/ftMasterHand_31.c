#include "ftMasterHand_31.h"

#include "ft/ft_877.h"
#include "ft/ftcommon.h"

// 80155A58 152638
// https://decomp.me/scratch/Q3fan
void ftMasterHand_80155A58(HSD_GObj* gobj_1, HSD_GObj* gobj_2)
{
    Fighter* ft_1;
    Fighter* ft_2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ft_1 = gobj_1->user_data;
    ft_2 = gobj_2->user_data;
    ftCommon_8007DB58(gobj_1);
    func_8009750C(gobj_1);
    func_800DD168(gobj_1);
    ft_1->x1A5C = gobj_2;
    ft_1->x1A58_interactedFighter = gobj_2;
    ft_1->x221B_b5 = 0;
    ft_1->x221B_b7 = 0;
    ft_1->facing_dir = ft_2->facing_dir;
    ftCommon_8007DBCC(ft_1, 0, func_800DA824(ft_2));
    func_800DB368(ft_2, ft_1);
    ft_1->cb.x21B0_callback_Accessory1 = &func_800DB464;
    ftCommon_8007D5D4(ft_1);
    Fighter_ChangeMotionState(gobj_1, 0x147, 0, 0, 0.0f, 1.0f, 0.0f);
    ft_1->x221E_flag.bits.b0 = 1;
    ft_1->x2220_flag.bits.b3 = 1;
    ftCommon_8007E2F4(ft_1, 0x1FFU);
    ftAnim_8006EBA4(gobj_1);
    ftCommon_8007E2FC(gobj_1);
}
