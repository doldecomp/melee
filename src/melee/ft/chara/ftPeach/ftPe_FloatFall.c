#include <platform.h>
#include "ft/forward.h"

#include "ftPe_FloatFall.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ftCommon/ftCo_FallSpecial.h"

#include <baselib/gobj.h>

void ftPe_FloatFall_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CCDA8(gobj);
    }
}

void ftPe_FloatFall_IASA(HSD_GObj* gobj) {}

void ftPe_FloatFall_Phys(HSD_GObj* gobj)
{
    ft_800CC6C8();
}

void ftPe_FloatFall_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ft_80096CC8, ft_80082B1C);
}
