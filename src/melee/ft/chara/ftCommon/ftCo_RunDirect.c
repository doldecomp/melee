#include "ftCo_RunDirect.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_AttackDash.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_Run.h"
#include "ftCommon/ftCo_SpecialS.h"

void ftCo_RunDirect_Anim(Fighter_GObj* gobj)
{
    ftCo_Run_Anim(gobj);
}

void ftCo_RunDirect_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_800D8A38(gobj));

    if (ftCo_AttackDash_CheckInput(gobj)) {
        ftCo_AttackDash_SetMv0(gobj);
        return;
    }

    if (ftCo_80091A4C(gobj)) {
        ftCo_80091B90(gobj, p_ftCommonData->x410);
        ftCo_80091B9C(gobj);
        return;
    }

    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(fn_800CAF78(gobj));
    RETURN_IF(fp->mv.ca.specials.grav <= 0.0F && fn_800CA698(gobj));
    RETURN_IF(ft_8008A244(gobj));
}

void ftCo_RunDirect_Phys(Fighter_GObj* gobj)
{
    ftCo_Run_Phys(gobj);
}

void ftCo_RunDirect_Coll(Fighter_GObj* gobj)
{
    ftCo_Run_Coll(gobj);
}
