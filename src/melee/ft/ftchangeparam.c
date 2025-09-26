#include "ftchangeparam.h"

#include <melee/ft/fighter.h>
#include <melee/ft/inlines.h>

float ftCo_CalcYScaledKnockback(float arg0, float scale, float arg2)
{
    if (scale == 0.0F) {
        __assert("ftchangeparam.c", 0x1E, "scale != 0.0F");
    }
    if (arg2 == 0.0F) {
        return arg0;
    }
    if (arg2 < 0.0F) {
        return arg0 / ftCo_CalcYScaledKnockback(1.0F, scale, -arg2);
    }
    if (scale >= 1.0F || arg2 <= 1.0F) {
        return (scale - 1.0F) * arg0 * arg2 + arg0;
    }
    return arg0 * scale / arg2;
}

/// #ftCo_CalcYScaledKnockback

/// #ftCo_800CF6E8

/// #ftCo_800D0CBC

float ftCo_800D0EC8(Fighter* fp)
{
    return -ftCo_CalcYScaledKnockback(Fighter_804D6524[12], fp->x34_scale.y,
                                      p_ftCommonData->x310);
}

void ftCo_800D0FA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->co_attrs = *fp->ft_data->x0;

    {
        Vec4* temp_r4 = fp->ft_data->x40;
        fp->x294_itPickup.gr_light_offset = temp_r4[0];
        fp->x294_itPickup.gr_heavy_offset = temp_r4[1];
        fp->x294_itPickup.air_light_offset = temp_r4[2];
        fp->x2C4 = *fp->ft_data->x50;
    }
}

/// #ftCo_800D105C
