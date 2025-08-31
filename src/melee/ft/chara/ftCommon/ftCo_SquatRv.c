#include "ftCo_SquatRv.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Walk.h"

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

/* 0D6620 */ static void ftCo_SquatRv_Enter(Fighter_GObj* gobj);

bool ftCo_SquatRv_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y > -p_ftCommonData->x94) {
        ftCo_SquatRv_Enter(gobj);
        return true;
    }

    return false;
}

void ftCo_SquatRv_Enter(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_SquatRv, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
}

void ftCo_SquatRv_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_SquatRv_IASA(Fighter_GObj* gobj)
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
    RETURN_IF(ftCo_Walk_CheckInput(gobj));
}

void ftCo_SquatRv_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_SquatRv_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
