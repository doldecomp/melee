#include "ftCo_Furafura.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

void ftCo_80099010(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Furafura,
                              Ft_MF_SkipModel | Ft_MF_SkipMatAnim, 0, 1, 0,
                              NULL);
    fp->shield_health = p_ftCommonData->x280_unkShieldHealth;
    {
        float percent = p_ftCommonData->x2F8 - fp->dmg.x1830_percent;
        if (percent < 0) {
            percent = 0;
        }
        ftCommon_InitGrab(fp, 0, percent + p_ftCommonData->x2FC);
    }
    ftCommon_8007EBAC(fp, 25, 0);
    ft_800885A8(fp, 95, 127, 64);
}

void ftCo_Furafura_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    fp->shield_health = p_ftCommonData->x280_unkShieldHealth;
    fp->grab_timer -= p_ftCommonData->x300;
    ftCommon_8007DC08(fp, p_ftCommonData->x304);
    if (fp->grab_timer <= 0) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Furafura_IASA(Fighter_GObj* gobj) {}

void ftCo_Furafura_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Furafura_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
