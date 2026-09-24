#include <melee/ft/kinds/ftCommon/ftCo_RunDirect.h>

#include <melee/ft/forward.h>

#include <melee/ft/kinds/ftCommon/ftCo_AppealS.h>
#include <melee/ft/kinds/ftCommon/ftCo_Attack100.h>
#include <melee/ft/kinds/ftCommon/ftCo_AttackDash.h>
#include <melee/ft/kinds/ftCommon/ftCo_Guard.h>
#include <melee/ft/kinds/ftCommon/ftCo_Jump.h>
#include <melee/ft/kinds/ftCommon/ftCo_Run.h>
#include <melee/ft/kinds/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

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
