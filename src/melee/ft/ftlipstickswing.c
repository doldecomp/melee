#include "ftlipstickswing.h"

#include "ft/ft_0CD1.h"

#include <baselib/gobj.h>

void ftCo_LipstickSwing_Anim(HSD_GObj* gobj)
{
    ftCo_800CD1BC(gobj);
}

void ftCo_LipstickSwing_IASA(HSD_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_LipstickSwing_Phys(HSD_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_LipstickSwing_Coll(HSD_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD31C);
}
