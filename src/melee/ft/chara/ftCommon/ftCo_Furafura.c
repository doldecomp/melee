#include <platform.h>

#include "ftCo_Furafura.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

void ftCo_80099010(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Furafura,
                              Ft_MF_SkipModel | Ft_MF_SkipMatAnim, NULL, 0, 1,
                              0);
    fp->shield_health = p_ftCommonData->x280_unkShieldHealth;
    {
        float percent = p_ftCommonData->x2F8 - fp->dmg.x1830_percent;
        if (percent < 0) {
            percent = 0;
        }
        ftCommon_8007DBCC(fp, 0, percent + p_ftCommonData->x2FC);
    }
    ftCommon_8007EBAC(fp, 25, 0);
    ft_800885A8(fp, 95, 127, 64);
}

void ftCo_Furafura_Anim(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    fp->shield_health = p_ftCommonData->x280_unkShieldHealth;
    fp->x1A4C -= p_ftCommonData->x300;
    ftCommon_8007DC08(fp, p_ftCommonData->x304);
    if (fp->x1A4C <= 0) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Furafura_IASA(ftCo_GObj* gobj) {}

void ftCo_Furafura_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Furafura_Coll(ftCo_GObj* gobj)
{
    ft_80083F88(gobj);
}
