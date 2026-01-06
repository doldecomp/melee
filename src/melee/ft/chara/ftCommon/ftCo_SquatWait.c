#include "ftCo_SquatWait.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftwaitanim.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCLink/ftCl_Init.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftCommon/ftCo_SquatRv.h"
#include "ftLink/ftLk_AttackAir.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

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
