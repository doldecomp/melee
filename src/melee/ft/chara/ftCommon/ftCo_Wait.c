#include <platform.h>
#include "forward.h"

#include "ftCo_Wait.h"

#include "ftCo_08A6.h"
#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcoll.h"
#include "ft/types.h"
#include "ftFox/ftFx_AppealS.h"

#include <placeholder.h>

void ftCo_Wait_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2224_flag.bits.b2) {
        ft_800C8B74();
    } else {
        ft_8008A7A8(gobj, fp->ft_data->x24);
    }
}

void ftCo_Wait_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ft_80096540(gobj))
    RETURN_IF(ftCo_Attack100_CheckInput(gobj))
    RETURN_IF(ft_800D6824(gobj))
    RETURN_IF(ft_800D68C0(gobj))
    RETURN_IF(ftCo_Catch_CheckInput(gobj))
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj))
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj))
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj))
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj))
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj))
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj))
    RETURN_IF(ftCo_Attack1_CheckInput(gobj))
    RETURN_IF(ft_80099794(gobj))
    RETURN_IF(ft_80091A4C(gobj))
    RETURN_IF(ftFx_AppealS_CheckInput(gobj))
    RETURN_IF(ft_800DE9D8(gobj))
    RETURN_IF(ftCo_Jump_CheckInput(gobj))
    RETURN_IF(ftCo_Dash_CheckInput(gobj))
    RETURN_IF(ft_800D5FB0(gobj))
    RETURN_IF(ftCo_Turn_CheckInput(gobj))
    RETURN_IF(ftCo_Walk_CheckInput(gobj))
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
