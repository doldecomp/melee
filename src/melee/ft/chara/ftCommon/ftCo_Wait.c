#include <platform.h>
#include "forward.h"

#include "ftCo_Wait.h"

#include "ftCo_08A6.h"
#include "ftCo_Attack1.h"
#include "ftCo_AttackS3.h"

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
    if (!ft_80096540(gobj) && !ft_800D695C(gobj) && !ft_800D6824(gobj) &&
        !ft_800D68C0(gobj) && !ft_800D8990(gobj) && !ft_8008BFC4(gobj) &&
        !ft_8008C830(gobj) && !ft_8008CB44(gobj) &&
        !ftCo_AttackS3_8008B658(gobj) && !ft_8008B980(gobj) &&
        !ft_8008BB44(gobj) && !ftCo_Attack1_DecideMotion(gobj) &&
        !ft_80099794(gobj) && !ft_80091A4C(gobj) &&
        !ftFx_AppealS_CheckInput(gobj) && !ft_800DE9D8(gobj) &&
        !ft_800CAED0(gobj) && !ft_800CA094(gobj) && !ft_800D5FB0(gobj) &&
        !ft_800C97DC(gobj) && !ft_800C9468(gobj))
    {
        return;
    }
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
