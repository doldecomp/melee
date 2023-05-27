#include <platform.h>
#include "ft/forward.h"

#include "ftCo_Passive.h"

#include "ef/efasync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

static inline void inlineA0(ftCo_GObj* gobj, HSD_JObj* joint)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    efAsync_Spawn(gobj, &fp->x60C, 1U, 1053, joint);
}

void ftCo_800987D0(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    Fighter_ChangeMotionState(gobj, 199, Ft_MF_None, NULL, 0, 1, 0);
    ft_800881D8(fp, fp->ft_data->x4C_collisionData->x24, 127, 64);
    ft_80088148(fp, 3, 127, 64);
    ftCommon_8007CCE8(fp);
    inlineA0(gobj, fp->parts[FtPart_TopN].joint);
    ft_800BFFD0(fp, 120, 0);
}

void ftCo_Passive_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Passive_IASA(HSD_GObj* gobj) {}

void ftCo_Passive_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Passive_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}
