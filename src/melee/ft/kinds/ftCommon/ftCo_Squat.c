#include "ftCo_Squat.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

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
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCommon/ftCo_SquatWait.h"
#include "mp/mpcoll.h"

#include <melee/ft/kinds/ftCommon/ftCo_Attack1.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/kinds/ftCommon/ftCo_Guard.h>
#include <melee/ft/kinds/ftCommon/ftCo_SpecialS.h>

/* 0D600C */ static void ftCo_Squat_Enter(Fighter_GObj* gobj);

bool ftCo_Squat_CheckInput(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y < -p_ftCommonData->x90) {
        return true;
    }

    return false;
}

bool fn_800D5F84(Fighter_GObj* gobj)
{
    return ftCo_Squat_CheckInput(gobj);
}

bool ftCo_800D5FB0(Fighter_GObj* gobj)
{
    if (ftCo_Squat_CheckInput(gobj)) {
        ftCo_Squat_Enter(gobj);
        return true;
    }

    return false;
}

void ftCo_Squat_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftCo_MS_Squat, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.co.squat.x0 = 0;
    ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
}

void ftCo_Squat_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800D638C(gobj);
    }
}

static inline bool ftCo_Squat_IASA_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.squat.x0 && fp->mv.co.squat.x4) {
        fp->mv.co.squat.x4 -= 1.0F;

        if (!fp->mv.co.squat.x4 && mpColl_IsOnPlatform(&fp->coll_data)) {
            ftCo_8009A228(gobj);
            return true;
        }
    }

    return false;
}

void ftCo_Squat_IASA(Fighter_GObj* gobj)
{
    PAD_STACK(8);

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
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
    RETURN_IF(ftCo_Squat_IASA_inline(gobj));
}

void ftCo_Squat_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Squat_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
