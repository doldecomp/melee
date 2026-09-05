#include "ftCo_SquatWait.h"

#include "ftCo_AppealS.h"
#include "ftCo_Attack1.h"
#include "ftCo_Attack100.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Dash.h"
#include "ftCo_Guard.h"
#include "ftCo_Jump.h"
#include "ftCo_Pass.h"
#include "ftCo_SquatRv.h"

#include "forward.h"
#include <melee/ft/forward.h>

#include <stdbool.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftwaitanim.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCLink/ftclink.h>
#include <melee/ft/kinds/ftLink/ftlinkattackair.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

/* 0D62C4 */ static void fn_800D62C4(Fighter_GObj* gobj);

bool ftCo_SquatWait_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->input.lstick.y < -p_ftCommonData->x90) {
        fn_800D62C4(gobj);
        return true;
    }

    return false;
}

static inline void ftCo_SquatWait_Enter_inline(Fighter_GObj* gobj,
                                               MotionFlags flags, bool arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftCo_MS_SquatWait, flags, 0.0F, 1.0F, 0.0F,
                              NULL);

    if (ftCo_8008A698(fp) && ftData_80085FD4(fp, ftCo_SM_SquatWaitItem)->x8) {
        ftCo_8008A6D8(gobj, ftCo_SM_SquatWaitItem);
    }

    if (arg2) {
        ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
    }

    switch (GET_FIGHTER(gobj)->kind) { /* irregular */
    case FTKIND_LINK:
        ftLk_AttackAir_800EB3BC(gobj);
        return;
    case FTKIND_CLINK:
        ftCl_Init_8014919C(gobj);
        return;
    default:
        return;
    }
}

void fn_800D62C4(Fighter_GObj* gobj)
{
    ftCo_SquatWait_Enter_inline(gobj, Ft_MF_None, true);
}

void ftCo_800D638C(Fighter_GObj* gobj)
{
    ftCo_SquatWait_Enter_inline(gobj, Ft_MF_SkipNametagVis, false);
}

void ftCo_SquatWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8008A7A8(gobj, fp->ft_data->x28);
}

void ftCo_SquatWait_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_80099F9C(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF(ftCo_SquatRv_CheckInput(gobj));
}

void ftCo_SquatWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftCo_SquatWait_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
