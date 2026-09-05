#include "ftCo_Wait.h"

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
#include "ftCo_DownSpot.h"
#include "ftCo_Escape.h"
#include "ftCo_Guard.h"
#include "ftCo_Jump.h"
#include "ftCo_SpecialS.h"
#include "ftCo_Squat.h"
#include "ftCo_Turn.h"
#include "ftCo_Walk.h"

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftwaitanim.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftFox/ftfoxappeals.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_Wait_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2224_b2) {
        ftCo_DownSpot_Enter(gobj);
    } else {
        ftCo_8008A7A8(gobj, fp->ft_data->x24);
    }
}

void ftCo_Wait_IASA(Fighter_GObj* gobj)
{
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
    RETURN_IF(ftCo_80099794(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftFx_AppealS_CheckInput(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF(ftCo_800D5FB0(gobj));
    RETURN_IF(ftCo_Turn_CheckInput(gobj));
    RETURN_IF(ftCo_Walk_CheckInput(gobj));
}

void ftCo_Wait_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftCo_Wait_Coll(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}
